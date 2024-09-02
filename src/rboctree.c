#include "rboctree.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

#include <asciigl.h>

// internals

#define ROOT_SIDE_LENGTH = 8000

typedef struct Node {
	size_t level;
	int x, y, z;
	struct Node *parent;
	struct Node *children[ 8 ];
} Node;

static Node root;

// static functions

static Node* generate_child_node( Node *node, int local_x, int local_y, int local_z );
static void free_node( Node *node, bool root_node );

static Node* generate_child_node( Node *node, int local_x, int local_y, int local_z )
{
	size_t i = local_y * 4 + local_z * 2 + local_x;
	if ( node->children[ i ] != NULL ) free_node( node->children[ i ], false );

	Node *child_node = malloc( sizeof( Node ) );
	child_node->level = node->level + 1;
	child_node->x = node->x * 2 + local_x;
	child_node->y = node->y * 2 + local_y;
	child_node->z = node->z * 2 + local_z;
	child_node->parent = node;
	for ( size_t q = 0; q < 8; ++q ) child_node->children[ q ] = NULL;

	node->children[ i ] = child_node;

	return child_node;
}

static void free_node( Node *node, bool root_node )
{
	for ( size_t i = 0; i < 8; ++i )
	{
		Node *child_node = node->children[ i ];
		free_node( child_node, false );
		node->children[ i ] = NULL; 
	}
	if ( !root_node ) free( node );
}

// API

void asciidng_init_octree()
{
	Node root_node = {
		0,
		0, 0, 0,
		NULL,
		{ NULL }
	};
	root = root_node;
}

void asciidng_terminate_octree()
{
	free_node( &root, true );
}
