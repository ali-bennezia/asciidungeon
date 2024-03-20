#ifndef _UTILS_H_
#define _UTILS_H_

#include <stddef.h>

struct DynamicArray;
typedef struct DynamicArray DynamicArray;

void foreach_dynarr( DynamicArray *arr, size_t elem_size, void (*func)(void*) );

#endif
