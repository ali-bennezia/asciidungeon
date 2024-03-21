#include "workspace.h"

#include <asciigl.h>

#include "ui.h"
#include "registry.h"

static DynamicArray tiles, props, entities;
static DynamicArray buttons, images, frames, texts; 

void asciidng_init_workspace()
{
	tiles = gen_dynamic_array( sizeof( TileInstance ) );
	props = gen_dynamic_array( sizeof( PropInstance ) );
	entities = gen_dynamic_array( sizeof( EntityInstance ) );

	buttons = gen_dynamic_array( sizeof( UIButtonInstance ) );
	images = gen_dynamic_array( sizeof( UIImageInstance ) ); 
	frames = gen_dynamic_array( sizeof( UIFrameInstance ) );
	texts = gen_dynamic_array( sizeof( UITextInstance ) );
}

void asciidng_terminate_workspace()
{
	free_dynamic_array( &texts );
	free_dynamic_array( &frames );
	free_dynamic_array( &images );
	free_dynamic_array( &buttons );

	free_dynamic_array( &tiles );
	free_dynamic_array( &props );
	free_dynamic_array( &entities );
}

static unsigned int clear_mode = 0;
static void dynarr_clear_fun( void *data )
{
	switch ( clear_mode ){
		case 0:
			free_ui_text( ( ( UITextInstance* ) data )->ui_txt );
			break;
		case 1:
			free_ui_frame( ( ( UIFrameInstance* ) data )->ui_frame );
			break;
		case 2:
			free_ui_image( ( ( UIImageInstance* ) data )->ui_image );
			break;	
		case 3:
			UIButtonInstance *case_3_instance = ( UIButtonInstance* ) data; 	
			free_ui_text( case_3_instance->ui_txt );
			free_ui_frame( case_3_instance->ui_frame );
			break;
		case 4:
			asciidng_remove_tile( ( TileInstance* ) data );
			break;
		case 5:
			asciidng_remove_prop( ( PropInstance* ) data );
			break;
		case 6:
			asciidng_remove_entity( ( EntityInstance* ) data );
			break;
		// TODO 	
	}
}

void asciidng_clear_workspace()
{
	clear_dynamic_array( &texts, sizeof( UITextInstance ) );
	clear_dynamic_array( &frames, sizeof( UIFrameInstance ) );
	clear_dynamic_array( &images, sizeof( UIImageInstance ) );
	clear_dynamic_array( &buttons, sizeof( UIButtonInstance ) );

	clear_dynamic_array( &tiles, sizeof( TileInstance ) );
	clear_dynamic_array( &props, sizeof( PropInstance ) );
	clear_dynamic_array( &entities, sizeof( EntityInstance ) );
}

TileInstance *asciidng_gen_tile( const char *tile_name, int x, int y, int z )
{
	TileDefinition *def = asciidng_get_tile_definition( tile_name );	

	if ( def == NULL ) return NULL;

	Model *model = gen_model();
	model->mesh = def->mesh;
	model->texture = def->texture;

	ivec3 coords = { x, y, z };
	Vec3 position = { 2*x, 2*y, 2*z };

	model->position = position;

	TileInstance instance = {
		def,
		model,
		coords
	};

	return insert_data( &tiles, &instance, sizeof( TileInstance ) );
}

void asciidng_remove_tile( TileInstance *instance )
{
	if ( instance == NULL ) return;

	Model *model = instance->model;
	if ( model != NULL ){
		model->mesh = NULL;
		model->texture = NULL;
		free_model( model );
	}

	size_t i = instance - ( ( TileInstance* ) tiles.buffer );
	remove_data( &tiles, i, sizeof( TileInstance ) );
}

PropInstance *asciidng_gen_prop( const char *prop_name, float x, float y, float z )
{
	PropDefinition *def = asciidng_get_prop_definition( prop_name );	

	if ( def == NULL ) return NULL;

	Model *model = gen_model();
	model->mesh = def->mesh;
	model->texture = def->texture;

	fvec3 fpos = { x, y, z };
	Vec3 position = { x, y, z };

	model->position = position;

	PropInstance instance = {
		def,
		model,
		fpos
	};

	return insert_data( &props, &instance, sizeof( PropInstance ) );
}

void asciidng_remove_prop( PropInstance *instance )
{
	if ( instance == NULL ) return;

	Model *model = instance->model;
	if ( model != NULL ){
		model->mesh = NULL;
		model->texture = NULL;
		free_model( model );
	}

	size_t i = instance - ( ( PropInstance* ) props.buffer );
	remove_data( &props, i, sizeof( PropInstance ) );
}

