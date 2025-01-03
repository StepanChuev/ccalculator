#ifndef LEXER_H

#define LEXER_H

#include "operators.h"

#define MAX_LEN_TOKEN_VALUE 312

#define END_TOKEN 0
#define OPERATOR_TOKEN 1
#define NUMBER_TOKEN 2
#define CONSTANT_TOKEN 3

#define END_TOKEN_VALUE ";"

typedef struct {
	int code;
	char *value;
} Token;

Token *getTokensFromExpression(char *expression);
int getTokenCode(char *expression, size_t index, int prevTokenCode);
int isOperatorToken(char *expression, size_t index, int prevTokenCode);
int isNumberToken(char *expression, size_t index, int prevTokenCode);
int isConstantToken(char *expression, size_t index, int prevTokenCode);
char *normalize(char *srcExp);
void freeTokens(Token *tokens);

#endif