#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "binaryTree.h"
#include "operators.h"
#include "parser.h"
#include "lexer.h"
#include "executor.h"
#include "io.h"

int main(int argc, char *argv[]){
	const size_t lenExpression = 1024;
	size_t i = 0;
	char *expression = NULL;
	char *normalized = NULL;
	Token *tokens = NULL;
	BinaryTreeNode *AST = NULL;
	FILE *input = NULL;
	FILE *output = NULL;
	double result = 0.0;

	if ((input = getIOFile(FILEIN_ARG, "r", argc, argv)) == NULL){
		input = stdin;
	}

	if ((output = getIOFile(FILEOUT_ARG, "w", argc, argv)) == NULL){
		output = stdout;
	}

	while (1){
		if (output != stdout){
			fflush(output);
		}

		if (input == stdin || input == NULL){
			printf(">>> ");

			if ((expression = getExpressionFromStdin(lenExpression)) == NULL){
				fprintf(stderr, "scan failed\n");
				free(expression);

				continue;
			}
		}

		else if (!feof(input)){
			expression = getExpressionFromFile(input, '\n');
		}

		else {
			break;
		}

		normalized = normalize(expression);
		tokens = getTokensFromExpression(normalized);

		if (tokens[0].code == END_TOKEN){
			fprintf(stderr, "empty expression\n");
			freeTokens(tokens);
			free(normalized);
			free(expression);

			continue;
		}

		AST = buildASTFromTokens(tokens);
		result = execute(AST);

		fprintf(output, "%0.15lf\n", result);

		freeBinaryTree(AST);
		freeTokens(tokens);
		free(normalized);
		free(expression);
	}

	if (input != stdin && input != NULL){
		fclose(input);
	}
	
	if (output != stdout && output != NULL){
		fclose(output);
	}

	return 0;
}