#include <stdio.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void readFile(char* fd)
{
	int fh;
	int rd,n;

	fh = open(fd,O_RDONLY);
	if(fh == -1){
		perror("oepn");
		return;
	}else{
		struct stat v;
		stat(fd,&v);
		int size = v.st_size;
		char *p = malloc(size * sizeof(char));

		int ret = read(fh,p,size);
		if(ret == -1){
			perror("read");
			return;
		}else{
			printf("%s\n",p);
		}
	}
}
