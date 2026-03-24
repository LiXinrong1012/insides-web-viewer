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
 * $Id: attrtest.c,v 1.4 2010-10-26 21:29:09 jason Exp $
 */

#include "hc.h"
#include "hc_standalone.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

#ifndef TRUE
#  define TRUE -1
#endif

#ifndef FALSE
#  define FALSE 0
#endif

#define NUM_RESULTS 14

typedef struct {
    float x, y, z;
} Point;

static Point results[16];
static float results_max;
    static char font[] = {
/*      general header          */
                3,  50,  30,  30,

/*      capital H               */
                72,
/*          header              */
                30,  0, 0,  0, 100,
/*          drawing             */
                2,  0, 0, 0, 100,
                2,  30, 0,   30, 100,
                2,  -15, 50,  30, 50,
                2,  -15, 40,  30, 40,
                0,

/*      capital O               */
                79,
/*          header              */
                30,  0, 0,  0, 100,
/*          drawing             */
                2,  0, 100,     30, 100,
                2,  0, 50,   30, 50,
                2,  0, 50,  0, 100,
                2,  30, 50,  30, 100,
                0,

/*      capital P               */
                80,
/*          header              */
                30,  0, 0,  0, 100,
/*          drawing             */
                2,  0, 0,    0, 100,
                2,  30, 50,   30, 100,
                2,  0, 100,    30, 100,
                2,  0, 50,    30, 50,
                0,

/*      capital S               */
                83,
/*          header              */
                30,  0, 0,  0, 100,
/*          drawing             */
                2,  0, 100,    30, 100,
                2,  0, 50,     30, 50,
                2,  0, 0,   30, 0,
                2,  0, 100,    0, 50,
                2,  30, 50,    30, 0,
                0,
};

void init_results (void) {
    int i;

    for (i = 0; i < (NUM_RESULTS + 2); i++) {
	results[i].x = (float)i;
	results[i].y = 0.0f;
	results[i].z = 0.0f;
    }
    results[0].x = results[1].x;
    results[NUM_RESULTS + 1].x = results[NUM_RESULTS].x;
    /* fudged so the polygon has at least some height */
    results[0].y = results[NUM_RESULTS + 1].y = -0.01f;
    results_max = -1.0f;
}

void setup_window_structure (void) {
    HC_Open_Segment ("?picture");
	HC_Clear_Display ();
	HC_Print_Version ();
	HC_Set_Camera_Projection ("stretched");
	HC_Set_Text_Font ("size = 0.01 sru");
	HC_Set_Color ("windows = white, text = black");
	HC_Set_Selectability ("off");
	HC_Set_Heuristics ("related selection limit = 0");
	HC_Set_Driver_Options ("no double-buffering");

	HC_Open_Segment ("title");
	    HC_Set_Text_Font ("size = 0.04 sru");
	    HC_Set_Window (-1.0, 1.0, 0.9, 1.0);
	    HC_Set_Heuristics ("no clipping, no hidden surfaces");
	    HC_Insert_Text (0.0, 0.0, 0.0, "Attributes Test");
	    HC_Open_Segment ("");
		HC_Set_Text_Font ("size = 0.01 sru");
		HC_Set_Text_Alignment ("<");
		HC_Insert_Text (-1.0, 0.0, 0.0, "Tech Soft Graphics Development");
	    HC_Close_Segment ();
	    HC_Open_Segment ("");
		HC_Set_Text_Font ("size = 0.01 sru");
		HC_Set_Text_Alignment (">");
		HC_Insert_Text (1.0, 0.0, 0.0, "$Revision: 1.4 $");
	    HC_Close_Segment ();
	HC_Close_Segment ();
	HC_Open_Segment ("draw");
	    HC_Set_Window (-1.0, 0.8, -0.9, 0.9);
	    HC_Open_Segment ("draw/text");
		HC_Set_Text_Font ("size = 0.02 sru");
		HC_Set_Window (-1.0, 1.0, 0.8, 1.0);
		HC_Insert_Text (0.0, 0.0, 0.0,
				"This test displays 6 windows for each geometry.");
	    HC_Close_Segment ();
	    HC_Open_Segment ("draw/picture1");
	      HC_Set_Window (-1.0, 1.0, 0.0, 0.8);
              HC_Insert_Text (0.0, 0.7, 0.0, "LIBRARY SEGMENT");
              HC_Insert_Line (0.0, 0.3, 0.0, -0.3, -0.3, 0.0);
              HC_Insert_Line (0.0, 0.3, 0.0, 0.3, -0.3, 0.0);
              HC_Open_Segment ("A");
                HC_Insert_Marker (0.0, 0.3, 0.0);
	        HC_Insert_Text (0.1, 0.3, 0.0, "A:  no geometry, attributes:  blue, etc.");
	        HC_Set_Text_Alignment ("<V");
              HC_Close_Segment ();
              HC_Open_Segment ("B");
                HC_Insert_Marker (-0.3, -0.3, 0.0);
	        HC_Insert_Text (-0.3, -0.5, 0.0, "B:  geometry, attributes:  magenta, etc.");
              HC_Close_Segment ();
              HC_Open_Segment ("C");
                HC_Insert_Marker (0.3, -0.3, 0.0);
	        HC_Insert_Text (0.3, -0.5, 0.0, "C:  geometry, no attributes");
              HC_Close_Segment ();
            HC_Close_Segment ();
	    HC_Open_Segment ("draw/picture2");
	      HC_Set_Window (-1.0, 1.0, -1.0, 0.0);
              HC_Open_Segment("draw/text/upper left");
	        HC_Set_Window (-1.0, -0.33, 0.0, 1.0);
                HC_Insert_Text (0.0, 0.3, 0.0, "UPPER LEFT WINDOW");
                HC_Insert_Text (0.0, 0.0, 0.0, "This segment's attributes are set locally.");
              HC_Close_Segment ();
              HC_Open_Segment("draw/text/upper middle");
	        HC_Set_Window (-0.33, 0.33, 0.0, 1.0);
                HC_Insert_Text (0.0, 0.3, 0.0, "UPPER MIDDLE WINDOW");
                HC_Insert_Text (0.0, 0.0, 0.0, "This segment's attributes are set");
                HC_Insert_Text (0.0, -0.2, 0.0, "using A as a style segment.");
              HC_Close_Segment ();
              HC_Open_Segment("draw/text/upper right");
	        HC_Set_Window (0.33, 1.0, 0.0, 1.0);
                HC_Insert_Text (0.0, 0.3, 0.0, "UPPER RIGHT WINDOW");
                HC_Insert_Text (0.0, 0.0, 0.0, "This segment's attributes are set");
                HC_Insert_Text (0.0, -0.2, 0.0, "using A as an include segment.");
              HC_Close_Segment ();
              HC_Open_Segment("draw/text/lower left");
	        HC_Set_Window (-1.0, -0.33, -1.0, 0.0);
                HC_Insert_Text (0.0, 0.3, 0.0, "LOWER LEFT WINDOW");
                HC_Insert_Text (0.0, 0.0, 0.0, "This segment's attributes are inherited");
                HC_Insert_Text (0.0, -0.2, 0.0, "from the parent segment.");
              HC_Close_Segment ();
              HC_Open_Segment("draw/text/lower middle");
	        HC_Set_Window (-0.33, 0.33, -1.0, 0.0);
                HC_Insert_Text (0.0, 0.3, 0.0, "LOWER MIDDLE WINDOW");
                HC_Insert_Text (0.0, 0.0, 0.0, "This segment's attributes are set");
                HC_Insert_Text (0.0, -0.2, 0.0, "using B as an include segment.");
              HC_Close_Segment ();
              HC_Open_Segment("draw/text/lower right");
	        HC_Set_Window (0.33, 1.0, -1.0, 0.0);
                HC_Insert_Text (0.0, 0.3, 0.0, "LOWER RIGHT WINDOW");
                HC_Insert_Text (0.0, 0.0, 0.0, "This segment's attributes are set");
                HC_Insert_Text (0.0, -0.2, 0.0, "using C as an include segment.");
              HC_Close_Segment ();
            HC_Close_Segment ();
	HC_Close_Segment ();

	HC_Open_Segment ("buttons");
	    HC_Set_Window (0.8, 1.0, -0.9, 0.9);
	    HC_Set_Heuristics ("no clipping, no hidden surfaces");
	    HC_Open_Segment ("line");
		HC_Set_Window (-1.0, 1.0, 0.88, 1.0);
		HC_Insert_Text (0.0, 0.0, 0.0, "line");
		HC_Set_Selectability ("windows = on");
	    HC_Close_Segment ();
	    HC_Open_Segment ("polygon");
		HC_Set_Window (-1.0, 1.0, 0.76, 0.88);
		HC_Insert_Text (0.0, 0.0, 0.0, "polygon");
		HC_Set_Selectability ("windows = on");
	    HC_Close_Segment ();
	    HC_Open_Segment ("circle");
		HC_Set_Window (-1.0, 1.0, 0.64, 0.76);
		HC_Insert_Text (0.0, 0.0, 0.0, "circle");
		HC_Set_Selectability ("windows = on");
	    HC_Close_Segment ();
	    HC_Open_Segment ("ellipse");
		HC_Set_Window (-1.0, 1.0, 0.52, 0.64);
		HC_Insert_Text (0.0, 0.0, 0.0, "ellipse");
		HC_Set_Selectability ("windows = on");
	    HC_Close_Segment ();
	    HC_Open_Segment ("mesh");
		HC_Set_Window (-1.0, 1.0, 0.40, 0.52);
		HC_Insert_Text (0.0, 0.0, 0.0, "mesh");
		HC_Set_Selectability ("windows = on");
	    HC_Close_Segment ();
	    HC_Open_Segment ("shell");
		HC_Set_Window (-1.0, 1.0, 0.28, 0.40);
		HC_Insert_Text (0.0, 0.0, 0.0, "shell");
		HC_Set_Selectability ("windows = on");
	    HC_Close_Segment ();
	    HC_Open_Segment ("polyline");
		HC_Set_Window (-1.0, 1.0, 0.16, 0.28);
		HC_Insert_Text (0.0, 0.0, 0.0, "polyline");
		HC_Set_Selectability ("windows = on");
	    HC_Close_Segment ();
	    HC_Open_Segment ("cutting plane");
		HC_Set_Window (-1.0, 1.0, 0.04, 0.16);
		HC_Insert_Text (0.0, 0.0, 0.0, "cutting plane");
		HC_Set_Selectability ("windows = on");
	    HC_Close_Segment ();
	    HC_Open_Segment ("grid");
		HC_Set_Window (-1.0, 1.0, -0.08, 0.04);
		HC_Insert_Text (0.0, 0.0, 0.0, "grid");
		HC_Set_Selectability ("windows = on");
	    HC_Close_Segment ();
	    HC_Open_Segment ("image");
		HC_Set_Window (-1.0, 1.0, -0.20, -0.08);
		HC_Insert_Text (0.0, 0.0, 0.0, "image");
		HC_Set_Selectability ("windows = on");
	    HC_Close_Segment ();
	    HC_Open_Segment ("ink");
		HC_Set_Window (-1.0, 1.0, -0.32, -0.20);
		HC_Insert_Text (0.0, 0.0, 0.0, "ink");
		HC_Set_Selectability ("windows = on");
	    HC_Close_Segment ();
	    HC_Open_Segment ("marker");
		HC_Set_Window (-1.0, 1.0, -0.44, -0.32);
		HC_Insert_Text (0.0, 0.0, 0.0, "marker");
		HC_Set_Selectability ("windows = on");
	    HC_Close_Segment ();
	    HC_Open_Segment ("text");
		HC_Set_Window (-1.0, 1.0, -0.56, -0.44);
		HC_Insert_Text (0.0, 0.0, 0.0, "text");
		HC_Set_Selectability ("windows = on");
	    HC_Close_Segment ();
	    HC_Open_Segment ("font");
		HC_Set_Window (-1.0, 1.0, -0.68, -0.56);
		HC_Insert_Text (0.0, 0.0, 0.0, "font");
		HC_Set_Selectability ("windows = on");
	    HC_Close_Segment ();
	    HC_Open_Segment ("quit");
		HC_Set_Window (-1.0, 1.0, -0.88, -0.68);
		HC_Insert_Text (0.0, 0.0, 0.0, "QUIT");
		HC_Set_Selectability ("windows = on");
	    HC_Close_Segment ();
	    HC_Open_Segment ("reset");
		HC_Set_Window (-1.0, 1.0, -1.0, -0.88);
		HC_Insert_Text (0.0, 0.0, 0.0, "RESET");
		HC_Set_Selectability ("windows = on");
	    HC_Close_Segment ();
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

    HC_Define_Alias ("?title", "?picture/title");
    HC_Define_Alias ("?draw", "?picture/draw");
    HC_Define_Alias ("?buttons", "?picture/buttons");
    HC_Define_Alias ("?memory", "?picture/memory");
    HC_Define_Alias ("?results", "?picture/results");
    HC_Define_Alias ("?time", "?picture/time");

    HC_Update_Display ();
}

