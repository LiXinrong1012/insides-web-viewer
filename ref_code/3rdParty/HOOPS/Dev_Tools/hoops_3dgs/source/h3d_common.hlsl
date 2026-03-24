// Copyright (c) 2007 by Tech Soft 3D, LLC.
// all rights reserved
// $Id: h3d_common.hlsl,v 1.53 2010-11-23 00:38:00 heppe Exp $

#define H3D_ROUND	1.0
#define H3D_SQUARE	2.0
#define H3D_MITER	3.0
#define WIDE_LINE_SCALE 1.0
#define WIDE_LINE_SAMPLER_SCALE 1.15

// This  macro helps prevent out-of-bounds array indexing errors when the array access is supposed to be
// compiled out anyways.  This problem was observed on a Radeon x1300.
#define COND(a,b) a < b ? a : 0

/* Helper functions **********************************************************/
/* ***************************************************************************/
/* ***************************************************************************/
#ifdef OPENGL2
#define rgb_to_gray(rgb) (rgb.r*0.3125 + rgb.g*0.5 + rgb.b*0.1875)
#else
float rgb_to_gray( float3 rgb )
{
	return dot( rgb, float3(0.3125, 0.5, 0.1875) );
}
#endif


/* Uniform Types *************************************************************/
/* ***************************************************************************/
/* ***************************************************************************/

/* Reflection plane */
struct reflection_plane_t
{
	float4 plane;
	float scale; // Convert depth to attenuation
	float bias;
};

#ifdef LIGHTING

#ifndef H3D_LIGHTING_MODEL
	#ifdef GOOCH
		#define BLACK_SHADOWS
		#define H3D_LIGHTING_MODEL H3D_LIGHTING_MODEL_NAME(gooch)
	#else
		#define H3D_LIGHTING_MODEL H3D_LIGHTING_MODEL_NAME(blinn_phong)
	#endif
#endif

/* A distant light */
struct distant_light_t
{
	float3 direction;
	float4 diffuse;
	float3 specular;
	float3 halfway;
};

/* A point light */
struct point_light_t
{
	float3 position;
	float4 diffuse;
	float3 specular;
};

/* A spotlight */
struct spot_light_t
{
	float3 position;
	float3 direction;
	float2 angles;
	float4 diffuse;
	float3 specular;
};

/* Distant lighting */
uniform distant_light_t DistantLights[DISTANT_LIGHT_COUNT+1];

/* Point lights */
uniform point_light_t PointLights[POINT_LIGHT_COUNT+1];

/* Spot lights */
uniform spot_light_t SpotLights[SPOT_LIGHT_COUNT+1];

//camera position in eye space
uniform float3 EyeCameraPosition;	

H3D_DECLARE_LIGHTING_MODEL(phong)
{
	/* Reflection vector */
	float3 R = reflect(-L, N);

	float NdotL = dot(N, L);
	float VdotR = dot(V, R);
	
	/* Compute diffuse */
	out_diffuse = diffuse.rgb * saturate(NdotL);
	
	/* Compute specular */
	out_specular = specular * pow(saturate(VdotR), color.specular.a);
}

H3D_DECLARE_LIGHTING_MODEL(blinn_phong)
{
	float NdotL = dot(N, L);
	float NdotH = dot(N, H);
	
	/* Compute diffuse */
	out_diffuse = diffuse.rgb * saturate(NdotL);
	
	/* Compute specular */
	out_specular = specular * pow(saturate(NdotH), color.specular.a);
}

H3D_DECLARE_LIGHTING_MODEL(blinn_phong_fresnel)
{
	// Basic Blinn-Phong first
	H3D_LIGHTING_MODEL_NAME(blinn_phong)(N, T, B, V, H, L, diffuse, specular, color, out_diffuse, out_specular);
	
	// Then layer Fresnel term on specular output
	out_specular *= h3d_schlick_fresnel_rgb(color.specular.rgb, dot(N, V), 4.0);
}

H3D_DECLARE_LIGHTING_MODEL(gooch)
{
	float NdotL = dot(N, L);
	float NdotH = dot(N, H);
	
	/* Compute diffuse greyscale, don't saturate */
	float d = NdotL * diffuse.a;
	out_diffuse = float3(d, d, d);
	
	/* Compute specular */
	out_specular = specular * pow(saturate(NdotH), color.specular.a);
}

