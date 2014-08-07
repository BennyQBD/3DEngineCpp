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

#ifndef X86SIMDACCEL_H_INCLUDED
#define X86SIMDACCEL_H_INCLUDED

#include "simddefines.h"

class SIMD4i
{
public:
	SIMD4i() {}
	
	SIMD4i(int32_t a) :
		m_data(_mm_set1_epi32(a)) {}
	
	SIMD4i(int32_t a, int32_t b, int32_t c, int32_t d) :
		m_data(_mm_setr_epi32(a, b, c, d)) {}
	
	SIMD4i(const __m128i& data) :
		m_data(data) {}
	
	inline void Get(int32_t* result) const 
	{
        _mm_storeu_si128((__m128i*)result, m_data);
    }
	
	inline void Set(const int32_t* data)
	{
		m_data = _mm_loadu_si128((__m128i*)data);
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
		#if SIMD_SUPPORTED_LEVEL >= SIMD_LEVEL_x86_SSE4_1
			return SIMD4i(_mm_blendv_epi8((*this), sourceIfTrue, sourceIfFalse));
		#else
			return ((*this) & sourceIfTrue) | (this->AndNot(sourceIfFalse));
		#endif
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
		return SIMD4i(_mm_shuffle_epi32(m_data, shuffleByte));
	}
	
	inline int32_t HorizontalAdd()
	{
		#if  SIMD_SUPPORTED_LEVEL >= SIMD_LEVEL_x86_SSSE3
			SIMD4i temp1 = SIMD4i(_mm_hadd_epi32(m_data, other.m_data));
			SIMD4i temp2 = SIMD4i(_mm_hadd_epi32(temp1, temp1));
			return _mm_cvtsi128_si32(temp2);
		#else
			SIMD4i temp1 = Shuffle(0x0E);
			SIMD4i temp2 = (*this) + temp1;
			SIMD4i temp3 = temp2.Shuffle(0x01);
			SIMD4i temp4 = temp2 + temp3;
			return _mm_cvtsi128_si32(temp4);
		#endif
	}
	
	inline SIMD4i Max(const SIMD4i& other)
	{
		#if SIMD_SUPPORTED_LEVEL >= SIMD_LEVEL_x86_SSE4_1
			return SIMD4i(_mm_max_epi32(m_data, other.m_data));
		#else
			SIMD4i isGreater = (*this) > other;
			return isGreater.Pick((*this), other);
		#endif
	}
	
	inline SIMD4i Min(const SIMD4i& other)
	{
		#if SIMD_SUPPORTED_LEVEL >= SIMD_LEVEL_x86_SSE4_1
			return SIMD4i(_mm_min_epi32(m_data, other.m_data));
		#else
			SIMD4i isGreater = (*this) > other;
			return isGreater.Pick(other, (*this));
		#endif
	}
	
	inline SIMD4i Abs()
	{
		#if SIMD_SUPPORTED_LEVEL >= SIMD_LEVEL_x86_SSSE3
			return SIMD4i(_mm_sign_epi32(m_data, m_data));
		#else
			SIMD4i sign    = _mm_srai_epi32(m_data, 31);
			SIMD4i flipped = _mm_xor_si128(m_data, sign);
			return SIMD4i(_mm_sub_epi32(flipped, sign));
		#endif
	}
	
	inline SIMD4i AndNot(const SIMD4i& other) const { return SIMD4i(_mm_andnot_si128(other.m_data, m_data)); }

	inline SIMD4i operator+ (const SIMD4i& other) const { return SIMD4i(_mm_add_epi32(m_data, other.m_data)); }
	inline void operator += (const SIMD4i& other)       { m_data = _mm_add_epi32(m_data, other.m_data); }
	
	inline SIMD4i operator- (const SIMD4i& other) const { return SIMD4i(_mm_sub_epi32(m_data, other.m_data)); }
	inline void operator -= (const SIMD4i& other)       { m_data = _mm_sub_epi32(m_data, other.m_data); }
	
