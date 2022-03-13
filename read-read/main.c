#include <stdio.h>
#include "read.h"

int main(int argc, char* argv[])
{
	char **temp=argv;
	if(argc<2)
	{
		printf("Zla ilosc argumentow\n");
		return 1;
	}
	else
	{
		temp++;
		while(*temp != NULL)
		{
			readFile(*temp);
			temp++;
		}
	}
}