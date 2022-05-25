#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "fvaria.h"
#include "fmutex.h"
#include "utils.h"

int main()
{
	int choice;

	printf("Wybierz wersje programu do uruchomienia\n1.Wersja oparta na mutexach/semaforach\n2.Wersja oparta na zmiennych warunkowych\n");
	scanf("%d", &choice);
	PrintStatus(1,1,1,1);
	if(choice == 1) Fmutex(1);
	else if(choice == 2) Fvaria(1);
	else
	{
		fprintf(stderr, "Invalid option\n");
		exit(EXIT_FAILURE);
	}
}
