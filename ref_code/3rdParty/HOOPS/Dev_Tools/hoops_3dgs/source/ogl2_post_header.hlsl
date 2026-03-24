// Copyright (c) 2007 by Tech Soft 3D, LLC.
// all rights reserved
// $Id: ogl2_post_header.hlsl,v 1.10 2010-05-14 10:14:01 will Exp $

#version 120

// ===========================
// BEGIN HEADER
// ===========================
#define DRIVER_SPECIFIC_FLIP -1.0
#define MUST_DEFINE_CLIP_FUNC
#define BAD_VARIABLE_INDEX



// compatibility datatypes
#define ddx dFdx
#define ddy dFdy
#define float2 vec2
#define float3 vec3
#define float4 vec4
#define float2x2 mat2
#define float3x3 mat3
#define float4x4 mat4
#define half float
#define half4 vec4
#define reg(a)
#define semantic(a)
#define sampler sampler2D
#define tex1D texture1D
#define tex2D texture2D
#define tex2Dproj texture2DProj
#define tex2Dlod(sampler,uv) texture2D(sampler, uv.xy, uv.w)
#define BRANCH
#define static
#define const

// compatibility functions
#define mul(a,b) b * a
#define saturate(a) clamp(a,0.0,1.0)
#define lerp(x,y,s) mix(x,y,s)
#define frac(x)	fract(x)


#define STATIC_ARRAY_BEGIN(name,type,size) type name[size] = type[size] (
#define STATIC_ARRAY_END )



// compatibility input "semantics" ( -> vs)
#define POSITION		gl_Vertex.xyz
#define NORMAL			gl_Normal
#define COLOR0			gl_Color
#define COLOR1			gl_SecondaryColor
#define TEXCOORD0		gl_MultiTexCoord0
#define TEXCOORD1		gl_MultiTexCoord1
#define TEXCOORD2		gl_MultiTexCoord2
#define TEXCOORD3		gl_MultiTexCoord3
#define TEXCOORD4		gl_MultiTexCoord4
#define TEXCOORD5		gl_MultiTexCoord5
#define TEXCOORD6		gl_MultiTexCoord6
#define TEXCOORD7		gl_MultiTexCoord7
#define FOG				gl_FogCoord

// compatibility output "semantics" (vs -> ps)
#define OUT_POSITION	gl_Position
#define OUT_COLOR0		gl_FrontColor
#define OUT_COLOR1		gl_FrontSecondaryColor
#define OUT_TEXCOORD0	gl_TexCoord[0]
#define OUT_TEXCOORD1	gl_TexCoord[1]
#define OUT_TEXCOORD2	gl_TexCoord[2]
#define OUT_TEXCOORD3	gl_TexCoord[3]
#define OUT_TEXCOORD4	gl_TexCoord[4]
#define OUT_TEXCOORD5	gl_TexCoord[5]
#define OUT_TEXCOORD6	gl_TexCoord[6]
#define OUT_TEXCOORD7	gl_TexCoord[7]
#define OUT_FOG			gl_FogFragCoord
#define OUT_PSIZE		gl_PointSize
// ===========================
// END HEADER
// ===========================

/// Unpacking a [0-1] float value from a 4D vector where each component was a 8-bits integer
float unpack_rgba(const float4 value)
{
	// Reconstruct by mutliplying each range by the remainder and add up.
	const float RADIX = 255.0;
	const float4 shift = float4(1.0, 1.0/RADIX, 1.0/(RADIX*RADIX),  1.0/(RADIX*RADIX*RADIX)); 
	return dot(value, shift);
}
