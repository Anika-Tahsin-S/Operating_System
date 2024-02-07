#include <pthread.h>
#include <semaphore.h> // an integer whose value is never allowed to fall below 0.
#include <stdio.h>
/*
This program provides a possible solution using mutex and semaphore.
use 5 Farmers and 5 ShopOwners to demonstrate the solution.
*/
#define MaxCrops 5 // Maximum crops a Farmer can produce or a Shpoowner can take
#define warehouseSize 5 // Size of the warehouse
sem_t empty;
sem_t full;
int in = 0;
int out = 0;
char crops[warehouseSize]={'R','W','P','S','M'}; //indicating room for different crops
char warehouse[warehouseSize]={'N','N','N','N','N'}; //initially all the room is empty
pthread_mutex_t mutex;


void *Farmer(void *far) 
{
    for (int i = 0; i < MaxCrops; i++){
        int x = *(int *)far;
        sem_wait(&empty); //sema_val > 0, sema decremented by 1. If sema_val = 0, the caller will be blocked (busy-waiting or more likely on a queue) until sema_val > 0, and then decremented by 1
        pthread_mutex_lock(&mutex);
        warehouse[in]=crops[x]; 
        printf("Farmer %d: insert crops %c at %d\n", *((int *)far), crops[x], in);
        in = (in + 1) % warehouseSize; // updating next available crop
        pthread_mutex_unlock(&mutex);
        sem_post(&full); // post operation increments the semaphore by 1
    }
    printf("Farmer%d: %.*s\n", *(int*)far, warehouseSize, warehouse);
}

void *ShopOwner(void *sho) 
{
    for (int i = 0; i < MaxCrops; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        printf("ShopOwner %d: remove crops %c from %d\n", *((int *)sho), warehouse[out], out); 
        warehouse[out] = 'N';
        out = (out + 1) % warehouseSize; // // updating next slot/crop to be taken
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
    printf("ShopOwner%d: %.*s\n", *(int*)sho, warehouseSize, warehouse);
}

int main() 
    {
    /*initializing thread,mutex,semaphore
    */
    pthread_t Far[5], Sho[5]; // arrays to store the thread IDs 
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, warehouseSize);//when the warehouse is full thread will wait
    sem_init(&full, 0, 0);//when the warehouse is empty thread will wait

    int a[5] = {1, 2, 3, 4, 5}; //Just used for numbering the Farmer and ShopOwner
    
    for (int i = 0; i < 5; i++) {
        pthread_create(&Far[i], NULL, (void *)Farmer, (void *)&a[i]);
        pthread_create(&Sho[i], NULL, (void *)ShopOwner, (void *)&a[i]);
    }
    for (int i = 0; i < 5; i++) {
        pthread_join(Far[i], NULL); // Waits for the completion of each farmer thread before continuing
        pthread_join(Sho[i], NULL); // Waits for the completion of each ShO thread before continuing
    }
    
    //  Closing or destroying mutex and semaphore
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty); // empty becomes uninitialized.
    sem_destroy(&full); // full becomes uninitialized.
    return 0;
}