void identify_test (
    char	*segment) {

    HC_Define_System_Options ("no message limit");
    HC_QSet_Color ("?buttons/*", "windows = white, text = black");
    HC_QSet_Color ("?draw", "markers = black");
    HC_QSet_Color (segment, "windows = red, text = white");
    HC_Delete_Segment ("?draw/*");
    HC_QUnSet_Face_Pattern ("?draw");
    HC_QUnSet_Marker_Size ("?draw");
    HC_QUnSet_Text_Alignment ("?draw");
    HC_QUnSet_Text_Font ("?draw");
    HC_QUnSet_Text_Path ("?draw");
    HC_QUnSet_Text_Spacing ("?draw");
    HC_QUnSet_Window_Frame ("?draw");
    HC_QUnSet_Camera ("?draw");
    HC_Create_Segment ("?include library/have at least one segment");
    HC_Delete_Segment ("?include library/*");
    HC_Create_Segment ("?style library/have at least one segment");
    HC_Delete_Segment ("?style library/*");
}

void post_memory (void) {
    long	allocated,
		in_use;
    char	string[256];

    HC_Show_Memory_Usage (&allocated, &in_use);
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

    HC_Open_Segment ("?results");
	HC_Flush_Contents (".", "geometry");
	HC_Insert_Text (0.0, 0.25, 0.0, message);
    HC_Close_Segment ();
}

void test_circle (void)  {
    float		start_time,
			stop_time,
			circle[3][3],
			circle2[3][3];

    circle[0][0] = -0.5f; circle[0][1] =  0.0f; circle[0][2] =  0.0f;
    circle[1][0] =  0.0f; circle[1][1] =  0.5f; circle[1][2] =  0.0f;
    circle[2][0] =  0.0f; circle[2][1] =  0.0f; circle[2][2] =  0.0f;

    circle2[0][0] =  0.0f; circle2[0][1] =  0.0f; circle2[0][2] =  0.0f;
    circle2[1][0] =  0.0f; circle2[1][1] =  0.75f; circle2[1][2] =  0.0f;
    circle2[2][0] =  0.75f; circle2[2][1] =  0.0f; circle2[2][2] =  0.0f;

    identify_test ("?buttons/circle");
    HC_Update_Display ();

    HC_Show_Time (&start_time);

    HC_Open_Segment ("?include library/line");
	HC_Set_Color ("faces = light blue, edges = navy blue");
        HC_Set_Edge_Weight (7.0);
        HC_Set_Edge_Pattern ("....");
        HC_Set_Face_Pattern ("solid");

      HC_Open_Segment ("?include library/line/geom1");
	  HC_Insert_Circle (circle[0], circle[1], circle[2]);
	  HC_Set_Color ("faces = magenta, edges = violet");
          HC_Set_Edge_Weight (5.0);
          HC_Set_Edge_Pattern ("-.-.");
          HC_Set_Face_Pattern ("##");
      HC_Close_Segment ();

      HC_Open_Segment ("?include library/line/geom2");
	  HC_Insert_Circle (circle2[0], circle2[1], circle2[2]);
      HC_Close_Segment ();

    HC_Close_Segment ();   /* library/line */

    HC_Open_Segment ("?draw");

	HC_Set_Color ("faces = red, text = black, edges = cyan");
	HC_Set_Edge_Weight (1.0);
	HC_Set_Visibility ("edges = on, markers = off, cutting planes = off");
	HC_Set_Face_Pattern ("==");
	HC_Set_Heuristics ("no hidden surfaces");

	HC_Open_Segment ("?draw/local ");
	  HC_Set_Window (-1.0, -0.33, 0.0, 1.0);
	  HC_Insert_Circle (circle[0], circle[1], circle[2]);
	  HC_Set_Color ("faces = green, edges = dark green");
          HC_Set_Edge_Weight (2.0);
          HC_Set_Edge_Pattern ("-- --");
          HC_Set_Face_Pattern ("//");
          HC_Insert_Text (0.0, -0.85, 0.0, "green, center, face = //, edge = dk green, -- --");
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/style");
	  HC_Set_Window (-0.33, 0.33, 0.0, 1.0);
	  HC_Insert_Circle (circle[0], circle[1], circle[2]);
          HC_Style_Segment ("?include library/line");
          HC_Insert_Text (0.0, -0.85, 0.0, "blue, center, face = solid, edge = dk blue, ....");
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/include");
	  HC_Set_Window (0.33, 1.0, 0.0, 1.0);
          HC_Include_Segment ("?include library/line");
          HC_Insert_Text (0.0, -0.85, 0.0, "magenta, center, face = #, edge = violet, -.-.");
          HC_Insert_Text (0.0, -0.95, 0.0, "lg blue, right, face = solid, edge = dk blue, ....");
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/parent");
	  HC_Set_Window (-1.0, -0.33, -1.0, 0.0);
	  HC_Insert_Circle (circle[0], circle[1], circle[2]);
	  HC_Insert_Text (0.0, -0.85, 0.0, "red, center, face = ==, edge = cyan, -...");
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/include2");
	  HC_Set_Window (-0.33, 0.33, -1.0, 0.0);
          HC_Include_Segment ("?include library/line/geom1");
          HC_Insert_Text (0.0, -0.85, 0.0, "magenta, center, face = #, edge = violet, -.-.");
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/include3");
	  HC_Set_Window (0.33, 1.0, -1.0, 0.0);
          HC_Include_Segment ("?include library/line/geom2");
          HC_Insert_Text (0.0, -0.85, 0.0, "lg red, right, face = ==, edge = cyan, -...");
        HC_Close_Segment ();

    HC_Close_Segment ();

    HC_Update_Display ();
    HC_Show_Time (&stop_time);

    post_memory ();
    post_results ("attributes from local, style, include, parent");
    post_time (3, start_time, stop_time);
}

void test_mesh (void) {
    float	start_time,
		stop_time;
    Point	mpts[9],
		mpts2[9];


   mpts[0].x = -1.0f; mpts[0].y =  1.0f; mpts[0].z =  0.0f;
   mpts[1].x =  0.0f; mpts[1].y =  1.0f; mpts[1].z =  0.0f;
   mpts[2].x =  1.0f; mpts[2].y =  1.0f; mpts[2].z =  0.0f;
   mpts[3].x = -1.0f; mpts[3].y =  0.0f; mpts[3].z =  0.0f;
   mpts[4].x =  0.0f; mpts[4].y =  0.0f; mpts[4].z =  1.0f;
   mpts[5].x =  1.0f; mpts[5].y =  0.0f; mpts[5].z =  0.0f;
   mpts[6].x = -1.0f; mpts[6].y = -1.0f; mpts[6].z =  0.0f;
   mpts[7].x =  0.0f; mpts[7].y = -1.0f; mpts[7].z =  0.0f;
   mpts[8].x =  1.0f; mpts[8].y = -1.0f; mpts[8].z =  0.0f;

   mpts2[0].x =  1.5f; mpts2[0].y =  1.5f; mpts2[0].z =  0.0f;
   mpts2[1].x =  1.0f; mpts2[1].y =  1.5f; mpts2[1].z =  0.0f;
   mpts2[2].x =  0.5f; mpts2[2].y =  1.5f; mpts2[2].z =  0.0f;
   mpts2[3].x =  1.5f; mpts2[3].y =  1.0f; mpts2[3].z =  0.0f;
   mpts2[4].x =  1.0f; mpts2[4].y =  1.0f; mpts2[4].z =  1.0f;
   mpts2[5].x =  0.5f; mpts2[5].y =  1.0f; mpts2[5].z =  0.0f;
   mpts2[6].x =  1.5f; mpts2[6].y =  0.5f; mpts2[6].z =  0.0f;
   mpts2[7].x =  1.0f; mpts2[7].y =  0.5f; mpts2[7].z =  0.0f;
   mpts2[8].x =  0.5f; mpts2[8].y =  0.5f; mpts2[8].z =  0.0f;

    identify_test ("?buttons/mesh");
    HC_Update_Display ();

    HC_Show_Time (&start_time);

    HC_Open_Segment ("?include library/line");
        HC_Set_Color ("faces = light blue, edges = navy blue");
        HC_Set_Edge_Weight (7.0);
        HC_Set_Edge_Pattern ("....");
        HC_Set_Face_Pattern ("solid");

      HC_Open_Segment ("?include library/line/geom1");
	  HC_Insert_Mesh (3, 3, mpts);
          HC_Set_Color ("faces = magenta, edges = violet");
          HC_Set_Edge_Weight (5.0);
          HC_Set_Edge_Pattern ("-.-.");
          HC_Set_Face_Pattern ("##");
      HC_Close_Segment ();

      HC_Open_Segment ("?include library/line/geom2");
         HC_Insert_Mesh (3, 3, mpts2);
      HC_Close_Segment ();

    HC_Close_Segment ();   /* library/line */

    HC_Open_Segment ("?draw");
      HC_Set_Heuristics ("hidden surfaces");
      HC_Set_Rendering_Options ("hsr algorithm = painters");
      HC_Set_Visibility ("edges = on, markers = on");

        HC_Insert_Distant_Light (1.0, 1.0, -1.0);
        HC_Set_Camera_Position (0.0, 0.0, -10.0);
        HC_Set_Color ("faces = red, text = black, edges = cyan");
        HC_Set_Edge_Weight (1.0);
        HC_Set_Face_Pattern ("==");

	HC_Open_Segment ("?draw/local ");
	  HC_Set_Window (-1.0, -0.33, 0.0, 1.0);
          HC_Insert_Mesh (3, 3, mpts);
          HC_Set_Color ("faces = green, edges = dark green");
          HC_Set_Edge_Weight (2.0);
          HC_Set_Edge_Pattern ("-- --");
          HC_Set_Face_Pattern ("//");
	  HC_Open_Segment ("");
            HC_Set_Camera_Projection ("orthographic");
            HC_Insert_Text (0.0, -0.85, 0.0, "lg green, center, face = //, edge = dk green, -- --");
          HC_Close_Segment ();
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/style");
	  HC_Set_Window (-0.33, 0.33, 0.0, 1.0);
          HC_Insert_Mesh (3, 3, mpts);
          HC_Style_Segment ("?include library/line");
	  HC_Open_Segment ("");
            HC_Set_Camera_Projection ("orthographic");
            HC_Insert_Text (0.0, -0.85, 0.0, "lg blue, center, face = solid, edge = dk blue, ....");
          HC_Close_Segment ();
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/include");
	  HC_Set_Window (0.33, 1.0, 0.0, 1.0);
          HC_Include_Segment ("?include library/line");
	  HC_Open_Segment ("");
            HC_Set_Camera_Projection ("orthographic");
            HC_Insert_Text (0.0, -0.85, 0.0, "lg magenta, center, face = #, edge = violet, -.-.");
            HC_Insert_Text (0.0, -0.95, 0.0, "sm blue, right, face = solid, edge = dk blue, ....");
          HC_Close_Segment ();
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/parent");
	  HC_Set_Window (-1.0, -0.33, -1.0, 0.0);
          HC_Insert_Mesh (3, 3, mpts);
	  HC_Open_Segment ("");
            HC_Set_Camera_Projection ("orthographic");
            HC_Insert_Text (0.0, -0.85, 0.0, "lg red, center, face = ==, edge = cyan, -...");
          HC_Close_Segment ();
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/include2");
	  HC_Set_Window (-0.33, 0.33, -1.0, 0.0);
          HC_Include_Segment ("?include library/line/geom1");
	  HC_Open_Segment ("");
            HC_Set_Camera_Projection ("orthographic");
            HC_Insert_Text (0.0, -0.85, 0.0, "lg magenta, center, face = #, edge = violet, -.-.");
          HC_Close_Segment ();
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/include3");
	  HC_Set_Window (0.33, 1.0, -1.0, 0.0);
          HC_Include_Segment ("?include library/line/geom2");
	  HC_Open_Segment ("");
            HC_Set_Camera_Projection ("orthographic");
            HC_Insert_Text (0.0, -0.85, 0.0, "sm red, right, face = ==, edge = cyan, -...");
          HC_Close_Segment ();
        HC_Close_Segment ();

    HC_Close_Segment ();

    HC_Update_Display ();
    HC_Show_Time (&stop_time);

    post_memory ();
    post_results ("attributes from local, style, include, parent");
    post_time (3, start_time, stop_time);
}

