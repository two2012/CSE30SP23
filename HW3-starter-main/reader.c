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

    int stats_flag = 0; /* keep track of whether -s flag is passed in or not */

    /* TODO: process named command line options using getopt and store the information
        in the appropriate local variables */
    int c;
    /* TODO: fill out this skeleton code calling getopt */
    while ((c = getopt(argc, argv, "sc:")) != -1)
    {
        switch (c)
        {

        case 's':
            stats_flag = 1;
            break;
        case 'c':
            in_cols = atoi(optarg);
            break;
        default:
            abort();
        }
    }

    /* TODO: process other command line arguments (list of output columns) */
    if (optind < argc)
    {
        // in_cols = atoi(argv[optind]);
        // optind++;
        out_cols = argc - optind;
        obuf = (int *)malloc(out_cols * sizeof(int));
        for (int i = 0; i < out_cols; i++)
        {
            obuf[i] = atoi(argv[optind]);
            optind++;
        }
    }

    /* TODO: allocate arrays dynamically */
    buf = (char **)malloc(in_cols * sizeof(char *));
    size_t readbuffer_size = 0;

    /* TODO: parse the input from stdin line by line and output
     the target columns as described in the writeup */
    while (getline(&readbuffer, &readbuffer_size, stdin) != -1)
    {
        linecnt++;
        char *tok = strtok(readbuffer, " \t\n");
        int col = 0;
        while (tok != NULL)
        {
            buf[col] = tok;
            col++;
            tok = strtok(NULL, " \t\n");
        }

        for (int i = 0; i < out_cols; i++)
        {
            int idx = obuf[i];
            if (idx < col)
            {
                printf("%s", buf[idx]);
                if (i < out_cols - 1)
                {
                    printf(" ");
                }
                if (strlen(buf[idx]) > lngst_fld)
                {
                    lngst_fld = strlen(buf[idx]);
                }
            }
        }
        printf("\n");
    }

    /* TODO: use this line to print out the statistics when -s flag is set */
    if (stats_flag)
    {
        printf("Number of lines: %d\nLongest field: %d characters\n", linecnt, lngst_fld);
    }

    /* TODO: free the memory for arrays allocated with malloc */
    free(readbuffer);
    free(obuf);
    free(buf);

    return EXIT_SUCCESS;
}
