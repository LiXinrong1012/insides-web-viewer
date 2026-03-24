// Copyright (c) 2007 by Tech Soft 3D, LLC.
// all rights reserved
// $Id: h3d_post_filter.hlsl,v 1.2 2009-04-29 21:09:53 warren Exp $

#ifndef NUM_TAPS
#error NUM_TAPS must be defined to use this shader!
#endif // NUM_TAPS

/* Uniforms ******************************************************************/

uniform sampler2D Sampler;
uniform float4 Kernel[NUM_TAPS];

/* Code **********************************************************************/

void post_pixel(
	float2 uv,
	out float4 result)
{
	result = float4(0.0, 0.0, 0.0, 0.0);
	for ( int i = 0; i < NUM_TAPS; ++i )
	{
		result += Kernel[i].w * tex2D( Sampler, uv + Kernel[i].xy );
	}
} 

