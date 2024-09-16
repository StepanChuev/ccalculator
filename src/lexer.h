#ifndef LEXER_H

#define LEXER_H

#define NUMBER_TOKEN "num"
#define OPERATOR_TOKEN "op"
#define END_TOKEN ";"

#define PLUS_OPERATOR "+"
#define MINUS_OPERATOR "-"
#define MULTIPLY_OPERATOR "*"
#define DIVIDE_OPERATOR "/"
#define ALL_OPERATORS "+-*/"

#define MAX_LEN_TOKEN_NAME 4

typedef struct {
	char *name;
	char *value;
} Token;

Token *getTokensFromExpression(char *expression);
const char *getTokenName(char *expression, int index);
char *normalize(char *expression);

#endif