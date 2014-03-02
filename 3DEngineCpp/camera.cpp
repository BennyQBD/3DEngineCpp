#include "camera.h"
#include "input.h"
#include "time.h"
#include "util.h"

Camera::Camera(const Vector3f& pos, const Vector3f& forward, const Vector3f& up) :
	m_pos(pos),
	m_forward(forward),
	m_up(up) {}

#include "window.h"
bool mouseLocked = false;

void Camera::Input()
{
	float sensitivity = 0.5f;
	float movAmt = (float)(10 * Time::GetDelta());
	//float rotAmt = (float)(100 * Time::getDelta());

	if(Input::GetKey(KEY::KEY_ESCAPE))
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
			RotateY(ToRadian(deltaPos.GetX() * sensitivity));
		if(rotX)
			RotateX(ToRadian(deltaPos.GetY() * sensitivity));
			
		if(rotY || rotX)
			Input::SetMousePosition(centerPosition);
	}

	if(Input::GetMouseDown(MOUSE::LEFT_MOUSE))
	{
		Vector2f centerPosition = Vector2f((float)Window::GetWidth()/2.0f, (float)Window::GetHeight()/2.0f);
		Input::SetCursor(false);
		Input::SetMousePosition(centerPosition);
		mouseLocked = true;
	}

	if(Input::GetKey(KEY::KEY_W))
		Move(GetForward(), movAmt);
	if(Input::GetKey(KEY::KEY_S))
		Move(GetForward(), -movAmt);
	if(Input::GetKey(KEY::KEY_A))
		Move(GetLeft(), movAmt);
	if(Input::GetKey(KEY::KEY_D))
		Move(GetRight(), movAmt);
	

	//if(Input::getKey(KEY::KEY_UP))
	//	rotateX(-rotAmt);
	//if(Input::getKey(KEY::KEY_DOWN))
	//	rotateX(rotAmt);
	//if(Input::getKey(KEY::KEY_LEFT))
	//	rotateY(-rotAmt);
	//if(Input::getKey(KEY::KEY_RIGHT))
	//	rotateY(rotAmt);
}

void Camera::Move(const Vector3f& direction, float amt)
{
	m_pos += (direction * amt);
}

void Camera::RotateY(float angle)
{
//	Vector3f hAxis = Vector3f::UP.Cross(m_forward).Normalized();
	Vector3f hAxis = Vector3f(0,1,0).Cross(m_forward).Normalized();

//	m_forward = m_forward.Rotate(angle, Vector3f::UP).Normalized();
	m_forward = m_forward.Rotate(angle, Vector3f(0,1,0)).Normalized();
	m_up = m_forward.Cross(hAxis).Normalized();
}

void Camera::RotateX(float angle)
{
//	Vector3f hAxis = Vector3f::UP.Cross(m_forward).Normalized();
	Vector3f hAxis = Vector3f(0,1,0).Cross(m_forward).Normalized();

	m_forward = m_forward.Rotate(angle, hAxis).Normalized();
	m_up = m_forward.Cross(hAxis).Normalized();
}
