#include "mutils.h"

#include <stddef.h>
#include <string.h>
#include <math.h>

fvec2 fvec2_add( fvec2 vec1, fvec2 vec2 )
{
	vec1.x += vec2.x;
	vec1.y += vec2.y;
	return vec1;
}

fvec3 fvec3_add( fvec3 vec1, fvec3 vec2 )
{
	vec1.x += vec2.x;
	vec1.y += vec2.y;
	vec1.z += vec2.z;
	return vec1;
}

fvec4 fvec4_add( fvec4 vec1, fvec4 vec2 )
{
	vec1.x += vec2.x;
	vec1.y += vec2.y;
	vec1.z += vec2.z;
	vec1.u += vec2.u;
	return vec1;
}

fvec2 fvec2_multiply( fvec2 vec, float factor )
{
	vec.x *= factor;
	vec.y *= factor;
	return vec;
}

fvec3 fvec3_multiply( fvec3 vec, float factor )
{
	vec.x *= factor;
	vec.y *= factor;
	vec.z *= factor;
	return vec;
}

fvec4 fvec4_multiply( fvec4 vec, float factor )
{
	vec.x *= factor;
	vec.y *= factor;
	vec.z *= factor;
	vec.u *= factor;
	return vec;
}

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

float fvec2_norm( fvec2 vec )
{
	return sqrt( pow( vec.x, 2 ) + pow( vec.y, 2 ) );
}

float fvec3_norm( fvec3 vec )
{
	return sqrt( pow( vec.x, 2 ) + pow( vec.y, 2 ) + pow( vec.z, 2 ) );
}

float fvec4_norm( fvec4 vec )
{
	return sqrt( pow( vec.x, 2 ) + pow( vec.y, 2 ) + pow( vec.z, 2 ) + pow( vec.u, 2 ) );
}

fvec2 fvec2_normalize( fvec2 vec )
{
	return fvec2_scalar_divide( vec, fvec2_norm( vec ) );
}

fvec3 fvec3_normalize( fvec3 vec )
{
	return fvec3_scalar_divide( vec, fvec3_norm( vec ) );
}

fvec4 fvec4_normalize( fvec4 vec )
{
	return fvec4_scalar_divide( vec, fvec4_norm( vec ) );
}

fvec2 fvec2_scalar_divide( fvec2 dividend, float divider )
{
	dividend.x /= divider;
	dividend.y /= divider;
	return dividend;
}

fvec3 fvec3_scalar_divide( fvec3 dividend, float divider )
{
	dividend.x /= divider;
	dividend.y /= divider;
	dividend.z /= divider;
	return dividend;
}

fvec4 fvec4_scalar_divide( fvec4 dividend, float divider )
{
	dividend.x /= divider;
	dividend.y /= divider;
	dividend.z /= divider;
	dividend.u /= divider;
	return dividend;
}

float fvec2_vector_divide( fvec2 dividend, fvec2 divider )
{
	float dividend_norm = fvec2_norm( dividend ), divider_norm = fvec2_norm( divider );
	fvec2 quotient = { 0, 0 };
	if ( divider.x != 0 ) quotient.x = fabs( dividend.x / divider.x );
	if ( divider.y != 0 ) quotient.y = fabs( dividend.y / divider.y );
	float d = fvec2_dot( fvec2_normalize( dividend ), fvec2_normalize( divider ) );
	if ( d > 0 ){
		float q = fmin( quotient.x, quotient.y );
		return q;
	}else if ( d < 0 ){
		float q = fmin( quotient.x, quotient.y );
		return -q;
	}else{
		return 0;
	}
}

float fvec3_vector_divide( fvec3 dividend, fvec3 divider )
{
	float dividend_norm = fvec3_norm( dividend ), divider_norm = fvec3_norm( divider );
	fvec3 quotient = { 0, 0, 0 };
	if ( divider.x != 0 ) quotient.x = fabs( dividend.x / divider.x );
	if ( divider.y != 0 ) quotient.y = fabs( dividend.y / divider.y );
	if ( divider.z != 0 ) quotient.z = fabs( dividend.z / divider.z );
	float d = fvec3_dot( fvec3_normalize( dividend ), fvec3_normalize( divider ) );
	if ( d > 0 ){
		float q = fmin( fmin( quotient.x, quotient.y ), quotient.z );
		return q;
	}else if ( d < 0 ){
		float q = fmin( fmin( quotient.x, quotient.y ), quotient.z );
		return -q;
	}else{
		return 0;
	}
}

