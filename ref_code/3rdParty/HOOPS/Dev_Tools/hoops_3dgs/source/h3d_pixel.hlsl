// Copyright (c) 2007 by Tech Soft 3D, LLC.
// all rights reserved
// $Id: h3d_pixel.hlsl,v 1.142 2010-11-22 23:48:59 warren Exp $

/* Uniforms ******************************************************************/
uniform int FrontDiffuseTextureEnable;

#ifdef HAS_VERTEX_FINDICES
uniform sampler IndexSampler reg(FINDEX_REGISTER);
#endif

#if defined(ROUND_LINE) || defined(ANTI_ALIASED_LINE)
uniform sampler LineToolsSampler reg(LINE_TOOLS_REGISTER);
#endif

#if (TEXTURE_COUNT > 0) && !defined(HAS_DEFINED_MATERIAL_SHADER)
	#ifdef HAS_TEXTURE3D
uniform sampler3D DiffuseSampler0 reg(DIFFUSE_TEXTURE0_REGISTER);
	#else
uniform sampler DiffuseSampler0 reg(DIFFUSE_TEXTURE0_REGISTER);
	#endif
#endif

// Diffuse samplers 1-4 located in h3d_material.hlsl

#if (TEXTURE_COUNT > 5)
uniform sampler DiffuseSampler5 reg(DIFFUSE_TEXTURE5_REGISTER);
#endif

#if (TEXTURE_COUNT > 6)
uniform sampler DiffuseSampler6 reg(DIFFUSE_TEXTURE6_REGISTER);
#endif

#if (TEXTURE_COUNT > 7)
uniform sampler DiffuseSampler7 reg(DIFFUSE_TEXTURE7_REGISTER);
#endif

#if (BACK_TEXTURE_COUNT > 0) && !defined(HAS_DEFINED_MATERIAL_SHADER) && !defined(HAS_TEXTURE3D)
uniform sampler BackDiffuseSampler0 reg(BACK_DIFFUSE_TEXTURE0_REGISTER);
#endif

#if (BACK_TEXTURE_COUNT > 1)
uniform sampler BackDiffuseSampler1 reg(BACK_DIFFUSE_TEXTURE1_REGISTER);
#endif

#if (BACK_TEXTURE_COUNT > 2)
uniform sampler BackDiffuseSampler2 reg(BACK_DIFFUSE_TEXTURE2_REGISTER);
#endif

#if (BACK_TEXTURE_COUNT > 3)
uniform sampler BackDiffuseSampler3 reg(BACK_DIFFUSE_TEXTURE3_REGISTER);
#endif

#if (BACK_TEXTURE_COUNT > 4)
uniform sampler BackDiffuseSampler4 reg(BACK_DIFFUSE_TEXTURE4_REGISTER);
#endif

#if (BACK_TEXTURE_COUNT > 5)
uniform sampler BackDiffuseSampler5 reg(BACK_DIFFUSE_TEXTURE5_REGISTER);
#endif

#if (BACK_TEXTURE_COUNT > 6)
uniform sampler BackDiffuseSampler6 reg(BACK_DIFFUSE_TEXTURE6_REGISTER);
#endif

#if (BACK_TEXTURE_COUNT > 7)
uniform sampler BackDiffuseSampler7 reg(BACK_DIFFUSE_TEXTURE7_REGISTER);
#endif

#ifdef TEXTURE_MARKER
uniform float MarkerSamplerBias;
uniform sampler MarkerSampler reg(MARKER_TEXTURE_REGISTER);
#endif

uniform float3 ModulationColor0;
uniform float3 ModulationColor1;
uniform float3 ModulationColor2;
uniform float3 ModulationColor3;
uniform float3 ModulationColor4;
uniform float3 ModulationColor5;
uniform float3 ModulationColor6;
uniform float3 ModulationColor7;


#ifdef SPECULAR_TEXTURE_REGISTER
uniform sampler SpecularSampler reg(SPECULAR_TEXTURE_REGISTER);
#endif

#ifdef BUMP_TEXTURE_REGISTER
uniform sampler BumpSampler reg(BUMP_TEXTURE_REGISTER);
#endif

#ifdef TRANSMISSION_TEXTURE_REGISTER
uniform sampler TransmissionSampler reg(TRANSMISSION_TEXTURE_REGISTER);

	#ifdef TRANSMISSION_TEXTURE_MODULATE
		uniform float3 TransmissionModulateColor;
	#endif
#endif

#ifdef EMISSION_TEXTURE_REGISTER
uniform sampler EmissionSampler reg(EMISSION_TEXTURE_REGISTER);
#endif

#ifdef HAS_FACE_PATTERN
uniform sampler FacePatternSampler reg(FACE_PATTERN_REGISTER);
uniform float4 FaceContrastColor;
#endif

#ifdef HAS_LINE_PATTERN
uniform sampler LinePatternSampler reg(LINE_PATTERN_REGISTER);
uniform float4 LineContrastColor;
#endif

#ifdef ENVIRONMENT_TEXTURE_REGISTER
#ifdef CUBE_ENVIRONMENT_MAP
uniform samplerCube EnvironmentSampler reg(ENVIRONMENT_TEXTURE_REGISTER);
#else
uniform sampler EnvironmentSampler reg(ENVIRONMENT_TEXTURE_REGISTER);
#endif
#endif

#ifdef MIRROR_TEXTURE_REGISTER
uniform sampler MirrorSampler reg(MIRROR_TEXTURE_REGISTER);
#endif

#ifdef DEPTH_PEELING
#undef WRITE_LUMINANCE
uniform sampler DepthPeelingTexture reg(DEPTH_PEELING_TEXTURE_REGISTER);
uniform float4 DepthPeelingScaleAndBias;

/* Viewport transform for depth peeling texture */
uniform float4 viewport_scale_and_bias;
#endif // DEPTH_PEELING