EntityInstance *asciidng_gen_entity( const char *entity_name, float x, float y, float z )
{
	EntityDefinition *def = asciidng_get_entity_definition( entity_name );	

	if ( def == NULL ) return NULL;

	Model *model = gen_model_billboard();
	model->mesh = asciidng_get_entity_mesh();
	model->texture = def->texture;

	fvec3 fpos = { x, y, z };
	Vec3 position = { x, y, z };

	model->position = position;

	EntityInstance instance = {
		def,
		model,
		fpos
	};

	return insert_data( &entities, &instance, sizeof( EntityInstance ) );
}

void asciidng_remove_entity( EntityInstance *instance )
{
	if ( instance == NULL ) return;

	Model *model = instance->model;
	if ( model != NULL ){
		model->mesh = NULL;
		model->texture = NULL;
		free_model( model );
	}

	size_t i = instance - ( ( EntityInstance* ) entities.buffer );
	remove_data( &entities, i, sizeof( EntityInstance ) );
}

UIButtonInstance *asciidng_gen_ui_button( int x, int y, unsigned int size_x, unsigned int size_y, char *text, int layer )
{
	IntVec2 btn_pos = { x, y }, btn_size = { size_x, size_y };
	RGB btn_col = { 255, 255, 255 };
	UIText *btn_txt = gen_ui_text( text, btn_pos, btn_col, layer );

	UIFrame *btn_frame = gen_ui_frame( btn_pos, btn_size, btn_col, layer );	

	UIButtonInstance instance = {
		btn_txt,
		btn_frame,
	};

	return insert_data( &buttons, &instance, sizeof( UIButtonInstance ) ); 
}

void asciidng_remove_ui_button( UIButtonInstance *instance )
{
	if ( instance == NULL ) return;

	UIText *txt = instance->ui_txt; 	
	UIFrame *frame = instance->ui_frame; 

	free_ui_text( txt );
	free_ui_frame( frame );

	size_t i = instance - ( ( UIButtonInstance* ) buttons.buffer );
	remove_data( &buttons, i, sizeof( UIButtonInstance ) );	
}

UIImageInstance *asciidng_gen_ui_image( int x, int y, unsigned int size_x, unsigned int size_y, Texture *texture, int layer )
{
	IntVec2 pos = { x,  y }, size = { size_x, size_y };
	RGB col = { 255, 255, 255 };

	UIImage *img = gen_ui_image( pos, size, col, layer, texture );

	UIImageInstance instance = {
		img		
	};

	return insert_data( &images, &instance, sizeof( UIImageInstance ) );
}

void asciidng_remove_ui_image( UIImageInstance *instance )
{
	if ( instance == NULL ) return;

	UIImage *img = instance->ui_image;

	free_ui_image( img );

	size_t i = instance - ( ( UIImageInstance* ) images.buffer );
	remove_data( &images, i, sizeof( UIImageInstance ) );	
}

UIFrameInstance *asciidng_gen_ui_frame( int x, int y, unsigned int size_x, unsigned int size_y, int layer )
{
	IntVec2 pos = { x,  y }, size = { size_x, size_y };
	RGB col = { 255, 255, 255 };

	UIFrame *frame = gen_ui_frame( pos, size, col, layer );

	UIFrameInstance instance = {
		frame
	};

	return insert_data( &frames, &instance, sizeof( UIFrameInstance ) );
}

void asciidng_remove_ui_frame( UIFrameInstance *instance )
{
	if ( instance == NULL ) return;

	UIFrame *frame = instance->ui_frame;

	free_ui_frame( frame );

	size_t i = instance - ( ( UIFrameInstance* ) frames.buffer );
	remove_data( &frames, i, sizeof( UIFrameInstance ) );
}

UITextInstance *asciidng_gen_ui_text( int x, int y, char *text, int layer )
{
	IntVec2 pos = { x,  y };
	RGB col = { 255, 255, 255 };

	UIText *ui_text = gen_ui_text( text, pos, col, layer );

	UITextInstance instance = {
		ui_text
	};

	return insert_data( &texts, &instance, sizeof( UITextInstance ) );
}

void asciidng_remove_ui_text( UITextInstance *instance )
{
	if ( instance == NULL ) return;

	UIText *text = instance->ui_txt;

	free_ui_text( text );

	size_t i = instance - ( ( UITextInstance* ) texts.buffer );
	remove_data( &texts, i, sizeof( UITextInstance ) );
}
