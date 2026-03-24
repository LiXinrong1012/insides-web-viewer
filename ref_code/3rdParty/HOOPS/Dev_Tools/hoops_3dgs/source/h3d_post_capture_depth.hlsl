// Copyright (c) 2007 by Tech Soft 3D, LLC.
// all rights reserved
// $Id: h3d_post_capture_depth.hlsl,v 1.5 2009-04-29 23:37:04 warren Exp $


/* Uniforms ******************************************************************/

uniform sampler2D Depth;
uniform sampler2D Pattern;

/* Code **********************************************************************/

void post_pixel(
	float2 in_uv,
	out float4 result)
{
	// This contains eight bit unsigned noise, which we interpret as texture
	// coordinates.
	float4 pattern = tex2D(Pattern, in_uv.xy);
	
	// Convert ARGB pattern into texture coordinates with 16 bit resolution.
	float2 uv;
	float2 reconstruct = float2(255.0/256.0, 1.0/256.0);
	uv.x = dot(pattern.xy, reconstruct);
	uv.y = dot(pattern.zw, reconstruct);
	
	// Write depth at this location
	result = tex2D(Depth, uv);
} 

