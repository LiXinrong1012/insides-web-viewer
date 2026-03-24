// Copyright (c) 2007 by Tech Soft 3D, LLC.
// all rights reserved
// $Id: h3d_post_depth_to_focus.hlsl,v 1.7 2009-08-21 07:46:47 will Exp $

/* Uniforms ******************************************************************/

uniform sampler2D Depth reg(s0);

uniform float DepthScale;
uniform float2 ScaleAndBias;

/* Code **********************************************************************/

void post_pixel(
	float2 in_uv,
	out float4 result)
{
	// Zero depths always output zero, as a selection mechanism
	float raw_z = unpack_rgba(tex2D(Depth, in_uv));
	float z = DepthScale * raw_z;
	
	// Scale and bias to get focus value
	float focus = saturate(z * ScaleAndBias.x + ScaleAndBias.y);
	result.rga = float3(focus, focus, focus);
	
	// 1.0 depths are special - these mark 'no depth of field' areas. We set
	// the output blue channel so the filters can see these, and zero the output
	// value wherever it falls in the focus region.
	result.b = float(raw_z != 1.0);
	result.rga *= result.b;
} 


