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
#include "physicsEngine.h"
#include "boundingSphere.h"

void PhysicsEngine::AddObject(const PhysicsObject& object)
{
	m_objects.push_back(object);
}

void PhysicsEngine::Simulate(float delta)
{
	for(unsigned int i = 0; i < m_objects.size(); i++)
	{
		m_objects[i].Integrate(delta);
	}
}

void PhysicsEngine::HandleCollisions()
{
	for(unsigned int i = 0; i < m_objects.size(); i++)
	{
		for(unsigned int j = i + 1; j < m_objects.size(); j++)
		{
			IntersectData intersectData = 
				m_objects[i].GetCollider().Intersect(
					m_objects[j].GetCollider());

			if(intersectData.GetDoesIntersect())
			{
				Vector3f direction = intersectData.GetDirection().Normalized();
				Vector3f otherDirection = Vector3f(direction.Reflect(m_objects[i].GetVelocity().Normalized()));
				m_objects[i].SetVelocity(
						Vector3f(m_objects[i].GetVelocity().Reflect(otherDirection)));

				m_objects[j].SetVelocity(
						Vector3f(m_objects[j].GetVelocity().Reflect(direction)));
			}
		}
	}
}
