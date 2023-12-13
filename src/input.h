#ifndef _INPUT_H_
#define _INPUT_H_


#include <stdint.h>

enum ASCIIDNG_MOUSE_EVENT {
	ASCIIDNG_MOUSE_BUTTON,
	ASCIIDNG_MOUSE_DCLICK,
	ASCIIDNG_MOUSE_MOVE,
	ASCIIDNG_MOUSE_VWHEEL,
	ASCIIDNG_MOUSE_HWHEEL	
};

enum ASCIIDNG_MOUSE_BUTTON {
	ASCIIDNG_MOUSE_LBTN,
	ASCIIDNG_MOUSE_RBTN
};

typedef struct _MouseButtonEvent {
	enum ASCIIDNG_MOUSE_BUTTON button;
	unsigned short state;
} MouseButtonEvent;

typedef struct _MouseMoveEvent {
	int mouse_position_x, mouse_position_y;
	int mouse_delta_x, mouse_delta_y;
} MouseMoveEvent;

typedef struct _MouseEvent {
	enum ASCIIDNG_MOUSE_EVENT type;
	union {
		MouseButtonEvent button_data;
		int wheel_delta;
		MouseMoveEvent move_data;
	};
} MouseEvent;

void asciidng_init_input();
void asciidng_terminate_input();
void asciidng_poll_input();

int asciidng_is_input_registered( char *identifier );
int asciidng_get_input_state( char *identifier );
int asciidng_register_input( char *identifier, uint16_t key );
int asciidng_unregister_input( char *identifier );
int asciidng_clear_inputs();

int asciidng_register_mouse_event_listener( void (*listener)(MouseEvent) ); 
int asciidng_unregister_mouse_event_listener( void (*listener)(MouseEvent) );
int asciidng_hide_mouse();
int asciidng_show_mouse(); 

int asciidng_register_input_listener( char *identifier, void (*listener)(uint16_t, uint8_t) );
int asciidng_unregister_input_listener( char *identifier, void (*listener)(uint16_t, uint8_t) );

#endif
