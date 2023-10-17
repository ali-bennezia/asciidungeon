#include "workspace.h"

#include <asciigl.h>

#include "ui.h"

static DynamicArray tiles, props, entities;
static DynamicArray buttons, images; 

void asciidng_init_workspace()
{
	tiles = gen_dynamic_array( sizeof( Model* ) );
	props = gen_dynamic_array( sizeof( Model* ) );
	entities = gen_dynamic_array( sizeof( Model* ) );

	buttons = gen_dynamic_array( sizeof( Button* ) );
	images = gen_dynamic_array( sizeof( UIImage* ) ); 
}

void asciidng_terminate_workspace()
{
	free_dynamic_array( &images );
	free_dynamic_array( &buttons );

	free_dynamic_array( &tiles );
	free_dynamic_array( &props );
	free_dynamic_array( &entities );
}


