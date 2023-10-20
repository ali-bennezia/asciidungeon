#include "input.h"
#include "conf.h"

#ifdef WINMODE
#include <windows.h>
static HANDLE hStdInput, hStdOutput;
static INPUT_RECORD inputRecord;
static CONSOLE_CURSOR_INFO cci;
static EVENTS events;
#elif defined LINMODE
#include <unistd.h>
#endif

void asciidng_init_input()
{
	#ifdef WINMODE

	hStdInput = GetStdHandle(STD_INPUT_HANDLE);
	hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleCursorInfo( hStdOutput, &cci );
	SetConsoleMode( hStdInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT );

	#elif defined LINMODE

	#endif
}

#ifdef WINMODE
static void handle_key_event( WORD keyCode )
#elif defined LINMODE
#endif
{

}

void asciidng_terminate_input()
{

	#ifdef WINMODE

	ReadConsoleInput( hStdInput, &inputRecord, 1, &events );
	switch ( inputRecord.EventType )
	{
		case KEY_EVENT:
			handle_key_event( inputRecord.Event.KeyEvent.wVirtualKeyCode );
			break;
		case MOUSE_EVENT:

			break;
		case WINDOW_BUFFER_SIZE_EVENT:
			break;
		case FOCUS_EVENT:
			break;
		case MENU_EVENT:
			break;
		default:
			break;

	}

	#endif

}

void asciidng_poll_input()
{
	#ifdef WINMODE

	#elif defined LINMODE

	#endif
}
