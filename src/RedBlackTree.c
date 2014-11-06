#include <stdio.h>
#include "Node.h"
#include "InitNode.h"
#include "Rotation.h"
#include "RedBlackTree.h"
#include "ErrorCode.h"
#include "CException.h"

void _addRedBlackTree(Node **rootPtr,Node *newNode);
Node *_delRedBlackTree(Node **rootPtr,Node *newNode);
Node *_delRedBlackTreeVer2(Node **rootPtr,Node *newNode);

void addRedBlackTree(Node **rootPtr,Node *newNode){
	_addRedBlackTree(rootPtr,newNode);
	(*rootPtr)->color='b';
}

void handleColor(Node **rootPtr,Node *newNode){
  Node *root = *rootPtr;
  if(root->left->color == 'r' && root->right->color == 'r'){
        root->left->color ='b';
        root->right->color ='b';
        root->color ='r';
      }
}

void _addRedBlackTree(Node **rootPtr,Node *newNode){
	Node *root = *rootPtr;
	if(root == NULL){
		*rootPtr = newNode;
    return;
  }
  if (root->left!=NULL && root->right!=NULL){
    handleColor(rootPtr,newNode); 
  }
  if(root->data > newNode->data){
	_addRedBlackTree(&root->left,newNode);
  }else if(root->data < newNode->data){
	_addRedBlackTree(&root->right,newNode);
  }else{
	Throw(ERR_EQUIVALENT_NODE);
  }
	
  if(root->left!=NULL && root->right==NULL){
		if(root->left->left !=NULL){
			if(root->left->color == 'r' && root->left->left->color == 'r'){
				rightRotate(rootPtr);
			}
		}else if(root->left->right !=NULL){
			if(root->left->color == 'r' && root->left->right->color == 'r'){
				leftRightRotate(rootPtr);
			}
		}
  }else if(root->left==NULL && root->right!=NULL){
		if(root->right->right !=NULL){
			if(root->right->color == 'r' && root->right->right->color == 'r'){
				leftRotate(rootPtr);
			}
		}else if(root->right->left !=NULL){
			if(root->right->color == 'r' && root->right->left->color == 'r'){
				rightLeftRotate(rootPtr);
			}
		}
  }
}

Node *delRedBlackTree(Node **rootPtr,Node *newNode){
  Node *node =_delRedBlackTree(rootPtr,newNode);
  if(*rootPtr!=NULL)
    (*rootPtr)->color='b';
  return node;
}

Node *_delRedBlackTree(Node **rootPtr,Node *newNode){
  Node *node;
  Node *root = *rootPtr;
  if(root==newNode){
    *rootPtr=NULL;
    return;
  }else{
	if(root->left == NULL && root->right == NULL){
        Throw(ERR_NODE_UNAVAILABLE);
    }else if(root->data > newNode->data){
		if(root->left->left!=NULL || root->left->right!=NULL){
			root->left->color='b';
			root->left->left->color='r';
			root->left->right->color='r';
		}
		node=_delRedBlackTree(&root->left,newNode);
		if(root->left==NULL && root->right!=NULL){
			if(root->right->right!=NULL){
				if(root->right->left->color=='b' && root->right->right->color=='b'){
					leftRotate(rootPtr);
					(*rootPtr)->left->right->color='r';
				}
			}
		}
	}else if(root->data < newNode->data){
		if(root->right->left!=NULL || root->right->right!=NULL){
			root->right->color='b';
			root->right->left->color='r';
			root->right->right->color='r';
		}
		node=_delRedBlackTree(&root->right,newNode);
		if(root->left!=NULL && root->right==NULL){
			if(root->left->left!=NULL){
				if(root->left->left->color=='b' && root->left->right->color=='b'){
					rightRotate(rootPtr);
					(*rootPtr)->right->left->color='r';
				}
			}
		}
	}
  }
  
  return node;
}

Node *delRedBlackTreeVer2(Node **rootPtr,Node *newNode){
	Node *node =_delRedBlackTreeVer2(rootPtr,newNode);
	if(*rootPtr!=NULL)
		(*rootPtr)->color='b';
	return node;
}

Node *_delRedBlackTreeVer2(Node **rootPtr,Node *newNode){
  Node *node;
  Node *root = *rootPtr;
  if(root==newNode){
	*rootPtr=NULL;
	return ;
  }else{
	if(root->left == NULL && root->right == NULL){
		 Throw(ERR_NODE_UNAVAILABLE);
	}else if(root->data > newNode->data){
		node=_delRedBlackTree(&root->left,newNode);
	}else if(root->data < newNode->data){
		node=_delRedBlackTree(&root->right,newNode);
	}	
  }
  if(isNodeRed(node)){
	return node;
  }
  if(isDoubleNodeBlack(root->left)){
	if(isNodeRed(root->right)){
		//restructureRedRight(rootPtr);
	}
  }
  return node;
}

