/*
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
#include "aabb.h"
#include "plane.h"
#include <iostream>

int main()
{
	BoundingSphere sphere1(Vector3f(0.0f, 0.0f, 0.0f), 1.0f);
	BoundingSphere sphere2(Vector3f(0.0f, 3.0f, 0.0f), 1.0f);
	BoundingSphere sphere3(Vector3f(0.0f, 0.0f, 2.0f), 1.0f);
	BoundingSphere sphere4(Vector3f(1.0f, 0.0f, 0.0f), 1.0f);
	
	IntersectData sphere1IntersectSphere2 = sphere1.IntersectBoundingSphere(sphere2);
	IntersectData sphere1IntersectSphere3 = sphere1.IntersectBoundingSphere(sphere3);
	IntersectData sphere1IntersectSphere4 = sphere1.IntersectBoundingSphere(sphere4);
	
	std::cout << "Sphere1 intersect Sphere2: " << sphere1IntersectSphere2.GetDoesIntersect() 
	          << ", Distance: "                << sphere1IntersectSphere2.GetDistance() << std::endl;
	std::cout << "Sphere1 intersect Sphere3: " << sphere1IntersectSphere3.GetDoesIntersect() 
	          << ", Distance: "                << sphere1IntersectSphere3.GetDistance() << std::endl;
	std::cout << "Sphere1 intersect Sphere4: " << sphere1IntersectSphere4.GetDoesIntersect() 
	          << ", Distance: "                << sphere1IntersectSphere4.GetDistance() << std::endl;

	std::cout << std::endl;

	AABB aabb1(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f));
	AABB aabb2(Vector3f(1.0f, 1.0f, 1.0f), Vector3f(2.0f, 2.0f, 2.0f));
	AABB aabb3(Vector3f(1.0f, 0.0f, 0.0f), Vector3f(2.0f, 1.0f, 1.0f));
	AABB aabb4(Vector3f(0.0f, 0.0f, -2.0f), Vector3f(1.0f, 1.0f, -1.0f));
	AABB aabb5(Vector3f(0.0f, 0.5f, 0.0f), Vector3f(1.0f, 1.5f, 1.0f));

	IntersectData aabb1Intersectaabb2 = aabb1.IntersectAABB(aabb2);
	IntersectData aabb1Intersectaabb3 = aabb1.IntersectAABB(aabb3);
	IntersectData aabb1Intersectaabb4 = aabb1.IntersectAABB(aabb4);
	IntersectData aabb1Intersectaabb5 = aabb1.IntersectAABB(aabb5);

	std::cout << "AABB1 intersect AABB2: " << aabb1Intersectaabb2.GetDoesIntersect() 
	          << ", Distance: "            << aabb1Intersectaabb2.GetDistance() << std::endl;

	std::cout << "AABB1 intersect AABB3: " << aabb1Intersectaabb3.GetDoesIntersect() 
	          << ", Distance: "            << aabb1Intersectaabb3.GetDistance() << std::endl;

	std::cout << "AABB1 intersect AABB4: " << aabb1Intersectaabb4.GetDoesIntersect() 
	          << ", Distance: "            << aabb1Intersectaabb4.GetDistance() << std::endl;

	std::cout << "AABB1 intersect AABB5: " << aabb1Intersectaabb5.GetDoesIntersect() 
	          << ", Distance: "            << aabb1Intersectaabb5.GetDistance() << std::endl;


	std::cout << std::endl;

	Plane plane1(Vector3f(0.0f, 1.0f, 0.0f), 0.0f);
	
	IntersectData plane1IntersectSphere1 = plane1.IntersectSphere(sphere1);
	IntersectData plane1IntersectSphere2 = plane1.IntersectSphere(sphere2);
	IntersectData plane1IntersectSphere3 = plane1.IntersectSphere(sphere3);
	IntersectData plane1IntersectSphere4 = plane1.IntersectSphere(sphere4);

	std::cout << "Plane1 intersect Sphere1: " << plane1IntersectSphere1.GetDoesIntersect() 
	          << ", Distance: "               << plane1IntersectSphere1.GetDistance() << std::endl;
	
	std::cout << "Plane1 intersect Sphere2: " << plane1IntersectSphere2.GetDoesIntersect() 
	          << ", Distance: "               << plane1IntersectSphere2.GetDistance() << std::endl;
	
	std::cout << "Plane1 intersect Sphere3: " << plane1IntersectSphere3.GetDoesIntersect() 
	          << ", Distance: "               << plane1IntersectSphere3.GetDistance() << std::endl;
	
	std::cout << "Plane1 intersect Sphere4: " << plane1IntersectSphere4.GetDoesIntersect() 
	          << ", Distance: "               << plane1IntersectSphere4.GetDistance() << std::endl;
	
	return 0;
}
