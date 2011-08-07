/** =========================================================================
    k-means - Partition n observations into k clusters
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

int main (int argc, char *argv[])
{
    if (argc < 3) {
        printf ("usage: kmeans [data] [centroids]\n");
        return 1;
    }

    //  read data from file
    int d_n=0, d_m=0;
    double data [MAX_N][MAX_M] = { 0 };
    readcsv (argv[1], data, &d_n, &d_m);
 
    //  read centroids from file
    int c_n=0, c_m=0;
    double centroids [MAX_N][MAX_M] = { 0 };
    readcsv (argv[2], centroids, &c_n, &c_m);
 
    if (d_n < c_n) {
        fprintf (stderr, "error: More clusters than data\n");
        return 1;
    }
    if (d_m != c_m) {
        fprintf (stderr, "error: Data and centroid dimensionalities differ\n");
        return 1;
    }

    int clusters [d_n]; // assigned cluster of datum
    int cluster_pop [c_n]; // population of cluster
    double data_sum [c_n][c_m]; // data column sum of cluster
    double cent_last [c_n][c_m]; // centroids (last iteration)

    int i, j, k;
    double dist, dist_min, c;

    //
    //  Iterate, converge absolutely

    do  //
    {   //  For each observation, calculate the distance from
        //  each centroid and then cluster by the nearest one

        memset (cluster_pop, 0, c_n*sizeof(int));

        for (i = 0; i < d_n; ++i) {
            dist_min = INFINITY;
            // assume distance minimum is +inf
            for (j = 0; j < c_n; ++j) {
                dist = 0.0;
                //  calculate distance to centroid j
                for (k = 0; k < d_m; ++k) {
                    c = data[i][k] - centroids[j][k];
                    dist += c * c;
                }
                //  minimize distance
                if (dist < dist_min) {
                    dist_min = dist;
                    clusters[i] = j;
                }
            }
            //  add element its nearest cluster
            ++cluster_pop[clusters[i]];
        }

        //
        //  Calculate new centroids

        memset (data_sum, 0, c_n*c_m*sizeof(double));

        //  sum data columns per cluster
        for (i = 0; i < d_n; ++i)
            for (k = 0; k < d_m; ++k)
                data_sum[clusters[i]][k] += data[i][k];

        //  centroid coordinate is mean of corresponding column
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
    printf ("centroids (%ix%i)\n", c_n, c_m);
    for (j = 0; j < c_n; ++j) {
        printf ("%5i  { ", j);
        for (k = 0; k < c_m; ++k)
            printf ("%7.3f ", centroids[j][k]);
        printf ("}\n");
    }

    return 0;
}


