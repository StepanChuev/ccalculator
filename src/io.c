#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "io.h"

void fprintBin(FILE *file, unsigned long int num){
	int flag = 0, bit = 0;

	for (int i = sizeof(unsigned long int) * 8 - 1; i >= 0; i--){
		bit = (num >> i) & 1;
		flag = flag | bit;

		if (flag || i == 0){
			fprintf(file, "%d", bit);
		}
	}
}

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

char *getValueByFlag(const char *flag, int argc, char *argv[]){
	char *value = NULL;

	for (int i = 0; i < argc - 1; i++){
		if (!strcmp(flag, argv[i])){
			value = argv[i + 1];
			break;
		}
	}

	return value;
}

FILE *getIOFile(const char *flag, const char *mode, int argc, char *argv[]){
	char *path = getValueByFlag(flag, argc, argv);
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