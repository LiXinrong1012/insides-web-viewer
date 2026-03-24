//
// Copyright (c) 2000 by Tech Soft 3D, LLC.
// The information contained herein is confidential and proprietary to
// Tech Soft 3D, LLC., and considered a trade secret as defined under
// civil and criminal statutes.  Tech Soft 3D shall pursue its civil
// and criminal remedies in the event of unauthorized use or misappropriation
// of its trade secrets.  Use of this information by anyone other than
// authorized employees of Tech Soft 3D, LLC. is granted only under a
// written non-disclosure agreement, expressly prescribing the scope and
// manner of such use.
//
// $Header: /files/homes/master/cvs/hoops_master/hoops_mvo/source/HPShowCache.h,v 1.8 2008-03-28 21:12:44 nathan Exp $
//


#ifndef _HPSHOWCACHE_H
#define _HPSHOWCACHE_H

#ifdef H_PACK_8
#pragma pack(push)
#pragma pack(8)
#endif

#include "HTools.h"
#include "HGlobals.h"
#include "vhash.h"


#define PSHOW_CACHE_MODELLING_MATRIX	0x00000001
#define PSHOW_CACHE_VISIBILITY			0x00000002
#define PSHOW_CACHE_RENDERING_OPTIONS	0x00000004
#define PSHOW_CACHE_HANDEDNESS			0x00000008
#define PSHOW_CACHE_HEURISTICS			0x00000010
#define PSHOW_CACHE_TEXT_FONT			0x00000020
#define PSHOW_CACHE_TEXT_ALIGNMENT		0x00000040
#define PSHOW_CACHE_TEXT_PATH			0x00000080
#define PSHOW_CACHE_TEXT_SPACING		0x00000100
#define PSHOW_CACHE_MARKER_SIZE			0x00000200
#define PSHOW_CACHE_MARKER_SYMBOL		0x00000400
#define PSHOW_CACHE_LINE_WEIGHT			0x00000800
#define PSHOW_CACHE_LINE_PATTERN		0x00001000
#define PSHOW_CACHE_COLOR				0x00002000
#define PSHOW_CACHE_EDGE_WEIGHT			0x00004000
#define PSHOW_CACHE_EDGE_PATTERN		0x00008000
#define PSHOW_CACHE_CAMERA				0x00010000

class HPShowCache
{
public:
	HPShowCache():flags(0), path(0), visibility(0), rendering_options(0), handedness(0), heuristics(0),
		text_font(0), text_alignment(0), text_spacing(1.f), marker_size(0), marker_symbol(0),
		line_weight(0), line_pattern(0), color(0), color_map(0), edge_weight(0), 
		edge_pattern(0), camera_position(0,0,0), camera_target(0,0,0), camera_up(0,0,0), 
		camera_width(0.f), camera_height(0.f), camera_projection(0)
	{
		HC_Compute_Identity_Matrix(modelling_matrix);
		text_path[0]=1.f;	text_path[1]=0.f;	text_path[2]=0.f;
	}

	~HPShowCache()
	{
		if(path)
			delete [] path;
		if(visibility)
			delete [] visibility;
		if(rendering_options)
			delete [] rendering_options;
		if(handedness)
			delete [] handedness;
		if(heuristics)
			delete [] heuristics;
		if(text_font)
			delete [] text_font;
		if(text_alignment)
			delete [] text_alignment;
		if(marker_size)
			delete [] marker_size;
		if(marker_symbol)
			delete [] marker_symbol;
		if(line_weight)
			delete [] line_weight;
		if(line_pattern)
			delete [] line_pattern;
		if(color)
			delete [] color;
		if(color_map)
			delete [] color_map;
		if(edge_weight)
			delete [] edge_weight;
		if(edge_pattern)
			delete [] edge_pattern;	
		if(camera_projection)
			delete [] camera_projection;
	}

	unsigned int flags;

	HC_KEY*	path;
	int		path_count;

	float	modelling_matrix[16];
	char *	visibility;
	char *	rendering_options;
	char *	handedness;
	char *	heuristics;
	char *	text_font;
	char *	text_alignment;
	float	text_path [3];
	float	text_spacing;
	char *	marker_size;
	char *	marker_symbol;
	char *	line_weight;
	char *	line_pattern;
	char *	color;
	char *	color_map;
	char *	edge_weight;
	char *	edge_pattern;
	HPoint	camera_position;
	HPoint	camera_target;
	HPoint	camera_up;
	float	camera_width;
	float	camera_height;
	char *	camera_projection;
};

//typedef VHash<HC_KEY, HPShowCache *> HVHashPShowCache;

class HVHashPShowCache: public VHash<HC_KEY, HPShowCache *>
{

};


#ifdef H_PACK_8
#pragma pack(pop)
#endif

#endif



















