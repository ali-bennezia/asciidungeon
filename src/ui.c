#include "ui.h"

#include "input.h"

#include <asciigl.h>

static void mouse_event_listener( MouseEvent e )
{

}

void asciidng_init_ui()
{
	asciidng_register_mouse_event_listener( mouse_event_listener );
}

void asciidng_terminate_ui()
{
	asciidng_unregister_mouse_event_listener( mouse_event_listener );
}
