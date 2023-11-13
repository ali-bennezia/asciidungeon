#include "input.h"
#include "conf.h"
#include "keys.h"

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
	uint16_t key;
	uint8_t state;
} RegisteredInput;

static DynamicArray g_registered_inputs;



void asciidng_init_input()
{
	asciidng_init_keys();
	g_registered_inputs = gen_dynamic_array( sizeof( RegisteredInput ) );

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
	for ( size_t i = 0; i < g_registered_inputs.usage; ++i )
	{
		if ( strcmp( identifier, ( ( RegisteredInput* ) g_registered_inputs.buffer + i )->identifier ) == 0 ){
			return 1;
		}
	}
	return 0;	
}

int asciidng_register_input( char *identifier, uint16_t key )
{
	if ( !identifier || asciidng_is_input_registered( identifier ) ) return 1;
	size_t identifier_len = strlen( identifier ) + 1;
	char *identifier_cpy = malloc( identifier_len );
	if ( !identifier_cpy ) return 1;
	strcpy( identifier_cpy, identifier ); 
	RegisteredInput inp = {
		identifier_cpy,
		key,
		0
	};
	insert_data( &g_registered_inputs, &inp, sizeof( RegisteredInput ) );	
}

static int asciidng_set_input_state( char *identifier, uint8_t state )
{
	for ( size_t i = 0; i < g_registered_inputs.usage; ++i )
	{
		RegisteredInput *input = ( RegisteredInput* ) g_registered_inputs.buffer + i; 
		if ( strcmp( identifier, input->identifier ) == 0 ){
			input->state = state;
			return 1;
		}
	}
	return 0;	
}

#include <stdio.h>

#ifdef WINMODE
static void win_handle_key_event( WORD key_code, BOOL key_down )
{
	printf( "Key event!\n" );
}
#elif defined LINMODE
static void uni_handle_key_event()
{

}
#endif


void asciidng_terminate_input()
{
	free_dynamic_array( &g_registered_inputs );
	asciidng_terminate_keys();
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
