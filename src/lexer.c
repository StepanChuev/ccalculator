#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include "lexer.h"

Token *getTokensFromExpression(char *expression){
	size_t lenTokens = 1024;
	size_t tokensIndex = 0;
	size_t startValueIndex = 0;
	size_t lenTokenValue = 0;
	int tokenCode = END_TOKEN;

	Token *tokens = (Token *)malloc(lenTokens * sizeof(Token));
	tokens[0].value = (char *)malloc(MAX_LEN_TOKEN_VALUE * sizeof(char));
	tokens[0].code = tokenCode = getTokenCode(expression, 0, tokenCode);

	for (size_t i = 1; expression[i] != '\0'; i++){
		tokenCode = getTokenCode(expression, i, tokenCode);

		if (tokensIndex + 1 >= lenTokens){
			if (lenTokens >= SIZE_MAX / 2){
				lenTokens = SIZE_MAX;
			}

			else {
				lenTokens *= 2;
			}

			tokens = (Token *)realloc(tokens, lenTokens * sizeof(Token));
		}

		if (tokenCode != tokens[tokensIndex].code || tokenCode == OPERATOR_TOKEN){
			lenTokenValue = i - startValueIndex;

			strncpy(tokens[tokensIndex].value, expression + startValueIndex, lenTokenValue);
			tokens[tokensIndex].value[lenTokenValue] = '\0';

			tokens[++tokensIndex].value = (char *)malloc(MAX_LEN_TOKEN_VALUE * sizeof(char));
			tokens[tokensIndex].code = tokenCode;

			startValueIndex = i;
		}
	}

	strcpy(tokens[tokensIndex].value, END_TOKEN_VALUE);

	return tokens;
}

int getTokenCode(char *expression, size_t index, int prevTokenCode){
	if (isOperatorToken(expression, index, prevTokenCode)){
		return OPERATOR_TOKEN;
	}

	if (isNumberToken(expression, index, prevTokenCode)){
		return NUMBER_TOKEN;
	}

	if (isNameToken(expression, index, prevTokenCode)){
		return NAME_TOKEN;
	}

	return END_TOKEN;
}

int isOperatorToken(char *expression, size_t index, int prevTokenCode){
	return (
		strchr(ALL_OPERATORS, expression[index]) && 
		(expression[index] != '-' || (index != 0 && expression[index - 1] == ')') || 
			(prevTokenCode != OPERATOR_TOKEN && 
			(index != 0 || (expression[index + 1] == '-' || expression[index + 1] == '\0')) &&
			!(index != 0 && prevTokenCode == NUMBER_TOKEN && (expression[index - 1] == 'e' || expression[index - 1] == 'E')))
		)
	);
}

int isNumberToken(char *expression, size_t index, int prevTokenCode){
	return (prevTokenCode != NAME_TOKEN && (
		isdigit(expression[index]) || expression[index] == '.' || 
		(
			expression[index] == '-' && isdigit(expression[index + 1]) && 
			(
				index == 0 || expression[index - 1] == 'e' || expression[index - 1] == 'E' || 
				(prevTokenCode == OPERATOR_TOKEN && CLOSEPAREN_OPERATOR[0] != expression[index - 1])
			)
		) ||
		(
			(expression[index] == 'e' || expression[index] == 'E') && 
			index > 0 && isdigit(expression[index - 1])
		) ||
		(
			prevTokenCode == NUMBER_TOKEN && isalpha(expression[index])
		)
	));
}

int isNameToken(char *expression, size_t index, int prevTokenCode){
	return (
		(prevTokenCode == NAME_TOKEN && (isalpha(expression[index]) || expression[index] == '_' || isdigit(expression[index]))) || 
		((prevTokenCode == OPERATOR_TOKEN || prevTokenCode == END_TOKEN) && 
		(
			isalpha(expression[index]) || expression[index] == '_' || 
			(expression[index] == '-' && (isalpha(expression[index + 1]) || expression[index + 1] == '_') && 
			(index == 0 || CLOSEPAREN_OPERATOR[0] != expression[index - 1]))
		)
	));
}

char *normalize(char *srcExp){
	const size_t limit = SIZE_MAX - 2;
	size_t lenNormalized = 1024;
	size_t normalizedIndex = 0;
	char *normalized = (char *)malloc(lenNormalized * sizeof(char));

	for (size_t i = 0; srcExp[i] != '\0'; i++){
		if (srcExp[i] == ' '){
			continue;
		}

		if (normalizedIndex + 3 >= lenNormalized){
			if (lenNormalized >= limit){
				normalized[normalizedIndex++] = srcExp[i];
				strcpy(normalized + normalizedIndex, END_TOKEN_VALUE);
				normalized[++normalizedIndex] = '\0';

				return normalized;
			}

			if (lenNormalized >= limit / 2){
				lenNormalized = limit;
			}

			else {
				lenNormalized *= 2;
			}

			normalized = (char *)realloc(normalized, lenNormalized * sizeof(char));
		}

		if (
			normalizedIndex > 0 && srcExp[i] == '(' && normalized[normalizedIndex - 1] == '-' && 
			(normalizedIndex <= 1 || strchr(ALL_OPERATORS, normalized[normalizedIndex - 2]))
		){
			normalized[normalizedIndex++] = '1';
			normalized[normalizedIndex++] = '*';
		}

		normalized[normalizedIndex++] = srcExp[i];
	}

	strcpy(normalized + normalizedIndex, END_TOKEN_VALUE);
	normalized[++normalizedIndex] = '\0';

	return normalized;
}

void freeTokens(Token *tokens){
	size_t i = 0;

	while (tokens[i].code != END_TOKEN){
		free(tokens[i].value);
		i++;
	}

	free(tokens[i].value);
	free(tokens);
}