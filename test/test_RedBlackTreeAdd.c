#include <stdio.h>
#include "unity.h"
#include "Node.h"
#include "InitNode.h"
#include "Rotation.h"
#include "RedBlackTree.h"
#include "CustomAssertions.h"
#include "ErrorCode.h"
#include "CException.h"

Node node1,node5,node8,node10,node13,node15,node20,node35;

void setUp(void){
	resetNode(&node1,1);
	resetNode(&node5,5);
	resetNode(&node8,8);
	resetNode(&node10,10);
	resetNode(&node13,13);
	resetNode(&node15,15);
	resetNode(&node20,20);
	resetNode(&node35,35);
}

void tearDown(void){}

/*****************************************

	1 NODE tests
	
*******************************************/

/**
*		root			     root
*		 |		add 10		  |
*		 v      ------>	      v
*		NULL                 10(b)
**/

void test_addRedBlackTree_add_10(void){
	setNode(&node10,NULL,NULL,'r');
	Node *root = NULL;
	
	addRedBlackTree(&root,&node10);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node10);
}

/*****************************************

	2 NODE tests
	
*******************************************/

/**
*		root			     root
*		 |		add 5		  |
*		 v      ------>	      v
*		10(b)               10(b)
*							/	
*						  5(r)
**/

void test_addRedBlackTree_add_5_to_tree_with_root_10(void){
	setNode(&node10,NULL,NULL,'b');
	setNode(&node5,NULL,NULL,'r');
	Node *root = &node10;
	
	addRedBlackTree(&root,&node5);
	
	TEST_ASSERT_EQUAL_PTR(&node10,root);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&node5);
	TEST_ASSERT_EQUAL_NODE(&node5,NULL,'b',root);
}

/**
*		root			     root
*		 |		add 15		  |
*		 v      ------>	      v
*		10(b)                10(b)
*							   \	
*							   15(r)
**/

void test_addRedBlackTree_add_15_to_tree_with_root_10(void){
	setNode(&node10,NULL,NULL,'b');
	setNode(&node15,NULL,NULL,'r');
	Node *root = &node10;
	
	addRedBlackTree(&root,&node15);
	
	TEST_ASSERT_EQUAL_PTR(&node10,root);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&node15);
	TEST_ASSERT_EQUAL_NODE(NULL,&node15,'b',&node10);
}

/*****************************************

	3 NODE tests
	
*******************************************/

/**
*		root			         root
*		 |		add 35 to 		  |
*		 v      right node	      v
*		20(b)    -------->        20(b)
*		/						 /  \	
*	15(r)					  15(r)  35(r)
**/

void test_addRedBlackTree_add_35_to_tree_with_root_20(void){
	setNode(&node20,&node15,NULL,'b');
	setNode(&node15,NULL,NULL,'r');
	setNode(&node35,NULL,NULL,'r');
	Node *root = &node20;
	
	addRedBlackTree(&root,&node35);
	
	TEST_ASSERT_EQUAL_PTR(&node20,root);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&node15);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&node35);
	TEST_ASSERT_EQUAL_NODE(&node15,&node35,'b',root);
}

/**
*		root			            	root
*		 |		add 1 to left node		  |
*		 v      ----------------->	      v
*		10(b)                			10(b)
*		  \					   			/	\	
*		  20(r)					   	1(r)	20(r)
**/

void test_addRedBlackTree_add_1_to_tree_with_root_10(void){
	setNode(&node10,NULL,&node20,'b');
	setNode(&node1,NULL,NULL,'r');
	setNode(&node20,NULL,NULL,'r');
	Node *root = &node10;
	
	addRedBlackTree(&root,&node1);
	
	TEST_ASSERT_EQUAL_PTR(&node10,root);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&node1);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&node20);
	TEST_ASSERT_EQUAL_NODE(&node1,&node20,'b',&node10);
}

/**
*		root			   root 				        root
*		 |		add 1(r)     |   				  		 |
*		 v      ------> 	 v     Right rotate 	     v
*		10(b)               10(b)     at 10				5(b)
*	    /					/		---------->			/  \
*	  5(r)			     5(r)			     		1(r)	10(r)
*						 /
*					  1(r)
**/

