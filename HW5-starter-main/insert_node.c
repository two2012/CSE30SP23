#include <stdlib.h>
#include <string.h>
#include "node.h"

node *insert_node(node *front, char* id, double x, double y) {
	
	// TODO: create a node, copy in the parameter fields
	// make sure that you do a deep copy
	node *new_node = malloc(sizeof(node));
	if (new_node == NULL)
	{
		return NULL;
	}

	new_node->id = malloc(strlen(id) + 1);
	if (new_node->id == NULL)
	{
		free(new_node);
		return NULL;
	}

	strcpy(new_node->id, id);

	new_node->xcoord = x;
	new_node->ycoord = y;

	// TODO: link the new node into the chain 
	if (front == NULL)
	{
		front = new_node;
	
	}
	else
	{
		new_node->next = front;
	}

	// TODO: return the new head of the chain if the function succeeded
	
	return new_node; // TODO: replace this once you implement
}


