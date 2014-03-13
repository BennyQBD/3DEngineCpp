#ifndef GAMECOMPONENT_H_INCLUDED
#define GAMECOMPONENT_H_INCLUDED

#include "transform.h"
#include "shader.h"

class GameComponent
{
public:
	virtual void Input(const Transform& transform) {}
	virtual void Update(const Transform& transform) {}
	virtual void Render(const Transform& transform, Shader* shader) {}
};

#endif // GAMECOMPONENT_H_INCLUDED
