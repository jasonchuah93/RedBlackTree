#include <stdio.h>
#include "unity.h"
#include "Node.h"
#include "InitNode.h"
#include "Rotation.h"
#include "RedBlackTree.h"
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


