#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Variáveis globais utilizadas pelas threads.
int counter;

void *threadFunction(void *thread_id) {
	long id = (long)thread_id;

    /* Incremento da variável global. */
    counter++;

	printf("Thread[%ld]:\n", id);
    printf("Counter: %d\n", counter);
}

void main() {
	int T;
	printf("Insira o número de threads: ");
	scanf("%d", &T);

	pthread_t thread[T]; 												// Vetor com 'T' threads para o cálculo dos núm. primos.
    long i; 															// ID da thread.

    counter = 0;

	for (i = 0; i < T; i++) {											// Criação das threads:
		printf("Criando thread %d\n", i);

		pthread_create(&thread[i], NULL, threadFunction, (void *)i);

		printf("\n");
	}

	// Espera por todas as threads encerrarem.
	for (i = 0; i < T; i++) {
		pthread_join(thread[i], NULL);
	}

	pthread_exit(NULL);
}
