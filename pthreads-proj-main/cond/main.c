#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <getopt.h>
#include "../functions.h"

pthread_cond_t shearEndCond;
pthread_cond_t wakeupBarberCond;
pthread_cond_t isBarberAvailableCond;

pthread_mutex_t waitingRoom;
pthread_mutex_t barberSeatMutex;
pthread_mutex_t clientFinished;
pthread_mutex_t barberMutex;


int seatsAmount = 10;
int freeSeatsAmount = 10;
int rejectedClientsCounter = 0;
int maxShearTime = 2;
int maxClientArriveTime = 8;
int clientOnSeatId = -1;

int isDebug = 0;
int isEnd = 0;
int isSeatBusy = 0;

struct Node *clients = NULL;
struct Node *rejectedClients = NULL;
struct Node *waitingClients = NULL;

void *Client(void *client) {
    struct Node *actualClient = (struct Node *) client;
    int clientId = (*actualClient).id;
    int clientTime = (*actualClient).time;

    clientDelay(clientTime);
    pthread_mutex_lock(&waitingRoom);
    if (freeSeatsAmount > 0) {
        freeSeatsAmount--;
        if (isDebug == 1)
            addToWList(clientId, clientTime);
        printf("Res:%d WRomm: %d/%d [in: %d]  - Nowy klient w poczekalni\n", rejectedClientsCounter,
               seatsAmount - freeSeatsAmount, seatsAmount, clientOnSeatId);

        pthread_mutex_unlock(&waitingRoom);

        pthread_mutex_lock(&barberSeatMutex);

        if (isSeatBusy == 1)
            pthread_cond_wait(&isBarberAvailableCond, &barberSeatMutex);

        isSeatBusy = 1;
        pthread_mutex_unlock(&barberSeatMutex);

        pthread_mutex_lock(&waitingRoom);
        freeSeatsAmount++;
        clientOnSeatId = clientId;
        printf("Res:%d WRomm: %d/%d [in: %d] - Klient usiadl na krzesle fryzjerskim\n", rejectedClientsCounter,
               seatsAmount - freeSeatsAmount, seatsAmount, clientOnSeatId);
        if (isDebug == 1)
        {
            deleteNode(&waitingClients, clientId);
        }
        printf("Res:%d WRomm: %d/%d [in: %d] - Klient jest stzyzony\n", rejectedClientsCounter,
               seatsAmount - freeSeatsAmount, seatsAmount, clientOnSeatId);
        pthread_mutex_unlock(&waitingRoom);


        pthread_cond_signal(&wakeupBarberCond);

        pthread_mutex_lock(&clientFinished);
        pthread_cond_wait(&shearEndCond, &clientFinished);
        isEnd = 0;
        pthread_mutex_unlock(&clientFinished);

        pthread_mutex_lock(&barberSeatMutex);
        isSeatBusy = 0;
        pthread_mutex_unlock(&barberSeatMutex);
        pthread_cond_signal(&isBarberAvailableCond);

    }
    else {
        pthread_mutex_unlock(&waitingRoom);
        rejectedClientsCounter++;
        if (isDebug == 1)
            addToRList(clientId, clientTime);
        printf("Res:%d WRomm: %d/%d [in: %d] - Klient zrezygnowal\n", rejectedClientsCounter,
               seatsAmount - freeSeatsAmount, seatsAmount, clientOnSeatId);
    }
    return NULL;
}

void *Barber() {
    pthread_mutex_lock(&barberMutex);
    while (isEnd == 0)
    {
        pthread_cond_wait(&wakeupBarberCond, &barberMutex);
        pthread_mutex_unlock(&barberMutex);
        if (isEnd == 0)
        {
            cut();
            printf("Res:%d WRomm: %d/%d [in: %d] - Klient zostal ostzyzony\n", rejectedClientsCounter,
                   seatsAmount - freeSeatsAmount, seatsAmount, clientOnSeatId);
            pthread_cond_signal(&shearEndCond);
        }
        else {
            if (isDebug == 1) printf("Fryzjer zakonczyl prace\n");
        }
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    static char usage[] = "Uzycie: %s -k wartosc -r wartosc [-c wartosc] [-f wartosc] [-d]\n";
    if (argc < 5) {
        fprintf(stderr, "%s: zbyt malo argumentow\n", argv[0]);
        fprintf(stderr, usage, argv[0]);
        exit(1);
    }
    if (argc > 10) {
        fprintf(stderr, "%s: zbyt duzo argumentow\n", argv[0]);
        fprintf(stderr, usage, argv[0]);
        exit(1);
    }

    srand(time(NULL));
    int clientCount = 5;
    int choice;
    int kFlag = 0;
    int rFlag = 0;
    while ((choice = getopt(argc, argv, "k:r:c:f:d")) != -1) {
        switch (choice) {
            case 'k':
                clientCount = atoi(optarg);
                kFlag = 1;
                break;
            case 'r':
                freeSeatsAmount = atoi(optarg);
                seatsAmount = atoi(optarg);
                rFlag = 1;
                break;
            case 'c':
                maxClientArriveTime = atoi(optarg);
                break;
            case 'f':
                maxShearTime = atoi(optarg);
                break;
            case 'd':
                isDebug = true;
                break;
        }
    }
    if (kFlag == 0) {
        fprintf(stderr, "%s: brakuje opcji -k\n", argv[0]);
        fprintf(stderr, usage, argv[0]);
        exit(1);
    }
    if (rFlag == 0) {
        fprintf(stderr, "%s: brakuje opcji -r\n", argv[0]);
        fprintf(stderr, usage, argv[0]);
        exit(1);
    }

    pthread_t *clientThreads = malloc(sizeof(pthread_t) * clientCount);
    pthread_t barberThread;

    if (isDebug == 1) printf("Liczba klientow: %d\n", clientCount);

    for (int i = 0; i < clientCount; i++) {
        int randomTime = rand() % maxClientArriveTime + 1;
        push(&clients, i, randomTime);
        pthread_create(&clientThreads[i], NULL, Client, (void *) clients);
    }

    pthread_cond_init(&isBarberAvailableCond, NULL);
    pthread_cond_init(&wakeupBarberCond, NULL);
    pthread_cond_init(&shearEndCond, NULL);

    pthread_mutex_init(&barberSeatMutex, NULL);
    pthread_mutex_init(&waitingRoom, NULL);
    pthread_mutex_init(&clientFinished, NULL);
    pthread_mutex_init(&barberMutex, NULL);

    pthread_create(&barberThread, 0, Barber, 0);

    for (int i = 0; i < clientCount; i++) {
        pthread_join(clientThreads[i], 0);
    }
    isEnd = 1;
    pthread_cond_signal(&wakeupBarberCond);
    pthread_join(barberThread, NULL);

    free(clients);
    free(waitingClients);
    free(rejectedClients);

    pthread_mutex_destroy(&barberMutex);
    pthread_mutex_destroy(&barberSeatMutex);
    pthread_mutex_destroy(&clientFinished);
    pthread_mutex_destroy(&waitingRoom);

    pthread_cond_destroy(&isBarberAvailableCond);
    pthread_cond_destroy(&wakeupBarberCond);
    pthread_cond_destroy(&shearEndCond);
    return 0;
}
