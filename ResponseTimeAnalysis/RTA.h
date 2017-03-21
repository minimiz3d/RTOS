/* Response time analysis header */
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>   // Ceil function

typedef struct task {
    int c;  // Computation
    int p;  // Period
    int d;  // Deadline
} Task;

// Functions
int randomNumber(int max);
float interfCalc(int computation_time, int last_response, int period);
