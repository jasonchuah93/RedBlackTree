#include <stdio.h>
#include "unity.h"
#include "Node.h"
#include "InitNode.h"
#include "Rotation.h"
#include "RedBlackTree.h"
#include "CustomAssertions.h"

Node node5,node10,node15;

void setUp(void){}

void tearDown(void){}

/**
*		root			     root
*		 /		add 10		  /
*		 v      ------>	     v
*		NULL                10
**/

void test_addRedBlackTree_add_10(void){
	setNode(&node10,NULL,NULL,'r');
	Node *root = NULL;
	
	addRedBlackTree(&root,&node10);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node10);
}

/**
*		root			     root
*		 /		add 5		  /
*		 v      ------>	     v
*		10(b)               10(b)
*							/	
*							5(r)
**/

void test_addRedBlackTree_add_5_to_tree_with_root_10(void){
	setNode(&node10,NULL,NULL,'b');
	setNode(&node5,NULL,NULL,'r');
	Node *root = &node10;
	
	addRedBlackTree(&root,&node5);
	
	TEST_ASSERT_EQUAL_PTR(root,&node10);
	TEST_ASSERT_EQUAL_NODE(&node5,NULL,'b',&node10);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&node5);
}

/**
*		root			     root
*		 /		add 15		  /
*		 v      ------>	     v
*		10(b)               10(b)
*							 \	
*							 15(r)
**/

void xtest_addRedBlackTree_add_15_to_tree_with_root_10(void){
	setNode(&node10,NULL,NULL,'b');
	setNode(&node15,NULL,NULL,'r');
	Node *root = &node10;
	
	addRedBlackTree(&root,&node15);
	
	TEST_ASSERT_EQUAL_PTR(root,&node10);
	TEST_ASSERT_EQUAL_NODE(NULL,&node15,'b',&node10);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&node15);
}