void test_addRedBlackTree_add_1_to_tree_with_root_10_and_rightRotate(void){
	setNode(&node1,NULL,NULL,'r');
	setNode(&node5,NULL,NULL,'r');
	setNode(&node10,&node5,NULL,'b');
	Node *root = &node10;
	addRedBlackTree(&root,&node1);
	TEST_ASSERT_EQUAL_PTR(&node5,root);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&node1);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&node10);
	TEST_ASSERT_EQUAL_NODE(&node1,&node10,'b',&node5);
}

/**
*		root			   root 				        root
*		 |		add 35(r)     |   				  		 |
*		 v      ------> 	 v     Left rotate 	     v
*		10(b)               10(b)     at 10				15(b)
*	      \					  \		---------->			/  \
*	     15(r)			      15(r)			     	10(r)	35(r)
*						 		\
*					  			35(r)
**/

void test_addRedBlackTree_add_35_to_tree_with_root_10_and_leftRotate(void){
	setNode(&node35,NULL,NULL,'r');
	setNode(&node15,NULL,NULL,'r');
	setNode(&node10,NULL,&node15,'b');
	Node *root = &node10;
	addRedBlackTree(&root,&node35);
	TEST_ASSERT_EQUAL_PTR(&node15,root);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&node10);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&node35);
	TEST_ASSERT_EQUAL_NODE(&node10,&node35,'b',&node15);
}

/**
*		root			   root 				        root
*		 |		add 8(r)     |   				  		  |
*		 v      ------> 	 v     LeftRight rotate 	  v
*		10(b)               10(b)     at 10(b)			  8(b)
*	    /					/		---------->			 / \  
*	  5(r)			      5(r)			     		  5(r) 10(r)	
*						   \						
*						  8(r)					  
**/

void test_addRedBlackTree_add_8_to_tree_with_root_10_and_leftRightRotate(void){
	setNode(&node8,NULL,NULL,'r');
	setNode(&node5,NULL,NULL,'r');
	setNode(&node10,&node5,NULL,'b');
	Node *root = &node10;
	
	addRedBlackTree(&root,&node8);
	TEST_ASSERT_EQUAL_PTR(&node8,root);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&node5);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&node10);
	TEST_ASSERT_EQUAL_NODE(&node5,&node10,'b',&node8);
}

/**
*		root 					root		        			root
*		8(b)					8(b)					   	    13(b)
*	      \		add 13 			  \      rightLeft Rotate	    /  \
*	      20(r) ------->		 20(r)	 --------------->	8(r)  20(r)
*	     						/		            
*      						 13(r) 		 	       
**/

void test_addRedBlackTree_add_13_to_tree_with_root_8_and_rightLeftRotate(void){
	setNode(&node20,NULL,NULL,'r');
	setNode(&node13,NULL,NULL,'r');
	setNode(&node8,NULL,&node20,'b');
	Node *root = &node8;
	
	addRedBlackTree(&root,&node13);
	TEST_ASSERT_EQUAL_PTR(&node13,root);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&node8);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&node20);
	TEST_ASSERT_EQUAL_NODE(&node8,&node20,'b',&node13);
}

/*****************************************

	4 NODE tests
	
*******************************************/



/*****************************************

	Error tests
	
*******************************************/

/**
*		root			     root
*		 |		add 10		  |
*		 v      ------>	      v
*		10(b)               10(b)
*							  \	
*							 10(r) (Throw Error)
**/

void test_addRedBlackTree_add_10_to_tree_with_root_10_should_throw_equivalent_error(void){
	setNode(&node10,NULL,NULL,'b');
	setNode(&node10,NULL,NULL,'r');
	Node *root = &node10;
	
	ErrorCode e;
	
	Try
	{
		addRedBlackTree(&root,&node10);
		TEST_FAIL_MESSAGE("Should throw equivalent error ");
	}
	Catch(e)
	{
		TEST_ASSERT_EQUAL(ERR_EQUIVALENT_NODE ,e);
	}
}

