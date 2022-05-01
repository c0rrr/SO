#ifndef FUNCTION_H
#define FUNCTION_H

int serialize(char *srcb, char *destb);
int copyDir(char *src, char *dest);
int copyFiles(char *src, char *dest);
int isdirex(const char *path); 
int isdir(char *filename);
int dostat(char *filename);
int mode_isReg(struct stat info);

#endif
