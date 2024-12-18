#include "workspace.h"

#include <asciigl.h>

#include "ui.h"
#include "utils.h"
#include "registry.h"
#include "pseudophysics.h"

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
			asciidng_remove_ui_text( ( UITextInstance* ) data );
			break;
		case 1:
			asciidng_remove_ui_frame( ( UIFrameInstance* ) data );
			break;
		case 2:
			asciidng_remove_ui_image( ( UIImageInstance* ) data );
			break;	
		case 3:
			asciidng_remove_ui_button( ( UIButtonInstance* ) data );
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
	}
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

	fvec3 position_fvec3 = { position.x, position.y, position.z };

	RigidBody *rigid_body = asciidng_create_rigid_body( 
		STATIC_BODY, 
		position_fvec3, 
		fvec3_zero() 
	);

	TileInstance instance = {
		def,
		model,
		coords,
		rigid_body
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
	if ( instance->rigid_body != NULL ){
		asciidng_remove_rigid_body( instance->rigid_body );
		instance->rigid_body = NULL;
	}

	size_t i = instance - ( ( TileInstance* ) tiles.buffer );
	remove_data( &tiles, i, sizeof( TileInstance ) );
}

void asciidng_clear_tiles()
{
	clear_mode = 4;
	foreach_dynarr( &tiles, sizeof( TileInstance ), dynarr_clear_fun );
	clear_dynamic_array( &tiles, sizeof( TileInstance ) );	
}

