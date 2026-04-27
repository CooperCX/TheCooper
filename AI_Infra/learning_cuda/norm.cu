#include <cmath>
#include <cstddef>
#include <vector>

#include "cuda_stub/cuda_runtime.h"

#define HIDDEN_SIZE 1024

// 1 个 Block 处理一行 (一个 Token)
__global__ void layer_norm_kernel(const float* x, const float* gamma, const float* beta, float* y, float episilon) {
    int row = blockIdx.x;
    int tid = threadIdx.x;

    const float* my_row_in = x + row * HIDDEN_SIZE;
    float* my_row_out = y + row * HIDDEN_SIZE;

    __shared__ float s_data[HIDDEN_SIZE];
    __shared__ float s_mean;
    __shared__ float s_var;

    float val = (tid < HIDDEN_SIZE) ? my_row_in[tid] : 0.0f;
    s_data[tid] = val;

    __syncthreads();

    for (int stride = blockDim.x / 2; stride > 0; stride >>= 1) {
        if (tid < stride) {
            s_data[tid] += s_data[tid + stride];
        }

        __syncthreads();
    }

    if (tid == 0) {
        s_mean = s_data[tid] / HIDDEN_SIZE;
    }

    __syncthreads();

    float diff = val - s_mean;
    s_data[tid] = (tid < HIDDEN_SIZE) ? (diff * diff) : 0.0f;

    __syncthreads();

    for (int stride = blockDim.x / 2; stride > 0; stride >>= 1) {
        if (tid < stride) {
            s_data[tid] += s_data[tid + stride];
        }

        __syncthreads();
    }

    if (tid == 0) {
        s_var = s_data[tid] / HIDDEN_SIZE;
    }

    __syncthreads();

    if (tid < HIDDEN_SIZE) {
        float inv_std = rsqrtf(s_var + episilon);
        my_row_out[tid] = (val - s_mean) * inv_std * gamma[tid] + beta[tid];
    }
}

// 1 个 Block 处理一行 (一个 Token)
__global__ void rms_norm_kernel(const float* x, const float* gamma, float* y, float episilon) {
    int row = blockIdx.x;
    int tid = threadIdx.x;

    const float* my_row_in = x + row * HIDDEN_SIZE;
    float* my_row_out = y + row * HIDDEN_SIZE;

    __shared__ float s_data[HIDDEN_SIZE];
    __shared__ float s_rms;

    float val = (tid < HIDDEN_SIZE) ? my_row_in[tid] : 0.0f;
    s_data[tid] = val * val;

    __syncthreads();

    for (int stride = blockDim.x / 2; stride > 0; stride >>= 1) {
        if (tid < stride) {
            s_data[tid] += s_data[tid + stride];
        }

        __syncthreads();
    }

    if (tid == 0) {
        s_rms = rsqrtf(s_data[tid] / HIDDEN_SIZE + episilon);
    }

    __syncthreads();

    if (tid < HIDDEN_SIZE) {
        my_row_out[tid] = gamma[tid] * (val * s_rms);
    }
}

int main() {
    int N = 10000 * 1024;
    int bytes = N * sizeof(float);

    std::vector<float> h_in(N);
    std::vector<float> h_out(N, 0.0f);

    for (int i = 0; i < N; ++i) {
        h_in[i] = (i & 1) ? -1.0f : 1.0f;
    }

    float *d_in = nullptr, *d_out = nullptr;
    cudaMalloc((void**)&d_in, bytes);
    cudaMalloc((void**)&d_out, bytes);

    cudaMemcpy(d_in, h_in.data(), bytes, cudaMemcpyHostToDevice);

    // 每一行用的都是同一套 Gamma 和 Beta, 只需要 Hidden Size 个
    std::vector<float> h_gamma(1024);
    std::vector<float> h_beta(1024);

    for (int i = 0; i < 1024; ++i) {
        h_gamma[i] = (i & 1) ? -1.0f : 1.0f;
        h_beta[i] = (i & 1) ? -2.0f : 2.0f;
    }

    int hidden_bytes = 1024 * sizeof(float);

    float *gamma = nullptr, *beta = nullptr;
    cudaMalloc((void**)&gamma, hidden_bytes);
    cudaMalloc((void**)&beta, hidden_bytes);

    cudaMemcpy(gamma, h_gamma.data(), hidden_bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(beta, h_beta.data(), hidden_bytes, cudaMemcpyHostToDevice);

    int blockSize = 1024;
    int numBlocks = (N + blockSize - 1) / blockSize;

    layer_norm_kernel<<<numBlocks, blockSize>>>(d_in, gamma, beta, d_out, 0.000001f);

    cudaDeviceSynchronize();

    cudaMemcpy(h_out.data(), d_out, bytes, cudaMemcpyDeviceToHost);

    cudaFree(d_in);
    cudaFree(d_out);
    cudaFree(gamma);
    cudaFree(beta);

    return 0;
}