#if (SHADOW_MAP_COUNT > 0)
uniform sampler ShadowMapTexture0 reg(SHADOW_MAP_TEXTURE0_REGISTER);
#ifdef SHADOW_MAP_JITTER
uniform float4 JitterScaleAndBias;
/* And for shadow jitter table */
uniform sampler ShadowMapJitterSampler reg(SHADOW_MAP_JITTER_REGISTER);
#endif // SHADOW_MAP_JITTER
#ifdef SHADOW_MAP_0_VIEW_DEPENDENT
uniform float3 SliceScales0[SHADOW_MAP_SLICE_COUNT];
uniform float3 SliceBiases0[SHADOW_MAP_SLICE_COUNT];
#endif // SHADOW_MAP_0_VIEW_DEPENDENT
#endif // SHADOW_MAP_COUNT > 0
#if (SHADOW_MAP_COUNT > 1)
uniform sampler ShadowMapTexture1 reg(SHADOW_MAP_TEXTURE1_REGISTER);
#ifdef SHADOW_MAP_1_VIEW_DEPENDENT
uniform float3 SliceScales1[SHADOW_MAP_SLICE_COUNT];
uniform float3 SliceBiases1[SHADOW_MAP_SLICE_COUNT];
#endif // SHADOW_MAP_1_VIEW_DEPENDENT
#endif // SHADOW_MAP_COUNT > 1
#if (SHADOW_MAP_COUNT > 2)
uniform sampler ShadowMapTexture2 reg(SHADOW_MAP_TEXTURE2_REGISTER);
#ifdef SHADOW_MAP_2_VIEW_DEPENDENT
uniform float3 SliceScales2[SHADOW_MAP_SLICE_COUNT];
uniform float3 SliceBiases2[SHADOW_MAP_SLICE_COUNT];
#endif // SHADOW_MAP_2_VIEW_DEPENDENT
#endif // SHADOW_MAP_COUNT > 2
#if (SHADOW_MAP_COUNT > 3)
uniform sampler ShadowMapTexture3 reg(SHADOW_MAP_TEXTURE3_REGISTER);
#ifdef SHADOW_MAP_3_VIEW_DEPENDENT
uniform float3 SliceScales3[SHADOW_MAP_SLICE_COUNT];
uniform float3 SliceBiases3[SHADOW_MAP_SLICE_COUNT];
#endif // SHADOW_MAP_3_VIEW_DEPENDENT
#endif // SHADOW_MAP_COUNT > 3

uniform float3 Mirror;

#ifdef HAS_LIGHTING

/* Ambient lighting - always provided per-pixel */
uniform float3 AmbientLightUp;
uniform float3 AmbientLightDown;

#ifdef PER_PIXEL_LIGHTING
// Per-pixel ambient
uniform float3 AmbientLightDir;
#else
// Per-vertex specular
uniform float3 SpecularTint;
#endif // ndef PER_PIXEL_LIGHTING

/* Emissive lighting - always provided per-pixel */
uniform float3 EmissiveLight;

#endif

/* Material properties */
uniform HColor MaterialColor;

#ifdef GOOCH
/* Gooch colour ramp (cool to warm) in here */
uniform sampler GoochSampler reg(GOOCH_TEXTURE_REGISTER);

/* Weights for diffuse material colour and Gooch ramp. */
uniform float4 GoochWeights;
#endif // GOOCH

/* Reflection plane data */
uniform reflection_plane_t ReflectionPlane;

// If we're using shader model 3, we need to support fog manually in the shader.
#if defined(SHADER_MUST_FOG) && defined(HAS_ATMOSPHERIC_ATTENUATION)
uniform float3 AtmosphericAttenuationColor;
#endif

// Output scale for frustum depth.
uniform float DepthWriteScale;

/* Code **********************************************************************/

// Pack a float value for output to RGBA8 texture.
float4 pack_rgba(float value)
{
#define RADIX 255.0
	const float4 shift = float4(1.0, RADIX, RADIX*RADIX,  RADIX*RADIX*RADIX); 
	const float4 mask = float4(1.0/RADIX, 1.0/RADIX, 1.0/RADIX, 0.0);
	
	if ( value == 1.0 )
		return float4(1.0, 0.0, 0.0, 0.0);

	float4 rgba;
	
#ifdef FULL_ENCODE
	// Encode magnitude as well
	float exponent;
	float mantissa = frexp(value, exponent);
	
	// Encode exponent
	rgba.w = (exponent + 128) / RADIX;
	
	// Encode mantissa using remaining 24 bits. No sign yet.
	rgba.xyz = frac(mantissa * shift.xyz);
	rgba.xy -= mask.x * rgba.yz;
	
#else
	// Encode in [0, 1]
	rgba = frac(value * shift);
	rgba.xyz -= mask.x * rgba.yzw;
#endif
	
	return rgba;
}

/// Unpacking a [0-1] float value from a 4D vector where each component was a 8-bits integer
float unpack_rgba(const float4 value)
{
	// Reconstruct by mutliplying each range by the remainder and add up.
	const float4 shift = float4(1.0, 1.0/RADIX, 1.0/(RADIX*RADIX),  1.0/(RADIX*RADIX*RADIX)); 
	
#ifdef FULL_ENCODE
	// Decode mantissa
	float mantissa = dot(value.xyz, shift.xyz);
	
	// Decode exponent
	float exponent = value.w * RADIX - 128;
	
	// Assemble
	return ldexp(mantissa, exponent);
#else
	return dot(value, shift);
#endif
#undef RADIX
}

#if (SHADOW_MAP_COUNT > 0)

#ifdef SHADOW_MAP_SLICE_COUNT

//float4 get_shadowmap_slice( float4 uv, float screen_z, float3 scales[SHADOW_MAP_SLICE_COUNT], float3 biases[SHADOW_MAP_SLICE_COUNT] )
#define get_shadowmap_slice( uv, screen_z, scales, biases) \
{ \
	float2 cascade_uv; \
	 \
	if ( screen_z < biases[0].z ) \
		cascade_uv = uv.xy * scales[0].xy + biases[0].xy; \
	else if ( screen_z < biases[1].z ) \
		cascade_uv = uv.xy * scales[1].xy + biases[1].xy; \
	else if ( screen_z < biases[2].z ) \
		cascade_uv = uv.xy * scales[2].xy + biases[2].xy; \
	else \
		cascade_uv = uv.xy * scales[3].xy + biases[3].xy; \
	\
	uv = float4(cascade_uv.xy, uv.zw); \
}

#endif // ndef SHADOW_MAP_SLICE_COUNT

// Abstract packed vs. unpacked sampling.
float read_shadowmap(sampler2D shadow, float4 uv)
{
#ifdef SHADOW_MAP_RGBA
	return unpack_rgba(tex2D(shadow, uv.xy));
#else
	return tex2D(shadow, uv.xy).x;
#endif
}


