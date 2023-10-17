#include "workspace.h"

#include <asciigl.h>

DynamicArray tiles, props, entities;

void asciidng_init_workspace()
{
	tiles = gen_dynamic_array( sizeof( Model* ) );
	props = gen_dynamic_array( sizeof( Model* ) );
	entities = gen_dynamic_array( sizeof( Model* ) );
}

void asciidng_cleanup_workspace()
{
	free_dynamic_array( &tiles );
	free_dynamic_array( &props );
	free_dynamic_array( &entities );
}
