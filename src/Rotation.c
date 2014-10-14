#include <stdio.h>
#include "Rotation.h"
#include "Node.h"

void rightRotate(Node **nodePtr){
	Node *currentRoot = (*nodePtr)->left;
	currentRoot->right = *nodePtr;
	(*nodePtr)->left=(currentRoot)->left->right;
	
	*nodePtr = currentRoot;
}