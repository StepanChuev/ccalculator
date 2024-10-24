#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binaryTree.h"
#include "parser.h"
#include "lexer.h"
#include "executor.h"

int main(int argc, char **argv){
	char *expression = "4+12*7-5"; // "  -12.5   +3.0    * -9  --17  "
	char *normalized = normalize(expression);
	Token *tokens = getTokensFromExpression(normalized);
	BinaryTreeNode *AST = buildASTFromTokens(tokens);

	printf("%p\n", AST);
	printf("%s\n", (char *)AST->value);
	printf("%s -> %s\n", expression, normalized);
	// printf("%f %f %f %f\n", getResultFromOperator("+", 45.0, 34.7), getResultFromOperator("-", 45.0, 34.7), getResultFromOperator("*", 45.0, 1.5), getResultFromOperator("/", 12.0, 3.4));

	size_t i;

	for (i = 0; strcmp(tokens[i].name, END_TOKEN); i++){
		printf("%s(%s) ", tokens[i].name, tokens[i].value);
	}

	printf("%s(%s) ", tokens[i].name, tokens[i].value);

	printf("\n");

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

	return 0;
}