#ifndef RedBlackTree_H
#define RedBlackTree_H


void addRedBlackTree(Node **rootPtr,Node *deleteNode);
void handleColor(Node **rootPtr,Node *deleteNode);
Node *delRedBlackTree(Node **rootPtr,Node *deleteNode);
Node *delRedBlackTreeVer2(Node **rootPtr,Node *deleteNode);
Node *removeNextLargerSuccessor(Node **parentPtr);

Node *delAndRestructureRedBlackTree(Node **rootPtr , Node *deleteNode);

#endif // RedBlackTree_H

