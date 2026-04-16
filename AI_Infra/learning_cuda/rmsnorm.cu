#include <cuda_runtime.h>
#include <iostream>
#include <vector>
#include <cmath>

/**
 * RMSNorm 核函数：实现协作求和（规约）
 * 为了简单，我们让一个 Block 处理一个包含 256 个元素的向量
 */
__global__ void rmsnorm_kernel(float* data, float eps, int n) {
    // 每一个车间（Block）都有一块公共的“黑板”
    // __shared__ 关键字定义的变量存放在 GPU 的 L1 缓存附近，速度极快
    __shared__ float s_sum_sq[256];

    int tid = threadIdx.x; // 线程在车间内的编号

    // 1. 每个工人算出自己那份数据的平方，写到黑板上
    if (tid < n) {
        s_sum_sq[tid] = data[tid] * data[tid];
    } else {
        s_sum_sq[tid] = 0.0f;
    }

    // --- 厂长吹哨：等待所有人写完黑板 ---
    __syncthreads();

    // 2. 团队协作：锦标赛式求和 (Parallel Reduction)
    // 256人 -> 128人 -> 64人 ... -> 1人
    for (int stride = blockDim.x / 2; stride > 0; stride /= 2) {
        if (tid < stride) {
            s_sum_sq[tid] += s_sum_sq[tid + stride];
        }
        // 每一轮合并完，都要吹哨等所有人跟上
        __syncthreads();
    }

    // 现在，s_sum_sq[0] 里存储的就是整行数据的平方和了！

    // 3. 计算缩放因子 (Scale)
    // 我们让 0 号员工来算这个共享的值，然后再分发给大家
    __shared__ float scale;
    if (tid == 0) {
        float mean_sq = s_sum_sq[0] / n;
        scale = 1.0f / sqrtf(mean_sq + eps);
    }

    // 吹哨：等 0 号员工算出 scale
    __syncthreads();

    // 4. 最终步：每个人把自己的数据乘以缩放因子
    if (tid < n) {
        data[tid] *= scale;
    }
}

int main() {
    int n = 256;
    float eps = 1e-5f;
    size_t bytes = n * sizeof(float);

    // CPU 准备数据
    std::vector<float> h_data(n);
    for (int i = 0; i < n; i++) h_data[i] = (float)i;

    // GPU 租地并运货
    float* d_data;
    cudaMalloc(&d_data, bytes);
    cudaMemcpy(d_data, h_data.data(), bytes, cudaMemcpyHostToDevice);

    // 开工：1 个 Block 负责这 256 个数
    rmsnorm_kernel<<<1, 256>>>(d_data, eps, n);

    // 运回结果
    std::vector<float> h_result(n);
    cudaMemcpy(h_result.data(), d_data, bytes, cudaMemcpyDeviceToHost);

    // 打印前几个结果验证
    std::cout << "RMSNorm 结果预览:" << std::endl;
    for (int i = 0; i < 5; i++) {
        std::cout << "Original[" << i << "]: " << h_data[i] 
                  << " -> Normed: " << h_result[i] << std::endl;
    }

    cudaFree(d_data);
    return 0;
}
