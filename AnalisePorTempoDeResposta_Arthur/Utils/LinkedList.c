#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

/* Function to insert a node at the begining of a linked list */
void insertAtTheBegin(struct node **start_ref, Task data) {
    struct node *currentPtr = (struct node*)malloc(sizeof(struct node));
    currentPtr->data = data;
    currentPtr->next = *start_ref;
    *start_ref = currentPtr;
}

/* Function to print nodes in a given linked list */
void printList(struct node *start) {
    struct node *temp = start;
    printf("\n");

    while (temp != NULL) {
        printTask(temp->data);
        temp = temp->next;
    }
}

/* Bubble sort the given linked lsit */
void bubbleSort(struct node *start) {
    int swapped, i;
    struct node *currentPtr;
    struct node *lastPtr = NULL;

    /* Checking for empty list */
    if (currentPtr == start)
        return;

    /* Iterates over the linked list to sort it */
    do {
        swapped = 0;
        currentPtr = start;

        /* Swap based on period */
        while (currentPtr->next != lastPtr) {
            if ((currentPtr->data.p) > (currentPtr->next->data.p)) {
                swap(currentPtr, currentPtr->next);
                swapped = 1;
            }
            currentPtr = currentPtr->next;
        }
        lastPtr = currentPtr;
    }
    while (swapped);
}

/* Function to swap data of two nodes a and b */
void swap(struct node *a, struct node *b) {
    Task temp;

    temp = a->data;
    a->data = b->data;
    b->data = temp;
}
