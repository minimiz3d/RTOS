#include "../Utils/LinkedList.h"
#include "RTA.h"

#define NUMBER_OF_TASKS 3

void rateMonotonicAnalysis(struct node *start) {
    double monotonicThreshold = NUMBER_OF_TASKS * (pow(2, (1/(double)NUMBER_OF_TASKS)) - 1);
    struct node *temp = start;
    float sum = 0;

    /* Iterates over the linked list */
    while (temp != NULL) {
        sum += rateMonotonicSummation(temp->data.c, temp->data.p);

        temp = temp->next;
    }

    printf("\n\tRate Monotonic Analysis\n");
    printf("\t- Soma: %.3f\n", sum);
    printf("\t- Monotonic Threshold: %.3lf\n", monotonicThreshold);

    bool testResult = rateMonotonicTest(sum, monotonicThreshold);
    if (testResult)
        printf("\tO sistema é escalonável.\n");
    else
        printf("\tO sistema não é escalonável.\n");
}

void responseTimeAnalysis(struct node *start) {
    /*  Ri = Ci + Sum([Rj/Pj] * Cj)
        - Ri = Current Response
        - Ci = Current Computation Time
        - Rj = Last Response
        - Pj = Higher Priority Task's Period
        - Cj = Higher Priority Task's Computation Time
    */
    struct node *currentTask = start;
    int i = 1;
    float currentResponse = 0, lastResponse = 0;
    bool convergence = true;

    /* Sorts the linked list based on period (higher priority <=> shorter period) */
    bubbleSort(start);

    /* Print list after sorting */
    printf("\n-> Linked list after sorting (Rate Monotonic):");
    printList(start);

    printf("\n\tResponse Time Analysis\n");
    printf("*** ResponseTime[iteration, task_priority] ***\n");
    /* Iterates over the linked list (main loop) */
    while (currentTask != NULL) {
        lastResponse = 0;
        currentResponse = currentTask->data.c;

        /* Iterates until convergence/!convergence */
        for (size_t x = 0; ; x++) {
            /* Higher priority task doesn't suffer interference */
            if (i == 1) {
                printf("Current Response (R[%d,%d] = %.2f)\n", x,i,currentResponse);
                break;
            }

            /* CurrentResponse calculation */
            if (x > 0) {
                int count = 1;
                struct node *temp = start;
                int interfSum = 0;

                /* Iterates over the list to check interference caused by higher priority tasks */
                while ((temp != NULL) && (count < i)) {
                    int cj = temp->data.c;
                    int pj = temp->data.p;

                    interfSum += interfCalc(cj, lastResponse, pj);
                    currentResponse = currentTask->data.c + interfSum;

                    temp = temp->next;
                    count++;
                }
            }
            printf("Current Response (R[%d,%d] = %.2f)\n", x,i,currentResponse);

            /* Convergence */
            if (currentResponse == lastResponse)
                break;

            /* !Convergence */
            if (currentResponse > currentTask->data.d) {
                printf("\n~DEBUG:\tCurrent Response = %.2f > Current Deadline = %.2f\n", currentResponse, currentTask->data.d);
                convergence = false;
                break;
            }

            lastResponse = currentResponse;
        }

        if (convergence == false) {
            printf("\tO sistema não é escalonável.\n");
            break;
        }

        /* Analysis over the next task */
        currentTask = currentTask->next;
        i++;
    }

    if (convergence == true) printf("\tO sistema é escalonável.\n");
}

int main(int argc, char const *argv[]) {
    Task taskVector[NUMBER_OF_TASKS];

    srand(time(NULL));

    /* Creating tasks */
    printf("-> List of tasks:\n");
    for (size_t i = 0; i < NUMBER_OF_TASKS; i++) {
        taskVector[i].id = i;
        taskVector[i].p = randomNumber(60) + randomNumber(20) + 20;
        taskVector[i].d = taskVector[i].p;
        taskVector[i].c = randomNumber(taskVector[i].p/2);

        printTask(taskVector[i]);
    }

    /* Start with empty linked list */
    struct node *start = NULL;

    /* Create linked list with tasks */
    for (size_t i = 0; i< NUMBER_OF_TASKS; i++)
        insertAtTheBegin(&start, taskVector[i]);

    /* Rate Monotonic Analysis */
    rateMonotonicAnalysis(start);

    /* Response Time Analysis */
    responseTimeAnalysis(start);

    return 0;
}
