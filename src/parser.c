#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lexer.h"
#include "executor.h"
#include "stack.h"
#include "binaryTree.h"
#include "names.h"
#include "parser.h"

static Token *lastToken = NULL;

BinaryTreeNode *buildASTFromTokens(Token *tokens){
	BinaryTreeNode *currentNode = createBinaryTreeNode();
	BinaryTreeNode *root = currentNode;
	BinaryTreeNode *parenAST = NULL;
	BinaryTreeNode **argsAST = NULL;
	Stack *stack = NULL;
	double *args = NULL;

	for (Token *currentToken = tokens; currentToken->code != END_TOKEN; currentToken++){
		if (CLOSEPAREN_OPERATOR[0] == currentToken->value[0] || COMMA_OPERATOR[0] == currentToken->value[0]){
			lastToken = currentToken;
			break;
		}

		if (OPENPAREN_OPERATOR[0] == currentToken->value[0]){
			parenAST = buildASTFromTokens(currentToken + 1);

			stack = pushToStack(stack);
			stack->value = malloc(MAX_LEN_TOKEN_VALUE * sizeof(char));
			sprintf((char *)stack->value, "%0.15lf", executeAST(parenAST));
			freeBinaryTree(parenAST);
			currentToken = lastToken;

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
				argsAST = buildASTsFromArgs(currentToken + 2);
				args = executeASTs(argsAST, MAX_LEN_ARGS);
				sprintf((char *)stack->value, "%0.15lf", getNameValue(currentToken->value, args));
				currentToken = lastToken;
				free(args);
				freeBinaryTrees(argsAST);
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

BinaryTreeNode **buildASTsFromArgs(Token *token){
	size_t i = 0;
	BinaryTreeNode **argsAST = (BinaryTreeNode **)malloc((MAX_LEN_ARGS + 1) * sizeof(BinaryTreeNode *));

	while (i < MAX_LEN_ARGS){
		argsAST[i] = buildASTFromTokens(token);
		token = lastToken + 1;
		i++;

		if (lastToken->value[0] == CLOSEPAREN_OPERATOR[0]){
			break;
		}
	}

	argsAST[i] = NULL;

	return argsAST;
}

BinaryTreeNode *moveElementsToAST(BinaryTreeNode **current, Stack **stack){
	BinaryTreeNode **retNode = &(*current)->right;

	if (*stack == NULL){
		return *current;
	}

	if (isOperatorToken((*stack)->value, 0, END_TOKEN) && (*stack)->next != NULL){
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