#ifdef GLSL_120
	#define FINAL_COLOR0 gl_FragData[0]
	#define FINAL_COLOR1 gl_FragData[1]
#else
	out float4 final_color;
	out float4 final_depth;
	#define FINAL_COLOR0 final_color
	#define FINAL_COLOR1 final_depth
#endif

void main()
{
	vertex_results result;


#ifndef CREATE_SHADOW_MAP
	/* Material color for interpolation */
	result.material_color_and_specular_intensity = OUT_COLOR0;

	#ifdef EYE_POSITION_COORD
		result.eye_position = EYE_POSITION_COORD_OUT;
	#endif
	
	#ifdef TANGENT_COORD
		result.eye_tangent = TANGENT_COORD_OUT;
	#endif
	
	#ifdef PER_PIXEL_LIGHTING
		result.eye_normal = OUT_COLOR1.xyz;
	#else
		#ifdef HAS_LIGHTING
		/* Light colors for interpolation */
		result.diffuse_light_and_ambient_blend = OUT_COLOR1;
		#endif // HAS_LIGHTING
	#endif // PER_PIXEL_LIGHTING
	#ifdef HAS_ATMOSPHERIC_ATTENUATION
		result.fog = OUT_FOG;
	#endif

	#ifdef HAS_VERTEX_FINDICES
		result.findex = FINDEX_COORD_OUT.xy;
	#endif

	#if defined(WIDE_LINE) || defined(ANTI_ALIASED_LINE)
		result.wide_line_offset = OFFSET_COORD_OUT.xyz;
	#endif

	#if defined(HAS_DEFINED_MATERIAL_SHADER) || defined(HAS_TEXTURE3D)
		result.uvst0 = DIFFUSE_TEXTURE_INTERPOLATOR0_OUT.xyzw;
	#endif
	
	#if (TEXTURE_COUNT > 0) && !defined(HAS_DEFINED_MATERIAL_SHADER) && !defined(HAS_TEXTURE3D)
		/* Diffuse texture coordinates */
		result.uv0 = DIFFUSE_TEXTURE_INTERPOLATOR0_OUT.xy;
	#endif
	#ifndef SHARED_DIFFUSE_COORDS
		#if (TEXTURE_COUNT > 1)
			result.uv1 = DIFFUSE_TEXTURE_COORD1_OUT.xy;
		#endif
		#if (TEXTURE_COUNT > 2) 
			result.uv2 = DIFFUSE_TEXTURE_COORD2_OUT.xy;
		#endif
		#if (TEXTURE_COUNT > 3) 
			result.uv3 = DIFFUSE_TEXTURE_COORD3_OUT.xy;
		#endif
		#if (TEXTURE_COUNT > 4) 
			result.uv4 = DIFFUSE_TEXTURE_COORD4_OUT.xy;
		#endif
		#if (TEXTURE_COUNT > 5) 
			result.uv5 = DIFFUSE_TEXTURE_COORD5_OUT.xy;
		#endif
		#if (TEXTURE_COUNT > 6) 
			result.uv6 = DIFFUSE_TEXTURE_COORD6_OUT.xy;
		#endif
		#if (TEXTURE_COUNT > 7) 
			result.uv7 = DIFFUSE_TEXTURE_COORD7_OUT.xy;
		#endif
	#endif
	
	#if (BACK_TEXTURE_COUNT > 0) && !defined(HAS_DEFINED_MATERIAL_SHADER) && !defined(HAS_TEXTURE3D)
		/* Diffuse texture coordinates */
		result.buv0 = BACK_DIFFUSE_TEXTURE_INTERPOLATOR0_OUT.xy;
	#endif
	#if (BACK_TEXTURE_COUNT > 1)
		result.buv1 = BACK_DIFFUSE_TEXTURE_COORD1_OUT.xy;
	#endif
	#if (BACK_TEXTURE_COUNT > 2) 
		result.buv2 = BACK_DIFFUSE_TEXTURE_COORD2_OUT.xy;
	#endif
	#if (BACK_TEXTURE_COUNT > 3) 
		result.buv3 = BACK_DIFFUSE_TEXTURE_COORD3_OUT.xy;
	#endif
	#if (BACK_TEXTURE_COUNT > 4) 
		result.buv4 = BACK_DIFFUSE_TEXTURE_COORD4_OUT.xy;
	#endif
	#if (BACK_TEXTURE_COUNT > 5) 
		result.buv5 = BACK_DIFFUSE_TEXTURE_COORD5_OUT.xy;
	#endif
	#if (BACK_TEXTURE_COUNT > 6) 
		result.buv6 = BACK_DIFFUSE_TEXTURE_COORD6_OUT.xy;
	#endif
	#if (BACK_TEXTURE_COUNT > 7) 
		result.buv7 = BACK_DIFFUSE_TEXTURE_COORD7_OUT.xy;
	#endif

	#if defined(CIRCLE_MARKER) || defined(TEXTURE_MARKER) || defined(MATERIAL_SHADER_MARKER)
		#ifdef SPRITE_MARKER
			result.marker_uv = gl_PointCoord;
		#else
			result.marker_uv = MARKER_TEXTURE_OUT.xy;
		#endif
	#endif
	
	#if (SHADOW_MAP_COUNT > 0)
		/* shadow maps */
		result.uvsm0 = SHADOW_MAP_COORD0_OUT;
	#if defined(SHADOW_MAP_JITTER) || defined(SHADOW_MAP_SLICE_COUNT)
		result.screen_position = SHADOW_MAP_JITTER_COORD_OUT;
	#endif
	#endif
	#if (SHADOW_MAP_COUNT > 1)
		result.uvsm1 = SHADOW_MAP_COORD1_OUT;
	#endif
	#if (SHADOW_MAP_COUNT > 2)
		result.uvsm2 = SHADOW_MAP_COORD2_OUT;
	#endif
	#if (SHADOW_MAP_COUNT > 3)
		result.uvsm3 = SHADOW_MAP_COORD3_OUT;
	#endif

	#if (CUTTING_PLANE_COUNT > 0)
		/* cutting planes */
		result.uvcp0 = CUTTING_PLANE_COORD0_OUT;
	#endif
	#if (CUTTING_PLANE_COUNT > 4)
		result.uvcp1 = CUTTING_PLANE_COORD1_OUT;
	#endif
	#if (CUTTING_PLANE_COUNT > 8)
		result.uvcp2 = CUTTING_PLANE_COORD2_OUT;
	#endif
	#if (CUTTING_PLANE_COUNT > 12)
		result.uvcp3 = CUTTING_PLANE_COORD3_OUT;
	#endif

	#ifdef ENVIRONMENT_TEXTURE
		#if !defined(CUBE_ENVIRONMENT_MAP) || !defined(PER_PIXEL_LIGHTING)
			/* special textures */
			result.uvenv = ENVIRONMENT_TEXTURE_OUT.xyz;
		#endif
	#endif

	#ifdef SPECULAR_TEXTURE
		/* special textures */
		result.uvspec = SPECULAR_TEXTURE_OUT.xy;
	#endif
	
	#ifdef BUMP_TEXTURE
		result.uvbump = BUMP_TEXTURE_OUT.xy;
	#endif

	#ifdef TRANSMISSION_TEXTURE
		result.uvtransmission = TRANSMISSION_TEXTURE_OUT.xy;
	#endif 

	#ifdef EMISSION_TEXTURE
		result.uvemission = EMISSION_TEXTURE_OUT.xy;
	#endif 

	#ifdef MIRROR_TEXTURE
		result.uvmirror = MIRROR_TEXTURE_OUT.xy;
	#endif 

	#if defined(DEPTH_PEELING) || defined(DEPTH_WRITING)
		/* Position as texcoords for depth peeling */
		result.peel_position = DEPTH_PEELING_POSITION_COORD_OUT;
	#endif

	#ifdef HAS_FACE_PATTERN
		result.uvzwfp = FACE_PATTERN_COORD_OUT;
	#endif

	#ifdef HAS_LINE_PATTERN
		result.uvlp = LINE_PATTERN_COORD_OUT;
	#endif
#else // CREATE_SHADOW_MAP
	/* Position as texcoords for shadow mapping. */
	result.shadow_position = OUT_TEXCOORD4;
#endif // ndef CREATE_SHADOW_MAP


#ifdef SHADER_MODEL_3
	float facing = gl_FrontFacing ? -1.0 : 1.0;
#endif // SHADER_MODEL_3

	pixel_common (
		result
		, FINAL_COLOR0
	#ifdef SHADER_MODEL_3
		, facing
	#endif // SHADER_MODEL_3
	#if defined(DEPTH_WRITING) && defined(DEPTH_WRITING_SINGLE_PASS)
		, FINAL_COLOR1
	#endif // DEPTH_WRITING_SINGLE_PASS && DEPTH_WRITING 
	);

	#ifndef DEPTH_WRITING
		FINAL_COLOR1 = float4(0.0, 0.0, 0.0, 0.0);
	#endif
}
