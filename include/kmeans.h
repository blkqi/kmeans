#ifndef __KMEANS_INCLUDED_H__
#define __KMEANS_INCLUDED_H__

#include <stdio.h>  // printf
#include <math.h>   // fabs, INFINITY
#include <stdlib.h> 
#include <string.h>
#include <assert.h>

#include "readcsv.h"
#include "norm.h"

//  -------------------------------------------------------------------------
//  Convergence tolerance
//
#   define TOL 1.0e-5

//  -------------------------------------------------------------------------
#   define MAX_N 2000  // maximum possible number of fields
#   define MAX_M 32    // longest possible field + 1 = 31 byte field


#endif