	inline SIMD4i operator* (const SIMD4i& other) const 
	{ 
		#if SIMD_SUPPORTED_LEVEL >= SIMD_LEVEL_x86_SSE4_1 
			return _mm_mullo_epi32(m_data, other.m_data);
		#else
			SIMD4i paramA1133 = Shuffle(0xF5);
			SIMD4i paramB1133 = other.Shuffle(0xF5);
			SIMD4i result0022 = _mm_mul_epu32(m_data, other.m_data);
			SIMD4i result1133 = _mm_mul_epu32(paramA1133, paramB1133);
			SIMD4i result0101 = _mm_unpacklo_epi32(result0022, result1133);
			SIMD4i result2323 = _mm_unpackhi_epi32(result0022, result1133);
			SIMD4i result0123 = _mm_unpacklo_epi64(result0101, result2323);
			return SIMD4i(result0123);
		#endif
	}
	inline void operator*= (const SIMD4i& other)       { m_data = (*this) * other; }
	
	inline SIMD4i operator<< (int32_t amt) const 
	{ 
		return SIMD4i(_mm_sll_epi32(m_data, _mm_cvtsi32_si128(amt)));
	}
	
	inline void operator<<= (int32_t amt) { m_data = (*this) << amt; }
	
	inline SIMD4i operator>> (int32_t amt) const 
	{ 
		return SIMD4i(_mm_sra_epi32(m_data, _mm_cvtsi32_si128(amt)));
	}
	
	inline void operator>>= (int32_t amt) { m_data = (*this) >> amt; }
	
//	inline SIMD4i operator/ (const SIMD4i& other) const { return SIMD4i(_mm_div_epi32(m_data, other.m_data)); }
//	inline void operator /= (const SIMD4i& other)       { m_data = _mm_div_epi32(m_data, other.m_data); }
	
	inline SIMD4i operator& (const SIMD4i& other) const { return SIMD4i(_mm_and_si128(m_data, other.m_data)); }
	inline void operator &= (const SIMD4i& other)       { m_data = _mm_and_si128(m_data, other.m_data); }
	inline SIMD4i operator&&(const SIMD4i& other) const { return (*this) & other; }
	
	inline SIMD4i operator| (const SIMD4i& other) const { return SIMD4i(_mm_or_si128(m_data, other.m_data)); }
	inline void operator |= (const SIMD4i& other)       { m_data = _mm_or_si128(m_data, other.m_data); }
	inline SIMD4i operator||(const SIMD4i& other) const { return (*this) | other; }
	
	inline SIMD4i operator^ (const SIMD4i& other) const { return SIMD4i(_mm_xor_si128(m_data, other.m_data)); }
	inline void operator ^= (const SIMD4i& other)       { m_data = _mm_xor_si128(m_data, other.m_data); }
	
	inline SIMD4i operator~() const { return SIMD4i(_mm_xor_si128(m_data, _mm_set1_epi32(-1))); }
	
	inline SIMD4i operator== (const SIMD4i& other) const { return SIMD4i(_mm_cmpeq_epi32(m_data, other.m_data)); }
	inline SIMD4i operator!= (const SIMD4i& other) const { return ~((*this) == other); }
	inline SIMD4i operator>  (const SIMD4i& other) const { return SIMD4i(_mm_cmpgt_epi32(m_data, other.m_data)); }
	inline SIMD4i operator<  (const SIMD4i& other) const { return other > (*this); }
	inline SIMD4i operator>= (const SIMD4i& other) const { return ~(other > (*this)); }
	inline SIMD4i operator<= (const SIMD4i& other) const { return other >= (*this); }
	
	inline SIMD4i operator!() const { return SIMD4i(_mm_cmpeq_epi32(m_data,_mm_setzero_si128())); }
	operator __m128i() const 
	{
        return m_data;
    };
protected:
private:
	__m128i m_data;
};

class SIMD4f
{
public:
	SIMD4f() {}
	SIMD4f(float a, float b, float c, float d) :
		m_data(_mm_setr_ps(a, b, c, d)) {}
	
