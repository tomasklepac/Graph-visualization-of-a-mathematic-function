#ifndef EXPRESSION_H
#define EXPRESSION_H

/*
 * Enum defining the types of nodes in an expression tree
 * - NODE_CONSTANT: Represents a numerical constant
 * - NODE_VARIABLE: Represents a variable
 * - NODE_OPERATOR: Represents an operator
 * - NODE_FUNCTION: Represents a mathematical function
 */
typedef enum {
    NODE_CONSTANT,
    NODE_VARIABLE,
    NODE_OPERATOR,
    NODE_FUNCTION
} NodeType;

/*
 * Structure representing a node in the expression tree
 * Each node can represent a constant, variable, operator, or function
 * The structure includes pointers to the left and right child nodes for building the tree
 */
typedef struct Expression {
    NodeType type;  /* The type of the node */
    union {
        double value;  /* Value for constants */
        char op;       /* Operator for operator nodes */
        char func[10]; /* Function name for function nodes */
    };
    struct Expression *left;  /* Pointer to the left child node */
    struct Expression *right; /* Pointer to the right child node */
} Expression;

#endif
