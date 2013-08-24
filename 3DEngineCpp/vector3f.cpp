#include "vector3f.h"
#include <math.h>
#include "quaternion.h"
#include "util.h"

const Vector3f Vector3f::UP(0,1,0);
const Vector3f Vector3f::DOWN(0,-1,0);
const Vector3f Vector3f::LEFT(-1,0,0);
const Vector3f Vector3f::RIGHT(1,0,0);
const Vector3f Vector3f::FORWARD(0,0,1);
const Vector3f Vector3f::BACK(0,0,-1);
const Vector3f Vector3f::ONE(1,1,1);
const Vector3f Vector3f::ZERO(0,0,0);

Vector3f::Vector3f(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

float Vector3f::length() const
{
	return sqrtf(x * x + y * y + z * z);
}

float Vector3f::dot(const Vector3f& v) const
{
	return x * v.x + y * v.y + z * v.z;
}

Vector3f Vector3f::cross(const Vector3f& v) const
{
	const float _x = y * v.z - z * v.y;
    const float _y = z * v.x - x * v.z;
    const float _z = x * v.y - y * v.x;

    return Vector3f(_x, _y, _z);
}

Vector3f& Vector3f::normalize()
{
    const float vectorLength = length();

    x /= vectorLength;
    y /= vectorLength;
    z /= vectorLength;

    return *this;
}

Vector3f Vector3f::rotate(float angle, const Vector3f& axe) const
{
    const float sinHalfAngle = sinf(ToRadian(angle/2));
    const float cosHalfAngle = cosf(ToRadian(angle/2));

    const float Rx = axe.x * sinHalfAngle;
    const float Ry = axe.y * sinHalfAngle;
    const float Rz = axe.z * sinHalfAngle;
    const float Rw = cosHalfAngle;

    Quaternion rotationQ(Rx, Ry, Rz, Rw);

    Quaternion conjugateQ = rotationQ.conjugate();
  //  ConjugateQ.Normalize();
    Quaternion w = rotationQ * (*this) * conjugateQ;

	Vector3f ret(w.x, w.y, w.z);

    return ret;
}

Vector3f& Vector3f::operator+=(const Vector3f& r)
{
    x += r.x;
    y += r.y;
    z += r.z;

    return *this;
}

Vector3f& Vector3f::operator-=(const Vector3f& r)
{
    x -= r.x;
    y -= r.y;
    z -= r.z;

    return *this;
}

Vector3f& Vector3f::operator*=(float f)
{
    x *= f;
    y *= f;
    z *= f;

    return *this;
}

Vector3f& Vector3f::operator/=(float f)
{
    x /= f;
    y /= f;
    z /= f;

    return *this;
}

Vector3f Vector3f::operator+(const Vector3f& r) const 
{
	Vector3f ret(x + r.x,
				 y + r.y,
				 z + r.z);

	return ret;
}

Vector3f Vector3f::operator-(const Vector3f& r) const 
{
	Vector3f ret(x - r.x,
				 y - r.y,
				 z - r.z);
	return ret;
}

Vector3f Vector3f::operator*(float f) const
{
	Vector3f ret(x * f,
				 y * f,
				 z * f);
	return ret;
}

Vector3f Vector3f::operator/(float f) const 
{
	Vector3f ret(x / f,
				 y / f,
				 z / f);
	return ret;
}

inline bool Vector3f::operator==(const Vector3f& r) const
{
	return x == r.x && y == r.y && z == r.z;
}

inline bool Vector3f::operator!=(const Vector3f& r) const
{
	return !operator==(r);
}