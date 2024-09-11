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

	DynamicArray rigid_bodies;
	bool list_initialized;
} Node;

static Node root;

// static functions

static size_t get_children_count( Node *node );
static ivec3 get_lower_level_coords( int x, int y, int z, size_t level, size_t backsteps );
static void get_bounding_box_coords( BoundingBox bb, ivec3 *coords_out, size_t *level_out );
static ivec3 get_position_node_coordinates( fvec3 position, size_t level );
static size_t get_nearest_side_length_level( float length );
static Node* get_or_create_child_node( Node *node, int local_x, int local_y, int local_z );
static Node* get_child_node( Node *node, int local_x, int local_y, int local_z );
static Node* get_node( int x, int y, int z, size_t level, Node **out_nearest_divergent_node, size_t *out_nearest_divergent_node_level );
static Node* generate_child_node( Node *node, int local_x, int local_y, int local_z );
static void free_node( Node *node, bool root_node );
static Node* get_nearest_manifold_ancestor( Node *node );
static void remove_child_node( Node *node, int local_x, int local_y, int local_z );
static void remove_node( int x, int y, int z, size_t level );
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

static void get_bounding_box_coords( BoundingBox bb, ivec3 *coords_out, size_t *level_out )
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

static Node* get_node( int x, int y, int z, size_t level, Node **out_nearest_divergent_node, size_t *out_nearest_divergent_node_level )
{
	Node *node = NULL, *nearest_divergent_node = NULL;
	size_t nearest_divergent_node_level = 0;
	for ( size_t l = 0; l <= level; ++l )
	{
		size_t backsteps = level - l;
		ivec3 coords = get_lower_level_coords( x, y, z, level, backsteps );
		if ( l > 0 ){
			node = get_child_node( node, coords.x % 2, coords.y % 2, coords.z % 2 );
		}else{
			if ( ivec3_equals( coords, ivec3_zero() ) ) node = &root; else node = NULL;	
		}
		if ( l < level && l > 0 && node != NULL && get_children_count( node ) > 1 ){
			nearest_divergent_node = node;
			nearest_divergent_node_level = l;
		}
		if ( node == NULL ) break;
	}
	if ( out_nearest_divergent_node != NULL ) {
		*out_nearest_divergent_node = nearest_divergent_node;
		if ( out_nearest_divergent_node_level != NULL ) *out_nearest_divergent_node_level = nearest_divergent_node_level;
	}
	return node;
}

static Node* generate_child_node( Node *node, int local_x, int local_y, int local_z )
{
	size_t i = local_y * 4 + local_z * 2 + local_x;
	if ( node->children[ i ] != NULL ) free_node( node->children[ i ], false );

	DynamicArray uninit_dynarr = { 0 };

	Node *child_node = malloc( sizeof( Node ) );
	child_node->level = node->level + 1;
	child_node->x = node->x * 2 + local_x;
	child_node->y = node->y * 2 + local_y;
	child_node->z = node->z * 2 + local_z;
	child_node->parent = node;
	child_node->rigid_bodies = uninit_dynarr;
	child_node->list_initialized = false;
	
	for ( size_t q = 0; q < 8; ++q ) child_node->children[ q ] = NULL;

	node->children[ i ] = child_node;

	return child_node;
}

static void free_node( Node *node, bool root_node )
{
	if ( node->list_initialized == true ){
		free_dynamic_array( &node->rigid_bodies );
		node->list_initialized = false;
	}

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

static void remove_child_node( Node *node, int local_x, int local_y, int local_z )
{
	size_t i = local_y * 4 + local_z * 2 + local_x;
	Node *child_node = node->children[ i ];
	if ( child_node != NULL ){
		free_node( child_node, false );
		node->children[ i ] = NULL;
	}
}

// TODO
static void remove_node( int x, int y, int z, size_t level )
{
	Node *nearest_manifold = NULL;
	size_t nearest_manifold_level;
	Node *node = get_node( x, y, z, level, &nearest_manifold, &nearest_manifold_level );
	if ( nearest_manifold != NULL ){
		ivec3 manifold_child_coords = get_lower_level_coords( x, y, z, level, level - ( nearest_manifold_level + 1 ) );
		remove_child_node( nearest_manifold, manifold_child_coords.x % 2, manifold_child_coords.y % 2, manifold_child_coords.z % 2 );
	}else{
	
	}
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
		{ NULL },
		{ 0 },
		false
	};
	root = root_node;
}

void asciidng_terminate_octree()
{
	free_node( &root, true );
}

void asciidng_register_octree_rigid_body( RigidBody *rb )
{
	asciidng_unregister_octree_rigid_body( rb );
	ivec3 coords;
	size_t level;
	get_bounding_box_coords( rb->bounding_box, &coords, &level );
	Node *node = generate_branch( coords.x, coords.y, coords.z, level );
	if ( node->list_initialized == false ){
		node->rigid_bodies = gen_dynamic_array( sizeof( RigidBody* ) );
		node->list_initialized = true;
	}
	insert_data( &node->rigid_bodies, &rb, sizeof( RigidBody* ) );
}

void asciidng_unregister_octree_rigid_body( RigidBody *rb )
{
	if ( rb->node_cache != NULL ){
		for ( size_t i = 0; i < rb->node_cache->rigid_bodies.usage; ++i ){
			RigidBody *data = *( (RigidBody**) get_data( &rb->node_cache->rigid_bodies, i, sizeof( RigidBody* ) ) );
			if ( data == rb ){
				remove_data( &rb->node_cache->rigid_bodies, i, sizeof( RigidBody* ) );
				break;
			}
		}

		size_t cnt = get_children_count( rb->node_cache );
		if ( cnt == 0 ){
			remove_node( rb->node_cache->x_coord, rb->node_cache->y_coord, rb->node_cache->z_coord, rb->node_cache->level );
		}
		rb->node_cache = NULL;
	}
}

void asciidng_update_octree_rigidbody_transform( RigidBody *rb, BoundingBox old_bb, BoundingBox new_bb )
{
	ivec3 old_coords, new_coords;
	size_t old_level, new_level;
	get_bounding_box_coords( old_bb, &old_coords, &old_level );
	get_bounding_box_coords( new_bb, &new_coords, &new_level );

	if ( !ivec3_equals( old_coords, new_coords ) || old_level != new_level ){
		asciidng_unregister_octree_rigid_body( rb );
		Node *node = generate_branch( new_coords.x, new_coords.y, new_coords.z, new_level );	
	}
}
