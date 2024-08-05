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

static void check_ui_button_events( MouseEvent e )
{
	size_t ui_count = asciidng_get_ui_buttons_count();

	for ( size_t i = 0; i < ui_count; ++i )
	{
		UIButtonInstance *ui = asciidng_ui_button_at( i );
		int size_x = ui->ui_frame->size.x, size_y = ui->ui_frame->size.y;

		if ( e.mouse_position_x < ui->ui_frame->position.x || e.mouse_position_x > ui->ui_frame->position.x + size_x ) continue;
		if ( e.mouse_position_y < ui->ui_frame->position.y || e.mouse_position_y > ui->ui_frame->position.y + size_y ) continue;

		if ( e.type == ASCIIDNG_MOUSE_BUTTON && ui->callbacks.on_mouse_click_callback != NULL )
			ui->callbacks.on_mouse_click_callback( e, ( void* ) ui, ASCIIDNG_UI_BUTTON );	
	}
}

static void mouse_event_listener( MouseEvent e )
{
	check_ui_button_events( e );
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
