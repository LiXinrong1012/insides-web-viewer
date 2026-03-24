// Copyright (c) 2007 by Tech Soft 3D, LLC.
// all rights reserved
// $Id: h3d_post_reproject.hlsl,v 1.2 2009-04-29 21:09:53 warren Exp $
 
/* Uniforms ******************************************************************/

uniform sampler2D Depth reg(s0);
uniform sampler2D Scene reg(s1);

uniform float3 EyeDir;

#define ReliefMapDepth 1.0

/* Code **********************************************************************/

// Ray marching code from Fabio Policarpo's original relief mapping paper.

// setup ray pos and dir based on view vector
// and apply depth bias and depth factor
void setup_ray(in float2 uv,out float3 p,out float3 v)
{
	p = float3(uv,0.0);
	v = normalize(EyeDir);
	
	v.z = abs(v.z);

	v.xy *= ReliefMapDepth;
}

// ray intersect depth map using linear and binary searches
// depth value stored in alpha channel (black at is object surface)
void ray_intersect_relief(
	sampler2D relief_map,
	inout float3 p,
	inout float3 v)
{
// SM3
	// const int num_steps_lin=12;
	// const int num_steps_bin=6;

// SM2
	const int num_steps_lin=2;
	const int num_steps_bin=1;
	
	v /= v.z*num_steps_lin;
	
	int i;
	for( i=0;i<num_steps_lin;i++ )
	{
		float4 tex = tex2D(relief_map, p.xy);
		if (p.z<tex.x)
			p+=v;
	}
	
	for( i=0;i<num_steps_bin;i++ )
	{
		v *= 0.5;
		float4 tex = tex2D(relief_map, p.xy);
		if (p.z<tex.x)
			p+=v;
		else
			p-=v;
	}
}

void post_pixel( 
	float2 in_uv,
	out float4 color,
	out float depth)
{
	float3 p,v;
	
	setup_ray(in_uv,p,v);

	ray_intersect_relief(Depth,p.xyz,v);

	color = tex2D(Scene, p.xy);
	depth = tex2D(Depth, p.xy).r;
	
// For verification
//	color = float4(uv, 0, 0);
//	color = float4(iterator.normal,1);
//	color = float4(EyeDir,1);
} 

