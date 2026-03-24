// Copyright (c) 2010 by Tech Soft 3D, LLC.
// all rights reserved
// $Id: ogl2_vertex.hlsl,v 1.43 2010-11-17 19:52:14 heppe Exp $

#ifdef GLSL_120
	#define ATTRIB attribute
#else
	#define ATTRIB in
#endif

ATTRIB float3 in_position;
ATTRIB float3 in_normal;
ATTRIB float4 in_color;
ATTRIB float4 in_secondary_color;
ATTRIB float4 in_texcoord0;
ATTRIB float4 in_texcoord1;
ATTRIB float4 in_texcoord2;
ATTRIB float4 in_texcoord3;
ATTRIB float4 in_texcoord4;
ATTRIB float4 in_texcoord5;
ATTRIB float4 in_texcoord6;
ATTRIB float4 in_texcoord7;

#define TEXCOORD0		in_texcoord0
#define TEXCOORD1		in_texcoord1
#define TEXCOORD2		in_texcoord2
#define TEXCOORD3		in_texcoord3
#define TEXCOORD4		in_texcoord4
#define TEXCOORD5		in_texcoord5
#define TEXCOORD6		in_texcoord6
#define TEXCOORD7		in_texcoord7

void main()
{	
	vertex_input vertex;
	vertex_results result;

	// Populate vertex_input struct with values
#ifndef CREATE_SHADOW_MAP

	/* Vertex position */
	vertex.position = in_position;

	#ifdef HAS_VERTEX_NORMALS
		/* Vertex normal (in object space) for lighting */
		vertex.normal = in_normal;
	#endif
	
	#ifdef TANGENT_COORD
		vertex.tangent = TANGENT_COORD;
	#endif
	
	#ifdef WIDE_LINE
		/* expected to be mutually exclusive with textures or normals */
		vertex.end = NEXT_COORD.xyz;
		#ifdef MITERED_LINE
			vertex.previous = PREV_COORD.xyz;	/* Start of previous line */
		#endif

		/* Mitered Offset constants
		 *   x displaces along line
		 *   y displaces perpendicular to line
		 *   z id's between the vertices used to start vs end a span */
		vertex.offset = OFFSET_COORD;

		#if defined(ROUND_LINE) || defined(ANTI_ALIASED_LINE)
			vertex.uv = ROUND_COORD;
		#endif
	#endif

	#ifdef PRIORITY_HSRA
		vertex.priority = PRIORITY_HSRA_COORD.x;
	#endif


	#ifdef HAS_VERTEX_COLORS
		/* Diffuse color from the material */
		vertex.color = in_color;
	#endif
	
	#ifdef HAS_AMBIENT_OCCLUSION
		/* AO term in specular.a */
		vertex.ambient_occlusion = in_secondary_color;
	#endif 
		
	#ifdef HAS_LINE_PATTERN
		vertex.uvlp = LINE_PATTERN_COORD.xy;
	#endif

	#ifdef HAS_VERTEX_FINDICES
		vertex.findex = FINDEX_COORD.xy;
	#endif

	#if defined(HAS_DEFINED_MATERIAL_SHADER) || defined(HAS_TEXTURE3D)
		vertex.uvst0 = DIFFUSE_TEXTURE_COORD0.xyzw;
	#endif
	
	#if (TEXTURE_COUNT > 0) && !defined(HAS_DEFINED_MATERIAL_SHADER) && !defined(HAS_TEXTURE3D)
		/* Texture coordinates */
		vertex.uv0 = DIFFUSE_TEXTURE_COORD0.xy;
	#endif
	#ifndef SHARED_DIFFUSE_COORDS
		#if (TEXTURE_COUNT > 1) 
			vertex.uv1 = DIFFUSE_TEXTURE_COORD1.xy;
		#endif
		#if (TEXTURE_COUNT > 2) 
			vertex.uv2 = DIFFUSE_TEXTURE_COORD2.xy;
		#endif
		#if (TEXTURE_COUNT > 3) 
			vertex.uv3 = DIFFUSE_TEXTURE_COORD3.xy;
		#endif
		#if (TEXTURE_COUNT > 4) 
			vertex.uv4 = DIFFUSE_TEXTURE_COORD4.xy;
		#endif
		#if (TEXTURE_COUNT > 5) 
			vertex.uv5 = DIFFUSE_TEXTURE_COORD5.xy;
		#endif
		#if (TEXTURE_COUNT > 6) 
			vertex.uv6 = DIFFUSE_TEXTURE_COORD6.xy;
		#endif
		#if (TEXTURE_COUNT > 7) 
			vertex.uv7 = DIFFUSE_TEXTURE_COORD7.xy;
		#endif
	#endif

	#if (BACK_TEXTURE_COUNT > 0)  && !defined(HAS_DEFINED_MATERIAL_SHADER) && !defined(HAS_TEXTURE3D)
		/* Texture coordinates */
		vertex.buv0 = BACK_DIFFUSE_TEXTURE_COORD0.xy;
	#endif
	#if (BACK_TEXTURE_COUNT > 1) 
		vertex.buv1 = BACK_DIFFUSE_TEXTURE_COORD1.xy;
	#endif
	#if (BACK_TEXTURE_COUNT > 2) 
		vertex.buv2 = BACK_DIFFUSE_TEXTURE_COORD2.xy;
	#endif
	#if (BACK_TEXTURE_COUNT > 3) 
		vertex.buv3 = BACK_DIFFUSE_TEXTURE_COORD3.xy;
	#endif
	#if (BACK_TEXTURE_COUNT > 4) 
		vertex.buv4 = BACK_DIFFUSE_TEXTURE_COORD4.xy;
	#endif
	#if (BACK_TEXTURE_COUNT > 5) 
		vertex.buv5 = BACK_DIFFUSE_TEXTURE_COORD5.xy;
	#endif
	#if (BACK_TEXTURE_COUNT > 6) 
		vertex.buv6 = BACK_DIFFUSE_TEXTURE_COORD6.xy;
	#endif
	#if (BACK_TEXTURE_COUNT > 7) 
		vertex.buv7 = BACK_DIFFUSE_TEXTURE_COORD7.xy;
	#endif

	#ifdef SPECULAR_TEXTURE
		vertex.uvspec = SPECULAR_TEXTURE.xy;
	#endif
	
	#ifdef BUMP_TEXTURE
		vertex.uvbump = BUMP_TEXTURE.xy;
	#endif

	#ifdef TRANSMISSION_TEXTURE
		vertex.uvtransmission = TRANSMISSION_TEXTURE.xy;
	#endif

	#ifdef EMISSION_TEXTURE
		vertex.uvemission = EMISSION_TEXTURE.xy;
	#endif

	#ifdef MIRROR_TEXTURE
		vertex.uvmirror = MIRROR_TEXTURE.xy;
	#endif

	#ifdef QUAD_MARKER
		vertex.marker_offset = MARKER_TEXTURE.xy;
	#endif
#else /* CREATE_SHADOW_MAP */
	/* Vertex position */
	vertex.position = in_position;

#endif


	// Perform calculations
	result = vertex_common(vertex);

	result.position.z = result.position.z*2.0 - 1.0*result.position.w;

#ifdef SPRITE_MARKER
	// HACK: prevent Radeon (X1300, and maybe others) GLSL compiler from optimizing MarkerSize out
	result.position.x += MarkerSize.y;
	result.position.x -= MarkerSize.y;
#endif


	/* 
	 * vertex_results
	 * Output to triangle setup 
	 */
#ifndef CREATE_SHADOW_MAP
	/* Transformed vertex position */
	OUT_POSITION = result.position;

	/* Material color for interpolation */
	OUT_COLOR0 = result.material_color_and_specular_intensity;
	

	#ifdef EYE_POSITION_COORD
		EYE_POSITION_COORD_OUT = result.eye_position;
	#endif
	
	#ifdef TANGENT_COORD
		TANGENT_COORD_OUT = result.eye_tangent;
	#endif
	
	#ifdef PER_PIXEL_LIGHTING
		OUT_COLOR1.xyz = result.eye_normal;
	#else
		#ifdef HAS_LIGHTING
		/* Light colors for interpolation */
		OUT_COLOR1 = result.diffuse_light_and_ambient_blend;
		#endif // HAS_LIGHTING
	#endif // PER_PIXEL_LIGHTING
			
	#ifdef HAS_ATMOSPHERIC_ATTENUATION
		OUT_FOG = clamp(result.fog, 0.0, 1.0);
	#endif

	#ifdef HAS_VERTEX_FINDICES
		FINDEX_COORD_OUT.xy = result.findex;
	#endif

	#if defined(WIDE_LINE) || defined(ANTI_ALIASED_LINE)
		OFFSET_COORD_OUT.xyz = result.wide_line_offset;
	#endif

	#if defined(HAS_DEFINED_MATERIAL_SHADER) || defined(HAS_TEXTURE3D)
		DIFFUSE_TEXTURE_INTERPOLATOR0_OUT.xyzw = result.uvst0;
	#endif
	
	#if (TEXTURE_COUNT > 0) && !defined(HAS_DEFINED_MATERIAL_SHADER) && !defined(HAS_TEXTURE3D)
		/* Diffuse texture coordinates */
		DIFFUSE_TEXTURE_INTERPOLATOR0_OUT.xy = result.uv0;
	#endif
	#ifndef SHARED_DIFFUSE_COORDS
		#if (TEXTURE_COUNT > 1)
			DIFFUSE_TEXTURE_COORD1_OUT.xy = result.uv1;
		#endif
		#if (TEXTURE_COUNT > 2) 
			DIFFUSE_TEXTURE_COORD2_OUT.xy = result.uv2;
		#endif
		#if (TEXTURE_COUNT > 3) 
			DIFFUSE_TEXTURE_COORD3_OUT.xy = result.uv3;
		#endif
		#if (TEXTURE_COUNT > 4) 
			DIFFUSE_TEXTURE_COORD4_OUT.xy = result.uv4;
		#endif
		#if (TEXTURE_COUNT > 5) 
			DIFFUSE_TEXTURE_COORD5_OUT.xy = result.uv5;
		#endif
		#if (TEXTURE_COUNT > 6) 
			DIFFUSE_TEXTURE_COORD6_OUT.xy = result.uv6;
		#endif
		#if (TEXTURE_COUNT > 7) 
			DIFFUSE_TEXTURE_COORD7_OUT.xy = result.uv7;
		#endif
	#endif

	#if (BACK_TEXTURE_COUNT > 0) && !defined(HAS_DEFINED_MATERIAL_SHADER) && !defined(HAS_TEXTURE3D)
		/* Diffuse texture coordinates */
		BACK_DIFFUSE_TEXTURE_INTERPOLATOR0_OUT.xy = result.buv0;
	#endif
	#if (BACK_TEXTURE_COUNT > 1)
		BACK_DIFFUSE_TEXTURE_COORD1_OUT.xy = result.buv1;
	#endif
	#if (BACK_TEXTURE_COUNT > 2) 
		BACK_DIFFUSE_TEXTURE_COORD2_OUT.xy = result.buv2;
	#endif
	#if (BACK_TEXTURE_COUNT > 3) 
		BACK_DIFFUSE_TEXTURE_COORD3_OUT.xy = result.buv3;
	#endif
	#if (BACK_TEXTURE_COUNT > 4) 
		BACK_DIFFUSE_TEXTURE_COORD4_OUT.xy = result.buv4;
	#endif
	#if (BACK_TEXTURE_COUNT > 5) 
		BACK_DIFFUSE_TEXTURE_COORD5_OUT.xy = result.buv5;
	#endif
	#if (BACK_TEXTURE_COUNT > 6) 
		BACK_DIFFUSE_TEXTURE_COORD6_OUT.xy = result.buv6;
	#endif
	#if (BACK_TEXTURE_COUNT > 7) 
		BACK_DIFFUSE_TEXTURE_COORD7_OUT.xy = result.buv7;
	#endif
	
	#if defined(CIRCLE_MARKER) || defined(TEXTURE_MARKER) || defined(MATERIAL_SHADER_MARKER)
		MARKER_TEXTURE_OUT.xy = result.marker_uv;

		#ifdef SPRITE_MARKER
			MARKER_TEXTURE_OUT.z = result.marker_size;
		#endif
	#endif
	
	#ifdef SPRITE_MARKER
		OUT_PSIZE = result.marker_size;
	#endif
	
	#if (SHADOW_MAP_COUNT > 0)
		/* cutting planes */
		SHADOW_MAP_COORD0_OUT = result.uvsm0;
	#if defined(SHADOW_MAP_JITTER) || defined(SHADOW_MAP_SLICE_COUNT)
		SHADOW_MAP_JITTER_COORD_OUT = result.screen_position;
	#endif
	#endif
	#if (SHADOW_MAP_COUNT > 1)
		SHADOW_MAP_COORD1_OUT = result.uvsm1;
	#endif
	#if (SHADOW_MAP_COUNT > 2)
		SHADOW_MAP_COORD2_OUT = result.uvsm2;
	#endif
	#if (SHADOW_MAP_COUNT > 3)
		SHADOW_MAP_COORD3_OUT = result.uvsm3;
	#endif

	#if (CUTTING_PLANE_COUNT > 0)
		/* cutting planes */
		CUTTING_PLANE_COORD0_OUT = result.uvcp0;
	#endif
	#if (CUTTING_PLANE_COUNT > 4)
		CUTTING_PLANE_COORD1_OUT = result.uvcp1;
	#endif
	#if (CUTTING_PLANE_COUNT > 8)
		CUTTING_PLANE_COORD2_OUT = result.uvcp2;
	#endif
	#if (CUTTING_PLANE_COUNT > 12)
		CUTTING_PLANE_COORD3_OUT = result.uvcp3;
	#endif

	#ifdef ENVIRONMENT_TEXTURE
		#if !defined(CUBE_ENVIRONMENT_MAP) || !defined(PER_PIXEL_LIGHTING)
			/* special textures */
			ENVIRONMENT_TEXTURE_OUT.xyz = result.uvenv;
		#endif
	#endif

	#ifdef SPECULAR_TEXTURE
		/* special textures */
		SPECULAR_TEXTURE_OUT.xy = result.uvspec;
	#endif
	
	#ifdef BUMP_TEXTURE
		BUMP_TEXTURE_OUT.xy = result.uvbump;
	#endif 

	#ifdef TRANSMISSION_TEXTURE
		TRANSMISSION_TEXTURE_OUT.xy = result.uvtransmission;
	#endif 

	#ifdef EMISSION_TEXTURE
		EMISSION_TEXTURE_OUT.xy = result.uvemission;
	#endif 

	#ifdef MIRROR_TEXTURE
		MIRROR_TEXTURE_OUT.xy = result.uvmirror;
	#endif 

	#if defined(DEPTH_PEELING) || defined(DEPTH_WRITING)
		/* Position as texcoords for depth peeling */
		DEPTH_PEELING_POSITION_COORD_OUT = result.peel_position;
	#endif

	#ifdef HAS_FACE_PATTERN
		FACE_PATTERN_COORD_OUT = result.uvzwfp;
	#endif

	#ifdef HAS_LINE_PATTERN
		LINE_PATTERN_COORD_OUT = result.uvlp;
	#endif
#else // CREATE_SHADOW_MAP
	/* Transformed vertex position */
	OUT_POSITION = result.position;
	/* Position as texcoords for shadow mapping. */
	OUT_TEXCOORD4 = result.shadow_position;
#endif // ndef CREATE_SHADOW_MAP
}


