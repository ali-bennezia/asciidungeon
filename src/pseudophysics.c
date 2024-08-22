#include "pseudophysics.h"

#include <stdlib.h>
#include <stddef.h>

#include <asciigl.h>

typedef struct RigidBodyQuadTreeNode {
	int x, y;
	DynamicArray data;
	struct RigidBodyQuadTreeNode *parent;
	int index;
	struct RigidBodyQuadTreeNode *children[ 4 ];
} RigidBodyQuadTreeNode;

static RigidBodyQuadTreeNode root;

static RigidBodyQuadTreeNode *get_node_child( RigidBodyQuadTreeNode *node, int local_x, int local_y )
{
	int local_index = local_y * 2 + local_x;
	return node->children[ local_index ];
}

static void init_node_child( RigidBodyQuadTreeNode *node, int local_x, int local_y )
{
	int local_index = local_y * 2 + local_x;
	RigidBodyQuadTreeNode *child_node = malloc( sizeof( RigidBodyQuadTreeNode ) );
	child_node->x = local_x;
	child_node->y = local_y;
	child_node->data = gen_dynamic_array( sizeof( RigidBody ) );
	child_node->parent = node;
	child_node->index = local_index;
	child_node->children = { NULL };
	node->children[ local_index ] = child_node;	
}

static void free_node_child( RigidBodyQuadTreeNode *node, int local_x, int local_y )
{
	RigidBodyQuadTreeNode *child_node = get_node_child( node, local_x, local_y );
	if ( child_node != NULL ) {
		free_node( child_node );
		int local_index = local_y * 2 + local_x;	
		node->children[ local_index ] = NULL;
	}
}

static void free_node( RigidBodyQuadTreeNode *node )
{
	free_dynamic_array( &node->data );
	for ( size_t i = 0; i < 4; ++i )
	{
		RigidBodyQuadTreeNode *child_node = node->children[ i ];
		if ( child_node != NULL ) free_node( child_node );
	}
	free( node );
}

static void init_quadtree_root()
{
	RigidBodyQuadTreeNode init_root = {
		0, 0,
		gen_dynamic_array( sizeof( RigidBody ) ),
		NULL,
		-1,
		{ NULL }
	};
	root = init_root;
}

static void free_quadtree_root()
{
	for ( size_t i = 0; i < 4; ++i )
	{
		RigidBodyQuadTreeNode *child_node = root.children[ i ];
		if ( child_node != NULL ) free_node( child_node );
		root.children[ i ] = NULL; 
	}	
	free_dynamic_array( &root.data );
}

RaycastResult asciidng_cast_ray( Ray ray )
{
	RaycastResult result = { ray, NULL, fvec3_zero() };
	return result;
}

void asciidng_init_physics()
{
	init_quadtree_root();	
}

void asciidng_loop_physics()
{
}

void asciidng_terminate_physics()
{
	free_quadtree_root();
}
