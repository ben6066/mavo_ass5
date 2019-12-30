#define _CRT_SECURE_NO_WARNINGS
#include <assert.h> 
#include "stack.h"
#include <cassert>

void expandStack(Stack* stack);

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

// check with Dan if expandedStack pointer needs to be freed
void expandStack(Stack* stack)
{
	if (stack == NULL ||stack->content == NULL)
	{
		return;
	}

	stack->size *= 2;

	Element* expandedStack = (Element*)malloc((stack->size) * sizeof(Element));

	//Case malloc failed
	if (expandedStack == NULL)
	{
		printf("Error! Malloc has failed in file 'stack.c', 'expandStack' function\n");
		return;
	}

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
	int lenOfStack = 0;

	for (int i = 0; i <= stack->topIndex; i++)
	{
		lenOfStack++;
	}

	return lenOfStack;
}

Element top(Stack* stack) 
{
	assert (isStackEmpty(stack) == 0);
	
	return stack->content[stack->topIndex];
}

capacityOfStack(Stack* stack)
{
	return stack->size;
}

void main()
{
	Stack* stack = initStack();

	Element e1;
	e1.c = 'a';

	Element e2;
	e2.c = 'b';

	Element e3;
	e3.c = 'c';

	Element e4;
	e4.c = 'd';

	Element e5;
	e5.c = 'e';

	Element e6;
	e6.c = 'f';

	push(stack, e1);

	push(stack, e2);

	push(stack, e3);

	push(stack, e4);

	push(stack, e5);

	push(stack, e6);

	printf("Length: %d\n", lenOfStack(stack));

	if (isStackEmpty(stack) == 0)
	{
		printf("Stack isn't empty\n");
	}

	else
	{
		printf("Stack is empty\n");
	}

	printf("Capacity: %d\n", capacityOfStack(stack));

	printStack(stack);

	printf("Top of stack: %c\n", top(stack).c);

	destroyStack(stack);

	printf("%d\n", stack->size);
}