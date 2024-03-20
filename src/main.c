#include "conf.h"

#include <signal.h>

#ifdef WINMODE
#include <windows.h>
#elif define LINMODE
#endif

#include <stdio.h>
#include <stdlib.h>

#include <asciigl.h>

#include "registry.h"
#include "workspace.h"
#include "ui.h"
#include "menu.h"
#include "input.h"
#include "boolval.h"
#include "player.h"

#define DEBUG


boolval g_running = true;


static void terminate()
{
	g_running = false;
	asciidng_terminate_player();
	asciidng_terminate_input();
	asciidng_terminate_workspace();
	asciidng_terminate_registry();
}

void sigint_handler( int sig )
{
	terminate();
}

static void init()
{
	asciigl_init();
	asciidng_init_registry();
	asciidng_init_workspace();
	asciidng_init_input();
	asciidng_init_player();

	atexit( terminate );
	signal( SIGINT, sigint_handler );

	asciidng_load_menu();

	/*Mesh *cube_mesh = load_mesh( "assets/cube.obj" );
	cube_model = gen_model();
	cube_model->mesh = cube_mesh;
	Vec3 cube_pos = {0, 0, 15}, cube_rot = {0, 75, 0};
	cube_model->position = cube_pos;
	cube_model->rotation = cube_rot;*/

	RGB white = { 255, 255, 255 };

	Vec3 dir = { -10, -5, -10 };
	dir = vec3_normalize( dir );

	add_ambient_light( "Ambient light", 55, white );
	add_directional_light( "Directional light", 100, dir, white );

	// debug
	asciidng_register_tile_definition( "test_tile", NULL, NULL );
	ivec3 coords = {0, 0, 15};
	TileInstance *instance = asciidng_gen_tile( "test_tile", 0, 0, 15 );
	asciidng_gen_tile( "test_tile", 0, -1, 14 );
	asciidng_gen_tile( "test_tile", 0, -1, 13 );
	asciidng_gen_tile( "test_tile", 0, -1, 12 );
	asciidng_gen_tile( "test_tile", 0, -1, 2 );
	asciidng_gen_tile( "test_tile", 0, -1, 1 );
	asciidng_gen_tile( "test_tile", 0, -1, 0 );
	asciidng_hide_mouse();
}

static void loop()
{
	while (g_running)
	{
		asciidng_poll_input();
		asciigl_process_frame();
		asciidng_player_loop();
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
