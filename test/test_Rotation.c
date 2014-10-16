#include <stdio.h>
#include "unity.h"
#include "Node.h"
#include "InitNode.h"
#include "Rotation.h"

Node node1,node3,node5,node6,node7,node8,node10,node13,node15,node20,node25,node30;

void setUp(void){
	resetNode(&node1,1);
	resetNode(&node3,3);
	resetNode(&node5,5);
	resetNode(&node6,6);
	resetNode(&node7,7);
	resetNode(&node8,8);
	resetNode(&node10,10);
	resetNode(&node13,13);
	resetNode(&node15,15);
	resetNode(&node20,20);
	resetNode(&node25,25);
	resetNode(&node30,30);
}
void tearDown(void){}

/****************************************
Right Rotate

*****************************************/
/**
*		root			root
*		 /				  /
*		10			 	 /
*		/				5
*	  5		--->	   / \
*	/				  1   10
*  1
**/
                             
void test_right_rotate_3_nodes(void){
	setNode(&node1,NULL,NULL,'b');
	setNode(&node5,&node1,NULL,'b');
	setNode(&node10,&node5,NULL,'b');
	Node *root = &node10;
	
	rightRotate(&root);
	TEST_ASSERT_EQUAL_PTR(node1.left,NULL);
	TEST_ASSERT_EQUAL_PTR(node1.right,NULL);
	TEST_ASSERT_EQUAL_PTR(node10.left,NULL);
	TEST_ASSERT_EQUAL_PTR(node10.right,NULL);
	TEST_ASSERT_EQUAL_PTR(node5.left,&node1);
	TEST_ASSERT_EQUAL_PTR(node5.right,&node10);
	TEST_ASSERT_EQUAL_PTR(root,&node5);
}

/**
*		root			root
*		 /				  /
*		10			 	 /
*		/ \				5
*	  5	   15 --->	   / \
*	/				  1   10
*  1					   \
*						    15	
**/
                             
void test_right_rotate_4_nodes(void){
	setNode(&node1,NULL,NULL,'b');
	setNode(&node15,NULL,NULL,'b');
	setNode(&node5,&node1,NULL,'b');
	setNode(&node10,&node5,&node15,'b');
	Node *root = &node10;
	
	rightRotate(&root);
	TEST_ASSERT_EQUAL_PTR(node1.left,NULL);
	TEST_ASSERT_EQUAL_PTR(node1.right,NULL);
	TEST_ASSERT_EQUAL_PTR(node15.left,NULL);
	TEST_ASSERT_EQUAL_PTR(node15.right,NULL);
	TEST_ASSERT_EQUAL_PTR(node10.left,NULL);
	TEST_ASSERT_EQUAL_PTR(node10.right,&node15);
	TEST_ASSERT_EQUAL_PTR(node5.left,&node1);
	TEST_ASSERT_EQUAL_PTR(node5.right,&node10);
	TEST_ASSERT_EQUAL_PTR(root,&node5);
}

/**
*		root			root
*		 /				  /
*		20			 	 /
*		/ \				10
*	  10  30 --->	   /  \
*	/	\			   1  20
*  1	15				 /  \
*						15	30					    	
**/
                             
void test_right_rotate_5_nodes(void){
	setNode(&node1,NULL,NULL,'b');
	setNode(&node15,NULL,NULL,'b');
	setNode(&node30,NULL,NULL,'b');
	setNode(&node10,&node1,&node15,'b');
	setNode(&node20,&node10,&node30,'b');
	Node *root = &node20;
	
	rightRotate(&root);
	TEST_ASSERT_EQUAL_PTR(node1.left,NULL);
	TEST_ASSERT_EQUAL_PTR(node1.right,NULL);
	TEST_ASSERT_EQUAL_PTR(node15.left,NULL);
	TEST_ASSERT_EQUAL_PTR(node15.right,NULL);
	TEST_ASSERT_EQUAL_PTR(node30.left,NULL);
	TEST_ASSERT_EQUAL_PTR(node30.right,NULL);
	TEST_ASSERT_EQUAL_PTR(node10.left,&node1);
	TEST_ASSERT_EQUAL_PTR(node10.right,&node20);
	TEST_ASSERT_EQUAL_PTR(node20.left,&node15);
	TEST_ASSERT_EQUAL_PTR(node20.right,&node30);
	TEST_ASSERT_EQUAL_PTR(root,&node10);
}

/****************************************	
	Left Rotate

*****************************************/

/**
*		root			root
*		 /				  /
*		10			 	 /
*		  \			 	15
*			15 	--->   / \
*			 \		  10  20
*             20
**/
                             
