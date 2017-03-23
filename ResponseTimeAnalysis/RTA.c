/* Response time analysis */
#include "RTA.h"

/* Generating random numbers */
int randomNumber(int max) {
    int r = (rand() % max) + 1;
    return r;
}

/* Interference from another task */
float interfCalc(int computation_time, int last_response, int period) {
    float interf = ceil(last_response/period) * computation_time;
    return interf;
}
