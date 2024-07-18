#ifndef _WORKSPACE_H_
#define _WORKSPACE_H_

#include "mutils.h"

struct Model;
typedef struct Model Model;

struct Texture;
typedef struct Texture Texture;

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
void asciidng_clear_tiles();

PropInstance *asciidng_gen_prop( const char *prop_name, float x, float y, float z );
void asciidng_remove_prop( PropInstance *instance );
void asciidng_clear_props();

EntityInstance *asciidng_gen_entity( const char *entity_name, float x, float y, float z );
void asciidng_remove_entity( EntityInstance *instance );
void asciidng_clear_entities();

UIButtonInstance *asciidng_gen_ui_button( int x, int y, unsigned int size_x, unsigned int size_y, char *text, int layer );
void asciidng_remove_ui_button( UIButtonInstance *instance );
void asciidng_clear_ui_buttons();
unsigned int asciidng_get_ui_buttons_count();
UIButtonInstance *asciidng_ui_button_at( unsigned int index );

UIImageInstance *asciidng_gen_ui_image( int x, int y, unsigned int size_x, unsigned int size_y, Texture *texture, int layer );
void asciidng_remove_ui_image( UIImageInstance *instance );
void asciidng_clear_ui_images();
unsigned int asciidng_get_ui_images_count();
UIImageInstance *asciidng_ui_image_at( unsigned int index );

UIFrameInstance *asciidng_gen_ui_frame( int x, int y, unsigned int size_x, unsigned int size_y, int layer );
void asciidng_remove_ui_frame( UIFrameInstance *instance );
void asciidng_clear_ui_frames();
unsigned int asciidng_get_ui_frames_count();
UIFrameInstance *asciidng_ui_frame_at( unsigned int index );

UITextInstance *asciidng_gen_ui_text( int x, int y, char *text, int layer );
void asciidng_remove_ui_text( UITextInstance *instance );
void asciidng_clear_ui_texts();
unsigned int asciidng_get_ui_texts_count();
UITextInstance *asciidng_ui_text_at( unsigned int index );

void asciidng_clear_objects();
void asciidng_clear_ui();
void asciidng_clear_workspace();

#endif
