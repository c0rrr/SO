#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

#include "serialize.h"

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "usage: %s source destination\n", *argv);
        exit(1);
    }

    /*pid_t pid, sid;

    pid = fork();
    if (pid < 0)
    {
        exit(EXIT_FAILURE);
    }

    if (pid > 0)
    {
        exit(EXIT_SUCCESS);
    }
    umask(0);

    sid = setsid();
    if (sid < 0)
    {
        /* Log the failure 
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
<<<<<<< HEAD
    close(STDERR_FILENO);*/
    int i=0;
    while (1)
    {
        i++;
        printf("%s %s\n", argv[1], argv[2]);
        serialize(argv[1], argv[2]);
        printf("%d\n", i);
        sleep(5);
=======
    close(STDERR_FILENO);

    if (argv[1][0] == '/' && argv[2][0] == '/')
    {
        while (1)
        {
            serialize(argv[1], argv[2]);
            sleep(5);
        }
        exit(EXIT_SUCCESS);
    }
    else
    {
        fprintf(stderr, "usage: ./serialize /source /destination\n");
        exit(1);
>>>>>>> 86eee976e438789b4d68a20397774a44b5b35ae8
    }
}