void restructureBlackRightWithOneRedChild(Node **nodePtr){
	Node *grandChild,*child,*parent = *nodePtr;
	char parentColor = parent->color;
	parent->color = 'b';
	child = parent->right;
	if(isNodeRed((grandChild = child->right))){
		leftRotateVer2(nodePtr);
		child->color = parentColor;
		if(grandChild)
			grandChild->color='b';
	}else if(isNodeRed((grandChild = child->left))){
		rightLeftRotateVer2(nodePtr);
		child->color='b';
		if(grandChild)
			grandChild->color='b';
	}
}

void restructureBlackLeftWithOneRedChild(Node **nodePtr){
	Node *grandChild,*child,*parent = *nodePtr;
	char parentColor = parent->color;
	parent->color = 'b';
	child = parent->left;
	if(isNodeRed((grandChild = child->left))){
		rightRotateVer2(nodePtr);
		child->color = parentColor;
		if(grandChild)
			grandChild->color='b';
	}else if(isNodeRed((grandChild = child->right))){
		leftRightRotateVer2(nodePtr);
		child->color='b';
		if(grandChild)
			grandChild->color='b';
	}
}

void restructureBlackRightWithBlackChildren(Node **nodePtr){
	Node *parent = *nodePtr;
	char parentColor=parent->color=='b'?'d':'r';
	if((parentColor = parent->color)=='b'){
		parent->color = 'd';
	}else{
		parent->color = 'b';
	}
	parent->right->color='r';
}

void restructureBlackLeftWithBlackChildren(Node **nodePtr){
	Node *parent = *nodePtr;
	char parentColor=parent->color=='b'?'d':'r';
	if((parentColor = parent->color)=='b'){
		parent->color = 'd';
	}else{
		parent->color = 'b';
	}
	parent->left->color='r';
}

void restructureBlackRightWithBlackChildrenForRedRight(Node **nodePtr){
	Node *parent = *nodePtr;
	char parentColor=parent->color=='b'?'d':'r';
	parent->right->color='r';
}

void restructureBlackLeftWithBlackChildrenForRedLeft(Node **nodePtr){
	Node *parent = *nodePtr;
	char parentColor=parent->color=='b'?'d':'r';
	parent->left->color='r';
}

void restructureRedRight(Node **nodePtr){
	Node *parent = *nodePtr;
	parent->color = 'r';
	leftRotate(nodePtr);
	(*nodePtr)->color='b';
	restructureBlackRight(&parent);
}

void restructureRedLeft(Node **nodePtr){
	Node *parent = *nodePtr;
	parent->color = 'r';
	rightRotate(nodePtr);
	(*nodePtr)->color='b';
	restructureBlackLeft(&parent);
}

void restructureBlackRight(Node **nodePtr){
	Node *grandChild,*child,*parent = *nodePtr;
	char parentColor = parent->color;
	parent->color = 'b';
	child = parent->right;
	if(isNodeRed((grandChild = child->right))){
		leftRotateVer2(nodePtr);
		child->color = parentColor;
		if(grandChild)
			grandChild->color='b';
	}else if(isNodeRed((grandChild = child->left))){
		rightLeftRotateVer2(nodePtr);
		child->color='b';
		if(grandChild)
			grandChild->color='b';
	}else{
		restructureBlackRightWithBlackChildrenForRedRight(nodePtr);
	}
}

void restructureBlackLeft(Node **nodePtr){
	Node *grandChild,*child,*parent = *nodePtr;
	char parentColor = parent->color;
	parent->color = 'b';
	child = parent->left;
	if(isNodeRed((grandChild = child->left))){
		rightRotateVer2(nodePtr);
		child->color = parentColor;
		if(grandChild)
			grandChild->color='b';
	}else if(isNodeRed((grandChild = child->right))){
		leftRightRotateVer2(nodePtr);
		child->color='b';
		if(grandChild)
			grandChild->color='b';
	}else{
		restructureBlackLeftWithBlackChildrenForRedLeft(nodePtr);
	}
}

int isNodeBlack(Node *node){
	if(node!=NULL && node->color=='b'){
		return 1;
	}else{
		return 0;
	}
}

int isNodeRed(Node *node){
	if(node!=NULL && node->color=='r'){
		return 1;
	}else{
		return 0;
	}
}

int isDoubleNodeBlack(Node *node){
	if(node==NULL){
		return 1;
	}
	if(node!=NULL && node->color=='d'){
		return 1;
	}else
		return 0;
	
}


