/* Response time analysis header */
#ifndef RTA_H_
#define RTA_H_

#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>   // Ceil function

/* Variables */
typedef struct task {
    int id; // Identification
    int c;  // Computation
    int p;  // Period
    int d;  // Deadline
} Task;

/*  Functions */
int randomNumber(int max);
float interfCalc(int computation_time, int last_response, int period);

#endif