float fvec4_vector_divide( fvec4 dividend, fvec4 divider )
{
	float dividend_norm = fvec4_norm( dividend ), divider_norm = fvec4_norm( divider );
	fvec4 quotient = { 0, 0, 0, 0 };
	if ( divider.x != 0 ) quotient.x = fabs( dividend.x / divider.x );
	if ( divider.y != 0 ) quotient.y = fabs( dividend.y / divider.y );
	if ( divider.z != 0 ) quotient.z = fabs( dividend.z / divider.z );
	if ( divider.u != 0 ) quotient.u = fabs( dividend.u / divider.u );
	float d = fvec4_dot( fvec4_normalize( dividend ), fvec4_normalize( divider ) );
	if ( d > 0 ){
		float q = fmin( fmin( fmin( quotient.x, quotient.y ), quotient.z ), quotient.u );
		return q;
	}else if ( d < 0 ){
		float q = fmin( fmin( fmin( quotient.x, quotient.y ), quotient.z ), quotient.u );
		return -q;
	}else{
		return 0;
	}
}

fvec2 fvec2_project_to( fvec2 vec, fcoordsys2 coordsys )
{
	return fvec2_add( 
		fvec2_add( 
			coordsys.origin, 
			fvec2_multiply( coordsys.x_axis, vec.x ) 
		), 
		fvec2_multiply( coordsys.y_axis, vec.y ) 
	);
}

fvec3 fvec3_project_to( fvec3 vec, fcoordsys3 coordsys )
{
	return fvec3_add(
		fvec3_add( 
			fvec3_add( 
				coordsys.origin, 
				fvec3_multiply( coordsys.x_axis, vec.x ) 
			), 
			fvec3_multiply( coordsys.y_axis, vec.y ) 
		),
		fvec3_multiply( coordsys.z_axis, vec.z )
	);
}

