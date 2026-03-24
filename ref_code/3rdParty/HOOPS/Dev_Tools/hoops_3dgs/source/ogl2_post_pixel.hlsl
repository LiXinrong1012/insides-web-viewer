/* Code **********************************************************************/

void main()
{
	post_pixel(
		gl_TexCoord[0].xy
#ifdef TEXCOORD_INPUT_2
		,gl_TexCoord[1].xy
#endif
		,gl_FragColor
#ifdef DEPTH_OUTPUT
		,gl_FragDepth
#endif
	);
}

