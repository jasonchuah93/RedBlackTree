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
	
}
