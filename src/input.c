#include "input.h"
#include "conf.h"

#ifdef WINMODE
#include <windows.h>
static HANDLE g_h_std_in, g_h_std_out;
static INPUT_RECORD g_input_record;
static CONSOLE_CURSOR_INFO g_cci;
static DWORD g_events;
#elif defined LINMODE
#include <unistd.h>
#endif

#include <string.h>
#include <stdint.h>

#include <asciigl.h>

typedef struct RegisteredInput {
	char *identifier;
	uint16_t key_code;
} RegisteredInput;

static DynamicArray registered_inputs;

void asciidng_init_input()
{
	registered_inputs = gen_dynamic_array( sizeof( RegisteredInput ) );

	#ifdef WINMODE

	g_h_std_in = GetStdHandle(STD_INPUT_HANDLE);
	g_h_std_out = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleCursorInfo( g_h_std_out, &g_cci );
	SetConsoleMode( g_h_std_in, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT );

	#elif defined LINMODE

	#endif
}

int asciidng_is_input_registered( char *identifier )
{
	
}

int asciidng_register_input( char *identifier )
{
	size_t identifier_len = strlen( identifier ) + 1;
	char *identifier_cpy = malloc( identifier_len );
	if ( !identifier_cpy ) return 1;
	strcpy( identifier_cpy, identifier ); 
}

#include <stdio.h>

#ifdef WINMODE
static void win_handle_key_event( WORD keyCode, BOOL keyDown )
#elif defined LINMODE
static void uni_handle_key_event()
#endif
{
	printf( "Key event!\n" );
}

void asciidng_terminate_input()
{
	free_dynamic_array( &registered_inputs );
}

void asciidng_poll_input()
{
	#ifdef WINMODE

	DWORD awaiting_events;
	GetNumberOfConsoleInputEvents( g_h_std_in, &awaiting_events );

	if ( awaiting_events <= 0 ) return;

	for ( size_t r = 0; r < awaiting_events; ++r ){
		ReadConsoleInput( g_h_std_in, &g_input_record, 1, &g_events );
		switch ( g_input_record.EventType )
		{
			case KEY_EVENT:
				win_handle_key_event( g_input_record.Event.KeyEvent.wVirtualKeyCode, g_input_record.Event.KeyEvent.bKeyDown );
				break;
			case MOUSE_EVENT:
				break;
			case WINDOW_BUFFER_SIZE_EVENT:
			case FOCUS_EVENT:
			case MENU_EVENT:
				break;
			default:
				break;
		}
	}
	#endif
}
