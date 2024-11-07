#include <string.h>
#include "constants.h"

double getConstantValue(char *constant){
	if (!strcmp(PI_CONSTANT, constant)){
		return 3.1415926535897932384;
	}

	if (!strcmp(E_CONSTANT, constant)){
		return 2.7182818284590452353;
	}

	if (constant[0] == '-' && !strcmp(PI_CONSTANT, constant + 1)){
		return -3.1415926535897932384;
	}

	if (constant[0] == '-' && !strcmp(E_CONSTANT, constant + 1)){
		return -2.7182818284590452353;
	}

	return 0.0;
}