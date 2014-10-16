#include <stdio.h>
#include "Rotation.h"
#include "Node.h"

void rightRotate(Node **nodePtr){
	Node *currentRoot = (*nodePtr)->left; 
	Node *newRoot = currentRoot->right;
	currentRoot->right=(*nodePtr);
	(*nodePtr)->left = newRoot;
	*nodePtr = currentRoot;
}

void leftRotate(Node **nodePtr){
	Node *currentRoot = (*nodePtr)->right;
	Node *newRoot = currentRoot->left;
	currentRoot->left=(*nodePtr);
	(*nodePtr)->right = newRoot;
	*nodePtr = currentRoot;
}

void leftRightRotate(Node **nodePtr){
	Node *currentRoot = *nodePtr;
	printf("currentRoot is %d \n",currentRoot->data);
	leftRotate(&currentRoot->left);
	rightRotate(&(*nodePtr));
}

void rightLeftRotate(Node **nodePtr){
	Node *currentRoot = *nodePtr;
	rightRotate(&currentRoot->right);
	leftRotate(&(*nodePtr));
}