H3D_DECLARE_LIGHTING_MODEL(cook_torrance)
{
	float NdotV = dot(N, V);
	float NdotL = dot(N, L);
	float NdotH = dot(N, H);
	float VdotH = dot(V, H);
	
	// Geometric term
	float t = 2.0*NdotH/VdotH;
	float G = min(1.0, max(0.0, min(t*NdotV, t*NdotL)));
	
	// Constants
	float Ro = color.specular.a;
	float Ro2 = saturate(0.001 + 0.999 * Ro*Ro);

	// Roughness term (Beckmann)
	float NdotH2 = NdotH*NdotH;
	float NdotH2_Ro2 = NdotH2 * Ro2;
	float R = exp( (NdotH2-1.0) / (NdotH2_Ro2) ) / (4.0*NdotH2_Ro2*NdotH2);
	
	// Fresnel
	float3 F = h3d_schlick_fresnel_rgb(color.specular.rgb, NdotV, 4.0);

	// RS term
	float3 Rs = R * F * G / (NdotV * NdotL);
	
	// Complete
	out_diffuse = saturate(NdotL) * diffuse.rgb;
	out_specular = saturate(NdotL) * Rs * specular;
}

H3D_DECLARE_LIGHTING_MODEL(heidrich_seidel)
{
	float NdotL = dot(N, L);
	float NdotH = dot(N, H);
	
	float VdotT = dot(V, T);
	float LdotT = dot(L, T);
	float sinVT = sqrt(1.0 - VdotT*VdotT);
	float sinLT = sqrt(1.0 - LdotT*LdotT);;
	
	/* Compute diffuse */
	out_diffuse = diffuse.rgb * saturate(NdotL);
	
	/* Compute specular */
	float var = sinVT*sinLT - VdotT*LdotT;
	if (var > 0.0)
		out_specular = specular * pow(var, color.specular.a);
	else
		out_specular = float3(0.0, 0.0, 0.0);
}

/*
 * Evaluate one distant light.
 */
void distant_light(HSurface surface, HColor color, distant_light_t light, float3 eye_vector, out float3 out_diffuse, out float3 out_specular)
{
	H3D_LIGHTING_MODEL(surface.normal, surface.tangent, surface.bitangent, eye_vector, light.halfway, light.direction, light.diffuse, light.specular.rgb, color, out_diffuse, out_specular);
}

/*
 * Evaluate one point light.
 */
void point_light(HSurface surface, HColor color, point_light_t light, float3 eye_vector, out float3 out_diffuse, out float3 out_specular)
{
	float3 light_vector = normalize(light.position - surface.position);
	float3 halfway = normalize(light_vector + eye_vector);

	H3D_LIGHTING_MODEL(surface.normal, surface.tangent, surface.bitangent, eye_vector, halfway, light_vector, light.diffuse, light.specular.rgb, color, out_diffuse, out_specular);
}

/*
 * Evaluate one spot light
 */
void spot_light(HSurface surface, HColor color, spot_light_t light, float3 eye_vector, out float3 out_diffuse, out float3 out_specular)
{
	float3 light_vector = normalize(light.position - surface.position);
	float3 halfway = normalize(light_vector + eye_vector);
	
	H3D_LIGHTING_MODEL(surface.normal, surface.tangent, surface.bitangent, eye_vector, halfway, light_vector, light.diffuse, light.specular.rgb, color, out_diffuse, out_specular);
	
	// Where is the point in the cone?
	float cone_dot = saturate( dot(light_vector, -light.direction) );
	
	// Work out cone angle factor
	float cone_attenuation = saturate( cone_dot * light.angles.x + light.angles.y );
	
	// Attenuate both components
	out_diffuse *= cone_attenuation;
	out_specular *= cone_attenuation;
 }

/*
 * Determine diffuse and specular light totals.
 */
