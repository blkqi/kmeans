#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_N 2000   // maximum possible number of fields
#define MAX_M 32  // longest possible field + 1 = 31 byte field
 
void parse (char *record, const char *delim, char data[][MAX_M], int *m)
{
    char *p = strtok (record, delim);
    *m = 0;
    while (p) {
        strcpy (data[(*m)++], p);
		p = strtok (0, delim);
	}
}
 
void readcsv (char *file, char data[][MAX_M], int *n, int *m)
{
    *n = 0; *m = 0;
	char tmp [1024] = { 0 };
	int cols = 0;

    // open csv file
	FILE *in = fopen(file, "r");
	if (!in) {
		perror ("File open error");
		exit (EXIT_FAILURE);
	}

    // parse line-by-line
	while (fgets (tmp, sizeof(tmp), in) != 0) {
		parse (tmp, ", \n", data+((*m)*(*n)), &cols);
        if (cols > *m) // nbr cols is max nbr cols
            *m = cols;
        if (cols > 0) // skip blank lines
            ++(*n);
    }
}

int main (int argc, char *argv[])
{
    int n, m;
	char data [MAX_N][MAX_M] = { 0 };
    readcsv (argv[1], data, &n, &m);

    int i, j;
    printf ("%ix%i\n", n, m);
    for (i = 0; i < n; ++i) {
        printf ("{ ");
        for (j = 0; j < m; ++j)
			printf ("%s ", data[i*m+j]);
        printf ("}\n");
    }

    return 0;
}
