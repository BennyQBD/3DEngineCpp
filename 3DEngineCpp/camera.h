#ifndef CAMERA_H
#define CAMERA_H

#include "math3d.h"

class Camera
{
public:
	Camera(float fov, float aspect, float zNear, float zFar);

	void Input();
	void Move(const Vector3f& direction, float amt);
	void RotateY(float angle);
	void RotateX(float angle);
	
	Matrix4f GetViewProjection() const;
	
	inline Vector3f& GetPos() { return m_pos; }
	inline Vector3f& GetForward() { return m_forward; }
	inline Vector3f& GetUp() { return m_up; }

	inline Vector3f GetLeft() const { return m_forward.Cross(m_up).Normalized(); }
	inline Vector3f GetRight() const { return m_up.Cross(m_forward).Normalized(); }

	inline void SetPos(const Vector3f& pos) { m_pos = pos; }
	inline void SetForward(const Vector3f& forward) { m_forward = forward; }
	inline void SetUp(const Vector3f& up) { m_up = up; }
protected:
private:
	Vector3f m_pos;
	Vector3f m_forward;
	Vector3f m_up;
	Matrix4f m_projection;
};

#endif
