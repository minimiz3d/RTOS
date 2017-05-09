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
#define NUMBER_OF_READERS 3
#define NUMBER_OF_WRITERS 2
#define BUFFER_SIZE 5
pthread_mutex_t bookLock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t rwCondition = PTHREAD_COND_INITIALIZER;
int buffer[BUFFER_SIZE] = {1,2,3,4,5}; // Meramente ilustrativo
int writing = 0;
int reading = 0;
int writers = 0;

/* Thread functions */
void *reader(void *param) {
    int id = (int) param;

    pthread_mutex_lock(&bookLock);
        while (writing || writers) {
            printf("R%d: Não estou lendo.\n", id);
            printf("~DEBUG: writers = %d\twriting = %d\n", writers, writing);
            pthread_cond_wait(&rwCondition, &bookLock);
        }

        reading++;
        printf("R%d: Estou lendo.\n", id);
        pthread_cond_broadcast(&rwCondition);
    pthread_mutex_unlock(&bookLock);

    pthread_mutex_lock(&bookLock);
        printf("R%d: Já li.\n", id);
        reading--;
        pthread_cond_broadcast(&rwCondition);
    pthread_mutex_unlock(&bookLock);
}
void *writer(void *param) {
    int id = (int) param;

    pthread_mutex_lock(&bookLock);
        // Entrando na fila dos leitores
        if (writers < NUMBER_OF_WRITERS)
            writers++;

        // Garantees 1 writer writing/time
        while (reading || writing) {
            printf("W%d: Esperando minha vez de escrever.\n", id);
            printf("~DEBUG: reading = %d\twriting = %d\twriters = %d\n", reading, writing, writers);
            pthread_cond_wait(&rwCondition, &bookLock);
        }

        writing++;
        printf("W%d: Estou escrevendo.\n", id);
    pthread_mutex_unlock(&bookLock);

    pthread_mutex_lock(&bookLock);
        writing = 0;
        writers--;
        printf("W%d: Já escrevi.\n", id);
        printf("Writers = %d\n", writers);
        pthread_cond_broadcast(&rwCondition);
    pthread_mutex_unlock(&bookLock);
}

int main(int argc, char const *argv[]) {
    pthread_t readers[NUMBER_OF_READERS];
    pthread_t writers[NUMBER_OF_WRITERS];

    while (1) {
        for (size_t i = 0; i < NUMBER_OF_WRITERS; i++)
            pthread_create(&writers[i], NULL, writer, (void *) i);

        for (size_t i = 0; i < NUMBER_OF_READERS; i++)
            pthread_create(&readers[i], NULL, reader, (void *) i);
    }

    return 0;
}
