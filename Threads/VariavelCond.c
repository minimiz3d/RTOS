#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 5

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int threads = 0;

void *PrintHello(void *threadid) {
    long tid, i;
    tid = (long)threadid;
    usleep(500000);
    printf("Thread %ld tentando obter mutex!\n", tid);
    // Até aqui tem competição entre as threads para tentar obter o mutex. Depois de obtido, ela executa até o wait.
    // .:. lock -> executando no mutex -> cond_wait.

    pthread_mutex_lock(&mutex);
    printf("Thread %ld executando no mutex!\n", tid);
    threads++;
    while (threads != 5) {
        printf("Thread %ld executando wait!\tThreads_Var = %d\n", tid, threads);
        pthread_cond_wait(&cond, &mutex);
    }
    usleep(1000000);
    printf("\nThread %ld executando signal!\n", tid);
    pthread_cond_signal(&cond);
    // pthread_cond_broadcast(&cond);
    printf("Thread %ld saindo do mutex!\n", tid);
    pthread_mutex_unlock(&mutex);

    printf("Thread %ld fora do mutex!\n", tid);
    pthread_exit(NULL);
}

int main (int argc, char *argv[]) {
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;

    for(t=0; t<NUM_THREADS; t++) {
        printf("In main: creating thread %ld\n", t);
        rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);

        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    for (t = 0; t < NUM_THREADS; t++)
        pthread_join(threads[t],NULL);
}
