#include <stdio.h>
#include "unity.h"
#include "Node.h"
#include "InitNode.h"
#include "Rotation.h"
#include "RedBlackTree.h"
#include "CustomAssertions.h"
#include "ErrorCode.h"
#include "CException.h"

Node node1,node2,node4,node5,node7,node8,node9,node10,node12,node13,
      node15,node18,node20,node22,node30,node35,node40,node60;

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

	2 height level tests

*******************************************/
/**
*	    root		     root
*	    |    remove 1	  |
*	    v    -------->    v
*	    2(b)             2(b)
*      / 
*    1(r)
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
*	    |    remove 10	  |
*	    v    -------->    v
*	    2(b)             2(b)
*        \
*        10(r)
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
*	    root		     root
*	    |    remove 1	  |
*	    v    -------->    v
*	    2(b)             2(b)
*      /  \					\
*    1(r) 5(r)				5(r)
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
*	    |    remove 5	  |
*	    v    -------->    v
*	    2(b)             2(b)
*      /  \				/	
*    1(r) 5(r)		  1(r)	
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
 *        /  \             \
 *     15(b) 30(b)         15(r)
 */

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
 *   5(r)   20(b)		1(b)  10(b) 
 *    /  \                   /
 *   1(b)8(b)   			8(r)
 */

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
 *     /   \              /   \
 *   5(b)  20(r)        5(b) 20(b)
 *        /  \                  \
 *     15(b) 30(b)              30(r)
 */

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
 *       |    remove 15     |
 *       V                  V
 *      10(b) --------->   10(b)
 *     /   \              /   \
 *   5(b)  20(r)        5(b) 20(b)
 *        /  \                /  
 *     15(b) 30(b)           15(r)
 */

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
 *       root                root
 *        |    remove 1       |
 *        V                   V
 *       10(b) --------->     10(b)
 *     /    \                /    \
 *   5(r)    20(r)        5(b)     20(r)
 *   / \      /  \          \      /   \ 
 * 1(b) 8(b) 15(b) 30(b)   8(r) 15(b) 30(b)
 */

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
 *       root                root
 *        |    remove 8       |
 *        V                   V
 *       10(b) --------->     10(b)
 *     /    \                /    \
 *   5(r)    20(r)        5(b)     20(r)
 *   / \      /  \         /      /   \ 
 * 1(b) 8(b) 15(b) 30(b) 1(r) 15(b) 30(b)
 */

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
 *       root                root
 *        |    remove 15       |
 *        V                   V
 *       10(b) --------->     10(b)
 *     /    \                /    \
 *   5(r)    20(r)        5(r)     20(b)
 *   / \      /  \         / \         \ 
 * 1(b) 8(b) 15(b) 30(b) 1(b) 8(b)  30(r)
 */

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
 *       root                root
 *        |    remove 30       |
 *        V                   V
 *       10(b) --------->     10(b)
 *     /    \                /    \
 *   5(r)    20(r)        5(r)     20(b)
 *   / \      /  \         /  \      /    
 * 1(b) 8(b) 15(b) 30(b) 1(b)8(b) 15(r)
 */

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
 *	Case(1a): Sibling is black and nephew is red
 * Parent being black
 *      
 *       |        		       |
 *       V     left rotate     V
 *      10(b) ------------>   20(b)
 *     //   \              	/   \
 *     -	20(b)         10(b) 30(b)
 *           \            / \   / \     
 *      	30(r)         -  -  - - 
 */
void test_restructureBlackRightWithOneRedChild_case_1a_parent_is_black(void){
	setNode(&node30,NULL,NULL,'r');
    setNode(&node20,NULL,&node30,'b');
	setNode(&node10,NULL,&node20,'b');
	
	Node *root=&node10;
	restructureBlackRightWithOneRedChild(&root);
	TEST_ASSERT_EQUAL_PTR(root,&node20);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node10);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node30);
	TEST_ASSERT_EQUAL_NODE(&node10,&node30,'b',&node20);
}

/**
 *	Case(1a): Sibling is black and nephew is red
 * Parent being black
 *      
 *       |        		     	|
 *       V     right rotate  	V
 *      10(b) ------------->   8(b)
 *      /   \\                /   \
 *     8(b)  -        		1(b) 10(b)
 *    /                		/ \   / \     
 *   1(r)              		-  -  - - 
 */
void test_restructureBlackLeftWithOneRedChild_case_1a_parent_is_black(void){
	setNode(&node1,NULL,NULL,'r');
    setNode(&node8,&node1,NULL,'b');
	setNode(&node10,&node8,NULL,'b');
	
	Node *root=&node10;
	restructureBlackLeftWithOneRedChild(&root);
	TEST_ASSERT_EQUAL_PTR(root,&node8);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node1);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node10);
	TEST_ASSERT_EQUAL_NODE(&node1,&node10,'b',&node8);
}

/**
 *	Case(1a): Sibling is black and nephew is red
 * Parent being red
 *      root               root
 *       |      		     |
 *       V     left rotate   V
 *      10(r) --------->    20(r)
 *     //   \              /   \
 *     -    20(b)        10(b) 30(b)
 *           \                  
 *      	30(r)           
 */
void test_restructureBlackRightWithOneRedChild_case_1a_parent_is_red(void){
	
    setNode(&node30,NULL,NULL,'r');
    setNode(&node20,NULL,&node30,'b');
	setNode(&node10,NULL,&node20,'r');
	
	Node *root=&node10;
	restructureBlackRightWithOneRedChild(&root);
	TEST_ASSERT_EQUAL_PTR(root,&node20);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node10);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node30);
	TEST_ASSERT_EQUAL_NODE(&node10,&node30,'r',&node20);
}

