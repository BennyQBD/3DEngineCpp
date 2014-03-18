#include "transform.h"

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

	translationMatrix.InitTranslation(Vector3f(m_pos.GetX(), m_pos.GetY(), m_pos.GetZ()));
	rotationMatrix.InitRotationEuler(ToRadians(m_rot.GetX()), ToRadians(m_rot.GetY()), ToRadians(m_rot.GetZ()));
	scaleMatrix.InitScale(Vector3f(m_scale, m_scale, m_scale));

	Matrix4f result = translationMatrix * rotationMatrix * scaleMatrix;

	return result;
}
