#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

/* Global variables */
#define BUFFER_VALUE 5
#define EMPTY 0
#define BUFFER_SIZE 10
#define NUM_THREADS 2
int buffer[BUFFER_SIZE] = {0};
int currentBufferSize = 0;
pthread_mutex_t bufferLock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t sizeCondition = PTHREAD_COND_INITIALIZER;

/* Functions */
void *producer(void *param) {
    int i = 0;

    while (1) {
        /* Enter critical section */
        pthread_mutex_lock(&bufferLock);
            while (currentBufferSize == BUFFER_SIZE) {
                printf("Produtor esperando.\n");
                pthread_cond_wait(&sizeCondition, &bufferLock);
            }

            printf("\nBuffer antes da produção (tamanho = %d):\n", currentBufferSize);
            for (size_t j = 0; j < BUFFER_SIZE; j++)
                printf("[%d] ", buffer[j]);

            buffer[i] = BUFFER_VALUE;
            i = (i + 1) % 10;
            currentBufferSize++;

            printf("\nBuffer depois da produção (tamanho = %d):\n", currentBufferSize);
            for (size_t j = 0; j < BUFFER_SIZE; j++)
                printf("[%d] ", buffer[j]);
            printf("\n");

            pthread_cond_signal(&sizeCondition);
        pthread_mutex_unlock(&bufferLock);

        // sleep(1);
    }

}
void *consumer(void *param) {
    int i = 0;

    while (1) {
        /* Enter critical section */
        pthread_mutex_lock(&bufferLock);
            while (currentBufferSize == EMPTY) {
                printf("Consumidor esperando.\n");
                pthread_cond_wait(&sizeCondition, &bufferLock);
            }

            printf("\nBuffer antes do consumo (tamanho = %d):\n", currentBufferSize);
            for (size_t j = 0; j < BUFFER_SIZE; j++)
                printf("[%d] ", buffer[j]);

            buffer[i] = 0;
            i = (i + 1) % 10;
            currentBufferSize--;

            printf("\nBuffer depois do consumo (tamanho = %d):\n", currentBufferSize);
            for (size_t j = 0; j < BUFFER_SIZE; j++)
                printf("[%d] ", buffer[j]);
            printf("\n");

            pthread_cond_signal(&sizeCondition);
        pthread_mutex_unlock(&bufferLock);

        // sleep(1);
    }
}

int main(int argc, char const *argv[]) {
    pthread_t threads[NUM_THREADS];

    while (1) {
        /* Producer */
        pthread_create(&threads[0], NULL, producer, NULL);

        /* Consumer */
        pthread_create(&threads[1], NULL, consumer, NULL);
    }

    return 0;
}
