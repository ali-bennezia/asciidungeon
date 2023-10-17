#include "menu.h"
#include "workspace.h"

#include <asciigl.h>

static void create_btn( IntVec2 pos, char *txt, void(*on_click_func)() )
{

}

void asciidng_load_menu()
{
	IntVec2 pos = { 10, 10 };
	RGB col = { 255, 255, 255 };
	UIText *txt = gen_ui_text( "Hello World!", pos, col, 1 );

	IntVec2 pos2 = { 5, 5 }, size = { 30, 10 };
	RGB col2 = { 255, 0, 0 };
	UIFrame *frm = gen_ui_frame( pos2, size, col2, 0 );
}
