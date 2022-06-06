#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

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

int Generate(int num)
{
	srand(time(NULL));
<<<<<<< HEAD
	if(num == 1) printf("Generowanie ilosci klientow\n");
	else if(num == 2) printf("Generowanie ilosci krzesel w poczekalni\n");
	else if(num == 3) printf("Generowanie dlugosci strzyzenia\n");

	for(int i = 0 ; i > 2 ; i++)
	{
		usleep(1000 * 500);
		printf(".");
	}

	if(num == 1)
	{
		num = rand()%50;
		printf("Wygenerowana ilosc klientow to = %d\n", num);
	}
	else if(num == 2)
	{
                num = rand()%20;
                printf("Wygenerowana ilosc klientow to = %d\n", num);
        }
	else if(num == 3)
	{
		num = rand()%5;
		printf("Wygenerowana dlugosc strzyzenia to = %ds\n", num);
	}

=======
	if(num == 1) num = rand()%60;
	else if(num == 2) num = rand()%20;

>>>>>>> c2a998fcdfc7310b7b222029b7ad91825928f43c
	return num;
}
