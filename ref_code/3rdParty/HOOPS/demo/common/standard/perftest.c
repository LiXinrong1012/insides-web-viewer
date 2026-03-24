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
 * $Id: perftest.c,v 1.7 2010-10-26 21:29:09 jason Exp $
 */

#include "hc.h"
#include "hc_standalone.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifndef TRUE
#  define TRUE -1
#endif

#ifndef FALSE
#  define FALSE 0
#endif

#define BLACK		0
#define RED		1
#define BLUE		2
#define GREEN		3
#define WHITE		4

#define NUM_RESULTS	16
#define WIDTH		0.25f
#define HEIGHT		0.25f
#define GAP		0.07f
#define Pi		(3.141592f)
#define S_NUMBER	8
#define S_ANGLE		(2.0f * Pi / (float)S_NUMBER)
#define NUM_COLORS	9

#define NUM_MARKERS	41
#define NUM_BUTTONS	26
static char *units[] =  {"2D polylines/sec",
			 "3D edges/sec",
			 "2D markers/sec",
			 "3D markers/sec",
			 "2D polygons/sec",
			 "2D ellipses/sec",
			 "3D polygons/sec",
			 "3D edgeless polygons/sec",
			 "3D lit edgeless polygons/sec",
			 "2D hello worlds/sec",
			 "3D hello worlds/sec",
			 "8 bit pixels/sec",
			 "24 bit pixels/sec",
			 "unlit shells/sec",
			 "flat lit shells/sec",
			 "gouraud lit shells/sec"};

typedef struct {
    float	x, y, z;
} Point;


static int	seconds_per_test;
static float	results1[NUM_RESULTS];
static float	results2[NUM_RESULTS];
static float	results3[NUM_RESULTS];


void init_results (void) {
    int i;

    for (i = 0; i < NUM_RESULTS; i++) {
	results1[i] = results2[i] = results3[i] = 0.0f;
    }
}


void setup_window_structure (void) {
    char	info[256];
    float	top, bottom, size;

    HC_Open_Segment ("?style library/danger");
	HC_Set_Color_By_Index ("window contrast", RED);
    HC_Close_Segment ();

    HC_Open_Segment ("?style library/toggle");
	HC_Set_Color_By_Index ("window contrast", BLUE);
    HC_Close_Segment ();

    HC_Open_Segment ("?style library/special");
	HC_Set_Color_By_Index ("window contrast", GREEN);
    HC_Close_Segment ();

    HC_Open_Segment ("?picture");
	HC_Set_Color_Map ("black, red, blue, green, white");
	HC_Set_Camera_Projection ("stretched");
	HC_Set_Text_Font ("size = 0.01 sru");
	HC_Set_Color_By_Index ("windows", WHITE);
	HC_Set_Color_By_Index ("text", BLACK);
	HC_Set_Selectability ("off");

	HC_Define_System_Options ("no bounding volumes, no sanity checking");
	HC_Set_Heuristics ("related selection limit = 0");
	HC_Set_Driver_Options ("no double-buffering");
	HC_Set_Driver_Options ("no force black-and-white");
	HC_Set_Driver_Options ("no update interrupts");
	HC_Set_Driver_Options ("subscreen = (-1.0, 1.0, -1.0, 1.0)");

	HC_Open_Segment ("title");
	    HC_Set_Text_Font ("size = 0.04 sru");
	    HC_Set_Window (-1.0, 1.0, 0.9, 1.0);
	    HC_Set_Heuristics ("no clipping, no hidden surfaces");
	    HC_Insert_Text (0.0, 0.0, 0.0, "Performance Test");
	    HC_Open_Segment ("");
		HC_Set_Text_Font ("size = 0.01 sru");
		HC_Set_Text_Alignment ("<");
		HC_Insert_Text (-1.0, 0.0, 0.0, "Tech Soft Graphics Development");
	    HC_Close_Segment ();
	    HC_Open_Segment ("");
		HC_Set_Text_Font ("size = 0.01 sru");
		HC_Set_Text_Alignment (">");
		HC_Insert_Text (1.0, 0.0, 0.0, "$Revision: 1.7 $");
	    HC_Close_Segment ();
	HC_Close_Segment ();
	HC_Open_Segment ("draw");
	    HC_Set_Window (-1.0, 0.8, -0.9, 0.9);
	    HC_Set_Selectability ("windows = on");
	HC_Close_Segment ();
	HC_Bring_To_Front ("draw");

	top = 1.0f;
	bottom = -1.0f;
	size = (top - bottom) / (float)NUM_BUTTONS;

	HC_Open_Segment ("buttons");
	    HC_Set_Window (0.8, 1.0, -0.9, 0.9);
	    HC_Set_Window_Frame ("off");
	    HC_Set_Heuristics ("no clipping, no hidden surfaces");
	    HC_Open_Segment ("all");
		HC_Set_Window (-1.0, 1.0, (double)(top - size), (double)top);
		top -= size;
		HC_Set_Window_Frame ("on");
		HC_Insert_Text (0.0, 0.0, 0.0, "ALL");
		HC_Set_Selectability ("windows = on");
	    HC_Close_Segment ();
	    HC_Open_Segment ("polyline_2d");
		HC_Set_Window (-1.0, 1.0, (double)(top - size), (double)top);
		top -= size;
		HC_Set_Window_Frame ("on");
		HC_Insert_Text (0.0, 0.0, 0.0, "polyline (2D)");
		HC_Set_Selectability ("windows = on");
	    HC_Close_Segment ();
	    HC_Open_Segment ("polyedge_3d");
		HC_Set_Window (-1.0, 1.0, (double)(top - size), (double)top);
		top -= size;
		HC_Set_Window_Frame ("on");
		HC_Insert_Text (0.0, 0.0, 0.0, "polyedge (3D)");
		HC_Set_Selectability ("windows = on");
	    HC_Close_Segment ();
	    HC_Open_Segment ("marker_2d");
		HC_Set_Window (-1.0, 1.0, (double)(top - size), (double)top);
		top -= size;
		HC_Set_Window_Frame ("on");
		HC_Insert_Text (0.0, 0.0, 0.0, "marker (2D)");
		HC_Set_Selectability ("windows = on");
	    HC_Close_Segment ();
	    HC_Open_Segment ("marker_3d");
		HC_Set_Window (-1.0, 1.0, (double)(top - size), (double)top);
		top -= size;
		HC_Set_Window_Frame ("on");
		HC_Insert_Text (0.0, 0.0, 0.0, "marker (3D)");
		HC_Set_Selectability ("windows = on");
	    HC_Close_Segment ();
	    HC_Open_Segment ("polygon_2d");
		HC_Set_Window (-1.0, 1.0, (double)(top - size), (double)top);
		top -= size;
		HC_Set_Window_Frame ("on");
		HC_Insert_Text (0.0, 0.0, 0.0, "polygon (2D)");
		HC_Set_Selectability ("windows = on");
	    HC_Close_Segment ();
	    HC_Open_Segment ("ellipse_2d");
		HC_Set_Window (-1.0, 1.0, (double)(top - size), (double)top);
		top -= size;
		HC_Set_Window_Frame ("on");
		HC_Insert_Text (0.0, 0.0, 0.0, "ellipse (2D)");
		HC_Set_Selectability ("windows = on");
	    HC_Close_Segment ();
	    HC_Open_Segment ("polygon_3d");
		HC_Set_Window (-1.0, 1.0, (double)(top - size), (double)top);
		top -= size;
		HC_Set_Window_Frame ("on");
		HC_Insert_Text (0.0, 0.0, 0.0, "polygon (3D)");
		HC_Set_Selectability ("windows = on");
	    HC_Close_Segment ();
	    HC_Open_Segment ("poly_no_edge");
		HC_Set_Window (-1.0, 1.0, (double)(top - size), (double)top);
		top -= size;
		HC_Set_Window_Frame ("on");
		HC_Insert_Text (0.0, 0.0, 0.0, "polygon (no edges)");
		HC_Set_Selectability ("windows = on");
	    HC_Close_Segment ();
	    HC_Open_Segment ("poly_flat");
		HC_Set_Window (-1.0, 1.0, (double)(top - size), (double)top);
		top -= size;
		HC_Set_Window_Frame ("on");
		HC_Insert_Text (0.0, 0.0, 0.0, "polygon (flat)");
		HC_Set_Selectability ("windows = on");
	    HC_Close_Segment ();
	    HC_Open_Segment ("text_2d");
		HC_Set_Window (-1.0, 1.0, (double)(top - size), (double)top);
		top -= size;
		HC_Set_Window_Frame ("on");
		HC_Insert_Text (0.0, 0.0, 0.0, "text (2D)");
		HC_Set_Selectability ("windows = on");
	    HC_Close_Segment ();
	    HC_Open_Segment ("text_3d");
		HC_Set_Window (-1.0, 1.0, (double)(top - size), (double)top);
		top -= size;
		HC_Set_Window_Frame ("on");
		HC_Insert_Text (0.0, 0.0, 0.0, "text (3D)");
		HC_Set_Selectability ("windows = on");
	    HC_Close_Segment ();
	    HC_Open_Segment ("image");
		HC_Set_Window (-1.0, 1.0, (double)(top - size), (double)top);
		top -= size;
		HC_Set_Window_Frame ("on");
		HC_Insert_Text (0.0, 0.0, 0.0, "image (8 bit)");
		HC_Set_Selectability ("windows = on");
	    HC_Close_Segment ();
	    HC_Open_Segment ("rgb_image");
		HC_Set_Window (-1.0, 1.0, (double)(top - size), (double)top);
		top -= size;
		HC_Set_Window_Frame ("on");
		HC_Insert_Text (0.0, 0.0, 0.0, "image (24 bit)");
		HC_Set_Selectability ("windows = on");
	    HC_Close_Segment ();
	    HC_Open_Segment ("shell");
		HC_Set_Window (-1.0, 1.0, (double)(top - size), (double)top);
		top -= size;
		HC_Set_Window_Frame ("on");
		HC_Insert_Text (0.0, 0.0, 0.0, "shell (unlit)");
		HC_Set_Selectability ("windows = on");
	    HC_Close_Segment ();
	    HC_Open_Segment ("shell_flat");
		HC_Set_Window (-1.0, 1.0, (double)(top - size), (double)top);
		top -= size;
		HC_Set_Window_Frame ("on");
		HC_Insert_Text (0.0, 0.0, 0.0, "shell (flat)");
		HC_Set_Selectability ("windows = on");
	    HC_Close_Segment ();
	    HC_Open_Segment ("shell_gouraud");
		HC_Set_Window (-1.0, 1.0, (double)(top - size), (double)top);
		top -= size;
		HC_Set_Window_Frame ("on");
		HC_Insert_Text (0.0, 0.0, 0.0, "shell (gouraud)");
		HC_Set_Selectability ("windows = on");
	    HC_Close_Segment ();
	    HC_Open_Segment ("write_results");
		HC_Set_Window (-1.0, 1.0, (double)(top - size), (double)top);
		top -= size;
		HC_Style_Segment ("?style library/special");
		HC_Set_Window_Frame ("on");
		HC_Insert_Text (0.0, 0.0, 0.0, "write results");
		HC_Set_Selectability ("windows = on");
	    HC_Close_Segment ();
	    HC_Open_Segment ("display_results");
		HC_Set_Window (-1.0, 1.0, (double)(top - size), (double)top);
		top -= size;
		HC_Style_Segment ("?style library/special");
		HC_Set_Window_Frame ("on");
		HC_Insert_Text (0.0, 0.0, 0.0, "display results");
		HC_Set_Selectability ("windows = on");
	    HC_Close_Segment ();
	    HC_Open_Segment ("quit");
		HC_Set_Window (-1.0, 1.0, (double)(top - size), (double)top);
		top -= size;
		HC_Style_Segment ("?style library/danger");
		HC_Set_Window_Frame ("on");
		HC_Insert_Text (0.0, 0.0, 0.0, "QUIT");
		HC_Set_Selectability ("windows = on");
	    HC_Close_Segment ();
	    HC_Open_Segment ("legend");
		HC_Set_Window (-1.0, 1.0, (double)(top - (2.0f * size)), (double)top);
		HC_Set_Window_Frame ("off");
		top -= (2.0f * size);
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
		HC_Set_Window (-1.0, 1.0, (double)(top - size), (double)top);
		top -= size;
		HC_Style_Segment ("?style library/danger");
		HC_Set_Window_Frame ("on");
		HC_Insert_Text (0.0, 0.0, 0.0, "RESET");
		HC_Set_Selectability ("windows = on");
	    HC_Close_Segment ();
	    HC_Open_Segment ("double_buffer");
		HC_Set_Window (-1.0, 1.0, (double)(top - size), (double)top);
		top -= size;
		HC_Style_Segment ("?style library/toggle");
		HC_Set_Window_Frame ("on");
		HC_Set_Window_Pattern ("//");
		HC_Insert_Text (0.0, 0.0, 0.0, "dbuffer");
		HC_Set_Selectability ("windows = on");
	    HC_Close_Segment ();
	    HC_Open_Segment ("culling");
		HC_Set_Window (-1.0, 1.0, (double)(top - size), (double)top);
		top -= size;
		HC_Style_Segment ("?style library/toggle");
		HC_Set_Window_Frame ("on");
		HC_Set_Window_Pattern ("//");
		HC_Insert_Text (0.0, 0.0, 0.0, "culling");
		HC_Set_Selectability ("windows = on");
	    HC_Close_Segment ();
	    HC_Open_Segment ("hsr");
		HC_Set_Window (-1.0, 1.0, (double)(top - size), (double)top);
		top -= size;
		HC_Style_Segment ("?style library/toggle");
		HC_Set_Window_Frame ("on");
		HC_Set_Window_Pattern ("//");
		HC_Insert_Text (0.0, 0.0, 0.0, "software Z");
		HC_Set_Selectability ("windows = on");
	    HC_Close_Segment ();
	HC_Close_Segment ();
	HC_Open_Segment ("memory");
	    HC_Set_Window (-1.0, -0.8, -1.0, -0.9);
	    HC_Set_Heuristics ("no clipping, no hidden surfaces");
	    HC_Insert_Text (0.0, 0.0, 0.0, "MEMORY");
	HC_Close_Segment ();
	HC_Open_Segment ("results");
	    HC_Set_Window (-0.8, 0.8, -1.0, -0.9);
	    HC_Set_Heuristics ("no hidden surfaces");
	    HC_Set_Text_Font ("size = 0.02 sru");
	    HC_Insert_Text (0.0, 0.0, 0.0,
			    "click on a test or hit <return> for all");
	HC_Close_Segment ();
	HC_Open_Segment ("time");
	    HC_Set_Window (0.8, 1.0, -1.0, -0.9);
	    HC_Set_Heuristics ("no clipping, no hidden surfaces");
	    HC_Insert_Text (0.0, 0.0, 0.0, "TIME");
	HC_Close_Segment ();
    HC_Close_Segment ();

    HC_Define_Alias ("?title", "?picture/title");
    HC_Define_Alias ("?draw", "?picture/draw");
    HC_Define_Alias ("?buttons", "?picture/buttons");
    HC_Define_Alias ("?memory", "?picture/memory");
    HC_Define_Alias ("?results", "?picture/results");
    HC_Define_Alias ("?time", "?picture/time");
}


