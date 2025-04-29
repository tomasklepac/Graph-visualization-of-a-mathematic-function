#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "graph.h"
#include "expression.h"
#include "math_ops.h"

/* Generates a graph from the given mathematical expression within the specified ranges */
int generate_graph(Expression *expr, const char *out_file, double x_min, double x_max, double y_min, double y_max) {
    /* Fixed size for the output area */
    int width = 800;
    int height = 600;

    /* Open the output file for writing */
    FILE *file = fopen(out_file, "w");
    if (!file) {
        return 0; /* Error while opening the file */
    }

    /* Write PostScript file header */
    fprintf(file, "%%!PS-Adobe-3.0\n");
    fprintf(file, "%%%%BoundingBox: 0 0 %d %d\n", width, height);

    /* Center the graph on the page */
    fprintf(file, "%d %d translate\n", (int)(width / 2.5), height);

    /* Fixed rectangle size for the graph */
    double rect_width = width * 0.6;  /* 60% of the page width */
    double rect_height = height * 0.6; /* 60% of the page height */

    /* Draw the rectangle representing the graph area */
    fprintf(file, "newpath\n");
    fprintf(file, "%f %f moveto\n", -rect_width / 2.0, -rect_height / 2.0); /* Bottom-left corner */
    fprintf(file, "%f %f lineto\n", rect_width / 2.0, -rect_height / 2.0);  /* Bottom-right corner */
    fprintf(file, "%f %f lineto\n", rect_width / 2.0, rect_height / 2.0);   /* Top-right corner */
    fprintf(file, "%f %f lineto\n", -rect_width / 2.0, rect_height / 2.0);  /* Top-left corner */
    fprintf(file, "closepath stroke\n");

    /* Setting distances of ticks on the axes */
    double x_step = (x_max - x_min) / 5.0;
    double y_step = (y_max - y_min) / 5.0;

    /* Set line width for the ticks */
    fprintf(file, "0.5 setlinewidth\n");

    /* Add ticks on the bottom and top sides */
    double x;
    for (x = x_min; x <= x_max; x += x_step) {
        double px = (x - x_min) / (x_max - x_min) * rect_width - rect_width / 2.0;
        /* Bottom side */
        fprintf(file, "newpath\n");
        fprintf(file, "%f %f moveto %f %f lineto stroke\n", px, -rect_height / 2.0, px, -rect_height / 2.0 + 5);
        /* Top side (without labels) */
        fprintf(file, "newpath\n");
        fprintf(file, "%f %f moveto %f %f lineto stroke\n", px, rect_height / 2.0, px, rect_height / 2.0 - 5);
    }

    /* Add ticks on the left and right side */
    double y;
    for (y = y_min; y <= y_max; y += y_step) {
        double py = (y - y_min) / (y_max - y_min) * rect_height - rect_height / 2.0;
        /* Left side */
        fprintf(file, "newpath\n");
        fprintf(file, "%f %f moveto %f %f lineto stroke\n", -rect_width / 2.0, py, -rect_width / 2.0 + 5, py);
        /* Right side (without labels) */
        fprintf(file, "newpath\n");
        fprintf(file, "%f %f moveto %f %f lineto stroke\n", rect_width / 2.0, py, rect_width / 2.0 - 5, py);
    }

    /* Add axis labels */
    fprintf(file, "/Times-Roman findfont 10 scalefont setfont\n");

    /* X-axis labels */
    for (x = x_min; x <= x_max; x += x_step) {
        double px = (x - x_min) / (x_max - x_min) * rect_width - rect_width / 2.0;
        fprintf(file, "%f %f moveto (%g) show\n", px, -rect_height / 2.0 - 15, x);
    }

    /* Y-axis labels */
    for (y = y_min; y <= y_max; y += y_step) {
        double py = (y - y_min) / (y_max - y_min) * rect_height - rect_height / 2.0;
        fprintf(file, "%f %f moveto (%g) show\n", -rect_width / 2.0 - 20, py, y);
    }

    /* Add axis titles */
    fprintf(file, "newpath\n");
    fprintf(file, "/Times-Roman findfont 12 scalefont setfont\n");
    fprintf(file, "%d %f moveto (x) show\n", 0, -rect_height / 2.0 - 30); /* X-axis title */
    fprintf(file, "%f %d moveto (f(x)) show\n", -rect_width / 2.0 - 50, 0); /* Y-axis title */

    /* Set line color to blue for the graph */
    fprintf(file, "0 0 1 setrgbcolor\n");

    /* Draw the graph within the rectangle */
    fprintf(file, "newpath\n");
    int first_point = 1; /* Flag to check if the first point has been plotted */
    double step = (x_max - x_min) / 100000;
    for (x = x_min; x <= x_max; x += step) {
        double y_value = evaluate_expression(expr, x);

        /* Check the value of y */
        int max_y = 1000000;
        if (fabs(y_value) > max_y || y_value != y_value || fabs(y_value) > DBL_MAX) {
            first_point = 1; /* Break the line if y is invalid */
            continue;
        }

        if (y_value >= y_min && y_value <= y_max) { /* Only plot points within the rectangle */
            double px = (x - x_min) / (x_max - x_min) * rect_width - rect_width / 2.0;
            double py = (y_value - y_min) / (y_max - y_min) * rect_height - rect_height / 2.0;
            if (first_point) {
                fprintf(file, "%f %f moveto\n", px, py);
                first_point = 0;
            } else {
                fprintf(file, "%f %f lineto\n", px, py);
            }
        }
    }
    fprintf(file, "stroke\n");

    /* End the PostScript file */
    fprintf(file, "showpage\n");
    fclose(file);
    return 1;
}
