#include <stdio.h>
#include "unity.h"
#include "Node.h"
#include "InitNode.h"
#include "Rotation.h"
#include "RedBlackTree.h"
#include "RestructureNode.h"
#include "CustomAssertions.h"
#include "ErrorCode.h"
#include "CException.h"

Node node1,node4,node5,node7,node8,node10,node12,node13,
      node15,node18,node20,node22,node30,node35,node40,node60;

void setUp(void){
	resetNode(&node1,1);
	resetNode(&node4,4);
  resetNode(&node5,5);
	resetNode(&node7,7);
  resetNode(&node8,8);
	resetNode(&node10,10);
	resetNode(&node12,12);
  resetNode(&node13,13);
	resetNode(&node15,15);
	resetNode(&node18,18);
  resetNode(&node20,20);
  resetNode(&node22,22);
  resetNode(&node30,30);
	resetNode(&node35,35);
  resetNode(&node40,40);
  resetNode(&node60,60);
}

void tearDown(void){}

/*****************************************

	1 NODE tests

*******************************************/
/**
*	root		root
*	 |    add 10	|
*	 v    ------>   v
*	NULL          10(b)
**/

void test_addRedBlackTree_add_10(void){
  setNode(&node10,NULL,NULL,'r');
  Node *root = NULL;

  addRedBlackTree(&root,&node10);
  TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',root);
}
/*****************************************

	2 NODE tests

*******************************************/

/**
*		root	       root
*		 |    add 5      |
*		 v   ------>	 v
*		10(b)          10(b)
*				/
*			      5(r)
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
*     		root	          root
*		 |    add 15       |
*		 v    ------>	   v
*		10(b)            10(b)
*			            \
*				   15(r)
**/

void test_addRedBlackTree_add_15_to_tree_with_root_10(void){
  setNode(&node10,NULL,NULL,'b');
  setNode(&node15,NULL,NULL,'r');
  Node *root = &node10;

  addRedBlackTree(&root,&node15);
 
  TEST_ASSERT_EQUAL_PTR(&node10,root);
  TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&node15);
  TEST_ASSERT_EQUAL_NODE(NULL,&node15,'b',root);
}

/*****************************************

	3 NODE tests

*******************************************/

/**
*		root		       root
*		 |    add 35 to 	|
*		 v    right node	v
*		20(b)  --------->     20(b)
*		/		      /   \
*	    15(r)		  15(r)  35(r)
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
*		root			       root
*		 |   add 1 to left node		|
*		 v    ----------------->  	v
*		10(b)                	      10(b)
*		  \			      /	\
*		  20(r)			  1(r)	20(r)
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
  TEST_ASSERT_EQUAL_NODE(&node1,&node20,'b',root);
}

/**
*	  root	         root 		     root
*	   |	add 1(r)  |   		      |
*	   v    ------->  v    	Right rotate  v
*	 10(b)          10(b)   at 10	     5(b)
*	 /	        /	---------->  /  \
*      5(r)	     5(r)		  1(r)	10(r)
*		     /
*		   1(r)
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
  TEST_ASSERT_EQUAL_NODE(&node1,&node10,'b',root);
}

/**
*	root		root 		          root
*	 |    add 35(r)  |   		            |
*	 v    -------->  v       Left rotate 	    v
*	10(b)           10(b)     at 10		  15(b)
*	  \	          \     ---------->       /  \
*	  15(r)	         15(r)		     10(r) 35(r)
*			    \
*			   35(r)
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
  TEST_ASSERT_EQUAL_NODE(&node10,&node35,'b',root);
}

/**
*	root		 root 		   	root
*         |     add 8(r)  |   		          |
*         v    -------->  v    LeftRight rotate   v
*	10(b)           10(b)  at 10(b)		 8(b)
*	/		 /     --------------->  / \
*    5(r)	       5(r)		      5(r) 10(r)
*		         \
*		        8(r)
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
  TEST_ASSERT_EQUAL_NODE(&node5,&node10,'b',root);
}

/**
*	root 			root		                   root
*	8(b)	         8(b)			      		  13(b)
*	  \		add 13 	  \     rightLeft Rotate      /  \
*	  20(r) ------>	20(r)	-----------------> 8(r)  20(r)
*	                 /
*      		        13(r)
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
  TEST_ASSERT_EQUAL_NODE(&node8,&node20,'b',root);
}

/*****************************************

	4 NODE tests

*******************************************/
/**
*		root	      root
*		 |    add 1 	|
*		 v    ----->    v
*		10(b)         10(r)
*		/  \	     /	  \
*	     5(r) 15(r)	  5(b)	15(b)
*                          /
*                        1(r)
**/
void test_addRedBlackTree_add_1_to_tree_with_root_5_10_15_nodes(void){
  setNode(&node1,NULL,NULL,'r');
  setNode(&node5,NULL,NULL,'r');
  setNode(&node15,NULL,NULL,'r');
  setNode(&node10,&node5,&node15,'b');
  Node *root = &node10;

  _addRedBlackTree(&root,&node1);
  TEST_ASSERT_EQUAL_PTR(&node10,root);
  TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&node1);
  TEST_ASSERT_EQUAL_NODE(&node1,NULL,'b',&node5);
  TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node15);
  TEST_ASSERT_EQUAL_NODE(&node5,&node15,'r',root);
}

