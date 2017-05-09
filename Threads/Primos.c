#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 9
#define NUM_MAX /*99999*/50
int num_primos = 0;
int *arrayPrimos = NULL;
int incremento = (int)(NUM_MAX/NUM_THREADS);
pthread_mutex_t bufferPrimosLock = PTHREAD_MUTEX_INITIALIZER;

void *encontrarPrimos(void *param) {
    // Definição de intervalo
    int low = (int)param * incremento;
    int high = low + incremento;

    while (low < high) {
        int flag = 0;

        for (size_t i = 2; i <= low/2; i++) {
            if (low % i == 0) {
                flag = 1;
                break;
            }
        }

        // Seção crítica
        pthread_mutex_lock(&bufferPrimosLock);
            // Adicionar o primo ao vetor
            if (flag == 0 & low != 1 && low != 0) {
                arrayPrimos = realloc((int *) arrayPrimos, (num_primos+1)*sizeof(int));
                arrayPrimos[num_primos] = low;
                // printf("%d \n", low);
                num_primos++;
            }

            ++low;
        pthread_mutex_unlock(&bufferPrimosLock);
    }
}

int main(int argc, char const *argv[]) {
    pthread_t threads[NUM_THREADS];
    arrayPrimos = (int *) malloc(sizeof(int));

    for (size_t i = 0; i < NUM_THREADS; i++)
        pthread_create(&threads[i], NULL, encontrarPrimos, (void *) i);

    for (size_t i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);

    printf("Threads encerraram.\nArray de primos (são %d):\n", num_primos);
    for (size_t i = 0; i < num_primos; i++)
        printf("[%d]\n", arrayPrimos[i]);

    return 0;
}
