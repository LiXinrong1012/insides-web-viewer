// Copyright (c) 2007 by Tech Soft 3D, LLC.
// all rights reserved
// $Id: ogl2_post_vertex.hlsl,v 1.4 2010-07-16 00:55:07 warren Exp $

attribute float4 in_position;

/* Uniforms ******************************************************************/

/* Depth value */
uniform float ConstantDepth;

/* 2D offset to centre pixels on texels correctly */
uniform vec2 TexelOffset;

/* Code **********************************************************************/
void main()
{
	// Assemble position with fixed depth and no perspective divide.
	vec4 position = vec4(in_position.xy,ConstantDepth,1.0);
	gl_Position = position;
	
    // Map NDC space into unit square UV space
	gl_TexCoord[0] = position * 0.5f + 0.5f;
} 

