#ifndef __PSEUDPHYSICS_H__
#define __PSEUDPHYSICS_H__

#include "mutils.h"

struct Node;
typedef struct Node Node;

typedef struct Transform {
	fvec3 position, rotation, velocity;
} Transform;

enum BODY_TYPE {
	STATIC_BODY,
	DYNAMIC_BODY
};

enum COLLIDER_TYPE {
	PARALLELEPIPED_COLLIDER,
	SPHERE_COLLIDER
};

typedef struct Collider {
	enum COLLIDER_TYPE collider_type;
	fvec3 local_position, local_rotation;
	union {
		fvec3 size;
		float radius;
	};
} Collider;

typedef struct BoundingBox {
	fvec3 min, max;
} BoundingBox;

typedef struct RigidBody {
	enum BODY_TYPE body_type;
	Transform transform;
	Collider collider;
	BoundingBox bounding_box;
	Node *node_cache;
} RigidBody;

typedef struct Ray {
	fvec3 vertex, direction;
	float length;
} Ray;

typedef struct RaycastResult {
	Ray ray;
	RigidBody *collided_object;
	fvec3 collision_point;	
} RaycastResult;

RaycastResult asciidng_cast_ray( Ray ray );

void asciidng_generate_parallelepiped_vertices( fvec3 size, fvec3 *vertices );
void asciidng_generate_parallelepiped_collider_vertices( Collider collider, fvec3 *vertices );
BoundingBox asciidng_generate_bounding_box( RigidBody *rigid_body );
void asciidng_update_rigid_body_bounding_box( RigidBody *rigid_body );

void asciidng_init_physics();
void asciidng_loop_physics();
void asciidng_terminate_physics();

#endif
