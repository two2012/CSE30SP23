#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZE 256
int main(int argc, char **argv)
{

    int in_cols = 0;  /* number of columns in input */
    int out_cols = 0; /* number of columns to output */

    /* readbuffer need to be initialized to NULL for getline to work properly */
    char *readbuffer = NULL; /* read buffer for processing lines in input */

    /* pointers to arrays which will be allocated dynamically by you */
    char **buf = NULL; /* pointer to array of pointers to the start of
                             each field in input buffer */
    int *obuf = NULL;  /* pointer to array of output indices */

    /* local variables to store the statistics */
    unsigned int linecnt = 0;   /* number of lines in input */
    unsigned int lngst_fld = 0; /* longest field in input */

    int stats_flag = 0; /* keep track of whether -s flag is passed in or not* /

    /* TODO: process named command line options using getopt and store the information
        in the appropriate local variables */
    int c;
    /* TODO: fill out this skeleton code calling getopt */
    while ((c = getopt(argc, argv, "")) != -1)
    {
        switch (c)
        {
        case '':
            break;
        default:
            abort();
        }
    }

    /* TODO: process other command line arguments (list of output columns) */

    /* TODO: allocate arrays dynamically */

    /* TODO: parse the input from stdin line by line and output
     the target columns as described in the writeup */

    /* TODO: use this line to print out the statistics when -s flag is set */
    printf("Number of lines: %d\nLongest field: %d characters\n", linecnt, lngst_fld);

    /* TODO: free the memory for arrays allocated with malloc */
}
