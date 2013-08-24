#include "camera.h"
#include "input.h"
#include "time.h"

Camera::Camera(Vector3f pos, Vector3f forward, Vector3f up)
{
	m_pos = pos;
	m_forward = forward;
	m_up = up;
}

Camera::~Camera()
{

}

#include "window.h"

bool mouseLocked = false;

void Camera::input()
{
	float sensitivity = 0.5f;
	float movAmt = (float)(10 * Time::getDelta());
	float rotAmt = (float)(100 * Time::getDelta());

	if(Input::getKey(KEY::KEY_ESCAPE))
	{
		Input::setCursor(true);
		mouseLocked = false;
	}

	if(mouseLocked)
	{
		Vector2f centerPosition = Vector2f((float)Window::getWidth()/2.0f, (float)Window::getHeight()/2.0f);
		Vector2f deltaPos = Input::getMousePosition() - centerPosition;
		
		bool rotY = deltaPos.x != 0;
		bool rotX = deltaPos.y != 0;
			
		if(rotY)
			rotateY(deltaPos.x * sensitivity);
		if(rotX)
			rotateX(deltaPos.y * sensitivity);
			
		if(rotY || rotX)
			Input::setMousePosition(centerPosition);
	}

	if(Input::getMouseDown(MOUSE::LEFT_MOUSE))
	{
		Vector2f centerPosition = Vector2f((float)Window::getWidth()/2.0f, (float)Window::getHeight()/2.0f);
		Input::setMousePosition(centerPosition);
		Input::setCursor(false);
		mouseLocked = true;
	}

	if(Input::getKey(KEY::KEY_W))
		move(getForward(), movAmt);
	if(Input::getKey(KEY::KEY_S))
		move(getForward(), -movAmt);
	if(Input::getKey(KEY::KEY_A))
		move(getLeft(), movAmt);
	if(Input::getKey(KEY::KEY_D))
		move(getRight(), movAmt);
	

	//if(Input::getKey(KEY::KEY_UP))
	//	rotateX(-rotAmt);
	//if(Input::getKey(KEY::KEY_DOWN))
	//	rotateX(rotAmt);
	//if(Input::getKey(KEY::KEY_LEFT))
	//	rotateY(-rotAmt);
	//if(Input::getKey(KEY::KEY_RIGHT))
	//	rotateY(rotAmt);
}

void Camera::move(const Vector3f& direction, float amt)
{
	m_pos += (direction * amt);
}

void Camera::rotateY(float angle)
{
	Vector3f hAxis = Vector3f::UP.cross(m_forward).normalize();

	m_forward = m_forward.rotate(angle, Vector3f::UP).normalize();
	m_up = m_forward.cross(hAxis).normalize();
}

void Camera::rotateX(float angle)
{
	Vector3f hAxis = Vector3f::UP.cross(m_forward).normalize();

	m_forward = m_forward.rotate(angle, hAxis).normalize();
	m_up = m_forward.cross(hAxis).normalize();
}

Vector3f& Camera::getPos()
{
	return m_pos;
}

Vector3f& Camera::getForward()
{
	return m_forward;
}

Vector3f& Camera::getUp()
{
	return m_up;
}

Vector3f Camera::getLeft() const
{
	return m_forward.cross(m_up).normalize();
}

Vector3f Camera::getRight() const
{
	return m_up.cross(m_forward).normalize();
}

void Camera::setPos(const Vector3f& pos)
{
	m_pos = pos;
}

void Camera::setForward(const Vector3f& forward)
{
	m_forward = forward;
}

void Camera::setUp(const Vector3f& up)
{
	m_up = up;
}