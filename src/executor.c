#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "operators.h"
#include "lexer.h"
#include "names.h"
#include "executor.h"

double executeAST(BinaryTreeNode *root){
	int tokenCode = getTokenCode(root->value, 0, END_TOKEN);

	if (tokenCode == OPERATOR_TOKEN){
		return getResultFromOperator((char *)root->value, executeAST(root->left), executeAST(root->right));
	}

	return numberTokenToDouble((char *)root->value);
}

double *executeASTs(BinaryTreeNode **ASTs, size_t amountASTs){
	size_t i = 0;
	double *results = (double *)malloc(amountASTs * sizeof(double));

	while (ASTs[i] != NULL && i < amountASTs){
		results[i] = executeAST(ASTs[i]);
		i++;
	}

	return results;
}

double getResultFromOperator(char *operator, double operand1, double operand2){
	if (!strcmp(PLUS_OPERATOR, operator)){
		return operand1 + operand2;
	}

	if (!strcmp(MINUS_OPERATOR, operator)){
		return operand1 - operand2;
	}

	if (!strcmp(MULTIPLY_OPERATOR, operator)){
		return operand1 * operand2;
	}

	if (!strcmp(DIVIDE_OPERATOR, operator)){
		return operand1 / operand2;
	}

	return 0.0;
}

double numberTokenToDouble(char *number){
	int negnum = (number[0] == '-');
	int tmp = negnum + 1;

	if (isdigit(number[tmp]) || number[tmp] == '.' || number[tmp] == '\0'){
		return atof(number);
	}

	tmp = DEFINE_BASE(number[tmp]);

	return (negnum ? -1.0 : 1.0) * (double)strtoul(number + 2 + negnum, NULL, tmp);
}