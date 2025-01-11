#ifndef BINARYTREE_H

#define BINARYTREE_H


typedef struct BinaryTreeNode {
	void *value;
	struct BinaryTreeNode *left;
	struct BinaryTreeNode *right;
} BinaryTreeNode;


BinaryTreeNode *createBinaryTreeNode(void);
void freeBinaryTree(BinaryTreeNode *root);
void freeBinaryTrees(BinaryTreeNode **trees);


#endif