/*
* Name: (Darius McAdam)
* Lab: (Tuesday)
* Assignment: Project 4 – Expression trees and traversals
*
* (Implementation for the tree)
*/

#include "tree.h"
#include "types.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*
 * create_singleton creates a new singleton (no children) tree
 * to hold an integer data value
 * 
 * d: the integer data
 * returns: a new TREE object holding d (with no children)
 */
TREE* create_singleton(int d)
{
    // Create the single tree and initalize it's values
    TREE* newTree = malloc(sizeof(TREE*));
    newTree->isleaf = true; 
    newTree->left = NULL;
    newTree->right = NULL;
    newTree->data.leafnum = d;

    return newTree;
}

/*
 * build_tree creates a non-leaf tree with the given
 * operator and left/right subtrees
 * 
 * oper: the operator to be stored as the data for the new tree
 * l: the left subtree for the new tree
 * r: the right subtree for the new tree
 * returns: the newly created TREE object holding oper, l, and r
 */
TREE* build_tree(OP oper, TREE* l, TREE* r)
{
    TREE* newTree = malloc(sizeof(TREE*));
    newTree->data.operator = oper;
    newTree->left = l;
    newTree->right = r;

    return newTree;
}

// Helper function for adding an operation to a string
void AddOPToBuffer(OP oper, char* buffer)
{
    if (oper == PLUS)
    {
        strcat(buffer, " +");
    }
    else if (oper == MINUS)
    {
        strcat(buffer, " -");
    }
        else if (oper == TIMES)
    {
        strcat(buffer, " *");
    }
    else // if (oper == DIVIDE)
    {
        strcat(buffer, " /");
    }
}

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
 * in the non-leaf case to express the correct order of operations. <------- ?
 * 
 * 
 * tree: the expression tree to traverse
 * buffer: where the traversal will be written
 */
void inorder(TREE* tree, char* buffer)
{
    if (tree->isleaf == true)
    {
        // Add the leaf's data to the buffer
        char numString[30];
        sprintf(numString, " %d ", tree->data.leafnum);
        strcat(buffer, numString);
    }
    else
    {
        strcat(buffer, "(");
        // Recursively do inorder traversal on the left tree
        inorder(tree->left, buffer);
        // Add operation to the buffer
        AddOPToBuffer(tree->data.operator, buffer);
        // Recursivley inorder traversal on the right tree
        inorder(tree->right, buffer);
        strcat(buffer, ")");
    }
}

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
void preorder(TREE* tree, char* buffer)
{
    if (tree->isleaf == true)
    {
        // Add the leaf's data to the buffer
        char numString[100];
        sprintf(numString, " %d", tree->data.leafnum);
        strcat(buffer, numString);
    }
    else
    {
        // Add operation to the buffer
        AddOPToBuffer(tree->data.operator, buffer);
        // Recursively do inorder traversal on the left tree
        preorder(tree->left, buffer);
        // Recursivley inorder traversal on the right tree
        preorder(tree->right, buffer);
    }
}

// For creating the array of functions in the main program
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
int evaluate(TREE* tree)
{
    if (tree->isleaf == true)
    {
        return tree->data.leafnum;
    }
    else
    {
        switch (tree->data.operator)
        {
        case PLUS:
            return evaluate(tree->left) + evaluate(tree->right);
            break;
        case MINUS:
            return evaluate(tree->left) - evaluate(tree->right);
            break;
        case TIMES:
            return evaluate(tree->left) * evaluate(tree->right);
            break;
        default: // DIVIDE
            return evaluate(tree->left) / evaluate(tree->right);
            break;
        }
    }
}

/*
 * free_tree releases all the memory allocated
 * for the given tree.
 * 
 * tree: the expression tree to free
 */
void free_tree(TREE* t)
{
    // Do nothing if passed to a null node
    if (t == NULL) return;

    // Call the free function on every single node
    free_tree(t->left);
    free_tree(t->right);

    free(t);
}
