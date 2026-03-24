// Copyright (c) 2007 by Tech Soft 3D, LLC.
// all rights reserved
// $Id: h3d_post_depth_of_field.hlsl,v 1.4 2009-05-31 20:21:46 will Exp $

/* Options *******************************************************************/

/* Uniforms ******************************************************************/

uniform sampler2D Scene reg(s0);

uniform float2 OneOverTexelSize;
uniform float MaxRadius;

/* Constants *****************************************************************/

// Available kernels
#define Kernel32_Size 32

STATIC_ARRAY_BEGIN(Kernel32_Taps, float4, Kernel32_Size/2)
	float4(-0.65229499,0.026542500,-0.26740900,-0.74962401),
	float4(-0.13066600,-0.024220601,0.59062499,-0.62143099),
	float4(0.72352201,0.38820800,0.053857900,0.83063298),
	float4(0.74592000,0.025707399,-0.12658300,-0.57638103),
	float4(0.60920501,-0.14094000,-0.31015599,0.41454300),
	float4(-0.70582801,-0.0084850304,-0.45170701,0.54161900),
	float4(0.16703700,0.11802500,0.42760801,-0.012630700),
	float4(0.032751001,0.43645099,-0.16200900,-0.11899800),
	float4(-0.79991800,-0.58339602,0.46310601,-0.63896102),
	float4(-0.35023299,0.40390000,0.21136899,0.00094752799),
	float4(0.50501800,0.63320202,-0.62858403,-0.49965000),
	float4(-0.070600897,0.84065801,-0.71336502,0.19370700),
	float4(0.18814000,-0.54516101,-0.094322897,-0.60351199),
	float4(0.25596899,0.52600801,0.58789700,0.46666300),
	float4(0.99604899,0.080805399,-0.40914601,-0.23615099),
	float4(0.19501600,-0.97045398,-0.88026899,0.40237501)
STATIC_ARRAY_END;

#if (QUALITY > 1)
#define TAP_COUNT 32
#elif (QUALITY > 0)
#define TAP_COUNT 16
#else
#define TAP_COUNT 8
#endif

/* Code **********************************************************************/

void post_pixel(
	float2 in_uv,
	out float4 result)
{
	float4 accumulator = tex2D(Scene, in_uv);
	
	// Search this radius around the source texel
	float4 tap_scale = OneOverTexelSize.xyxy * accumulator.a;
	
//	result = accumulator.a;
//	result.a = 1;
//	return;

	// Start with one sample
	accumulator.a = 1.0;
	
	for ( int i = 0; i < TAP_COUNT/2; ++i )
	{
		float4 uv = in_uv.xyxy + Kernel32_Taps[i] * tap_scale;
		
		float4 sample = tex2D(Scene, uv.xy);
		
		// Pre-weight
		sample.rgb *= sample.a;
		
		// Accumulate weighted sample and weight in A
		accumulator += sample;

		sample = tex2D(Scene, uv.zw);
		
		// Pre-weight
		sample.rgb *= sample.a;
		
		// Accumulate weighted sample and weight in A
		accumulator += sample;
	}
	
	// Normalise
	result = accumulator / accumulator.a;
} 


