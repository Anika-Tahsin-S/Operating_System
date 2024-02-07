#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define TOTAL_TICKETS 10
#define TOTAL_PERSONS 12

sem_t semaphore;
int tickets_Left = TOTAL_TICKETS;

void* purchaseTicket(void* arg) {
    int person_in_queue = *((int*)arg);
    sem_wait(&semaphore);
    if (tickets_Left > 0) {
        printf("Person %d is purchasing\n", person_in_queue);
        printf("Tickets left: %d\n", tickets_Left);
        printf("Person: %d, Purchase Done\n", person_in_queue);
        tickets_Left--;
    } else {
        printf("Person %d can not purchase\n", person_in_queue);
        printf("Tickets left: 0\n");
        printf("Person: %d, Purchase failed\n", person_in_queue);
    }
    sem_post(&semaphore);
    return NULL;
}

int main() {
    pthread_t threads[TOTAL_PERSONS];
    int all_person_in_queue[TOTAL_PERSONS];
    sem_init(&semaphore, 0, 1);
    for (int i = 0; i < TOTAL_PERSONS; i += 2) {
        all_person_in_queue[i] = i + 1;
        all_person_in_queue[i + 1] = i + 2;
        pthread_create(&threads[i], NULL, purchaseTicket, &all_person_in_queue[i]);
        pthread_create(&threads[i + 1], NULL, purchaseTicket, &all_person_in_queue[i + 1]);
        pthread_join(threads[i], NULL);
        pthread_join(threads[i + 1], NULL);
    }
    sem_destroy(&semaphore);
    return 0;
}
