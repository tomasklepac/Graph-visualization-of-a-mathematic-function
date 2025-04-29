#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"

/* Converts a list of tokens from infix notation to postfix notation (RPN) */
int to_postfix(Token tokens[], int token_count, Token output[]) {
    Token stack[64];
    int stack_top = -1, output_count = 0;

    int i;
    for (i = 0; i < token_count; i++) {
        Token t = tokens[i];

        /* If the token is a constant or variable, add it directly to the output */
        if (t.type == TOKEN_CONSTANT || t.type == TOKEN_VARIABLE) {
            output[output_count++] = t;
        } 
        /* If the token is a function, push it onto the stack */
        else if (t.type == TOKEN_FUNCTION) {
            stack[++stack_top] = t;
        } 
        /* If the token is an operator, handle operator precedence */
        else if (t.type == TOKEN_OPERATOR) {
            while (stack_top >= 0 && ((stack[stack_top].type == TOKEN_OPERATOR && strchr("^", t.op) == NULL) || (stack[stack_top].type == TOKEN_OPERATOR && strchr("^", t.op) != NULL && t.op != '^')) && stack[stack_top].op != '(') {
                output[output_count++] = stack[stack_top--];
            }
            stack[++stack_top] = t;
        } 
        /* If the token is a left parenthesis, push it onto the stack */
        else if (t.op == '(') {
            stack[++stack_top] = t;
        } 
        /* If the token is a right parenthesis, pop until the matching left parenthesis is found */
        else if (t.op == ')') {
            while (stack_top >= 0 && stack[stack_top].op != '(') {
                output[output_count++] = stack[stack_top--];
            }
            if (stack_top >= 0 && stack[stack_top].op == '(') {
                stack_top--; /* Remove the left parenthesis from the stack */
            }
            /* If a function is at the top of the stack, add it to the output */
            if (stack_top >= 0 && stack[stack_top].type == TOKEN_FUNCTION) {
                output[output_count++] = stack[stack_top--];
            }
        }
    }

    /* Pop remaining operators from the stack and add them to the output */
    while (stack_top >= 0) {
        if (stack[stack_top].op == '(' || stack[stack_top].op == ')') {
            fprintf(stderr, "Mismatched parentheses\n");
            return -1;
        }
        output[output_count++] = stack[stack_top--];
    }

    return output_count;
}

/* Builds an expression tree from a list of tokens in postfix notation */
Expression* build_expression_tree(Token postfix[], int count) {
    Expression* stack[64];
    int stack_top = -1;

    int i;
    for (i = 0; i < count; i++) {
        /* Retrieve the current token from the postfix array */
        Token t = postfix[i];

        /* Allocate memory for a new Expression node */
        Expression* node = malloc(sizeof(Expression));

        /* Check if memory allocation was successful */
        if (!node) {
            fprintf(stderr, "Memory allocation failed\n");
            return NULL;
        }

        /* Handle constants */
        if (t.type == TOKEN_CONSTANT) {
            node->type = NODE_CONSTANT;
            node->value = t.value;
            node->left = node->right = NULL;
        } 
        /* Handle variables */
        else if (t.type == TOKEN_VARIABLE) {
            node->type = NODE_VARIABLE;
            node->left = node->right = NULL;
        } 
        /* Handle operators, which require two operands */
        else if (t.type == TOKEN_OPERATOR) {
            node->type = NODE_OPERATOR;
            node->op = t.op;
            if (stack_top >= 1) {
                node->right = stack[stack_top--];
                node->left = stack[stack_top--];
            } else {
                fprintf(stderr, "Operator '%c' is missing operands.\n", t.op);
                free(node);
                return NULL;
            }
        } 
        /* Handle functions, which require one operand */
        else if (t.type == TOKEN_FUNCTION) {
            node->type = NODE_FUNCTION;
            strcpy(node->func, t.func);

            if (stack_top >= 0) {
                node->left = stack[stack_top--];
            } else {
                fprintf(stderr, "Function '%s' is missing an argument.\n", t.func);
                free(node);
                return NULL;
            }
            node->right = NULL;
        }

        /* Push the constructed node onto the stack */
        stack[++stack_top] = node;
    }

    /* Return the root of the tree */
    return stack_top >= 0 ? stack[stack_top] : NULL;
}

/* Parses a mathematical expression and creates an expression tree */
int parse_expression(const char *func_str, Expression **expr) {
    int max_size = 128;
    Token tokens[max_size];
    Token postfix[max_size];

    /* Tokenize the input string */
    int token_count = tokenize(func_str, tokens, max_size);
    if (token_count < 0) {
        fprintf(stderr, "Failed to tokenize expression.\n");
        return 0;
    }

    /* Convert the tokens to postfix notation */
    int postfix_count = to_postfix(tokens, token_count, postfix);
    if (postfix_count < 0) {
        fprintf(stderr, "Failed to convert to postfix notation.\n");
        return 0;
    }

    /* Build the expression tree from the postfix tokens */
    *expr = build_expression_tree(postfix, postfix_count);
    if (*expr == NULL) {
        fprintf(stderr, "Failed to build expression tree.\n");
        return 0;
    }

    return 1;
}

/* Frees the memory allocated for the expression tree */
void free_expression(Expression* expr) {
    if (expr) {
        if (expr->left) free_expression(expr->left);
        if (expr->right) free_expression(expr->right);
        free(expr);
    }
}
