#define _CRT_SECURE_NO_WARNINGS
#include "stack.h"

void expandStack(Stack* stack);

Stack* initStack()
{
	Stack stack;

	stack.size = 1;

	stack.topIndex = -1;

	stack.content = (Element*)malloc(sizeof(Element));

	//Case malloc failed
	if (stack.content == NULL)
	{
		printf("Error! Malloc has failed in file 'stack.c', 'initStack' function\n");
	}

	Stack* pS = &stack;

	return pS;
}

// check with Dan if expandedStack pointer needs to be freed
void expandStack(Stack* stack)
{
	if (stack->content == NULL)
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
	if (stack->content != NULL)
	{
		free(stack->content);
	}
}

void printStack(Stack* stack)
{
	if (stack->content != NULL)
	{
		for (int i = stack->topIndex; i >= 0; i--)
		{
			printf("%d: %c", stack->topIndex + 1, stack->content[i].c);
		}
	}
}

void main()
{
	Stack* pS = initStack();

	printf("%d\n", pS->topIndex);

	printf("%d\n", pS->size);

	Element e1;
	e1.c = 'a';

	Element e2;
	e2.c = 'b';

	Element e3;
	e3.c = 'c';

	push(pS, e1);

	push(pS, e2);

	push(pS, e3);

	printStack(pS);
}