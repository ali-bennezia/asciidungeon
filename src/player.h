#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "boolval.h"

void asciidng_loop_player();

void asciidng_init_player();
void asciidng_terminate_player();

boolval sciidng_get_movement_enabled();
void asciidng_set_movement_enabled( boolval val );

#endif
