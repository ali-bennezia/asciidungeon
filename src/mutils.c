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

fvec3 fmat3_get_row( fmat3 mat, int i )
{
	fvec3 result = {
		mat[ i * 3 + 0 ],
		mat[ i * 3 + 1 ],
		mat[ i * 3 + 2 ]
	};
	return result;
}

fvec3 fmat3_get_column( fmat3 mat, int i )
{
	fvec3 result = {
		mat[ i ],
		mat[ i + 1 * 3 ],
		mat[ i + 2 * 3 ]
	};
	return result;
}

fvec4 fmat4_get_row( fmat4 mat, int i )
{
	fvec4 result = {
		mat[ i * 4 + 0 ],
		mat[ i * 4 + 1 ],
		mat[ i * 4 + 2 ],
		mat[ i * 4 + 3 ]
	};
	return result;
}

fvec4 fmat4_get_column( fmat4 mat, int i )
{
	fvec4 result = {
		mat[ i ],
		mat[ i + 1 * 4 ],
		mat[ i + 2 * 4 ],
		mat[ i + 3 * 4 ]
	};
	return result;
}

void fmat2_set( fmat2 mat, float val, int i, int j )
{
	const size_t mat_size = 2;
	mat[ i * mat_size + j ] = val;
}

void fmat3_set( fmat3 mat, float val, int i, int j )
{
	const size_t mat_size = 3;
	mat[ i * mat_size + j ] = val;
}

void fmat4_set( fmat4 mat, float val, int i, int j )
{
	const size_t mat_size = 4;
	mat[ i * mat_size + j ] = val;
}

void fmat2_cpy( fmat2 dest, fmat2 source )
{
	const size_t mat_size = 2;
	memcpy( dest, source, sizeof( float ) * mat_size * mat_size );
}

void fmat3_cpy( fmat3 dest, fmat3 source )
{
	const size_t mat_size = 3;
	memcpy( dest, source, sizeof( float ) * mat_size * mat_size );
}

void fmat4_cpy( fmat4 dest, fmat4 source )
{
	const size_t mat_size = 4;
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

void fmat3_mult( fmat3 mat1, fmat3 mat2, fmat3 out )
{
	const size_t mat_size = 3;

	for ( size_t i = 0; i < mat_size; ++i )
	{
		for ( size_t j = 0; j < mat_size; ++j )
		{
			fvec3 row_vec = fmat3_get_row( mat1, i ), col_vec = fmat3_get_column( mat2, j );
			fmat3_set( out, fvec3_dot( row_vec, col_vec ), i, j );	
		} 	
	} 
}

void fmat4_mult( fmat4 mat1, fmat4 mat2, fmat4 out )
{
	const size_t mat_size = 4;

	for ( size_t i = 0; i < mat_size; ++i )
	{
		for ( size_t j = 0; j < mat_size; ++j )
		{
			fvec4 row_vec = fmat4_get_row( mat1, i ), col_vec = fmat4_get_column( mat2, j );
			fmat4_set( out, fvec4_dot( row_vec, col_vec ), i, j );	
		} 	
	} 
}

fvec2 fmat2_fvec2_mult( fmat2 mat1, fvec2 vec )
{
	const size_t mat_size = 2;
	float data[ mat_size ];

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

fvec3 fmat3_fvec3_mult( fmat3 mat1, fvec3 vec )
{
	const size_t mat_size = 3;
	float data[ mat_size ];

	for ( size_t i = 0; i < mat_size; ++i )
	{
		fvec3 row_vec = fmat3_get_row( mat1, i );
		data[ i ] = fvec3_dot( row_vec, vec );
	} 

	fvec3 result = {
		data[ 0 ],
		data[ 1 ],
		data[ 2 ]
	};
	return result;
}

fvec4 fmat4_fvec3_mult( fmat4 mat1, fvec4 vec )
{
	const size_t mat_size = 4;
	float data[ mat_size ];

	for ( size_t i = 0; i < mat_size; ++i )
	{
		fvec4 row_vec = fmat4_get_row( mat1, i );
		data[ i ] = fvec4_dot( row_vec, vec );
	} 

	fvec4 result = {
		data[ 0 ],
		data[ 1 ],
		data[ 2 ],
		data[ 3 ]
	};
	return result;
}
