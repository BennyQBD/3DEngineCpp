#include "boundingSphere.h"

IntersectData BoundingSphere::IntersectBoundingSphere(const BoundingSphere& other)
{
	float radiusDistance = m_radius + other.GetRadius();
	float centerDistance = (other.GetCenter() - m_center).Length();
	float distance = centerDistance - radiusDistance;

	return IntersectData(centerDistance < radiusDistance, distance);
}
