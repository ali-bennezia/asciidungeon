#ifndef __RBOCTREE_H__
#define __RBOCTREE_H__

#include "pseudophysics.h"

//struct RigidBody;
//typedef struct RigidBody RigidBody;

void asciidng_init_octree();
void asciidng_terminate_octree();

void asciidng_register_octree_rigid_body( RigidBody *rb );
void asciidng_unregister_octree_rigid_body( RigidBody *rb );
void asciidng_update_octree_rigid_body( RigidBody *rb, BoundingBox old_bb );

#endif
