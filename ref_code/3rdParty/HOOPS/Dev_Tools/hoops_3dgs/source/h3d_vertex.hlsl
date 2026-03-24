// Copyright (c) 2007 by Tech Soft 3D, LLC.
// all rights reserved
// $Id: h3d_vertex.hlsl,v 1.87 2011-01-20 22:36:04 heppe Exp $
 
/* Shared IO Types ***********************************************************/

/* 
 * VERTEX
 * Input from vertex buffer 
 */
#ifndef CREATE_SHADOW_MAP
struct vertex_input
{
	/* Vertex position */
	float3 position semantic(POSITION);

	#ifdef HAS_VERTEX_NORMALS
		/* Vertex normal (in object space) for lighting */
		float3 normal semantic(NORMAL);
	#endif
	#ifdef TANGENT_COORD
		/* Vertex tangent (in object space) for lighting */
		float4 tangent semantic(TANGENT_COORD);
	#endif
	#ifdef WIDE_LINE
		/* expected to be mutually exclusive with textures or normals */
		float3 end semantic(NEXT_COORD);
		#ifdef MITERED_LINE
			float3 previous semantic(PREV_COORD);	/* Start of previous line */
		#endif

		/* Mitered Offset constants
		 *   x displaces along line
		 *   y displaces perpendicular to line
		 *   z id's between the vertices used to start vs end a span */
		float4 offset semantic(OFFSET_COORD);

		#if defined(ROUND_LINE) || defined(ANTI_ALIASED_LINE)
			float4 uv semantic(ROUND_COORD);
		#endif
	#endif

	#ifdef HAS_VERTEX_COLORS
		/* Diffuse color from the material */
		float4 color semantic(COLOR0);
	#endif
	
	#ifdef HAS_AMBIENT_OCCLUSION
		/* AO term in specular.a */
		float4 ambient_occlusion semantic(COLOR1);
	#endif 
		
	#ifdef HAS_LINE_PATTERN
		float2 uvlp semantic(LINE_PATTERN_COORD);
	#endif

	#ifdef HAS_VERTEX_FINDICES
		float2 findex semantic(FINDEX_COORD);
	#endif

	#if defined(HAS_DEFINED_MATERIAL_SHADER) || defined(HAS_TEXTURE3D)
		float4 uvst0 semantic(DIFFUSE_TEXTURE_COORD0);
	#endif
	
	#if (TEXTURE_COUNT > 0) && !defined(HAS_DEFINED_MATERIAL_SHADER) && !defined(HAS_TEXTURE3D)
		/* Texture coordinates */
		float2 uv0 semantic(DIFFUSE_TEXTURE_COORD0);
	#endif

	#ifndef SHARED_DIFFUSE_COORDS
		#if (TEXTURE_COUNT > 1) 
			float2 uv1 semantic(DIFFUSE_TEXTURE_COORD1);
		#endif
		#if (TEXTURE_COUNT > 2) 
			float2 uv2 semantic(DIFFUSE_TEXTURE_COORD2);
		#endif
		#if (TEXTURE_COUNT > 3) 
			float2 uv3 semantic(DIFFUSE_TEXTURE_COORD3);
		#endif
		#if (TEXTURE_COUNT > 4) 
			float2 uv4 semantic(DIFFUSE_TEXTURE_COORD4);
		#endif
		#if (TEXTURE_COUNT > 5) 
			float2 uv5 semantic(DIFFUSE_TEXTURE_COORD5);
		#endif
		#if (TEXTURE_COUNT > 6) 
			float2 uv6 semantic(DIFFUSE_TEXTURE_COORD6);
		#endif
		#if (TEXTURE_COUNT > 7) 
			float2 uv7 semantic(DIFFUSE_TEXTURE_COORD7);
		#endif
	#endif

	#if (BACK_TEXTURE_COUNT > 0) && !defined(HAS_DEFINED_MATERIAL_SHADER) && !defined(HAS_TEXTURE3D)
		/* Texture coordinates */
		float2 buv0 semantic(BACK_DIFFUSE_TEXTURE_COORD0);
	#endif
	#if (BACK_TEXTURE_COUNT > 1) 
		float2 buv1 semantic(BACK_DIFFUSE_TEXTURE_COORD1);
	#endif
	#if (BACK_TEXTURE_COUNT > 2) 
		float2 buv2 semantic(BACK_DIFFUSE_TEXTURE_COORD2);
	#endif
	#if (BACK_TEXTURE_COUNT > 3) 
		float2 buv3 semantic(BACK_DIFFUSE_TEXTURE_COORD3);
	#endif
	#if (BACK_TEXTURE_COUNT > 4) 
		float2 buv4 semantic(BACK_DIFFUSE_TEXTURE_COORD4);
	#endif
	#if (BACK_TEXTURE_COUNT > 5) 
		float2 buv5 semantic(BACK_DIFFUSE_TEXTURE_COORD5);
	#endif
	#if (BACK_TEXTURE_COUNT > 6) 
		float2 buv6 semantic(BACK_DIFFUSE_TEXTURE_COORD6);
	#endif
	#if (BACK_TEXTURE_COUNT > 7) 
		float2 buv7 semantic(BACK_DIFFUSE_TEXTURE_COORD7);
	#endif

