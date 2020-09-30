#include "kernel/types.h"
#include "user/user.h"

void main(int argc, char *agrv[]) {
    static char buf[100];
    char c;
    int i, cc;
    for(i = 0; i + 1 < sizeof(buf); ) {
        cc = read(0, &c, 1);
        if (cc < 1) {
            break;
        }
        buf[i++] = c;
    }
    buf[i] = '\0';
    printf("debug: %s\n", buf);
}