/**
*		root	      root
*		 |    add 7 	|
*		 v    ----->    v
*		10(b)        10(r)
*		/  \	     /	  \
*	     5(r) 15(r)	   5(b)	15(b)
*                             \
*                             7(r)
**/
void test_addRedBlackTree_add_7_to_tree_with_root_5_10_15_nodes(void){
  setNode(&node7,NULL,NULL,'r');
  setNode(&node5,NULL,NULL,'r');
  setNode(&node15,NULL,NULL,'r');
  setNode(&node10,&node5,&node15,'b');
  Node *root = &node10;

  _addRedBlackTree(&root,&node7);
  TEST_ASSERT_EQUAL_PTR(&node10,root);
  TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&node7);
  TEST_ASSERT_EQUAL_NODE(NULL,&node7,'b',&node5);
  TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node15);
  TEST_ASSERT_EQUAL_NODE(&node5,&node15,'r',root);
}

/**
*		root	      root
*		 |    add 12 	|
*		 v    ----->    v
*		10(b)         10(r)
*		/  \	      /	  \
*	     5(r) 15(r)	   5(b)	15(b)
*                           /
*                        12(r)
**/
void test_addRedBlackTree_add_12_to_tree_with_root_5_10_15_nodes(void){
  setNode(&node12,NULL,NULL,'r');
  setNode(&node5,NULL,NULL,'r');
  setNode(&node15,NULL,NULL,'r');
  setNode(&node10,&node5,&node15,'b');
  Node *root = &node10;

  _addRedBlackTree(&root,&node12);
  TEST_ASSERT_EQUAL_PTR(&node10,root);
  TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&node12);
  TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node5);
  TEST_ASSERT_EQUAL_NODE(&node12,NULL,'b',&node15);
  TEST_ASSERT_EQUAL_NODE(&node5,&node15,'r',root);
}

/**
*		root	       root
*		 |    add 18 	|
*		 v    ----->    v
*		10(b)         10(r)
*		/  \	      /	  \
*	     5(r) 15(r)	   5(b)	15(b)
*                             \
*                           18(r)
**/
void test_addRedBlackTree_add_18_to_tree_with_root_5_10_15_nodes(void){
  setNode(&node18,NULL,NULL,'r');
  setNode(&node5,NULL,NULL,'r');
  setNode(&node15,NULL,NULL,'r');
  setNode(&node10,&node5,&node15,'b');
  Node *root = &node10;

  _addRedBlackTree(&root,&node18);
  TEST_ASSERT_EQUAL_PTR(&node10,root);
  TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&node18);
  TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node5);
  TEST_ASSERT_EQUAL_NODE(NULL,&node18,'b',&node15);
  TEST_ASSERT_EQUAL_NODE(&node5,&node15,'r',root);
}

