#ifndef _INPUT_H_
#define _INPUT_H_

#include <stdint.h>

void asciidng_init_input();
void asciidng_terminate_input();
void asciidng_poll_input();

int asciidng_is_input_registered( char *identifier );
int asciidng_get_key_state( uint16_t key_code );
int asciidng_register_input( char *identifier, uint16_t key );
int asciidng_unregister_input( char *identifier );
int asciidng_clear_inputs();

int asciidng_register_input_listener( char *identifier, void (*listener)(uint16_t, uint8_t) );
int asciidng_unregister_input_listener( char *identifier, void (*listener)(uint16_t, uint8_t) );

#endif
