#include "rboctree.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <math.h>

#include <asciigl.h>

#include "pseudophysics.h"
#include "mutils.h"

// internals

#define ROOT_SIDE_LENGTH 20000

typedef struct Node {
	size_t level;
	int x, y, z;
	struct Node *parent;
	struct Node *children[ 8 ];
} Node;

static Node root;

// static functions

static ivec3 get_lower_level_coords( int x, int y, int z, size_t level, size_t backsteps );
static void get_bounding_box_coords( BoundingBox bb, size_t *level_out, ivec3 *coords_out );
static ivec3 get_position_node_coordinates( fvec3 position, size_t level );
static size_t get_nearest_side_length_level( float length );
static Node* generate_child_node( Node *node, int local_x, int local_y, int local_z );
static void free_node( Node *node, bool root_node );

static ivec3 get_lower_level_coords( int x, int y, int z, size_t level, size_t backsteps )
{
	size_t target_level = level - backsteps;
	size_t divider = pow( 2, backsteps );

	ivec3 result = {
		( x - x % divider ) / divider,
		( y - y % divider ) / divider,
		( z - z % divider ) / divider
	};
	return result;
}

static void get_bounding_box_coords( BoundingBox bb, size_t *level_out, ivec3 *coords_out )
{
	fvec3 bb_size = fvec3_abs( fvec3_substract( bb.min, bb.max ) );		
	float max_side_length = fmax( fmax( bb_size.x, bb_size.y ), bb_size.z );
	size_t nearest_level = get_nearest_side_length_level( max_side_length );

	ivec3 min_node_coords = get_position_node_coordinates( bb.min, nearest_level ),
		max_node_coords = get_position_node_coordinates( bb.max, nearest_level );

	if ( ivec3_equals( min_node_coords, max_node_coords ) ){
		*level_out = nearest_level;
		*coords_out = min_node_coords;
	}else{
		ivec3 min_node_lower_level_coords = get_lower_level_coords( min_node_coords.x, min_node_coords.y, min_node_coords.z, nearest_level, 1 );
		ivec3 max_node_lower_level_coords = get_lower_level_coords( max_node_coords.x, max_node_coords.y, max_node_coords.z, nearest_level, 1 );
		if ( ivec3_equals( min_node_lower_level_coords, max_node_lower_level_coords ) ){
			*level_out = nearest_level - 1;
			*coords_out = min_node_lower_level_coords;
		}else{
			ivec3 min_node_lowest_level_coords = get_lower_level_coords( min_node_coords.x, min_node_coords.y, min_node_coords.z, nearest_level, 2 );
			*level_out = nearest_level - 2;
			*coords_out = min_node_lowest_level_coords;
		}
	}	
}

static ivec3 get_position_node_coordinates( fvec3 position, size_t level )
{
	float node_side_length = ROOT_SIDE_LENGTH / pow( 2, level );
	ivec3 result = {
		( position.x - fmod( position.x, node_side_length ) ) / node_side_length,
		( position.y - fmod( position.y, node_side_length ) ) / node_side_length,
		( position.z - fmod( position.z, node_side_length ) ) / node_side_length
	};

	return result;
}

static size_t get_nearest_side_length_level( float length )
{
	int result = 0;
	float side = ROOT_SIDE_LENGTH;
	while ( side > length ){
		side /= 2.0f;
		++result;
	}
	return max( result - 1, 0 );
}

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
