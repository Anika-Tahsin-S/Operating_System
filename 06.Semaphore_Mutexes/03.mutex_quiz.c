#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define TOTAL_TICKETS 10
#define TOTAL_PERSONS 12

pthread_mutex_t lock;
int ticketsLeft = TOTAL_TICKETS;

void* purchaseTicket(void* arg) {
    int personID = *((int*)arg);
    pthread_mutex_lock(&lock);
    if (ticketsLeft > 0) {
        printf("Person %d is purchasing\n", personID);
        printf("Tickets left: %d\n", ticketsLeft);
        printf("Person: %d, Purchase Done\n", personID);
        ticketsLeft--;
    } else {
        printf("Person %d can not purchase\n", personID);
        printf("Tickets left: 0\n");
        printf("Person: %d, Purchase failed\n", personID);
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    pthread_t threads[TOTAL_PERSONS];
    int personIDs[TOTAL_PERSONS];

    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < TOTAL_PERSONS; i += 2) {
        personIDs[i] = i + 1;
        personIDs[i + 1] = i + 2;
        pthread_create(&threads[i], NULL, purchaseTicket, &personIDs[i]);
        pthread_create(&threads[i + 1], NULL, purchaseTicket, &personIDs[i + 1]);
        pthread_join(threads[i], NULL);
        pthread_join(threads[i + 1], NULL);
    }

    pthread_mutex_destroy(&lock);

    return 0;
}

