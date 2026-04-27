#ifndef CUDA_RUNTIME_STUB_H
#define CUDA_RUNTIME_STUB_H

#include <stddef.h>

#include <cmath>

// =====================================
// 1. 修饰符宏定义 (消除未定义报错)
// =====================================
#define __global__
#define __device__
#define __host__
#define __shared__
#define __constant__
#define __forceinline__ inline

// =====================================
// 2. 内置同步与数学原语假定义
// =====================================
inline void __syncthreads() {}
inline unsigned int __activemask() {
    return 0xFFFFFFFF;
}
inline float __shfl_down_sync(unsigned int mask, float var, unsigned int delta, int width = 32) {
    return var;
}
inline float rsqrtf(float x) {
    return 1.0f / std::sqrt(x);
}

// 添加基于重载的原子操作存根，应对常见的 IDE 报错
inline float atomicAdd(float *address, float val) {
    return *address;
}
inline int atomicAdd(int *address, int val) {
    return *address;
}

// 模拟 CUDA 的双输出三角函数指令
inline void sincosf(float x, float *sptr, float *cptr) {
    if (sptr) *sptr = std::sin(x);
    if (cptr) *cptr = std::cos(x);
}

// =====================================
// 3. 硬件拓扑内置变量类型定义 (触发代码补全)
// =====================================
struct uint3 {
    unsigned int x, y, z;
};

struct dim3 {
    unsigned int x, y, z;
    dim3(unsigned int _x = 1, unsigned int _y = 1, unsigned int _z = 1) : x(_x), y(_y), z(_z) {}
};

// 欺骗 IDE，让其知道有下面这些全局内置变量存在
extern const uint3 threadIdx;
extern const uint3 blockIdx;
extern const dim3 blockDim;
extern const dim3 gridDim;
extern const int warpSize;

// =====================================
// 4. CUDA Runtime API 定义
// =====================================
enum cudaMemcpyKind {
    cudaMemcpyHostToHost = 0,
    cudaMemcpyHostToDevice = 1,
    cudaMemcpyDeviceToHost = 2,
    cudaMemcpyDeviceToDevice = 3,
    cudaMemcpyDefault = 4
};

typedef int cudaError_t;
const int cudaSuccess = 0;

cudaError_t cudaMalloc(void **devPtr, size_t size);
cudaError_t cudaFree(void *devPtr);
cudaError_t cudaMemcpy(void *dst, const void *src, size_t count, cudaMemcpyKind kind);
cudaError_t cudaDeviceSynchronize();

#endif  // CUDA_RUNTIME_STUB_H

struct alignas(16) float4 {
    float x;
    float y;
    float z;
    float w;
};

struct alignas(8) float2 {
    float x;
    float y;
};