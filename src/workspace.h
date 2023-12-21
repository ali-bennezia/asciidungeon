#ifndef _WORKSPACE_H_
#define _WORKSPACE_H_

#include "utils.h"

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

#endif
