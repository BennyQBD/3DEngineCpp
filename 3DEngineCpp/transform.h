#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "math3d.h"
#include "camera.h"

class Transform
{
public:
	Transform(Vector3f pos = Vector3f(0,0,0), Vector3f rot = Vector3f(0,0,0), float scale = 1.0f);

	Matrix4f GetTransformation() const;

	inline Vector3f& GetPos() { return m_pos; }
	inline Vector3f& GetRot() { return m_rot; }
	inline float GetScale() const { return m_scale; }

	inline void SetPos(const Vector3f& pos) { m_pos = pos; }
	inline void SetRot(const Vector3f& rot) { m_rot = rot; }
	inline void SetScale(float scale) { m_scale = scale; }
protected:
private:
	Vector3f m_pos;
	Vector3f m_rot;
	float m_scale;
};

#endif