	SIMD4f(float a) :
		m_data(_mm_set1_ps(a)) {}
	
	SIMD4f(const __m128& data) :
		m_data(data) {}
	
	inline void Get(float* result) const 
	{
        _mm_storeu_ps(result, m_data);
    }
	
	inline void Set(const float* data)
	{
		m_data = _mm_loadu_ps(data);
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
		return SIMD4f(_mm_andnot_ps(m_data, other.m_data));
	}
	
	inline SIMD4f Max(const SIMD4f& other) const
	{
		return SIMD4f(_mm_max_ps(m_data, other.m_data));
	}
	
	inline SIMD4f Min(const SIMD4f& other) const
	{
		return SIMD4f(_mm_min_ps(m_data, other.m_data));
	}
	
	inline SIMD4f Pick(const SIMD4f& sourceIfTrue, const SIMD4f& sourceIfFalse)
	{
		#if SIMD_SUPPORTED_LEVEL >= SIMD_LEVEL_x86_SSE4_1
			return SIMD4f(_mm_blendv_ps((*this), sourceIfTrue, sourceIfFalse));
		#else
			return ((*this) & sourceIfTrue) | (this->AndNot(sourceIfFalse));
		#endif
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
		return SIMD4f(_mm_shuffle_ps(m_data, m_data, shuffleByte));
	}
	
	inline float HorizontalAdd() const
	{
	#if SIMD_SUPPORTED_LEVEL >= SIMD_LEVEL_x86_SSSE3
	    SIMD4f temp1 = _mm_hadd_ps(m_data, m_data);
	    SIMD4f temp2 = _mm_hadd_ps(temp1, temp1);
	    return _mm_cvtss_f32(temp2);        
	#else
		SIMD4f temp1 = _mm_movehl_ps(m_data, m_data);
		SIMD4f temp2 = _mm_add_ps(m_data, temp1);
		SIMD4f temp3 = _mm_shuffle_ps(temp2, temp2, 1);
		SIMD4f temp4 = _mm_add_ss(temp2, temp3);
		return _mm_cvtss_f32(temp4);
	#endif
	}
	
	inline SIMD4i RoundToInt() const
	{
		return SIMD4i(_mm_cvtps_epi32(m_data));
	}
	
	inline SIMD4i TruncateToInt() const
	{
		return SIMD4i(_mm_cvttps_epi32(m_data));
	}
	
	inline SIMD4f Round(int roundingMode = 0) const
	{
		roundingMode = roundingMode & 3; //Use low bits, since rounding mode only uses 2 bits.
	
		#if SIMD_SUPPORTED_LEVEL >= SIMD_LEVEL_x86_SSE4_1
			return _mm_round_ps(m_data, roundingMode);
		#else 
			//If the hardware doesn't support rounding, it must be emulated
			//by manipulating the MXCSR modes.
			uint32_t mxcsr    = _mm_getcsr();
			uint32_t newmxcsr = mxcsr | (roundingMode << 13); 
			_mm_setcsr(newmxcsr);
			
			static const __m128 SIGN_MASK               = _mm_castsi128_ps(SIMD4i(0x80000000,0x80000000,0x80000000,0x80000000));
			static const __m128 MAGIC_ROUNDING_CONSTANT = _mm_castsi128_ps(SIMD4i(0x4B000000,0x4B000000,0x4B000000,0x4B000000));
			SIMD4f sign                                 = _mm_and_ps(m_data, SIGN_MASK);
			SIMD4f signedMagic                          = _mm_or_ps(MAGIC_ROUNDING_CONSTANT, sign);
			SIMD4f dataPlusSignedMagic                  = _mm_add_ps(m_data, signedMagic);
			
			SIMD4f result = SIMD4f(_mm_sub_ps(dataPlusSignedMagic, signedMagic));
			
			_mm_setcsr(mxcsr);
		return result;
		#endif
	}
	
