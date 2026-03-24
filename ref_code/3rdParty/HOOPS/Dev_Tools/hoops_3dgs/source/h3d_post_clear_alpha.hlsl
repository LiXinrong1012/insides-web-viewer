// Copyright (c) 2007 by Tech Soft 3D, LLC.
// all rights reserved
// $Id: h3d_post_clear_alpha.hlsl,v 1.1 2009-06-10 22:07:16 warren Exp $
 
/* IO Types ******************************************************************/


/* Uniforms ******************************************************************/

uniform sampler2D Scene reg(s0);

/* Code **********************************************************************/

void post_pixel(
	float2 in_uv,
	out float4 result)
{
	float4 pixel = tex2D( Scene, in_uv );
	result = float4(pixel.r, pixel.g, pixel.b, 0.0);
} 

