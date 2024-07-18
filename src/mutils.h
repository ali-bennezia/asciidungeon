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

float fvec2_dot( fvec2 vec1, fvec2 vec2 );
float fvec3_dot( fvec3 vec1, fvec3 vec2 );
float fvec4_dot( fvec4 vec1, fvec4 vec2 );

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

void fmat2_rotation_matrix( float theta, fmat2 out );

#endif
