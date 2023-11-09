#ifndef _KEYS_H_
#define _KEYS_H_

#include <stdint.h>

void asciidng_init_keys();
void asciidng_terminate_keys();

int asciidng_is_key_registered( char *identifier );
uint16_t asciidng_get_key_code( char *identifier );
int asciidng_register_key( char *identifier );

#endif
