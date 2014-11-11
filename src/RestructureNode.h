#ifndef RestructureNode_H
#define RestructureNode_H

int isNodeBlack(Node **node);
int isNodeRed(Node **node);
int isDoubleNodeBlack(Node **node);

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

#endif // RestructureNode_H