	#ifdef MIRROR_TEXTURE
		float2 uvmirror semantic(MIRROR_TEXTURE);
	#endif

	#ifdef SPECULAR_TEXTURE
		float2 uvspec semantic(SPECULAR_TEXTURE);
	#endif
	
	#ifdef BUMP_TEXTURE
		float2 uvbump semantic(BUMP_TEXTURE);
	#endif

	#ifdef TRANSMISSION_TEXTURE
		float2 uvtransmission semantic(TRANSMISSION_TEXTURE);
	#endif

	#ifdef EMISSION_TEXTURE
		float2 uvemission semantic(EMISSION_TEXTURE);
	#endif

	#ifdef QUAD_MARKER
		float2 marker_offset semantic(MARKER_TEXTURE);
	#endif
	
	#ifdef PRIORITY_HSRA
		float priority semantic(PRIORITY_HSRA_COORD);
	#endif 
	
};
#else /* CREATE_SHADOW_MAP */
struct vertex_input
{
	/* Vertex position */
	float3 position semantic(POSITION);

	#ifdef WIDE_LINE
		/* expected to be mutually exclusive with textures or normals */
		float3 end semantic(NEXT_COORD);
		#ifdef MITERED_LINE
			float3 previous semantic(PREV_COORD);	/* Start of previous line */
		#endif

		/* Mitered Offset constants
		 *   x displaces along line
		 *   y displaces perpendicular to line
		 *   z id's between the vertices used to start vs end a span */
		float4 offset semantic(OFFSET_COORD);

		#if defined(ROUND_LINE) || defined(ANTI_ALIASED_LINE)
			float4 uv semantic(ROUND_COORD);
		#endif
	#endif

#ifdef QUAD_MARKER
	float2 marker_offset semantic(MARKER_TEXTURE);
#endif
};
#endif

/* Uniform Types *************************************************************/
/* ***************************************************************************/
/* ***************************************************************************/
/* shadow map */
struct shadow_map_t
{
	float4x4 transform;
#ifdef SHADOW_MAP_DISTORTION
	float4 distortion;
#endif // SHADOW_MAP_DISTORTION
};

/* Atmospheric Attenuation */
struct atmospheric_attenuation_t
{
	float hither;
	float yon;
};

/* Uniforms ******************************************************************/
/* ***************************************************************************/
/* ***************************************************************************/

/* Transformations */
#ifdef DC
	uniform float4x4 WorldViewProj;
#else
	uniform float4x4 Projection;
	uniform float4x4 ModelView;
	uniform float4x4 Model;
	uniform float3x3 NormalizedModelView3x3;

	#ifdef HAS_VERTEX_FINDICES
		uniform float4x4 IndexTextureMatrix;
	#endif

	#if (TEXTURE_COUNT > 0 || BACK_TEXTURE_COUNT > 0)
		uniform float4x4 TextureMatrix0;
	#endif
	#if (TEXTURE_COUNT > 1 || BACK_TEXTURE_COUNT > 1)
		uniform float4x4 TextureMatrix1;
	#endif
	#if (TEXTURE_COUNT > 2 || BACK_TEXTURE_COUNT > 2)
		uniform float4x4 TextureMatrix2;
	#endif
	#if (TEXTURE_COUNT > 3 || BACK_TEXTURE_COUNT > 3)
		uniform float4x4 TextureMatrix3;
	#endif
	#if (TEXTURE_COUNT > 4 || BACK_TEXTURE_COUNT > 4)
		uniform float4x4 TextureMatrix4;
	#endif
	#if (TEXTURE_COUNT > 5 || BACK_TEXTURE_COUNT > 5)
		uniform float4x4 TextureMatrix5;
	#endif
	#if (TEXTURE_COUNT > 6 || BACK_TEXTURE_COUNT > 6)
		uniform float4x4 TextureMatrix6;
	#endif
	#if (TEXTURE_COUNT > 7 || BACK_TEXTURE_COUNT > 7)
		uniform float4x4 TextureMatrix7;
	#endif
	
	#ifdef BUMP_TEXTURE
		uniform float4x4 BumpTextureMatrix;
	#endif
	
	#ifdef SPECULAR_TEXTURE
		uniform float4x4 SpecularTextureMatrix;
	#endif

	#ifdef MIRROR_TEXTURE
		uniform float4x4 MirrorTextureMatrix;
	#endif

	#ifdef ENVIRONMENT_TEXTURE
		uniform float4x4 EnvironmentTextureMatrix;
	#endif

	#ifdef TRANSMISSION_TEXTURE
		uniform float4x4 TransmissionTextureMatrix;
	#endif
	
	#ifdef EMISSION_TEXTURE
		uniform float4x4 EmissionTextureMatrix;
	#endif
#endif
uniform float FaceDisplacement;
uniform float GeneralDisplacement;

uniform float3 CameraPosition;		//camera position in object space

#ifdef WIDE_LINE
	uniform float WindowWidth;
	uniform float WindowHeight;
#endif

#if defined(HAS_FACE_PATTERN) || defined(HAS_DEFINED_MATERIAL_SHADER)
	uniform float ScaledWindowWidth;
	uniform float ScaledWindowHeight;
#endif

