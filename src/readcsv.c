/** =========================================================================
    readcsv - Read data from comma separated value files
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
 
static void 
parse (char *record, const char *delim, double (*data)[MAX_M], int *m)
{
    *m = 0;
    char *p = strtok (record, delim);
    while (p) {
        (*data)[(*m)++] = atof (p);
        p = strtok (0, delim);
    }
}
 
void 
readcsv (char *file, double (*data)[MAX_M], int *n, int *m)
{
    //  open csv file
    FILE *in = fopen (file, "r");
    if (!in) {
        fprintf (stderr, "error: %s: ", file), perror(0);
        exit (EXIT_FAILURE);
    }

    int cols=0;
    *n = 0; *m = 0;

    //  parse line-by-line
    char tmp [1024] = { 0 };
    while (fgets (tmp, sizeof(tmp), in) != 0) {
        parse (tmp, ", \n", (data+(*n)), &cols);
        if (cols > *m) // nbr cols is max nbr cols
            *m = cols;
        if (cols > 0) // skip blank lines
            ++(*n);
    }
}
