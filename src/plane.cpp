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

#include "plane.h"

Plane Plane::Normalized() const
{
	float magnitude = m_normal.Length();

	//Dividing the normal by it's length performs vector normalization.
	//Distance however, must also be divided by the normal's length in
	//order to create an equivalent plane.
	return Plane(m_normal/magnitude, m_distance/magnitude);
}

IntersectData Plane::IntersectSphere(const BoundingSphere& other) const
{
	//Calculating the dot product between the Plane's normal and the Sphere's 
	//center gets how far the sphere's center is along the Plane's normal.
	//
	//Adding the distance adjusts this value based on how far the Plane itself
	//is along the normal.
	//
	//The end result of this is how far the Sphere's center is from the Plane.
	//The absolute value is taken so that this result is always positive.
	float distanceFromSphereCenter = 
		(float)fabs(m_normal.Dot(other.GetCenter()) + m_distance);

	//As long as the distanceFromSphereCenter is valid and positive, then
	//the distance from the sphere can be calculated simply by subtracting
	//it's radius.
	float distanceFromSphere = distanceFromSphereCenter - other.GetRadius();

	//The only time the plane can be intersecting the sphere is if the sphere
	//has less than 0 distance from the plane. Otherwise, if there is distance
	//between the plane and sphere, then there must be a gap between the
	//plane and sphere, and they cannot be intersecting.
	return IntersectData(distanceFromSphere < 0, distanceFromSphere);
}
