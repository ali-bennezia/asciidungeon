#include "pseudophysics.h"

#include <stddef.h>

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

void asciidng_process_transform_bounding_box( RigidBody *rigid_body )
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

	rigid_body->bounding_box_min = bb_min;
	rigid_body->bounding_box_max = bb_max;
}

void asciidng_init_physics()
{
}

void asciidng_loop_physics()
{
}

void asciidng_terminate_physics()
{
}
