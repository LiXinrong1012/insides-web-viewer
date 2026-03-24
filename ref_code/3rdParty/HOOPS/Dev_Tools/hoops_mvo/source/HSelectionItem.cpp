//
// Copyright (c) 2004 by Tech Soft 3D, LLC.
// The information contained herein is confidential and proprietary to
// Tech Soft 3D, LLC., and considered a trade secret as defined under
// civil and criminal statutes.  Tech Soft 3D shall pursue its civil
// and criminal remedies in the event of unauthorized use or misappropriation
// of its trade secrets.  Use of this information by anyone other than
// authorized employees of Tech Soft 3D, LLC. is granted only under a
// written non-disclosure agreement, expressly prescribing the scope and
// manner of such use.
//
// $Header: /files/homes/master/cvs/hoops_master/hoops_mvo/source/HSelectionItem.cpp,v 1.135 2010-12-22 22:56:20 nathan Exp $
//

// HSelectionItem.cpp : implementation of the HSelectionItem class
//

#include <stdio.h>
#include <string.h>

#include "HSelectionItem.h"
#include "HSelectionSet.h"
#include "HUtility.h"
#include "HUtilityAnnotation.h"
#include "HBaseView.h"
#include "HPShowCache.h"
#include "HEventManager.h"

#include "vlist.h"
#include "vhash.h"

/////////////////////////////////////////////////////////////////////////////
// HSelectionItem
//  An interface to a selection item held in a list the HSelectionSet class. This class is meant to be derived 
//  from and have it's virtual function implemented

HSelectionItem::HSelectionItem(HC_KEY key, HSelectionSet * selection_set) : m_key(key), m_pSelectionSet(selection_set)
{
	m_FullPath = 0;
	m_FullPathCount = 0;
}


HSelectionItem::~HSelectionItem( void )
{
}


bool HSelectionItem::Equals(const HSelectionItem* i2) const
{
	// if primary selection key is same
	if( this->GetKey() != i2->GetKey() )
		return false;

	// return false if they are of different type
	if( !streq(this->GetName(), i2->GetName()) )
		return false;

	 /*TODO: may be this should just always return false*/

	return true;
}


HC_KEY HSelectionItem::GetSegmentKey() const
{
    char keytype[MVO_BUFFER_SIZE];
	HC_KEY seg_key;

    HC_Show_Key_Type(m_key, keytype);

    if (streq(keytype, "segment")) 
		seg_key = m_key;
	else
	{
		// this is entity selection, check if highlighted
		seg_key = HC_KShow_Owner_Original_Key(m_key);
		if( IsHighlighted() )
			// walk one more level up
			seg_key = HC_KShow_Owner_Original_Key(seg_key);
	}
	return seg_key;
}


const HC_KEY *HSelectionItem::GetFullPathKeys(HBaseView *view)
{
	if (!m_FullPath) { 
		int keycount;
		HC_KEY temparray[ 512 ], key, limit;

		key = m_key;
		limit = HC_KCreate_Segment ("/"); //doesn't actually create anything-- just gets the key
		keycount = 0;
		while (keycount < 510) {
			temparray[ keycount++ ] = key;
			key = HC_KShow_Owner_Original_Key (key);
			if (key == view->GetModelKey() || key == limit)
				break;
		}
		temparray[ keycount++ ] = view->GetModelKey();
		temparray[ keycount++ ] = key = view->GetIncludeLinkKey();
		while (keycount < 512) {
			key = HC_KShow_Owner_Original_Key (key);
			temparray[ keycount++ ] = key;
			if (key == view->GetViewKey() || key == limit)
				break;
		}
		m_FullPathCount = keycount;
		m_FullPath = new HC_KEY[ keycount ];
		memcpy(&m_FullPath[0], &temparray[0], keycount*sizeof(HC_KEY));
	}
	return m_FullPath;
}

void HSelectionItem::GetFullPathKeys (HBaseView *view, HC_KEY *path) {
	const HC_KEY *temp = GetFullPathKeys(view);
	int path_size = GetFullPathCount(view);

	memcpy(path, temp, path_size * sizeof(HC_KEY));
}


int HSelectionItem::GetFullPathCount (HBaseView *view)
{
	GetFullPathKeys (view);
	return m_FullPathCount;
}





/////////////////////////////////////////////////////////////////////////////
// HSmartSelItem
/*!
  Implementation of HSelectionItem class which handles instanced segments and entities. 
*/

enum HHighlightObjectType
{
	HHighlightSegment,
	HHighlightGeometry,
	HHighlightRegion,
	HHighlightSubentity
};

struct HSubentityPassthrough
{
	int face_count;
	int * faces;
	int vertex_count;
	int * vertex1;
	int * vertex2;
	bool maintain_maps;
	int vertex_map_count;
	int * vertex_map;
	int face_map_count;
	int * face_map;
	int highlight_subentity;
};

#define HTYPE_NONE				0x0000
#define HTYPE_TEXT				0x0001
#define	HTYPE_MARKER			0x0002
#define	HTYPE_LINE				0x0004
#define	HTYPE_SHELL_MESH		0x0008
#define	HTYPE_OTHER				0x0010

#define HSPECIAL_NOTHING		0x0000
#define HSPECIAL_TRANSMISSION	0x0001
#define	HSPECIAL_SCREEN_RANGE	0x0002
#define	HSPECIAL_DEPTH_RANGE	0x0004
#define	HSPECIAL_IMAGE_SCALE	0x0008
#define HSPECIAL_HANDEDNESS		0x0010
#define HSPECIAL_MASK_TRANSFORM 0x0020
#define HSPECIAL_GENERAL_DISPLACEMENT 0x0040
#define HSPECIAL_CAMERA			0x0080
#define HSPECIAL_ANTIALIAS		0x0100


//from driver.h
#define RED_GRAYNESS			0.3125f
#define GREEN_GRAYNESS			0.5000f
#define BLUE_GRAYNESS			0.1875f

static int pshow_net_color_map(int count, const HC_KEY *keys, char*& out_color_map)
{
	int length = 0;
	HC_PShow_Net_Color_Map_Length(count,keys,&length);
	out_color_map = new char[length+1];
	HC_PShow_Net_Color_Map(count,keys,out_color_map);

	return length;
}