void test_shell (void) {
    float	start_time,
		stop_time;
    Point	spts[9],
		spts2[9];
    int		facelist[32];

    spts[0].x = -1.0f; spts[0].y =  1.0f; spts[0].z =  0.0f;
    spts[1].x =  0.0f; spts[1].y =  1.0f; spts[1].z =  0.0f;
    spts[2].x =  1.0f; spts[2].y =  1.0f; spts[2].z =  0.0f;
    spts[3].x = -1.0f; spts[3].y =  0.0f; spts[3].z =  0.0f;
    spts[4].x =  0.0f; spts[4].y =  0.0f; spts[4].z =  1.0f;
    spts[5].x =  1.0f; spts[5].y =  0.0f; spts[5].z =  0.0f;
    spts[6].x = -1.0f; spts[6].y = -1.0f; spts[6].z =  0.0f;
    spts[7].x =  0.0f; spts[7].y = -1.0f; spts[7].z =  0.0f;
    spts[8].x =  1.0f; spts[8].y = -1.0f; spts[8].z =  0.0f;

    spts2[0].x =  1.5f; spts2[0].y =  1.5f; spts2[0].z =  0.0f;
    spts2[1].x =  1.0f; spts2[1].y =  1.5f; spts2[1].z =  0.0f;
    spts2[2].x =  0.5f; spts2[2].y =  1.5f; spts2[2].z =  0.0f;
    spts2[3].x =  1.5f; spts2[3].y =  1.0f; spts2[3].z =  0.0f;
    spts2[4].x =  1.0f; spts2[4].y =  1.0f; spts2[4].z =  1.0f;
    spts2[5].x =  0.5f; spts2[5].y =  1.0f; spts2[5].z =  0.0f;
    spts2[6].x =  1.5f; spts2[6].y =  0.5f; spts2[6].z =  0.0f;
    spts2[7].x =  1.0f; spts2[7].y =  0.5f; spts2[7].z =  0.0f;
    spts2[8].x =  0.5f; spts2[8].y =  0.5f; spts2[8].z =  0.0f;

    facelist[0]  = 3; facelist[1]  = 0; facelist[2]  = 1; facelist[3] = 4;
    facelist[4]  = 3; facelist[5]  = 1; facelist[6]  = 2; facelist[7] = 4;
    facelist[8]  = 3; facelist[9]  = 2; facelist[10] = 5; facelist[11] = 4;
    facelist[12] = 3; facelist[13] = 5; facelist[14] = 8; facelist[15] = 4;
    facelist[16] = 3; facelist[17] = 8; facelist[18] = 7; facelist[19] = 4;
    facelist[20] = 3; facelist[21] = 7; facelist[22] = 6; facelist[23] = 4;
    facelist[24] = 3; facelist[25] = 6; facelist[26] = 3; facelist[27] = 4;
    facelist[28] = 3; facelist[29] = 3; facelist[30] = 0; facelist[31] = 4;

    identify_test ("?buttons/shell");
    HC_Update_Display ();

    HC_Show_Time (&start_time);

    HC_Open_Segment ("?include library/line");
        HC_Set_Color ("faces = light blue, edges = navy blue");
        HC_Set_Edge_Weight (7.0);
        HC_Set_Edge_Pattern ("....");
        HC_Set_Face_Pattern ("solid");
      HC_Open_Segment ("?include library/line/geom1");
          HC_Insert_Shell (9, spts, 32, facelist);
          HC_Set_Color ("faces = magenta, edges = violet");
          HC_Set_Edge_Weight (5.0);
          HC_Set_Edge_Pattern ("-.-.");
          HC_Set_Face_Pattern ("##");
      HC_Close_Segment ();

      HC_Open_Segment ("?include library/line/geom2");
         HC_Insert_Shell (9, spts2, 32, facelist);
      HC_Close_Segment ();

    HC_Close_Segment ();   /* library/line */

    HC_Open_Segment ("?draw");
      HC_Set_Heuristics ("hidden surfaces");
      HC_Set_Rendering_Options ("hsr algorithm = painters");
      HC_Set_Visibility ("edges = on, markers = on");
      HC_Insert_Distant_Light (1.0, 1.0, -1.0);
      HC_Set_Camera_Position (0.0, 0.0, -10.0);

      HC_Set_Color ("faces = red, text = black, edges = cyan");
      HC_Set_Edge_Weight (1.0);
      HC_Set_Face_Pattern ("==");

      HC_Open_Segment ("?draw/local ");
	  HC_Set_Window (-1.0, -0.33, 0.0, 1.0);
	  HC_Insert_Shell (9, spts, 32, facelist);
          HC_Set_Color ("faces = green, edges = dark green");
          HC_Set_Edge_Weight (2.0);
          HC_Set_Edge_Pattern ("-- --");
          HC_Set_Face_Pattern ("//");
	  HC_Open_Segment ("");
            HC_Set_Camera_Projection ("orthographic");
            HC_Insert_Text (0.0, -0.85, 0.0, "lg green, center, face = //, edge = dk green, -- --");
          HC_Close_Segment ();
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/style");
	  HC_Set_Window (-0.33, 0.33, 0.0, 1.0);
	  HC_Insert_Shell (9, spts, 32, facelist);
          HC_Style_Segment ("?include library/line");
	  HC_Open_Segment ("");
            HC_Set_Camera_Projection ("orthographic");
            HC_Insert_Text (0.0, -0.85, 0.0, "lg blue, center, face = solid, edge = dk blue, ....");
          HC_Close_Segment ();
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/include");
	  HC_Set_Window (0.33, 1.0, 0.0, 1.0);
          HC_Include_Segment ("?include library/line");
	  HC_Open_Segment ("");
            HC_Set_Camera_Projection ("orthographic");
            HC_Insert_Text (0.0, -0.85, 0.0, "lg magenta, center, face = #, edge = violet, -.-.");
            HC_Insert_Text (0.0, -0.95, 0.0, "sm blue, right, face = solid, edge = dk blue, ....");
          HC_Close_Segment ();
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/parent");
	  HC_Set_Window (-1.0, -0.33, -1.0, 0.0);
          HC_Insert_Shell (9, spts, 32, facelist);
	  HC_Open_Segment ("");
            HC_Set_Camera_Projection ("orthographic");
            HC_Insert_Text (0.0, -0.85, 0.0, "lg red, center, face = ==, edge = cyan, -...");
          HC_Close_Segment ();
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/include2");
	  HC_Set_Window (-0.33, 0.33, -1.0, 0.0);
          HC_Include_Segment ("?include library/line/geom1");
	  HC_Open_Segment ("");
            HC_Set_Camera_Projection ("orthographic");
            HC_Insert_Text (0.0, -0.85, 0.0, "lg magenta, center, face = #, edge = violet, -.-.");
          HC_Close_Segment ();
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/include3");
	  HC_Set_Window (0.33, 1.0, -1.0, 0.0);
          HC_Include_Segment ("?include library/line/geom2");
	  HC_Open_Segment ("");
            HC_Set_Camera_Projection ("orthographic");
            HC_Insert_Text (0.0, -0.85, 0.0, "sm red, right, face = ==, edge = cyan, -...");
          HC_Close_Segment ();
        HC_Close_Segment ();

    HC_Close_Segment ();

    HC_Update_Display ();
    HC_Show_Time (&stop_time);

    post_memory ();
    post_results ("attributes from local, style, include, parent");
    post_time (3, start_time, stop_time);
}

void test_ellipse (void) {
    float		start_time,
			stop_time,
			ellipse[3][3],
			ellipse2[3][3];

    ellipse[0][0] = -0.5f; ellipse[0][1] =  0.0f; ellipse[0][2] =  0.0f;
    ellipse[1][0] =  0.0f; ellipse[1][1] =  0.5f; ellipse[1][2] =  0.0f;
    ellipse[2][0] =  0.0f; ellipse[2][1] =  0.0f; ellipse[2][2] =  0.0f;

    ellipse2[0][0] =  0.5f; ellipse2[0][1] =  0.0f; ellipse2[0][2] =  0.0f;
    ellipse2[1][0] =  0.0f; ellipse2[1][1] = -0.5f; ellipse2[1][2] =  0.0f;
    ellipse2[2][0] =  0.0f; ellipse2[2][1] =  0.0f; ellipse2[2][2] =  0.0f;

    identify_test ("?buttons/ellipse");
    HC_Update_Display ();

    HC_Show_Time (&start_time);

    HC_Open_Segment ("?include library/line");
        HC_Set_Color ("faces = light blue, edges = navy blue");
        HC_Set_Edge_Weight (7.0);
        HC_Set_Edge_Pattern ("....");
        HC_Set_Face_Pattern ("solid");

      HC_Open_Segment ("?include library/line/geom1");
	  HC_Insert_Ellipse (ellipse[0], ellipse[1], ellipse[2]);
          HC_Set_Color ("faces = magenta, edges = violet");
          HC_Set_Edge_Weight (5.0);
          HC_Set_Edge_Pattern ("-.-.");
          HC_Set_Face_Pattern ("##");
      HC_Close_Segment ();

      HC_Open_Segment ("?include library/line/geom2");
	  HC_Insert_Ellipse (ellipse2[0], ellipse2[1], ellipse2[2]);
      HC_Close_Segment ();

    HC_Close_Segment ();   /* library/line */

    HC_Open_Segment ("?draw");
        HC_Set_Color ("faces = red, text = black, edges = cyan");
	HC_Set_Visibility ("edges = on, markers = off, cutting planes = off");
        HC_Set_Edge_Weight (1.0);
        HC_Set_Face_Pattern ("==");
        HC_Set_Heuristics ("no hidden surfaces");

	HC_Open_Segment ("?draw/local ");
	  HC_Set_Window (-1.0, -0.33, 0.0, 1.0);
	  HC_Insert_Ellipse (ellipse[0], ellipse[1], ellipse[2]);
          HC_Set_Color ("faces = green, edges = dark green");
          HC_Set_Edge_Weight (2.0);
          HC_Set_Edge_Pattern ("-- --");
          HC_Set_Face_Pattern ("//");
          HC_Insert_Text (0.0, -0.85, 0.0, "left green, face = //, edge = dk green, -- --");
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/style");
	  HC_Set_Window (-0.33, 0.33, 0.0, 1.0);
	  HC_Insert_Ellipse (ellipse[0], ellipse[1], ellipse[2]);
          HC_Style_Segment ("?include library/line");
          HC_Insert_Text (0.0, -0.85, 0.0, "left blue, face = solid, edge = dk blue, ....");
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/include");
	  HC_Set_Window (0.33, 1.0, 0.0, 1.0);
          HC_Include_Segment ("?include library/line");
          HC_Insert_Text (0.0, -0.85, 0.0, "left magenta, face = #, edge = violet, -.-.");
          HC_Insert_Text (0.0, -0.95, 0.0, "right blue, face = solid, edge = dk blue, ....");
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/parent");
	  HC_Set_Window (-1.0, -0.33, -1.0, 0.0);
	  HC_Insert_Ellipse (ellipse[0], ellipse[1], ellipse[2]);
          HC_Insert_Text (0.0, -0.85, 0.0, "left red, face = ==, edge = cyan, -...");
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/include2");
	  HC_Set_Window (-0.33, 0.33, -1.0, 0.0);
          HC_Include_Segment ("?include library/line/geom1");
          HC_Insert_Text (0.0, -0.85, 0.0, "left magenta, face = #, edge =  violet, -.-.");
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/include3");
	  HC_Set_Window (0.33, 1.0, -1.0, 0.0);
          HC_Include_Segment ("?include library/line/geom2");
          HC_Insert_Text (0.0, -0.85, 0.0, "right red, face = ==, edge = cyan, -...");
        HC_Close_Segment ();

    HC_Close_Segment ();

    HC_Update_Display ();
    HC_Show_Time (&stop_time);

    post_memory ();
    post_results ("attributes from local, style, include, parent");
    post_time (3, start_time, stop_time);
}

