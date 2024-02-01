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

	buttons = gen_dynamic_array( sizeof( UIButton* ) );
	images = gen_dynamic_array( sizeof( UIImage* ) ); 
	frames = gen_dynamic_array( sizeof( UIFrame* ) );
	texts = gen_dynamic_array( sizeof( UIText* ) );
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

void asciidng_clear_workspace()
{
	clear_dynamic_array( &tiles, sizeof( TileInstance ) );
	clear_dynamic_array( &props, sizeof( PropInstance ) );
	clear_dynamic_array( &entities, sizeof( EntityInstance ) );
}

TileInstance *gen_tile( const char *tile_name, int x, int y, int z )
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
		model,
		coords
	};

	return insert_data( &tiles, &instance, sizeof( TileInstance ) );
}

void remove_tile( TileInstance *instance )
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

PropInstance *gen_prop( const char *prop_name, float x, float y, float z )
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
		model,
		fpos
	};

	return insert_data( &props, &instance, sizeof( PropInstance ) );
}

void remove_prop( PropInstance *instance )
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

EntityInstance *gen_entity( const char *entity_name, float x, float y, float z )
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
		model,
		fpos
	};

	return insert_data( &entities, &instance, sizeof( EntityInstance ) );
}

void remove_entity( EntityInstance *instance )
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

