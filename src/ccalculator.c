#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binaryTree.h"
#include "operators.h"
#include "parser.h"
#include "lexer.h"
#include "executor.h"
#include "io.h"

int main(int argc, char **argv){
	const size_t lenExpression = 1024;
	size_t i = 0;
	char *expression = NULL;
	char *normalized = NULL;
	Token *tokens = NULL;
	BinaryTreeNode *AST = NULL;
	double result = 0.0;

	while (1){
		expression = (char *)malloc(lenExpression * sizeof(char));

		printf(">>> ");

		if (getExpressionFromStdin(expression, lenExpression) == NULL){
			fprintf(stderr, "scan failed\n");
			free(expression);

			continue;
		}

		normalized = normalize(expression);

		if (!strcmp(normalized, END_TOKEN)){
			fprintf(stderr, "empty expression\n");
			free(normalized);
			free(expression);

			continue;
		}

		tokens = getTokensFromExpression(normalized);
		AST = buildASTFromTokens(tokens);
		result = execute(AST);

		printf("%0.15lf\n", result);
	
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