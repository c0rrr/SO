#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "functions.h"

struct Node *clients;
struct Node *rejectedClients;
struct Node *waitingClients;

void printWList() {
    printf("Czeka: ");
    printList(waitingClients);
    printf("\n");
}

void doBarberWork() {
    int randomShearTime = rand() % maxShearTime + 1;
    sleep(randomShearTime);
}

void clientDelay(int clientTime) {
    sleep(clientTime);
}

void push(struct Node **head_ref, int clientId, int clientTime) {
    struct Node *new_node = (struct Node *) malloc(sizeof(struct Node));
    new_node->id = clientId;
    new_node->time = clientTime;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void append(struct Node **head_ref, int clientId, int clientTime) {
    if (isDebug == 1) printf("Dodanie klienta o id: %d czas: %d\n", clientId, clientTime);
    struct Node *new_node = (struct Node *) malloc(sizeof(struct Node));
    struct Node *last = *head_ref;
    new_node->id = clientId;
    new_node->time = clientId;
    new_node->next = NULL;
    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }
    while (last->next != NULL)
        last = last->next;
    last->next = new_node;
}

void printList(struct Node *node) {
    while (node != NULL) {
        printf(" %d ", node->id);
        node = node->next;
    }
}

void addToWList(int clientId, int clientTime) {
    append(&waitingClients, clientId, clientTime);
    printWList();
}

void deleteNode(struct Node **head_ref, int key) {
    struct Node *temp = *head_ref, *prev;
    if (temp != NULL && temp->id == key) {
        *head_ref = temp->next;
        free(temp);
        return;
    }
    while (temp != NULL && temp->id != key) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) return;
    prev->next = temp->next;
    free(temp);
    printWList();
}

void addToRList(int clientId, int clientTime) {
    append(&rejectedClients, clientId, clientTime);
    printf("Nie obsluzono: \n");
    printList(rejectedClients);
    printf("\n");
}
