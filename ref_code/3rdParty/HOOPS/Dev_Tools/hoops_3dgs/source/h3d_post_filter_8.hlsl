// Copyright (c) 2007 by Tech Soft 3D, LLC.
// all rights reserved
// $Id: h3d_post_filter_8.hlsl,v 1.1 2009-04-28 01:04:35 warren Exp $
#define NUM_TAPS 8

#ifndef NUM_TAPS
#error NUM_TAPS must be defined to use this shader!
#endif // NUM_TAPS

/* Uniforms ******************************************************************/

uniform sampler2D Sampler;
uniform float4 Kernel[NUM_TAPS];

/* Code **********************************************************************/

float4 post_pixel(
	float2 uv)
{
	float4 result = float4(0.0, 0.0, 0.0, 0.0);
	for ( int i = 0; i < NUM_TAPS; ++i )
	{
		result += Kernel[i].w * tex2D( Sampler, uv + Kernel[i].xy );
	}

	return result;
} 

