#ifndef _WORKSPACE_H_
#define _WORKSPACE_H_

#include "mutils.h"

struct Model;
typedef struct Model Model;

struct TileDefinition;
typedef struct TileDefinition TileDefinition;

struct PropDefinition;
typedef struct PropDefinition PropDefinition;

struct EntityDefinition;
typedef struct EntityDefinition EntityDefinition;

struct UITextInstance;
typedef struct UITextInstance UITextInstance;

struct UIFrameInstance;
typedef struct UIFrameInstance UIFrameInstance;

struct UIImageInstance;
typedef struct UIImageInstance UIImageInstance;

struct UIButtonInstance;
typedef struct UIButtonInstance UIButtonInstance;

typedef struct TileInstance {
	TileDefinition *def;
	Model *model;
	ivec3 coords;
} TileInstance;

typedef struct PropInstance {
	PropDefinition *def;
	Model *model;
	fvec3 position;
} PropInstance;

typedef struct EntityInstance {
	EntityDefinition *def;
	Model *model;
	fvec3 position;
} EntityInstance;

void asciidng_init_workspace();
void asciidng_terminate_workspace();

void asciidng_clear_workspace();

TileInstance *asciidng_gen_tile( const char *tile_name, int x, int y, int z );
void asciidng_remove_tile( TileInstance *instance );

PropInstance *asciidng_gen_prop( const char *prop_name, float x, float y, float z );
void asciidng_remove_prop( PropInstance *instance );

EntityInstance *asciidng_gen_entity( const char *entity_name, float x, float y, float z );
void asciidng_remove_entity( EntityInstance *instance );

UIButtonInstance *asciidng_gen_ui_button( int x, int y, unsigned int size_x, unsigned int size_y, char *text, int layer );
void asciidng_remove_ui_button( UIButtonInstance *instance );

#endif
