#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

/* Function to insert a node at the begining of a linked lsit */
void insertAtTheBegin(struct node **start_ref, Task data) {
    struct node *ptr1 = (struct node*)malloc(sizeof(struct node));
    ptr1->data = data;
    ptr1->next = *start_ref;
    *start_ref = ptr1;
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

/* Function to print task info */
void printTask(Task data) {
    printf("Tarefa %d:\n", data.id);
    printf("* Computação: %d\n", data.c);
    printf("* Período: %d\n", data.p);
    printf("* Deadlock: %d\n", data.d);
}

/* Bubble sort the given linked lsit */
void bubbleSort(struct node *start) {
    int swapped, i;
    struct node *ptr1;
    struct node *lptr = NULL;

    /* Checking for empty list */
    if (ptr1 == NULL)
        return;

    do {
        swapped = 0;
        ptr1 = start;

        while (ptr1->next != lptr) {
            if (ptr1->data.p > ptr1->next->data.p) {
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}

/* Function to swap data of two nodes a and b*/
void swap(struct node *a, struct node *b) {
    int temp = a->data.p;
    a->data.p = b->data.p;
    b->data.p = temp;
}
