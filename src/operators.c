#include <string.h>
#include "operators.h"

int getOperatorPriority(char *operator){
	if (operator[0] == PLUS_OPERATOR[0] || operator[0] == MINUS_OPERATOR[0]){
		return 1;
	}

	if (operator[0] == MULTIPLY_OPERATOR[0] || operator[0] == DIVIDE_OPERATOR[0]){
		return 2;
	}

	return -1;
}