#include "keys.h"
#include "input.h"

#include <asciigl.h>

typedef struct RegisteredKey {
	char *identifier;
} RegisteredKey;

static DynamicArray g_registered_keys;

void asciidng_init_keys()
{
	g_registered_keys = gen_dynamic_array( sizeof( RegisteredKey ) );

	asciidng_register_key( "0" );
	asciidng_register_key( "1" );
	asciidng_register_key( "2" );
	asciidng_register_key( "3" );
	asciidng_register_key( "4" );
	asciidng_register_key( "5" );
	asciidng_register_key( "6" );
	asciidng_register_key( "7" );
	asciidng_register_key( "8" );
	asciidng_register_key( "9" );
	asciidng_register_key( "A" );
	asciidng_register_key( "B" );
	asciidng_register_key( "C" );
	asciidng_register_key( "D" );
	asciidng_register_key( "E" );
	asciidng_register_key( "F" );
	asciidng_register_key( "G" );
	asciidng_register_key( "H" );
	asciidng_register_key( "I" );
	asciidng_register_key( "J" );
	asciidng_register_key( "K" );
	asciidng_register_key( "L" );
	asciidng_register_key( "M" );
	asciidng_register_key( "N" );
	asciidng_register_key( "O" );
	asciidng_register_key( "P" );
	asciidng_register_key( "Q" );
	asciidng_register_key( "R" );
	asciidng_register_key( "S" );
	asciidng_register_key( "T" );
	asciidng_register_key( "U" );
	asciidng_register_key( "V" );
	asciidng_register_key( "W" );
	asciidng_register_key( "X" );
	asciidng_register_key( "Y" );
	asciidng_register_key( "Z" );
	asciidng_register_key( "LBUTTON" );
	asciidng_register_key( "RBUTTON" );
	asciidng_register_key( "CANCEL" );
	asciidng_register_key( "MBUTTON" );
	asciidng_register_key( "XBUTTON1" );
	asciidng_register_key( "XBUTTON2" );
	asciidng_register_key( "BACK" );
	asciidng_register_key( "TAB" );
	asciidng_register_key( "CLEAR" );
	asciidng_register_key( "RETURN" );
	asciidng_register_key( "SHIFT" );
	asciidng_register_key( "CONTROL" );
	asciidng_register_key( "MENU" );
	asciidng_register_key( "PAUSE" );
	asciidng_register_key( "CAPITAL" );
	asciidng_register_key( "KANA" );
	asciidng_register_key( "HANGUL" );
	asciidng_register_key( "IME_ON" );
	asciidng_register_key( "JUNJA" );
	asciidng_register_key( "FINAL" );
	asciidng_register_key( "HANJA" );
	asciidng_register_key( "KANJI" );
	asciidng_register_key( "IME_OFF" );
	asciidng_register_key( "ESCAPE" );
	asciidng_register_key( "CONVERT" );
	asciidng_register_key( "NONCONVERT" );
	asciidng_register_key( "ACCEPT" );
	asciidng_register_key( "MODECHANGE" );
	asciidng_register_key( "SPACE" );
	asciidng_register_key( "PRIOR" );
	asciidng_register_key( "NEXT" );
	asciidng_register_key( "END" );
	asciidng_register_key( "HOME" );
	asciidng_register_key( "LEFT" );
	asciidng_register_key( "UP" );
	asciidng_register_key( "RIGHT" );
	asciidng_register_key( "DOWN" );
	asciidng_register_key( "SELECT" );
	asciidng_register_key( "PRINT" );
	asciidng_register_key( "EXECUTE" );
	asciidng_register_key( "SNAPSHOT" );
	asciidng_register_key( "INSERT" );
	asciidng_register_key( "DELETE" );
	asciidng_register_key( "HELP" );
	asciidng_register_key( "LWIN" );
	asciidng_register_key( "RWIN" );
	asciidng_register_key( "APPS" );
	asciidng_register_key( "SLEEP" );
	asciidng_register_key( "NUMPAD0" );
	asciidng_register_key( "NUMPAD1" );
	asciidng_register_key( "NUMPAD2" );
	asciidng_register_key( "NUMPAD3" );
	asciidng_register_key( "NUMPAD4" );
	asciidng_register_key( "NUMPAD5" );
	asciidng_register_key( "NUMPAD6" );
	asciidng_register_key( "NUMPAD7" );
	asciidng_register_key( "NUMPAD8" );
	asciidng_register_key( "NUMPAD9" );
	asciidng_register_key( "MULTIPLY" );
	asciidng_register_key( "ADD" );
	asciidng_register_key( "SEPARATOR" );
	asciidng_register_key( "SUBTRACT" );
	asciidng_register_key( "DECIMAL" );
	asciidng_register_key( "DIVIDE" );
	asciidng_register_key( "F1" );
	asciidng_register_key( "F2" );
	asciidng_register_key( "F3" );
	asciidng_register_key( "F4" );
	asciidng_register_key( "F5" );
	asciidng_register_key( "F6" );
	asciidng_register_key( "F7" );
	asciidng_register_key( "F8" );
	asciidng_register_key( "F9" );
	asciidng_register_key( "F10" );
	asciidng_register_key( "F11" );
	asciidng_register_key( "F12" );
	asciidng_register_key( "F13" );
	asciidng_register_key( "F14" );
	asciidng_register_key( "F15" );
	asciidng_register_key( "F16" );
	asciidng_register_key( "F17" );
	asciidng_register_key( "F18" );
	asciidng_register_key( "F19" );
	asciidng_register_key( "F20" );
	asciidng_register_key( "F21" );
	asciidng_register_key( "F22" );
	asciidng_register_key( "F23" );
	asciidng_register_key( "F24" );
	asciidng_register_key( "NUMLOCK" );
	asciidng_register_key( "SCROLL" );
	asciidng_register_key( "LSHIFT" );
	asciidng_register_key( "RSHIFT" );
	asciidng_register_key( "LCONTROL" );
	asciidng_register_key( "RCONTROL" );
	asciidng_register_key( "LMENU" );
	asciidng_register_key( "RMENU" );
	asciidng_register_key( "BROWSER_BACK" );
	asciidng_register_key( "BROWSER_FORWARD" );
	asciidng_register_key( "BROWSER_REFRESH" );
	asciidng_register_key( "BROWSER_STOP" );
	asciidng_register_key( "BROWSER_SEARCH" );
	asciidng_register_key( "BROWSER_FAVORITES" );
	asciidng_register_key( "BROWSER_HOME" );
	asciidng_register_key( "VOLUME_MUTE" );
	asciidng_register_key( "VOLUME_DOWN" );
	asciidng_register_key( "VOLUME_UP" );
	asciidng_register_key( "MEDIA_NEXT_TRACK" );
	asciidng_register_key( "MEDIA_PREV_TRACK" );
	asciidng_register_key( "MEDIA_STOP" );
	asciidng_register_key( "MEDIA_PLAY_PAUSE" );
	asciidng_register_key( "LAUNCH_MAIL" );
	asciidng_register_key( "LAUNCH_MEDIA_SELECT" );
	asciidng_register_key( "LAUNCH_APP1" );
	asciidng_register_key( "LAUNCH_APP2" );
	asciidng_register_key( "OEM_1" );
	asciidng_register_key( "OEM_PLUS" );
	asciidng_register_key( "OEM_COMMA" );
	asciidng_register_key( "OEM_MINUS" );
	asciidng_register_key( "OEM_PERIOD" );
	asciidng_register_key( "OEM_2" );
	asciidng_register_key( "OEM_3" );
	asciidng_register_key( "OEM_4" );
	asciidng_register_key( "OEM_5" );
	asciidng_register_key( "OEM_6" );
	asciidng_register_key( "OEM_7" );
	asciidng_register_key( "OEM_8" );
	asciidng_register_key( "OEM_102" );
	asciidng_register_key( "PROCESSKEY" );
	asciidng_register_key( "PACKET" );
	asciidng_register_key( "PACKET" );
	asciidng_register_key( "ATTN" );
	asciidng_register_key( "CRSEL" );
	asciidng_register_key( "EXSEL" );
	asciidng_register_key( "EREOF" );
	asciidng_register_key( "PLAY" );
	asciidng_register_key( "ZOOM" );
	asciidng_register_key( "NONAME" );
	asciidng_register_key( "PA1" );
	asciidng_register_key( "OEM_CLEAR" );
}

void asciidng_terminate_keys()
{
	free_dynamic_array( &g_registered_keys );
}


int asciidng_is_key_registered( char *identifier )
{
	for ( size_t i = 0; i < g_registered_keys.usage; ++i )
	{
		if ( strcmp( identifier, ( ( RegisteredKey* ) g_registered_keys.buffer + i )->identifier ) == 0 ){
			return 1;
		}
	}
	return 0;	
}

uint16_t asciidng_get_key_code( char *identifier )
{
	for ( size_t i = 0; i < g_registered_keys.usage; ++i )
	{
		if ( strcmp( identifier, ( ( RegisteredKey* ) g_registered_keys.buffer + i )->identifier ) == 0 ){
			return i;
		}
	}
	return 0;	
}

int asciidng_register_key( char *identifier )
{
	if ( !identifier || asciidng_is_key_registered( identifier ) ) return 1;
	size_t identifier_len = strlen( identifier ) + 1;
	char *identifier_cpy = malloc( identifier_len );
	if ( !identifier_cpy ) return 1;
	strcpy( identifier_cpy, identifier ); 
	RegisteredKey inp = {
		identifier_cpy,
	};
	insert_data( &g_registered_keys, &inp, sizeof( RegisteredKey ) );	
}

