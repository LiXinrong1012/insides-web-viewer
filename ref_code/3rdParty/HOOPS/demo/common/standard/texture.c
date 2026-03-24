/*---------------------------------------------------------------------*\
 |                                                                     |
 |  Copyright (c) 1986-1992, 1993 by Ithaca Software.                  |
 |  All rights reserved.                                               |
 |  Use of copyright notice does not imply publication or disclosure.  |
 |                                                                     |
 |  THIS SOFTWARE CONTAINS CONFIDENTIAL AND PROPRIETARY INFORMATION    |
 |  CONSTITUTING VALUABLE TRADE SECRETS OF ITHACA SOFTWARE AND MAY     |
 |  NOT BE (a) DISCLOSED TO THIRD PARTIES, (b) COPIED IN ANY FORM,     |
 |  OR (c) USED FOR ANY PURPOSE EXCEPT AS SPECIFICALLY PERMITTED IN    |
 |  WRITING BY ITHACA SOFTWARE.                                        |
 |                                                                     |
\*---------------------------------------------------------------------*/

/*
 * $Id: texture.c,v 1.5 2010-10-26 21:29:09 jason Exp $
 */


#include "hc.h"
#include "hc_standalone.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

#define N		20
#define MYDOMAIN	6.0f
#define F(x)		((float)(x))
#define SURFACE		1

/* Definitions for menu selections */
#define ID_FACES	0
#define ID_EDGES	1
#define ID_MARKERS	2
#define ID_CACHE	3
#define ID_PREVIOUS	4
#define ID_NEXT		5
#define ID_EXIT		6
#define ID_SWZB		7
#define ID_SWFB		8
#define ID_DBLBUF	9
#define ID_PRINT	10

#define FIRST_SCREEN	0
#define LAST_SCREEN	12

typedef int Boolean;
#define false	(Boolean)0
#define true	(Boolean)(-1)

typedef struct {
    int		Id;
    char	Name[256];
    HC_KEY	SegId;
    char	bgclr[20];
    char	fgclr[20];
    char	hlclr[20];
    float	ButtonHt;
    float	ButtonWt;
    Boolean	bToggle;
    Boolean	bPressed;
} ButtonType;

typedef struct {
    float   x, y, z;
} Point;

static	float	square_mesh[] = {
				 -0.8f,	-0.8f,	0.0f,
				 -0.8f,	 0.8f,	0.0f,
				  0.8f,	-0.8f,	0.0f,
				  0.8f,	 0.8f,	0.0f
				};

static	float	square_mesh_param[] = {
				 0.0f,	0.0f,	0.0f,
				 0.0f,	1.0f,	0.0f,
				 1.0f,	0.0f,	0.0f,
				 1.0f,	1.0f,	0.0f
				};

static	float	square_menu[] = {
				  -0.1f, -0.1f, 0.0f,
				  -0.1f,  0.1f, 0.0f,
				   0.1f, -0.1f, 0.0f,
				   0.1f,  0.1f, 0.0f
				};

Point	base[] = {  
	{-1.0f, -1.0f, 0.0f},
	{-1.0f,  1.0f, 0.0f},
	{1.0f,  1.0f, 0.0f},
	{1.0f, -1.0f, 0.0f}};

Point	horiz_panel[] = {  
	{-1.0f, -0.1f, 0.0f},
	{-0.9f,  0.1f, 0.0f},
	{0.9f,  0.1f, 0.0f},
	{1.0f, -0.1f, 0.0f}};

Point	vert_panel[] =  {  
	{-0.05f, -1.0f, 0.0f},
	{-0.05f,  1.0f, 0.0f},
	{0.05f,  0.8f, 0.0f},
	{0.05f, -0.8f, 0.0f}};

char	    tex_def[256];
char        style_segment[80];
char	    texture_image[80], caching[8];
int	    faces_on = 1;
int	    edges_on = 0;
int	    markers_on = 0;
int	    cache_on = 0;
int	    swzb_on = 0;
int	    swfb_on = 0;
int	    dblbuf_on = 0;
ButtonType  Buttons[20];
int	    button_id[20];
int	    num_buttons;


/* Function Prototypes */
void Initialize ();
void Init_Buttons (void);
int  Create_Button (char *, int, float, float, float, float, Boolean);
void Turn_Button_On (int);
void Turn_Button_Off (int);
void Toggle_Button (int, int);
int  Get_Button_Selection (HC_KEY);
int  Get_Next_Action (void);
void Delete_Buttons (void);
void HighLight (char *, int);
void Display_Header (char *);
void Display_Footer (char *);
int  Display_Screen (int);
int  Select_Texture (char *);
int  Tiling_Demo (char *);
int  Interpolation_Demo (char *);
int  Channel_Mapping_Demo (char *);
int  Value_Scale_Demo (char *);
int  Perspective_Correction_Demo (char *);
int  Transformation_Demo (char *);
int  Styled_Transforms_Demo (char *);
int  Multiple_Texture_Demo (char *);
int  Multiple_Texture_Transforms_Demo (char *);
int  Surface_Texture_Demo (char *);
int  Surface_UV_Demo (char *);
int  Surface_World_Demo (char *);
int  Surface_Normal_Demo (char *);


int main ()
{   long    key;
    int	    selected = -1;
    int	    screen = FIRST_SCREEN;

    strcpy (caching, "off");
    Init_Buttons ();
    Initialize ();

    HC_Open_Segment ("?Picture");
	HC_Define_Alias ("?Menu",   "?Picture/Menu");
	HC_Define_Alias ("?Screen", "?Picture/Screen");
	HC_Define_Alias ("?Title",  "?Picture/Title");

	HC_Set_Driver_Options ("no double-buffering");
	HC_Set_Heuristics ("hidden surfaces");
	HC_Set_Color (
	    "Windows = darker darker gray, text = white, window contrast = black");
	HC_Set_Visibility ("markers = off, edges = off, faces = on");
	HC_Set_Marker_Symbol ("[*]");
    HC_Close_Segment ();

    HC_Open_Segment ("?Menu");
	HC_Set_Window (0.7, 1.0, -1.0, 1.0);
	HC_Open_Segment ("settings");
	    HC_Include_Segment ("?Main Menu");
	HC_Close_Segment ();
	HC_Open_Segment ("navigation");
	    HC_Include_Segment ("?First Screen");
	HC_Close_Segment ();
	HC_Open_Segment ("selected texture");
	    HC_Open_Segment ("object");
		HC_Set_Visibility (
		    "edges = off, lights = off, markers = off, faces = on");
		HC_Scale_Object (7.5, 7.5, 1.0);
		HC_Include_Segment ("?Texture");
	    HC_Close_Segment ();
	    key = 0;
	HC_Close_Segment ();
    HC_Close_Segment ();

    HC_Open_Segment ("?Screen");
	HC_Set_Window (-1.0, 0.7, -1.0, 1.0);
	HC_Set_Window_Frame ("off");

	while (selected != ID_EXIT) {
	    selected = Display_Screen (screen);
	    switch (selected) {
		case ID_NEXT : {
		    if (screen == FIRST_SCREEN) {
			HC_Open_Segment ("?Menu/navigation");
			    HC_Flush_Contents (".", "includes");
			    HC_Include_Segment ("?Middle Screen");
			HC_Close_Segment ();
		    }
		    screen++;
		    if (screen > LAST_SCREEN) screen = LAST_SCREEN;
		    if (screen == LAST_SCREEN) {
			HC_Open_Segment ("?Menu/navigation");
			    HC_Flush_Contents (".", "includes");
			    HC_Include_Segment ("?Last Screen");
			HC_Close_Segment ();
		    }
		}   break;

		case ID_PREVIOUS : {
		    if (screen == LAST_SCREEN) {
			HC_Open_Segment ("?Menu/navigation");
			    HC_Flush_Contents (".", "includes");
			    HC_Include_Segment ("?Middle Screen");
			HC_Close_Segment ();
		    }
		    screen--;
		    if (screen < FIRST_SCREEN) screen = FIRST_SCREEN;
		    if (screen == FIRST_SCREEN) {
			HC_Open_Segment ("?Menu/navigation");
			    HC_Flush_Contents (".", "includes");
			    HC_Include_Segment ("?First Screen");
			HC_Close_Segment ();
		    }
		}   break;
	    }
	}
    HC_Close_Segment ();

    HC_Exit_Program ();
    return 0;
}


