#include <iostream>
#include <vector>

#include "cuda_runtime.h"

// ==========================================
// 1. Device 端：定义 Kernel 核函数
// ==========================================
__global__ void vector_square_kernel(const float* d_in, float* d_out, int N) {
    // 每一个进入 Kernel 的线程，第一件事就是寻找自己的身份定位
    int global_tid = blockIdx.x * blockDim.x + threadIdx.x;

    // 边界检查：防止最后 24 个冗余线程发生越界内存访问 (Segmentation Fault)
    if (global_tid < N) {
        d_out[global_tid] = d_in[global_tid] * d_in[global_tid];
    }
}

// ==========================================
// 2. Host 端：主程序控制流
// ==========================================
int main() {
    int N = 1000;
    size_t size = N * sizeof(float);

    // [A] 在 CPU 内存准备初始数据
    std::vector<float> h_in(N);
    std::vector<float> h_out(N, 0.0f);
    for (int i = 0; i < N; ++i) {
        h_in[i] = static_cast<float>(i);
    }

    // [B] 声明显存指针并在 GPU 端租用空间
    float *d_in = nullptr, *d_out = nullptr;
    cudaMalloc((void**)&d_in, size);
    cudaMalloc((void**)&d_out, size);

    // [C] 将数据从 Host (内存) 拷贝到 Device (显存)
    cudaMemcpy(d_in, h_in.data(), size, cudaMemcpyHostToDevice);

    // [D] 核心：配置 Kernel 的执行拓扑参数
    int block_size = 128;                               // 一个车间 128 个工人
    int grid_size = (N + block_size - 1) / block_size;  // 向上取整计算车间总数 (这里结果为 8)

    // [E] 启动 Kernel (Launch Kernel)
    // 注意 <<< >>> 语法，这是 nvcc 编译器特有的 Execution Configuration (执行配置)
    vector_square_kernel<<<grid_size, block_size>>>(d_in, d_out, N);

    // [F] CUDA 是异步执行的，必须同步以确保结果算完！
    cudaDeviceSynchronize();

    // [G] 将结果从 Device 运回 Host
    cudaMemcpy(h_out.data(), d_out, size, cudaMemcpyDeviceToHost);

    // [H] 释放显存，防止显存泄漏 (OOM)
    cudaFree(d_in);
    cudaFree(d_out);

    // 验证结果（打印前 5 个）
    std::cout << "GPU computation completed. Previewing first 5 results:" << std::endl;
    for (int i = 0; i < 5; ++i) {
        std::cout << h_in[i] << "^2 = " << h_out[i] << std::endl;
    }

    return 0;
}
