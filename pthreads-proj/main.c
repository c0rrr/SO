#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "fvaria.h"
#include "fmutex.h"
#include "utils.h"

#define clear() printf("\033[H\033[J")

void Fmutex(int debug);
void Fvaria(int debug);
int PrintStatus(int resigned, int wcurrent, int wmax, int current, int res[], int wcurr[], int debug);

int main()
{
	int choice;
	printf("Wybierz wersje programu do uruchomienia\n1.Wersja oparta na mutexach/semaforach\n2.Wersja oparta na zmiennych warunkowych\n");
	scanf("%d", &choice);
	clear();
	if(choice == 1) Fmutex(1);
	else if(choice == 2) Fvaria(1);
	else
	{
		fprintf(stderr, "Invalid option\n");
		exit(EXIT_FAILURE);
	}
}
