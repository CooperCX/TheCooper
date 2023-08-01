#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("%s filename\n", argv[0]);
        return -1;
    }
    struct stat st;
    int ret = stat(argv[1], &st);
    if (ret == -1) {
        perror("stat");
        return -1;
    }
    char perms[11] = {};
    switch(st.st_mode & S_IFMT) {
        case S_IFLNK:
            perms[0] = 'l';
            break;
        case S_IFDIR:
            perms[0] = 'd';
            break;
        case S_IFREG:
            perms[0] = '-';
            break;
        case S_IFBLK:
            perms[0] = 'b';
            break;
        case S_IFCHR:
            perms[0] = 'c';
            break;
        case S_IFSOCK:
            perms[0] = 's';
            break;
        case S_IFIFO:
            perms[0] = 'p';
            break;
        default:
            perms[0] = '?';
            break;
    }

    perms[1] = (st.st_mode & S_IRUSR) ? 'r' : '-';
    perms[2] = (st.st_mode & S_IWUSR) ? 'w' : '-';
    perms[3] = (st.st_mode & S_IXUSR) ? 'x' : '-';
    perms[4] = (st.st_mode & S_IRGRP) ? 'r' : '-';
    perms[5] = (st.st_mode & S_IRGRP) ? 'w' : '-';
    perms[6] = (st.st_mode & S_IRGRP) ? 'x' : '-';
    perms[7] = (st.st_mode & S_IROTH) ? 'r' : '-';
    perms[8] = (st.st_mode & S_IROTH) ? 'w' : '-';
    perms[9] = (st.st_mode & S_IROTH) ? 'x' : '-';

    int linkNum = st.st_nlink;

    char* fileUser = getpwuid(st.st_uid)->pw_name;
    char* fileGrp = getgrgid(st.st_gid)->gr_name;

    long int fileSize = st.st_size;

    char* mtime = ctime(&st.st_mtime);
    char* time;
    strncpy(time, mtime, strlen(mtime) - 1);

    char buf[1024];
    sprintf(buf, "%s %d %s %s %ld %s %s", perms, linkNum, fileUser, fileGrp, fileSize, time, argv[1]);

    printf("%s\n", buf);
}