static HC_KEY ref_highlight_common(HC_KEY key, int incl_count, const HC_KEY * const incl_path, 
								 HSelectionSet * selection, HHighlightObjectType hl_type, 
								 int region = -1, void * data=0)
{
	HC_KEY seg_key=INVALID_KEY, ref_key=INVALID_KEY;
	float mod_mat[16];
	char type[128], align[128], vis[MVO_BUFFER_SIZE]="\0", whand[128]="\0", phand[128]="\0", 
		heur[MVO_BUFFER_SIZE], color[MVO_BUFFER_SIZE], ropt[MVO_BUFFER_SIZE], marker_size[MVO_BUFFER_SIZE], 
		line_weight[MVO_BUFFER_SIZE], line_pattern[MVO_BUFFER_SIZE], text_font[MVO_BUFFER_SIZE], 
		marker_symbol[MVO_BUFFER_SIZE], edge_pattern[MVO_BUFFER_SIZE], edge_weight[MVO_BUFFER_SIZE],
		camera_projection[MVO_BUFFER_SIZE], scene_projection[MVO_BUFFER_SIZE],
		anti_alias[MVO_BUFFER_SIZE], mask_transform[MVO_BUFFER_SIZE];
	char *color_map = 0;
	bool hsra=false, inv_trans=selection->GetHighlightMode()==InverseTransparency, scene_camera_exists;
	char *cursor=0;
	int gd=0;
	float sr_1=-1.f, sr_2=1.f, sr_3=-1.f, sr_4=1.f, dr_1=0.f, dr_2=1.f, is_1=1.f, is_2=1.f;
	float path_x=0, path_y=0, path_z=0, spacing=-1.f;
	float intensity=0.f;
	int i, j, has_type=HTYPE_NONE, special=HSPECIAL_NOTHING;
	int path_count = incl_count+2;
	HC_KEY *path = new HC_KEY[path_count];
	HPShowCache * cache=0;
	HPoint	camera_position, camera_target, camera_up;
	float	camera_width, camera_height;
	HPoint	scene_position, scene_target, scene_up;
	float	scene_width = 0.0f, scene_height = 0.0f;

	if(hl_type==HHighlightSegment && incl_count != 0)
	{
		HC_KEY tmp_key;
		HC_Show_Key_Type(incl_path[incl_count-1], type);
		if(streq(type, "include"))
		{
			tmp_key = HC_KShow_Include_Segment(incl_path[incl_count-1]);
			if(tmp_key == key)
			{
				seg_key = HC_KShow_Owner_Original_Key(incl_path[incl_count-1]);
				--incl_count;
				--path_count;
			}
		}
	}
	if(seg_key == INVALID_KEY)
		seg_key = HC_KShow_Owner_Original_Key(key);

	//-- Check if this is an object key (manipulator handle, annotation) --
	char obj_type[512];
	HC_KEY obj_key=HObjectManager::FindHObjectSegment(seg_key, obj_type);
	if(obj_key!=seg_key || strstr(obj_type, "Annotation"))
	{
		delete [] path;
		return INVALID_KEY;
	}
	//-- Done checking for objects --
		
	//-- Set up the path for PShow --
	path[0]=seg_key;
	for(i=1; i<incl_count; ++i)
		path[i]=incl_path[incl_count-i];
	path[path_count-2] = HC_KShow_Owner_Original_Key(path[path_count-3]);
	path[path_count-1] = INVALID_KEY;
	
	//-- Get the scene camera to compare to local camera
	HC_Open_Segment_By_Key(incl_path[0]);
	HC_Open_Segment("scene");
		if(scene_camera_exists=(HC_Show_Existence("camera") > 0))
			HC_Show_Camera(&scene_position, &scene_target, &scene_up, &scene_width, &scene_height, scene_projection);
	HC_Close_Segment();
	HC_Close_Segment();


	HC_Show_Key_Type(key, type);
	if(streq(type, "reference"))
	{
		key=HC_KShow_Reference_Geometry(key);
		HC_Show_Key_Type(key, type);
	}

	//--Collect basic information --
	//--Use the cache if we've got one --
	if(selection->GetPShowCache())
	{
		bool cache_hit=false;
	
		for(i=0; ; ++i)
		{
			cache=0;
			if (VHASH_STATUS_SUCCESS != 
				selection->GetPShowCache()->LookupNthItem(seg_key, i, &cache))
				break;
			
			cache_hit=true;
			if(path_count == cache->path_count)
			{
				for(j=0; j<cache->path_count; ++j)
				{
					if(cache->path[j]!=path[j])
					{
						cache_hit=false;
						break;
					}
				}
			}
			else 
				cache_hit=false;
			
			if(cache_hit)
				break;
		}
		
		if(!cache || !cache_hit)
		{
			cache = new HPShowCache;
			cache->path_count=path_count;
			cache->path=new HC_KEY [path_count];
			memcpy(cache->path, path, path_count*sizeof(HC_KEY));

			selection->GetPShowCache()->InsertItem(seg_key, cache);
		}
		
		if(cache->flags & PSHOW_CACHE_MODELLING_MATRIX)
			memcpy(mod_mat, cache->modelling_matrix, 16*sizeof(float));
		else
		{
			HC_PShow_Net_Modelling_Matrix(path_count, path, mod_mat);
			memcpy(cache->modelling_matrix, mod_mat, 16*sizeof(float));
			cache->flags|=PSHOW_CACHE_MODELLING_MATRIX;
		}

		if(cache->flags & PSHOW_CACHE_VISIBILITY)
			strcpy(vis, cache->visibility);
		else
		{
			HC_PShow_Net_Visibility(path_count, path, vis);
			cache->visibility=new char[strlen(vis)+1];
			strcpy(cache->visibility, vis);
			cache->flags|=PSHOW_CACHE_VISIBILITY;
		}

		if(cache->flags & PSHOW_CACHE_COLOR)
		{
			strcpy(color, cache->color);

			int length = (int)strlen(cache->color_map) + 1;
			color_map = new char[length];			
			strcpy(color_map, cache->color_map);
		}

		else
		{
			HC_PShow_Net_Color(path_count, path, color);
			cache->color=new char[strlen(color)+1];
			strcpy(cache->color, color);

			int length = pshow_net_color_map(path_count,path,color_map);
			cache->color_map = new char[length];
			memcpy(cache->color_map,color_map,length*sizeof(char));

			cache->flags|=PSHOW_CACHE_COLOR;
		}

		if(cache->flags & PSHOW_CACHE_RENDERING_OPTIONS)
			strcpy(ropt, cache->rendering_options);
		else
		{
			HC_PShow_Net_Rendering_Options(path_count, path, ropt);
			cache->rendering_options=new char[strlen(ropt)+1];
			strcpy(cache->rendering_options, ropt);
			cache->flags|=PSHOW_CACHE_RENDERING_OPTIONS;
		}

		if(cache->flags & PSHOW_CACHE_HANDEDNESS)
			strcpy(whand, cache->handedness);
		else
		{
			HC_PShow_Net_Handedness(path_count, path, whand);
			cache->handedness=new char[strlen(whand)+1];
			strcpy(cache->handedness, whand);
			cache->flags|=PSHOW_CACHE_HANDEDNESS;
		}

		if(cache->flags & PSHOW_CACHE_HEURISTICS)
			strcpy(heur, cache->heuristics);
		else
		{
			HC_PShow_Net_Heuristics(path_count, path, heur);
			cache->heuristics=new char[strlen(heur)+1];
			strcpy(cache->heuristics, heur);
			cache->flags|=PSHOW_CACHE_HEURISTICS;
		}		

		if(cache->flags & PSHOW_CACHE_CAMERA)
		{
			camera_position=cache->camera_position;
			camera_target=cache->camera_target;
			camera_up=cache->camera_up;
			camera_width=cache->camera_width;
			camera_height=cache->camera_height;
			strcpy(camera_projection, cache->camera_projection);
		}
		else
		{
			HC_PShow_Net_Camera(path_count, path, &camera_position, &camera_target, &camera_up, 
				&camera_width, &camera_height, camera_projection);
			
			cache->camera_position=camera_position;
			cache->camera_target=camera_target;
			cache->camera_up=camera_up;
			cache->camera_width=camera_width;
			cache->camera_height=camera_height;
			cache->camera_projection=new char[strlen(camera_projection)+1];
			strcpy(cache->camera_projection, camera_projection);			
			cache->flags|=PSHOW_CACHE_CAMERA;
		}		
		
		if(cache->flags & PSHOW_CACHE_MARKER_SIZE)
			strcpy(marker_size, cache->marker_size);
		else
		{
			HC_PShow_Net_Var_Marker_Size(path_count, path, marker_size);
			cache->marker_size=new char [strlen(marker_size)+1];
			strcpy(cache->marker_size, marker_size);
			cache->flags|=PSHOW_CACHE_MARKER_SIZE;
		}

		if(cache->flags & PSHOW_CACHE_MARKER_SYMBOL)
			strcpy(marker_symbol, cache->marker_symbol);
		else
		{
			HC_PShow_Net_Marker_Symbol(path_count, path, marker_symbol);
			cache->marker_symbol=new char[strlen(marker_symbol)+1];
			strcpy(cache->marker_symbol, marker_symbol);
			cache->flags|=PSHOW_CACHE_MARKER_SYMBOL;
		}
	}
	else
	{
		HC_PShow_Net_Modelling_Matrix(path_count, path, mod_mat);
		HC_PShow_Net_Visibility(path_count, path, vis);
		HC_PShow_Net_Color(path_count, path, color);
		pshow_net_color_map(path_count,path,color_map);
		HC_PShow_Net_Rendering_Options(path_count, path, ropt);
		HC_PShow_Net_Handedness(path_count, path, whand);
		HC_PShow_Net_Heuristics(path_count, path, heur);	
		HC_PShow_Net_Camera(path_count, path, &camera_position, &camera_target, &camera_up, 
				&camera_width, &camera_height, camera_projection);
		HC_PShow_Net_Var_Marker_Size(path_count, path, marker_size);
		HC_PShow_Net_Marker_Symbol(path_count, path, marker_symbol);
	}
	//-- Done collecting basic information --


	//-- Collect type-specific information and set has_type --
	if(hl_type==HHighlightRegion || hl_type==HHighlightSubentity)
		has_type=HTYPE_SHELL_MESH;
	else 
	{
		if((hl_type==HHighlightSegment && HC_Show_Existence_By_Key(key, "text")) ||
			(hl_type==HHighlightGeometry && streq(type, "text")))
		{
			has_type|=HTYPE_TEXT;
			if(cache)
			{
				if(cache->flags & PSHOW_CACHE_TEXT_FONT)
					strcpy(text_font, cache->text_font);
				else
				{
					HC_PShow_Net_Text_Font(path_count, path, text_font);
					cache->text_font=new char[strlen(text_font)+1];
					strcpy(cache->text_font, text_font);
					cache->flags|=PSHOW_CACHE_TEXT_FONT;
				}
				
				if(cache->flags & PSHOW_CACHE_TEXT_ALIGNMENT)
					strcpy(align, cache->text_alignment);
				else
				{
					HC_PShow_Net_Text_Alignment(path_count, path, align);
					cache->text_alignment=new char[strlen(align)+1];
					strcpy(cache->text_alignment, align);
					cache->flags|=PSHOW_CACHE_TEXT_ALIGNMENT;
				}

				if(cache->flags & PSHOW_CACHE_TEXT_PATH)
				{
					path_x=cache->text_path[0];
					path_y=cache->text_path[1];
					path_z=cache->text_path[2];
				}
				else
				{
					HC_PShow_Net_Text_Path(path_count, path, &path_x, &path_y, &path_z);
					cache->text_path[0]=path_x;
					cache->text_path[1]=path_y;
					cache->text_path[2]=path_z;
					cache->flags|=PSHOW_CACHE_TEXT_PATH;
				}

				if(cache->flags & PSHOW_CACHE_TEXT_SPACING)
					spacing=cache->text_spacing;
				else
				{
					HC_PShow_Net_Text_Spacing(path_count, path, &spacing);
					cache->text_spacing=spacing;
					cache->flags|=PSHOW_CACHE_TEXT_SPACING;
				}
			}
			else
			{
				HC_PShow_Net_Text_Font(path_count, path, text_font);
				HC_PShow_Net_Text_Alignment(path_count, path, align);
				HC_PShow_Net_Text_Path(path_count, path, &path_x, &path_y, &path_z);
				HC_PShow_Net_Text_Spacing(path_count, path, &spacing);
			}
		}

		if((hl_type==HHighlightSegment && HC_Show_Existence_By_Key(key, "marker")) ||
			(hl_type==HHighlightGeometry && streq(type, "marker")))
		{
			has_type|=HTYPE_MARKER;
		}
		
		if((hl_type==HHighlightSegment && HC_Show_Existence_By_Key(key, "circle, polylines, lines, elliptical arcs, circular arcs, NURBS curve")) ||
			(hl_type==HHighlightGeometry && (strstr(type, "line") || strstr(type, "arc") || strstr(type, "curve") || strstr(type, "circle"))))
		{
			has_type|=HTYPE_LINE;
			if(cache)
			{
				if(cache->flags & PSHOW_CACHE_LINE_WEIGHT)
					strcpy(line_weight, cache->line_weight);
				else
				{
					HC_PShow_Net_Var_Line_Weight(path_count, path, line_weight);
					cache->line_weight=new char[strlen(line_weight)+1];
					strcpy(cache->line_weight, line_weight);
					cache->flags|=PSHOW_CACHE_LINE_WEIGHT;
				}

				if(cache->flags & PSHOW_CACHE_LINE_PATTERN)
					strcpy(line_pattern, cache->line_pattern);
				else
				{
					HC_PShow_Net_Line_Pattern(path_count, path, line_pattern);
					cache->line_pattern=new char[strlen(line_pattern)+1];
					strcpy(cache->line_pattern, line_pattern);
					cache->flags|=PSHOW_CACHE_LINE_PATTERN;
				}
			}
			else
			{
				HC_PShow_Net_Var_Line_Weight(path_count, path, line_weight);
				HC_PShow_Net_Line_Pattern(path_count, path, line_pattern);
			}
		}	
		
		if((hl_type==HHighlightSegment && HC_Show_Existence_By_Key(key, "shells, meshes")) ||
			(hl_type==HHighlightGeometry && (streq(type, "shell") || streq(type, "mesh"))))
			has_type|=HTYPE_SHELL_MESH;
		
		if(hl_type==HHighlightSegment || (hl_type==HHighlightGeometry && strstr(type, "circle")) )
			has_type|=HTYPE_OTHER;
	}
	
	if(has_type & HTYPE_SHELL_MESH || has_type & HTYPE_OTHER)
	{
		if(cache)
		{
			if(cache->flags & PSHOW_CACHE_EDGE_WEIGHT)
				strcpy(edge_weight, cache->edge_weight);
			else
			{
				HC_PShow_Net_Var_Edge_Weight(path_count, path, edge_weight);
				cache->edge_weight=new char[strlen(edge_weight)+1];
				strcpy(cache->edge_weight, edge_weight);
				cache->flags|=PSHOW_CACHE_EDGE_WEIGHT;
			}

			if(cache->flags & PSHOW_CACHE_EDGE_PATTERN)
				strcpy(edge_pattern, cache->edge_pattern);
			else
			{
				HC_PShow_Net_Edge_Pattern (path_count, path, edge_pattern);
				cache->edge_pattern=new char[strlen(edge_pattern)+1];
				strcpy(cache->edge_pattern, edge_pattern);
				cache->flags|=PSHOW_CACHE_EDGE_PATTERN;
			}
		}	
		else
		{
			HC_PShow_Net_Var_Edge_Weight(path_count, path, edge_weight);
			HC_PShow_Net_Edge_Pattern (path_count, path, edge_pattern);
		}
	}
	//-- Done collecting type-specific information --


	//-- Collect *special* information (if any) --
	if(color[0]!='\0' && !inv_trans)
	{
		cursor=strstr(color, "face=");
		cursor=strstr(cursor, "transmission");
		if(cursor && (has_type & HTYPE_OTHER || has_type & HTYPE_SHELL_MESH))
		{
			char clr_tmp[MVO_BUFFER_SIZE];
			HPoint tc;

			cursor+=13; //"transmission="
			HC_Parse_String(cursor, ",", 0, clr_tmp);
			HC_Compute_Color(clr_tmp, "RGB", &tc);
			intensity = tc.x*RED_GRAYNESS + tc.y*GREEN_GRAYNESS + tc.z*BLUE_GRAYNESS;
			intensity = (float)((int)((intensity+0.005)*100))/100;  //round to hundreths place
			if(intensity>0.f)
			{
				HCLOCALE(sprintf(color, "faces = transmission = (r=%f g=%f b=%f)", intensity, intensity, intensity));
				special|=HSPECIAL_TRANSMISSION;
			}
		}
	}

	if(ropt[0]!='\0')
	{
		cursor=strstr(ropt, "screen range");
		if(cursor)
		{
			HCLOCALE(sscanf(cursor, "screen range=(%f,%f,%f,%f)", &sr_1, &sr_2, &sr_3, &sr_4));
			
			if(sr_1!=-1.f || sr_2!=1.f || sr_3!=-1.f || sr_4!=1.f)
				special|=HSPECIAL_SCREEN_RANGE;
		}
		
		cursor=strstr(ropt, "depth range");
		if(cursor)
		{
			HCLOCALE(sscanf(cursor, "depth range=(%f,%f)", &dr_1, &dr_2));
			
			if(dr_1!=0.f || dr_2!=1.f)
				special|=HSPECIAL_DEPTH_RANGE;
		}
			
		
		cursor=strstr(ropt, "image scale");
		if(cursor)
		{
			HCLOCALE(sscanf(cursor, "image scale=(%f,%f)", &is_1, &is_2));

			if(is_1!=1.f || is_2!=1.f)
				special|=HSPECIAL_IMAGE_SCALE;
		}

		cursor=strstr(ropt, "hidden surface removal algorithm");
		if(cursor && hl_type!=HHighlightRegion)
		{
			char  hsra_tmp[128];

			cursor+=33; //"hidden surface removal algorithm="
			HC_Parse_String(cursor, ",", 0, hsra_tmp);

			if(strstr(hsra_tmp, "hidden line"))
				hsra=true;
		}

		cursor=strstr(ropt, "general displacement");
		if(cursor)
		{
			sscanf(cursor, "general displacement=%d", &gd);
			
			if(gd!=0)
				special|=HSPECIAL_GENERAL_DISPLACEMENT;
		}

		cursor=strstr(ropt, "anti-alias=");
		if(cursor)
		{			
			cursor += 11; // strlen("anti-alias=")

			char *aa = anti_alias;
			
			// multi-item case: anti-alias=(... 
			if ( *cursor == '(' )
			{	
				cursor++;
				while ( *cursor != ')' )							
					*aa++ = *cursor++;				
			}

			// single item case: anti-alias=...
			else
			{
				while ( *cursor != ',' )							
					*aa++ = *cursor++;				
			}

			*aa = 0;			
			special|=HSPECIAL_ANTIALIAS;
		}

		cursor=strstr(ropt, "mask transform=");
		if(cursor)
		{			
			cursor += 15; // strlen("mask transform=")
			char *mt = mask_transform;
			unsigned int parens = 0;
			
			do {
				if(*cursor == '(')
					++parens;
				else if(*cursor == ')')
					--parens;
				*mt++ = *cursor++;				
			} while(*cursor && (*cursor!=',' || parens!=0));
			*mt = 0;			
			//update the modelling matrix
			HC_Compute_Transform_By_Path(path_count-1, path, "object", "world", mod_mat);

			special|=HSPECIAL_MASK_TRANSFORM;
		}
	}

	
	if(whand[0]!='\0' || heur[0]!='\0')
	{
		if(whand[0]!='\0')
			special|=HSPECIAL_HANDEDNESS;

		if (!strstr(heur, "no polygon handedness")) 
		{
			cursor=strstr(heur, "polygon handedness");
			if(cursor) 
			{
				cursor+=19; //"polygon handedness="
				HC_Parse_String(cursor, ",", 0, phand);
				
				if(phand[0]!='\0')
					special|=HSPECIAL_HANDEDNESS;
			}		
		}
	}

	if(scene_camera_exists && (scene_position!=camera_position || scene_target!=camera_target || scene_up!=camera_up
		|| scene_width!=camera_width || scene_height!=camera_height 
		|| !streq(scene_projection, camera_projection)) )
	{
		special|=HSPECIAL_CAMERA;
	}
	//-- Done collecting special information -- 

	//-- Create the highlight reference --
	HC_Open_Segment_By_Key(selection->GetSelectionSegment());
		//-- If special information exists, create a child segment --
		if(special!=HSPECIAL_NOTHING)
		{
			if((has_type & HTYPE_OTHER || has_type & HTYPE_SHELL_MESH) && (special & HSPECIAL_TRANSMISSION))
			{
				char seg_name[128];

				HCLOCALE(sprintf(seg_name, "intensity_%f", intensity));
				HC_Open_Segment(seg_name);
					if(!HC_Show_Existence("color"))
						HC_Set_Color(color);
			}
			if(special & ~HSPECIAL_TRANSMISSION)
			{	
				char str_tmp[MVO_BUFFER_SIZE], new_ropt[MVO_BUFFER_SIZE] = "";

				seg_key = HC_KOpen_Segment("");
					if(special & HSPECIAL_SCREEN_RANGE)
					{
						HCLOCALE(sprintf(str_tmp, "screen range=(%f,%f,%f,%f)", sr_1, sr_2, sr_3, sr_4));
						strcat(new_ropt, str_tmp);
					}
					if(special & HSPECIAL_DEPTH_RANGE)
					{
						HCLOCALE(sprintf(str_tmp, "depth range=(%f,%f)", dr_1, dr_2));
						if(special & HSPECIAL_SCREEN_RANGE)
							strcat(new_ropt, ", ");
						strcat(new_ropt, str_tmp);
					}
					if(special & HSPECIAL_IMAGE_SCALE)
					{
						HCLOCALE(sprintf(str_tmp, "image scale=(%f,%f)", is_1, is_2));
						if(special & (HSPECIAL_SCREEN_RANGE | HSPECIAL_DEPTH_RANGE))
							strcat(new_ropt, ", ");
						strcat(new_ropt, str_tmp);
					}
					if(special & HSPECIAL_GENERAL_DISPLACEMENT)
					{
						HCLOCALE(sprintf(str_tmp, "general displacement=(%d)", gd));
						if(special & (HSPECIAL_SCREEN_RANGE | HSPECIAL_DEPTH_RANGE | HSPECIAL_IMAGE_SCALE))
							strcat(new_ropt, ", ");
						strcat(new_ropt, str_tmp);
					}
					if(special & HSPECIAL_ANTIALIAS)
					{
						sprintf(str_tmp, "anti-alias=(%s)", anti_alias);
						if(special & ( HSPECIAL_GENERAL_DISPLACEMENT | HSPECIAL_SCREEN_RANGE | HSPECIAL_DEPTH_RANGE | HSPECIAL_IMAGE_SCALE))
							strcat(new_ropt, ", ");
						strcat(new_ropt, str_tmp);
					}
					if(special & HSPECIAL_MASK_TRANSFORM)
					{
						sprintf(str_tmp, "mask transform=%s", mask_transform);
						if(special & ( HSPECIAL_ANTIALIAS | HSPECIAL_GENERAL_DISPLACEMENT | HSPECIAL_SCREEN_RANGE 
										| HSPECIAL_DEPTH_RANGE | HSPECIAL_IMAGE_SCALE))
							strcat(new_ropt, ", ");
						strcat(new_ropt, str_tmp);
					}
					if(special & (HSPECIAL_MASK_TRANSFORM | HSPECIAL_ANTIALIAS | HSPECIAL_SCREEN_RANGE 
									| HSPECIAL_DEPTH_RANGE | HSPECIAL_IMAGE_SCALE | HSPECIAL_GENERAL_DISPLACEMENT))
						HC_Set_Rendering_Options(new_ropt);
					
					if(special & HSPECIAL_HANDEDNESS)
					{
						if(whand[0]!='\0')
							HC_Set_Handedness(whand);
						if(phand[0]!='\0')
						{	
							sprintf(heur, "polygon handedness = %s", phand);
							HC_Set_Heuristics(heur);
						}
					}
					
					if(special & HSPECIAL_CAMERA)
						HC_Set_Camera(&camera_position, &camera_target, &camera_up, camera_width, 
							camera_height, camera_projection);
			}	
		}
		//-- Done handling special information --

		//-- Create the highlight reference --
		if(hl_type==HHighlightRegion)
		{
			if(!(special & ~HSPECIAL_TRANSMISSION))
				ref_key=HC_KOpen_Segment("");

			HC_Insert_Shell_From_Region(key, region, "");
			HC_Set_Selectability("off");
			if (!HUtility::IsIdentityMatrix(mod_mat))
				HC_Set_Modelling_Matrix(mod_mat);
			if (vis[0] != '\0') 				
				HC_Set_Visibility(vis);
			if (marker_size[0] != '\0')
				HC_Set_Variable_Marker_Size(marker_size);
			if (marker_symbol[0] != '\0')
				HC_Set_Marker_Symbol(marker_symbol);
			if (edge_weight[0] != '\0')
				HC_Set_Variable_Edge_Weight(edge_weight);
			if (edge_pattern[0] != '\0')
				HC_Set_Edge_Pattern(edge_pattern);
			
			if(!(special & ~HSPECIAL_TRANSMISSION))
				HC_Close_Segment();
		}
		else if (hl_type==HHighlightSubentity)
		{
			HC_KEY sub_key;
			int sub_flist_count=0, sub_pcount=0;

			if(!(special & ~HSPECIAL_TRANSMISSION))
				ref_key=HC_KOpen_Segment("");

			HSubentityPassthrough * pt = (HSubentityPassthrough *)data;

			sub_key=HC_Compute_Subshell(key, pt->face_count, pt->faces, 
				pt->vertex_count, pt->vertex1, pt->vertex2, pt->face_map, pt->vertex_map);
			HC_Show_Shell_Size(sub_key, &sub_pcount, &sub_flist_count);
			
			int max = sub_pcount>pt->vertex_count ? sub_pcount : pt->vertex_count;
			
			//we receive a list of faces, vertices,and edges to KEEP,
			//but we need a list of edges to REMOVE.  
			
			//translate vertex numbers
			if(pt->vertex_count > 0)
			{
				int * new_v1 = new int [max];
				int * new_v2 = 0;
				int remove_vert_count = sub_pcount;
				char * vert_vis = new char [max];
				VHash <int, int> edge_hash;

				memset(vert_vis, 0, max);
				
				if(pt->vertex2)
					new_v2 = new int [max];

				//convert point indices from original shell to sub-shell
				for(i=0; i<pt->vertex_count; ++i)
				{
					new_v1[i]=pt->vertex_map[pt->vertex1[i]];

					//keep track of which vertices should be visible
					if(vert_vis[new_v1[i]]==0)
					{
						vert_vis[new_v1[i]]=(char)1;
						--remove_vert_count;
					}

					//if we have edges to consider too, translate their indices as well
					//do not consider them for purposes of visibility
					if(pt->vertex2)
					{
						if(pt->vertex2[i]>=0)
							new_v2[i]=pt->vertex_map[pt->vertex2[i]];
						else
							new_v2[i]=-1;

						if(new_v1[i] < new_v2[i])
							edge_hash.InsertItem(new_v1[i], new_v2[i]);
						else
							edge_hash.InsertItem(new_v2[i], new_v1[i]);
					}
				}

				int actual_count = 0;

				if(pt->highlight_subentity & HSUBENTITY_VERTICES)
				{
					if(remove_vert_count>0)
					{
						//generate list of indices to be removed
						int * modify_verts = new int [max];
						char * modify_vis = new char [max];

						memset(modify_vis, 0, remove_vert_count);					

						for(i=0; i<sub_pcount; ++i)
						{
							if(vert_vis[i]==0)
								modify_verts[actual_count++]=i;
						}

						HC_MSet_Specific_Vertex_Visibilities(sub_key, actual_count, modify_verts, modify_vis);

						delete [] modify_verts;
						delete [] modify_vis;
					}
				}
				
				//now handle edges...
				if(pt->vertex2 && pt->highlight_subentity & HSUBENTITY_EDGES)
				{
					int fsize, first_index, edge1, edge2, tmp;
					int * remove_v1, * remove_v2;
					int * sub_flist;
					int j, k;

					sub_flist = new int [sub_flist_count];
					HC_Show_Shell(sub_key, 0, 0, 0, sub_flist);

					remove_v1 = new int [sub_flist_count];
					remove_v2 = new int [sub_flist_count];

					i=0;
					actual_count=0;
					while(i<sub_flist_count)
					{
						fsize=sub_flist[i++];
						first_index=sub_flist[i];
						
						//order the indices, lowest first
						if(first_index<sub_flist[i+fsize-1])
						{
							edge1=first_index;
							edge2=sub_flist[i+fsize-1];
						}
						else
						{
							edge1=sub_flist[i+fsize-1];
							edge2=first_index;							
						}
						
						//check edge between first and last points in the face
						for(k=0; ; ++k)
						{
							//edge not found, add it to the remove list
							//also add it to the hash to prevent duplicate removals
							if (VHASH_STATUS_SUCCESS != edge_hash.LookupNthItem(edge1, k, &tmp))
							{
								remove_v1[actual_count]=edge1;
								remove_v2[actual_count++]=edge2;
								edge_hash.InsertItem(edge1, edge2);
								break;
							}
							
							//edge is in the hash, no need to keep looking
							if (tmp == edge2)
								break;
						}

						//check the edges between the rest of the points in the face
						for(j=0; j< fsize-1; ++j)
						{
							//order the indices, lowest first
							if(sub_flist[i+j]<sub_flist[i+j+1])
							{
								edge1=sub_flist[i+j];
								edge2=sub_flist[i+j+1];
							}
							else
							{
								edge1=sub_flist[i+j+1];
								edge2=sub_flist[i+j];
							}

							for(k=0; ; ++k)
							{
								//edge not found, add it to the remove list.
								//also add it to the hash to prevent duplicate removals
								if (VHASH_STATUS_SUCCESS != edge_hash.LookupNthItem(edge1, k, &tmp))
								{
									remove_v1[actual_count]=edge1;
									remove_v2[actual_count++]=edge2;
									edge_hash.InsertItem(edge1, edge2);
									break;
								}
								
								//edge is in the hash, no need to keep looking
								if (tmp == edge2)
									break;
							}
						}

						i+=fsize;
					}

					if(actual_count>0)
					{
						char * modify_edge_vis = new char[actual_count];
						memset(modify_edge_vis, 0, actual_count);
						
						HC_MSet_Specific_Edge_Visibilities(sub_key, actual_count, remove_v1, remove_v2, modify_edge_vis);
						
						delete [] modify_edge_vis;
					}

					delete [] sub_flist;
					delete [] remove_v1;
					delete [] remove_v2;					
				}

				delete [] new_v1;
				delete [] new_v2; 
				delete [] vert_vis;
			}
			
			if(!(pt->highlight_subentity & HSUBENTITY_VERTICES))
			{
				//remove them all
				char * modify_vis = new char [sub_pcount];

				memset(modify_vis, 0, sub_pcount);

				HC_MSet_Vertex_Visibilities(sub_key, 0, sub_pcount, modify_vis);

				delete [] modify_vis;
			}
	
			if(!(pt->highlight_subentity & HSUBENTITY_EDGES))
			{
				int fsize, first_index, edge1, edge2;
				int * remove_v1, * remove_v2;
				int * sub_flist;
				int j;
				int actual_count=0;

				sub_flist = new int [sub_flist_count];
				HC_Show_Shell(sub_key, 0, 0, 0, sub_flist);

				remove_v1 = new int [sub_flist_count];
				remove_v2 = new int [sub_flist_count];

				i=0;
				while(i<sub_flist_count)
				{
					fsize=sub_flist[i++];
					first_index=sub_flist[i];
					
					//order the indices, lowest first
					if(first_index<sub_flist[i+fsize-1])
					{
						edge1=first_index;
						edge2=sub_flist[i+fsize-1];
					}
					else
					{
						edge1=sub_flist[i+fsize-1];
						edge2=first_index;							
					}
					
					remove_v1[actual_count]=edge1;
					remove_v2[actual_count++]=edge2;
					
					//remove the edges between the rest of the points in the face
					for(j=0; j< fsize-1; ++j)
					{
						//order the indices, lowest first
						if(sub_flist[i+j]<sub_flist[i+j+1])
						{
							edge1=sub_flist[i+j];
							edge2=sub_flist[i+j+1];
						}
						else
						{
							edge1=sub_flist[i+j+1];
							edge2=sub_flist[i+j];
						}

						remove_v1[actual_count]=edge1;
						remove_v2[actual_count++]=edge2;
					}

					i+=fsize;
				}

				if(actual_count>0)
				{
					char * modify_edge_vis = new char[actual_count];
					memset(modify_edge_vis, 0, actual_count);
					
					HC_MSet_Specific_Edge_Visibilities(sub_key, actual_count, remove_v1, remove_v2, modify_edge_vis);
					
					delete [] modify_edge_vis;
				}

				delete [] sub_flist;
				delete [] remove_v1;
				delete [] remove_v2;
			}


			HC_Set_Selectability("off");
			if (!HUtility::IsIdentityMatrix(mod_mat))
				HC_Set_Modelling_Matrix(mod_mat);
			if (vis[0] != '\0') 				
				HC_Set_Visibility(vis);
			if(pt->highlight_subentity & HSUBENTITY_EDGES)
			{
				char patchup[MVO_BUFFER_SIZE];
				HC_Show_One_Visibility("edge", patchup);
				if(!streq("off", patchup))
					HC_Set_Visibility("edges=on");
			}
			if(hsra)
				HC_Set_Visibility("no faces");
			if (marker_size[0] != '\0')
				HC_Set_Variable_Marker_Size(marker_size);
			if (marker_symbol[0] != '\0')
				HC_Set_Marker_Symbol(marker_symbol);
			if (edge_weight[0] != '\0')
				HC_Set_Variable_Edge_Weight(edge_weight);
			if (edge_pattern[0] != '\0')
				HC_Set_Edge_Pattern(edge_pattern);
			
			if(!(special & ~HSPECIAL_TRANSMISSION))
				HC_Close_Segment();
		}
		else
		{
			if(hl_type == HHighlightSegment)
			{
				ref_key = HC_KInclude_Segment_By_Key(key);
				if(!inv_trans)
					HC_Set_Rendering_Options("attribute lock = (color), ignore subsegment locks = (color)");
				if(hsra)
					HC_Set_Rendering_Options("attribute lock = (visibility), ignore subsegment locks = (visibility)");
			}
			else
				ref_key = HC_KReference_Geometry_By_Key(key);

			if(hl_type != HHighlightSegment && !(special & ~HSPECIAL_TRANSMISSION))
				HC_Open_Geometry(ref_key);

				if (!HUtility::IsIdentityMatrix(mod_mat))
					HC_Set_Modelling_Matrix(mod_mat);
				if(inv_trans && color[0] != '\0')
				{
					char face_color[MVO_BUFFER_SIZE];
					sprintf(face_color, "faces=%s", color);

					if(color_map && *color_map)
						HC_Set_Color_Map(color_map);
					HC_Set_Color(face_color);
				}
				if (vis[0] != '\0') 
					HC_Set_Visibility(vis);
				if(hsra)
					HC_Set_Visibility("no faces");
				if(has_type & HTYPE_TEXT)
				{
					if (text_font[0] != '\0') 
						HC_Set_Text_Font(text_font);
					if (align[0] != '\0') 
						HC_Set_Text_Alignment(align);
					if (path_x != 0 || path_y!= 0 || path_z != 0)
						HC_Set_Text_Path(path_x, path_y, path_z);
					if (spacing != -1.f) 
						HC_Set_Text_Spacing(spacing);
				}	
				if(has_type & HTYPE_LINE)
				{
					if (line_weight[0] != '\0')
						HC_Set_Variable_Line_Weight(line_weight);
					if (line_pattern[0] != '\0')
						HC_Set_Line_Pattern(line_pattern);
				}
				if(has_type & HTYPE_MARKER || has_type & HTYPE_SHELL_MESH || 
					has_type & HTYPE_LINE || has_type & HTYPE_OTHER)
				{
					if (marker_size[0] != '\0')
						HC_Set_Variable_Marker_Size(marker_size);
					if (marker_symbol[0] != '\0')
						HC_Set_Marker_Symbol(marker_symbol);
				}
				if(has_type & HTYPE_SHELL_MESH || has_type & HTYPE_OTHER)
				{
					if (edge_weight[0] != '\0')
						HC_Set_Variable_Edge_Weight(edge_weight);
					if (edge_pattern[0] != '\0')
						HC_Set_Edge_Pattern(edge_pattern);
				}

			if(hl_type != HHighlightSegment && !(special & ~HSPECIAL_TRANSMISSION))
				HC_Close_Geometry();
		}
		if(special!=HSPECIAL_NOTHING)
		{
			if(special & ~HSPECIAL_TRANSMISSION)
			{
				HC_Close_Segment();
				ref_key=seg_key;
			}

			if((has_type & HTYPE_OTHER || has_type & HTYPE_SHELL_MESH) && (special & HSPECIAL_TRANSMISSION))
				HC_Close_Segment();
		}
	HC_Close_Segment();
	//-- Done creating the highlight reference --

	delete [] path;
	delete [] color_map;

	return ref_key;
}


