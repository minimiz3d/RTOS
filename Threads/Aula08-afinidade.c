#define _GNU_SOURCE
#include <sched.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

void *teste(void *arg) {
    int *tid;
    long i;
    tid = (int *)arg;

    printf("tid(%d) antes do loop\n", *tid);
    for (i = 0; i < 100000000; i++) { }
    //    printf("tid(%d) i = %d\n", *tid, i);
    printf("tid(%d) apos o loop\n", *tid);

    pthread_exit(NULL);
}

int main() {
    pthread_t t;
    int tid = 5, i;
    cpu_set_t s, s1;
    long procs;

    // Obtem quantidade de processadores disponiveis
    procs = sysconf(_SC_NPROCESSORS_ONLN);
    printf("Processadores disponiveis = %ld\n", procs);

    // Limpa a estrutura cpu_set_s
    CPU_ZERO(&s);

    // Adiciona a CPU 0 e 2 ao conjunto de CPUS
    CPU_SET(0, &s);
    CPU_SET(2, &s);

    // Conta a quantidade de CPUs da estrutura
    printf("%d CPUs fazem parte do conjunto\n", CPU_COUNT(&s));

    // Verifica quais CPUs fazem parte da estrutura
    for (i = 0; i < procs; i++)
        if (CPU_ISSET(i, &s))
          printf("CPU %d FAZ parte do conjunto\n", i);
        else
          printf("CPU %d NAO FAZ parte do conjunto\n", i);

    // Remove a CPU 0 do conjunto
    CPU_CLR(0, &s);

    // Conta a quantidade de CPUs da estrutura
    printf("%d CPUs fazem parte do conjunto\n", CPU_COUNT(&s));

    // Verifica quais CPUs fazem parte da estrutura
    for (i = 0; i < procs; i++)
        if (CPU_ISSET(i, &s))
          printf("CPU %d FAZ parte do conjunto\n", i);
        else
          printf("CPU %d NAO FAZ parte do conjunto\n", i);
    pthread_create(&t, NULL, teste, (void *)&tid);

    // Define a afinidade da thread para o processador 2
    pthread_setaffinity_np(t, sizeof(s), &s);
    printf("Obtem valores de afinidade da thread\n");

    // Limpa o conjunto
    CPU_ZERO(&s1);

    // Obtem afinidade da thread
    pthread_getaffinity_np(t, sizeof(s1), &s1);

    // Verifica quais CPUs fazem parte da estrutura
    for (i = 0; i < procs; i++)
        if (CPU_ISSET(i, &s1))
          printf("CPU %d FAZ parte do conjunto\n", i);
        else
          printf("CPU %d NAO FAZ parte do conjunto\n", i);
    pthread_join(t, NULL);

    return 0;
}
