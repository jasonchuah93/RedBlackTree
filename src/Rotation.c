#include <stdio.h>
#include "Rotation.h"
#include "Node.h"
#include "InitNode.h"

void rightRotate(Node **nodePtr){
	Node *currentRoot = (*nodePtr)->left; 
	Node *newRoot = currentRoot->right;
	currentRoot->right=(*nodePtr);
	(*nodePtr)->left = newRoot;
    *nodePtr = currentRoot;
	currentRoot->right->color='r';
}

void leftRotate(Node **nodePtr){
	Node *currentRoot = (*nodePtr)->right;
	Node *newRoot = currentRoot->left;
	currentRoot->left=(*nodePtr);
	(*nodePtr)->right = newRoot;
	*nodePtr = currentRoot;
	currentRoot->left->color='r';
}

void leftRightRotate(Node **nodePtr){
	Node *currentRoot = *nodePtr;
	leftRotate(&currentRoot->left);
	rightRotate(&(*nodePtr));
}

void rightLeftRotate(Node **nodePtr){
	Node *currentRoot = *nodePtr;
	rightRotate(&currentRoot->right);
	leftRotate(&(*nodePtr));
}

