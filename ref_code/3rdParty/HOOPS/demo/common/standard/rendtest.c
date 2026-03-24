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
 *
 * $Id: rendtest.c,v 1.36 2010-10-26 21:29:09 jason Exp $
 */

#include "hc.h"
#include "hc_standalone.h"
#include "hic.h"
#include "hversion.h"
#ifdef _MSW_VER
#   include <malloc.h>
#endif /* _MSW_VER */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>


#ifndef USE_NO_GL

#ifdef OSX_SYSTEM

# undef OS_INLINE
# define OS_INLINE static __inline__ /* workaround for a problem in agl headers */
# include <AGL/agl.h>
# include <OpenGL/gl.h>
# include <OpenGL/glu.h>
# include <Carbon/Carbon.h>

#else

#ifdef WINDOWS_SYSTEM
#	ifndef WIN32_LEAN_AND_MEAN
#		define WIN32_LEAN_AND_MEAN
#	endif
# include <windows.h>
#endif

# include <GL/gl.h>
# include <GL/glu.h>

#endif
#endif

#include "rendtest.h"

#ifdef UNIX_SYSTEM
#include <unistd.h>
#endif

#define EXTRA_POINTER_FORMAT extra_pointer_format()


#define BLACK		0
#define RED		1
#define GREEN		2
#define BLUE		3
#define WHITE		4

#define NUM_RESULTS	15
static char *labels[] = {"show.info",
		         "atmos.att",
		         "attr.lock",
		         "col.int",
		         "col.indx.int",
		         "face.disp",
		         "hsr.alg",
		         "light.int1",
		         "light.int2",
		         "local.viewer",
				 "persp.corr",
		         "quantization",
		         "sw.fb.opts",
		         "technology",
		         "texture.int"};

/* timing */
static Vertex	results[NUM_RESULTS + 2];
static float	results_max;
/* allocated memory */
static Vertex	results2[NUM_RESULTS + 2];
static float	results2_max;
/* in use memory */
static Vertex	results3[NUM_RESULTS + 2];


/* image output globals */
int     b_image_out = 0;
int     image_file_format = RAW_ASCII;
int     image_source = HOOPS_SW;
int     driver_type = DEFAULT_DRIVER;
char    image_file_root[80];
char    image_file_name[80];
char    temp_file_name[80];
char    *driver_name;
char    unixtime[256];


void compute_mesh_data (
    float	xstart,
    float	xend,
    int		xnodes,
    float	ystart,
    float	yend,
    int		ynodes,
    Vertex	*pl,
    Parameter	*uvl) {
    float	x, y;
    float	xinc, yinc;

    xinc = (xend - xstart) / (xnodes - 1);
    yinc = (yend - ystart) / (ynodes - 1);

    for (x = xstart; x < xend + xinc/2.0; x += xinc) {
	float		phi;

	phi = x * 3.1415927f;
	for (y = ystart; y < yend + yinc/2.0f; y += yinc) {
	    float	theta;

	    theta = y * 3.1415927f / 2.0f;

	    pl->x = (float)cos (theta) * (float)cos (phi);
	    pl->y = (float)sin (theta);
	    pl->z = (float)cos (theta) * (float)sin (phi);

	    uvl->u = x * 3;
	    uvl->v = y * 3;
	    uvl->w = 0.0f;

	    pl++;
	    uvl++;
	}
    }
}

void construct_mesh (
    char	*segment,
    int		x_count,
    int		y_count) {
    Vertex	*points;
    Parameter	*parameters;
    int		v_count;
    HC_KEY	mesh_key;

    HC_Open_Segment (segment);
	v_count = x_count * y_count;
	points = (Vertex *)malloc (v_count * sizeof (Vertex));
	parameters = (Parameter *)malloc (v_count * sizeof (Parameter));

	compute_mesh_data (-1.0f, 1.0f, x_count,
			   -1.0f, 1.0f, y_count,
			   points, parameters);

	mesh_key = HC_KInsert_Mesh (x_count, y_count, points);
	{
	    float	*findices, *fiptr;
	    Vertex	*vptr = &points[0];
	    int		row, col;
	    int		fcyc;
	    int		ccount;

	    /* put in a rainbow map */
	    HC_Set_Color_By_Index ("faces, edges, markers", BLUE);
	    HC_Set_Marker_Symbol ("@");
	    HC_Set_Marker_Size (0.33);
	    ccount = 3;

	    /* compute and set FIndices */
	    findices = (float *)malloc (v_count * sizeof (float));

	    fcyc = 1;
	    row = 0;
	    fiptr = findices;
	    do {
		col = 0;
		do {
		    *fiptr++= (vptr->y + 1.0f) * 1.5f;
		    vptr++;
		} while (++col < y_count);
	    } while (++row < x_count);

	    HC_MSet_Vertex_Colors_By_FIndex (mesh_key,
					     "faces, edges, markers",
					     0, v_count, findices);
	    HC_MSet_Vertex_Parameters (mesh_key, 0, v_count,
				       3, (float *)parameters);
	    free (findices);
	}
	free (points);
	free (parameters);
    HC_Close_Segment ();
}

void setup_window_structure () {

    int	x_count,y_count;

    char	info[256];
    float	y, size;

	x_count = y_count = 20;

    HC_Open_Segment ("?style library/danger");
	HC_Set_Color_By_Index ("window contrast", RED);
    HC_Close_Segment ();

    HC_Open_Segment ("?style library/toggle");
	HC_Set_Color_By_Index ("window contrast", BLUE);
    HC_Close_Segment ();

    HC_Open_Segment ("?style library/special");
	HC_Set_Color_By_Index ("window contrast", GREEN);
    HC_Close_Segment ();

    HC_Open_Segment ("?my_picture");
	HC_Set_Color_Map ("black, red, green, blue, white");
	HC_Define_System_Options ("obsolete checking, no bounding volumes");
	HC_Set_Driver_Options ("no double-buffering");
	HC_Set_Driver_Options ("no force black-and-white");
	if (b_image_out) {
		HC_Set_Driver_Options ("subscreen = (-1.0, 1.0, -1.0, 1.0)");
	}
	HC_Set_Heuristics ("related selection limit = 0");

	HC_Set_Camera_Projection ("stretched");
	HC_Set_Text_Font ("size = 0.01 sru");
	HC_Set_Color_By_Index ("windows", WHITE);
	HC_Set_Color_By_Index ("text", BLACK);

	HC_Set_Selectability ("off");
	HC_Update_Display ();

	HC_Open_Segment ("title");
	    HC_Set_Text_Font ("size = 0.04 sru");
	    HC_Set_Window (-1.0, 1.0, 0.9, 1.0);
	    HC_Set_Heuristics ("no hidden surfaces");
	    HC_Insert_Text (0.0, 0.0, 0.0, "Rendering Test");
	    HC_Open_Segment ("");
		HC_Set_Text_Font ("size = 0.01 sru");
		HC_Set_Text_Alignment ("<");
		HC_Insert_Text (-1.0, 0.0, 0.0, "Tech Soft Graphics Development");
	    HC_Close_Segment ();
	    HC_Open_Segment ("");
		HC_Set_Text_Font ("size = 0.01 sru");
		HC_Set_Text_Alignment (">");
		HC_Insert_Text (1.0, 0.0, 0.0, "$Revision: 1.36 $");
	    HC_Close_Segment ();
	HC_Close_Segment ();
	HC_Open_Segment ("draw");
	    HC_Set_Window (-1.0, 0.8, -0.9, 0.9);
	    HC_Set_Selectability ("windows = on");
	    HC_Set_Camera_Projection ("perspective");
	    HC_Set_Heuristics ("polygon handedness = right");
	HC_Close_Segment ();
	HC_Open_Segment ("buttons");
	    HC_Set_Window (0.8, 1.0, -0.9, 0.9);
	    HC_Set_Window_Frame ("off");
	    HC_Set_Heuristics ("no clipping, no hidden surfaces");
	    HC_Set_Selectability ("windows = on");
#define NUM_BUTTONS	25	/* legend counts as 2 */
	    size = (1.0f - (-1.0f)) / (float)NUM_BUTTONS;
	    y = 1.0f;
	    HC_Open_Segment ("atmospheric attenuation");
		HC_Set_Window (-1.0, 1.0, (double)(y - size), (double)y);
		y -= size;
		HC_Insert_Text (0.0,  0.4, 0.0, "atmospheric");
		HC_Insert_Text (0.0, -0.4, 0.0, "attenuation");
	    HC_Close_Segment ();
	    HC_Open_Segment ("attribute lock");
		HC_Set_Window (-1.0, 1.0, (double)(y - size), (double)y);
		y -= size;
		HC_Insert_Text (0.0,  0.4, 0.0, "attribute");
		HC_Insert_Text (0.0, -0.4, 0.0, "lock");
	    HC_Close_Segment ();
	    HC_Open_Segment ("color interpolation");
		HC_Set_Window (-1.0, 1.0, (double)(y - size), (double)y);
		y -= size;
		HC_Insert_Text (0.0,  0.4, 0.0, "color");
		HC_Insert_Text (0.0, -0.4, 0.0, "interpolation");
	    HC_Close_Segment ();
	    HC_Open_Segment ("color index interpolation");
		HC_Set_Window (-1.0, 1.0, (double)(y - size), (double)y);
		y -= size;
		HC_Insert_Text (0.0,  0.4, 0.0, "color index");
		HC_Insert_Text (0.0, -0.4, 0.0, "interpolation");
	    HC_Close_Segment ();
	    HC_Open_Segment ("face displacement");
		HC_Set_Window (-1.0, 1.0, (double)(y - size), (double)y);
		y -= size;
		HC_Insert_Text (0.0,  0.4, 0.0, "face");
		HC_Insert_Text (0.0, -0.4, 0.0, "displacement");
	    HC_Close_Segment ();
	    HC_Open_Segment ("hsr algorithm");
		HC_Set_Window (-1.0, 1.0, (double)(y - size), (double)y);
		y -= size;
		HC_Insert_Text (0.0,  0.4, 0.0, "hsr");
		HC_Insert_Text (0.0, -0.4, 0.0, "algorithm");
	    HC_Close_Segment ();
	    HC_Open_Segment ("lighting interpolation 1");
		HC_Set_Window (-1.0, 1.0, (double)(y - size), (double)y);
		y -= size;
		HC_Insert_Text (0.0,  0.4, 0.0, "lighting");
		HC_Insert_Text (0.0, -0.4, 0.0, "interpolation 1");
	    HC_Close_Segment ();
	    HC_Open_Segment ("lighting interpolation 2");
		HC_Set_Window (-1.0, 1.0, (double)(y - size), (double)y);
		y -= size;
		HC_Insert_Text (0.0,  0.4, 0.0, "lighting");
		HC_Insert_Text (0.0, -0.4, 0.0, "interpolation 2");
	    HC_Close_Segment ();
	    HC_Open_Segment ("local viewer");
		HC_Set_Window (-1.0, 1.0, (double)(y - size), (double)y);
		y -= size;
		HC_Insert_Text (0.0,  0.4, 0.0, "local");
		HC_Insert_Text (0.0, -0.4, 0.0, "viewer");
	    HC_Close_Segment ();
	    HC_Open_Segment ("perspective correction");
		HC_Set_Window (-1.0, 1.0, (double)(y - size), (double)y);
		y -= size;
		HC_Insert_Text (0.0,  0.4, 0.0, "perspective");
		HC_Insert_Text (0.0, -0.4, 0.0, "correction");
	    HC_Close_Segment ();
	    HC_Open_Segment ("quantization");
		HC_Set_Window (-1.0, 1.0, (double)(y - size), (double)y);
		y -= size;
		HC_Insert_Text (0.0, 0.0, 0.0, "quantization");
		HC_Show_Device_Info ("?my_picture", "max colors", info);
		if (!strcmp (info, "16777216") != 0)
		    HC_Set_Window_Pattern ("//");
	    HC_Close_Segment ();
	    HC_Open_Segment ("software fb options");
		HC_Set_Window (-1.0, 1.0, (double)(y - size), (double)y);
		y -= size;
		HC_Insert_Text (0.0,  0.4, 0.0, "sw fb");
		HC_Insert_Text (0.0, -0.4, 0.0, "options");
	    HC_Close_Segment ();
	    HC_Open_Segment ("technology");
		HC_Set_Window (-1.0, 1.0, (double)(y - size), (double)y);
		y -= size;
		HC_Insert_Text (0.0, 0.0, 0.0, "technology");
	    HC_Close_Segment ();
	    HC_Open_Segment ("texture interpolation");
		HC_Set_Window (-1.0, 1.0, (double)(y - size), (double)y);
		y -= size;
		HC_Insert_Text (0.0,  0.4, 0.0, "texture");
		HC_Insert_Text (0.0, -0.4, 0.0, "interpolation");
	    HC_Close_Segment ();
	    HC_Open_Segment ("quit");
		HC_Set_Window (-1.0, 1.0, (double)(y - size), (double)y);
		y -= size;
		HC_Style_Segment ("?style library/danger");
		HC_Insert_Text (0.0, 0.0, 0.0, "QUIT");
	    HC_Close_Segment ();

	    HC_Open_Segment ("legend");
		HC_Set_Window (-1.0, 1.0, (double)(y - (size * 2)), (double)y);
		HC_Set_Selectability ("windows = off");
		y -= (size * 2);
		HC_Set_Text_Font ("size = 0.01 sru");
		HC_Open_Segment ("");
		    HC_Set_Text_Alignment ("<");
		    HC_Insert_Text (-0.9, 0.7, 0.0, "HOOPS:");
		    HC_Insert_Text (-0.9, 0.2, 0.0, "A.I.R.:");
		    HC_Insert_Text (-0.9, -0.2, 0.0, "I.M.:");
		    HC_Insert_Text (-0.9, -0.7, 0.0, "Kanji:");
		HC_Close_Segment ();
		HC_Open_Segment ("");
		    HC_Set_Text_Alignment (">");
		    HC_Show_System_Info ("hoops version", info);
		    HC_Insert_Text (0.9, 0.7, 0.0, info);
		    HC_Show_System_Info ("a.i.r. version", info);
		    if (strcmp (info, "not available") != 0)
			HC_Insert_Text (0.9, 0.2, 0.0, info);
		    else
			HC_Insert_Text (0.9, 0.2, 0.0, "N/A");
		    HC_Show_System_Info ("i.m. version", info);
		    if (strcmp (info, "not available") != 0)
			HC_Insert_Text (0.9, -0.2, 0.0, info);
		    else
			HC_Insert_Text (0.9, -0.2, 0.0, "N/A");
		    HC_Show_System_Info ("kanji present", info);
		    HC_Insert_Text (0.9, -0.7, 0.0, info);
		HC_Close_Segment ();
	    HC_Close_Segment ();

	    HC_Open_Segment ("reset");
		HC_Set_Window (-1.0, 1.0, (double)(y - size), (double)y);
		y -= size;
		HC_Style_Segment ("?style library/danger");
		HC_Insert_Text (0.0, 0.0, 0.0, "RESET");
	    HC_Close_Segment ();
	    HC_Open_Segment ("color consolidation");
		HC_Set_Window (-1.0, 1.0, (double)(y - size), (double)y);
		y -= size;
		HC_Style_Segment ("?style library/toggle");
		HC_Set_Window_Pattern ("//");
		HC_Insert_Text (0.0,  0.4, 0.0, "color");
		HC_Insert_Text (0.0, -0.4, 0.0, "consolidation");
	    HC_Close_Segment ();
	    HC_Open_Segment ("fixed colors");
		HC_Set_Window (-1.0, 1.0, (double)(y - size), (double)y);
		y -= size;
		HC_Style_Segment ("?style library/toggle");
		HC_Set_Window_Pattern ("//");
		HC_Insert_Text (0.0,  0.4, 0.0, "fixed");
		HC_Insert_Text (0.0, -0.4, 0.0, "colors");
	    HC_Close_Segment ();
	    HC_Open_Segment ("gamma correction");
		HC_Set_Window (-1.0, 1.0, (double)(y - size), (double)y);
		y -= size;
		HC_Style_Segment ("?style library/toggle");
		HC_Insert_Text (0.0,  0.4, 0.0, "gamma");
		HC_Insert_Text (0.0, -0.4, 0.0, "correction");
	    HC_Close_Segment ();
	    HC_Open_Segment ("light scaling");
		HC_Set_Window (-1.0, 1.0, (double)(y - size), (double)y);
		y -= size;
		HC_Style_Segment ("?style library/toggle");
		HC_Set_Window_Pattern ("//");
		HC_Insert_Text (0.0,  0.4, 0.0, "light");
		HC_Insert_Text (0.0, -0.4, 0.0, "scaling");
	    HC_Close_Segment ();
	    HC_Open_Segment ("number of colors");
		HC_Set_Window (-1.0, 1.0, (double)(y - size), (double)y);
		y -= size;
		HC_Style_Segment ("?style library/toggle");
		HC_Set_Window_Pattern ("//");
		HC_Insert_Text (0.0,  0.4, 0.0, "number of");
		HC_Insert_Text (0.0, -0.4, 0.0, "colors");
	    HC_Close_Segment ();
	    HC_Open_Segment ("update interrupts");
		HC_Set_Window (-1.0, 1.0, (double)(y - size), (double)y);
		y -= size;
		HC_Style_Segment ("?style library/toggle");
		HC_Insert_Text (0.0,  0.4, 0.0, "update");
		HC_Insert_Text (0.0, -0.4, 0.0, "interrupts");
	    HC_Close_Segment ();
	    HC_Open_Segment ("graph");
		HC_Set_Window (-1.0, 1.0, (double)(y - size), (double)y);
		y -= size;
		HC_Style_Segment ("?style library/special");
		HC_Insert_Text (0.0, 0.0, 0.0, "graph");
	    HC_Close_Segment ();
	    HC_QSet_Window_Frame ("*", "on");
	    HC_QUnSet_Window_Frame ("legend");
	HC_Close_Segment ();
	HC_Open_Segment ("memory");
	    HC_Set_Window (-1.0, -0.8, -1.0, -0.9);
	    HC_Set_Heuristics ("no clipping, no hidden surfaces");
	HC_Close_Segment ();
	HC_Open_Segment ("results");
	    HC_Set_Window (-0.8, 0.8, -1.0, -0.9);
	    HC_Set_Heuristics ("no hidden surfaces");
	    HC_Set_Text_Font ("size = 0.02 sru");
	HC_Close_Segment ();
	HC_Open_Segment ("time");
	    HC_Set_Window (0.8, 1.0, -1.0, -0.9);
	    HC_Set_Heuristics ("no clipping, no hidden surfaces");
	HC_Close_Segment ();
    HC_Close_Segment ();

    HC_Define_Alias ("?title",   "?my_picture/title");
    HC_Define_Alias ("?draw",    "?my_picture/draw");
    HC_Define_Alias ("?buttons", "?my_picture/buttons");
    HC_Define_Alias ("?memory",  "?my_picture/memory");
    HC_Define_Alias ("?results", "?my_picture/results");
    HC_Define_Alias ("?time",    "?my_picture/time");

	/* have to do this because internally ?keyboard is */
	/* set to ?picture -- go figure */
	HC_UnDefine_Alias ("?keyboard");
    HC_Define_Alias ("?keyboard", "?my_picture");

    HC_Open_Segment ("?include library/sphere");
	construct_mesh ("?include library/sphere", x_count, y_count);
	HC_Scale_Object (0.8, 0.8, 0.8);
    HC_Close_Segment ();
    HC_Define_Alias ("?sphere", "?include library/sphere");

    HC_Open_Segment ("?include library/ellipsoid");
	construct_mesh ("?include library/ellipsoid", x_count, y_count);
	HC_Scale_Object (0.8, 0.8, 3.0);
	HC_Rotate_Object (-15.0, 10.0, 0.0);
	HC_Translate_Object (0.1, 0.25, 2.0);
    HC_Close_Segment ();
    HC_Define_Alias ("?ellipsoid", "?include library/ellipsoid");

    HC_Open_Segment ("?include library/image");
    {
	unsigned char	pixels[100][100];
	int	i, j;


	for (i = 0; i < 100; ++i)
	    for (j = 0; j < 100; ++j)
		pixels[j][i] = GREEN;
	for (i = 0; i < 100; ++i) {
	    for (j = 0; j < 5; ++j)
		pixels[j][i] = RED;
	    for (j = 10; j < 15; ++j)
		pixels[j][i] = RED;
	    for (j = 20; j < 25; ++j)
		pixels[j][i] = RED;
	    for (j = 30; j < 35; ++j)
		pixels[j][i] = RED;
	    for (j = 40; j < 45; ++j)
		pixels[j][i] = RED;
	    for (j = 50; j < 55; ++j)
		pixels[j][i] = RED;
	    for (j = 60; j < 65; ++j)
		pixels[j][i] = RED;
	    for (j = 70; j < 75; ++j)
		pixels[j][i] = RED;
	    for (j = 80; j < 85; ++j)
		pixels[j][i] = RED;
	    for (j = 90; j < 95; ++j)
		pixels[j][i] = RED;
	}
	for (i = 10; i < 45; ++i) {
	    for (j = 10; j < 45; ++j) {
		pixels[j][i] = RED;
		pixels[j][99 - i] = GREEN;
		pixels[99 - j][i] = BLUE;
		pixels[99 - j][99 - i] = RED;
	    }
	}
	HC_Insert_Image (0.0, 0.0, 0.0,
			 "mapped 8, name = squares and stripes",
			 100, 100, (void *)pixels);
	HC_Define_Texture ("nice image",
			   "tiling, source = squares and stripes");
    }
    HC_Close_Segment ();
    HC_Define_Alias ("?image", "?include library/image");

    HC_Open_Segment ("?include library/tilted floor");
    {
	Vertex	points[4];

	HC_Set_Color_By_Index ("faces", GREEN);
	points[0].x = -1.0f; points[0].y = -0.5f; points[0].z = -1.0f;
	points[1].x = -1.0f; points[1].y =  0.5f; points[1].z =  1.0f;
	points[2].x =  1.0f; points[2].y = -0.5f; points[2].z = -1.0f;
	points[3].x =  1.0f; points[3].y =  0.5f; points[3].z =  1.0f;
	HC_Insert_Mesh (2, 2, points);
    }
    HC_Close_Segment ();
    HC_Define_Alias ("?floor", "?include library/tilted floor");

    HC_Open_Segment ("?include library/wall");
    {
	Vertex	points[4];

	HC_Set_Color_By_Index ("faces", BLUE);
	points[0].x = -1.0f; points[0].y = -1.0f; points[0].z = 0.0f;
	points[1].x = -1.0f; points[1].y =  1.0f; points[1].z = 0.0f;
	points[2].x =  1.0f; points[2].y = -1.0f; points[2].z = 0.0f;
	points[3].x =  1.0f; points[3].y =  1.0f; points[3].z = 0.0f;
	HC_Insert_Mesh (2, 2, points);
    }
    HC_Close_Segment ();
    HC_Define_Alias ("?wall", "?include library/wall");
}