void test_polygon (void) {
    float		start_time,
			stop_time;
    Point		pts2[3],
			pts3[3];


    pts2[0].x = -0.75f; pts2[0].y = -0.25f; pts2[0].z =  0.0f;
    pts2[1].x =  0.0f; pts2[1].y =  0.25f; pts2[1].z =  0.0f;
    pts2[2].x =  0.75f; pts2[2].y =  0.25f; pts2[2].z =  0.0f;

    pts3[0].x = -0.75f; pts3[0].y =  0.0f; pts3[0].z =  2.0f;
    pts3[1].x =  0.0f; pts3[1].y =  0.75f; pts3[1].z =  2.0f;
    pts3[2].x =  0.75f; pts3[2].y =  0.0f; pts3[2].z =  2.0f;

    identify_test ("?buttons/polygon");
    HC_Update_Display ();

    HC_Show_Time (&start_time);

    HC_Open_Segment ("?include library/line");
        HC_Set_Color ("faces = light blue, edges = navy blue");
        HC_Set_Edge_Weight (7.0);
        HC_Set_Edge_Pattern ("....");
        HC_Set_Face_Pattern ("solid");

      HC_Open_Segment ("?include library/line/geom1");
          HC_Insert_Polygon (3, pts3);
          HC_Set_Color ("faces = magenta, edges = violet");
          HC_Set_Edge_Weight (5.0);
          HC_Set_Edge_Pattern ("-.-.");
          HC_Set_Face_Pattern ("##");
      HC_Close_Segment ();

      HC_Open_Segment ("?include library/line/geom2");
          HC_Insert_Polygon (3, pts2);
      HC_Close_Segment ();

    HC_Close_Segment ();   /* library/line */

    HC_Open_Segment ("?draw");
        HC_Set_Color ("faces = red, text = black, edges = cyan");
	HC_Set_Visibility ("edges = on, markers = off, cutting planes = off");
        HC_Set_Edge_Weight (1.0);
        HC_Set_Face_Pattern ("==");
        HC_Set_Heuristics ("no hidden surfaces");

	HC_Open_Segment ("?draw/local ");
	  HC_Set_Window (-1.0, -0.33, 0.0, 1.0);
          HC_Insert_Polygon (3, pts3);
          HC_Set_Color ("faces = green, edges = dark green");
          HC_Set_Edge_Weight (2.0);
          HC_Set_Edge_Pattern ("-- --");
          HC_Set_Face_Pattern ("//");
	  HC_Insert_Text (0.0, -0.85, 0.0, "green, face = //, edge = dk green, -- --");
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/style");
	  HC_Set_Window (-0.33, 0.33, 0.0, 1.0);
          HC_Insert_Polygon (3, pts3);
          HC_Style_Segment ("?include library/line");
	  HC_Insert_Text (0.0, -0.85, 0.0, "blue, face = solid, edge = dk blue, ....");
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/include");
	  HC_Set_Window (0.33, 1.0, 0.0, 1.0);
          HC_Include_Segment ("?include library/line");
	  HC_Insert_Text (0.0, -0.75, 0.0, "magenta, face = #, edge =  violet, -.-.");
	  HC_Insert_Text (0.0, -0.85, 0.0, "blue, face = solid, edge = dk blue, ....");
	  HC_Insert_Text (0.0, -0.95, 0.0, "blue triangle is obtuse");
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/parent");
	  HC_Set_Window (-1.0, -0.33, -1.0, 0.0);
          HC_Insert_Polygon (3, pts3);
          HC_Insert_Text (0.0, -0.85, 0.0, "red, face = ==, edge = cyan, -...");
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/include2");
	  HC_Set_Window (-0.33, 0.33, -1.0, 0.0);
          HC_Include_Segment ("?include library/line/geom1");
	  HC_Insert_Text (0.0, -0.85, 0.0, "magenta, face = #, edge = violet, -.-.");
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/include3");
	  HC_Set_Window (0.33, 1.0, -1.0, 0.0);
          HC_Include_Segment ("?include library/line/geom2");
          HC_Insert_Text (0.0, -0.85, 0.0, "red, face = ==, edge = cyan, -...");
	  HC_Insert_Text (0.0, -0.95, 0.0, "red triangle is obtuse");
        HC_Close_Segment ();

    HC_Close_Segment ();

    HC_Update_Display ();
    HC_Show_Time (&stop_time);

    post_memory ();
    post_results ("attributes from local, style, include, parent");
    post_time (3, start_time, stop_time);
}

void test_polyline (void) {
    float		start_time,
			stop_time;
    Point		pts[4],
			pts2[3];

    pts[0].x = -0.75f; pts[0].y =  0.25f; pts[0].z =  0.0f;
    pts[1].x = -0.5f; pts[1].y =  0.0f; pts[1].z =  0.0f;
    pts[2].x =  0.5f; pts[2].y =  0.0f; pts[2].z =  0.0f;
    pts[3].x =  0.75f; pts[3].y = -0.25f; pts[3].z =  0.0f;

    pts2[0].x = -0.75f; pts2[0].y = -0.25f; pts2[0].z =  0.0f;
    pts2[1].x =  0.0f; pts2[1].y =  0.25f; pts2[1].z =  0.0f;
    pts2[2].x =  0.75f; pts2[2].y =  0.25f; pts2[2].z =  0.0f;

    identify_test ("?buttons/polyline");
    HC_Update_Display ();

    HC_Show_Time (&start_time);

    HC_Open_Segment ("?include library/line");
	HC_Set_Color ("polylines = blue");
        HC_Set_Line_Weight (7.0);
        HC_Set_Line_Pattern ("....");

      HC_Open_Segment ("?include library/line/geom1");
          HC_Insert_Polyline (4, pts);
	  HC_Set_Color ("polylines = magenta");
          HC_Set_Line_Weight (10.0);
          HC_Set_Line_Pattern ("-.-.");
      HC_Close_Segment ();

      HC_Open_Segment ("?include library/line/geom2");
          HC_Insert_Polyline (3, pts2);
      HC_Close_Segment ();
    HC_Close_Segment ();   /* library/line */

    HC_Open_Segment ("?draw");
	HC_Set_Color ("polylines = red, text = black");
	HC_Set_Line_Weight (1.0);
	HC_Set_Line_Pattern ("-...");
	HC_Set_Heuristics ("no hidden surfaces");

	HC_Open_Segment ("?draw/local ");
	  HC_Set_Window (-1.0, -0.33, 0.0, 1.0);
          HC_Insert_Polyline (4, pts);
	  HC_Set_Color ("polylines = green");
          HC_Set_Line_Weight (20.0);
          HC_Set_Line_Pattern ("-- --");
	  HC_Insert_Text (0.0, -0.75, 0.0, "line from upper left, flat, then lower right");
	  HC_Insert_Text (0.0, -0.85, 0.0, "green, 20, -- --");
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/style");
	  HC_Set_Window (-0.33, 0.33, 0.0, 1.0);
          HC_Insert_Polyline (4, pts);
          HC_Style_Segment ("?include library/line");
	  HC_Insert_Text (0.0, -0.75, 0.0, "line from upper left, flat, then lower right");
	  HC_Insert_Text (0.0, -0.85, 0.0, "blue, 7.0, ....");
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/include");
	  HC_Set_Window (0.33, 1.0, 0.0, 1.0);
          HC_Include_Segment ("?include library/line");
	  HC_Insert_Text (0.0, -0.85, 0.0, "line from upper left, flat");
	  HC_Insert_Text (0.0, -0.75, 0.0, "then lower right,  magenta, 10, -.-.");
	  HC_Insert_Text (0.0, -0.65, 0.0, "line from lower left, then flat");
	  HC_Insert_Text (0.0, -0.95, 0.0, "blue, 7.0, ....");
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/parent");
	  HC_Set_Window (-1.0, -0.33, -1.0, 0.0);
          HC_Insert_Polyline (4, pts);
	  HC_Insert_Text (0.0, -0.75, 0.0, "line from upper left, flat, then lower right");
	  HC_Insert_Text (0.0, -0.85, 0.0, "red, 1, -...");
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/include2");
	  HC_Set_Window (-0.33, 0.33, -1.0, 0.0);
          HC_Include_Segment ("?include library/line/geom1");
	  HC_Insert_Text (0.0, -0.75, 0.0, "line from upper left, flat, then lower right");
	  HC_Insert_Text (0.0, -0.85, 0.0, "magenta, 10, -.-.");
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/include3");
	  HC_Set_Window (0.33, 1.0, -1.0, 0.0);
          HC_Include_Segment ("?include library/line/geom2");
	  HC_Insert_Text (0.0, -0.75, 0.0, "line from lower left, then flat");
	  HC_Insert_Text (0.0, -0.85, 0.0, "red, 1, -...");
        HC_Close_Segment ();
    HC_Close_Segment ();

    HC_Update_Display ();
    HC_Show_Time (&stop_time);

    post_memory ();
    post_results ("attributes from local, style, include, parent");
    post_time (3, start_time, stop_time);
}

