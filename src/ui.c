#include "ui.h"

#include "input.h"
#include "workspace.h"

#include <asciigl.h>

/*
	ASCIIDNG_MOUSE_BUTTON,
	ASCIIDNG_MOUSE_DCLICK,
	ASCIIDNG_MOUSE_MOVE,
	ASCIIDNG_MOUSE_VWHEEL,
	ASCIIDNG_MOUSE_HWHEEL	
*/

static void check_ui_button_events()
{
	size_t btn_count = asciidng_get_ui_buttons_count();

	for ( size_t i = 0; i < btn_count; ++i )
	{
		UIButtonInstance *btn = asciidng_ui_button_at( i );		
	}
}

static void mouse_event_listener( MouseEvent e )
{
	switch ( e.type )
	{
		case ASCIIDNG_MOUSE_MOVE:

			break;
		default:
			break;
	}
}

void asciidng_init_ui()
{
	asciidng_register_mouse_event_listener( mouse_event_listener );
}

void asciidng_terminate_ui()
{
	asciidng_unregister_mouse_event_listener( mouse_event_listener );
}