void identify_test (
    char	*segment) {

    HC_QUnSet_Color ("?buttons/*");
    HC_QSet_Color_By_Index (segment, "windows", RED);
    HC_QSet_Color_By_Index (segment, "text", WHITE);
    HC_Flush_Contents ("?draw", "geometry");

    HC_QUnSet_Window_Frame ("?draw");
    HC_Delete_Segment ("?draw/*");

    HC_Flush_Contents ("?memory", "geometry");
    HC_Flush_Contents ("?results", "geometry");
    HC_Flush_Contents ("?time", "geometry");
    HC_Relinquish_Memory ();
    HC_Update_Display ();
}

void post_memory (
    int		index) {
    long	allocated,
		in_use;
    char	string[256];

    HC_Show_Memory_Usage (&allocated, &in_use);

    results2[index].y = (float)allocated / 1024.0f;
    if (results2[index].y > results2_max)
	results2_max = results2[index].y;
    results3[index].y = (float)in_use / 1024.0f;

    HC_Open_Segment ("?memory");
	HC_Flush_Contents (".", "geometry");
	sprintf (string,
		 "%0.1f/%0.1f K",
		 (float)allocated / 1024.0f,
		 (float)in_use / 1024.0f);
	HC_Insert_Text (0.0, 0.0, 0.0, string);
    HC_Close_Segment ();
}

void post_time (
    int		index,
    float	start_time,
    float	stop_time) {
    char	string[256];

    results[index].y = stop_time - start_time;
    if (results[index].y > results_max)
	results_max = results[index].y;

    HC_Open_Segment ("?time");
	HC_Flush_Contents (".", "geometry");
	sprintf (string,
		 "%0.2f secs",
		 stop_time - start_time);
	HC_Insert_Text (0.0, 0.0, 0.0, string);
    HC_Close_Segment ();
}

void post_results (
    char	*message) {

   /*
    * redundant flush in case update interrupts prevents the
    * one in identify_test from occurring
    */
    HC_Open_Segment ("?results");
	HC_Flush_Contents (".", "geometry");
	HC_Insert_Text (0.0, 0.25, 0.0, message);
    HC_Close_Segment ();
}

const char* extra_pointer_format(void)
{
	char buffer[1024];

	sprintf (buffer, "%p", (void*) buffer);
	if (buffer[0] == '0' && buffer[1] == 'x')
		return "";
	else 
		return "0x";

}


int raw_write (HC_KEY image_key, int width, int height, int binary)
{
	int row=0,col=0;
	char temp[256];
	char *rawfile;

	FILE *fp;

	Pixel *image_row;
	Pixel *pixel;

	image_row = (Pixel *) malloc (width * sizeof(Pixel));
	rawfile = (char *) malloc (strlen(unixtime)+strlen("_")+strlen(image_file_name)+strlen(".raw")+1);

    if (binary){

			sprintf (rawfile, "%s-%s.rwb", unixtime, image_file_name);
            /* binary header info */
            fp = fopen (rawfile, "wb");

            fwrite (&width, sizeof(int), 1, fp);
            fwrite (&height, sizeof(int), 1, fp);
            /* binary image info */
            for (row = 0; row < height; ++row) {
                    HC_Show_Partial_Image (image_key, 0, row, width, 1, image_row);
                    pixel = image_row;
                    for (col = 0; col < width; ++col) {
                            fwrite (pixel, sizeof(Pixel), 1, fp);
                            ++pixel;
                    }
            }
            fclose (fp);
			free(rawfile);
			free(image_row);
            return 1;
    }

	sprintf (rawfile, "%s-%s.raw", unixtime, image_file_name);
    /* ascii header info */
    fp = fopen (rawfile, "wt");
    sprintf (temp, "%d %d\n", width, height);
    fputs (temp, fp);

    /* ascii image info */
    for (row = 0; row < height; ++row) {
            HC_Show_Partial_Image (image_key, 0, row, width, 1, image_row);
            pixel = image_row;
            for (col = 0; col < width; ++col) {
                    sprintf (temp, "%d ", pixel->r);
                    fputs (temp, fp);
                    sprintf (temp, "%d ", pixel->g);
                    fputs (temp, fp);
                    sprintf (temp, "%d\n", pixel->b);
                    fputs (temp, fp);
                    ++pixel;
            }
    }
	fclose (fp);

	free(rawfile);
	free(image_row);
	return 1;

} /* raw_write */


void my_ogl_finish_picture(
	HIC_Rendition const * nr,
	bool swap_buffers)
{

	char	format[80];
    int		i=0, j=0, width, height, success;

	Pixel	*data, *flip, *pixel;
	HC_KEY	key;

	/* use IM's opinion even though it lies about width */
	width = HIC_Show_Device_Pixels_X(nr);
	height = HIC_Show_Device_Pixels_Y(nr);
	/* this fudge factor must be explainable */
	width += 9;

	/* hard wire the image size causes clipping*/
	/*
	width = 1280;
	height = 960;
	*/

	/* create a place to store the image and zero the block */
	data = (Pixel *) malloc (width * height * sizeof(Pixel)); 
	pixel = data;
	j = width * height;

	for (i = 0; i < j; i++){
		pixel->r = 0;
		pixel->g = 0;
		pixel->b = 0;
		++pixel;	
	}

    HIC_Finish_Picture( nr, swap_buffers );

#ifndef USE_NO_GL
	glReadBuffer(GL_FRONT);
	glReadPixels( 
		0, 0,
		width, height,
		GL_RGB,
		GL_UNSIGNED_BYTE,
		data);
#endif

	/* ogl and HOOPS data order is flipped */
	flip = (Pixel *) malloc (width * height * sizeof(Pixel)); 
	for (i = 0; i < height; i++) {
		for (j=0; j < width; j++) {

			flip[(i*width) + j].r = data[((height - 1 - i)*width)+j].r;
			flip[(i*width) + j].g = data[((height - 1 - i)*width)+j].g;
			flip[(i*width) + j].b = data[((height - 1 - i)*width)+j].b;
		}
	}


	/* create a HOOPS image from the frame buffer data */
	HC_Open_Segment ("/export");
		sprintf (format, "RGB,name=%s", image_file_name);
		key = HC_KInsert_Image (0.0, 0.0, 0.0, format, width, height, flip);
	HC_Close_Segment ();

	
	/* write binary or ascii file */
	success = raw_write (key, width, height, image_file_format);

	HC_Flush_Contents ("/export", "everything");
	HC_Delete_Segment ("/export");
 
	free(flip);
	free(data);
}

void export_image(char *name) {

	char	format[80], option[80];
    int		i=0, j=0, width, height, success;

	HC_KEY	key;
	Pixel	*data, *pixel;
	Vertex	wul,wlr;

	if (image_source == OGL_HW) {

		sprintf (image_file_name, "%s-opengl", name);

		HC_Open_Segment ("?driver/opengl/temp_window");
			HC_Set_Color_Map ("black, red, green, blue, white");
			HC_Set_Camera_Projection ("stretched");
			HC_Set_Text_Font ("size = 0.01 sru");
			HC_Set_Callback ("finish picture = my ogl finish picture");
			HC_QUnSet_Window("?draw");
			HC_Include_Segment ("?draw");
		HC_Close_Segment();
		HC_Update_Display();

		HC_QSet_Window ("?draw",-1.0, 0.8, -0.9, 0.9);
   
		HC_Delete_Segment ("?driver/opengl/temp_window");

		return;
	}

	sprintf (image_file_name, "%s-image", name);

	
	/* determine size of the image */
	/* draw window is (-1.0, 0.8, -0.9, 0.9) */
	wul.x  = -1.0f;
	wul.y  =  0.8f;
	wul.z  =  0.0f;

	wlr.x =  0.9f;
	wlr.y = -0.9f;
	wlr.z =  0.0f;

	/* for now, we'll hard wire the image size instead of using the stuff below */
	width = 1024;
	height = 768;

/*
	if (HC_Compute_Coordinates ("?my_picture", "outer window", &wul,"local pixels",&pul) &&
		HC_Compute_Coordinates ("?my_picture", "outer window", &wlr,"local pixels",&plr)) {

		width = (int)((plr.x - pul.x));
		height = (int)((plr.y - pul.y));
	}
	else {
		width = (int)(1280.0f / 3.0f);
		height = (int)(1024.0f / 3.0f);
	}

*/


	/* create a place to store the image and zero the block */
	data = (Pixel *) malloc (width * height * sizeof(Pixel)); 
	pixel = data;
	j = width * height;

	for (i = 0; i < j; i++){
		pixel->r = 0;
		pixel->g = 0;
		pixel->b = 0;
		++pixel;	
	}

	/* create the image */
	HC_Open_Segment ("/export");
		sprintf (format, "RGB,name=%s", name);
		key = HC_KInsert_Image (0.0, 0.0, 0.0, format, width, height, data);
	HC_Close_Segment ();

	/* capture the main window into the image */
	HC_Open_Segment ("?driver/image/export");

		sprintf (option, "use window id = %s%p", EXTRA_POINTER_FORMAT, (void*)(HC_KEY)key);
		HC_Set_Driver_Options (option);
		/* HC_Set_Visibility("text=off"); */
		/* have to recreate some ?my_picture settings */
		HC_Set_Color_Map ("black, red, green, blue, white");
		HC_Set_Camera_Projection ("stretched");
		HC_Set_Text_Font ("size = 0.01 sru");

		/* unset window before include or there will be two on the draw segment */
		HC_QUnSet_Window("?draw");
    	HC_Include_Segment ("?draw");
	HC_Close_Segment ();
	
	/* this temporarily stomps other windows with the draw window*/
	HC_Update_Display ();
	
	HC_QSet_Window ("?draw",-1.0, 0.8, -0.9, 0.9);
	
	/* write binary or ascii file */
	success = raw_write (key, width, height, image_file_format);

	HC_Flush_Contents ("/export", "everything");
	HC_Flush_Contents ("?driver/image/export", "everything");
	HC_Delete_Segment ("/export");
	HC_Delete_Segment ("?driver/image/export");

	free(data);

} /* export_image */