int Display_Screen (int screen)
{
    int	selected;

    switch (screen) {
	case 0 : {
	    selected = Select_Texture (texture_image);
	}   break;

	case 1 : {
	    selected = Tiling_Demo (texture_image);
	}   break;

	case 2 : {
	    selected = Interpolation_Demo (texture_image);
	}   break;

	case 3 : {
	    selected = Channel_Mapping_Demo (texture_image);
	}   break;

	case 4 : {
	    selected = Value_Scale_Demo (texture_image);
	}   break;

	case 5 : {
	    selected = Perspective_Correction_Demo (texture_image);
	}   break;

	case 6 : {
	    selected = Transformation_Demo (texture_image);
	}   break;

	case 7 : {
	    selected = Styled_Transforms_Demo (texture_image);
	}   break;

	case 8 : {
	    selected = Multiple_Texture_Demo (texture_image);
	}   break;

	case 9 : {
	    selected = Multiple_Texture_Transforms_Demo (texture_image);
	}   break;

	case 10 : {
	    selected = Surface_UV_Demo (texture_image);
	}   break;

	case 11 : {
	    selected = Surface_World_Demo (texture_image);
	}   break;

	case 12 : {
	    selected = Surface_Normal_Demo (texture_image);
	}   break;

	default : {
	    selected = 0;
	}
    }

    return selected;
}


void HighLight (char *seg, int on)
{
    HC_Open_Segment (seg);
	if (on)
	    HC_Set_Color ("faces = bright red");
	else
	    HC_Set_Color ("faces = dark red");
    HC_Close_Segment ();
}


void Display_Header (char *header)
{
    HC_Open_Segment ("header");
	HC_Set_Text_Font ("size = 0.03 sru");
	HC_Set_Text_Alignment ("*");
	HC_Insert_Text (0.0, 0.85, 0.0, header);
    HC_Close_Segment ();
}

void Display_Footer (char *footer)
{
    HC_Open_Segment ("footer");
	HC_Set_Text_Font ("size = 0.03 sru");
	HC_Insert_Text (0.0, -0.85, 0.0, footer);
    HC_Close_Segment ();
}

void Initialize ()
{
    HC_KEY  mesh_key, menu_key;
    char    tex_def[80];

    HC_Define_Alias ("?IFruit",  "?Include Library/Metafiles/Fruit");
    HC_Define_Alias ("?IClrBar", "?Include Library/Metafiles/ClrBar");
    HC_Define_Alias ("?IArches", "?Include Library/Metafiles/Arches");
    HC_Define_Alias ("?IGrid",   "?Include Library/Metafiles/Grid");
    HC_Define_Alias ("?IClrSq",  "?Include Library/Metafiles/ClrSq");

    HC_Define_Alias ("?Texture", "?Include Library/Texture");

    HC_Define_Alias ("?menu_square", "?Include Library/Geometry/menu_sq");
    HC_Define_Alias ("?mesh_square", "?Include Library/Geometry/mesh_sq");
    HC_Define_Alias ("?Surface",     "?Include Library/Geometry/surface");

    HC_Define_Alias ("?Styled Transforms",  "?Style Library/Transforms/Texture");
    HC_Define_Alias ("?Diffuse Transforms",  "?Style Library/Transforms/Diffuse");
    HC_Define_Alias ("?Specular Transforms", "?Style Library/Transforms/Specular");

    strcpy (texture_image, "nicefruit");
    strcpy (style_segment, "?IFruit");

    /* Load all the images */
    HC_Open_Segment ("?IFruit");
	HC_Read_Metafile ("fruit.hmf", ".", "");
    HC_Close_Segment ();
    HC_Open_Segment ("?IClrBar");
	HC_Read_Metafile ("clrbar.hmf", ".", "");
    HC_Close_Segment ();
    HC_Open_Segment ("?IArches");
	HC_Read_Metafile ("arches.hmf", ".", "");
    HC_Close_Segment ();
    HC_Open_Segment ("?IGrid");
	HC_Read_Metafile ("grid.hmf", ".", "");
    HC_Close_Segment ();
    HC_Open_Segment ("?IClrSq");
	HC_Read_Metafile ("clrsq.hmf", ".", "");
    HC_Close_Segment ();

    /* Load the geometry */
    HC_Open_Segment ("?menu_square");
	menu_key = HC_KInsert_Mesh (2, 2, square_menu);
	HC_MSet_Vertex_Parameters (menu_key, 0, 4, 3, square_mesh_param);
    HC_Close_Segment ();

    HC_Open_Segment ("?mesh_square");
	mesh_key = HC_KInsert_Mesh (2, 2, square_mesh);
	HC_MSet_Vertex_Parameters (mesh_key, 0, 4, 3, square_mesh_param);
    HC_Close_Segment ();

    /* Styled Transforms */
    HC_Open_Segment ("?Styled Transforms");
	HC_Scale_Texture (2.0, 2.0, 2.0);
	HC_Rotate_Texture (0.0, 0.0, 45.0);
    HC_Close_Segment ();

    HC_Open_Segment ("?Diffuse Transforms");
	HC_Rotate_Texture (0.0, 0.0, 45.0);
    HC_Close_Segment ();

    HC_Open_Segment ("?Specular Transforms");
	HC_Rotate_Texture (0.0, 0.0, -45.0);
    HC_Close_Segment ();

    /* Selected Texture :: Default - nicefruit */
    HC_Open_Segment ("?Texture");
	HC_Include_Segment ("?menu_square");
	sprintf (tex_def, "tiling = off, source = %s", texture_image);
	HC_Define_Texture ("choice tile", tex_def);
	HC_Set_Color ("faces = choice tile");
    HC_Close_Segment ();

    /* Example Surface */
    HC_Open_Segment ("?Surface");
    {
	int		i, j;
	Point	pt[N][N];
	float	param[N][N][3];
	float	spacing = MYDOMAIN / (float)(N - 1);

	for (i = 0; i < N; ++i) {
	    for (j = 0; j < N; ++j) {
		pt[i][j].x = i * spacing;
		pt[i][j].y = j * spacing;
		pt[i][j].z = 0.7f * (float) sin(pt[i][j].x) *
			     (float) sin(3.0f * pt[i][j].y);
		param[i][j][0] = (float)i * spacing;
		param[i][j][1] = (float)j * spacing;
		param[i][j][2] = 0.0f;
	    }
	}
	mesh_key = HC_KInsert_Mesh (N, N, pt);
	HC_MSet_Vertex_Parameters (mesh_key, 0, (N*N), 3, (float *)param);
    }
    HC_Close_Segment ();
}

