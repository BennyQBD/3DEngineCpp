#include "transform.h"

//TODO: This will need to be changed later to avoid memory issues!
Camera* Transform::s_camera = new Camera();//&Camera();
float Transform::m_zFar = 0;
float Transform::m_zNear = 0;
float Transform::m_fov = 0;
float Transform::m_width = 0;
float Transform::m_height = 0;

Transform::Transform(Vector3f pos, Vector3f rot, float scale)
{
	m_pos = pos;
	m_rot = rot;
	m_scale = scale;
}

Matrix4f Transform::GetTransformation() const
{
	Matrix4f translationMatrix;
	Matrix4f rotationMatrix;
	Matrix4f scaleMatrix;

	translationMatrix.InitTranslationTransform(Vector3f(m_pos.GetX(), m_pos.GetY(), m_pos.GetZ()));
	rotationMatrix.InitRotateTransform(ToRadians(m_rot.GetX()), ToRadians(m_rot.GetY()), ToRadians(m_rot.GetZ()));
	scaleMatrix.InitScaleTransform(Vector3f(m_scale, m_scale, m_scale));

	Matrix4f result = translationMatrix * rotationMatrix * scaleMatrix;

	return result;
}

Matrix4f Transform::GetProjectedTransformation() const
{
	Matrix4f transformationMatrix = GetTransformation();
	Matrix4f projectionMatrix;
	Matrix4f cameraRotation;
	Matrix4f cameraTranslation;

	projectionMatrix.InitPersProjTransform(ToRadians(m_fov),(float)m_width/(float)m_height,m_zNear,m_zFar);
	cameraRotation.InitCameraTransform(s_camera->GetForward(),s_camera->GetUp());
	cameraTranslation.InitTranslationTransform(Vector3f(-s_camera->GetPos().GetX(), -s_camera->GetPos().GetY(), -s_camera->GetPos().GetZ()));

	Matrix4f result = projectionMatrix * cameraRotation * cameraTranslation * transformationMatrix;
	
	return result;
}

void Transform::SetProjection(float fov, float width, float height, float zNear, float zFar)
{
	Transform::m_fov = fov;
	Transform::m_width = width;
	Transform::m_height = height;
	Transform::m_zNear = zNear;
	Transform::m_zFar = zFar;
}
