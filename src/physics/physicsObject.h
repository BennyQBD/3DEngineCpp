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

#ifndef PHYSICS_OBJECT_INCLUDED_H
#define PHYSICS_OBJECT_INCLUDED_H

#include "../core/math3d.h"
#include "boundingSphere.h"

/**
 * The PhysicsObject class represents an object that can be used in a physics
 * engine. 
 */
class PhysicsObject
{
public:
	/** 
	 * Creates a PhysicsObject in a usable state.
	 * 
	 * @param position Where this object is in 3D space.
	 * @param velocity How fast this object is moving and in what direction.
	 * @param radius   The radius of the object; TODO: This is temporary!
	 */
	PhysicsObject(const Vector3f& position, const Vector3f& velocity, float radius) :
		m_position(position),
		m_velocity(velocity),
		m_radius(radius) {}
	
	/**
	 * Calculate this object's new location and properties after delta seconds
	 *
	 * @param delta How much time to simulate.
	 */
	void Integrate(float delta);

	/** Basic getter */
	inline const Vector3f& GetPosition() const { return m_position; }
	/** Basic getter */
	inline const Vector3f& GetVelocity() const { return m_velocity; }
	/** Basic getter */
	inline float GetRadius() const { return m_radius; }

	/** 
	 * Returns a bounding sphere around this object; 
	 * TODO: This is termporary! 
	 */
	inline BoundingSphere GetBoundingSphere() const
	{
		return BoundingSphere(m_position, m_radius);
	}

	/** Basic setter */
	inline void SetVelocity(const Vector3f& velocity) { m_velocity = velocity; }

	/** Performs a Unit Test of this class */
	static void Test();
private:
	/** Where this object is in 3D space. */
	Vector3f m_position;
	/** How fast this object is moving and in what direction */
	Vector3f m_velocity;
	/** The radius of this object; TODO: this is temporary! */
	float    m_radius;
};

#endif
