// Copyright (c) 2007 by Tech Soft 3D, LLC.
// all rights reserved
// $Id: h3d_post_focus_filter.hlsl,v 1.1 2009-05-26 18:29:40 will Exp $
 
// Copyright (c) 2007 by Tech Soft 3D, LLC.
// all rights reserved
// $Id: h3d_post_focus_filter.hlsl,v 1.1 2009-05-26 18:29:40 will Exp $
 
#ifndef NUM_TAPS
#error NUM_TAPS must be defined to use this shader!
#endif // NUM_TAPS
 
/* Uniforms ******************************************************************/

uniform sampler2D Sampler reg(s0);
uniform const float4 Kernel[NUM_TAPS];

#define CENTRE_WEIGHT (1.414*112.0/256.0)

/* Code **********************************************************************/

void post_pixel(
	float2 in_uv,
	out float4 result)
{
	float4 centre = tex2D(Sampler, in_uv);
	
	// Initialise accumulator
	float total_weight = CENTRE_WEIGHT;
	result = centre * CENTRE_WEIGHT;

	for ( int i = 0; i < NUM_TAPS; ++i )
	{
		float2 uv = in_uv + Kernel[i].xy;
		float4 sample = tex2D(Sampler, uv);
		
		// Accumulate weighted by centre's blue channel. 
		result += Kernel[i].w * sample * centre.b;
		total_weight += Kernel[i].w;
	}
	
	// Normalise
	result /= total_weight;

	// Don't filter the output blue channel
	result.b = centre.b;
} 

