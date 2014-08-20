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
#include <cassert>

IntersectData BoundingSphere::IntersectBoundingSphere(const BoundingSphere& other) const
{
	//The radius is the distance from any point on the sphere to the center.
	//
	//Therefore, by adding the radius of two spheres together, the result is
	//the distance between the centers of the spheres when they are touching.
	float radiusDistance = m_radius + other.GetRadius();
	Vector3f direction = (other.GetCenter() - m_center);
	float centerDistance = direction.Length();
	direction /= centerDistance;

	//Since the radiusDistance is the distance bwteen the centers of the 
	//spheres are when they're touching, you can subtract that from the
	//distance between the centers of the spheres to get the actual distance
	//between the two spheres.
	float distance = centerDistance - radiusDistance;

	//Spheres can only be intersecting if the distance between them is less
	//than 0.
	return IntersectData(distance < 0, direction * distance);
}

void BoundingSphere::Transform(const Vector3f& translation)
{
	m_center += translation;
}

void BoundingSphere::Test()
{
	BoundingSphere sphere1(Vector3f(0.0f, 0.0f, 0.0f), 1.0f);
	BoundingSphere sphere2(Vector3f(0.0f, 3.0f, 0.0f), 1.0f);
	BoundingSphere sphere3(Vector3f(0.0f, 0.0f, 2.0f), 1.0f);
	BoundingSphere sphere4(Vector3f(1.0f, 0.0f, 0.0f), 1.0f);
	
	IntersectData sphere1IntersectSphere2 = sphere1.IntersectBoundingSphere(sphere2);
	IntersectData sphere1IntersectSphere3 = sphere1.IntersectBoundingSphere(sphere3);
	IntersectData sphere1IntersectSphere4 = sphere1.IntersectBoundingSphere(sphere4);
	
	assert(sphere1IntersectSphere2.GetDoesIntersect() == false);
	assert(sphere1IntersectSphere2.GetDistance()      == 1.0f);

	assert(sphere1IntersectSphere3.GetDoesIntersect() == false);
	assert(sphere1IntersectSphere3.GetDistance()      == 0.0f);

	assert(sphere1IntersectSphere4.GetDoesIntersect() == true);
	assert(sphere1IntersectSphere4.GetDistance()      == 1.0f);

//	std::cout << "Sphere1 intersect Sphere2: " << sphere1IntersectSphere2.GetDoesIntersect() 
//	          << ", Distance: "                << sphere1IntersectSphere2.GetDistance() << std::endl;
//	std::cout << "Sphere1 intersect Sphere3: " << sphere1IntersectSphere3.GetDoesIntersect() 
//	          << ", Distance: "                << sphere1IntersectSphere3.GetDistance() << std::endl;
//	std::cout << "Sphere1 intersect Sphere4: " << sphere1IntersectSphere4.GetDoesIntersect() 
//	          << ", Distance: "                << sphere1IntersectSphere4.GetDistance() << std::endl;
}
