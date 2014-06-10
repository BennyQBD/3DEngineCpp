#include "transform.h"

bool Transform::HasChanged()
{	
	if(m_parent != 0 && m_parent->HasChanged())
	{
		return true;
	}
	
	if(m_pos != m_oldPos)
	{
		return true;
	}

	if(m_rot != m_oldRot)
	{
		return true;
	}
	
	if(m_scale != m_scale)
	{
		return true;
	}
		
	return false;
}

void Transform::Update()
{
	if(m_initializedOldStuff)
	{
		m_oldPos = m_pos;
		m_oldRot = m_rot;
		m_oldScale = m_scale;
	}
	else
	{
		m_oldPos = m_pos + Vector3f(1,1,1);
		m_oldRot = m_rot * 0.5f;
		m_oldScale = m_scale + 1;
		m_initializedOldStuff = true;
	}
}

void Transform::Rotate(const Vector3f& axis, float angle)
{
	Rotate(Quaternion(axis, angle));
}

void Transform::Rotate(const Quaternion& rotation)
{
	m_rot = Quaternion((rotation * m_rot).Normalized());
}

void Transform::LookAt(const Vector3f& point, const Vector3f& up)
{
	m_rot = GetLookAtRotation(point, up);
}

Matrix4f Transform::GetTransformation() const
{
	Matrix4f translationMatrix;
	Matrix4f scaleMatrix;

	translationMatrix.InitTranslation(Vector3f(m_pos.GetX(), m_pos.GetY(), m_pos.GetZ()));
	scaleMatrix.InitScale(Vector3f(m_scale, m_scale, m_scale));

	Matrix4f result = translationMatrix * m_rot.ToRotationMatrix() * scaleMatrix;

	return GetParentMatrix() * result;
}

const Matrix4f& Transform::GetParentMatrix() const
{
	if(m_parent != 0 && m_parent->HasChanged())
	{
		m_parentMatrix = m_parent->GetTransformation();
	}
		
	return m_parentMatrix;
}

Quaternion Transform::GetTransformedRot() const
{
	Quaternion parentRot = Quaternion(0,0,0,1);
	
	if(m_parent)
	{
		parentRot = m_parent->GetTransformedRot();
	}
	
	return parentRot * m_rot;
}
