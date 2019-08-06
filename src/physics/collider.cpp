#include "collider.h"
#include "boundingSphere.h"
#include <iostream>
#include <cstdlib>

IntersectData Collider::Intersect(const Collider& other) const
{
	if(m_type == TYPE_SPHERE && other.GetType() == TYPE_SPHERE)
	{
		BoundingSphere* self = std::dynamic_pointer_cast<BoundingSphere>(*this);
		return self->IntersectBoundingSphere(std::dynamic_pointer_cast<BoundingSphere&>(other));
	}

	std::cerr << "Error: Collisions not implemented between specified "
	          << "colliders." << std::endl;
	exit(1);
	
	//Control should never reach this point
	return IntersectData(false, 0);
}

