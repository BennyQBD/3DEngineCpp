/*
 * Copyright (C) 2014 Benny Bobaganoosh
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SIMDEMULATOR_H_INCLUDED
#define SIMDEMULATOR_H_INCLUDED

#include <math.h>

class SIMD4i
{
public:
	SIMD4i() {}
	SIMD4i(int32_t* data)
	{
		m_data[0] = data[0];
		m_data[1] = data[1];
		m_data[2] = data[2];
		m_data[3] = data[3];
	}
	
	SIMD4i(int32_t a)
	{
		for(int i = 0; i < 4; i++)
		{
			m_data[i] = a;
		}
	}
	
	SIMD4i(int32_t a, int32_t b, int32_t c, int32_t d)
	{
		m_data[0] = a;
		m_data[1] = b;
		m_data[2] = c;
		m_data[3] = d;
	}
	
	inline void Get(int32_t* result) const 
	{
		for(int i = 0; i < 4; i++)
		{
			result[i] = m_data[i];
		}
    }
	
	inline void Set(const int32_t* data)
	{
		for(int i = 0; i < 4; i++)
		{
			m_data[i] = data[i];
		}
	}
	
	inline void GetBytes(int8_t* result) const
	{
		Get((int32_t*)result);
	}
	
	inline void SetBytes(const int8_t* data)
	{
		Set((const int32_t*)data);
	}

	inline SIMD4i Pick(const SIMD4i& sourceIfTrue, const SIMD4i& sourceIfFalse)
	{
		int32_t result[4];
		
		for(int i = 0; i < 4; i++)
		{
			if(m_data[i] == 0)
			{
				result[i] = sourceIfFalse.m_data[i];
			}
			else
			{
				result[i] = sourceIfTrue.m_data[i];
			}
		}
		
		return SIMD4i(result);
//		return ((*this) & sourceIfTrue) | AndNot(sourceIfFalse);
	}
	
	inline SIMD4i ConditionalAdd(const SIMD4i& num1, const SIMD4i& num2)
	{
		return num1 + ((*this) & num2);
	}
	
	//Shuffle byte is arranged as follows:
	//Bit 0/1: Which element goes to slot 1
	//Bit 2/3: Which element goes to slot 2
	//Bit 4/5: Which element goes to slot 3
	//Bit 6/7: Which element goes to slot 4
	inline SIMD4i Shuffle(int8_t shuffleByte)
	{
		int index0 = (shuffleByte)      & 3;
		int index1 = (shuffleByte >> 2) & 3;
		int index2 = (shuffleByte >> 4) & 3;
		int index3 = (shuffleByte >> 6) & 3;
		
		return SIMD4i(m_data[index0], m_data[index1], m_data[index2], m_data[index3]);
	}
	
	inline int32_t HorizontalAdd()
	{
		int32_t result = int32_t(0);
		for(int i = 0; i < 4; i++)
		{
			result += m_data[i];
		}
		
		return result;
	}
	
	inline SIMD4i Max(const SIMD4i& other)
	{
		SIMD4i isGreater = (*this) > other;
		return isGreater.Pick((*this), other);
	}
	
	inline SIMD4i Min(const SIMD4i& other)
	{
		SIMD4i isGreater = (*this) > other;
		return isGreater.Pick(other, (*this));
	}
	
	inline SIMD4i Abs()
	{
		int32_t result[4];
		for(int i = 0; i < 4; i++)
		{
			result[i] = abs(m_data[i]);
		}
		return SIMD4i(result);
	}
	
	inline SIMD4i AndNot(const SIMD4i& other) const 
	{ 
		return (*this) & (!other);
	}

	inline SIMD4i operator+ (const SIMD4i& other) const 
	{ 
		int32_t result[4];
		for(int i = 0; i < 4; i++)
		{
			result[i] = m_data[i] + other.m_data[i];
		}
		return SIMD4i(result);
	}
	inline void operator += (const SIMD4i& other)       { (*this) = (*this) + other; }
	
	inline SIMD4i operator- (const SIMD4i& other) const 
	{ 
		int32_t result[4];
		for(int i = 0; i < 4; i++)
		{
			result[i] = m_data[i] - other.m_data[i];
		}
		return SIMD4i(result);
	}
	inline void operator -= (const SIMD4i& other)       { (*this) = (*this) - other; }
	
	inline SIMD4i operator* (const SIMD4i& other) const 
	{ 
		int32_t result[4];
		for(int i = 0; i < 4; i++)
		{
			result[i] = m_data[i] * other.m_data[i];
		}
		return SIMD4i(result);
	}
	inline void operator*= (const SIMD4i& other)       { (*this) = (*this) * other; }
	
	inline SIMD4i operator<< (int32_t amt) const 
	{ 
		int32_t result[4];
		for(int i = 0; i < 4; i++)
		{
			result[i] = m_data[i] << amt;
		}
		return SIMD4i(result);
	}
	
	inline void operator<<= (int32_t amt) { (*this) = (*this) << amt; }
	
	inline SIMD4i operator>> (int32_t amt) const 
	{ 
		int32_t result[4];
		for(int i = 0; i < 4; i++)
		{
			result[i] = m_data[i] >> amt;
		}
		return SIMD4i(result);
	}
	
	inline void operator>>= (int32_t amt) { (*this) = (*this) >> amt; }
	
	inline SIMD4i operator& (const SIMD4i& other) const 
	{ 
		int32_t result[4];
		for(int i = 0; i < 4; i++)
		{
			result[i] = m_data[i] & other.m_data[i];
		}
		return SIMD4i(result);
	}
	inline void operator &= (const SIMD4i& other)       { (*this) = (*this) & other; }
	inline SIMD4i operator&&(const SIMD4i& other) const { return (*this) & other; }
	
	inline SIMD4i operator| (const SIMD4i& other) const 
	{ 
		int32_t result[4];
		for(int i = 0; i < 4; i++)
		{
			result[i] = m_data[i] | other.m_data[i];
		}
		return SIMD4i(result); 
	}
	inline void operator |= (const SIMD4i& other)       { (*this) = (*this) | other; }
	inline SIMD4i operator||(const SIMD4i& other) const { return (*this) | other; }
	
	inline SIMD4i operator^ (const SIMD4i& other) const 
	{ 
		int32_t result[4];
		for(int i = 0; i < 4; i++)
		{
			result[i] = m_data[i] ^ other.m_data[i];
		}
		return SIMD4i(result); 
	}
	inline void operator ^= (const SIMD4i& other)       { (*this) = (*this) ^ other; }
	
	inline SIMD4i operator~() const 
	{ 
		int32_t result[4];
		for(int i = 0; i < 4; i++)
		{
			result[i] = ~m_data[i];
		}
		return SIMD4i(result); 
	}
	
	inline SIMD4i operator== (const SIMD4i& other) const 
	{ 
		int32_t result[4];
		for(int i = 0; i < 4; i++)
		{
			if(m_data[i] == other.m_data[i])
			{
				result[i] = -1;
			}
			else
			{
				result[i] = 0;
			}
		}
		return SIMD4i(result); 
	}
	inline SIMD4i operator!= (const SIMD4i& other) const { return ~((*this) == other); }
	inline SIMD4i operator>  (const SIMD4i& other) const 
	{ 
		int32_t result[4];
		for(int i = 0; i < 4; i++)
		{
			if(m_data[i] > other.m_data[i])
			{
				result[i] = -1;
			}
			else
			{
				result[i] = 0;
			}
		}
		return SIMD4i(result); 
	}
	inline SIMD4i operator<  (const SIMD4i& other) const { return other > (*this); }
	inline SIMD4i operator>= (const SIMD4i& other) const { return ~(other > (*this)); }
	inline SIMD4i operator<= (const SIMD4i& other) const { return other >= (*this); }
	
	inline SIMD4i operator!() const 
	{ 
		int32_t compareVal[4];
		for(int i = 0; i < 4; i++)
		{
			compareVal[i] = 0;
		}
		SIMD4i  compare(compareVal);
		return (*this) == compare;
	}
protected:
private:
	int32_t m_data[4];
};


class SIMD4f
{
public:
	SIMD4f() {}
	SIMD4f(float a, float b, float c, float d)
	{
		m_data[0] = a;
		m_data[1] = b;
		m_data[2] = c;
		m_data[3] = d;
	}
	
	SIMD4f(float a)
	{
		m_data[0] = a;
		m_data[1] = a;
		m_data[2] = a;
		m_data[3] = a;
	}
	
	SIMD4f(const float* data)
	{
		m_data[0] = data[0];
		m_data[1] = data[1];
		m_data[2] = data[2];
		m_data[3] = data[3];
	}
	
	inline void Get(float* result) const 
	{
		for(int i = 0; i < 4; i++)
		{
			result[i] = m_data[i];
		}
    }
	
	inline void Set(const float* data)
	{
		for(int i = 0; i < 4; i++)
		{
			m_data[i] = data[i];
		}
	}
	
	inline void GetBytes(int8_t* result) const
	{
		Get((float*)result);
	}
	
	inline void SetBytes(const int8_t* data)
	{
		Set((const float*)data);
	}
	
	inline SIMD4f AndNot(const SIMD4f& other) const
	{
		return (*this) & (!other);
	}
	
	inline SIMD4f Max(const SIMD4f& other) const
	{
		float result[4];
		for(int i = 0; i < 4; i++)
		{
			result[i] = other.m_data[i] > m_data[i] ? other.m_data[i] : m_data[i];
		}
		return SIMD4f(result);
	}
	
	inline SIMD4f Min(const SIMD4f& other) const
	{
		float result[4];
		for(int i = 0; i < 4; i++)
		{
			result[i] = other.m_data[i] < m_data[i] ? other.m_data[i] : m_data[i];
		}
		return SIMD4f(result);
	}
	
	inline SIMD4f Pick(const SIMD4f& sourceIfTrue, const SIMD4f& sourceIfFalse)
	{
		float result[4];
		
		for(int i = 0; i < 4; i++)
		{
			if(m_data[i] == 0)
			{
				result[i] = sourceIfFalse.m_data[i];
			}
			else
			{
				result[i] = sourceIfTrue.m_data[i];
			}
		}
		
		return SIMD4f(result);
	}
	
	inline SIMD4f ConditionalAdd(const SIMD4f& num1, const SIMD4f& num2)
	{
		return num1 + ((*this) & num2);
	}
	
	//Shuffle byte is arranged as follows:
	//Bit 0/1: Which element goes to slot 1
	//Bit 2/3: Which element goes to slot 2
	//Bit 4/5: Which element goes to slot 3
	//Bit 6/7: Which element goes to slot 4
	inline SIMD4f Shuffle(int8_t shuffleByte)
	{
		int index0 = (shuffleByte)      & 3;
		int index1 = (shuffleByte >> 2) & 3;
		int index2 = (shuffleByte >> 4) & 3;
		int index3 = (shuffleByte >> 6) & 3;
		
		return SIMD4f(m_data[index0], m_data[index1], m_data[index2], m_data[index3]);
	}
	
	inline float HorizontalAdd() const
	{
		float result = 0.0f;
		for(int i = 0; i < 4; i++)
		{
			result += m_data[i];
		}
		return result;
	}
	
	inline SIMD4i RoundToInt() const
	{
		int32_t result[4];
		for(int i = 0; i < 4; i++)
		{
			result[i] = (int)floor(m_data[i] + 0.5f);
		}
		return SIMD4i(result);
	}
	
	inline SIMD4i TruncateToInt() const
	{
		int32_t result[4];
		for(int i = 0; i < 4; i++)
		{
			result[i] = (int)m_data[i];
		}
		return SIMD4i(result);
	}
	
	inline SIMD4f Round(int roundingMode = 0) const
	{
		roundingMode = roundingMode & 3;
	
		if(roundingMode == 0)
		{
			float result[4];
			for(int i = 0; i < 4; i++)
			{
				result[i] = floor(m_data[i] + 0.5f);
			}
			return SIMD4f(result);
		}
		else if(roundingMode == 1)
		{
			return Floor();
		}
		else if(roundingMode == 2)
		{
			return Ceil();
		}
		else if(roundingMode == 3)
		{
			return Truncate();
		}
	}
	
	inline SIMD4f Floor() const
	{ 
		float result[4];
		for(int i = 0; i < 4; i++)
		{
			result[i] = floor(m_data[i]);
		}
		return SIMD4f(result);
	}
	inline SIMD4f Ceil() const
	{ 
		float result[4];
		for(int i = 0; i < 4; i++)
		{
			result[i] = ceil(m_data[i]);
		}
		return SIMD4f(result);
	}
	inline SIMD4f Truncate() const
	{ 
		float result[4];
		for(int i = 0; i < 4; i++)
		{
			result[i] = (float)((int)m_data[i]);
		}
		return SIMD4f(result);
	}
	
	inline SIMD4f Abs() const
	{
		float result[4];
		for(int i = 0; i < 4; i++)
		{
			result[i] = abs(m_data[i]);
		}
		return SIMD4f(result);
	}
	
	inline SIMD4f Sqrt() const
	{
		float result[4];
		for(int i = 0; i < 4; i++)
		{
			result[i] = sqrt(m_data[i]);
		}
		return SIMD4f(result);
	}
	
	//Uses Quake-style fast inverse square root trick, except
	//implemented in hardware (if available) and more
	//Newton-Raphson refinements.
	inline SIMD4f FastRSqrt() const
	{
		//Haven't gotten around to implementing the trick yet,
		//should later be changed to that.
	
		float result[4];
		for(int i = 0; i < 4; i++)
		{
			result[i] = 1.0f/sqrt(m_data[i]);
		}
		return SIMD4f(result);
	}
	
	inline SIMD4f FastReciprocal() const
	{
		//This should be changed to use the fast reciprocal trick.
		float result[4];
		for(int i = 0; i < 4; i++)
		{
			result[i] = 1.0f/m_data[i];
		}
		return SIMD4f(result);
	}
	
	inline SIMD4f operator+ (const SIMD4f& other) const 
	{ 
		float result[4];
		for(int i = 0; i < 4; i++)
		{
			result[i] = m_data[i] + other.m_data[i];
		}
		return SIMD4f(result);
	}
	inline void operator += (const SIMD4f& other)       { (*this) = (*this) + other; }
	
	inline SIMD4f operator- (const SIMD4f& other) const 
	{ 
		float result[4];
		for(int i = 0; i < 4; i++)
		{
			result[i] = m_data[i] - other.m_data[i];
		}
		return SIMD4f(result);
	}
	inline void operator -= (const SIMD4f& other)       { (*this) = (*this) - other; }
	
	inline SIMD4f operator* (const SIMD4f& other) const 
	{ 
		float result[4];
		for(int i = 0; i < 4; i++)
		{
			result[i] = m_data[i] * other.m_data[i];
		}
		return SIMD4f(result);
	}
	inline void operator *= (const SIMD4f& other)       { (*this) = (*this) * other; }
	
	inline SIMD4f operator/ (const SIMD4f& other) const 
	{ 
		float result[4];
		for(int i = 0; i < 4; i++)
		{
			result[i] = m_data[i] / other.m_data[i];
		}
		return SIMD4f(result);
	}
	inline void operator /= (const SIMD4f& other)       { (*this) = (*this) / other; }
	
	inline SIMD4f operator& (const SIMD4f& other) const 
	{ 
		float result[4];
		for(int i = 0; i < 4; i++)
		{
			result[i] = (float)((int)m_data[i] & (int)other.m_data[i]);
		}
		return SIMD4f(result);
	}
	inline void operator &= (const SIMD4f& other)       { (*this) = (*this) & other; }
	
	inline SIMD4f operator| (const SIMD4f& other) const 
	{ 
		float result[4];
		for(int i = 0; i < 4; i++)
		{
			result[i] = (float)((int)m_data[i] | (int)other.m_data[i]);
		}
		return SIMD4f(result);
	}
	inline void operator |= (const SIMD4f& other)       { (*this) = (*this) | other; }
	
	inline SIMD4f operator^ (const SIMD4f& other) const 
	{ 
		float result[4];
		for(int i = 0; i < 4; i++)
		{
			result[i] = (float)((int)m_data[i] ^ (int)other.m_data[i]);
		}
		return SIMD4f(result);
	}
	inline void operator ^= (const SIMD4f& other)       { (*this) = (*this) ^ other; }
	
	inline SIMD4f operator== (const SIMD4f& other) const 
	{ 
		float result[4];
		for(int i = 0; i < 4; i++)
		{
			if(m_data[i] == other.m_data[i])
			{
				result[i] = -1;
			}
			else
			{
				result[i] = 0;
			}
		}
		return SIMD4f(result); 
	}
	inline SIMD4f operator!= (const SIMD4f& other) const { return !((*this) == other); }
	inline SIMD4f operator>  (const SIMD4f& other) const 
	{ 
		float result[4];
		for(int i = 0; i < 4; i++)
		{
			if(m_data[i] > other.m_data[i])
			{
				result[i] = -1;
			}
			else
			{
				result[i] = 0;
			}
		}
		return SIMD4f(result); 
	}
	inline SIMD4f operator<  (const SIMD4f& other) const { return other > (*this); }
	inline SIMD4f operator>= (const SIMD4f& other) const { return !(other > (*this)); }
	inline SIMD4f operator<= (const SIMD4f& other) const { return other >= (*this); }
	
	inline SIMD4f operator!() const { return SIMD4f((*this) == SIMD4f(0.0f)); }
protected:
private:
	float m_data[4];
};

#endif // SIMDEMULATOR_H_INCLUDED
