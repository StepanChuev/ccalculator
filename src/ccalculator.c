#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

int main(int argc, char **argv){
	char *expression = "  -12.5   +3.0    * -9  --17  ;";
	char *normalized = normalize(expression);
	Token *tokens = getTokensFromExpression(normalized);

	printf("%s -> %s\n", expression, normalized);

	for (int i = 0; strcmp(tokens[i].name, END_TOKEN); i++){
		printf("%s(%s) ", tokens[i].name, tokens[i].value);
	}

	printf("\n");

	for (int i = 0; strcmp(tokens[i].name, END_TOKEN); i++){
		free(tokens[i].name);
		free(tokens[i].value);
	}

	free(tokens);
	free(normalized);

	return 0;
}