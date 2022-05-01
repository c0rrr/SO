#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <signal.h>
#include <ctype.h>

#include "serialize.h"

char *src;
char *dest;

void handler(int signum)
{
    syslog(LOG_NOTICE, "Forced serialization occured (SIGUSR1)");
    serialize(src, dest);
}

int main(int argc, char *argv[])
{
    signal(SIGUSR1, handler);

    int slp = 300;

    if (argc < 3 || argv[3][0] == '/' && argv[4][0] == '/')
    {
        fprintf(stderr, "usage: %s source destination\n", *argv);
        exit(1);
    }

    int svalue = 300;
    int sw;

    while ((sw = getopt(argc, argv, "s:")) != -1)
        switch (sw)
        {
        case 's':
            svalue = atoi(optarg);
            break;
        case '?':
            if (optopt == 's')
                fprintf(stderr, "Option -%c requires an argument.\n", optopt);
            else if (isprint(optopt))
                fprintf(stderr, "Unknown option `-%c'.\n", optopt);
            else
                fprintf(stderr,"Unknown option character `\\x%x'.\n",optopt);
            return 1;
        default:
            abort();
        }

    slp = svalue;

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
    close(STDERR_FILENO);*/

        openlog("Folder serialization deamon:", LOG_PID, LOG_USER);


        src = argv[3];
        dest = argv[4];
        int i;
        for (i = 1; i <= strlen(dest); i++)
        {
            dest[(i - 1)] = dest[i];
        }
        for (i = 1; i <= strlen(src); i++)
        {
            src[(i - 1)] = src[i];
        }
        strcat(dest, "/");
        strcat(src, "/");

        while (1)
        {
            syslog(LOG_NOTICE, "Normal serialization occured");
            //printf("%s %s\n", src, dest);
            serialize(src, dest);
            sleep(slp);
        }
        closelog();
        exit(EXIT_SUCCESS);
}