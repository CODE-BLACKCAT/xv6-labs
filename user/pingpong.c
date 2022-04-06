#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) 
{
    int ptoc_fd[2], ctop_fd[2];
    pipe(ptoc_fd);
    pipe(ctop_fd);
    char buf[6];
    if (fork() == 0) {
        read(ptoc_fd[0], buf, 4);
        printf("%d received %s\n", getpid(), buf);
        write(ctop_fd[1], "pong", strlen("pong"));
    } 
    else {
        write(ptoc_fd[1], "ping", strlen("ping"));
        wait(0);
        read(ctop_fd[0], buf, 4);
        printf("%d received %s\n", getpid(), buf);
    }
    exit(0);
}