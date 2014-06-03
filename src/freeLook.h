#ifndef FREELOOK_H
#define FREELOOK_H

#include "math3d.h"
#include "gameComponent.h"

class FreeLook : public GameComponent
{
public:
	FreeLook(const Vector2f& windowCenter, float sensitivity = 0.5f, int unlockMouseKey = Input::KEY_ESCAPE) :
		m_sensitivity(sensitivity),
		m_unlockMouseKey(unlockMouseKey),
		m_mouseLocked(false),
		m_windowCenter(windowCenter) {}
	
	virtual void ProcessInput(const Input& input, float delta);
protected:
private:
	float    m_sensitivity;
	int      m_unlockMouseKey;
	bool     m_mouseLocked;
	Vector2f m_windowCenter;
};

#endif // FREELOOK_H
