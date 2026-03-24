/*
 * Copyright (c) 1998 by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.  Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 * Copyright (c) 1998 by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.  Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: pyramids.c,v 1.6 2006-08-07 20:38:49 stage Exp $
 */

#include "hc.h"

#include <stdio.h>

#define local static
#define PI 3.1415926
#include <math.h>
#define countof(x) (sizeof(x)/sizeof(x[0]))

typedef struct {float x, y, z;} Point;

local  Point	shell[] = {
	{-0.8f, -0.8f, -0.3f},
	{0.8f, -0.8f, -0.3f},
	{-0.8f,  0.8f, -0.3f},
	{0.8f,  0.8f, -0.3f},
	{0.0f,  0.0f, -0.5f}};

local  int	list[] = {3, 0, 1, 4,
			  3, 1, 3, 4,
			  3, 3, 2, 4,
			  3, 2, 0, 4
			 };
local  float	sindices[] = {0.0f, 2.0f, 2.0f, 0.0f, 3.0f};

local	char	*color_map = "red, green, white, blue";

local	Point	mesh[] = {
	{1.3f, -0.8f, 0.0f},
	{1.7f, -0.8f, 0.0f},
	{1.3f,  0.8f, 0.0f},
	{1.7f,  0.8f, 0.0f}};

local  float	mindices[] = {-0.5f, -0.5f, 3.5f, 3.5f};

local char	*texture_name = "pyramid_texture";

local  float	vparams[] = {   0.0f,	0.0f, 0.0,
				1.0f,	0.0f, 0.0,
				0.0f,	1.0f, 0.0,
				1.0f,	1.0f, 0.0,
				0.5f,	0.5f, 0.0
			    };

local void insert_pyramid () {
    long key;

    key = HC_KInsert_Shell (countof(shell), shell, countof(list), list);
    HC_MSet_Vertex_Colors_By_FIndex (key, "faces, edges, markers",
				     0, countof (sindices), sindices);
    HC_MSet_Vertex_Normals (key, 0, countof(shell), shell);
    HC_MSet_Vertex_Parameters(key, 0, countof(shell), 3, vparams);
}

local void insert_texture() {
    char texdef[128];

    HC_Read_Metafile ("fruit.hmf", ".", "");
    sprintf( texdef, "source = %s", "nicefruit");
    HC_Define_Texture( texture_name, texdef );
}