void init (void) {
    
	int     i;
	char    expansion[1024];
	time_t  tp;

	time (&tp);
	sprintf (unixtime, "%ld", tp);

    HC_Show_Pathname_Expansion ("?picture", expansion);
    HC_Delete_Segment("?picture");
    HC_UnDefine_Alias("?picture");

    switch (driver_type) {

	case OGL: {
	    #ifdef WINDOWS_SYSTEM
		    HC_Define_Alias ("?my_picture", "?driver/opengl/window0");
		    HC_Create_Segment ("?my_picture");
	    #endif
	    #ifdef UNIX_SYSTEM
		    HC_Define_Alias ("?my_picture", "?driver/opengl/:0.0");
		    HC_Create_Segment ("?my_picture");
	    #endif

	    HC_Open_Segment("?my_picture");
		HC_Set_Rendering_Options("hsra=hzb");
		HC_Set_Driver_Options ("double-buffering");
	    HC_Close_Segment();

	}   break;

	case MSW: {
	    HC_Define_Alias ("?my_picture", "?driver/msw/window0");

	    HC_Open_Segment("?my_picture");
		HC_Set_Rendering_Options("hsra=szb");
		HC_Set_Driver_Options ("no double-buffering");
	    HC_Close_Segment();
	}   break;

	case X11: {
	    HC_Define_Alias ("?my_picture", "?driver/x11/:0.0");
	    HC_Open_Segment("?my_picture");
		HC_Set_Rendering_Options("hsra=szb");
		HC_Set_Driver_Options ("no double-buffering");
	    HC_Close_Segment();
	}	break;
	
	case DEFAULT_DRIVER: {
	    HC_Define_Alias ("?my_picture", expansion);
	    HC_Create_Segment ("?my_picture");
	}

    }

    /* timing results */
    for (i = 0; i < (NUM_RESULTS + 2); i++) {
	results[i].x = (float)i;
	results[i].y = 0.0f;
	results[i].z = 0.0f;
    }
    results[0].x = results[1].x;
    results[NUM_RESULTS + 1].x = results[NUM_RESULTS].x;
    /* fudged so the polygon has at least some height */
    results[0].y = results[NUM_RESULTS + 1].y = -0.001f;
    results_max = -1.0f;

    /* allocated and in use memory results */
    for (i = 0; i < (NUM_RESULTS + 2); i++) {
	results2[i].x = results3[i].x = results[i].x;
	results2[i].y = results3[i].y = results[i].y;
	results2[i].z = results3[i].z = 0.0f;
    }
    results2_max = -1.0f;

	HC_Define_Callback_Name ("my ogl finish picture", my_ogl_finish_picture);
	
	setup_window_structure ();
}

void show_execution_context (void) {
    float	start_time,
		stop_time,
		y,
		ydelta;
    int		i;


    HC_Show_Time (&start_time);
    HC_Open_Segment ("?draw/execution info");
	HC_Set_Camera_Projection ("stretched");
	HC_Set_Text_Font ("size = 0.02 sru");
	HC_Open_Segment ("left");
	    HC_Set_Color_By_Index ("text", BLACK);
	    HC_Set_Text_Alignment ("<");
	HC_Close_Segment ();
	HC_Open_Segment ("right");
	    HC_Set_Color_By_Index ("text", RED);
	    HC_Set_Text_Alignment (">");
	HC_Close_Segment ();
	HC_Open_Segment ("titles");
	    HC_Set_Color_By_Index ("text", BLUE);
	HC_Close_Segment ();
	HC_Open_Segment ("center");
	    HC_Set_Color_By_Index ("text", BLACK);
	    HC_Set_Text_Font ("size = 0.01 sru");
	HC_Close_Segment ();
	HC_Open_Segment ("center red");
	    HC_Set_Color_By_Index ("text", RED);
	    HC_Set_Text_Font ("size = 0.01 sru");
	HC_Close_Segment ();

	ydelta = 1.9f / (float)((NUM_CHOICES / 2) + NUM_VARIABLES + 3);
	y = 0.95f;

	HC_QInsert_Text ("titles", 0.0, (double)y, 0.0, "Device Info");
	y -= ydelta;
	for (i = 0; i < NUM_CHOICES; i++) {
	    char descriptor[256];
	    char answer[256];

	    sprintf (descriptor, "%s :", choices[i]);
	    HC_Show_Device_Info ("?my_picture", choices[i], answer);
	    if (strlen (answer) == 0)
		sprintf (answer, "%s", "<none>");

	    if (i % 2 == 0) {
		HC_QInsert_Text ("left",  -0.9, (double)y, 0.0, descriptor);
		HC_QInsert_Text ("right", -0.2, (double)y, 0.0, answer);
	    }
	    else {
		HC_QInsert_Text ("left",  0.2, (double)y, 0.0, descriptor);
		HC_QInsert_Text ("right", 0.9, (double)y, 0.0, answer);
		y -= ydelta;
	    }
	}

	y -= (ydelta * 2);
	HC_QInsert_Text ("titles", 0.0, (double)y, 0.0, "Environment Variables");
	y -= ydelta;
	for (i = 0; i < NUM_VARIABLES; i++) {
	    char out[300];
	    char buf[256];

	    if (HC_Show_Environment (variables[i], buf)) {
		sprintf (out,
			 "%s : %s",
			 variables[i],
			 buf);
		HC_QInsert_Text ("center red", 0.0, (double)y, 0.0, out);
	    }
	    else {
		sprintf (out,
			 "%s : <undefined>",
			 variables[i]);
		HC_QInsert_Text ("center", 0.0, (double)y, 0.0, out);
	    }
	    y -= ydelta;
	}
    HC_Close_Segment ();
    HC_Update_Display ();
    HC_Show_Time (&stop_time);

    post_memory (1);
    post_results ("Environment variables may be overridden by program statements");
    post_time (1, start_time, stop_time);

    
}

void test_atmospheric_attenuation (void) {
    float	start_time,
		stop_time;
    char	*option;
    float	cd; /* camera distance */

    identify_test ("?buttons/atmospheric attenuation");
    HC_Update_Display ();

    HC_Show_Time (&start_time);
    HC_Open_Segment ("?draw/aa");
	HC_Set_Color_By_Index ("lines", RED);
    HC_Close_Segment ();

    cd = 5.0f;
    HC_Open_Segment ("?draw/aa/one");
	option = "no atmospheric attenuation";
	HC_Insert_Text (0.0, 0.9, 0.0, option);
	HC_Set_Rendering_Options (option);
	HC_Set_Window (-0.9, -0.1, 0.1, 0.9);
	HC_Open_Segment ("object");
	    HC_Include_Segment ("?ellipsoid");
	    HC_Set_Marker_Symbol (".");
	    HC_Set_Rendering_Options ("attribute lock = marker symbol");
	HC_Close_Segment ();
	HC_Insert_Distant_Light (-1.0, 1.5, -2.0);
	HC_Insert_Line (-10.0, -0.3, 4.0 - cd, 10.0, -0.3, 4.0 - cd);
	HC_Insert_Line (-10.0,  0.3, 8.0 - cd, 10.0,  0.3, 8.0 - cd);
	HC_Insert_Text (0.0, -0.9, 0.0, "looks perfect");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/aa/two");
	option = "atmospheric attenuation = (hither = 4.0, yon = 8.0)";
	HC_Set_Window (-0.9, -0.1, -0.9, -0.1);
	HC_Set_Rendering_Options (option);
	HC_Include_Segment ("../one/object");
	HC_Insert_Distant_Light (-1.0, 1.5, -2.0);
	HC_Open_Segment ("");
	    HC_Set_Rendering_Options ("no atmospheric attenuation");
	    HC_Insert_Text (0.0, 0.9, 0.0, option);
	    HC_Insert_Line (-10.0, -0.3, 4.0 - cd, 10.0, -0.3, 4.0 - cd);
	    HC_Insert_Line (-10.0,  0.3, 8.0 - cd, 10.0,  0.3, 8.0 - cd);
	HC_Close_Segment ();
	HC_Insert_Text (0.0, -0.9, 0.0, "fades from front tip to very back");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/aa/three");
	option = "atmospheric attenuation = (hither = 2.0, yon = 6.0)";
	HC_Set_Window (0.1, 0.9, 0.1, 0.9);
	HC_Set_Rendering_Options (option);
	HC_Include_Segment ("../one/object");
	HC_Insert_Distant_Light (-1.0, 1.5, -2.0);
	HC_Open_Segment ("");
	    HC_Set_Rendering_Options ("no atmospheric attenuation");
	    HC_Insert_Text (0.0, 0.9, 0.0, option);
	    HC_Insert_Line (-10.0, -0.3, 2.0 - cd, 10.0, -0.3, 2.0 - cd);
	    HC_Insert_Line (-10.0,  0.3, 6.0 - cd, 10.0,  0.3, 6.0 - cd);
	    HC_Insert_Text (0.0, -0.9, 0.0, "all very faded");
	HC_Close_Segment ();
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/aa/four");
	option = "atmospheric attenuation = (hither = 5.0, yon = 7.0)";
	HC_Set_Window (0.1, 0.9, -0.9, -0.1);
	HC_Set_Rendering_Options (option);
	HC_Include_Segment ("../one/object");
	HC_Insert_Distant_Light (-1.0, 1.5, -2.0);
	HC_Open_Segment ("");
	    HC_Set_Rendering_Options ("no atmospheric attenuation");
	    HC_Insert_Text (0.0, 0.9, 0.0, option);
	    HC_Insert_Line (-10.0, -0.3, 5.0 - cd, 10.0, -0.3, 5.0 - cd);
	    HC_Insert_Line (-10.0,  0.3, 7.0 - cd, 10.0,  0.3, 7.0 - cd);
	    HC_Insert_Text (0.0, -0.9, 0.0, "fades from middle to back");
	HC_Close_Segment ();
    HC_Close_Segment ();
    HC_Update_Display ();
    HC_Show_Time (&stop_time);

    post_memory (2);
    post_results ("red lines depict hither / yon positions");
    post_time (2, start_time, stop_time);

    if (b_image_out) {
		sprintf (temp_file_name, "%s-atmospheric_attenuation", image_file_root);
		export_image (temp_file_name);
    }
}

void test_attribute_lock (void) {
    float	start_time,
		stop_time;
    char	*option;

    identify_test ("?buttons/attribute lock");
    HC_Update_Display ();

    HC_Show_Time (&start_time);
    HC_Open_Segment ("?draw/al/one");
	option = "no attribute lock";
	HC_Set_Text_Path (0.0, -1.0, 0.0);
	HC_Insert_Text (-1.1, 0.0, 0.0, option);
	HC_Set_Window (-1.0, -0.33, 0.33, 1.0);
	HC_Set_Color_By_Index ("faces", BLACK);
	HC_Set_Color_By_Index ("edges", BLACK);
	HC_Set_Color_By_Index ("markers", BLACK);
	HC_Set_Visibility ("faces = off, edges = off, markers = off");
	HC_Set_Rendering_Options (option);
	HC_Open_Segment ("sphere");
	    HC_Set_Visibility ("faces = on, edges = on, markers = on, lights = (edges = off)");
	    HC_Set_Rendering_Options ("lighting interpolation = (faces = on, edges = off)");
	    HC_Include_Segment ("?sphere");
	HC_Close_Segment ();
	HC_Insert_Text (1.1, 0.0, 0.0, "all visible");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/al/two");
	option = "attribute lock = visibility";
	HC_Insert_Text (0.0, 0.9, 0.0, option);
	HC_Set_Window (-1.0, -0.33, -0.33, 0.33);
	HC_Set_Color_By_Index ("faces", BLACK);
	HC_Set_Color_By_Index ("edges", BLACK);
	HC_Set_Color_By_Index ("markers", BLACK);
	HC_Set_Visibility ("faces = off, edges = off, markers = off");
	HC_Set_Rendering_Options (option);
	HC_Include_Segment ("?draw/al/one/sphere");
	HC_Insert_Text (0.0, -0.9, 0.0, "nothing visible");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/al/three");
	option = "attribute lock = marker symbol";
	HC_Set_Text_Path (0.0, -1.0, 0.0);
	HC_Insert_Text (-1.1, 0.0, 0.0, "marker symbol");
	HC_Set_Window (-1.0, -0.33, -1.0, -0.33);
	HC_Set_Marker_Symbol ("[]");
	HC_Set_Rendering_Options (option);
	HC_Include_Segment ("?draw/al/one/sphere");
	HC_Insert_Text (1.1, 0.0, 0.0, "square markers");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/al/four");
	option = "attribute lock = (color = faces)";
	HC_Set_Text_Path (0.0, -1.0, 0.0);
	HC_Insert_Text (-1.1, 0.0, 0.0, "face color");
	HC_Set_Window (-0.33, 0.33, 0.33, 1.0);
	HC_Set_Color_By_Index ("faces", BLACK);
	HC_Set_Color_By_Index ("edges", BLACK);
	HC_Set_Color_By_Index ("markers", BLACK);
	HC_Set_Visibility ("faces = off, edges = off, markers = off");
	HC_Set_Rendering_Options (option);
	HC_Include_Segment ("?draw/al/one/sphere");
	HC_Insert_Text (1.1, 0.0, 0.0, "black faces");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/al/five");
	option = "attribute lock = (color = edges)";
	HC_Set_Text_Path (0.0, -1.0, 0.0);
	HC_Insert_Text (-1.1, 0.0, 0.0, "edge color");
	HC_Set_Window (-0.33, 0.33, -0.33, 0.33);
	HC_Set_Color_By_Index ("faces", BLACK);
	HC_Set_Color_By_Index ("edges", BLACK);
	HC_Set_Color_By_Index ("markers", BLACK);
	HC_Set_Visibility ("faces = off, edges = off, markers = off");
	HC_Set_Rendering_Options (option);
	HC_Include_Segment ("?draw/al/one/sphere");
	HC_Insert_Text (1.1, 0.0, 0.0, "black edges");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/al/six");
	option = "attribute lock = (color = markers)";
	HC_Set_Text_Path (0.0, -1.0, 0.0);
	HC_Insert_Text (-1.1, 0.0, 0.0, "marker color");
	HC_Set_Window (-0.33, 0.33, -1.0, -0.33);
	HC_Set_Color_By_Index ("faces", BLACK);
	HC_Set_Color_By_Index ("edges", BLACK);
	HC_Set_Color_By_Index ("markers", BLACK);
	HC_Set_Visibility ("faces = off, edges = off, markers = off");
	HC_Set_Rendering_Options (option);
	HC_Include_Segment ("?draw/al/one/sphere");
	HC_Insert_Text (1.1, 0.0, 0.0, "black markers");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/al/seven");
	option = "attribute lock = (visibility = faces)";
	HC_Set_Text_Path (0.0, -1.0, 0.0);
	HC_Insert_Text (-1.1, 0.0, 0.0, "face visibility");
	HC_Set_Window (0.33, 1.0, 0.33, 1.0);
	HC_Set_Color_By_Index ("faces", BLACK);
	HC_Set_Color_By_Index ("edges", BLACK);
	HC_Set_Color_By_Index ("markers", BLACK);
	HC_Set_Visibility ("faces = off, edges = off, markers = off");
	HC_Set_Rendering_Options (option);
	HC_Include_Segment ("?draw/al/one/sphere");
	HC_Insert_Text (1.1, 0.0, 0.0, "no faces");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/al/eight");
	option = "attribute lock = (visibility = edges)";
	HC_Set_Text_Path (0.0, -1.0, 0.0);
	HC_Insert_Text (-1.1, 0.0, 0.0, "edge visibility");
	HC_Set_Window (0.33, 1.0, -0.33, 0.33);
	HC_Set_Color_By_Index ("faces", BLACK);
	HC_Set_Color_By_Index ("edges", BLACK);
	HC_Set_Color_By_Index ("markers", BLACK);
	HC_Set_Visibility ("faces = off, edges = off, markers = off");
	HC_Set_Rendering_Options (option);
	HC_Include_Segment ("?draw/al/one/sphere");
	HC_Insert_Text (1.1, 0.0, 0.0, "no edges");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/al/nine");
	option = "attribute lock = (visibility = markers)";
	HC_Set_Text_Path (0.0, -1.0, 0.0);
	HC_Insert_Text (-1.1, 0.0, 0.0, "marker visibility");
	HC_Set_Window (0.33, 1.0, -1.0, -0.33);
	HC_Set_Color_By_Index ("faces", BLACK);
	HC_Set_Color_By_Index ("edges", BLACK);
	HC_Set_Color_By_Index ("markers", BLACK);
	HC_Set_Visibility ("faces = off, edges = off, markers = off");
	HC_Set_Rendering_Options (option);
	HC_Include_Segment ("?draw/al/one/sphere");
	HC_Insert_Text (1.1, 0.0, 0.0, "no markers");
    HC_Close_Segment ();
    HC_Update_Display ();
    HC_Show_Time (&stop_time);

    post_memory (3);
    post_results ("attribute locks, one attribute at a time");
    post_time (3, start_time, stop_time);

    if (b_image_out) {
		sprintf (temp_file_name, "%s-attribute_lock", image_file_root);
		export_image (temp_file_name);
    }
}

