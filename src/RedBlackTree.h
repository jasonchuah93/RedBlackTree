#ifndef RedBlackTree_H
#define RedBlackTree_H

void addRedBlackTree(Node **rootPtr,Node *newNode);
void handleColor(Node **rootPtr,Node *newNode);
Node *delRedBlackTree(Node **rootPtr,Node *newNode);
Node *delRedBlackTreeVer2(Node **rootPtr,Node *newNode);
int isNodeBlack(Node *node);
int isNodeRed(Node *node);
int isDoubleNodeBlack(Node *node);
void restructureBlackRightWithOneRedChild(Node **nodePtr);
void restructureBlackLeftWithOneRedChild(Node **nodePtr);

void restructureBlackRightWithBlackChildren(Node **nodePtr);
void restructureBlackLeftWithBlackChildren(Node **nodePtr);

void restructureRedRight(Node **nodePtr);
void restructureRedLeft(Node **nodePtr);

void restructureBlackRight(Node **nodePtr);
void restructureBlackLeft(Node **nodePtr);

void restructureBlackRightWithBlackChildrenForRedRight(Node **nodePtr);
void restructureBlackLeftWithBlackChildrenForRedLeft(Node **nodePtr);

#endif // RedBlackTree_H
