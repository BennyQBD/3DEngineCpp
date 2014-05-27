#include "math3d.h"

Vector3f Vector3f::Rotate(const Quaternion& rotation) const
{
	Quaternion conjugateQ = rotation.Conjugate();
	Quaternion w = rotation * (*this) * conjugateQ;

	Vector3f ret(w.GetX(), w.GetY(), w.GetZ());

	return ret;
}
