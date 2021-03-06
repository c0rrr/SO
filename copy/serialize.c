#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
#include "serialize.h"

#define BUFFERSIZE 1024
#define COPYMORE 0644

int serialize(char *srcb, char *destb);
int copyDir(char *src, char *dest);
int copyFiles(char *src, char *dest);
int isdirex(const char *path);
int isdir(char *filename);
int dostat(char *filename);
int mode_isReg(struct stat info);

int serialize(char *srcb, char *destb)
{
    openlog("Folder serialization deamon [serializer]:", LOG_PID, LOG_USER);

    char *src = srcb;
    char *dest = destb;

    DIR *theFolder = opendir(dest);
    struct dirent *next_file;
    char filepath[256];

    while ((next_file = readdir(theFolder)) != NULL)
    {
        sprintf(filepath, "%s/%s", dest, next_file->d_name);
        remove(filepath);
    }
    closedir(theFolder);
    copyDir(src, dest);
    closelog();
}

int copyDir(char *source, char *destination)
{
    DIR *dir_ptr = NULL;
    struct dirent *direntp;
    char tempDest[strlen(destination)];
    char tempSrc[strlen(source)];
    strcpy(tempDest, destination);
    strcpy(tempSrc, source);

    struct stat fileinfo;

    if ((dir_ptr = opendir(source)) == NULL)
    {
        syslog(LOG_ERR, "Cannot open source folder, exiting.");
        return 0;
    }
    else
    {
        char choice;
        while ((direntp = readdir(dir_ptr)))
        {
            if (dostat(direntp->d_name))
            {
                strcat(tempDest, direntp->d_name);

                strcat(tempSrc, direntp->d_name);
                copyFiles(tempSrc, tempDest);
                strcpy(tempDest, destination);
                strcpy(tempSrc, source);
            }
        }
        closedir(dir_ptr);
        return 1;
    }
}

int isdirex(const char *path)
{
    struct stat stats;

    stat(path, &stats);

    if (S_ISDIR(stats.st_mode))
        return 0;

    return 1;
}

int isdir(char *filename)
{
    struct stat fileInfo;

    if (stat(filename, &fileInfo) >= 0)
        if (S_ISDIR(fileInfo.st_mode))
            return 1;
        else
            return 0;

    return;
}

int dostat(char *filename)
{
    struct stat fileInfo;

    if (stat(filename, &fileInfo) >= 0)
        if (S_ISREG(fileInfo.st_mode))
            return 1;
        else
            return 0;

    return;
}

int copyFiles(char *source, char *destination)
{
    int in_fd, out_fd, n_chars;
    char buf[BUFFERSIZE];

    if ((in_fd = open(source, O_RDONLY)) == -1)
    {
        syslog(LOG_ERR, "Cannot open source folder, exiting.");
        return 0;
    }

    if ((out_fd = creat(destination, COPYMORE)) == -1)
    {
        syslog(LOG_ERR, "Cannot open destination folder, exiting.");
        return 0;
    }

    while ((n_chars = read(in_fd, buf, BUFFERSIZE)) > 0)
    {
        if (write(out_fd, buf, n_chars) != n_chars)
        {
            syslog(LOG_ERR, "Cannot cannot write to destination folder, exiting.");
            return 0;
        }

        if (n_chars == -1)
        {
            syslog(LOG_ERR, "Cannot cannot read from source folder, exiting.");
            return 0;
        }
    }

    if (close(in_fd) == -1 || close(out_fd) == -1)
    {
        syslog(LOG_ERR, "Error closing files, exiting.");
        return 0;
    }

    return 1;
}
