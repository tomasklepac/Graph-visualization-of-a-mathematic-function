#ifndef PARSER_H
#define PARSER_H

#include "tokenizer.h"
#include "expression.h"

/*
 * Converts tokens from infix notation to postfix notation (RPN).
 *
 * Parameters:
 * - tokens: Input tokens in infix notation.
 * - token_count: Number of input tokens.
 * - output: Array for output tokens in postfix notation.
 * - max_output: Maximum size of the output array.
 *
 * Returns:
 * - Number of tokens in postfix notation, or -1 if an error occurred.
 */
int to_postfix(Token tokens[], int token_count, Token output[]);

/*
 * Builds an expression tree from tokens in postfix notation.
 *
 * Parameters:
 * - postfix: Array of tokens in postfix notation.
 * - count: Number of tokens.
 *
 * Returns:
 * - Root of the expression tree, or NULL if an error occurred.
 */
Expression* build_expression_tree(Token postfix[], int count);

/*
 * Parses a mathematical expression and creates an expression tree.
 *
 * Parameters:
 * - func_str: String containing the mathematical expression.
 * - expr: Pointer to a pointer for storing the root of the tree.
 *
 * Returns:
 * - 1 if parsing is successful, otherwise 0.
 */
int parse_expression(const char *func_str, Expression **expr);

/*
 * Frees the memory allocated for the expression tree.
 *
 * Parameters:
 * - expr: Root of the expression tree.
 */
void free_expression(Expression *expr);

#endif
