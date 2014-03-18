#include "camera.h"
#include "input.h"
#include "time.h"
#include "util.h"

Camera::Camera(float fov, float aspect, float zNear, float zFar) :
	m_pos(Vector3f(0,0,0)),
	m_forward(Vector3f(0,0,1)),
	m_up(Vector3f(0,1,0)) 
{
	m_projection.InitPerspective(fov, aspect, zNear, zFar);
}

Matrix4f Camera::GetViewProjection() const
{
	Matrix4f cameraRotation;
	Matrix4f cameraTranslation;
	
	cameraRotation.InitRotationFromDirection(m_forward, m_up);
	cameraTranslation.InitTranslation(m_pos * -1);
	
	return m_projection * cameraRotation * cameraTranslation;
}

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
			RotateY(ToRadians(deltaPos.GetX() * sensitivity));
		if(rotX)
			RotateX(ToRadians(deltaPos.GetY() * sensitivity));
			
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
