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

#include <stdio.h>  // printf
#include <math.h>   // INFINITY macro

//  matrix (nxm) infinity norm
double norm (double *matrix, int n, int m);

//  -------------------------------------------------------------------------
//  Convergence tolerance
//
#   define TOL 1.0e-5

//  -------------------------------------------------------------------------
//  Sample data
//
#   define D_N 27
#   define D_M 2

static const double 
data [D_N][D_M] = {
    { 340, 2.6 },
    { 245, 2.7 },
    { 420, 2.0 },
    { 375, 2.6 },
    { 180, 3.7 },
    { 115, 1.4 },
    { 170, 1.5 },
    { 160, 5.9 },
    { 265, 2.6 },
    { 300, 2.3 },
    { 340, 2.5 },
    { 340, 2.5 },
    { 355, 2.4 },
    { 205, 2.5 },
    { 185, 2.7 },
    { 135, 0.6 },
    {  70, 6.0 },
    {  45, 5.4 },
    {  90, 0.8 },
    { 135, 0.5 },
    { 200, 1.0 },
    { 155, 1.8 },
    { 195, 1.3 },
    { 120, 0.7 },
    { 180, 2.5 },
    { 170, 1.2 },
    { 110, 2.6 }
};


//  -------------------------------------------------------------------------
//  Initial centroids
//
#   define C_N 3
#   define C_M D_M

static double 
centroids [C_N][C_M] = {
    { 100, 6.0 },
    { 300, 3.0 },
    { 150, 1.0 }
};


//  -------------------------------------------------------------------------
//  k-means routine
int main ()
{
    int clusters [D_N]; // cluster classification
    double cent_last [C_N][C_M]; // centroids (last iteration)

    int i=0, j=0, k=0;
    double c=0.0, d=0.0, d_min=INFINITY;

    //
    //  Iterate, converge absolutely

    do  //
    {   //  For each observation, calculate the distance from
        //  each centroid and then cluster by the nearest one

        int cluster_pop [C_N] = { 0 }; // cluster populations

        for (i = 0; i < D_N; ++i) {
            d_min = INFINITY;

            for (j = 0; j < C_N; ++j) {
                //  calculate distance to centroid j
                d = 0.0;

                for (k = 0; k < D_M; ++k) {
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
        double data_sum [C_N][C_M] = { 0 };

        for (i = 0; i < D_N; ++i)
            for (k = 0; k < D_M; ++k)
                data_sum[clusters[i]][k] += data[i][k];

        //  centroid coordinate is mean of the column
        for (j = 0; j < C_N; ++j) {
            for (k = 0; k < D_M; ++k) {
                cent_last[j][k] = centroids[j][k];
                centroids[j][k] = data_sum[j][k] / cluster_pop[j];
            }
        }

    //  displacement-->0 (n-->inf)
    } while (norm(*centroids, C_N, C_M) - norm(*cent_last, C_N, C_M) > TOL);

    //
    //  Printout final centroid coordinates

    for (j = 0; j < C_N; ++j) {
        printf ("c[%d] = {", j);
        for (k = 0; k < C_M; ++k)
            printf ("%8.3f ", centroids[j][k]);
        printf ("}\n");
    }

    return 0;
}


//  -------------------------------------------------------------------------
//  Matrix (infinity) norm
//  nxm

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
