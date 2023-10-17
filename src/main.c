#include <stdio.h>
#include <stdlib.h>

#include <asciigl.h>

#include "workspace.h"
#include "menu.h"

static void cleanup()
{
	asciidng_cleanup_workspace();
}

static void init()
{
	asciigl_init();
	asciidng_init_workspace();

	atexit( cleanup );

	asciidng_load_menu();
}

static void loop()
{
	while (1){
		asciigl_process_frame();
	}
}

int main( int argc, char **argv )
{
	init();
	loop();
	
	return 0;
}
