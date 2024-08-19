#include "pseudophysics.h"

#include <asciigl.h>

typedef struct RigidBodyQuadTreeNode {
	int x, y;
	DynamicArray data;
	struct RigidBodyQuadTreeNode *children[ 4 ];
} RigidBodyQuadTreeNode;

static RigidBodyQuadTreeNode root;

RaycastResult asciidng_cast_ray( Ray ray )
{
	RaycastResult result = { ray, NULL, fvec3_zero() };
	return result;
}

void asciidng_init_physics()
{
	
}

void asciidng_loop_physics()
{

}

void asciidng_terminate_physics()
{
}
