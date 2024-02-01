#ifndef _REGISTRY_H_
#define _REGISTRY_H_

#include "mutils.h"

struct Mesh;
struct Texture;
typedef struct Mesh Mesh;
typedef struct Texture Texture;

typedef struct TileDefinition {
	char *name;
	Mesh *mesh;
	Texture *texture;
} TileDefinition;

typedef struct PropDefinition {
	char *name;
	fvec3 scale;
	Mesh *mesh;
	Texture *texture;
} PropDefinition;

typedef struct EntityDefinition {
	char *name;
	ivec2 scale;
	Texture *texture;
} EntityDefinition;

void asciidng_init_registry();
void asciidng_terminate_registry();

TileDefinition* asciidng_get_tile_definition( const char *name );
int asciidng_register_tile_definition( const char *name, Mesh *mesh, Texture *texture );

PropDefinition* asciidng_get_prop_definition( const char *name );
int asciidng_register_prop_definition( const char *name, fvec3 scale, Mesh *mesh, Texture *texture );

EntityDefinition* asciidng_get_entity_definition( const char *name );
int asciidng_register_entity_definition( const char *name, ivec2 scale, Texture *texture );

Mesh *asciidng_get_entity_mesh();

#endif
