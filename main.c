#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parser.h"
#include "graph.h"

/* Removing spaces from input */
void remove_spaces(const char *input, char *output) {
    int i;
    int j = 0;
    for (i = 0; input[i] != '\0'; i++) {
        if (!isspace(input[i])) { /* Skipping spaces */
            output[j++] = input[i];
        }
    }
    output[j] = '\0'; /* Adding null terminator at the end */
}

int main(int argc, char *argv[]) {
    if (argc < 3) { /* If there is not enough arguments, error is printed out */
        fprintf(stderr, "Usage: %s <expression> <output file> [<limits>]\n", argv[0]);
        return 1;
    }

    /* Input expression with spaces removed */
    char clean_expression[1024];
    remove_spaces(argv[1], clean_expression);

    /* Output file */
    const char *out_file = argv[2];

    /* Check if the output file can be created */
    FILE *file = fopen(out_file, "w");
    if (!file) {
        fprintf(stderr, "Cannot create or write to file: %s\n", out_file);
        return 3;
    }
    fclose(file);

    /* Check if the output file name ends with ".ps" */
    const char *ps_extension = ".ps";
    size_t out_file_len = strlen(out_file);
    size_t ps_extension_len = strlen(ps_extension);
    if (out_file_len < ps_extension_len || strcmp(out_file + out_file_len - ps_extension_len, ps_extension) != 0) {
        fprintf(stderr, "Output file must have a .ps extension: %s\n", out_file);
        remove(out_file); /* Remove the file */
        return 3; 
    }

    /* Default limits if they are not set in the input argument */
    double x_min = -10, x_max = 10, y_min = -5, y_max = 5;

    /* If limits are specified, process them */
    if (argc == 4) {
        if (sscanf(argv[3], "%lf:%lf:%lf:%lf", &x_min, &x_max, &y_min, &y_max) != 4) {
            fprintf(stderr, "Invalid limits format. Use x_min:x_max:y_min:y_max\n");
            return 4;
        }
    }

    /* Declare a pointer to Expression */
    Expression *expr = NULL;
    if (!parse_expression(clean_expression, &expr)) {
        fprintf(stderr, "Failed to parse expression: %s\n", clean_expression);
        return 2;
    }

    /* If the program fails generating a graph */
    if (!generate_graph(expr, out_file, x_min, x_max, y_min, y_max)) {
        fprintf(stderr, "Failed to generate graph\n");
        free_expression(expr);
        return 5;
    }

    free_expression(expr);
    return 0;
}
