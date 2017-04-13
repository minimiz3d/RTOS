#include <pthread.h>
#include <time.h>

#define N_SEGUNDOS 5

void *thread_teste(void *arg) {
	int tid;
	long l;
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
	// 2 threads
	pthread_t t[2];

	// estrutura para obter/setar o tempo de um relógio
	struct timespec tempo_atual, tempo_atual1;

	// obtém o tempo atual do relógio que conta o tempo passado a partir de uma época específica (CLOCK_MONOTONIC)
	// no Linux essa época é o tempo de início do sistema
	// esse relógio não pode ser modificado, garantindo que ele é sempre crescente (monotônico)
	clock_gettime(CLOCK_MONOTONIC, &tempo_atual);
	printf("MAIN: Clock MONOTONIC Atual %ld segundos e %ld nanosegundos!\n", tempo_atual.tv_sec, tempo_atual.tv_nsec);

	pthread_create(&t[0], NULL, thread_teste, (void *)0);
	pthread_create(&t[1], NULL, thread_teste, (void *)1);

	pthread_join(t[0], NULL);
	pthread_join(t[1], NULL);

	clock_gettime(CLOCK_MONOTONIC, &tempo_atual1);
	printf("MAIN: Clock MONOTONIC Atual %ld segundos e %ld nanosegundos!\n", tempo_atual1.tv_sec, tempo_atual1.tv_nsec);
	printf("MAIN: Tempo do processo (somente segundos, ignora nanosegundos) %ld!\n", (tempo_atual1.tv_sec-tempo_atual.tv_sec));

	return 0;
}