void test_color_interpolation (void) {
    float	start_time,
		stop_time;
    char	*option;

    identify_test ("?buttons/color interpolation");
    HC_Update_Display ();

    HC_Show_Time (&start_time);
    HC_Open_Segment ("?draw/ci");
	HC_Set_Window_Frame ("off");
	HC_Set_Visibility ("no cutting planes");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/ci/one");
	HC_Set_Visibility ("faces = on, edges = off, markers = off");
	option = "color interpolation = (faces = off)";
	HC_Insert_Text (0.0, 0.9, 0.0, option);
	HC_Set_Window (-1.0, -0.33, 0.33, 1.0);
	HC_Set_Rendering_Options (option);
	HC_Open_Segment ("lit sphere");
	    HC_Set_Visibility ("cutting planes");
	    HC_Insert_Cutting_Plane (0.0, 0.0, 1.0, 0.0);
	    HC_Include_Segment ("?sphere");
	    HC_Insert_Distant_Light (-1.0, 1.5, -2.0);
	HC_Close_Segment ();
	HC_Insert_Text (0.0, -0.9, 0.0, "discretely banded face");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/ci/two");
	HC_Set_Visibility ("faces = on, edges = off, markers = off");
	option = "color interpolation = (faces = on)";
	HC_Insert_Text (0.0, 0.9, 0.0, option);
	HC_Set_Window (-0.33, 0.33, 0.33, 1.0);
	HC_Set_Rendering_Options (option);
	HC_Include_Segment ("?draw/ci/one/lit sphere");
	HC_Insert_Text (0.0, -0.9, 0.0, "smeared banded face");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/ci/three");
	HC_Set_Visibility ("faces = on, edges = on, markers = on");
	option = "color interpolation = (faces = on, edges = on, markers = on)";
	HC_Insert_Text (0.0, 0.9, 0.0, "faces = on, edges = on, markers = on");
	HC_Set_Window (0.33, 1.0, 0.33, 1.0);
	HC_Set_Rendering_Options (option);
	HC_Include_Segment ("?draw/ci/one/lit sphere");
	HC_Insert_Text (0.0, -0.9, 0.0, "faces, markers, and edges blend");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/ci/four");
	HC_Set_Visibility ("faces = off, edges = on, markers = off");
	option = "color interpolation = (edges = off)";
	HC_Insert_Text (0.0, 0.9, 0.0, option);
	HC_Set_Window (-1.0, -0.33, -0.33, 0.33);
	HC_Set_Rendering_Options (option);
	HC_Include_Segment ("?draw/ci/one/lit sphere");
	HC_Insert_Text (0.0, -0.9, 0.0, "discretely banded edges");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/ci/five");
	HC_Set_Visibility ("faces = off, edges = on, markers = off");
	option = "color interpolation = (edges = on)";
	HC_Insert_Text (0.0, 0.9, 0.0, option);
	HC_Set_Window (-0.33, 0.33, -0.33, 0.33);
	HC_Set_Rendering_Options (option);
	HC_Include_Segment ("?draw/ci/one/lit sphere");
	HC_Insert_Text (0.0, -0.9, 0.0, "smeared banded edges");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/ci/six");
	HC_Set_Visibility ("faces = on, edges = on, markers = off");
	option = "color interpolation = (faces = on, edges = on)";
	HC_Insert_Text (0.0, 0.9, 0.0, option);
	HC_Set_Window (0.33, 1.0, -0.33, 0.33);
	HC_Set_Rendering_Options (option);
	HC_Include_Segment ("?draw/ci/one/lit sphere");
	HC_Insert_Text (0.0, -0.9, 0.0, "faces and edges blend");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/ci/seven");
	HC_Set_Visibility ("faces = off, edges = off, markers = on");
	option = "no color interpolation";
	HC_Insert_Text (0.0, 0.9, 0.0, option);
	HC_Set_Window (-1.0, -0.33, -1.0, -0.33);
	HC_Set_Rendering_Options (option);
	HC_Include_Segment ("?draw/ci/one/lit sphere");
	HC_Insert_Text (0.0, -0.9, 0.0, "discretely banded markers");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/ci/eight");
	HC_Set_Visibility ("faces = off, edges = off, markers = on");
	option = "color interpolation";
	HC_Insert_Text (0.0, 0.9, 0.0, option);
	HC_Set_Window (-0.33, 0.33, -1.0, -0.33);
	HC_Set_Rendering_Options (option);
	HC_Include_Segment ("?draw/ci/one/lit sphere");
	HC_Insert_Text (0.0, -0.9, 0.0, "smeared banded markers");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/ci/nine");
	HC_Set_Visibility ("faces = on, edges = off, markers = on");
	option = "color interpolation";
	HC_Insert_Text (0.0, 0.9, 0.0, option);
	HC_Set_Window (0.33, 1.0, -1.0, -0.33);
	HC_Set_Rendering_Options (option);
	HC_Include_Segment ("?draw/ci/one/lit sphere");
	HC_Insert_Text (0.0, -0.9, 0.0, "faces and markers blend");
    HC_Close_Segment ();
    HC_Update_Display ();
    HC_Show_Time (&stop_time);

    post_memory (4);
    post_results ("face, edge, and marker color interpolation");
    post_time (4, start_time, stop_time);

    if (b_image_out) {
		sprintf (temp_file_name, "%s-color_interpolation", image_file_root);
		export_image (temp_file_name);
    }
}

void test_color_index_interpolation (void) {
    float	start_time,
		stop_time;
    char	*option;

    identify_test ("?buttons/color index interpolation");
    HC_Update_Display ();

    HC_Show_Time (&start_time);
    HC_Open_Segment ("?draw/cii");
	HC_Set_Rendering_Options ("no color interpolation");
	HC_Set_Window_Frame ("off");
	HC_Set_Visibility ("no cutting planes");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/cii/one");
	HC_Set_Visibility ("faces = on, edges = off, markers = off");
	option = "color index interpolation = (faces = off)";
	HC_Insert_Text (0.0, 0.9, 0.0, option);
	HC_Set_Window (-1.0, -0.33, 0.33, 1.0);
	HC_Set_Rendering_Options (option);
	HC_Open_Segment ("lit sphere");
	    HC_Set_Visibility ("cutting planes");
	    HC_Insert_Cutting_Plane (0.0, 0.0, 1.0, 0.0);
	    HC_Include_Segment ("?sphere");
	    HC_Insert_Distant_Light (-1.0, 1.5, -2.0);
	HC_Close_Segment ();
	HC_Insert_Text (0.0, -0.9, 0.0, "lit blue face");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/cii/two");
	HC_Set_Visibility ("faces = on, edges = off, markers = off");
	option = "color index interpolation = (faces = on)";
	HC_Insert_Text (0.0, 0.9, 0.0, option);
	HC_Set_Window (-0.33, 0.33, 0.33, 1.0);
	HC_Set_Rendering_Options (option);
	HC_Include_Segment ("?draw/cii/one/lit sphere");
	HC_Insert_Text (0.0, -0.9, 0.0, "discretely banded face");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/cii/three");
	HC_Set_Visibility ("faces = on, edges = on, markers = on");
	option = "color index interpolation";
	HC_Insert_Text (0.0, 0.9, 0.0, option);
	HC_Set_Window (0.33, 1.0, 0.33, 1.0);
	HC_Set_Rendering_Options (option);
	HC_Include_Segment ("?draw/cii/one/lit sphere");
	HC_Insert_Text (0.0, -0.9, 0.0, "face, edges, and markers blend");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/cii/four");
	HC_Set_Visibility ("faces = off, edges = on, markers = off");
	option = "color index interpolation = (edges = off)";
	HC_Insert_Text (0.0, 0.9, 0.0, option);
	HC_Set_Window (-1.0, -0.33, -0.33, 0.33);
	HC_Set_Rendering_Options (option);
	HC_Include_Segment ("?draw/cii/one/lit sphere");
	HC_Insert_Text (0.0, -0.9, 0.0, "lit blue edges");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/cii/five");
	HC_Set_Visibility ("faces = off, edges = on, markers = off");
	option = "color index interpolation = (edges = on)";
	HC_Insert_Text (0.0, 0.9, 0.0, option);
	HC_Set_Window (-0.33, 0.33, -0.33, 0.33);
	HC_Set_Rendering_Options (option);
	HC_Include_Segment ("?draw/cii/one/lit sphere");
	HC_Insert_Text (0.0, -0.9, 0.0, "discretely banded edges");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/cii/six");
	HC_Set_Visibility ("faces = on, edges = on, markers = off");
	option = "color index interpolation = (faces = on, edges = on)";
	HC_Insert_Text (0.0, 0.9, 0.0, option);
	HC_Set_Window (0.33, 1.0, -0.33, 0.33);
	HC_Set_Rendering_Options (option);
	HC_Include_Segment ("?draw/cii/one/lit sphere");
	HC_Insert_Text (0.0, -0.9, 0.0, "faces and edges blend");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/cii/seven");
	HC_Set_Visibility ("faces = off, edges = off, markers = on");
	option = "no color index interpolation";
	HC_Set_Color_By_Index ("markers", BLUE);
	HC_Set_Rendering_Options ("attribute lock = (color = marker)");
	HC_Insert_Text (0.0, 0.9, 0.0, option);
	HC_Set_Window (-1.0, -0.33, -1.0, -0.33);
	HC_Set_Rendering_Options (option);
	HC_Include_Segment ("?draw/cii/one/lit sphere");
	HC_Insert_Text (0.0, -0.9, 0.0, "lit blue markers");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/cii/eight");
	HC_Set_Visibility ("faces = off, edges = off, markers = on");
	option = "color index interpolation";
	HC_Insert_Text (0.0, 0.9, 0.0, option);
	HC_Set_Window (-0.33, 0.33, -1.0, -0.33);
	HC_Set_Rendering_Options (option);
	HC_Include_Segment ("?draw/cii/one/lit sphere");
	HC_Insert_Text (0.0, -0.9, 0.0, "discretely banded markers");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/cii/nine");
	HC_Set_Visibility ("faces = on, edges = off, markers = on");
	option = "color index interpolation";
	HC_Insert_Text (0.0, 0.9, 0.0, option);
	HC_Set_Window (0.33, 1.0, -1.0, -0.33);
	HC_Set_Rendering_Options (option);
	HC_Include_Segment ("?draw/cii/one/lit sphere");
	HC_Insert_Text (0.0, -0.9, 0.0, "faces and markers blend");
    HC_Close_Segment ();
    HC_Update_Display ();
    HC_Show_Time (&stop_time);

    post_memory (5);
    post_results ("face, edge, and marker color index interpolation");
    post_time (5, start_time, stop_time);

    if (b_image_out) {
		sprintf (temp_file_name, "%s-color_index_interpolation", image_file_root);
		export_image (temp_file_name);
    }
}

void test_face_displacement (void) {
    float	start_time,
		stop_time;
    char	*option;

    identify_test ("?buttons/face displacement");
    HC_Update_Display ();

    HC_Show_Time (&start_time);
    HC_Open_Segment ("?draw/fd");
	HC_Set_Window_Frame ("off");
	HC_Set_Visibility ("lights = (edges = off), markers = off");
	HC_Set_Color_By_Index ("edges", BLACK);
	HC_Set_Rendering_Options ("attribute lock = (color = edges)");
	HC_Set_Rendering_Options ("no color index interpolation, no color interpolation");
	HC_Set_Rendering_Options ("lighting interpolation = (faces = on, edges = off)");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/fd/one");
	option = "face displacement = 8";
	HC_Insert_Text (0.0, 0.9, 0.0, option);
	HC_Set_Window (-1.0, 0.0, 0.0, 1.0);
	HC_Set_Rendering_Options (option);
	HC_Open_Segment ("lit sphere");
	    HC_Include_Segment ("?sphere");
	    HC_Insert_Distant_Light (-1.0, 1.5, -2.0);
	HC_Close_Segment ();
	HC_Insert_Text (0.0, -0.9, 0.0, "default stitching");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/fd/two");
	option = "face displacement = 0";
	HC_Insert_Text (0.0, 0.9, 0.0, option);
	HC_Set_Window (-1.0, 0.0, -1.0, 0.0);
	HC_Set_Rendering_Options (option);
	HC_Include_Segment ("?draw/fd/one/lit sphere");
	HC_Insert_Distant_Light (-1.0, 1.5, -2.0);
	HC_Insert_Text (0.0, -0.9, 0.0, "some stitching");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/fd/three");
	option = "face displacement = -2";
	HC_Insert_Text (0.0, 0.9, 0.0, option);
	HC_Set_Window (0.0, 1.0, 0.0, 1.0);
	HC_Set_Rendering_Options (option);
	HC_Include_Segment ("?draw/fd/one/lit sphere");
	HC_Insert_Distant_Light (-1.0, 1.5, -2.0);
	HC_Insert_Text (0.0, -0.9, 0.0, "bad stitching");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/fd/four");
	option = "face displacement = 16";
	HC_Insert_Text (0.0, 0.9, 0.0, option);
	HC_Set_Window (0.0, 1.0, -1.0, 0.0);
	HC_Set_Visibility ("lights = (edges = off), markers = off");
	HC_Set_Rendering_Options (option);
	HC_Include_Segment ("?draw/fd/one/lit sphere");
	HC_Insert_Distant_Light (-1.0, 1.5, -2.0);
	HC_Insert_Text (0.0, -0.9, 0.0, "no stitching");
    HC_Close_Segment ();
    HC_Update_Display ();
    HC_Show_Time (&stop_time);

    post_memory (6);
    post_results ("various levels of face displacement");
    post_time (6, start_time, stop_time);

    if (b_image_out) {
		sprintf (temp_file_name, "%s-face_displacement", image_file_root);
		export_image (temp_file_name);
    }
}

