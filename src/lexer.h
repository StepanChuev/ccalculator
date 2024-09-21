#include "operators.h"

#ifndef LEXER_H

#define LEXER_H

#define MAX_LEN_TOKEN_NAME 4
#define MAX_LEN_TOKEN_VALUE 312

typedef struct {
	char *name;
	char *value;
} Token;

Token *getTokensFromExpression(char *expression);
const char *getTokenName(char *expression, int index);
char *normalize(char *srcExp);

#endif