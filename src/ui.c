#include "ui.h"

#include "input.h"
#include "workspace.h"

#include <asciigl.h>

/*
	ASCIIDNG_MOUSE_BUTTON,
	ASCIIDNG_MOUSE_DCLICK,
	ASCIIDNG_MOUSE_MOVE,
	ASCIIDNG_MOUSE_VWHEEL,
	ASCIIDNG_MOUSE_HWHEEL	
*/

static void *selected_ui = NULL;
static int selected_ui_layer = -1;
static enum ASCIIDNG_UI_INSTANCE_TYPE selected_ui_type = ASCIIDNG_UI_TEXT;

static void check_ui_text_events( MouseEvent e, void **current_selected_ui_out, int* current_selected_ui_layer_out, enum ASCIIDNG_UI_INSTANCE_TYPE *current_selected_ui_type_out )
{
	size_t ui_count = asciidng_get_ui_texts_count();
	void *current_selected_ui = NULL;
	int current_selected_ui_layer = -1;
	enum ASCIIDNG_UI_INSTANCE_TYPE current_selected_ui_type = ASCIIDNG_UI_TEXT;

	for ( size_t i = 0; i < ui_count; ++i )
	{
		UITextInstance *ui = asciidng_ui_text_at( i );
		int size_x = ui->ui_txt->size_x, size_y = ui->ui_txt->size_y;

		switch (e.type){
			case ASCIIDNG_MOUSE_MOVE:
				if (
					( e.mouse_position_x < ui->ui_txt->position.x || e.mouse_position_x > ui->ui_txt->position.x + size_x ) ||
					( e.mouse_position_y < ui->ui_txt->position.y || e.mouse_position_y > ui->ui_txt->position.y + size_y )  
				){
					continue;
				} else {
					if ( (int) ui->ui_txt->layer >= current_selected_ui_layer ){
						current_selected_ui = ui;
						current_selected_ui_layer = ui->ui_txt->layer;
					}
				}

				break;
			case ASCIIDNG_MOUSE_BUTTON:
				if ( e.mouse_position_x < ui->ui_txt->position.x || e.mouse_position_x > ui->ui_txt->position.x + size_x ) continue;
				if ( e.mouse_position_y < ui->ui_txt->position.y || e.mouse_position_y > ui->ui_txt->position.y + size_y ) continue;

				if ( ui->callbacks.on_mouse_click_callback != NULL ){
					ui->callbacks.on_mouse_click_callback( e, ( void* ) ui, ASCIIDNG_UI_TEXT );	
				}
				break;
			default:
				break;
		}


	}

	if ( e.type == ASCIIDNG_MOUSE_MOVE && current_selected_ui != NULL && *current_selected_ui_layer_out < current_selected_ui_layer ){
		*current_selected_ui_out = current_selected_ui;
		*current_selected_ui_layer_out = current_selected_ui_layer;
		*current_selected_ui_type_out = current_selected_ui_type;
	}
}

static void check_ui_frame_events( MouseEvent e, void **current_selected_ui_out, int* current_selected_ui_layer_out, enum ASCIIDNG_UI_INSTANCE_TYPE *current_selected_ui_type_out )
{
	size_t ui_count = asciidng_get_ui_frames_count();
	void *current_selected_ui = NULL;
	int current_selected_ui_layer = -1;
	enum ASCIIDNG_UI_INSTANCE_TYPE current_selected_ui_type = ASCIIDNG_UI_FRAME;

	for ( size_t i = 0; i < ui_count; ++i )
	{
		UIFrameInstance *ui = asciidng_ui_frame_at( i );
		int size_x = ui->ui_frame->size.x, size_y = ui->ui_frame->size.y;

		switch (e.type){
			case ASCIIDNG_MOUSE_MOVE:
				if (
					( e.mouse_position_x < ui->ui_frame->position.x || e.mouse_position_x > ui->ui_frame->position.x + size_x ) ||
					( e.mouse_position_y < ui->ui_frame->position.y || e.mouse_position_y > ui->ui_frame->position.y + size_y )  
				){
					continue;
				} else {
					if ( (int) ui->ui_frame->layer >= current_selected_ui_layer ){
						current_selected_ui = ui;
						current_selected_ui_layer = ui->ui_frame->layer;
					}
				}

				break;
			case ASCIIDNG_MOUSE_BUTTON:
				if ( e.mouse_position_x < ui->ui_frame->position.x || e.mouse_position_x > ui->ui_frame->position.x + size_x ) continue;
				if ( e.mouse_position_y < ui->ui_frame->position.y || e.mouse_position_y > ui->ui_frame->position.y + size_y ) continue;

				if ( ui->callbacks.on_mouse_click_callback != NULL ){
					ui->callbacks.on_mouse_click_callback( e, ( void* ) ui, ASCIIDNG_UI_FRAME );	
				}
				break;
			default:
				break;
		}


	}

	if ( e.type == ASCIIDNG_MOUSE_MOVE && current_selected_ui != NULL && *current_selected_ui_layer_out < current_selected_ui_layer ){
		*current_selected_ui_out = current_selected_ui;
		*current_selected_ui_layer_out = current_selected_ui_layer;
		*current_selected_ui_type_out = current_selected_ui_type;
	}
}