int Select_Texture (char *texture_image)
{
    char	szSegment[80];
    HC_KEY	key_list[10];
    HC_KEY	key;
    int		dc;
    int		selected = -1;

    HC_Open_Segment ("Images");
	Display_Header ("TEXTURE MAPPING EXAMPLE");
	HC_Set_Visibility ("faces = on, markers = off, edges = off");

	key_list[0] = HC_KOpen_Segment ("Fruit Image");
	    HC_Set_Window (-0.5, -0.3, 0.3, 0.5);
	    HC_Set_Window_Frame ("off");
	    HC_Scale_Object (10.0, 10.0, 1.0);
	    HC_Include_Segment ("?menu_square");
	    HC_Style_Segment ("?IFruit");
	    sprintf (tex_def, "tiling = off, source = %s, caching = %s",
		     "nicefruit", caching);
	    HC_Define_Texture ("fruit tile", tex_def);
	    HC_Set_Color ("faces = fruit tile");
	HC_Close_Segment ();

	key_list[1] = HC_KOpen_Segment ("Arches Image");
	    HC_Set_Window (-0.1, 0.1, -0.1, 0.1);
	    HC_Set_Window_Frame ("off");
	    HC_Scale_Object (10.0, 10.0, 1.0);
	    HC_Include_Segment ("?menu_square");
	    HC_Style_Segment ("?IArches");
	    sprintf (tex_def, "tiling = off, source = %s, caching = %s",
		     "arches", caching);
	    HC_Define_Texture ("arches tile", tex_def);
	    HC_Set_Color ("faces = arches tile");
	HC_Close_Segment ();

	key_list[2] = HC_KOpen_Segment ("ClrBar Image");
	    HC_Set_Window (0.3, 0.5, 0.3, 0.5);
	    HC_Set_Window_Frame ("off");
	    HC_Scale_Object (10.0, 10.0, 1.0);
	    HC_Include_Segment ("?menu_square");
	    HC_Style_Segment ("?IClrBar");
	    sprintf (tex_def, "tiling = off, source = %s, caching = %s",
		     "clrbar", caching);
	    HC_Define_Texture ("clrbar tile", tex_def);
	    HC_Set_Color ("faces = clrbar tile");
	HC_Close_Segment ();

	key_list[3] = HC_KOpen_Segment ("Grid Image");
	    HC_Set_Window (-0.5, -0.3, -0.5, -0.3);
	    HC_Set_Window_Frame ("off");
	    HC_Scale_Object (10.0, 10.0, 1.0);
	    HC_Include_Segment ("?menu_square");
	    HC_Style_Segment ("?IGrid");
	    sprintf (tex_def, "tiling = off, source = %s, caching = %s",
		     "grid", caching);
	    HC_Define_Texture ("grid tile", tex_def);
	    HC_Set_Color ("faces = grid tile");
	HC_Close_Segment ();

	key_list[4] = HC_KOpen_Segment ("ClrSq Image");
	    HC_Set_Window (0.3, 0.5, -0.5, -0.3);
	    HC_Set_Window_Frame ("off");
	    HC_Scale_Object (10.0, 10.0, 1.0);
	    HC_Include_Segment ("?menu_square");
	    HC_Style_Segment ("?IClrSq");
	    sprintf (tex_def, "tiling = off, source = %s, caching = %s",
		     "clrsq", caching);
	    HC_Define_Texture ("clrsq tile", tex_def);
	    HC_Set_Color ("faces = clrsq tile");
	HC_Close_Segment ();
    HC_Close_Segment ();

    while ((selected != ID_NEXT) &&
	   (selected != ID_PREVIOUS) &&
	   (selected != ID_EXIT)) {
	HC_Get_Selection (szSegment);
	HC_Show_Selection_Element (&key, &dc, &dc, &dc);
	if (key == key_list[0])
	    selected = 10;
	else if (key == key_list[1])
	    selected = 11;
	else if (key == key_list[2])
	    selected = 12;
	else if (key == key_list[3])
	    selected = 13;
	else if (key == key_list[4])
	    selected = 14;
	else
	    selected = Get_Button_Selection (key);

	switch (selected) {
	    case 10 : sprintf (texture_image, "%s", "nicefruit");
		      strcpy (style_segment, "?IFruit");
		      break;
	    case 11 : sprintf (texture_image, "%s", "arches");
		      strcpy (style_segment, "?IArches");
		      break;
	    case 12 : sprintf (texture_image, "%s", "clrbar");
		      strcpy (style_segment, "?IClrBar");
		      break;
	    case 13 : sprintf (texture_image, "%s", "grid");
		      strcpy (style_segment, "?IGrid");
		      break;
	    case 14 : sprintf (texture_image, "%s", "clrsq");
		      strcpy (style_segment, "?IClrSq");
		      break;
	}

	HC_Open_Segment ("?Texture");
	    HC_Flush_Contents (".", "styles");
	    HC_Style_Segment (style_segment);
	    HC_UnDefine_Texture ("choice tile");
	    sprintf (tex_def, "tiling = off, source = %s", texture_image);
	    HC_Define_Texture ("choice tile", tex_def);
	    HC_Set_Color ("faces = choice tile");
	HC_Close_Segment ();
    }

    HC_UnDefine_Texture ("fruit tile");
    HC_UnDefine_Texture ("arches tile");
    HC_UnDefine_Texture ("clrbar tile");
    HC_UnDefine_Texture ("grid tile");
    HC_UnDefine_Texture ("clrsq tile");
    HC_Delete_Segment ("Images");

    /*
    **	Style Segment is used so that the color map associated with the
    **	texture image is loaded in.
    */
    HC_Flush_Contents (".", "styles");
    HC_Style_Segment (style_segment);

    return (selected);
}

int Tiling_Demo (char *texture_image)
{
    int	    selected;

    HC_Open_Segment ("tiling");
	Display_Header ("TILING");

	HC_Open_Segment ("types");
	    HC_Set_Text_Font ("size = 0.015 sru");

	    HC_Open_Segment ("clamp");
	        HC_Insert_Text (0.0, 0.98, 0.0, "clamp");
		HC_Scale_Object (0.3333, 0.3333, 0.3333);
		HC_Translate_Object (-0.6667, 0.0, 0.0);
		HC_Include_Segment ("?mesh_square");
		HC_Scale_Texture (0.45, 0.45, 0.45);
		sprintf (tex_def, "tiling = off, source = %s, caching = %s",
			 texture_image, caching);
		HC_Define_Texture ("clamped tile", tex_def);
		HC_Set_Color ("faces = edges = markers = clamped tile");
	    HC_Close_Segment ();

	    HC_Open_Segment ("tile");
	        HC_Insert_Text (0.0, 0.98, 0.0, "tile");
		HC_Scale_Object (0.3333, 0.3333, 0.3333);
		HC_Include_Segment ("?mesh_square");
		HC_Scale_Texture (0.45, 0.45, 0.45);
		sprintf (tex_def, "tiling, source = %s, caching = %s",
			 texture_image, caching);
		HC_Define_Texture ("normal tile", tex_def);
		HC_Set_Color ("faces = edges = markers = normal tile");
	    HC_Close_Segment ();

	    HC_Open_Segment ("mirror");
	        HC_Insert_Text (0.0, 0.98, 0.0, "mirror");
		HC_Scale_Object (0.3333, 0.3333, 0.3333);
		HC_Translate_Object (0.6667, 0.0, 0.0);
		HC_Include_Segment ("?mesh_square");
		HC_Scale_Texture (0.45, 0.45, 0.45);
		sprintf (tex_def, "tiling = mirror, source = %s, caching = %s",
			 texture_image, caching);
		HC_Define_Texture ("mirror tile", tex_def);
		HC_Set_Color ("faces = edges = markers = mirror tile");
	    HC_Close_Segment ();
	HC_Close_Segment ();
    HC_Close_Segment ();

    selected = Get_Next_Action ();

    HC_Delete_Segment ("tiling");
    HC_UnDefine_Texture ("clamped tile");
    HC_UnDefine_Texture ("normal tile");
    HC_UnDefine_Texture ("mirror tile");

    return (selected);
}

