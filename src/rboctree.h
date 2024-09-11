#ifndef __RBOCTREE_H__
#define __RBOCTREE_H__

struct RigidBody;
typedef struct RigidBody RigidBody;

void asciidng_init_octree();
void asciidng_terminate_octree();

void asciidng_register_octree_rigid_body( RigidBody *rb );
void asciidng_unregister_octree_rigid_body( RigidBody *rb );
void asciidng_update_octree_rigidbody_transform( RigidBody *rb, BoundingBox old_bb, BoundingBox new_bb );

#endif
