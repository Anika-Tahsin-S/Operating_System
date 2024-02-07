#include <stdio.h>
#include <pthread.h>
#define NUM_THREADS 5

void *threadFunction(void *threadId) {
    long tid = (long)threadId;

    printf("Thread-%ld running\n", tid);

    for (int i = 0; i < 1000000; i++) {
    }

    printf("Thread-%ld closed\n", tid);
    pthread_exit(NULL);
}

int main() {
    pthread_t create_thread[NUM_THREADS];
    for (long i = 1; i <= NUM_THREADS; i++) {
        pthread_create(&create_thread[i - 1], NULL, threadFunction, (void *)i);
        pthread_join(create_thread[i - 1], NULL);
    }
    pthread_exit(NULL);
}

