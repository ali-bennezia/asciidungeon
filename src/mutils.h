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

fvec2 fmat2_get_row( fmat2 mat, int i );
fvec2 fmat2_get_column( fmat2 mat, int i );

void fmat2_set( fmat2 mat, float val, int i, int j );
void fmat2_cpy( fmat2 dest, fmat2 source );
void fmat2_mult( fmat2 mat1, fmat2 mat2, fmat2 out );
fvec2 fmat2_fvec2_mult( fmat2 mat1, fvec2 vec2 );

#endif