void test_hsr_algorithm (void) {
    float	start_time,
		stop_time;
    char	*option;

    identify_test ("?buttons/hsr algorithm");
    HC_Update_Display ();

    HC_Show_Time (&start_time);
    HC_Open_Segment ("?draw/h");
	HC_Set_Window_Frame ("off");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/h/one");
	option = "hsr algorithm = hardware z buffer";
	HC_Insert_Text (0.0, 0.95, 0.0, option);
	HC_Set_Window (-1.0, -0.33, 0.0, 1.0);
	HC_Set_Rendering_Options (option);
	HC_Open_Segment ("two spheres");
	    HC_Set_Visibility ("lights = (edges = off), markers = off");
	    HC_Set_Color_By_Index ("edges", BLACK);
	    HC_Set_Rendering_Options ("attribute lock = (color = edges)");
	    HC_Set_Rendering_Options ("lighting interpolation = (faces = on, edges = off)");
	    HC_Open_Segment ("");
		HC_Include_Segment ("?sphere");
		HC_Scale_Object (0.8, 0.8, 0.8);
		HC_Translate_Object (0.2, 0.2, 0.1);
	    HC_Close_Segment ();
	    HC_Open_Segment ("");
		HC_Include_Segment ("?sphere");
		HC_Scale_Object (0.8, 0.8, 0.8);
		HC_Translate_Object (-0.2, -0.2, -0.1);
	    HC_Close_Segment ();
	    HC_Insert_Distant_Light (-1.0, 1.5, -2.0);
	HC_Close_Segment ();
	HC_Insert_Text (0.0, -0.95, 0.0, "any stitching?");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/h/two");
	option = "hsr algorithm = software z buffer";
	HC_Insert_Text (0.0, 0.95, 0.0, option);
	HC_Set_Window (-1.0, -0.33, -1.0, 0.0);
	HC_Set_Rendering_Options (option);
	HC_Include_Segment ("?draw/h/one/two spheres");
	HC_Insert_Text (0.0, -0.95, 0.0, "rasters drawn correctly?");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/h/three");
	option = "hsr algorithm = painters";
	HC_Insert_Text (0.0, 0.95, 0.0, option);
	HC_Set_Window (-0.33, 0.33, 0.0, 1.0);
	HC_Set_Rendering_Options (option);
	HC_Include_Segment ("?draw/h/one/two spheres");
	HC_Insert_Text (0.0, -0.95, 0.0, "should match hardware z?");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/h/four");
	option = "hsr algorithm = z sort only";
	HC_Insert_Text (0.0, 0.95, 0.0, option);
	HC_Set_Window (-0.33, 0.33, -1.0, 0.0);
	HC_Set_Rendering_Options (option);
	HC_Include_Segment ("?draw/h/one/two spheres");
	HC_Insert_Text (0.0, -0.95, 0.0, "intersection is unclean");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/h/five");
	option = "hsr algorithm = priority";
	HC_Insert_Text (0.0, 0.95, 0.0, option);
	HC_Set_Window (0.33, 1.0, 0.0, 1.0);
	HC_Set_Rendering_Options (option);
	HC_Include_Segment ("?draw/h/one/two spheres");
	HC_Insert_Text (0.0, -0.95, 0.0, "lower sphere totally in front");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/h/six");
	HC_Insert_Text (0.0, 0.95, 0.0, "no hidden surface removal");
	HC_Set_Window (0.33, 1.0, -1.0, 0.0);
	HC_Set_Heuristics ("no hidden surfaces");
	HC_Include_Segment ("?draw/h/one/two spheres");
	HC_Insert_Distant_Light (-1.0, 1.5, -2.0);
	HC_Insert_Text (0.0, -0.95, 0.0, "edges out of whack, lower in back");
    HC_Close_Segment ();
    HC_Update_Display ();
    HC_Show_Time (&stop_time);

    post_memory (7);
    post_results ("all available hsr algorithms");
    post_time (7, start_time, stop_time);

    if (b_image_out) {
		sprintf (temp_file_name, "%s-hsr_algorithm", image_file_root);
		export_image (temp_file_name);
    }
}

void test_lighting_interpolation1 (void) {
    float	start_time,
		stop_time;

    identify_test ("?buttons/lighting interpolation 1");
    HC_Update_Display ();

    HC_Show_Time (&start_time);
    HC_Open_Segment ("?draw/li");
	HC_Set_Visibility ("no cutting planes");
	HC_Open_Segment ("row labels");
	    HC_Set_Window (-1.0, -0.85, -1.0, 0.9);
	    HC_Set_Window_Frame ("off");
	    HC_Set_Camera_Projection ("stretched");
	    HC_Insert_Text (0.0,  0.75, 0.0, "FACES");
	    HC_Insert_Text (0.0,  0.25, 0.0, "EDGES");
	    HC_Insert_Text (0.0, -0.25, 0.0, "MARKERS");
	    HC_Insert_Text (0.0, -0.75, 0.0, "COMBINED");
	HC_Close_Segment ();
	HC_Open_Segment ("column labels");
	    HC_Set_Window (-0.85, 1.0, 0.9, 1.0);
	    HC_Set_Window_Frame ("off");
	    HC_Set_Camera_Projection ("stretched");
	    HC_Insert_Text (-0.75, 0.0, 0.0, "UNLIT");
	    HC_Insert_Text (-0.25, 0.0, 0.0, "FLAT");
	    HC_Insert_Text (0.25, 0.0, 0.0, "GOURAUD");
	    HC_Insert_Text (0.75, 0.0, 0.0, "PHONG");
	HC_Close_Segment ();
	HC_Open_Segment ("action");
	    HC_Set_Window (-0.85, 1.0, -1.0, 0.9);
	    HC_Open_Segment ("faces");
		HC_Set_Visibility ("faces = on, edges = off, markers = off");
		HC_Open_Segment ("unlit");
		    HC_Set_Window (-1.0, -0.5, 0.5, 1.0);
		    HC_Open_Segment ("object");
			HC_Set_Visibility ("cutting planes");
			HC_Insert_Cutting_Plane (0.0, 0.0, 1.0, 0.0);
			HC_Set_Rendering_Options (
			    "no color index interpolation, no color interpolation");
			HC_Set_Rendering_Options (
			    "attribute lock = (color = marker)");
			HC_Set_Color_By_Index ("markers", BLUE);
			HC_Include_Segment ("?sphere");
		    HC_Close_Segment ();
		HC_Close_Segment ();
		HC_Open_Segment ("flat");
		    HC_Set_Rendering_Options ("no lighting interpolation");
		    HC_Set_Window (-0.5, 0.0, 0.5, 1.0);
		    HC_Insert_Distant_Light (-1.0, 1.5, -2.0);
		    HC_Include_Segment ("../unlit/object");
		HC_Close_Segment ();
		HC_Open_Segment ("gouraud");
		    HC_Set_Window (0.0, 0.5, 0.5, 1.0);
		    HC_Insert_Distant_Light (-1.0, 1.5, -2.0);
		    HC_Include_Segment ("../unlit/object");
		HC_Close_Segment ();
		HC_Open_Segment ("phong");
		    HC_Set_Rendering_Options ("lighting interpolation = phong");
		    HC_Set_Window (0.5, 1.0, 0.5, 1.0);
		    HC_Insert_Distant_Light (-1.0, 1.5, -2.0);
		    HC_Include_Segment ("../unlit/object");
		HC_Close_Segment ();
	    HC_Close_Segment ();
	    HC_Open_Segment ("edges");
		HC_Set_Visibility ("faces = off, edges = on, markers = off");
		HC_Open_Segment ("unlit");
		    HC_Set_Window (-1.0, -0.5, 0.0, 0.5);
		    HC_Include_Segment ("../../faces/unlit/object");
		HC_Close_Segment ();
		HC_Open_Segment ("flat");
		    HC_Set_Rendering_Options ("no lighting interpolation");
		    HC_Set_Window (-0.5, 0.0, 0.0, 0.5);
		    HC_Insert_Distant_Light (-1.0, 1.5, -2.0);
		    HC_Include_Segment ("../../faces/unlit/object");
		HC_Close_Segment ();
		HC_Open_Segment ("gouraud");
		    HC_Set_Window (0.0, 0.5, 0.0, 0.5);
		    HC_Insert_Distant_Light (-1.0, 1.5, -2.0);
		    HC_Include_Segment ("../../faces/unlit/object");
		HC_Close_Segment ();
		HC_Open_Segment ("phong");
		    HC_Set_Rendering_Options ("lighting interpolation = phong");
		    HC_Set_Window (0.5, 1.0, 0.0, 0.5);
		    HC_Insert_Distant_Light (-1.0, 1.5, -2.0);
		    HC_Include_Segment ("../../faces/unlit/object");
		HC_Close_Segment ();
	    HC_Close_Segment ();
	    HC_Open_Segment ("markers");
		HC_Set_Visibility ("faces = off, edges = off, markers = on");
		HC_Open_Segment ("unlit");
		    HC_Set_Window (-1.0, -0.5, -0.5, 0.0);
		    HC_Include_Segment ("../../faces/unlit/object");
		HC_Close_Segment ();
		HC_Open_Segment ("flat");
		    HC_Set_Rendering_Options ("no lighting interpolation");
		    HC_Set_Window (-0.5, 0.0, -0.5, 0.0);
		    HC_Insert_Distant_Light (-1.0, 1.5, -2.0);
		    HC_Include_Segment ("../../faces/unlit/object");
		HC_Close_Segment ();
		HC_Open_Segment ("gouraud");
		    HC_Set_Window (0.0, 0.5, -0.5, 0.0);
		    HC_Insert_Distant_Light (-1.0, 1.5, -2.0);
		    HC_Include_Segment ("../../faces/unlit/object");
		HC_Close_Segment ();
		HC_Open_Segment ("phong");
		    HC_Set_Rendering_Options ("lighting interpolation = phong");
		    HC_Set_Window (0.5, 1.0, -0.5, 0.0);
		    HC_Insert_Distant_Light (-1.0, 1.5, -2.0);
		    HC_Include_Segment ("../../faces/unlit/object");
		HC_Close_Segment ();
	    HC_Close_Segment ();
	    HC_Open_Segment ("combined");
		HC_Set_Visibility ("faces = on, edges = on, markers = on");
		HC_Open_Segment ("unlit");
		    HC_Set_Window (-1.0, -0.5, -1.0, -0.5);
		    HC_Include_Segment ("../../faces/unlit/object");
		HC_Close_Segment ();
		HC_Open_Segment ("flat");
		    HC_Set_Rendering_Options ("no lighting interpolation");
		    HC_Set_Window (-0.5, 0.0, -1.0, -0.5);
		    HC_Insert_Distant_Light (-1.0, 1.5, -2.0);
		    HC_Include_Segment ("../../faces/unlit/object");
		HC_Close_Segment ();
		HC_Open_Segment ("gouraud");
		    HC_Set_Window (0.0, 0.5, -1.0, -0.5);
		    HC_Insert_Distant_Light (-1.0, 1.5, -2.0);
		    HC_Include_Segment ("../../faces/unlit/object");
		HC_Close_Segment ();
		HC_Open_Segment ("phong");
		    HC_Set_Rendering_Options ("lighting interpolation = phong");
		    HC_Set_Window (0.5, 1.0, -1.0, -0.5);
		    HC_Insert_Distant_Light (-1.0, 1.5, -2.0);
		    HC_Include_Segment ("../../faces/unlit/object");
		HC_Close_Segment ();
	    HC_Close_Segment ();
	HC_Close_Segment ();
    HC_Close_Segment ();
    HC_Update_Display ();
    HC_Show_Time (&stop_time);

    post_memory (8);
    post_results ("lighting interpolations and geometries");
    post_time (8, start_time, stop_time);

    if (b_image_out) {
		sprintf (temp_file_name, "%s-lighting_interpolation1", image_file_root);
		export_image (temp_file_name);
    }
}

void test_lighting_interpolation2 (void) {
    float	start_time,
		stop_time;
    char	*option;

    identify_test ("?buttons/lighting interpolation 2");
    HC_Update_Display ();

    HC_Show_Time (&start_time);
    HC_Open_Segment ("?draw/li");
	HC_Set_Window_Frame ("off");
	HC_Set_Visibility ("markers = off");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/li/one");
	option = "lighting interpolation = (faces = off, edges = off)";
	HC_Insert_Text (0.0, 0.9, 0.0, "faces unlit, edges unlit");
	HC_Set_Window (-1.0, -0.5, 0.33, 1.0);
	HC_Set_Visibility ("lights = off");
	HC_Set_Rendering_Options (option);
	HC_Open_Segment ("lit sphere");
	    HC_Include_Segment ("?sphere");
	    HC_Set_Rendering_Options ("no color index interpolation, no color interpolation");
	    HC_Insert_Distant_Light (-1.0, 1.5, -2.0);
	HC_Close_Segment ();
	HC_Insert_Text (0.0, -0.9, 0.0, "solid unlit blue");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/li/two");
	option = "lighting interpolation = (faces = off, edges = off)";
	HC_Insert_Text (0.0, 0.9, 0.0, "faces unlit, edges flat");
	HC_Set_Window (-1.0, -0.5, -0.33, 0.33);
	HC_Set_Visibility ("lights = (faces = off)");
	HC_Set_Rendering_Options (option);
	HC_Include_Segment ("?draw/li/one/lit sphere");
	HC_Insert_Text (0.0, -0.9, 0.0, "each edge has one distinct color");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/li/three");
	option = "lighting interpolation = (faces = off, edges = gouraud)";
	HC_Insert_Text (0.0, 0.9, 0.0, "faces unlit, edges gouraud");
	HC_Set_Window (-1.0, -0.5, -1.0, -0.33);
	HC_Set_Visibility ("lights = (faces = off)");
	HC_Set_Rendering_Options (option);
	HC_Include_Segment ("?draw/li/one/lit sphere");
	HC_Insert_Text (0.0, -0.9, 0.0, "edge color varies from vertex to vertex");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/li/four");
	option = "lighting interpolation = (faces = off, edges = off)";
	HC_Insert_Text (0.0, 0.9, 0.0, "faces flat, edges unlit");
	HC_Set_Window (-0.5, 0.0, 0.33, 1.0);
	HC_Set_Visibility ("lights = (edges = off)");
	HC_Set_Rendering_Options (option);
	HC_Include_Segment ("?draw/li/one/lit sphere");
	HC_Insert_Text (0.0, -0.9, 0.0, "typical flat with edges");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/li/five");
	option = "lighting interpolation = (faces = off, edges = off)";
	HC_Insert_Text (0.0, 0.9, 0.0, "faces flat, edges flat");
	HC_Set_Window (-0.5, 0.0, -0.33, 0.33);
	HC_Set_Rendering_Options (option);
	HC_Include_Segment ("?draw/li/one/lit sphere");
	HC_Insert_Text (0.0, -0.9, 0.0, "no discernable edges");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/li/six");
	option = "lighting interpolation = (faces = off, edges = gouraud)";
	HC_Insert_Text (0.0, 0.9, 0.0, "faces flat, edges gouraud");
	HC_Set_Window (-0.5, 0.0, -1.0, -0.33);
	HC_Set_Rendering_Options (option);
	HC_Include_Segment ("?draw/li/one/lit sphere");
	HC_Insert_Text (0.0, -0.9, 0.0, "look closely to spot edges");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/li/seven");
	option = "lighting interpolation = (faces = gouraud, edges = off)";
	HC_Insert_Text (0.0, 0.9, 0.0, "faces gouraud, edges unlit");
	HC_Set_Window (0.0, 0.5, 0.33, 1.0);
	HC_Set_Visibility ("lights = (edges = off)");
	HC_Set_Rendering_Options (option);
	HC_Include_Segment ("?draw/li/one/lit sphere");
	HC_Insert_Text (0.0, -0.9, 0.0, "typical gouraud with edges");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/li/eight");
	option = "lighting interpolation = (faces = gouraud, edges = off)";
	HC_Insert_Text (0.0, 0.9, 0.0, "faces gouraud, edges flat");
	HC_Set_Window (0.0, 0.5, -0.33, 0.33);
	HC_Set_Rendering_Options (option);
	HC_Include_Segment ("?draw/li/one/lit sphere");
	HC_Insert_Text (0.0, -0.9, 0.0, "look closely to spot edges");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/li/nine");
	option = "lighting interpolation = (faces = gouraud, edges = gouraud)";
	HC_Insert_Text (0.0, 0.9, 0.0, "faces gouraud, edges gouraud");
	HC_Set_Window (0.0, 0.5, -1.0, -0.33);
	HC_Set_Rendering_Options (option);
	HC_Include_Segment ("?draw/li/one/lit sphere");
	HC_Insert_Text (0.0, -0.9, 0.0, "no discernable edges");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/li/ten");
	option = "lighting interpolation = (faces = phong, edges = off)";
	HC_Insert_Text (0.0, 0.9, 0.0, "faces phong, edges unlit");
	HC_Set_Window (0.5, 1.0, 0.33, 1.0);
	HC_Set_Visibility ("lights = (edges = off)");
	HC_Set_Rendering_Options (option);
	HC_Include_Segment ("?draw/li/one/lit sphere");
	HC_Insert_Text (0.0, -0.9, 0.0, "typical phong with edges");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/li/eleven");
	option = "lighting interpolation = (faces = phong, edges = off)";
	HC_Insert_Text (0.0, 0.9, 0.0, "faces phong, edges flat");
	HC_Set_Window (0.5, 1.0, -0.33, 0.33);
	HC_Set_Rendering_Options (option);
	HC_Include_Segment ("?draw/li/one/lit sphere");
	HC_Insert_Text (0.0, -0.9, 0.0, "look closely to spot edges");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/li/twelve");
	option = "lighting interpolation = (faces = phong, edges = phong)";
	HC_Insert_Text (0.0, 0.9, 0.0, "faces phong, edges phong");
	HC_Set_Window (0.5, 1.0, -1.0, -0.33);
	HC_Set_Rendering_Options (option);
	HC_Include_Segment ("?draw/li/one/lit sphere");
	HC_Insert_Text (0.0, -0.9, 0.0, "no discernable edges");
    HC_Close_Segment ();
    HC_Update_Display ();
    HC_Show_Time (&stop_time);

    post_memory (9);
    post_results ("combinations of face and edge lighting interpolation");
    post_time (9, start_time, stop_time);

    if (b_image_out) {
		sprintf (temp_file_name, "%s-lighting_interpolation2", image_file_root);
		export_image (temp_file_name);
    }
}

