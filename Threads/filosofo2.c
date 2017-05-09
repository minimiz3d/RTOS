#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define NUM_THREADS 5

pthread_mutex_t garfo[NUM_THREADS] = PTHREAD_MUTEX_INITIALIZER;
int garfos[5]={0,0,0,0,0};
pthread_cond_t c[5] = {0,0,0,0,0};


void *filosofo(void *threadid) {
    long tid;
    tid = (long)threadid;
    while (1){
        printf("Thread %ld tentando obter garfo à esquerda!\n", tid);
        if (pthread_mutex_lock(&garfo[(tid+1)%NUM_THREADS])){ //errado
            while(garfos[(tid+1)%NUM_THREADS]!=0){
                pthread_cond_wait(&c[(tid+1)%NUM_THREADS], &garfo[(tid+1)%NUM_THREADS]);
            }
            garfos[(tid+1)%NUM_THREADS]=1;

            printf("Thread %ld tentando obter garfo à direita!\n", tid);
            //unlock do acima
            if(pthread_mutex_lock(&garfo[tid])){ //nao é dentro do outro lock
                while(garfos[tid!=0]){
                    pthread_cond_wait(&c[tid], &garfo[tid]);
                }
                garfos[tid]=1;
                printf("Filosofo %ld COMENDO!\n", tid);
                usleep(100);
                printf("Filosofo %ld liberando o garfo à direita!\n", tid);
                pthread_mutex_unlock(&garfo[(tid+1)%NUM_THREADS]);
                printf("Filosofo %ld liberando o garfo à direita!\n", tid);
                pthread_mutex_unlock(&garfo[tid]);
                printf("Thread %ld fora do mutex!\n", tid);
            }
        }
        garfos[(tid+1)%NUM_THREADS]=0;
        garfos[tid]=0;
    }
    pthread_exit(NULL);
}
int main (int argc, char *argv[]) {
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;
    for(t=0; t<NUM_THREADS; t++){
        printf("In main: creating thread %ld\n", t);
        rc = pthread_create(&threads[t], NULL, filosofo, (void *)t);
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
        exit(-1);
        }
    }

    for (t = 0; t < NUM_THREADS; t++)
        pthread_join(threads[t],NULL);
}
