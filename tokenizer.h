#ifndef TOKENIZER_H
#define TOKENIZER_H

/* Token types */
typedef enum {
    TOKEN_OPERATOR,     /* Represents an operator */
    TOKEN_FUNCTION,     /* Represents a function */
    TOKEN_CONSTANT,     /* Represents a constant */
    TOKEN_VARIABLE,     /* Represents a variable */
    TOKEN_PARENTHESIS   /* Represents a parenthesis */
} TokenType;

/* Structure of a token */
typedef struct {
    TokenType type;     /* Type of the token */
    char op;            /* Operator */
    double value;       /* Value of constants */
    char func[16];      /* Function name */
} Token;

/*
 * Splits the input string into individual tokens.
 *
 * Parameters:
 * - input: Input string containing the expression.
 * - tokens: Array to store the extracted tokens.
 * - max_tokens: Maximum size of the token array.
 *
 * Returns:
 * - The number of tokens in the array, or -1 if an error occurs.
 */
int tokenize(const char *input, Token tokens[], int max_tokens);

#endif