void construct_letter (
    char	letter) {
    Point	points[13];

    if (letter == 'H') {
	points[0].x =  -1.0f; points[0].y =  -1.0f; points[0].z =  0.0f;
	points[1].x =  -1.0f; points[1].y =   1.0f; points[1].z =  0.0f;
	points[2].x =  -0.3f; points[2].y =   1.0f; points[2].z =  0.0f;
	points[3].x =  -0.3f; points[3].y =   0.3f; points[3].z =  0.0f;
	points[4].x =   0.3f; points[4].y =   0.3f; points[4].z =  0.0f;
	points[5].x =   0.3f; points[5].y =   1.0f; points[5].z =  0.0f;
	points[6].x =   1.0f; points[6].y =   1.0f; points[6].z =  0.0f;
	points[7].x =   1.0f; points[7].y =  -1.0f; points[7].z =  0.0f;
	points[8].x =   0.3f; points[8].y =  -1.0f; points[8].z =  0.0f;
	points[9].x =   0.3f; points[9].y =  -0.3f; points[9].z =  0.0f;
	points[10].x = -0.3f; points[10].y = -0.3f; points[10].z = 0.0f;
	points[11].x = -0.3f; points[11].y = -1.0f; points[11].z = 0.0f;
	points[12].x = -1.0f; points[12].y = -1.0f; points[12].z = 0.0f;
	HC_Insert_Polyline (13, points);
    }
    else if (letter == 'O') {
	points[0].x =   0.0f; points[0].y =  -1.0f; points[0].z =  0.0f;
	points[1].x =   1.0f; points[1].y =   0.0f; points[1].z =  0.0f;
	points[2].x =   0.0f; points[2].y =   1.0f; points[2].z =  0.0f;
	HC_Insert_Circle (&points[0], &points[1], &points[2]);
	points[0].x =   0.0f; points[0].y =  -0.3f; points[0].z =  0.0f;
	points[1].x =   0.3f; points[1].y =   0.0f; points[1].z =  0.0f;
	points[2].x =   0.0f; points[2].y =   0.3f; points[2].z =  0.0f;
	HC_Insert_Circle (&points[0], &points[1], &points[2]);
    }
    else if (letter == 'P') {
	points[0].x =  -1.0f; points[0].y =  -1.0f; points[0].z =  0.0f;
	points[1].x =  -1.0f; points[1].y =   1.0f; points[1].z =  0.0f;
	points[2].x =   1.0f; points[2].y =   1.0f; points[2].z =  0.0f;
	points[3].x =   1.0f; points[3].y =  -0.3f; points[3].z =  0.0f;
	points[4].x =  -0.3f; points[4].y =  -0.3f; points[4].z =  0.0f;
	points[5].x =  -0.3f; points[5].y =  -1.0f; points[5].z =  0.0f;
	points[6].x =  -1.0f; points[6].y =  -1.0f; points[6].z =  0.0f;
	HC_Insert_Polyline (7, points);
	points[0].x =   0.2f; points[0].y =  0.05f; points[0].z =  0.0f;
	points[1].x =   0.5f; points[1].y =  0.35f; points[1].z =  0.0f;
	points[2].x =   0.2f; points[2].y =  0.65f; points[2].z =  0.0f;
	HC_Insert_Circle (&points[0], &points[1], &points[2]);
    }
    else if (letter == 'S') {
	points[0].x =  -1.0f; points[0].y =  -1.0f; points[0].z =  0.0f;
	points[1].x =   1.0f; points[1].y =  -1.0f; points[1].z =  0.0f;
	points[2].x =   1.0f; points[2].y =   0.2f; points[2].z =  0.0f;
	points[3].x =  -0.3f; points[3].y =   0.2f; points[3].z =  0.0f;
	points[4].x =  -0.3f; points[4].y =   0.6f; points[4].z =  0.0f;
	points[5].x =   1.0f; points[5].y =   0.6f; points[5].z =  0.0f;
	points[6].x =   1.0f; points[6].y =   1.0f; points[6].z =  0.0f;
	points[7].x =  -1.0f; points[7].y =   1.0f; points[7].z =  0.0f;
	points[8].x =  -1.0f; points[8].y =  -0.2f; points[8].z =  0.0f;
	points[9].x =   0.3f; points[9].y =  -0.2f; points[9].z =  0.0f;
	points[10].x =  0.3f; points[10].y = -0.6f; points[10].z = 0.0f;
	points[11].x = -1.0f; points[11].y = -0.6f; points[11].z = 0.0f;
	points[12].x = -1.0f; points[12].y = -1.0f; points[12].z = 0.0f;
	HC_Insert_Polyline (13, points);
    }
    else if (letter == 'T') {
	points[0].x =  -0.35f; points[0].y =  -1.0f; points[0].z =  0.0f;
	points[1].x =  -0.35f; points[1].y =   0.3f; points[1].z =  0.0f;
	points[2].x =  -1.0f;  points[2].y =   0.3f; points[2].z =  0.0f;
	points[3].x =  -1.0f;  points[3].y =   1.0f; points[3].z =  0.0f;
	points[4].x =   1.0f;  points[4].y =   1.0f; points[4].z =  0.0f;
	points[5].x =   1.0f;  points[5].y =   0.3f; points[5].z =  0.0f;
	points[6].x =   0.35f; points[6].y =   0.3f; points[6].z =  0.0f;
	points[7].x =   0.35f; points[7].y =  -1.0f; points[7].z =  0.0f;
	points[8].x =  -0.35f; points[8].y =  -1.0f; points[8].z =  0.0f;
	HC_Insert_Polyline (9, points);
    }
    else if (letter == 'E') {
	points[0].x =  -1.0f; points[0].y =  -1.0f; points[0].z =  0.0f;
	points[1].x =  -1.0f; points[1].y =   1.0f; points[1].z =  0.0f;
	points[2].x =   1.0f; points[2].y =   1.0f; points[2].z =  0.0f;
	points[3].x =   1.0f; points[3].y =   0.6f; points[3].z =  0.0f;
	points[4].x =  -0.3f; points[4].y =   0.6f; points[4].z =  0.0f;
	points[5].x =  -0.3f; points[5].y =   0.2f; points[5].z =  0.0f;
	points[6].x =   1.0f; points[6].y =   0.2f; points[6].z =  0.0f;
	points[7].x =   1.0f; points[7].y =  -0.2f; points[7].z =  0.0f;
	points[8].x =  -0.3f; points[8].y =  -0.2f; points[8].z =  0.0f;
	points[9].x =  -0.3f; points[9].y =  -0.6f; points[9].z =  0.0f;
	points[10].x =  1.0f; points[10].y = -0.6f; points[10].z = 0.0f;
	points[11].x =  1.0f; points[11].y = -1.0f; points[11].z = 0.0f;
	points[12].x = -1.0f; points[12].y = -1.0f; points[12].z = 0.0f;
	HC_Insert_Polyline (13, points);
    }
    else if (letter == 'R') {
	points[0].x =  -1.0f; points[0].y =  -1.0f; points[0].z =  0.0f;
	points[1].x =  -1.0f; points[1].y =   1.0f; points[1].z =  0.0f;
	points[2].x =   1.0f; points[2].y =   1.0f; points[2].z =  0.0f;
	points[3].x =   1.0f; points[3].y =  -0.3f; points[3].z =  0.0f;
	points[4].x =   0.4f; points[4].y =  -0.3f; points[4].z =  0.0f;
	points[5].x =   1.0f; points[5].y =  -1.0f; points[5].z =  0.0f;
	points[6].x =   0.3f; points[6].y =  -1.0f; points[6].z =  0.0f;
	points[7].x =  -0.3f; points[7].y =  -0.3f; points[7].z =  0.0f;
	points[8].x =  -0.3f; points[8].y =  -1.0f; points[8].z =  0.0f;
	points[9].x =  -1.0f; points[9].y =  -1.0f; points[9].z =  0.0f;
	HC_Insert_Polyline (10, points);
	points[0].x =   0.2f; points[0].y =  0.05f; points[0].z =  0.0f;
	points[1].x =   0.5f; points[1].y =  0.35f; points[1].z =  0.0f;
	points[2].x =   0.2f; points[2].y =  0.65f; points[2].z =  0.0f;
	HC_Insert_Circle (&points[0], &points[1], &points[2]);
    }
    else if (letter == 'F') {
	points[0].x =  -1.0f; points[0].y =  -1.0f; points[0].z =  0.0f;
	points[1].x =  -1.0f; points[1].y =   1.0f; points[1].z =  0.0f;
	points[2].x =   1.0f; points[2].y =   1.0f; points[2].z =  0.0f;
	points[3].x =   1.0f; points[3].y =   0.6f; points[3].z =  0.0f;
	points[4].x =  -0.3f; points[4].y =   0.6f; points[4].z =  0.0f;
	points[5].x =  -0.3f; points[5].y =   0.2f; points[5].z =  0.0f;
	points[6].x =   1.0f; points[6].y =   0.2f; points[6].z =  0.0f;
	points[7].x =   1.0f; points[7].y =  -0.2f; points[7].z =  0.0f;
	points[8].x =  -0.3f; points[8].y =  -0.2f; points[8].z =  0.0f;
	points[9].x =  -0.3f; points[9].y =  -1.0f; points[9].z =  0.0f;
	points[10].x = -1.0f; points[10].y = -1.0f; points[10].z = 0.0f;
	HC_Insert_Polyline (11, points);
    }
    else
	printf ("Unexpected letter: %c\n", letter);
}


