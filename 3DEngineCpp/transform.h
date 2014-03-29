#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "math3d.h"

class Transform
{
public:
	Transform(const Vector3f& pos = Vector3f(0,0,0), const Quaternion& rot = Quaternion(0,0,0,1), float scale = 1.0f);

	Matrix4f GetTransformation() const;

	inline Vector3f& GetPos() { return m_pos; }
	inline const Vector3f& GetPos() const { return m_pos; }
	inline Quaternion& GetRot() { return m_rot; }
	inline const Quaternion& GetRot() const { return m_rot; }
	inline float GetScale() const { return m_scale; }

	inline void SetPos(const Vector3f& pos) { m_pos = pos; }
	inline void SetRot(const Quaternion& rot) { m_rot = rot; }
	inline void SetScale(float scale) { m_scale = scale; }
protected:
private:
	Vector3f m_pos;
	Quaternion m_rot;
	float m_scale;
};

#endif
