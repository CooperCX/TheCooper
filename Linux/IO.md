## 文件IO
* 标准C库IO函数，调用Linux系统IO函数
    * FILE结构体：文件描述符（int）, 文件读写指针位置, I/O缓冲区（内存地址）
        * 文件描述符：用于找到磁盘中对应的文件
        * 文件读写指针：读写过程中指针的实际位置
        * 缓冲区：数据先写入缓冲区，再进入磁盘
* 虚拟地址空间（虚拟内存）：每个进程使用一个虚拟内存运行程序
    * 内存管理单元MMU: 映射到真实物理内存
    * 内核区：受到系统保护，用户无法读写，操作需要调用系统API
        * 内存管理
        * 进程管理
        * 设备驱动管理
        * VFS虚拟文件系统
    * 用户区
        * 环境变量
        * 命令行参数
        * 共享库（动态库）
        * 栈：高地址 -> 低地址
        * 堆：低地址 -> 高地址
        * 全局变量：未初始化的全局变量(.bss)，初始化的全局变量(.data)
        * 代码区：二进制代码
        * 受保护的地址：NULL nullptr
* 文件描述符：在进程的内核区，PCB进程控制块来管理文件描述符表
    * 文件描述符表: 默认最大为1024个，即一个进程最多可以打开1024个文件，前三个默认被占用
        * 0-STDIN_FILENO：标准输入
        * 1-STDOUT_FILENO：标准输出
        * 2-STDERR_FILENO：标准错误
        * 后面每打开一个新文件，则占用一个空闲的文件描述符，同一个文件被多次打开占用不同的文件描述符
