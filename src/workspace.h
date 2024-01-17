#ifndef _WORKSPACE_H_
#define _WORKSPACE_H_

#include "mutils.h"

struct Model;
typedef struct Model Model;

typedef struct TileInstance {
	Model *model;
	ivec3 coords;
} TileInstance;

typedef struct PropInstance {
	Model *model;
	fvec3 position;
} PropInstance;

typedef struct EntityInstance {
	Model *model;
	fvec3 position;
} EntityInstance;

void asciidng_init_workspace();
void asciidng_terminate_workspace();

TileInstance *gen_tile( const char *tile_name, int x, int y, int z );

#endif
