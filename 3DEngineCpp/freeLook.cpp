#include "freeLook.h"
#include "window.h"

bool mouseLocked = false;

FreeLook::FreeLook(float sensitivity, int unlockMouseKey)
{
	m_sensitivity = sensitivity;
	m_unlockMouseKey = unlockMouseKey;
}

void FreeLook::Input(float delta)
{
	if(Input::GetKey(m_unlockMouseKey))
	{
		Input::SetCursor(true);
		mouseLocked = false;
	}

	if(mouseLocked)
	{
		Vector2f centerPosition = Vector2f((float)Window::GetWidth()/2.0f, (float)Window::GetHeight()/2.0f);
		Vector2f deltaPos = Input::GetMousePosition() - centerPosition;
		
		bool rotY = deltaPos.GetX() != 0;
		bool rotX = deltaPos.GetY() != 0;
			
		if(rotY)
			GetTransform().Rotate(Vector3f(0,1,0), ToRadians(deltaPos.GetX() * m_sensitivity));
		if(rotX)
			GetTransform().Rotate(GetTransform().GetRot().GetRight(), ToRadians(deltaPos.GetY() * m_sensitivity));
			
		if(rotY || rotX)
			Input::SetMousePosition(centerPosition);
	}

	if(Input::GetMouseDown(Input::LEFT_MOUSE))
	{
		Vector2f centerPosition = Vector2f((float)Window::GetWidth()/2.0f, (float)Window::GetHeight()/2.0f);
		Input::SetCursor(false);
		Input::SetMousePosition(centerPosition);
		mouseLocked = true;
	}
}