void test_left_rotate_3_nodes(void){
	setNode(&node20,NULL,NULL,'b');
	setNode(&node15,NULL,&node20,'b');
	setNode(&node10,NULL,&node15,'b');
	Node *root = &node10;
	
	leftRotate(&root);
	TEST_ASSERT_EQUAL_PTR(node20.left,NULL);
	TEST_ASSERT_EQUAL_PTR(node20.right,NULL);
	TEST_ASSERT_EQUAL_PTR(node10.left,NULL);
	TEST_ASSERT_EQUAL_PTR(node10.right,NULL);
	TEST_ASSERT_EQUAL_PTR(node15.left,&node10);
	TEST_ASSERT_EQUAL_PTR(node15.right,&node20);
	TEST_ASSERT_EQUAL_PTR(root,&node15);
}

/**
*		root			root
*		 /				  /
*		10			 	 /
*	    /  \			15
*	   5	15 	--->   / \
*			 \		  10 20
*             20	  /	  
*					5
**/
                             
void test_left_rotate_4_nodes(void){
	setNode(&node5,NULL,NULL,'b');
	setNode(&node20,NULL,NULL,'b');
	setNode(&node15,NULL,&node20,'b');
	setNode(&node10,&node5,&node15,'b');
	Node *root = &node10;
	
	leftRotate(&root);
	TEST_ASSERT_EQUAL_PTR(node5.left,NULL);
	TEST_ASSERT_EQUAL_PTR(node5.right,NULL);
	TEST_ASSERT_EQUAL_PTR(node20.left,NULL);
	TEST_ASSERT_EQUAL_PTR(node20.right,NULL);
	TEST_ASSERT_EQUAL_PTR(node10.left,&node5);
	TEST_ASSERT_EQUAL_PTR(node10.right,NULL);
	TEST_ASSERT_EQUAL_PTR(node15.left,&node10);
	TEST_ASSERT_EQUAL_PTR(node15.right,&node20);
	TEST_ASSERT_EQUAL_PTR(root,&node15);
}

/**
*		root			root
*		 /				  /
*		10			 	 /
*	    /  \			15
*	   5	15 	--->   /  \
*			/ \		  10  20
*          13  20	  /	\  
*					5	13
**/
                             
void test_left_rotate_5_nodes(void){
	
	setNode(&node5,NULL,NULL,'b');
	setNode(&node13,NULL,NULL,'b');
	setNode(&node20,NULL,NULL,'b');
	setNode(&node15,&node13,&node20,'b');
	setNode(&node10,&node5,&node15,'b');
	Node *root = &node10;
	
	leftRotate(&root);
	TEST_ASSERT_EQUAL_PTR(node5.left,NULL);
	TEST_ASSERT_EQUAL_PTR(node5.right,NULL);
	TEST_ASSERT_EQUAL_PTR(node20.left,NULL);
	TEST_ASSERT_EQUAL_PTR(node20.right,NULL);
	TEST_ASSERT_EQUAL_PTR(node13.left,NULL);
	TEST_ASSERT_EQUAL_PTR(node13.right,NULL);
	TEST_ASSERT_EQUAL_PTR(node10.left,&node5);
	TEST_ASSERT_EQUAL_PTR(node10.right,&node13);
	TEST_ASSERT_EQUAL_PTR(node15.left,&node10);
	TEST_ASSERT_EQUAL_PTR(node15.right,&node20);
	TEST_ASSERT_EQUAL_PTR(root,&node15);
}

/****************************************
 Left Right Rotate

*****************************************/

/**
*		root		root	 root
*		10			10		   7
*	    /    -->	/	-->	  /	\
*	  5				7		5	10
*	   \			/
*      7 			5
**/

void test_leftRight_rotate_3_nodes(void){
	setNode(&node7,NULL,NULL,'b');
	setNode(&node5,NULL,&node7,'b');
	setNode(&node10,&node5,NULL,'b');
	Node *root = &node10;
	
	leftRightRotate(&root);
	TEST_ASSERT_EQUAL_PTR(node5.left,NULL);
	TEST_ASSERT_EQUAL_PTR(node5.right,NULL);
	TEST_ASSERT_EQUAL_PTR(node10.left,NULL);
	TEST_ASSERT_EQUAL_PTR(node10.right,NULL);
	TEST_ASSERT_EQUAL_PTR(node7.left,&node5);
	TEST_ASSERT_EQUAL_PTR(node7.right,&node10);
	TEST_ASSERT_EQUAL_PTR(root,&node7);
}

/**
*		root		root	 root
*		10			10		   7
*	    /    -->	/	-->	  /	\
*	  5			   7		5	10
*	 / \		  /        /
*   1  7 		 5        1
*				/
*              1
**/