HSmartSelItem::HSmartSelItem(HC_KEY key, HSelectionSet * selection_set, int incl_count, HC_KEY * incl_keys) 
			  : HSelectionItem(key, selection_set)
{
	m_ConditionStyle = INVALID_KEY;
	m_QuickHighlightGeom = INVALID_KEY;
	m_HighlightMode = HighlightDefault;
	m_IncludePath.count = incl_count;
	m_IncludePath.keys = new HC_KEY[incl_count];
	memcpy(&m_IncludePath.keys[0], incl_keys, incl_count*sizeof(HC_KEY));
	m_pSelKeyList = new_vlist(malloc, free);

}


HRegionSelItem::HRegionSelItem(HShellObject const & oShell, HSelectionSet * selection_set, int incl_count, HC_KEY * incl_keys, int region) 
: HSmartSelItem(oShell.GetKey(), selection_set, incl_count, incl_keys),
m_Region(region),
m_oShellObj(oShell),
m_oRegionObj(&m_oShellObj, region)
{
}

HSubentitySelItem::HSubentitySelItem(HC_KEY key, HSelectionSet * selection_set, int incl_count, HC_KEY * incl_keys, 
		int face_count, const int * faces, int vertex_count, const int * vertex1, const int * vertex2, 
		bool highlight_faces, bool highlight_vertices, bool highlight_edges, bool maintain_maps)
	: HSmartSelItem(key, selection_set, incl_count, incl_keys), 
	m_face_count(face_count), m_faces(0), m_vertex_count(vertex_count), m_vertex1(0), m_vertex2(0),
	m_maintain_maps(maintain_maps), m_face_map_count(0), m_face_map(0), m_vertex_map_count(0), m_vertex_map(0),
	m_subentity_highlight(0)
{
	if(m_face_count)
	{
		m_faces = new int [m_face_count];
		memcpy(m_faces, faces, m_face_count*sizeof(int));
	}
	if(m_vertex_count)
	{
		m_vertex1 = new int [m_vertex_count];
		memcpy(m_vertex1, vertex1, m_vertex_count*sizeof(int));
	}
	if(m_vertex_count && vertex2)
	{
		m_vertex2 = new int [m_vertex_count];
		memcpy(m_vertex2, vertex2, m_vertex_count*sizeof(int));
	}
	m_subentity_highlight |= (highlight_faces ? HSUBENTITY_FACES : 0) | 
		(highlight_vertices ? HSUBENTITY_VERTICES : 0) | (highlight_edges ? HSUBENTITY_EDGES : 0);
}

