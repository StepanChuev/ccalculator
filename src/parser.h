#ifndef PARSER_H

#define PARSER_H

#include "lexer.h"
#include "binaryTree.h"
#include "stack.h"

BinaryTreeNode *buildASTFromTokens(Token *tokens);
BinaryTreeNode *moveElementsToAST(BinaryTreeNode **current, Stack **stack);

#endif