#ifdef WIDE_LINE
	#define LINE_TOOLS_SIZE 256.0
	uniform float LineWeight;		
	uniform float CircleSubImageStart;

	#ifdef MITERED_LINE
	uniform float CosJoinCutoffAngle;
	#endif
#endif

/* Shadow maps */
uniform shadow_map_t ShadowMaps[SHADOW_MAP_COUNT+1];

#ifdef SHADOW_MAP_DISTORTION
#ifdef CREATE_SHADOW_MAP
/* Shadow distortion when rendering depth image */
uniform float4 ShadowDistortion;
#endif // CREATE_SHADOW_MAP
#endif // SHADOW_MAP_DISTORTION

/* Material properties */
uniform HColor MaterialColor;

/* Cutting planes */
uniform float4 CuttingPlanes[CUTTING_PLANE_COUNT+1];

/* Atmospheric attenuation */
uniform atmospheric_attenuation_t AtmosphericAttenuation;

/* Colormap Size */
uniform float ColormapSize;

#if defined(QUAD_MARKER) || defined(SPRITE_MARKER)
/* Marker size in X and Y*/
uniform float2 MarkerSize;
#endif

#ifdef SNAPPED_MARKER
/* Marker snap / unsnap values */
uniform float4 MarkerSnap;
uniform float4 MarkerUnsnap;
#endif 

#ifdef POLY_CYLINDER
/* Size of half a pixel in view space */
uniform float4 PolyCylinderScale;
#endif

#if defined(HAS_LIGHTING) && !defined(PER_PIXEL_LIGHTING)
uniform float3 AmbientLightDir;
#endif

/* Code **********************************************************************/
/* ***************************************************************************/
/* ***************************************************************************/

#ifdef SHADOW_MAP_DISTORTION

//
// Use logarithmic distortion to concentrate shadow texels around the viewer.
// Rescale projected texture coordinates or position for shadowing around the
// projection of the viewer onto the shadow map plane.
//
float4 distort_shadowmap_position( float4 position, uniform float4 distortion )
{
	// Where is the shadowed point relative to the viewer's projection on the shadow plane?
	float2 delta = position.xy - distortion.xy;
	
	// Calculate undistorted distance from viewer position at the texture
	float t = length(delta);
	
	#ifndef CREATE_SHADOW_MAP
		// If we're creating a shadow map, these coordinates will be in 
		// NDC space. If not, they'll be in UV space and we need to double
		// the scale to get the same distortion.
		t *= 2.0f;
	#endif // CREATE_SHADOW_MAP
	
	// If this point is inside the distortion circle...
	if ( t < 1 )
	{
		// Compute log(kt + 1) distortion factor, normalise log s.t. t = 1 -> no distortion.
		// Dividing by t turns delta into a unit vector suitable for rescaling.
		float t_dash = distortion.w * log( distortion.z * t + 1) / t; 

		// Remap using distorted distance.
		position.xy = distortion.xy + delta * t_dash;
	}
	
	// Otherwise leave the point along - gives slightly better texel density on
	// distant texels
	
	// Done
	return position;
}

#endif // SHADOW_MAP_DISTORTION

#ifndef CREATE_SHADOW_MAP
#ifdef HAS_VERTEX_NORMALS
float3 spheremap( float3 ray )
{
	/* map to sphere */
	ray.z = 1.0 - ray.z;
	float tmp = length(ray);
	if(tmp < 0.000001)
		tmp = 0.000001;
	tmp = 0.5 / tmp;

	ray.y = -ray.y;

	float3 uv;
	uv.xy = ray.xy * tmp + 0.5;
	uv.z = 0.0;
	
	return uv;
}

#endif // HAS_VERTEX_NORMALS
#endif // CREATE_SHADOW_MAP

