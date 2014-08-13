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
#ifndef PHYSICS_ENGINE_INCLUDED_H
#define PHYSICS_ENGINE_INCLUDED_H

#include "physicsObject.h"
#include <vector>

/**
 * The PhysicsEngine encapsulates all the functions and information necessary
 * to perform a physics simulation.
 */
class PhysicsEngine
{
public:
	/** 
	 * Creates a PhysicsEngine in a usable state.
	 */
	PhysicsEngine() {}

	void AddObject(const PhysicsObject& object);
	
	/**
	 * Simulates the physics world for a certain period of time. Does not take
	 * object interaction into accounter; if two objects run into each other,
	 * they will pass through each other.
	 *
	 * If object interaction is desired, collision detection and response must
	 * be performed after this.
	 *
	 * @param delta How much time to simulate.
	 */
	void Simulate(float delta);

	/** 
	 * Finds all objects that have collided since the last step and updates
	 * them to adjust for the collision.
	 */
	void HandleCollisions();

	//TODO: Temporary Getters
	inline const PhysicsObject& GetObject(unsigned int index) const 
	{ 
		return m_objects[index]; 
	}
	inline unsigned int GetNumObjects() const 
	{ 
		return (unsigned int)m_objects.size();
	}
private:
	/** All the objects being simulated by the PhysicsEngine. */
	std::vector<PhysicsObject> m_objects;
};

#endif
