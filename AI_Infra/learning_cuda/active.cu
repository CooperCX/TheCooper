#include <cmath>
#include <vector>

#include "cuda_stub/cuda_runtime.h"

__global__ void sigmoid_kernel(const float* x, float* y, int N) {
    int global_tid = blockIdx.x * blockDim.x + threadIdx.x;

    if (global_tid < N) {
        y[global_tid] = 1.0f / (1 + expf(-x[global_tid]));
    }
}

__global__ void tanh_kernel(const float* x, float* y, int N) {
    int global_tid = blockIdx.x * blockDim.x + threadIdx.x;

    if (global_tid < N) {
        float val = x[global_tid];
        y[global_tid] = tanhf(val);
    }
}

__global__ void relu_kernel(const float* x, float* y, int N) {
    int global_tid = blockIdx.x * blockDim.x + threadIdx.x;

    if (global_tid < N) {
        y[global_tid] = fmaxf(0.0f, x[global_tid]);
    }
}

__global__ void leaky_relu_kernel(const float* x, float* y, int N, float alpha = 0.01f) {
    int global_tid = blockIdx.x * blockDim.x + threadIdx.x;

    if (global_tid < N) {
        float val = x[global_tid];
        y[global_tid] = fmaxf(val, alpha * val);
    }
}

__global__ void silu_kernel(const float* x, float* y, int N) {
    int global_tid = blockIdx.x * blockDim.x + threadIdx.x;

    if (global_tid < N) {
        float val = x
            [global_tid];  // 将显存（Global
                           // Memory）中的数据先读取到寄存器（Register）如果接下来需要多次使用这个值，直接从寄存器读取会非常快
        y[global_tid] = val / (1.0f + expf(-val));
    }
}

__global__ void gelu_exact_kernel(const float* x, float* y, int N) {
    int global_tid = blockIdx.x * blockDim.x + threadIdx.x;

    if (global_tid < N) {
        float val = x[global_tid];
        const float M_SQRT1_2_F = 0.70710678118654752440f;

        y[global_tid] = 0.5f * val * (1.0f + erff(val * M_SQRT1_2_F));
    }
}

__global__ void gelu_approx_kernel(const float* x, float* y, int N) {
    int global_tid = blockIdx.x * blockDim.x + threadIdx.x;

    // GeLU_Approx(x) = 0.5 * x * [ 1.0 + tanh( sqrt(2 / pi) * (x + 0.044715 * x^3) ) ]
    if (global_tid < N) {
        float val = x[global_tid];
        const float SQRT_2_OVER_PI = 0.7978845608028654f;  // sqrt(2/pi)
        const float COEF = 0.044715f;

        float val_sq = val * val;
        float polynomial = SQRT_2_OVER_PI * (1.0f + COEF * val_sq);
        float inner = val * polynomial;

        y[global_tid] = 0.5f * val * (1.0f + tanhf(inner));
    }
}

__global__ void relu_float4_kernel(const float* x, float* y, int N) {
    const float4* x_vec = reinterpret_cast<const float4*>(x);
    float4* y_vec = reinterpret_cast<float4*>(y);

    int N_vec = N / 4;

    int global_tid = blockIdx.x * blockDim.x + threadIdx.x;

    if (global_tid < N_vec) {
        float4 val = x_vec[global_tid];
        float4 out;
        out.x = fmaxf(0.0f, val.x);
        out.y = fmaxf(0.0f, val.y);
        out.z = fmaxf(0.0f, val.z);
        out.w = fmaxf(0.0f, val.w);

        y_vec[global_tid] = out;
    }

    int remain_start = N_vec * 4;
    int remain_idx = remain_start + global_tid;
    if (global_tid < (N % 4) && remain_idx < N) {
        y[remain_idx] = fmaxf(0.0f, x[remain_idx]);
    }
}

// Safe Softmax 激活函数 (单 Block 处理一行数据版)
// 面试核心：归约 (Reduction)、Shared Memory 缓存通信、防溢出技巧 (Max Subtraction)
// 假设：N 是矩阵的一行
__global__ void safe_softmax_kernel(const float* x, float* y, int N) {
    int row_idx = blockIdx.x;
    int tid = threadIdx.x;
    int hidden_size = blockDim.x;

    // 🌟 核心：指针偏移到属于我这一行的数据开头！
    const float* my_row_in = x + row_idx * N;
    float* my_row_out = y + row_idx * N;

    __shared__ float s_data[1024];

    float val = (tid < N) ? my_row_in[tid] : -INFINITY;
    s_data[tid] = val;

    __syncthreads();

    // 第一步：找全局最大值 (Max Reduction)
    for (int stride = hidden_size / 2; stride > 0; stride >>= 1) {
        if (tid < stride) {
            s_data[tid] = fmaxf(s_data[tid], s_data[tid + stride]);
        }
        __syncthreads();
    }
    float max_val = s_data[0];
    __syncthreads();

    // 第二步：算指数及其总和 (Sum Reduction)
    float exp_val = 0.0f;
    if (tid < N) {
        exp_val = expf(val - max_val);
    }
    s_data[tid] = exp_val;

    __syncthreads();

    for (int stride = hidden_size / 2; stride > 0; stride >>= 1) {
        if (tid < stride) {
            s_data[tid] += s_data[tid + stride];
        }
        __syncthreads();
    }

    float exp_sum = s_data[0];

    // 第三步：计算最终概率并写回显存
    if (tid < N) {
        my_row_out[tid] = exp_val / exp_sum;
    }
}

int main() {
    // 设定测试的数据规模 (1000 万个浮点数，约 40MB 数据)
    const int rows = 10000;
    const int cols = 1024;
    const int N = rows * cols;
    const int bytes = N * sizeof(float);

    // 1. Host (CPU) 端申请内存并初始化
    std::vector<float> h_in(N);
    std::vector<float> h_out(N);

    // 生成一些测试数据，包含正负数
    for (int i = 0; i < N; ++i) {
        h_in[i] = (i & 1) ? -1.0f : 1.0f;
    }

    // 2. Device (GPU) 端申请显存
    float *d_in = nullptr, *d_out = nullptr;
    cudaMalloc((void**)&d_in, bytes);
    cudaMalloc((void**)&d_out, bytes);

    // 3. 将数据从 Host 拷贝到 Device (H2D)
    cudaMemcpy(d_in, h_in.data(), bytes, cudaMemcpyHostToDevice);

    // 4. 执行 kernel 函数
    safe_softmax_kernel<<<rows, cols>>>(d_in, d_out, cols);

    // 等待 GPU 真的执行完毕 (因为 Kernel 启动是异步的!)
    cudaDeviceSynchronize();

    cudaMemcpy(h_out.data(), d_out, bytes, cudaMemcpyDeviceToHost);
    // 5. 释放资源，好习惯
    cudaFree(d_in);
    cudaFree(d_out);

    return 0;
}