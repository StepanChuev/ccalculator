#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lexer.h"
#include "executor.h"
#include "stack.h"
#include "binaryTree.h"
#include "parser.h"

BinaryTreeNode *buildASTFromTokens(Token *tokens){
	int prior = -1, countParen = 0;
	BinaryTreeNode *current = createBinaryTreeNode();
	BinaryTreeNode *root = current;
	BinaryTreeNode *parenAST = NULL;
	Stack *stack = NULL;

	for (size_t i = 0; strcmp(tokens[i].name, END_TOKEN); i++){
		if (strchr(CLOSEPAREN_OPERATOR, tokens[i].value[0]) && countParen <= 0){
			break;
		}

		if (countParen > 0){
			countParen += !!strchr(OPENPAREN_OPERATOR, tokens[i].value[0]);
			countParen -= !!strchr(CLOSEPAREN_OPERATOR, tokens[i].value[0]);

			continue;
		}

		if (strchr(OPENPAREN_OPERATOR, tokens[i].value[0])){
			parenAST = buildASTFromTokens(tokens + i + 1);

			stack = pushToStack(stack);
			stack->value = malloc(MAX_LEN_TOKEN_VALUE * sizeof(char));
			sprintf((char *)stack->value, "%0.15f", execute(parenAST));
			freeBinaryTree(parenAST);
			countParen++;

			continue;
		}

		if (!strcmp(tokens[i].name, NUMBER_TOKEN) || !strcmp(tokens[i].name, CONSTANT_TOKEN)){
			stack = pushToStack(stack);
			stack->value = malloc(MAX_LEN_TOKEN_VALUE * sizeof(char));
			strcpy((char *)stack->value, tokens[i].value);
		}

		else if (!strcmp(tokens[i].name, OPERATOR_TOKEN)){ // strchr(ALL_OPERATORS, tokens[i].value[0])
			stack = pushToStack(stack);
			stack->value = malloc(MAX_LEN_TOKEN_VALUE * sizeof(char));
			strcpy((char *)stack->value, tokens[i].value);

			if (
				(prior = getOperatorPriority((char *)stack->value)) < getOperatorPriority((char *)tokens[i + 2].value) || 
				prior < getOperatorPriority((char *)tokens[i + 1].value)
			){
				current = moveElementsToAST(&current, &stack);

				freeStack(stack);
			}
		}
	}

	current = moveElementsToAST(&current, &stack);

	freeStack(stack);

	return root;
}

BinaryTreeNode *moveElementsToAST(BinaryTreeNode **current, Stack **stack){
	BinaryTreeNode **retNode = &(*current)->right;

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