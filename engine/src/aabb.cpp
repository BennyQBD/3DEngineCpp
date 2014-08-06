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

#include "aabb.h"

IntersectData AABB::IntersectAABB(const AABB& other) const
{
	//The distance between the AABB's on the X, Y, and Z axis.
	//Computed twice because there are two possible valid distances, depending
	//on the location of the AABB's.
	Vector3f distances1 = other.GetMinExtents() - m_maxExtents;
	Vector3f distances2 = m_minExtents - other.GetMaxExtents();

	//The correct distances will be whichever distance is larger for that
	//particular axis.
	Vector3f distances = Vector3f(distances1.Max(distances2));

	float maxDistance = distances.Max();
	
	//If there is any distance between the two AABB's, then max distance will
	//be greather than or equal to 0. If there is distance between the two
	//AABBs, then they aren't intersecting.
	//
	//Therefore, if the AABBs are intersecting, then the distance between them
	//must be less than zero.
	return IntersectData(maxDistance < 0, maxDistance);
}
