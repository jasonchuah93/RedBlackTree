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

/**************************************************
    COLOR NODE UNIT TESTS
**************************************************/

void test_isNodeBlack_should_return_1_if_the_node_is_black_color(void){
    setNode(&node5,NULL,NULL,'b');
    setNode(&node30,NULL,NULL,'b');
    setNode(&node20,&node5,&node30,'b');
    Node *nodeA = &node5;
    Node *nodeB = &node30;
    Node *nodeC = &node20;
    TEST_ASSERT_EQUAL(1,isNodeBlack(&nodeA));
    TEST_ASSERT_EQUAL(1,isNodeBlack(&nodeB));
    TEST_ASSERT_EQUAL(1,isNodeBlack(&nodeC));
}

void test_isNodeBlack_should_return_0_if_the_node_is_not_black_color(void){
    setNode(&node5,NULL,NULL,'r');
    setNode(&node30,NULL,NULL,'d');
    setNode(&node20,&node5,&node30,'r');
    Node *nodeA = &node5;
    Node *nodeB = &node30;
    Node *nodeC = &node20;
    TEST_ASSERT_EQUAL(0,isNodeBlack(&nodeA));
    TEST_ASSERT_EQUAL(0,isNodeBlack(&nodeB));
    TEST_ASSERT_EQUAL(0,isNodeBlack(&nodeC));
}

void test_isNodeRed_should_return_1_if_the_node_is_red_color(void){
    setNode(&node5,NULL,NULL,'r');
    setNode(&node30,NULL,NULL,'r');
    setNode(&node20,&node5,&node30,'r');
    Node *nodeA = &node5;
    Node *nodeB = &node30;
    Node *nodeC = &node20;
    TEST_ASSERT_EQUAL(1,isNodeRed(&nodeA));
    TEST_ASSERT_EQUAL(1,isNodeRed(&nodeB));
    TEST_ASSERT_EQUAL(1,isNodeRed(&nodeC));
}

void test_isNodeRed_should_return_0_if_the_node_is_not_red_color(void){
    setNode(&node5,NULL,NULL,'b');
    setNode(&node30,NULL,NULL,'b');
    setNode(&node20,&node5,&node30,'d');
    Node *nodeA = &node5;
    Node *nodeB = &node30;
    Node *nodeC = &node20;
    TEST_ASSERT_EQUAL(0,isNodeRed(&nodeA));
    TEST_ASSERT_EQUAL(0,isNodeRed(&nodeB));
    TEST_ASSERT_EQUAL(0,isNodeRed(&nodeC));
}

/**************************************************

    RESTRUCTURE NODE UNIT TESTS
***************************************************/

