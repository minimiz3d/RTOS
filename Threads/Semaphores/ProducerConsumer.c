#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 16
int ringBuffer[BUFFER_SIZE] = {0};
int in, out = 0;
pthread_mutex_t bufferLock = PTHREAD_MUTEX_INITIALIZER;
sem_t count_sem, space_sem;

void *producer(void *value) {
    int data = (int) value;

    while (1) {
        sem_wait(&space_sem);
            // Critical Section
            pthread_mutex_lock(&bufferLock);
                printf("\nBuffer before adding new value:\n");
                for (size_t i = 0; i < BUFFER_SIZE; i++)
                    printf("[%d] ", ringBuffer[i]);

                ringBuffer[in++ & BUFFER_SIZE - 1] = data;
                usleep(1000);

                printf("\nBuffer after adding new value:\n");
                for (size_t i = 0; i < BUFFER_SIZE; i++)
                    printf("[%d] ", ringBuffer[i]);
            pthread_mutex_unlock(&bufferLock);
        sem_post(&count_sem);
    }

}
void *consumer() {
    while (1) {
        sem_wait(&count_sem);
            // Critical Section
            pthread_mutex_lock(&bufferLock);
                printf("\nBuffer before removing value:\n");
                for (size_t i = 0; i < BUFFER_SIZE; i++)
                    printf("[%d] ", ringBuffer[i]);

                ringBuffer[in++ & BUFFER_SIZE - 1] = -1;
                sleep(1);

                printf("\nBuffer after removing value:\n");
                for (size_t i = 0; i < BUFFER_SIZE; i++)
                    printf("[%d] ", ringBuffer[i]);
            pthread_mutex_unlock(&bufferLock);
        sem_post(&space_sem);
    }
}
void init() {
    sem_init(&count_sem, 0, 0);
    sem_init(&space_sem, 0, 16);
}

int main(int argc, char const *argv[]) {
    pthread_t producer_thread, consumers[2];
    int value = 5;

    init();

    pthread_create(&producer_thread, NULL, producer, (void *) value);
    pthread_create(&consumers[0], NULL, consumer, NULL);
    pthread_create(&consumers[1], NULL, consumer, NULL);

    pthread_exit(NULL);

    return 0;
}
