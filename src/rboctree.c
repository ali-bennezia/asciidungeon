#include "rboctree.h"

#include <stddef.h>

#include <asciigl.h>

// internals

#define ROOT_SIDE_LENGTH = 8000

typedef struct Node {
	size_t level;
	int x, y, z;
	struct Node *parent;
	struct Node *children[ 8 ];
} Node;

static Node root;

// API


