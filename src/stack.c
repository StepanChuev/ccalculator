#include <stdlib.h>
#include "stack.h"

Stack *createStack(void){
	Stack *head = (Stack *)malloc(sizeof(Stack));

	head->value = NULL;
	head->next = NULL;

	return head;
}

Stack *pushToStack(Stack *head){
	Stack *newHead = createStack();
	newHead->next = head;

	return newHead;
}

Stack *popFromStack(Stack *head){
	Stack *newHead = head->next;

	free(head->value);
	free(head);

	return newHead;
}

void freeStack(Stack *head){
	while (head != NULL){
		head = popFromStack(head);
	}
}