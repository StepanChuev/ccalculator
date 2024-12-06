#ifndef LEXER_H

#define LEXER_H

#include "operators.h"

#define MAX_LEN_TOKEN_NAME 4
#define MAX_LEN_TOKEN_VALUE 312

#define NUMBER_TOKEN "num"
#define OPERATOR_TOKEN "op"
#define CONSTANT_TOKEN "con"
#define END_TOKEN ";"

typedef struct {
	char *name;
	char *value;
} Token;

Token *getTokensFromExpression(char *expression);
const char *getTokenName(char *expression, size_t index);
char *normalize(char *srcExp);
void freeTokens(Token *tokens);

#endif