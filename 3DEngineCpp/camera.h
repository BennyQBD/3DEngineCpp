#ifndef CAMERA_H
#define CAMERA_H

#include "vector3f.h"

class Camera
{
public:
	Camera(Vector3f pos = Vector3f(0,0,0), Vector3f forward = Vector3f(0,0,1), Vector3f up = Vector3f(0,1,0));
	~Camera();

	void input();
	void move(const Vector3f& direction, float amt);
	void rotateY(float angle);
	void rotateX(float angle);

	Vector3f& getPos();
	Vector3f& getForward();
	Vector3f& getUp();

	Vector3f getLeft() const;
	Vector3f getRight() const;

	void setPos(const Vector3f& pos);
	void setForward(const Vector3f& forward);
	void setUp(const Vector3f& up);
protected:
private:
	Vector3f m_pos;
	Vector3f m_forward;
	Vector3f m_up;
};

#endif