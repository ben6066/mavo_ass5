#define _CRT_SECURE_NO_WARNINGS
#include <assert.h> 
#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

void expandStack(Stack* stack);
void reduceStack(Stack* stack);

Stack* initStack()
{
	Stack* stack = (Stack*)malloc(sizeof(Stack));

	if (stack == NULL)
	{
		printf("Error! Malloc has failed in file 'stack.c', 'initStack' function\n");
		return NULL;
	}

	stack->size = 1;

	stack->topIndex = -1;

	stack->content = (Element*)malloc(sizeof(Element));

	//Case malloc failed
	if (stack->content == NULL)
	{
		printf("Error! Malloc has failed in file 'stack.c', 'initStack' function\n");
		return NULL;
	}

	return stack;
}

void expandStack(Stack* stack)
{
	if (stack == NULL ||stack->content == NULL)
	{
		return;
	}

	Element* expandedStack = (Element*)malloc(2 * (stack->size) * sizeof(Element));

	//Case malloc failed
	if (expandedStack == NULL)
	{
		printf("Error! Malloc has failed in file 'stack.c', 'expandStack' function\n");
		return;
	}

	stack->size *= 2;

	//Copy values
	for (int i = 0; i <= stack->topIndex; i++)
	{
		expandedStack[i].c = stack->content[i].c;
	}

	//Free old array
	free(stack->content);

	//Point to the new array in the heap
	stack->content = expandedStack;
}

void reduceStack(Stack* stack)
{
	if (stack == NULL || stack->content == NULL)
	{
		return;
	}

	Element* reducedStack = (Element*)malloc(((stack->size) / 2) * sizeof(Element));

	//Case malloc failed
	if (reducedStack == NULL)
	{
		printf("Error! Malloc has failed in file 'stack.c', 'reduceStack' function\n");
		return;
	}

	stack->size /= 2;

	//Copy values
	for (int i = 0; i <= stack->topIndex; i++)
	{
		reducedStack[i].c = stack->content[i].c;
	}

	//Free old array
	free(stack->content);

	//Point to the new array in the heap
	stack->content = reducedStack;
}

void push(Stack* stack, Element element)
{
	//forward array's index
	stack->topIndex++;

	//Push element character in the array
	stack->content[stack->topIndex].c = element.c;

	//In order to make sure there is an available spot
	if (stack->topIndex == stack->size - 1)
	{
		expandStack(stack);
	}
}

void destroyStack(Stack* stack)
{
	if (stack != NULL)
	{
		if (stack->content != NULL)
		{
			free(stack->content);
		}

		free(stack);
	}
}

void printStack(Stack* stack)
{
	if (stack->content != NULL)
	{
		for (int i = stack->topIndex; i >= 0; i--)
		{
			printf("%d: %c\n", i + 1, stack->content[i].c);
		}
	}
}

int isStackEmpty(Stack* stack)
{
	if (stack->topIndex == -1)
	{
		return 1;
	}

	return 0;
}

int lenOfStack(Stack* stack)
{
	return stack->topIndex + 1;
}

Element top(Stack* stack) 
{
	assert (isStackEmpty(stack) == 0);
	
	return stack->content[stack->topIndex];
}

int capacityOfStack(Stack* stack)
{
	return stack->size;
}

Element pop(Stack* stack)
{
	assert(isStackEmpty(stack) == 0);

	Element topElement = top(stack);

	stack->topIndex--;

	if (stack->topIndex == (stack->size / 2) - 2)
	{
		reduceStack(stack);
	}

	return topElement;
}

