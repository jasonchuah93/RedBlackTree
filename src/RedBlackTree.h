#ifndef RedBlackTree_H
#define RedBlackTree_H


void addRedBlackTree(Node **rootPtr,Node *newNode);
void handleColor(Node **rootPtr,Node *newNode);
Node *delRedBlackTree(Node **rootPtr,Node *newNode);
Node *delRedBlackTreeVer2(Node **rootPtr,Node *newNode);
Node *removeNextLargerSuccessor(Node **parentPtr);

#endif // RedBlackTree_H
