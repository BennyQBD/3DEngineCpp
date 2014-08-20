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

#ifndef INTERSECT_DATA_INCLUDED_H
#define INTERSECT_DATA_INCLUDED_H

#include "../core/math3d.h"

/**
 * The IntersectData class stores information about two intersecting objects.
 */
class IntersectData
{
public:
	/** 
	 * Creates Intersect Data in a usable state.
	 * 
	 * @param doesIntersect Whether or not the objects are intersecting.
	 * @param direction     The collision normal, with length set to distance.
	 */
	IntersectData(const bool doesIntersect, const Vector3f& direction) :
		m_doesIntersect(doesIntersect),
		m_direction(direction) {}

	/** Basic getter for m_doesIntersect */
	inline bool GetDoesIntersect() const { return m_doesIntersect; }
	/** Basic getter for m_distance */
	inline float GetDistance()     const { return m_direction.Length(); }
	/** Basic getter */
	inline const Vector3f& GetDirection() const { return m_direction; }
private:
	/** Whether or not the objects are intersecting */
	const bool  m_doesIntersect;
	/** The collision normal, with length set to distance. */
	const Vector3f m_direction;
};

#endif
