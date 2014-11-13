#include <stdio.h>
#include "Node.h"
#include "InitNode.h"
#include "Rotation.h"
#include "RestructureNode.h"
#include "RedBlackTree.h"
#include "ErrorCode.h"
#include "CException.h"

#define leftChild (*rootPtr)->left
#define rightChild (*rootPtr)->right
#define leftGrandChild (*rootPtr)->left->left
#define rightGrandChild (*rootPtr)->right->right
#define leftRightGrandChild (*rootPtr)->left->right
#define rightLeftGrandChild (*rootPtr)->right->left

void _addRedBlackTree(Node **rootPtr,Node *newNode);
Node *_delRedBlackTree(Node **rootPtr,Node *newNode);
Node *_delRedBlackTreeVer2(Node **rootPtr,Node *newNode);

void handleColor(Node **rootPtr,Node *newNode){
  Node *root = *rootPtr;
  if(root->left->color == 'r' && root->right->color == 'r'){
        root->left->color ='b';
        root->right->color ='b';
        root->color ='r';
      }
}

void addRedBlackTree(Node **rootPtr,Node *newNode){
	_addRedBlackTree(rootPtr,newNode);
	(*rootPtr)->color='b';
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
  Node *root=*rootPtr;
  if(root==newNode){
	*rootPtr=NULL;
    return node;
  }else{
	if(leftChild == NULL && rightChild == NULL){
		 Throw(ERR_NODE_UNAVAILABLE);
    }else if((*rootPtr)->data > newNode->data){
        node= _delRedBlackTree(&leftChild,newNode);
    }else if((*rootPtr)->data < newNode->data){
		node= _delRedBlackTree(&rightChild,newNode);
        
	}
  }
  restructureRedBlackTree(rootPtr,newNode);
  
  return node;
}

Node *removeNextLargerSuccessor(Node **rootPtr){
	Node *removeNode, *childOfParent;
	
	if(leftChild !=NULL){
		removeNode = removeNextLargerSuccessor(&leftChild);
        
	}else if(rightChild == NULL){
		removeNode = *rootPtr;
		*rootPtr = NULL;
        return removeNode;
	}else if(leftChild == NULL){
		removeNode = *rootPtr;
		*rootPtr = rightChild;
		(*rootPtr)->color = 'b';
        return removeNode;
	}
    
	restructureRedBlackTree(rootPtr,removeNode);
	return removeNode;
}

/******************************************************]
	********************
		Old function 
	********************
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

Node *removeNextLargetSuccessor(Node **childOfParentPtr){
	Node *removeNode, *childOfParent = *childOfParentPtr;
	if(childOfParent->left){
		removeNode = removeNextLargetSuccessor(&childOfParent->left);
		if(childOfParent = *childOfParentPtr){
			if(childOfParent->right->color == 'b'){
				restructureBlackRightWithOneRedChild(childOfParentPtr);
			}else{
				restructureRedRight(childOfParentPtr,removeNode);
			}
		}
	}else{
		removeNode = *childOfParentPtr;
		*childOfParentPtr = NULL;
	}
	return removeNode;		
}

*********************************************************************/
