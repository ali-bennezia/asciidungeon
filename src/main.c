#include <stdio.h>
#include <asciigl.h>

static void init()
{
	asciigl_init();
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
