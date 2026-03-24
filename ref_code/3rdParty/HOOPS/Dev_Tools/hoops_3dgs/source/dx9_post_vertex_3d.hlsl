// Copyright (c) 2007 by Tech Soft 3D, LLC.
// all rights reserved
// $Id: dx9_post_vertex_3d.hlsl,v 1.2 2009-01-25 18:26:30 will Exp $
 
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
	float2 uv : TEXCOORD0;
	
	/* Texture coordinate */
	float4 vpos : TEXCOORD1;
};

/* Uniforms ******************************************************************/

/* Depth value */
float ConstantDepth;
float4x4 ModelToProjection;

/* Code **********************************************************************/

Iterator main( const Vertex vertex )
{
	Iterator result;

	// Assemble and transform position
	float4 position = mul(float4(vertex.position.xy,0,1), ModelToProjection);
	
	// Output a position at a fixed depth, working around perspective divide
	result.position = float4(position.xy, ConstantDepth * position.w, position.w);
	    
    // Map NDC space into unit square UV space
	result.uv = vertex.position.xy * 0.5 + 0.5;
	result.uv.y = 1 - result.uv.y;
	result.vpos = position;
	
	// Done
	return result;
} 