int main () {
    long key;
    char texture_color[128];

    HC_Open_Segment ("?include library/object");
        insert_pyramid ();
	HC_Insert_Distant_Light (1.0, 3.0, -1.0);
    HC_Close_Segment ();

    HC_Open_Segment ("?include library/texture");
        insert_texture ();
    HC_Close_Segment ();


    HC_Open_Segment ("?include library/triple");

        HC_Open_Segment ("dark");
	    HC_Set_Window (-1.0, -0.5, -1.0, 1.0);
            HC_Set_Visibility ("lights = off");
	    HC_Include_Segment ("?include library/object");
	HC_Close_Segment ();

        HC_Open_Segment ("flat");
	    HC_Set_Window (-0.5, 0.0, -1.0, 1.0);
	    HC_Set_Rendering_Options ("no lighting interpolation");
	    HC_Include_Segment ("?include library/object");
	HC_Close_Segment ();

	HC_Open_Segment ("gouraud");
	    HC_Set_Window (0.0, 0.5, -1.0, 1.0);
	    HC_Set_Rendering_Options ("lighting interpolation = gouraud");
	    HC_Include_Segment ("?include library/object");
	HC_Close_Segment ();

	HC_Open_Segment ("phong");
	    HC_Set_Window (0.5, 1.0, -1.0, 1.0);
	    HC_Set_Rendering_Options ("lighting interpolation = phong");
	    HC_Include_Segment ("?include library/object");
	HC_Close_Segment ();

    HC_Close_Segment ();

    HC_Open_Segment ("?picture");
	HC_Set_Window_Frame ("off");
	HC_Set_Color_Map (color_map);
	HC_Set_Color ("windows = black, window contrast = red, text = grey");
	HC_Set_Text_Size (0.4);

	HC_Open_Segment ("reference");
	    HC_Set_Window (-1.0, -0.7, 0.7, 1.0);
	    HC_Set_Camera_By_Volume ("ortho", -1.2, 1.8, -1.2, 1.2);
	    HC_Set_Rendering_Options ("no lighting interpolation");
	    HC_Set_Rendering_Options ("no color interpolation");
	    HC_Set_Rendering_Options ("no color index interpolation");

	    HC_Open_Segment ("model");
		HC_Set_Color ("edges = white");
		HC_Set_Marker_Symbol ("<*>");
		HC_Set_Marker_Size (0.5);
		HC_Set_Visibility ("lights = off, markers = on, edges = on, faces = off");
		HC_Include_Segment ("?include library/object");
	    HC_Close_Segment ();

	    HC_Open_Segment ("map");
		HC_Set_Visibility ("lights = off, markers = off, edges = off");
		HC_Set_Rendering_Options ("color index interpolation");
		key = HC_KInsert_Mesh (2, 2, mesh);
		HC_MSet_Vertex_Colors_By_FIndex (key, "faces",
				     0, countof (mindices), mindices);
	    HC_Close_Segment ();
	HC_Close_Segment ();

	HC_Open_Segment ("columns");
	    HC_Set_Window (-0.7, 1.0, 0.7, 1.0);
	    HC_Set_Camera_By_Volume ("stretched", -1.0, 1.0, -1.0, 1.0);
	    HC_Insert_Text (-0.75, 0.0, 0.0, "No Lighting");
	    HC_Insert_Text (-0.25, 0.0, 0.0, "Flat Lighting");
	    HC_Insert_Text ( 0.25, 0.0, 0.0, "Gouraud");
	    HC_Insert_Text ( 0.75, 0.0, 0.0, "Phong");
	HC_Close_Segment ();
	HC_Open_Segment ("rows");
	    HC_Set_Window (-1.0, -0.7, -1.0, 0.7);
	    HC_Set_Camera_By_Volume ("stretched", -1.0, 1.0, -1.0, 1.0);
	    HC_Insert_Text (0.0,  0.85, 0.0, "No Color Interpolation");
	    HC_Insert_Text (0.0,  0.75, 0.0, "No Index Interpolation");

	    HC_Insert_Text (0.0,  0.45, 0.0, "Color Interpolation");
	    HC_Insert_Text (0.0,  0.35, 0.0, "No Index Interpolation");

	    HC_Insert_Text (0.0,  0.05, 0.0, "No Color Interpolation");
	    HC_Insert_Text (0.0, -0.05, 0.0, "Index Interpolation");

	    HC_Insert_Text (0.0, -0.35, 0.0, "Color Interpolation");
	    HC_Insert_Text (0.0, -0.45, 0.0, "Index Interpolation");

	    HC_Insert_Text (0.0, -0.85, 0.0, "Texture");

	HC_Close_Segment ();

	HC_Open_Segment ("options");
	    HC_Set_Window (-0.7, 1.0, -1.0, 0.7);
	    HC_Set_Color ("face = grey, edges = grey, lights = white");
	    HC_Set_Visibility ("faces = on, edges = off, markers = off");

	    HC_Open_Segment ("nci ncii");
		HC_Set_Window (-1.0, 1.0, 0.6, 1.0);
		HC_Set_Rendering_Options ("no color interpolation");
		HC_Set_Rendering_Options ("no color index interpolation");
		HC_Include_Segment ("?include library/triple");
	    HC_Close_Segment ();

	    HC_Open_Segment ("ci ncii");
		HC_Set_Window (-1.0, 1.0, 0.2, 0.6);
		HC_Set_Rendering_Options ("color interpolation");
		HC_Set_Rendering_Options ("no color index interpolation");
		HC_Include_Segment ("?include library/triple");
	    HC_Close_Segment ();

	    HC_Open_Segment ("nci cii");
		HC_Set_Window (-1.0, 1.0, -0.2, 0.2);
		HC_Set_Rendering_Options ("no color interpolation");
		HC_Set_Rendering_Options ("color index interpolation");
		HC_Include_Segment ("?include library/triple");
	    HC_Close_Segment ();

	    HC_Open_Segment ("ci cii");
		HC_Set_Window (-1.0, 1.0, -0.6, -0.2);
		HC_Set_Rendering_Options ("color interpolation");
		HC_Set_Rendering_Options ("color index interpolation");
		HC_Include_Segment ("?include library/triple");
	    HC_Close_Segment ();

	    HC_Open_Segment ("tex");
		HC_Set_Rendering_Options ("no color index interpolation");
		HC_Set_Rendering_Options ("no color interpolation");
		HC_Set_Window (-1.0, 1.0, -1.0, -0.6);
		sprintf( texture_color, "faces = %s, edges = %s", texture_name, texture_name );
		HC_Set_Color( texture_color );
		HC_Include_Segment ("?include library/triple");
	    HC_Close_Segment ();

	HC_Close_Segment ();
	HC_Pause ();

	HC_Open_Segment ("options");
	    HC_Set_Visibility ("faces = off, edges = on, markers = off");
	HC_Close_Segment ();
	HC_Pause ();

	HC_Open_Segment ("options");
	    HC_Set_Visibility ("faces = on, edges = on, markers = off");
	HC_Close_Segment ();
	HC_Pause ();
    HC_Close_Segment ();

    HC_Exit_Program ();
    return 0;
}
