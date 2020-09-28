#include "kernel/types.h"
#include "user/user.h"

// communicate between two processes

int main() {
    int pid;
    int status;

    pid = fork();

    // printf("fork() return %d\n", pid);

    if (pid == 0) {
        printf("child\n");
        exit(0);
    } else {
        // printf("parent waiting...\n");
        wait(&status);
        printf("parent, the child exited with status %d\n", status);
    }
    exit(0);
}