void unveil_letter (
    char		*segment) {
    int	i;

    for (i = 0; i < 9; i++) {
	HC_QRotate_Object (segment, 0.0, -10.0, 0.0);
	HC_Update_Display ();
    }
}


void tumble_letter (
    char		*segment,
    char		axis) {
    int	i;

    if (axis == 'x')
	for (i = 0; i < 9; i++) {
	    HC_QRotate_Object (segment, 40.0, 0.0, 0.0);
	    HC_Update_Display ();
	}
    else if (axis == 'y')
	for (i = 0; i < 9; i++) {
	    HC_QRotate_Object (segment, 0.0, 40.0, 0.0);
	    HC_Update_Display ();
	}
    else if (axis == 'z')
	for (i = 0; i < 9; i++) {
	    HC_QRotate_Object (segment, 0.0, 0.0, 40.0);
	    HC_Update_Display ();
	}
    else
	printf ("Unexpected axis: %c\n", axis);
}


void intro_screen (void) {
    HC_Open_Segment ("?draw/intro_screen");
	HC_Set_Camera_Projection ("perspective");
	HC_Zoom_Camera (0.85);
	HC_Set_Window_Frame ("off");
	HC_Set_Visibility ("faces = off, edges = on");
	HC_Set_Color_By_Index ("lines", RED);
	HC_Set_Color_By_Index ("edges", RED);
	HC_Set_Heuristics ("no hidden surfaces");

	/* spell out HOOPS */
	HC_Open_Segment ("hoops/H");
	    HC_Set_Window (-1.0, -0.6, 0.5, 0.9);
	    construct_letter ('H');
	HC_Close_Segment ();
	HC_Open_Segment ("hoops/O1");
	    HC_Set_Window (-0.6, -0.2, 0.5, 0.9);
	    construct_letter ('O');
	HC_Close_Segment ();
	HC_Open_Segment ("hoops/O2");
	    HC_Set_Window (-0.2, 0.2, 0.5, 0.9);
	    construct_letter ('O');
	HC_Close_Segment ();
	HC_Open_Segment ("hoops/P");
	    HC_Set_Window (0.2, 0.6, 0.5, 0.9);
	    construct_letter ('P');
	HC_Close_Segment ();
	HC_Open_Segment ("hoops/S");
	    HC_Set_Window (0.6, 1.0, 0.5, 0.9);
	    construct_letter ('S');
	HC_Close_Segment ();

	/* spell out PERF */
	HC_Open_Segment ("perf/P");
	    HC_Set_Window (-1.0, -0.5, -0.2, 0.2);
	    construct_letter ('P');
	HC_Close_Segment ();
	HC_Open_Segment ("perf/E");
	    HC_Set_Window (-0.5, 0.0, -0.2, 0.2);
	    construct_letter ('E');
	HC_Close_Segment ();
	HC_Open_Segment ("perf/R");
	    HC_Set_Window (0.0, 0.5, -0.2, 0.2);
	    construct_letter ('R');
	HC_Close_Segment ();
	HC_Open_Segment ("perf/F");
	    HC_Set_Window (0.5, 1.0, -0.2, 0.2);
	    construct_letter ('F');
	HC_Close_Segment ();

	/* spell out TEST */
	HC_Open_Segment ("test/T1");
	    HC_Set_Window (-1.0, -0.5, -0.9, -0.5);
	    construct_letter ('T');
	HC_Close_Segment ();
	HC_Open_Segment ("test/E");
	    HC_Set_Window (-0.5, 0.0, -0.9, -0.5);
	    construct_letter ('E');
	HC_Close_Segment ();
	HC_Open_Segment ("test/S");
	    HC_Set_Window (0.0, 0.5, -0.9, -0.5);
	    construct_letter ('S');
	HC_Close_Segment ();
	HC_Open_Segment ("test/T2");
	    HC_Set_Window (0.5, 1.0, -0.9, -0.5);
	    construct_letter ('T');
	HC_Close_Segment ();

	/* turn almost sideways to start */
	HC_Rotate_Object (0.0, 90.0, 0.0);
	HC_Update_Display ();
	HC_Get_Wakeup (0.5);

	/* reveal letters one at a time */
	unveil_letter ("hoops/H");
	unveil_letter ("hoops/O1");
	unveil_letter ("hoops/O2");
	unveil_letter ("hoops/P");
	unveil_letter ("hoops/S");

	unveil_letter ("perf/P");
	unveil_letter ("perf/E");
	unveil_letter ("perf/R");
	unveil_letter ("perf/F");

	unveil_letter ("test/T1");
	unveil_letter ("test/E");
	unveil_letter ("test/S");
	unveil_letter ("test/T2");
	HC_Get_Wakeup (0.5);

	tumble_letter ("?draw/intro_screen", 'x');
	HC_Get_Wakeup (0.5);
	tumble_letter ("?draw/intro_screen", 'y');
	HC_Get_Wakeup (0.5);
	tumble_letter ("?draw/intro_screen", 'z');
	HC_Get_Wakeup (0.5);
    HC_Close_Segment ();
    HC_Delete_Segment ("?draw/intro_screen");
}


void driver_info (void) {
    char	info[64], message[80];

    HC_Open_Segment ("?draw/info");
	HC_Set_Text_Font ("size = 0.05 sru");
	HC_Set_Color ("text = red");
	if (!HC_Show_Environment ("HOOPS_PICTURE", info))
	    HC_Show_Device_Info ("?picture", "driver type", info);
	strcpy (message, "driver = ");
	strcat (message, info);
	HC_Insert_Text (0.0, 0.8, 0.0, message);
	HC_Show_Device_Info ("?picture", "driver version", info);
	strcpy (message, "driver version = ");
	strcat (message, info);
	HC_Insert_Text (0.0, 0.4, 0.0, message);
	HC_Show_Device_Info ("?picture", "max pixels", info);
	strcpy (message, "max pixels = ");
	strcat (message, info);
	HC_Insert_Text (0.0, 0.0, 0.0, message);
	HC_Show_Device_Info ("?picture", "max colors", info);
	strcpy (message, "max colors = ");
	strcat (message, info);
	HC_Insert_Text (0.0, -0.4, 0.0, message);
	HC_Show_Device_Info ("?picture", "Z buffer depth", info);
	strcpy (message, "Z buffer depth = ");
	strcat (message, info);
	HC_Insert_Text (0.0, -0.8, 0.0, message);
    HC_Close_Segment ();
}


void identify_test (
    char	*segment) {

    HC_QUnSet_Color ("?buttons/*");
    HC_Open_Segment (segment);
	HC_Set_Color_By_Index ("windows", RED);
	HC_Set_Color_By_Index ("text", WHITE);
    HC_Close_Segment ();
    HC_Flush_Contents ("?draw", "geometry, heuristics");
    HC_Create_Segment ("?draw/have at least one segment");
    HC_Delete_Segment ("?draw/*");
    HC_QUnSet_Window_Frame ("?draw");
    HC_Create_Segment ("?include library/have at least one segment");
    HC_Delete_Segment ("?include library/*");
    HC_Flush_Contents ("?memory", "geometry");
    HC_Flush_Contents ("?time", "geometry");
}


void post_message (
    char	*message) {

    HC_Open_Segment ("?results");
	HC_Flush_Contents (".", "geometry");
	HC_Insert_Text (0.0, 0.0, 0.0, message);
    HC_Close_Segment ();
}


void post_memory (
    int		index) {
    long	allocated,
		in_use;
    char	string[256];

    HC_Show_Memory_Usage (&allocated, &in_use);
    results2[index] = (float)allocated / 1024.0f;
    results3[index] = (float)in_use / 1024.0f;
    HC_Open_Segment ("?memory");
	HC_Flush_Contents (".", "geometry");
	sprintf (string,
		 "%0.1f/%0.1f K",
		 results2[index],
		 results3[index]);
	HC_Insert_Text (0.0, 0.0, 0.0, string);
    HC_Close_Segment ();
}


void post_time (
    float	start_time,
    float	stop_time) {
    char	string[256];

    HC_Open_Segment ("?time");
	HC_Flush_Contents (".", "geometry");
	sprintf (string,
		 "%0.2f secs",
		 stop_time - start_time);
	HC_Insert_Text (0.0, 0.0, 0.0, string);
    HC_Close_Segment ();
}


int driver_has_a_keyboard_or_mouse (void) {
    char answer[256];

    HC_Show_Device_Info ("?picture", "keyboard", answer);
    if (strcmp (answer, "yes") == 0)
	return TRUE;
    else {
	HC_Show_Device_Info ("?picture", "locater", answer);
	if (strcmp (answer, "yes") == 0)
	    return TRUE;
	else
	    return FALSE;
    }
}


#define ROT_30Z		1
#define ROT_30Y		2
#define ROT_30Y_COLOR	3
#define TOGGLE_VIS	4

int get_run_count (
   int	       timing_method,
   char *      segment) {
   int	       count;
   float       start_time,
	       one_time,
	       stop_time;

    if (!driver_has_a_keyboard_or_mouse ())
	return 2;

    HC_Open_Segment (segment);
	HC_Show_Time (&start_time);
	switch (timing_method) {
	    case ROT_30Z: {
		HC_Rotate_Object (0.0, 0.0, 30.0);
		HC_Update_Display ();
		HC_Rotate_Object (0.0, 0.0, -30.0);
		HC_Update_Display ();
	    }   break;

	    case ROT_30Y: {
		HC_Rotate_Object (0.0, 30.0, 0.0);
		HC_Update_Display ();
		HC_Rotate_Object (0.0, -30.0, 0.0);
		HC_Update_Display ();
	    }   break;

	    case ROT_30Y_COLOR: {
		HC_Set_Color_By_Index ("faces", RED);
		HC_Set_Color_By_Index ("edges", BLUE);
		HC_Rotate_Object (0.0, 30.0, 0.0);
		HC_Update_Display ();
		HC_Set_Color_By_Index ("faces", BLUE);
		HC_Set_Color_By_Index ("edges", RED);
		HC_Rotate_Object (0.0, -30.0, 0.0);
		HC_Update_Display ();
	    }   break;

	    case TOGGLE_VIS:
	    default: {
		HC_Set_Visibility ("images = off, text = off");
		HC_Update_Display ();
		HC_Set_Visibility ("images = on, text = on");
		HC_Update_Display ();
		HC_Set_Visibility ("images = off, text = off");
		HC_Update_Display ();
		HC_Set_Visibility ("images = on, text = on");
		HC_Update_Display ();
	    }
	}
	HC_Show_Time (&stop_time);
    HC_Close_Segment ();

    one_time = (stop_time - start_time)/2.0f;
	
    if (one_time < 1E-5)
	return 5000;	
	
    count = (int)((float)seconds_per_test / one_time);
    if (count < 2)
	return 2;
    else
	return count;
}