void test_local_viewer (void) {
    float	start_time,
		stop_time;
    char	*option;

    identify_test ("?buttons/local viewer");
    HC_Update_Display ();

    HC_Show_Time (&start_time);
    HC_Open_Segment ("?draw/lv");
	HC_Set_Visibility ("markers = off, edges = off");
	HC_Set_Rendering_Options ("lighting interpolation = gouraud");
	/* HC_Set_Color ("faces = (gloss = 20)"); */
	HC_Set_Camera_Position (0.0, 0.0, -1.0);
	HC_Set_Camera_Field (2.0, 2.0);
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/lv/one");
	option = "no local viewer";
	HC_Insert_Text (0.0, 0.9, 0.0, option);
	HC_Set_Rendering_Options (option);
	HC_Set_Window (-0.9, -0.1, -0.5, 0.5);
	HC_Open_Segment ("wall");
	    HC_Include_Segment ("?wall");
	    HC_Insert_Distant_Light (0.0, 0.0, -1.0);
	HC_Close_Segment ();
	HC_Insert_Text (0.0, -0.9, 0.0, "washed out blue wall");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/lv/two");
	option = "local viewer";
	HC_Insert_Text (0.0, 0.9, 0.0, option);
	HC_Set_Rendering_Options (option);
	HC_Set_Window (0.1, 0.9, -0.5, 0.5);
	HC_Include_Segment ("?draw/lv/one/wall");
	HC_Insert_Text (0.0, -0.9, 0.0, "most washed out in center");
    HC_Close_Segment ();
    HC_Update_Display ();
    HC_Show_Time (&stop_time);

    post_memory (10);
    post_results ("phong rendering with and without local viewer");
    post_time (10, start_time, stop_time);

    if (b_image_out) {
		sprintf (temp_file_name, "%s-local_viewer", image_file_root);
		export_image (temp_file_name);
    }
}

void test_perspective_correction (void) {
    float	start_time,
		stop_time;
    char	*option;

    identify_test ("?buttons/perspective correction");
    HC_Update_Display ();

    HC_Show_Time (&start_time);
    HC_Open_Segment ("?draw/pc");
	HC_Set_Visibility ("markers = off, edges = off");
	HC_Set_Rendering_Options ("lighting interpolation = phong");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/pc/one");
	option = "no perspective correction";
	HC_Insert_Text (0.0, 0.9, 0.0, option);
	HC_Set_Rendering_Options (option);
	HC_Set_Window (-0.9, -0.1, -0.5, 0.5);
	HC_Open_Segment ("floor");
	{
	    Vertex	position, target;

	    HC_Include_Segment ("?floor");
	    position.x = 0.0f; position.y = 2.0f; position.z = 0.0f;
	    target.x = 0.0f; target.y = 0.0f; target.z = 0.0f;
	    HC_Insert_Spot_Light (&position, &target, "");
	    HC_Set_Visibility ("faces = on, edges = off, markers = off");
	}
	HC_Close_Segment ();
	HC_Insert_Text (0.0, -0.9, 0.0, "deformed spot projection");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/pc/two");
	option = "perspective correction";
	HC_Insert_Text (0.0, 0.9, 0.0, option);
	HC_Set_Rendering_Options (option);
	HC_Set_Window (0.1, 0.9, -0.5, 0.5);
	HC_Include_Segment ("?draw/pc/one/floor");
	HC_Insert_Text (0.0, -0.9, 0.0, "elliptical spot projection");
    HC_Close_Segment ();
    HC_Update_Display ();
    HC_Show_Time (&stop_time);

    post_memory (11);
    post_results ("phong rendering with and without correction");
    post_time (11, start_time, stop_time);

    if (b_image_out) {
		sprintf (temp_file_name, "%s-perspective_correction", image_file_root);
		export_image (temp_file_name);
    }
}

void test_quantization (void) {
    float	start_time,
		stop_time;
    char	*option;
    char	info[256];

    identify_test ("?buttons/quantization");
    HC_Update_Display ();

    HC_Show_Time (&start_time);
    HC_Open_Segment ("?draw/q");
	HC_Set_Window_Frame ("off");
	HC_Set_Visibility ("edges = off, markers = off");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/q/one");
	option = "quantization = threshold";
	HC_Insert_Text (0.0, 0.9, 0.0, option);
	HC_Set_Window (-1.0, -0.33, -0.8, 0.8);
	HC_Set_Rendering_Options (option);
	HC_Open_Segment ("lit sphere");
	    HC_Include_Segment ("?sphere");
	    HC_Insert_Distant_Light (-1.0, 1.5, -2.0);
	HC_Close_Segment ();
	HC_Insert_Text (0.0, -0.9, 0.0, "banded");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/q/two");
	option = "quantization = ordered dither";
	HC_Insert_Text (0.0, 0.9, 0.0, option);
	HC_Set_Window (-0.33, 0.33, -0.8, 0.8);
	HC_Set_Rendering_Options (option);
	HC_Include_Segment ("?draw/q/one/lit sphere");
	HC_Insert_Text (0.0, -0.9, 0.0, "normal");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/q/three");
	option = "quantization = error diffusion";
	HC_Insert_Text (0.0, 0.9, 0.0, option);
	HC_Set_Window (0.33, 1.0, -0.8, 0.8);
	HC_Set_Rendering_Options (option);
	HC_Set_Rendering_Options ("hsr algorithm = software z buffer");
	HC_Set_Rendering_Options ("software frame buffer options = (color depth = full color)");
	HC_Include_Segment ("?draw/q/one/lit sphere");
	HC_Insert_Text (0.0, -0.9, 0.0, "nicer (needs full color image data)");
    HC_Close_Segment ();
    HC_Update_Display ();
    HC_Show_Time (&stop_time);

    post_memory (12);
    HC_Show_Device_Info ("?my_picture", "max colors", info);
    if (!strcmp (info, "16777216") != 0)
	post_results ("quantization methods make no sense on an RGB device");
    else
	post_results ("various quantization methods");
    post_time (12, start_time, stop_time);

    if (b_image_out) {
		sprintf (temp_file_name, "%s-quantization", image_file_root);
		export_image (temp_file_name);
    }
}

void test_software_fb_options (void) {
    float	start_time,
		stop_time;
    char	*option;

    identify_test ("?buttons/software fb options");
    HC_Update_Display ();

    HC_Show_Time (&start_time);
    HC_Open_Segment ("?draw/sfbo");
	HC_Set_Window_Frame ("off");
	HC_Set_Rendering_Options ("hsr algorithm = software z buffer");
	HC_Set_Visibility ("edges = off, markers = off");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/sfbo/one");
	HC_Insert_Text (0.0, 0.95, 0.0, "defaults");
	HC_Set_Window (-1.0, -0.33, 0.0, 1.0);
	HC_Open_Segment ("lit sphere");
	    HC_Include_Segment ("?sphere");
	    HC_Insert_Distant_Light (-1.0, 1.5, -2.0);
	HC_Close_Segment ();
	HC_Insert_Text (0.0, -0.95, 0.0, "drawn normally");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/sfbo/two");
	option = "software frame buffer options = (size limit = 128 rasters)";
	HC_Insert_Text (0.0, 0.95, 0.0, "size limit = 128 rasters");
	HC_Set_Window (-1.0, -0.33, -1.0, 0.0);
	HC_Set_Rendering_Options (option);
	HC_Include_Segment ("?draw/sfbo/one/lit sphere");
	HC_Insert_Text (0.0, -0.95, 0.0, "128 rasters at a time");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/sfbo/three");
	option = "software frame buffer options = (size limit = 40960 bytes)";
	HC_Insert_Text (0.0, 0.95, 0.0, "size limit = 40960 bytes");
	HC_Set_Window (-0.33, 0.33, 0.0, 1.0);
	HC_Set_Rendering_Options (option);
	HC_Include_Segment ("?draw/sfbo/one/lit sphere");
	HC_Insert_Text (0.0, -0.95, 0.0, "40, 960 bytes at a time");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/sfbo/four");
	option = "software frame buffer options = (color depth = match device)";
	HC_Insert_Text (0.0, 0.95, 0.0, "color depth = match device");
	HC_Set_Window (-0.33, 0.33, -1.0, 0.0);
	HC_Set_Rendering_Options (option);
	HC_Include_Segment ("?draw/sfbo/one/lit sphere");
	HC_Insert_Text (0.0, -0.95, 0.0, "internal buffer matches device");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/sfbo/five");
	option = "software frame buffer options = (color depth = full color)";
	HC_Insert_Text (0.0, 0.95, 0.0, "color depth = full color");
	HC_Set_Window (0.33, 1.0, 0.0, 1.0);
	HC_Set_Rendering_Options (option);
	HC_Include_Segment ("?draw/sfbo/one/lit sphere");
	HC_Insert_Text (0.0, -0.95, 0.0, "internal buffer is RGB");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/sfbo/six");
	option = "software frame buffer options = (no retention)";
	HC_Insert_Text (0.0, 0.95, 0.0, "no retention");
	HC_Set_Window (0.33, 1.0, -1.0, 0.0);
	HC_Set_Rendering_Options (option);
	HC_Include_Segment ("?draw/sfbo/one/lit sphere");
	HC_Insert_Text (0.0, -0.95, 0.0, "memory freed");
    HC_Close_Segment ();
    HC_Update_Display ();
    HC_Show_Time (&stop_time);

    post_memory (13);
    post_results ("software frame buffer options for hsr algorithm = software z buffer");
    post_time (13, start_time, stop_time);

    if (b_image_out) {
		sprintf (temp_file_name, "%s-software_fb_options", image_file_root);
		export_image (temp_file_name);
    }
}

void test_technology (void) {
    float	start_time,
		stop_time;
    char	info[32];
    char	*option;

    identify_test ("?buttons/technology");
    HC_Update_Display ();

    HC_Show_Time (&start_time);
    HC_Open_Segment ("?draw/technology");
	HC_Show_System_Info ("a.i.r. present", info);
	if (strcmp (info, "no") != 0) {
	    HC_Open_Segment ("a");
		option = "technology = standard";
		HC_Insert_Text (-0.6, 0.95, 0.0, option);
		HC_Open_Segment ("w");
		    HC_Set_Window (-0.9, -0.1, 0.1, 0.9);
		    HC_Open_Segment ("lit scene");
			HC_Set_Rendering_Options (option);
			HC_Open_Segment ("");
			    HC_Include_Segment ("?sphere");
			    HC_Scale_Object (0.5, 0.5, 0.5);
			    HC_Translate_Object (0.0, 0.35, -0.5);
			HC_Close_Segment ();
			HC_Include_Segment ("?floor");
			HC_Insert_Distant_Light (-1.0, 1.0, -3.0);
			HC_Set_Visibility ("edges = off, markers = off");
		    HC_Close_Segment ();
		HC_Close_Segment ();
	    HC_Close_Segment ();
	    HC_Open_Segment ("b");
		option = "technology = software frame buffer";
		HC_Insert_Text (-0.6, -0.05, 0.0, option);
		HC_Open_Segment ("");
		    HC_Set_Window (-0.9, -0.1, -0.9, -0.1);
		    HC_Set_Rendering_Options (option);
		    HC_Set_Rendering_Options ("hsr algorithm = painters");
		    HC_Include_Segment ("?draw/technology/a/w/lit scene");
		HC_Close_Segment ();
	    HC_Close_Segment ();
	    HC_Open_Segment ("c");
		option = "technology = radiosity";
		HC_Insert_Text (0.6, 0.95, 0.0, option);
		HC_Open_Segment ("");
		    HC_Set_Window (0.1, 0.9, 0.1, 0.9);
		    HC_Set_Rendering_Options (option);
		    HC_Set_Rendering_Options ("radiosity options = (internal subdivision = 0.1)");
		    HC_Include_Segment ("?draw/technology/a/w/lit scene");
		HC_Close_Segment ();
	    HC_Close_Segment ();
	    HC_Open_Segment ("d");
		option = "technology = ray trace";
		HC_Insert_Text (0.6, -0.05, 0.0, option);
		HC_Open_Segment ("");
		    HC_Set_Window (0.1, 0.9, -0.9, -0.1);
		    HC_Set_Rendering_Options (option);
		    HC_Set_Rendering_Options ("ray trace options = (blocking = 9)");
		    HC_Include_Segment ("?draw/technology/a/w/lit scene");
		HC_Close_Segment ();
	    HC_Close_Segment ();
	}
	else {
	    HC_Open_Segment ("a");
		HC_Set_Window (-0.9, 0.9, 0.1, 0.9);
		option = "technology = standard";
		HC_Set_Rendering_Options (option);
		HC_Insert_Text (0.0, -0.9, 0.0, option);
		HC_Open_Segment ("lit scene");
		    HC_Open_Segment ("");
			HC_Include_Segment ("?sphere");
			HC_Scale_Object (0.5, 0.5, 0.5);
			HC_Translate_Object (0.0, 0.35, -0.5);
		    HC_Close_Segment ();
		    HC_Include_Segment ("?floor");
		    HC_Insert_Distant_Light (-1.0, 1.0, -3.0);
		    HC_Set_Visibility ("edges = off, markers = off");
		HC_Close_Segment ();
	    HC_Close_Segment ();
	    HC_Open_Segment ("b");
		HC_Set_Window (-0.9, 0.9, -0.9, -0.1);
		option = "technology = software frame buffer";
		HC_Set_Rendering_Options (option);
		HC_Insert_Text (0.0, -0.9, 0.0, option);
		option = "hsr algorithm = painters";
		HC_Set_Rendering_Options (option);
		HC_Include_Segment ("?draw/technology/a/lit scene");
	    HC_Close_Segment ();
	}
    HC_Close_Segment ();
    HC_Update_Display ();
    HC_Show_Time (&stop_time);

    post_memory (14);
    post_results ("various rendering technologies");
    post_time (14, start_time, stop_time);

    if (b_image_out) {
		sprintf (temp_file_name, "%s-technology", image_file_root);
		export_image (temp_file_name);
    }
}

