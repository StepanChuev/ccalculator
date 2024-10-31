#include <string.h>
#include "operators.h"

int getOperatorPriority(char *operator){
	if (!strcmp(PLUS_OPERATOR, operator) || !strcmp(MINUS_OPERATOR, operator)){
		return 1;
	}

	if (!strcmp(MULTIPLY_OPERATOR, operator) || !strcmp(DIVIDE_OPERATOR, operator)){
		return 2;
	}

	if (!strcmp(OPENPAREN_OPERATOR, operator)){
		return 3;
	}

	return -1;
}