#include "testing.h"

#include "physics/boundingSphere.h"
#include "physics/aabb.h"
#include "physics/plane.h"
#include "physics/physicsObject.h"

#include <iostream>
#include <cassert>

void Testing::RunAllTests()
{
	BoundingSphere::Test();
	AABB::Test();
	Plane::Test();
	PhysicsObject::Test();
}


