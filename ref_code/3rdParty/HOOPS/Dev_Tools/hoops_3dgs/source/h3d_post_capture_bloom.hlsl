// Copyright (c) 2007 by Tech Soft 3D, LLC.
// all rights reserved
// $Id: h3d_post_capture_bloom.hlsl,v 1.6 2010-05-17 17:39:41 warren Exp $
 
/* IO Types ******************************************************************/


/* Uniforms ******************************************************************/

uniform sampler2D Scene reg(s0);

#define TINT float4(1.0,0.7,0.4,1.0);

/* Code **********************************************************************/

void post_pixel(
	float2 in_uv,
	out float4 result)
{
	float4 pixel = tex2D( Scene, in_uv );
	
	// Unbias pixel luminance
	pixel.a = (pixel.a - (1.0/255.0)) * (255.0/254.0);
	
	// Unpack brightness - [0, 0.5] scales RGB for normal bloom, [0.5,1] drives stars.
	float bloom = 2.0 * pixel.a;
	float star = 2.0 * pixel.a - 1.0;
	
	// Weight by "brightness" value
	pixel.rgb *= bloom;
	pixel.a = star;
	
	result = pixel * TINT;
} 

