#include <stdio.h>
#include <pthread.h>

int counter=0;

void *Count()
{
	while(1) printf("%d\n", counter);
}

void *Increment()
{
	while(1) counter++;
}

int main()
{
	pthread_t t1, t2;
	if(pthread_create(&t1, NULL, Count, NULL)) return 1;
	if(pthread_create(&t1, NULL, Increment, NULL)) return 1;
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	return 0;
}
