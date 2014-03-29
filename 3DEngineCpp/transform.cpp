#include "transform.h"

Transform::Transform(const Vector3f& pos, const Quaternion& rot, float scale)
{
	m_pos = pos;
	m_rot = rot;
	m_scale = scale;
	m_initializedOldStuff = false;
	m_parent = 0;
	
	m_parentMatrix = Matrix4f().InitIdentity();
}

bool Transform::HasChanged()
{
	if(!m_initializedOldStuff)
	{
		m_oldPos = m_pos;
		m_oldRot = m_rot;
		m_oldScale = m_scale;
		m_initializedOldStuff = true;
		return true;
	}
	
	if(m_parent != 0 && m_parent->HasChanged())
		return true;
	
	if(m_pos != m_oldPos)
		return true;

	if(m_rot != m_oldRot)
		return true;
	
	if(m_scale != m_scale)
		return true;
		
	return false;
}

Matrix4f Transform::GetTransformation() const
{
	Matrix4f translationMatrix;
	Matrix4f scaleMatrix;

	translationMatrix.InitTranslation(Vector3f(m_pos.GetX(), m_pos.GetY(), m_pos.GetZ()));
	scaleMatrix.InitScale(Vector3f(m_scale, m_scale, m_scale));

	Matrix4f result = translationMatrix * m_rot.ToRotationMatrix() * scaleMatrix;

	if(m_initializedOldStuff)
	{
		m_oldPos = m_pos;
		m_oldRot = m_rot;
		m_oldScale = m_scale;
	}

	return GetParentMatrix() * result;
}

Matrix4f Transform::GetParentMatrix() const
{
	if(m_parent != 0 && m_parent->HasChanged())
		m_parentMatrix = m_parent->GetTransformation();
		
	return m_parentMatrix;
}