#define ACCUMULATE_SAMPLES(which) \
	{\
		uv = position_xyxy;\
#ifdef SHADOW_MAP_JITTER \
		/* Rotate two sample locations by 2x2 jitter matrix and offset uv.*/ \
		uv += jitter_adad * pcf_taps[which * 2].xyzw;\
		uv += jitter_bcbc * pcf_taps[which * 2].yxwz;\
#else \
		/* Just offset uv directly. */ \
		uv += pcf_taps[which * 2]; \
#endif /* SHADOW_MAP_JITTER */ \
 \
		/* Take first two samples */ \
		results.x = read_shadowmap(shadowmap, float4(uv.xy,position.zw)); \
		results.y = read_shadowmap(shadowmap, float4(uv.zw,position.zw)); \
 \
		uv = position_xyxy; \
#ifdef SHADOW_MAP_JITTER \
		/* Rotate second two sample points and offset uv */ \
		uv += jitter_adad * pcf_taps[which * 2 + 1].xyzw; \
		uv += jitter_bcbc * pcf_taps[which * 2 + 1].yxwz; \
#else \
		/* Just offset uv directly. */ \
		uv += pcf_taps[which * 2 + 1]; \
#endif \
		 \
		/* Take second two samples */ \
		results.z = read_shadowmap(shadowmap, float4(uv.xy,position.zw)); \
		results.w = read_shadowmap(shadowmap, float4(uv.zw,position.zw)); \
		 \
#ifndef DEPTH_TEXTURE_HARDWARE \
		/* Do tests */ \
		/* This would be ideal: results = float4(position.z < results); */ \
		/* but the DX9 compiler must optimise the below correctly anyway.*/ \
		results.x = (position.z < results.x) ? 1.0 : 0.0; \
		results.y = (position.z < results.y) ? 1.0 : 0.0; \
		results.z = (position.z < results.z) ? 1.0 : 0.0; \
		results.w = (position.z < results.w) ? 1.0 : 0.0; \
#endif \
 \
		/* Sum results  */ \
		accumulator += results; \
	}

/**
 * Perform shadowmap test and return suitable values to knockout the diffuse
 * (in X) and specular (in Y) lighting contributions.
 */
float get_shadowmap_illumination( float4 jitter, float4 position, sampler2D shadowmap )
{
	float result;
	
	// Divide by W for perspective lights
	position /= position.w;

#ifndef SHADOW_MAP_SAMPLES

#ifdef SHADOW_MAP_JITTER
	// Offset by jitter vector
	position.xy += jitter.xy / SHADOW_MAP_SIZE;
#endif

	// Read sample
	result = read_shadowmap(shadowmap, position);
		
#ifndef DEPTH_TEXTURE_HARDWARE
	// Do test
	result = (position.z < result) ? 1.0 : 0.0;
#endif

#else

	//
	// Multiple samples in batches of four, vectorised.
	//

	// Temps
	float4 uv;
	float4 results;
	float4 accumulator = float4(0.0,0.0,0.0,0.0);
	
	// Weight each sample by 1/num samples
	const float weight = 1.0/SHADOW_MAP_SAMPLESF;
	const float4 weights = float4(weight, weight, weight, weight);
	
	// Hoisting these swizzles seems to help the compiler generate vector rather than scalar code.
	float4 position_xyxy = position.xyxy;
	float4 jitter_adad = jitter.xwxw;
	float4 jitter_bcbc = jitter.yzyz;
	
#if (SHADOW_MAP_SAMPLES > 0)
	ACCUMULATE_SAMPLES(0);
#endif
#if (SHADOW_MAP_SAMPLES > 4)
	ACCUMULATE_SAMPLES(1);
#endif
#if (SHADOW_MAP_SAMPLES > 8)
	ACCUMULATE_SAMPLES(2);
#endif
#if (SHADOW_MAP_SAMPLES > 12)
	ACCUMULATE_SAMPLES(3);
#endif
	
	// Normalise
	result = dot(accumulator, weights);
	
#endif // def SHADOW_MAP_SAMPLES
	
	// Done
	return result;
}

#ifdef BLACK_SHADOWS
// Full-strength shadow
#define APPLY_SHADOW(dest, illum) ((dest) *= (illum))
#else
// Half-strength shadow
#define APPLY_SHADOW(dest, illum) ((dest) *= 0.5 + 0.5 * (illum))
#endif

void shadowed_direct_lighting( const HColor color, 
							   const float4 jitter,
							   const float4 shadow_map_uv[SHADOW_MAP_COUNT],
							   const HSurface surface,
							   inout HLighting lighting )
{
	// Temporaries
	float3 d, s;
	
	// Compute this once
	float3 eye_vector = normalize(EyeCameraPosition -surface.position);
	
#if (DISTANT_LIGHT_COUNT > 0)
	// Accumulate lighting from first four (optionally shadowed) distant lights
	SHADOWED_DISTANT_LIGHT0(jitter, surface, color, eye_vector, lighting)
	SHADOWED_DISTANT_LIGHT1(jitter, surface, color, eye_vector, lighting)
	SHADOWED_DISTANT_LIGHT2(jitter, surface, color, eye_vector, lighting)
	SHADOWED_DISTANT_LIGHT3(jitter, surface, color, eye_vector, lighting)
	
	// Accumulate any remaining lights (unshadowed)
	for ( int i = 4; i < DISTANT_LIGHT_COUNT; ++i )
	{
		distant_light(surface, color, DistantLights[i], eye_vector, d, s);
		lighting.diffuse += d;
		lighting.specular += s;
	}
#endif
				
#if (POINT_LIGHT_COUNT > 0)
	// Factor in point lights
	for ( int i = 0; i < POINT_LIGHT_COUNT; i++)
	{
		point_light(surface, color, PointLights[i], eye_vector, d, s);
		lighting.diffuse += d;
		lighting.specular += s;
	}
#endif // POINT_LIGHT_COUNT > 0

#if (SPOT_LIGHT_COUNT > 0)
	// Accumulate lighting from first four (optionally shadowed) spot lights
	SHADOWED_SPOT_LIGHT0(jitter, surface, color, eye_vector, lighting)
	SHADOWED_SPOT_LIGHT1(jitter, surface, color, eye_vector, lighting)
	SHADOWED_SPOT_LIGHT2(jitter, surface, color, eye_vector, lighting)
	SHADOWED_SPOT_LIGHT3(jitter, surface, color, eye_vector, lighting)

	// Accumulate any remaining lights
	for ( int i = 4; i < SPOT_LIGHT_COUNT; i++)
	{
		spot_light(surface, color, SpotLights[i], eye_vector, d, s);
		lighting.diffuse += d;
		lighting.specular += s;
	}
#endif // SPOT_LIGHT_COUNT > 0
}