fvec4 fvec4_project_to( fvec4 vec, fcoordsys4 coordsys )
{
	return fvec4_add(
		fvec4_add(
			fvec4_add( 
				fvec4_add( 
					coordsys.origin, 
					fvec4_multiply( coordsys.x_axis, vec.x ) 
				), 
				fvec4_multiply( coordsys.y_axis, vec.y ) 
			),
			fvec4_multiply( coordsys.z_axis, vec.z )
		),
		fvec4_multiply( coordsys.u_axis, vec.u )
	);
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

void fmat2_fill( fmat2 mat, float val )
{
	const size_t mat_size = 2;
	for ( size_t i = 0; i < mat_size*mat_size; ++i )
	{
		mat[ i ] = val;
	}
}

void fmat3_fill( fmat3 mat, float val )
{
	const size_t mat_size = 3;
	for ( size_t i = 0; i < mat_size*mat_size; ++i )
	{
		mat[ i ] = val;
	}
}

void fmat4_fill( fmat4 mat, float val )
{
	const size_t mat_size = 4;
	for ( size_t i = 0; i < mat_size*mat_size; ++i )
	{
		mat[ i ] = val;
	}
}

void fmat2_identity( fmat2 out )
{
	fmat2_fill( out, 0 );
	const size_t mat_size = 2;
	for ( size_t i = 0; i < mat_size; ++i )
	{
		fmat2_set( out, 1, i, i );
	}
}

void fmat3_identity( fmat3 out )
{
	fmat3_fill( out, 0 );
	const size_t mat_size = 3;
	for ( size_t i = 0; i < mat_size; ++i )
	{
		fmat3_set( out, 1, i, i );
	}
}

void fmat4_identity( fmat4 out )
{
	fmat4_fill( out, 0 );
	const size_t mat_size = 4;
	for ( size_t i = 0; i < mat_size; ++i )
	{
		fmat4_set( out, 1, i, i );
	}
}

void fmat2_zero( fmat2 out )
{
	fmat2_fill( out, 0 );
}

void fmat3_zero( fmat3 out )
{
	fmat3_fill( out, 0 );
}

void fmat4_zero( fmat4 out )
{
	fmat4_fill( out, 0 );
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

fvec4 fmat4_fvec4_mult( fmat4 mat1, fvec4 vec )
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

void fmat2_rotation_matrix( float theta, fmat2 out )
{
	fmat2_set( out, cos( theta ), 0, 0 );
	fmat2_set( out, -sin( theta ), 0, 1 );
	fmat2_set( out, sin( theta ), 1, 0 );
	fmat2_set( out, cos( theta ), 1, 1 );	
}

void fmat3_x_rotation_matrix( float theta, fmat3 out )
{
	fmat3_set( out, 0, 0, 0 );
	fmat3_set( out, 0, 1, 0 );
	fmat3_set( out, 0, 2, 0 );

	fmat3_set( out, 0, 0, 1 );
	fmat3_set( out, 0, 0, 2 );

	fmat3_set( out, cos( theta ), 1, 1 );
	fmat3_set( out, -sin( theta ), 1, 2 );
	fmat3_set( out, sin( theta ), 2, 1 );
	fmat3_set( out, cos( theta ), 2, 2 );
}

void fmat3_y_rotation_matrix( float theta, fmat3 out )
{
	fmat3_set( out, 0, 1, 0 );

	fmat3_set( out, 0, 0, 1 );
	fmat3_set( out, 0, 1, 1 );
	fmat3_set( out, 0, 2, 1 );

	fmat3_set( out, 0, 1, 2 );

	fmat3_set( out, cos( theta ), 0, 0 );
	fmat3_set( out, -sin( theta ), 0, 2 );
	fmat3_set( out, sin( theta ), 2, 0 );
	fmat3_set( out, cos( theta ), 2, 2 );
}

void fmat3_z_rotation_matrix( float theta, fmat3 out )
{
	fmat3_set( out, 0, 2, 0 );

	fmat3_set( out, 0, 2, 1 );

	fmat3_set( out, 0, 0, 2 );
	fmat3_set( out, 0, 1, 2 );
	fmat3_set( out, 0, 2, 2 );

	fmat3_set( out, cos( theta ), 0, 0 );
	fmat3_set( out, -sin( theta ), 0, 1 );
	fmat3_set( out, sin( theta ), 1, 0 );
	fmat3_set( out, cos( theta ), 1, 1 );
}

void fmat3_rotation_matrix( float x_angle_rads, float y_angle_rads, float z_angle_rads, fmat3 out )
{
	fmat3 a, b, c;

	#if EULER_ANGLES_ORDER == X_Y_Z

	fmat3_x_rotation_matrix( x_angle_rads, a );
	fmat3_y_rotation_matrix( y_angle_rads, b );
	fmat3_z_rotation_matrix( z_angle_rads, c );

	#elif EULER_ANGLES_ORDER == X_Z_Y

	fmat3_x_rotation_matrix( x_angle_rads, a );
	fmat3_z_rotation_matrix( z_angle_rads, b );
	fmat3_y_rotation_matrix( y_angle_rads, c );

	#elif EULER_ANGLES_ORDER == Y_X_Z

	fmat3_y_rotation_matrix( y_angle_rads, a );
	fmat3_x_rotation_matrix( x_angle_rads, b );
	fmat3_z_rotation_matrix( z_angle_rads, c );

	#elif EULER_ANGLES_ORDER == Y_Z_X

	fmat3_y_rotation_matrix( y_angle_rads, a );
	fmat3_z_rotation_matrix( z_angle_rads, b );
	fmat3_x_rotation_matrix( x_angle_rads, c );

	#elif EULER_ANGLES_ORDER == Z_Y_X

	fmat3_z_rotation_matrix( z_angle_rads, a );
	fmat3_y_rotation_matrix( y_angle_rads, b );
	fmat3_x_rotation_matrix( x_angle_rads, c );

	#elif EULER_ANGLES_ORDER == Z_X_Y

	fmat3_z_rotation_matrix( z_angle_rads, a );
	fmat3_x_rotation_matrix( x_angle_rads, b );
	fmat3_y_rotation_matrix( y_angle_rads, c );

	#endif

	fmat3 step0, step1, step2;
	fmat3_zero( step0 );

	fmat3_mult( a, step0, step1 );
	fmat3_mult( b, step1, step2 );
	fmat3_mult( c, step2, out );
}