void test_leftRight_rotate_4_nodes(void){
	setNode(&node1,NULL,NULL,'b');
	setNode(&node7,NULL,NULL,'b');
	setNode(&node5,&node1,&node7,'b');
	setNode(&node10,&node5,NULL,'b');
	Node *root = &node10;
	
	leftRightRotate(&root);
	TEST_ASSERT_EQUAL_PTR(node1.left,NULL);
	TEST_ASSERT_EQUAL_PTR(node1.right,NULL);
	TEST_ASSERT_EQUAL_PTR(node10.left,NULL);
	TEST_ASSERT_EQUAL_PTR(node10.right,NULL);
	TEST_ASSERT_EQUAL_PTR(node5.left,&node1);
	TEST_ASSERT_EQUAL_PTR(node5.right,NULL);
	TEST_ASSERT_EQUAL_PTR(node7.left,&node5);
	TEST_ASSERT_EQUAL_PTR(node7.right,&node10);
	TEST_ASSERT_EQUAL_PTR(root,&node7);
}

/**
*		root		root	 	root
*		10			10		   	  7
*	    / \   -->	/ \	-->	     /	\
*	  5	  15	   7  15	   5	 10
*	 / \		  / \        /       / \
*   1  7 		 5   8      1		8  15
*		\		/
*        8      1
**/

void test_leftRight_rotate_6_nodes(void){
	setNode(&node8,NULL,NULL,'b');
	setNode(&node1,NULL,NULL,'b');
	setNode(&node15,NULL,NULL,'b');
	setNode(&node7,NULL,&node8,'b');
	setNode(&node5,&node1,&node7,'b');
	setNode(&node10,&node5,&node15,'b');
	Node *root = &node10;
	
	leftRightRotate(&root);
	TEST_ASSERT_EQUAL_PTR(node1.left,NULL);
	TEST_ASSERT_EQUAL_PTR(node1.right,NULL);
	TEST_ASSERT_EQUAL_PTR(node8.left,NULL);
	TEST_ASSERT_EQUAL_PTR(node8.right,NULL);
	TEST_ASSERT_EQUAL_PTR(node15.left,NULL);
	TEST_ASSERT_EQUAL_PTR(node15.right,NULL);
	TEST_ASSERT_EQUAL_PTR(node10.left,&node8);
	TEST_ASSERT_EQUAL_PTR(node10.right,&node15);
	TEST_ASSERT_EQUAL_PTR(node5.left,&node1);
	TEST_ASSERT_EQUAL_PTR(node5.right,NULL);
	TEST_ASSERT_EQUAL_PTR(node7.left,&node5);
	TEST_ASSERT_EQUAL_PTR(node7.right,&node10);
	TEST_ASSERT_EQUAL_PTR(root,&node7);
}

/**
*		root		root	 	root
*		10			10		   	  7
*	    / \   -->	/ \	 -->	 /	\
*	  5	  15	   7  15	   5	 10
*	 / \	\	  / \   \      / \    / \
*   1  7 	30	 5   8  30   1	6	8  15
*	  /	\		/ \						\
*    6   8     1  6						30
**/

void test_leftRight_rotate_8_nodes(void){
	setNode(&node6,NULL,NULL,'b');
	setNode(&node8,NULL,NULL,'b');
	setNode(&node1,NULL,NULL,'b');
	setNode(&node30,NULL,NULL,'b');
	setNode(&node15,NULL,&node30,'b');
	setNode(&node7,&node6,&node8,'b');
	setNode(&node5,&node1,&node7,'b');
	setNode(&node10,&node5,&node15,'b');
	Node *root = &node10;
	
	leftRightRotate(&root);
	TEST_ASSERT_EQUAL_PTR(node1.left,NULL);
	TEST_ASSERT_EQUAL_PTR(node1.right,NULL);
	TEST_ASSERT_EQUAL_PTR(node8.left,NULL);
	TEST_ASSERT_EQUAL_PTR(node8.right,NULL);
	TEST_ASSERT_EQUAL_PTR(node6.left,NULL);
	TEST_ASSERT_EQUAL_PTR(node6.right,NULL);
	TEST_ASSERT_EQUAL_PTR(node30.left,NULL);
	TEST_ASSERT_EQUAL_PTR(node30.right,NULL);
	TEST_ASSERT_EQUAL_PTR(node15.left,NULL);
	TEST_ASSERT_EQUAL_PTR(node15.right,&node30);
	TEST_ASSERT_EQUAL_PTR(node5.left,&node1);
	TEST_ASSERT_EQUAL_PTR(node5.right,&node6);
	TEST_ASSERT_EQUAL_PTR(node10.left,&node8);
	TEST_ASSERT_EQUAL_PTR(node10.right,&node15);
	TEST_ASSERT_EQUAL_PTR(node7.left,&node5);
	TEST_ASSERT_EQUAL_PTR(node7.right,&node10);
	TEST_ASSERT_EQUAL_PTR(root,&node7);
}

/****************************************
 Right Left Rotate

*****************************************/

/**
*		root		root	 root
*		15			15		   13
*	     \     -->	 \	-->	  /	 \
*	     20	       	  13     15  20
*	    /		       \
*      13 		 	    20
**/

