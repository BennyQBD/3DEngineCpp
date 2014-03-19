#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include "transform.h"
class GameComponent;
class Shader;
class RenderingEngine;

class GameObject
{
public:
	GameObject() {}
	virtual ~GameObject();
	
	GameObject* AddChild(GameObject* child);
	GameObject* AddComponent(GameComponent* component);
	
	void Input(float delta);
	void Update(float delta);
	void Render(Shader* shader, RenderingEngine* renderingEngine);
	void AddToRenderingEngine(RenderingEngine* renderingEngine);
	
	inline Transform& GetTransform() { return m_transform; }
protected:
private:
	std::vector<GameObject*> m_children;
	std::vector<GameComponent*> m_components;
	Transform m_transform;
};

#endif // GAMEOBJECT_H
