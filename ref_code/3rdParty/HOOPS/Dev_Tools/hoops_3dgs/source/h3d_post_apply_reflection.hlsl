// Copyright (c) 2007 by Tech Soft 3D, LLC.
// all rights reserved
// $Id: h3d_post_apply_reflection.hlsl,v 1.5 2009-04-29 23:37:04 warren Exp $

/* Uniforms ******************************************************************/

uniform sampler2D ReflectionSampler;
uniform float Opacity;

#ifdef REFLECTION_BUMPMAP
uniform sampler2D NormalMapSampler;
uniform float BumpSize;
uniform float BumpStrength;
#endif // REFLECTION_BUMPMAP

/* Code **********************************************************************/

void post_pixel(
	float2 in_uv0,
	float2 in_uv1,
	out float4 result)
{
	// For diagnosing problems with the UV mapping
	// return float4(frac(gl_TexCoord[1]/BumpSize),0,1);
	
#ifdef REFLECTION_BUMPMAP
	// Form perspective-correct bumped image-space texture coords
	float2 uv = 0.5f + 0.5f * (in_uv0.xy/in_uv0.w);

	// Lookup bump
	float2 offset = tex2D(NormalMapSampler, in_uv1/BumpSize).rg * 2.0 - 1.0;

	// Offset coordinates
	uv += offset * BumpStrength;
#else
	
	// Use 2D coords
	float2 uv = in_uv0.xy;

#endif // REFLECTION_BUMPMAP
	
	// Sample reflection
	float4 reflection = tex2D( ReflectionSampler, uv );

	// Fade reflection (premultiplied alpha, don't forget, so we multiply alpha and rgb)
	result = reflection * Opacity;
} 

