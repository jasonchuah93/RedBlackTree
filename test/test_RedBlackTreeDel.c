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

Node node1,node2,node4,node5,node7,node8,node9,node10,node12,node13,
      node15,node18,node20,node21,node22,node30,node35,node40,node60;

void setUp(void){
	resetNode(&node1,1);
	resetNode(&node2,2);
	resetNode(&node4,4);
	resetNode(&node5,5);
	resetNode(&node7,7);
	resetNode(&node8,8);	
	resetNode(&node9,9);
	resetNode(&node10,10);
	resetNode(&node12,12);
	resetNode(&node13,13);
	resetNode(&node15,15);
	resetNode(&node18,18);
	resetNode(&node20,20);
	resetNode(&node21,21);
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
*	root		         root
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

	2 height level tests

*******************************************/
/**
*	    root		 root
*	    |    remove 1	  |
*	    v    -------->        v
*	    2(b)                2(b)
*          /                     / \ 
*        1(r)                   -  -
*
**/

void test_delRedBlackTree_remove_1_from_tree_with_root_2(void){
  setNode(&node1,NULL,NULL,'r');
  setNode(&node2,&node1,NULL,'b');
  Node *root = &node2;

  delRedBlackTree(&root,&node1);
  TEST_ASSERT_EQUAL_PTR(root,&node2);
  TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node2);
}

/**
*	    root		     root
*	    |    remove 10	      |
*	    v    -------->            v
*	    2(b)                     2(b)
*            \                      / \
*            10(r)                 -   -
*	     / \
*           -   -
*
**/


void test_delRedBlackTree_remove_10_from_tree_with_root_2(void){
  setNode(&node10,NULL,NULL,'r');
  setNode(&node2,NULL,&node10,'b');
  Node *root = &node2;

  delRedBlackTree(&root,&node10);
  TEST_ASSERT_EQUAL_PTR(root,&node2);
  TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node2);
}

/**
*	
*
*	    root		     root
*	    |    remove 1	      |
*	    v    -------->            v
*	    2(b)                     2(b)
*          /  \			       \
*        1(r) 5(r)		      5(r)
*        / \  / \                      / \
*       -  -  -  -                    -   -
*
**/

void test_delRedBlackTree_remove_1_from_tree_with_nodes_1_2_5(void){
  setNode(&node1,NULL,NULL,'r');
  setNode(&node5,NULL,NULL,'r');
  setNode(&node2,&node1,&node5,'b');
  Node *root = &node2;
  
  delRedBlackTree(&root,&node1);
  TEST_ASSERT_EQUAL_PTR(root,&node2);
  TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&node5);
  TEST_ASSERT_EQUAL_NODE(NULL,&node5,'b',&node2);
}

/**
*	    root		     root
*	    |    remove 5	      |
*	    v    -------->            v
*	    2(b)                     2(b)
*          /  \			     /	
*       1(r) 5(r)		   1(r)	
*	 / \  / \                  / \
*       -  - -  -                 -   -
*
**/

void test_delRedBlackTree_remove_5_from_tree_with_nodes_1_2_5(void){
  setNode(&node1,NULL,NULL,'r');
  setNode(&node5,NULL,NULL,'r');
  setNode(&node2,&node1,&node5,'b');
  Node *root = &node2;
  
  delRedBlackTree(&root,&node5);
  TEST_ASSERT_EQUAL_PTR(root,&node2);
  TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&node1);
  TEST_ASSERT_EQUAL_NODE(&node1,NULL,'b',&node2);
}

/*****************************************

	3 height level tests

*******************************************/

/**
 *      root              root
 *       |    remove 5      |
 *       V   left rotate    V
 *      10(b) --------->   20(b)
 *     /   \              /   \
 *   5(b)  20(r)        10(b) 30(b)
 *   / \    /  \         / \    \
 *   -  -  15(b) 30(b)  -   -   15(r)
 *        / \  / \              / \
 *        -  -  - -             -   -
**/

void test_delRedBlackTree_remove_5_from_tree_and_left_rotate_with_nodes_10_15_20_30(void){
    setNode(&node5,NULL,NULL,'b');
    setNode(&node15,NULL,NULL,'b');
    setNode(&node30,NULL,NULL,'b');
    setNode(&node20,&node15,&node30,'r');
    setNode(&node10,&node5,&node20,'b');
    Node *root = &node10;
    delRedBlackTree(&root,&node5);
    TEST_ASSERT_EQUAL_PTR(root,&node20);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&node15);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node30);
    TEST_ASSERT_EQUAL_NODE(NULL,&node15,'b',&node10);
    TEST_ASSERT_EQUAL_NODE(&node10,&node30,'b',&node20);
}

/**
 *      root              root
 *       |    remove 20      |
 *       V   right rotate    V
 *      10(b) --------->   5(b)
 *     /   \               /  \
 *   5(r)   20(b)       1(b)  10(b) 
 *   / \    / \          / \   /
 *  1(b)8(b)-  -   	-  -  8(r)
 * / \ / \                   / \
 *-  - -  -                  -  -
**/

