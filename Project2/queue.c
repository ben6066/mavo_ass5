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
	if ((isStackEmpty(queue->s1) == 1) && (isStackEmpty(queue->s2) == 1))
	{
		return 1;
	}

	return 0;
}

int lenOfQueue(Queue* queue)
{
	return lenOfStack(queue->s1) + lenOfStack(queue->s2);
}

int capacityOfQueue(Queue* queue)
{
	return (capacityOfStack(queue->s1) + capacityOfStack(queue->s2));
}

void enqueue(Queue* queue, Element element)
{
	push(queue->s1, element);
}

void oppositeStack(Stack* s1, Stack* s2)
{
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
	assert(isQueueEmpty(queue) == 0);

	if (isStackEmpty(queue->s2) == 1)
	{
		oppositeStack(queue->s1, queue->s2);
	}

	Element topInQueue = pop(queue->s2);

	return topInQueue;
}

Element peek(Queue* queue)
{
	assert(isQueueEmpty(queue) == 0);

	Element peek;

	if (isStackEmpty(queue->s2) == 1)
	{
		oppositeStack(queue->s1, queue->s2);
	}

	return top(queue->s2);
}

void printQueue(Queue* queue)
{
	if (isStackEmpty(queue->s1) == 1 && isStackEmpty(queue->s2) == 1)
	{
		return;
	}

	printf("Queue: ");

	if (isStackEmpty(queue->s1) != 1)
	{
		for (int i = lenOfStack(queue->s1) - 1; i >= 0; i--)
		{
			printf("%c ", queue->s1->content[i].c);
		}
	}

	if (isStackEmpty(queue->s2) != 1)
	{
		for (int i = 0; i <= queue->s2->topIndex; i++)
		{
			printf("%c ", queue->s2->content[i].c);
		}
	}
	
	printf("\n\n");
}

void main()
{
	Queue* queue = initQueue();

	printf("Capacity Of Empty Queue: %d\n\n", capacityOfQueue(queue));

	Element e1;
	e1.c = '1';
	Element e2;
	e2.c = '2';
	Element e3;
	e3.c = '3';

	enqueue(queue, e1);
	enqueue(queue, e2);
	enqueue(queue, e3);

	printQueue(queue);

	printf("Peek: %c\n", peek(queue).c);

	dequeue(queue);
	printf("Removed First Element\n");

	printQueue(queue);

	printf("Peek: %c\n\n", peek(queue).c);

	Element e4;
	e4.c = '4';

	enqueue(queue, e4);

	printQueue(queue);

	printf("Capacity Of Queue: %d\n", capacityOfQueue(queue));
}
