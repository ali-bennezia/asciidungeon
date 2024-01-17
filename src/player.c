#include "player.h"

#include <asciigl.h>

#include "boolval.h"
#include "input.h"

static boolval g_movement_enabled = false;

void asciidng_player_loop()
{
	if ( !g_movement_enabled ) return;
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
	if ( asciidng_get_input_state( "Jump" ) == 1 )
	{
		translate_player(0, 1, 0);
	}
	if ( asciidng_get_input_state( "Crouch" ) == 1 )
	{
		translate_player(0, -1, 0);
	}
}

static void player_mouse_event_listener( MouseEvent ev )
{
	if ( !g_movement_enabled ) return;
	if ( ev.type == ASCIIDNG_MOUSE_MOVE )
	{
		rotate_player(0, ( float ) -ev.move_data.mouse_delta_x / 30.0, 0);
		rotate_player(( float ) -ev.move_data.mouse_delta_y / 30.0, 0, 0);	
	}
}

void asciidng_init_player()
{
	asciidng_register_mouse_event_listener( player_mouse_event_listener );
}

void asciidng_terminate_player()
{
	asciidng_unregister_mouse_event_listener( player_mouse_event_listener );
}

void asciidng_set_movement_enabled( boolval val )
{
	g_movement_enabled = val;
}


