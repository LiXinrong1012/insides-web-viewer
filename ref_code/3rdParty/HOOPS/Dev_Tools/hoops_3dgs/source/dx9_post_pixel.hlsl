// Copyright (c) 2007 by Tech Soft 3D, LLC.
// all rights reserved
// $Id: dx9_post_pixel.hlsl,v 1.2 2010-08-05 23:24:18 warren Exp $
 
/* IO Types ******************************************************************/

/* 
 * ITERATOR
 * Input from triangle setup 
 */
struct Iterator
{
	/* Transformed vertex position */
	float4 position : POSITION;
	
	/* Texture coordinates */
	float4 uv : TEXCOORD0;

#ifdef TEXCOORD_INPUT_2
	float2 world_uv : TEXCOORD1;
#endif // REFLECTION_BUMPMAP
};


/* Code **********************************************************************/

void main( Iterator iterator
		  , out float4 color : COLOR0 
#ifdef DEPTH_OUTPUT
		  , out float depth : DEPTH 
#endif
		  )
{

	post_pixel(
		iterator.uv.xy
#ifdef TEXCOORD_INPUT_2
		,iterator.world_uv
#endif
		,color
#ifdef DEPTH_OUTPUT
		,depth
#endif
	);
} 

