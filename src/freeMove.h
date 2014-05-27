#ifndef FREEMOVE_H
#define FREEMOVE_H

#include "math3d.h"
#include "gameComponent.h"
#include "input.h"

class FreeMove : public GameComponent
{
public:
	FreeMove(float speed = 10.0f, int forwardKey = Input::KEY_W, int backKey = Input::KEY_S, int leftKey = Input::KEY_A, int rightKey = Input::KEY_D);
	
	virtual void Input(float delta);
protected:
private:
	void Move(const Vector3f& direction, float amt);

	float m_speed;
	int m_forwardKey;
	int m_backKey;
	int m_leftKey;
	int m_rightKey;
};

#endif // FREEMOVE_H