void test_delRedBlackTree_remove_20_from_tree_and_right_rotate_with_nodes_1_8_10_15_20(void){
    setNode(&node1,NULL,NULL,'b');
    setNode(&node8,NULL,NULL,'b');
    setNode(&node20,NULL,NULL,'b');
    setNode(&node5,&node1,&node8,'r');
    setNode(&node10,&node5,&node20,'b');
    
    Node *root = &node10;
    delRedBlackTree(&root,&node20);
    TEST_ASSERT_EQUAL_PTR(root,&node5);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node1);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&node8);
    TEST_ASSERT_EQUAL_NODE(&node8,NULL,'b',&node10);
    TEST_ASSERT_EQUAL_NODE(&node1,&node10,'b',&node5);
}

/**
 *      root              root
 *       |    remove 15     |
 *       V                  V
 *      10(b) --------->   10(b)
 *     /     \              /   \
 *   5(b)    20(r)        5(b) 20(b)
 *   / \      /  \        / \     \
 *  -  -    15(b) 30(b)  -  -     30(r)
 *          / \  / \              / \
 *         -  -  -  -            -   -
**/

void test_delRedBlackTree_remove_15_from_tree_with_nodes_5_10_20_30(void){
    setNode(&node5,NULL,NULL,'b');
    setNode(&node15,NULL,NULL,'b');
    setNode(&node30,NULL,NULL,'b');
    setNode(&node20,&node15,&node30,'r');
    setNode(&node10,&node5,&node20,'b');
    
    Node *root = &node10;
    delRedBlackTree(&root,&node15);
    TEST_ASSERT_EQUAL_PTR(root,&node10);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node5);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&node30);
    TEST_ASSERT_EQUAL_NODE(NULL,&node30,'b',&node20);
    TEST_ASSERT_EQUAL_NODE(&node5,&node20,'b',&node10);
}

/**
 *      root              root
 *       |    remove 30     |
 *       V                  V
 *      10(b) --------->   10(b)
 *     /   \              /   \
 *   5(b)  20(r)        5(b) 20(b)
 *   / \    /  \        / \   /  
 *  -  -  15(b) 30(b)  -  -  15(r)
 *        / \  / \          / \
 *       -  -  -  -        -  -
**/

void test_delRedBlackTree_remove_30_from_tree_with_nodes_5_10_15_20(void){
    setNode(&node5,NULL,NULL,'b');
    setNode(&node15,NULL,NULL,'b');
    setNode(&node30,NULL,NULL,'b');
    setNode(&node20,&node15,&node30,'r');
    setNode(&node10,&node5,&node20,'b');
    
    Node *root = &node10;
    delRedBlackTree(&root,&node30);
    TEST_ASSERT_EQUAL_PTR(root,&node10);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node5);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&node15);
    TEST_ASSERT_EQUAL_NODE(&node15,NULL,'b',&node20);
    TEST_ASSERT_EQUAL_NODE(&node5,&node20,'b',&node10);
}

/**
 *	
 *          root                root
 *           |    remove 1       |
 *           V                   V
 *         10(b) --------->     10(b)
 *        /    \                /    \
 *      5(r)    20(r)        5(b)     20(r)
 *      / \      /  \          \      /   \ 
 *    1(b) 8(b) 15(b)30(b)   8(r) 15(b) 30(b)
 *    / \ / \   / \ / \       / \   / \   / \ 
 *   -  - -  - -  - - -      -  -  -   -  -  -
**/

void test_delRedBlackTree_remove_1_from_tree_and_with_nodes_1_5_8_10_15_20_30(void){
    setNode(&node1,NULL,NULL,'b');
    setNode(&node8,NULL,NULL,'b');
    setNode(&node15,NULL,NULL,'b');
    setNode(&node30,NULL,NULL,'b');
    setNode(&node5,&node1,&node8,'r');
    setNode(&node20,&node15,&node30,'r');
    setNode(&node10,&node5,&node20,'b');
    
    Node *root = &node10;
    delRedBlackTree(&root,&node1);
    TEST_ASSERT_EQUAL_PTR(root,&node10);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&node8);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node15);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node30);
    TEST_ASSERT_EQUAL_NODE(NULL,&node8,'b',&node5);
    TEST_ASSERT_EQUAL_NODE(&node15,&node30,'r',&node20);
    TEST_ASSERT_EQUAL_NODE(&node5,&node20,'b',&node10);
}

/**
 *	
 *          root                root
 *           |    remove 8       |
 *           V                   V
 *          10(b) --------->     10(b)
 *        /    \                /    \
 *      5(r)    20(r)        5(b)     20(r)
 *      / \      /  \         /      /   \ 
 *    1(b) 8(b) 15(b)30(b) 1(r)    15(b) 30(b)
 *    / \ / \   / \ / \     / \    / \  / \
 *   -  - -  - -  - -  -   -  -   -  - -  -
**/

