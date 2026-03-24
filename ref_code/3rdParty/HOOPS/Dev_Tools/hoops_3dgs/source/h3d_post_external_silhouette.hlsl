// Copyright (c) 2007 by Tech Soft 3D, LLC.
// all rights reserved
// $Id: h3d_post_external_silhouette.hlsl,v 1.13 2009-07-27 17:46:33 warren Exp $
 
/* Uniforms ******************************************************************/

uniform sampler2D Depth reg(s0);

uniform float2 OneOverTexelSize;
uniform float2 ToleranceScaleAndBias;
uniform float2 Taps[4];
uniform float3 EdgeColor;

/* Code **********************************************************************/

void post_pixel(
	float2 uv,
	out float4 result)
{
	float4 samples;
	samples.x = unpack_rgba(tex2D( Depth, uv + Taps[0] * OneOverTexelSize ));
	samples.y = unpack_rgba(tex2D( Depth, uv + Taps[1] * OneOverTexelSize ));
	samples.z = unpack_rgba(tex2D( Depth, uv + Taps[2] * OneOverTexelSize ));
	samples.w = unpack_rgba(tex2D( Depth, uv + Taps[3] * OneOverTexelSize ));
	
#define ONE float4(1.0,1.0,1.0,1.0)
#define THRESHOLD float4(254.0/255.0,254.0/255.0,254.0/255.0,254.0/255.0)
	
	float disable = dot(ONE, float4(samples == ONE));
	
#ifdef DX9
	float back = dot(ONE, float4(samples >= THRESHOLD));
#else
	float back = dot(ONE, float4(greaterThanEqual(samples, THRESHOLD)));
#endif
	
	// Generate a silhouette pixel if the filter straddles the boundary but
	// doesn't touch any excluded pixels.
	float silhouette = 0.0;
	if ( disable == 0.0 && back > 0.0 && back < 4.0 )
		silhouette = 1.0;
	
	// Darken via blend.
	result = float4(EdgeColor.r, EdgeColor.g, EdgeColor.b, silhouette);
} 

