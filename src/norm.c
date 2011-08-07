/** =========================================================================
    norm - Get infinity norm of an nxm matrix
    -------------------------------------------------------------------------
    @author Brett L. Kleinschmidt <blk@blk.me>
    @copyright Copyright (c) 2010-2011, Brett L. Kleinschmidt

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published
    by the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    For Support, please visit http://blk.me/
     -------------------------------------------------------------------------
*/
#   include "kmeans.h"
//  -------------------------------------------------------------------------
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
