#include <iostream>
#include <vector>
#include <cmath>
#include "cuda_runtime.h"
// #include "cuda_stub/cuda_runtime.h" // 根据你的 IDE 环境自行决定是否启用

// ==========================================
// 高性能 Fused Online Softmax
// 逻辑：启动足够的 Block 对应矩阵的行。
// 每个 Block 里的 blockDim 个线程协作处理一整行。
// ==========================================
__global__ void block_online_softmax_kernel(const float* X, float* Y, int N) {
    // blockIdx.x 代表当前在处理矩阵的哪一行
    const float* row_x = X + blockIdx.x * N;
    float* row_y = Y + blockIdx.x * N;

    int tid = threadIdx.x; // 车间内的工人编号

    // ----------------------------------------------------
    // Phase 1: Thread-Local 在线归约 (工人在自己的跑道上贪吃蛇)
    // ----------------------------------------------------
    float local_m = -INFINITY;
    float local_d = 0.0f;

    // Grid-Stride Loop: 如果一行有 2000 个数，但这车间只有 128 人，大家就跑多圈
    for (int i = tid; i < N; i += blockDim.x) {
        float val = row_x[i];

        // 🔥 核心的在线数学打折机制 🔥
        float new_m = fmaxf(local_m, val);
        local_d = local_d * expf(local_m - new_m) + expf(val - new_m);
        local_m = new_m;
    }

    // ----------------------------------------------------
    // Phase 2: Block-Level 汇总 (厂长合并大家的账本)
    // 刚才所有人都算出了自以为的极大值，现在要通过大家都看得见的黑板进行汇总
    // ----------------------------------------------------
    // 申请一块外部传入尺寸的 Shared Memory 作为黑板
    extern __shared__ float s_mem[];
    float* s_m = s_mem;                  // 前半段给 Maximum 存放
    float* s_d = s_mem + blockDim.x;     // 后半段给 Denominator(分母) 存放

    s_m[tid] = local_m; // 每个人把自己的结果写上黑板
    s_d[tid] = local_d;
    __syncthreads();    // 严禁抢乱：吹哨等所有人都写完

    // 为了最直观的教学展示，我们让 0 号线程（队长）通过遍历黑板来汇总。
    // （在真实的高级工程里，这里会用昨天的 Warp Shuffle 进行树状折叠，以达到纳秒级速度）
    if (tid == 0) {
        float block_m = -INFINITY;
        float block_d = 0.0f;
        for (int i = 0; i < blockDim.x; ++i) {
            float m = s_m[i];
            float d = s_d[i];
            
            // 🔥 这里又发生了一次同样原理的打折合并！🔥
            // 把各个工人手里段落的旧账，合并成整个车间的终极老账
            float new_m = fmaxf(block_m, m);
            block_d = block_d * expf(block_m - new_m) + d * expf(m - new_m);
            block_m = new_m;
        }
        // 队长把车间的最终王者值，广播放到黑板的第 0 格
        s_m[0] = block_m;
        s_d[0] = block_d;
    }
    __syncthreads(); // 再次吹哨：所有人必须等队长算出车间最终值！

    // 所有工人去黑板读最终的王者数据
    float final_m = s_m[0];
    float final_d = s_d[0];

    // ----------------------------------------------------
    // Phase 3: 无可奈何的第二次回头 (Materialize Y 输出阶段)
    // 因为这是一个基础算子，没有融合 V 矩阵，所以必须开环算完写进内存。
    // ----------------------------------------------------
    for (int i = tid; i < N; i += blockDim.x) {
        // 利用最终真理的 final_m 和 final_d 进行绝对不会溢出的概率运算
        row_y[i] = expf(row_x[i] - final_m) / final_d;
    }
}

// ==========================================
// Host 端驱动代码：搭建环境并执行
// ==========================================
int main() {
    int batch_size = 1;     // 我们就处理一行数据
    int N = 2000;           // 这行有 2000 长度
    size_t size = batch_size * N * sizeof(float);

    std::vector<float> h_x(N);
    std::vector<float> h_y(N, 0.0f);

    // 人造一些易爆数值：如果这里直接指数 expf(100+i)，普通算法早溢出变 Inf 了。
    for (int i = 0; i < N; ++i) {
        h_x[i] = -50.0f + static_cast<float>(i) * 0.1f; 
    }

    float *d_x, *d_y;
    cudaMalloc(&d_x, size);
    cudaMalloc(&d_y, size);
    cudaMemcpy(d_x, h_x.data(), size, cudaMemcpyHostToDevice);

    // 执行拓扑规划
    int block_size = 128; // 一个车间 128 号工位
    int grid_size = batch_size; // 有几行矩阵就开几个车间处理

    // 要给厂长留够黑板空间存放 M 和 D（每个分别长 block_size）
    size_t shared_mem_size_bytes = 2 * block_size * sizeof(float);

    // Launch! 注意 <<< >>> 中的第三个参数，表示运行时动态为 Shared Memory 拨发内存大小
    block_online_softmax_kernel<<<grid_size, block_size, shared_mem_size_bytes>>>(d_x, d_y, N);

    cudaDeviceSynchronize();
    cudaMemcpy(h_y.data(), d_y, size, cudaMemcpyDeviceToHost);

    // 验证成果：
    std::cout << "===== Fused Online Softmax 执行结果 (末尾5项) =====" << std::endl;
    for (int i = N - 5; i < N; ++i) {
        std::cout << "Original[" << i << "]: " << h_x[i] << "  --> Softmax Prob: " << h_y[i] << std::endl;
    }

    cudaFree(d_x);
    cudaFree(d_y);

    return 0;
}
