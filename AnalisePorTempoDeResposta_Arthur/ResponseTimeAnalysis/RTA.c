/* Response time analysis */
#include "RTA.h"

/* Generating random numbers */
int randomNumber(int max) {
    int r = (rand() % max) + 1;
    return r;
}

/* Interference from another task */
float interfCalc(float computation_time, int last_response, float period) {
    float interf = ceil(last_response/period) * computation_time;
    return interf;
}

/* Function to print task info */
void printTask(Task data) {
    printf("Tarefa %d:\n", data.id);
    printf("* Computação: %.2f\n", data.c);
    printf("* Período: %.2f\n", data.p);
    printf("* Deadline: %.2f\n", data.d);
}

/* Returns time used by the current task */
float rateMonotonicSummation(float computation_time, float period) {
    return computation_time/period;
}

/* Check the system's scalability */
bool rateMonotonicTest(float sum, float threshold) {
    if (sum < threshold) return true; else return false;
}
