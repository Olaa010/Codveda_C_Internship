#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_ITEMS 10

int buffer[BUFFER_SIZE];
int in = 0, out = 0, count = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t not_full = PTHREAD_COND_INITIALIZER;
pthread_cond_t not_empty = PTHREAD_COND_INITIALIZER;

void* producer(void* arg){
    for(int i=1;i<=NUM_ITEMS;i++){
        pthread_mutex_lock(&mutex);
        while(count==BUFFER_SIZE){
            printf("[Producer] Buffer full, waiting...\n");
            pthread_cond_wait(&not_full, &mutex);
        }
        buffer[in]=i;
        printf("[Producer] Produced %d at index %d (count=%d)\n", i, in, count+1);
        in = (in+1)%BUFFER_SIZE;
        count++;
        pthread_cond_signal(&not_empty);
        pthread_mutex_unlock(&mutex);
        usleep(200000); // simulate work 0.2s
    }
    printf("[Producer] Finished producing.\n");
    return NULL;
}

void* consumer(void* arg){
    for(int i=1;i<=NUM_ITEMS;i++){
        pthread_mutex_lock(&mutex);
        while(count==0){
            printf("[Consumer] Buffer empty, waiting...\n");
            pthread_cond_wait(&not_empty, &mutex);
        }
        int item=buffer[out];
        printf("[Consumer] Consumed %d from index %d (count=%d)\n", item, out, count-1);
        out = (out+1)%BUFFER_SIZE;
        count--;
        pthread_cond_signal(&not_full);
        pthread_mutex_unlock(&mutex);
        usleep(400000); // consumer slower 0.4s
    }
    printf("[Consumer] Finished consuming.\n");
    return NULL;
}

int main(){
    printf("=== Multithreaded Producer-Consumer - Level 3 Task 2 ===\n");
    printf("Buffer Size: %d, Items: %d\n", BUFFER_SIZE, NUM_ITEMS);
    printf("Using POSIX threads, mutex, and condition variables.\n\n");

    pthread_t prod_thread, cons_thread;
    
    if(pthread_create(&prod_thread, NULL, producer, NULL)!=0){
        perror("Failed to create producer thread"); return 1;
    }
    if(pthread_create(&cons_thread, NULL, consumer, NULL)!=0){
        perror("Failed to create consumer thread"); return 1;
    }

    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    printf("\nAll threads completed. Program safe and synchronized.\n");
    
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&not_full);
    pthread_cond_destroy(&not_empty);
    return 0;
}
