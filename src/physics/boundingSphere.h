/*
 * @file
 * @author Benny Bobaganoosh <thebennybox@gmail.com>
 * @section LICENSE
 *
 * Copyright (C) 2014 Benny Bobaganoosh
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef BOUNDING_SPHERE_INCLUDED_H
#define BOUNDING_SPHERE_INCLUDED_H

#include "../core/math3d.h"
#include "intersectData.h"
#include "collider.h"

/**
 * The BoundingSphere class represents an sphere that can be used as a
 * collider in a physics engine.
 */
class BoundingSphere : public Collider
{
public:
	/** 
	 * Creates a BoundingSphere in a usable state.
	 * 
	 * @param center The center point of the sphere.
	 * @param radius The distance from any point on the sphere to the center.
	 */
	BoundingSphere(const Vector3f& center, float radius) :
		Collider(Collider::TYPE_SPHERE),
		m_center(center),
		m_radius(radius) {}

	/**
	 * Computes information about if this sphere intersects another aphere.
	 *
	 * @param other The sphere that's being tested for intersection with this
	 *                sphere.
	 */
	IntersectData IntersectBoundingSphere(const BoundingSphere& other) const;
	virtual void Transform(const Vector3f& translation);
	virtual Vector3f GetCenter() const { return m_center; }

	/** Basic getter for the radius */
	inline float GetRadius()           const { return m_radius; }

	/** Performs a Unit Test of this class */
	static void Test();
private:
	/** The center point of the sphere */
	Vector3f m_center;
	/** The distance from any point on the sphere to the center */
	float    m_radius;
};

#endif
