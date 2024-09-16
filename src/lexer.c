#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

Token *getTokensFromExpression(char *expression){
	int lenTokens = 10000;
	int tokensIndex = 0;
	int startValueIndex = 0;
	int lenTokenValue = 0;

	Token *tokens = (Token *)malloc(lenTokens * sizeof(Token));
	tokens[0].name = (char *)malloc(MAX_LEN_TOKEN_NAME * sizeof(char));
	tokens[0].value = (char *)malloc(MAX_LEN_TOKEN_VALUE * sizeof(char));

	strcpy(tokens[0].name, getTokenName(expression, 0));

	for (int i = 1; expression[i] != '\0'; i++){
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
	int lenNormalized = 10000;
	int normalizedIndex = 0;
	char *normalized = (char *)malloc(lenNormalized * sizeof(char));

	for (int i = 0; srcExp[i] != '\0'; i++){
		if (srcExp[i] == ' '){
			continue;
		}

		normalized[normalizedIndex++] = srcExp[i];
	}

	strcpy(normalized + normalizedIndex, END_TOKEN);
	normalized[++normalizedIndex] = '\0';

	return normalized;
}