int Interpolation_Demo (char *texture_image)
{
    int	    selected;

    HC_Open_Segment ("interpolation");
	Display_Header ("INTERPOLATION FILTER");

	HC_Open_Segment ("types");
            HC_Set_Text_Alignment ("*v");
	    HC_Set_Text_Font ("size = 0.015 sru");

	    HC_Open_Segment ("no interpolation");
		HC_Insert_Text (0.0, 0.98, 0.0, "no interpolation filter");
		HC_Scale_Object (0.3333, 0.3333, 0.3333);
		HC_Translate_Object (-0.6667, 0.0, 0.0);
		HC_Include_Segment ("?mesh_square");
		HC_Translate_Texture (-0.052, -0.22, 0.0);
		HC_Scale_Texture (30.0, 30.0, 30.0);
		sprintf (tex_def, "interpolation filter = off, source = %s, caching = %s",
			 texture_image, caching);
		HC_Define_Texture ("no interp", tex_def);
		HC_Set_Color ("faces = edges = markers = no interp");
	    HC_Close_Segment ();

	    HC_Open_Segment ("bilinear");
		HC_Insert_Text (0.0, 0.98, 0.0, "bilinear");
		HC_Scale_Object (0.3333, 0.3333, 0.3333);
		HC_Include_Segment ("?mesh_square");
		HC_Translate_Texture (-0.052, -0.22, 0.0);
		HC_Scale_Texture (30.0, 30.0, 30.0);
		sprintf (tex_def, "interpolation filter, source = %s, caching = %s",
			 texture_image, caching);
		HC_Define_Texture ("bilinear interp", tex_def);
		HC_Set_Color ("faces = edges = markers = bilinear interp");
	    HC_Close_Segment ();

	    HC_Open_Segment ("stochastic");
		HC_Insert_Text (0.0, 0.98, 0.0, "stochastic");
		HC_Scale_Object (0.3333, 0.3333, 0.3333);
		HC_Translate_Object (0.6667, 0.0, 0.0);
		HC_Include_Segment ("?mesh_square");
		HC_Translate_Texture (-0.052, -0.22, 0.0);
		HC_Scale_Texture (30.0, 30.0, 30.0);
		sprintf (tex_def,
			 "interpolation filter = stochastic, source = %s, caching = %s",
			 texture_image, caching);
		HC_Define_Texture ("stochastic interp", tex_def);
		HC_Set_Color ("faces = edges = markers = stochastic interp");
	    HC_Close_Segment ();
	HC_Close_Segment ();
    HC_Close_Segment ();

    selected = Get_Next_Action ();

    HC_Delete_Segment ("interpolation");
    HC_UnDefine_Texture ("no interp");
    HC_UnDefine_Texture ("bilinear interp");
    HC_UnDefine_Texture ("stochastic interp");

    return (selected);
}


int Channel_Mapping_Demo (char *texture_image)
{
    int	    selected;

    HC_Open_Segment ("channel mapping");
        Display_Header ("CHANNEL MAPPING");

	HC_Open_Segment ("types");
	    HC_Set_Text_Alignment ("*v");
	    HC_Set_Text_Font ("size = 0.015 sru");
	    HC_Open_Segment ("red is zero");
		HC_Insert_Text (0.0, 0.98, 0.0,
				"red channel mapping = zero");
		HC_Scale_Object (0.3333, 0.3333, 0.3333);
		HC_Translate_Object (-0.6667, 0.0, 0.0);
		HC_Include_Segment ("?mesh_square");
		sprintf (tex_def,
			 "red channel mapping = zero, source = %s, caching = %s",
			texture_image, caching);
		HC_Define_Texture ("red_is_zero", tex_def);
		HC_Set_Color ("faces = edges = markers = red_is_zero");
	    HC_Close_Segment ();

	    HC_Open_Segment ("green blue red");
		HC_Insert_Text (0.0, 0.98, 0.0, "rc = g, gc = b, bc = r");
		HC_Scale_Object (0.3333, 0.3333, 0.3333);
		HC_Include_Segment ("?mesh_square");
		sprintf (tex_def,
			 "red channel mapping = green, green channel mapping = blue, blue channel mapping = red, source = %s, caching = %s",
			 texture_image, caching);
		HC_Define_Texture ("rgb_gbr", tex_def);
		HC_Set_Color ("faces = edges = markers = rgb_gbr");
	    HC_Close_Segment ();

	    HC_Open_Segment ("grayscale");
		HC_Insert_Text (0.0, 0.98, 0.0, "rc = gc = bc = luminance");
		HC_Scale_Object (0.3333, 0.3333, 0.3333);
		HC_Translate_Object (0.6667, 0.0, 0.0);
		HC_Include_Segment ("?mesh_square");
		sprintf (tex_def,
			 "red channel mapping = luminance, green channel mapping = luminance, blue channel mapping = luminance, source = %s, caching = %s",
			 texture_image, caching);
		HC_Define_Texture ("gray_scale", tex_def);
		HC_Set_Color ("faces = edges = markers = gray_scale");
	    HC_Close_Segment ();
	HC_Close_Segment ();
    HC_Close_Segment ();

    selected = Get_Next_Action ();

    HC_Delete_Segment ("channel mapping");
    HC_UnDefine_Texture ("red_is_zero");
    HC_UnDefine_Texture ("rgb_gbr");
    HC_UnDefine_Texture ("gray_scale");

    return (selected);
}


int Value_Scale_Demo (char *texture_image)
{
    int	    selected;

    HC_Open_Segment ("value scale");
	Display_Header ("VALUE SCALE");

	HC_Open_Segment ("types");
	    HC_Set_Text_Alignment ("*v");
	    HC_Set_Text_Font ("size = 0.015 sru");

	    HC_Open_Segment ("Invert");
		HC_Insert_Text (0.0, 0.98, 0.0, "no value scale");
		HC_Scale_Object (0.3333, 0.3333, 0.3333);
		HC_Translate_Object (-0.6667, 0.0, 0.0);
		HC_Include_Segment ("?mesh_square");
		sprintf (tex_def, "no value scale, source = %s, caching = %s",
			 texture_image, caching);
		HC_Define_Texture ("invert", tex_def);
		HC_Set_Color ("faces = edges = markers = invert");
	    HC_Close_Segment ();

	    HC_Open_Segment ("brighten");
		HC_Insert_Text (0.0, 0.98, 0.0, "value scale = (0, 0.5)");
		HC_Scale_Object (0.3333, 0.3333, 0.3333);
		HC_Include_Segment ("?mesh_square");
		sprintf (tex_def,
			 "value scale = (0.0, 0.5), source = %s, caching = %s",
			 texture_image, caching);
		HC_Define_Texture ("brighten", tex_def);
		HC_Set_Color ("faces = edges = markers = brighten");
	    HC_Close_Segment ();

	    HC_Open_Segment ("darken");
		HC_Insert_Text (0.0, 0.98, 0.0, "value scale = (0.5, 1.0)");
		HC_Scale_Object (0.3333, 0.3333, 0.3333);
		HC_Translate_Object (0.6667, 0.0, 0.0);
		HC_Include_Segment ("?mesh_square");
		sprintf (tex_def,
			 "value scale = (0.5, 1.0), source = %s, caching = %s",
			 texture_image, caching);
		HC_Define_Texture ("darken", tex_def);
		HC_Set_Color ("faces = edges = markers = darken");
	    HC_Close_Segment ();
	HC_Close_Segment ();
    HC_Close_Segment ();

    selected = Get_Next_Action ();

    HC_Delete_Segment ("value scale");
    HC_UnDefine_Texture ("invert");
    HC_UnDefine_Texture ("brighten");
    HC_UnDefine_Texture ("darken");

    return (selected);
}


