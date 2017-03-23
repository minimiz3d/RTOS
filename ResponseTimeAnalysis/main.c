#include "../Utils/LinkedList.h"
#include "RTA.h"

#define NUMBER_OF_TASKS 3

int main(int argc, char const *argv[]) {
    Task taskVector[NUMBER_OF_TASKS];
    int i;

    srand(time(NULL));

    /* Creating tasks */
    printf("-> List of tasks:\n");
    for (size_t i = 0; i < NUMBER_OF_TASKS; i++) {
        taskVector[i].id = i;
        taskVector[i].c = randomNumber(10);
        taskVector[i].p = randomNumber(100);
        taskVector[i].d = taskVector[i].p;

        printTask(taskVector[i]);
    }

    /* Start with empty linked list */
    struct node *start = NULL;

    /* Create linked list with tasks */
    for (i = 0; i< NUMBER_OF_TASKS; i++)
        insertAtTheBegin(&start, taskVector[i]);

    /* Print list before sorting */
    printf("\n-> Linked list before sorting:");
    printList(start);

    /* Sort the linked list */
    bubbleSort(start);

    /* Print list after sorting */
    printf("\n-> Linked list after sorting (by 'Period'):");
    printList(start);

    return 0;
}
