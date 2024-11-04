#include <string.h>
#include "constants.h"

double getConstantValue(char *constant){
	if (!strcmp(PI_CONSTANT, constant)){
		return 3.14; // 3.14159265358979323846
	}

	if (!strcmp(E_CONSTANT, constant)){
		return 2.71; // 2.71828182845904523536
	}

	return 0.0;
}