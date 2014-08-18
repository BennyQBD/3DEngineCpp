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

#ifndef COLLIDER_INCLUDED_H
#define COLLIDER_INCLUDED_H

#include "intersectData.h"
#include "../core/math3d.h"
#include "../core/referenceCounter.h"

/**
 * The Collider class is the base class for colliders that can be used in the
 * physics engine. More specific colliders should inherit from this class
 */
class Collider : public ReferenceCounter
{
public:
	/**
	 * This enumeration stores all the types of colliders that can be used.
	 */
	enum
	{
		TYPE_SPHERE,
		TYPE_AABB,

		TYPE_SIZE
	};

	/**
	 * Creates a Collider in a usable state.
	 *
	 * @param type The type of collider this represents.
	 */
	Collider(int type) :
		ReferenceCounter(),
		m_type(type) {}
	
	/**
	 * Calculates information about if this collider is intersecting with 
	 * another collider.
	 *
	 * @param other The collider that is being checked for intersection.
	 */
	IntersectData Intersect(const Collider& other) const;

	/**
	 * Moves the entire collider by translation distance. Should be overriden
	 * by subclasses.
	 *
	 * @param translation Distance to move the collider
	 */
	virtual void Transform(const Vector3f& translation) {}
	/**
	 * Returns the center position of the collider. Should be overriden by
	 * subclasses.
	 */
	virtual Vector3f GetCenter() const { return Vector3f(0,0,0); }

	/** Basic getter */
	inline int GetType() const { return m_type; }
private:
	/**
	 * What type of collider this is. Should be set to some value from the 
	 * TYPE enum. This value determines what sort of intersect checks are used
	 * and other details about the collider; should only be set by an appropriate
	 * subclass or strange behaviour may result!
	 */
	int m_type;
};

#endif
