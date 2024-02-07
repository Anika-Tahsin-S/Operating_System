#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int ticketsLeft = 10;

void* purchaseTicket(void* arg) {
    int* person = (int*)arg;
    int ticketNumber;

    while (1) {
        pthread_mutex_lock(&mutex);

        if (ticketsLeft > 0) {
            ticketNumber = 10 - ticketsLeft + 1;
            printf("Person %d is purchasing\nTickets left: %d\n", *person, ticketsLeft);
            ticketsLeft--;

            pthread_mutex_unlock(&mutex);

            // Simulate the purchase process
            sleep(1);

            printf("Person: %d, Purchase Done\n", *person);
        } else {
            pthread_mutex_unlock(&mutex);
            printf("Person: %d, Purchase failed\nTickets left: 0\n", *person);
            break;
        }

        // Wait for the next pair of persons to complete their purchase
        sleep(1);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[12];
    int persons[12];

    for (int i = 0; i < 12; i++) {
        persons[i] = i + 1;
        pthread_create(&threads[i], NULL, purchaseTicket, (void*)&persons[i]);
    }

    for (int i = 0; i < 12; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}