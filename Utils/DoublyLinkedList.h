/* Doubly Linked List header file */
#ifndef DLL_H_
#define DLL_H_

#include <stdio.h>
#include <stdlib.h>

/* Functions */
//Creates a new Node and returns pointer to it.
struct Node* GetNewNode(int x);

//Inserts a Node at head of doubly linked list
void InsertAtHead(int x);

//Inserts a Node at tail of Doubly linked list
void InsertAtTail(int x);

//Prints all the elements in linked list in forward traversal order
void Print();

//Prints all elements in linked list in reverse traversal order.
void ReversePrint();

/* Variables */
struct Node {
	int data;
	struct Node* next;
	struct Node* prev;
};

struct Node* head; // global variable - pointer to head node.

#endif
