#include <stdio.h>

int Generate(int num);

int Fmutex(int debug)
{
	printf("Fmutex\n");
	int clients = Generate(1);
	int wmax = Generate(2);
	printf("Wygenerowana ilość klientow: %d\n",clients);
	printf("Wygenerowana ilość miejsc w poczekalni: %d\n",wmax);
}