void test_delRedBlackTree_remove_8_from_tree_and_with_nodes_1_5_8_10_15_20_30(void){
    setNode(&node1,NULL,NULL,'b');
    setNode(&node8,NULL,NULL,'b');
    setNode(&node15,NULL,NULL,'b');
    setNode(&node30,NULL,NULL,'b');
    setNode(&node5,&node1,&node8,'r');
    setNode(&node20,&node15,&node30,'r');
    setNode(&node10,&node5,&node20,'b');
    
    Node *root = &node10;
    delRedBlackTree(&root,&node8);
    TEST_ASSERT_EQUAL_PTR(root,&node10);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&node1);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node15);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node30);
    TEST_ASSERT_EQUAL_NODE(&node1,NULL,'b',&node5);
    TEST_ASSERT_EQUAL_NODE(&node15,&node30,'r',&node20);
    TEST_ASSERT_EQUAL_NODE(&node5,&node20,'b',&node10);
}

/**
 *	Improved delRedBlackTree function
 *       root                root
 *        |    remove 15       |
 *        V                   V
 *       10(b) --------->     10(b)
 *     /    \                /    \
 *   5(r)    20(r)        5(r)     20(b)
 *   / \      /  \         / \      \ 
 * 1(b) 8(b) 15(b)30(b) 1(b) 8(b)  30(r)
 * / \ / \   / \   / \   / \ / \   / \
 * -  - -  - -  -  -  - -  - -  -  -  -
**/

void test_delRedBlackTree_remove_15_from_tree_and_with_nodes_1_5_8_10_15_20_30(void){
    setNode(&node1,NULL,NULL,'b');
    setNode(&node8,NULL,NULL,'b');
    setNode(&node15,NULL,NULL,'b');
    setNode(&node30,NULL,NULL,'b');
    setNode(&node5,&node1,&node8,'r');
    setNode(&node20,&node15,&node30,'r');
    setNode(&node10,&node5,&node20,'b');
    
    Node *root = &node10;
    delRedBlackTree(&root,&node15);
    TEST_ASSERT_EQUAL_PTR(root,&node10);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node1);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node8);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&node30);
    TEST_ASSERT_EQUAL_NODE(&node1,&node8,'r',&node5);
    TEST_ASSERT_EQUAL_NODE(NULL,&node30,'b',&node20);
    TEST_ASSERT_EQUAL_NODE(&node5,&node20,'b',&node10);
}

/**
 *	Improved delRedBlackTree function
 *       root                root
 *        |    remove 30       |
 *        V                   V
 *       10(b) --------->     10(b)
 *     /    \                /    \
 *   5(r)    20(r)        5(r)     20(b)
 *   / \      /  \         /  \      /    
 * 1(b) 8(b) 15(b)30(b) 1(b)8(b) 15(r)
 *  / \ / \   / \ / \    / \  / \  / \
 * -  - -  - -  - -  -   -  - -  - -  -
**/

void test_delRedBlackTree_remove_30_from_tree_and_with_nodes_1_5_8_10_15_20_30(void){
    setNode(&node1,NULL,NULL,'b');
    setNode(&node8,NULL,NULL,'b');
    setNode(&node15,NULL,NULL,'b');
    setNode(&node30,NULL,NULL,'b');
    setNode(&node5,&node1,&node8,'r');
    setNode(&node20,&node15,&node30,'r');
    setNode(&node10,&node5,&node20,'b');
    
    Node *root = &node10;
    delRedBlackTree(&root,&node30);
    TEST_ASSERT_EQUAL_PTR(root,&node10);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node1);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node8);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&node15);
    TEST_ASSERT_EQUAL_NODE(&node1,&node8,'r',&node5);
    TEST_ASSERT_EQUAL_NODE(&node15,NULL,'b',&node20);
    TEST_ASSERT_EQUAL_NODE(&node5,&node20,'b',&node10);
}

/**
 *	Case(1b): Sibling is black and nephew is red
 *      root              		       root
 *       |       remove 5  			|
 *       V     rightLeft rotate 		V
 *      10(b) ----------------->   	      15(b)
 *     /   \              	              /   \
 *    5(b) 20(b)        		   10(b) 20(b)
 *    / \   /   			    / \  / \	                
 *   -  -  15(r)		           -  -  -  -
 *        / \
 *       -  -     
**/

void test_delRedBlackTree_using_rightLeftRotate_for_case_1b(void){
    setNode(&node5,NULL,NULL,'b');
    setNode(&node15,NULL,NULL,'r');
    setNode(&node20,&node15,NULL,'b');
	setNode(&node10,&node5,&node20,'b');
	
    Node *root=&node10;
    delRedBlackTree(&root,&node5);
    TEST_ASSERT_EQUAL_PTR(root,&node15);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node10);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node20);
    TEST_ASSERT_EQUAL_NODE(&node10,&node20,'b',&node15);
}

