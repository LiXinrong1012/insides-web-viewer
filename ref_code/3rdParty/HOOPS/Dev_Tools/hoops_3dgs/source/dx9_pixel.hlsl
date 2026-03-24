// Copyright (c) 2007 by Tech Soft 3D, LLC.
// all rights reserved
// $Id: dx9_pixel.hlsl,v 1.87 2008-05-12 22:36:33 warren Exp $


/* Main **********************************************************************/
void main (
	vertex_results input
	, out float4 FinalColor : COLOR0
#ifdef SHADER_MODEL_3
	, in float Face : VFACE
#endif // SHADER_MODEL_3
#if defined(DEPTH_WRITING) && defined(DEPTH_WRITING_SINGLE_PASS)
	, out float4 FinalDepth : COLOR1
#endif // DEPTH_WRITING_SINGLE_PASS && DEPTH_WRITING 
)
{  

	pixel_common(input
		, FinalColor
#ifdef SHADER_MODEL_3
		, Face
#endif // SHADER_MODEL_3
#if defined(DEPTH_WRITING) && defined(DEPTH_WRITING_SINGLE_PASS)
		, FinalDepth
#endif // DEPTH_WRITING_SINGLE_PASS && DEPTH_WRITING 
	);

}

