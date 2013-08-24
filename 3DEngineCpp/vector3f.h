#ifndef VECTOR3F_H
#define VECTOR3F_H

class Vector3f
{
public:
	static const Vector3f UP;
	static const Vector3f DOWN;
	static const Vector3f LEFT;
	static const Vector3f RIGHT;
	static const Vector3f FORWARD;
	static const Vector3f BACK;
	static const Vector3f ONE;
	static const Vector3f ZERO;

	float x,y,z;

	Vector3f(float x = 0.0f, float y = 0.0f, float z = 0.0f);

	float length() const;
	float dot(const Vector3f& v) const;

	Vector3f cross(const Vector3f& v) const;
	Vector3f rotate(float angle, const Vector3f& axis) const;

	Vector3f& normalize();

	Vector3f& operator+=(const Vector3f& r);
    Vector3f& operator-=(const Vector3f& r);
    Vector3f& operator*=(float f);
	Vector3f& operator/=(float f);

	Vector3f operator+(const Vector3f& r) const;
	Vector3f operator-(const Vector3f& r) const;
	Vector3f operator*(float f) const;
	Vector3f operator/(float f) const;

	inline bool operator==(const Vector3f& r) const;
	inline bool operator!=(const Vector3f& r) const;
};

#endif