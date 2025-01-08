#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lexer.h"
#include "executor.h"
#include "stack.h"
#include "binaryTree.h"
#include "names.h"
#include "parser.h"

static Token *lastParen = NULL;

BinaryTreeNode *buildASTFromTokens(Token *tokens){
	BinaryTreeNode *currentNode = createBinaryTreeNode();
	BinaryTreeNode *root = currentNode;
	BinaryTreeNode *parenAST = NULL;
	BinaryTreeNode *argAST = NULL;
	Stack *stack = NULL;
	double args[MAX_LEN_ARGS];

	for (Token *currentToken = tokens; currentToken->code != END_TOKEN; currentToken++){
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

		if (currentToken->code == NUMBER_TOKEN){
			stack = pushToStack(stack);
			stack->value = malloc(MAX_LEN_TOKEN_VALUE * sizeof(char));
			strcpy((char *)stack->value, currentToken->value);
		}

		else if (currentToken->code == NAME_TOKEN){
			stack = pushToStack(stack);
			stack->value = malloc(MAX_LEN_TOKEN_VALUE * sizeof(char));

			if ((currentToken + 1)->value[0] == OPENPAREN_OPERATOR[0]){
				argAST = buildASTFromTokens(currentToken + 2);
				args[0] = execute(argAST);
				sprintf((char *)stack->value, "%0.15lf", getNameValue(currentToken->value, args));
				currentToken = lastParen;
				freeBinaryTree(argAST);
			}

			else {
				sprintf((char *)stack->value, "%0.15lf", getNameValue(currentToken->value, NULL));
			}
		}

		else if (currentToken->code == OPERATOR_TOKEN){
			stack = pushToStack(stack);
			stack->value = malloc(MAX_LEN_TOKEN_VALUE * sizeof(char));
			strcpy((char *)stack->value, currentToken->value);

			if (getOperatorPriority((char *)stack->value) < getOperatorPriority((char *)(currentToken + 2)->value)){
				currentNode = moveElementsToAST(&currentNode, &stack);
			}
		}
	}

	currentNode = moveElementsToAST(&currentNode, &stack);

	return root;
}

BinaryTreeNode *moveElementsToAST(BinaryTreeNode **current, Stack **stack){
	BinaryTreeNode **retNode = &(*current)->right;

	if (*stack == NULL){
		return *current;
	}

	if (getTokenCode((*stack)->value, 0, END_TOKEN) == OPERATOR_TOKEN && (*stack)->next != NULL){
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