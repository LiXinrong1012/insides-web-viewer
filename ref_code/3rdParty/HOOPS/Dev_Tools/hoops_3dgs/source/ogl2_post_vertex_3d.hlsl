// Copyright (c) 2007 by Tech Soft 3D, LLC.
// all rights reserved
// $Id: ogl2_post_vertex_3d.hlsl,v 1.4 2010-07-16 00:55:07 warren Exp $

attribute float3 in_position;

/* Uniforms ******************************************************************/

/* Depth value */
uniform float ConstantDepth;
uniform mat4 ModelToProjection;

/* Code **********************************************************************/

void main()
{
	// Assemble and transform position
	float4 position = mul(float4(in_position.xy,0.0,1.0), ModelToProjection);
	
	// Output a position at a fixed depth, working around perspective divide
	gl_Position = float4(position.xy, ConstantDepth * position.w, position.w);

	// Map NDC space into unit square UV space
	gl_TexCoord[0].xy = in_position.xy * 0.5 + 0.5;
	gl_TexCoord[0].y = 1.0 - gl_TexCoord[0].y;
	gl_TexCoord[1] = position;
} 