void test_cutting_plane (void) {
    float		start_time,
			stop_time,
			plane[5][3];
    Point		mpts[9],
			mpts2[9];
    int			facelist[32];


   mpts[0].x = -1.0f; mpts[0].y =  1.0f; mpts[0].z =  0.0f;
   mpts[1].x =  0.0f; mpts[1].y =  1.0f; mpts[1].z =  0.0f;
   mpts[2].x =  1.0f; mpts[2].y =  1.0f; mpts[2].z =  0.0f;
   mpts[3].x = -1.0f; mpts[3].y =  0.0f; mpts[3].z =  0.0f;
   mpts[4].x =  0.0f; mpts[4].y =  0.0f; mpts[4].z =  1.0f;
   mpts[5].x =  1.0f; mpts[5].y =  0.0f; mpts[5].z =  0.0f;
   mpts[6].x = -1.0f; mpts[6].y = -1.0f; mpts[6].z =  0.0f;
   mpts[7].x =  0.0f; mpts[7].y = -1.0f; mpts[7].z =  0.0f;
   mpts[8].x =  1.0f; mpts[8].y = -1.0f; mpts[8].z =  0.0f;

   mpts2[0].x =  1.5f; mpts2[0].y =  1.5f; mpts2[0].z =  0.0f;
   mpts2[1].x =  1.0f; mpts2[1].y =  1.5f; mpts2[1].z =  0.0f;
   mpts2[2].x =  0.5f; mpts2[2].y =  1.5f; mpts2[2].z =  0.0f;
   mpts2[3].x =  1.5f; mpts2[3].y =  1.0f; mpts2[3].z =  0.0f;
   mpts2[4].x =  1.0f; mpts2[4].y =  1.0f; mpts2[4].z =  1.0f;
   mpts2[5].x =  0.5f; mpts2[5].y =  1.0f; mpts2[5].z =  0.0f;
   mpts2[6].x =  1.5f; mpts2[6].y =  0.5f; mpts2[6].z =  0.0f;
   mpts2[7].x =  1.0f; mpts2[7].y =  0.5f; mpts2[7].z =  0.0f;
   mpts2[8].x =  0.5f; mpts2[8].y =  0.5f; mpts2[8].z =  0.0f;

    facelist[0]  = 3; facelist[1]  = 0; facelist[2]  = 1; facelist[3] = 4;
    facelist[4]  = 3; facelist[5]  = 1; facelist[6]  = 2; facelist[7] = 4;
    facelist[8]  = 3; facelist[9]  = 2; facelist[10] = 5; facelist[11] = 4;
    facelist[12] = 3; facelist[13] = 5; facelist[14] = 8; facelist[15] = 4;
    facelist[16] = 3; facelist[17] = 8; facelist[18] = 7; facelist[19] = 4;
    facelist[20] = 3; facelist[21] = 7; facelist[22] = 6; facelist[23] = 4;
    facelist[24] = 3; facelist[25] = 6; facelist[26] = 3; facelist[27] = 4;
    facelist[28] = 3; facelist[29] = 3; facelist[30] = 0; facelist[31] = 4;


    plane[0][0] = -1.0f; plane[0][1] =  1.0f; plane[0][2] =  -1.0f;
    plane[1][0] = -1.0f; plane[1][1] = -1.0f; plane[1][2] =   1.0f;
    plane[2][0] =  1.0f; plane[2][1] = -1.0f; plane[2][2] =   1.0f;
    plane[3][0] =  1.0f; plane[3][1] =  1.0f; plane[3][2] =  -1.0f;
    plane[4][0] = -1.0f; plane[4][1] =  1.0f; plane[4][2] =  -1.0f;

    identify_test ("?buttons/cutting plane");
    HC_Update_Display ();

    HC_Show_Time (&start_time);

    HC_Open_Segment ("?include library/line");
      HC_Set_Visibility ("cutting planes = off");
      HC_Open_Segment ("?include library/line/geom1");
          HC_Insert_Cutting_Plane (0.0, -1.0, -1.0, 0.0);
          HC_Set_Visibility ("cutting planes = on");
      HC_Close_Segment ();

      HC_Open_Segment ("?include library/line/geom2");
          HC_Insert_Cutting_Plane (0.0, -1.0, -1.0, 0.0);
      HC_Close_Segment ();
    HC_Close_Segment ();   /* library/line */

    HC_Open_Segment ("?draw");
      HC_Set_Heuristics ("hidden surfaces");
      HC_Set_Rendering_Options ("hsr algorithm = painters");
      HC_Set_Visibility ("edges = off, markers = off, cutting planes = on");
      HC_UnSet_Line_Pattern ();

      HC_Insert_Distant_Light (1.0, 1.0, -1.0);
      HC_Set_Camera_Position (0.0, 0.0, -10.0);

      HC_Set_Visibility ("cutting planes = on");
      HC_Set_Color ("faces = red, text = black, lines = black");

      HC_Open_Segment ("?draw/local ");
	  HC_Set_Window (-1.0, -0.33, 0.0, 1.0);
          HC_Insert_Cutting_Plane (0.0, -1.0, -1.0, 0.0);
          HC_Insert_Distant_Light (1.0, 1.0, -1.0);
          HC_Set_Camera_Position (0.0, 0.0, -10.0);
          HC_Orbit_Camera (75.0, 0.0);
          HC_Insert_Shell (9, mpts, 32, facelist);
          HC_Set_Visibility ("cutting planes = on");
          HC_Open_Segment ("polyline");
            HC_Insert_Polyline (5, plane);
            HC_Set_Visibility ("cutting planes = off");
          HC_Close_Segment ();
	  HC_Open_Segment ("");
            HC_Set_Camera_Projection ("orthographic");
            HC_Set_Visibility ("cutting planes = off");
	    HC_Insert_Text (0.0, -0.85, 0.0, "Visibility = ON");
          HC_Close_Segment ();
      HC_Close_Segment ();

        HC_Open_Segment ("?draw/style");
	  HC_Set_Window (-0.33, 0.33, 0.0, 1.0);
          HC_Insert_Cutting_Plane (0.0, -1.0, -1.0, 0.0);
          HC_Insert_Distant_Light (1.0, 1.0, -1.0);
          HC_Set_Camera_Position (0.0, 0.0, -10.0);
          HC_Orbit_Camera (75.0, 0.0);
          HC_Insert_Shell (9, mpts, 32, facelist);
          HC_Style_Segment ("?include library/line");
	  HC_Open_Segment ("polyline");
            HC_Set_Visibility ("cutting planes = off");
            HC_Insert_Polyline (5, plane);
          HC_Close_Segment ();
	  HC_Open_Segment ("");
            HC_Set_Camera_Projection ("orthographic");
            HC_Set_Visibility ("cutting planes = off");
	    HC_Insert_Text (0.0, -0.85, 0.0, "Visibility = OFF");
          HC_Close_Segment ();
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/include");
	  HC_Set_Window (0.33, 1.0, 0.0, 1.0);
          HC_Include_Segment ("?include library/line");
          HC_Insert_Shell (9, mpts, 32, facelist);
          HC_Insert_Distant_Light (1.0, 1.0, -1.0);
          HC_Set_Camera_Position (0.0, 0.0, -10.0);
          HC_Orbit_Camera (75.0, 0.0);
	  HC_Open_Segment ("polyline");
            HC_Set_Visibility ("cutting planes = off");
            HC_Insert_Polyline (5, plane);
          HC_Close_Segment ();
	  HC_Open_Segment ("");
            HC_Set_Camera_Projection ("orthographic");
            HC_Set_Visibility ("cutting planes = off");
	    HC_Insert_Text (0.0, -0.85, 0.0, "Visibility = ON");
          HC_Close_Segment ();
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/parent");
	  HC_Set_Window (-1.0, -0.33, -1.0, 0.0);
          HC_Insert_Cutting_Plane (0.0, -1.0, -1.0, 0.0);
          HC_Insert_Distant_Light (1.0, 1.0, -1.0);
          HC_Set_Camera_Position (0.0, 0.0, -10.0);
          HC_Orbit_Camera (75.0, 0.0);
          HC_Insert_Shell (9, mpts, 32, facelist);
	  HC_Open_Segment ("polyline");
            HC_Set_Visibility ("cutting planes = off");
            HC_Insert_Polyline (5, plane);
          HC_Close_Segment ();
	  HC_Open_Segment ("");
            HC_Set_Camera_Projection ("orthographic");
            HC_Set_Visibility ("cutting planes = off");
	    HC_Insert_Text (0.0, -0.85, 0.0, "Visibility = ON");
          HC_Close_Segment ();
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/include2");
	  HC_Set_Window (-0.33, 0.33, -1.0, 0.0);
          HC_Insert_Distant_Light (1.0, 1.0, -1.0);
          HC_Set_Camera_Position (0.0, 0.0, -10.0);
          HC_Orbit_Camera (75.0, 0.0);
          HC_Insert_Shell (9, mpts, 32, facelist);
          HC_Include_Segment ("?include library/line/geom1");
	  HC_Open_Segment ("polyline");
            HC_Set_Visibility ("cutting planes = off");
            HC_Insert_Polyline (5, plane);
          HC_Close_Segment ();
	  HC_Open_Segment ("");
            HC_Set_Camera_Projection ("orthographic");
            HC_Set_Visibility ("cutting planes = off");
	    HC_Insert_Text (0.0, -0.85, 0.0, "Visibility = ON");
          HC_Close_Segment ();
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/include3");
	  HC_Set_Window (0.33, 1.0, -1.0, 0.0);
          HC_Insert_Distant_Light (1.0, 1.0, -1.0);
          HC_Set_Camera_Position (0.0, 0.0, -10.0);
          HC_Insert_Shell (9, mpts, 32, facelist);
          HC_Orbit_Camera (75.0, 0.0);
          HC_Include_Segment ("?include library/line/geom2");
	  HC_Open_Segment ("polyline");
            HC_Set_Visibility ("cutting planes = off");
            HC_Insert_Polyline (5, plane);
          HC_Close_Segment ();
	  HC_Open_Segment ("");
            HC_Set_Camera_Projection ("orthographic");
            HC_Set_Visibility ("cutting planes = off");
	    HC_Insert_Text (0.0, -0.85, 0.0, "Visibility = ON");
          HC_Close_Segment ();
        HC_Close_Segment ();
    HC_Close_Segment ();

    HC_Update_Display ();
    HC_Show_Time (&stop_time);

    post_memory ();
    post_results ("attributes from local, style, include, parent");
    post_time (3, start_time, stop_time);
}

void test_image (void) {
    int			i = 0;
    int			j = 0;
    float		start_time,
			stop_time;
    unsigned char       pixels[100][100];

    identify_test ("?buttons/image");
    HC_Update_Display ();

    HC_Show_Time (&start_time);

    for (i = 0; i < 100; ++i)
      for (j = 0; j < 100; ++j)
        pixels[j][i] = 3;
    for (i = 0; i < 100; ++i) {
      for (j = 0; j < 5; ++j)
        pixels[j][i] = 0;
      for (j = 10; j < 15; ++j)
        pixels[j][i] = 0;
      for (j = 20; j < 25; ++j)
        pixels[j][i] = 0;
      for (j = 30; j < 35; ++j)
        pixels[j][i] = 0;
      for (j = 40; j < 45; ++j)
        pixels[j][i] = 0;
      for (j = 50; j < 55; ++j)
        pixels[j][i] = 0;
      for (j = 60; j < 65; ++j)
        pixels[j][i] = 0;
      for (j = 70; j < 75; ++j)
        pixels[j][i] = 0;
      for (j = 80; j < 85; ++j)
        pixels[j][i] = 0;
      for (j = 90; j < 95; ++j)
        pixels[j][i] = 0;
    }
    for (i = 0; i < 25; ++i) {
      for (j = 0; j < 25; ++j) {
        pixels[j][i] = 1;
        pixels[j][99 - i] = 2;
        pixels[99 - j][i] = 4;
        pixels[99 - j][99 - i] = 5;
        }
    }

    HC_Open_Segment ("?include library/line");
      HC_Set_Color_Map ("dark blue, blue, light blue, gray, gray, gray");

      HC_Open_Segment ("?include library/line/geom1");
        HC_Set_Color_Map ("dark magenta, magenta, light magenta, gray, gray, gray");
        HC_Insert_Image (0.0, 0.0, 0.0, "mapped 8", 100, 100, (void *)pixels);
      HC_Close_Segment ();

      HC_Open_Segment ("?include library/line/geom2");
        HC_Insert_Image (0.5, 0.5, 0.0, "mapped 8", 100, 100, (void *)pixels);
      HC_Close_Segment ();
    HC_Close_Segment ();   /* library/line */

    HC_Open_Segment ("?draw");
        HC_Set_Color ("text = black");
        HC_Set_Color_Map ("dark red, red, light red, gray, gray, gray");

	HC_Open_Segment ("?draw/local ");
	  HC_Set_Window (-1.0, -0.33, 0.0, 1.0);
          HC_Set_Color_Map ("dark green, green, light green, gray, gray, gray");
          HC_Insert_Image (0.0, 0.0, 0.0, "mapped 8", 100, 100, (void *)pixels);
	  HC_Insert_Text (0.0, -0.85, 0.0,
			  "centered box, green upper corners, gray lower");
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/style");
	  HC_Set_Window (-0.33, 0.33, 0.0, 1.0);
          HC_Insert_Image (0.0, 0.0, 0.0, "mapped 8", 100, 100, (void *)pixels);
          HC_Style_Segment ("?include library/line");
	  HC_Insert_Text (0.0, -0.85, 0.0,
			  "centered box, blue uuper corners, gray lower");
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/include");
	  HC_Set_Window (0.33, 1.0, 0.0, 1.0);
          HC_Include_Segment ("?include library/line");
	  HC_Insert_Text (0.0, -0.85, 0.0,
			  "centered box, magenta upper corners, gray lower");
	  HC_Insert_Text (0.0, -0.95, 0.0,
			  "upper right box, blue upper corners, gray lower");
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/parent");
	  HC_Set_Window (-1.0, -0.33, -1.0, 0.0);
          HC_Insert_Image (0.0, 0.0, 0.0, "mapped 8", 100, 100, (void *)pixels);
	  HC_Insert_Text (0.0, -0.85, 0.0,
			  "centered box, red upper corners, gray lower");
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/include2");
	  HC_Set_Window (-0.33, 0.33, -1.0, 0.0);
          HC_Include_Segment ("?include library/line/geom1");
	  HC_Insert_Text (0.0, -0.85, 0.0,
			  "centered box, magenta upper corners, gray lower");
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/include3");
	  HC_Set_Window (0.33, 1.0, -1.0, 0.0);
          HC_Include_Segment ("?include library/line/geom2");
	  HC_Insert_Text (0.0, -0.85, 0.0,
			  "upper right box, red upper corners, gray lower");
        HC_Close_Segment ();
    HC_Close_Segment ();

    HC_Update_Display ();
    HC_Show_Time (&stop_time);

    post_memory ();
    post_results ("attributes from local, style, include, parent");
    post_time (3, start_time, stop_time);
}

