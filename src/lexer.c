#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "lexer.h"

Token *getTokensFromExpression(char *expression){
	int lenTokens = 1000;
	int tokensIndex = 0;
	int startValueIndex = 0;
	int lenTokenValue = 0;

	Token *tokens = (Token *)malloc(lenTokens * sizeof(Token));
	tokens[0].name = (char *)malloc(MAX_LEN_TOKEN_NAME * sizeof(char));
	tokens[0].value = (char *)malloc(MAX_LEN_TOKEN_VALUE * sizeof(char));

	strcpy(tokens[0].name, getTokenName(expression, 0));

	for (int i = 1; expression[i] != '\0'; i++){
		if (tokensIndex + 1 >= lenTokens){
			if ((long long int)lenTokens * 2 >= INT_MAX){
				lenTokens = INT_MAX;
			}

			else {
				lenTokens *= 2;
			}

			tokens = (Token *)realloc(tokens, lenTokens * sizeof(Token));
		}

		if (strcmp(tokens[tokensIndex].name, getTokenName(expression, i))){
			lenTokenValue = i - startValueIndex;

			strncpy(tokens[tokensIndex].value, expression + startValueIndex, lenTokenValue);
			tokens[tokensIndex].value[lenTokenValue] = '\0';

			tokens[++tokensIndex].name = (char *)malloc(MAX_LEN_TOKEN_NAME * sizeof(char));
			tokens[tokensIndex].value = (char *)malloc(MAX_LEN_TOKEN_VALUE * sizeof(char));

			strcpy(tokens[tokensIndex].name, getTokenName(expression, i));

			startValueIndex = i;
		}
	}

	return tokens;
}

const char *getTokenName(char *expression, int index){
	if (
		isdigit(expression[index]) || expression[index] == '.' || 
		(expression[index] == '-' && (index == 0 || strchr(ALL_OPERATORS, expression[index - 1])))
	){
		return NUMBER_TOKEN;
	}

	if (strchr(ALL_OPERATORS, expression[index])){
		return OPERATOR_TOKEN;
	}

	return END_TOKEN;
}

char *normalize(char *srcExp){
	const int limit = INT_MAX - 2;
	int lenNormalized = 1000;
	int normalizedIndex = 0;
	char *normalized = (char *)malloc(lenNormalized * sizeof(char));

	for (int i = 0; srcExp[i] != '\0'; i++){
		if (srcExp[i] == ' '){
			continue;
		}

		if (normalizedIndex + 1 >= lenNormalized){
			if (lenNormalized >= limit){
				normalized[normalizedIndex++] = srcExp[i];
				strcpy(normalized + normalizedIndex, END_TOKEN);
				normalized[++normalizedIndex] = '\0';

				return normalized;
			}

			if ((long long int)lenNormalized * 2 >= limit){
				lenNormalized = limit;
			}

			else {
				lenNormalized *= 2;
			}

			normalized = (char *)realloc(normalized, lenNormalized * sizeof(char));
		}

		normalized[normalizedIndex++] = srcExp[i];
	}

	strcpy(normalized + normalizedIndex, END_TOKEN);
	normalized[++normalizedIndex] = '\0';

	return normalized;
}