void direct_lighting( const HColor color,
					  const HSurface surface,
					  inout HLighting lighting )
{
	// Temporaries
	float3 d, s;
	
	// Compute this once
	float3 eye_vector = normalize(EyeCameraPosition - surface.position);
	
#if (DISTANT_LIGHT_COUNT > 0)
	distant_light( surface, color, DistantLights[0], eye_vector, d, s); lighting.diffuse += d; lighting.specular += s;
#endif
#if (DISTANT_LIGHT_COUNT > 1)
	distant_light( surface, color, DistantLights[1], eye_vector, d, s); lighting.diffuse += d; lighting.specular += s;
#endif
#if (DISTANT_LIGHT_COUNT > 2)
	distant_light( surface, color, DistantLights[2], eye_vector, d, s); lighting.diffuse += d; lighting.specular += s;
#endif
#if (DISTANT_LIGHT_COUNT > 3)
	distant_light( surface, color, DistantLights[3], eye_vector, d, s); lighting.diffuse += d; lighting.specular += s;
#endif
#if (DISTANT_LIGHT_COUNT > 4)
	distant_light( surface, color, DistantLights[4], eye_vector, d, s); lighting.diffuse += d; lighting.specular += s;
#endif
#if (DISTANT_LIGHT_COUNT > 5)
	distant_light( surface, color, DistantLights[5], eye_vector, d, s); lighting.diffuse += d; lighting.specular += s;
#endif
#if (DISTANT_LIGHT_COUNT > 6)
	distant_light( surface, color, DistantLights[6], eye_vector, d, s); lighting.diffuse += d; lighting.specular += s;
#endif
#if (DISTANT_LIGHT_COUNT > 7)
	distant_light( surface, color, DistantLights[7], eye_vector, d, s); lighting.diffuse += d; lighting.specular += s;
#endif
#if (DISTANT_LIGHT_COUNT > 8)
	distant_light( surface, color, DistantLights[8], eye_vector, d, s); lighting.diffuse += d; lighting.specular += s;
#endif
#if (DISTANT_LIGHT_COUNT > 9)
	distant_light( surface, color, DistantLights[9], eye_vector, d, s); lighting.diffuse += d; lighting.specular += s;
#endif
#if (DISTANT_LIGHT_COUNT > 10)
	distant_light( surface, color, DistantLights[10], eye_vector, d, s); lighting.diffuse += d; lighting.specular += s;
#endif
#if (DISTANT_LIGHT_COUNT > 11)
	distant_light( surface, color, DistantLights[11], eye_vector, d, s); lighting.diffuse += d; lighting.specular += s;
#endif
#if (DISTANT_LIGHT_COUNT > 12)
	distant_light( surface, color, DistantLights[12], eye_vector, d, s); lighting.diffuse += d; lighting.specular += s;
#endif
#if (DISTANT_LIGHT_COUNT > 13)
	distant_light( surface, color, DistantLights[13], eye_vector, d, s); lighting.diffuse += d; lighting.specular += s;
#endif
#if (DISTANT_LIGHT_COUNT > 14)
	distant_light( surface, color, DistantLights[14], eye_vector, d, s); lighting.diffuse += d; lighting.specular += s;
#endif
#if (DISTANT_LIGHT_COUNT > 15)
	distant_light( surface, color, DistantLights[15], eye_vector, d, s); lighting.diffuse += d; lighting.specular += s;
#endif

#if (POINT_LIGHT_COUNT > 0)
	// Factor in point lights
	for( int i = 0; i < POINT_LIGHT_COUNT; i++)
	{
		point_light( surface, color, PointLights[i], eye_vector, d, s);
		lighting.diffuse += d;
		lighting.specular += s;
	}
#endif // POINT_LIGHT_COUNT > 0

#if (SPOT_LIGHT_COUNT > 0)
	// Factor in spot lights
	for( int i = 0; i < SPOT_LIGHT_COUNT; i++)
	{
		spot_light( surface, color, SpotLights[i], eye_vector, d, s);
		lighting.diffuse += d;
		lighting.specular += s;
	}
#endif // SPOT_LIGHT_COUNT > 0
}

#endif // LIGHTING

/* 
 * vertex_results
 * Output to triangle setup 
 *
 *
 * NOTE THAT IF ANYTHING IS ADDED TO THIS STRUCTURE OPENGL2 WILL BREAK UNLESS
 * THE CODE TO COPY VALUES TO/FROM THE OPENGL INTRINSICS (see ogl2_vertex.hlsl and ogl2_pixel.hlsl)
 *
 */
#ifndef CREATE_SHADOW_MAP
struct vertex_results
{
	/* Transformed vertex position */
	float4 position semantic(POSITION);

	/* Material color for interpolation */
	float4 material_color_and_specular_intensity semantic(COLOR0);
	
