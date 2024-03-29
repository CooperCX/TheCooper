# 算法复杂度

## 时间复杂度:用于评估执行程序所消耗的时间，可以估算出程序对处理器的使用程度
* 渐进时间复杂度：用大写O表示，成为大O表示法
    * Ο(1) ＜ Ο(log n) ＜ Ο(n)＜ Ο(nlog n) ＜ Ο(n2) ＜ Ο(n3) ＜…＜ Ο(2^n) ＜ Ο(n!)
    * 推导：找出算法中最内层的循环体，计算其执行次数的数量级，只需保证函数中的最高次幂正确。
        * 规则：用常数1取代运行时间中的所有加法常数；只保留时间函数中的最高阶项；如果最高阶项存在，则省去最高阶项前面的系数；

    * 常数阶O(1): 没有循环的结构
    ```
        int a = 1, b = 2;
        int c = a + b;
    ```
    * 对数阶Ο(log n): 循环体的条件以2的指数增长接近n
    ```
        int i = 1;
        while (i <= n) {
            i *= 2;
        }
    ```
    * 线性阶O(n): 循环体的条件以线性递增的方式接近n
    ```
        int num = 0;
        for (int i = 0; i < n; i++) {
            num += i;
        }
    ```
    * 线性对数阶Ο(nlog n): 在对数阶的循环体外面套上线性阶的循环
    ```
        for (int i = 0; i < n; i++) {
            int k = 1;
            while (k <= n) {
                k *= 2;
            }
        }
    ```
    * 平方阶Ο(n2): 在线性阶的循环体外面套上线性阶的循环
    ```
        int num = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                num++;
            }
        }
    ```
    * O(m * n):
    ```
        int num = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                num++;
            }
        }
    ```

## 空间复杂度:用于评估执行程序所占用的内存空间，可以估算出程序对计算机内存的使用程度
* 空间复杂度O(1): 算法执行所需要的临时空间随着不会某个变量n的大小而变化，此算法空间复杂度为一个常量，可表示为 O(1)
* 空间复杂度O(n):算法执行所需要的临时空间随着某个变量n的大小而变化，可表示为 O(n)

## 排序算法的复杂度
| 排序算法 | 时间 | 空间 |
| :-----: | :-: | :-: |
| 冒泡 | Ο(n2) | O(1) |
| 插入 | Ο(n2) | O(1) |
| 归并 | Ο(nlogn) | O(n) |
| 基数 | Ο(n * m) | O(m) |
| 选择 | Ο(n2) | O(1) |
| 希尔 | Ο(nlogn) | O(1) |
| 快速 | Ο(nlogn) | O(nlogn) |
| 堆 | Ο(nlogn) | O(1) |
| 计数 | Ο(n + k) | O(n + k) |
| 桶 | Ο(n + k) | O(n * k) |