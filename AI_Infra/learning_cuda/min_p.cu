#include <cmath>

#include <cuda_runtime.h>

// 设定: 假设用单个 Block 内的 1024 个线程，去清洗高达 128,000 个单词的分布概率
#define THREAD_SIZE 1024

// 极速采样算子：Min-P 概率过滤
__global__ void min_p_kernel(float* probs, int vocab_size, float min_p) {
    int tid = threadIdx.x;

    __shared__ float s_data[THREAD_SIZE];

    float local_max = 0.0f;
    for (int i = tid; i < vocab_size; i += blockDim.x) {
        local_max = fmaxf(local_max, probs[i]);
    }

    s_data[tid] = local_max;

    __syncthreads();

    for (int stride = blockDim.x / 2; stride > 0; stride >>= 1) {
        if (tid < stride) {
            s_data[tid] = fmaxf(s_data[tid], s_data[tid + stride]);
        }

        __syncthreads();
    }

    __shared__ float threald;
    if (tid == 0) {
        threald = min_p * s_data[tid];
    }

    __syncthreads();

    for (int i = tid; i < vocab_size; i += blockDim.x) {
        probs[i] = (probs[i] > threald) ? probs[i] : 0.0f;
    }
}