void test_texture_interpolation (void) {
    float	start_time,
		stop_time;

    identify_test ("?buttons/texture interpolation");
    HC_Update_Display ();

    HC_Show_Time (&start_time);
    HC_Open_Segment ("?draw/ti");
	HC_Set_Visibility ("no cutting planes");
	HC_Open_Segment ("row labels");
	    HC_Set_Window (-1.0, -0.85, -1.0, 0.9);
	    HC_Set_Window_Frame ("off");
	    HC_Set_Camera_Projection ("stretched");
	    HC_Insert_Text (0.0,  0.8, 0.0, "FACES");
	    HC_Insert_Text (0.0,  0.4, 0.0, "EDGES");
	    HC_Insert_Text (0.0,  0.0, 0.0, "MARKERS");
	    HC_Insert_Text (0.0, -0.4, 0.0, "COMBINED");
	    HC_Insert_Text (0.0, -0.8, 0.0, "OFF");
	HC_Close_Segment ();
	HC_Open_Segment ("column labels");
	    HC_Set_Window (-0.85, 1.0, 0.9, 1.0);
	    HC_Set_Window_Frame ("off");
	    HC_Set_Camera_Projection ("stretched");
	    HC_Insert_Text (-0.75, 0.0, 0.0, "UNLIT");
	    HC_Insert_Text (-0.25, 0.0, 0.0, "FLAT");
	    HC_Insert_Text (0.25, 0.0, 0.0, "GOURAUD");
	    HC_Insert_Text (0.75, 0.0, 0.0, "PHONG");
	HC_Close_Segment ();
	HC_Open_Segment ("action");
	    HC_Set_Window (-0.85, 1.0, -1.0, 0.9);
	    HC_Open_Segment ("faces");
		HC_Set_Visibility ("faces = on, edges = off, markers = off");
		HC_Open_Segment ("unlit");
		    HC_Set_Window (-1.0, -0.5, 0.6, 1.0);
		    HC_Open_Segment ("object");
			HC_Set_Visibility ("cutting planes");
			HC_Insert_Cutting_Plane (0.0, 0.0, 1.0, 0.0);
			HC_Set_Color ("faces = nice image");
			HC_Set_Color ("edges = nice image");
			HC_Set_Color ("markers = nice image");
			HC_Set_Rendering_Options ("attribute lock = color");
			HC_Include_Segment ("?sphere");
		    HC_Close_Segment ();
		HC_Close_Segment ();
		HC_Open_Segment ("flat");
		    HC_Set_Rendering_Options ("no lighting interpolation");
		    HC_Set_Window (-0.5, 0.0, 0.6, 1.0);
		    HC_Insert_Distant_Light (-1.0, 1.5, -2.0);
		    HC_Include_Segment ("../unlit/object");
		HC_Close_Segment ();
		HC_Open_Segment ("gouraud");
		    HC_Set_Window (0.0, 0.5, 0.6, 1.0);
		    HC_Insert_Distant_Light (-1.0, 1.5, -2.0);
		    HC_Include_Segment ("../unlit/object");
		HC_Close_Segment ();
		HC_Open_Segment ("phong");
		    HC_Set_Rendering_Options ("lighting interpolation = phong");
		    HC_Set_Window (0.5, 1.0, 0.6, 1.0);
		    HC_Insert_Distant_Light (-1.0, 1.5, -2.0);
		    HC_Include_Segment ("../unlit/object");
		HC_Close_Segment ();
	    HC_Close_Segment ();
	    HC_Open_Segment ("edges");
		HC_Set_Visibility ("faces = off, edges = on, markers = off");
		HC_Open_Segment ("unlit");
		    HC_Set_Window (-1.0, -0.5, 0.2, 0.6);
		    HC_Include_Segment ("../../faces/unlit/object");
		HC_Close_Segment ();
		HC_Open_Segment ("flat");
		    HC_Set_Rendering_Options ("no lighting interpolation");
		    HC_Set_Window (-0.5, 0.0, 0.2, 0.6);
		    HC_Insert_Distant_Light (-1.0, 1.5, -2.0);
		    HC_Include_Segment ("../../faces/unlit/object");
		HC_Close_Segment ();
		HC_Open_Segment ("gouraud");
		    HC_Set_Window (0.0, 0.5, 0.2, 0.6);
		    HC_Insert_Distant_Light (-1.0, 1.5, -2.0);
		    HC_Include_Segment ("../../faces/unlit/object");
		HC_Close_Segment ();
		HC_Open_Segment ("phong");
		    HC_Set_Rendering_Options ("lighting interpolation = phong");
		    HC_Set_Window (0.5, 1.0, 0.2, 0.6);
		    HC_Insert_Distant_Light (-1.0, 1.5, -2.0);
		    HC_Include_Segment ("../../faces/unlit/object");
		HC_Close_Segment ();
	    HC_Close_Segment ();
	    HC_Open_Segment ("markers");
		HC_Set_Visibility ("faces = off, edges = off, markers = on");
		HC_Open_Segment ("unlit");
		    HC_Set_Window (-1.0, -0.5, -0.2, 0.2);
		    HC_Include_Segment ("../../faces/unlit/object");
		HC_Close_Segment ();
		HC_Open_Segment ("flat");
		    HC_Set_Rendering_Options ("no lighting interpolation");
		    HC_Set_Window (-0.5, 0.0, -0.2, 0.2);
		    HC_Insert_Distant_Light (-1.0, 1.5, -2.0);
		    HC_Include_Segment ("../../faces/unlit/object");
		HC_Close_Segment ();
		HC_Open_Segment ("gouraud");
		    HC_Set_Window (0.0, 0.5, -0.2, 0.2);
		    HC_Insert_Distant_Light (-1.0, 1.5, -2.0);
		    HC_Include_Segment ("../../faces/unlit/object");
		HC_Close_Segment ();
		HC_Open_Segment ("phong");
		    HC_Set_Rendering_Options ("lighting interpolation = phong");
		    HC_Set_Window (0.5, 1.0, -0.2, 0.2);
		    HC_Insert_Distant_Light (-1.0, 1.5, -2.0);
		    HC_Include_Segment ("../../faces/unlit/object");
		HC_Close_Segment ();
	    HC_Close_Segment ();
	    HC_Open_Segment ("combined");
		HC_Set_Visibility ("faces = on, edges = on, markers = on");
		HC_Open_Segment ("unlit");
		    HC_Set_Window (-1.0, -0.5, -0.6, -0.2);
		    HC_Include_Segment ("../../faces/unlit/object");
		HC_Close_Segment ();
		HC_Open_Segment ("flat");
		    HC_Set_Rendering_Options ("no lighting interpolation");
		    HC_Set_Window (-0.5, 0.0, -0.6, -0.2);
		    HC_Insert_Distant_Light (-1.0, 1.5, -2.0);
		    HC_Include_Segment ("../../faces/unlit/object");
		HC_Close_Segment ();
		HC_Open_Segment ("gouraud");
		    HC_Set_Window (0.0, 0.5, -0.6, -0.2);
		    HC_Insert_Distant_Light (-1.0, 1.5, -2.0);
		    HC_Include_Segment ("../../faces/unlit/object");
		HC_Close_Segment ();
		HC_Open_Segment ("phong");
		    HC_Set_Rendering_Options ("lighting interpolation = phong");
		    HC_Set_Window (0.5, 1.0, -0.6, -0.2);
		    HC_Insert_Distant_Light (-1.0, 1.5, -2.0);
		    HC_Include_Segment ("../../faces/unlit/object");
		HC_Close_Segment ();
	    HC_Close_Segment ();
	    HC_Open_Segment ("off");
		HC_Set_Visibility ("faces = on, edges = on, markers = on");
		HC_Set_Rendering_Options ("no texture interpolation");
		HC_Open_Segment ("unlit");
		    HC_Set_Window (-1.0, -0.5, -1.0, -0.6);
		    HC_Include_Segment ("../../faces/unlit/object");
		HC_Close_Segment ();
		HC_Open_Segment ("flat");
		    HC_Set_Rendering_Options ("no lighting interpolation");
		    HC_Set_Window (-0.5, 0.0, -1.0, -0.6);
		    HC_Insert_Distant_Light (-1.0, 1.5, -2.0);
		    HC_Include_Segment ("../../faces/unlit/object");
		HC_Close_Segment ();
		HC_Open_Segment ("gouraud");
		    HC_Set_Window (0.0, 0.5, -1.0, -0.6);
		    HC_Insert_Distant_Light (-1.0, 1.5, -2.0);
		    HC_Include_Segment ("../../faces/unlit/object");
		HC_Close_Segment ();
		HC_Open_Segment ("phong");
		    HC_Set_Rendering_Options ("lighting interpolation = phong");
		    HC_Set_Window (0.5, 1.0, -1.0, -0.6);
		    HC_Insert_Distant_Light (-1.0, 1.5, -2.0);
		    HC_Include_Segment ("../../faces/unlit/object");
		HC_Close_Segment ();
	    HC_Close_Segment ();
	HC_Close_Segment ();
    HC_Close_Segment ();
    HC_Update_Display ();
    HC_Show_Time (&stop_time);

    post_memory (15);
    post_results ("de-activating ignores texture (row = OFF, geometry = black)");
    post_time (15, start_time, stop_time);

    if (b_image_out) {
		sprintf (temp_file_name, "%s-texture_interpolation", image_file_root);
		export_image (temp_file_name);
    }
}

void toggle_color_consolidation (void) {
    char	value[64];

    identify_test ("?buttons/color consolidation");
    HC_Update_Display ();

    HC_QShow_One_Net_Driver_Option ("?my_picture", "color consolidation", value);
    if (strcmp (value, "10%") == 0) {
	HC_QSet_Driver_Options ("?my_picture", "color consolidation = 1.5625%");
	HC_QSet_Window_Pattern ("?buttons/color consolidation", "//");
    }
    else {
	HC_QSet_Driver_Options ("?my_picture", "color consolidation = 10%");
	HC_QSet_Window_Pattern ("?buttons/color consolidation", "solid");
    }
    HC_QShow_One_Net_Driver_Option ("?my_picture", "color consolidation", value);

    HC_Open_Segment ("?draw/text output");
	HC_Set_Text_Font ("size = 0.2 oru");
	HC_Set_Heuristics ("no hidden surfaces");
	HC_Insert_Text (0.0, 0.6, 0.0, "color");
	HC_Insert_Text (0.0, 0.2, 0.0, "consolidation");
	HC_Insert_Text (0.0, -0.2, 0.0, "is now");
	HC_Open_Segment ("");
	    HC_Set_Color_By_Index ("text", RED);
	    HC_Insert_Text (0.0, -0.6, 0.0, value);
	HC_Close_Segment ();
    HC_Close_Segment ();

    post_results ("toggled color consolidation");
}

void toggle_fixed_colors (void) {
    char	value[64];

    identify_test ("?buttons/fixed colors");
    HC_Update_Display ();

    HC_QShow_One_Net_Driver_Option ("?my_picture", "fixed colors", value);
    if (strcmp (value, "8") == 0) {
	HC_QSet_Driver_Options ("?my_picture", "no fixed colors");
	HC_QSet_Window_Pattern ("?buttons/fixed colors", "//");
    }
    else {
	HC_QSet_Driver_Options ("?my_picture", "fixed colors = 8");
	HC_QSet_Window_Pattern ("?buttons/fixed colors", "solid");
    }
    HC_QShow_One_Net_Driver_Option ("?my_picture", "fixed colors", value);

    HC_Open_Segment ("?draw/text output");
	HC_Set_Text_Font ("size = 0.2 oru");
	HC_Set_Heuristics ("no hidden surfaces");
	HC_Insert_Text (0.0, 0.6, 0.0, "fixed");
	HC_Insert_Text (0.0, 0.2, 0.0, "colors");
	HC_Insert_Text (0.0, -0.2, 0.0, "are now");
	HC_Open_Segment ("");
	    HC_Set_Color_By_Index ("text", RED);
	    HC_Insert_Text (0.0, -0.6, 0.0, value);
	HC_Close_Segment ();
    HC_Close_Segment ();

    post_results ("toggled fixed colors");
}

void toggle_gamma_correction (void) {
    char	value[64];

    identify_test ("?buttons/gamma correction");
    HC_Update_Display ();

    HC_QShow_One_Net_Driver_Option ("?my_picture", "gamma correction", value);
    if (strcmp (value, "on") == 0) {
	HC_QSet_Driver_Options ("?my_picture", "no gamma correction");
	HC_QSet_Window_Pattern ("?buttons/gamma correction", "//");
    }
    else {
	HC_QSet_Driver_Options ("?my_picture", "gamma correction");
	HC_QSet_Window_Pattern ("?buttons/gamma correction", "solid");
    }
    HC_QShow_One_Net_Driver_Option ("?my_picture", "gamma correction", value);

    HC_Open_Segment ("?draw/text output");
	HC_Set_Text_Font ("size = 0.2 oru");
	HC_Set_Heuristics ("no hidden surfaces");
	HC_Insert_Text (0.0, 0.6, 0.0, "gamma");
	HC_Insert_Text (0.0, 0.2, 0.0, "correction");
	HC_Insert_Text (0.0, -0.2, 0.0, "is now");
	HC_Open_Segment ("");
	    HC_Set_Color_By_Index ("text", RED);
	    HC_Insert_Text (0.0, -0.6, 0.0, value);
	HC_Close_Segment ();
    HC_Close_Segment ();

    post_results ("toggled gamma correction");
}

void toggle_light_scaling (void) {
    char	value[64];

    identify_test ("?buttons/light scaling");
    HC_Update_Display ();

    HC_QShow_One_Net_Driver_Option ("?my_picture", "light scaling", value);
    if (strcmp (value, "1.4") == 0) {
	HC_QSet_Driver_Options ("?my_picture", "no light scaling");
	HC_QSet_Window_Pattern ("?buttons/light scaling", "//");
    }
    else {
	HC_QSet_Driver_Options ("?my_picture", "light scaling = 1.4");
	HC_QSet_Window_Pattern ("?buttons/light scaling", "solid");
    }
    HC_QShow_One_Net_Driver_Option ("?my_picture", "light scaling", value);

    HC_Open_Segment ("?draw/text output");
	HC_Set_Text_Font ("size = 0.2 oru");
	HC_Set_Heuristics ("no hidden surfaces");
	HC_Insert_Text (0.0, 0.6, 0.0, "light");
	HC_Insert_Text (0.0, 0.2, 0.0, "scaling");
	HC_Insert_Text (0.0, -0.2, 0.0, "is now");
	HC_Open_Segment ("");
	    HC_Set_Color_By_Index ("text", RED);
	    HC_Insert_Text (0.0, -0.6, 0.0, value);
	HC_Close_Segment ();
    HC_Close_Segment ();

    post_results ("toggled light scaling");
}

void toggle_number_of_colors (void) {
    char	value[64];

    identify_test ("?buttons/number of colors");
    HC_Update_Display ();

    HC_QShow_One_Net_Driver_Option ("?my_picture", "number of colors", value);
    if (strcmp (value, "16") == 0) {
	HC_QSet_Driver_Options ("?my_picture", "no number of colors");
	HC_QSet_Window_Pattern ("?buttons/number of colors", "//");
    }
    else {
	HC_QSet_Driver_Options ("?my_picture", "number of colors = 16");
	HC_QSet_Window_Pattern ("?buttons/number of colors", "solid");
    }
    HC_QShow_One_Net_Driver_Option ("?my_picture", "number of colors", value);

    HC_Open_Segment ("?draw/text output");
	HC_Set_Text_Font ("size = 0.2 oru");
	HC_Set_Heuristics ("no hidden surfaces");
	HC_Insert_Text (0.0, 0.6, 0.0, "number of");
	HC_Insert_Text (0.0, 0.2, 0.0, "colors");
	HC_Insert_Text (0.0, -0.2, 0.0, "is now");
	HC_Open_Segment ("");
	    HC_Set_Color_By_Index ("text", RED);
	    HC_Insert_Text (0.0, -0.6, 0.0, value);
	HC_Close_Segment ();
    HC_Close_Segment ();

    post_results ("toggled number of colors");
}