int Perspective_Correction_Demo (char *texture_image)
{
    int	    selected;

    HC_Open_Segment ("perspective correction");
	Display_Header ("PERSPECTIVE CORRECTION");

	sprintf (tex_def, "tiling, source = %s, caching = %s",
		 texture_image, caching);
	HC_Define_Texture ("normal tile", tex_def);

	HC_Open_Segment ("types");
	    HC_Set_Text_Alignment ("*v");
	    HC_Set_Text_Font ("size = 0.015 sru");

	    HC_Open_Segment ("no correction");
		HC_Insert_Text (0.0, -0.95, 0.0,
				"no perspective correction");
		HC_Scale_Object (0.5, 0.5, 0.5);
		HC_Translate_Object (-0.5, 0.0, 0.0);
		HC_Open_Segment ("");
		    HC_Include_Segment ("?mesh_square");
		    HC_Translate_Object (0.0, 0.8, 0.0);
		    HC_Scale_Object (1.0, 20.0, 1.0);
		    HC_Rotate_Object (80.0, 0.0, 0.0);
		    HC_Translate_Object (0.0, -0.8, 0.0);
		    HC_Scale_Texture (1.0, 0.1, 1.0);
		HC_Close_Segment ();
		HC_Set_Rendering_Options ("no perspective correction");
		HC_Set_Color ("faces = edges = markers = normal tile");
	    HC_Close_Segment ();

	    HC_Open_Segment ("corrected");
		HC_Insert_Text (0.0, -0.95, 0.0, "perspective correction");
		HC_Scale_Object (0.5, 0.5, 0.5);
		HC_Translate_Object (0.5, 0.0f, 0.0);
		HC_Open_Segment ("");
		    HC_Include_Segment ("?mesh_square");
		    HC_Translate_Object (0.0, 0.8, 0.0);
		    HC_Scale_Object (1.0, 20.0, 1.0);
		    HC_Rotate_Object (80.0, 0.0, 0.0);
		    HC_Translate_Object (0.0, -0.8, 0.0);
		    HC_Scale_Texture (1.0, 0.1, 1.0);
		HC_Close_Segment ();
		HC_Set_Rendering_Options ("perspective correction");
		HC_Set_Color ("faces = edges = markers = normal tile");
	    HC_Close_Segment ();
	HC_Close_Segment ();
    HC_Close_Segment ();

    selected = Get_Next_Action ();

    HC_UnDefine_Texture ("normal tile");
    HC_Delete_Segment ("perspective correction");

    return (selected);
}


int Transformation_Demo (char *texture_image)
{
    int	    selected;

    HC_Open_Segment ("transformations");
	Display_Header ("TRANSFORMATIONS (with tiling on)");

	sprintf (tex_def, "tiling, source = %s, caching = %s",
		 texture_image, caching);
	HC_Define_Texture ("normal tile", tex_def);

	HC_Open_Segment ("types");
	    HC_Set_Text_Alignment ("*v");
	    HC_Set_Text_Font ("size = 0.015 sru");

	    HC_Open_Segment ("rotate");
		HC_Insert_Text (0.0, 0.98, 0.0,
				"Rotate_Texture(0.0,0.0,30.0)");
		HC_Scale_Object (0.3333, 0.3333, 0.3333);
		HC_Translate_Object (-0.6667, 0.0, 0.0);
		HC_Include_Segment ("?mesh_square");
		HC_Rotate_Texture (0.0, 0.0, 30.0);
		HC_Set_Color ("faces = edges = markers = normal tile");
	    HC_Close_Segment ();

	    HC_Open_Segment ("translate");
		HC_Insert_Text (0.0, 0.98, 0.0,
				"Translate_Texture(0.5,-0.5,0.0)");
		HC_Scale_Object (0.3333, 0.3333, 0.3333);
		HC_Include_Segment ("?mesh_square");
		HC_Translate_Texture (0.5, -0.5, 0.0);
		HC_Set_Color ("faces = edges = markers = normal tile");
	    HC_Close_Segment ();

	    HC_Open_Segment ("scale");
		HC_Insert_Text (0.0, 0.98, 0.0,
				"Scale_Texture(1.5,-1.0,1.0)");
		HC_Scale_Object (0.3333, 0.3333, 0.3333);
		HC_Translate_Object (0.6667, 0.0, 0.0);
		HC_Include_Segment ("?mesh_square");
		HC_Scale_Texture (1.5, -1.0, 1.0);
		HC_Set_Color ("faces = edges = markers = normal tile");
	    HC_Close_Segment ();
	HC_Close_Segment ();
    HC_Close_Segment ();

    selected = Get_Next_Action ();

    HC_UnDefine_Texture ("normal tile");
    HC_Delete_Segment ("transformations");

    return (selected);
}


int Styled_Transforms_Demo (char *texture_image)
{
    int	    selected;

    sprintf (tex_def,
	     "tiling, transform = \"?Styled Transforms\", source = %s, caching = %s",
	     texture_image, caching);
    HC_Define_Texture ("style_matrix tile", tex_def);

    sprintf (tex_def,
	     "no tiling, transform = \"?Styled Transforms\", source = %s, caching = %s",
	     texture_image, caching);
    HC_Define_Texture ("style_matrix no tile", tex_def);

    HC_Open_Segment ("transformations");
	Display_Header ("TRANSFORMATIONS (with styled xform)");

	HC_Open_Segment ("");
	    HC_Set_Text_Alignment ("*v");
	    HC_Set_Text_Font ("size = 0.015 sru");
	    HC_Insert_Text (0.0, 0.7, 0.0,
		"Scale_Texture(2.0,2.0,2.0) Rotate_Texture(0.0,0.0,45.0)");
	HC_Close_Segment ();

	HC_Open_Segment ("types");
	    HC_Set_Text_Alignment ("*v");
	    HC_Set_Text_Font ("size = 0.015 sru");

		HC_Open_Segment ("rotate");
		    HC_Insert_Text (0.0, 0.98, 0.0,
				    "Rotate_Texture(0.0,0.0,45.0)");
		    HC_Scale_Object (0.3333, 0.3333, 0.3333);
		    HC_Translate_Object (-0.6667, 0.0, 0.0);
		    HC_Include_Segment ("?mesh_square");
		    HC_Rotate_Texture (0.0, 0.0, 45.0);
		    HC_Set_Color ("faces = edges = markers = style_matrix tile");
		HC_Close_Segment ();

		HC_Open_Segment ("translate");
		    HC_Insert_Text (0.0, 0.98, 0.0,
			"Translate_Texture(0.5,0.5,0.0) - No Tiling");
		    HC_Scale_Object (0.3333, 0.3333, 0.3333);
		    HC_Include_Segment ("?mesh_square");
		    HC_Rotate_Texture (0.0, 0.0, -45.0);
		    HC_Scale_Texture (0.5, 0.5, 0.5);
		    HC_Translate_Texture (0.5, 0.5, 0.0);
		    HC_Set_Color ("faces = edges = markers = style_matrix no tile");
		HC_Close_Segment ();

		HC_Open_Segment ("scale");
		    HC_Insert_Text (0.0, 1.1, 0.0,
				    "Rotate_Texture(0.0,0.0,-45.0)");
		    HC_Insert_Text (0.0, 0.98, 0.0,
				    "Scale_Texture(0.5,-0.5,0.5)");
		    HC_Scale_Object (0.3333, 0.3333, 0.3333);
		    HC_Translate_Object (0.6667, 0.0, 0.0);
		    HC_Include_Segment ("?mesh_square");
		    HC_Rotate_Texture (0.0, 0.0, -45.0);
		    HC_Scale_Texture (0.5, -0.5, 0.5);
		    HC_Set_Color ("faces = edges = markers = style_matrix tile");
		HC_Close_Segment ();
	HC_Close_Segment ();
    HC_Close_Segment ();

    selected = Get_Next_Action ();

    HC_UnDefine_Texture ("style_matrix tile");
    HC_UnDefine_Texture ("style_matrix no tile");
    HC_Delete_Segment ("transformations");

    return (selected);
}

