#define _USE_MATH_DEFINES
#include "tokenizer.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

/* Tokenizes the input string into individual tokens */
int tokenize(const char *input, Token tokens[], int max_tokens) {
    int i = 0, token_count = 0;

    while (input[i] != '\0' && token_count < max_tokens) {
        /* Handle constants */
        if (isdigit(input[i]) || input[i] == '.') {
            char buffer[32];
            int j = 0;

            /* Processing the numerical part */
            while (isdigit(input[i]) || input[i] == '.') {
                buffer[j++] = input[i++];
            }

            /* Processing scientific notation */
            if (input[i] == 'E') {
                buffer[j++] = input[i++];
                if (input[i] == '+' || input[i] == '-') { /* Handling the sign of the exponent */
                    buffer[j++] = input[i++];
                }
                while (isdigit(input[i])) { /* Processing the digits of the exponent */
                    buffer[j++] = input[i++];
                }
            }

            buffer[j] = '\0';

            tokens[token_count].type = TOKEN_CONSTANT;
            tokens[token_count].value = atof(buffer);
            token_count++;
        }

        /* Handle variables and functions */
        else if (isalpha(input[i])) {
            char buffer[16];
            int j = 0;

            while (isalpha(input[i])) {
                buffer[j++] = input[i++];
            }
            buffer[j] = '\0';

            /* Check if the token is a variable */
            if (strcmp(buffer, "x") == 0) {
                tokens[token_count].type = TOKEN_VARIABLE;
                token_count++;
            }

            /* Check if the token is a function */
            else if (strcmp(buffer, "sin") == 0 || strcmp(buffer, "cos") == 0 || strcmp(buffer, "tan") == 0 ||
                       strcmp(buffer, "asin") == 0 || strcmp(buffer, "acos") == 0 || strcmp(buffer, "atan") == 0 ||
                       strcmp(buffer, "sinh") == 0 || strcmp(buffer, "cosh") == 0 || strcmp(buffer, "tanh") == 0 ||
                       strcmp(buffer, "ln") == 0 || strcmp(buffer, "log") == 0 || strcmp(buffer, "abs") == 0) {
                tokens[token_count].type = TOKEN_FUNCTION;
                strncpy(tokens[token_count].func, buffer, 15);
                tokens[token_count].func[15] = '\0';
                token_count++;

                /* Ensure the function is followed by an opening parenthesis */
                if (input[i] != '(') {
                    fprintf(stderr, "Function '%s' must be followed by '('.\n", buffer);
                    return -1;
                }
            } else {
                fprintf(stderr, "Unknown token: %s\n", buffer);
                return -1;
            }
        }

        /* Handle operators and parentheses */
        else if (strchr("+-*/^()", input[i])) {
            tokens[token_count].type = (input[i] == '(' || input[i] == ')') ? TOKEN_PARENTHESIS : TOKEN_OPERATOR;
            tokens[token_count].op = input[i];
            token_count++;
            i++;
        } 
        
        else {
            /* Handle unknown characters */
            fprintf(stderr, "Unknown character: %c\n", input[i]);
            return -1;
        }

        /* Handle implicit multiplication between tokens */
        if (token_count > 0) {
            Token prev = tokens[token_count - 1];
            char next_char = input[i];

            /* Conditions for implicit multiplication */
            if ((prev.type == TOKEN_CONSTANT || prev.type == TOKEN_VARIABLE || 
                 (prev.type == TOKEN_PARENTHESIS && prev.op == ')')) &&
                (isalpha(next_char) || next_char == '(')) {
                if (token_count >= max_tokens) {
                    fprintf(stderr, "Too many tokens\n");
                    return -1;
                }
                tokens[token_count].type = TOKEN_OPERATOR;
                tokens[token_count].op = '*';
                token_count++;
            }
        }
    }

    return token_count;
}
