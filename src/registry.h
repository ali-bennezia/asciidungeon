#ifndef _REGISTRY_H_
#define _REGISTRY_H_

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
	Mesh *mesh;
	Texture *texture;
} PropDefinition;

typedef struct EntityDefinition {
	char *name;
	Texture *texture;
} EntityDefinition;

void asciidng_init_registry();
void asciidng_terminate_registry();

#endif
