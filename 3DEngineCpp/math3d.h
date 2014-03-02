#ifndef MATH3D_H_INCLUDED
#define MATH3D_H_INCLUDED

#include <math.h>
#define MATH_PI 3.1415926535897932384626433832795
#define ToRadians(x) (float)(((x) * MATH_PI / 180.0f))
#define ToDegrees(x) (float)(((x) * 180.0f / MATH_PI))

template<typename T, unsigned int D>
class Vector
{
public:
	Vector() { }

	inline T Dot(const Vector<T, D>& r) const
	{
		T result = T(0);
		for(unsigned int i = 0; i < D; i++)
			result += (*this)[i] * r[i];
			
		return result;
	}
	
	inline T LengthSq() const { return this->Dot(*this); }
	inline T Length() const { return sqrt(LengthSq()); }
	inline Vector<T,D> Normalized() const { return *this/Length(); }

	inline Vector<T, D> operator+(const Vector<T,D>& r) const
	{
		Vector<T, D> result;
		for(unsigned int i = 0; i < D; i++)
			result[i] = values[i] + r[i];
		
		return result;
	}
	
	inline Vector<T, D> operator-(const Vector<T,D>& r) const
	{
		Vector<T, D> result;
		for(unsigned int i = 0; i < D; i++)
			result[i] = values[i] - r[i];
		
		return result;
	}
	
	inline Vector<T, D> operator*(const T& r) const
	{
		Vector<T, D> result;
		for(unsigned int i = 0; i < D; i++)
			result[i] = values[i] * r;
		
		return result;
	}
	
	inline Vector<T, D> operator/(const T& r) const
	{
		Vector<T, D> result;
		for(unsigned int i = 0; i < D; i++)
			result[i] = values[i] / r;
		
		return result;
	}
	
	inline Vector<T, D>& operator+=(const Vector<T,D>& r) 
	{
		for(unsigned int i = 0; i < D; i++)
			(*this)[i] = values[i] + r[i];
		
		return *this;
	}
	
	inline Vector<T, D>& operator-=(const Vector<T,D>& r) 
	{
		for(unsigned int i = 0; i < D; i++)
			(*this)[i] = values[i] - r[i];
		
		return *this;
	}
	
	inline Vector<T, D>& operator*=(const T& r) 
	{
		for(unsigned int i = 0; i < D; i++)
			(*this)[i] = values[i] * r;
		
		return *this;
	}
	
	inline Vector<T, D>& operator/=(const T& r) 
	{
		for(unsigned int i = 0; i < D; i++)
			(*this)[i] = values[i] / r;
		
		return *this;
	}
	
	T& operator [] (unsigned int i) { return values[i]; }
	T operator [] (unsigned int i) const { return values[i]; }
protected:
private:
	T values[D];
};

template<typename T>
class Vector2 : public Vector<T, 2>
{
public:
	Vector2() { }
	
	Vector2(const Vector<T, 2>& r)
	{
		(*this)[0] = r[0];
		(*this)[1] = r[1];
	}
	
	Vector2(T x, T y)
	{
		(*this)[0] = x;
		(*this)[1] = y;
	}
	
	inline T GetX() const { return (*this)[0]; }
	inline T GetY() const { return (*this)[1]; }
	
	inline void SetX(const T& x) { (*this)[0] = x; }
	inline void SetY(const T& y) { (*this)[1] = y; }
	
	inline void Set(const T& x, const T& y) { SetX(x); SetY(y); }
protected:
private:
};

template<typename T>
class Vector3 : public Vector<T, 3>
{
public:
	Vector3() { }
	
	Vector3(const Vector<T, 3>& r)
	{
		(*this)[0] = r[0];
		(*this)[1] = r[1];
		(*this)[2] = r[2];
	}
	
	Vector3(T x, T y, T z)
	{
		(*this)[0] = x;
		(*this)[1] = y;
		(*this)[2] = z;
	}
	
	inline Vector3<T> Cross(const Vector3<T>& r) const
	{
		T x = (*this)[1] * r[2] - (*this)[2] * r[1];
		T y = (*this)[2] * r[0] - (*this)[0] * r[2];
		T z = (*this)[0] * r[1] - (*this)[1] * r[0];

		return Vector3<T>(x, y, z);
	}
	
	inline Vector3<T> Rotate(T angle, const Vector3<T>& axis) const
	{
		const T sinAngle = sin(-angle);
		const T cosAngle = cos(-angle);
		
		return this->Cross(axis * sinAngle) +        //Rotation on local X
			(*this * cosAngle) +                     //Rotation on local Z
		    axis * this->Dot(axis * (1 - cosAngle)); //Rotation on local Y
	}
	
	inline T GetX() const { return (*this)[0]; }
	inline T GetY() const { return (*this)[1]; }
	inline T GetZ() const { return (*this)[2]; }
	
	inline void SetX(const T& x) { (*this)[0] = x; }
	inline void SetY(const T& y) { (*this)[1] = y; }
	inline void SetZ(const T& z) { (*this)[2] = z; }
	
