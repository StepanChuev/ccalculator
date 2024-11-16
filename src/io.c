#include <stdio.h>
#include <string.h>
#include "io.h"

char *getExpressionFromStdin(char *expression, size_t maxLen){
	char *newln = NULL;

	if (fgets(expression, maxLen, stdin) == NULL){
		return NULL;
	}

	if ((newln = strchr(expression, '\n')) != NULL){
		*newln = '\0';
	}

	return expression;
}