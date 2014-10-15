#include <stdio.h>
#include "Rotation.h"
#include "Node.h"

void rightRotate(Node **nodePtr){
	Node *currentRoot = (*nodePtr)->left; //10
	Node *newRoot = currentRoot->right;
	currentRoot->right=(*nodePtr);
	(*nodePtr)->left = newRoot;
	*nodePtr = currentRoot;
}

void leftRotate(Node **nodePtr){
	Node *currentRoot = (*nodePtr)->right; //10
	Node *newRoot = currentRoot->left;
	currentRoot->left=(*nodePtr);
	(*nodePtr)->right = newRoot;
	*nodePtr = currentRoot;
}