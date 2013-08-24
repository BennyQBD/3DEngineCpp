#include "transform.h"


Camera* Transform::m_camera = &Camera();
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

Matrix4f Transform::getTransformation()
{
	Matrix4f translationMatrix;
	Matrix4f rotationMatrix;
	Matrix4f scaleMatrix;

	translationMatrix.initTranslationTransform(m_pos.x, m_pos.y, m_pos.z);
	rotationMatrix.initRotateTransform(m_rot.x, m_rot.y, m_rot.z);
	scaleMatrix.initScaleTransform(m_scale.x, m_scale.y, m_scale.z);

	return translationMatrix * rotationMatrix * scaleMatrix;
}

Matrix4f Transform::getProjectedTransformation()
{
	Matrix4f transformationMatrix = getTransformation();
	Matrix4f projectionMatrix;
	Matrix4f cameraRotation;
	Matrix4f cameraTranslation;

	projectionMatrix.initPersProjTransform(m_fov,m_width,m_height,m_zNear,m_zFar);
	cameraRotation.initCameraTransform(m_camera->getForward(),m_camera->getUp());
	cameraTranslation.initTranslationTransform(-m_camera->getPos().x, -m_camera->getPos().y, -m_camera->getPos().z);

	return projectionMatrix * cameraRotation * cameraTranslation * transformationMatrix;
}

Vector3f& Transform::getPos()
{
	return m_pos;
}

Vector3f& Transform::getRot()
{
	return m_rot;
}

Vector3f& Transform::getScale()
{
	return m_scale;
}

void Transform::setPos(const Vector3f& pos)
{
	this->m_pos = pos;
}

void Transform::setRot(const Vector3f& rot)
{
	this->m_rot = rot;
}

void Transform::setScale(const Vector3f& scale)
{
	this->m_scale = scale;
}

void Transform::setProjection(float fov, float width, float height, float zNear, float zFar)
{
	Transform::m_fov = fov;
	Transform::m_width = width;
	Transform::m_height = height;
	Transform::m_zNear = zNear;
	Transform::m_zFar = zFar;
}

Camera& Transform::getCamera()
{
	return *m_camera;
}

void Transform::setCamera(Camera& camera)
{
	Transform::m_camera = &camera;
}