static void check_ui_image_events( MouseEvent e, void **current_selected_ui_out, int* current_selected_ui_layer_out, enum ASCIIDNG_UI_INSTANCE_TYPE *current_selected_ui_type_out )
{
	size_t ui_count = asciidng_get_ui_images_count();
	void *current_selected_ui = NULL;
	int current_selected_ui_layer = -1;
	enum ASCIIDNG_UI_INSTANCE_TYPE current_selected_ui_type = ASCIIDNG_UI_IMAGE;

	for ( size_t i = 0; i < ui_count; ++i )
	{
		UIImageInstance *ui = asciidng_ui_image_at( i );
		int size_x = ui->ui_image->size.x, size_y = ui->ui_image->size.y;

		switch (e.type){
			case ASCIIDNG_MOUSE_MOVE:
				if (
					( e.mouse_position_x < ui->ui_image->position.x || e.mouse_position_x > ui->ui_image->position.x + size_x ) ||
					( e.mouse_position_y < ui->ui_image->position.y || e.mouse_position_y > ui->ui_image->position.y + size_y )  
				){
					continue;
				} else {
					if ( (int)  ui->ui_image->layer >= current_selected_ui_layer ){
						current_selected_ui = ui;
						current_selected_ui_layer = ui->ui_image->layer;
					}
				}

				break;
			case ASCIIDNG_MOUSE_BUTTON:
				if ( e.mouse_position_x < ui->ui_image->position.x || e.mouse_position_x > ui->ui_image->position.x + size_x ) continue;
				if ( e.mouse_position_y < ui->ui_image->position.y || e.mouse_position_y > ui->ui_image->position.y + size_y ) continue;

				if ( ui->callbacks.on_mouse_click_callback != NULL ){
					ui->callbacks.on_mouse_click_callback( e, ( void* ) ui, ASCIIDNG_UI_IMAGE );	
				}
				break;
			default:
				break;
		}


	}

	if ( e.type == ASCIIDNG_MOUSE_MOVE && current_selected_ui != NULL && *current_selected_ui_layer_out < current_selected_ui_layer ){
		*current_selected_ui_out = current_selected_ui;
		*current_selected_ui_layer_out = current_selected_ui_layer;
		*current_selected_ui_type_out = current_selected_ui_type;
	}
}

