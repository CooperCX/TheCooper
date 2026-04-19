在 CUDA 编程中：
Host (主机) 指的是 CPU 和主板上的内存（RAM）。
Device (设备) 指的是 GPU 和显卡上的显存（VRAM）。

[重要] 核心工作流
CPU 在内存里准备好数据
CPU 把数据从内存运到显存（拷贝数据）
CPU 给工人们发统一的操作手册（这个手册叫 Kernel，核函数）
多个 GPU 线程同时开工，瞬间完成计算
CPU 把结果从显存运回内存

CUDA 的线程层次结构
一次内核函数 (Kernel) 的启动 (Launch) 对应一个完整的执行实例，其包含三个主要层级结构：
**1. Grid（网格）**
定义：一个 Kernel 启动时产生的所有线程的集合称为一个 Grid。
组织方式：Grid 由多个 Block 组成，可以通过 dim3 结构体配置为一维、二维或三维的拓扑结构。
硬件映射：当 Grid 被加载到 GPU 时，其内部的 Block 会被分发 (Dispatch) 到各个 Streaming Multiprocessor (SM) 上执行。
并发与同步：CUDA 编程模型不保证同一 Grid 内不同 Block 的执行顺序，因此原生的 CUDA 并没有提供跨整个 Grid 的直接同步机制（尽管在较新的架构中引入了 Cooperative Groups，但在经典理解中，**同一 Grid 内Block 是相互独立的**）。

**2. Block（线程块）**
定义：位于 Grid 内部，由若干个 Thread 组成的执行批次集合。
组织方式：同样支持 1D/2D/3D 拓扑。现代 GPU 限制单个 Block 的最大线程数量通常为 1024。
硬件映射与生命周期：一个 Block 一旦被调度到某个特定的 SM 上，就会在该 SM 上驻留直到执行完毕，不会发生迁移。
核心特性 (重点面试考点)：
快速通信：Block 内的线程可以通过低延迟的片上存储器——**共享内存 (Shared Memory)**交换数据。
块内同步：Block 内的线程可以通过 **__syncthreads()** 指令实现硬件级别的屏障同步 (Barrier Synchronization)。

**3. Thread（线程 / 硬件级上下文）**
定义：CUDA 编程模型中最小的执行单元。
硬件映射 (SIMT 执行模型)：虽然程序员以单个 Thread 为视角编写代码，但在硬件底层，NVIDIA GPU 是以 **Warp** (线程束/线程簇，通常包含 32 个线程) 为基本调度和执行单位的。SM 的指令调度单元广播同一条指令给 Warp 内的 32 个线程同时执行，这就是 **SIMT (Single Instruction, Multiple Threads)** 架构的核心。


在一段 .cu 代码里，既有 CPU 的代码，也有 GPU 的代码。编译器 (NVCC) 是通过以下三个修饰符（Qualifiers）来区分它们的：
__global__ : 核函数 (Kernel)。跑在 GPU 上，由 CPU 调用。必须返回 void。这是连接 Host 和 Device 的入口。
__device__ : 设备函数。跑在 GPU 上，只能由 GPU 上的其他函数（如 Kernel 或其他 device 函数）调用。
__host__ : 主机函数（默认）。跑在 CPU 上，只能由 CPU 调用。一般可省略。

核心内存管理 API
在 CPU 端（Host），我们需要**手动管理 GPU 端（Device）的显存分配**：
cudaMalloc(void **devPtr, size_t size): 在显存中分配内存 (Global Memory)。
cudaFree(void *devPtr): 释放显存。
cudaMemcpy(void *dst, const void *src, size_t count, cudaMemcpyKind kind): 控制数据在内存和显存之间搬运。
kind 是一个枚举：
    **cudaMemcpyHostToDevice**
    **cudaMemcpyDeviceToHost**