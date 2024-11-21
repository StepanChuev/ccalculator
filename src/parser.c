#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lexer.h"
#include "executor.h"
#include "stack.h"
#include "binaryTree.h"
#include "parser.h"

static Token *lastParen = NULL;

BinaryTreeNode *buildASTFromTokens(Token *tokens){
	BinaryTreeNode *currentNode = createBinaryTreeNode();
	BinaryTreeNode *root = currentNode;
	BinaryTreeNode *parenAST = NULL;
	Stack *stack = NULL;

	for (Token *currentToken = tokens; strcmp(currentToken->name, END_TOKEN); currentToken++){
		if (strchr(CLOSEPAREN_OPERATOR, currentToken->value[0])){
			lastParen = currentToken;
			break;
		}

		if (strchr(OPENPAREN_OPERATOR, currentToken->value[0])){
			parenAST = buildASTFromTokens(currentToken + 1);

			stack = pushToStack(stack);
			stack->value = malloc(MAX_LEN_TOKEN_VALUE * sizeof(char));
			sprintf((char *)stack->value, "%0.15lf", execute(parenAST));
			freeBinaryTree(parenAST);
			currentToken = lastParen;

			continue;
		}

		if (!strcmp(currentToken->name, NUMBER_TOKEN) || !strcmp(currentToken->name, CONSTANT_TOKEN)){
			stack = pushToStack(stack);
			stack->value = malloc(MAX_LEN_TOKEN_VALUE * sizeof(char));
			strcpy((char *)stack->value, currentToken->value);
		}

		else if (!strcmp(currentToken->name, OPERATOR_TOKEN)){
			stack = pushToStack(stack);
			stack->value = malloc(MAX_LEN_TOKEN_VALUE * sizeof(char));
			strcpy((char *)stack->value, currentToken->value);

			if (getOperatorPriority((char *)stack->value) < getOperatorPriority((char *)(currentToken + 2)->value)){
				currentNode = moveElementsToAST(&currentNode, &stack);

				freeStack(stack);
			}
		}
	}

	currentNode = moveElementsToAST(&currentNode, &stack);

	freeStack(stack);

	return root;
}

BinaryTreeNode *moveElementsToAST(BinaryTreeNode **current, Stack **stack){
	BinaryTreeNode **retNode = &(*current)->right;

	if (*stack == NULL){
		return *current;
	}

	if (!strcmp(getTokenName((*stack)->value, 0), OPERATOR_TOKEN) && (*stack)->next != NULL){
		(*current)->value = malloc(MAX_LEN_TOKEN_VALUE * sizeof(char));
		strcpy((char *)(*current)->value, (*stack)->value);
		*stack = popFromStack(*stack);

		(*current)->left = createBinaryTreeNode();
		(*current)->right = createBinaryTreeNode();
		*current = (*current)->left;
	}

	if ((*stack)->next == NULL){
		(*current)->value = malloc(MAX_LEN_TOKEN_VALUE * sizeof(char));
		strcpy((char *)(*current)->value, (*stack)->value);
		*stack = popFromStack(*stack);

		(*current)->left = createBinaryTreeNode();
		(*current)->right = createBinaryTreeNode();

		return *retNode;
	}

	while (*stack != NULL){
		(*current)->value = malloc(MAX_LEN_TOKEN_VALUE * sizeof(char));
		strcpy((char *)(*current)->value, (*stack)->next->value);

		(*current)->left = createBinaryTreeNode();
		(*current)->right = createBinaryTreeNode();

		(*current)->right->value = malloc(MAX_LEN_TOKEN_VALUE * sizeof(char));
		strcpy((char *)(*current)->right->value, (*stack)->value);
		*stack = popFromStack(*stack);

		if ((*stack)->next->next == NULL){
			(*current)->left->value = malloc(MAX_LEN_TOKEN_VALUE * sizeof(char));
			strcpy((char *)(*current)->left->value, (*stack)->next->value);
			*stack = popFromStack(*stack);
		}

		*stack = popFromStack(*stack);
		*current = (*current)->left;
	}

	return *retNode;
}