* Linux系统IO函数
    * open函数
    ```
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>

    // 打开一个已经存在的文件
    int open(const char *pathname, int flags);
        参数：
            - pathname：要打开的文件路径
            - flags：对文件的操作权限设置还有其他的设置
              O_RDONLY,  O_WRONLY,  O_RDWR  这三个设置是互斥的
        返回值：返回一个新的文件描述符，如果调用失败，返回-1

    errno：属于Linux系统函数库，库里面的一个全局变量，记录的是最近的错误号。

    #include <stdio.h>
    void perror(const char *s);作用：打印errno对应的错误描述
        s参数：用户描述，比如hello,最终输出的内容是  hello:xxx(实际的错误描述)


    // 创建一个新的文件
    int open(const char *pathname, int flags, mode_t mode);
        参数：
            - pathname：要创建的文件的路径
            - flags：对文件的操作权限和其他的设置
                - 必选项：O_RDONLY,  O_WRONLY, O_RDWR  这三个之间是互斥的
                - 可选项：O_CREAT 文件不存在，创建新文件
            - mode：八进制的数，表示创建出的新的文件的操作权限，比如：0775
            最终的权限是：mode & ~umask
            0777   ->   111111111
        &   0775   ->   111111101
        ----------------------------
                        111111101
        按位与：0和任何数都为0
        umask的作用就是抹去某些权限。

        flags参数是一个int类型的数据，占4个字节，32位。
        flags 32个位，每一位就是一个标志位。
    ```
    * 缓冲区 <--> 磁盘
        * write
    ```
    ssize_t write(int fd, const void *buf, size_t count);
    参数：
        - fd：文件描述符，open得到的，通过这个文件描述符操作某个文件
        - buf：要往磁盘写入的数据，数据
        - count：要写的数据的实际的大小
    返回值：
        成功：实际写入的字节数
        失败：返回-1，并设置errno
    ```
    * read
    ```
    ssize_t read(int fd, void *buf, size_t count);
    参数：
        - fd：文件描述符，open得到的，通过这个文件描述符操作某个文件
        - buf：需要读取数据存放的地方，数组的地址（传出参数）
        - count：指定的数组的大小
    返回值：
        - 成功：
            >0: 返回实际的读取到的字节数
            =0：文件已经读取完了
        - 失败：-1 ，并且设置errno
    ```
    * lseek(int fd, off_t offset, int whence);
    ```
    #include <sys/types.h>
    #include <unistd.h>
    off_t lseek(int fd, off_t offset, int whence);
        参数：
            - fd：文件描述符，通过open得到的，通过这个fd操作某个文件
            - offset：偏移量
            - whence:
                SEEK_SET
                    设置文件指针的偏移量
                SEEK_CUR
                    从当前位置偏移第二个参数offset的值
                SEEK_END
                    从文件末尾偏移第二个参数offset的值
        返回值：返回文件指针的位置


    作用：
        1.移动文件指针到文件头：lseek(fd, 0, SEEK_SET);
        2.获取当前文件指针的位置：lseek(fd, 0, SEEK_CUR);
        3.获取文件长度：lseek(fd, 0, SEEK_END);
        4.拓展文件的长度：lseek(fd, 100, SEEK_END)，注意：需要写一次数据
    ```
    * stat()/lstat()
    ```
    int stat(const char *pathname, struct stat *statbuf)，获取具体文件信息
    int lstat(const char *pathname, struct stat *statbuf)，获取软链接文件信息
        参数:
            - pathname：操作的文件的路径
            - statbuf：结构体变量，传出参数，用于保存获取到的文件的信息
        返回值：
            成功：返回0
            失败：返回-1 设置errno
    ```
    * mode_t变量: 16位整数，记录文件类型和权限
    * 文件属性函数
    ```
    int access(const char *pathname, int mode);
    作用：判断某个文件是否有某个权限，或者判断文件是否存在
    参数：
        - pathname: 判断的文件路径
        - mode:
            R_OK: 判断是否有读权限
            W_OK: 判断是否有写权限
            X_OK: 判断是否有执行权限
            F_OK: 判断文件是否存在
    返回值：成功返回0， 失败返回-1
    int chmod(const char *pathname, mode_t mode);
        修改文件的权限
        参数：
            - pathname: 需要修改的文件的路径
            - mode:需要修改的权限值，八进制的数
        返回值：成功返回0，失败返回-1
    int truncate(const char *path, off_t length);
        作用：缩减或者扩展文件的尺寸至指定的大小
        参数：
            - path: 需要修改的文件的路径
            - length: 需要最终文件变成的大小
        返回值：
            成功返回0， 失败返回-1
    ```
    * 目录操作函数
    ```
        int mkdir(const char *pathname, mode_t mode);
        作用：创建一个目录
        参数：
            pathname: 创建的目录的路径
            mode: 权限，八进制的数
        返回值：
            成功返回0， 失败返回-1

        int rename(const char *oldpath, const char *newpath);

        int chdir(const char *path);
        作用：修改进程的工作目录
            比如在/home/nowcoder 启动了一个可执行程序a.out, 进程的工作目录 /home/nowcoder
        参数：
            path : 需要修改的工作目录

        char *getcwd(char *buf, size_t size);
        作用：获取当前工作目录
        参数：
            - buf : 存储的路径，指向的是一个数组（传出参数）
            - size: 数组的大小
        返回值：
            返回的指向的一块内存，这个数据就是第一个参数
    ```
    * 目录遍历函数
    ```
        DIR *opendir(const char *name);
        参数：
            - name: 需要打开的目录的名称
        返回值：
            DIR * 类型，理解为目录流
            错误返回NULL

        struct dirent *readdir(DIR *dirp);
        - 参数：dirp是opendir返回的结果
        - 返回值：
            struct dirent，代表读取到的文件的信息
            读取到了末尾或者失败了，返回NULL

        int closedir(DIR *dirp);
    ```

    ```
        int dup(int oldfd);
        作用：复制一个新的文件描述符
        fd=3, int fd1 = dup(fd),
        fd指向的是a.txt, fd1也是指向a.txt
        从空闲的文件描述符表中找一个最小的，作为新的拷贝的文件描述符

        int dup2(int oldfd, int newfd);
        作用：重定向文件描述符
        oldfd 指向 a.txt, newfd 指向 b.txt
        调用函数成功后：newfd 和 b.txt 做close, newfd 指向了 a.txt
        oldfd 必须是一个有效的文件描述符
        oldfd和newfd值相同，相当于什么都没有做
    ```
    ```
        int fcntl(int fd, int cmd, ...);
        参数：
        fd : 表示需要操作的文件描述符
        cmd: 表示对文件描述符进行如何操作
            - F_DUPFD : 复制文件描述符,复制的是第一个参数fd，得到一个新的文件描述符（返回值）
                int ret = fcntl(fd, F_DUPFD);

            - F_GETFL : 获取指定的文件描述符文件状态flag
              获取的flag和我们通过open函数传递的flag是一个东西。

            - F_SETFL : 设置文件描述符文件状态flag
              必选项：O_RDONLY, O_WRONLY, O_RDWR 不可以被修改
              可选性：O_APPEND, O_NONBLOCK
                O_APPEND 表示追加数据
                O_NONBLOCK 设置成非阻塞

        阻塞和非阻塞：描述的是函数调用的行为。
    ```