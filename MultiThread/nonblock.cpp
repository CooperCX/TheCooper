#include "unistd.h"
#include "sys/types.h"
#include "stdio.h"
#include "stdlib.h"
#include <string>
#include "fcntl.h"

/*
    设置管道非阻塞：管道的读写端都是文件描述符，可以用fcntl函数设置文件描述符，flag为O_NONBLOCK非阻塞
    int flags = fcntl(fd[0], F_GETFL);  // 获取原来的flag
    flags |= O_NONBLOCK;            // 修改flag的值
    fcntl(fd[0], F_SETFL, flags);   // 设置新的flag
*/

int main() {
    int fd[2];
    int ret = pipe(fd);
    if (ret == -1) {
        perror("pipe");
        exit(0);
    }

    pid_t pid = fork();
    if (pid > 0) {
        printf("i am parent process, pid : %d\n", getpid());
        close(fd[1]);

        int flags = fcntl(fd[0], F_GETFL);
        flags |= O_NONBLOCK;
        fcntl(fd[0], F_SETFL, flags);

       char buf[1024];
        while (1) {
            int len = read(fd[0], buf, sizeof(buf));
            if (len == -1) {
                printf("child process sleep\n");
                sleep(1);
            } else {
                printf("parent pid %d recv: %s\n",  getpid(), buf);
                memset(buf, 0, 1024);
                sleep(1);
            }
        }
    } else if (pid == 0) {
        printf("i am child process, pid : %d\n", getpid());
        close(fd[0]);
        while (1) {
            std::string str = "child process " + std::to_string(getpid());
            write(fd[1], str.c_str(), str.length());
            sleep(5);
        }
    } else {
        perror("fork");
        exit(0);
    }
}