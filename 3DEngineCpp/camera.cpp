#include "camera.h"
#include "renderingEngine.h"
#include "coreEngine.h"

Camera::Camera(const Matrix4f& projection) :
	m_projection(projection) {}

Matrix4f Camera::GetViewProjection() const
{
	Matrix4f cameraRotation = GetTransform().GetTransformedRot().Conjugate().ToRotationMatrix();
	Matrix4f cameraTranslation;
	
	cameraTranslation.InitTranslation(GetTransform().GetTransformedPos() * -1);
	
	return m_projection * cameraRotation * cameraTranslation;
}

void Camera::AddToEngine(CoreEngine* engine)
{
	engine->GetRenderingEngine()->AddCamera(this);
}
