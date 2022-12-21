/*
* Name: (Darius McAdam)
* Lab: (Tuesday)
* Assignment: Project 4 – Expression trees and traversals
*
* (Header file for stack)
*/

#ifndef STACK_H
#define STACK_H

#include "types.h"
#include "tree.h"

/*
* NODE represents a node in a stack. The data field is type TREE 
* (defined in tree.h).
*/
typedef struct snode {
    TREE* data;
    struct snode* next;
} NODE;

/*
* STACK represents a stack of type TREE. top is the first NODE
* (defined above) in the stack.
*/
typedef struct {
    NODE* top;
} STACK;

/*
 * init_stack creates and returns a new stack object.
 *
 * returns: the new stack object
 */
STACK* init_stack(void);

/*
 * Push adds a value to the top of the given stack
 *
 * s: the stack to push onto
 * d: the data (a TREE) to push
 */
void push(STACK* s, TREE* d);

/*
 * Pop removes and returns the top value (tree) on the given stack. It assumes the 
 * stack has at least one node.
 *
 * s: the stack to pop
 * returns: the TREE that was on the top of stack s
 */
TREE* pop(STACK* s);

/*
 * free_stack frees all nodes on stack s
 *
 * s: the stack to free
 */
void free_stack(STACK* s);

#endif