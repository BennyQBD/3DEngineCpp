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

#ifndef SIMDACCELDEFINES_H_INCLUDED
#define SIMDACCELDEFINES_H_INCLUDED

//Defines for SIMD-enabled CPU architectures, and supported
//feature levels
#define SIMD_CPU_ARCH_OTHER  0
#define SIMD_CPU_ARCH_x86    1
#define SIMD_CPU_ARCH_x86_64 2

#define SIMD_LEVEL_NONE   0
#define SIMD_LEVEL_x86_SSE    1
#define SIMD_LEVEL_x86_SSE2   2
#define SIMD_LEVEL_x86_SSE3   3
#define SIMD_LEVEL_x86_SSSE3  4
#define SIMD_LEVEL_x86_SSE4_1 5
#define SIMD_LEVEL_x86_SSE4_2 6
#define SIMD_LEVEL_x86_AVX    7
#define SIMD_LEVEL_x86_AVX2   8

//Detect CPU architecture
#if (defined(_M_AMD64) || defined(_M_X64) || defined(__amd64) ) || defined(__x86_64__)
	#define SIMD_CPU_ARCH SIMD_CPU_ARCH_x86_64
#elif defined(_M_X86) || defined(__i386__) || defined(_X86_) || defined(_M_IX86)
	#define SIMD_CPU_ARCH SIMD_CPU_ARCH_x86
#else
	#define SIMD_CPU_ARCH SIMD_CPU_ARCH_OTHER
#endif

//Detect supported SIMD features
#if defined(SIMD_CPU_ARCH_x86) || defined(SIMD_CPU_ARCH_x86_64)
	#if defined(INSTRSET)
		#define SIMD_SUPPORTED_LEVEL INSTRSET
	#elif defined(__AVX2__)
		#define SIMD_SUPPORTED_LEVEL SIMD_LEVEL_x86_AVX2
	#elif defined(__AVX__)
		#define SIMD_SUPPORTED_LEVEL SIMD_LEVEL_x86_AVX
	#elif defined(__SSE4_2__)
		#define SIMD_SUPPORTED_LEVEL SIMD_LEVEL_x86_SSE4_2
	#elif defined(__SSE4_1__)
		#define SIMD_SUPPORTED_LEVEL SIMD_LEVEL_x86_SSE4_1
	#elif defined(__SSSE3__)
		#define SIMD_SUPPORTED_LEVEL SIMD_LEVEL_x86_SSSE3
	#elif defined(__SSE3__)
		#define SIMD_SUPPORTED_LEVEL SIMD_LEVEL_x86_SSE3
	#elif defined(__SSE2__) || defined(SIMD_CPU_ARCH_x86_64)
		#define SIMD_SUPPORTED_LEVEL SIMD_LEVEL_x86_SSE2
	#elif defined(__SSE__)
		#define SIMD_SUPPORTED_LEVEL SIMD_LEVEL_x86_SSE
	#elif defined(_M_IX86_FP)
		#define SIMD_SUPPORTED_LEVEL _M_IX86_FP
	#else
		#define SIMD_SUPPORTED_LEVEL SIMD_LEVEL_NONE
	#endif
#else
	#define SIMD_SUPPORTED_LEVEL SIMD_LEVEL_NONE
#endif

//Include appropriate header files for SIMD features and CPU architecture
#if defined(SIMD_CPU_ARCH_x86) || defined(SIMD_CPU_ARCH_x86_64)
	#if SIMD_SUPPORTED_LEVEL >= SIMD_LEVEL_x86_AVX2
		#ifdef __GNUC__
			#include <x86intrin.h>
		#else
			#include <immintrin.h>
		#endif
	#elif SIMD_SUPPORTED_LEVEL == SIMD_LEVEL_x86_AVX
		#include <immintrin.h>
	#elif SIMD_SUPPORTED_LEVEL == SIMD_LEVEL_x86_SSE4_2
		#include <nmmintrin.h>
	#elif SIMD_SUPPORTED_LEVEL == SIMD_LEVEL_x86_SSE4_1
		#include <smmintrin.h>
	#elif SIMD_SUPPORTED_LEVEL == SIMD_LEVEL_x86_SSSE3
		#include <tmmintrin.h>
	#elif SIMD_SUPPORTED_LEVEL == SIMD_LEVEL_x86_SSE3
		#include <pmmintrin.h>
	#elif SIMD_SUPPORTED_LEVEL == SIMD_LEVEL_x86_SSE2
		#include <emmintrin.h>
	#elif SIMD_SUPPORTED_LEVEL == SIMD_LEVEL_x86_SSE
		#include <xmmintrin.h>
	#endif
#endif

//Include known-size integer files, based on compiler. Some compilers do not have these
//files, so they must be created manually.
#if defined(__GNUC__) || defined(__clang__) || (defined(_MSC_VER) && _MSC_VER >= 1600)
	#include <stdint.h>
#elif defined(_MSC_VER)
	typedef signed   __int8  int8_t;
	typedef unsigned __int8  uint8_t;
	typedef signed   __int16 int16_t;
	typedef unsigned __int16 uint16_t;
	typedef signed   __int32 int32_t;
	typedef unsigned __int32 uint32_t;
	typedef signed   __int64 int64_t;
	typedef unsigned __int64 uint64_t;
#else
	typedef signed   char      int8_t;
	typedef unsigned char      uint8_t;
	typedef signed   short int int16_t;
	typedef unsigned short int uint16_t;
	typedef signed   int       int32_t;
	typedef unsigned int       uint32_t;
	typedef long long          int64_t;
	typedef unsigned long long uint64_t;
#endif

//#if defined(_MSC_VEC)
//     /* Microsoft C/C++-compatible compiler */
//     #include <intrin.h>
//#elif defined(__GNUC__) && (defined(__x86_64__) || defined(__i386__))
//     /* GCC-compatible compiler, targeting x86/x86-64 */
//     #include <x86intrin.h>
//#elif defined(__GNUC__) && defined(__ARM_NEON__)
//     /* GCC-compatible compiler, targeting ARM with NEON */
//     #include <arm_neon.h>
//#elif defined(__GNUC__) && defined(__IWMMXT__)
//     /* GCC-compatible compiler, targeting ARM with WMMX */
//     #include <mmintrin.h>
//#elif (defined(__GNUC__) || defined(__xlC__)) && (defined(__VEC__) || defined(__ALTIVEC__))
//     /* XLC or GCC-compatible compiler, targeting PowerPC with VMX/VSX */
//     #include <altivec.h>
//#elif defined(__GNUC__) && defined(__SPE__)
//     /* GCC-compatible compiler, targeting PowerPC with SPE */
//     #include <spe.h>
//#endif

#endif // SIMDACCELDEFINES_H_INCLUDED
