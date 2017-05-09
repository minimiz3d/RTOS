#include <time.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

#define NUM_THREADS 10
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
    int periodo_thread = (param + 1);   // 1s
    int periodo_total = 10;             // Repete a cada 10s

    itval.it_interval.tv_sec = periodo_total;
    itval.it_interval.tv_nsec = 0;
    itval.it_value.tv_sec = periodo_thread;
    itval.it_value.tv_nsec = 0;

    int ret = timer_settime(timer_id, 0, &itval, NULL);

    return ret;
}
static void wait_period(struct periodic_info *info) {
    sigwait(&(info->alarm_sig), &(info->sig));
}

void *thread_exercicio(void *param) {
    struct periodic_info info;

    // Definição do timer usado para alertar as threads.
    // Cada thread executa por 1 segundo/período
    make_periodic(&info, (int)param);

    while (1) {
        if ((int) param == 0)
            printf("\n"); /* Indicando nova execução */
        printf("T%d executando.\n", (int)param);
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
    for (size_t i = 0; i < NUM_THREADS; i++)
        pthread_create(&threads[i], NULL, thread_exercicio, (void *) i);

    for (size_t i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);

    return 0;
}