/**
 *	Case(1b): Sibling is black and nephew is red
 *       |        remove20		|
 *       V     leftRight rotate  	V
 *      10(b) ----------------->      9(b)
 *      /   \                	      /   \
 *     8(b)  20(b)        	    8(b) 10(b)
 *     	\                    	    / \   / \     
 *   	9(r)              	   -  -  -   - 
**/

void test_delRedBlackTree_using_leftRightRotate_for_case_1b(void){
    setNode(&node9,NULL,NULL,'r');
    setNode(&node20,NULL,NULL,'b');
    setNode(&node8,NULL,&node9,'b');
    setNode(&node10,&node8,&node20,'b');
	
    Node *root=&node10;
    delRedBlackTree(&root,&node20);
    TEST_ASSERT_EQUAL_PTR(root,&node9);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node8);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node10);
    TEST_ASSERT_EQUAL_NODE(&node8,&node10,'b',&node9);
}

/**
 *	Case(3a): Sibling is red
 *	
 *       root             	   root					root				root
 *       |     remove 5   	     |					  |		                  |
 *       V       	             V	   leftRotate	                  V	   case 1		  V
 *      10(b) -------------- >     10(b) --------------->               15(b)     ------->  	        15(b)
 *      /   \                	  //   \			        /  \				/  \
 *    5(b)   15(r)               -    15(r)  		             10(r) 20(b)                    12(r) 20(b)
 *           / \                      /  \      	             /   \			    /  \
 *        12(b) 20(b)             12(b)  20(b)	                   -   12(b)		         10(b) 13(b)
 *      	 \		      \ 				   \	
 *      	 13(r)               13(r)				  13(r)
**/

void test_delRedBlackTree_for_case_3a_using_case1_leftRotate(void){
    setNode(&node5,NULL,NULL,'b');
    setNode(&node13,NULL,NULL,'r');
    setNode(&node20,NULL,NULL,'b');
    setNode(&node12,NULL,&node13,'b');
    setNode(&node15,&node12,&node20,'r');
    setNode(&node10,&node5,&node15,'b');
	
    Node *root=&node10;
    delRedBlackTree(&root,&node5);
    TEST_ASSERT_EQUAL_PTR(root,&node15);
    TEST_ASSERT_EQUAL_NODE(&node12,&node20,'b',&node15);
    TEST_ASSERT_EQUAL_NODE(&node10,&node13,'r',&node12);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node13);
}


/**
 *	Case(3b): Sibling is red
 *	
 *      root             	       root		         root
 *       |     remove 20   		|		          |
 *       V     rotate right      	V     case 2		  V
 *      10(b) ----------------->      8(b) ------------>        8(b)
 *      /   \                	     /   \		        / \
 *     8(r)  20(b)        	  5(r)  10(b)		     5(b) 10(b)
 *    /   \                    	    \      	      	          /
 *   5(b) 9(b)                     9(b) 	   	        9(r)
 *             
**/

void test_delRedBlackTree_for_case_3b_using_rotate_right(void){
    setNode(&node20,NULL,NULL,'b');
    setNode(&node5,NULL,NULL,'b');
    setNode(&node9,NULL,NULL,'b');
    setNode(&node8,&node5,&node9,'r');
    setNode(&node10,&node8,&node20,'b');
	
    Node *root=&node10;
    delRedBlackTree(&root,&node20);
    TEST_ASSERT_EQUAL_PTR(root,&node8);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&node9);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node5);
    TEST_ASSERT_EQUAL_NODE(&node9,NULL,'b',&node10);
    TEST_ASSERT_EQUAL_NODE(&node5,&node10,'b',&node8);
}

/**
 *	Case(3b): Sibling is red
 *	
 *      root                     root			 root
 *       |    remove 5    	   |	   use 	           |
 *       V     rotate left  	   V	   case 2          V
 *      10(b) ------------->     20(b)	  --------->	  20(b)
 *     /   \                     /   \                    / \		
 *    5(b) 20(r)              10(r)  30(b)	      10(b) 30(b)
 *        /  \                 /  \     		  \
 *     15(b) 30(b)           -   15(b)  	         15(r)
 */
void test_delRedBlackTree_for_case_3b_using_rotate_left(void){
    setNode(&node5,NULL,NULL,'b');
    setNode(&node15,NULL,NULL,'b');
    setNode(&node30,NULL,NULL,'b');
    setNode(&node20,&node15,&node30,'r');
    setNode(&node10,&node5,&node20,'b');
	
    Node *root=&node10;
    delRedBlackTree(&root,&node5);
    TEST_ASSERT_EQUAL_PTR(root,&node20);
    TEST_ASSERT_EQUAL_NODE(&node10,&node30,'b',&node20);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node30);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&node15);
    TEST_ASSERT_EQUAL_NODE(NULL,&node15,'b',&node10);
	
}