void post_results (
    int		index,
    long	number,
    float	start_time,
    float       stop_time) {
    float	total_time;
    char	string[256];

    total_time = stop_time - start_time;
    if (total_time > 0.0f) {
	results1[index] = (float)number / total_time;
	sprintf (string, "%0.2f %s", results1[index], units[index]);
    }
    else {
	results1[index] = 0.0f;
	sprintf (string, "no results for %s", units[index]);
    }
    HC_Open_Segment ("?results");
	HC_Flush_Contents (".", "geometry");
	HC_Insert_Text (0.0, 0.0, 0.0, string);
    HC_Close_Segment ();
}


void test_polyline_2d (void) {
    int	i;
    int			desired_runs;
    float		x, inc,
			start_time,
			stop_time;
    Point		two_points[2];
    Point		three_points[3];
    Point		four_points[4];

    /* display which test is about to execute */
    identify_test ("?buttons/polyline_2d");
    post_message ("656 2D polylines per update");
    HC_Update_Display ();

    /* setup HOOPS database */
    two_points[0].z = 0.0f;
    two_points[1].z = 0.0f;
    three_points[0].z = 0.0f;
    three_points[1].z = 0.0f;
    three_points[2].z = 0.0f;
    four_points[0].z = 0.0f;
    four_points[1].z = 0.0f;
    four_points[2].z = 0.0f;
    four_points[3].z = 0.0f;
    i = 0;
    inc = 0.005f;
    HC_Open_Segment ("?draw/polyline_2d");
	HC_Set_Heuristics ("no hidden surfaces");
	for (x = -0.99f; x < 0.0; x += inc) {
	    two_points[0].x =  x;
	    two_points[0].y = -x;
	    two_points[1].x = -x - (2 * inc);
	    two_points[1].y = -x;

	    three_points[0].x = -x - inc;
	    three_points[0].y = -x;
	    three_points[1].x = -x;
	    three_points[1].y = -x;
	    three_points[2].x = -x;
	    three_points[2].y = 0.0f;

	    four_points[0].x = -x;
	    four_points[0].y = -inc;
	    four_points[1].x = -x;
	    four_points[1].y = x;
	    four_points[2].x = x;
	    four_points[2].y = x;
	    four_points[3].x = x;
	    four_points[3].y = -x - inc;

	    HC_Insert_Polyline (2, two_points);
	    HC_Insert_Polyline (3, three_points);
	    HC_Insert_Polyline (4, four_points);
	}
	HC_Update_Display ();

	/* see how many runs can fit in 30 seconds */
	desired_runs = get_run_count (ROT_30Z, "?draw/polyline_2d");

	/* execute the test */
	HC_Show_Time (&start_time);
	for (i = 0; i < desired_runs; i++) {
	    HC_Rotate_Object (0.0, 0.0, 30.0);
	    HC_Update_Display ();
	}
	HC_Show_Time (&stop_time);
    HC_Close_Segment ();

    /* display results of the test */
    post_memory (0);
    post_time (start_time, stop_time);
    post_results (0, desired_runs * 656L, start_time, stop_time);
}


void test_polyedge_3d (void) {
    int	i;
    int			desired_runs;
    float		start_time,
			stop_time;

    /* display which test is about to execute */
    identify_test ("?buttons/polyedge_3d");
    post_message ("3816 3D lines per update");
    HC_Update_Display ();

    /* setup HOOPS database */
    HC_Open_Segment ("?draw/polyedge_3d");
	HC_Read_Metafile ("petepart", ".", "");
	HC_Rotate_Object (-20.0, 0.0, 0.0);
	HC_Set_Camera_By_Volume ("perspective", -1.2, 1.2, -1.2, 1.2);
	HC_Set_Rendering_Options ("lighting interpolation = off");
	HC_Set_Heuristics ("no hidden surfaces");
	HC_Set_Visibility ("markers = off, faces = off, edges = on");
	HC_Set_Color_By_Index ("edges", BLACK);
	HC_Update_Display ();

	/* see how many runs can fit in 30 seconds */
	desired_runs = get_run_count (ROT_30Y_COLOR, "?draw/polyedge_3d");

	/* execute the test */
	HC_Show_Time (&start_time);
	for (i = 0; i < desired_runs; i++) {
	    HC_Set_Color_By_Index ("edges", i % 4);
	    HC_Rotate_Object (0.0, 30.0, 0.0);
	    HC_Update_Display ();
	}
	HC_Show_Time (&stop_time);
    HC_Close_Segment ();

    /* display results of the test */
    post_memory (1);
    post_time (start_time, stop_time);
    post_results (1, desired_runs * 3816L, start_time, stop_time);
}


void test_marker_2d (void) {
    int	i;
    int	j;
    float	x,
			y;
    int			desired_runs, num;
    float		size,
			start_time,
			stop_time;
    char		*symbol[41];

    /* display which test is about to execute */
    identify_test ("?buttons/marker_2d");
    post_message ("1476 (36 rows of 41) 2D markers per update");
    HC_Update_Display ();

    /* setup HOOPS database */
    symbol[0] = "()";
    symbol[1] = "(.)";
    symbol[2] = "(+)";
    symbol[3] = "(x)";
    symbol[4] = "(())";
    symbol[5] = "(*)";
    symbol[6] = ".";
    symbol[7] = "+";
    symbol[8] = "x";
    symbol[9] = "*";
    symbol[10] = "[]";
    symbol[11] = "[.]";
    symbol[12] = "[x]";
    symbol[13] = "[*]";
    symbol[14] = "<>";
    symbol[15] = "<.>";
    symbol[16] = "<+>";
    symbol[17] = "<*>";
    symbol[18] = "/\\";
    symbol[19] = "/.\\";
    symbol[20] = "/*\\";
    symbol[21] = "|>";
    symbol[22] = "|.>";
    symbol[23] = "|*>";
    symbol[24] = "<|";
    symbol[25] = "<.|";
    symbol[26] = "<*|";
    symbol[27] = "#";
    symbol[28] = "++";
    symbol[29] = "/ \\";
    symbol[30] = "/_\\";
    symbol[31] = "|";
    symbol[32] = "/";
    symbol[33] = "\\";
    symbol[34] = "/__\\";
    symbol[35] = "/_^_\\";
    symbol[36] = "Y";
    symbol[37] = "Z";
    symbol[38] = "\\/";
    symbol[39] = "\\./";
    symbol[40] = "\\*/";
    num = 0;
    HC_Open_Segment ("?draw/marker_2d");
	{
#	ifndef countof
#	    define countof(x) (sizeof(x) / sizeof(x[0]))
#	endif
	const char marker_pound[] = {100, 0, 0,   2, -38, 87, -38, -87, 2, 38, 87, 38, -87,
						     2, 87, -38, -87, -38, 2, 87, 38, -87, 38, 0};
	const char marker_wide_plus[] = {100, 0, 0,   13, 100, 25, 100, -25, 25, -25, 25, -100, -25, -100,
							     -25, -25, -100, -25, -100, 25, -25, 25, -25, 100,
							     25, 100, 25, 25, 100, 25, 0};
	const char marker_open_arrow[] = {100, 0, 0,   3, 83, -100, 0, 100, -83, -100, 0};
	const char marker_closed_arrow[] = {100, 0, 0,   4, 83, -100, 0, 100, -83, -100, 83, -100, 0};
	const char marker_vertical_bar[] = {100, 0, 0,   2, 0, 87, 0, -87, 0};
	const char marker_half_arrow_left[] = {100, 0, 0,   2, 100, 100, -87, -87, 0};
	const char marker_half_arrow_right[] = {100, 0, 0,   2, -100, 100, 87, -87, 0};
	const char marker_wide_arrow[] = {100, 0, 0,   4, 0, 100, -100, -100, 100, -100, 0, 100, 0};
	const char marker_double_arrow[] = {100, 0, 0,   8, -100, 0, 0, 0, 100, -100, -100, -100,
								0, 0, 100, 0, 0, 100, -100, 0, 0};
	const char marker_letter_y[] = {100, 0, 0,   2, -63, 87, 0, 0, 2, 0, 0, 63, 87, 2, 0, 0, 0, -87, 0};
	const char marker_letter_z[] = {100, 0, 0,   4, -63, 87, 63, 87, -63, -87, 63, -87, 0};

	HC_Define_Glyph("#", countof(marker_pound), marker_pound);
	HC_Define_Glyph("++", countof(marker_wide_plus), marker_wide_plus);
	HC_Define_Glyph("/ \\", countof(marker_open_arrow), marker_open_arrow);
	HC_Define_Glyph("/_\\", countof(marker_closed_arrow), marker_closed_arrow);
	HC_Define_Glyph("|", countof(marker_vertical_bar), marker_vertical_bar);
	HC_Define_Glyph("/", countof(marker_half_arrow_left), marker_half_arrow_left);
	HC_Define_Glyph("\\", countof(marker_half_arrow_right), marker_half_arrow_right);
	HC_Define_Glyph("/__\\", countof(marker_wide_arrow), marker_wide_arrow);
	HC_Define_Glyph("/_^_\\", countof(marker_double_arrow), marker_double_arrow);
	HC_Define_Glyph("y", countof(marker_letter_y), marker_letter_y);
	HC_Define_Glyph("z", countof(marker_letter_z), marker_letter_z);
	}
	HC_Set_Heuristics ("no hidden surfaces");
	x = -0.97f;
	for (i = 0; i < NUM_MARKERS; i++) {
	    size = 0.125f;
	    y = -0.95f;
	    for (j = 0; j < NUM_COLORS; j++) {
		HC_Open_Segment ("");
		    HC_Set_Marker_Symbol (symbol[i]);
		    HC_Insert_Marker ((double)x, (double)y, 0.0);
		    HC_Insert_Marker ((double)x, y + 0.475, 0.0);
		    HC_Insert_Marker ((double)x, y + 0.95, 0.0);
		    HC_Insert_Marker ((double)x, y + 1.425, 0.0);
		    num++;
		    HC_Set_Color_By_Index ("marker", i % 4);
		    HC_Set_Marker_Size (size);
		HC_Close_Segment ();
		size += 0.125f;
		y += (0.5f / (float)NUM_COLORS);
	    }
	    x += (2.0f / (float)NUM_MARKERS);
	}
	HC_Update_Display ();

	/* see how many runs can fit in 30 seconds */
	desired_runs = get_run_count (ROT_30Z, "?draw/marker_2d");

	/* execute the test */
	HC_Show_Time (&start_time);
	for (i = 0; i < desired_runs; i++) {
	    HC_Rotate_Object (0.0, 0.0, 30.0);
	    HC_Update_Display ();
	}
	HC_Show_Time (&stop_time);
    HC_Close_Segment ();

    /* display results of the test */
    post_memory (2);
    post_time (start_time, stop_time);
    post_results (2, desired_runs * 1476L, start_time, stop_time);
}


