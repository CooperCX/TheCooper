#include <cstdint>
#include <cuda_runtime.h>

#define QK4_0 32  // 每一个量化块包含 32 个元素

// Q4_0 量化块的物理内存结构
struct block_q4_0 {
    float d;             // 缩放因子 (Scale)
    uint8_t qs[16];      // 16 个字节，每个字节装 2 个 4-bit 权重，共包揽 32 个元素
};

// ==============================================================================
// 极速量化点乘算子：边解压，边计算 (On-the-fly Dequantization GEMV)
// 战术：1 个 Thread 独自包揽并拆解 1 个 block_q4_0 块 (共 32 个计算单元)
// ==============================================================================
__global__ void q4_0_gemv_kernel(
    const block_q4_0* weight_matrix, // 已经完全挤干水分的量化权重矩阵
    const float* x,                  // 正常的 FP32 动态输入向量
    float* y,                        // 输出结果向量
    int blocks_per_row               // 每行的块数量 (例如 Hidden_size 4096 / 32 = 128 块)
) {
    // 拿到全局兵牌号
    int global_tid = blockIdx.x * blockDim.x + threadIdx.x; 
    
    // 定位当前的这批 32 个权重，到底是在为矩阵的哪一行服务？
    int row = global_tid / blocks_per_row;
    
    // 算出在输入向量 x 中，我要从哪个脚印开始对齐相乘？
    int x_offset = (global_tid % blocks_per_row) * QK4_0; 

    // 【极其致命的优化点】：将整个结构体读进当前线程的高速私有寄存器 (Registers)！绝不要在显存里慢慢抠！
    block_q4_0 my_block = weight_matrix[global_tid];
    float d = my_block.d;

    float local_sum = 0.0f;

    // 开始疯狂的微操作流水线：打爆这个压缩包裹
    for (int i = 0; i < 16; ++i) {
        uint8_t byte = my_block.qs[i];

        // 1. 揪出右半边的肉（低 4 位），使用掩码 0x0F (即二进制 00001111)
        float weight0 = ((byte & 0x0F) - 8.0f) * d;
        
        // 2. 揪出左半边的肉（高 4 位），向右横移 4 个身位顶掉右半部分
        float weight1 = ((byte >> 4) - 8.0f) * d;

        // 3. 原地和干净的输入浮点数进行乘加 (FMA) 计算
        local_sum += weight0 * x[x_offset + i * 2];
        local_sum += weight1 * x[x_offset + i * 2 + 1];
    }

    // 4. 将积攒的这 32 个单元的纯血浮点计算结果，作为一份微小贡献，利用不可被打断的物理锁扣入全行结果。
    atomicAdd(&y[row], local_sum);
}

int main() {
    // 编译测试入口
    return 0;
}