#endif // (SHADOW_MAP_COUNT > 0)

#ifdef PER_PIXEL_LIGHTING

float3 fix_normal_handedness( float3 normal, float face )
{
#if defined(SHADER_MODEL_3) && defined(HAS_HANDEDNESS) && defined(TRIANGLE)
	// Exact normal fix using face register.
	normal *= NORMAL_FLIP_SIGN * sign(face);
	#ifdef RIGHT_HANDED_MATRIX
		normal = -normal;
	#endif
#else	
	// Less accurate fix
	#ifdef HAS_HANDEDNESS
		#ifdef RIGHT_HANDED_MATRIX
			normal = -normal;
		#endif
	#else
		if(normal.z > 0.0)
			normal = -normal;
	#endif
#endif 
	normal *= DRIVER_SPECIFIC_FLIP;
	return normal;
}

void reconstruct_surface(const vertex_results vertex, float face, inout HSurface surface)
{
	// Reconstruct interpolated normal
	surface.normal = normalize(vertex.eye_normal.xyz * 2.0 - 1.0);

	// Fixup any flipped normals using the face register if possible
	surface.normal = fix_normal_handedness( surface.normal, face );

	#ifdef TANGENT_COORD
		// Construct tangent frame
		surface.tangent = normalize(vertex.eye_tangent.xyz * 2.0 - 1.0);
		surface.bitangent = normalize(cross(surface.normal, surface.tangent)) * vertex.eye_tangent.w ;
		
		// Fixup tangent vector - driver coordinate spaces have different handedness.
		surface.tangent *= DRIVER_SPECIFIC_FLIP;
	#endif
	
	#ifdef EYE_POSITION_COORD
		// Use real eye position
		surface.position = vertex.eye_position.xyz;
	#endif // EYE_POSITION_COORD
}		

void apply_bump(const vertex_results vertex, inout HSurface surface)
{
#ifdef BUMP_TEXTURE
	// Sample and unpack normal map
	float3 map_normal = tex2D(BumpSampler, vertex.uvbump).xyz * 2.0 - 1.0;
	h3d_normal_map(map_normal, surface);
#endif // BUMP_TEXTURE
}

#endif // PER_PIXEL_LIGHTING

void apply_gooch(const HLighting lighting, inout float3 lit_color)
{
#ifdef GOOCH
	// Diffuse light is monochrome in Gooch mode
	float diffuse_intensity = saturate(0.5 + 0.5 * lighting.diffuse.r);
		
	// 	Look up Gooch shading colour from table.
	float gooch_coord = GoochWeights.x * diffuse_intensity + GoochWeights.y;
	float3 gooch_color = tex2D(GoochSampler, float2(gooch_coord,0.0)).rgb;
		
	// Blend with diffuse-lit material before adding specular below.
	lit_color = lerp( gooch_color, lit_color, GoochWeights.z );
#endif // GOOCH
}

void apply_mirror( const vertex_results vertex, inout HEffects effects )
{
#ifdef ENVIRONMENT_TEXTURE
	effects.mirror = Mirror;
#ifdef MIRROR_TEXTURE_REGISTER
	effects.mirror *= tex2D(MirrorSampler, vertex.uvmirror).xyz;
#endif
#endif
}

void apply_environment( const vertex_results vertex, const HSurface surface, inout HEffects effects )
{
#ifdef ENVIRONMENT_TEXTURE
	// Compute environment map UVs	
	float3 uvenv;
#if defined(PER_PIXEL_LIGHTING) && defined(CUBE_ENVIRONMENT_MAP)
	// Reflect per pixel
	#ifdef HAS_PHYSICAL_REFLECTION
		// Reflect in object space
		uvenv = reflect(normalize(surface.position), surface.normal);

		// Fixup direction into cube map
		uvenv = uvenv.zyx;
		uvenv.x *= -DRIVER_SPECIFIC_FLIP;
	#else
		// Fixup normal
		uvenv = reflect(float3(0,0,1), surface.normal);
		
		// Fixup direction
		uvenv.xy *= DRIVER_SPECIFIC_FLIP;
	#endif
#else
	// Load per-vertex reflection
	uvenv = vertex.uvenv.xyz;	
#endif
	
	// Sample environment
#ifdef CUBE_ENVIRONMENT_MAP
	effects.environment = texCUBE(EnvironmentSampler, uvenv).rgb;
#else
	effects.environment = tex2D(EnvironmentSampler, uvenv.xy).rgb;
#endif
#endif // ENVIRONMENT_TEXTURE
}

void apply_luminance( const HLighting lighting, inout HEffects effects )
{
#ifdef WRITE_LUMINANCE
	// For lit opaque pixels, write glow value to dest alpha. Constrain range.
	effects.luminance += 0.5*rgb_to_gray(lighting.emissive);
	
	// Output full range of specular to activate stars.
	effects.luminance += rgb_to_gray(lighting.specular);

	// Use upper half of texture as luminance key, and then square for sharper results.
	float tex_luminance = saturate(2.0 * rgb_to_gray(effects.environment.rgb) - 1.0);
	effects.luminance += tex_luminance*tex_luminance;
#endif
}

#ifdef DEPTH_PEELING

#ifdef DEPTH_PACKING_RGBA
// MSAA bias constant - discarding half the pixels means we need more bias at polygon edges
// Non-MSAA RGBA encoded depth could really use the below bias.
#define DEPTH_PEELING_BIAS 0.0001
#else
// Standard bias constant
#define DEPTH_PEELING_BIAS 0.000001
#endif

#endif // DEPTH_PEELING


#ifdef MUST_DEFINE_CLIP_FUNC
// Compatibility functions (ATI has warnings if it sees "discard" in vertex shader)
void clip(float x)
{
	if (x < 0.0)
		discard;
}
void clip(vec2 x) 
{
	bvec2 result = lessThan(x, float2(0.0,0.0));
	if (any(result))
		discard;
}
void clip(vec3 x) 
{
	bvec3 result = lessThan(x, float3(0.0,0.0,0.0));
	if (any(result))
		discard;
}
void clip(vec4 x) 
{
	bvec4 result = lessThan(x, float4(0.0,0.0,0.0,0.0));
	if (any(result))
		discard;
}
#endif

