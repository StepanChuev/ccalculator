#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "stack.h"
#include "binaryTree.h"
#include "parser.h"

BinaryTreeNode *buildASTFromTokens(Token *tokens){
	BinaryTreeNode *current = createBinaryTreeNode();
	BinaryTreeNode *root = current;
	Stack *operands = NULL;
	Stack *operators = NULL;

	for (size_t i = 0; strcmp(tokens[i].name, END_TOKEN); i++){
		if (!strcmp(tokens[i].name, NUMBER_TOKEN)){
			operands = pushToStack(operands);
			operands->value = malloc(MAX_LEN_TOKEN_VALUE * sizeof(char));
			strcpy((char *)operands->value, tokens[i].value);
		}

		else if (strchr(ALL_OPERATORS, tokens[i].value[0])){
			operators = pushToStack(operators);
			operators->value = malloc(MAX_LEN_TOKEN_VALUE * sizeof(char));
			strcpy((char *)operators->value, tokens[i].value);

			if (getOperatorPriority(((char *)(operators->value))[0]) < getOperatorPriority(((char *)(tokens[i + 2].value))[0])){
				current = *moveElementsToAST(&current, &operators, &operands);
			}
		}
	}

	current = *moveElementsToAST(&current, &operators, &operands);

	freeStack(operators);
	freeStack(operands);

	return root;
}

BinaryTreeNode **moveElementsToAST(BinaryTreeNode **current, Stack **operators, Stack **operands){
	while (*operands != NULL){ //  && operators != NULL
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

	freeStack(*operators);
	freeStack(*operands);

	return current;
}