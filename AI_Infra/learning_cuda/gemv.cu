#include <sys/cdefs.h>

#include "cuda_stub/cuda_runtime.h"

#define WARP_SIZE 32

__inline__ __device__ float warpSum(float val) {
    for (int offset = WARP_SIZE / 2; offset > 0; offset >>= 1) {
        val += __shfl_down_sync(0xffffffff, val, offset);
    }

    return val;
}

__global__ void gemv_warp_kernel(const float* A, const float* x, float* y, int M, int N) {
    int global_tid = blockIdx.x * blockDim.x + threadIdx.x;
    int warp_id = global_tid / WARP_SIZE;
    int lane_id = threadIdx.x % WARP_SIZE;

    int row = warp_id;

    if (row < M) {
        float sum = 0.0f;

        for (int i = lane_id; i < N; i += WARP_SIZE) {
            sum += A[row * N + i] * x[i];
        }

        sum = warpSum(sum);

        if (lane_id == 0) {
            y[row] = sum;
        }
    }
}