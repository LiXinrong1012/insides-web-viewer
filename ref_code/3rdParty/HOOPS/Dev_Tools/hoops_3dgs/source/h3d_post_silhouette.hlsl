// Copyright (c) 2007 by Tech Soft 3D, LLC.
// all rights reserved
// $Id: h3d_post_silhouette.hlsl,v 1.15 2009-09-18 17:40:04 warren Exp $
 
/* Uniforms ******************************************************************/

uniform sampler2D Depth reg(s0);

uniform float2 OneOverTexelSize;
uniform float2 ToleranceScaleAndBias;
uniform float2 Taps[4];
uniform float DepthScale;
uniform float3 EdgeColor;

#define ONE float4(1.0, 1.0, 1.0, 1.0)

/* Code **********************************************************************/

void post_pixel(
	float2 uv,
	out float4 result)
{
	const float sharp = unpack_rgba(tex2D(Depth, uv));
	
	float silhouette = 0.0;
	
	if (sharp != 1.0)
	{
		float4 samples;
		samples.x = unpack_rgba(tex2D( Depth, uv + Taps[0] * OneOverTexelSize ));
		samples.y = unpack_rgba(tex2D( Depth, uv + Taps[1] * OneOverTexelSize ));
		samples.z = unpack_rgba(tex2D( Depth, uv + Taps[2] * OneOverTexelSize ));
		samples.w = unpack_rgba(tex2D( Depth, uv + Taps[3] * OneOverTexelSize ));
	
		// Compute deltas
		float4 deltas = abs(samples - float4(sharp, sharp, sharp, sharp)) * DepthScale;
	
		// Invalidate any excluded samples
#ifdef DX9
		deltas *= float4(notEqual(samples, ONE));
#else
		if (samples.x == 1.0)
			deltas.x = 0.0;
		if (samples.y == 1.0)
			deltas.y = 0.0;
		if (samples.z == 1.0)
			deltas.z = 0.0;
		if (samples.w == 1.0)
			deltas.w = 0.0;
#endif
	
		// Take maximum
		float max_delta = max(max(deltas.x, deltas.y), max(deltas.z, deltas.w));

		// Generate smooth silhouette value from active range.
		silhouette = saturate(max_delta * ToleranceScaleAndBias.x + ToleranceScaleAndBias.y);
	}
	
	// Darken via blend.
	result = float4(EdgeColor.r, EdgeColor.g, EdgeColor.b, silhouette);
} 
