// Copyright (c) 2007 by Tech Soft 3D, LLC.
// all rights reserved
// $Id: h3d_post_copy.hlsl,v 1.5 2009-04-30 20:59:26 warren Exp $

/* Uniforms ******************************************************************/

uniform sampler2D Sampler;
uniform float4 ModulationColor;

/* Code **********************************************************************/

void post_pixel(
	float2 uv,
	out float4 result)
{
	result = ModulationColor * tex2D( Sampler, uv.xy );
} 

