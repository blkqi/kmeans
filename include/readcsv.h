#ifndef __READCSV_INCLUDED_H__
#define __READCSV_INCLUDED_H__

//  -------------------------------------------------------------------------
//  Max size of data buffer
//
#   define MAX_N 2000  // maximum possible number of fields
#   define MAX_M 32    // longest possible field + 1 = 31 byte field


//  Read csv file into double array
void 
    readcsv (char *file, double (*data)[MAX_M], int *n, int *m);

#endif
