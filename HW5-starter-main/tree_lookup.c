#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "node.h"

#define MIN_TAB_SZ 3
#define DEFAULT_TAB_SZ 1873
#define QUERY_SUCCESS_FORMAT "found tree id=%s, x=%.5f, y=%.5f\n" 
#define QUERY_FAILURE_FORMAT "could not find tree with id=%s\n"

int main(int argc, char **argv) {
	int s_flag;
	unsigned long tabsz;
	// TODO: parse opts with getopt and initialize these variables 
	// (see strtoul for parsing unsigned long)
	int opt;
	while ((opt = getopt(argc, argv, "st:")) != -1)
	{
		switch (opt)
		{
			case 's':
				s_flag = 1;
				break;
			case 't':
				tabsz = strtoul(optarg, NULL, 10);
				if (tabsz < MIN_TAB_SZ)
				{
					tabsz = DEFAULT_TAB_SZ;
				}
				break;
		}
	}

	
	// TODO: initialze htable
	// using calloc so all buckets are initialized to NULL
	node **htable = calloc(tabsz, sizeof(node*));
	if (htable == NULL) {
		return EXIT_FAILURE;
	}
	
	// TODO: get filename and call load_table;
	
	char *filename = argv[optind];

	if (load_table(htable, tabsz, filename) != 0) {
		fprintf(stderr, "error in load_table\n");
		free(htable);
		return EXIT_FAILURE;
	}
	
	size_t bufsz = 0;
	char *buf = NULL; 
	
	// read one line at a time from stdin, do a lookup for that id
	// 
	ssize_t bytes;
	int successful_queries = 0;
	while ((bytes = getline(&buf, &bufsz, stdin)) > 0) {
		// replace the \n, if it exists (for hashing)
		if (buf[bytes - 1] == '\n') buf[bytes - 1] = '\0';

		// TODO: read a line from stdin and perform a lookup
		// if the tree is found, print its x and y to stdout
		// using QUERY_SUCCESS_FORMAT
		//
		unsigned long hashed_id = hash(buf);
		node *found = node_lookup(htable[hashed_id % tabsz], buf);
		if (found != NULL)
		{
			printf(QUERY_SUCCESS_FORMAT, found->id, found->xcoord, found->ycoord);
			successful_queries++;
		}
		else
		{
			// if the tree is not found, print a message to **stdout**
			// using QUERY_FAILURE_FORMAT
			printf(QUERY_FAILURE_FORMAT, buf);
		}
		
		// keep track of the number of successful queries
	}
	printf("%d successful queries\n", successful_queries);

	// if -s called then print stats
	if (s_flag) {
		// TODO: output the stats
		print_info(htable, tabsz);

	}

	// TODO: free all allocated memory associated with the table 
	// using delete_table()
	delete_table(htable, tabsz);
	free(buf);  // free the buffer allocated by getline()

	return EXIT_SUCCESS;
}



