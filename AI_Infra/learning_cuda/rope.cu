#include <cmath>

#include <cuda_runtime.h>

__global__ void rope_kernel(float2* q, float2* k, int seq_len, int head_dim, float base = 10000.0f) {
    int global_tid = blockIdx.x * blockDim.x + threadIdx.x;
    int half_head_dim = head_dim / 2;
    int token_pos = global_tid / half_head_dim;
    int pair_pos = global_tid % half_head_dim;

    if (token_pos < seq_len) {
        // 1. 根据 LLaMA 论文公式，计算旋转频率: theta = base ^ (-2j / head_dim)
        float theta = exp2f((-2.0f * (float)pair_pos) / (float)head_dim * log2f(base));
        // 2. 算出当前位置要旋转的绝对弧度角: token_pos * theta
        float angle = (float)token_pos * theta;

        float sin_val, cos_val;
        sincosf(angle, &sin_val, &cos_val);
        // 3. 开始秀操作！利用 float2 指针，一次性掏出一对相邻数字
        // 注意：因为我们传进来的是 float2*，所以 global_tid 每走 1，地址偏移其实是 2 个 float！
        float2 q_val, k_val;
        q_val = q[global_tid], k_val = k[global_tid];

        // 4. 原地进行复数旋转的数学公式替换
        float2 q_out, k_out;
        q_out.x = q_val.x * cos_val - q_val.y * sin_val;
        q_out.y = q_val.y * cos_val + q_val.x * sin_val;

        k_out.x = k_val.x * cos_val - k_val.y * sin_val;
        k_out.y = k_val.y * cos_val + k_val.x * sin_val;

        q[global_tid] = q_out;
        k[global_tid] = k_out;
    }
}