TileInstance *asciidng_set_tile_coords( TileInstance *tile, int x, int y, int z )
{
	ivec3 coords = { x, y, z };
	fvec3 position = { 2*x, 2*y, 2*z };

	tile->coords = coords;
	asciidng_set_rigid_body_transform_position( tile->rigid_body, position );
	
	return tile;
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
	fvec3 position_fvec3 = { x, y, z };

	model->position = position;

	RigidBody *rigid_body = asciidng_create_rigid_body( 
		STATIC_BODY, 
		position_fvec3, 
		fvec3_zero() 
	);

	PropInstance instance = {
		def,
		model,
		fpos,
		fvec3_zero(),
		rigid_body
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
	if ( instance->rigid_body != NULL ){
		asciidng_remove_rigid_body( instance->rigid_body );
		instance->rigid_body = NULL;
	}

	size_t i = instance - ( ( PropInstance* ) props.buffer );
	remove_data( &props, i, sizeof( PropInstance ) );
}

void asciidng_clear_props()
{
	clear_mode = 5;
	foreach_dynarr( &props, sizeof( PropInstance ), dynarr_clear_fun );
	clear_dynamic_array( &props, sizeof( PropInstance ) );	
}

PropInstance *asciidng_set_prop_position( PropInstance *prop, float x, float y, float z )
{
	fvec3 position = { x, y, z };
	prop->position = position;
	asciidng_set_rigid_body_transform_position( prop->rigid_body, position );
	return prop;
}

PropInstance *asciidng_set_prop_rotation( PropInstance *prop, float x, float y, float z )
{
	fvec3 rotation = { x, y, z };
	prop->rotation = rotation;
	asciidng_set_rigid_body_transform_rotation( prop->rigid_body, rotation );
	return prop;
}

PropInstance *asciidng_translate_prop( PropInstance *prop, float x, float y, float z )
{
	fvec3 position = { x, y, z };
	position = fvec3_add( prop->rigid_body->transform.position, position );
	prop->position = position;
	asciidng_set_rigid_body_transform_position( prop->rigid_body, position );
	return prop;
}

PropInstance *asciidng_rotate_prop( PropInstance *prop, float x, float y, float z )
{
	fvec3 rotation = { x, y, z };
	rotation = fvec3_add( prop->rigid_body->transform.rotation, rotation );
	prop->rotation = rotation;
	asciidng_set_rigid_body_transform_rotation( prop->rigid_body, rotation );
	return prop;
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
	fvec3 position_fvec3 = { x, y, z };

	model->position = position;

	RigidBody *rigid_body = asciidng_create_rigid_body( 
		STATIC_BODY, 
		position_fvec3, 
		fvec3_zero() 
	);

	EntityInstance instance = {
		def,
		model,
		fpos,
		fvec3_zero(),
		rigid_body
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
	if ( instance->rigid_body != NULL ){
		asciidng_remove_rigid_body( instance->rigid_body );
		instance->rigid_body = NULL;
	}

	size_t i = instance - ( ( EntityInstance* ) entities.buffer );
	remove_data( &entities, i, sizeof( EntityInstance ) );
}

void asciidng_clear_entities()
{
	clear_mode = 6;
	foreach_dynarr( &entities, sizeof( EntityInstance ), dynarr_clear_fun );
	clear_dynamic_array( &entities, sizeof( EntityInstance ) );	
}

EntityInstance *asciidng_set_entity_position( EntityInstance *entity, float x, float y, float z )
{
	fvec3 position = { x, y, z };
	entity->position = position;
	asciidng_set_rigid_body_transform_position( entity->rigid_body, position );
	return entity;
}

EntityInstance *asciidng_set_entity_rotation( EntityInstance *entity, float x, float y, float z )
{
	fvec3 rotation = { x, y, z };
	entity->rotation = rotation;
	asciidng_set_rigid_body_transform_rotation( entity->rigid_body, rotation );
	return entity;
}

EntityInstance *asciidng_translate_entity( EntityInstance *entity, float x, float y, float z )
{
	fvec3 position = { x, y, z };
	position = fvec3_add( entity->rigid_body->transform.position, position );
	entity->position = position;
	asciidng_set_rigid_body_transform_position( entity->rigid_body, position );
	return entity;
}

EntityInstance *asciidng_rotate_entity( EntityInstance *entity, float x, float y, float z )
{
	fvec3 rotation = { x, y, z };
	rotation = fvec3_add( entity->rigid_body->transform.rotation, rotation );
	entity->rotation = rotation;
	asciidng_set_rigid_body_transform_rotation( entity->rigid_body, rotation );
	return entity;
}

UIButtonInstance *asciidng_gen_ui_button( int x, int y, unsigned int size_x, unsigned int size_y, char *text, int layer )
{
	IntVec2 btn_pos = { x, y }, btn_size = { size_x, size_y };
	IntVec2 txt_pos = {
		floor( (float)(x + x+size_x)/2.0 ) - strlen( text ) / 2,
		floor( (float)(y + y+size_y)/2.0 ),
	};
	RGB btn_col = { 255, 255, 255 };

	UIFrame *btn_frame = gen_ui_frame( btn_pos, btn_size, btn_col, layer );	
	UIText *btn_txt = gen_ui_text( text, txt_pos, btn_col, layer );

	UICallbacks clbs = {
		NULL, NULL, NULL
	};

	UIButtonInstance instance = {
		btn_txt,
		btn_frame,
		clbs
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

void asciidng_clear_ui_buttons()
{
	clear_mode = 3;
	foreach_dynarr( &buttons, sizeof( UIButtonInstance ), dynarr_clear_fun );
	clear_dynamic_array( &buttons, sizeof( UIButtonInstance ) );	
}

unsigned int asciidng_get_ui_buttons_count()
{
	return buttons.usage;
}

UIButtonInstance *asciidng_ui_button_at( unsigned int index )
{
	if ( index >= buttons.usage ) return NULL;
	return ( UIButtonInstance* ) buttons.buffer + index;
}

UIImageInstance *asciidng_gen_ui_image( int x, int y, unsigned int size_x, unsigned int size_y, Texture *texture, int layer )
{
	IntVec2 pos = { x,  y }, size = { size_x, size_y };
	RGB col = { 255, 255, 255 };

	UIImage *img = gen_ui_image( pos, size, col, layer, texture );

	UICallbacks clbs = {
		NULL, NULL, NULL
	};

	UIImageInstance instance = {
		img,
		clbs	
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

void asciidng_clear_ui_images()
{
	clear_mode = 2;
	foreach_dynarr( &images, sizeof( UIImageInstance ), dynarr_clear_fun );
	clear_dynamic_array( &images, sizeof( UIImageInstance ) );	
}

unsigned int asciidng_get_ui_images_count()
{
	return images.usage;
}

UIImageInstance *asciidng_ui_image_at( unsigned int index )
{
	if ( index >= images.usage ) return NULL;
	return ( UIImageInstance* ) images.buffer + index;
}

UIFrameInstance *asciidng_gen_ui_frame( int x, int y, unsigned int size_x, unsigned int size_y, int layer )
{
	IntVec2 pos = { x,  y }, size = { size_x, size_y };
	RGB col = { 255, 255, 255 };

	UIFrame *frame = gen_ui_frame( pos, size, col, layer );

	UICallbacks clbs = {
		NULL, NULL, NULL
	};

	UIFrameInstance instance = {
		frame,
		clbs
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

void asciidng_clear_ui_frames()
{
	clear_mode = 1;
	foreach_dynarr( &frames, sizeof( UIFrameInstance ), dynarr_clear_fun );
	clear_dynamic_array( &frames, sizeof( UIFrameInstance ) );	
}

unsigned int asciidng_get_ui_frames_count()
{
	return frames.usage;
}

UIFrameInstance *asciidng_ui_frame_at( unsigned int index )
{
	if ( index >= frames.usage ) return NULL;
	return ( UIFrameInstance* ) frames.buffer + index;
}

UITextInstance *asciidng_gen_ui_text( int x, int y, char *text, int layer )
{
	IntVec2 pos = { x,  y };
	RGB col = { 255, 255, 255 };

	UIText *ui_text = gen_ui_text( text, pos, col, layer );

	UICallbacks clbs = {
		NULL, NULL, NULL
	};

	UITextInstance instance = {
		ui_text,
		clbs
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

void asciidng_clear_ui_texts()
{
	clear_mode = 0;
	foreach_dynarr( &texts, sizeof( UITextInstance ), dynarr_clear_fun );
	clear_dynamic_array( &texts, sizeof( UITextInstance ) );	
}

unsigned int asciidng_get_ui_texts_count()
{
	return texts.usage;
}

UITextInstance *asciidng_ui_text_at( unsigned int index )
{
	if ( index >= texts.usage ) return NULL;
	return ( UITextInstance* ) texts.buffer + index;
}

void asciidng_clear_objects()
{
	asciidng_clear_tiles();
	asciidng_clear_props();
	asciidng_clear_entities();
}

void asciidng_clear_ui()
{
	asciidng_clear_ui_buttons();
	asciidng_clear_ui_images();
	asciidng_clear_ui_texts();
}

void asciidng_clear_workspace()
{
	asciidng_clear_objects();
	asciidng_clear_ui();
}
