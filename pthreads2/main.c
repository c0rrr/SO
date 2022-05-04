#include <stdio.h>
#include <pthread.h>
#include <time.h>

typedef struct thread_data
{
	int n;
	int it;
} thread_data;

void *Iterator(void *arg)
{
	thread_data *tdata = (thread_data *)arg;

	srand(time(NULL));
	int num = rand() % 10000;

	for(int i=1; i <= num; i++)
	{
		if(i%100 == 0)printf("Watek %d, iteracja %d\n", tdata->n, i);
	}

	tdata->it = num;
	pthread_exit(NULL);
}

int main()
{
	int sum=0,temp;
	thread_data td1, td2, td3, td4, td5, td6, td7, td8, td9, td10;
	td1.n=1;
	td2.n=2;
	td3.n=3;
	td4.n=4;
	td5.n=5;
	td6.n=6;
	td7.n=7;
	td8.n=8;
	td9.n=9;
	td10.n=10;
	pthread_t w1, w2, w3, w4, w5, w6, w7, w8, w9, w10;
	pthread_create(&w1, NULL, Iterator, (void *)&td1);
	pthread_create(&w2, NULL, Iterator, (void *)&td2);
	pthread_create(&w3, NULL, Iterator, (void *)&td3);
	pthread_create(&w4, NULL, Iterator, (void *)&td4);
	pthread_create(&w5, NULL, Iterator, (void *)&td5);
	pthread_create(&w6, NULL, Iterator, (void *)&td6);
	pthread_create(&w7, NULL, Iterator, (void *)&td7);
	pthread_create(&w8, NULL, Iterator, (void *)&td8);
	pthread_create(&w9, NULL, Iterator, (void *)&td9);
	pthread_create(&w10, NULL, Iterator, (void *)&td10);

	pthread_join(w1, NULL);
	pthread_join(w2, NULL);
	pthread_join(w3, NULL);
	pthread_join(w4, NULL);
	pthread_join(w5, NULL);
	pthread_join(w6, NULL);
	pthread_join(w7, NULL);
	pthread_join(w8, NULL);
	pthread_join(w9, NULL);
	pthread_join(w10, NULL);

	sum += td1.it;
	sum += td2.it;
	sum += td3.it;
	sum += td4.it;
	sum += td5.it;
	sum += td6.it;
	sum += td7.it;
	sum += td8.it;
	sum += td9.it;
	sum += td10.it;

	printf("Suma iteracji %d\n", sum);
}
