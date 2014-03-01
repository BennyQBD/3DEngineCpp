#ifndef VECTOR3F_H
#define VECTOR3F_H

#include <math.h>

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

	Vector3f(float x = 0.0f, float y = 0.0f, float z = 0.0f) :
		x(x),
		y(y),
		z(z) {}

	inline float Length() const { return sqrtf(x * x + y * y + z * z); }
	float Dot(const Vector3f& v) const { return x * v.x + y * v.y + z * v.z; }

	inline Vector3f Cross(const Vector3f& v) const
	{
		const float _x = y * v.z - z * v.y;
		const float _y = z * v.x - x * v.z;
		const float _z = x * v.y - y * v.x;

		return Vector3f(_x, _y, _z);
	}
	
	inline Vector3f Rotate(float angle, const Vector3f& axis) const
	{
		const float sin = sinf(-angle);
		const float cos = cosf(-angle);
		
		return this->Cross(axis * sin) +        //Rotation on local X
			(*this * cos) +                     //Rotation on local Z
		    axis * this->Dot(axis * (1 - cos)); //Rotation on local Y
		
//		const float sinHalfAngle = sinf(angle/2);
//		const float cosHalfAngle = cosf(angle/2);
//
//		const float Rx = axis.x * sinHalfAngle;
//		const float Ry = axis.y * sinHalfAngle;
//		const float Rz = axis.z * sinHalfAngle;
//		const float Rw = cosHalfAngle;
//
//		Quaternion rotationQ(Rx, Ry, Rz, Rw);
//
//		Quaternion conjugateQ = rotationQ.Conjugate();
//	  //  ConjugateQ.Normalize();
//		Quaternion w = rotationQ * (*this) * conjugateQ;
//
//		Vector3f ret(w.GetX(), w.GetY(), w.GetZ());
//
//		return ret;
	}

	inline Vector3f Normalized() const
	{
		const float length = Length();

		return Vector3f(x / length, y / length, z / length);
	}

	inline Vector3f operator+(const Vector3f& r) const { return Vector3f(x + r.x, y + r.y, z + r.z); }
	inline Vector3f operator-(const Vector3f& r) const { return Vector3f(x - r.x, y - r.y, z - r.z); }
	inline Vector3f operator*(float f) const { return Vector3f(x * f, y * f, z * f); }
	inline Vector3f operator/(float f) const { return Vector3f(x / f, y / f, z / f); }

	inline bool operator==(const Vector3f& r) const { return x == r.x && y == r.y && z == r.z; }
	inline bool operator!=(const Vector3f& r) const { return !operator==(r); }
	
	inline Vector3f& operator+=(const Vector3f& r)
	{
		x += r.x;
		y += r.y;
		z += r.z;

		return *this;
	}
	
    inline Vector3f& operator-=(const Vector3f& r)
    {
		x -= r.x;
		y -= r.y;
		z -= r.z;

		return *this;
    }
    
    inline Vector3f& operator*=(float f)
    {
		x *= f;
		y *= f;
		z *= f;

		return *this;
    }
    
	inline Vector3f& operator/=(float f)
	{
		x /= f;
		y /= f;
		z /= f;

		return *this;
	}
	
	inline float GetX() const { return x; }
	inline float GetY() const { return y; }
	inline float GetZ() const { return z; }
	
	inline void SetX(float x) { this->x = x; }
	inline void SetY(float y) { this->y = y; }
	inline void SetZ(float z) { this->z = z; }
	
	inline void Set(float x, float y, float z) { this->x = x; this->y = y; this->z = z; }
private:
	float x,y,z;
};

#endif
