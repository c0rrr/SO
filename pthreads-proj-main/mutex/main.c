#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <getopt.h>
#include "../functions.h"

sem_t clientsSem;
sem_t barberSem;
pthread_mutex_t barberSeat;
pthread_mutex_t waitingRoom;

int seatsAmount = 10;
int freeSeatsAmount = 10;
int rejectedClientsCounter = 0;
int maxShearTime = 2;
int maxClientArriveTime = 8;
int clientOnSeatId = -1;

int isDebug = 0;
int isEnd = 0;

struct Node *clients = NULL;
struct Node *rejectedClients = NULL;
struct Node *waitingClients = NULL;

void *BarberThred() {
    while (isEnd != 1) {
        sem_wait(&clientsSem);
        pthread_mutex_lock(&waitingRoom);
        freeSeatsAmount++;
        sem_post(&barberSem);
        pthread_mutex_unlock(&waitingRoom);


        doBarberWork();

        printf("Res:%d WRomm: %d/%d [in: %d] - Client has new haircut!\n", rejectedClientsCounter,
               seatsAmount - freeSeatsAmount, seatsAmount, clientOnSeatId);
        pthread_mutex_unlock(&barberSeat);
    }
    if (isDebug == 1) printf("Barber finished work!\n");
    return NULL;
}

void *ClientThread(void *client) {
    struct Node *actualClient = (struct Node *) client;
    int clientId = (*actualClient).id;
    int clientTime = (*actualClient).time;

    ClientDelay(clientTime);

    pthread_mutex_lock(&waitingRoom);
    if (freeSeatsAmount > 0) {
        freeSeatsAmount--;
        if (isDebug == 1)
            addToWaitingList(clientId, clientTime);

        printf("Res:%d WRomm: %d/%d [in: %d] - New client in waiting room!\n", rejectedClientsCounter,
               seatsAmount - freeSeatsAmount, seatsAmount, clientOnSeatId);

        sem_post(&clientsSem);
        pthread_mutex_unlock(&waitingRoom);
        sem_wait(&barberSem);
        pthread_mutex_lock(&barberSeat);
        clientOnSeatId = clientId;
        printf("Res:%d WRomm: %d/%d [in: %d] - The client's hair was cut!\n", rejectedClientsCounter, seatsAmount - freeSeatsAmount,
               seatsAmount, clientOnSeatId);
        if (isDebug == 1)
            deleteNode(&waitingClients, clientId);

    }
    else {
        pthread_mutex_unlock(&waitingRoom);
        rejectedClientsCounter++;
        printf("Res:%d WRomm: %d/%d [in: %d] - Client rejected!\n", rejectedClientsCounter, seatsAmount - freeSeatsAmount,
               seatsAmount, clientOnSeatId);
        if (isDebug == 1) addToRejectedList(clientId, clientTime);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    static char usage[] = "Usage: %s -k value -r value [-c value] [-f value] [-d]\n";
    if(argc<5){
        fprintf(stderr, "%s: too few command-line arguments\n",argv[0]);
        fprintf(stderr,usage, argv[0]);
        exit(1);
    }
    if(argc>10){
        fprintf(stderr, "%s: too many command-line arguments\n",argv[0]);
        fprintf(stderr,usage, argv[0]);
        exit(1);
    }

    srand(time(NULL));

    int clientCount = 5;
    int option;
    int kFlag=0;
    int rFlag=0;
    while ((option = getopt(argc, argv, "k:r:c:f:d")) != -1) {
        switch (option) {
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
                isDebug = 1;
                break;
        }
    }
    if(kFlag == 0){
        fprintf(stderr, "%s: missing -k option\n",argv[0]);
        fprintf(stderr, usage,argv[0]);
        exit(1);
    }
    if(rFlag == 0){
        fprintf(stderr, "%s: missing -r option\n",argv[0]);
        fprintf(stderr, usage,argv[0]);
        exit(1);
    }

    pthread_t *clientThreads = malloc(sizeof(pthread_t) * clientCount);
    pthread_t barberThread;

    if (isDebug == 1) printf("Number of Clients: %d\n", clientCount);

    for (int i = 0; i < clientCount; i++) {
        int randomTime = rand() % maxClientArriveTime + 1;
        push(&clients, i, randomTime);
        pthread_create(&clientThreads[i], NULL, ClientThread, (void *) clients);
    }

    sem_init(&clientsSem, 0, 0);
    sem_init(&barberSem, 0, 0);

    if (pthread_mutex_init(&barberSeat, NULL) != 0) {
        fprintf(stderr, "barebrSeat mutex init error");
        exit(1);
    }
    if (pthread_mutex_init(&waitingRoom, NULL) != 0) {
        fprintf(stderr, "barebrSeat mutex init error");
        exit(1);
    }
    pthread_create(&barberThread, NULL, BarberThred, NULL);

    for (int i = 0; i < clientCount; i++) {
        pthread_join(clientThreads[i], NULL);
    }

    isEnd = 1;
    pthread_join(barberThread, NULL);

    pthread_mutex_destroy(&barberSeat);
    pthread_mutex_destroy(&waitingRoom);
    sem_destroy(&clientsSem);
    sem_destroy(&barberSem);
    free(clients);
    free(waitingClients);
    free(rejectedClients);
    return 0;
}