HSubentitySelItem::~HSubentitySelItem()
{
	if(m_faces)
		delete [] m_faces;

	if(m_vertex1)
		delete [] m_vertex1;

	if(m_vertex2)
		delete [] m_vertex2;

	if(m_vertex_map)
		delete [] m_vertex_map;

	if(m_face_map)
		delete [] m_face_map;
}

bool HSubentitySelItem::Equals(const HSelectionItem* i2) const
{
	// if primary selection key is same
	if( this->GetKey() != i2->GetKey() )
		return false;

	// return false if they are of different type
	if( !streq(this->GetName(), i2->GetName()) )
		return false;

	// safe to typecast now
	HSubentitySelItem * sub_sel2 = (HSubentitySelItem*) i2;

	// if the include keys in the path are same
	int incl_count;
	if( (incl_count = this->GetIncludeCount()) != sub_sel2->GetIncludeCount() )
		return false;

	const HC_KEY * ikeys1 = this->GetIncludeKeys();
	const HC_KEY * ikeys2 = sub_sel2->GetIncludeKeys();
	int i;

	for (i = 0; i < incl_count; i++)
	{
		if(ikeys1[i] != ikeys2[i])
			return false;
	}

 	int count1, count2;
	int * array2;
	
	count1=GetFaceCount();
	count2=sub_sel2->GetFaceCount();
	
	if(count1!=count2)
		return false;

	if(count1>0)
	{
		array2 = new int [count2];
		sub_sel2->GetFaces(array2);

		for(i=0; i<count1; ++i)
		{
			if(m_faces[i]!=array2[i])
			{
				delete [] array2;
				return false;
			}
		}
		delete [] array2;
	}

	count1=GetVertexCount();
	count2=sub_sel2->GetVertexCount();
	
	if(count1!=count2)
		return false;

	if(count1>0)
	{
		array2 = new int [count2];
		int * array2_2 = new int [count2];		
		sub_sel2->GetVertices(array2, array2_2);

		for(i=0; i<count1; ++i)
		{
			if(m_vertex1[i]!=array2[i])
			{
				delete [] array2;
				delete [] array2_2;
				return false;
			}
		}

		if((m_vertex2 && !array2_2) || (!m_vertex2 && array2_2))
		{
			delete [] array2;
			delete [] array2_2;
			return false;
		}

		if(array2_2)
		{
			for(i=0; i<count1; ++i)
			{
				if(m_vertex2[i]!=array2_2[i])
				{
					delete [] array2;
					delete [] array2_2;
					return false;
				}
			}
		}
		
		delete [] array2;
		delete [] array2_2;
	}	
	
	return true;
}
	

bool HSubentitySelItem::UnHighlight()
{
	HC_KEY ref_key;
		
	while((ref_key=GetHighlightedRefKey()) != INVALID_KEY)
	{
		if(HC_Show_Existence_By_Key(ref_key, "self"))
			HC_Delete_By_Key(ref_key);
	}

	return true;
}

static void check_points_in_use(int count, const int * flist, char * appears)
{
	int i=0, j, face_size;

	while(i<count)
	{
		face_size=flist[i++];
		
		for(j=0; j<face_size; ++j)
			appears[flist[i+j]]=(char)0x01;

		i+=face_size;
	}
}

bool HSubentitySelItem::Delete()
{
	// unhighlight it first
	UnHighlight();
	
	if(HC_Show_Existence_By_Key(m_key, "self"))
	{
		int i, actual_count, * faces, * verts, shell_face_cnt, shell_pts_cnt, * shell_flist;
		char * in_use;
		faces = new int [m_face_map_count];
		verts = new int [m_vertex_map_count];
	
		//walk face map and log faces to be deleted.
		actual_count=0;
		for(i=0; i<m_face_map_count; ++i)
		{
			if(m_face_map[i]>=0)
				faces[actual_count++]=i;
		}

		if(actual_count>0)
			HC_Delete_Specific_Shell_Faces(m_key, actual_count, faces);

		//walk vertex map and log vertices to be deleted.
		//don't delete vertices that are still being used
		HC_Show_Shell_Size(m_key, &shell_pts_cnt, &shell_face_cnt);
		in_use = new char [shell_pts_cnt];
		memset(in_use, 0x00, shell_pts_cnt);

		if(shell_face_cnt)
		{
			shell_flist = new int [shell_face_cnt];
			HC_Show_Shell(m_key, &shell_pts_cnt, 0, &shell_face_cnt, shell_flist);
		
			check_points_in_use(shell_face_cnt, shell_flist, in_use);

			delete [] shell_flist;
		}

		actual_count=0;
		for(i=0; i<m_vertex_map_count; ++i)
		{
			if(m_vertex_map[i]>=0 && in_use[i]==0)
				verts[actual_count++]=i;
		}

		if(shell_pts_cnt==actual_count)
			HC_Delete_By_Key(m_key);
		else if(actual_count>0)
			HC_Delete_Specific_Shell_Points(m_key, actual_count, verts);	

		delete [] faces;
		delete [] verts;
		delete [] in_use;
	}

	return true;
}

void HSubentitySelItem::GetFaces(int * faces)
{
	if(m_faces)
		memcpy(faces, m_faces, m_face_count*sizeof(int));
	else
		*faces=0; 
}

void HSubentitySelItem::GetVertices(int * vertex1, int * vertex2) 
{ 
	if(m_vertex1)
		memcpy(vertex1, m_vertex1, m_vertex_count*sizeof(int));
	else
		*vertex1=0;

	if(m_vertex2)
		memcpy(vertex2, m_vertex2, m_vertex_count*sizeof(int));
	else
		*vertex2=0;	
}

void HSubentitySelItem::GetMaps(int * face_map, int * vertex_map) 
{
	if(m_face_map)
		memcpy(face_map, m_face_map, m_face_map_count*sizeof(int));
	else
		*face_map=0;

	if(m_vertex_map)
		memcpy(vertex_map, m_vertex_map, m_vertex_map_count*sizeof(int));
	else
		*vertex_map=0;	
}

void HSubentitySelItem::GetMapCounts(int * face_map_count, int * vertex_map_count) 
{
	*face_map_count=m_face_map_count;
	*vertex_map_count=m_vertex_map_count;
}

bool HRegionSelItem::Equals(const HSelectionItem* i2) const
{
	// if primary selection key is same
	if( this->GetKey() != i2->GetKey() )
		return false;

	// return false if they are of different type
	if( !streq(this->GetName(), i2->GetName()) )
		return false;

	// safe to typecast now
	HRegionSelItem * smart_sel2 = (HRegionSelItem*) i2;

	// if the include keys in the path are same
	int incl_count;
	if( (incl_count = this->GetIncludeCount()) != smart_sel2->GetIncludeCount() )
		return false;

	const HC_KEY * ikeys1 = this->GetIncludeKeys();
	const HC_KEY * ikeys2 = smart_sel2->GetIncludeKeys();
	for (int i = 0; i < incl_count; i++)
	{
		if(ikeys1[i] != ikeys2[i])
			return false;
	}

 	if (this->m_Region != smart_sel2->GetRegion())
		return false;
	
	return true;
}

HSmartSelItem::~HSmartSelItem( void )
{
	H_SAFE_DELETE_ARRAY(m_IncludePath.keys);
	H_SAFE_DELETE_ARRAY(m_FullPath);
	delete_vlist(m_pSelKeyList);
}

void HSmartSelItem::GetIncludeKeys(HC_KEY *includes) const {
	const HC_KEY * const temp = GetIncludeKeys();
	int include_count = GetIncludeCount();

	memcpy(includes, temp, include_count * sizeof(HC_KEY));
}


const HC_KEY *HSmartSelItem::GetFullPathKeys( HBaseView *view )
{
	if (!m_FullPath) { 
		if(m_pSelectionSet->GetReferenceSelection())
		{
			HC_KEY seg_key=m_key;
			char type[MVO_BUFFER_SIZE];
			int i;
			m_FullPathCount = m_IncludePath.count + 1;
			m_FullPath = new HC_KEY[ m_FullPathCount ];

			HC_Show_Key_Type(m_key, type);
			if(!streq(type, "segment"))
				seg_key= HC_KShow_Owner_Original_Key(m_key);
				
			//-- Set up the path for PShow --
			m_FullPath[0]=seg_key;
			for(i=0; i<m_IncludePath.count; ++i)
				m_FullPath[i+1]=m_IncludePath.keys[m_IncludePath.count-i-1];
		}
		else
		{
			m_FullPathCount = m_IncludePath.count + 2;
			m_FullPath = new HC_KEY[ m_FullPathCount ];
			m_FullPath[0] = m_key;
			memcpy(&m_FullPath[1], &m_IncludePath.keys[0], m_IncludePath.count*sizeof(HC_KEY));
			m_FullPath[ m_IncludePath.count + 1 ] = view->GetViewKey();
		}
	}
	UNREFERENCED (view);
	return m_FullPath;
}