void test_rightLeft_rotate_3_nodes(void){
	setNode(&node13,NULL,NULL,'b');
	setNode(&node20,&node13,NULL,'b');
	setNode(&node15,NULL,&node20,'b');
	Node *root = &node15;
	
	rightLeftRotate(&root);
	TEST_ASSERT_EQUAL_PTR(node15.left,NULL);
	TEST_ASSERT_EQUAL_PTR(node15.right,NULL);
	TEST_ASSERT_EQUAL_PTR(node20.left,NULL);
	TEST_ASSERT_EQUAL_PTR(node20.right,NULL);
	TEST_ASSERT_EQUAL_PTR(node13.left,&node15);
	TEST_ASSERT_EQUAL_PTR(node13.right,&node20);
	TEST_ASSERT_EQUAL_PTR(root,&node13);
}

/**
*		root		root	  root
*		15			15		   	   13
*	    / \     -->	 \	-->	  	  /	 \
*	  10  20	      13    	15   20
*	     /		      / \	    /
*      13 		 	 10  20	   10
**/

void test_rightLeft_rotate_4_nodes(void){
	setNode(&node13,NULL,NULL,'b');
	setNode(&node10,NULL,NULL,'b');
	setNode(&node20,&node13,NULL,'b');
	setNode(&node15,&node10,&node20,'b');
	Node *root = &node15;
	
	rightLeftRotate(&root);
	TEST_ASSERT_EQUAL_PTR(node10.left,NULL);
	TEST_ASSERT_EQUAL_PTR(node10.right,NULL);
	TEST_ASSERT_EQUAL_PTR(node15.left,&node10);
	TEST_ASSERT_EQUAL_PTR(node15.right,NULL);
	TEST_ASSERT_EQUAL_PTR(node20.left,NULL);
	TEST_ASSERT_EQUAL_PTR(node20.right,NULL);
	TEST_ASSERT_EQUAL_PTR(node13.left,&node15);
	TEST_ASSERT_EQUAL_PTR(node13.right,&node20);
	TEST_ASSERT_EQUAL_PTR(root,&node13);
}

/**
*		root		root	      root
*		15			15		   	   13
*	    / \     -->	/ \	-->	  	  /	 \
*	  10  20	   10  13    	15   20
*	  /   / \	   /    \	    /     \    
*    5   13  30	   5    20	   10     30
*                        \     /
*                        30   5
**/

void test_rightLeft_rotate_6_nodes(void){
	setNode(&node13,NULL,NULL,'b');
	setNode(&node5,NULL,NULL,'b');
	setNode(&node30,NULL,NULL,'b');
	setNode(&node10,&node5,NULL,'b');
	setNode(&node20,&node13,&node30,'b');
	setNode(&node15,&node10,&node20,'b');
	Node *root = &node15;
	
	rightLeftRotate(&root);
	TEST_ASSERT_EQUAL_PTR(node5.left,NULL);
	TEST_ASSERT_EQUAL_PTR(node5.right,NULL);
	TEST_ASSERT_EQUAL_PTR(node30.left,NULL);
	TEST_ASSERT_EQUAL_PTR(node30.right,NULL);
	TEST_ASSERT_EQUAL_PTR(node10.left,&node5);
	TEST_ASSERT_EQUAL_PTR(node10.right,NULL);
	TEST_ASSERT_EQUAL_PTR(node15.left,&node10);
	TEST_ASSERT_EQUAL_PTR(node15.right,NULL);
	TEST_ASSERT_EQUAL_PTR(node20.left,NULL);
	TEST_ASSERT_EQUAL_PTR(node20.right,&node30);
	TEST_ASSERT_EQUAL_PTR(node13.left,&node15);
	TEST_ASSERT_EQUAL_PTR(node13.right,&node20);
	TEST_ASSERT_EQUAL_PTR(root,&node13);
}

/*******************************************************************************************************************************************/
void changeRootByVal(Node *node,Node *newNode){
	node = newNode;
	printf("changeRootByVal:node =%x\n",node);
}

void changeRootByRef(Node **nodePtr,Node *newNode){
	*nodePtr = newNode;
	printf("changeRootByRef:node =%x\n",*nodePtr);
}

void test_changeRootByVal(){
	Node *root;
	root = &node10;
	
	printf("change root by val \n");
	printf("root is node %d with address %x\n",root->data,root);
	changeRootByVal(root,&node5);
	printf("new root is node %d with address %x\n",root->data,root);
}

void test_changeRootByRef(){
	Node *root;
	root = &node10;
	
	printf("change root by ref \n");
	printf("root is node %d with address %x\n",root->data,root);
	changeRootByRef(&root,&node5);
	printf("new root is node %d with address %x\n",root->data,root);
}

