# 算法框架

## TensorFlow

* TensorFlow是什么？
    - 是一个基于Python的深度学习框架，用于创建机器/深度学习算法。
    - TensorFlow = Tensor(张量) + Flow(流)

* TensorFlow的特点是什么？
    - 丰富算法API：内置了能用到的大部分算法
    - 可移植性：支持Linux、Mac、window、移动端平台，CPU或GPU（配置环境变量参数CUDA_VISIABLE_DEVICES）
    - 编程扩展性：支持多语言，python、C++、Go等
    - 以及完善的技术文档

* Tensor张量是什么？
    - 表示n维数组的向量或矩阵的泛化。
    - 三种张量：常量张量、变量张量、占位符张量

* 变量张量与占位符张量的区别是什么？
    - variable需要初始化，placeholder不需要初始化
    - variable随时间变化，placeholder不随时间变化的特定输入数据

* TensorBoard是什么？
    - 数据可视化工具，Dashboard跟踪模型指标（损失、精度）
    - 查看图像文本音频等非图表数据
    - 高维数据向低维投影

* TensorFlow 架构的三个工作组件是什么？
    - 数据预处理
    - 模型训练
    - 模型验证

* tensorflow如何加载数据？
    - 预加载数据：将数据加载到张量中
    - 填充数据：使用sess.run()中的feed_dict参数
    - 读取文件数据：先写入到TFRecords中，再解码使用

* TensorFlow和PyTorch有什么区别？
```
| TensorFlow | PyTorch |
| 基于Theano库 | 基于Torch库 |
```

* TensorFlow常用函数
    - 数学函数：Add, Sub, Mul, Exp, Log, Greater, Less, Equal
    - 数组操作：cast, Concat, Slice, Split, Shape, Shuffle
    - 矩阵操作：matmul, Matrix_inverse, Matrix_Determinant
    - 神经网络：激活函数relu, sigmoid、卷积操作conv2d\conv3d、池化操作avg/max_pool、归一化normalize

## TensorRT

* TensorRT是什么？
    - 是Nvidia提供的C++推理框架。将训练好的模型转为TensorRT格式，使用TensorRT推理引擎运行，提升模型在Nvidia GPU上的性能
    - 由C++、CUDA、python编写而成，核心代码为C++、CUDA

* TensorRT为什么能提升性能？
    - 算子融合：合并或去除一些计算操作，减少数据流通和显存频繁使用
    - 量化：不同于常规FP32精度，使用INT8、FP16、TF32等精度提升模型性能，保持模型精度
    - 内核调整：根据硬件选择不同的优化策略和计算方式
    - 动态张量显存：减少模型中现存的开辟和释放
    - 多流执行：stream技术最大化并行操作

* 模型怎么转为TensorRT格式？
    - TensorFlow集成的TF-TRT
    - ONNX2TensorRT
    - Pytorch -> ONNX -> TensorRT
    - torch2trt\torch2trt_dynamic\TRTorch

* 使用TensorRT的方式?
    - TensorFlow集成的TF-TRT，加速效果不是很好
    - 在TensorRT Runtime环境中运行模型
    - 搭配服务器triton-server使用

* TensorRT支持哪几种权重精度？
    - FP32：单精度浮点型，最常见
    - FP16：半精度浮点型，相比FP32内存占用减少一半，速度快很多
    - INT8：整型，相比FP16内存占用减少一半，模型量化后可以使用INT8加速
    - TF32：截短的FP32类型


## 跟踪算法 MOT
* Sort：卡尔曼滤波（预测、更新） + 匈牙利算法（匹配，代价矩阵）
    * 关键步骤：通过卡尔曼滤波预测track目标下一帧的位置，使用匈牙利算法和当前帧中的detection进行匹配（IOU），没有匹配的track将保留一段时间后删除，没有匹配的detection将成为新的track，匹配上的track将使用卡尔曼滤波更新
    * 卡尔曼滤波：每个track分配一个卡尔曼滤波器

    * 匈牙利算法：二分图匹配算法
        * 代价矩阵：IOU，Re-ID，马氏距离


## 深度学习基础

* 1x1卷积
    - 降维：减少参数量
    - 升维：调整通道数
    - 跨通道信息交互
    - 增加非线性特征：后接非线性激活函数
* 卷积操作
    - 局部连接：局部感受野内进行点积运算（全连接是全局感受野）
    - 权值共享：一个卷积核滑动遍历整个输入进行卷积，都是用来减少参数量的
* 池化
    - 特征不变形：使模型更加关注某些特征是否存在而不是其具体位置
    - 特征降维：减小了特征的分辨率，进而减小了参数量
    - 防止过拟合：去除掉一些特征细节，关注主要特征

* 卷积后和池化后的大小计算
    - input: N * N * C, kernel: C * k * k * n
    - 分辨率计算： (N + 2 * padding - k) / strid + 1
    - 参数量计算： (N * N) * (C * k * k * n)

* IOU | GIOU | DIOU | CIOU
    - IOU：最基本的IOU，没有相交都为0，不够精准反映重合度
    - GIOU：IOU - (Ac - U) / Ac，考虑重合度
    - DIOU：IOU - (中心欧式距离^2 / 最小闭包区域对角线距离^2)，考虑距离
    - CIOU：IOU - (中心欧式距离^2 / 最小闭包区域对角线距离^2) - alpha * (arctan(W / H) - arctan(w / h))^2，考虑长宽比

* 损失函数
    - 回归
        - 平方损失：(y - f(x)) ^ 2
        - 绝对损失：|y - f(x)|
        - Huber损失：|y - f(x)| > sigma, |y - f(x)| * sigma - sigma^2 / 2; |y - f(x)| < sigma, (y - f(x)) ^ 2 / 2
    - 分类
        - 0-1损失
        - CE 损失：正 -log(p), 负 -log(1 - p)
        - focal loss：平衡参数alpha，平衡正负样本；调制因子gamma，减少易分类样本的权重，从而使得模型在训练时更专注于难分类的样本
        - softmax损失：多分类

* 常用指标
    - accuracy = (TP + TN) / (TP + TN + FP + FN)
    - precision = TP / (TP + FP)
    - recall = TP / (TP + FN)
    - P-R曲线
    - AP = P-R曲线下的面积
    - mAP = 各类AP的平均

* BN层