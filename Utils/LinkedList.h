#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include "../ResponseTimeAnalysis/RTA.h"

/* Structure for a node */
struct node {
    Task data;
    struct node *next;
};

void insertAtTheBegin(struct node **start_ref, Task data);
void printList(struct node *start);
void printTask(Task data);
void bubbleSort(struct node *start);
void swap(struct node *a, struct node *b);

#endif
