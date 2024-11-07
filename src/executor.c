#include <string.h>
#include <math.h>
#include <ctype.h>
#include "operators.h"
#include "lexer.h"
#include "constants.h"
#include "executor.h"

double execute(BinaryTreeNode *root){
	if (!strcmp(getTokenName(root->value, 0), CONSTANT_TOKEN)){
		return getConstantValue(root->value);
	}

	if (!strcmp(getTokenName(root->value, 0), OPERATOR_TOKEN)){
		return getResultFromOperator((char *)root->value, execute(root->left), execute(root->right));
	}

	return atof(root->value);
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