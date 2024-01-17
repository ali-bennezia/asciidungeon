#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "boolval.h"

void asciidng_player_loop();
void asciidng_set_movement_enabled( boolval val );
void asciidng_init_player();
void asciidng_terminate_player();

#endif
