#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

int main(int argc, char **argv){
	Token *tokens = getTokensFromExpression("12.5   +3.0    * -9  ;");

	for (int i = 0; strcmp(tokens[i].name, END_TOKEN); i++){
		printf("%s(%s) ", tokens[i].name, tokens[i].value);
	}

	printf("\n");

	free(tokens);

	return 0;
}