#define _CRT_SECURE_NO_WARNINGS
#include <assert.h> 
#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

void oppositeStack(Stack* s1, Stack* s2);

Queue* initQueue()
{
	Queue* queue = (Queue*)malloc(sizeof(Queue));

	//Case malloc failed
	if (queue == NULL)
	{
		printf("Error! Malloc has failed in file 'queue.c', 'initQueue' function\n");
		return NULL;
	}

	queue->s1 = initStack();
	queue->s2 = initStack();

	return queue;
}

void destroyQueue(Queue* queue)
{
	if (queue != NULL)
	{
		destroyStack(queue->s1);
		destroyStack(queue->s2);

		free(queue);
	}
}

int isQueueEmpty(Queue* queue)
{
	if (isStackEmpty(queue->s1) == 1)
	{
		return 1;
	}

	return 0;
}

int lenOfQueue(Queue* queue)
{
	return lenOfStack(queue->s1);
}

int capacityOfQueue(Queue* queue)
{
	return (capacityOfStack(queue->s1) + capacityOfStack(queue->s2));
}

void enqueue(Queue* queue, Element element)
{
	push(queue->s1, element);
}

//Fix
void oppositeStack(Stack* s1, Stack* s2)
{
	/*for (int i = s1->topIndex; i >= 0; i--)
	{
		push(s2, s1->content[i]);

		pop(s1);
	}*/

	if (isStackEmpty(s1) == 1)
	{
		return;
	}

	for (int i = lenOfStack(s1) - 1; i >= 0; i--)
	{
		push(s2, pop(s1));
	}
}

Element dequeue(Queue* queue)
{
	assert(isStackEmpty(queue->s1) == 0);

	oppositeStack(queue->s1, queue->s2);

	Element topInQueue = pop(queue->s2);

	oppositeStack(queue->s2, queue->s1);

	return topInQueue;
}

//Fix
Element peek(Queue* queue)
{
	assert(isStackEmpty(queue->s1) == 0);

	oppositeStack(queue->s1, queue->s2);

	Element peek = top(queue->s2);

	oppositeStack(queue->s2, queue->s1);

	return peek;
	
	//return queue->s1->content[0];
}

void main()
{
	Queue* queue = initQueue();

	Element e1;
	e1.c = 'a';
	Element e2;
	e2.c = 'b';
	Element e3;
	e3.c = 'c';

	enqueue(queue, e1);
	enqueue(queue, e2);
	enqueue(queue, e3);

	printf("Peek: %c\n", peek(queue).c);

	printStack(queue->s1);
	
	dequeue(queue);
	printf("\n");
	printStack(queue->s1);

	printf("Peek: %c\n", peek(queue).c);

	printf("Capacity Of Queue: %d", capacityOfQueue(queue));
}
