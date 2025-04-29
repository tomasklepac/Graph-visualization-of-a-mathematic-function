#include <math.h>
#include <string.h>
#include "math_ops.h"
#include "expression.h"

/* Recursively evaluates a mathematical expression represented as an expression tree */
double evaluate_expression(Expression *expr, double x) {
    /* If the node is a constant, return its value */
    if (expr->type == NODE_CONSTANT) {
        return expr->value;
    } 
    /* If the node is a variable, return the value of 'x' */
    else if (expr->type == NODE_VARIABLE) {
        return x;
    } 
    /* If the node is an operator, evaluate its operands */
    else if (expr->type == NODE_OPERATOR) {
        double left_val = evaluate_expression(expr->left, x); /* Evaluate left operand */
        double right_val = expr->right ? evaluate_expression(expr->right, x) : 0; /* Evaluate right operand (if exists) */

        /* Perform the operation based on the operator */
        switch (expr->op) {
            case '+': return left_val + right_val; /* Addition */
            case '-': return expr->right ? left_val - right_val : -left_val; /* Subtraction or unary minus */
            case '*': return left_val * right_val; /* Multiplication */
            case '/': return right_val != 0 ? left_val / right_val : 0; /* Avoid division by zero */
            case '^': return pow(left_val, right_val); /* Exponentiation */
        }
    } 
    /* If the node is a function, evaluate its argument */
    else if (expr->type == NODE_FUNCTION) {
        double arg = evaluate_expression(expr->left, x); /* Evaluate the argument of the function */

        /* Check which function to apply */
        if (strcmp(expr->func, "sin") == 0) return sin(arg);
        if (strcmp(expr->func, "cos") == 0) return cos(arg);
        if (strcmp(expr->func, "tan") == 0) return tan(arg);
        if (strcmp(expr->func, "asin") == 0) return asin(arg);
        if (strcmp(expr->func, "acos") == 0) return acos(arg);
        if (strcmp(expr->func, "atan") == 0) return atan(arg);
        if (strcmp(expr->func, "sinh") == 0) return sinh(arg);
        if (strcmp(expr->func, "cosh") == 0) return cosh(arg);
        if (strcmp(expr->func, "tanh") == 0) return tanh(arg);
        if (strcmp(expr->func, "ln") == 0) return log(arg); /* Natural logarithm */
        if (strcmp(expr->func, "log") == 0) return log10(arg); /* Base-10 logarithm */
        if (strcmp(expr->func, "abs") == 0) return fabs(arg); /* Absolute value */
    }

    /* Return 0 if the expression is invalid or cannot be evaluated */
    return 0;
}
