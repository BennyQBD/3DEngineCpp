#ifndef FREELOOK_H
#define FREELOOK_H

#include "math3d.h"
#include "gameComponent.h"
#include "input.h"

class FreeLook : public GameComponent
{
public:
	FreeLook(float sensitivity = 0.5f, int unlockMouseKey = Input::KEY_ESCAPE);
	
	virtual void Input(float delta);
protected:
private:
	float m_sensitivity;
	int m_unlockMouseKey;
};

#endif // FREELOOK_H
