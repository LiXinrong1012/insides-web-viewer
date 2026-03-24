// Copyright (c) 2007 by Tech Soft 3D, LLC.
// all rights reserved
// $Id: dx9_post_header.hlsl,v 1.7 2010-08-05 23:24:18 warren Exp $

#define STATIC_ARRAY_BEGIN(name,type,size) static const type name[size] = {
#define STATIC_ARRAY_END }

#define DRIVER_SPECIFIC_FLIP 1.0

#ifdef DEPTH_PACKING_RGBA
/// Unpacking a [0-1] float value from a 4D vector where each component was a 8-bits integer
float unpack_rgba(const float4 value)
{
	// Reconstruct by mutliplying each range by the remainder and add up.
	#define RADIX 255.0
	const float4 shift = float4(1.0, 1.0/RADIX, 1.0/(RADIX*RADIX),  1.0/(RADIX*RADIX*RADIX)); 
	return dot(value, shift);
}
#else
#define unpack_rgba(x) x
#endif

#define reg(s) : s
#define BRANCH [branch]
#define DX9

// OpenGL compatibility
#define equal(a, b) ((a) == (b))
#define notEqual(a, b) ((a) != (b))
#define greaterThan(a, b) ((a) > (b))
#define lessThan(a, b) ((a) < (b))

