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

#ifndef AABB_INCLUDED_H
#define AABB_INCLUDED_H

#include "../core/math3d.h"
#include "intersectData.h"

/**
 * The AABB class represents an Axis Aligned Bounding Box that can be used as
 * a collider in a physics engine.
 */
class AABB
{
public:
	/** 
	 * Creates an AABB in a usable state.
	 * 
	 * @param minExtents The corner of the AABB with the smallest coordinates.
	 * @param maxExtents The corner of the AABB with the largest coordinates.
	 */
	AABB(const Vector3f& minExtents, const Vector3f& maxExtents) :
		m_minExtents(minExtents),
		m_maxExtents(maxExtents) {}
	
	/**
	 * Computes information about if this AABB intersects another AABB.
	 *
	 * @param other The AABB that's being tested for intersection with this
	 *                AABB.
	 */
	IntersectData IntersectAABB(const AABB& other) const;

	/** Basic getter for the min extents */
	inline const Vector3f& GetMinExtents() const { return m_minExtents; }
	/** Basic getter for the max extents */
	inline const Vector3f& GetMaxExtents() const { return m_maxExtents; }

	/** Performs a Unit test of this class */
	static void Test();
private:
	/** The corner of the AABB with the smallest coordinates */
	const Vector3f m_minExtents;
	/** The corner of the AABB with the largest coordinates */
	const Vector3f m_maxExtents;
};

#endif
