#include "kernel/types.h"
#include "user/user.h"

int main() {
    int pid;
    int status;
    int fds[2];
    char buf[5];


    pipe(fds);

    pid = fork();

    if (pid == 0) {
        //child process 
        write(fds[1], "a", 1);
        fprintf(1, "%d: received ping\n", getpid());
        exit(0);   
    } else {
        // parent process
        wait(&status);
        read(fds[0], buf, 1);
        fprintf(1, "%d: received pong\n", getpid());
    }
    exit(0);  
}