	inline void Set(const T& x, const T& y, const T& z) { SetX(x); SetY(y); SetZ(z); }
protected:
private:
};

template<typename T>
class Vector4 : public Vector<T, 4>
{
public:
	Vector4() { }
	
	Vector4(const Vector<T, 4>& r)
	{
		(*this)[0] = r[0];
		(*this)[1] = r[1];
		(*this)[2] = r[2];
		(*this)[3] = r[3];
	}
	
//	Vector4(const Vector<T, 3>& r)
//	{
//		(*this)[0] = r[0];
//		(*this)[1] = r[1];
//		(*this)[2] = r[2];
//		(*this)[3] = T(1);
//	}
	
	Vector4(T x, T y, T z, T w)
	{
		(*this)[0] = x;
		(*this)[1] = y;
		(*this)[2] = z;
		(*this)[3] = w;
	}
	
	inline T GetX() const { return (*this)[0]; }
	inline T GetY() const { return (*this)[1]; }
	inline T GetZ() const { return (*this)[2]; }
	inline T GetW() const { return (*this)[3]; }
	
	inline void SetX(const T& x) { (*this)[0] = x; }
	inline void SetY(const T& y) { (*this)[1] = y; }
	inline void SetZ(const T& z) { (*this)[2] = z; }
	inline void SetW(const T& w) { (*this)[3] = w; }
	
	inline void Set(const T& x, const T& y, const T& z, const T& w) { SetX(x); SetY(y); SetZ(z); SetW(w); }
protected:
private:
};

template<typename T, unsigned int D>
class Matrix
{
public:
	inline void InitIdentity()
	{
		for(unsigned int i = 0; i < D; i++)
		{
			for(unsigned int j = 0; j < D; j++)
			{
				if(i == j)
					m[i][j] = T(1);
				else
					m[i][j] = T(0);
			}
		}
	}
	
	inline void InitScaleTransform(const Vector<T,D - 1>& r)
	{
		for(unsigned int i = 0; i < D; i++)
		{
			for(unsigned int j = 0; j < D; j++)
			{
				if(i == j && i != D - 1)
					m[i][j] = r[i];
				else
					m[i][j] = T(0);
			}
		}
		
		m[D - 1][D - 1] = T(1);
	}
	
	inline void InitTranslationTransform(const Vector<T,D - 1>& r)
	{
		for(unsigned int i = 0; i < D; i++)
		{
			for(unsigned int j = 0; j < D; j++)
			{
				if(i == D - 1 && j != D - 1)
					m[i][j] = r[j];
				else if(i == j)
					m[i][j] = T(1);
				else
					m[i][j] = T(0);
			}
		}
		
		m[D - 1][D - 1] = T(1);
	}

	inline Matrix<T,D> operator*(const Matrix<T,D>& r) const
	{
		Matrix<T,D> ret;
		for (unsigned int i = 0 ; i < D ; i++) 
		{
			for (unsigned int j = 0 ; j < D; j++) 
			{
				ret.m[i][j] = T(0);
				for(unsigned int k = 0; k < D; k++)
					ret.m[i][j] += m[k][j] * r.m[i][k];
			}
		}
		return ret;
	}
	
	inline void Set(unsigned int x, unsigned int y, T val) { m[x][y] = val; }
	
	inline const T* operator[](int index) const { return m[index]; }
	inline T* operator[](int index) { return m[index]; }
protected:
private:
	T m[D][D];
};

template<typename T>
class Matrix4 : public Matrix<T, 4>
{
public:
	Matrix4() { }

	Matrix4(const Matrix<T, 4>& r)
	{
		for(unsigned int i = 0; i < 4; i++)
			for(unsigned int j = 0; j < 4; j++)
				(*this)[i][j] = r[i][j];
	}

	inline void InitRotateTransform(T rotateX, T rotateY, T rotateZ)
	{
		Matrix4<T> rx, ry, rz;

		const T x = rotateX;
		const T y = rotateY;
		const T z = rotateZ;

		rx[0][0] = T(1);   rx[1][0] = T(0)  ;  rx[2][0] = T(0)   ; rx[3][0] = T(0);
		rx[0][1] = T(0);   rx[1][1] = cos(x);  rx[2][1] = -sin(x); rx[3][1] = T(0);
		rx[0][2] = T(0);   rx[1][2] = sin(x);  rx[2][2] = cos(x) ; rx[3][2] = T(0);
		rx[0][3] = T(0);   rx[1][3] = T(0)  ;  rx[2][3] = T(0)   ; rx[3][3] = T(1);
		
		ry[0][0] = cos(y); ry[1][0] = T(0);    ry[2][0] = -sin(y); ry[3][0] = T(0);
		ry[0][1] = T(0)  ; ry[1][1] = T(1);    ry[2][1] = T(0)   ; ry[3][1] = T(0);
		ry[0][2] = sin(y); ry[1][2] = T(0);    ry[2][2] = cos(y) ; ry[3][2] = T(0);
		ry[0][3] = T(0)  ; ry[1][3] = T(0);    ry[2][3] = T(0)   ; ry[3][3] = T(1);
		
		rz[0][0] = cos(z); rz[1][0] = -sin(z); rz[2][0] = T(0);    rz[3][0] = T(0);
		rz[0][1] = sin(z); rz[1][1] = cos(z) ; rz[2][1] = T(0);    rz[3][1] = T(0);
		rz[0][2] = T(0)  ; rz[1][2] = T(0)   ; rz[2][2] = T(1);    rz[3][2] = T(0);
		rz[0][3] = T(0)  ; rz[1][3] = T(0)   ; rz[2][3] = T(0);    rz[3][3] = T(1);

		*this = rz * ry * rx;
	}
	