void tst_text (void) {
    float		start_time,
			stop_time;

    identify_test ("?buttons/text");
    HC_Update_Display ();

    HC_Show_Time (&start_time);

    HC_Open_Segment ("?include library/line");
	HC_Set_Color ("text = dark blue");
        HC_Set_Text_Alignment ("**");
        HC_Set_Text_Font ("name = typewriter");
        HC_Set_Text_Path (1.0, 0.0, 0.0);
        HC_Set_Text_Spacing (1.0);

      HC_Open_Segment ("?include library/line/geom1");
          HC_Insert_Text (0.0, 0.0, 0.0, "Here's a different string!");
	  HC_Set_Color ("text = cyan");
          HC_Set_Text_Alignment ("*");
          HC_Set_Text_Font ("name = roman");
	  HC_Set_Text_Path (0.5, 1.0, 0.0);
          HC_Set_Text_Spacing (1.0);
      HC_Close_Segment ();

      HC_Open_Segment ("?include library/line/geom2");
          HC_Insert_Text (0.0, 0.0, 0.0, "Here's a text string!");
      HC_Close_Segment ();
    HC_Close_Segment ();   /* library/line */

    HC_Open_Segment ("?draw");
	HC_Set_Color ("text = red");
        HC_Set_Text_Alignment ("*");
        HC_Set_Text_Font ("name = Brooktondale");
        HC_Set_Text_Path (1.0, 0.5, 0.0);
        HC_Set_Text_Spacing (1.0);

	HC_Open_Segment ("?draw/local ");
	  HC_Set_Window (-1.0, -0.33, 0.0, 1.0);
          HC_Insert_Text (0.0, 0.0, 0.0, "Here's a text string!");
	  HC_Set_Color ("text = dark green");
          HC_Set_Text_Alignment ("*");
          HC_Set_Text_Font ("name = Newfield");
          HC_Set_Text_Path (0.0, 1.0, 0.0);
          HC_Set_Text_Spacing (1.0);
          HC_Open_Segment ("");
	    HC_Insert_Text (0.0, -0.85, 0.0, "local:  green, 25, -- --");
          HC_Close_Segment ();
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/style");
	  HC_Set_Window (-0.33, 0.33, 0.0, 1.0);
          HC_Insert_Text (0.0, 0.0, 0.0, "Here's a text string!");
          HC_Style_Segment ("?include library/line");
	  HC_Insert_Text (0.0, -0.85, 0.0, "style lib:  blue, 7.0, ....");
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/include");
	  HC_Set_Window (0.33, 1.0, 0.0, 1.0);
          HC_Include_Segment ("?include library/line");
	  HC_Insert_Text (0.0, -0.85, 0.0, "include:  cyan, 50, -.-.");
	  HC_Insert_Text (0.0, -0.95, 0.0, "include:  blue, 7.0, ....");
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/parent");
	  HC_Set_Window (-1.0, -0.33, -1.0, 0.0);
          HC_Insert_Text (0.0, 0.0, 0.0, "Here's a text string!");
	  HC_Insert_Text (0.0, -0.85, 0.0, "parent:  red, 1, -...");
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/include2");
	  HC_Set_Window (-0.33, 0.33, -1.0, 0.0);
          HC_Include_Segment ("?include library/line/geom1");
	  HC_Insert_Text (0.0, -0.85, 0.0, "include:  cyan, 50, -.-.");
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/include3");
	  HC_Set_Window (0.33, 1.0, -1.0, 0.0);
          HC_Include_Segment ("?include library/line/geom2");
	  HC_Insert_Text (0.0, -0.85, 0.0, "include:  red, 1, -...");
        HC_Close_Segment ();
    HC_Close_Segment ();

    HC_Update_Display ();
    HC_Show_Time (&stop_time);

    post_memory ();
    post_results ("attributes from local, style, include, parent");
    post_time (3, start_time, stop_time);
}

void test_font (void) {
    float		start_time,
			stop_time;

    HC_Define_Font ("testfont", "", sizeof(font), font);
    identify_test ("?buttons/font");
    HC_Update_Display ();

    HC_Show_Time (&start_time);

    HC_Open_Segment ("?include library/line");
	HC_Set_Color ("text = blue");
	HC_Set_Text_Alignment ("<^");
	HC_Set_Text_Font ("name = testfont");
        HC_Set_Text_Path (1.0, 0.0, 0.0);
	HC_Set_Text_Spacing (1.0);
      HC_Open_Segment ("?include library/line/geom1");
	  HC_Insert_Text (0.0, 0.0, 0.0, "HOOPS");
	  HC_Set_Color ("text = magenta");
	  HC_Set_Text_Alignment ("<V");
	  HC_Set_Text_Font ("name = testfont");
	  HC_Set_Text_Path (1.0, 0.5, 0.0);
	  HC_Set_Text_Spacing (2.0);
      HC_Close_Segment ();

      HC_Open_Segment ("?include library/line/geom2");
	  HC_Insert_Text (0.0, 0.75, 0.0, "HOOPS");
      HC_Close_Segment ();
    HC_Close_Segment ();   /* library/line */

    HC_Open_Segment ("?draw");
	HC_Set_Color ("text = red");
	HC_Set_Text_Alignment ("*");
	HC_Set_Text_Font ("name = testfont");
	HC_Set_Text_Path (0.5, 1.0, 0.0);
	HC_Set_Text_Spacing (2.5);

	HC_Open_Segment ("?draw/local ");
	  HC_Set_Window (-1.0, -0.33, 0.0, 1.0);
	  HC_Insert_Text (0.0, 0.0, 0.0, "HOOPS");
	  HC_Set_Color ("text = dark green");
	  HC_Set_Text_Alignment (">*");
	  HC_Set_Text_Font ("name = testfont");
	  HC_Set_Text_Path (0.0, 1.0, 0.0);
	  HC_Set_Text_Spacing (1.5);
	  HC_Open_Segment ("");
	    HC_Set_Color ("text = black");
	    HC_Set_Text_Alignment ("*");
	    HC_Set_Text_Font ("name = Sans Serif");
	    HC_Set_Text_Path (1.0, 0.0, 0.0);
	    HC_Set_Text_Spacing (1.0);
	    HC_Insert_Text (0.0, -0.85, 0.0, "green, sp = 1.5, align:>*");
	    HC_Insert_Text (0.0, -0.95, 0.0, "insert:  0, 0, 0; path:  0, -1, 0");
          HC_Close_Segment ();
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/style");
	  HC_Set_Window (-0.33, 0.33, 0.0, 1.0);
	  HC_Insert_Text (0.0, 0.0, 0.0, "HOOPS");
          HC_Style_Segment ("?include library/line");
	  HC_Open_Segment ("");
	    HC_Set_Color ("text = black");
	    HC_Set_Text_Alignment ("*");
	    HC_Set_Text_Font ("name = Sans Serif");
	    HC_Set_Text_Path (1.0, 0.0, 0.0);
	    HC_Set_Text_Spacing (1.0);
	    HC_Insert_Text (0.0, -0.85, 0.0, "blue, sp = 1.0, align:<^");
	    HC_Insert_Text (0.0, -0.95, 0.0, "insert:  0, 0, 0; path:  1, 0, 0");
          HC_Close_Segment ();
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/include");
	  HC_Set_Window (0.33, 1.0, 0.0, 1.0);
          HC_Include_Segment ("?include library/line");
	  HC_Open_Segment ("");
	    HC_Set_Color ("text = black");
	    HC_Set_Text_Alignment ("*");
	    HC_Set_Text_Font ("name = Sans Serif");
	    HC_Set_Text_Path (1.0, 0.0, 0.0);
	    HC_Set_Text_Spacing (1.0);
	    HC_Insert_Text (0.0, -0.65, 0.0, "magenta, sp = 2.0, align:<V");
	    HC_Insert_Text (0.0, -0.75, 0.0, "insert:  0, 0, 0; path:  1, .5, 0");
	    HC_Insert_Text (0.0, -0.85, 0.0, "blue, sp = 1.0, align:<^");
	    HC_Insert_Text (0.0, -0.95, 0.0, "insert:  0, .75, 0; path:  1, 0, 0");
          HC_Close_Segment ();
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/parent");
	  HC_Set_Window (-1.0, -0.33, -1.0, 0.0);
	  HC_Insert_Text (0.0, -0.0, 0.0, "HOOPS");
	  HC_Open_Segment ("");
	    HC_Set_Color ("text = black");
	    HC_Set_Text_Alignment ("*");
	    HC_Set_Text_Font ("name = Sans Serif");
	    HC_Set_Text_Path (1.0, 0.0, 0.0);
	    HC_Set_Text_Spacing (1.0);
	    HC_Insert_Text (0.0, -0.85, 0.0, "red, sp = 2.5, align:*");
	    HC_Insert_Text (0.0, -0.95, 0.0, "insert:  0, 0, 0; path:  .5, 1, 0");
          HC_Close_Segment ();
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/include2");
	  HC_Set_Window (-0.33, 0.33, -1.0, 0.0);
          HC_Include_Segment ("?include library/line/geom1");
	  HC_Open_Segment ("");
	    HC_Set_Color ("text = black");
	    HC_Set_Text_Alignment ("*");
	    HC_Set_Text_Font ("name = Sans Serif");
	    HC_Set_Text_Path (1.0, 0.0, 0.0);
	    HC_Set_Text_Spacing (1.0);
	    HC_Insert_Text (0.0, -0.85, 0.0, "magenta, sp = 2.0, align:<V");
	    HC_Insert_Text (0.0, -0.95, 0.0, "insert:  0, .75, 0; path:  1, .5, 0");
          HC_Close_Segment ();
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/include3");
	  HC_Set_Window (0.33, 1.0, -1.0, 0.0);
          HC_Include_Segment ("?include library/line/geom2");
	  HC_Open_Segment ("");
	    HC_Set_Color ("text = black");
	    HC_Set_Text_Alignment ("*");
	    HC_Set_Text_Font ("name = Sans Serif");
	    HC_Set_Text_Path (1.0, 0.0, 0.0);
	    HC_Set_Text_Spacing (1.0);
	    HC_Insert_Text (0.0, -0.85, 0.0, "red, sp = 2.5, align:*");
	    HC_Insert_Text (0.0, -0.95, 0.0, "path:  .5, 1, 0");
          HC_Close_Segment ();
        HC_Close_Segment ();
    HC_Close_Segment ();

    HC_Update_Display ();
    HC_Show_Time (&stop_time);

    post_memory ();
    post_results ("attributes from local, style, include, parent");
    post_time (3, start_time, stop_time);
}

