#include "pseudophysics.h"

#include <stddef.h>

#include <asciigl.h>

#include "rboctree.h"

#include "geo.h"

static DynamicArray rigid_bodies;

RaycastResult asciidng_cast_ray( Ray ray )
{
	RaycastResult result = { ray, NULL, fvec3_zero() };
	return result;
}

static void asciidng_generate_parallelepiped_collider_vertices( Collider collider, fvec3 *vertices )
{
	asciidng_geo_parallelepiped( collider.size, vertices );
	fmat3 rotation_matrix;
	fmat3_rotation_matrix( collider.local_rotation.x, collider.local_rotation.y, collider.local_rotation.z, rotation_matrix );
	for ( size_t i = 0; i < 8; ++i ){
		vertices[ i ] = fmat3_fvec3_mult( rotation_matrix, vertices[ i ] );
		vertices[ i ] = fvec3_add( vertices[ i ], collider.local_position );
	}
}

static BoundingBox asciidng_generate_parallelepiped_rigid_body_bounding_box( RigidBody *rigid_body )
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

static BoundingBox asciidng_generate_sphere_rigid_body_bounding_box( RigidBody *rigid_body )
{
	Transform transform = rigid_body->transform;

	fvec3 bb_min, bb_max;
	bb_min = fvec3_substract( 
		rigid_body->collider.local_position,
		fvec3_multiply( fvec3_scalar( rigid_body->collider.radius ), -1 )
	);

	bb_max = fvec3_substract( 
		rigid_body->collider.local_position,
		fvec3_scalar( rigid_body->collider.radius )
	);

	BoundingBox bb = {
		bb_min, bb_max
	};

	return bb;
}

BoundingBox asciidng_generate_bounding_box( RigidBody *rigid_body )
{

	switch ( rigid_body->collider.collider_type ){
		case PARALLELEPIPED_COLLIDER:
			return asciidng_generate_parallelepiped_rigid_body_bounding_box( rigid_body );
		default:
			BoundingBox empty = { 0 };
			return empty;
	}

}

void asciidng_update_rigid_body_bounding_box( RigidBody *rigid_body )
{
	BoundingBox old_bb = rigid_body->bounding_box;
	BoundingBox bb = asciidng_generate_bounding_box( rigid_body );
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
	fvec3 one = { 1, 1, 1 };

	Transform transform = {
		position,
		rotation,
		fvec3_zero(),
		fvec3_zero()
	};

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
		NULL,
		0.5f
	};

	bb = asciidng_generate_bounding_box( &rb );
	rb.bounding_box = bb;

	RigidBody *rb_ptr = insert_data( &rigid_bodies, &rb, sizeof( RigidBody ) );
	asciidng_register_octree_rigid_body( rb_ptr );
	return rb_ptr;
}

void asciidng_remove_rigid_body( RigidBody *rigid_body )
{
	RigidBody *found = NULL;
	int found_i = -1;
	for ( size_t i = 0; i < rigid_bodies.usage; ++i ){
		if ( ( RigidBody* ) rigid_bodies.buffer + i == rigid_body ){
			found = ( RigidBody* ) rigid_bodies.buffer + i;
			found_i = (int) i;
			break;
		}
	}
	if ( found != NULL && found_i >= 0 ){
		remove_data( &rigid_bodies, found_i, sizeof( RigidBody ) );
	}
}

void asciidng_generate_rigid_body_model_matrix( RigidBody *rigid_body, fmat4 out )
{
	fmat4 local_rot, local_pos, rot, pos;
	fmat4 local_model_matrix, world_model_matrix;
	fmat4_rotation_matrix( 
		to_rads( rigid_body->collider.local_rotation.x ),
		to_rads( rigid_body->collider.local_rotation.y ),
		to_rads( rigid_body->collider.local_rotation.z ),
		local_rot
		);
	fmat4_translation_matrix( rigid_body->collider.local_position, local_pos );
	fmat4_mult(local_pos, local_rot, local_model_matrix);
	fmat4_rotation_matrix(
		to_rads( rigid_body->transform.rotation.x ),
		to_rads( rigid_body->transform.rotation.y ),
		to_rads( rigid_body->transform.rotation.z ),
		rot
	);
	fmat4_translation_matrix( rigid_body->transform.position, pos );
	fmat4_mult(pos, rot, world_model_matrix);
	fmat4 result;
	fmat4_mult( world_model_matrix, local_model_matrix, result );
	fmat4_cpy( out, result );
}

void asciidng_init_physics()
{
	asciidng_init_octree();
	rigid_bodies = gen_dynamic_array( sizeof( RigidBody ) );
}

void asciidng_loop_physics( double delta_time )
{
	for ( size_t i = 0; i < rigid_bodies.usage; ++i ){
		RigidBody *rb = ( RigidBody* ) rigid_bodies.buffer + i;
	}
}

void asciidng_terminate_physics()
{
	free_dynamic_array( &rigid_bodies );
	asciidng_terminate_octree();
}