static void check_ui_button_events( MouseEvent e, void **current_selected_ui_out, int* current_selected_ui_layer_out, enum ASCIIDNG_UI_INSTANCE_TYPE *current_selected_ui_type_out )
{
	size_t ui_count = asciidng_get_ui_buttons_count();
	void *current_selected_ui = NULL;
	int current_selected_ui_layer = -1;
	enum ASCIIDNG_UI_INSTANCE_TYPE current_selected_ui_type = ASCIIDNG_UI_BUTTON;

	for ( size_t i = 0; i < ui_count; ++i )
	{
		UIButtonInstance *ui = asciidng_ui_button_at( i );
		int size_x = ui->ui_frame->size.x, size_y = ui->ui_frame->size.y;

		switch (e.type){
			case ASCIIDNG_MOUSE_MOVE:
				if (
					( e.mouse_position_x < ui->ui_frame->position.x || e.mouse_position_x > ui->ui_frame->position.x + size_x ) ||
					( e.mouse_position_y < ui->ui_frame->position.y || e.mouse_position_y > ui->ui_frame->position.y + size_y )  
				){
					continue;
				} else {
					if ( (int) ui->ui_frame->layer >= current_selected_ui_layer ){
						current_selected_ui = ui;
						current_selected_ui_layer = ui->ui_frame->layer;
					}
				}

				break;
			case ASCIIDNG_MOUSE_BUTTON:
				if ( e.mouse_position_x < ui->ui_frame->position.x || e.mouse_position_x > ui->ui_frame->position.x + size_x ) continue;
				if ( e.mouse_position_y < ui->ui_frame->position.y || e.mouse_position_y > ui->ui_frame->position.y + size_y ) continue;

				if ( ui->callbacks.on_mouse_click_callback != NULL ){
					ui->callbacks.on_mouse_click_callback( e, ( void* ) ui, ASCIIDNG_UI_BUTTON );	
				}
				break;
			default:
				break;
		}


	}

	if ( e.type == ASCIIDNG_MOUSE_MOVE && current_selected_ui != NULL && *current_selected_ui_layer_out < current_selected_ui_layer ){
		*current_selected_ui_out = current_selected_ui;
		*current_selected_ui_layer_out = current_selected_ui_layer;
		*current_selected_ui_type_out = current_selected_ui_type;
	}
}

static void mouse_event_listener( MouseEvent e )
{
	void *current_selected_ui = NULL;
	int current_selected_ui_layer = -1;
	enum ASCIIDNG_UI_INSTANCE_TYPE current_selected_ui_type = ASCIIDNG_UI_TEXT;

	check_ui_text_events( e, &current_selected_ui, &current_selected_ui_layer, &current_selected_ui_type );
	check_ui_frame_events( e, &current_selected_ui, &current_selected_ui_layer, &current_selected_ui_type );
	check_ui_image_events( e, &current_selected_ui, &current_selected_ui_layer, &current_selected_ui_type );
	check_ui_button_events( e, &current_selected_ui, &current_selected_ui_layer, &current_selected_ui_type );

	if ( selected_ui == NULL && current_selected_ui != NULL ){
		UICallback cb1 = get_ui_callbacks( current_selected_ui, current_selected_ui_type )->on_mouse_enter_callback;
		if ( cb1 != NULL ) cb1( e, ( void* ) current_selected_ui, current_selected_ui_type );	
	}else if ( selected_ui != NULL && current_selected_ui == NULL ){
		UICallback cb1 = get_ui_callbacks( selected_ui, selected_ui_type )->on_mouse_leave_callback;
		if ( cb1 != NULL ) cb1( e, ( void* ) selected_ui, selected_ui_type );	
	}else if ( selected_ui != NULL && current_selected_ui != NULL && selected_ui != current_selected_ui ){
		UICallback cb1 = get_ui_callbacks( selected_ui, selected_ui_type )->on_mouse_leave_callback;
		if ( cb1 != NULL ) cb1( e, ( void* ) selected_ui, selected_ui_type );
		UICallback cb2 = get_ui_callbacks( current_selected_ui, current_selected_ui_type )->on_mouse_enter_callback;
		if ( cb2 != NULL ) cb2( e, ( void* ) current_selected_ui, current_selected_ui_type );	
	}

	selected_ui = current_selected_ui;
	selected_ui_layer = current_selected_ui_layer;
	selected_ui_type = current_selected_ui_type;
}

UICallbacks *get_ui_callbacks( void *ui, enum ASCIIDNG_UI_INSTANCE_TYPE type )
{
	switch ( type )
	{
		case ASCIIDNG_UI_TEXT:
			return &(( ( UITextInstance* ) ui )->callbacks);
		case ASCIIDNG_UI_FRAME:
			return &(( ( UIFrameInstance* ) ui )->callbacks);
		case ASCIIDNG_UI_IMAGE:
			return &(( ( UIImageInstance* ) ui )->callbacks);
		case ASCIIDNG_UI_BUTTON:
			return &(( ( UIButtonInstance* ) ui )->callbacks);
	}
	return NULL;
}

void asciidng_init_ui()
{
	asciidng_register_mouse_event_listener( mouse_event_listener );
}

void asciidng_terminate_ui()
{
	asciidng_unregister_mouse_event_listener( mouse_event_listener );
}
