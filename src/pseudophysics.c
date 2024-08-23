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
	fvec3 vertices[ 8 ];
	
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