void test_marker_3d (void) {
    int	i;
    int			desired_runs;
    float		start_time,
			stop_time;

    /* display which test is about to execute */
    identify_test ("?buttons/marker_3d");
    post_message ("3817 3D markers per update");
    HC_Update_Display ();

    /* setup HOOPS database */
    HC_Open_Segment ("?draw/marker_3d");
	HC_Read_Metafile ("petepart", ".", "");
	HC_Rotate_Object (-20.0, 0.0, 0.0);
	HC_Set_Camera_By_Volume ("perspective", -1.2, 1.2, -1.2, 1.2);
	HC_Set_Rendering_Options ("lighting interpolation = off");
	HC_Set_Heuristics ("no hidden surfaces");
	HC_Set_Marker_Symbol (".");
	HC_Set_Marker_Size (0.0);
	HC_Set_Visibility ("markers = on, faces = off, edges = off");
	HC_Set_Color_By_Index ("markers", BLACK);
	HC_Update_Display ();

	/* see how many runs can fit in 30 seconds */
	desired_runs = get_run_count (ROT_30Y_COLOR, "?draw/marker_3d");

	/* execute the test */
	HC_Show_Time (&start_time);
	for (i = 0; i < desired_runs; i++) {
	    HC_Set_Color_By_Index ("marker", i % 4);
	    HC_Rotate_Object (0.0, 30.0, 0.0);
	    HC_Update_Display ();
	}
	HC_Show_Time (&stop_time);
    HC_Close_Segment ();

    /* display results of the test */
    post_memory (3);
    post_time (start_time, stop_time);
    post_results (3, desired_runs * 3817L, start_time, stop_time);
}


void draw_triangle (
    float	x1,
    float	y1,
    float	x2,
    float	y2,
    float	x3,
    float	y3) {
    Point	vector[4];

    vector[0].x = x1;  vector[0].y = y1;  vector[0].z = 0.0f;
    vector[1].x = x2;  vector[1].y = y2;  vector[1].z = 0.0f;
    vector[2].x = x3;  vector[2].y = y3;  vector[2].z = 0.0f;
    HC_Insert_Polygon (3, vector);
}


void draw_star (
    float		x,
    float		y,
    float		r1,
    float		r2) {
    Point	vector[12];
    int	i;

    for (i = 0; i <= S_NUMBER; i += 2) {
	vector[i].x = x + r1 * (float)sin (S_ANGLE * i);
	vector[i].y = y + r1 * (float)cos (S_ANGLE * i);
	vector[i].z = 0.0f;
    }
    for (i = 1; i <= S_NUMBER; i += 2) {
	vector[i].x = x + r2 * (float)sin (S_ANGLE * i);
	vector[i].y = y + r2 * (float)cos (S_ANGLE * i);
	vector[i].z = 0.0f;
    }
    HC_Insert_Polygon (S_NUMBER, vector);
}


void draw_shape (
    float		x,
    float		y) {
    Point		data[11];

    data[0].x  = x;
    data[0].y  = y;
    data[0].z  = 0.0f;
    data[1].x  = x + WIDTH/8.0f;
    data[1].y  = y + HEIGHT;
    data[1].z  = 0.0f;
    data[2].x  = x + WIDTH - WIDTH/8.0f;
    data[2].y  = y + HEIGHT;
    data[2].z  = 0.0f;
    data[3].x  = x + WIDTH;
    data[3].y  = y;
    data[3].z  = 0.0f;
    data[4].x  = x + WIDTH - WIDTH/3.0f;
    data[4].y  = y;
    data[4].z  = 0.0f;
    data[5].x  = x + WIDTH - WIDTH/3.0f;
    data[5].y  = y + HEIGHT/6.0f;
    data[5].z  = 0.0f;
    data[6].x  = x + WIDTH - WIDTH/9.0f;
    data[6].y  = y+ HEIGHT/6.0f;
    data[6].z  = 0.0f;
    data[7].x  = x + WIDTH/2.0f;
    data[7].y  = y + HEIGHT - HEIGHT/6.0f;
    data[7].z  = 0.0f;
    data[8].x  = x + WIDTH/9.0f;
    data[8].y  = y + HEIGHT/6.0f;
    data[8].z  = 0.0f;
    data[9].x  = x + WIDTH/3.0f;
    data[9].y  = y + HEIGHT/6.0f;
    data[9].z  = 0.0f;
    data[10].x = x+ WIDTH/3.0f;
    data[10].y = y;
    data[10].z = 0.0f;
    HC_Insert_Polygon (11, data);
}


void draw_circle (
    float	x,
    float	y,
    float	r) {
    Point	vector[3];

    vector[0].x = x + r; vector[0].y = y;     vector[0].z = 0.0f;
    vector[1].x = x;     vector[1].y = y + r; vector[1].z = 0.0f;
    vector[2].x = x - r; vector[2].y = y;     vector[2].z = 0.0f;
    HC_Insert_Circle (&vector[0], &vector[1], &vector[2]);
}


void draw_ellipse (
    float	x,
    float	y,
    float	r1,
    float	r2) {
    Point	vector[3];

    vector[0].x = x;      vector[0].y = y;      vector[0].z = 0.0f;
    vector[1].x = x + r1; vector[1].y = y;      vector[1].z = 0.0f;
    vector[2].x = x;      vector[2].y = y + r2; vector[2].z = 0.0f;
    HC_Insert_Ellipse (&vector[0], &vector[1], &vector[2]);
}


void test_polygon_2d (void) {
    int	i = 0;
    float	x, y;
    int			desired_runs;
    float		start_time,
			stop_time;

    /* display which test is about to execute */
    identify_test ("?buttons/polygon_2d");
    post_message ("238 (14 rows of 17) 2D polygons per update");
    HC_Update_Display ();

    /* setup HOOPS database */
    HC_Open_Segment ("?draw/polygon_2d");
	HC_Set_Heuristics ("no hidden surfaces, concave polygons");
	HC_Set_Camera_Projection ("perspective");
	HC_Set_Visibility ("faces = on, edges = off");
	i = 0;
	for (x = 0.9f; x > -1.2; x -= WIDTH / 2.0f) {
	    for (y = -0.9f; y < 0.8; y += HEIGHT / 2.0f) {
		HC_Open_Segment ("");
		    i++;
		    HC_Set_Color_By_Index ("polygons", i % 4);
		    switch (i % 5) {
			case 0: {
			    draw_triangle (x,	    y,
					   x + WIDTH/2, y + HEIGHT,
					   x + WIDTH,   y);
			}   break;

			case 1: {
			    draw_shape (x, y);
			}   break;

			case 2: {
			    draw_star (x + WIDTH/2.0f, y + HEIGHT/2.0f, 0.14f, 0.07f);
			}   break;

			case 3: {
			    draw_shape (x, y);
			}   break;

			case 4: {
			    draw_triangle (x,	    y,
					   x + WIDTH/2.0f, y + HEIGHT,
					   x + WIDTH,   y);
			}
		    }
		HC_Close_Segment ();
	    }
	}
	HC_Update_Display ();

	/* see how many runs can fit in 30 seconds */
	desired_runs = get_run_count (ROT_30Z, "?draw/polygon_2d");

	/* execute the test */
	HC_Show_Time (&start_time);
	for (i = 0; i < desired_runs; i++) {
	    HC_Rotate_Object (0.0, 0.0, 30.0);
	    HC_Update_Display ();
	}
	HC_Show_Time (&stop_time);
    HC_Close_Segment ();

    /* display results of the test */
    post_memory (4);
    post_time (start_time, stop_time);
    post_results (4, desired_runs * 238L, start_time, stop_time);
}


void test_ellipse_2d (void) {
    int	i = 0;
    float      x, y;
    int                 desired_runs;
    float               start_time,
			stop_time;

    /* display which test is about to execute */
    identify_test ("?buttons/ellipse_2d");
    post_message ("238 (14 rows of 17) 2D ellipses per update");
    HC_Update_Display ();

    /* setup HOOPS database */
    HC_Open_Segment ("?draw/ellipse_2d");
	HC_Set_Heuristics ("no hidden surfaces, no concave polygons");
	HC_Set_Camera_Projection ("perspective");
	HC_Set_Visibility ("faces = on, edges = off");
	i = 0;
	for (x = 0.9f; x > -1.2; x -= WIDTH / 2.0f) {
	    for (y = -0.95f; y < 0.8; y += HEIGHT / 2.0f) {
		HC_Open_Segment ("");
		    i++;
		    HC_Set_Color_By_Index ("polygons", i % 4);
		    switch (i % 3) {
			case 0: {
			    draw_ellipse (x + WIDTH/2.0f, y+HEIGHT/2.0f, 0.2f, 0.1f);
			}   break;

			case 1: {
			    draw_circle (x + 0.125f, y + 0.125f, 0.125f);
			}   break;

			case 2: {
			    draw_ellipse (x + WIDTH/2.0f, y+HEIGHT/2.0f, 0.1f, 0.2f);
			}   break;
		    }
		HC_Close_Segment ();
	    }
	}
	HC_Update_Display ();

	/* see how many runs can fit in 30 seconds */
	desired_runs = get_run_count (ROT_30Z, "?draw/ellipse_2d");

	/* execute the test */
	HC_Show_Time (&start_time);
	for (i = 0; i < desired_runs; i++) {
	    HC_Rotate_Object (0.0, 0.0, 30.0);
	    HC_Update_Display ();
	}
	HC_Show_Time (&stop_time);
    HC_Close_Segment ();

    /* display results of the test */
    post_memory (5);
    post_time (start_time, stop_time);
    post_results (5, desired_runs * 238L, start_time, stop_time);
}


void test_polygon_3d (void) {
    int	i = 0;
    int			desired_runs;
    float		start_time,
			stop_time;

    /* display which test is about to execute */
    identify_test ("?buttons/polygon_3d");
    post_message ("7200 (1800 * 4) 3D polygons per update");
    HC_Update_Display ();

    /* setup HOOPS database */
    HC_Open_Segment ("?draw/polygon_3d");
	HC_Set_Heuristics ("hidden surfaces");
	HC_Set_Camera_By_Volume ("perspective", -1.2, 1.2, -1.2, 1.2);
	HC_Set_Visibility ("faces = on, edges = on");
	HC_Open_Segment ("");
	    HC_Set_Color_By_Index ("faces", RED);
	    HC_Set_Color_By_Index ("edges", BLUE);
	    HC_Read_Metafile ("spring", ".", "");
	    HC_Translate_Object (-0.5, -0.5, 0.0);
	HC_Close_Segment ();
	HC_Open_Segment ("");
	    HC_Set_Color_By_Index ("faces", BLUE);
	    HC_Set_Color_By_Index ("edges", BLACK);
	    HC_Read_Metafile ("spring", ".", "");
	    HC_Translate_Object (-0.5, 0.5, 0.0);
	HC_Close_Segment ();
	HC_Open_Segment ("");
	    HC_Set_Color_By_Index ("faces", BLACK);
	    HC_Set_Color_By_Index ("edges", WHITE);
	    HC_Read_Metafile ("spring", ".", "");
	    HC_Translate_Object (0.5, -0.5, 0.0);
	HC_Close_Segment ();
	HC_Open_Segment ("");
	    HC_Set_Color_By_Index ("faces", GREEN);
	    HC_Set_Color_By_Index ("edges", RED);
	    HC_Read_Metafile ("spring", ".", "");
	    HC_Translate_Object (0.5, 0.5, 0.0);
	HC_Close_Segment ();
	HC_Update_Display ();

	/* see how many runs can fit in 30 seconds */
	desired_runs = get_run_count (ROT_30Z, "?draw/polygon_3d");

	/* execute the test */
	HC_Show_Time (&start_time);
	for (i = 0; i < desired_runs; i++) {
	    HC_Rotate_Object (0.0, 30.0, 0.0);
	    HC_Update_Display ();
	}
	HC_Show_Time (&stop_time);
    HC_Close_Segment ();

    /* display results of the test */
    post_memory (6);
    post_time (start_time, stop_time);
    post_results (6, desired_runs * 7200L, start_time, stop_time);
}