/**
 * Case(1a): Sibling is black and nephew is red
 * Parent being black
 *      
 *       |        	        |
 *       V     left rotate     	V
 *      10(b) ------------>   20(b)
 *     //   \                 /   \
 *     -   20(b)           10(b) 30(b)
 *            \            /  \   / \     
 *           30(r)         -  -   -  - 
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
 * Case(1a): Sibling is black and nephew is red
 * Parent being black
 *      
 *       |        		|
 *       V     right rotate  	V
 *      10(b) ------------->   8(b)
 *      /   \\                /   \
 *     8(b)  -        	    1(b) 10(b)
 *    /                	    / \   / \     
 *   1(r)              	    -  -  - - 
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
 *  Case(1a): Sibling is black and nephew is red
 * Parent being red
 *      root               root
 *       |                   |
 *       V     left rotate   V
 *      10(r) --------->    20(r)
 *     //   \              /   \
 *     -    20(b)        10(b) 30(b)
 *            \          / \    / \        
 *           30(r)      -  -   -   - 
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
 * Case(1a): Sibling is black and nephew is red
 * Parent being red
 *     	 |        		|
 *       V     right rotate  	V
 *      10(r) ------------->   8(r)
 *      /   \\                /   \
 *     8(b)  -        	    1(b) 10(b)
 *    /                	    / \   / \     
 *   1(r)              	    -  -  - - 
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
 * Case(1b): Sibling is black and nephew is red
 *      root              	     root
 *       |         		       |
 *       V     rightLeft rotate        V
 *      10(b) ----------------->     15(b)
 *     //   \              	    /   \
 *     -   20(b)        	 10(b) 20(b)
 *          /                     / \   / \
 *        15(r)                  -   -  -  -
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
 *  Case(1b): Sibling is black and nephew is red
 *       |        		     	|
 *       V     leftRight rotate  	V
 *      10(b) ----------------->      9(b)
 *      /   \\                	     /   \
 *     8(b)  -        		   8(b) 10(b)
 *     	\                    	   / \   / \     
 *   	9(r)              	  -  -  -   - 
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
 *  Case(2a): Sibling is black and both nephew are black
 *  Parent is black lastly become double
 *     root                root
 *       |        	    |
 *       V     flip color   V
 *      10(b) --------->  10(d)
 *     //   \             /   \
 *    -	   20(b)         -  20(r)
 *          /  \             /  \     
 *        15(b) 30(b)     15(b) 30(b) 
 *        / \   / \	   / \   / \
 *       -  -  -  -	   -  -  -  -
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
 * Case(2a): Sibling is black and both nephew are black
 * Parent is black lastly become double
 *       |        		     	| 
 *       V     flip color  	        V
 *      10(b) ----------------->      10(d)
 *     /   \\                	     /   \
 *    8(b)  -        		    8(r)  -
 *   /   \                    	   / \        
 *  5(b) 9(b)                    5(b) 9(b)	     
 * /   \ / \                  	/ \  / \  
 * -   - -  -                  -  -  -  -
 **/
 
void test_restructureBlackLeftWithBlackChildren_case_2a(void){
	setNode(&node5,NULL,NULL,'b');
	setNode(&node9,NULL,NULL,'b');
    setNode(&node8,&node5,&node9,'b');
	setNode(&node10,&node8,NULL,'b');
	
	Node *root=&node10;
	restructureBlackLeftWithBlackChildren(&root);
	TEST_ASSERT_EQUAL_PTR(root,&node10);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node5);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node9);
	TEST_ASSERT_EQUAL_NODE(&node5,&node9,'r',&node8);
	TEST_ASSERT_EQUAL_NODE(&node8,NULL,'d',&node10);
}

/**
 * Case(2b): Sibling is black and both nephew are black
 * Parent is red and lastly become black
 *       root                   root
 *        |        	         |
 *        V     flip color       V
 *       10(r) --------->       10(b)
 *      //   \                 /   \
 *    -	    20(b)             -  20(r)
 *          /  \                  /  \     
 *        15(b) 30(b)          15(b) 30(b) 
 *        / \  / \              / \  / \
 *       -  - -   -            -  - -   -
 **/
 
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
 * Case(2b): Sibling is black and both nephew are black
 * Parent is red and lastly become black
 *        root             		root
 *         |        		     	 |
 *         V     flip color  	         V
 *        10(r) ----------------->     10(b)
 *        /   \\                       /   \
 *       8(b)  -        	      8(r)  -
 *      /   \                        / \        
 *     5(b) 9(b)                  5(b)  9(b)	     
 *    / \   / \			   / \   / \
 *   -  -  -   -		  -  -  -   -
 **/
 
void test_restructureBlackLeftWithBlackChildren_case_2b(void){
    setNode(&node5,NULL,NULL,'b');
    setNode(&node9,NULL,NULL,'b');
    setNode(&node8,&node5,&node9,'b');
    setNode(&node10,&node8,NULL,'r');
	
	Node *root=&node10;
	restructureBlackLeftWithBlackChildren(&root);
	TEST_ASSERT_EQUAL_PTR(root,&node10);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node5);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&node9);
	TEST_ASSERT_EQUAL_NODE(&node5,&node9,'r',&node8);
	TEST_ASSERT_EQUAL_NODE(&node8,NULL,'b',&node10);
}

/***************************************************
	Case 3 unit tests on test_RedBlackTreeDel.c
****************************************************/




