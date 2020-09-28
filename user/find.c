#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fs.h"
#include "user/user.h"


char*
fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;
  strcpy(buf, p);
  return buf;
}

void find(char *path, char *filename) {
    int fd;
    char buf[512], *p;
    struct dirent de;
    struct stat st;
    char curDir[] = ".";
    char parDir[] = "..";


    if ((fd = open(path, 0)) < 0) {
        fprintf(2, "find: cannot open %s\n", path);
        return;
    }
    if ((fstat(fd, &st)) < 0) {
        fprintf(2, "find: cannot stat %s\n", path);
        close(fd);
        return;
    }

    switch(st.type) {
        case T_FILE:
            if (!strcmp(fmtname(path), filename))
                printf("%s\n", path);
            break;
        case T_DIR:
            if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
                printf("find: path too long\n");
                break;
            }
            strcpy(buf, path);
            p = buf + strlen(buf);
            *p++ = '/';

            while(read(fd, &de, sizeof(de)) == sizeof(de)) {
                if (de.inum == 0) // what's this?
                    continue;
                memmove(p, de.name, DIRSIZ);
                p[DIRSIZ] = 0;
                if (stat(buf, &st) < 0) {
                    printf("find: cannot stat %s\n", buf);
                    continue;
                }

                if (!strcmp(de.name, curDir) || !strcmp(de.name, parDir)) {
                    continue;
                }
                find(buf, filename);
            }            
            break;
    }
    close(fd);
}

int main(int argc, char *argv[]) {
    find(argv[1], argv[2]);
    exit(0);
}
