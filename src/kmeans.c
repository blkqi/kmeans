/** =========================================================================
    k-means - clusters a multivaraite dataset into N neighborhoods
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

#include "kmeans.h"

//  -------------------------------------------------------------------------
//  k-means routine
int main (int argc, char *argv[])
{
    int d_n=0, d_m=0;
    int c_n=0, c_m=0;
    
    //  read data from file
	double data [MAX_N][MAX_M] = { 0 };
    readcsv (argv[1], *data, &d_n, &d_m);
 
    //  read centroids from file
	double centroids [MAX_N][MAX_M] = { 0 };
    readcsv (argv[2], *centroids, &c_n, &c_m);
 
    assert (d_m == c_m);

    int clusters [d_n]; // cluster classification
    double cent_last [c_n][c_m]; // centroids (last iteration)

    int i=0, j=0, k=0;
    double c=0.0, d=0.0, d_min=INFINITY;

    //
    //  Iterate, converge absolutely

    do  //
    {   //  For each observation, calculate the distance from
        //  each centroid and then cluster by the nearest one

        int cluster_pop [c_n]; // cluster populations
        memset (cluster_pop, 0, c_n*sizeof(int));

        for (i = 0; i < d_n; ++i) {
            d_min = INFINITY;

            for (j = 0; j < c_n; ++j) {
                //  calculate distance to centroid j
                d = 0.0;

                for (k = 0; k < d_m; ++k) {
                    c = data[i][k] - centroids[j][k];
                    d += c * c;
                }
                //  minize distance d
                if (d < d_min) {
                    d_min = d;
                    clusters[i] = j;
                }
            }
            //  add element its nearest cluster
            ++cluster_pop[clusters[i]];
        }

        //
        //  Calculate new centroids

        //  data column sum for each cluster
        double data_sum [c_n][c_m];
        memset (data_sum, 0, c_n*c_m*sizeof(double));

        for (i = 0; i < d_n; ++i)
            for (k = 0; k < d_m; ++k)
                data_sum[clusters[i]][k] += data[i][k];

        //  centroid coordinate is mean of the column
        for (j = 0; j < c_n; ++j) {
            for (k = 0; k < d_m; ++k) {
                cent_last[j][k] = centroids[j][k];
                centroids[j][k] = data_sum[j][k] / cluster_pop[j];
            }
        }

    //  displacement-->0 (n-->inf)
    } while (norm(*centroids, c_n, c_m) - norm(*cent_last, c_n, c_m) > TOL);

    //
    //  Printout final centroid coordinates

    printf ("data (%ix%i)\n", d_n, d_m);
    for (i = 0; i < d_n; ++i) {
        printf ("%5i  { ", i);
        for (j = 0; j < d_m; ++j)
			printf ("%7.3f ", data[i][j]);
        printf ("}  --> %2i\n", clusters[i]);
    }

    printf ("centroids (%ix%i)\n", d_n, d_m);
    for (j = 0; j < c_n; ++j) {
        printf ("%5i  {", j);
        for (k = 0; k < c_m; ++k)
            printf ("%8.3f ", centroids[j][k]);
        printf ("}\n");
    }

    return 0;
}

