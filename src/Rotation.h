#ifndef Rotation_H
#define Rotation_H

#include "Node.h"

void leftRotate(Node **nodePtr); //pivot point
void rightRotate(Node **nodePtr);
void leftRightRotate(Node **nodePtr);
void rightLeftRotate(Node **nodePtr);

#endif // Rotation_H
