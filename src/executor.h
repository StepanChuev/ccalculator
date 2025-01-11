#ifndef EXECUTOR_H

#include "binaryTree.h"

#define EXECUTOR_H

double execute(BinaryTreeNode *root);
double *executeASTs(BinaryTreeNode **ASTs, size_t amountASTs);
double getResultFromOperator(char *operator, double operand1, double operand2);

#endif