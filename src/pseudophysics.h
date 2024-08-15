#ifndef __PSEUDPHYSICS_H__
#define __PSEUDPHYSICS_H__

#include "mutils.h"

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
	union {
		fvec3 size;
		float radius;
	};
};

typedef struct RigidBody {
	enum BODY_TYPE body_type;
	Transform transform;
	Collider collider;
} RigidBody;

void asciidng_physics_init();
void asciidng_physics_loop();
void asciidng_physics_terminate();

#endif
