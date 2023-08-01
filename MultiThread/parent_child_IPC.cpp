#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include <string>
#include <fcntl.h>

int main() {
    int pipefd[2];
    int ret = pipe(pipefd);
    if (ret == -1) {
        perror("create pipe");
        exit(-1);
    }

    pid_t pid = fork();

    if (pid == 0) {
        close(pipefd[1]);
        char buf[1024];
        int len;
        while ((len = read(pipefd[0], buf, sizeof(buf) - 1)) > 0) {
            printf("%s", buf);
            memset(buf, 0, 1024);
        }
        wait(nullptr);
    } else if (pid > 0) {
        close(pipefd[0]);
        dup2(pipefd[0], STDOUT_FILENO);
        execlp("ps", "ps", "aux", nullptr);
        perror("execlp");
        exit(0);
    } else {
        perror("fork");
        exit(0);
    }
}