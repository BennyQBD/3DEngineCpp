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
#include <cassert>

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
	return IntersectData(distanceFromSphere < 0, m_normal * distanceFromSphere);
}

void Plane::Test()
{
	BoundingSphere sphere1(Vector3f(0.0f, 0.0f, 0.0f), 1.0f);
	BoundingSphere sphere2(Vector3f(0.0f, 3.0f, 0.0f), 1.0f);
	BoundingSphere sphere3(Vector3f(0.0f, 0.0f, 2.0f), 1.0f);
	BoundingSphere sphere4(Vector3f(1.0f, 0.0f, 0.0f), 1.0f);

	Plane plane1(Vector3f(0.0f, 1.0f, 0.0f), 0.0f);
	
	IntersectData plane1IntersectSphere1 = plane1.IntersectSphere(sphere1);
	IntersectData plane1IntersectSphere2 = plane1.IntersectSphere(sphere2);
	IntersectData plane1IntersectSphere3 = plane1.IntersectSphere(sphere3);
	IntersectData plane1IntersectSphere4 = plane1.IntersectSphere(sphere4);

	assert(plane1IntersectSphere1.GetDoesIntersect() == true);
	assert(plane1IntersectSphere1.GetDistance()      == 1.0f);

	assert(plane1IntersectSphere2.GetDoesIntersect() == false);
	assert(plane1IntersectSphere2.GetDistance()      == 2.0f);

	assert(plane1IntersectSphere3.GetDoesIntersect() == true);
	assert(plane1IntersectSphere3.GetDistance()      == 1.0f);
	
	assert(plane1IntersectSphere4.GetDoesIntersect() == true);
	assert(plane1IntersectSphere4.GetDistance()      == 1.0f);

//	std::cout << "Plane1 intersect Sphere1: " << plane1IntersectSphere1.GetDoesIntersect() 
//	          << ", Distance: "               << plane1IntersectSphere1.GetDistance() << std::endl;
//	
//	std::cout << "Plane1 intersect Sphere2: " << plane1IntersectSphere2.GetDoesIntersect() 
//	          << ", Distance: "               << plane1IntersectSphere2.GetDistance() << std::endl;
//	
//	std::cout << "Plane1 intersect Sphere3: " << plane1IntersectSphere3.GetDoesIntersect() 
//	          << ", Distance: "               << plane1IntersectSphere3.GetDistance() << std::endl;
//	
//	std::cout << "Plane1 intersect Sphere4: " << plane1IntersectSphere4.GetDoesIntersect() 
//	          << ", Distance: "               << plane1IntersectSphere4.GetDistance() << std::endl;
}
