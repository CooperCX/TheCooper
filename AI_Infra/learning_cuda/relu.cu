#include <cuda_runtime.h>
#include <iostream>
#include <vector>

/**
 * 1. GPU 端的“工作手册”（核函数）
 * 每个线程都会看到这份说明书，并执行对应的计算。
 */
__global__ void relu_kernel(float* data, int n) {
    // 计算当前员工的全局编号
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    // 只有在数据范围内才干活
    if (i < n) {
        // ReLU 逻辑：如果小于 0，变成 0
        if (data[i] < 0.0f) {
            data[i] = 0.0f;
        }
    }
}

/**
 * 2. CPU 端的“厂长逻辑”
 */
int main() {
    int n = 10;                     // 我们处理 10 个数
    size_t bytes = n * sizeof(float);

    // --- A. 在 CPU (Host) 上准备原始原料 ---
    std::vector<float> h_data = {-2.0, -1.0, 0.0, 1.0, 2.0, -5.0, 3.0, -0.5, 4.0, 10.0};
    std::vector<float> h_result(n); 

    // --- B. 在 GPU (Device) 上租用仓库空间 ---
    float* d_data;
    cudaMalloc(&d_data, bytes);     // 这个函数在显存里开辟空间

    // --- C. 把原料从 CPU 运到 GPU ---
    // cudaMemcpyHostToDevice 表示：搬运方向是从 CPU 到 GPU
    cudaMemcpy(d_data, h_data.data(), bytes, cudaMemcpyHostToDevice);

    // --- D. 调用核函数，开工！ ---
    // <<<网格数, 每个块的线程数>>> 这里的 (1, 256) 表示：
    // 我们启动 1 个线程块，里面包含 256 个工位（虽然我们只处理 10 个数，但也足够了）
    relu_kernel<<<1, 256>>>(d_data, n);

    // 等待 GPU 干完活（同步）
    cudaDeviceSynchronize();

    // --- E. 把成品从 GPU 运回 CPU ---
    // cudaMemcpyDeviceToHost 表示：搬运方向是从 GPU 到 CPU
    cudaMemcpy(h_result.data(), d_data, bytes, cudaMemcpyDeviceToHost);

    // --- F. 验证结果 ---
    std::cout << "ReLU 运行结果:" << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << h_data[i] << " -> " << h_result[i] << std::endl;
    }

    // --- G. 释放 GPU 仓库（好借好还） ---
    cudaFree(d_data);

    return 0;
}
