#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int 
main(int argc, char *argv[]) {
    int timeSlice;
    if (argc < 2) {
        fprintf(2, "Usage: sleep t...");
        exit(1);
    }
    timeSlice = atoi(argv[1]);
    sleep(timeSlice);
    exit(0);
}
