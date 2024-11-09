#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binaryTree.h"
#include "parser.h"
#include "lexer.h"
#include "executor.h"

int main(int argc, char **argv){
	const size_t lenExpression = 1024;
	size_t i = 0;
	char *expression = NULL;
	char *normalized = NULL;
	Token *tokens = NULL;
	BinaryTreeNode *AST = NULL;

	while (1){
		expression = (char *)malloc(lenExpression * sizeof(char));

		printf(">>> ");
		gets(expression);

		normalized = normalize(expression);
		tokens = getTokensFromExpression(normalized);
		AST = buildASTFromTokens(tokens);

		printf("%f\n", execute(AST));
	
		for (i = 0; strcmp(tokens[i].name, END_TOKEN); i++){
			free(tokens[i].name);
			free(tokens[i].value);
		}

		free(tokens[i].name);
		free(tokens[i].value);

		freeBinaryTree(AST);
		free(tokens);
		free(normalized);
		free(expression);
	}

	return 0;
}