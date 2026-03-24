// Copyright (c) 2007 by Tech Soft 3D, LLC.
// all rights reserved
// $Id: h3d_post_add_8.hlsl,v 1.3 2009-04-29 21:09:53 warren Exp $
 
#ifndef NUM_TAPS
#error NUM_TAPS must be defined to use this shader!
#endif // NUM_TAPS
 
/* Uniforms ******************************************************************/

uniform sampler2D Sampler0;
uniform sampler2D Sampler1;
uniform sampler2D Sampler2;
uniform sampler2D Sampler3;
uniform sampler2D Sampler4;
uniform sampler2D Sampler5;
uniform sampler2D Sampler6;
uniform sampler2D Sampler7;
uniform float4 Kernel[NUM_TAPS];

/* Code **********************************************************************/

void post_pixel(
	float2 in_uv,
	out float4 result)
{
	result = float4(0.0, 0.0, 0.0, 0.0);
	result += Kernel[0] * tex2D( Sampler0, in_uv.xy );
	result += Kernel[1] * tex2D( Sampler1, in_uv.xy );
	result += Kernel[2] * tex2D( Sampler2, in_uv.xy );
	result += Kernel[3] * tex2D( Sampler3, in_uv.xy );
	result += Kernel[4] * tex2D( Sampler4, in_uv.xy );
	result += Kernel[5] * tex2D( Sampler5, in_uv.xy );
	result += Kernel[6] * tex2D( Sampler6, in_uv.xy );
	result += Kernel[7] * tex2D( Sampler7, in_uv.xy );
}

