#include <algorithm>
#include <cmath>
#include <cstdint>

struct block_q4_0 {
    float d;
    uint8_t qs[16];
};

void quantize_q4_0(const float* src, block_q4_0* dst, int n) {
    const int block_size = 32;
    int n_block = n / block_size;

    for (int i = 0; i < n_block; ++i) {
        // 计算当前块最大的绝对值
        float amax = 0.0f;
        for (int j = 0; j < block_size; ++j) {
            amax = std::max(amax, std::abs(src[i * block_size + j]));
        }

        // 计算缩放因子
        float d = amax / 8.0f;
        dst[i].d = d;
        float id = d ? 1.0f / d : 0.0f;

        for (int j = 0; j < block_size / 2; ++j) {
            // 将原始权重 * 缩放因子
            float v0 = src[i * block_size + j] * id;
            float v1 = src[i * block_size + j + 16] * id;

            // 将 (-8, 7) 的范围 + 8 偏移到 (0, 15) 以便存储
            uint8_t q0 = (uint8_t)std::round(v0 + 8.0f);
            uint8_t q1 = (uint8_t)std::round(v1 + 8.0f);

            // 限制边界
            q0 = std::min(q0, (uint8_t)15);
            q1 = std::min(q1, (uint8_t)15);

            // 位操作：两个 4-bit 拼成一个 uint8
            dst[i].qs[j] = q0 | (q1 << 4);
        }
    }
}

void dequantize_q4_0(const block_q4_0* src, float* dst, int n) {
    const int block_size = 32;
    int n_block = n / block_size;

    for (int i = 0; i < n_block; ++i) {
        float d = src[i].d;

        for (int j = 0; j < block_size / 2; ++j) {
            uint8_t q0 = src[i].qs[j] & 0x0F;
            uint8_t q1 = src[i].qs[j] >> 4;

            dst[i * block_size + j] = (q0 - 8.0f) * d;
            dst[i * block_size + j + 16] = (q1 - 8.0f) * d;
        }
    }
}