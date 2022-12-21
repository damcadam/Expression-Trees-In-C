/*
* Name: (Darius McAdam)
* Lab: (Tuesday)
* Assignment: Project 4 – Expression trees and traversals
*
* (Header file for tree code)
*/

#ifndef TREE_H
#define TREE_H

#include "types.h"

/*
* TREE represents an expression tree. Each TREE
* can either be a leaf node (which holds a number)
* or a non-leaf node (which holds an operator).
*/
typedef struct tnode {
    union {
        int leafnum;
        OP operator;
    } data;
    BOOL isleaf;
    struct tnode* left;
    struct tnode* right;
} TREE;

/*
 * create_singleton creates a new singleton (no children) tree
 * to hold an integer data value
 * 
 * d: the integer data
 * returns: a new TREE object holding d (with no children)
 */
TREE* create_singleton(int d);

/*
 * build_tree creates a non-leaf tree with the given
 * operator and left/right subtrees
 * 
 * oper: the operator to be stored as the data for the new tree
 * l: the left subtree for the new tree
 * r: the right subtree for the new tree
 * returns: the newly created TREE object holding oper, l, and r
 */
TREE* build_tree(OP oper, TREE* l, TREE* r);

/*
 * inorder does an inorder traversal on the given tree,
 * and writes the traversal in the given buffer. Here is the
 * inorder traversal algorithm:
 *      If the tree is a leaf, add its data to the buffer
 *      Otherwise:
 *          Recursively do an inorder traversal on the left subtree
 *          Add the current data to the buffer
 *          Recursively do an inorder traversal on the right subtree
 * 
 * You will also need to add ( ) around everything (left, data, right)
 * in the non-leaf case to express the correct order of operations.
 * 
 * 
 * tree: the expression tree to traverse
 * buffer: where the traversal will be written
 */
void inorder(TREE* tree, char* buffer);

/*
 * preorder does an preorder traversal on the given tree,
 * and writes the traversal in the given buffer. Here is the
 * preorder traversal algorithm:
 *      If the tree is a leaf, add its data to the buffer
 *      Otherwise:
 *          Add the current data to the buffer
 *          Recursively do an preorder traversal on the left subtree
 *          Recursively do an preorder traversal on the right subtree
 * 
 * tree: the expression tree to traverse
 * buffer: where the traversal will be written
 */
void preorder(TREE* tree, char* buffer);

/*
 * defines a function pointer type called "trav_fn"
 * for a function that takes a tree and character buffer,
 * and that writes a traversal for the tree to the buffer.
 */
typedef void (*trav_fn)(TREE* tree, char* buffer);

/*
 * evaluate returns the evaluation of the expression
 * represented by the given expression tree.
 * 
 * If tree is a leaf, return its data
 * Otherwise, return the result of:
 *      (recursively evaluate left) op (recursively evaluate right)
 * 
 * Where "op" is the operator (+, -, *, /) stored in tree's data
 * 
 * tree: the expression tree to evalute
 * returns: the evaluation of tree
 */
int evaluate(TREE* tree);

/*
 * free_tree releases all the memory allocated
 * for the given tree.
 * 
 * tree: the expression tree to free
 */
void free_tree(TREE* t);

#endif