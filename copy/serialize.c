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

#define BUFFERSIZE 1024
#define COPYMORE 0644

int serialize(char *srcb, char *destb);
void oops(char *, char *);
int copyDir(char *src, char *dest);
int copyFiles(char *src, char *dest);
int isdirex(const char *path);
int isdir(char *filename);
int dostat(char *filename);
int mode_isReg(struct stat info);

int serialize(char *srcb, char *destb)
{

    char *src = srcb;
    char *dest = destb;

    if (src[0] == '/' && dest[0] == '/') // cp1 /dir1 /dir2
    {                                    //- copies all regular files from /dir1 to /dir2
        int i;
        for (i = 1; i <= strlen(dest); i++)
        {
            dest[(i - 1)] = dest[i];
        }
        for (i = 1; i <= strlen(src); i++)
        {
            src[(i - 1)] = src[i];
        }

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
    }
    else
    {
        fprintf(stderr, "usage: ./serialize /source /destination\n");
        exit(1);
    }
}

int copyDir(char *source, char *destination)
{
    DIR *dir_ptr = NULL;
    struct dirent *direntp;
    char tempDest[strlen(destination) + 1];
    char tempSrc[strlen(source) + 1];
    strcat(destination, "/");
    strcat(source, "/");
    strcpy(tempDest, destination);
    strcpy(tempSrc, source);

    struct stat fileinfo;

    if ((dir_ptr = opendir(source)) == NULL)
    {
        fprintf(stderr, "cp1: cannot open %s for copying\n", source);
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
            /*else if (isdir(direntp->d_name))
            {
                if (direntp->d_name != "." && direntp->d_name != "..")
                {
                    char directory[] = "/";
                    strcat(directory, tempDest);
                    strcat(directory, direntp->d_name);

                    if (mkdir(directory, S_IRWXU | S_IRWXG | S_IRWXO) == -1)
                    {
                        oops("Error creating directory", "");
                    }

                    strcat(tempDest, direntp->d_name);
                    strcat(tempSrc, direntp->d_name);
                    copyDir(tempSrc, tempDest);
                }
            }*/
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

    /* open files */
    if ((in_fd = open(source, O_RDONLY)) == -1)
    {
        oops("Cannot open ", source);
    }

    if ((out_fd = creat(destination, COPYMORE)) == -1)
    {
        oops("Cannot creat ", destination);
    }

    /* copy files */
    while ((n_chars = read(in_fd, buf, BUFFERSIZE)) > 0)
    {
        if (write(out_fd, buf, n_chars) != n_chars)
        {
            oops("Write error to ", destination);
        }

        if (n_chars == -1)
        {
            oops("Read error from ", source);
        }
    }

    /* close files */
    if (close(in_fd) == -1 || close(out_fd) == -1)
    {
        oops("Error closing files", "");
    }

    return 1;
}

void oops(char *s1, char *s2)
{
    fprintf(stderr, "Error: %s ", s1);
    perror(s2);
    exit(1);
}