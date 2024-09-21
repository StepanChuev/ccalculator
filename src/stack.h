#ifndef STACK_H

#define STACK_H

typedef struct Stack {
	void *value;
	struct Stack *next;
} Stack;

Stack *createStack(void);
Stack *pushToStack(Stack *head);
Stack *popFromStack(Stack *head);
void freeStack(Stack *head);

#endif