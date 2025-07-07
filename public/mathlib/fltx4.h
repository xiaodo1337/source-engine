//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: - defines the type fltx4 - Avoid cyclic includion.
//
//===========================================================================//

#ifndef FLTX4_H
#define FLTX4_H

#if defined(GNUC)
#define USE_STDC_FOR_SIMD 0
#else
#define USE_STDC_FOR_SIMD 0
#endif
#if defined (__arm__) || defined (__aarch64__)
#include "sse2neon.h"
#endif
#if (!defined(_X360) && (USE_STDC_FOR_SIMD == 0))
#define _SSE1 1
#endif

// I thought about defining a class/union for the SIMD packed floats instead of using fltx4,
// but decided against it because (a) the nature of SIMD code which includes comparisons is to blur
// the relationship between packed floats and packed integer types and (b) not sure that the
// compiler would handle generating good code for the intrinsics.

#if USE_STDC_FOR_SIMD

typedef union
{
	float  m128_f32[4];
	uint32 m128_u32[4];
} fltx4;

typedef fltx4 i32x4;
typedef fltx4 u32x4;

#elif ( defined( _X360 ) )

typedef union
{
	// This union allows float/int access (which generally shouldn't be done in inner loops)
	__vector4	vmx;
	float		m128_f32[4];
	uint32		m128_u32[4];
} fltx4_union;

typedef __vector4 fltx4;
typedef __vector4 i32x4; // a VMX register; just a way of making it explicit that we're doing integer ops.
typedef __vector4 u32x4; // a VMX register; just a way of making it explicit that we're doing unsigned integer ops.

#else

typedef __m128 fltx4;
typedef __m128 i32x4;
typedef __m128 u32x4;
typedef __m128i shortx8;

#endif

#endif
