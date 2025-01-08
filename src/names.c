#include <string.h>
#include <math.h>
#include "names.h"

double getNameValue(char *name, double *args){
	if (name[0] == '-' && name[1] != '-'){
		return -getNameValue(name + 1, args);
	}

	if (!strcmp(SQRT_NAME, name)){
		return sqrt(args[0]);
	}

	if (!strcmp(CBRT_NAME, name)){
		return cbrt(args[0]);
	}

	if (!strcmp(PI_NAME, name)){
		return 3.1415926535897932384;
	}

	if (!strcmp(E_NAME, name)){
		return 2.7182818284590452353;
	}

	if (!strcmp(SQRT2_NAME, name)){
		return 1.4142135623730950488;
	}

	return 0.0;
}