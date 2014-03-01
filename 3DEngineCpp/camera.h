#ifndef CAMERA_H
#define CAMERA_H

#include "vector3f.h"

class Camera
{
public:
	Camera(const Vector3f& pos = Vector3f(0,0,0), const Vector3f& forward = Vector3f(0,0,1), const Vector3f& up = Vector3f(0,1,0));

	void Input();
	void Move(const Vector3f& direction, float amt);
	void RotateY(float angle);
	void RotateX(float angle);

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
};

#endif
