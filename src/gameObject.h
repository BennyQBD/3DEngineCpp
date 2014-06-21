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

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include "transform.h"
#include "input.h"
class Camera;
class CoreEngine;
class GameComponent;
class Shader;
class RenderingEngine;

class GameObject
{
public:
	GameObject(const Vector3f& pos = Vector3f(0,0,0), const Quaternion& rot = Quaternion(0,0,0,1), float scale = 1.0f) : 
		m_transform(pos, rot, scale),
		m_coreEngine(0) {}
		
	virtual ~GameObject();
	
	GameObject* AddChild(GameObject* child);
	GameObject* AddComponent(GameComponent* component);
	
	void ProcessInputAll(const Input& input, float delta);
	void UpdateAll(float delta);
	void RenderAll(const Shader& shader, const RenderingEngine& renderingEngine, const Camera& camera) const;
	
	std::vector<GameObject*> GetAllAttached();
	
	inline Transform* GetTransform() { return &m_transform; }
	void SetEngine(CoreEngine* engine);
protected:
private:
	std::vector<GameObject*>    m_children;
	std::vector<GameComponent*> m_components;
	Transform                   m_transform;
	CoreEngine*                 m_coreEngine;

	void ProcessInput(const Input& input, float delta);
	void Update(float delta);
	void Render(const Shader& shader, const RenderingEngine& renderingEngine, const Camera& camera) const;
	
	GameObject(const GameObject& other) {}
	void operator=(const GameObject& other) {}
};

#endif // GAMEOBJECT_H
