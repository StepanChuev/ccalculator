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
	char base = '\0';
	const size_t lenExpression = 1024;
	char *baseValuePtr = NULL;
	char *expression = NULL;
	char *normalized = NULL;
	Token *tokens = NULL;
	BinaryTreeNode *AST = NULL;
	FILE *input = NULL;
	FILE *output = NULL;
	double result = 0.0;

	if ((input = getIOFile(FILEIN_FLAG, "r", argc, argv)) == NULL){
		input = stdin;
	}

	if ((output = getIOFile(FILEOUT_FLAG, "w", argc, argv)) == NULL){
		output = stdout;
	}

	if ((baseValuePtr = getValueByFlag(BASE_FLAG, argc, argv)) == NULL){
		base = 'd';
	}

	else {
		base = *baseValuePtr;
	}

	while (1){
		if (output != stdout){
			fflush(output);
		}

		if (input == stdin || input == NULL){
			printf(">>> ");

			if ((expression = getExpressionFromStdin(lenExpression)) == NULL){
				fprintf(stderr, "Scan failed\n");
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
			fprintf(stderr, "Empty expression\n");
			freeTokens(tokens);
			free(normalized);
			free(expression);

			continue;
		}

		AST = buildASTFromTokens(tokens);
		result = executeAST(AST);

		if (result < 0.0){
			fprintf(output, "-");
			result = -result;
		}

		switch (base){
			case 'b':
				fprintBin(output, (unsigned long int)result);
				fprintf(output, "\n");
				break;

			case 'o':
				fprintf(output, "%lo\n", (unsigned long int)result);
				break;

			case 'x':
				fprintf(output, "%lx\n", (unsigned long int)result);
				break;

			case 'X':
				fprintf(output, "%lX\n", (unsigned long int)result);
				break;

			default:
				fprintf(output, "%0.15lf\n", result);
				break;
		}

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