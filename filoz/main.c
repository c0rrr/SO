#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

pthread_mutex_t chop[4] = PTHREAD_MUTEX_INITIALIZER;

void eat(int peat)
{
	printf("Filozof %d je\n", peat+1);
	sleep(1);
}

void philo(int pnum)
{
	printf("Filozof %d chce jesc\n", pnum+1);
	pthread_mutex_lock(&chop[pnum]);
	pthread_mutex_lock(&chop[(pnum+1)%5]);
	eat(pnum);
	printf("Filozof %d zakonczyl jedzenie\n", pnum+1);
	pthread_mutex_unlock(&chop[pnum]);
	pthread_mutex_unlock(&chop[(pnum+1)%5]);
}

int main()
{
	pthread_t filoz[4];
	int index;

	for(int i=0; i<5; i++)
	{
		index = i;
		pthread_create(&filoz[1], NULL, philo, (void *) index);
	}
	sleep(5);
	for(int i=0; i<5; i++)
		pthread_join(filoz[1], NULL);

	return 0;
}
