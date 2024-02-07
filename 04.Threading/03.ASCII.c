#include <stdio.h>
#include <pthread.h>
#include <string.h>
#define MAX_NAME_LENGTH 100
#define NUM_THREADS 3

struct Thread {
    char name[MAX_NAME_LENGTH];
    int result;
};

int ASCII_Sum(const char *name) {
    int sum = 0;
    while (*name != '\0') {
        sum += *name++;
    }
    return sum;
}

void *threadFunction(void *threadDataPtr) {
    struct Thread *data = (struct Thread *)threadDataPtr;
    data->result = ASCII_Sum(data->name);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    struct Thread threadData[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        printf("Enter name %d: ", i + 1);
        scanf("%s", threadData[i].name);
        pthread_create(&threads[i], NULL, threadFunction, (void *)&threadData[i]);
        pthread_join(threads[i], NULL);
    }

    int result1 = threadData[0].result;
    int result2 = threadData[1].result;
    int result3 = threadData[2].result;

    if (result1 == result2 && result2 == result3) {
        printf("Youreka\n");
    } else if (result1 == result2 || result2 == result3 || result1 == result3) {
        printf("Miracle\n");
    } else {
        printf("Hasta la vista\n");
    }
    return 0;
}

