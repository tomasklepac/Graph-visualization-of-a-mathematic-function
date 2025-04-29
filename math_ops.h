#ifndef MATH_OPS_H
#define MATH_OPS_H

#include "expression.h"

/*
 * Evaluates a mathematical expression represented as an expression tree.
 *
 * Parameters:
 * - expr: Pointer to the root of the expression tree.
 * - x: The value of the variable 'x' used in the expression (if applicable).
 *
 * Returns:
 * - The result of evaluating the expression.
 */
double evaluate_expression(Expression *expr, double x);

#endif