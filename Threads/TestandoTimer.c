#include <time.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

#define NUM_THREADS 2
struct periodic_info {
    int sig;
    sigset_t alarm_sig;
};

static int make_periodic(struct periodic_info *info, int param) {
    static int next_sig = 0;
    struct sigevent sigev;
    struct itimerspec itval;
    timer_t timer_id;

    if (next_sig == 0)
        next_sig = SIGRTMIN;
    /* Check that we have not run out of signals */
    if (next_sig > SIGRTMAX)
        return -1;
    info->sig = next_sig;
    next_sig++;

    sigemptyset(&(info->alarm_sig));
    sigaddset(&(info->alarm_sig), info->sig);

    // Criação do timer que vai gerar os sinais para alertar as threads
    sigev.sigev_notify = SIGEV_SIGNAL;
    sigev.sigev_signo = info->sig;
    sigev.sigev_value.sival_ptr = (void *) &timer_id;
    timer_create(CLOCK_MONOTONIC, &sigev, &timer_id);

    // Tornar o timer periódico
    int delay = param; // A thread executa a cada 'param' segundos
    int reload = 10;  // Recomeça o timer a cada 'reload' segundos

    itval.it_value.tv_sec = delay;
    itval.it_value.tv_nsec = 0;
    itval.it_interval.tv_sec = reload;
    itval.it_interval.tv_nsec = 0;

    int ret = timer_settime(timer_id, 0, &itval, NULL);

    return ret;
}
static void wait_period(struct periodic_info *info) {
    sigwait(&(info->alarm_sig), &(info->sig));
}

void *thread1() {
    struct periodic_info info;

    // Definição do timer usado para alertar as threads.
    // Cada thread executa por 1 segundo/período
    make_periodic(&info, 1);

    while (1) {
        printf("\n"); /* Indicando nova execução */
        printf("T%d executando.\n", 1);
        wait_period(&info); /* Aguarda alarme para próxima execução */
    }

    return NULL;
}
void *thread2() {
    struct periodic_info info;

    // Definição do timer usado para alertar as threads.
    // Cada thread executa por 1 segundo/período
    make_periodic(&info, 2);

    while (1) {
        printf("T%d executando.\n", 2);
        wait_period(&info); /* Aguarda alarme para próxima execução */
    }

    return NULL;
}

int main(int argc, char const *argv[]) {
    pthread_t threads[NUM_THREADS];
    sigset_t alarm_sig;

    // Definição do conjunto de sinais (alarm_sig)
    sigemptyset(&alarm_sig);
    for (size_t i = SIGRTMIN; i <= SIGRTMAX; i++)
        sigaddset(&alarm_sig, i);
    sigprocmask(SIG_BLOCK, &alarm_sig, NULL);

    // Thread creation
    pthread_create(&threads[0], NULL, thread1, NULL);
    pthread_create(&threads[1], NULL, thread2, NULL);

    for (size_t i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);

    return 0;
}
