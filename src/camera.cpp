#include "camera.h"
#include "renderingEngine.h"
#include "coreEngine.h"

Matrix4f Camera::GetViewProjection() const
{
	Matrix4f cameraRotation = GetTransform().GetTransformedRot().Conjugate().ToRotationMatrix();
	Matrix4f cameraTranslation;
	
	cameraTranslation.InitTranslation(GetTransform().GetTransformedPos() * -1);
	
	return m_projection * cameraRotation * cameraTranslation;
}

void CameraComponent::AddToEngine(CoreEngine* engine) const
{
	engine->SetCamera(m_camera);
}

void CameraComponent::SetParent(GameObject* parent)
{
	GameComponent::SetParent(parent);
	m_camera.SetTransform(GetTransform());
}
