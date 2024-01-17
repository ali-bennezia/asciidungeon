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
