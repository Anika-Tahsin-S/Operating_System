#include <pthread.h> // A mutex (named for "mutual exclusion") a binary semaphore with an ownership restriction: it can be unlocked (the post operation) only by whoever locked it (the wait operation). 
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAX 10 //producers and consumers can produce and consume upto MAX
#define BUFLEN 6
#define NUMTHREAD 2   /* number of threads */

void *consumer(int *id);
void *producer(int *id);

char buffer[BUFLEN];
char source[BUFLEN];//from this array producer will store it's production into buffer
int pCount = 0;
int cCount = 0;
int buflen;

//initializing pthread mutex and condition variables
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t nonEmpty = PTHREAD_COND_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;
int thread_id[NUMTHREAD] = {0, 1};

int main()
{
    int i;
    /* define the type to be pthread */
    pthread_t thread[NUMTHREAD];

    strcpy(source, "abcdef");
    buflen = strlen(source);

    pthread_mutex_init(&count_mutex, NULL);
    pthread_cond_init(&nonEmpty, NULL);
    pthread_cond_init(&full, NULL);

    for (i = 0; i < NUMTHREAD; i++)
    {
        pthread_create(&thread[i], NULL, (void *(*)(void *))(i == 0 ? &producer : &consumer), (void *)&thread_id[i]); if (i == 0) sleep(1); // ternary conditional operator condition ?
    }
    // thread[i] = to store thread ID
    // (void *)&thread_id[i] passes the address of thread_id array element to the function being called
    // if producer sleep(1) while printing


    for (i = 0; i < NUMTHREAD; i++)
    {
        pthread_join(thread[i], NULL);
    }

    pthread_mutex_destroy(&count_mutex); // count_mutex becomes uninitialized.
    pthread_cond_destroy(&nonEmpty);
    pthread_cond_destroy(&full);

    return 0;
}

void *producer(int *id)
{
    int i = 0;
    while (i < MAX)
    {
        pthread_mutex_lock(&count_mutex); // ensure exclusive access to critical sections where shared variables (pCount and cCount) and buffer are manipulated.

        while ((pCount - cCount) == BUFLEN) // checking for full buffer
        {
            pthread_cond_wait(&full, &count_mutex); // helps avoid overproduction when buffer is full.
        }

        char produce = source[pCount % buflen]; // item to be placed in the buffer. selects an item from the source array based on the current value of pCount using modulo % to ensure cycling through the source array
        buffer[pCount % buflen] = produce; // Places the produced item into the buffer
        printf("%d produced %c by Thread %d\n", pCount, produce, *id);
        pCount++;

        pthread_mutex_unlock(&count_mutex); // allowing other threads to access the critical section.
        pthread_cond_signal(&nonEmpty); // Signals the consumer thread that the buffer is no longer empty, which allows the consumer to consume items.

        sleep(1);
        i++;
    }

    pthread_exit(NULL);
}

void *consumer(int *id)
{
    int j = 0;
    while (j < MAX)
    {
        pthread_mutex_lock(&count_mutex);

        while (cCount == pCount) // checks whether buffer is empty. If true=empty, the consumer waits by calling 
        {
            pthread_cond_wait(&nonEmpty, &count_mutex); // helps avoid consuming when there are no items in the buffer.
        }

        char consume = buffer[cCount % buflen]; // takes an item from the buffer. selects an item from the buffer based on the current value of cCount using modulo % to ensure cycling through the buffer
        printf("%d consumed %c by Thread %d\n", cCount, consume, *id);
        cCount++;

        pthread_mutex_unlock(&count_mutex);
        pthread_cond_signal(&full);

        sleep(2);
        j++;

        if (cCount == 5) {
            pthread_exit(NULL); // Exit consumer thread after consuming 4 items
        }
    }

    pthread_exit(NULL);
}


