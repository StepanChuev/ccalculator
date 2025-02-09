#ifndef EXECUTOR_H

#include "binaryTree.h"

#define EXECUTOR_H
#define DEFINE_BASE(chr) ((chr) == 'b' ? 2 : ((chr) == 'o' ? 8 : ((chr) == 'x' ? 16 : 10)))

double executeAST(BinaryTreeNode *root);
double *executeASTs(BinaryTreeNode **ASTs, size_t amountASTs);
double getResultFromOperator(char *operator, double operand1, double operand2);
double numberTokenToDouble(char *number); // convert dec, octodec and hex numbers to double

#endif