void test_text (void) {
    float		start_time,
			stop_time;

    identify_test ("?buttons/text");
    HC_Update_Display ();

    HC_Show_Time (&start_time);

    HC_Open_Segment ("?include library/line");
	HC_Set_Color ("text = blue");
	HC_Set_Text_Alignment ("<^");
	HC_Set_Text_Font ("name = Enfield");
        HC_Set_Text_Path (1.0, 0.0, 0.0);
	HC_Set_Text_Spacing (1.0);
      HC_Open_Segment ("?include library/line/geom1");
	  HC_Insert_Text (0.0, 0.0, 0.0, "A Text String");
	  HC_Set_Color ("text = magenta");
	  HC_Set_Text_Alignment ("<V");
	  HC_Set_Text_Font ("name = Roman");
	  HC_Set_Text_Path (1.0, 0.5, 0.0);
	  HC_Set_Text_Spacing (2.0);
      HC_Close_Segment ();

      HC_Open_Segment ("?include library/line/geom2");
	  HC_Insert_Text (0.0, 0.75, 0.0, "A Text String");
      HC_Close_Segment ();
    HC_Close_Segment ();   /* library/line */

    HC_Open_Segment ("?draw");
	HC_Set_Color ("text = red");
	HC_Set_Text_Alignment ("*");
	HC_Set_Text_Font ("name = Sans Serif");
	HC_Set_Text_Path (0.5, 1.0, 0.0);
	HC_Set_Text_Spacing (2.5);

	HC_Open_Segment ("?draw/local ");
	  HC_Set_Window (-1.0, -0.33, 0.0, 1.0);
	  HC_Insert_Text (0.0, 0.0, 0.0, "A Text String");
	  HC_Set_Color ("text = dark green");
	  HC_Set_Text_Alignment (">*");
	  HC_Set_Text_Font ("name = typewriter");
	  HC_Set_Text_Path (0.0, -1.0, 0.0);
	  HC_Set_Text_Spacing (1.5);
	  HC_Open_Segment ("");
	    HC_Set_Color ("text = black");
	    HC_Set_Text_Alignment ("*");
	    HC_Set_Text_Font ("name = Sans Serif");
	    HC_Set_Text_Path (1.0, 0.0, 0.0);
	    HC_Set_Text_Spacing (1.0);
	    HC_Insert_Text (0.0, -0.85, 0.0, "green, typewriter, sp = 1.5, align:>*");
	    HC_Insert_Text (0.0, -0.95, 0.0, "insert:  0, 0, 0; path:  0, -1, 0");
          HC_Close_Segment ();
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/style");
	  HC_Set_Window (-0.33, 0.33, 0.0, 1.0);
	  HC_Insert_Text (0.0, 0.0, 0.0, "A Text String");
          HC_Style_Segment ("?include library/line");
	  HC_Open_Segment ("");
	    HC_Set_Color ("text = black");
	    HC_Set_Text_Alignment ("*");
	    HC_Set_Text_Font ("name = Sans Serif");
	    HC_Set_Text_Path (1.0, 0.0, 0.0);
	    HC_Set_Text_Spacing (1.0);
	    HC_Insert_Text (0.0, -0.85, 0.0, "blue, Enfield, sp = 1, align:<^");
	    HC_Insert_Text (0.0, -0.95, 0.0, "insert:  0, 0, 0; path:  1, 0, 0");
          HC_Close_Segment ();
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/include");
	  HC_Set_Window (0.33, 1.0, 0.0, 1.0);
          HC_Include_Segment ("?include library/line");
	  HC_Open_Segment ("");
	    HC_Set_Color ("text = black");
	    HC_Set_Text_Alignment ("*");
	    HC_Set_Text_Font ("name = Sans Serif");
	    HC_Set_Text_Path (1.0, 0.0, 0.0);
	    HC_Set_Text_Spacing (1.0);
	    HC_Insert_Text (0.0, -0.65, 0.0, "magenta, Roman, sp = 1, align:<V ");
	    HC_Insert_Text (0.0, -0.75, 0.0, "insert:  0, 0, 0; path:  1, .5, 0");
	    HC_Insert_Text (0.0, -0.85, 0.0, "blue, Enfield, sp = 1, align:<^");
	    HC_Insert_Text (0.0, -0.95, 0.0, "insert:  0, .75, 0; path:  1, 0, 0");
          HC_Close_Segment ();
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/parent");
	  HC_Set_Window (-1.0, -0.33, -1.0, 0.0);
	  HC_Insert_Text (0.0, 0.0, 0.0, "A Text String");
	  HC_Open_Segment ("");
	    HC_Set_Color ("text = black");
	    HC_Set_Text_Alignment ("*");
	    HC_Set_Text_Font ("name = Sans Serif");
	    HC_Set_Text_Path (1.0, 0.0, 0.0);
	    HC_Set_Text_Spacing (1.0);
	    HC_Insert_Text (0.0, -0.85, 0.0, "red, Sans Seri, sp = 2.5, align:* ");
	    HC_Insert_Text (0.0, -0.95, 0.0, "insert:  0, 0, 0; path:  .5, 1, 0");
          HC_Close_Segment ();
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/include2");
	  HC_Set_Window (-0.33, 0.33, -1.0, 0.0);
          HC_Include_Segment ("?include library/line/geom1");
	  HC_Open_Segment ("");
	    HC_Set_Color ("text = black");
	    HC_Set_Text_Alignment ("*");
	    HC_Set_Text_Font ("name = Sans Serif");
	    HC_Set_Text_Path (1.0, 0.0, 0.0);
	    HC_Set_Text_Spacing (1.0);
	    HC_Insert_Text (0.0, -0.85, 0.0, "magenta, Roman, sp = 1, align:<V ");
	    HC_Insert_Text (0.0, -0.95, 0.0, "insert:  0, 0, 0; path:  1, .5, 0");
          HC_Close_Segment ();
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/include3");
	  HC_Set_Window (0.33, 1.0, -1.0, 0.0);
          HC_Include_Segment ("?include library/line/geom2");
	  HC_Open_Segment ("");
	    HC_Set_Color ("text = black");
	    HC_Set_Text_Alignment ("*");
	    HC_Set_Text_Font ("name = Sans Serif");
	    HC_Set_Text_Path (1.0, 0.0, 0.0);
	    HC_Set_Text_Spacing (1.0);
	    HC_Insert_Text (0.0, -0.85, 0.0, "red, Sans Seri, sp = 2.5, align:* ");
	    HC_Insert_Text (0.0, -0.95, 0.0, "insert:  0, .75, 0; path:  .5, 1, 0");
          HC_Close_Segment ();
        HC_Close_Segment ();
    HC_Close_Segment ();

    HC_Update_Display ();
    HC_Show_Time (&stop_time);

    post_memory ();
    post_results ("attributes from local, style, include, parent");
    post_time (3, start_time, stop_time);
}

void test_ink (void) {
    float		start_time,
			stop_time;

    identify_test ("?buttons/ink");
    HC_Update_Display ();

    HC_Show_Time (&start_time);

    HC_Open_Segment ("?include library/line");
	HC_Set_Color ("polylines = blue");
        HC_Set_Line_Weight (7.0);
        HC_Set_Line_Pattern ("....");

      HC_Open_Segment ("?include library/line/geom1");
          HC_Insert_Ink (-0.65, -0.65, 0.0);
          HC_Insert_Ink (0.65, -0.65, 0.0);
	  HC_Set_Color ("polylines = magenta");
          HC_Set_Line_Weight (10.0);
          HC_Set_Line_Pattern ("-.-.");
      HC_Close_Segment ();

      HC_Open_Segment ("?include library/line/geom2");
          HC_Insert_Ink (-0.65, 0.65, 0.0);
          HC_Insert_Ink (0.65, 0.65, 0.0);
      HC_Close_Segment ();

    HC_Close_Segment ();   /* library/line */

    HC_Open_Segment ("?draw");

	HC_Set_Color ("polylines = red, text = black");
	HC_Set_Line_Weight (1.0);
	HC_Set_Line_Pattern ("-...");
	HC_Set_Heuristics ("no hidden surfaces");

	HC_Open_Segment ("?draw/local ");
	  HC_Set_Window (-1.0, -0.33, 0.0, 1.0);
          HC_Insert_Ink (-0.65, -0.65, 0.0);
          HC_Insert_Ink (0.65, -0.65, 0.0);
	  HC_Set_Color ("polylines = green");
          HC_Set_Line_Weight (20.0);
          HC_Set_Line_Pattern ("-- --");
          HC_Insert_Text (0.0, -0.85, 0.0, "low line:  green, 20, -- --");
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/style");
	  HC_Set_Window (-0.33, 0.33, 0.0, 1.0);
          HC_Insert_Ink (-0.65, -0.65, 0.0);
          HC_Insert_Ink (0.65, -0.65, 0.0);
          HC_Style_Segment ("?include library/line");
          HC_Insert_Text (0.0, -0.85, 0.0, "low line:  blue, 7.0, ....");
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/include");
	  HC_Set_Window (0.33, 1.0, 0.0, 1.0);
          HC_Include_Segment ("?include library/line");
          HC_Insert_Text (0.0, -0.85, 0.0, "low line:  magenta, 10, -.-.");
          HC_Insert_Text (0.0, -0.95, 0.0, "high line:  blue, 7.0, ....");
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/parent");
	  HC_Set_Window (-1.0, -0.33, -1.0, 0.0);
          HC_Insert_Ink (-0.65, -0.65, 0.0);
          HC_Insert_Ink (0.65, -0.65, 0.0);
          HC_Insert_Text (0.0, -0.85, 0.0, "low line:  red, 1, -...");
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/include2");
	  HC_Set_Window (-0.33, 0.33, -1.0, 0.0);
          HC_Include_Segment ("?include library/line/geom1");
          HC_Insert_Text (0.0, -0.85, 0.0, "low line:  magenta, 10, -.-.");
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/include3");
	  HC_Set_Window (0.33, 1.0, -1.0, 0.0);
          HC_Include_Segment ("?include library/line/geom2");
          HC_Insert_Text (0.0, -0.85, 0.0, "high line:  red, 1, -...");
        HC_Close_Segment ();
    HC_Close_Segment ();

    HC_Update_Display ();
    HC_Show_Time (&stop_time);

    post_memory ();
    post_results ("attributes from local, style, include, parent");
    post_time (3, start_time, stop_time);
}

void test_grid (void) {
    float		start_time,
			stop_time;
    Point		grid,
			ref1,
			ref2;

    grid.x = -0.3f; grid.y =  0.0f; grid.z =  1.0f;
    ref1.x = -0.2f; ref1.y =  0.0f; ref1.z =  1.0f;
    ref2.x = -0.3f; ref2.y =  0.2f; ref2.z =  1.0f;

    identify_test ("?buttons/grid");
    HC_Update_Display ();

    HC_Show_Time (&start_time);

    HC_Open_Segment ("?include library/line");
        HC_Set_Color ("faces = light blue, edges = navy blue");
        HC_Set_Edge_Weight (7.0);
        HC_Set_Edge_Pattern ("....");
        HC_Set_Face_Pattern ("solid");

        HC_Open_Segment ("?include library/line/geom1");
          HC_Insert_Grid ("quadrilateral", &grid, &ref1, &ref2, 10, 10);
          HC_Set_Color ("faces = magenta, edges = violet");
          HC_Set_Edge_Weight (5.0);
          HC_Set_Edge_Pattern ("-.-.");
          HC_Set_Face_Pattern ("##");
        HC_Close_Segment ();

      HC_Open_Segment ("?include library/line/geom2");
          HC_Insert_Grid ("radial", &grid, &ref1, &ref2, 5, 5);
      HC_Close_Segment ();
    HC_Close_Segment ();   /* library/line */

    HC_Open_Segment ("?draw");
        HC_Set_Color ("faces = red, text = black, edges = cyan");
        HC_Set_Edge_Weight (1.0);
        HC_Set_Face_Pattern ("==");
        HC_Set_Visibility ("edges = on, markers = off");

	HC_Open_Segment ("?draw/local ");
	  HC_Set_Window (-1.0, -0.33, 0.0, 1.0);
          HC_Insert_Grid ("quadrilateral", &grid, &ref1, &ref2, 10, 10);
          HC_Set_Color ("faces = green, edges = dark green");
          HC_Set_Edge_Weight (2.0);
          HC_Set_Edge_Pattern ("-- --");
          HC_Set_Face_Pattern ("//");
          HC_Insert_Text (0.0, -0.85, 0.0, "quad green, face = //, edge = dk green, -- --");
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/style");
	  HC_Set_Window (-0.33, 0.33, 0.0, 1.0);
          HC_Insert_Grid ("quadrilateral", &grid, &ref1, &ref2, 10, 10);
          HC_Style_Segment ("?include library/line");
          HC_Insert_Text (0.0, -0.85, 0.0, "quad blue, face = solid, edge = dk blue, ....");
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/include");
	  HC_Set_Window (0.33, 1.0, 0.0, 1.0);
          HC_Include_Segment ("?include library/line");
          HC_Insert_Text (0.0, -0.85, 0.0, "quad magenta, face = #, edge = violet, -.-.");
          HC_Insert_Text (0.0, -0.95, 0.0, "radial blue, face = solid, edge = dk blue, ....");
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/parent");
	  HC_Set_Window (-1.0, -0.33, -1.0, 0.0);
          HC_Insert_Grid ("quadrilateral", &grid, &ref1, &ref2, 10, 10);
          HC_Insert_Text (0.0, -0.85, 0.0, "quad red, face = ==, edge = cyan, -...");
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/include2");
	  HC_Set_Window (-0.33, 0.33, -1.0, 0.0);
          HC_Include_Segment ("?include library/line/geom1");
          HC_Insert_Text (0.0, -0.85, 0.0, "quad magenta, face = #, edge = violet, -.-.");
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/include3");
	  HC_Set_Window (0.33, 1.0, -1.0, 0.0);
          HC_Include_Segment ("?include library/line/geom2");
          HC_Insert_Text (0.0, -0.85, 0.0, "radial red, face = ==, edge = cyan, -...");
        HC_Close_Segment ();
    HC_Close_Segment ();

    HC_Update_Display ();
    HC_Show_Time (&stop_time);

    post_memory ();
    post_results ("attributes from local, style, include, parent");
    post_time (3, start_time, stop_time);
}

