#include "input.h"
#include "conf.h"
#include "keys.h"
#include "boolval.h"

#ifdef WINMODE
#define OEMRESOURCE
#include <windows.h>
static HWND g_h_console;
static HANDLE g_h_std_in, g_h_std_out;
static INPUT_RECORD g_input_records[ 128 ];
static CONSOLE_CURSOR_INFO g_cci;
static DWORD g_events;

static HANDLE g_hArrowCursor, g_hNoCursor;
static HCURSOR g_hcArrowCursor, g_hcNoCursor;
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

static DynamicArray g_registered_inputs, g_mouse_event_listeners;

static IntVec2 g_mouse_position = { 0, 0 }, g_mouse_btn_states = { 0, 0 };
static IntVec2 g_old_mouse_pos = { 0, 0 };

static boolval g_lock_mouse = false;

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

static int set_input_state( RegisteredInput *input, uint8_t state )
{
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

static int get_mouse_event_listener_index( void (*listener)(MouseEvent) )
{
	for ( size_t i = 0; i < g_mouse_event_listeners.usage; ++i )
	{
		void (*i_listener)(MouseEvent) = *( ( void(**)(MouseEvent) ) g_mouse_event_listeners.buffer + i );
		if ( i_listener == listener ) return i;	
	}
	return -1;
}

static void call_mouse_event_listeners( MouseEvent event )
{
	for ( size_t i = 0; i < g_mouse_event_listeners.usage; ++i )
	{
		void (*i_listener)(MouseEvent) = *( ( void(**)(MouseEvent) ) g_mouse_event_listeners.buffer + i );
		i_listener( event );
	}
}

// input funcs

void asciidng_init_input()
{
	asciidng_init_keys();
	g_registered_inputs = gen_dynamic_array( sizeof( RegisteredInput ) );
	g_mouse_event_listeners = gen_dynamic_array( sizeof( void(*)(MouseEvent) ) );

	#ifdef WINMODE

	g_h_std_in = GetStdHandle(STD_INPUT_HANDLE);
	g_h_std_out = GetStdHandle(STD_OUTPUT_HANDLE);

	g_h_console = GetConsoleWindow();

	SetConsoleCursorInfo( g_h_std_out, &g_cci );
	SetConsoleMode( g_h_std_in, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT );

	g_hArrowCursor = LoadImage( NULL, MAKEINTRESOURCE( IDC_ARROW ), IMAGE_CURSOR, 0, 0, LR_SHARED );
	g_hNoCursor = LoadImage( GetModuleHandle( NULL ), "../assets/nocursor.cur", IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE );

	g_hcArrowCursor = CopyCursor( g_hArrowCursor );
	g_hcNoCursor = CopyCursor( g_hNoCursor );

	#elif defined LINMODE

	#endif

	asciidng_register_input( "Forward", ASCIIDNG_KEY_W );
	asciidng_register_input( "Backward", ASCIIDNG_KEY_S );
	asciidng_register_input( "Rightward", ASCIIDNG_KEY_D );	
	asciidng_register_input( "Leftward", ASCIIDNG_KEY_A );
	asciidng_register_input( "Jump", ASCIIDNG_KEY_SPACE );
	asciidng_register_input( "Crouch", ASCIIDNG_KEY_SHIFT );	
}

int asciidng_is_input_registered( char *identifier )
{
	return ( get_input_ptr( identifier ) != NULL );
}

int asciidng_get_input_state( char *identifier )
{
	RegisteredInput *input = get_input_ptr( identifier );
	if ( input == NULL ) return 1;
	return input->state;
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

int asciidng_clear_inputs()
{
	for ( size_t i = 0; i < g_registered_inputs.usage; ++i )
	{	
		RegisteredInput *input = ( RegisteredInput* ) g_registered_inputs.buffer + i;
		free_dynamic_array( &input->listeners );
	}
	clear_dynamic_array( &g_registered_inputs, sizeof( RegisteredInput ) );	
}

int asciidng_register_mouse_event_listener( void (*listener)(MouseEvent) )
{
	insert_data( &g_mouse_event_listeners, &listener, sizeof( void(*)(MouseEvent) ) );
}

int asciidng_unregister_mouse_event_listener( void (*listener)(MouseEvent) )
{
	int index = get_mouse_event_listener_index( listener );
	if ( index < 0 ) return 1;
	remove_data( &g_mouse_event_listeners, index, sizeof( void(*)(MouseEvent) ) );
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

int asciidng_hide_mouse()
{
	g_lock_mouse = true;
	asciidng_center_mouse();

	#ifdef WINMODE

	RECT rect;

	GetClientRect( g_h_console, &rect );
	ClientToScreen( g_h_console, ( POINT* ) &rect.left ); 
	ClientToScreen( g_h_console, ( POINT* ) &rect.right );
	ClipCursor( &rect );

	SetSystemCursor( g_hcNoCursor, OCR_NORMAL );

	#elif defined LINMODE

	#endif
}

int asciidng_show_mouse()
{
	g_lock_mouse = false;

	#ifdef WINMODE
	ClipCursor( NULL );
	SetSystemCursor( g_hcArrowCursor, OCR_NORMAL );
	#elif defined LINMODE
	#endif
}

int asciidng_center_mouse()
{
	IntVec2 delta_mouse = {
		g_mouse_position.x - g_old_mouse_pos.x,
		g_mouse_position.y - g_old_mouse_pos.y
	};

	#ifdef WINMODE

	RECT rect;

	GetClientRect( g_h_console, &rect );
	ClientToScreen( g_h_console, ( POINT* ) &rect.left );
	ClientToScreen( g_h_console, ( POINT* ) &rect.right );

	int X =	rect.left + ( (int) rect.right - (int) rect.left ) / 2.0;
	int Y =	rect.bottom + ( (int) rect.top - (int) rect.bottom ) / 2.0;

	SetCursorPos( X, Y );

	g_mouse_position.x = X;
	g_mouse_position.y = Y;
	g_old_mouse_pos.x = g_mouse_position.x - delta_mouse.x;
	g_old_mouse_pos.y = g_mouse_position.y - delta_mouse.y;

	#elif define LINMODE

	#endif
}

#ifdef WINMODE
static void win_handle_key_event( WORD key_code, BOOL key_down )
{
	enum ASCIIDNG_KEY stw_key = asciidng_get_key_from_os_keycode( ( int ) key_code );
	uint8_t new_state = (uint8_t) key_down;
	RegisteredInput *input = get_input_ptr_from_key( ( uint16_t ) stw_key );
	set_input_state( input, new_state );
}

static void win_poll_mouse_events()
{
	MouseEvent ev;

	POINT m_pos;
	GetCursorPos( &m_pos );
	g_old_mouse_pos.x = g_mouse_position.x;
	g_old_mouse_pos.y = g_mouse_position.y;
	g_mouse_position.x = m_pos.x;
	g_mouse_position.y = m_pos.y;

	IntVec2 delta_mouse_pos = {
		g_mouse_position.x - g_old_mouse_pos.x,
		g_mouse_position.y - g_old_mouse_pos.y
	};

	if ( g_old_mouse_pos.x != g_mouse_position.x || g_old_mouse_pos.y != g_mouse_position.y )
	{
		ev.type = ASCIIDNG_MOUSE_MOVE;
		ev.move_data.mouse_delta_x = delta_mouse_pos.x;
		ev.move_data.mouse_delta_y = delta_mouse_pos.y;
		ev.move_data.mouse_position_x = g_mouse_position.x;
		ev.move_data.mouse_position_y = g_mouse_position.y;
		call_mouse_event_listeners( ev );
	}

	SHORT lbtndata = GetAsyncKeyState( VK_LBUTTON );
	short left_btn_state = ( lbtndata >> 16 != 0 );
	SHORT rbtndata = GetAsyncKeyState( VK_RBUTTON );
	short right_btn_state = ( rbtndata >> 16 != 0 );

	IntVec2 new_btn_states = {
		left_btn_state,
		right_btn_state
	}, old_btn_states = g_mouse_btn_states;
	g_mouse_btn_states = new_btn_states;
	
	if ( new_btn_states.x != old_btn_states.x )
	{
		ev.type = ASCIIDNG_MOUSE_BUTTON;
		ev.button_data.button = ASCIIDNG_MOUSE_LBTN;	
		ev.button_data.state = g_mouse_btn_states.x;
		call_mouse_event_listeners( ev );
	}

	if ( new_btn_states.y != old_btn_states.y )
	{
		ev.type = ASCIIDNG_MOUSE_BUTTON;
		ev.button_data.button = ASCIIDNG_MOUSE_RBTN;	
		ev.button_data.state = g_mouse_btn_states.y;
		call_mouse_event_listeners( ev );
	}
}

#elif defined LINMODE
static void uni_handle_key_event()
{

}
#endif


void asciidng_terminate_input()
{
	asciidng_show_mouse();
	asciidng_clear_inputs();
	free_dynamic_array( &g_mouse_event_listeners );
	free_dynamic_array( &g_registered_inputs );
	asciidng_terminate_keys();

	#ifdef WINMODE
	DestroyCursor( g_hcArrowCursor );
	DestroyCursor( g_hcNoCursor );
	#elif defined LINMODE

	#endif
}

void asciidng_poll_input()
{
	#ifdef WINMODE

	DWORD awaiting_events;
	GetNumberOfConsoleInputEvents( g_h_std_in, &awaiting_events );

	if ( awaiting_events > 0 ){

		ReadConsoleInput( g_h_std_in, &g_input_records[ 0 ], 128, &g_events );
		for ( size_t r = 0; r < g_events; ++r ){
			INPUT_RECORD input_record = g_input_records[ r ];
			switch ( input_record.EventType )
			{
				case KEY_EVENT:
					win_handle_key_event( input_record.Event.KeyEvent.wVirtualKeyCode, input_record.Event.KeyEvent.bKeyDown );
					break;
				case MOUSE_EVENT:
				case WINDOW_BUFFER_SIZE_EVENT:
				case FOCUS_EVENT:
				case MENU_EVENT:
					break;
				default:
					break;
			}
		}

	}

	win_poll_mouse_events();
	#endif

	if ( g_lock_mouse )
		asciidng_center_mouse();
}