#ifdef WIDE_LINE
/* Wide line transform *******************************************************/
/* ***************************************************************************/
void wide_line_transform(
		const vertex_input vertex,
		out float4 position,
		out float3 wide_line_offset)
{
	position = float4(vertex.position,1);

#ifdef DC
	float2 windowfactor = float2(1.0,1.0);
#else
	float2 windowfactor = float2(2.0 / WindowWidth, 2.0 / WindowHeight);
	float ratio = WindowWidth / WindowHeight;
#endif


#ifdef MITERED_LINE
	position.x = ceil(position.x) - 0.5;
	position.y = ceil(position.y) - 0.5;

	if (vertex.offset.w == H3D_MITER) {

		#ifdef DC
			//calculate vectors pointing away from start point of line
			float2 prev_path = normalize( float2(vertex.previous.xy - vertex.position.xy) );
			float2 path = normalize( float2(vertex.end.xy - vertex.position.xy) );
		#else
			float4 end = mul (float4(vertex.end,1.0), ModelView);
			end = mul(end, Projection);

			float4 prev = mul (float4(vertex.previous,1.0), ModelView);
			prev = mul(prev, Projection);

			float4 pos = mul (float4(vertex.position,1.0), ModelView);
			pos = mul(pos, Projection);

			#ifdef CAMERA_PERSPECTIVE
				end /= end.w;
				prev /= prev.w;
				pos /= pos.w;
			#endif
			
			position = pos;

			float4 prev_path = prev - pos;
			float4 path = end - pos;

			prev_path.x *= ratio;
			path.x *= ratio;

			prev_path.xy = normalize(prev_path.xy);
			path.xy = normalize(path.xy);
		#endif	
	
		//keep cos_angle from actually hitting 1, since that would cause divide by 0
		float cos_angle = dot(prev_path, path) * 0.999;
		//sin is z component of cross product
		float sin_angle = prev_path.x*path.y - prev_path.y*path.x;
		float tan_half = sqrt( (1.0+cos_angle) / (1.0-cos_angle) );
		float adjust = tan_half;
		
		//check against the miter limit
		if (cos_angle >= CosJoinCutoffAngle)
			adjust = 0.0;
			
		float3 miter_offset = vertex.offset.xyz;

#ifdef DC
		prev_path *= WIDE_LINE_SCALE;
		path *= WIDE_LINE_SCALE;
#endif

		//Scale the offsets up to the given line weight
		if (miter_offset.z > 0.0)
			path = -prev_path * LineWeight/2.0;
		else
			path *= LineWeight/2.0;

		if (vertex.offset.w == H3D_ROUND)		// shrink the line a bit if we're not texture sampling
			path *= WIDE_LINE_SAMPLER_SCALE;
		path *= position.w;
		
		//clockwise bends rotate seam between line segments clockwise,
		//but counterclockwise bends rotate seam counterclockwise
		if (sin_angle < -0.00001)
			miter_offset.x *= -1.0;

		// Offset horizontally (away from line axis)
		position.xy += miter_offset.x * float2( -path.y, path.x ) * windowfactor;
				
		// Offset vertically (along line axis, for caps/joints)
		position.xy += miter_offset.y * adjust * path.xy * windowfactor;
	}
	else
#endif
	{
		#ifdef DC
			// Point along the line
			float2 path = normalize( float2(vertex.end.xy - vertex.position.xy) );
			path *= WIDE_LINE_SCALE;
		#else
			float4 end = mul (float4(vertex.end,1.0), ModelView);
			end = mul(end, Projection);
			float4 pos = mul (float4(vertex.position,1.0), ModelView);
			pos = mul(pos, Projection);
			
			
			position = pos;
			float4 path = end - pos;
			path.x *= ratio;
			float len = length(path.xy);
			if (len > 0.00001) {
				path.xy /= len;
			}
			#ifdef CAMERA_PERSPECTIVE
				else {
					//path is length 0.  divide by w and try again
					end /= end.w;
					pos /= pos.w;
					path = end - pos;
					path.x *= ratio;
					len = length(path.xy);
					if (len > 0.00001)
						path.xy /= len;
				}
			#endif
		#endif

		// Scale up
		path *= LineWeight/2.0;
		if (vertex.offset.w == H3D_ROUND)	// shrink the line a bit if we're not texture sampling
			path *= WIDE_LINE_SAMPLER_SCALE;
		path.xy *= position.w;

		// Offset horizontally (away from line axis)
		position.xy += vertex.offset.x * float2( -path.y, path.x ) * windowfactor;
		// Offset vertically (along line axis, for caps/joints)
		position.xy += vertex.offset.y * path.xy * windowfactor;
	}

	#if defined(ROUND_LINE) || defined(ANTI_ALIASED_LINE)	
		if (vertex.offset.w == H3D_ROUND) {
			// Compress [-1, 1] into [0, 1]
			// First offset (x) defines V coordinate for line
			// Second offset (y) defines U coordinate - 0.5 except at endcaps
			wide_line_offset.xy = vertex.uv.xy * 0.5 + 0.5;
		}
		else
			wide_line_offset.xy = float2(0.5, 0.5);

		#if defined(ANTI_ALIASED_LINE)
			wide_line_offset.xy = vertex.uv.xy * 0.5 + 0.5;
		#endif

		// Compress [0,1] into circle's subimage
		wide_line_offset.xy *= (LineWeight+2.0)/LINE_TOOLS_SIZE;
		wide_line_offset.x += CircleSubImageStart;
		//uv0.y += 0.5/LINE_TOOLS_SIZE;
	#else
		wide_line_offset.xy = float2(0.0, 0.0);
	#endif

	wide_line_offset.z = vertex.offset.w;			//pass through the flag stored in w

	#ifdef DC
		position += 0.5;
	#endif
}
#endif

