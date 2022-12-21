/*
* Name: (Darius McAdam)
* Lab: (Tuesday)
* Assignment: Project 4 – Expression trees and traversals
*
* (Main program. Asks for an expression to calculate. Then it will use a tree to 
*  evaluate the expression.)
*/

#include "stack.h"
#include "tree.h"
#include "types.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//YOU DO THIS

//Complete the main function for the project
//(You can include additional functions if you want)

//The main function should get a postfix expression from the user and then
//follow the algorithm for building an expression tree from a postfix expression
//using a stack (see the project writeup). It should then ask the user
//whether they want to convert to prefix or postfix, and should call the
//appropriate traversal function on the expression tree to do the conversion.
//Finally, it should evaluate the expression tree and print the result.

//Your main function must declare an array of function pointers to hold
//the two traversal functions. You should call the appropriate traversal
//function by treating the user input as an array index (minus an offset) value.
//See https://textbooks.cs.ksu.edu/cis308/7-chapter/7_3-arraysfnptrs/for more details.
//You will have a size-2 array of type trav_fn, which holds the values {inorder, preorder}.
//This will be similar to the textbook example with function allOps.


/*
 * Check if a string only contains numberic characters
 *
 * returns: 1 if numeric and 0 otherwise
 */
int IsNumber(char* str)
{
    for(int i = 0; i < strlen(str); i++)
    {
        // Return false if any char is not numeric
        if (!isdigit(str[i])) return 0;
    }
    return 1;
}

/*
 * Determine if a string contains an operation
 *
 * returns: the OP in the string, defaults to division 
 */
OP GetOperatorFromString(char* str)
{
    if (strstr(str, "+") != NULL) return PLUS;
    else if (strstr(str, "-") != NULL) return MINUS;
    else if (strstr(str, "*") != NULL) return TIMES;
    else return DIVIDE; 
}

int main()
{
    // Point to the two traversal functions in a function pointer
    trav_fn traversalArray[2] = {inorder, preorder};

    // Ask the user for an expression to evaluate with the tree
    char expression[100];
    int infixOrPrefix;
    printf("Enter postfix expression: ");
    fgets(expression, 100, stdin);
    printf("Enter 1 for infix, 2 for prefix: ");
    scanf("%d", &infixOrPrefix);
    // Offset their answer to match our array indicies
    infixOrPrefix--;

    // Construct expression tree from the postfix expression
    STACK* expressionTrees = init_stack();
    // For each number or operator from the postfix expression
    char *token;
    token = strtok(expression, " ");
    while (token != NULL) 
    {
        // Check if the piece is a number
        if (IsNumber(token))
        {
            // Create singleton tree and push to the stack
            int tokNum = atoi(token);
            TREE* singleton = create_singleton(tokNum);
            push(expressionTrees, singleton);
        }
        // When we have an operator
        else
        {
            OP tokOper = GetOperatorFromString(token);
            TREE* tree1 = pop(expressionTrees);
            TREE* tree2 = pop(expressionTrees);
            // Build a new tree from the operator and the two sub trees
            // Tree1 is the right, tree2 is the left
            TREE* newExpressionTree = build_tree(tokOper, tree2, tree1);
            // Push the new tree
            push(expressionTrees, newExpressionTree);
        }

        token = strtok(NULL, " ");
    } // After this loop the only item on the stack is the complete expression tree
    
    // call the appropriate traversal function on the expression tree to do the conversion.
    char traversalBuffer[100];
    traversalArray[infixOrPrefix](expressionTrees->top->data, traversalBuffer);

    // Finally, it should evaluate the expression tree and print the result.
    printf("%s\n", traversalBuffer);

    // Now calculate the expression and output
    int calc = evaluate(expressionTrees->top->data);
    printf("Answer: %d", calc);

    // Free the stack
    free_stack(expressionTrees);

    return 0;
}