int Multiple_Texture_Demo (char *texture_image)
{
    int	    selected;
    Point   pos, tgt;

    pos.x = 0.0f; pos.y = 0.0f; pos.z = -1.0f;
    tgt.x = 0.0f; tgt.y = 0.0f; tgt.z = 0.0f;

    HC_Open_Segment ("Multiple Textures");
	Display_Header ("MULTIPLE TEXTURES");


	HC_Open_Segment ("types");
	    sprintf (tex_def,
		     "tiling, source = %s, caching = %s",
		     texture_image, caching);
	    HC_Define_Texture ("diffuse tex", tex_def);

	    sprintf (tex_def,
		     "tiling, source = %s, caching = %s",
		     "clrsq", caching);
	    HC_Define_Texture ("specular tex", tex_def);

	    HC_Set_Color ("faces = (diffuse = diffuse tex, specular = specular tex)");
            HC_Set_Color ("edges = markers = diffuse tex");

	    HC_Set_Text_Alignment ("*v");
	    HC_Set_Text_Font ("size = 0.015 sru");

	    HC_Open_Segment ("Spot");
		HC_Open_Segment ("Geometry");
		    HC_Insert_Text (0.0, 0.98, 0.0,
			"Diffuse = Fruit, Specular = ClrBar, Spot Light");
		    HC_Include_Segment ("?mesh_square");
		    HC_Scale_Object (0.666667, 0.666667, 0.666667);
		    HC_Insert_Spot_Light (&pos, &tgt,
			"illumination cone = 60 degrees");
		HC_Close_Segment ();
	    HC_Close_Segment ();
	HC_Close_Segment ();
    HC_Close_Segment ();

    selected = Get_Next_Action ();

    HC_UnDefine_Texture ("diffuse tex");
    HC_UnDefine_Texture ("specular tex");
    HC_Delete_Segment ("Multiple Textures");

    return (selected);
}


int Multiple_Texture_Transforms_Demo (char *texture_image)
{
    int	    selected;
    Point   pos, tgt;

    pos.x = 0.0f; pos.y = 0.0f; pos.z = -1.0f;
    tgt.x = 0.0f; tgt.y = 0.0f; tgt.z = 0.0f;

    sprintf (tex_def,
	     "tiling, transform = \"?Diffuse Transforms\", source = %s, caching = %s",
	     texture_image, caching);
    HC_Define_Texture ("diffuse tile", tex_def);

    sprintf (tex_def,
	     "tiling, transform = \"?Specular Transforms\", source = %s, caching = %s",
	     "clrsq", caching);
    HC_Define_Texture ("specular tile", tex_def);

    HC_Open_Segment ("Multiple Texture Transforms");
	Display_Header ("TRANSFORMATIONS (with multiple styled xform)");

	HC_Open_Segment ("");
	    HC_Set_Text_Alignment ("*v");
	    HC_Set_Text_Font ("size = 0.015 sru");
	    HC_Insert_Text (0.0, 0.7, 0.0,
			    "Diffuse Texture = Rotate(0,0,45), Specular Texture = Rotate(0,0,-45)");
	HC_Close_Segment ();

	HC_Open_Segment ("types");
	    HC_Set_Text_Alignment ("*v");
	    HC_Set_Text_Font ("size = 0.015 sru");

	    HC_Set_Color ("edges = markers = diffuse tile");
	    HC_Set_Color ("faces = (diffuse = diffuse tile, specular = specular tile)");

		HC_Open_Segment ("rotate");
		    HC_Insert_Text (0.0, 0.98, 0.0, "No Local Transforms");
		    HC_Scale_Object (0.3333, 0.3333, 0.3333);
		    HC_Translate_Object (-0.6667, 0.0, 0.0);
		    HC_Include_Segment ("?mesh_square");
		    HC_Insert_Spot_Light (&pos, &tgt,
					  "illumination cone = 60 degrees");
		HC_Close_Segment ();

		HC_Open_Segment ("translate");
		    HC_Insert_Text (0.0, 0.98, 0.0,
				    "Rotate Texture(0.0,0.0,45.0)");
		    HC_Scale_Object (0.3333, 0.3333, 0.3333);
		    HC_Include_Segment ("?mesh_square");
		    HC_Rotate_Texture (0.0, 0.0, 45.0);
		    HC_Insert_Spot_Light (&pos, &tgt,
					  "illumination cone = 60 degrees");
		HC_Close_Segment ();

		HC_Open_Segment ("scale");
		    HC_Insert_Text (0.0, 0.98, 0.0,
				    "Scale_Texture(1.0,-1.0,1.0)");
		    HC_Scale_Object (0.3333, 0.3333, 0.3333);
		    HC_Translate_Object (0.6667, 0.0, 0.0);
		    HC_Include_Segment ("?mesh_square");
		    HC_Scale_Texture (1.0, -1.0, 1.0);
		    HC_Insert_Spot_Light (&pos, &tgt,
					  "illumination cone = 60 degrees");
		HC_Close_Segment ();
	HC_Close_Segment ();
    HC_Close_Segment ();

    selected = Get_Next_Action ();

    HC_UnDefine_Texture ("diffuse tile");
    HC_UnDefine_Texture ("specular tile");
    HC_Delete_Segment ("Multiple Texture Transforms");

    return (selected);
}