void toggle_update_interrupts (void) {
    char	value[64];

    identify_test ("?buttons/update interrupts");
    HC_Update_Display ();

    HC_QShow_One_Net_Driver_Option ("?my_picture", "update interrupts", value);
    if (strcmp (value, "on") == 0) {
	HC_QSet_Driver_Options ("?my_picture", "no update interrupts");
	HC_QSet_Window_Pattern ("?buttons/update interrupts", "//");
    }
    else {
	HC_QSet_Driver_Options ("?my_picture", "update interrupts");
	HC_QSet_Window_Pattern ("?buttons/update interrupts", "solid");
    }
    HC_QShow_One_Net_Driver_Option ("?my_picture", "update interrupts", value);

    HC_Open_Segment ("?draw/text output");
	HC_Set_Text_Font ("size = 0.2 oru");
	HC_Set_Heuristics ("no hidden surfaces");
	HC_Insert_Text (0.0, 0.6, 0.0, "update");
	HC_Insert_Text (0.0, 0.2, 0.0, "interrupts");
	HC_Insert_Text (0.0, -0.2, 0.0, "are now");
	HC_Open_Segment ("");
	    HC_Set_Color_By_Index ("text", RED);
	    HC_Insert_Text (0.0, -0.6, 0.0, value);
	HC_Close_Segment ();
    HC_Close_Segment ();

    post_results ("toggled update interrupts");
}

void show_device_results (void) {
    int	i, s, cap;

    identify_test ("?buttons/graph");
    HC_Update_Display ();

    HC_Open_Segment ("?draw/graph");
	HC_Set_Window_Frame ("off");
	HC_Set_Heuristics ("concave polygons, no polygon handedness");
	HC_Set_Visibility ("faces = on, edges = on");
	HC_Set_Color_By_Index ("faces", RED);
	HC_Set_Color_By_Index ("edges", BLUE);
	HC_Set_Rendering_Options ("hsr algorithm = priority");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/graph/timing");
	HC_Set_Window (-1.0, 0.0, -1.0, 1.0);
	i = (int)(log10 (ceil (results_max)) - 0.5f);
	s = 1;
	while (i-- > 0)
	    s *= 10;
	cap = (int)(ceil (results_max) + s - 1) / s;
	cap *= s;
	HC_Set_Camera_By_Volume ("stretched",
				 -0.5,
				 (double)NUM_RESULTS + 0.5,
				 (double)cap * -0.25,
				 (double)cap * 1.25);
	HC_Insert_Polygon ((NUM_RESULTS + 2), results);
	HC_Open_Segment ("title");
	    HC_Set_Text_Font ("size = 0.02 sru");
	    HC_Insert_Text ((double)(NUM_RESULTS / 2),
			    (double)cap * 1.125,
			    0.0,
			    "Timing Results by Test");
	HC_Close_Segment ();
	HC_Open_Segment ("y axis");
	    HC_Set_Text_Path (0.0, 1.0, 0.0);
	    HC_Set_Text_Font ("size = 0.01 sru, rotation = 90");
	    HC_Insert_Text (0.0, 0.5 * (double)cap, 0.0, "seconds");
	HC_Close_Segment ();
	HC_Open_Segment ("lines and y values");
	    HC_Set_Line_Pattern ("- -");
	    HC_Set_Text_Path (0.25, -1.0, 0.0);
	    HC_Set_Text_Font ("size = 0.01 sru");
	    HC_Set_Text_Alignment ("<^");
	    for (i = 1; i < (NUM_RESULTS + 1); i++) {
		HC_Insert_Line ((double)i, 0.0, 0.0,
				(double)i, (double)cap, 0.0);
		HC_Insert_Text ((double)i, -0.01, 0.0, labels[i - 1]);
	    }
	HC_Close_Segment ();
	HC_Open_Segment ("lines and x values");
	    HC_Set_Line_Pattern ("- -");
	    HC_Set_Text_Font ("size = 0.01 sru");
	    HC_Set_Text_Alignment (">");
	    for (i = 0; i <= cap; i += s) {
		char	string[64];

		HC_Insert_Line (1.0, (double)i, 0.0,
				(double)NUM_RESULTS, (double)i, 0.0);
		sprintf (string, "%d", i);
		HC_Insert_Text (0.85, (double)i, 0.0, string);
	    }
	HC_Close_Segment ();
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/graph/memory");
	HC_Set_Window (0.0, 1.0, -1.0, 1.0);
	i = (int)(log10 (ceil (results2_max)) - 0.5f);
	s = 1;
	while (i-- > 0)
	    s *= 10;
	cap = (int)(ceil (results2_max) + s - 1) / s;
	cap *= s;
	HC_Set_Camera_By_Volume ("stretched",
				 -0.5,
				 (double)NUM_RESULTS + 0.5,
				 (double)cap * -0.25,
				 (double)cap * 1.25);
	HC_Insert_Polygon ((NUM_RESULTS + 2), results2);
	HC_Open_Segment ("");
	    HC_Set_Color_By_Index ("faces", GREEN);
	    HC_Insert_Polygon ((NUM_RESULTS + 2), results3);
	HC_Close_Segment ();
	HC_Open_Segment ("");
	    HC_Set_Text_Font ("size = 0.02 sru");
	    HC_Insert_Text ((double)(NUM_RESULTS / 2),
			    (double)cap * 1.125,
			    0.0,
			    "Memory Use by Test");
	HC_Close_Segment ();
	HC_Open_Segment ("");
	    HC_Set_Text_Path (0.0, 1.0, 0.0);
	    HC_Set_Text_Font ("size = 0.01 sru, rotation = 90");
	    HC_Insert_Text (0.0, 0.5 * (double)cap, 0.0, "K");
	HC_Close_Segment ();
	HC_Open_Segment ("");
	    HC_Set_Line_Pattern ("- -");
	    HC_Set_Text_Path (0.25, -1.0, 0.0);
	    HC_Set_Text_Font ("size = 0.01 sru");
	    HC_Set_Text_Alignment ("<^");
	    for (i = 1; i < (NUM_RESULTS + 1); i++) {
		HC_Insert_Line ((double)i, 0.0, 0.0,
				(double)i, (double)cap, 0.0);
		HC_Insert_Text ((double)i, -0.01, 0.0, labels[i - 1]);
	    }
	HC_Close_Segment ();
	HC_Open_Segment ("");
	    HC_Set_Line_Pattern ("- -");
	    HC_Set_Text_Font ("size = 0.01 sru");
	    HC_Set_Text_Alignment (">");
	    for (i = 0; i <= cap; i += s) {
		char	string[64];

		HC_Insert_Line (1.0, (double)i, 0.0,
				(double)NUM_RESULTS, (double)i, 0.0);
		sprintf (string, "%d", i);
		HC_Insert_Text (0.85, (double)i, 0.0, string);
	    }
	HC_Close_Segment ();
    HC_Close_Segment ();

    post_results ("timing and memory (allocated=red, in-use=green) results");
}

int driver_has_a_keyboard_or_mouse (void) {
    char answer[256];

    HC_Show_Device_Info ("?my_picture", "keyboard", answer);
    if (strcmp (answer, "yes") == 0)
	return TRUE;
    else {
	HC_Show_Device_Info ("?my_picture", "locater", answer);
	if (strcmp (answer, "yes") == 0)
	    return TRUE;
	else
	    return FALSE;
    }
}

void run_tests_based_on_user_input () {

    int		test_number, previous_test_number;
    char	selection[256];
    int		keep_testing;
    char	event[256];

    HC_Enable_Button_Events ("?my_picture", "anything");
    HC_Enable_Selection_Events ("?my_picture", "?my_picture");

    test_number = 0;
    keep_testing = TRUE;
    show_execution_context ();
    while (keep_testing) {
	previous_test_number = test_number;

	HC_Await_Event (event);

	/*
	 * decide if the user hit enter (next test)
	 * or clicked on a specific test to run and
	 * set the test number (test to run) accordingly
	 */
	if (strcmp (event, "selection") == 0) {
	    HC_Show_Selection (selection);
	    if (strcmp (selection, "atmospheric attenuation") == 0)
		test_number = 1;
	    else if (strcmp (selection, "attribute lock") == 0)
		test_number = 2;
	    else if (strcmp (selection, "color interpolation") == 0)
		test_number = 3;
	    else if (strcmp (selection, "color index interpolation") == 0)
		test_number = 4;
	    else if (strcmp (selection, "face displacement") == 0)
		test_number = 5;
	    else if (strcmp (selection, "hsr algorithm") == 0)
		test_number = 6;
	    else if (strcmp (selection, "lighting interpolation 1") == 0)
		test_number = 7;
	    else if (strcmp (selection, "lighting interpolation 2") == 0)
		test_number = 8;
	    else if (strcmp (selection, "local viewer") == 0)
		test_number = 9;
	    else if (strcmp (selection, "perspective correction") == 0)
		test_number = 10;
	    else if (strcmp (selection, "quantization") == 0)
		test_number = 11;
	    else if (strcmp (selection, "software fb options") == 0)
		test_number = 12;
	    else if (strcmp (selection, "technology") == 0)
		test_number = 13;
	    else if (strcmp (selection, "texture interpolation") == 0)
		test_number = 14;
	    else if (strcmp (selection, "quit") == 0)
		test_number = 15;
	    else if (strcmp (selection, "reset") == 0)
		test_number = 16;
	    else if (strcmp (selection, "color consolidation") == 0)
		test_number = 17;
	    else if (strcmp (selection, "fixed colors") == 0)
		test_number = 18;
	    else if (strcmp (selection, "gamma correction") == 0)
		test_number = 19;
	    else if (strcmp (selection, "light scaling") == 0)
		test_number = 20;
	    else if (strcmp (selection, "number of colors") == 0)
		test_number = 21;
	    else if (strcmp (selection, "update interrupts") == 0)
		test_number = 22;
	    else if (strcmp (selection, "graph") == 0)
		test_number = 23;
	    else
		test_number++;
	}
	else if (strcmp (event, "button") == 0) {
	    HC_Show_Button (selection);
	    if (strcmp (selection, "q") == 0)
		test_number = 14;
	    else
		test_number++;
	}
	else if (strcmp (event, "none") == 0)
	    /* driver killed by the system */
	    HC_Exit_Program ();
	else
	    /* unexpected special event */
	    test_number = 14;

	/*
	 * run the desired test regardless of how
	 * test number was set above
	 */
	switch (test_number) {
	    case 1: {
		test_atmospheric_attenuation ();
	    }   break;

	    case 2: {
		test_attribute_lock ();
	    }   break;

	    case 3: {
		test_color_interpolation ();
	    }   break;

	    case 4: {
		test_color_index_interpolation ();
	    }   break;

	    case 5: {
		test_face_displacement ();
	    }   break;

	    case 6: {
		test_hsr_algorithm ();
	    }   break;

	    case 7: {
		test_lighting_interpolation1 ();
	    }   break;

	    case 8: {
		test_lighting_interpolation2 ();
	    }   break;

	    case 9: {
		test_local_viewer ();
	    }   break;

	    case 10: {
		test_perspective_correction ();
	    }   break;

	    case 11: {
		test_quantization ();
	    }   break;

	    case 12: {
		test_software_fb_options ();
	    }   break;

	    case 13: {
		test_technology ();
	    }   break;

	    case 14: {
		test_texture_interpolation ();
	    }   break;

	    case 15:
	    default: {
		keep_testing = FALSE;
	    }   break;

	    case 16: {
		HC_Disable_Button_Events ("?my_picture", "anything");
		HC_Disable_Selection_Events ("?my_picture", "?my_picture");

		HC_Reset_System ();

		init ();
		test_number = 0;
		show_execution_context ();
		HC_Enable_Button_Events ("?my_picture", "anything");
		HC_Enable_Selection_Events ("?my_picture", "?my_picture");
	    }   break;

	    case 17: {
		test_number = previous_test_number - 1;
		toggle_color_consolidation ();
	    }   break;

	    case 18: {
		test_number = previous_test_number - 1;
		toggle_fixed_colors ();
	    }   break;

	    case 19: {
		test_number = previous_test_number - 1;
		toggle_gamma_correction ();
	    }   break;

	    case 20: {
		test_number = previous_test_number - 1;
		toggle_light_scaling ();
	    }   break;

	    case 21: {
		test_number = previous_test_number - 1;
		toggle_number_of_colors ();
	    }   break;

	    case 22: {
		test_number = previous_test_number - 1;
		toggle_update_interrupts ();
	    }   break;

	    case 23: {
		test_number = previous_test_number - 1;
		show_device_results ();
	    }   break;
	}
    }

    HC_Disable_Button_Events ("?my_picture", "anything");
    HC_Disable_Selection_Events ("?my_picture", "?my_picture");
    HC_Exit_Program ();
}

void run_non_input_tests_once (void) {
    show_execution_context ();
   
    test_atmospheric_attenuation ();
   
    test_attribute_lock ();
    
    test_color_interpolation ();
    
    test_color_index_interpolation ();
    
    test_face_displacement ();
    
    test_hsr_algorithm ();
    
    test_lighting_interpolation1 ();
    
    test_lighting_interpolation2 ();
    
    test_perspective_correction ();
    
    test_quantization ();
    
    test_software_fb_options ();
    
    test_technology ();
    
    test_texture_interpolation ();

    show_device_results ();
    HC_Update_Display ();

    HC_Exit_Program ();
}


int main (
    int		argc,
    char	**argv) {

    int		run_interactively;
    size_t	i;
	char	hostname_buffer[1024];
    const char	*hostname;

    run_interactively = TRUE;

#ifdef UNIX_SYSTEM
    gethostname(hostname_buffer,1024);
#else
    hostname = getenv("COMPUTERNAME");

    if(hostname)
    	strcpy(hostname_buffer, hostname);
    else
    	hostname_buffer[0] = '\0';
#endif

    /* in case of host.techsoft3d.com */
    for(i=0; i < strlen(hostname_buffer); i++) {

    	if(hostname_buffer[i] == '.') {
    		hostname_buffer[i] = '\0';
    		break;
    	}
    	hostname_buffer[i] = tolower (hostname_buffer[i]);
    }

    hostname=&hostname_buffer[0];
    
    /* driver type */
    if (argc >= 2) {
		if (!strcmp (argv[1], "ogl")) {
			driver_type = OGL;
			driver_name = "ogl";
		}
		else if (!strcmp (argv[1], "msw")) {
			driver_type = MSW;
			driver_name = "msw";
		}
		else if (!strcmp (argv[1], "x11")) {
			driver_type = X11;
			driver_name = "x11";
		}
		else if (!strcmp (argv[1], "default")) {
			driver_type = DEFAULT_DRIVER;
			driver_name = "default";
		}
    }

	/* automation */
    if (argc >= 3) {
		if (!strncmp (argv[2], "image", 3)){
			b_image_out = 1;
		}
		else {
			char	option_string[64];

			HC_Define_Alias ("?picture", "?driver/printf/stdtest.out");
			strcpy (option_string, "debug = ");
			strcat (option_string, argv[2]);
			HC_QSet_Driver_Options ("/", option_string);
		}
		run_interactively = FALSE;
    }

	/* image file format */
	if (argc >= 4 && (!strncmp (argv[3], "binary",3))) {
		image_file_format = RAW_BINARY;
	}

	/* image file name  */
	if (argc >= 5) {
    	/* argv[4] should be the plantform type */
		sprintf (image_file_root, "%s-%s", hostname, argv[4]);
	}
	else {
		sprintf (image_file_root, "rendtest");
	}

	/* image source */
	if (argc >= 6 && (!strncmp (argv[5], "oglhardware",4))) {
		image_source = OGL_HW;
	}

    init();

	if (!driver_has_a_keyboard_or_mouse ())
		run_interactively = FALSE;

    if (run_interactively)
		run_tests_based_on_user_input ();
    else
		run_non_input_tests_once ();

    return 0;
}

