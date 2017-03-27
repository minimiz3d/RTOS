/* Response time analysis header */
#ifndef RTA_H_
#define RTA_H_

#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>   // Ceil function

/* Variables */
typedef struct task {
    int id;     // Identification
    float c;    // Computation
    float p;    // Period
    float d;    // Deadline
} Task;

/*  Functions */
int randomNumber(int max);
void printTask(Task data);
bool rateMonotonicTest(float sum, float threshold);
float interfCalc(float computation_time, int last_response, float period);
float rateMonotonicSummation(float computation_time, float period);

#endif
