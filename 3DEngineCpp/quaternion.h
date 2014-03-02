#ifndef QUATERNION_H
#define QUATERNION_H

#include "math3d.h"

//class Quaternion
//{
//public:
//    Quaternion(float x, float y, float z, float w) :
//		x(x),
//		y(y),
//		z(z),
//		w(w) {}
//
//	inline float Length() const { return sqrtf(x * x + y * y + z * z + w * w); }
//
//    inline Quaternion Normalized() const
//    {
//		float length = Length();
//		return Quaternion(x / length, y / length, z / length, w / length);
//    }
//    
//    inline Quaternion Conjugate() const { return Quaternion(-x, -y, -z, w); }
//
//	inline float GetX() const { return x; }
//	inline float GetY() const { return y; }
//	inline float GetZ() const { return z; }
//	inline float GetW() const { return w; }
//
//	inline Quaternion operator*(const Quaternion& r) const
//	{
//		const float _w = (w * r.w) - (x * r.x) - (y * r.y) - (z * r.z);
//		const float _x = (x * r.w) + (w * r.x) + (y * r.z) - (z * r.y);
//		const float _y = (y * r.w) + (w * r.y) + (z * r.x) - (x * r.z);
//		const float _z = (z * r.w) + (w * r.z) + (x * r.y) - (y * r.x);
//
//		Quaternion ret(_x, _y, _z, _w);
//
//		return ret;
//	}
//	
//	inline Quaternion operator*(const Vector3f& v) const
//	{
//		const float _w = - (x * v.x) - (y * v.y) - (z * v.z);
//		const float _x =   (w * v.x) + (y * v.z) - (z * v.y);
//		const float _y =   (w * v.y) + (z * v.x) - (x * v.z);
//		const float _z =   (w * v.z) + (x * v.y) - (y * v.x);
//
//		Quaternion ret(_x, _y, _z, _w);
//
//		return ret;
//	}
//private:
//	float x, y, z, w;
// };



#endif
