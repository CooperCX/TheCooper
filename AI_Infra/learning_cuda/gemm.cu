#include "cuda_stub/cuda_runtime.h"

// Lv1: Naive GEMM (朴素版本)
// C = A * B
// A (M x K), B (K x N) -> C (M x N)
__global__ void naive_gemm_kernel(const float* A, const float* B, float* C, int M, int N, int K) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < M && col < N) {
        float sum = 0.0f;

        for (int i = 0; i < K; ++i) {
            sum += A[row * K + i] * B[i * N + col];
        }

        C[row * N + col] = sum;
    }
}

// Lv2: Tiled GEMM 利用共享内部分块优化
// 默认假设 TILE_SIZE 设置为 32，矩阵长宽都是 32 的倍数
#define TILE_SIZE 32
__global__ void tiled_gemm_kernel(const float* A, const float* B, float* C, int M, int N, int K) {
    // 两个二维(Shared Memory)，供全 Block 共享
    __shared__ float S_A[TILE_SIZE][TILE_SIZE];
    __shared__ float S_B[TILE_SIZE][TILE_SIZE];

    int ty = threadIdx.y;
    int tx = threadIdx.x;

    int row = blockIdx.y * TILE_SIZE + ty;
    int col = blockIdx.x * TILE_SIZE + tx;

    int num_tiles = (K + TILE_SIZE - 1) / TILE_SIZE;

    float sum = 0.0f;
    for (int t = 0; t < num_tiles; ++t) {
        // 1. S_A
        if (row < M && (t * TILE_SIZE + tx) < K) {
            S_A[ty][tx] = A[row * K + (t * TILE_SIZE + tx)];
        } else {
            S_A[ty][tx] = 0.0f;
        }

        // 2. S_B
        if (col < N && (t * TILE_SIZE + ty) < K) {
            S_B[ty][tx] = B[N * (t * TILE_SIZE + ty) + col];
        } else {
            S_B[ty][tx] = 0.0f;
        }

        __syncthreads();

        // 3. 求内积
        for (int i = 0; i < TILE_SIZE; ++i) {
            sum += S_A[ty][i] * S_B[i][tx];
        }

        __syncthreads();
    }

    if (row < M && col < N) {
        C[row * N + col] = sum;
    }
}