void test_polygon_3d_no_edge (void) {
    int	i = 0;
    int			desired_runs;
    float		start_time,
			stop_time;

    /* display which test is about to execute */
    identify_test ("?buttons/poly_no_edge");
    post_message ("7200 (1800 * 4) 3D edgeless polygons per update");
    HC_Update_Display ();

    /* setup HOOPS database */
    HC_Open_Segment ("?draw/poly_no_edge");
	HC_Set_Heuristics ("hidden surfaces");
	HC_Set_Camera_By_Volume ("perspective", -1.2, 1.2, -1.2, 1.2);
	HC_Set_Visibility ("faces = on, edges = off");
	HC_Open_Segment ("");
	    HC_Set_Color_By_Index ("faces", RED);
	    HC_Read_Metafile ("spring", ".", "");
	    HC_Translate_Object (-0.5, -0.5, 0.0);
	HC_Close_Segment ();
	HC_Open_Segment ("");
	    HC_Set_Color_By_Index ("faces", BLUE);
	    HC_Read_Metafile ("spring", ".", "");
	    HC_Translate_Object (-0.5, 0.5, 0.0);
	HC_Close_Segment ();
	HC_Open_Segment ("");
	    HC_Set_Color_By_Index ("faces", BLACK);
	    HC_Read_Metafile ("spring", ".", "");
	    HC_Translate_Object (0.5, -0.5, 0.0);
	HC_Close_Segment ();
	HC_Open_Segment ("");
	    HC_Set_Color_By_Index ("faces", GREEN);
	    HC_Read_Metafile ("spring", ".", "");
	    HC_Translate_Object (0.5, 0.5, 0.0);
	HC_Close_Segment ();
	HC_Update_Display ();

	/* see how many runs can fit in 30 seconds */
	desired_runs = get_run_count (ROT_30Y, "?draw/poly_no_edge");

	/* execute the test */
	HC_Show_Time (&start_time);
	for (i = 0; i < desired_runs; i++) {
	    HC_Rotate_Object (0.0, 30.0, 0.0);
	    HC_Update_Display ();
	}
	HC_Show_Time (&stop_time);
    HC_Close_Segment ();

    /* display results of the test */
    post_memory (7);
    post_time (start_time, stop_time);
    post_results (7, desired_runs * 7200L, start_time, stop_time);
}


void test_polygon_3d_flat (void) {
    int	i = 0;
    int			desired_runs;
    float		start_time,
			stop_time;

    /* display which test is about to execute */
    identify_test ("?buttons/poly_flat");
    post_message ("7200 (1800 * 4) 3D lit edgeless polygons per update");
    HC_Update_Display ();

    /* setup HOOPS database */
    HC_Open_Segment ("?draw/poly_flat");
	HC_Set_Heuristics ("hidden surfaces");
	HC_Set_Camera_By_Volume ("perspective", -1.2, 1.2, -1.2, 1.2);
	HC_Set_Visibility ("faces = on, edges = off");
	HC_Insert_Distant_Light (1.0, 1.0, -1.0);
	HC_Open_Segment ("");
	    HC_Set_Color_By_Index ("faces", RED);
	    HC_Read_Metafile ("spring", ".", "");
	    HC_Translate_Object (-0.5, -0.5, 0.0);
	HC_Close_Segment ();
	HC_Open_Segment ("");
	    HC_Set_Color_By_Index ("faces", BLUE);
	    HC_Read_Metafile ("spring", ".", "");
	    HC_Translate_Object (-0.5, 0.5, 0.0);
	HC_Close_Segment ();
	HC_Open_Segment ("");
	    HC_Set_Color_By_Index ("faces", BLACK);
	    HC_Read_Metafile ("spring", ".", "");
	    HC_Translate_Object (0.5, -0.5, 0.0);
	HC_Close_Segment ();
	HC_Open_Segment ("");
	    HC_Set_Color_By_Index ("faces", GREEN);
	    HC_Read_Metafile ("spring", ".", "");
	    HC_Translate_Object (0.5, 0.5, 0.0);
	HC_Close_Segment ();
	HC_Update_Display ();

	/* see how many runs can fit in 30 seconds */
	desired_runs = get_run_count (ROT_30Y, "?draw/poly_flat");

	/* execute the test */
	HC_Show_Time (&start_time);
	for (i = 0; i < desired_runs; i++) {
	    HC_Rotate_Object (0.0, 30.0, 0.0);
	    HC_Update_Display ();
	}
	HC_Show_Time (&stop_time);
    HC_Close_Segment ();

    /* display results of the test */
    post_memory (8);
    post_time (start_time, stop_time);
    post_results (8, desired_runs * 7200L, start_time, stop_time);
}


void test_text_2d (void) {
    int		k, desired_runs;
    float       j, i,
		start_time,
		stop_time;

    /* display which test is about to execute */
    identify_test ("?buttons/text_2d");
    post_message ("871 'hello world' strings per update");
    HC_Update_Display ();

    /* setup HOOPS database */
    HC_Open_Segment ("?draw/text_2d");
	HC_Set_Heuristics ("no hidden surfaces");
	HC_Set_Text_Font ("size = 12 pt");
	k = 0;
	for (i = -1.0f; i < 1.0; i += 0.03f)
	    for (j = -0.9f; j < 1.0; j += 0.15f) {
		HC_Open_Segment ("");
		    HC_Insert_Text ((double)j, (double)i, 0.0, "hello world");
		    HC_Set_Color_By_Index ("text", (k % 3) + 1);
		HC_Close_Segment ();
		k++;
	    }
	HC_Update_Display ();

	/* see how many runs can fit in 30 seconds */
	desired_runs = get_run_count (TOGGLE_VIS, "?draw/text_2d");

	/* execute the test */
	HC_Show_Time (&start_time);
	for (k = 0; k < desired_runs; k++) {
	    HC_Set_Visibility ("text = off");
	    HC_Update_Display ();
	    HC_Set_Visibility ("text = on");
	    HC_Update_Display ();
	}
	HC_Show_Time (&stop_time);
    HC_Close_Segment ();

    /* display results of the test */
    post_memory (9);
    post_time (start_time, stop_time);
    post_results (9, desired_runs * 871L, start_time, stop_time);
}


void test_text_3d (void) {
    float	i;
    int		desired_runs,
		j, k;
    float	start_time,
		stop_time;

    /* display which test is about to execute */
    identify_test ("?buttons/text_3d");
    post_message ("938 (67 rows of 14) 'hello world' strings per update");
    HC_Update_Display ();

    /* setup HOOPS database */
    HC_Open_Segment ("?draw/text_3d");
	HC_Set_Text_Font ("size = 12 pt");
	HC_Set_Heuristics ("hidden surfaces");
	HC_Set_Camera_Projection ("perspective");
	k = 0;
	for (i = 1.0f; i >= -1.0; i -= 0.03f) {
	    HC_Open_Segment ("");
		HC_Insert_Text (0.0, (double)i, -1.5,
				"hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world");
		HC_Set_Color_By_Index ("text", (k % 3) + 1);
	    HC_Close_Segment ();
	    k++;
	}
	HC_Update_Display ();

	/* see how many runs can fit in 30 seconds */
	desired_runs = get_run_count (TOGGLE_VIS, "?draw/text_3d");

	/* execute the test */
	HC_Show_Time (&start_time);
	for (j = 0; j < desired_runs; j++) {
	    HC_Translate_Object (0.0, 0.0, 0.5);
	    HC_Update_Display ();
	}
	HC_Show_Time (&stop_time);
    HC_Close_Segment ();

    /* display results of the test */
    post_memory (10);
    post_time (start_time, stop_time);
    post_results (10, desired_runs * 938L, start_time, stop_time);
}


void test_image (void) {
    float		start_time,
			stop_time,
			x,
			y;
    int			desired_runs, i, j;
    unsigned char	pixels[100][100];

    /* display which test is about to execute */
    identify_test ("?buttons/image");
    post_message ("64 (100 pixel x 100 pixel) 8 bit images per update");
    HC_Update_Display ();

    /* setup HOOPS database */
    HC_Open_Segment ("?include library/image");
	for (i = 0; i < 100; i++) {
	    for (j = 0; j < 25; j++)
		pixels[i][j] = BLACK;
	    for (j = 25; j < 50; j++)
		pixels[i][j] = RED;
	    for (j = 50; j < 75; j++)
		pixels[i][j] = GREEN;
	    for (j = 75; j < 100; j++)
		pixels[i][j] = BLUE;
	}
	HC_Insert_Image (0.0, 0.0, 0.0,
			 "mapped 8", 100, 100, (void *)pixels);
    HC_Close_Segment ();
    HC_Open_Segment ("?draw/image");
	HC_Set_Heuristics ("no hidden surfaces");
	for (x = -0.875f; x < 0.9; x += 0.25f)
	    for (y = -0.875f; y < 0.9; y += 0.25f) {
		HC_Open_Segment ("");
		    HC_Include_Segment ("?include library/image");
		    HC_Translate_Object ((double)x, (double)y, 0.0);
		HC_Close_Segment ();
	    }
	HC_Update_Display ();

	/* see how many runs can fit in 30 seconds */
	desired_runs = get_run_count (ROT_30Z, "?draw/image");

	/* execute the test */
	HC_Show_Time (&start_time);
	for (i = 0; i < desired_runs; i++) {
	    HC_Rotate_Object (0.0, 0.0, 30.0);
	    HC_Update_Display ();
	}
	HC_Show_Time (&stop_time);
    HC_Close_Segment ();

    /* display results of the test */
    post_memory (11);
    post_time (start_time, stop_time);
    post_results (11, desired_runs * 640000L, start_time, stop_time);
}


void test_rgb_image (void) {
    float		start_time,
			stop_time,
			x,
			y;
    int			desired_runs, i, j;
    unsigned char	pixels[100][100][3];

    /* display which test is about to execute */
    identify_test ("?buttons/rgb_image");
    post_message ("64 (100 pixel x 100 pixel) 24 bit images per update");
    HC_Update_Display ();

    /* setup HOOPS database */
    HC_Open_Segment ("?include library/image");
	for (i = 0; i < 100; i++) {
	    for (j = 0; j < 34; j++) {
		pixels[i][j][0] = 255;
		pixels[i][j][1] = 0;
		pixels[i][j][2] = 0;
	    }
	    for (j = 34; j < 67; j++) {
		pixels[i][j][0] = 0;
		pixels[i][j][1] = 255;
		pixels[i][j][2] = 0;
	    }
	    for (j = 67; j < 100; j++) {
		pixels[i][j][0] = 0;
		pixels[i][j][1] = 0;
		pixels[i][j][2] = 255;
	    }
	}
	HC_Insert_Image (0.0, 0.0, 0.0,
			 "rgb", 100, 100, (void *)pixels);
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/rgb_image");
	HC_Set_Heuristics ("no hidden surfaces");
	for (x = -0.875f; x < 0.9; x += 0.25f)
	    for (y = -0.875f; y < 0.9; y += 0.25f) {
		HC_Open_Segment ("");
		    HC_Include_Segment ("?include library/image");
		    HC_Translate_Object ((double)x, (double)y, 0.0);
		HC_Close_Segment ();
	    }
	HC_Update_Display ();

	/* see how many runs can fit in 30 seconds */
	desired_runs = get_run_count (ROT_30Z, "?draw/rgb_image");

	/* execute the test */
	HC_Show_Time (&start_time);
	for (i = 0; i < desired_runs; i++) {
	    HC_Rotate_Object (0.0, 0.0, 30.0);
	    HC_Update_Display ();
	}
	HC_Show_Time (&stop_time);
    HC_Close_Segment ();

    /* display results of the test */
    post_memory (12);
    post_time (start_time, stop_time);
    post_results (12, desired_runs * 640000L, start_time, stop_time);
}


