#ifndef _MUTILS_H_
#define _MUTILS_H_

typedef struct ivec2 {
	int x, y;
} ivec2;

typedef struct fvec2 {
	float x, y;
} fvec2;

typedef struct ivec3 {
	int x, y, z;
} ivec3;

typedef struct fvec3 {
	float x, y, z;
} fvec3;

typedef struct ivec4 {
	int x, y, z, u;
} ivec4;

typedef struct fvec4 {
	float x, y, z, u;
} fvec4;

typedef float fmat2[2*2];
typedef float fmat3[3*3];
typedef float fmat4[4*4];

typedef struct fcoordsys2 {
	fvec2 origin, x_axis, y_axis;
} fcoordsys2;

typedef struct fcoordsys3 {
	fvec3 origin, x_axis, y_axis, z_axis;
} fcoordsys3;

typedef struct fcoordsys4 {
	fvec4 origin, x_axis, y_axis, z_axis, u_axis;
} fcoordsys4;

int ivec2_equals( ivec2 vec1, ivec2 vec2 );
int ivec3_equals( ivec3 vec1, ivec3 vec2 );
int ivec4_equals( ivec4 vec1, ivec4 vec2 );

int fvec2_equals( fvec2 vec1, fvec2 vec2 );
int fvec3_equals( fvec3 vec1, fvec3 vec2 );
int fvec4_equals( fvec4 vec1, fvec4 vec2 );

fvec2 fvec2_add( fvec2 vec1, fvec2 vec2 );
fvec3 fvec3_add( fvec3 vec1, fvec3 vec2 );
fvec4 fvec4_add( fvec4 vec1, fvec4 vec2 );

fvec2 fvec2_substract( fvec2 vec1, fvec2 vec2 );
fvec3 fvec3_substract( fvec3 vec1, fvec3 vec2 );
fvec4 fvec4_substract( fvec4 vec1, fvec4 vec2 );

fvec2 fvec2_multiply( fvec2 vec, float factor );
fvec3 fvec3_multiply( fvec3 vec, float factor );
fvec4 fvec4_multiply( fvec4 vec, float factor );

float fvec2_dot( fvec2 vec1, fvec2 vec2 );
float fvec3_dot( fvec3 vec1, fvec3 vec2 );
float fvec4_dot( fvec4 vec1, fvec4 vec2 );

float fvec2_norm( fvec2 vec );
float fvec3_norm( fvec3 vec );
float fvec4_norm( fvec4 vec );

fvec2 fvec2_normalize( fvec2 vec );
fvec3 fvec3_normalize( fvec3 vec );
fvec4 fvec4_normalize( fvec4 vec );

fvec2 fvec2_abs( fvec2 vec );
fvec3 fvec3_abs( fvec3 vec );
fvec4 fvec4_abs( fvec4 vec );

fvec2 fvec2_scalar_divide( fvec2 dividend, float divider );
fvec3 fvec3_scalar_divide( fvec3 dividend, float divider );
fvec4 fvec4_scalar_divide( fvec4 dividend, float divider );

float fvec2_vector_divide( fvec2 dividend, fvec2 divider );
float fvec3_vector_divide( fvec3 dividend, fvec3 divider );
float fvec4_vector_divide( fvec4 dividend, fvec4 divider );

fvec2 fvec2_project_to( fvec2 vec, fcoordsys2 coordsys );
fvec3 fvec3_project_to( fvec3 vec, fcoordsys3 coordsys );
fvec4 fvec4_project_to( fvec4 vec, fcoordsys4 coordsys );

fvec2 fvec2_project_from_to( fvec2 vec, fcoordsys2 from, fcoordsys2 to );
fvec3 fvec3_project_from_to( fvec3 vec, fcoordsys3 from, fcoordsys3 to );
fvec4 fvec4_project_from_to( fvec4 vec, fcoordsys4 from, fcoordsys4 to );

fvec2 fvec2_zero();
fvec3 fvec3_zero();
fvec4 fvec4_zero();

fvec2 fmat2_get_row( fmat2 mat, int i );
fvec2 fmat2_get_column( fmat2 mat, int i );
fvec3 fmat3_get_row( fmat3 mat, int i );
fvec3 fmat3_get_column( fmat3 mat, int i );
fvec4 fmat4_get_row( fmat4 mat, int i );
fvec4 fmat4_get_column( fmat4 mat, int i );

void fmat2_set( fmat2 mat, float val, int i, int j );
void fmat3_set( fmat3 mat, float val, int i, int j );
void fmat4_set( fmat4 mat, float val, int i, int j );

void fmat2_fill( fmat2 mat, float val );
void fmat3_fill( fmat3 mat, float val );
void fmat4_fill( fmat4 mat, float val );

void fmat2_identity( fmat2 out );
void fmat3_identity( fmat3 out );
void fmat4_identity( fmat4 out );

void fmat2_zero( fmat2 out );
void fmat3_zero( fmat3 out );
void fmat4_zero( fmat4 out );

void fmat2_cpy( fmat2 dest, fmat2 source );
void fmat3_cpy( fmat3 dest, fmat3 source );
void fmat4_cpy( fmat4 dest, fmat4 source );

void fmat2_mult( fmat2 mat1, fmat2 mat2, fmat2 out );
void fmat3_mult( fmat3 mat1, fmat3 mat2, fmat3 out );
void fmat4_mult( fmat4 mat1, fmat4 mat2, fmat4 out );

fvec2 fmat2_fvec2_mult( fmat2 mat1, fvec2 vec2 );
fvec3 fmat3_fvec3_mult( fmat3 mat1, fvec3 vec2 );
fvec4 fmat4_fvec4_mult( fmat4 mat1, fvec4 vec2 );

void fmat3_x_rotation_matrix( float theta, fmat3 out );
void fmat3_y_rotation_matrix( float theta, fmat3 out );
void fmat3_z_rotation_matrix( float theta, fmat3 out );

void fmat2_rotation_matrix( float theta, fmat2 out );
void fmat3_rotation_matrix( float x_angle_rads, float y_angle_rads, float z_angle_rads, fmat3 out );

#endif