void apply_line_styles(const vertex_results vertex, inout HColor color)
{
#if defined(ROUND_LINE) || defined(ANTI_ALIASED_LINE)
	float alpha = tex2D(LineToolsSampler, vertex.wide_line_offset.xy).a;
	#ifndef ANTI_ALIASED_LINE
		if (vertex.wide_line_offset.z > H3D_ROUND - 0.0001 && 
			vertex.wide_line_offset.z < H3D_ROUND + 0.0001) {
			if(alpha < 0.5)
				discard;
		}
	#else
		color.diffuse.a *= alpha;
	#endif
#endif
}

#endif

void apply_vertex_findices(const vertex_results vertex, inout HColor color)
{
#ifdef HAS_VERTEX_FINDICES
	float4 tex_color = tex2D(IndexSampler, vertex.findex.xy);
	color.diffuse = tex_color * float4(1.0, 1.0, 1.0, color.diffuse.a);
#endif
}

void apply_face_pattern(const vertex_results vertex, inout HColor color)
{
#ifdef HAS_FACE_PATTERN
	float4 uvzwfp = vertex.uvzwfp;
	#ifdef CAMERA_PERSPECTIVE	
		uvzwfp.xy /= uvzwfp.w;
		#ifdef DX9
			float texel_offset;
			#ifdef HAS_TRANSPARENCY_STIPPLE
				texel_offset = 0.5/16.0;
			#else
				texel_offset = 0.5/32.0;
			#endif
			uvzwfp.xy += texel_offset;
		#endif
	#endif
	
	float4 tex_color = tex2D(FacePatternSampler, uvzwfp.xy);

	#ifdef HAS_TRANSPARENCY_STIPPLE
		if(tex_color.a > 0.0)
			discard;
	#else
		if(tex_color.a < 1.0)
			color.diffuse = FaceContrastColor;
	#endif
#endif // HAS_FACE_PATTERN
}

void apply_line_pattern(const vertex_results vertex, inout HColor color)
{
#ifdef HAS_LINE_PATTERN
	float4 tex_color = tex2D(LinePatternSampler, vertex.uvlp.xy);

	if(tex_color.a < 1.0)
		discard;
#endif // HAS_LINE_PATTERN	
}

void apply_multitexture(const vertex_results vertex, inout HColor color)
{
#if !defined(HAS_DEFINED_MATERIAL_SHADER) || defined(DEFINED_MATERIAL_MULTITEXTURE)

	// Start
	float4 material_color = color.diffuse;
	float4 final_color = color.diffuse;
	float4 tex_color = float4(0.0,0.0,0.0,0.0);
	float4 new_color = float4(0.0,0.0,0.0,0.0);

	#if (TEXTURE_COUNT > 0) && !defined(HAS_DEFINED_MATERIAL_SHADER)
		// Factor in the diffuse texture specular_color
		// Deal with Texture Unit 0
		if (FrontDiffuseTextureEnable == 1) {
			#ifdef HAS_TEXTURE3D
				tex_color = tex3D(DiffuseSampler0, vertex.uvst0.xyz); //float4 (vertex.uvst0.xyz, 1); //
			#else
				tex_color = tex2D(DiffuseSampler0, vertex.uv0.xy);
			#endif
				
			#ifdef TEXTURE0_COLOR
				tex_color *= float4(ModulationColor0,1);
			#endif

			#ifdef TEXTURE0_DROP
				if (vertex.uv0.x < 0.0 || vertex.uv0.x > 1.0 ||
					vertex.uv0.y < 0.0 || vertex.uv0.y > 1.0)
				tex_color = float4(0.0, 0.0, 0.0, 0.0);
			#endif
			
			#ifdef TEXTURE0_DECAL
				new_color = float4(lerp(final_color.rgb, tex_color.rgb, tex_color.a), 1.0);
			#else
				new_color = tex_color;
			#endif

			#ifdef TEXTURE0_MODULATE
				final_color *= new_color;
			#else
				final_color = float4(new_color.rgb, final_color.a * new_color.a);
			#endif
		}
	#endif // TEXTURE_COUNT > 0 
	#if (TEXTURE_COUNT > 1)
		PROCESS_PS_TEXTURE_Diffuse_1(TEXTURE1_COLOR, TEXTURE1_MODULATE, TEXTURE1_DROP);
	#endif
	#if (TEXTURE_COUNT > 2)
		PROCESS_PS_TEXTURE_Diffuse_2(TEXTURE2_COLOR, TEXTURE2_MODULATE, TEXTURE2_DROP);
	#endif
	#if (TEXTURE_COUNT > 3)
		PROCESS_PS_TEXTURE_Diffuse_3(TEXTURE3_COLOR, TEXTURE3_MODULATE, TEXTURE3_DROP);
	#endif
	#if (TEXTURE_COUNT > 4)
		PROCESS_PS_TEXTURE_Diffuse_4(TEXTURE4_COLOR, TEXTURE4_MODULATE, TEXTURE4_DROP);
	#endif
	#if (TEXTURE_COUNT > 5)
		PROCESS_PS_TEXTURE_Diffuse_5(TEXTURE5_COLOR, TEXTURE5_MODULATE, TEXTURE5_DROP);
	#endif
	#if (TEXTURE_COUNT > 6)
		PROCESS_PS_TEXTURE_Diffuse_6(TEXTURE6_COLOR, TEXTURE6_MODULATE, TEXTURE6_DROP);
	#endif
	#if (TEXTURE_COUNT > 7)
		PROCESS_PS_TEXTURE_Diffuse_7(TEXTURE7_COLOR, TEXTURE7_MODULATE, TEXTURE7_DROP);
	#endif
	
	#if (BACK_TEXTURE_COUNT > 0) && !defined(HAS_DEFINED_MATERIAL_SHADER)
		// Factor in the diffuse texture specular_color
		// Deal with Texture Unit 0
		if (FrontDiffuseTextureEnable == 0) {
			#ifdef BACK_TEXTURE0_COLOR
				//xxx we should be using BackModulationColor0, not ModulationColor0
				tex_color = tex2D(BackDiffuseSampler0, vertex.buv0.xy) * float4(ModulationColor0,1);
			#else
				tex_color = tex2D(BackDiffuseSampler0, vertex.buv0.xy);
			#endif

			#ifdef BACK_TEXTURE0_DROP
				if (vertex.uv0.x < 0.0 || vertex.uv0.x > 1.0 ||
					vertex.uv0.y < 0.0 || vertex.uv0.y > 1.0)
				tex_color = float4(0.0, 0.0, 0.0, 0.0);
			#endif
			
			#ifdef BACK_TEXTURE0_DECAL
				new_color = float4(lerp(final_color.rgb, tex_color.rgb, tex_color.a), 1.0);
			#else
				new_color = tex_color;
			#endif

			#ifdef BACK_TEXTURE0_MODULATE
				final_color *= new_color;
			#else
				final_color = float4(new_color.rgb, final_color.a * new_color.a);
			#endif
		}
	#endif
	#if (BACK_TEXTURE_COUNT > 1)
		PROCESS_PS_TEXTURE_BackDiffuse_1(BACK_TEXTURE1_COLOR, BACK_TEXTURE1_MODULATE, BACK_TEXTURE1_DROP);
	#endif
	#if (BACK_TEXTURE_COUNT > 2)
		PROCESS_PS_TEXTURE_BackDiffuse_2(BACK_TEXTURE2_COLOR, BACK_TEXTURE2_MODULATE, BACK_TEXTURE2_DROP);
	#endif
	#if (BACK_TEXTURE_COUNT > 3)
		PROCESS_PS_TEXTURE_BackDiffuse_3(BACK_TEXTURE3_COLOR, BACK_TEXTURE3_MODULATE, BACK_TEXTURE3_DROP);
	#endif
	#if (BACK_TEXTURE_COUNT > 4)
		PROCESS_PS_TEXTURE_BackDiffuse_4(BACK_TEXTURE4_COLOR, BACK_TEXTURE4_MODULATE, BACK_TEXTURE4_DROP);
	#endif
	#if (BACK_TEXTURE_COUNT > 5)
		PROCESS_PS_TEXTURE_BackDiffuse_5(BACK_TEXTURE5_COLOR, BACK_TEXTURE5_MODULATE, BACK_TEXTURE5_DROP);
	#endif
	#if (BACK_TEXTURE_COUNT > 6)
		PROCESS_PS_TEXTURE_BackDiffuse_6(BACK_TEXTURE6_COLOR, BACK_TEXTURE6_MODULATE, BACK_TEXTURE6_DROP);
	#endif
	#if (BACK_TEXTURE_COUNT > 7)
		PROCESS_PS_TEXTURE_BackDiffuse_7(BACK_TEXTURE7_COLOR, BACK_TEXTURE7_MODULATE, BACK_TEXTURE7_DROP);
	#endif

	// Update material colour
	color.diffuse = final_color;
#endif
}

