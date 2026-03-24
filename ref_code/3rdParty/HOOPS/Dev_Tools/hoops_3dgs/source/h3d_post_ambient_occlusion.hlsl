// Copyright (c) 2007 by Tech Soft 3D, LLC.
// all rights reserved
// $Id: h3d_post_ambient_occlusion.hlsl,v 1.29 2010-05-14 10:14:01 will Exp $

/* Options *******************************************************************/

// Used to scale the intensity curve divisor - large values mean faster falloff.
#define RATIO 40.0

/* Uniforms ******************************************************************/

uniform sampler2D Depth reg(s0);

uniform float2 OneOverTexelSize;
uniform float Strength;
uniform float DepthScale;
uniform float MaxRadius;

uniform sampler2D Jitter reg(s1);
uniform float2 JitterScale;

/* Constants *****************************************************************/

// Taps packed pairwise.
uniform float4 Taps[16];

// Weights packed fourwise
uniform float4 Weights[8];

// Output scales
uniform float OutputScale;

/* Code **********************************************************************/

float4 dz_weight( float4 dz )
{
	return dz / (1.0 + RATIO * dz * dz);
}

#if QUALITY > 0
#ifdef tex2D
#undef tex2D
#endif
#define tex2D(sampler, uv) tex2Dlod((sampler), float4((uv).x,(uv).y,0.0,0.0))
#endif

#define ZERO float4(0.0, 0.0, 0.0, 0.0)

#if QUALITY > 0
#define SUM_WEIGHTS(a, b) (a + b)
#else
// Shader model 2 just can't afford to compute both sets of weights.
#define SUM_WEIGHTS(a, b) (2.0 * a)
#endif

#define JITTER
#ifndef JITTER
#define JITTER_OFFSET(offset) offset *= r
#else
#define JITTER_OFFSET(offset) offset = jitter_acac * offset.xxzz + jitter_bdbd * offset.yyww
#endif

#define FOUR_SAMPLES(which) \
	offset01 = Taps[which*2+0]; \
	offset23 = Taps[which*2+1]; \
	JITTER_OFFSET(offset01); \
	JITTER_OFFSET(offset23); \
	uv01 = in_uv.xyxy + offset01; \
	uv23 = in_uv.xyxy + offset23; \
	samples0.x = unpack_rgba(tex2D(Depth, uv01.xy)); \
	samples0.y = unpack_rgba(tex2D(Depth, uv01.zw)); \
	samples0.z = unpack_rgba(tex2D(Depth, uv23.xy)); \
	samples0.w = unpack_rgba(tex2D(Depth, uv23.zw)); \
	uv01 = in_uv.xyxy - offset01; \
	uv23 = in_uv.xyxy - offset23; \
	samples1.x = unpack_rgba(tex2D(Depth, uv01.xy)); \
	samples1.y = unpack_rgba(tex2D(Depth, uv01.zw)); \
	samples1.z = unpack_rgba(tex2D(Depth, uv23.xy)); \
	samples1.w = unpack_rgba(tex2D(Depth, uv23.zw)); \
	dz0 = z + samples0 * -Strength; \
	dz1 = z + samples1 * -Strength; \
	os0 = dz_weight( dz0 ); \
	os1 = dz_weight( dz1 ); \
	masks = float4(greaterThan(dz0, ZERO)) * float4(greaterThan(dz1, ZERO)); \
	o = Weights[which] * SUM_WEIGHTS(os0, os1); \
	occlusions += o * masks;

// Pack a float value for output to RGB8 texture.
float3 pack_rgb(float value)
{
	const float3 shift = float3(1.0, 255.0, 255.0*255.0); 
	const float3 mask = float3(1.0/255.0, 1.0/255.0, 0.0); 

	// Shift into the different ranges and take the fractional part in each.
	float3 packed_rgb = frac(value * shift);
	
	// Remove what can't be represented.
	return packed_rgb - mask * packed_rgb.yzz; 
}

void post_pixel(
	float2 in_uv,
	out float4 result)
{
	// Load central depth value
	float sharp = unpack_rgba(tex2D(Depth, in_uv));
	
	// Optimisation: Don't process background or excluded geometry.
#if (QUALITY > 0) && !defined(SHADER_MODEL_2)
BRANCH 
#endif
	if ( sharp >= 254.0/255.0 )
	{
		result = float4(0.0, 0.0, 0.0, 0.0);
		return;
	}
	
	// Otherwise proceed.
	const float4 z = float4(sharp, sharp, sharp, sharp) * Strength;
	float r_value = min(MaxRadius, max(1.0, DepthScale * sharp));
	const float4 r = float4(r_value, r_value, r_value, r_value) * OneOverTexelSize.xyxy;
	
	// Load jitter matrix entries
	float4 jitter = tex2D(Jitter, in_uv * JitterScale) * 2.0 - 1.0;
#ifndef DX9
	// Internal OpenGL texture format is different so the matrix entries need to be unswizzled
	jitter = jitter.wxyz;
#endif 
	// Precompute two sets of jitter matrix mulitplied by two sets of UV scaling.
	const float4 jitter_acac = jitter.xyxy * r;
	const float4 jitter_bdbd = jitter.zwzw * r;

	float4 occlusions = float4(0.0,0.0,0.0,0.0);
	
	float4 offset01, offset23, uv01, uv23;
	float4 samples0, samples1, dz0, dz1, os0, os1, masks, o;

	FOUR_SAMPLES(0)
#if QUALITY > 0
	FOUR_SAMPLES(1)
#if QUALITY > 1
	FOUR_SAMPLES(2)
	FOUR_SAMPLES(3)
#endif
#endif
/* Very high quality mode for future use
#if QUALITY > 2
	FOUR_SAMPLES(4)
	FOUR_SAMPLES(5)
	FOUR_SAMPLES(6)
	FOUR_SAMPLES(7)
#endif
*/

	const float scale = OutputScale;
	float occlusion = dot(occlusions, float4(scale, scale, scale, scale));
	
	// Write occlusion to alpha, depth to RGB
	result.rgb = pack_rgb(sharp);
	result.a = occlusion;

	// DEBUG: Show AO term
	// result = float4(1-occlusion, 1-occlusion, 1-occlusion, 1);

	// DEBUG: Show depth buffer
	// result = float4(sharp, sharp, sharp, 1);
}
