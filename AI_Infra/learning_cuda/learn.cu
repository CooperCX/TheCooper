#include <vector>

#include <cuda_runtime.h>

// ==========================================
// 核心算子 1：Global Memory 基础访问
// 面试考点：全局线程索引的计算与边界防御
// ==========================================
__global__ void vector_square_kernel(const float* d_in, float* d_out, int N) {
    // 经典寻址公式：我是所有工人中的第几个？
    int global_tid = blockIdx.x * blockDim.x + threadIdx.x;
    
    // 边界检查：防御最后几个多余工人的越界访问 (防止 SegFault)
    if (global_tid < N) {
        d_out[global_tid] = d_in[global_tid] * d_in[global_tid];
    }
}

// ==========================================
// 核心算子 2：Shared Memory 优化设计
// 面试考点：局部缓存、线程同步、全局与局部索引视角的切换
// ==========================================
__global__ void moving_average_kernel(const float* d_in, float* d_out, int N) {
    // 【硬件黑板】分配在 SM 的 L1 缓存旁边，Block 内 128 人共享，速度极快
    __shared__ float s_data[128];

    int tid = threadIdx.x; // Block 内部的局部工人编号 (0-127，用于操作黑板)
    int global_tid = blockIdx.x * blockDim.x + threadIdx.x; // 全局编号 (用于操作 Global Memory 仓库)

    // 第一步：将慢速仓库 (Global) 数据搬运到高速缓存 (Shared)
    if (global_tid < N) {
        s_data[tid] = d_in[global_tid];
    } else {
        s_data[tid] = 0.0f; // 越界部分置 0，保持缓存清洁
    }

    // ⭐ 核心原语：块内屏障同步 (Block-level Barrier)
    // 强制等待，直到本车间所有人把数据贴在黑板上，防止 Race Condition！
    __syncthreads();

    // 第二步：利用高速缓存进行邻域计算
    if (global_tid < N - 1) {
        float left = s_data[tid]; // 自己：极速读取黑板
        
        // 面试极致边界：最右边边缘的人 (`tid == 127`) 的邻居在隔壁车间
        // 由于黑板只在车间内共享，他必须去满速仓库 (d_in) 读取
        float right = (tid < 127) ? s_data[tid + 1] : d_in[global_tid + 1];

        // 写入结果（注意 C++ 优先级，加上括号）
        d_out[global_tid] = (left + right) / 2.0f;
    }
}

// ==========================================
// 核心算子 3：Warp-level Register 优化
// 面试考点：无锁归约、寄存器洗牌 (FlashAttention 地基)
// ==========================================
__device__ float warp_reduce_sum(float val) {
    // 32 个人的小队 (Warp)，在寄存器级别彼此偷看对方的数据进行二叉树归并
    // 5 行极低延迟的汇编指令执行完毕后，0 号队长持有 32 个人的总和！
    val += __shfl_down_sync(0xFFFFFFFF, val, 16);
    val += __shfl_down_sync(0xFFFFFFFF, val, 8);
    val += __shfl_down_sync(0xFFFFFFFF, val, 4);
    val += __shfl_down_sync(0xFFFFFFFF, val, 2);
    val += __shfl_down_sync(0xFFFFFFFF, val, 1);

    return val;
}

// 这个算子展示了底层 `__device__` 技巧如何被上层 Kernel 嵌入并调用的全过程
__global__ void array_sum_kernel(const float* d_in, float* d_out, int N) {
    int global_tid = blockIdx.x * blockDim.x + threadIdx.x;

    // 获取个人的数据进寄存器
    float my_val = (global_tid < N) ? d_in[global_tid] : 0.0f;

    // 【寄存器极限优化阶段】一瞬间获取整队 32 人的总和 (摒弃 Shared Memory)
    float sum_of_warp = warp_reduce_sum(my_val);

    // 筛选出本小队队长 (在队内排名 0 号)
    int lane_id = threadIdx.x % 32;
    if (lane_id == 0) {
        // 【最差情况保护机制阶段】这虽然是硬件级原子加，但它是排队串行操作。
        // 上面的一通操作使得来撞这座锁排队的人从 1000 瞬间将降到了 30 个。极大缓解争用！
        atomicAdd(d_out, sum_of_warp);
    }
}

// 主机控制流代码：标准的分配与执行脚手架
int main() {
    int N = 1000;
    int size = N * sizeof(float);

    std::vector<float> h_in(N);
    std::vector<float> h_out(N, 0.0f);
    for (int i = 0; i < N; ++i) {
        h_in[i] = static_cast<float>(i);
    }

    float *d_in = nullptr, *d_out = nullptr;
    cudaMalloc((void**)&d_in, size);
    cudaMalloc((void**)&d_out, size);

    cudaMemcpy(d_in, h_in.data(), size, cudaMemcpyHostToDevice);

    int block_size = 128;
    int grid_size = (N + block_size - 1) / block_size;

    // 执行配置 (Execution Configuration) 
    vector_square_kernel<<<grid_size, block_size>>>(d_in, d_out, N);

    // 等待异步 Kernel 彻底执行完毕，保障接下来内存拷贝不会拿走垃圾值
    cudaDeviceSynchronize();

    cudaMemcpy(h_out.data(), d_out, size, cudaMemcpyDeviceToHost);

    cudaFree(d_in);
    cudaFree(d_out);

    return 0;
}