#include <stdio.h>
#include "Node.h"
#include "InitNode.h"
#include "Rotation.h"
#include "RestructureNode.h"
#include "ErrorCode.h"
#include "CException.h"

#define leftChild (*nodePtr)->left
#define rightChild (*nodePtr)->right
#define leftGrandChild (*nodePtr)->left->left
#define rightGrandChild (*nodePtr)->right->right
#define leftRightGrandChild (*nodePtr)->left->right
#define rightLeftGrandChild (*nodePtr)->right->left

int isNodeBlack(Node **node){
	if(*node!=NULL && (*node)->color=='b'){
		return 1;
	}else{
		return 0;
	}
}

int isNodeRed(Node **node){
	if(*node!=NULL && (*node)->color=='r'){
		return 1;
	}else{
		return 0;
	}
}

int isDoubleNodeBlack(Node **node){
	if(*node==NULL){
		return 1;
	}
	if(*node!=NULL &&(*node)->color=='d'){
		return 1;
	}else
		return 0;
}

/*************************

 CASE 1 SUB-FUNCTION
*************************/
void restructureBlackRightWithOneRedChild(Node **nodePtr){
	char parentColor = (*nodePtr)->color;
	if(isNodeRed(&rightGrandChild)){
		rightChild->color = parentColor;
        leftRotateVer2(nodePtr);
    }else if(isNodeRed(&rightLeftGrandChild)){
		rightLeftGrandChild->color = parentColor;
        rightLeftRotateVer2(nodePtr);
	}
    if(leftChild)
        leftChild->color='b';
    if(rightChild)
        rightChild->color='b';
}

void restructureBlackLeftWithOneRedChild(Node **nodePtr){
	char parentColor = (*nodePtr)->color;
	if(isNodeRed(&leftGrandChild)){
		leftChild->color = parentColor;
        rightRotateVer2(nodePtr);
    }else if(isNodeRed(&leftRightGrandChild)){
		leftRightGrandChild->color = parentColor;
        leftRightRotateVer2(nodePtr);
	}
    if(leftChild)
        leftChild->color='b';
    if(rightChild)
        rightChild->color='b';
}

/*************************

 CASE 2 SUB-FUNCTION
*************************/

void restructureBlackRightWithBlackChildren(Node **nodePtr){
	char parentColor=(*nodePtr)->color;
	if((parentColor = (*nodePtr)->color)=='b'){
		(*nodePtr)->color = 'd';
	}else{
		(*nodePtr)->color = 'b';
	}
    rightChild->color='r';
}

void restructureBlackLeftWithBlackChildren(Node **nodePtr){
	char parentColor=(*nodePtr)->color;
	if((parentColor = (*nodePtr)->color)=='b'){
		(*nodePtr)->color = 'd';
	}else{
		(*nodePtr)->color = 'b';
	}
	leftChild->color='r';
}

/*************************

 CASE 3 SUB-FUNCTION
*************************/

void restructureRedRight(Node **nodePtr){
	leftRotate(nodePtr);
    (*nodePtr)->color = 'b';
    restructureBlackRightWithBlackChildren(&leftChild);
    leftChild->color='b';
}

void restructureRedLeft(Node **nodePtr){
	rightRotate(nodePtr);
    (*nodePtr)->color = 'b';
	restructureBlackLeftWithBlackChildren(&rightChild);
	rightChild->color='b';
}


