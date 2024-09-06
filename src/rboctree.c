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

static size_t get_children_count( Node *node );
static ivec3 get_lower_level_coords( int x, int y, int z, size_t level, size_t backsteps );
static void get_bounding_box_coords( BoundingBox bb, size_t *level_out, ivec3 *coords_out );
static ivec3 get_position_node_coordinates( fvec3 position, size_t level );
static size_t get_nearest_side_length_level( float length );
static Node* get_or_create_child_node( Node *node, int local_x, int local_y, int local_z );
static Node* get_child_node( Node *node, int local_x, int local_y, int local_z );
static Node* get_node( int x, int y, int z, size_t level, Node **out_nearest_divergent_node );
static Node* generate_child_node( Node *node, int local_x, int local_y, int local_z );
static void free_node( Node *node, bool root_node );
static Node* get_nearest_manifold_ancestor( Node *node );
static Node* generate_branch( int x, int y, int z, size_t level );

static size_t get_children_count( Node *node )
{
	size_t c = 0;
	for ( size_t i = 0; i < 8; ++i ){
		if ( node->children[ i ] != NULL ) ++c;
	}
	return c;
}

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

static Node* get_or_create_child_node( Node *node, int local_x, int local_y, int local_z )
{
	Node *child = get_child_node( node, local_x, local_y, local_z );
	if ( child == NULL ) child = generate_child_node( node, local_x, local_y, local_z );
	return child;
}

static Node* get_child_node( Node *node, int local_x, int local_y, int local_z )
{
	size_t i = local_y * 4 + local_z * 2 + local_x;
	return node->children[ i ];
}

static Node* get_node( int x, int y, int z, size_t level, Node **out_nearest_divergent_node )
{
	Node *node = NULL, *nearest_divergent_node = NULL;
	for ( size_t l = 0; l <= level; ++l )
	{
		size_t backsteps = abs( (int) l - (int) level );
		ivec3 coords = get_lower_level_coords( x, y, z, level, backsteps );
		if ( l > 0 ){
			node = get_child_node( node, coords.x % 2, coords.y % 2, coords.z % 2 );
		}else{
			if ( ivec3_equals( coords, ivec3_zero() ) ) node = &root; else node = NULL;	
		}
		if ( l < level && node != NULL && get_children_count( node ) > 1 ){
			nearest_divergent_node = node;
		}
		if ( node == NULL ) break;
	}
	if ( out_nearest_divergent_node != NULL ) *out_nearest_divergent_node = nearest_divergent_node;
	return node;
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

static Node* get_nearest_manifold_ancestor( Node *node )
{
	Node *i = node->parent;
	while ( i != NULL ){
		bool found_divergence = false;
		for ( size_t q = 0; q < 8; ++q ){
			Node *child_node = i->children[ q ];
			if ( child_node != node && child_node != NULL ) found_divergence = true;
		}
		if ( found_divergence ) break;	
		i = i->parent;
	}
	return i;
}

static void remove_node( int x, int y, int z, size_t level )
{
	
}

static Node* generate_branch( int x, int y, int z, size_t level )
{
	Node *node = NULL;
	for ( size_t l = 0; l <= level; ++l ){
		size_t backsteps = level - l;
		ivec3 coords = get_lower_level_coords( x, y, z, level, backsteps );
		if ( l > 0 ){
			node = get_or_create_child_node( node, coords.x % 2, coords.y % 2, coords.z % 2 );
		}else if ( !ivec3_equals( coords, ivec3_zero() ) ) return NULL; else node = &root;
		if ( node == NULL ) break;
	}
	return node;
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
