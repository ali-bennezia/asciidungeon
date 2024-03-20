#include "utils.h"

#include <asciigl.h>

void foreach_dynarr( DynamicArray *arr, size_t elem_size, void (*func)(void*) )
{
	for ( size_t i = 0; i < arr->usage; ++i )
	{
		func( ( char* ) arr->buffer + elem_size * i );
	}	
}
