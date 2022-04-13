#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

void Err(char* errc)
{
	printf("1");
	perror(errc);
	return;
}

void CpFile(char* src, char* dest)
{
	char buf[128];
	int fileread, inft;
	int outft = open(dest, O_CREAT| O_APPEND| O_RDWR);
	if(outft == -1) Err("open");
	inft = open(src, O_RDONLY);
	if(inft >0)
	{
		while((fileread = read(inft, buf, sizeof(buf))) > 0)
		{
			if(fileread == -1) Err("read");
			if(write(outft, buf, fileread) == -1) Err("write");
		}
		if(close(inft) == -1) Err("close");
	}
	if(close(outft) == -1) Err("close");
	return;
}
