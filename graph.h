#ifndef GRAPH_H
#define GRAPH_H

#include "expression.h"

/*
 * Generates a graph based on the given expression and range.
 * The graph is saved to a specified output file in PostScript format.
 *
 * Parameters:
 * - expr: Pointer to the root of the expression tree.
 * - out_file: The name of the output file.
 * - x_min, x_max: The range of the x-axis.
 * - y_min, y_max: The range of the y-axis.
 *
 * Returns:
 * - 1 if the graph generation is successful, otherwise 0.
 */
int generate_graph(Expression *expr, const char *out_file, double x_min, double x_max, double y_min, double y_max);

#endif
