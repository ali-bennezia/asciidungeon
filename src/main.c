#include "conf.h"

#ifdef WINMODE
#include <windows.h>
#elif define LINMODE

#endif

#include <stdio.h>
#include <stdlib.h>

#include <asciigl.h>

#include "workspace.h"
#include "ui.h"
#include "menu.h"
#include "input.h"

static void test_on_forward( uint16_t key_code, uint8_t state )
{
	printf("forward\n");
}

static void test_on_backward( uint16_t key_code, uint8_t state )
{

}

static void test_on_rightward( uint16_t key_code, uint8_t state )
{

}

static void test_on_leftward( uint16_t key_code, uint8_t state )
{

}

static void terminate()
{
	asciidng_terminate_input();
	asciidng_terminate_workspace();
}

static void init()
{
	asciigl_init();
	asciidng_init_workspace();
	asciidng_init_input();

	atexit( terminate );

	asciidng_load_menu();

	// test
	asciidng_register_input_listener( "Forward", test_on_forward );
	asciidng_register_input_listener( "Backward", test_on_backward );
	asciidng_register_input_listener( "Rightward", test_on_rightward );
	asciidng_register_input_listener( "Leftward", test_on_leftward );
}

static void loop()
{

	while (1){
		asciidng_poll_input();
		asciigl_process_frame();
	}
}

#ifdef WINMODE
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow )
#elif defined LINMODE
int main( int argc, char **argv )
#endif
{
	init();
	loop();
	
	return 0;
}
