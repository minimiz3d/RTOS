#include <pthread.h>
#include <stdio.h>

#define N 16
/* Global Variables */
pthread_mutex_t varLock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t varCond = PTHREAD_COND_INITIALIZER;
int data[256][8192];
int remain = N;

void *calc(void *param) {
    int x, y, start = N * (int) param;
    int end = start + N;

    for (x = start; x < end; x++)
        for (y = 0; y < 8192; y++)
            printf("Calculando...\n");

    printf("Fim de cálculo.\n");

    /* Seção crítica
    Daria pra fazer com uma variável começando em 0 indo até N, para saber quantas já fizeram o trabalho.
    Dessa forma, o teste da variável de condição seria: while (executadas == 0) {p_c_wait} e if (executadas == N) {p_c_broadcast}
     */
    pthread_mutex_lock(&varLock);
        remain--;

        if (remain == 0) {
            printf("Todas as threads executaram.\n");
            pthread_cond_broadcast(&varCond);
        } else {
            while (remain != 0) {
                printf("Ainda há threads que precisam executar.\n");
                pthread_cond_wait(&varCond, &varLock);
            }
        }
    pthread_mutex_unlock(&varLock);
}

int main(int argc, char const *argv[]) {
    pthread_t threads[N];

    for (size_t i = 0; i < N; i++)
        pthread_create(&threads[i], NULL, calc, (void *) i);

    return 0;
}
