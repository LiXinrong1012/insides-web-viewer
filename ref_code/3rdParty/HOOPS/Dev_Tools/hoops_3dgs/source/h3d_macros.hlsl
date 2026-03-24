#define PROCESS_PS_TEXTURE_##(sampler)_##(sampler_unit)(use_color, modulate, drop) \
{ \
	if (FrontDiffuseTextureEnable == ##(facing_value)) { \
		tex_color = tex2D(##(sampler)Sampler##(sampler_unit), vertex.##(uv)##(unit).xy); \
		if (use_color) \
			tex_color *= float4(ModulationColor##(sampler_unit),1.0); \
\
		if (drop && (vertex.##(uv)##(unit).x < 0.0 || vertex.##(uv)##(unit).x > 1.0 || \
					vertex.##(uv)##(unit).y < 0.0 || vertex.##(uv)##(unit).y > 1.0)) \
			tex_color = float4(0.0, 0.0, 0.0, 0.0); \
\
		new_color = float4(lerp(final_color, tex_color, tex_color.a)); \
\
		if(modulate) \
			final_color *= new_color; \
		else \
			final_color = new_color; \
	} \
}
#endmacro


#define PROCESS_VS_TEXTURE_##(facing)_##(unit)(world) \
{ \
	#ifndef DC \
		if (world) \
			result.##(uv)##(unit) = world_position.xy; \
		else \
			result.##(uv)##(unit) = vertex.##(uv)##(unit).xy; \
		result.##(uv)##(unit) = (mul(float4(result.##(uv)##(unit), 0.0, 1.0), TextureMatrix##(unit))).xy; \
	#else \
		result.##(uv)##(unit) = vertex.##(uv)##(unit).xy; \
	#endif \
}
#endmacro

#define SHADOWED_DISTANT_LIGHT##(which)(jitter,surface,color,eye_vector,lighting) \
{ \
	if ( DISTANT_LIGHT_COUNT > ##(which)) { \
		float3 d, s; \
		distant_light( surface, color, DistantLights[COND(##(which),DISTANT_LIGHT_COUNT)], eye_vector, d, s); \
		if (DISTANT_SHADOW_MAP_COUNT > ##(which)) { \
			float illumination = get_shadowmap_illumination( jitter, shadow_map_uv[DISTANT_SHADOW_MAP_UV##(which)], DISTANT_SHADOW_MAP_TEXTURE##(which)); \
			APPLY_SHADOW(d, illumination); \
			s *= illumination; \
		} \
		lighting.diffuse += d; \
		lighting.specular += s; \
	} \
}
#endmacro

#define SHADOWED_SPOT_LIGHT##(which)(jitter,surface,color,eye_vector,lighting) \
{ \
	if ( SPOT_LIGHT_COUNT > ##(which)) { \
		float3 d, s; \
		spot_light( surface, color, SpotLights[COND(##(which),SPOT_LIGHT_COUNT)], eye_vector, d, s); \
		if (SPOT_SHADOW_MAP_COUNT > ##(which)) { \
			float illumination = get_shadowmap_illumination( jitter, shadow_map_uv[SPOT_SHADOW_MAP_UV##(which)], SPOT_SHADOW_MAP_TEXTURE##(which)); \
			d *= illumination; \
			s *= illumination; \
		} \
		lighting.diffuse += d; \
		lighting.specular += s; \
	} \
}
#endmacro
