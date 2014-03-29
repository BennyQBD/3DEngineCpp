#include "camera.h"
#include "input.h"
#include "time.h"
#include "util.h"
#include "renderingEngine.h"

Camera::Camera(float fov, float aspect, float zNear, float zFar)
{
	m_projection.InitPerspective(fov, aspect, zNear, zFar);
}

Matrix4f Camera::GetViewProjection() const
{
	Matrix4f cameraRotation = GetTransform().GetTransformedRot().Conjugate().ToRotationMatrix();
	Matrix4f cameraTranslation;
	
	cameraTranslation.InitTranslation(GetTransform().GetTransformedPos() * -1);
	
	return m_projection * cameraRotation * cameraTranslation;
}

void Camera::AddToRenderingEngine(RenderingEngine* renderingEngine)
{
	renderingEngine->AddCamera(this);
}

#include "window.h"
bool mouseLocked = false;

void Camera::Input(float delta)
{
	float sensitivity = 0.5f;
	float movAmt = (float)(10 * delta);

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
			GetTransform().Rotate(Vector3f(0,1,0), ToRadians(deltaPos.GetX() * sensitivity));
		if(rotX)
			GetTransform().Rotate(GetTransform().GetRot().GetRight(), ToRadians(deltaPos.GetY() * sensitivity));
			
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
		Move(GetTransform().GetRot().GetForward(), movAmt);
	if(Input::GetKey(KEY::KEY_S))
		Move(GetTransform().GetRot().GetBack(), movAmt);
	if(Input::GetKey(KEY::KEY_A))
		Move(GetTransform().GetRot().GetLeft(), movAmt);
	if(Input::GetKey(KEY::KEY_D))
		Move(GetTransform().GetRot().GetRight(), movAmt);
}

void Camera::Move(const Vector3f& direction, float amt)
{
	GetTransform().SetPos(GetTransform().GetPos() + (direction * amt));
}