/* Main vertex function ******************************************************/
/* ***************************************************************************/
/* ***************************************************************************/
vertex_results vertex_common(vertex_input vertex)
{
	int i;
	vertex_results result;

#ifndef CREATE_SHADOW_MAP

	#ifdef HAS_VERTEX_COLORS
		// Vertex color overrides material properties (except alpha)
		#if !defined(HAS_VERTEX_RGBAS) && !defined(DC)
			vertex.color.a = MaterialColor.diffuse.a;
		#endif
		result.material_color_and_specular_intensity = vertex.color;
	#else
		// Set default output color
		result.material_color_and_specular_intensity = MaterialColor.diffuse;
	#endif
	
#endif // ndef CREATE_SHADOW_MAP

	float3 position = vertex.position;
	


#ifdef DC	
	#ifdef WIDE_LINE
		float4 out_pos;
		wide_line_transform(vertex, out_pos, result.wide_line_offset);
		position.xyz = out_pos.xyz;
	#endif

	// DC projections are trivial
    result.position = mul(float4(position, 1.0), WorldViewProj);

	#ifdef EYE_POSITION_COORD
		result.eye_position = result.position;
	#endif 

#else // ndef DC -> 3D

	//
	// Transformation
	// ====================================================================

	// Transform point to eye space
	float4 eye_position = mul( float4(position,1.0), ModelView);
	
	#ifdef HAS_VERTEX_NORMALS

		// Transform normal to eye space
		float3 eye_normal = mul( vertex.normal, NormalizedModelView3x3);
		#ifdef HAS_NON_UNIFORM_SCALE
			eye_normal = normalize(eye_normal);
		#endif
	
		#if defined(HAS_VERTEX_NORMALS) && defined(POLY_CYLINDER)
			// Polycylinder expansion - push by one half pixel in the direction of the normal
		#ifndef CAMERA_PERSPECTIVE
			// Ortho case - direct relationship between eye space and projected space
			eye_position.xyz += PolyCylinderScale.x * eye_normal;
		#else
			// Perspective case - need to work out size of pixel at our distance
			float pixel = PolyCylinderScale.y * eye_position.z;
			eye_position.xyz += pixel * eye_normal;
		#endif
		#endif

	#endif
	
	#ifdef TANGENT_COORD
		// Transform tangent to eye space
		float3 eye_tangent = float3(1,0,0);
		if (vertex.tangent.x != 0 ||
			vertex.tangent.y != 0 ||
			vertex.tangent.z != 0) {
			eye_tangent = mul( vertex.tangent.xyz, NormalizedModelView3x3);
			#ifdef HAS_NON_UNIFORM_SCALE
				eye_tangent = normalize(eye_tangent);
			#endif
		}
	#endif
	
	#ifndef WIDE_LINE
		// Transform point to screen space (TODO: One transform not two, if the
		// world position is not needed for lighting)
		result.position = mul( eye_position, Projection );
	#else
		wide_line_transform(vertex, result.position, result.wide_line_offset);
	#endif
#ifndef CREATE_SHADOW_MAP

	#ifdef EYE_POSITION_COORD
		result.eye_position = eye_position;
	#endif 
	
	#ifdef TANGENT_COORD
		result.eye_tangent.xyz = eye_tangent * 0.5 + 0.5;
		
		// Forward W component for bitangent reconstruction
		result.eye_tangent.w = vertex.tangent.w;
	#endif
	
	#ifdef HAS_VERTEX_NORMALS
		
		#ifdef HAS_LIGHTING
		
			#ifdef PER_PIXEL_LIGHTING
				// Send normal through to PS
				result.eye_normal.xyz = eye_normal * 0.5 + 0.5;
			#endif // PER_PIXEL_LIGHTING

			// temporarily flip all normals to face the camera
			#ifdef HAS_HANDEDNESS
				#ifdef RIGHT_HANDED_MATRIX
					eye_normal = -eye_normal;
				#endif
				eye_normal *= DRIVER_SPECIFIC_FLIP;
			#else
				#ifdef CAMERA_PERSPECTIVE
					if (dot(eye_position.xyz,eye_normal) > 0.0)
						eye_normal = -eye_normal;
				#else
					if(eye_normal.z > 0.0)
						eye_normal = -eye_normal;
					eye_normal *= DRIVER_SPECIFIC_FLIP;
				#endif
			#endif

			#ifndef PER_PIXEL_LIGHTING	
			
				//
				// Lighting
				// ====================================================================
				
				// Simple surface
				HSurface surface;
				surface.position = eye_position.xyz;
				surface.normal = eye_normal;
				#ifdef TANGENT_COORD
					surface.tangent = eye_tangent;
				#else
					surface.tangent = float3(1.0, 0.0, 0.0);
				#endif
				surface.bitangent = normalize(cross(surface.normal, surface.tangent));
				
				// No lighting yet
				HLighting lighting;
				lighting.diffuse = float3(0.0, 0.0, 0.0);
				lighting.specular = float3(0.0, 0.0, 0.0);
				
				direct_lighting( MaterialColor, surface, lighting );

				// Output lighting color and spec value		
				result.diffuse_light_and_ambient_blend.rgb = lighting.diffuse;
				result.material_color_and_specular_intensity.a = rgb_to_gray(lighting.specular);
				
				// Output ambient blend
				float ambient_blend = 0.5 + 0.5 * dot(eye_normal, AmbientLightDir);
				result.diffuse_light_and_ambient_blend.a = ambient_blend;

			#endif // ndef PER_PIXEL_LIGHTING
			
		#endif // HAS_LIGHTING
	
	#endif // HAS_VERTEX_NORMALS

#endif // ndef CREATE_SHADOW_MAP

#endif // ndef DC

#ifdef SNAPPED_MARKER

	//
	// Snap point to a pixel location.
	//

#ifdef CAMERA_PERSPECTIVE
	// Go into post-perspective space.
	result.position.xy /= result.position.w;
#endif // CAMERA_PERSPECTIVE

	// Scale to pixel coordinates, snap, and scale back.
	result.position.xy = result.position.xy * MarkerSnap.xy + MarkerSnap.zw;
	result.position.xy = floor(result.position.xy) + MARKER_HALF_PIXEL_OFFSET;
	result.position.xy = result.position.xy * MarkerUnsnap.xy + MarkerUnsnap.zw;
	
#ifdef CAMERA_PERSPECTIVE
	// Go back to pre-perspective space since we can't prevent the shader 
	// doing the divide.
	result.position.xy *= result.position.w;

#endif

#endif // SNAPPED_MARKER

#ifdef QUAD_MARKER

#if defined (CIRCLE_MARKER) || defined(TEXTURE_MARKER) || defined(MATERIAL_SHADER_MARKER)
	// Output texture coordinates
	result.marker_uv = float2(1.0,-1.0) * vertex.marker_offset * 0.5 + 0.5;	
#endif
	
	// Now offset corners to make quad.
#ifndef WORLD_SPACE_MARKER
	result.position.xy += MarkerSize * vertex.marker_offset.xy * result.position.w;
#else
	result.position.xy += MarkerSize * vertex.marker_offset.xy;
#endif
	
#endif // QUAD_MARKER

#ifdef SPRITE_MARKER

#if defined(CIRCLE_MARKER) || defined(TEXTURE_MARKER) || defined(MATERIAL_SHADER_MARKER)
	// Output texture coordinates to satisfy validation - these will be overwritten by point sprites.
	result.marker_uv = float2(0.0, 0.0);
#endif
	
	// Output size
#ifdef WORLD_SPACE_MARKER
	result.marker_size = MarkerSize.y / result.position.w;
#else
	result.marker_size = MarkerSize.y;
#endif

#endif // ndef MARKER_SPRITE

#ifndef CREATE_SHADOW_MAP

#ifdef HAS_VERTEX_FINDICES
	result.findex = (mul(float4(vertex.findex, 0.0, 1.0), IndexTextureMatrix)).xy;

	float colormap_shift = 0.5/ColormapSize;
	result.findex.x = result.findex.x / ColormapSize + colormap_shift;
	result.findex.y -= 0.5;
#endif

#if (TEXTURE_COUNT > 0) || (BACK_TEXTURE_COUNT > 0)
	#ifndef DC
	// calculate the world position in case this or any of the subsequent stages need it
		float4 world_position = mul(float4(vertex.position,1), Model);
	#endif
#endif

#if (TEXTURE_COUNT > 0)
	//
	// Texturing
	// ====================================================================
	#ifndef DC
		#if defined(HAS_DEFINED_MATERIAL_SHADER) || defined(HAS_TEXTURE3D)
			#if defined(DEFINED_MATERIAL_PS_UVW) || defined(HAS_TEXTURE3D)
				result.uvst0 = float4(vertex.uvst0.xyz, 1.0);
			#endif
			#if defined(DEFINED_MATERIAL_PS_WORLD)
				result.uvst0 = float4(world_position.xyz, 1.0) / world_position.w;
			#endif
			#if defined(DEFINED_MATERIAL_PS_OBJECT)
				result.uvst0 = float4(vertex.position, 1.0);	
			#endif
			#if defined(DEFINED_MATERIAL_PS_SURFACE_NORMAL)
				#if defined(HAS_VERTEX_NORMALS)
					result.uvst0 = float4(vertex.normal,1.0);
				#else
					result.uvst0 = float4(0.0, 0.0, 0.0, 1.0);
				#endif
			#endif
			#if defined(DEFINED_MATERIAL_PS_LOCAL_PIXELS) || defined(DEFINED_MATERIAL_PS_OUTER_PIXELS)
				//todo: handle subwindows
				result.uvst0.x = ScaledWindowWidth * result.position.x;
				result.uvst0.y = -ScaledWindowHeight * result.position.y;
				result.uvst0.z = 0.0;
				result.uvst0.w = result.position.w;
			#endif
			#if defined(DEFINED_MATERIAL_PS_LOCAL_WINDOW) || defined(DEFINED_MATERIAL_PS_OUTER_WINDOW)
				//todo: handle subwindows
				result.uvst0.x = result.position.x;
				result.uvst0.y = result.position.y;
				result.uvst0.z = 0.0;
				result.uvst0.w = result.position.w;
			#endif
			#if defined(DEFINED_MATERIAL_PS_PHYSICAL_REFLECTION)
				#if defined(HAS_VERTEX_NORMALS)
					result.uvst0 = float4(reflect(normalize(vertex.position - CameraPosition), vertex.normal), 1);
				#else
					result.uvst0 = float4(0.0, 0.0, 0.0, 1.0);
				#endif
			#endif
			result.uvst0 = mul(result.uvst0, TextureMatrix0);
		#else
			#if defined(TEXTURE0_WORLD)
				result.uv0 = world_position.xy;
			#else
				result.uv0 = vertex.uv0.xy;
			#endif
			result.uv0 = (mul(float4(result.uv0, 0.0, 1.0), TextureMatrix0)).xy;
		#endif
	#else
	    result.uv0 = vertex.uv0.xy;
	#endif
#endif

#ifndef SHARED_DIFFUSE_COORDS
	#if (TEXTURE_COUNT > 1) 
		PROCESS_VS_TEXTURE_FRONT_1(TEXTURE1_WORLD);
	#endif
	#if (TEXTURE_COUNT > 2) 
		PROCESS_VS_TEXTURE_FRONT_2(TEXTURE2_WORLD);
	#endif
	#if (TEXTURE_COUNT > 3) 
		PROCESS_VS_TEXTURE_FRONT_3(TEXTURE3_WORLD);
	#endif
	#if (TEXTURE_COUNT > 4) 
		PROCESS_VS_TEXTURE_FRONT_4(TEXTURE4_WORLD);
	#endif
	#if (TEXTURE_COUNT > 5) 
		PROCESS_VS_TEXTURE_FRONT_5(TEXTURE5_WORLD);
	#endif
	#if (TEXTURE_COUNT > 6) 
		PROCESS_VS_TEXTURE_FRONT_6(TEXTURE6_WORLD);
	#endif
	#if (TEXTURE_COUNT > 7) 
		PROCESS_VS_TEXTURE_FRONT_7(TEXTURE7_WORLD);
	#endif
#endif

#if (BACK_TEXTURE_COUNT > 0)
	//
	// Texturing
	// ====================================================================
	#ifndef DC
		#ifdef BACK_TEXTURE0_WORLD
			result.buv0 = world_position.xy;
		#else
			result.buv0 = vertex.buv0.xy;
		#endif
		result.buv0 = (mul(float4(result.buv0, 0.0, 1.0), TextureMatrix0)).xy;
	#else
	    result.buv0 = vertex.buv0.xy;
	#endif
#endif
#if (BACK_TEXTURE_COUNT > 1) 
	PROCESS_VS_TEXTURE_BACK_1(BACK_TEXTURE1_WORLD);
#endif
#if (BACK_TEXTURE_COUNT > 2)
	PROCESS_VS_TEXTURE_BACK_2(BACK_TEXTURE2_WORLD);
#endif
#if (BACK_TEXTURE_COUNT > 3)
	PROCESS_VS_TEXTURE_BACK_3(BACK_TEXTURE3_WORLD);
#endif
#if (BACK_TEXTURE_COUNT > 4)
	PROCESS_VS_TEXTURE_BACK_4(BACK_TEXTURE4_WORLD);
#endif
#if (BACK_TEXTURE_COUNT > 5)
	PROCESS_VS_TEXTURE_BACK_5(BACK_TEXTURE5_WORLD);
#endif
#if (BACK_TEXTURE_COUNT > 6)
	PROCESS_VS_TEXTURE_BACK_6(BACK_TEXTURE6_WORLD);
#endif
#if (BACK_TEXTURE_COUNT > 7)
	PROCESS_VS_TEXTURE_BACK_7(BACK_TEXTURE7_WORLD);
#endif

#ifdef HAS_FACE_PATTERN
	result.uvzwfp.x = ScaledWindowWidth * result.position.x;
	result.uvzwfp.y = -ScaledWindowHeight * result.position.y;
	result.uvzwfp.z = 0.0;
	result.uvzwfp.w = result.position.w;
	#ifndef CAMERA_PERSPECTIVE
		#ifdef HAS_TRANSPARENCY_STIPPLE
			float texel_offset = 0.5 / 16.0;
		#else
			float texel_offset = 0.5 / 32.0;
		#endif
		result.uvzwfp.xy += texel_offset;
	#endif
#endif

#ifdef HAS_LINE_PATTERN
	result.uvlp.x = vertex.uvlp.x;
	result.uvlp.y = vertex.uvlp.y;
	result.uvlp.z = 0.0;
	result.uvlp.w = 0.0;
#endif

#ifdef ENVIRONMENT_TEXTURE
	// Cubemaps with per pixel lighting handled in pixel shader
	#if !defined(CUBE_ENVIRONMENT_MAP) || !defined(PER_PIXEL_LIGHTING)
		#ifdef HAS_PHYSICAL_REFLECTION
			// Reflect in object space
			result.uvenv = reflect(normalize(vertex.position - CameraPosition), vertex.normal);
		#else
			// Reflect in eye space
			eye_normal.xy *= DRIVER_SPECIFIC_FLIP;
			result.uvenv = reflect(float3(0,0,1), eye_normal);
		#endif
	
		#ifndef CUBE_ENVIRONMENT_MAP
			// Convert from cubemap coordinates to 2D spheremap
			result.uvenv = spheremap( result.uvenv );
			result.uvenv = (mul(float4(result.uvenv,1.0), EnvironmentTextureMatrix)).xyz;
		#endif
	#endif
#endif
#ifdef SPECULAR_TEXTURE
	result.uvspec = (mul(float4(vertex.uvspec, 0.0, 1.0), SpecularTextureMatrix)).xy;
#endif
#ifdef BUMP_TEXTURE
	result.uvbump = (mul(float4(vertex.uvbump, 0.0, 1.0), BumpTextureMatrix)).xy;
#endif
#ifdef MIRROR_TEXTURE
	result.uvmirror = (mul(float4(vertex.uvmirror, 0.0, 1.0), MirrorTextureMatrix)).xy;
#endif
#ifdef TRANSMISSION_TEXTURE
	result.uvtransmission = (mul(float4(vertex.uvtransmission, 0.0, 1.0), TransmissionTextureMatrix)).xy;
#endif
#ifdef EMISSION_TEXTURE
	result.uvemission = (mul(float4(vertex.uvemission, 0.0, 1.0), EmissionTextureMatrix)).xy;
#endif
		
#if (SHADOW_MAP_COUNT > 0)
	result.uvsm0 = mul( float4(vertex.position,1), ShadowMaps[0].transform);
#ifdef SHADOW_MAP_DISTORTION
	result.uvsm0 = distort_shadowmap_position( result.uvsm0, ShadowMaps[0].distortion );
#endif // SHADOW_MAP_DISTORTION
#if defined(SHADOW_MAP_JITTER) || defined(SHADOW_MAP_SLICE_COUNT)
	result.screen_position = result.position;
#endif // SHADOW_MAP_JITTER
#endif
#if (SHADOW_MAP_COUNT > 1)
	result.uvsm1 = mul( float4(vertex.position,1), ShadowMaps[1].transform);
#ifdef SHADOW_MAP_DISTORTION
	result.uvsm1 = distort_shadowmap_position( result.uvsm0, ShadowMaps[1].distortion );
#endif // SHADOW_MAP_DISTORTION
#endif
#if (SHADOW_MAP_COUNT > 2)
	result.uvsm2 = mul( float4(vertex.position,1), ShadowMaps[2].transform);
#ifdef SHADOW_MAP_DISTORTION
	result.uvsm2 = distort_shadowmap_position( result.uvsm0, ShadowMaps[2].distortion );
#endif // SHADOW_MAP_DISTORTION
#endif
#if (SHADOW_MAP_COUNT > 3)
	result.uvsm3 = mul( float4(vertex.position,1), ShadowMaps[3].transform);
#ifdef SHADOW_MAP_DISTORTION
	result.uvsm3 = distort_shadowmap_position( result.uvsm0, ShadowMaps[3].distortion );
#endif // SHADOW_MAP_DISTORTION
#endif

#if (CUTTING_PLANE_COUNT > 0)
	#ifdef DC
		float4 cutting_position = float4(vertex.position,1.0);
	#else
		float4 cutting_position = eye_position;
	#endif

	result.uvcp0 = float4(dot(cutting_position, CuttingPlanes[0]),1.0,1.0,1.0);
#endif
#if (CUTTING_PLANE_COUNT > 1)
	result.uvcp0.y = dot(cutting_position, CuttingPlanes[1]);
#endif
#if (CUTTING_PLANE_COUNT > 2)
	result.uvcp0.z = dot(cutting_position, CuttingPlanes[2]);
#endif
#if (CUTTING_PLANE_COUNT > 3)
	result.uvcp0.w = dot(cutting_position, CuttingPlanes[3]);
#endif
#if (CUTTING_PLANE_COUNT > 4)
	result.uvcp1 = float4(dot(cutting_position, CuttingPlanes[4]),1.0,1.0,1.0);
#endif
#if (CUTTING_PLANE_COUNT > 5)
	result.uvcp1.y = dot(cutting_position, CuttingPlanes[5]);
#endif
#if (CUTTING_PLANE_COUNT > 6)
	result.uvcp1.z = dot(cutting_position, CuttingPlanes[6]);
#endif
#if (CUTTING_PLANE_COUNT > 7)
	result.uvcp1.w = dot(cutting_position, CuttingPlanes[7]);
#endif
#if (CUTTING_PLANE_COUNT > 8)
	result.uvcp2 = float4(dot(cutting_position, CuttingPlanes[8]),1.0,1.0,1.0);
#endif
#if (CUTTING_PLANE_COUNT > 9)
	result.uvcp2.y = dot(cutting_position, CuttingPlanes[9]);
#endif
#if (CUTTING_PLANE_COUNT > 10)
	result.uvcp2.z = dot(cutting_position, CuttingPlanes[10]);
#endif
#if (CUTTING_PLANE_COUNT > 11)
	result.uvcp2.w = dot(cutting_position, CuttingPlanes[11]);
#endif
#if (CUTTING_PLANE_COUNT > 12)
	result.uvcp3 = float4(dot(cutting_position, CuttingPlanes[12]),1.0,1.0,1.0);
#endif
#if (CUTTING_PLANE_COUNT > 13)
	result.uvcp3.y = dot(cutting_position, CuttingPlanes[13]);
#endif
#if (CUTTING_PLANE_COUNT > 14)
	result.uvcp3.z = dot(cutting_position, CuttingPlanes[14]);
// SIL: Only support up to 15 - need to make space in shader ID for one more to complete.
#endif

#ifdef PRIORITY_HSRA
	result.position.z = vertex.priority * result.position.w;
#endif

#if defined(DEPTH_PEELING) || defined(DEPTH_WRITING)
	// Copy position to iterator
	result.peel_position = result.position;
#endif

#ifdef HAS_ATMOSPHERIC_ATTENUATION
	float fog_z = abs(eye_position.z);
	result.fog = (fog_z - AtmosphericAttenuation.yon) / (AtmosphericAttenuation.hither - AtmosphericAttenuation.yon);
#endif

#else // CREATE_SHADOW_MAP

#ifdef SHADOW_MAP_DISTORTION
	// Distort position
	result.position = distort_shadowmap_position( result.position, ShadowDistortion );
#endif // SHADOW_MAP_DISTORTION

	// Output position to texcoords
	result.shadow_position = result.position;

#endif // ndef CREATE_SHADOW_MAP

	// Done
	return result;
}
