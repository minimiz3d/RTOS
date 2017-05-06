#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct {
    int position;
    int count;
    sem_t *forks;
    sem_t *lock;
} params_t;

void initialize_semaphores(sem_t *lock, sem_t *forks, int num_forks);
void run_all_threads(pthread_t *threads, sem_t *forks, sem_t *lock, int NUM_PHILOSOPHERS);

void *philosopher(void *params);
void think(int position);
void eat(int position);

int main(int argc, char *args[]) {
    int NUM_PHILOSOPHERS = 5;

    sem_t lock;
    sem_t forks[NUM_PHILOSOPHERS];
    pthread_t philosophers[NUM_PHILOSOPHERS];

    initialize_semaphores(&lock, forks, NUM_PHILOSOPHERS);
    run_all_threads(philosophers, forks, &lock, NUM_PHILOSOPHERS);
    pthread_exit(NULL);
}

void initialize_semaphores(sem_t *lock, sem_t *forks, int num_forks) {
    int i;
    for(i = 0; i < num_forks; i++)
        sem_init(&forks[i], 0, 1);

    sem_init(lock, 0, num_forks - 1);
}
void run_all_threads(pthread_t *threads, sem_t *forks, sem_t *lock, int NUM_PHILOSOPHERS) {
    int i;
    for(i = 0; i < NUM_PHILOSOPHERS; i++) {
        params_t *arg = malloc(sizeof(params_t));
        arg->position = i;
        arg->count = NUM_PHILOSOPHERS;
        arg->lock = lock;
        arg->forks = forks;

        pthread_create(&threads[i], NULL, philosopher, (void *)arg);
    }
}

void *philosopher(void *params) {
    int i;
    params_t self = *(params_t *)params;

    for(i = 0; i < 3; i++) {
        think(self.position);

        sem_wait(self.lock);
        sem_wait(&self.forks[self.position]);
        sem_wait(&self.forks[(self.position + 1) % self.count]);
        eat(self.position);
        sem_post(&self.forks[self.position]);
        sem_post(&self.forks[(self.position + 1) % self.count]);
        sem_post(self.lock);
    }

    think(self.position);
    pthread_exit(NULL);
}
void think(int position) {
  printf("Philosopher %d thinking...\n", position);
}
void eat(int position) {
  printf("Philosopher %d eating...\n", position);
}

// AULA FILOSOFOS VAR COND:
pthread_mutex_t m[5] = PTHREAD_MUTEX_INITIALIZER;
int g[5] = {0,0,0,0,0};
pthread_cond_t c[5] = PTHREAD_COND_INITIALIZER;

int id = 0;
int d = (id == 0)? 4 : id = 1;
int e = id;

e = tid;
d = tid == 0 ? 4 : tid - 1;

while (1) {
    // espera

    // pega garfo (D)
    pthread_mutex_lock(&m[d]);
        while (g[d] == 1)
            pthread_cond_wait(&c[d], &m[d]);
        g[d] = 1;
    pthread_mutex_unlock(&m[d]);
    // pega garfo (E)
    pthread_mutex_lock(&m[e]);
        while (g[e] == 1)
            pthread_cond_wait(&c[e], &m[e]);
        g[e] = 1;
    pthread_mutex_unlock(&m[e]);

    // come
    sleep(10);

    // liberar garfo D
    pthread_mutex_lock(&m[d]);
        g[d] = 0;
        pthread_cond_signal(&c[d]);
    pthread_mutex_unlock(&m[d]);
    // liberar garfo D
    pthread_mutex_lock(&m[e]);
        g[e] = 0;
        pthread_cond_signal(&c[e]);
    pthread_mutex_unlock(&m[e]);
}