int Surface_UV_Demo (char *texture_image)
{
    int	    selected;

    HC_Open_Segment ("heading");
	Display_Header ("Surface :: source parametrization - uv");
    HC_Close_Segment ();

    HC_Open_Segment ("example surface");
	HC_Set_Heuristics ("hidden surfaces");
	HC_Set_Rendering_Options ("perspective correction");
	HC_Insert_Distant_Light (0.0, 0.0, -1.0);

	HC_Set_Camera_By_Volume ("perspective", 0.0, MYDOMAIN, 0.0, MYDOMAIN);
	HC_Orbit_Camera (0.0, -60.0);
	HC_Orbit_Camera (20.0, 0.0);

	HC_Open_Segment ("source uv");
	    HC_Include_Segment ("?Surface");
	    sprintf (tex_def,
		     "tiling, source = %s, caching = %s",
		     texture_image, caching);
	    HC_Define_Texture ("uvw tile", tex_def);
	    HC_Set_Color ("faces = edges = markers = uvw tile");
	    HC_Scale_Texture (2.3, 2.3, 2.3);
	HC_Close_Segment ();

    HC_Close_Segment ();

    selected = Get_Next_Action ();

    HC_Delete_Segment ("example surface");
    HC_Delete_Segment ("heading");
    HC_UnDefine_Texture ("uvw tile");

    return (selected);
}

int Surface_World_Demo (char *texture_image)
{
    int	    selected;

    HC_Open_Segment ("heading");
	Display_Header ("Surface :: source parametrization - world");
    HC_Close_Segment ();

    HC_Open_Segment ("example surface");
	HC_Set_Heuristics ("hidden surfaces");
	HC_Set_Rendering_Options ("perspective correction");
	HC_Insert_Distant_Light (0.0, 0.0, -1.0);

	HC_Set_Camera_By_Volume ("perspective", 0.0, MYDOMAIN, 0.0, MYDOMAIN);
	HC_Orbit_Camera (0.0, -60.0);
	HC_Orbit_Camera (20.0, 0.0);

	HC_Open_Segment ("source world");
	    HC_Include_Segment ("?Surface");
	    sprintf (tex_def,
		     "tiling, parameterization source = world, source = %s, caching = %s",
		     texture_image, caching);
	    HC_Define_Texture ("world tile", tex_def);
	    HC_Set_Color ("faces = edges = markers = world tile");
	    HC_Scale_Texture (1.0, 1.0, 1.0);
	HC_Close_Segment ();

    HC_Close_Segment ();

    selected = Get_Next_Action ();

    HC_Delete_Segment ("example surface");
    HC_Delete_Segment ("heading");
    HC_UnDefine_Texture ("world tile");

    return (selected);
}


int Surface_Normal_Demo (char *texture_image)
{
    int	    selected;

    HC_Open_Segment ("heading");
	Display_Header ("Surface :: source parametrization - surface normal");
    HC_Close_Segment ();

    HC_Open_Segment ("example surface");
	HC_Set_Heuristics ("hidden surfaces");
	HC_Set_Rendering_Options ("perspective correction");
	HC_Insert_Distant_Light (0.0, 0.0, -1.0);

	HC_Set_Camera_By_Volume ("perspective", 0.0, MYDOMAIN, 0.0, MYDOMAIN);
	HC_Orbit_Camera (0.0, -60.0);
	HC_Orbit_Camera (20.0, 0.0);

	HC_Open_Segment ("normal world");
	    HC_Include_Segment ("?Surface");
	    sprintf (tex_def,
		     "tiling, parameterization source = surface normal, source = %s, caching = %s",
		     texture_image, caching);
	    HC_Define_Texture ("normal tile", tex_def);
	    HC_Set_Color ("faces = edges = markers = normal tile");
	    HC_Scale_Texture (1.0, 1.0, 1.0);
	HC_Close_Segment ();

    HC_Close_Segment ();

    selected = Get_Next_Action ();

    HC_Delete_Segment ("example surface");
    HC_Delete_Segment ("heading");
    HC_UnDefine_Texture ("normal tile");

    return (selected);
}

void Init_Buttons (void)
{
    num_buttons = 0;

    HC_Define_Alias ("?Previous",	"?Include Library/Footer Menu/Previous");
    HC_Define_Alias ("?Next",	"?Include Library/Footer Menu/Next");
    HC_Define_Alias ("?Exit",	"?Include Library/Footer Menu/Exit");
    HC_Define_Alias ("?First Screen",	"?Include Library/Footer Menu/First Screen");
    HC_Define_Alias ("?Middle Screen",	"?Include Library/Footer Menu/Middle Screen");
    HC_Define_Alias ("?Last Screen",	"?Include Library/Footer Menu/Last Screen");
    HC_Define_Alias ("?Settings Menu",	"?Include Library/Settings Menu");
    HC_Define_Alias ("?Main Menu",	"?Include Library/Main Menu");

    HC_Open_Segment ("?Include Library");
	HC_Open_Segment ("panels");
	    HC_Open_Segment ("vert-panel");
		HC_Insert_Polygon (4, vert_panel);
	    HC_Close_Segment ();
	    HC_Open_Segment ("horiz-panel");
		HC_Insert_Polygon (4, horiz_panel);
	    HC_Close_Segment ();
	HC_Close_Segment ();

	HC_Open_Segment ("Button");
	    HC_Set_Camera_Projection ("stretched");
	    HC_Set_Visibility ("edges = on, faces = off, markers = off");
	    HC_Insert_Polygon (4, base);
	    HC_Open_Segment ("Parts");
		HC_Set_Visibility ("edges = off, faces = on, markers = off");
		HC_Open_Segment ("bottom-right");
		    HC_Set_Color ("faces = darker darker gray");
		    HC_Open_Segment ("bottom");
			HC_Include_Segment ("?Include Library/panels/horiz-panel");
			HC_Translate_Object (0.0, -0.9, 0.0);
		    HC_Close_Segment ();
		    HC_Open_Segment ("right");
			HC_Include_Segment ("?Include Library/panels/vert-panel");
			HC_Scale_Object (-1.0, 1.0, 1.0);
			HC_Translate_Object (0.95, 0.0, 0.0);
		    HC_Close_Segment ();
		HC_Close_Segment ();
		HC_Open_Segment ("top-left");
		    HC_Set_Color ("faces = lighter gray");
		    HC_Open_Segment ("top");
			HC_Include_Segment ("?Include Library/panels/horiz-panel");
			HC_Scale_Object (1.0, -1.0, 1.0);
			HC_Translate_Object (0.0, 0.9, 0.0);
		    HC_Close_Segment ();
		    HC_Open_Segment ("left");
			HC_Include_Segment ("?Include Library/panels/vert-panel");
			HC_Translate_Object (-0.95, 0.0, 0.0);
		    HC_Close_Segment ();
		HC_Close_Segment ();
	    HC_Close_Segment ();
	HC_Close_Segment ();


	HC_Open_Segment ("Footer Menu");
	    HC_Open_Segment ("Previous");
		Create_Button ("<<< Previous <<<", ID_PREVIOUS, 0.0f, -0.75f, 2.0f, 0.1f, false);
	    HC_Close_Segment ();
	    HC_Open_Segment ("Next");
		Create_Button (">>> Next >>>", ID_NEXT, 0.0f, -0.85f, 2.0f, 0.1f, false);
	    HC_Close_Segment ();
	    HC_Open_Segment ("Exit");
		Create_Button ("Exit", ID_EXIT, 0.0f, -0.95f, 2.0f, 0.1f, false);
	    HC_Close_Segment ();
	    HC_Open_Segment ("First Screen");
		HC_Include_Segment ("?Exit");
		HC_Include_Segment ("?Next");
	    HC_Close_Segment ();
	    HC_Open_Segment ("Last Screen");
		HC_Include_Segment ("?Previous");
		HC_Include_Segment ("?Exit");
	    HC_Close_Segment ();
	    HC_Open_Segment ("Middle Screen");
		HC_Include_Segment ("?Previous");
		HC_Include_Segment ("?Exit");
		HC_Include_Segment ("?Next");
	    HC_Close_Segment ();
	HC_Close_Segment ();

	HC_Open_Segment ("?Main Menu");
	    Create_Button ("Faces", ID_FACES, 0.0f, 0.95f, 2.0f, 0.1f, true);
	    Create_Button ("Edges", ID_EDGES, 0.0f, 0.85f, 2.0f, 0.1f, true);
	    Create_Button ("Markers", ID_MARKERS, 0.0f, 0.75f, 2.0f, 0.1f, true);
	    Create_Button ("Cache", ID_CACHE, 0.0f, 0.65f, 2.0f, 0.1f, true);
	    Create_Button ("SW Z Buf", ID_SWZB, 0.0f, 0.55f, 2.0f, 0.1f, true);
	    Create_Button ("Frame Buffer", ID_SWFB, 0.0f, 0.45f, 2.0f, 0.1f, true);
	    Create_Button ("Double Buffer", ID_DBLBUF, 0.0f, 0.35f, 2.0f, 0.1f, true);
	    Create_Button ("Print", ID_PRINT, 0.0f, 0.25f, 2.0f, 0.1f, false);
	    Toggle_Button (ID_FACES, faces_on);
	    Toggle_Button (ID_EDGES, edges_on);
	    Toggle_Button (ID_MARKERS, markers_on);
	    Toggle_Button (ID_CACHE, cache_on);
	    Toggle_Button (ID_SWZB, swzb_on);
	    Toggle_Button (ID_SWFB, swfb_on);
	    Toggle_Button (ID_DBLBUF, dblbuf_on);
	HC_Close_Segment ();
    HC_Close_Segment ();
}


