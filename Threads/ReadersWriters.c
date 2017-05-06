#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

/*  READERS & WRITERS PROBLEM
    'N' readers reading at the same time
    '1' writer writing at a time
*/

/* Global variables */
#define NUMBER_OF_READERS 2
#define NUMBER_OF_WRITERS 2
#define READERS_VALUE 0
#define WRITERS_VALUE 666
#define BUFFER_SIZE 5
pthread_mutex_t bookLock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t rwCondtion = PTHREAD_COND_INITIALIZER;
int buffer[BUFFER_SIZE] = {1,2,3,4,5};
int writing = 1;
int reading = 0;

/* Thread functions */
void *reader(void *param) {
    int i = 0;

    // TODO: Faltou dar signal no primeiro lock

    while (1) {
        pthread_mutex_lock(&bookLock);
            while (writing > 0) {
                printf("Não estou lendo.\n");
                pthread_cond_wait(&rwCondtion, &bookLock);
            }
            reading++;
        pthread_mutex_unlock(&bookLock);

        printf("Estou lendo.\n");
        buffer[i] = READERS_VALUE;
        i = (i + 1) % 10;

        pthread_mutex_lock(&bookLock);
            printf("Já li.\n");
            reading--;
            pthread_cond_broadcast(&rwCondtion);
        pthread_mutex_unlock(&bookLock);
    }
}
void *writer(void *param) {
    int i = 0;

    // TODO: Faltou dar signal no primeiro lock

    while (1) {
        pthread_mutex_lock(&bookLock);
            // Garantees 1 writer writing/time
            while (reading || writing) {
                printf("Esperando minha vez de ler.\n");
                pthread_cond_wait(&rwCondtion, &bookLock);
            }

            writing++;
        pthread_mutex_unlock(&bookLock);

        printf("Estou escrevendo.\n");
        buffer[i] = WRITERS_VALUE;
        i = (i + 1) % 10;

        pthread_mutex_lock(&bookLock);
            writing--;
            printf("Já li.\n");
            pthread_cond_broadcast(&rwCondtion);
        pthread_mutex_unlock(&bookLock);
    }
}

int main(int argc, char const *argv[]) {
    pthread_t readers[NUMBER_OF_READERS];
    pthread_t writers[NUMBER_OF_WRITERS];

    int num_of_threads = (int) NUMBER_OF_READERS + (int) NUMBER_OF_WRITERS;

    for (size_t i = 0; i < num_of_threads; i++) {
        /* Readers */
        pthread_create(&readers[i], NULL, reader, NULL);

        /* Writers */
        pthread_create(&writers[i], NULL, writer, NULL);
    }

    return 0;
}
