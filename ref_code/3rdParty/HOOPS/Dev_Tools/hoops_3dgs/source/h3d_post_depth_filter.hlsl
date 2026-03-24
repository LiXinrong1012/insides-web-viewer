// Copyright (c) 2007 by Tech Soft 3D, LLC.
// all rights reserved
// $Id: h3d_post_depth_filter.hlsl,v 1.5 2009-05-31 20:21:47 will Exp $
 
// Copyright (c) 2007 by Tech Soft 3D, LLC.
// all rights reserved
// $Id: h3d_post_depth_filter.hlsl,v 1.5 2009-05-31 20:21:47 will Exp $
 
#ifndef NUM_TAPS
#error NUM_TAPS must be defined to use this shader!
#endif // NUM_TAPS
 
/* Uniforms ******************************************************************/

uniform sampler2D Sampler reg(s0);
uniform sampler2D Depth reg(s1);
uniform const float4 Kernel[NUM_TAPS];
uniform const float Tolerance;

/* Code **********************************************************************/

void post_pixel(
	float2 in_uv,
	out float4 result)
{
	float centre_depth = unpack_rgba(tex2D(Depth, in_uv));
	float total_weight = 0.0;
	result = float4(0.0, 0.0, 0.0, 0.0);

	for ( int i = 0; i < NUM_TAPS; ++i )
	{
		float2 uv = in_uv + Kernel[i].xy;
		float depth = unpack_rgba(tex2D(Depth, uv));
		
		// As depth difference increases, fade out sample influence sharply.
		float w = saturate( 1.0 - abs(depth - centre_depth) * Tolerance );
		
#ifndef SHADER_MODEL_2
		w = smoothstep(0.0, 1.0, w);
#endif // SHADER_MODEL_2
		
		float4 sample = tex2D(Sampler, uv);
		result += Kernel[i].w * sample * w;
		total_weight += Kernel[i].w * w; 
	}
	
	result /= total_weight;
} 

