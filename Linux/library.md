# 库
* 库：库不能单独使用，是一种特殊的程序，提供给使用者可以直接使用的变量、函数、类。
* 静态库和动态库（共享库）
    * 静态库：在程序链接阶段被复制到程序中
    * 动态库：在程序运行阶段加载到内存中使用

## 静态库
* 命名规则
    * Linux： libxxx.a
    * windows：libxxx.lib
* 制作
    * gcc得到.o文件（将10个cpp文件编译为10个.o目标文件）
    ```
    gcc -c xxx.c xxx.c ...
    ```
    * 使用工具将.o文件打包（将10个.o文件打包成libxxx.a静态库）
    ```
    ar rcs libxxx.a xxx.o xxx.o ...
    ```
* 使用
    ```
    gcc main.c -o app -I xxx头文件目录 -L xxx库的目录 -l xxx库
    ```
* 工作原理：gcc进行链接时，将静态库中代码打包到可执行文件中

## 动态库
* 命名规则
    * Linux： libxxx.so，是一个可执行文件
    * windows：libxxx.dll
* 制作
    * gcc得到.o文件，得到和位置无关的代码（将10个cpp文件编译为10个.o目标文件）
    ```
    gcc -c -fpic xxx.c xxx.c ...
    ```
    * 使用gcc得到动态库
    ```
    gcc -shared xxx.o xxx.o ... -o libxxx.so
    ```
* 使用
    ```
    gcc main.c -o app -I xxx头文件目录 -L xxx库的目录 -l xxx库
    ```
* 工作原理：gcc进行链接时，不将动态库中代码打包到可执行文件中，而是在程序启动后被加载到内存中
    * 可通过ldd（list dynamic dependencies）命令检查动态库依赖关系
    ```
    ldd 可执行文件名
    ```
* 动态库加载
    * 系统需要知道库的名字，以及绝对路径
    * 系统的动态载入器ld-linux.so获取，依次搜索：
        * DT_RPATH段
        * LD_LIBRARY_PATH环境变量
        * /etc/ls.so.cache文件列表
        * /lib/, /usr/lib目录
    ```
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/lib/libxxx.so
    ```

## 静态库和动态库的对比
* 静态库和动态库的区别在于链接阶段如何链接成可执行程序：静态链接，动态链接
* 静态库
    优：加载速度快，移植方便
    缺：消耗内存，更新部署发布麻烦
* 动态库
    优：实现进程间资源共享（共享库），更新部署发布简单，使用时才加载
    缺：加载速度慢，发布程序时需要提供以来的动态库