int Create_Button (char *button_name, int button_id, float xpos, float ypos,
		   float wt, float ht, Boolean bToggle)
{
    char    segName[80];

    sprintf (segName, "Buttons/button-%d", num_buttons);
    Buttons[num_buttons].Id = button_id;
    Buttons[num_buttons].bToggle = bToggle;
    Buttons[num_buttons].bPressed = 0;
    strcpy (Buttons[num_buttons].Name, button_name);
    strcpy (Buttons[num_buttons].hlclr, "yellow");
    Buttons[num_buttons].SegId = HC_KOpen_Segment (segName);
	HC_Set_Window (xpos-wt/2, xpos+wt/2, ypos-ht/2, ypos+ht/2);
	HC_Set_Window_Frame ("off");
	HC_Set_Color ("windows = gray, lines = white");
	HC_Include_Segment ("?Include Library/Button");
	HC_Set_Color ("text = black");
	HC_Set_Text_Font ("size = 0.015 sru");
	HC_Set_Text_Alignment ("*");
	HC_Insert_Text (0.0, 0.0, 0.0, button_name);
	if (bToggle) {
	    HC_Open_Segment ("light");
		HC_Set_Window (-0.85, -0.75, -0.65, 0.65);
		HC_Set_Window_Frame ("off");
		HC_Set_Color ("windows = darker darker gray");
	    HC_Close_Segment ();
	}
    HC_Close_Segment ();
    return (Buttons[num_buttons++].Id);
}

void Turn_Button_On (int index)
{
    char    clr[80];

    sprintf (clr, "windows = %s", Buttons[index].hlclr);
    HC_Open_Segment_By_Key (Buttons[index].SegId);
	HC_Open_Segment ("light");
	    HC_Set_Color (clr);
	HC_Close_Segment ();
    HC_Close_Segment ();
}

void Turn_Button_Off (int index)
{
    HC_Open_Segment_By_Key (Buttons[index].SegId);
	HC_Open_Segment ("light");
	    HC_Set_Color ("windows = darker darker gray");
	HC_Close_Segment ();
    HC_Close_Segment ();
}

void Toggle_Button (int button_id, int status)
{
    int	    i;

    for (i = 0; i < num_buttons; i++) {
	if (Buttons[i].Id == button_id) {
	    if (Buttons[i].bToggle) {
		Buttons[i].bPressed = status;
		if (Buttons[i].bPressed)
		    Turn_Button_On (i);
		else
		    Turn_Button_Off (i);
		return;
	    }
	}
    }
}

int Get_Button_Selection (HC_KEY key)
{
    char    visibility[80];
    int	    i;
    int	    found = 0;

    for (i = 0; i < num_buttons; i++) {
	if (Buttons[i].SegId == key) {
	    found = 1;
	    switch (Buttons[i].Id) {
		case ID_FACES : {
		    faces_on = !faces_on;
		    Toggle_Button (ID_FACES, faces_on);
		}   break;

		case ID_EDGES : {
		    edges_on = !edges_on;
		    Toggle_Button (ID_EDGES, edges_on);
		}   break;

		case ID_MARKERS : {
		    markers_on = !markers_on;
		    Toggle_Button (ID_MARKERS, markers_on);
		}   break;

		case ID_CACHE : {
		    cache_on = !cache_on;
		    Toggle_Button (ID_CACHE, cache_on);
		    if (cache_on)   strcpy (caching, "on");
		    else	    strcpy (caching, "off");
		}   break;

		case ID_SWZB : {
		    swzb_on = !swzb_on;
		    Toggle_Button (ID_SWZB, swzb_on);
		    if (swzb_on)
			HC_QSet_Rendering_Options ("?Picture/Screen",
			    "hsr algorithm = software z buffer");
		    else
			HC_QSet_Rendering_Options ("?Picture/Screen",
			    "hsr algorithm = painters");
		}   break;

		case ID_SWFB : {
		    swfb_on = !swfb_on;
		    Toggle_Button (ID_SWFB, swfb_on);
		    if (swfb_on)
			HC_QSet_Rendering_Options ("?Picture/Screen",
			    "technology = frame buffer");
		    else
			HC_QSet_Rendering_Options ("?Picture/Screen",
			    "technology = standard");
		}   break;

		case ID_DBLBUF : {
		    dblbuf_on = !dblbuf_on;
		    Toggle_Button (ID_DBLBUF, dblbuf_on);
		    if (dblbuf_on)
			HC_QSet_Driver_Options ("?Picture",
						"double-buffering");
		    else
			HC_QSet_Driver_Options ("?Picture",
						"no double-buffering");
		}   break;

		case ID_PRINT : {
		printf ("In Print\n");
		    HC_Open_Segment ("/driver/postscript/tex.ps");
			HC_Set_Color (	/* included segment does not modify top-level window */
			    "Windows = darker darker gray, text = white, window contrast = black");
			HC_Include_Segment ("?Picture");
		    HC_Close_Segment ();
		    HC_Update_Display ();
		    HC_Delete_Segment ("/driver/postscript/tex.ps");
		}   break;

		default:
			 break;
	    }
	    if (found)
		break;
	}
    }
    if (found) {
        sprintf (visibility, "faces = %s, edges = %s, markers = %s",
		 ((faces_on) ? "on" : "off"),
		 ((edges_on) ? "on" : "off"),
		 ((markers_on) ? "on" : "off"));
	HC_QSet_Visibility ("?Picture/Screen", visibility);
	return (Buttons[i].Id);
    }
    else
	return -1;
}

int Get_Next_Action () {
    char    seg[80];
    HC_KEY  key;
    int	    dc;
    int	    sel = -1;

    while (sel == -1) {
	HC_Get_Selection (seg);
	HC_Show_Selection_Element (&key, &dc, &dc, &dc);
	sel = Get_Button_Selection (key);
    }

    return (sel);
}