void HSmartSelItem::GetFullPathKeys (HBaseView *view, HC_KEY *path) {
	const HC_KEY *temp = GetFullPathKeys(view);
	int path_size = GetFullPathCount(view);

	memcpy(path, temp, path_size * sizeof(HC_KEY));
}


bool HSmartSelItem::Equals(const HSelectionItem* i2) const
{
	// if primary selection key is same
	if( this->GetKey() != i2->GetKey() )
		return false;

	// return false if they are of different type
	if( !streq(this->GetName(), i2->GetName()) )
		return false;

	// safe to typecast now
	HSmartSelItem * smart_sel2 = (HSmartSelItem*) i2;

	// if the include keys in the path are same
	int incl_count;
	if( (incl_count = this->GetIncludeCount()) != smart_sel2->GetIncludeCount() )
		return false;

	const HC_KEY * ikeys1 = this->GetIncludeKeys();
	const HC_KEY * ikeys2 = smart_sel2->GetIncludeKeys();
	for (int i = 0; i < incl_count; i++)
	{
		if(ikeys1[i] != ikeys2[i])
			return false;
	}

	return true;
}


// finds if the given style segment is applied on the currently opened segment with given conditions
// returns the conditional style key if found otherwise returns INVALID_KEY
static HC_KEY Show_Existence_Conditional_Style(const HC_KEY which_style, const char * what_condition )
{
    HC_KEY return_key = INVALID_KEY;
	// check if same conditional style already exists
	// this is particularly true for non-instanced multiple entities 
	// as they get pushed into a common highlight segment
	HC_Begin_Contents_Search(".", "style");
		HC_KEY foundkey = INVALID_KEY;
		char type[MVO_BUFFER_SIZE];
		char condition[MVO_BUFFER_SIZE];
		while(HC_Find_Contents(type, &foundkey))
		{
			if(HC_KShow_Style_Segment(foundkey) == which_style)
			{
				HC_Show_Conditional_Style(foundkey, 0, condition);
				if(strieq(condition, what_condition))
				{
				    return_key = foundkey;
					break;
				}
			}
		}
	HC_End_Contents_Search();

	return return_key;
}


int HSmartSelItem::GetHighlightedRefListCount()
{
	return vlist_count(m_pSelKeyList);
}

	
void HSmartSelItem::GetHighlightedRefList(HC_KEY * keys)
{
	unsigned int i=0;

	vlist_reset_cursor(m_pSelKeyList);
	do 
	{
		keys[i++]=(HC_KEY)vlist_peek_cursor(m_pSelKeyList);
		vlist_advance_cursor(m_pSelKeyList);
	} while(i < vlist_count(m_pSelKeyList));
}


HC_KEY HSmartSelItem::GetHighlightedRefKey()
{
	HC_KEY ret = INVALID_KEY;

	if(vlist_peek_first(m_pSelKeyList))
	{
		ret = (HC_KEY)vlist_peek_first(m_pSelKeyList);
		vlist_remove_first(m_pSelKeyList);
	}

	return ret;
}
	
void HSmartSelItem::AddHighlightedRefKey(HC_KEY key)
{
	if(key!=INVALID_KEY)
		vlist_add_last(m_pSelKeyList, (void*)key);
}

static void validate_include_path(HC_KEY selection_key, int *count, HC_KEY ** keys, bool is_ref_sel, HC_KEY view_key, HC_KEY incl_link_key)
{
	int num_include_keys = *count;
	bool child_of_view = (selection_key == view_key);
	HC_KEY tmp_key = selection_key;

	while((tmp_key = HC_KShow_Owner_Original_Key(tmp_key)) != INVALID_KEY)
	{
		if(tmp_key == view_key)
		{
			child_of_view = true;
			break;
		}
	}

	if(is_ref_sel)
	{
		//reference highlighting requires the view and the include link
		if(num_include_keys==0)
		{
			HC_KEY * seg_path = 0;

			if(child_of_view)
			{
				num_include_keys = 1;
				seg_path = new HC_KEY[num_include_keys];

				seg_path[0]=view_key;
			}
			else
			{
				num_include_keys = 2;
				seg_path = new HC_KEY[num_include_keys];

				seg_path[0]=view_key;
				seg_path[1]=incl_link_key;
			}			
			
			delete [] *keys;
			*keys = seg_path;
			*count = num_include_keys;
		}
		else
		{
			bool add_view=false, add_incl_link=false;
			int add_count=0;

			if ((*keys)[0]!=view_key)
			{
				add_view=true;
				++add_count;
			}
			if ((*keys)[0]!=incl_link_key && (num_include_keys==1 || (num_include_keys>1 && (*keys)[1]!=incl_link_key)) && !child_of_view)
			{
				add_incl_link=true;
				++add_count;
			}

			if(add_view || add_incl_link)
			{
				HC_KEY * seg_path = new HC_KEY[num_include_keys+add_count];
				int i;

				seg_path[0]=view_key;
				seg_path[1]=incl_link_key;
				for(i=2; i-add_count<num_include_keys; ++i)
					seg_path[i] = (*keys)[i-add_count];

				num_include_keys+=add_count;
				delete [] *keys;
				*keys = seg_path;
				*count = num_include_keys;
			}
		}
	}
	else
	{
		//default (conditional) highlighting requires the include link and no view
		if(num_include_keys==0)
		{
			if(!child_of_view)
			{
				num_include_keys = 1;
				HC_KEY * seg_path = new HC_KEY[num_include_keys];

				seg_path[0]=incl_link_key;
				
				delete [] *keys;
				*keys = seg_path;
				*count = num_include_keys;
			}
		}
		else
		{
			bool remove_view=false, add_incl_link=false;

			if ((*keys)[0]==view_key)
				remove_view=true;
			if ((*keys)[0]!=incl_link_key && (num_include_keys==1 || (num_include_keys>1 && (*keys)[1]!=incl_link_key)) && !child_of_view)
				add_incl_link=true;

			if(remove_view || add_incl_link)
			{
				int mod = (remove_view && add_incl_link) ? 0 : (remove_view ? -1 : 1);
				HC_KEY * seg_path = new HC_KEY[num_include_keys+mod];
				int i;

				seg_path[0]=incl_link_key;
				for(i=1; i-mod<num_include_keys; ++i)
					seg_path[i] = (*keys)[i-mod];

				num_include_keys+=mod;
				delete [] *keys;
				*keys = seg_path;
				*count = num_include_keys;
			}
		}
	}
}

bool HSmartSelItem::Highlight()
{

	validate_include_path(m_key, &m_IncludePath.count, &m_IncludePath.keys,
		m_pSelectionSet->GetHighlightMode()!=HighlightDefault, 
		m_pSelectionSet->GetView()->GetViewKey(), m_pSelectionSet->GetView()->GetIncludeLinkKey());

	if(m_pSelectionSet->GetHighlightMode() == HighlightQuickmoves
		|| m_pSelectionSet->GetHighlightMode() == InverseTransparency
		|| m_pSelectionSet->GetHighlightMode() == ColoredInverseTransparency)
	{
		char keytype[MVO_BUFFER_SIZE];
		HC_KEY ref_key;

		if(m_pSelectionSet->GetSelectionSegment() == INVALID_KEY)
			m_pSelectionSet->UpdateHighlightStyle();

		if(m_pSelectionSet->GetIsSelection(m_key))
			return true;

		HC_Show_Key_Type(m_key, keytype);

		ref_key = ref_highlight_common(m_key, m_IncludePath.count, m_IncludePath.keys, 
			m_pSelectionSet, (streq(keytype, "segment") ? HHighlightSegment : HHighlightGeometry) );
		//add the new key to the list of highlighted geometry
		AddHighlightedRefKey(ref_key);
	}
	else
	{
		char keytype[MVO_BUFFER_SIZE];
		HC_KEY seg_key = m_key;

		// if it is an entity, move it down under a segment
		HC_Show_Key_Type(m_key, keytype);
		if (!streq(keytype, "segment")) 
		{
			// do not do it if the owner is already a highlight segment
			// this is possible is a different instance of same geometry is selected
			seg_key = HC_KShow_Owner_Original_Key(m_key);
			if( !m_pSelectionSet->IsHighlightSegment(seg_key) )
			{
				// Note: Optimization - creating a new highlight segment per entity causes 
				// severe performance problems when large number of entities are selected (floorplan.hmf)
				// To counter that, we are going to put a selected entity under a new highlight segment
				// only if it could be instanced. Otherwise we are just going to dump it under 
				// a common highlight segment - Rajesh B (02-Mar-05)
				char hilite_seg_name[MVO_BUFFER_SIZE];
				if( IsInstanced())
				{
					MAKE_HIGHLIGHT_SEGMENT_NAME(hilite_seg_name, m_key);
				}
				else
				{
					MAKE_COMMON_HIGHLIGHT_SEGMENT_NAME(hilite_seg_name);
				}

				HC_Open_Segment_By_Key(seg_key);
					seg_key = HC_KOpen_Segment(hilite_seg_name);
						if (GetHighlightMode() == HighlightQuickmoves && !(streq(keytype, "shell") || streq(keytype, "mesh")) ){
							HC_Set_Heuristics("quick moves");
							m_QuickHighlightGeom = HC_KCopy_Geometry(m_key, ".");
						}
						//else if(GetHighlightMode() == HighlightDefault){
						else{
							HC_Move_By_Key(m_key, ".");
						}
					HC_Close_Segment();
				HC_Close_Segment();

				m_pSelectionSet->RegisterHighlightSeg(seg_key);
				
			}
		}

		// tag all the includers and prepare our final condition tag
		char base_tag[MVO_BUFFER_SIZE], sel_tag[MVO_BUFFER_SIZE], condition_tag[MVO_BUFFER_SIZE];
		condition_tag[0] = '\0';
		GetBaseTag(base_tag);
		for(int i = 1; i < m_IncludePath.count; i++)
		{
			sprintf(sel_tag, "%s_%d", base_tag, i); //MAKE_MVO_SELECT_TAG

			HC_Define_System_Options("no update control");
			HC_Open_Segment_By_Key(HC_KShow_Owner_Original_Key(m_IncludePath.keys[i]));
				HC_Set_Conditions(sel_tag);
			HC_Close_Segment();
			HC_Define_System_Options("update control");

			strcat(condition_tag, sel_tag);
			if(i < m_IncludePath.count-1)
				strcat(condition_tag, " and ");
		}

		// set the conditional style
		HC_Open_Segment_By_Key(seg_key);

			// check if same conditional style already exists
			// this is particularly true for non-instanced multiple entities 
			// as they get pushed into a common highlight segment
			m_ConditionStyle = Show_Existence_Conditional_Style(m_pSelectionSet->GetHighlightStyle(), condition_tag);
			if(m_ConditionStyle == INVALID_KEY)
				m_ConditionStyle = HC_KConditional_Style_By_Key(m_pSelectionSet->GetHighlightStyle(), condition_tag);
			else if(condition_tag[0] != '\0'){

				char buffer[MVO_BUFFER_SIZE];
				int count=0;

				sprintf(buffer, "user option=%s", condition_tag);
				if (HC_Show_Existence(buffer)) {
					HC_Show_One_User_Option(condition_tag, buffer);
					sscanf(buffer, "%d", &count);
				}

				count++;

				sprintf(buffer, "%s=%d", condition_tag, count);
				HC_Set_User_Options(buffer);
			}

		HC_Close_Segment();
		m_pSelectionSet->GetView()->SetGeometryChanged();
	}
	
	return true;
}

void HSmartSelItem::UpdateIncludePath(int incl_count, HC_KEY * incl_keys)
{
	m_IncludePath.count=incl_count;
	if(m_IncludePath.keys)
		delete [] m_IncludePath.keys;
	m_IncludePath.keys = incl_keys;
}

bool HSubentitySelItem::Highlight()
{
	int cnt = GetIncludeCount();
	HSubentityPassthrough pt;
	HC_KEY ref_key;
	HC_KEY * new_path = new HC_KEY [cnt];

	memcpy(new_path, GetIncludeKeys(), cnt*sizeof(HC_KEY));
	validate_include_path(m_key, &cnt, &new_path, true, 
		m_pSelectionSet->GetView()->GetViewKey(), m_pSelectionSet->GetView()->GetIncludeLinkKey());
	if(cnt!=GetIncludeCount())
		UpdateIncludePath(cnt, new_path);

	HC_Show_Shell_Size(m_key, &m_vertex_map_count, &m_face_map_count);
	
	m_face_map = new int [m_face_map_count];
	memset(m_face_map, -1, m_face_map_count*sizeof(int));
	m_vertex_map = new int [m_vertex_map_count];

	pt.face_count=m_face_count;
	pt.faces=m_faces;
	pt.vertex_count=m_vertex_count;
	pt.vertex1=m_vertex1;
	pt.vertex2=m_vertex2;
	pt.maintain_maps=m_maintain_maps;
	pt.vertex_map_count=m_vertex_map_count;
	pt.vertex_map=m_vertex_map;
	pt.face_map_count=m_face_map_count;
	pt.face_map=m_face_map;
	pt.highlight_subentity=m_subentity_highlight;

	//always uses over-draw to create highlighted geometry
	ref_key = ref_highlight_common(m_key, GetIncludeCount(), GetIncludeKeys(), 
			m_pSelectionSet, HHighlightSubentity, -1, &pt);

	if(!m_maintain_maps)
	{
		delete [] m_face_map;
		m_face_map=0;
		m_face_map_count=0;

		delete [] m_vertex_map;
		m_vertex_map=0;
		m_vertex_map_count=0;		
	}

	//add the new key to the list of highlighted geometry
	AddHighlightedRefKey(ref_key);

	return true;
}

