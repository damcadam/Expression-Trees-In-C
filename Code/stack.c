/*
* Name: (Darius McAdam)
* Lab: (Tuesday)
* Assignment: Project 4 – Expression trees and traversals
*
* (Stack implementation)
*/

#include "stack.h"
#include "types.h"
#include <stdlib.h>

/*
 * init_stack creates and returns a new stack object.
 *
 * returns: the new stack object
 */
STACK* init_stack(void)
{
    // Create new stack and the top to new
    STACK* newStack = malloc(sizeof(STACK*));
    newStack->top = NULL;
    return newStack;
}

/*
 * Push adds a value to the top of the given stack
 *
 * s: the stack to push onto
 * d: the data (a TREE) to push
 */
void push(STACK* s, TREE* d)
{
    // Create new node using this new tree
    NODE* newNode = malloc(sizeof(NODE*));
    newNode->data = d;
    // Point to new node to the current top
    newNode->next = s->top;

    // Set the newNode as the current top
    s->top = newNode;
}

/*
 * Pop removes and returns the top value (tree) on the given stack. It assumes the 
 * stack has at least one node.
 *
 * s: the stack to pop
 * returns: the TREE that was on the top of stack s
 */
TREE* pop(STACK* s)
{
    // Get the tree on top of the stack
    TREE* returnTree = s->top->data;

    // Get the next node on the stack or NULL
    NODE* newTop = s->top->next;
    // Free the old top
    free(s->top);
    // Point the newTop to the top of our stack
    s->top = newTop;

    // Return the tree that was in the popped node
    return returnTree;
}

/*
 * free_stack frees all nodes on stack s
 *
 * s: the stack to free
 */
void free_stack(STACK* s)
{
    // Pop all nodes all the stack because our pop function also frees the node
    while(s->top != NULL)
    {
        pop(s);
    }
    // Finally free the stack itself
    free(s);
}