/* Main **********************************************************************/

void pixel_common (
	vertex_results vertex
	, out float4 FinalColor semantic(COLOR0)
#ifdef SHADER_MODEL_3
	, in float Face semantic(VFACE)
#endif // SHADER_MODEL_3
#if defined(DEPTH_WRITING) && defined(DEPTH_WRITING_SINGLE_PASS)
	, out float4 FinalDepth semantic(COLOR1)
#endif // DEPTH_WRITING_SINGLE_PASS && DEPTH_WRITING 
)
{   
	//
	// Special case reduced shading and early-out logic - markers, shadow maps, clip planes, depth peeling.
	// 

#if defined(CIRCLE_MARKER) || defined(MATERIAL_SHADER_MARKER)
	// Rasterize circle from UV coordinates. Do this as soon as possible to get fastest kill.
	float2 marker_uv = vertex.marker_uv * 2.0 - 1.0;
	#ifdef CIRCLE_MARKER
		if ( dot(marker_uv, marker_uv) >= 1.0 )
			discard;
	#endif
#endif

#ifdef TEXTURE_MARKER
	float4 marker_texture = tex2D(MarkerSampler, vertex.marker_uv + MarkerSamplerBias);
	if ( marker_texture.a == 0.0 )
		discard;
#endif

#ifdef CREATE_SHADOW_MAP
	#ifdef DEPTH_TEXTURE_HARDWARE
		// Output garbage to discard
		FinalColor = 0;
	#else
		// Read position from input, bias, and write z.
		float finaldepth = vertex.shadow_position.z/vertex.shadow_position.w + SHADOW_MAP_BIAS;
		
		#ifdef SHADOW_MAP_RGBA
			FinalColor = pack_rgba(finaldepth);
		#else
			FinalColor = float4(finaldepth,0.0,0.0,0.0);
		#endif
	#endif // ndef DEPTH_TEXTURE_HARDWARE
#else // CREATE_SHADOW_MAP (non-standard indent in else case)


#if defined (DEPTH_PEELING) || defined(DEPTH_WRITING)

	// Read position from input
	float4 peel = vertex.peel_position;

	#ifdef DEPTH_PEELING_MODE

		// Depth values will be used for peeling, not framebuffer effects. Don't mangle the range of values,
		// just do the perspective divide.
		peel.xyz /= peel.w;

	#else // DEPTH_PEELING_MODE

		// Depth values will be used for framebuffer effects, either to feed values to the effect, or to
		// disable it on particular pixels.

		#ifdef FRAME_BUFFER_EFFECTS
			// Framebuffer effects: Scale orthographic and perspective outputs so Z is in the same range.
			// Ensure output value is slightly less than 1.0, consistent with background depth set when
			// the depth texture is cleared.
			peel.z = (254.0/255.0) * saturate( peel.z * DepthWriteScale );
		#else
			// If effects are turned off, generate true 1.0 Z values so we can pick them up in the effect.
			peel.z = 1.0f;
		#endif // FRAME_BUFFER_EFFECTS
		
	#endif // ndef DEPTH_PEELING_MODE
	
#endif // DEPTH_PEELING || DEPTH_WRITING

#ifdef DEPTH_PEELING

	// Map to viewport
	#ifndef DC
		peel.xy *= viewport_scale_and_bias.xy;
		peel.xy += viewport_scale_and_bias.zw;
	#endif

	// Scale and bias to turn into texture coords
	peel.xy *= DepthPeelingScaleAndBias.xy;
	peel.xy += DepthPeelingScaleAndBias.zw;
	
	// Lookup depth texture
	float4 peel_texture = tex2D( DepthPeelingTexture, peel.xy );
	
	#ifdef DEPTH_PACKING_RGBA
		// Unpack from RGBA
		float previous_depth = unpack_rgba( peel_texture );
	#else
		// Use directly.
		float previous_depth = peel_texture.r;
	#endif // DEPTH_PACKING_RGBA
	
	// If this fragment is nearer (depth less than) what we drew last time, discard it.
	clip( peel.z - (previous_depth + DEPTH_PEELING_BIAS) );
	
#endif // DEPTH_PEELING

#ifdef DEPTH_WRITING

	#ifdef DEPTH_PACKING_RGBA
		// Pack depth into colour channels
		float4 final_depth = pack_rgba(peel.z);
	#else
		// Output depth as float
		const float4 final_depth = peel.z;
	#endif // DEPTH_PACKING_RGBA
	
	#ifdef DEPTH_WRITING_SINGLE_PASS
		// Output depth to second channel, carry on through shader to do colour.
		FinalDepth = final_depth;
	#else
		// If we're in multipass, output depth and stop
		FinalColor = final_depth;
		return;
	#endif // DEPTH_WRITING_SINGLE_PASS

#endif // DEPTH_WRITING
	
	//If cutting planes exist, and the pixel is 'cut', then discard
	#if (CUTTING_PLANE_COUNT > 0)
		clip(vertex.uvcp0);
	#endif
	#if (CUTTING_PLANE_COUNT > 4)
		clip(vertex.uvcp1);
	#endif
	#if (CUTTING_PLANE_COUNT > 8)
		clip(vertex.uvcp2);
	#endif
	#if (CUTTING_PLANE_COUNT > 12)
		clip(vertex.uvcp3);
	#endif
	
	//
	// More usual shading.
	//
	
	// Material color defaults to what was passed in
	HColor color;
	color.diffuse = vertex.material_color_and_specular_intensity;
	color.specular = MaterialColor.specular;
	
#if defined(HAS_LIGHTING) && !defined(PER_PIXEL_LIGHTING)
	color.diffuse.a = MaterialColor.diffuse.a;
#endif

	// Default surface - flat and distant
	HSurface surface;
	surface.normal = float3(0.0, 0.0, -DRIVER_SPECIFIC_FLIP);
	surface.position = float3(0.0, 0.0, DRIVER_SPECIFIC_FLIP * 100000.0);
	surface.tangent = float3(1.0, 0.0, 0.0);
	surface.bitangent = float3(0.0, 1.0, 0.0);
#if defined(MATERIAL_SHADER_MARKER)
	surface.marker_uv = marker_uv;
#else
	surface.marker_uv = float2(0.0, 0.0);
#endif

	// Default lighting - black
	HLighting lighting;
	lighting.ambient = float3(0.0, 0.0, 0.0);
	lighting.diffuse = float3(0.0, 0.0, 0.0);
	lighting.specular = float3(0.0, 0.0, 0.0);
	lighting.emissive = float3(0.0, 0.0, 0.0);

	// Default effects - nothing	
	HEffects effects;
	effects.mirror = float3(0.0, 0.0, 0.0);
	effects.environment = float3(0.0, 0.0, 0.0);
	effects.luminance = 0.0;
	effects.alpha = color.diffuse.a;

	// Apply mirror value here so lighting can see it to fade emissive.
	apply_mirror(vertex, effects);
	
	// Special material handling
	apply_line_styles(vertex, color);
	apply_vertex_findices(vertex, color);

#ifdef HAS_DEFINED_MATERIAL_SHADER
	// Setup material shader globals
	HGlobals globals;
	globals.cam.direction = float3(0, 0, DRIVER_SPECIFIC_FLIP);
	globals.tex.coords = vertex.uvst0;
#endif // HAS_DEFINED_MATERIAL_SHADER

#ifdef H3D_COLOR_SHADER
	// Apply user's color shader if present
	H3D_COLOR_SHADER(globals, color);
#endif

	// Multitexture material
	apply_multitexture(vertex, color);
	
#ifdef HAS_LIGHTING
	
	#ifdef PER_PIXEL_LIGHTING
	
		// 
		// Define surface
		//
		
		#ifdef SHADER_MODEL_3
			float face = Face;
		#else
			float face = 1.0;
		#endif
			
		// Load and reconstruct normal
		reconstruct_surface(vertex, face, surface);

		// Apply bump map to normal
		apply_bump(vertex, surface);
		
		#ifdef H3D_SURFACE_SHADER
			// Apply user's surface shader last
			H3D_SURFACE_SHADER(globals, surface);
		#endif // H3D_SURFACE_SHADER
		
		//
		// Lighting
		//
		
		#if (SHADOW_MAP_COUNT > 0)

			// Default to no jitter. Will be ignored.
			float4 jitter = float4(0.0,0.0,0.0,0.0);

			// Default to no screen position. Will be ignored.
			float screen_z = 0.0;

			#if defined(SHADOW_MAP_JITTER) || defined(SHADOW_MAP_SLICE_COUNT)
				vertex.screen_position.xy /= vertex.screen_position.w;

				#ifdef SHADOW_MAP_JITTER
					// Map to viewport
					float2 jitter_position = vertex.screen_position.xy * JitterScaleAndBias.xy + JitterScaleAndBias.zw;
					
					// 2x2 Rotation matrix with row 0 in xy, row 1 in zw. Load this once.
					jitter = tex2D(ShadowMapJitterSampler, jitter_position) * 2.0 - 1.0;
				#endif // SHADOW_MAP_JITTER

				#ifdef SHADOW_MAP_SLICE_COUNT
					screen_z = vertex.screen_position.z;
				#endif

			#endif
					
			// Setup shadowmaps array for lighting code
			float4 shadow_map_uv[SHADOW_MAP_COUNT];
			shadow_map_uv[0] = vertex.uvsm0;
				
			#ifdef SHADOW_MAP_0_VIEW_DEPENDENT
				// Adjust UV to map onto slice.
				get_shadowmap_slice( shadow_map_uv[0], screen_z, SliceScales0, SliceBiases0);
			#endif
			#if (SHADOW_MAP_COUNT > 1)
				shadow_map_uv[1]= vertex.uvsm1;
				#ifdef SHADOW_MAP_1_VIEW_DEPENDENT
					// Adjust UV to map onto slice.
					get_shadowmap_slice( shadow_map_uv[1], screen_z, SliceScales1, SliceBiases1);
				#endif
			#endif
			#if (SHADOW_MAP_COUNT > 2)
				shadow_map_uv[2] = vertex.uvsm2;
				#ifdef SHADOW_MAP_2_VIEW_DEPENDENT
					// Adjust UV to map onto slice.
					get_shadowmap_slice( shadow_map_uv[2], screen_z, SliceScales2, SliceBiases2);
				#endif
			#endif
			#if (SHADOW_MAP_COUNT > 3)
				shadow_map_uv[3] = vertex.uvsm3;
				#ifdef SHADOW_MAP_3_VIEW_DEPENDENT
					// Adjust UV to map onto slice.
					get_shadowmap_slice( shadow_map_uv[3], screen_z, SliceScales3, SliceBiases3);
				#endif
			#endif

			// Light with shadow maps
			shadowed_direct_lighting( color, jitter, shadow_map_uv, surface, lighting );
		#else
		
			// Light without shadowmaps
			direct_lighting( color, surface, lighting );
		
		#endif // SHADOW_MAP_COUNT == 0
		
		// Compute ambient lighting
		float ambient_blend = 0.5 + 0.5 * dot(surface.normal, AmbientLightDir);
		lighting.ambient = lerp( AmbientLightDown, AmbientLightUp, ambient_blend );
		
	#else // PER_PIXEL_LIGHTING
	
		//
		// Per vertex lighting
		//

		// Load lighting calculation results from vertex shader. Reconstruct specular from intensity and tint.
		lighting.diffuse = vertex.diffuse_light_and_ambient_blend.rgb;
		lighting.specular = vertex.material_color_and_specular_intensity.a * SpecularTint;
		
		// Load ambient blend and substitute alpha from material.
		lighting.ambient = lerp( AmbientLightDown, AmbientLightUp, vertex.diffuse_light_and_ambient_blend.a );

	#endif // PER_PIXEL_LIGHTING

	// Compute emissive lighting (always per-pixel)
	#ifdef EMISSION_TEXTURE_REGISTER
		lighting.emissive = tex2D(EmissionSampler, vertex.uvemission.xy).xyz;
		#ifdef EMISSION_TEXTURE_MODULATE
			lighting.emissive *= EmissiveLight;
		#endif
	#else
		lighting.emissive = EmissiveLight;
	#endif
	
	#ifdef ENVIRONMENT_TEXTURE
		// Fade emissive by mirror
		lighting.emissive *= float3(1.0, 1.0, 1.0) - effects.mirror;
	#endif
	
	#ifdef SPECULAR_TEXTURE
		// Specular texture modulates intensity
		lighting.specular *= tex2D(SpecularSampler, vertex.uvspec).rgb;
	#endif

	#ifdef H3D_LIGHTING_SHADER
		// Apply user's lighting shader last
		H3D_LIGHTING_SHADER(globals, surface, lighting);
	#endif

	//
	// Now apply lighting to material color
	// 
	
	// Combine material with diffuse and ambient.
    #ifdef AMBIENT_MATERIAL
	    color.diffuse.rgb *= (lighting.ambient + lighting.diffuse);
    #else
		//ambient unaffected by material	    
	    color.diffuse.rgb = color.diffuse.rgb * lighting.diffuse + lighting.ambient;
    #endif
	
	apply_gooch(lighting, color.diffuse.rgb);
	
#endif // HAS_LIGHTING

	//
	// Apply effects to lit material.
	//
	
	apply_environment(vertex, surface, effects);
	apply_luminance(lighting, effects);
	
	// Store latest alpha in effects
	effects.alpha = color.diffuse.a;

#ifdef H3D_EFFECTS_SHADER
	// Apply user's effect shader last
	H3D_EFFECTS_SHADER(globals, surface, lighting, effects);
#endif // H3D_EFFECTS_SHADER
	
	//
	// Final combine, set alpha, and output
	//
	
	// Take alpha from effects shader
	color.diffuse.a = effects.alpha;
	
#ifdef ENVIRONMENT_TEXTURE
	// Apply to color
	color.diffuse.rgb *= 1.0 - rgb_to_gray(effects.mirror);
	color.diffuse.rgb += effects.environment.rgb * effects.mirror;
#endif

#if defined(HAS_LIGHTING)
	// SIL: Skipping this for markers seems like a hack, but matches OGL
	// Spec and emissive always add, unaffected by material color.
	color.diffuse.rgb += (lighting.specular + lighting.emissive);
#endif

	// Have to apply this after lighting since contrast colour is unlit
	apply_face_pattern(vertex, color);
	apply_line_pattern(vertex, color);

#if defined(SHADER_MUST_FOG) && defined(HAS_ATMOSPHERIC_ATTENUATION)
	color.diffuse.rgb = lerp(AtmosphericAttenuationColor,color.diffuse.rgb, vertex.fog);
#endif

#ifdef FORCE_GRAYSCALE
	float gray = rgb_to_gray(color.diffuse.rgb);
	color.diffuse.rgb = float3(gray, gray, gray);
#endif

#ifdef CREATE_REFLECTION_PLANE
	// How far is the point from the reflection plane?
	float plane_distance = dot(vertex.eye_position, ReflectionPlane.plane);

	// Scale into suitable range
	float reflection_strength = 1.0 - saturate( plane_distance * ReflectionPlane.scale + ReflectionPlane.bias );
	color.diffuse.a *= reflection_strength * reflection_strength;

	// Premultiply by alpha so we can filter and compose properly.
	color.diffuse.rgb *= color.diffuse.a;
#endif // CREATE_REFLECTION_PLANE 

#ifdef WRITE_LUMINANCE
#ifdef FRAME_BUFFER_EFFECTS
	if (color.diffuse.a < (1.0/255.0))
		discard;

	// Output biased luminance for bloom etc.
	color.diffuse.a = (1.0/255.0) + effects.luminance;
#else
	// Effects disabled - Output zero luminance.
	color.diffuse.a = 0.0;
#endif
#endif

#ifdef TRANSMISSION_TEXTURE_REGISTER
	float3 transmission = tex2D(TransmissionSampler, vertex.uvtransmission.xy).xyz;

	#ifdef TRANSMISSION_TEXTURE_MODULATE
		transmission *= TransmissionModulateColor;
	#endif

	float tgray = rgb_to_gray(transmission);
	color.diffuse.a = 1.0 - tgray;
#endif

#ifdef CREATE_SIMPLE_SHADOW
	// Output whiteness, let material determine opacity.
	color.diffuse.rgb = float3(1.0,1.0,1.0);
#endif // CREATE_SIMPLE_SHADOW

   	// Output color
	FinalColor = color.diffuse;
	
#endif // ndef CREATE_SHADOW_MAP

}

