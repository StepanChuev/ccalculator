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
	Stack *operands = NULL;
	Stack *operators = NULL; 

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

			operands = pushToStack(operands);
			operands->value = malloc(MAX_LEN_TOKEN_VALUE * sizeof(char));
			sprintf((char *)operands->value, "%0.15f", execute(parenAST));
			freeBinaryTree(parenAST);
			countParen++;

			continue;
		}

		if (!strcmp(tokens[i].name, NUMBER_TOKEN)){
			operands = pushToStack(operands);
			operands->value = malloc(MAX_LEN_TOKEN_VALUE * sizeof(char));
			strcpy((char *)operands->value, tokens[i].value);
		}

		else if (strchr(ALL_OPERATORS, tokens[i].value[0])){
			operators = pushToStack(operators);
			operators->value = malloc(MAX_LEN_TOKEN_VALUE * sizeof(char));
			strcpy((char *)operators->value, tokens[i].value);

			if (
				(prior = getOperatorPriority((char *)operators->value)) < getOperatorPriority((char *)tokens[i + 2].value) || 
				prior < getOperatorPriority((char *)tokens[i + 1].value)
			){
				current = moveElementsToAST(&current, &operators, &operands);

				freeStack(operators);
				freeStack(operands);
			}
		}
	}

	current = moveElementsToAST(&current, &operators, &operands);

	freeStack(operators);
	freeStack(operands);

	return root;
}

BinaryTreeNode *moveElementsToAST(BinaryTreeNode **current, Stack **operators, Stack **operands){
	if (*operators == NULL && *operands != NULL){
		(*current)->value = malloc(MAX_LEN_TOKEN_VALUE * sizeof(char));
		strcpy((char *)(*current)->value, (*operands)->value);
	}

	while (*operands != NULL && *operators != NULL){
		(*current)->value = malloc(MAX_LEN_TOKEN_VALUE * sizeof(char));
		strcpy((char *)(*current)->value, (*operators)->value);
		*operators = popFromStack(*operators);

		(*current)->left = createBinaryTreeNode();
		(*current)->right = createBinaryTreeNode();

		if ((*operands)->next != NULL){
			(*current)->right->value = malloc(MAX_LEN_TOKEN_VALUE * sizeof(char));
			strcpy((char *)(*current)->right->value, (*operands)->value);
			*operands = popFromStack(*operands);
		}

		// another if-construction
		if ((*operands)->next == NULL){
			(*current)->left->value = malloc(MAX_LEN_TOKEN_VALUE * sizeof(char));
			strcpy((char *)(*current)->left->value, (*operands)->value);
			*operands = popFromStack(*operands);

			current = &(*current)->right;
		}

		
		else {
			current = &(*current)->left;
		}
	}

	return *current;
}