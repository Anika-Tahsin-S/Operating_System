#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 6
#define NUM_INTS_PER_THREAD 5

void *threadFunction(void *threadId) {
    long tid = (long)threadId;
    for (int i = 1; i <= NUM_INTS_PER_THREAD; i++) {
        printf("Thread %ld prints %ld\n", tid, (tid * NUM_INTS_PER_THREAD) + i);
        for (int j = 0; j < 10000000; j++) {}
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    for (long i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, threadFunction, (void *)i)) {
            fprintf(stderr, "Error creating thread %ld\n", i);
            return 1;
        }
        pthread_join(threads[i], NULL);
    }
    return 0;
}

