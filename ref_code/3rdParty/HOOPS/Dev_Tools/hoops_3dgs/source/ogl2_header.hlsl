// Copyright (c) 2007 by Tech Soft 3D, LLC.
// all rights reserved
// $Id: ogl2_header.hlsl,v 1.31 2010-10-05 18:12:54 warren Exp $

#ifndef GLSL_120
precision highp float;
#extension GL_EXT_gpu_shader4 : enable
#endif

// ===========================
// BEGIN HEADER
// ===========================
#define DRIVER_SPECIFIC_FLIP -1.0
#define MUST_DEFINE_CLIP_FUNC
#define BAD_VARIABLE_INDEX
#define OPENGL2

// compatibility datatypes
#define ddx dFdx
#define ddy dFdy
#define float2 vec2
#define float3 vec3
#define float4 vec4
#define float2x2 mat2
#define float3x3 mat3
#define float4x4 mat4
#define reg(a)
#define semantic(a)
#define sampler sampler2D
#define tex2D texture2D
#define tex3D texture3D
#define texCUBE textureCube
#define tex2Dgrad texture2DGrad
#define static
#define const

// compatibility functions
#define mul(a,b) ((b) * (a))
#define saturate(a) clamp((a),0.0,1.0)
#define lerp(x,y,s) mix(x,y,s)
#define frac(x)	fract(x)
//arg reversal in next line is intentional
#define atan2(x,y) atan(y,x)


#define STATIC_ARRAY_BEGIN(name,type,size) type name[size] = type[size] (
#define STATIC_ARRAY_END )


// compatibility output "semantics" (vs -> ps)
#define OUT_POSITION	gl_Position
#define OUT_PSIZE		gl_PointSize

// work around bug on radeon x1300 with point sprites getting wrong color
#ifdef GLSL_120
	#ifdef OPENGL_PIXEL_SHADER
		#define OUT_COLOR0		gl_Color
		#define OUT_COLOR1		gl_SecondaryColor
	#else
		#define OUT_COLOR0		gl_FrontColor
		#define OUT_COLOR1		gl_FrontSecondaryColor
	#endif
	
	#define OUT_TEXCOORD0	gl_TexCoord[0]
	#define OUT_TEXCOORD1	gl_TexCoord[1]
	#define OUT_TEXCOORD2	gl_TexCoord[2]
	#define OUT_TEXCOORD3	gl_TexCoord[3]
	#define OUT_TEXCOORD4	gl_TexCoord[4]
	#define OUT_TEXCOORD5	gl_TexCoord[5]
	#define OUT_TEXCOORD6	gl_TexCoord[6]
	#define OUT_TEXCOORD7	gl_TexCoord[7]
	#define OUT_FOG			gl_FogFragCoord
#else
	#ifdef OPENGL_PIXEL_SHADER
		#define VARYING in
	#else
		#define VARYING out
	#endif

	#ifdef FLAT_SHADING
		flat VARYING float4 out_color0;
		flat VARYING float4 out_color1;
	#else 
		VARYING float4 out_color0;
		VARYING float4 out_color1;
	#endif
	VARYING float4 out_texcoord0;
	VARYING float4 out_texcoord1;
	VARYING float4 out_texcoord2;
	VARYING float4 out_texcoord3;
	VARYING float4 out_texcoord4;
	VARYING float4 out_texcoord5;
	VARYING float4 out_texcoord6;
	VARYING float4 out_texcoord7;
	VARYING float out_fogcoord;

	#define OUT_COLOR0		out_color0
	#define OUT_COLOR1		out_color1
	#define OUT_TEXCOORD0	out_texcoord0
	#define OUT_TEXCOORD1	out_texcoord1
	#define OUT_TEXCOORD2	out_texcoord2
	#define OUT_TEXCOORD3	out_texcoord3
	#define OUT_TEXCOORD4	out_texcoord4
	#define OUT_TEXCOORD5	out_texcoord5
	#define OUT_TEXCOORD6	out_texcoord6
	#define OUT_TEXCOORD7	out_texcoord7
	#define OUT_FOG			out_fogcoord
#endif


// ===========================
// END HEADER
// ===========================


