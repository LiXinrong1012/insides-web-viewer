// Copyright (c) 2007 by Tech Soft 3D, LLC.
// all rights reserved
// $Id: h3d_post_ambient_occlusion_filter.hlsl,v 1.4 2010-05-14 10:14:01 will Exp $

/* Uniforms ******************************************************************/

uniform sampler2D Sampler reg(s0);
uniform const float4 Taps[4];
uniform const float4 Weights[2];
uniform const float Tolerance;

/* Code **********************************************************************/

/// Unpacking a [0-1] float value from a 4D vector where each component was a 8-bits integer
float unpack_rgb(const float3 value)
{
	// Reconstruct by mutliplying each range by the remainder and add up.
	const float3 shift = float3(1.0, 1.0/255.0, 1.0/(255.0*255.0));
	return dot(value, shift);
}

void post_pixel(
	float2 in_uv,
	out float4 result)
{
	// Read centre sample
	result = tex2D(Sampler, in_uv);

	// Unpack depth
	float centre_z = unpack_rgb(result.rgb);
/*	
#ifndef SHADER_MODEL_2
	BRANCH
#endif
	if ( centre_z == 0.0 )
	{
		return;
	}
*/	
	// Weight value (central kernel weight from 7-tap Gaussian)
	const float CENTRE_WEIGHT = (20.0/64.0);
	result.a *= CENTRE_WEIGHT;
	
	//
	// Now read the six neighbouring samples
	//
	
	// Sample first two
	float4 uv = in_uv.xyxy + Taps[0];
	float4 sample0 = tex2D(Sampler, uv.xy);
	float4 sample1 = tex2D(Sampler, uv.zw);

	// Sample second two
	uv = in_uv.xyxy + Taps[1];
	float4 sample2 = tex2D(Sampler, uv.xy);
	float4 sample3 = tex2D(Sampler, uv.zw);
	
	// Unpack first four
	float4 z;
	float4 a;
	z.x = unpack_rgb(sample0.rgb);
	a.x = sample0.a;	
	z.y = unpack_rgb(sample1.rgb);
	a.y = sample1.a;	
	z.z = unpack_rgb(sample2.rgb);
	a.z = sample2.a;	
	z.w = unpack_rgb(sample3.rgb);
	a.w = sample3.a;	
	
	// As depth difference increases, fade out sample influence sharply.
	float4 w = saturate( 1.0 - abs(z - float4(centre_z,centre_z,centre_z,centre_z)) * Tolerance );
		
#ifndef SHADER_MODEL_2
//	w = smoothstep(0.0, 1.0, w);
#endif // SHADER_MODEL_2

	// Accumulate them
	w *= Weights[0];
	float4 total_w = w;
	float4 total_a = a * w;
	
	// Sample third two
	uv = in_uv.xyxy + Taps[2];
	sample0 = tex2D(Sampler, uv.xy);
	sample1 = tex2D(Sampler, uv.zw);
	
	// Unpack third two
	z.x = unpack_rgb(sample0.rgb);
	a.x = sample0.a;	
	z.y = unpack_rgb(sample1.rgb);
	a.y = sample1.a;	
	
	// As depth difference increases, fade out sample influence sharply.
	w.xy = saturate( 1.0 - abs(z.xy - float2(centre_z,centre_z)) * Tolerance );
		
#ifndef SHADER_MODEL_2
//	w.xy = smoothstep(0.0, 1.0, w.xy);
#endif // SHADER_MODEL_2
	
	// Accumulate them
	w.xy *= Weights[1].xy;
	total_w.xy += w.xy;
	total_a.xy += a.xy * w.xy;

	// Add to centre sample	
	result.a += dot(total_a, float4(1.0,1.0,1.0,1.0));
	result.a /= CENTRE_WEIGHT + dot(total_w, float4(1.0,1.0,1.0,1.0));
} 

