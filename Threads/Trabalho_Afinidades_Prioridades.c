/* Modificar o código encontrado no Moodle para a aula 9 (que implementa duas threads executando por 5 segundos de CPU), de forma que:

1) A thread 1 sempre termine antes da thread 2 - uso de prioridades e política de escalonamento.

2) Ambas as threads executem no mesmo processador - uso de afinidades. */

#define _GNU_SOURCE
#include <sched.h>
#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>

#define N_SEGUNDOS 1

void *thread_teste(void *arg) {
	int tid;
	tid = (int)arg;

	// estrutura para obter/setar o tempo de um relógio
	struct timespec tempo_atual;

	// obtém o tempo atual do relógio que conta o tempo de CPU da thread (CLOCK_THREAD_CPUTIME_ID)
	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &tempo_atual);

	// imprime o tempo atual obtido do relógio
	printf("TID %d: Clock Atual %ld segundos e %ld nanosegundos!\n", tid, tempo_atual.tv_sec, tempo_atual.tv_nsec);

	// força a execução da thread por N_SEGUNDOS
	while (tempo_atual.tv_sec < N_SEGUNDOS) {
		clock_gettime(CLOCK_THREAD_CPUTIME_ID, &tempo_atual);
	}

	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &tempo_atual);
	printf("TID %d: Clock Atual %ld segundos e %ld nanosegundos!\n", tid, tempo_atual.tv_sec, tempo_atual.tv_nsec);
	pthread_exit(NULL);
}

int main() {
	// Afinidade
	cpu_set_t s;

	// Prioridade
	struct sched_param param1, param2;

	// Verificar CPUs disponiveis
	long procs = sysconf(_SC_NPROCESSORS_ONLN);
	printf("Processadores disponiveis = %ld\n", procs);

	// Definindo a conjunto de CPUs
	CPU_ZERO(&s);
	CPU_SET(0, &s);

	printf("%d CPUs no conjunto.\n", CPU_COUNT(&s));

	// 2 threads
	pthread_t t[2];

	// estrutura para obter/setar o tempo de um relógio
	struct timespec tempo_atual, tempo_atual1;

	// obtém o tempo atual do relógio que conta o tempo passado a partir de uma época específica (CLOCK_MONOTONIC)
	// no Linux essa época é o tempo de início do sistema
	// esse relógio não pode ser modificado, garantindo que ele é sempre crescente (monotônico)
	clock_gettime(CLOCK_MONOTONIC, &tempo_atual);
	printf("MAIN: Clock MONOTONIC Atual %ld segundos e %ld nanosegundos!\n", tempo_atual.tv_sec, tempo_atual.tv_nsec);

	int creation = 1;
	creation = pthread_create(&t[0], NULL, thread_teste, (void *)0);
	while (creation != 0) {}
	pthread_create(&t[1], NULL, thread_teste, (void *)1);

	// Prioridades
	int prio_min, prio_max;
	prio_min = sched_get_priority_min(SCHED_FIFO);
	prio_max = sched_get_priority_max(SCHED_FIFO);

	// Definição das priodades (thread[0].priority > thread[1].priority)
	param1.sched_priority = (int)prio_max; printf("prior1 = %d\n", param1.sched_priority);
	int ret = pthread_setschedparam(t[0], SCHED_FIFO, &param1);
	if (ret != 0) {
        printf("Erro pthread_setschedparam! Thread1\nERRO: %d\n", ret);
        return 0;
    }

	param2.sched_priority = (int)prio_min; printf("prior2 = %d\n", param2.sched_priority);
	ret = pthread_setschedparam(t[1], SCHED_FIFO, &param2);
	if (ret != 0) {
        printf("Erro pthread_setschedparam! Thread2\nERRO: %d\n", ret);
        return 0;
    }

	// Definição das afinidades
	pthread_setaffinity_np(t[0], sizeof(s), &s);
	pthread_setaffinity_np(t[1], sizeof(s), &s);

	pthread_join(t[1], NULL);
	pthread_join(t[0], NULL);

	clock_gettime(CLOCK_MONOTONIC, &tempo_atual1);
	printf("MAIN: Clock MONOTONIC Atual %ld segundos e %ld nanosegundos!\n", tempo_atual1.tv_sec, tempo_atual1.tv_nsec);
	printf("MAIN: Tempo do processo (somente segundos, ignora nanosegundos) %ld!\n", (tempo_atual1.tv_sec-tempo_atual.tv_sec));

	return 0;
}
