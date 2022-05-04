#include <stdio.h>
#include <pthread.h>
#include <time.h>


int Iterator(int wnum)
{
	srand(time(NULL));
	int num = rand() % 10000;

	for(int i=1; i <= num; i++)
	{
		if(i%1000 == 0)printf("Watek %d, iteracja %d\n", wnum, i);
	}
	return num;
}

int main()
{
	int sum=0;
	pthrad_t w1, w2, w3, w4, w5, w6, w7, w8, w9, w10;
	pthread_create(w1);
	pthread_create();
	pthread_create();
	pthread_create();
	pthread_create();
	pthread_create();
	pthread_create();
}
