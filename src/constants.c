#include <string.h>
#include "constants.h"

double getConstantValue(char *constant){
	if (!strcmp(PI_CONSTANT, constant)){
		return 3.1415926535897932384;
	}

	if (!strcmp(E_CONSTANT, constant)){
		return 2.7182818284590452353;
	}

	if (constant[0] == '-' && constant[1] != '-'){
		return -getConstantValue(constant + 1);
	}

	return 0.0;
}