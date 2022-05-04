#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

void *incCounter();

int counter = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("usage: %s thread_count interation_count\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int NUMT = atoi(argv[1]);
    int ITER = atoi(argv[2]);
    pthread_t threads[NUMT];

    int iret1;

    int i = 0;
    for (i = 0; i < NUMT; i++)
    {
        iret1 = pthread_create(&threads[i], NULL, incCounter, (void *)(intptr_t)ITER);
        if (iret1)
        {
            fprintf(stderr, "Error - pthread_create() return code: %d\n", iret1);
            exit(EXIT_FAILURE);
        }
    }

    for (i = 0; i < NUMT; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("Counter final value: %d\n", counter);
    exit(0);
}

void *incCounter(void *count)
{
    pthread_mutex_lock(&mutex);
    int i = 0;
    int iter = (int)(intptr_t)count;
    for (i = 0; i < iter; i++)
    {
        counter++;
    }
    pthread_mutex_unlock(&mutex);
}