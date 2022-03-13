#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int readFile(char *fn) 
{
    int fd = open(fn, O_RDWR, 0777);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    char buf[BUFSIZ+1];
    ssize_t n = 0;
    while ((n = read(fd, buf, BUFSIZ)) > 0) {
        buf[n] = '\0';
        if ((write(STDOUT_FILENO, buf, n)) == -1) {
            perror("write");
            return 1;        
        }        
    }
    if (n == -1) {
        perror("read");
        return 1;
    }

    if (close(fd) == -1) {
        perror("close");
        return 1;    
    }
    return 0;
}