/**
 *	Case(1a): Sibling is black and nephew is red
 * Parent being red
 *     	 |        		     	|
 *       V     right rotate  	V
 *      10(r) ------------->   8(r)
 *      /   \\                /   \
 *     8(b)  -        		1(b) 10(b)
 *    /                		/ \   / \     
 *   1(r)              		-  -  - - 
 */
void test_restructureBlackLeftWithOneRedChild_case_1a_parent_is_red(void){
	setNode(&node1,NULL,NULL,'r');
    setNode(&node8,&node1,NULL,'b');
	setNode(&node10,&node8,NULL,'r');
	
	Node *root=&node10;
	restructureBlackLeftWithOneRedChild(&root);
	TEST_ASSERT_EQUAL_PTR(root,&node8);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node1);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node10);
	TEST_ASSERT_EQUAL_NODE(&node1,&node10,'r',&node8);
}

/**
 *	Case(1b): Sibling is black and nephew is red
 *      root              			   root
 *       |         						|
 *       V     rightLeft rotate 		V
 *      10(b) ----------------->   	   15(b)
 *     //   \              			   /   \
 *     -   20(b)        			10(b) 20(b)
 *          /                   
 *        15(r)           
 */
void test_restructureBlackRightWithOneRedChild_case_1b(void){
	setNode(&node15,NULL,NULL,'r');
    setNode(&node20,&node15,NULL,'b');
	setNode(&node10,NULL,&node20,'b');
	
	Node *root=&node10;
	restructureBlackRightWithOneRedChild(&root);
	TEST_ASSERT_EQUAL_PTR(root,&node15);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node10);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node20);
	TEST_ASSERT_EQUAL_NODE(&node10,&node20,'b',&node15);
}

/**
 *	Case(1b): Sibling is black and nephew is red
 *       |        		     	    |
 *       V     leftRight rotate  	V
 *      10(b) ----------------->   9(b)
 *      /   \\                	  /   \
 *     8(b)  -        			8(b) 10(b)
 *     	\                    	/ \   / \     
 *   	9(r)              	   -  -  -   - 
 */
void test_restructureBlackLeftWithOneRedChild_case_1b(void){
	setNode(&node9,NULL,NULL,'r');
    setNode(&node8,NULL,&node9,'b');
	setNode(&node10,&node8,NULL,'b');
	
	Node *root=&node10;
	restructureBlackLeftWithOneRedChild(&root);
	TEST_ASSERT_EQUAL_PTR(root,&node9);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node8);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node10);
	TEST_ASSERT_EQUAL_NODE(&node8,&node10,'b',&node9);
}
/**
 *	Case(2a): Sibling is black and both nephew are black
 *	Parent is black lastly become double
 *      root              root
 *       |        			|
 *       V     flip color   V
 *      10(b) --------->  10(d)
 *     //   \             /   \
 *    -		20(b)         -  20(r)
 *          /  \              /  \     
 *        15(b) 30(b)        15(b) 30(b) 
 */
void test_restructureBlackRightWithBlackChildren_case_2a(void){
	setNode(&node15,NULL,NULL,'b');
	setNode(&node30,NULL,NULL,'b');
    setNode(&node20,&node15,&node30,'b');
	setNode(&node10,NULL,&node20,'b');
	
	Node *root=&node10;
	restructureBlackRightWithBlackChildren(&root);
	TEST_ASSERT_EQUAL_PTR(root,&node10);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node15);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node30);
	TEST_ASSERT_EQUAL_NODE(&node15,&node30,'r',&node20);
	TEST_ASSERT_EQUAL_NODE(NULL,&node20,'d',&node10);
}

/**
 *	Case(2b): Sibling is black and both nephew are black
 *	Parent is red and lastly become black
 *      root              root
 *       |        			|
 *       V     flip color   V
 *      10(r) --------->  10(b)
 *     //   \             /   \
 *    -		20(b)         -  20(r)
 *          /  \              /  \     
 *        15(b) 30(b)        15(b) 30(b) 
 */
void test_restructureBlackRightWithBlackChildren_case_2b(void){
	setNode(&node15,NULL,NULL,'b');
	setNode(&node30,NULL,NULL,'b');
    setNode(&node20,&node15,&node30,'b');
	setNode(&node10,NULL,&node20,'r');
	
	Node *root=&node10;
	restructureBlackRightWithBlackChildren(&root);
	TEST_ASSERT_EQUAL_PTR(root,&node10);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node15);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node30);
	TEST_ASSERT_EQUAL_NODE(&node15,&node30,'r',&node20);
	TEST_ASSERT_EQUAL_NODE(NULL,&node20,'b',&node10);
}

/**
 *	Case(3): Sibling is red
 *	Parent is red and lastly become black
 *      root              root						root
 *       |    rotate    	|		use 			  |
 *       V     left			V		case 2			  V
 *      10(b) --------->  20(b)		--------->	     20(b)
 *     //   \             /   \						 / \		
 *    -		20(r)       10(r)  30(b)			 10(b) 30(b)
 *          /  \            \     					\
 *        15(b) 30(b)       15(b)  					15(r)
 */
void test_restructureRedRight_case_3(void){
	setNode(&node15,NULL,NULL,'b');
	setNode(&node30,NULL,NULL,'b');
    setNode(&node20,&node15,&node30,'r');
	setNode(&node10,NULL,&node20,'b');
	
	Node *root=&node10;
	restructureRedRight(&root);
	TEST_ASSERT_EQUAL_PTR(root,&node20);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&node15);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node30);
	TEST_ASSERT_EQUAL_NODE(NULL,&node15,'b',&node10);
	TEST_ASSERT_EQUAL_NODE(&node10,&node30,'b',&node20);
}


