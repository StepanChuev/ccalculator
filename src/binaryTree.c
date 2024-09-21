#include <stdlib.h>
#include <string.h>
#include "binaryTree.h"

BinaryTreeNode *createBinaryTreeNode(void *value, BinaryTreeNode *left, BinaryTreeNode *right){
	BinaryTreeNode *root = (BinaryTreeNode *)malloc(sizeof(BinaryTreeNode));

	root->value = value;
	root->left = left;
	root->right = right;

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

void setValueToBinaryTreeNode(BinaryTreeNode *node, void *newValue, size_t size){
	if (node->value != NULL){
		free(node->value);
	}

	node->value = malloc(size);
	memcpy(node->value, newValue, size);
}