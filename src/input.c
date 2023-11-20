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
	DynamicArray listeners;
} RegisteredInput;

static DynamicArray g_registered_inputs;

// static utils

static RegisteredInput *get_input_ptr( char *identifier )
{
	for ( size_t i = 0; i < g_registered_inputs.usage; ++i )
	{
		RegisteredInput *input = ( RegisteredInput* ) g_registered_inputs.buffer + i;

		if ( strcmp( input->identifier, identifier ) == 0 )
		{
			return input;
		} 
	}
	return NULL;
}

static RegisteredInput *get_input_ptr_from_key( uint16_t key_code )
{
	for ( size_t i = 0; i < g_registered_inputs.usage; ++i )
	{
		RegisteredInput *input = ( RegisteredInput* ) g_registered_inputs.buffer + i;

		if ( input->key == key_code )
		{
			return input;
		} 
	}
	return NULL;
}

static void call_input_listeners( RegisteredInput *input )
{
	for ( size_t i = 0; i < input->listeners.usage; ++ i)
	{
		void (*i_listener)(uint16_t,uint8_t) = *( ( void(**)(uint16_t,uint8_t) ) input->listeners.buffer + i );
		i_listener( input->key, input->state );
	}	
}

static int set_input_state( char *identifier, uint8_t state )
{
	RegisteredInput *input = get_input_ptr( identifier );
	if ( input == NULL ) return 1;
	uint8_t p_state = input->state;
	input->state = state;
	if ( p_state != state )
		call_input_listeners( input );
	return 0;	
}

static int get_listener_index( RegisteredInput *input, void (*listener)(uint16_t,uint8_t) )
{
	for ( size_t i = 0; i < input->listeners.usage; ++i )
	{
		void (*i_listener)(uint16_t,uint8_t) = *( ( void (**)(uint16_t,uint8_t )  ) input->listeners.buffer + i );
		if ( listener == i_listener )
			return i;
	}
	return -1;
}


// input funcs

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
	return ( get_input_ptr( identifier ) != NULL );
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
		0,
		gen_dynamic_array( sizeof( void (*)(uint16_t, uint8_t) ) )
	};
	insert_data( &g_registered_inputs, &inp, sizeof( RegisteredInput ) );	
	return 0;
}

int asciidng_unregister_input( char *identifier )
{
	if ( !identifier || !asciidng_is_input_registered( identifier ) ) return 1;

	for ( size_t i = 0; i < g_registered_inputs.usage; ++i )
	{
		RegisteredInput *input = ( RegisteredInput* ) g_registered_inputs.buffer + i;

		if ( strcmp( input->identifier, identifier ) == 0 )
		{
			free_dynamic_array( &input->listeners );
			remove_data( &g_registered_inputs, i, sizeof( RegisteredInput ) );
			return 0;
		} 
	}
	
	return 1;
}

int asciidng_register_input_listener( char *identifier, void (*listener)(uint16_t, uint8_t) )
{
	if ( !identifier || !asciidng_is_input_registered( identifier ) ) return 1;

	RegisteredInput *input = get_input_ptr( identifier );
	insert_data( &input->listeners, &listener, sizeof( void(*)(uint16_t, uint8_t) ) );
	return 0;
}

int asciidng_unregister_input_listener( char *identifier, void (*listener)(uint16_t, uint8_t) )
{
	if ( !identifier || !asciidng_is_input_registered( identifier ) ) return 1;

	RegisteredInput *input = get_input_ptr( identifier );
	int listener_index = get_listener_index( input, listener );	

	if ( listener_index == -1 ) return 1;	

	remove_data( &input->listeners, listener_index, sizeof( void (*)(uint16_t, uint8_t) ) );	

	return 0;
}

#include <stdio.h>

#ifdef WINMODE
static void win_handle_key_event( WORD key_code, BOOL key_down )
{
	enum ASCIIDNG_KEY stw_key = asciidng_get_key_from_os_keycode( ( int ) key_code );
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
