#include "keys.h"

#include "conf.h"

#include <stdlib.h>
#include <stdio.h>

#include <asciigl.h>

typedef struct IntPair {
	int key, value;
} IntPair;

static DynamicArray g_os_software_key_mappings;

static void register_os_software_key_mapping( int os_keycode, enum ASCIIDNG_KEY software_keycode )
{
	IntPair data = {
		os_keycode,
		( int ) software_keycode
	};	
	insert_data( &g_os_software_key_mappings, &data, sizeof( IntPair ) );
}

#ifdef WINMODE
static void register_os_software_key_mappings()
{
	register_os_software_key_mapping( 48, ASCIIDNG_KEY_0 );
	register_os_software_key_mapping( 49, ASCIIDNG_KEY_1 );
	register_os_software_key_mapping( 50, ASCIIDNG_KEY_2 );
	register_os_software_key_mapping( 51, ASCIIDNG_KEY_3 );
	register_os_software_key_mapping( 52, ASCIIDNG_KEY_4 );
	register_os_software_key_mapping( 53, ASCIIDNG_KEY_5 );
	register_os_software_key_mapping( 54, ASCIIDNG_KEY_6 );
	register_os_software_key_mapping( 55, ASCIIDNG_KEY_7 );
	register_os_software_key_mapping( 56, ASCIIDNG_KEY_8 );
	register_os_software_key_mapping( 57, ASCIIDNG_KEY_9 );
	register_os_software_key_mapping( 65, ASCIIDNG_KEY_A );
	register_os_software_key_mapping( 66, ASCIIDNG_KEY_B );
	register_os_software_key_mapping( 67, ASCIIDNG_KEY_C );
	register_os_software_key_mapping( 68, ASCIIDNG_KEY_D );
	register_os_software_key_mapping( 69, ASCIIDNG_KEY_E );
	register_os_software_key_mapping( 70, ASCIIDNG_KEY_F );
	register_os_software_key_mapping( 71, ASCIIDNG_KEY_G );
	register_os_software_key_mapping( 72, ASCIIDNG_KEY_H );
	register_os_software_key_mapping( 73, ASCIIDNG_KEY_I );
	register_os_software_key_mapping( 74, ASCIIDNG_KEY_J );
	register_os_software_key_mapping( 75, ASCIIDNG_KEY_K );
	register_os_software_key_mapping( 76, ASCIIDNG_KEY_L );
	register_os_software_key_mapping( 77, ASCIIDNG_KEY_M );
	register_os_software_key_mapping( 78, ASCIIDNG_KEY_N );
	register_os_software_key_mapping( 79, ASCIIDNG_KEY_O );
	register_os_software_key_mapping( 80, ASCIIDNG_KEY_P );
	register_os_software_key_mapping( 81, ASCIIDNG_KEY_Q );
	register_os_software_key_mapping( 82, ASCIIDNG_KEY_R );
	register_os_software_key_mapping( 83, ASCIIDNG_KEY_S );
	register_os_software_key_mapping( 84, ASCIIDNG_KEY_T );
	register_os_software_key_mapping( 85, ASCIIDNG_KEY_U );
	register_os_software_key_mapping( 86, ASCIIDNG_KEY_V );
	register_os_software_key_mapping( 87, ASCIIDNG_KEY_W );
	register_os_software_key_mapping( 88, ASCIIDNG_KEY_X );
	register_os_software_key_mapping( 89, ASCIIDNG_KEY_Y );
	register_os_software_key_mapping( 90, ASCIIDNG_KEY_Z );
	register_os_software_key_mapping( 1, ASCIIDNG_KEY_LBUTTON );
	register_os_software_key_mapping( 2, ASCIIDNG_KEY_RBUTTON );
	register_os_software_key_mapping( 3, ASCIIDNG_KEY_CANCEL );
	register_os_software_key_mapping( 4, ASCIIDNG_KEY_MBUTTON );
	register_os_software_key_mapping( 5, ASCIIDNG_KEY_XBUTTON1 );
	register_os_software_key_mapping( 6, ASCIIDNG_KEY_XBUTTON2 );
	register_os_software_key_mapping( 8, ASCIIDNG_KEY_BACK );
	register_os_software_key_mapping( 9, ASCIIDNG_KEY_TAB );
	register_os_software_key_mapping( 12, ASCIIDNG_KEY_CLEAR );
	register_os_software_key_mapping( 13, ASCIIDNG_KEY_RETURN );
	register_os_software_key_mapping( 16, ASCIIDNG_KEY_SHIFT );
	register_os_software_key_mapping( 17, ASCIIDNG_KEY_CONTROL );
	register_os_software_key_mapping( 18, ASCIIDNG_KEY_MENU );
	register_os_software_key_mapping( 19, ASCIIDNG_KEY_PAUSE );
	register_os_software_key_mapping( 20, ASCIIDNG_KEY_CAPITAL );
	register_os_software_key_mapping( 21, ASCIIDNG_KEY_KANA );
	register_os_software_key_mapping( 21, ASCIIDNG_KEY_HANGUL );
	register_os_software_key_mapping( 22, ASCIIDNG_KEY_IME_ON );
	register_os_software_key_mapping( 23, ASCIIDNG_KEY_JUNJA );
	register_os_software_key_mapping( 24, ASCIIDNG_KEY_FINAL );
	register_os_software_key_mapping( 25, ASCIIDNG_KEY_HANJA );
	register_os_software_key_mapping( 25, ASCIIDNG_KEY_KANJI );
	register_os_software_key_mapping( 26, ASCIIDNG_KEY_IME_OFF );
	register_os_software_key_mapping( 27, ASCIIDNG_KEY_ESCAPE );
	register_os_software_key_mapping( 28, ASCIIDNG_KEY_CONVERT );
	register_os_software_key_mapping( 29, ASCIIDNG_KEY_NONCONVERT );
	register_os_software_key_mapping( 30, ASCIIDNG_KEY_ACCEPT );
	register_os_software_key_mapping( 31, ASCIIDNG_KEY_MODECHANGE );
	register_os_software_key_mapping( 32, ASCIIDNG_KEY_SPACE );
	register_os_software_key_mapping( 33, ASCIIDNG_KEY_PRIOR );
	register_os_software_key_mapping( 34, ASCIIDNG_KEY_NEXT );
	register_os_software_key_mapping( 35, ASCIIDNG_KEY_END );
	register_os_software_key_mapping( 36, ASCIIDNG_KEY_HOME );
	register_os_software_key_mapping( 37, ASCIIDNG_KEY_LEFT );
	register_os_software_key_mapping( 38, ASCIIDNG_KEY_UP );
	register_os_software_key_mapping( 39, ASCIIDNG_KEY_RIGHT );
	register_os_software_key_mapping( 40, ASCIIDNG_KEY_DOWN );
	register_os_software_key_mapping( 41, ASCIIDNG_KEY_SELECT );
	register_os_software_key_mapping( 42, ASCIIDNG_KEY_PRINT );
	register_os_software_key_mapping( 43, ASCIIDNG_KEY_EXECUTE );
	register_os_software_key_mapping( 44, ASCIIDNG_KEY_SNAPSHOT );
	register_os_software_key_mapping( 45, ASCIIDNG_KEY_INSERT );
	register_os_software_key_mapping( 46, ASCIIDNG_KEY_DELETE );
	register_os_software_key_mapping( 47, ASCIIDNG_KEY_HELP );
	register_os_software_key_mapping( 91, ASCIIDNG_KEY_LWIN );
	register_os_software_key_mapping( 92, ASCIIDNG_KEY_RWIN );
	register_os_software_key_mapping( 93, ASCIIDNG_KEY_APPS );
	register_os_software_key_mapping( 95, ASCIIDNG_KEY_SLEEP );
	register_os_software_key_mapping( 96, ASCIIDNG_KEY_NUMPAD0 );
	register_os_software_key_mapping( 97, ASCIIDNG_KEY_NUMPAD1 );
	register_os_software_key_mapping( 98, ASCIIDNG_KEY_NUMPAD2 );
	register_os_software_key_mapping( 99, ASCIIDNG_KEY_NUMPAD3 );
	register_os_software_key_mapping( 100, ASCIIDNG_KEY_NUMPAD4 );
	register_os_software_key_mapping( 101, ASCIIDNG_KEY_NUMPAD5 );
	register_os_software_key_mapping( 102, ASCIIDNG_KEY_NUMPAD6 );
	register_os_software_key_mapping( 103, ASCIIDNG_KEY_NUMPAD7 );
	register_os_software_key_mapping( 104, ASCIIDNG_KEY_NUMPAD8 );
	register_os_software_key_mapping( 105, ASCIIDNG_KEY_NUMPAD9 );
	register_os_software_key_mapping( 106, ASCIIDNG_KEY_MULTIPLY );
	register_os_software_key_mapping( 107, ASCIIDNG_KEY_ADD );
	register_os_software_key_mapping( 108, ASCIIDNG_KEY_SEPARATOR );
	register_os_software_key_mapping( 109, ASCIIDNG_KEY_SUBTRACT );
	register_os_software_key_mapping( 110, ASCIIDNG_KEY_DECIMAL );
	register_os_software_key_mapping( 111, ASCIIDNG_KEY_DIVIDE );
	register_os_software_key_mapping( 112, ASCIIDNG_KEY_F1 );
	register_os_software_key_mapping( 113, ASCIIDNG_KEY_F2 );
	register_os_software_key_mapping( 114, ASCIIDNG_KEY_F3 );
	register_os_software_key_mapping( 115, ASCIIDNG_KEY_F4 );
	register_os_software_key_mapping( 116, ASCIIDNG_KEY_F5 );
	register_os_software_key_mapping( 117, ASCIIDNG_KEY_F6 );
	register_os_software_key_mapping( 118, ASCIIDNG_KEY_F7 );
	register_os_software_key_mapping( 119, ASCIIDNG_KEY_F8 );
	register_os_software_key_mapping( 120, ASCIIDNG_KEY_F9 );
	register_os_software_key_mapping( 121, ASCIIDNG_KEY_F10 );
	register_os_software_key_mapping( 122, ASCIIDNG_KEY_F11 );
	register_os_software_key_mapping( 123, ASCIIDNG_KEY_F12 );
	register_os_software_key_mapping( 124, ASCIIDNG_KEY_F13 );
	register_os_software_key_mapping( 125, ASCIIDNG_KEY_F14 );
	register_os_software_key_mapping( 126, ASCIIDNG_KEY_F15 );
	register_os_software_key_mapping( 127, ASCIIDNG_KEY_F16 );
	register_os_software_key_mapping( 128, ASCIIDNG_KEY_F17 );
	register_os_software_key_mapping( 129, ASCIIDNG_KEY_F18 );
	register_os_software_key_mapping( 130, ASCIIDNG_KEY_F19 );
	register_os_software_key_mapping( 131, ASCIIDNG_KEY_F20 );
	register_os_software_key_mapping( 132, ASCIIDNG_KEY_F21 );
	register_os_software_key_mapping( 133, ASCIIDNG_KEY_F22 );
	register_os_software_key_mapping( 134, ASCIIDNG_KEY_F23 );
	register_os_software_key_mapping( 135, ASCIIDNG_KEY_F24 );
	register_os_software_key_mapping( 144, ASCIIDNG_KEY_NUMLOCK );
	register_os_software_key_mapping( 145, ASCIIDNG_KEY_SCROLL );
	register_os_software_key_mapping( 160, ASCIIDNG_KEY_LSHIFT );
	register_os_software_key_mapping( 161, ASCIIDNG_KEY_RSHIFT );
	register_os_software_key_mapping( 162, ASCIIDNG_KEY_LCONTROL );
	register_os_software_key_mapping( 163, ASCIIDNG_KEY_RCONTROL );
	register_os_software_key_mapping( 164, ASCIIDNG_KEY_LMENU );
	register_os_software_key_mapping( 165, ASCIIDNG_KEY_RMENU );
	register_os_software_key_mapping( 166, ASCIIDNG_KEY_BROWSER_BACK );
	register_os_software_key_mapping( 167, ASCIIDNG_KEY_BROWSER_FORWARD );
	register_os_software_key_mapping( 168, ASCIIDNG_KEY_BROWSER_REFRESH );
	register_os_software_key_mapping( 169, ASCIIDNG_KEY_BROWSER_STOP );
	register_os_software_key_mapping( 170, ASCIIDNG_KEY_BROWSER_SEARCH );
	register_os_software_key_mapping( 171, ASCIIDNG_KEY_BROWSER_FAVORITES );
	register_os_software_key_mapping( 172, ASCIIDNG_KEY_BROWSER_HOME );
	register_os_software_key_mapping( 173, ASCIIDNG_KEY_VOLUME_MUTE );
	register_os_software_key_mapping( 174, ASCIIDNG_KEY_VOLUME_DOWN );
	register_os_software_key_mapping( 175, ASCIIDNG_KEY_VOLUME_UP );
	register_os_software_key_mapping( 176, ASCIIDNG_KEY_MEDIA_NEXT_TRACK );
	register_os_software_key_mapping( 177, ASCIIDNG_KEY_MEDIA_PREV_TRACK );
	register_os_software_key_mapping( 178, ASCIIDNG_KEY_MEDIA_STOP );
	register_os_software_key_mapping( 179, ASCIIDNG_KEY_MEDIA_PLAY_PAUSE );
	register_os_software_key_mapping( 180, ASCIIDNG_KEY_LAUNCH_MAIL );
	register_os_software_key_mapping( 181, ASCIIDNG_KEY_LAUNCH_MEDIA_SELECT );
	register_os_software_key_mapping( 182, ASCIIDNG_KEY_LAUNCH_APP1 );
	register_os_software_key_mapping( 183, ASCIIDNG_KEY_LAUNCH_APP2 );
	register_os_software_key_mapping( 186, ASCIIDNG_KEY_OEM_1 );
	register_os_software_key_mapping( 187, ASCIIDNG_KEY_OEM_PLUS );
	register_os_software_key_mapping( 188, ASCIIDNG_KEY_OEM_COMMA );
	register_os_software_key_mapping( 189, ASCIIDNG_KEY_OEM_MINUS );
	register_os_software_key_mapping( 190, ASCIIDNG_KEY_OEM_PERIOD );
	register_os_software_key_mapping( 191, ASCIIDNG_KEY_OEM_2 );
	register_os_software_key_mapping( 192, ASCIIDNG_KEY_OEM_3 );
	register_os_software_key_mapping( 219, ASCIIDNG_KEY_OEM_4 );
	register_os_software_key_mapping( 220, ASCIIDNG_KEY_OEM_5 );
	register_os_software_key_mapping( 221, ASCIIDNG_KEY_OEM_6 );
	register_os_software_key_mapping( 222, ASCIIDNG_KEY_OEM_7 );
	register_os_software_key_mapping( 223, ASCIIDNG_KEY_OEM_8 );
	register_os_software_key_mapping( 226, ASCIIDNG_KEY_OEM_102 );
	register_os_software_key_mapping( 229, ASCIIDNG_KEY_PROCESSKEY );
	register_os_software_key_mapping( 231, ASCIIDNG_KEY_PACKET );
	register_os_software_key_mapping( 231, ASCIIDNG_KEY_PACKET );
	register_os_software_key_mapping( 246, ASCIIDNG_KEY_ATTN );
	register_os_software_key_mapping( 247, ASCIIDNG_KEY_CRSEL );
	register_os_software_key_mapping( 248, ASCIIDNG_KEY_EXSEL );
	register_os_software_key_mapping( 249, ASCIIDNG_KEY_EREOF );
	register_os_software_key_mapping( 250, ASCIIDNG_KEY_PLAY );
	register_os_software_key_mapping( 251, ASCIIDNG_KEY_ZOOM );
	register_os_software_key_mapping( 252, ASCIIDNG_KEY_NONAME );
	register_os_software_key_mapping( 253, ASCIIDNG_KEY_PA1 );
	register_os_software_key_mapping( 254, ASCIIDNG_KEY_OEM_CLEAR );
}
#elif defined LINMODE
static void register_os_software_key_mappings()
{

}
#endif

enum ASCIIDNG_KEY asciidng_get_key_from_os_keycode( int keycode )
{
	for ( size_t i = 0 ; i < g_os_software_key_mappings.usage; ++i )
	{
		IntPair data = *( ( IntPair* ) g_os_software_key_mappings.buffer + i );
		if ( data.key == keycode )
		{
			return ( enum ASCIIDNG_KEY ) data.value;
			break;
		}
	}
	return 0;
}

void asciidng_init_keys()
{
	g_os_software_key_mappings = gen_dynamic_array( sizeof( IntPair ) );
	register_os_software_key_mappings();
}

void asciidng_terminate_keys()
{
	free_dynamic_array( &g_os_software_key_mappings );
}



