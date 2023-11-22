#include "conf.h"

#ifdef WINMODE
#include <windows.h>
#elif define LINMODE

#endif

#include <stdio.h>
#include <stdlib.h>

#include <asciigl.h>

#include "workspace.h"
#include "ui.h"
#include "menu.h"
#include "input.h"

Model *cube_model;

static void debug_loop()
{
	cube_model->rotation.x += 7;
	cube_model->rotation.y += 8;
	cube_model->rotation.z += 5;

	if ( asciidng_get_input_state( "Forward" ) == 1 )
	{
		translate_player(0, 0, 1);
	}
	if ( asciidng_get_input_state( "Backward" ) == 1 )
	{
		translate_player(0, 0, -1);
	}
	if ( asciidng_get_input_state( "Rightward" ) == 1 )
	{
		translate_player(1, 0, 0);
	}
	if ( asciidng_get_input_state( "Leftward" ) == 1 )
	{
		translate_player(-1, 0, 0);
	}
}

static void terminate()
{
	asciidng_terminate_input();
	asciidng_terminate_workspace();
}

static void init()
{
	asciigl_init();
	asciidng_init_workspace();
	asciidng_init_input();

	atexit( terminate );

	asciidng_load_menu();

	Mesh *cube_mesh = load_mesh( "assets/cube.obj" );
	cube_model = gen_model();
	cube_model->mesh = cube_mesh;
	Vec3 cube_pos = {0, 0, 15}, cube_rot = {0, 75, 0};
	cube_model->position = cube_pos;
	cube_model->rotation = cube_rot;

	RGB white = { 255, 255, 255 };

	Vec3 dir = { -10, -5, -10 };
	dir = vec3_normalize( dir );

	add_ambient_light( "Ambient light", 55, white );
	add_directional_light( "Directional light", 100, dir, white );
}

static void loop()
{
	while (1){
		asciidng_poll_input();
		asciigl_process_frame();
		debug_loop();
	}
}

#ifdef WINMODE
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow )
#elif defined LINMODE
int main( int argc, char **argv )
#endif
{
	init();
	loop();
	
	return 0;
}
