#ifndef __RBOCTREE_H__
#define __RBOCTREE_H__

#include "pseudophysics.h"

//struct RigidBody;
//typedef struct RigidBody RigidBody;

struct DynamicArray;
typedef struct DynamicArray DynamicArray;

void asciidng_init_octree();
void asciidng_terminate_octree();

void asciidng_register_octree_rigid_body( RigidBody *rb );
void asciidng_unregister_octree_rigid_body( RigidBody *rb );
void asciidng_update_octree_rigid_body( RigidBody *rb, BoundingBox old_bb );

DynamicArray *asciidng_get_nearby_objects( fvec3 position, float range );

#endif
