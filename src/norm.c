#include "kmeans.h"
//  -------------------------------------------------------------------------
//  Matrix infinity norm (nxm)
//

double norm (double *matrix, int n, int m)
{
    double column_sum [n];
    double max = 0, test = 0;
    int i, j;

    for (i = 0; i < n; ++i) {
        column_sum[i] = 0;

        for (j = 0; j < m; ++j)
            column_sum[i] += matrix[i*m+j];

        if ((test = fabs (column_sum [i])) > max)
            max = test;
    }

    return max;
}
