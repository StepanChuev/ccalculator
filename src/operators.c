#include <string.h>
#include "operators.h"

int getOperatorPriority(char operator){
	if (PLUS_OPERATOR[0] == operator || MINUS_OPERATOR[0] == operator){
		return 1;
	}

	if (MULTIPLY_OPERATOR[0] == operator || DIVIDE_OPERATOR[0] == operator){
		return 2;
	}

	return -1;
}