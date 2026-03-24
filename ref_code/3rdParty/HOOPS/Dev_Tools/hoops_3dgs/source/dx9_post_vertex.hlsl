// Copyright (c) 2007 by Tech Soft 3D, LLC.
// all rights reserved
// $Id: dx9_post_vertex.hlsl,v 1.5 2009-04-14 16:43:49 will Exp $
 
/* IO Types ******************************************************************/

/* 
 * VERTEX
 * Input from vertex buffer 
 */
struct Vertex
{
	/* Vertex position */
	float3 position : POSITION;
};


/* 
 * ITERATOR
 * Output to triangle setup 
 */
struct Iterator
{
	/* Transformed vertex position */
	float4 position : POSITION;
	
	/* Texture coordinate */
	float4 screen_uv : TEXCOORD0;
};

/* Uniforms ******************************************************************/

/* Depth value */
float ConstantDepth;

/* 2D offset to centre pixels on texels correctly */
float2 TexelOffset;

/* Code **********************************************************************/

Iterator main( const Vertex vertex )
{
	Iterator result;

	// Assemble position with fixed depth and no perspective divide.
	float4 position = float4(vertex.position.xy,ConstantDepth,1);
	result.position = position;
	
    // Map NDC space into unit square UV space
	result.screen_uv = position * 0.5f + 0.5f;
	result.screen_uv.xy += TexelOffset;
	result.screen_uv.y = 1 - result.screen_uv.y;
    
	// Done
	return result;
} 

