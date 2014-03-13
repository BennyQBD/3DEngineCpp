#ifndef GAMECOMPONENT_H_INCLUDED
#define GAMECOMPONENT_H_INCLUDED

class GameComponent
{
public:
	virtual void Input(const Transform& transform) {}
	virtual void Update(const Transform& transform) {}
	virtual void Render(const Transform& transform) {}
};

#endif // GAMECOMPONENT_H_INCLUDED
