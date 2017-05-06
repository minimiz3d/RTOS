#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
    int sig;
    sigset_t s;
    sigemptyset(&s);
    sigaddset(&s, SIGKILL);
    // sigaddset(&s, SIGINT);
    sigaddset(&s, SIGTSTP);
    sigprocmask(SIG_BLOCK, &s, NULL);

    for(;;) {
        sigwait(&s, &sig);
        printf("Recebeu o sinal: %d\n", sig);
    }

    return 0;
}
