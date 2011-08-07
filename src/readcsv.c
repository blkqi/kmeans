#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_N 2000   // maximum possible number of fields
#define MAX_M 32  // longest possible field + 1 = 31 byte field
 
void parse (char *record, const char *delim, double data[], int *m)
{
    *m = 0;
    char *p = strtok (record, delim);
    while (p) {
        data[(*m)++] = atof (p);
		p = strtok (0, delim);
	}
}
 
void readcsv (char *file, double data[], int *n, int *m)
{
    //  open csv file
	FILE *in = fopen(file, "r");
	if (!in) {
		perror ("File open error");
		exit (EXIT_FAILURE);
	}

    *n = 0; *m = 0;
	int cols = 0;

    //  parse line-by-line
	char tmp [1024] = { 0 };
	while (fgets (tmp, sizeof(tmp), in) != 0) {
		parse (tmp, ", \n", &data[(*n)*(*m)*(*m)*sizeof(double)], &cols);
        if (cols > *m) // nbr cols is max nbr cols
            *m = cols;
        if (cols > 0) // skip blank lines
            ++(*n);
    }
}
