#include <stdio.h>
#include "unity.h"
#include "Node.h"
#include "InitNode.h"
#include "Rotation.h"
#include "RedBlackTree.h"
#include "CustomAssertions.h"
#include "ErrorCode.h"
#include "CException.h"

Node node1,node2,node4,node5,node7,node8,node10,node12,node13,
      node15,node18,node20,node22,node30,node35,node40,node60;

void setUp(void){
	resetNode(&node1,1);
	resetNode(&node2,2);
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
*	root		        root
*	 |    remove 1	  |
*	 v    -------->   v
*	1(b)             NULL
**/

void test_delRedBlackTree_remove_1_from_tree_with_root_1(void){
  setNode(&node1,NULL,NULL,'b');
  Node *root = &node1;

  delRedBlackTree(&root,&node1);
  TEST_ASSERT_EQUAL_PTR(NULL,root);
}

/**
*	root		        
*	 |    remove 2	  
*	 v    -------->  Throw ERR_NODE_UNAVAILABLE 
*	1(b)             
**/

void test_delRedBlackTree_remove_2_from_tree_with_root_1_should_throw_error(void){
  CEXCEPTION_T err;
  setNode(&node1,NULL,NULL,'b');
  Node *root = &node1;
  Try{
    delRedBlackTree(&root,&node2);
    TEST_FAIL_MESSAGE("Expected ERR_NODE_UNAVAILABLE to be thrown.But receive none");
  }Catch(err){
    TEST_ASSERT_EQUAL_PTR(root,&node1);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node1);
  }
}

/*****************************************

	2 NODE tests

*******************************************/
/**
*	    root		        root
*	    |    remove 1	    |
*	    v    -------->    v
*	    2(b)             2(b)
*    / 
*   1(r)
*
**/

void test_delRedBlackTree_remove_1_from_tree_with_root_2(void){
  setNode(&node1,NULL,NULL,'r');
  setNode(&node2,&node1,NULL,'b');
  Node *root = &node2;

  delRedBlackTree(&root,&node1);
  //TEST_ASSERT_EQUAL_PTR(root,&node2);
  //EST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node2);
}