/**
 *	Case(3a): Sibling is red
 *	
 *       root             	   root			  root				 root
 *       |     remove 60             |			   |			          |	  
 *       V       	             V	  rightRotate	   V	    case 1	          V
 *      30(b) -------------- >     30(b) -------------->  20(b)    -------->            20(b)          
 *      /   \                	  /   \\	          /  \				 / \   
 *    20(r)  60(b)       	20(r)  -              15(b)  30(b)		     15(b) 22(r)
 *    /  \                      /  \      	     	    / 	  	   		   / \	
 *  15(b) 22(b)              15(b) 22(b)                   22(b)  			21(b) 30(b)
 *    	  /		           /		          /
 *    	21(r)			21(r)                   21(r)
 */
void test_delRedBlackTree_for_case_3a_using_case1_rightRotate(void){
    setNode(&node60,NULL,NULL,'b');
    setNode(&node21,NULL,NULL,'r');
    setNode(&node15,NULL,NULL,'b');
    setNode(&node22,&node21,NULL,'b');
    setNode(&node20,&node15,&node22,'r');
    setNode(&node30,&node20,&node60,'b');
	
    Node *root=&node30;
    delRedBlackTree(&root,&node60);
    TEST_ASSERT_EQUAL_PTR(root,&node20);
    TEST_ASSERT_EQUAL_NODE(&node15,&node22,'b',&node20);
    TEST_ASSERT_EQUAL_NODE(&node21,&node30,'r',&node22);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node15);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node21);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node30);
}

/********************************************************
	Unit tests for function removeNextLargerSuccessor
**********************************************************/
/****************************************
*
*	root		     root
*	 |                     |
*	 v	               v
*	5(b)   successor 5    10(b)
*	  \  ------------->   / \
*     10(r)	             -   -      
*
*****************************************/

void test_removeNextLargerSuccessor_given_5b_10r_then_remove_successor_5b_should_return_10b(void){
    setNode(&node10,NULL,NULL,'r');
    setNode(&node5,NULL,&node10,'b');
    Node *removeNode, *parentNode=&node5;
	
    removeNode = removeNextLargerSuccessor(&parentNode);
    TEST_ASSERT_EQUAL_PTR(&node5,removeNode);
    TEST_ASSERT_EQUAL_PTR(&node10,parentNode);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node10);
}

/****************************************
*
*	root			root
*	 |                        |
*	 v	                  v
*       /	successor 1	 //
*     1(b)	 ---------->	 -
*     / \
*    -   -
*
*****************************************/

void test_removeNextLargerSuccessor_given_1b_then_remove_successor_1b_should_return_double_black_node(void){
    setNode(&node1,NULL,NULL,'b');
    Node *removeNode, *parentNode=&node1;
	
    removeNode = removeNextLargerSuccessor(&parentNode);
    TEST_ASSERT_EQUAL_PTR(&node1,removeNode);
    TEST_ASSERT_NULL(parentNode);
    TEST_ASSERT_EQUAL(1,isDoubleNodeBlack(parentNode,removeNode));
}

/****************************************
*
*	root			root
*	 |                        |
*	 v	                  v
*       /	successor 1      /
*     1(r)	 ---------->	-
*     / \
*     -  -
*
*****************************************/

void test_removeNextLargerSuccessor_given_1r_then_remove_successor_1r_should_return_black_node(void){
    setNode(&node1,NULL,NULL,'r');
    Node *removeNode, *parentNode=&node1;

    removeNode = removeNextLargerSuccessor(&parentNode);
    TEST_ASSERT_EQUAL_PTR(&node1,removeNode);
    TEST_ASSERT_NULL(parentNode);
    TEST_ASSERT_EQUAL(0,isDoubleNodeBlack(parentNode,removeNode));
}

/****************************************
*
*    root			  root
*     |                            |
*     v	                           v
*   12(b)                        12(b)
*   / \	      successor 5         / \
* 5(r) 18(r)  ------------>	 - 18(r)
*  
* 
*
*****************************************/

void test_removeNextLargerSuccessor_given_12b_5r_18r_then_remove_successor_5r_should_return_12b_18r(void){
    setNode(&node5,NULL,NULL,'r');
    setNode(&node18,NULL,NULL,'r');
    setNode(&node12,&node5,&node18,'b');
    Node *removeNode, *parentNode=&node12;
	
    removeNode = removeNextLargerSuccessor(&parentNode);
    TEST_ASSERT_EQUAL_PTR(&node5,removeNode);
    TEST_ASSERT_EQUAL_PTR(&node12,parentNode);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&node18);
    TEST_ASSERT_EQUAL_NODE(NULL,&node18,'b',&node12);
}

/*************************************************************
*
*	     root			    root
*	      |                               |
*	      v	                              v
*           12(b)                            12(b)
*           /  \	 successor 1        /   \
*        5(b)  18(b)    ------------>	 5(b)   18(b)
*        /     /                                /       
*     1(r)   13(r)                            13(r)
*
****************************************************************/

