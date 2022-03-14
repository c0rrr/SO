#include <stdio.h>
#include "read.h"

int main(int argc, char* argv[])
{
	;
	if(argc<2)
	{
		printf("Zla ilosc argumentow\n");
		return 1;
	}
	else
	{
		while(temp != argc)
		{
			readFile(argv[temp]);
			temp++;
		}
	}
}
