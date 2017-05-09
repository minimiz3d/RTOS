#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define NUM_THREADS 3

pthread_mutex_t varLock = PTHREAD_MUTEX_INITIALIZER;
int var = 0;
typedef struct {
    int id;
    int value;
} thread_info;

void *threadFunc(void *info) {
    thread_info *INFO = (thread_info*) info;

    printf("Sou a thread %d. Meu valor é: %d\n", (int)INFO->id, INFO->value);

    int local = 0;
    for (size_t i = 0; i < 5; i++)
        local++;

    pthread_mutex_lock(&varLock);
        printf("var_antes = %d\n", var);
        var += local;
        printf("var_depois = %d\n", var);
    pthread_mutex_unlock(&varLock);
}

int main(int argc, char const *argv[]) {
    pthread_t THREADS[NUM_THREADS];
    thread_info *threads = calloc((int) NUM_THREADS, sizeof(thread_info));

    for (size_t i = 0; i < NUM_THREADS; i++) {
        threads[i].id = i;
        threads[i].value = 10 * i;
        pthread_create(&THREADS[i], NULL, threadFunc, &threads[i]);
    }

    // Main Thread espera pelas outras encerrarem
    for (size_t i = 0; i < NUM_THREADS; i++)
        pthread_join(&THREADS[i], NULL);

    pthread_exit(NULL);

    return 0;
}
