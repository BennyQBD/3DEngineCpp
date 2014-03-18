#ifndef GAMECOMPONENT_H_INCLUDED
#define GAMECOMPONENT_H_INCLUDED

#include "transform.h"
class RenderingEngine;
class Shader;

class GameComponent
{
public:
	virtual ~GameComponent() {}

	virtual void Input(const Transform& transform, float delta) {}
	virtual void Update(const Transform& transform, float delta) {}
	virtual void Render(const Transform& transform, Shader* shader, RenderingEngine* renderingEngine) {}
};

#endif // GAMECOMPONENT_H_INCLUDED
