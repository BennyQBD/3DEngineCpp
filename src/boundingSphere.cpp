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

#include "boundingSphere.h"

IntersectData BoundingSphere::IntersectBoundingSphere(const BoundingSphere& other) const
{
	//The radius is the distance from any point on the sphere to the center.
	//
	//Therefore, by adding the radius of two spheres together, the result is
	//the distance between the centers of the spheres when they are touching.
	float radiusDistance = m_radius + other.GetRadius();
	float centerDistance = (other.GetCenter() - m_center).Length();

	//Since the radiusDistance is the distance bwteen the centers of the 
	//spheres are when they're touching, you can subtract that from the
	//distance between the centers of the spheres to get the actual distance
	//between the two spheres.
	float distance = centerDistance - radiusDistance;

	//Spheres can only be intersecting if the distance between them is less
	//than 0.
	return IntersectData(distance < 0, distance);
}
