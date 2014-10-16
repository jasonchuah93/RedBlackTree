#include <stdio.h>
#include "Node.h"
#include "RedBlackTree.h"
#include "ErrorCode.h"


void _addRedBlackTree(Node **rootPtr,Node *newNode){
	if(*rootPtr == NULL){
		newNode=*rootPtr;
	}else{
		newNode=(*rootPtr)->left;
		printf("what node is this %d \n",&newNode->data);
		//*rootPtr=newNode;
	}
}


void addRedBlackTree(Node **rootPtr,Node *newNode){
	_addRedBlackTree(rootPtr,newNode);
	(newNode)->color='b';
}