void test_removeNextLargerSuccessor_given_12b_5b_18b_1r_13r_then_remove_successor_1b_should_return_12b_5b_18b_13r(void){
    setNode(&node1,NULL,NULL,'r');
    setNode(&node13,NULL,NULL,'r');
    setNode(&node5,&node1,NULL,'b');
    setNode(&node18,&node13,NULL,'b');
    setNode(&node12,&node5,&node18,'b');
    Node *removeNode,*parentNode=&node12;

    removeNode = removeNextLargerSuccessor(&parentNode);
    TEST_ASSERT_EQUAL_PTR(&node1,removeNode);
    TEST_ASSERT_EQUAL_PTR(&node12,parentNode);
    TEST_ASSERT_EQUAL_NODE(&node5,&node18,'b',&node12);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node5);
    TEST_ASSERT_EQUAL_NODE(&node13,NULL,'b',&node18);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&node13);
}

/*************************************************************
*
*	     root			    	 root
*	      |                                   |  
*	      v	                                  v
*           12(b)                               12(d)
*           /  \	   successor 1	        /    \
*        5(b)  18(b)	  ------------>	     5(b)   18(r)
*        / \    /  \                           \     /  \    
*     1(b) 7(b)13(b) 20(b)                     7(r) 13(b)20(b)
*
****************************************************************/

void test_removeNextLargerSuccessor_given_12b_5r_18r_1b_7b_13b_20b_then_remove_successor_1b_should_return_12d_5b_7r_18r_13b_20b(void){
    setNode(&node1,NULL,NULL,'b');
    setNode(&node7,NULL,NULL,'b');
    setNode(&node13,NULL,NULL,'b');
    setNode(&node20,NULL,NULL,'b');
    setNode(&node5,&node1,&node7,'b');
    setNode(&node18,&node13,&node20,'b');
    setNode(&node12,&node5,&node18,'b');
    Node *removeNode, *parentNode=&node12;
	
    removeNode = removeNextLargerSuccessor(&parentNode);
    TEST_ASSERT_EQUAL_PTR(&node1,removeNode);
    TEST_ASSERT_EQUAL_PTR(&node12,parentNode);
    TEST_ASSERT_EQUAL_NODE(&node5,&node18,'d',&node12);
    TEST_ASSERT_EQUAL_NODE(&node13,&node20,'r',&node18);
    TEST_ASSERT_EQUAL_NODE(NULL,&node7,'b',&node5);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&node7);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node13);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node20);
}

/************************************************************
*	     root			       
root
*	      |		successor 1	        |
*	      v		 ---------->	        v
*	    18(b)			      18(b)
*	   /	\			    /       \
* 	5(b)	 22(b)		 	 5(b)     22(b)
*	/ \	 /   \			 / \      /   \
*     1(b) 12(b)20(b)35(b)  	      2(b) 12(b) 20(b) 35(b)  
*	\
*	2(r)
************************************************************/

void test_removeNextLargerSuccessor_given_18b_5b_22b_1b_12b_20b_35b_2r_then_remove_successor_1b_should_return_18b_5b_22b_12b_20b_35b_2b(void){
    setNode(&node2,NULL,NULL,'r');
    setNode(&node1,NULL,&node2,'b');
    setNode(&node12,NULL,NULL,'b');
    setNode(&node20,NULL,NULL,'b');
    setNode(&node35,NULL,NULL,'b');
    setNode(&node5,&node1,&node12,'b');
    setNode(&node22,&node20,&node35,'b');
    setNode(&node18,&node5,&node22,'b');
	
    Node *removeNode, *parentNode=&node18;
    
    removeNode = removeNextLargerSuccessor(&parentNode);
    TEST_ASSERT_EQUAL_PTR(&node1,removeNode);
    TEST_ASSERT_EQUAL_PTR(&node18,parentNode);
    TEST_ASSERT_EQUAL_NODE(&node5,&node22,'b',&node18);
    TEST_ASSERT_EQUAL_NODE(&node2,&node12,'b',&node5);
    TEST_ASSERT_EQUAL_NODE(&node20,&node35,'b',&node22);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node2);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node12);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node20);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node35);
}

/******************************************************
    Unit tests to implement removeNextLargerSuccessor
    into function delRedBlackTree
*******************************************************/

/****************************************
*
*	root		     root
*	 |                     |
*	 v	               v
*	5(b)  successor 5     1(b)
*	/    ------------->   / \
*     1(r)	             -   -      
*
*****************************************/

void test_delRedBlackTree_given_5b_1r_then_remove_successor_5b_should_return_1b(void){
    setNode(&node1,NULL,NULL,'r');
    setNode(&node5,&node1,NULL,'b');
    Node *parentNode=&node5;
	
    delRedBlackTree(&parentNode,&node5);
    TEST_ASSERT_EQUAL_PTR(&node1,parentNode);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node1);
}