/**
*	   	root			 root                    root
*		  |		 	  |                       |
*		  v                       v                       v
*		 20(b)                   20(b)                    20(b)
*		/     \	    add 7       /   \        flip         /  \
*	     10(b) 22(b)  ------->     10(b) 22(b) color       10(r) 22(b)
*            /  \                      / \          ------->    /  \
*         5(r) 15(r)              5(r)  15(r)               5(b)  15(b)
*            			    \                         \
*            		           7(r)                      7(r)
**/
void test_addRedBlackTree_add_7_to_tree_with_root_5_10_15_20_22_nodes(void){
  setNode(&node7,NULL,NULL,'r');
  setNode(&node5,NULL,NULL,'r');
  setNode(&node15,NULL,NULL,'r');
  setNode(&node22,NULL,NULL,'b');
  setNode(&node10,&node5,&node15,'b');
  setNode(&node20,&node10,&node22,'b');
  Node *root = &node20;

  addRedBlackTree(&root,&node7);
  TEST_ASSERT_EQUAL_PTR(&node20,root);
  TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&node7);
  TEST_ASSERT_EQUAL_NODE(NULL,&node7,'b',&node5);
  TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node15);
  TEST_ASSERT_EQUAL_NODE(&node5,&node15,'r',&node10);
  TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node22);
  TEST_ASSERT_EQUAL_NODE(&node10,&node22,'b',root);
}

/**
*	   	   root			            root                         root
*		      |		 	              |                           |
*		      v                               v                           v
*		     20(b)                          20(b)                          20(b)
*		    /    \        add 7	            /	 \        flip         /       \
*	   	4(r)      40(r)	 ------->       4(r)	  40(r)    color     4(b)      40(b)
*   		/   \       / \                /  \       /  \     ------->  /  \        /   \
* 	1(b) 10(b) 30(b) 60(b)        1(b)  10(b) 30(b) 60(b)            1(b)  10(r)   30(b) 60(b)
*      	     / \                            / \                           /   \
*         5(r) 15(r)                    5(r)   15(r)                    5(b)   15(b)
*                                         \                                \
*                                        7(r)                              7(r)
**/
void test_addRedBlackTree_add_7_to_tree_with_root_1_4_5_10_15_20_30_40_60nodes(void){
  setNode(&node1,NULL,NULL,'b');
  setNode(&node5,NULL,NULL,'r');
  setNode(&node7,NULL,NULL,'r');
  setNode(&node15,NULL,NULL,'r');
  setNode(&node30,NULL,NULL,'b');
  setNode(&node60,NULL,NULL,'b');
  setNode(&node4,&node1,&node10,'r');
  setNode(&node10,&node5,&node15,'b');
  setNode(&node40,&node30,&node60,'r');
  setNode(&node20,&node4,&node40,'b');
  Node *root = &node20;

  addRedBlackTree(&root,&node7);
  TEST_ASSERT_EQUAL_PTR(&node20,root);
  TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&node7);
  TEST_ASSERT_EQUAL_NODE(NULL,&node7,'b',&node5);
  TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node15);
  TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node1);
  TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node30);
  TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node60);
  TEST_ASSERT_EQUAL_NODE(&node5,&node15,'r',&node10);
  TEST_ASSERT_EQUAL_NODE(&node1,&node10,'b',&node4);
  TEST_ASSERT_EQUAL_NODE(&node30,&node60,'b',&node40);

}

/*****************************************

	Error tests

*******************************************/

/**
*		root	         root
*		 |	add 10	  |
*		 v   ------>	 v
*		10(b)           10(b)
*				  \
*			        10(r) (Throw Error)
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



