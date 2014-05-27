#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include "transform.h"
class CoreEngine;
class GameComponent;
class Shader;
class RenderingEngine;

class GameObject
{
public:
	GameObject() { m_coreEngine = 0; }
	virtual ~GameObject();
	
	GameObject* AddChild(GameObject* child);
	GameObject* AddComponent(GameComponent* component);
	
	void InputAll(float delta);
	void UpdateAll(float delta);
	void RenderAll(Shader* shader, RenderingEngine* renderingEngine);
	
	std::vector<GameObject*> GetAllAttached();
	
	inline Transform& GetTransform() { return m_transform; }
	void SetEngine(CoreEngine* engine);
protected:
private:
	void Input(float delta);
	void Update(float delta);
	void Render(Shader* shader, RenderingEngine* renderingEngine);

	std::vector<GameObject*> m_children;
	std::vector<GameComponent*> m_components;
	Transform m_transform;
	CoreEngine* m_coreEngine;
};

#endif // GAMEOBJECT_H
