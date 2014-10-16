#include <stdio.h>
#include "Node.h"
#include "InitNode.h"
#include "Rotation.h"
#include "RedBlackTree.h"
#include "ErrorCode.h"
#include "CException.h"

void _addRedBlackTree(Node **rootPtr,Node *newNode);

void addRedBlackTree(Node **rootPtr,Node *newNode){
	_addRedBlackTree(rootPtr,newNode);
	(*rootPtr)->color='b';
	
}

void _addRedBlackTree(Node **rootPtr,Node *newNode){
	Node *root = *rootPtr;
	if(root == NULL){
		*rootPtr = newNode;
		return;
	}else if(newNode->data < root->data){
		_addRedBlackTree(&root->left,newNode);
	}else if(newNode->data > root->data){
		_addRedBlackTree(&root->right,newNode);
	}else{
		Throw(ERR_EQUIVALENT_NODE);
	}
	
	if(root->left !=NULL && root->left->left !=NULL){
		if(root->left->color == 'r' && root->left->left->color == 'r'){
			rightRotate(rootPtr);
			(*rootPtr)->right->color='r';
		}
	}else if(root->right !=NULL && root->right->right !=NULL){
		if(root->right->color == 'r' && root->right->right->color == 'r'){
			leftRotate(rootPtr);
			(*rootPtr)->left->color='r';
		}
	}
	else if(root->left !=NULL && root->left->right !=NULL){
		if(root->left->color == 'r' && root->left->right->color == 'r'){
			leftRightRotate(rootPtr);
			(*rootPtr)->right->color='r';
		}
	}
}	