#if 1

int HRegionSelItem::IncrEdgeHighlightCount(HC_KEY key, HShellEdge const & oEdge)
{
	char options[64] = {""};
	int highlight_count = 0;
	void * hash_value = 0;
	
	HC_Open_Geometry(key);{

		struct vhash_s * pEdgeHash;

		if(HC_Show_Existence("user options = edgelookup")){
			HC_Show_One_User_Option("edgelookup", options);
			sscanf(options, "%p", &pEdgeHash);
		} else {
			pEdgeHash = new_vhash(1,malloc,free);
			sprintf(options, "edgelookup = %p", pEdgeHash);
			HC_Set_User_Options(options);
		}
		
		char string_key[128];
		sprintf(string_key, "%x %x", oEdge.GetFirst(), oEdge.GetSecond());
		vhash_status_t tStatus = vhash_lookup_string_key_item(pEdgeHash, string_key, &hash_value);
		highlight_count = MVO_V2I(hash_value);

		if(tStatus != VHASH_STATUS_SUCCESS){
			highlight_count = 1;
			hash_value = MVO_I2V(highlight_count);
			vhash_insert_string_key_item(pEdgeHash, string_key, hash_value);
		}
		else {
			++highlight_count;
			void * not_used;
			hash_value = MVO_I2V(highlight_count);
			vhash_replace_string_key_item(pEdgeHash, string_key, hash_value, &not_used);
		}

	}HC_Close_Geometry();

	return highlight_count;
}


int HRegionSelItem::DecrEdgeHighlightCount(HC_KEY key, HShellEdge const & oEdge)
{
	char options[64] = {""};
	int highlight_count = 0;
	void * hash_value = 0;
	
	HC_Open_Geometry(key);{
		HC_Show_One_User_Option("edgelookup", options);
		struct vhash_s * pEdgeHash = 0;
		sscanf(options, "%p", &pEdgeHash);
		char string_key[128];
		sprintf(string_key, "%x %x", oEdge.GetFirst(), oEdge.GetSecond());
		vhash_lookup_string_key_item(pEdgeHash, string_key, &hash_value);
		highlight_count = MVO_V2I(hash_value);
		--highlight_count;
		hash_value = MVO_I2V(highlight_count);
		void * not_used;
		vhash_replace_string_key_item(pEdgeHash, string_key, hash_value, &not_used);

		if(highlight_count == 0){
			vhash_remove_string_key_item(pEdgeHash, string_key, &not_used);
			if(vhash_count(pEdgeHash) == 0){
				delete_vhash(pEdgeHash);
				HC_UnSet_One_User_Option("edgelookup");
			}
		}

	}HC_Close_Geometry();

	return highlight_count;
}

#else

#include <map>

typedef std::map<int const, int> EdgeLookup;

int HRegionSelItem::IncrEdgeHighlightCount(HC_KEY key, HShellEdge const & oEdge)
{
	int highlight_count = 0;
	char options[64] = {""};
	
	HC_Open_Geometry(key);{

		EdgeLookup * pEdgeMap = 0;

		if(HC_Show_Existence("user options = edgelookup")){
			HC_Show_One_User_Option("edgelookup", options);
			sscanf(options, "%p", &pEdgeMap);
		} else {
			pEdgeMap = new EdgeLookup();
			sprintf(options, "edgelookup = %p", pEdgeMap);
			HC_Set_User_Options(options);
		}
		
		EdgeLookup::iterator iter = pEdgeMap->find(oEdge.GetIndex());
		if(iter == pEdgeMap->end()){
			highlight_count = 1;
			pEdgeMap->insert(std::make_pair(oEdge.GetIndex(), highlight_count));
		}
		else {
			highlight_count = ++iter->second;
		}

	}HC_Close_Geometry();

	return highlight_count;
}


int HRegionSelItem::DecrEdgeHighlightCount(HC_KEY key, HShellEdge const & oEdge)
{
	int highlight_count = 0;
	char options[64] = {""};
	
	HC_Open_Geometry(key);{
		HC_Show_One_User_Option("edgelookup", options);
		EdgeLookup * pEdgeMap = 0;
		sscanf(options, "%p", &pEdgeMap);
		EdgeLookup::iterator iter = pEdgeMap->find(oEdge.GetIndex());
		highlight_count = --iter->second;

		if(highlight_count == 0){
			pEdgeMap->erase(oEdge.GetIndex());
			if(pEdgeMap->empty()){
				delete pEdgeMap;
				HC_UnSet_One_User_Option("edgelookup");
			}
		}

	}HC_Close_Geometry();

	return highlight_count;
}

#endif

void HRegionSelItem::HighlightFaces()
{
	if(m_pSelectionSet->GetReferenceSelection())
	{
		int i, count = GetHighlightedRefListCount();
		HC_KEY * keys = new HC_KEY[count];
		GetHighlightedRefList(keys);
		
		for(i=0; i<count; ++i)
		{
			HC_Open_Segment_By_Key(keys[i]);
				if(m_pSelectionSet->HighlightRegionFacesAutoVisibility() == FacesForcedOn)
					HC_Set_Visibility("faces = on");
				else if(m_pSelectionSet->HighlightRegionFacesAutoVisibility() == FacesForcedOff)
					HC_Set_Visibility("faces = off");
			HC_Close_Segment();
		}

		delete [] keys;
	}
}

void HRegionSelItem::UnHighlightFaces()
{
	if(m_pSelectionSet->GetReferenceSelection())
	{
		int i, count = GetHighlightedRefListCount();
		HC_KEY * keys = new HC_KEY[count];
		GetHighlightedRefList(keys);
		
		for(i=0; i<count; ++i)
		{
			HC_Open_Segment_By_Key(keys[i]);
				HC_UnSet_One_Visibility("faces");
			HC_Close_Segment();
		}

		delete [] keys;
	}
}

void HRegionSelItem::HighlightEdges()
{
	if(m_pSelectionSet->GetReferenceSelection())
	{
		int i, count = GetHighlightedRefListCount();
		HC_KEY * keys = new HC_KEY[count];
		GetHighlightedRefList(keys);
		
		for(i=0; i<count; ++i)
		{
			HC_Open_Segment_By_Key(keys[i]);
				if(m_pSelectionSet->HighlightRegionEdgesAutoVisibility() == AllEdges)
					HC_Set_Visibility("edges = on");
				else if(m_pSelectionSet->HighlightRegionEdgesAutoVisibility() == PerimeterEdges)
					HC_Set_Visibility("edges = perimeter only");
			HC_Close_Segment();
		}

		delete [] keys;
	}
	else
	{
		float r,g,b;
		char style[32] = {""};
		HC_Open_Segment_By_Key(m_pSelectionSet->GetHighlightStyle());{
			HC_Show_One_Color_By_Value("faces", style, &r, &g, &b);
		}HC_Close_Segment();

		for(int iFaceIndex=0; iFaceIndex<m_oRegionObj.GetFaceCount(); ++iFaceIndex){
			for(int iEdgeIndex=0; iEdgeIndex<m_oRegionObj.GetFace(iFaceIndex).GetEdgeCount(); ++iEdgeIndex){
				m_oRegionObj.GetFace(iFaceIndex).OpenEdge(iEdgeIndex);{
					HShellEdge const oEdge = m_oRegionObj.GetFace(iFaceIndex).GetEdge(iEdgeIndex);
					if(IncrEdgeHighlightCount(m_key, oEdge) == 1){
						if(m_pSelectionSet->HighlightRegionEdgesAutoVisibility() == AllEdges)
							HC_Set_Visibility("edges = on");
						else if(m_pSelectionSet->HighlightRegionEdgesAutoVisibility() == PerimeterEdges)
							HC_Set_Visibility("edges = perimeter only");
						HC_Set_Color_By_Value("edges", "RGB", r, g, b);
					}
				}m_oRegionObj.GetFace(iFaceIndex).CloseEdge();
			}
		}
	}
}

void HRegionSelItem::UnHighlightEdges()
{
	if(!m_pSelectionSet->GetReferenceSelection())
	{
		for(int iFaceIndex=0; iFaceIndex<m_oRegionObj.GetFaceCount(); ++iFaceIndex)
		{
			for(int iEdgeIndex=0; iEdgeIndex<m_oRegionObj.GetFace(iFaceIndex).GetEdgeCount(); ++iEdgeIndex)
			{
				m_oRegionObj.GetFace(iFaceIndex).OpenEdge(iEdgeIndex);{
					HShellEdge const oEdge = m_oRegionObj.GetFace(iFaceIndex).GetEdge(iEdgeIndex);
					if(DecrEdgeHighlightCount(m_key, oEdge) == 0)
					{
						if(m_pSelectionSet->HighlightRegionEdgesAutoVisibility())
							HC_UnSet_Visibility();
						HC_UnSet_Color();
					}
				}
				m_oRegionObj.GetFace(iFaceIndex).CloseEdge();
			}
		}
	}
}


bool HRegionSelItem::Highlight()
{

	int cnt = GetIncludeCount();
	HC_KEY * new_path = new HC_KEY [cnt];
	memcpy(new_path, GetIncludeKeys(), cnt*sizeof(HC_KEY));
	validate_include_path(m_key, &cnt, &new_path, m_pSelectionSet->GetReferenceSelection(), 
		m_pSelectionSet->GetView()->GetViewKey(), m_pSelectionSet->GetView()->GetIncludeLinkKey());
	if(cnt!=GetIncludeCount())
		UpdateIncludePath(cnt, new_path);
	else
		delete [] new_path;
	
	if(m_pSelectionSet->GetReferenceSelection())
	{
		HC_KEY ref_key;

		ref_key = ref_highlight_common(m_key, GetIncludeCount(), GetIncludeKeys(), 
				m_pSelectionSet, HHighlightRegion, m_Region);

		//add the new key to the list of highlighted geometry
		AddHighlightedRefKey(ref_key);
	}
	else
	{
		char style[32];
		char buffer[4096];
		float r,g,b;

		HC_Open_Segment_By_Key(m_pSelectionSet->GetHighlightStyle());{
			HC_Show_One_Color_By_Value("faces", style, &r, &g, &b);
		}HC_Close_Segment();

		HC_Open_Geometry(m_key);{
			HC_Open_Region(m_Region);{
				HC_Set_Color_By_Value("faces", "RGB", r, g, b);
			}HC_Close_Region();
			sprintf(buffer, "hregion%d highlighted", m_Region);
			HC_Set_User_Options(buffer);
		}HC_Close_Geometry();
	}

	if(m_pSelectionSet->HighlightRegionEdgesAutoVisibility())
		HighlightEdges();

	if(m_pSelectionSet->HighlightRegionFacesAutoVisibility())
		HighlightFaces();

	return true;
}

bool HRegionSelItem::UnHighlight()
{
	if(m_pSelectionSet->GetReferenceSelection())
	{
		HC_KEY ref_key;
		
		while((ref_key=GetHighlightedRefKey()) != INVALID_KEY)
		{
			if(HC_Show_Existence_By_Key(ref_key, "self"))
				HC_Delete_By_Key(ref_key);
		}
	}
	else
	{
		char status[32];
		HC_Show_Key_Status(m_key, status);
		if(!streq(status, "invalid")){
			HC_Open_Geometry(m_key);
			HC_Open_Region(m_Region);
 			HC_UnSet_Color();
			HC_Close_Region();
			char buffer[4096];
			sprintf(buffer, "hregion%d highlighted", m_Region);
			HC_UnSet_One_User_Option(buffer);
			HC_Close_Geometry();
		}

		if(m_pSelectionSet->HighlightRegionEdgesAutoVisibility())
			UnHighlightEdges();

		if(m_pSelectionSet->HighlightRegionFacesAutoVisibility())
			UnHighlightFaces();
	}
	
	return true;
}

