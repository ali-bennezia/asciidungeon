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