	#ifdef EYE_POSITION_COORD
		float4 eye_position semantic(EYE_POSITION_COORD_OUT);
	#endif
	
	#ifdef PER_PIXEL_LIGHTING
		float3 eye_normal semantic(COLOR1);
	#else
		#ifdef HAS_LIGHTING
		/* Light colors for interpolation */
		float4 diffuse_light_and_ambient_blend semantic(COLOR1);
		#endif // HAS_LIGHTING
	#endif // PER_PIXEL_LIGHTING

	#ifdef TANGENT_COORD	
		float4 eye_tangent semantic(TANGENT_COORD_OUT);
	#endif
			
	#ifdef HAS_ATMOSPHERIC_ATTENUATION
		float fog semantic(FOG);
	#endif
	
	#ifdef HAS_VERTEX_FINDICES
		float2 findex semantic(FINDEX_COORD_OUT);
	#endif

	#if defined(WIDE_LINE) || defined(ANTI_ALIASED_LINE)
		float3 wide_line_offset semantic(OFFSET_COORD_OUT);
	#endif

	#if defined(HAS_DEFINED_MATERIAL_SHADER) || defined(HAS_TEXTURE3D)
		float4 uvst0 semantic(DIFFUSE_TEXTURE_INTERPOLATOR0_OUT);
	#endif
		
	#if (TEXTURE_COUNT > 0) && !defined(HAS_DEFINED_MATERIAL_SHADER) && !defined(HAS_TEXTURE3D)
		/* Diffuse texture coordinates */
		float2 uv0 semantic(DIFFUSE_TEXTURE_INTERPOLATOR0_OUT);
	#endif
	#ifndef SHARED_DIFFUSE_COORDS
		#if (TEXTURE_COUNT > 1)
			float2 uv1 semantic(DIFFUSE_TEXTURE_COORD1_OUT);
		#endif
		#if (TEXTURE_COUNT > 2) 
			float2 uv2 semantic(DIFFUSE_TEXTURE_COORD2_OUT);
		#endif
		#if (TEXTURE_COUNT > 3) 
			float2 uv3 semantic(DIFFUSE_TEXTURE_COORD3_OUT);
		#endif
		#if (TEXTURE_COUNT > 4) 
			float2 uv4 semantic(DIFFUSE_TEXTURE_COORD4_OUT);
		#endif
		#if (TEXTURE_COUNT > 5) 
			float2 uv5 semantic(DIFFUSE_TEXTURE_COORD5_OUT);
		#endif
		#if (TEXTURE_COUNT > 6) 
			float2 uv6 semantic(DIFFUSE_TEXTURE_COORD6_OUT);
		#endif
		#if (TEXTURE_COUNT > 7) 
			float2 uv7 semantic(DIFFUSE_TEXTURE_COORD7_OUT);
		#endif
	#endif

	#if (BACK_TEXTURE_COUNT > 0) && !defined(HAS_DEFINED_MATERIAL_SHADER) && !defined(HAS_TEXTURE3D)
		/* Diffuse texture coordinates */
		float2 buv0 semantic(BACK_DIFFUSE_TEXTURE_INTERPOLATOR0_OUT);
	#endif
	#if (BACK_TEXTURE_COUNT > 1)
		float2 buv1 semantic(BACK_DIFFUSE_TEXTURE_COORD1_OUT);
	#endif
	#if (BACK_TEXTURE_COUNT > 2) 
		float2 buv2 semantic(BACK_DIFFUSE_TEXTURE_COORD2_OUT);
	#endif
	#if (BACK_TEXTURE_COUNT > 3) 
		float2 buv3 semantic(BACK_DIFFUSE_TEXTURE_COORD3_OUT);
	#endif
	#if (BACK_TEXTURE_COUNT > 4) 
		float2 buv4 semantic(BACK_DIFFUSE_TEXTURE_COORD4_OUT);
	#endif
	#if (BACK_TEXTURE_COUNT > 5) 
		float2 buv5 semantic(BACK_DIFFUSE_TEXTURE_COORD5_OUT);
	#endif
	#if (BACK_TEXTURE_COUNT > 6) 
		float2 buv6 semantic(BACK_DIFFUSE_TEXTURE_COORD6_OUT);
	#endif
	#if (BACK_TEXTURE_COUNT > 7) 
		float2 buv7 semantic(BACK_DIFFUSE_TEXTURE_COORD7_OUT);
	#endif
	
