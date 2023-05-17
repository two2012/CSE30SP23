#include <stdio.h>
#include <limits.h>
#include "node.h"

#define TABSZ_MSG "Table size: %lu\n"
#define TOTAL_ENTRIES_MSG "Total entries: %lu\n"
#define LONGEST_MSG "Longest chain: %lu\n"
#define SHORTEST_MSG "Shortest chain: %lu\n"
#define EMPTY_MSG "Empty buckets: %lu\n"
#define TREES_WITHIN_REGION_MSG "Total trees within given region: %lu\n"


void print_info(node **htable, unsigned long tabsz) {
	// TODO: walk down the indices of the htable
	// iterate through each chain and update statistics
	// print out statistics at end
	//
	// NOTE: all your statistics variables should be of type
	// unsigned long
	//
	// NOTE: you may use ULONG_MAX if you want
	// (maximum value for unsigned long int)
	
	unsigned long total_entries = 0;
    unsigned long longest_chain = 0;
    unsigned long shortest_chain = tabsz;
    unsigned long empty_buckets = 0;
	

	for (unsigned long i = 0; i < tabsz; i++)
	{
		unsigned long chain_length = 0;
		if (htable[i] == NULL)
		{
			empty_buckets++;
			shortest_chain = 0;
		}
		for (node *curr = htable[i]; curr != NULL; curr = curr->next)
		{
			chain_length++;
			total_entries++;
		}
		if (chain_length > longest_chain)
		{
			longest_chain = chain_length;
		}
		if (chain_length < shortest_chain)
		{
			shortest_chain = chain_length;
		}
	}

	printf(TABSZ_MSG, tabsz);
	printf(TOTAL_ENTRIES_MSG, total_entries);
	printf(LONGEST_MSG, longest_chain);
	printf(SHORTEST_MSG, shortest_chain);
	printf(EMPTY_MSG, empty_buckets);

}