/****************************************
*
*	root			 root
*	 |                         |
*	 v	                   v
*	5(b)   successor 5	` 10(b)
*	  \  ------------->       / \
*        10(r)	                  -   -      
*
*****************************************/

void test_delRedBlackTree_given_5b_10r_then_remove_successor_5b_should_return_10b(void){
    setNode(&node10,NULL,NULL,'r');
    setNode(&node5,NULL,&node10,'b');
    Node *parentNode=&node5;
	
    delRedBlackTree(&parentNode,&node5);
    TEST_ASSERT_EQUAL_PTR(&node10,parentNode);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node10);
}

/****************************************
*
*	root			   root
*	 |                          |
*	 v	                    v
*	5(b)   successor 5	` 10(b)
*	/  \  ------------->       / \
*    1(r) 10(r)	                 1(r) -      
*
*****************************************/

void test_delRedBlackTree_given_5b_1r_10r_then_remove_successor_5b_should_return_10b_1r(void){
    setNode(&node1,NULL,NULL,'r');
    setNode(&node10,NULL,NULL,'r');
    setNode(&node5,&node1,&node10,'b');
    Node *parentNode=&node5;
	
    delRedBlackTree(&parentNode,&node5);
    TEST_ASSERT_EQUAL_PTR(&node10,parentNode);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&node1);
    TEST_ASSERT_EQUAL_NODE(&node1,NULL,'b',&node10);
}

/**
*	  root			   root
*	   |		 	    |
*	   v		            v
*	  20(b)	 successor 15	  20(b) 
*	 /   \	 ----------->     /  \
*      15(b) 30(b)	       13(b) 30(b)
*      /  \		        /
*   10(r) 13(r)		     10(r)
*/

void test_delRedBlackTree_given_10r_13r_15b_30b_20b_then_remove_successor_15b_should_return_20b_13b_30b_10r(void){

	setNode(&node10,NULL,NULL,'r');
	setNode(&node13,NULL,NULL,'r');
	setNode(&node30,NULL,NULL,'b');
	setNode(&node15,&node10,&node13,'b');
    setNode(&node20,&node15,&node30,'b');
	
    Node *parentNode = &node20;
	
    delRedBlackTree(&parentNode,&node15);
    TEST_ASSERT_EQUAL_PTR(&node20,parentNode);
    TEST_ASSERT_EQUAL_NODE(&node13,&node30,'b',&node20);
    TEST_ASSERT_EQUAL_NODE(&node10,NULL,'b',&node13);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&node10);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node30);
}

/*********************************************************************************************
*	  root				   root               root                  root
*	    \		successor 22	     \                 \                      \    
*	     \ 		 ------------>	      \                 \                      \
*	    18(r)			    18(r)      ----->    18(r)      ----->     18(b)
*	   /	 \			    /	\              /     \\               /    \
* 	12(b)	  22(b)		        12(b)	35(b)       12(b)      35(b)       12(r)    35(b)
*	/  \	   /  \		         /  \	 /   \\	    /  \      /    \      /  \      /   \
*     10(b)13(b)20(b) 35(b)  	     10(b) 13(b) 20(b) -  10(b) 13(b) 20(b) -   10(b)13(b) 20(r) - 
*	
*	
***********************************************************************************************/

void test_delRedBlackTree_given_10b_13b_20b_35b_12b_22b_18r_then_remove_successor_22b_should_return_root_18b_12r_25b_10b_13b_20r(void){
    setNode(&node10,NULL,NULL,'b');
    setNode(&node13,NULL,NULL,'b');
    setNode(&node20,NULL,NULL,'b');
    setNode(&node35,NULL,NULL,'b');
    setNode(&node12,&node10,&node13,'b');
    setNode(&node22,&node20,&node35,'b');
    setNode(&node18,&node12,&node22,'r');
    
    Node *parentNode=&node18;
    delRedBlackTree(&parentNode,&node22);
    TEST_ASSERT_EQUAL_PTR(&node18,parentNode);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&node20);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node10);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node13);
    TEST_ASSERT_EQUAL_NODE(&node12,&node35,'b',&node18);
    TEST_ASSERT_EQUAL_NODE(&node20,NULL,'b',&node35);
    TEST_ASSERT_EQUAL_NODE(&node10,&node13,'r',&node12);
}

/*********************************************************************************************
*	  root				   root               root                  root
*	    \		successor 12	     \                 \                      \    
*	     \ 		 ------------>	      \                 \                      \
*	    18(r)			    18(r)      ----->    18(r)      ----->     18(b)
*	   /	 \			    /	\              //     \               /    \
* 	12(b)	  22(b)		        13(b)	22(b)       13(b)      22(b)       13(b)   22(r)
*	/  \	   /  \		         /  \\	 / \   	    /   \      /  \       /  \      / \
*     10(b)13(b)20(b) 35(b)  	     10(b)   - 20(b)35(b)  10(b) - 20(b) 35(b)  10(r) - 20(b) 35(b) 
*	
*	
***********************************************************************************************/