void test_shell (void) {
    int	i;
    int			desired_runs;
    float		start_time,
			stop_time;

    /* display which test is about to execute */
    identify_test ("?buttons/shell");
    post_message ("130 unlit shells per update");
    HC_Update_Display ();

    /* setup HOOPS database */
    HC_Open_Segment ("?draw/shell");
	HC_Read_Metafile ("petepart", ".", "");
	HC_Rotate_Object (-20.0, 0.0, 0.0);
	HC_Set_Camera_By_Volume ("perspective", -1.2, 1.2, -1.2, 1.2);
	HC_Set_Rendering_Options ("lighting interpolation = off");
	HC_Set_Visibility ("markers = off, faces = on, edges = off");
	HC_Set_Heuristics ("hidden surfaces");
	HC_Set_Color_By_Index ("faces", BLACK);
	HC_Update_Display ();

	/* see how many runs can fit in 30 seconds */
	desired_runs = get_run_count (ROT_30Y_COLOR, "?draw/shell");

	/* execute the test */
	HC_Show_Time (&start_time);
	for (i = 0; i < desired_runs; i++) {
	    HC_Set_Color_By_Index ("faces", (i % 3) + 1);
	    HC_Rotate_Object (0.0, 30.0, 0.0);
	    HC_Update_Display ();
	}
	HC_Show_Time (&stop_time);
    HC_Close_Segment ();

    /* display results of the test */
    post_memory (13);
    post_time (start_time, stop_time);
    post_results (13, desired_runs * 130L, start_time, stop_time);
}


void test_shell_flat (void) {
    float	start_time,
		stop_time;
    int		desired_runs,
		i;

    /* display which test is about to execute */
    identify_test ("?buttons/shell_flat");
    post_message ("130 flat lit shells per update");
    HC_Update_Display ();

    /* setup HOOPS database */
    HC_Open_Segment ("?draw/shell_flat");
	HC_Read_Metafile ("petepart", ".", "");
	HC_Rotate_Object (-20.0, 0.0, 0.0);
	HC_Set_Camera_By_Volume ("perspective", -1.2, 1.2, -1.2, 1.2);
	HC_Set_Rendering_Options ("lighting interpolation = off");
	HC_Insert_Distant_Light (1.0, 1.0, -1.0);
	HC_Set_Visibility ("markers = off, faces = on, edges = off");
	HC_Set_Heuristics ("hidden surfaces");
	HC_Set_Color_By_Index ("faces", BLACK);
	HC_Update_Display ();

	/* see how many runs can fit in 30 seconds */
	desired_runs = get_run_count (ROT_30Y_COLOR, "?draw/shell_flat");

	/* execute the test */
	HC_Show_Time (&start_time);
	for (i = 0; i < desired_runs; i++) {
	    HC_Set_Color_By_Index ("faces", (i % 3) + 1);
	    HC_Rotate_Object (0.0, 30.0, 0.0);
	    HC_Update_Display ();
	}
	HC_Show_Time (&stop_time);
    HC_Close_Segment ();

    /* display results of the test */
    post_memory (14);
    post_time (start_time, stop_time);
    post_results (14, desired_runs * 130L, start_time, stop_time);
}


void test_shell_gouraud (void) {
    float	start_time,
		stop_time;
    int		desired_runs,
		i;

    /* display which test is about to execute */
    identify_test ("?buttons/shell_gouraud");
    post_message ("130 Gouraud lit shells per update");
    HC_Update_Display ();

    /* setup HOOPS database */
    HC_Open_Segment ("?draw/shell_gouraud");
	HC_Read_Metafile ("petepart", ".", "");
	HC_Rotate_Object (-20.0, 0.0, 0.0);
	HC_Set_Camera_By_Volume ("perspective", -1.2, 1.2, -1.2, 1.2);
	HC_Set_Visibility ("markers = off, faces = on, edges = off");
	HC_Insert_Distant_Light (1.0, 1.0, -1.0);
	HC_Set_Rendering_Options ("lighting interpolation");
	HC_Set_Heuristics ("hidden surfaces");
	HC_Set_Color_By_Index ("faces", BLACK);
	HC_Update_Display ();

	/* see how many runs can fit in 30 seconds */
	desired_runs = get_run_count (ROT_30Y_COLOR, "?draw/shell_gouraud");

	/* execute the test */
	HC_Show_Time (&start_time);
	for (i = 0; i < desired_runs; i++) {
	    HC_Set_Color_By_Index ("faces", (i % 3) + 1);
	    HC_Rotate_Object (0.0, 30.0, 0.0);
	    HC_Update_Display ();
	}
	HC_Show_Time (&stop_time);
    HC_Close_Segment ();

    /* display results of the test */
    post_memory (15);
    post_time (start_time, stop_time);
    post_results (15, desired_runs * 130L, start_time, stop_time);
}


void write_results (void) {
    FILE	*result_file;
    char	answer[256];
    char	file_name[32];
    int		i;

    identify_test ("?buttons/write_results");
    HC_Update_Display ();

    HC_Show_System_Info ("hoops version", answer);
    strcpy (file_name, "results.");
    file_name[8] = answer[0];
    file_name[9] = answer[2];
    file_name[10] = answer[3];
    file_name[11] = '\0';

    result_file = fopen (file_name, "w");
#	ifndef __DATE__
#	   define __DATE__ "today"
#	endif
	fprintf (result_file, "date:             %s\n\n", __DATE__);

	fprintf (result_file, "program:          perftest\n");
	fprintf (result_file, "program version:  %s\n\n", "$Revision: 1.7 $");

	/* HC_Show_System_Info ("hoops version", answer); */
	fprintf (result_file, "HOOPS version:    %s\n", answer);

	if (!HC_Show_Environment ("HOOPS_PICTURE", answer))
	    HC_Show_Device_Info ("?picture", "driver type", answer);
	fprintf (result_file, "driver:           %s\n", answer);

	HC_Show_Device_Info ("?picture", "driver version", answer);
	fprintf (result_file, "driver version:   %s\n", answer);

	HC_Show_Device_Info ("?picture", "pixels", answer);
	fprintf (result_file, "number of pixels: %s\n", answer);

	HC_Show_Device_Info ("?picture", "colors", answer);
	fprintf (result_file, "number of colors: %s\n\n", answer);

	HC_QShow_One_Net_Driver_Option ("?picture", "double-buffering", answer);
	fprintf (result_file, "double buffering: %s\n\n", answer);

	HC_QShow_One_Net_Heuristic ("?picture", "polygon handedness", answer);
	fprintf (result_file, "polygon culling:  %s\n\n", answer);

	HC_QShow_One_Net_Rendering_Opti ("?picture", "hsr algorithm", answer);
	fprintf (result_file, "hsr algorithm:    %s\n\n", answer);

	for (i = 0; i < NUM_RESULTS; i++) {
	    if (results1[i] > 0)
		fprintf (result_file, "%2d. %0.2f %s (%0.1f K allocated / %0.1f K in use)\n",
			 i + 1, results1[i], units[i], results2[i], results3[i]);
	    else
		fprintf (result_file, "%2d.\n", i + 1);
	}
    fclose (result_file);

    sprintf (answer, "results written to file: %s", file_name);
    post_message (answer);
}


void display_results (void) {
    char	string[256];
    int		i;
    float	size, x, y, max1, max2, xfrac, yfrac;

    identify_test ("?buttons/display_results");
    HC_Update_Display ();

    HC_Open_Segment ("?draw/words");
	HC_Set_Heuristics ("no hidden surfaces");
	HC_Set_Text_Font ("size = 0.02 sru, no size tolerance");
	HC_Open_Segment ("label");
	    HC_Set_Text_Alignment (">");
	    HC_Set_Color_By_Index ("text", BLACK);
	HC_Close_Segment ();
	HC_Open_Segment ("info");
	    HC_Set_Text_Alignment ("<");
	    HC_Set_Color_By_Index ("text", RED);
	HC_Close_Segment ();
	HC_Open_Segment ("data");
	    HC_Set_Text_Alignment (">");
	    HC_Set_Color_By_Index ("text", RED);
	HC_Close_Segment ();
	HC_Open_Segment ("unit");
	    HC_Set_Text_Alignment ("<");
	    HC_Set_Color_By_Index ("text", BLUE);
	HC_Close_Segment ();
	HC_Open_Segment ("allocated");
	    HC_Set_Text_Alignment (">");
	    HC_Set_Color_By_Index ("text", GREEN);
	HC_Close_Segment ();
	HC_Open_Segment ("in use");
	    HC_Set_Text_Alignment (">");
	    HC_Set_Color_By_Index ("text", RED);
	HC_Close_Segment ();

	size = (0.95f - (-0.95f)) / (float)(NUM_RESULTS + 9);
	y = 0.90f;

	HC_QInsert_Text ("label", -0.01, (double)y, 0.0, "date:");
	strcpy (string, __DATE__);
	HC_QInsert_Text ("info", 0.01, (double)y, 0.0, string);
	y -= size;

	if (!HC_Show_Environment ("HOOPS_PICTURE", string))
	    HC_Show_Device_Info ("?picture", "driver type", string);
	HC_QInsert_Text ("label", -0.01, (double)y, 0.0, "driver:");
	HC_QInsert_Text ("info", 0.01, (double)y, 0.0, string);
	y -= size;

	HC_Show_Device_Info ("?picture", "driver version", string);
	HC_QInsert_Text ("label", -0.01, (double)y, 0.0, "driver version:");
	HC_QInsert_Text ("info", 0.01, (double)y, 0.0, string);
	y -= size;

	HC_Show_Device_Info ("?picture", "pixels", string);
	HC_QInsert_Text ("label", -0.01, (double)y, 0.0, "number of pixels:");
	HC_QInsert_Text ("info", 0.01, (double)y, 0.0, string);
	y -= size;

	HC_Show_Device_Info ("?picture", "colors", string);
	HC_QInsert_Text ("label", -0.01, (double)y, 0.0, "number of colors:");
	HC_QInsert_Text ("info", 0.01, (double)y, 0.0, string);
	y -= size;

	HC_QShow_One_Net_Driver_Option ("?picture", "double-buffering", string);
	HC_QInsert_Text ("label", -0.01, (double)y, 0.0, "double buffering:");
	HC_QInsert_Text ("info", 0.01, (double)y, 0.0, string);
	y -= size;

	HC_QShow_One_Net_Heuristic ("?picture", "polygon handedness", string);
	HC_QInsert_Text ("label", -0.01, (double)y, 0.0, "polygon culling:");
	HC_QInsert_Text ("info", 0.01, (double)y, 0.0, string);
	y -= size;

	HC_QShow_One_Net_Rendering_Opti ("?picture", "hsr algorithm", string);
	HC_QInsert_Text ("label", -0.01, (double)y, 0.0, "hsr algorithm:");
	HC_QInsert_Text ("info", 0.01, (double)y, 0.0, string);
	y -= size;
	y -= size;

	max1 = -1.0f;
	for (i = 0; i < NUM_RESULTS; i++)
	    if (max1 < results1[i])
		max1 = results1[i];
	sprintf (string, "%0.2f", max1);
	HC_Compute_Text_Extent ("?draw/words", string, &xfrac, &yfrac);
	max1 = 2.0f * xfrac;

	max2 = -1.0f;
	for (i = 0; i < NUM_RESULTS; i++)
	    if (max2 < results3[i])
		max2 = results3[i];
	sprintf (string, "%0.2f", max2);
	HC_Compute_Text_Extent ("?draw/words", string, &xfrac, &yfrac);
	max2 = 2.0f * xfrac;

	for (i = 0; i < NUM_RESULTS; i++) {
	    x = -0.9f;
	    sprintf (string, "%d.", i + 1);
	    HC_QInsert_Text ("label", (double)x, (double)y, 0.0, string);

	    if (results1[i] > 0.0f) {
		x = x + max1 + 0.01f;
		sprintf (string, "%0.2f", results1[i]);
		HC_QInsert_Text ("data", (double)x, (double)y, 0.0, string);

		x += 0.01f;
		sprintf (string, "%s", units[i]);
		HC_QInsert_Text ("unit", (double)x, (double)y, 0.0, string);

		x = 0.9f - max2 - 0.01f;
		sprintf (string, "%0.1f", results2[i]);
		HC_QInsert_Text ("allocated", (double)x, (double)y, 0.0, string);

		x = 0.9f;
		sprintf (string, "%0.1f", results3[i]);
		HC_QInsert_Text ("in use", (double)x, (double)y, 0.0, string);
	    }

	    y -= size;
	}
    HC_Close_Segment ();

    post_message ("results = red, units = blue, allocated K = green, in use K = red");
}


