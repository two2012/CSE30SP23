#include <string.h>
#include "node.h"

node *node_lookup(node *front, char *id) {
	// TODO: step through the chain pointed to by front
	// use function like strcmp to compare the id to the current node
	// if found return a pointer to the node, else return NULL
	for (node *curr = front; curr != NULL; curr = curr->next)
	{
		if (strcmp(curr->id, id) == 0)
		{
			return curr;
		}
	}

	return NULL; 
}
