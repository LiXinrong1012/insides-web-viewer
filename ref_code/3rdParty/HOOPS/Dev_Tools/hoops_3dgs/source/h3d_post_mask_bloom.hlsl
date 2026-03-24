// Copyright (c) 2007 by Tech Soft 3D, LLC.
// all rights reserved
// $Id: h3d_post_mask_bloom.hlsl,v 1.3 2009-05-29 09:44:20 heppe Exp $
 
/* IO Types ******************************************************************/


/* Uniforms ******************************************************************/

uniform sampler2D Scene reg(s0);

/* Code **********************************************************************/

void post_pixel(
	float2 in_uv,
	out float4 result)
{
	float4 pixel = tex2D( Scene, in_uv );
	
	// Convert nonzero luminance into 1.0 alpha
	float mask = float(pixel.a != 0.0);
	result = float4(mask, mask, mask, mask);
} 