bool HSmartSelItem::UnHighlight()
{

	if(m_pSelectionSet->GetHighlightMode()!=HighlightDefault)
	{
		HC_KEY ref_key;
		
		while((ref_key=GetHighlightedRefKey()) != INVALID_KEY)
		{
			if(HC_Show_Existence_By_Key(ref_key, "self"))
				HC_Delete_By_Key(ref_key);
		}
		
		return true;
	}

	else
	{
		// if we are not highlighted currently, return false
		if( m_ConditionStyle == INVALID_KEY )
			return false;

		// If this key has a value we flush it, otherwise continue on with the normal case
		if( m_QuickHighlightGeom != INVALID_KEY && (m_HighlightMode == HighlightQuickmoves)){
			char keytype[MVO_BUFFER_SIZE];
			HC_KEY seg_key = m_QuickHighlightGeom;

			// if it is an entity, move it down under a segment
			HC_Show_Key_Type(seg_key, keytype);
			if (!streq(keytype, "shell") && !streq(keytype, "mesh")) {
				char par[MVO_BUFFER_SIZE];
				HC_Show_Owner_By_Key(m_QuickHighlightGeom, par);
				HC_Flush_Geometry(par);
				m_QuickHighlightGeom = INVALID_KEY; // now that it's deleted, reset the key
				return true;
			} 
		}

		char keytype[MVO_BUFFER_SIZE];
		HC_KEY seg_key = m_key;

		bool is_entity_sel = false;
		if (!HC_Show_Existence_By_Key(m_key, "self"))
			return true;
		HC_Show_Key_Type(m_key, keytype);
		if (!streq(keytype, "segment")) 
			is_entity_sel = true;

		// Note: we can't delete the conditional style segment for entity selection 
		// because the for multiple non-instanced entity selection we use the same conditional style
		// This gets deleted anyway when the highlight segment is deleted later
		if(!is_entity_sel) {

			// tag all the includers and prepare our final condition tag
			char base_tag[MVO_BUFFER_SIZE], sel_tag[MVO_BUFFER_SIZE], condition_tag[MVO_BUFFER_SIZE];
			condition_tag[0] = '\0';
			GetBaseTag(base_tag);
			for(int i = 1; i < m_IncludePath.count; i++)
			{
				sprintf(sel_tag, "%s_%d", base_tag, i); //MAKE_MVO_SELECT_TAG

				HC_Define_System_Options("no update control");
				HC_Open_Segment_By_Key(HC_KShow_Owner_Original_Key(m_IncludePath.keys[i]));
					HC_Set_Conditions(sel_tag);
				HC_Close_Segment();
				HC_Define_System_Options("update control");

				strcat(condition_tag, sel_tag);
				if(i < m_IncludePath.count-1)
					strcat(condition_tag, " and ");
			}


			if (HC_Show_Existence_By_Key(m_ConditionStyle, "self")) {
				HC_Open_Segment_By_Key(HC_KShow_Owner_By_Key(m_ConditionStyle));
					char buffer[MVO_BUFFER_SIZE];
					int count=0;
					sprintf(buffer, "user option=%s", condition_tag);
					if (condition_tag[0] != '\0' && HC_Show_Existence(buffer)) 
					{
						HC_Show_One_User_Option(condition_tag, buffer);
						sscanf(buffer, "%d", &count);
						
						count--;

						if (count>0) {
							sprintf(buffer, "%s=%d", condition_tag, count);
							HC_Set_User_Options(buffer);
						}
						else
							HC_UnSet_One_User_Option(condition_tag);
					}
					else
						HC_Delete_By_Key(m_ConditionStyle);

				HC_Close_Segment();
			}

		}

		// untag all the includers
		char base_tag[MVO_BUFFER_SIZE], sel_tag[MVO_BUFFER_SIZE];
		GetBaseTag(base_tag);
		for(int i = 1; i < m_IncludePath.count; i++)
		{
			sprintf(sel_tag, "%s_%d", base_tag, i); //MAKE_MVO_SELECT_TAG
			HC_Open_Segment_By_Key(HC_KShow_Owner_Original_Key(m_IncludePath.keys[i]));
				HC_UnSet_One_Condition(sel_tag);
			HC_Close_Segment();
		}


		// if it is an entity, may be we will have to move it back up under its parent segment
		if (is_entity_sel)
		{
			HC_KEY hilight_seg_key = HC_KShow_Owner_Original_Key(m_key);

			// if there is no other style applied, then we know we can safely move
			// the entity back - as there is not other path which wants it to be highlighted
			// else we just get rid of the style segment
			if( HC_Show_Existence_By_Key(hilight_seg_key, "style") <= 1)
			{
				seg_key = HC_KShow_Owner_Original_Key(hilight_seg_key );
				HC_Open_Segment_By_Key(seg_key);
						HC_Move_By_Key(m_key, ".");
				HC_Close_Segment();
			}
			else
				HC_Delete_By_Key(m_ConditionStyle);

			// if there is nothing else in the highlight segment get rid of it
			m_pSelectionSet->UnRegisterHighlightSeg(hilight_seg_key);
			if(HC_Show_Existence_By_Key(hilight_seg_key, "first match, geometry, subsegment") <= 0)
				HC_Delete_By_Key(hilight_seg_key);
		}


		m_ConditionStyle = INVALID_KEY;


		return true;
	}
}


static void get_base_tag(HC_KEY key, const int incl_count, const HC_KEY * incl_keys, char * retTag)
{
#if 1
	const char hex[] = "0123456789abcdef";
	const char * prefix = "mvo_select";
	int i, j;
	
	while ((*retTag++ = *prefix++));	
	retTag--;

	for(i = 0; i <= incl_count; i++)
	{

		*retTag++ = '_';

		for(j = 0; j < (int)(2*sizeof(HC_KEY)); j++) { 
			*retTag++ = hex[(int)(key&0x0F)];
			key>>=4;
		}

		if(i < incl_count)
			key = incl_keys[i];
	}

	*retTag = '\0';
#else
	retTag += sprintf(retTag, "mvo_select_%p", (void*) key);
	for(int i = 0; i < incl_count; i++)
	{
		retTag += sprintf(retTag, "_%p", (void*)incl_keys[i]);
	}
#endif
}


void HSmartSelItem::GetBaseTag(char * retTag)
{
	get_base_tag(m_key, m_IncludePath.count, m_IncludePath.keys, retTag);
}


bool HSmartSelItem::IsInstanced() const
{
	// if this is something directly under the model key 
	// then it isn't instanced
	if( m_IncludePath.count <= (m_pSelectionSet->GetReferenceSelection() ? 2 : 1))
		return false;

	return true;
}


bool HSmartSelItem::Delete()
{
	// unhighlight it first
	UnHighlight();
	
	// if this is old style selection or something directly 
	// under the model key - use direct delete
	if( !m_pSelectionSet->GetReferenceSelection() && m_IncludePath.count > 1)
		m_pSelectionSet->DeInstance(this);

	if(HC_Show_Existence_By_Key(m_key, "self"))
	{
		HC_Delete_By_Key(m_key);
		m_key = INVALID_KEY;
	}

	return true;
}



bool HSmartSelItem::IsHighlighted() const
{
	if(m_pSelectionSet->GetReferenceSelection())
	{
		if((const_cast<HSmartSelItem*>(this))->GetHighlightedRefListCount()>0)
			return true;
		else
			return false;
	}
	else
	{
		if(m_ConditionStyle != INVALID_KEY)
			return true;
		else
			return false;
	}
}


bool HSmartSelItem::IsRegionHighlighted(const HC_KEY key, const HSelectionSet * selection_set, 
								  const int incl_count, const HC_KEY * incl_keys, int region)
{
	if(selection_set->GetReferenceSelection())
	{
		return selection_set->IsRegionSelected(key, incl_count, incl_keys, region);
	}
	else
	{
		bool retval = false;
		HC_Open_Geometry(key);{
			char region_str[MVO_BUFFER_SIZE];
			sprintf(region_str, "user options = hregion%d highlighted", region);
			if(HC_Show_Existence(region_str)){
				retval = true;
			}
		}HC_Close_Geometry();
		return retval;
	}
}

bool HSmartSelItem::IsHighlighted(const HC_KEY key, const HSelectionSet * selection_set, 
								  const int incl_count, const HC_KEY * incl_keys)

{
	if(selection_set->GetReferenceSelection())
	{
		return selection_set->IsSelected(key, incl_count, incl_keys);
	}
	else
	{
		// figure out the condition we might have set to highlight this
		char base_tag[MVO_BUFFER_SIZE], condition_tag[MVO_BUFFER_SIZE];
		char * cp=condition_tag;

		*cp = '\0';
		get_base_tag(key, incl_count, incl_keys, base_tag);
		for(int i = 1; i < incl_count; i++)
		{
			cp += sprintf(cp, "%s_%d", base_tag, i); //MAKE_MVO_SELECT_TAG

			if(i < incl_count-1) {
				*cp++ = ' ';
				*cp++ = 'a';
				*cp++ = 'n';
				*cp++ = 'd';
				*cp++ = ' ';
			}
		}

		// now find out if such a conditional style exists
		HC_KEY seg_key = key;
		char keytype[MVO_BUFFER_SIZE];
		HC_Show_Key_Type(key, keytype);
		if (!streq(keytype, "segment")) 
			seg_key = HC_KShow_Owner_Original_Key(key);

		
		HC_Open_Segment_By_Key(seg_key);
			HC_KEY found = Show_Existence_Conditional_Style(selection_set->GetHighlightStyle(), condition_tag);	
		HC_Close_Segment();

		if (found == INVALID_KEY)
			return false;
		else
			return true;
	}
}


bool HSmartSelItem::QueryIncludeDependency(HC_KEY include_key, HC_KEY& ret_dependent_key)
{
	bool has_dependency = false;
	for(int i = 0; i < m_IncludePath.count; i++)
	{
		if( m_IncludePath.keys[i] == include_key )
		{
			// we are indeed using this include_key - who's the dependent
			if( (i+1) < m_IncludePath.count)
				ret_dependent_key = m_IncludePath.keys[i+1];
			else
				ret_dependent_key = m_key;

			has_dependency = true;
			break;
		}
	}

	return has_dependency;
}

bool HSmartSelItem::UpdateIncludeDependency(HC_KEY include_key, HC_KEY dependent_key, HC_KEY replacement_key)
{
	bool updated=false;

	for(int i = 0; i < m_IncludePath.count; i++)
	{
		if( m_IncludePath.keys[i] == include_key )
		{
			// we are indeed using this include_key - replace the dependent
			if(dependent_key == m_key)
				m_key = replacement_key;
			else if(i+1<m_IncludePath.count && m_IncludePath.keys[i+1]==dependent_key)
			{
				// replace the include key and dependent and adjust the array
				//don't leave invalid keys in the array.
				if(replacement_key!=INVALID_KEY)
					m_IncludePath.keys[i++] = replacement_key;
				for(;(i+1) < m_IncludePath.count; i++)
					m_IncludePath.keys[i] = m_IncludePath.keys[i+1];
			}
			else 
				break;

			// adjust the count
			m_IncludePath.count--;
			updated=true;
			break;
		}
	}

	return updated;
}


/////////////////////////////////////////////////////////////////////////////
// HOldSelItem
//  A wrapper over selection item held in a list the HSelectionSet class. Typically a HOldSelItem 
//  is just a key to a selected segment or shell. In some cases it might have more information viz. sub-elements 
//  associated with it. 

HOldSelItem::HOldSelItem(HC_KEY key, HSelectionSet * selection_set, const char * selection_path, 
						 HC_KEY include_key, HC_KEY includer_key)
			  : HSelectionItem(key, selection_set)
{
	m_pSelectionPath = new char[strlen(selection_path)+1];
	strcpy(m_pSelectionPath, selection_path);
	m_IncludeKey = include_key;
	m_IncluderKey = includer_key;

}


HOldSelItem::~HOldSelItem( void )
{
	H_SAFE_DELETE_ARRAY(m_pSelectionPath);
}


bool HOldSelItem::Equals(const HSelectionItem* i2) const
{
	return HSelectionItem::Equals(i2);
}