void test_all (void) {
    identify_test ("?buttons/all");
    HC_Update_Display ();

    test_polyline_2d ();
    test_polyedge_3d ();
    test_marker_2d ();
    test_marker_3d ();
    test_polygon_2d ();
    test_ellipse_2d ();
    test_polygon_3d ();
    test_polygon_3d_no_edge ();
    test_polygon_3d_flat ();
    test_text_2d ();
    test_text_3d ();
    test_image ();
    test_rgb_image ();
    test_shell ();
    test_shell_flat ();
    test_shell_gouraud ();

    write_results ();
    display_results ();
}


void toggle_double_buffer (void) {
    char	value[64];

    identify_test ("?buttons/double_buffer");
    HC_QUnSet_One_Color ("?buttons/double_buffer", "windows");
    HC_QUnSet_One_Color ("?buttons/double_buffer", "text");
    HC_QShow_One_Net_Driver_Option ("?picture", "double-buffering", value);
    if (strcmp (value, "on") == 0) {
	HC_QSet_Driver_Options ("?picture", "no double-buffering");
	HC_QSet_Window_Pattern ("?buttons/double_buffer", "//");
    }
    else {
	HC_QSet_Driver_Options ("?picture", "double-buffering");
	HC_QSet_Window_Pattern ("?buttons/double_buffer", "solid");
    }
    HC_Update_Display ();

    HC_Open_Segment ("?draw/text output");
	HC_Set_Text_Font ("size = 0.2 oru");
	HC_Set_Heuristics ("no hidden surfaces");
	HC_Insert_Text (0.0, 0.33, 0.0, "double-buffering");
	HC_Insert_Text (0.0, 0.0, 0.0, "is now");
	HC_Open_Segment ("");
	    HC_Set_Color_By_Index ("text", RED);
	    if (strcmp (value, "on") == 0)
		HC_Insert_Text (0.0, -0.33, 0.0, "OFF");
	    else
		HC_Insert_Text (0.0, -0.33, 0.0, "ON");
	HC_Close_Segment ();
    HC_Close_Segment ();

    post_message ("toggled double buffering");
}


void toggle_culling (void) {
    char	value[64];

    identify_test ("?buttons/culling");
    HC_QUnSet_One_Color ("?buttons/culling", "windows");
    HC_QUnSet_One_Color ("?buttons/culling", "text");
    HC_QShow_One_Net_Heuristic ("?picture", "polygon handedness", value);
    if (strcmp (value, "right") == 0) {
	HC_QSet_Heuristics ("?picture", "no polygon handedness ");
	HC_QSet_Window_Pattern ("?buttons/culling", "//");
    }
    else {
	HC_QSet_Heuristics ("?picture", "polygon handedness = right");
	HC_QSet_Window_Pattern ("?buttons/culling", "solid");
    }
    HC_Update_Display ();

    HC_Open_Segment ("?draw/text output");
	HC_Set_Text_Font ("size = 0.2 oru");
	HC_Set_Heuristics ("no hidden surfaces");
	HC_Insert_Text (0.0, 0.33, 0.0, "CULLING");
	HC_Insert_Text (0.0, 0.0, 0.0, "is now");
	HC_Open_Segment ("");
	    HC_Set_Color_By_Index ("text", RED);
	    if (strcmp (value, "right") == 0)
		HC_Insert_Text (0.0, -0.33, 0.0, "OFF");
	    else
		HC_Insert_Text (0.0, -0.33, 0.0, "ON");
	HC_Close_Segment ();
    HC_Close_Segment ();

    post_message ("toggled culling");
}


void toggle_hsr (void) {
    char	value[64];

    HC_QSet_Color ("?buttons/*", "windows = white, text = black");

    HC_QShow_One_Net_Rendering_Opti ("?picture", "hsr algorithm", value);
    if (strcmp (value, "software z buffer") == 0) {
	HC_QSet_Rendering_Options ("?picture",
				   "hsr algorithm = hardware z buffer");
	HC_QSet_Window_Pattern ("?buttons/hsr", "//");
    }
    else {
	HC_QSet_Rendering_Options ("?picture",
				   "hsr algorithm = software z buffer");
	HC_QSet_Window_Pattern ("?buttons/hsr", "solid");
    }
    HC_Delete_Segment ("?draw/*");
    HC_QUnSet_Window_Frame ("?draw");
    HC_Create_Segment ("?include library/have at least one segment");
    HC_Delete_Segment ("?include library/*");
    HC_Update_Display ();

    HC_Open_Segment ("?draw/text output");
	HC_Set_Text_Font ("size = 0.2 oru");
	HC_Set_Heuristics ("no hidden surfaces");
	HC_Insert_Text (0.0, 0.6, 0.0, "software");
	HC_Insert_Text (0.0, 0.2, 0.0, "Z buffering");
	HC_Insert_Text (0.0, -0.2, 0.0, "is now");
	HC_Open_Segment ("");
	    HC_Set_Color ("text = red");
	    if (strcmp (value, "software z buffer") == 0)
		HC_Insert_Text (0.0, -0.6, 0.0, "OFF");
	    else
		HC_Insert_Text (0.0, -0.6, 0.0, "ON");
	HC_Close_Segment ();
    HC_Close_Segment ();

    post_message ("toggled hidden surface removal algorithm");
}


void run_tests_based_on_user_input (void) {
    int		test_number,
		previous_test_number;
    char	selection[256];
    int		keep_testing;
    char	event[256];

    HC_Enable_Button_Events ("?picture", "anything");
    HC_Enable_Selection_Events ("?picture", "?picture");

    test_number = 0;
    keep_testing = TRUE;
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
	    if (strcmp (selection, "all") == 0)
		test_number = 1;
	    else if (strcmp (selection, "polyline_2d") == 0)
		test_number = 2;
	    else if (strcmp (selection, "polyedge_3d") == 0)
		test_number = 3;
	    else if (strcmp (selection, "marker_2d") == 0)
		test_number = 4;
	    else if (strcmp (selection, "marker_3d") == 0)
		test_number = 5;
	    else if (strcmp (selection, "polygon_2d") == 0)
		test_number = 6;
	    else if (strcmp (selection, "ellipse_2d") == 0)
		test_number = 7;
	    else if (strcmp (selection, "polygon_3d") == 0)
		test_number = 8;
	    else if (strcmp (selection, "poly_no_edge") == 0)
		test_number = 9;
	    else if (strcmp (selection, "poly_flat") == 0)
		test_number = 10;
	    else if (strcmp (selection, "text_2d") == 0)
		test_number = 11;
	    else if (strcmp (selection, "text_3d") == 0)
		test_number = 12;
	    else if (strcmp (selection, "image") == 0)
		test_number = 13;
	    else if (strcmp (selection, "rgb_image") == 0)
		test_number = 14;
	    else if (strcmp (selection, "shell") == 0)
		test_number = 15;
	    else if (strcmp (selection, "shell_flat") == 0)
		test_number = 16;
	    else if (strcmp (selection, "shell_gouraud") == 0)
		test_number = 17;
	    else if (strcmp (selection, "write_results") == 0)
		test_number = 18;
	    else if (strcmp (selection, "display_results") == 0)
		test_number = 19;
	    else if (strcmp (selection, "quit") == 0)
		test_number = 20;
	    else if (strcmp (selection, "reset") == 0)
		test_number = 21;
	    else if (strcmp (selection, "double_buffer") == 0)
		test_number = 22;
	    else if (strcmp (selection, "culling") == 0)
		test_number = 23;
	    else if (strcmp (selection, "hsr") == 0)
		test_number = 24;
	    else
		test_number++;
	}
	else if (strcmp (event, "button") == 0) {
	    HC_Show_Button (selection);
	    if (strcmp (selection, "a") == 0)
		test_number = 1;
	    else if (strcmp (selection, "q") == 0)
		test_number = 20;
	    else
		test_number++;
	}
	else if (strcmp (event, "none") == 0)
	    /* driver got killed by the system */
	    HC_Exit_Program ();
	else
	    /* unexpected special event */
	    test_number = 20;

	/*
	 * run the desired test based on how
	 * test number was set above
	 */
	switch (test_number) {
	    case 1: {
		test_all ();
	    }   break;

	    case 2: {
		test_polyline_2d ();
	    }   break;

	    case 3: {
		test_polyedge_3d ();
	    }   break;

	    case 4: {
		test_marker_2d ();
	    }   break;

	    case 5: {
		test_marker_3d ();
	    }   break;

	    case 6: {
		test_polygon_2d ();
	    }   break;

	    case 7: {
		test_ellipse_2d ();
	    }   break;

	    case 8: {
		test_polygon_3d ();
	    }   break;

	    case 9: {
		test_polygon_3d_no_edge ();
	    }   break;

	    case 10: {
		test_polygon_3d_flat ();
	    }   break;

	    case 11: {
		test_text_2d ();
	    }   break;

	    case 12: {
		test_text_3d ();
	    }   break;

	    case 13: {
		test_image ();
	    }   break;

	    case 14: {
		test_rgb_image ();
	    }   break;

	    case 15: {
		test_shell ();
	    }   break;

	    case 16: {
		test_shell_flat ();
	    }   break;

	    case 17: {
		test_shell_gouraud();
	    }   break;

	    case 18: {
		write_results ();
	    }   break;

	    case 19: {
		display_results ();
	    }   break;

	    case 20:
	    default: {
		keep_testing = FALSE;
	    }   break;

	    case 21: {
		HC_Disable_Button_Events ("?picture", "anything");
		HC_Disable_Selection_Events ("?picture", "?picture");

		HC_Reset_System ();

		init_results ();
		setup_window_structure ();
		test_number = 0;
		HC_Enable_Button_Events ("?picture", "anything");
		HC_Enable_Selection_Events ("?picture", "?picture");
	    }   break;

	    case 22: {
		test_number = previous_test_number - 1;
		toggle_double_buffer ();
		init_results ();
	    }   break;

	    case 23: {
		test_number = previous_test_number - 1;
		toggle_culling ();
		init_results ();
	    }   break;

	    case 24: {
		test_number = previous_test_number - 1;
		toggle_hsr ();
		init_results ();
	    }
	}
    }

    HC_Disable_Button_Events ("?picture", "anything");
    HC_Disable_Selection_Events ("?picture", "?picture");
    HC_Exit_Program ();
}


void run_tests_once (void) {
    test_all ();
    HC_Exit_Program ();
}


int main (
    int		argc,
    char	**argv) {

    /* see how long tests should run */
    if ( (argc >= 2) && (strcmp (argv[1], "N")) )
		seconds_per_test = atoi (argv[1]);
    else
		seconds_per_test = 10;

    /* setup menus / output areas */
    init_results ();
    setup_window_structure ();

    /* have some fun, can avoid by invoking perftest N */
    if ((argc == 2) && (!strcmp (argv[1], "N")))
		intro_screen ();

    /* show configuration information */
    driver_info ();

    /* run the tests */
    if ((driver_has_a_keyboard_or_mouse ()) && (argc != 3) )
		run_tests_based_on_user_input ();
	else if (argc == 3){
		if (!strcmp (argv[2], "s"))
		run_tests_once();
	}
    else
		run_tests_once ();
    return 0;
}
