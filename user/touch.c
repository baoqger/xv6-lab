#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    char *filename;
    if (argc < 2) {
        fprintf(2, "Usage: touch filename");
        exit(1);        
    }
    filename = argv[1];
    fprintf(1, "filename is: %s \n", filename);
    open(filename, O_CREATE);
    exit(0);
}