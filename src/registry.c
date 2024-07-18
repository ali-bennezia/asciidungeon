#include "registry.h"

#include <asciigl.h>

static DynamicArray tile_definitions, prop_definitions, entity_definitions;

static Mesh *g_default_cube_mesh = NULL, *g_default_quad_mesh;

void asciidng_init_registry()
{
	g_default_cube_mesh = load_mesh( "assets/tiles/models/default_cube.obj" );
	g_default_quad_mesh = load_mesh( "assets/entities/models/default_quad.obj" );

	tile_definitions = gen_dynamic_array( sizeof( TileDefinition ) );
	prop_definitions = gen_dynamic_array( sizeof( PropDefinition ) );
	entity_definitions = gen_dynamic_array( sizeof( EntityDefinition ) );
}

void asciidng_terminate_registry()
{
	free_dynamic_array( &tile_definitions );
	free_dynamic_array( &prop_definitions );
	free_dynamic_array( &entity_definitions );

	free_mesh( g_default_quad_mesh );
	free_mesh( g_default_cube_mesh );
}

TileDefinition* asciidng_get_tile_definition( const char *name )
{
	for ( size_t i = 0; i < tile_definitions.usage; ++i )
	{
		TileDefinition *def = ( TileDefinition* ) tile_definitions.buffer + i;
		if ( strcmp( def->name, name ) == 0 ) return def;
	}
	return NULL;
}

PropDefinition* asciidng_get_prop_definition( const char *name )
{
	for ( size_t i = 0; i < prop_definitions.usage; ++i )
	{
		PropDefinition *def = ( PropDefinition* ) prop_definitions.buffer + i;
		if ( strcmp( def->name, name ) == 0 ) return def;
	}
	return NULL;
}

EntityDefinition* asciidng_get_entity_definition( const char *name )
{
	for ( size_t i = 0; i < entity_definitions.usage; ++i )
	{
		EntityDefinition *def = ( EntityDefinition* ) entity_definitions.buffer + i;
		if ( strcmp( def->name, name ) == 0 ) return def;
	}
	return NULL;
}

int asciidng_register_tile_definition( const char *name, Mesh *mesh, Texture *texture )
{
	if ( asciidng_get_tile_definition( name ) != NULL ) return 1;

	char *def_name = malloc( strlen( name ) + 1 );
	strcpy( def_name, name );

	TileDefinition def = {
		def_name,
		mesh == NULL ? g_default_cube_mesh : mesh,
		texture
	};
	insert_data( &tile_definitions, &def, sizeof( TileDefinition ) );

	return 0;
}

int asciidng_register_prop_definition( const char *name, fvec3 scale,  Mesh *mesh, Texture *texture )
{
	if ( asciidng_get_prop_definition( name ) != NULL ) return 1;

	char *def_name = malloc( strlen( name ) + 1 );
	strcpy( def_name, name );

	PropDefinition def = {
		def_name,
		scale,
		mesh == NULL ? g_default_cube_mesh : mesh,
		texture
	};
	insert_data( &prop_definitions, &def, sizeof( PropDefinition ) );

	return 0;
}

int asciidng_register_entity_definition( const char *name, ivec2 scale, Texture *texture )
{
	if ( asciidng_get_entity_definition( name ) != NULL ) return 1;

	char *def_name = malloc( strlen( name ) + 1 );
	strcpy( def_name, name );

	EntityDefinition def = {
		def_name,
		scale,
		texture
	};
	insert_data( &entity_definitions, &def, sizeof( EntityDefinition ) );

	return 0;
}

Mesh *asciidng_get_entity_mesh()
{
	return g_default_quad_mesh;
}
