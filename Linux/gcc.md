# gcc/g++
* gcc: 原来是专门的C代码的编译器（GNU C Compiler），现在指的是GNU编译器套件（GNU Compiler Collection），包含C\C++（不同版本）, Objective-C, Java等
* gcc流程：
    * 源代码（.c/.cpp）-预编译器-> 预编译后的源代码(.i)
    ```
    gcc test.c -E -o test.i
    ```
    * 预编译后的源代码(.i) -编译器-> 汇编代码(.s)
    ```
    gcc test.c -S -o test.s
    ```
    * 汇编代码(.s) -汇编器-> 目标代码(.o)
    ```
    gcc test.c -c -o test.o
    ```
    * 目标代码(.o) -链接器-> 可执行文件(.out/.exe)
    ```
    gcc test.c -o test.out
    ```
* gcc常用参数选项
```
[file2] -o [file1]：将file1编译为file2
-I directory: 指定include包含文件的搜索目录
-D macro: 指定一个宏，相当于在程序中添加：#define macro
-g: 生成调试信息
-w: 不生成警告信息
-Wall: 生成所有警告信息
-On: 指定编译器的优化选项，默认为-O1，-O0 ~ -O3
-l: 指定使用的库
-L: 指定搜索的库的路径
-shared: 生成共享目标文件，简历共享库
-std: 指定C语言标准
```
* gcc和g++的区别
    * 都是GNU的编译器，都可以编译C/C++的源代码
    * g++编译阶段调用gcc，但是gcc不能自动链接，通常使用g++链接
    ```
    编译: gcc/g++
    链接: g++/gcc -lstdc++
    ```
    * __cplusplus宏：表示编译器将代码视为C还是C++