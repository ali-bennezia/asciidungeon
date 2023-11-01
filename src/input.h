#ifndef _INPUT_H_
#define _INPUT_H_

#include <stdint.h>

void asciidng_init_input();
void asciidng_terminate_input();
void asciidng_poll_input();

int asciidng_is_key_registered( char *identifier );
uint16_t asciidng_get_key_code( char *identifier );
int asciidng_register_key( char *identifier );

int asciidng_is_input_registered( char *identifier );
int asciidng_register_input( char *identifier, uint16_t key );

#endif
