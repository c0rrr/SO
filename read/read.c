#include <stdio.h>
#include <stdlib.h>

void read(char *fd)
{
	FILE *fptr;
	char c;
	fptr = fopen(fd,"r");
	if(fptr == NULL)
	{
		printf("Nie mozna otworzyc pliku\n");
		exit(0);
	}
	c = fgetc(fptr);
	while(c != EOF)
	{
		printf("%c", c);
		c = fgetc(fptr);
	}
	fclose(fptr);
}