void test_marker (void) {
    float		start_time,
			stop_time;

    identify_test ("?buttons/marker");
    HC_Update_Display ();

    HC_Show_Time (&start_time);

    HC_Open_Segment ("?include library/line");
        HC_Set_Color ("markers = blue");
        HC_Set_Marker_Symbol("<*>");
        HC_Set_Marker_Size (2.0);

        HC_Open_Segment ("?include library/line/geom1");
          HC_Insert_Marker(0.0, 0.0, 0.0);
          HC_Set_Color ("markers = magenta");
          HC_Set_Marker_Symbol("*");
          HC_Set_Marker_Size (1.5);
        HC_Close_Segment ();

        HC_Open_Segment ("?include library/line/geom2");
          HC_Insert_Marker(0.5, 0.5, 0.0);
        HC_Close_Segment ();
    HC_Close_Segment ();   /* library/line */

    HC_Open_Segment ("?draw");
        HC_Set_Visibility ("markers = on");
        HC_Set_Color ("markers = red, text = black");
        HC_Set_Marker_Symbol("(+)");
        HC_Set_Marker_Size (.5);

	HC_Open_Segment ("?draw/local ");
	  HC_Set_Window (-1.0, -0.33, 0.0, 1.0);
          HC_Set_Color ("markers = green");
          HC_Set_Marker_Symbol("(x)");
          HC_Set_Marker_Size (5.0);
          HC_Insert_Marker(0.0, 0.0, 0.0);
	  HC_Insert_Text (0.0, -0.85, 0.0, "green: large centered circle with X ");
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/style");
	  HC_Set_Window (-0.33, 0.33, 0.0, 1.0);
          HC_Insert_Marker (0.0, 0.0, 0.0);
          HC_Style_Segment ("?include library/line");
	  HC_Insert_Text (0.0, -0.85, 0.0, "blue: centered diamond");
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/include");
	  HC_Set_Window (0.33, 1.0, 0.0, 1.0);
          HC_Include_Segment ("?include library/line");
	  HC_Insert_Text (0.0, -0.85, 0.0, "magenta centered asterisk");
	  HC_Insert_Text (0.0, -0.95, 0.0, "blue: upper right, diamond");
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/parent");
	  HC_Set_Window (-1.0, -0.33, -1.0, 0.0);
          HC_Insert_Marker (0.0, 0.0, 0.0);
	  HC_Insert_Text (0.0, -0.85, 0.0, "red, centered small cirle with +");
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/include2");
	  HC_Set_Window (-0.33, 0.33, -1.0, 0.0);
          HC_Include_Segment ("?include library/line/geom1");
	  HC_Insert_Text (0.0, -0.85, 0.0, "magenta centered asterisk");
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/include3");
	  HC_Set_Window (0.33, 1.0, -1.0, 0.0);
          HC_Include_Segment ("?include library/line/geom2");
	  HC_Insert_Text (0.0, -0.85, 0.0, "red, upper right small cirle with +");
        HC_Close_Segment ();
    HC_Close_Segment ();

    HC_Update_Display ();
    HC_Show_Time (&stop_time);

    post_memory ();
    post_results ("attributes from local, style, include, parent");
    post_time (3, start_time, stop_time);
}

void test_line (void) {
    float		start_time,
			stop_time;

    identify_test ("?buttons/line");
    HC_Update_Display ();

    HC_Show_Time (&start_time);

    HC_Open_Segment ("?include library/line");
	HC_Set_Color ("polylines = blue");
        HC_Set_Line_Weight (7.0);
        HC_Set_Line_Pattern ("....");

      HC_Open_Segment ("?include library/line/geom1");
          HC_Insert_Line (-0.9,	-0.9, 0.0, 0.9, 0.9, 0.0);
	  HC_Set_Color ("polylines = magenta");
          HC_Set_Line_Weight (50.0);
          HC_Set_Line_Pattern ("-.-.");
      HC_Close_Segment ();

      HC_Open_Segment ("?include library/line/geom2");
          HC_Insert_Line (0.9, -0.9, 0.0, -0.9, 0.9, 0.0);
      HC_Close_Segment ();
    HC_Close_Segment ();   /* library/line */

    HC_Open_Segment ("?draw");
	HC_Set_Color ("polylines = red, text = black");
	HC_Set_Line_Weight (1.0);
	HC_Set_Line_Pattern ("-...");
	HC_Set_Heuristics ("no hidden surfaces");

	HC_Open_Segment ("?draw/local ");
	  HC_Set_Window (-1.0, -0.33, 0.0, 1.0);
          HC_Insert_Line (-0.9,	-0.9, 0.0, 0.9, 0.9, 0.0);
	  HC_Set_Color ("polylines = green");
          HC_Set_Line_Weight (25.0);
          HC_Set_Line_Pattern ("-- --");
          HC_Open_Segment ("text");
	    HC_Insert_Text (0.0, -0.85, 0.0, "lower left to upper rt, green, 25, -- --");
	  HC_Close_Segment ();
	    HC_Bring_To_Front ("text");
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/style");
	  HC_Set_Window (-0.33, 0.33, 0.0, 1.0);
          HC_Insert_Line (-0.9,	-0.9, 0.0, 0.9, 0.9, 0.0);
          HC_Style_Segment ("?include library/line");
	  HC_Insert_Text (0.0, -0.85, 0.0, "lower left to upper rt, blue, 7.0, ....");
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/include");
	  HC_Set_Window (0.33, 1.0, 0.0, 1.0);
          HC_Include_Segment ("?include library/line");
          HC_Open_Segment ("text");
	    HC_Insert_Text (0.0, -0.85, 0.0, "lower left to upper rt, magenta, 50, -.-.");
	    HC_Insert_Text (0.0, -0.95, 0.0, "upper left to lower rt, blue, 7.0, ....");
          HC_Close_Segment ();
          HC_Bring_To_Front ("text");
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/parent");
	  HC_Set_Window (-1.0, -0.33, -1.0, 0.0);
          HC_Insert_Line (-0.9,	-0.9, 0.0, 0.9, 0.9, 0.0);
	  HC_Insert_Text (0.0, -0.85, 0.0, "lower left to upper rt, red, 1, -...");
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/include2");
	  HC_Set_Window (-0.33, 0.33, -1.0, 0.0);
          HC_Include_Segment ("?include library/line/geom1");
          HC_Open_Segment ("text");
	    HC_Insert_Text (0.0, -0.85, 0.0, "lower left to upper rt, magenta, 50, -.-.");
          HC_Close_Segment ();
          HC_Bring_To_Front ("text");
        HC_Close_Segment ();

        HC_Open_Segment ("?draw/include3");
	  HC_Set_Window (0.33, 1.0, -1.0, 0.0);
          HC_Include_Segment ("?include library/line/geom2");
	  HC_Insert_Text (0.0, -0.85, 0.0, "upper left to lower rt, red, 1, -...");
        HC_Close_Segment ();
    HC_Close_Segment ();

    HC_Update_Display ();
    HC_Show_Time (&stop_time);

    post_memory ();
    post_results ("attributes from local, style, include, parent");
    post_time (3, start_time, stop_time);
}

void process_input (void) {
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

	if (strcmp (event, "none") == 0) {
		HC_Exit_Program ();
	}

	/*
	 * decide if the user hit enter (next test)
	 * or clicked on a specific test to run and
	 * set the test number (test to run) accordingly
	 */
	if (strcmp (event, "selection") == 0) {
	    HC_Show_Selection (selection);
	    if (strcmp (selection, "line") == 0)
		test_number = 1;
	    else if (strcmp (selection, "polygon") == 0)
		test_number = 2;
	    else if (strcmp (selection, "circle") == 0)
		test_number = 3;
	    else if (strcmp (selection, "ellipse") == 0)
		test_number = 4;
	    else if (strcmp (selection, "mesh") == 0)
		test_number = 5;
	    else if (strcmp (selection, "shell") == 0)
		test_number = 6;
	    else if (strcmp (selection, "polyline") == 0)
		test_number = 7;
	    else if (strcmp (selection, "cutting plane") == 0)
		test_number = 8;
	    else if (strcmp (selection, "grid") == 0)
		test_number = 9;
	    else if (strcmp (selection, "image") == 0)
		test_number = 10;
	    else if (strcmp (selection, "ink") == 0)
		test_number = 11;
	    else if (strcmp (selection, "marker") == 0)
		test_number = 12;
	    else if (strcmp (selection, "text") == 0)
		test_number = 13;
	    else if (strcmp (selection, "font") == 0)
		test_number = 14;
	    else if (strcmp (selection, "quit") == 0)
		test_number = 15;
	    else if (strcmp (selection, "reset") == 0)
		test_number = 16;
	    else
		test_number = 17;
	}
	else {
	    HC_Show_Button (selection);
	    if (strcmp (selection, "q") == 0)
		test_number = 15;
	    else
		test_number++;
	}

	/*
	 * run the desired test based on how
	 * test number was set above
	 */
	switch (test_number) {
	    case 1: {
		test_line ();
	    }   break;

	    case 2: {
		test_polygon ();
	    }   break;

	    case 3: {
		test_circle ();
	    }   break;

	    case 4: {
		test_ellipse ();
	    }   break;

	    case 5: {
		test_mesh ();
	    }   break;

	    case 6: {
		test_shell ();
	    }   break;

	    case 7: {
		test_polyline ();
	    }   break;

	    case 8: {
		test_cutting_plane ();
	    }   break;

	    case 9: {
		test_grid ();
	    }   break;

	    case 10: {
		test_image ();
	    }   break;

	    case 11: {
		test_ink ();
	    }   break;

	    case 12: {
		test_marker ();
	    }   break;

	    case 13: {
		test_text ();
	    }   break;

	    case 14: {
		test_font ();
	    }   break;

	    case 15: {
		keep_testing = FALSE;
	    }   break;

	    case 16: {
		HC_Disable_Button_Events ("?picture", "anything");
		HC_Disable_Selection_Events ("?picture", "?picture");

		HC_Reset_System ();
		init_results ();
		setup_window_structure ();
		test_number = 0;
		HC_Enable_Button_Events ("?picture", "anything");
		HC_Enable_Selection_Events ("?picture", "?picture");
	    }   break;

	    case 17: {
	    }   break;

	    default: {
	    }
	}
    }
    HC_Exit_Program ();
}

int main () {
    init_results ();
    setup_window_structure ();
    process_input ();
    return 0;
}
