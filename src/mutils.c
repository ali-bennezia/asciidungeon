#include "mutils.h"

#include <stddef.h>
#include <string.h>

float fvec2_dot( fvec2 vec1, fvec2 vec2 )
{
	return vec1.x * vec2.x + vec1.y * vec2.y;
}

float fvec3_dot( fvec3 vec1, fvec3 vec2 )
{
	return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

float fvec4_dot( fvec4 vec1, fvec4 vec2 )
{
	return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z + vec1.u * vec2.u;
}


fvec2 fmat2_get_row( fmat2 mat, int i )
{
	fvec2 result = {
		mat[ i * 2 + 0 ],
		mat[ i * 2 + 1 ]
	};
	return result;
}

fvec2 fmat2_get_column( fmat2 mat, int i )
{
	fvec2 result = {
		mat[ i ],
		mat[ i + 1 * 2 ]
	};
	return result;
}

void fmat2_set( fmat2 mat, float val, int i, int j )
{
	const size_t mat_size = 2;
	mat[ i * mat_size + j ] = val;
}

void fmat2_cpy( fmat2 dest, fmat2 source )
{
	const size_t mat_size = 2;
	memcpy( dest, source, sizeof( float ) * mat_size * mat_size );
}

void fmat2_mult( fmat2 mat1, fmat2 mat2, fmat2 out )
{
	const size_t mat_size = 2;

	for ( size_t i = 0; i < mat_size; ++i )
	{
		for ( size_t j = 0; j < mat_size; ++j )
		{
			fvec2 row_vec = fmat2_get_row( mat1, i ), col_vec = fmat2_get_column( mat2, j );
			fmat2_set( out, fvec2_dot( row_vec, col_vec ), i, j );	
		} 	
	} 
}

fvec2 fmat2_fvec2_mult( fmat2 mat1, fvec2 vec )
{
	const size_t mat_size = 2;
	float data[ 2 ];

	for ( size_t i = 0; i < mat_size; ++i )
	{
		fvec2 row_vec = fmat2_get_row( mat1, i );
		data[ i ] = fvec2_dot( row_vec, vec );
	} 

	fvec2 result = {
		data[ 0 ],
		data[ 1 ]
	};
	return result;
}


