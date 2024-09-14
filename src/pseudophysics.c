#include "pseudophysics.h"

#include <stddef.h>

#include <asciigl.h>

#include "rboctree.h"

static DynamicArray rigid_bodies;

RaycastResult asciidng_cast_ray( Ray ray )
{
	RaycastResult result = { ray, NULL, fvec3_zero() };
	return result;
}

void asciidng_generate_parallelepiped_vertices( fvec3 size, fvec3 *vertices )
{
	fvec3 half_size = fvec3_scalar_divide( size, 2 );
	size_t index = 0;
	for ( int x = 0; x < 2; ++x ){
		if ( x <= 0 ) x = -1;
		for ( int y = 0; y < 2; ++y ){
			if ( y <= 0 ) y = -1;
			for ( int z = 0; z < 2; ++z ){
				if ( z <= 0 ) z = -1;
				fvec3 vert = {
					half_size.x * x,
					half_size.y * y,
					half_size.z * z
				};
				*( vertices + index ) = vert;
				++index;
			}
		}
	}
}

void asciidng_generate_parallelepiped_collider_vertices( Collider collider, fvec3 *vertices )
{
	asciidng_generate_parallelepiped_vertices( collider.size, vertices );
	fmat3 rotation_matrix;
	fmat3_rotation_matrix( collider.local_rotation.x, collider.local_rotation.y, collider.local_rotation.z, rotation_matrix );
	for ( size_t i = 0; i < 8; ++i ){
		vertices[ i ] = fmat3_fvec3_mult( rotation_matrix, vertices[ i ] );
		vertices[ i ] = fvec3_add( vertices[ i ], collider.local_position );
	}
}

BoundingBox asciidng_generate_transform_bounding_box( RigidBody *rigid_body )
{
	Transform transform = rigid_body->transform;

	fvec3 vertices[ 8 ];
	asciidng_generate_parallelepiped_collider_vertices( rigid_body->collider, vertices );

	fmat3 rotation_matrix;
	fmat3_rotation_matrix( transform.rotation.x, transform.rotation.y, transform.rotation.z, rotation_matrix );

	float min_x, min_y, min_z, max_x, max_y, max_z;

	for ( size_t i = 0; i < 8; ++i ){
		vertices[ i ] = fmat3_fvec3_mult( rotation_matrix, vertices[ i ] );
		if ( i > 0 ){
			if ( min_x > vertices[ i ].x ) min_x = vertices[ i ].x;
			if ( min_y > vertices[ i ].y ) min_y = vertices[ i ].y;
			if ( min_z > vertices[ i ].z ) min_z = vertices[ i ].z;

			if ( max_x < vertices[ i ].x ) max_x = vertices[ i ].x;
			if ( max_y < vertices[ i ].y ) max_y = vertices[ i ].y;
			if ( max_z < vertices[ i ].z ) max_z = vertices[ i ].z;
		} else {
			min_x = vertices[ i ].x;
			min_y = vertices[ i ].y;
			min_z = vertices[ i ].z;

			max_x = vertices[ i ].x;
			max_y = vertices[ i ].y;
			max_z = vertices[ i ].z;
		} 
	}

	fvec3 bb_min = { min_x, min_y, min_z }, bb_max = { max_x, max_y, max_z };

	BoundingBox bb = {
		bb_min, bb_max
	};

	return bb;
}

void asciidng_update_rigid_body_bounding_box( RigidBody *rigid_body )
{
	BoundingBox old_bb = rigid_body->bounding_box;
	BoundingBox bb = asciidng_generate_transform_bounding_box( rigid_body );
	rigid_body->bounding_box = bb;
	asciidng_update_octree_rigid_body( rigid_body, old_bb );
}

void asciidng_set_rigid_body_transform_position( RigidBody *rigid_body, fvec3 position )
{
	rigid_body->transform.position = position;
	asciidng_update_rigid_body_bounding_box( rigid_body );	
}

void asciidng_set_rigid_body_transform_rotation( RigidBody *rigid_body, fvec3 rotation )
{
	rigid_body->transform.rotation = rotation;
	asciidng_update_rigid_body_bounding_box( rigid_body );	
}

void asciidng_set_rigid_body_collider( RigidBody *rigid_body, Collider collider )
{
	rigid_body->collider = collider;
	asciidng_update_rigid_body_bounding_box( rigid_body );	
}

void asciidng_translate_rigid_body( RigidBody *rigid_body, fvec3 translation )
{
	asciidng_set_rigid_body_transform_position( rigid_body, fvec3_add( rigid_body->transform.position, translation ) );
}

void asciidng_rotate_rigid_body( RigidBody *rigid_body, fvec3 rotation )
{
	asciidng_set_rigid_body_transform_rotation( rigid_body, fvec3_add( rigid_body->transform.rotation, rotation ) );
}

RigidBody *asciidng_create_rigid_body( enum BODY_TYPE type, fvec3 position, fvec3 rotation )
{
	Transform transform = {
		position,
		rotation,
		fvec3_zero(),
		fvec3_zero()
	};

	fvec3 one = { 1, 1, 1 };

	BoundingBox bb;

	Collider collider = {
		PARALLELEPIPED_COLLIDER,
		fvec3_zero(),
		fvec3_zero(),
		one
	};

	RigidBody rb = {
		type,
		transform,
		collider,
		bb,
		NULL
	};

	bb = asciidng_generate_transform_bounding_box( &rb );
	rb.bounding_box = bb;


	RigidBody *rb_ptr = insert_data( &rigid_bodies, &rb, sizeof( RigidBody ) );
	asciidng_register_octree_rigid_body( rb_ptr );
	return rb_ptr;
}

void asciidng_remove_rigid_body( RigidBody *rigid_body )
{

}

void asciidng_init_physics()
{
	rigid_bodies = gen_dynamic_array( sizeof( RigidBody ) );
}

void asciidng_loop_physics()
{
	free_dynamic_array( &rigid_bodies );
}

void asciidng_terminate_physics()
{
}