	inline void InitCameraTransform(const Vector3<T>& target, const Vector3<T>& up)
	{
		Vector3<T> n = target.Normalized();
		Vector3<T> u = Vector3<T>(up.Normalized()).Cross(n);
		Vector3<T> v = n.Cross(u);
		   
		(*this)[0][0] = u.GetX();   (*this)[1][0] = u.GetY();   (*this)[2][0] = u.GetZ();   (*this)[3][0] = T(0);
		(*this)[0][1] = v.GetX();   (*this)[1][1] = v.GetY();   (*this)[2][1] = v.GetZ();   (*this)[3][1] = T(0);
		(*this)[0][2] = n.GetX();   (*this)[1][2] = n.GetY();   (*this)[2][2] = n.GetZ();   (*this)[3][2] = T(0);
		(*this)[0][3] = T(0);       (*this)[1][3] = T(0);       (*this)[2][3] = T(0);       (*this)[3][3] = T(1);  
	}
	
	inline void InitPersProjTransform(T fov, T aspectRatio, T zNear, T zFar)
	{
		const T zRange     = zNear - zFar;
		const T tanHalfFOV = tanf(fov / T(2));

		(*this)[0][0] = T(1)/(tanHalfFOV * aspectRatio); (*this)[1][0] = T(0);   (*this)[2][0] = T(0);            (*this)[3][0] = T(0);
		(*this)[0][1] = T(0);                   (*this)[1][1] = T(1)/tanHalfFOV; (*this)[2][1] = T(0);            (*this)[3][1] = T(0);
		(*this)[0][2] = T(0);                   (*this)[1][2] = T(0);            (*this)[2][2] = (-zNear - zFar)/zRange ; (*this)[3][2] = T(2)*zFar*zNear/zRange;
		(*this)[0][3] = T(0);                   (*this)[1][3] = T(0);            (*this)[2][3] = T(1);            (*this)[3][3] = T(0); 
	}
protected:
private:
};

class Quaternion : public Vector4<float>
{
public:
	Quaternion() { }
	
	Quaternion(float x, float y, float z, float w)
	{
		(*this)[0] = x;
		(*this)[1] = y;
		(*this)[2] = z;
		(*this)[3] = w;
	}

	inline Quaternion Conjugate() const { return Quaternion(-GetX(), -GetY(), -GetZ(), GetW()); }

	inline Quaternion operator*(const Quaternion& r) const
	{
		const float _w = (GetW() * r.GetW()) - (GetX() * r.GetX()) - (GetY() * r.GetY()) - (GetZ() * r.GetZ());
		const float _x = (GetX() * r.GetW()) + (GetW() * r.GetX()) + (GetY() * r.GetZ()) - (GetZ() * r.GetY());
		const float _y = (GetY() * r.GetW()) + (GetW() * r.GetY()) + (GetZ() * r.GetX()) - (GetX() * r.GetZ());
		const float _z = (GetZ() * r.GetW()) + (GetW() * r.GetZ()) + (GetX() * r.GetY()) - (GetY() * r.GetX());

		return Quaternion(_x, _y, _z, _w);
	}
	
	inline Quaternion operator*(const Vector3<float>& v) const
	{
		const float _w = - (GetX() * v.GetX()) - (GetY() * v.GetY()) - (GetZ() * v.GetZ());
		const float _x =   (GetW() * v.GetX()) + (GetY() * v.GetZ()) - (GetZ() * v.GetY());
		const float _y =   (GetW() * v.GetY()) + (GetZ() * v.GetX()) - (GetX() * v.GetZ());
		const float _z =   (GetW() * v.GetZ()) + (GetX() * v.GetY()) - (GetY() * v.GetX());

		return Quaternion(_x, _y, _z, _w);
	}
};

typedef Vector2<int> Vector2i;
typedef Vector3<int> Vector3i;
typedef Vector4<int> Vector4i;

typedef Vector2<float> Vector2f;
typedef Vector3<float> Vector3f;
typedef Vector4<float> Vector4f;

typedef Vector2<double> Vector2d;
typedef Vector3<double> Vector3d;
typedef Vector4<double> Vector4d;

typedef Matrix4<float> Matrix4f;

#endif // MATH3D_H_INCLUDED
