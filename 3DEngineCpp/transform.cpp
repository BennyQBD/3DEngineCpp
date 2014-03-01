#include "transform.h"


//TODO: This will need to be changed later to avoid memory issues!
Camera* Transform::s_camera = new Camera();//&Camera();
float Transform::m_zFar = 0;
float Transform::m_zNear = 0;
float Transform::m_fov = 0;
float Transform::m_width = 0;
float Transform::m_height = 0;

Transform::Transform(Vector3f pos, Vector3f rot, Vector3f scale)
{
	m_pos = pos;
	m_rot = rot;
	m_scale = scale;
}

Transform::~Transform()
{

}

Matrix4f Transform::GetTransformation()
{
	Matrix4f translationMatrix;
	Matrix4f rotationMatrix;
	Matrix4f scaleMatrix;

	translationMatrix.InitTranslationTransform(m_pos.GetX(), m_pos.GetY(), m_pos.GetZ());
	rotationMatrix.InitRotateTransform(m_rot.GetX(), m_rot.GetY(), m_rot.GetZ());
	scaleMatrix.InitScaleTransform(m_scale.GetX(), m_scale.GetY(), m_scale.GetZ());

	return translationMatrix * rotationMatrix * scaleMatrix;
}

Matrix4f Transform::GetProjectedTransformation()
{
	Matrix4f transformationMatrix = GetTransformation();
	Matrix4f projectionMatrix;
	Matrix4f cameraRotation;
	Matrix4f cameraTranslation;

	projectionMatrix.InitPersProjTransform(m_fov,m_width,m_height,m_zNear,m_zFar);
	cameraRotation.InitCameraTransform(s_camera->GetForward(),s_camera->GetUp());
	cameraTranslation.InitTranslationTransform(-s_camera->GetPos().GetX(), -s_camera->GetPos().GetY(), -s_camera->GetPos().GetZ());

	return projectionMatrix * cameraRotation * cameraTranslation * transformationMatrix;
}

void Transform::SetProjection(float fov, float width, float height, float zNear, float zFar)
{
	Transform::m_fov = fov;
	Transform::m_width = width;
	Transform::m_height = height;
	Transform::m_zNear = zNear;
	Transform::m_zFar = zFar;
}
