#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "io.h"

char *getExpressionFromStdin(size_t maxLen){
	char *expression = (char *)malloc(maxLen * sizeof(char));
	char *newln = NULL;

	if (fgets(expression, maxLen, stdin) == NULL){
		return NULL;
	}

	if ((newln = strchr(expression, '\n')) != NULL){
		*newln = '\0';
	}

	return expression;
}

char *getExpressionFromFile(FILE *file, char sep){
	const size_t limit = SIZE_MAX - 1;
	size_t lenExpression = 1024, i;
	char *expression = (char *)malloc(lenExpression * sizeof(char));

	for (i = 0; (expression[i] = getc(file)) != sep && expression[i] != EOF; i++){
		if (i + 1 >= lenExpression){
			if (lenExpression == limit){
				break;
			}

			if (lenExpression >= limit / 2){
				lenExpression = limit;
			}

			else {
				lenExpression *= 2;
			}

			expression = (char *)realloc(expression, lenExpression * sizeof(char));
		}
	}

	expression[i] = '\0';

	return expression;
}

char *getFilePathByFlag(const char *flag, int argc, char *argv[]){
	char *path = NULL;

	for (int i = 0; i < argc - 1; i++){
		if (!strcmp(flag, argv[i])){
			path = argv[i + 1];
			break;
		}
	}

	return path;
}

FILE *getIOFile(const char *flag, const char *mode, int argc, char *argv[]){
	char *path = getFilePathByFlag(flag, argc, argv);
	FILE *file = NULL;

	if (path == NULL){
		return NULL;
	}

	file = fopen(path, mode);

	if (file == NULL){
		fprintf(stderr, "Error opening file\n");
	}

	return file;
}