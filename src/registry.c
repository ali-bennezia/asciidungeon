#include "registry.h"

#include <asciigl.h>

static DynamicArray tile_definitions, prop_definitions, entity_definitions;

void asciidng_init_registry()
{
	tile_definitions = gen_dynamic_array( sizeof( TileDefinition ) );
	prop_definitions = gen_dynamic_array( sizeof( PropDefinition ) );
	entity_definitions = gen_dynamic_array( sizeof( EntityDefinition ) );
}

void asciidng_terminate_registry()
{
	free_dynamic_array( &tile_definitions );
	free_dynamic_array( &prop_definitions );
	free_dynamic_array( &entity_definitions );
}

static void *find_definition_by_name( DynamicArray *dynarr, const char *name, size_t def_size )
{
	for ( size_t i = 0; i < dynarr->usage; ++i )
	{
		char *dname = ( char* ) dynarr->buffer + i * def_size;
		if ( strcmp( dname, name ) == 0 ) return def;
	}

	return NULL;
}

TileDefinition* asciidng_get_tile_definition( const char *name )
{
	return find_definition_by_name( &tile_definitions, name, sizeof( TileDefinition ) );
}

PropDefinition* asciidng_get_prop_definition( const char *name )
{
	return find_definition_by_name( &prop_definitions, name, sizeof( PropDefinition ) );
}

EntityDefinition* asciidng_get_entity_definition( const char *name )
{
	return find_definition_by_name( &entity_definitions, name, sizeof( EntityDefinition ) );
}

int asciidng_register_tile_definition( const char *name, Mesh *mesh, Texture *texture )
{
	if ( asciidng_get_tile_definition( name ) != NULL ) return 1;

	TileDefinition def = {
		name,
		mesh,
		texture
	};
	insert_data( &tile_definitions, &def, sizeof( TileDefinition ) );

	return 0;
}

int asciidng_register_prop_definition( const char *name, fvec3 scale,  Mesh *mesh, Texture *texture )
{
	if ( asciidng_get_prop_definition( name ) != NULL ) return 1;

	PropDefinition def = {
		name,
		scale,
		mesh,
		texture
	};
	insert_data( &prop_definitions, &def, sizeof( PropDefinition ) );

	return 0;
}

int asciidng_register_entity_definition( const char *name, ivec2 scale, Texture *texture )
{
	if ( asciidng_get_entity_definition( name ) != NULL ) return 1;

	EntityDefinition def = {
		name,
		scale,
		texture
	};
	insert_data( &entity_definitions, &def, sizeof( EntityDefinition ) );

	return 0;
}