bool HOldSelItem::Highlight()
{  
    char color1[MVO_BUFFER_SIZE], origcolor[MVO_BUFFER_SIZE], keytype[MVO_BUFFER_SIZE];
	char pathname[MVO_SEGMENT_PATHNAME_BUFFER], token[MVO_BUFFER_SIZE];
	HC_KEY key, seg_key, skey;
	float weight;
	bool is_segment_level;

	HPixelRGBA selectedFaceColor, selectedEdgeColor, selectedMarkerColor;
	float selectedEdgeWeight, selectedMarkerSize;
	m_pSelectionSet->GetSelectionFaceColor(selectedFaceColor);
	m_pSelectionSet->GetSelectionEdgeColor(selectedEdgeColor);
	m_pSelectionSet->GetSelectionMarkerColor(selectedMarkerColor);
	selectedEdgeWeight = m_pSelectionSet->GetSelectionEdgeWeight();
	selectedMarkerSize = m_pSelectionSet->GetSelectionMarkerSize();

	key = m_key;

    HC_Show_Key_Type(key, keytype);

    if (streq(keytype, "segment")) 
	{
		HUtilityAnnotation annotation;
		if (annotation.IsNote(key))
			key = HC_KShow_Owner_Original_Key(key);
		HC_Show_Segment(key, pathname);
		HC_Parse_String(pathname, "/", -1, token);

		if (streq(token, "cutting grids"))
			seg_key = HC_KShow_Owner_Original_Key(key);
		else
			seg_key = key;

	    is_segment_level = true;
	}
	else if (streq(keytype, "grid"))
	{
	    is_segment_level = true;
		seg_key = HC_KShow_Owner_Original_Key(key);
		seg_key = HC_KShow_Owner_Original_Key(seg_key);
	}
	else
	{
	    is_segment_level = false;
        seg_key = HC_KShow_Owner_Original_Key(key);
    }


	skey = seg_key;


    if ( is_segment_level )
	{
		bool include = (strchr (m_pSelectionPath, '<') != 0);


		if ((include) && (m_IncludeKey != INVALID_KEY) && (m_IncluderKey != INVALID_KEY))
		{
			HC_Delete_By_Key(m_IncludeKey);					// remove the original include link
			
			HC_Open_Segment_By_Key(m_IncluderKey);
			 seg_key = HC_KCopy_Segment(m_pSelectionPath, "tmp");	// copy the included segment
			HC_Close_Segment();

			HC_Open_Segment_By_Key(seg_key);
			 HC_Set_User_Index(H_HIGHLIGHT_KEY_MAGIC, (void *)skey); // store the orig included segment key in the copied segment
			HC_Close_Segment();
		}
		
		HC_Open_Segment_By_Key(seg_key);

			HC_Set_User_Value(1L);

			if (HC_Show_Existence("color"))
			{
				HC_Show_Color(color1);
				sprintf(origcolor, "origcolor = (%s)", color1);
				HC_Set_User_Options(origcolor);
			}

			if (HC_Show_Existence("line weight"))
			{
				HC_Show_Line_Weight(&weight);
				HCLOCALE(sprintf(origcolor, "origlineweight = (%f)", weight));
				HC_Set_User_Options(origcolor);
			}

			if (HC_Show_Existence("edge weight"))
			{
				HC_Show_Edge_Weight(&weight);
				HCLOCALE(sprintf(origcolor, "origedgeweight = (%f)", weight));
				HC_Set_User_Options(origcolor);
			}

			if (HC_Show_Existence("marker size"))
			{
				HUtility::PushAttribute("marker size");
				HC_Show_Marker_Size(&weight);
				HCLOCALE(sprintf(origcolor, "origmarkersize = (%f)", weight));
				HC_Set_User_Options(origcolor);
			}


			HC_Set_Color_By_Value ("geometry", "rgb", (float)selectedFaceColor.r()/255.0,
			    (float)selectedFaceColor.g()/255.0,  (float)selectedFaceColor.b()/255.0); 
			HC_Set_Color_By_Value ("edges,lines", "rgb", (float)selectedEdgeColor.r()/255.0,
			    (float)selectedEdgeColor.g()/255.0,  (float)selectedEdgeColor.b()/255.0); 
			HC_Set_Color_By_Value ("markers", "rgb", (float)selectedMarkerColor.r()/255.0,
			    (float)selectedMarkerColor.g()/255.0,  (float)selectedMarkerColor.b()/255.0); 

			if (selectedFaceColor.a() != 0 || selectedEdgeColor.a() != 0 || selectedMarkerColor.a() != 0)
			{
			    char color[MVO_BUFFER_SIZE];
				HCLOCALE(sprintf(color, "geometry = (transmission=(R=%1.4f G=%1.4f B=%1.4f)), edges = (transmission=(R=%1.4f G=%1.4f B=%1.4f)), lines = (transmission=(R=%1.4f G=%1.4f B=%1.4f)), markers = (transmission=(R=%1.4f G=%1.4f B=%1.4f))", 
					(float)selectedFaceColor.a()/256.0,  (float)selectedFaceColor.a()/256.0,  (float)selectedFaceColor.a()/256.0, 
					(float)selectedEdgeColor.a()/256.0,  (float)selectedEdgeColor.a()/256.0,  (float)selectedEdgeColor.a()/256.0,
					(float)selectedEdgeColor.a()/256.0,  (float)selectedEdgeColor.a()/256.0,  (float)selectedEdgeColor.a()/256.0,
					(float)selectedMarkerColor.a()/256.0,  (float)selectedMarkerColor.a()/256.0,  (float)selectedMarkerColor.a()/256.0));
				HC_Set_Color(color);
			}

			if (selectedEdgeWeight != 1.0)
			{
				HC_Set_Edge_Weight(selectedEdgeWeight);
				HC_Set_Line_Weight(selectedEdgeWeight);
			}

			if(selectedMarkerSize != 1.0)
				HC_Set_Marker_Size(selectedMarkerSize);

			HC_Set_Rendering_Options("attribute lock = color = (on, faces = no transmission)");
			HC_Set_Rendering_Options("general displacement = -8");

		HC_Close_Segment();
	}
    else 
	{
		HC_Open_Segment_By_Key(seg_key);
		 int ready = HC_QShow_Existence ("highlight", "self");
		 HC_Open_Segment("highlight");   
		 if (!ready) {
		    HC_Set_User_Index(H_HIGHLIGHT_KEY_MAGIC, (void *)seg_key);
			HC_Set_Color_By_Value ("geometry", "rgb", (float)selectedFaceColor.r()/255.0,
			    (float)selectedFaceColor.g()/255.0,  (float)selectedFaceColor.b()/255.0); 
			HC_Set_Color_By_Value ("edges,lines", "rgb", (float)selectedEdgeColor.r()/255.0,
			    (float)selectedEdgeColor.g()/255.0,  (float)selectedEdgeColor.b()/255.0); 
			HC_Set_Color_By_Value ("markers", "rgb", (float)selectedMarkerColor.r()/255.0,
			    (float)selectedMarkerColor.g()/255.0,  (float)selectedMarkerColor.b()/255.0); 

			if (selectedFaceColor.a() != 0 || selectedEdgeColor.a() != 0 || selectedMarkerColor.a() != 0)
			{
			    char color[MVO_BUFFER_SIZE];
				HCLOCALE(sprintf(color, "geometry = (transmission=(R=%1.4f G=%1.4f B=%1.4f)), edges = (transmission=(R=%1.4f G=%1.4f B=%1.4f)), lines = (transmission=(R=%1.4f G=%1.4f B=%1.4f)), markers = (transmission=(R=%1.4f G=%1.4f B=%1.4f))", 
					(float)selectedFaceColor.a()/256.0,  (float)selectedFaceColor.a()/256.0,  (float)selectedFaceColor.a()/256.0, 
					(float)selectedEdgeColor.a()/256.0,  (float)selectedEdgeColor.a()/256.0,  (float)selectedEdgeColor.a()/256.0,
					(float)selectedEdgeColor.a()/256.0,  (float)selectedEdgeColor.a()/256.0,  (float)selectedEdgeColor.a()/256.0,
					(float)selectedMarkerColor.a()/256.0,  (float)selectedMarkerColor.a()/256.0,  (float)selectedMarkerColor.a()/256.0));
				HC_Set_Color(color);
			}

			if (selectedEdgeWeight != 1.0)
			{
				HC_Set_Edge_Weight(selectedEdgeWeight);
				HC_Set_Line_Weight(selectedEdgeWeight);
			}
			if(selectedMarkerSize != 1.0)
				HC_Set_Marker_Size(selectedMarkerSize);
		 }
		 HC_Move_By_Key(key, ".");

		 HC_Close_Segment();
		HC_Close_Segment();	
    }

	return true;
}


bool HOldSelItem::UnHighlight()
{
	HoopsRemove(m_key);
	return true;
}

void HOldSelItem::DeselectSegment(HC_KEY key, char const *keytype)
{
	HC_KEY orig_key = INVALID_KEY;
    HC_KEY owner = INVALID_KEY;
    HC_KEY seg_key = INVALID_KEY;
    HUserOptions orig;
	char origdest[MVO_BUFFER_SIZE];
	char pathname[MVO_SEGMENT_PATHNAME_BUFFER];
	char token[MVO_BUFFER_SIZE];

    if (streq(keytype, "segment")) 
	{
		HC_Show_Segment(key, pathname);
		HC_Parse_String(pathname, "/", -1, token);

		if (streq(token, "cutting grids"))
			seg_key = HC_KShow_Owner_Original_Key(key);
		else
			seg_key = key;
	}
	else if (streq(keytype, "grid"))
	{
		seg_key = HC_KShow_Owner_Original_Key(key);
		seg_key = HC_KShow_Owner_Original_Key(seg_key);
	}
    assert( seg_key != INVALID_KEY );
    if( seg_key == INVALID_KEY )
        //this should never happen, because keytype != [segment,grid] should have 
        //already been screened out by the calling function
        return; 

	HC_Open_Segment_By_Key(seg_key);
		if (!HC_Show_One_Net_User_Index(H_HIGHLIGHT_KEY_MAGIC, &orig_key))
			orig_key = INVALID_KEY;
	HC_Close_Segment();

	if (orig_key != INVALID_KEY)			// segment was previously included
	{			
		owner = HC_KShow_Owner_Original_Key(seg_key);

		HC_Open_Segment_By_Key(seg_key);
		float matrix[16];
		    if (HC_Show_Existence("modelling matrix"))
		    {		    
 			HC_Show_Modelling_Matrix(matrix);
			HC_Open_Segment_By_Key(orig_key);
			HC_Set_Modelling_Matrix(matrix);
			HC_Close_Segment();
		    }
 		HC_Close_Segment();
 		HC_Open_Segment_By_Key(owner);
			HC_Include_Segment_By_Key(orig_key);
		HC_Close_Segment();
		HC_Delete_By_Key(seg_key);
	}
	else
	{
		HC_Open_Segment_By_Key(seg_key);{
			
			if(!streq(pathname, "/")){
				HC_UnSet_Color();
				HC_UnSet_Line_Weight();
				HC_UnSet_Edge_Weight();
				HC_UnSet_Marker_Size();
			}
			
			if (HC_Show_Existence("user options = origcolor")){
				
				orig.Show_One_Net_User_Option("origcolor");
				if (strcmp(orig.m_data,"")!=0){
					strncpy(origdest, orig.m_data + 1, strlen(orig.m_data) - 2);	// strip off parens
					strncpy(origdest + (strlen(orig.m_data) - 2), "\0", 2);		// null terminate the string
					HC_Set_Color(origdest);
					HC_UnSet_One_User_Option("origcolor");
				}
			}
			
			if (HC_Show_Existence("user options = origlineweight")){

				orig.Show_One_Net_User_Option("origlineweight");
				if (strcmp(orig.m_data,"")!=0){
					float oldweight;
					strncpy(origdest, orig.m_data + 1, strlen(orig.m_data) - 2);	// strip off parens
					strncpy(origdest + (strlen(orig.m_data) - 2), "\0", 2);		// null terminate the string
					HCLOCALE(oldweight = (float) atof(origdest));
					HC_Set_Line_Weight(oldweight);
					HC_UnSet_One_User_Option("origlineweight");
				}
			}
			
			
			if (HC_Show_Existence("user options = origedgeweight")){

				orig.Show_One_Net_User_Option("origedgeweight");
				if (strcmp(orig.m_data,"")!=0){
					float oldweight;
					strncpy(origdest, orig.m_data + 1, strlen(orig.m_data) - 2);	// strip off parens
					strncpy(origdest + (strlen(orig.m_data) - 2), "\0", 2);		// null terminate the string
					HCLOCALE(oldweight = (float) atof(origdest));
					HC_Set_Edge_Weight(oldweight);
					HC_UnSet_One_User_Option("origedgeweight");
				}
			}
			
			if (HC_Show_Existence("user options = origmarkersize")){

				orig.Show_One_Net_User_Option("origmarkersize");
				if (strcmp(orig.m_data,"")!=0){
					float oldweight;
					strncpy(origdest, orig.m_data + 1, strlen(orig.m_data) - 2);	// strip off parens
					strncpy(origdest + (strlen(orig.m_data) - 2), "\0", 2);		// null terminate the string
					HCLOCALE(oldweight = (float) atof(origdest));
					HC_Set_Marker_Size(oldweight);
					HC_UnSet_One_User_Option("origmarkersize");
				}
			}
			
			if(HC_Show_Existence("rendering options = general displacement"))
				HC_UnSet_One_Rendering_Option("general displacement");
			
			if(streq(pathname, "/"))
				HC_Set_Rendering_Options("no attribute lock");
			else 
				HC_UnSet_One_Rendering_Option("attribute lock");

			HC_Set_User_Value(0L);

		}HC_Close_Segment();		
	}
}


void HOldSelItem::DeselectGeometry(HC_KEY key)
{
	HC_KEY orig_key, seg_key;
	float matrix[16];
	bool has_matrix = false;
	
    seg_key = HC_KShow_Owner_Original_Key(key);
	HC_Open_Segment_By_Key(seg_key);
		HC_Show_One_Net_User_Index(H_HIGHLIGHT_KEY_MAGIC, &orig_key);
		if (HC_Show_Existence ("modelling matrix")) 
		{
			HC_Show_Modelling_Matrix (matrix);
			HC_UnSet_Modelling_Matrix ();
			has_matrix = true;
		}
	HC_Close_Segment();
	HC_Open_Segment_By_Key(orig_key);
		if( has_matrix && HC_Show_Existence ("geometry, subsegments, first match") ) {
			HC_Open_Segment( "" );
				HC_Set_Modelling_Matrix( matrix );
				HC_Move_By_Key(key, ".");
			HC_Close_Segment();
		}
		else {
			HC_Move_By_Key(key, ".");
		}
	HC_Close_Segment();
}


/* deselect an item
 - if a piece of geometry, move it back to it's original segment
 - if a segment, restore the original rendering attributes (color, etc...)
*/
void HOldSelItem::HoopsRemove(HC_KEY key)
{
	char key_status[MVO_BUFFER_SIZE];
    char keytype[MVO_BUFFER_SIZE];

	//if the object has already been deleted, there's nothing to do
	HC_Show_Key_Status (key, key_status);
	if( streq( key_status, "invalid" ) )
		return;

	HC_Show_Key_Type(key, keytype);
	if( streq( keytype, "segment" ) ||
		streq( keytype, "grid" ) ) {
		DeselectSegment( key, keytype );
	}
	else {
		DeselectGeometry( key );
	}
	 
}


bool HOldSelItem::Delete()
{
	// unhighlight it first
	UnHighlight();
	
	HC_Delete_By_Key(m_key);
	m_key = INVALID_KEY;
	return true;
}



bool HOldSelItem::IsHighlighted() const
{
	HC_KEY orig_key = INVALID_KEY;
	char keytype[MVO_BUFFER_SIZE];
	MVO_POINTER_SIZED_INT hlite = 0;
	
	HC_Show_Key_Type(m_key, keytype);
	
	if (streq(keytype, "segment"))
	{
		HC_Open_Segment_By_Key(m_key);
	}
	else {
		HC_KEY owner_key = HC_KShow_Owner_Original_Key(m_key);
		
		if (owner_key < 0)
			HC_Open_Segment_By_Key(owner_key);
		else {
			char segment[MVO_SEGMENT_PATHNAME_BUFFER];
			HC_Show_Owner_By_Key(m_key, segment);
			HC_Open_Segment(segment);
		}
	}
	
		if (HC_Show_Existence("user value"))
			HC_Show_User_Value(&hlite);

		if (!HC_Show_One_Net_User_Index(H_HIGHLIGHT_KEY_MAGIC, &orig_key))
			orig_key = INVALID_KEY;
	HC_Close_Segment();
	
	
	if((hlite == 1) || (orig_key != INVALID_KEY))
		return true;
	else
		return false;
	
}

bool HOldSelItem::QueryIncludeDependency(HC_KEY include_key, HC_KEY& ret_dependent_key)
{
	// I don't handle includes - isn't that why I am called Old?
	return false;		// false is not failure, but says do we have dependency
}


bool HOldSelItem::UpdateIncludeDependency(HC_KEY include_key, HC_KEY dependent_key, HC_KEY replacement_key)
{
	// don't care about instancing
	return true;
}