	//Floor, ceil, and truncate are just different rounding modes.
	//Therefore, we can use the rounding function for it.
	inline SIMD4f Floor()    const { return Round(1); }
	inline SIMD4f Ceil()     const { return Round(2); }
	inline SIMD4f Truncate() const { return Round(3); }
	
	inline SIMD4f Abs() const
	{
		static const __m128 ABS_MASK = _mm_castsi128_ps(_mm_set1_epi32(0x7FFFFFFF));
		
		return SIMD4f(_mm_and_ps(m_data, ABS_MASK));
	}
	
	inline SIMD4f Sqrt() const
	{
		return SIMD4f(_mm_sqrt_ps(m_data));
	}
	
	//Uses Quake-style fast inverse square root trick, except
	//implemented in hardware (if available) and more
	//Newton-Raphson refinements.
	inline SIMD4f FastRSqrt() const
	{
		return SIMD4f(_mm_rsqrt_ps(m_data));
	}
	
	inline SIMD4f FastReciprocal() const
	{
		return SIMD4f(_mm_rcp_ps(m_data));
	}
	
	inline SIMD4f operator+ (const SIMD4f& other) const { return SIMD4f(_mm_add_ps(m_data, other.m_data)); }
	inline void operator += (const SIMD4f& other)       { m_data = _mm_add_ps(m_data, other.m_data); }
	
	inline SIMD4f operator- (const SIMD4f& other) const { return SIMD4f(_mm_sub_ps(m_data, other.m_data)); }
	inline void operator -= (const SIMD4f& other)       { m_data = _mm_sub_ps(m_data, other.m_data); }
	
	inline SIMD4f operator* (const SIMD4f& other) const { return SIMD4f(_mm_mul_ps(m_data, other.m_data)); }
	inline void operator *= (const SIMD4f& other)       { m_data = _mm_mul_ps(m_data, other.m_data); }
	
	inline SIMD4f operator/ (const SIMD4f& other) const { return SIMD4f(_mm_div_ps(m_data, other.m_data)); }
	inline void operator /= (const SIMD4f& other)       { m_data = _mm_div_ps(m_data, other.m_data); }
	
	inline SIMD4f operator& (const SIMD4f& other) const { return SIMD4f(_mm_and_ps(m_data, other.m_data)); }
	inline void operator &= (const SIMD4f& other)       { m_data = _mm_and_ps(m_data, other.m_data); }
	
	inline SIMD4f operator| (const SIMD4f& other) const { return SIMD4f(_mm_or_ps(m_data, other.m_data)); }
	inline void operator |= (const SIMD4f& other)       { m_data = _mm_or_ps(m_data, other.m_data); }
	
	inline SIMD4f operator^ (const SIMD4f& other) const { return SIMD4f(_mm_xor_ps(m_data, other.m_data)); }
	inline void operator ^= (const SIMD4f& other)       { m_data = _mm_xor_ps(m_data, other.m_data); }
	
	inline SIMD4f operator== (const SIMD4f& other) const { return SIMD4f(_mm_cmpeq_ps(m_data, other.m_data)); }
	inline SIMD4f operator!= (const SIMD4f& other) const { return SIMD4f(_mm_cmpneq_ps(m_data, other.m_data)); }
	inline SIMD4f operator>  (const SIMD4f& other) const { return SIMD4f(_mm_cmpgt_ps(m_data, other.m_data)); }
	inline SIMD4f operator<  (const SIMD4f& other) const { return SIMD4f(_mm_cmplt_ps(m_data, other.m_data)); }
	inline SIMD4f operator>= (const SIMD4f& other) const { return SIMD4f(_mm_cmpge_ps(m_data, other.m_data)); }
	inline SIMD4f operator<= (const SIMD4f& other) const { return SIMD4f(_mm_cmple_ps(m_data, other.m_data)); }
	
	inline SIMD4f operator!() const { return SIMD4f((*this) == SIMD4f(0.0f)); }
	
	operator __m128() const 
	{
        return m_data;
    }
protected:
private:
	__m128 m_data;
};

#endif // X86SIMDACCEL_H_INCLUDED
