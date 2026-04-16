#include <cuda_runtime.h>
#include <iostream>
#include <vector>

/**
 * 向量加法核函数：C = A + B
 */
__global__ void vector_add_kernel(const float* A, const float* B, float* C, int n) {
    // 核心公式：计算全局唯一的线程编号
    // blockIdx.x: 当前是第几个车间 (Block)
    // blockDim.x: 每个车间有多少工位 (Threads per block)
    // threadIdx.x: 你在当前车间是第几个工位
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i < n) {
        C[i] = A[i] + B[i];
    }
}

int main() {
    int n = 100000;                  // 10 万个数据，一个车间装不下了
    size_t bytes = n * sizeof(float);

    // 1. CPU 上准备数据
    std::vector<float> h_A(n, 1.0f); // 全是 1.0
    std::vector<float> h_B(n, 2.0f); // 全是 2.0
    std::vector<float> h_C(n);

    // 2. GPU 上租地
    float *d_A, *d_B, *d_C;
    cudaMalloc(&d_A, bytes);
    cudaMalloc(&d_B, bytes);
    cudaMalloc(&d_C, bytes);

    // 3. 把货运进厂
    cudaMemcpy(d_A, h_A.data(), bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B.data(), bytes, cudaMemcpyHostToDevice);

    // 4. 重头戏：配置工厂参数
    int threads_per_block = 256;     // 固定每个车间 256 人
    
    // 计算需要多少个车间？
    // 技巧：(n + threads_per_block - 1) / threads_per_block
    // 这能保证向上取整，比如 257 个数据就需要 2 个车间。
    int blocks_per_grid = (n + threads_per_block - 1) / threads_per_block;

    std::cout << "启动工厂设置：" << std::endl;
    std::cout << "数据总量: " << n << std::endl;
    std::cout << "每个 Block 线程数: " << threads_per_block << std::endl;
    std::cout << "计算出的 Block 数量: " << blocks_per_grid << std::endl;

    // 发布指令：<<<Block 数, 每个 Block 的线程数>>>
    vector_add_kernel<<<blocks_per_grid, threads_per_block>>>(d_A, d_B, d_C, n);

    // 5. 运送成品回 CPU
    cudaMemcpy(h_C.data(), d_C, bytes, cudaMemcpyDeviceToHost);

    // 6. 验证前 5 个结果
    for (int i = 0; i < 5; i++) {
        std::cout << h_A[i] << " + " << h_B[i] << " = " << h_C[i] << std::endl;
    }

    // 7. 清理
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    return 0;
}