void test_delRedBlackTree_given_10b_13b_20b_35b_12b_22b_18r_then_remove_successor_12b_should_return_root_18b_13r_10b_22r_20b_35b(void){
    setNode(&node10,NULL,NULL,'b');
    setNode(&node13,NULL,NULL,'b');
    setNode(&node20,NULL,NULL,'b');
    setNode(&node35,NULL,NULL,'b');
    setNode(&node12,&node10,&node13,'b');
    setNode(&node22,&node20,&node35,'b');
    setNode(&node18,&node12,&node22,'r');
    
    Node *parentNode=&node18;
    delRedBlackTree(&parentNode,&node12);
    TEST_ASSERT_EQUAL_PTR(&node18,parentNode);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node20);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&node10);
    TEST_ASSERT_EQUAL_NODE(&node10,NULL,'b',&node13);
    TEST_ASSERT_EQUAL_NODE(&node13,&node22,'b',&node18);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node35);
    TEST_ASSERT_EQUAL_NODE(&node20,&node35,'r',&node22);
}

/****************************************
*
*	root			root
*	 |                        |
*	 v	                  v
*       /	successor 1	 //
*     1(b)	 ---------->	 -
*     / \
*    -   -
*
*****************************************/

void test_delRedBlackTree_given_1b_then_remove_successor_1b_should_return_double_black_node(void){
    setNode(&node1,NULL,NULL,'b');
    Node *parentNode=&node1;
	
    delRedBlackTree(&parentNode,&node1);
    TEST_ASSERT_NULL(parentNode);
}

/************************************************************
*	     root			       
root
*	      |		successor 1	        |
*	      v		 ---------->	        v
*	    18(b)			      18(b)
*	   /	\			    /       \
* 	5(b)	 22(b)		 	 5(b)     22(b)
*	/ \	 /   \			 / \      /   \
*     1(b) 12(b)20(b)35(b)  	      2(b) 12(b) 20(b) 35(b)  
*	\
*	2(r)
************************************************************/

void test_delRedBlackTree_given_18b_5b_22b_1b_12b_20b_35b_2r_then_remove_successor_1b_should_return_18b_5b_22b_12b_20b_35b_2b(void){
    setNode(&node2,NULL,NULL,'r');
    setNode(&node1,NULL,&node2,'b');
    setNode(&node12,NULL,NULL,'b');
    setNode(&node20,NULL,NULL,'b');
    setNode(&node35,NULL,NULL,'b');
    setNode(&node5,&node1,&node12,'b');
    setNode(&node22,&node20,&node35,'b');
    setNode(&node18,&node5,&node22,'b');
	
    Node *parentNode=&node18;
    
    delRedBlackTree(&parentNode,&node1);
    TEST_ASSERT_EQUAL_PTR(&node18,parentNode);
    TEST_ASSERT_EQUAL_NODE(&node5,&node22,'b',&node18);
    TEST_ASSERT_EQUAL_NODE(&node2,&node12,'b',&node5);
    TEST_ASSERT_EQUAL_NODE(&node20,&node35,'b',&node22);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node2);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node12);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node20);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node35);
}

/***************************************************************************
*
*	 root					    root
*	  |				              |
*	  v		 			      v
*	 20(b)					    20(b) 
*        /   \		successor 35	  	    /	\
*      5(b)  35(b)      ------------>	       5(b)	30(b)
*    /  \      /   \			       / \      /    \
* 1(b)  15(b) 22(b)60(b)	           1(b)  15(b)	22(b) 60(b) 
*		\
*		30(r)
****************************************************************************/

void test_delRedBlackTree_given_20b_5b_35b_1b_15b_22b_60b_30r_then_remove_successor_35b_should_return_20b_5b_30b_1b_15b_22b_60b(){

	setNode(&node30,NULL, NULL,'r');
	setNode(&node1,NULL,NULL,'b');
	setNode(&node15,NULL,NULL,'b');
	setNode(&node22,NULL,&node30,'b');
	setNode(&node60,NULL,NULL,'b');
	setNode(&node5,&node1,&node15,'b');
	setNode(&node35,&node22,&node60,'b');
	setNode(&node20,&node5,&node35,'b');
	
	Node *parentNode = &node20;
	
    delRedBlackTree(&parentNode,&node35);
	TEST_ASSERT_EQUAL_PTR(&node20, parentNode);
    TEST_ASSERT_EQUAL_NODE(&node5, &node30, 'b', &node20);
    TEST_ASSERT_EQUAL_NODE(&node1, &node15, 'b', &node5);
    TEST_ASSERT_EQUAL_NODE(&node22, &node60, 'b', &node30);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node1);
	TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node15);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node22);
	TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node60);
}

