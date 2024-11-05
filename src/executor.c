#include <string.h>
#include <math.h>
#include <ctype.h>
#include "operators.h"
#include "lexer.h"
#include "constants.h"
#include "executor.h"

double execute(BinaryTreeNode *root){
	if (((char *)(root->value))[0] >= 'a' && ((char *)(root->value))[0] <= 'z'){
		return getConstantValue(root->value);
	}

	if (isdigit(((char *)(root->value))[0]) || (((char *)(root->value))[0] == '-' && isdigit(((char *)(root->value))[1]))){
		return atof(root->value);
	}

	return getResultFromOperator((char *)root->value, execute(root->left), execute(root->right));
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