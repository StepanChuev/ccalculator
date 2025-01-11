#include <stdlib.h>
#include <string.h>
#include "binaryTree.h"

BinaryTreeNode *createBinaryTreeNode(void){
	BinaryTreeNode *root = (BinaryTreeNode *)malloc(sizeof(BinaryTreeNode));

	root->value = NULL;
	root->left = NULL;
	root->right = NULL;

	return root;
}

void freeBinaryTree(BinaryTreeNode *root){
	if (root == NULL){
		return;
	}

	freeBinaryTree(root->left);
	freeBinaryTree(root->right);

	free(root->value);
	free(root);
}

void freeBinaryTrees(BinaryTreeNode **trees){
	for (size_t i = 0; trees[i] != NULL; i++){
		freeBinaryTree(trees[i]);
	}

	free(trees);
}