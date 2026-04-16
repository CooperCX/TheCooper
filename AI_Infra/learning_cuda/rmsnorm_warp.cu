#include <cuda_runtime.h>

#include <cmath>
#include <iostream>
#include <vector>

/**
 * 终极武器：Warp Shuffle (束内洗牌)
 * 这是 llama.cpp 源码中真正使用的技术
 */
__device__ float warp_reduce_sum(float val) {
    // 32 个人的“内部快速传话”
    // __shfl_xor_sync 会根据 bitwise XOR 交换数据
    // 5 步之内 (log 32)，让小组里所有人手里都拿着总和
    for (int offset = 16; offset > 0; offset /= 2) {
        val += __shfl_xor_sync(0xFFFFFFFF, val, offset);
    }
    return val;
}

__global__ void rmsnorm_warp_kernel(float* data, float eps, int n) {
    // 虽然不用黑板求和了，但还是需要一块“迷你黑板”来让 8 个小组长汇报工作
    // 因为 256 / 32 = 8 个小组 (Warps)
    __shared__ float s_warp_sums[8];

    int tid = threadIdx.x;
    int warp_id = tid / 32;  // 我属于第几个小组
    int lane_id = tid % 32;  // 我在小组里是老几

    // 1. 各自算平方
    float x_sq = 0.0f;
    if (tid < n) {
        x_sq = data[tid] * data[tid];
    }

    // 2. 小组内部快速求和 (Warp-level Reduction)
    // 这一步不需要 __syncthreads()，硬件保证了同步！
    float sum_sq = warp_reduce_sum(x_sq);

    // 3. 小组长把结果写到“迷你黑板”上
    if (lane_id == 0) {
        s_warp_sums[warp_id] = sum_sq;
    }

    // 只要涉及到写黑板，就必须吹哨同步
    __syncthreads();

    // 4. 让第一个小组的 8 个人，把“迷你黑板”上的 8 个小组和再次汇总
    // 这里我们再次利用强大的 Warp Reduce
    float final_sum_sq = (tid < 8) ? s_warp_sums[lane_id] : 0.0f;
    if (warp_id == 0) {
        final_sum_sq = warp_reduce_sum(final_sum_sq);
    }

    // 5. 将最终结果分发给所有人
    __shared__ float scale;
    if (tid == 0) {
        float mean_sq = final_sum_sq / n;
        scale = 1.0f / sqrtf(mean_sq + eps);
    }

    __syncthreads();

    // 6. 最终缩放
    if (tid < n) {
        data[tid] *= scale;
    }
}

int main() {
    int n = 256;
    float eps = 1e-5f;
    size_t bytes = n * sizeof(float);

    std::vector<float> h_data(n);
    for (int i = 0; i < n; i++) h_data[i] = (float)i;

    float* d_data;
    cudaMalloc(&d_data, bytes);
    cudaMemcpy(d_data, h_data.data(), bytes, cudaMemcpyHostToDevice);

    // 启动 256 个线程 (即 8 个 Warp)
    rmsnorm_warp_kernel<<<1, 256>>>(d_data, eps, n);

    std::vector<float> h_result(n);
    cudaMemcpy(h_result.data(), d_data, bytes, cudaMemcpyDeviceToHost);

    std::cout << "Warp Shuffle 版 RMSNorm 结果预览:" << std::endl;
    for (int i = 0; i < 5; i++) {
        std::cout << "Original[" << i << "]: " << h_data[i] << " -> Normed: " << h_result[i] << std::endl;
    }

    cudaFree(d_data);
    return 0;
}
