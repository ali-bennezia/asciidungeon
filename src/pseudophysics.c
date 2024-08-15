#include "pseudophysics.h"

#include <asciigl.h>

static DynamicArray rigid_bodies;

void asciidng_physics_init()
{
	rigid_bodies = gen_dynamic_array( sizeof( RigidBody ) );
}

void asciidng_physics_loop()
{

}

void asciidng_physics_terminate()
{
	free_dynamic_array( &rigid_bodies );
}
