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

void asciidng_clear_workspace();

TileInstance *gen_tile( const char *tile_name, int x, int y, int z );
void remove_tile( TileInstance *instance );

PropInstance *gen_prop( const char *prop_name, float x, float y, float z );
void remove_prop( PropInstance *instance );

EntityInstance *gen_entity( const char *entity_name, float x, float y, float z );
void remove_entity( EntityInstance *instance );

#endif