	#if defined(CIRCLE_MARKER) || defined(TEXTURE_MARKER) || defined(MATERIAL_SHADER_MARKER)
		float2 marker_uv semantic(MARKER_TEXTURE_OUT);
	#endif
	
	#ifdef SPRITE_MARKER
		float marker_size semantic(PSIZE);
	#endif
	
	#if (SHADOW_MAP_COUNT > 0)
		/* cutting planes */
		float4 uvsm0 semantic(SHADOW_MAP_COORD0_OUT);	
	#if defined(SHADOW_MAP_JITTER) || defined(SHADOW_MAP_SLICE_COUNT)
		float4 screen_position semantic(SHADOW_MAP_JITTER_COORD_OUT);
	#endif
	#endif
	#if (SHADOW_MAP_COUNT > 1)
		float4 uvsm1 semantic(SHADOW_MAP_COORD1_OUT);
	#endif
	#if (SHADOW_MAP_COUNT > 2)
		float4 uvsm2 semantic(SHADOW_MAP_COORD2_OUT);
	#endif
	#if (SHADOW_MAP_COUNT > 3)
		float4 uvsm3 semantic(SHADOW_MAP_COORD3_OUT);
	#endif

	#if (CUTTING_PLANE_COUNT > 0)
		/* cutting planes */
		float4 uvcp0 semantic(CUTTING_PLANE_COORD0_OUT);
	#endif
	#if (CUTTING_PLANE_COUNT > 4)
		float4 uvcp1 semantic(CUTTING_PLANE_COORD1_OUT);
	#endif
	#if (CUTTING_PLANE_COUNT > 8)
		float4 uvcp2 semantic(CUTTING_PLANE_COORD2_OUT);
	#endif
	#if (CUTTING_PLANE_COUNT > 12)
		float4 uvcp3 semantic(CUTTING_PLANE_COORD3_OUT);
	#endif

	#ifdef ENVIRONMENT_TEXTURE 
		#if !defined(CUBE_ENVIRONMENT_MAP) || !defined(PER_PIXEL_LIGHTING)
			/* special textures */
			float3 uvenv semantic(ENVIRONMENT_TEXTURE_OUT);
		#endif
	#endif

	#ifdef MIRROR_TEXTURE
		float2 uvmirror semantic(MIRROR_TEXTURE_OUT);
	#endif

	#ifdef SPECULAR_TEXTURE
		/* special textures */
		float2 uvspec semantic(SPECULAR_TEXTURE_OUT);
	#endif
	
	#ifdef BUMP_TEXTURE
		float2 uvbump semantic(BUMP_TEXTURE_OUT);
	#endif 

	#ifdef TRANSMISSION_TEXTURE
		float2 uvtransmission semantic(TRANSMISSION_TEXTURE_OUT);
	#endif

	#ifdef EMISSION_TEXTURE
		float2 uvemission semantic(EMISSION_TEXTURE_OUT);
	#endif

	#if defined(DEPTH_PEELING) || defined(DEPTH_WRITING)
		/* Position as texcoords for depth peeling */
		float4 peel_position semantic(DEPTH_PEELING_POSITION_COORD_OUT);
	#endif

	#ifdef HAS_FACE_PATTERN
		float4 uvzwfp semantic(FACE_PATTERN_COORD_OUT);
	#endif

	#ifdef HAS_LINE_PATTERN
		float4 uvlp semantic(LINE_PATTERN_COORD_OUT);
	#endif
};
#else // CREATE_SHADOW_MAP
struct vertex_results
{
	/* Transformed vertex position */
	float4 position semantic(POSITION);
	/* Position as texcoords for shadow mapping. */
	float4 shadow_position semantic(TEXCOORD4);

	#if defined(WIDE_LINE) || defined(ANTI_ALIASED_LINE)
		float3 wide_line_offset semantic(OFFSET_COORD_OUT);
	#endif

#if defined(CIRCLE_MARKER) || defined(TEXTURE_MARKER) || defined(MATERIAL_SHADER_MARKER)
	float2 marker_uv semantic(MARKER_INTERPOLATOR_OUT);
#endif
};
#endif // ndef CREATE_SHADOW_MAP

