#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void PrintStatus(int resigned, int wcurrent, int wmax, int current, int res[], int wcurr[], int debug)
{
	printf("Res: ");
	printf("\033[0;35m");
	printf("%d ", resigned);
	printf("\033[0;37m");
	printf("Wroom: ");
	printf("\033[0;35m");
	printf("%d", wcurrent);
	printf("\033[0;37m");
	printf("/");
	printf("\033[0;35m");
	printf("%d ", wmax);
	printf("\033[0;37m");
	printf("[in: ");
	printf("\033[0;35m");
	printf("%d", current);
	printf("\033[0;37m");
	printf("]\n");

	printf("Resigned clients: ");
	if(debug)
	{
		for(int i = 0 ; i < resigned ; i++)
		{
			printf("\033[0;35m");
			printf("%d", res[i]);
			printf("\033[0;37m");
			printf(", ");
		}
		printf("\nWaiting clients: ");
		for(int i = 0 ; i < wcurrent ; i++)
		{
			printf("\033[0;35m");
			printf("%d", wcurr[i]);
			printf("\033[0;37m");
			printf(", ");
		}
		printf("\n");
	}
}

