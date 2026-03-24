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
 * $Id: qmoves.c,v 1.3 2010-10-26 21:29:09 jason Exp $
 */

/*
 * Test of quickmoves on various types of geometry
 *
 * Note: The X11 multibuffering capabilities of some
 * Unix platforms have trouble with XOR drawing.
 * IRIX is one example. For these platforms, the
 * symptoms that arise are that some geometries are
 * missing. When this occurs, the debug driver option
 * (debug = 16) set for the X11 driver alleviates the
 * deficiency.
 */

#include "hc.h"
#include "hc_standalone.h"

static	float	polyline[] = {	-0.5f, 0.9f, 0.1f,
				-0.25f, 0.5f, 0.0f,
				-0.55f, 0.3f, 0.0f,
				-0.2f, 0.2f, 0.0f	};
static	float	circ_pt1[] = {	0.7f, 0.5f, 0.1f },
		circ_pt2[] = {	0.8f, 0.6f, 0.1f },
		circ_pt3[] = {	0.9f, 0.5f, 0.1f };

static	float	polygon[] = {	-0.9f, -0.2f, 0.1f,
				-0.8f, -0.7f, 0.0f,
				-0.7f, -0.5f, 0.0f };

static	float	shell_pts[] = {	-0.1f, -0.2f, 0.1f,
				 0.0f, -0.7f, 0.0f,
				 0.1f, -0.5f, 0.0f };

static	int	shell_faces[] = { 3, 0, 1, 2 };

int main () {
    int		loop, dub_buf, dbcount;
    char	button[80];

    dub_buf = dbcount = 0;
    HC_Open_Segment ("?Picture");
	HC_Set_Window_Frame ("off");
	HC_Set_Driver_Options ("no double-buffering");
	HC_Set_Color ("windows = white, window contrast = red, text = black");
	HC_Set_Camera_Projection ("s");
	HC_Open_Segment ("instructions");
	    HC_Set_Text_Font ("size = 0.02 sru");
	    HC_Set_Text_Alignment ("*^");
	    HC_Set_Heuristics ("no quick moves");
	    HC_Insert_Text (0.0, 0.99, 0.0, "Test of Quick-Moves");
	    HC_Insert_Text (0.0, 0.9, 0.0,
		"The text labels should not flash.");
	    HC_Insert_Text (0.0, 0.8, 0.0,
		"Type Q to quit, any other key to animate.");
	HC_Close_Segment ();
	HC_Open_Segment ("labels");
	    HC_Set_Text_Alignment ("<v");
	    HC_Set_Text_Font ("size = 0.015 sru");
	    HC_Set_Heuristics ("no quick moves");
	    HC_Insert_Text (0.2, -0.9, 0.0, "Turquoise --- Shell Edges");
	    HC_Insert_Text (0.6, -0.99, 0.0, "Orange solid Shell Faces");
	    HC_Insert_Text (-0.2, -0.99, 0.0, "Gray Shell Vertices");
	    HC_Insert_Text (-0.6, -0.9, 0.0, "Tan -..-.. Polygon Edges");
	    HC_Insert_Text (-0.99, -0.99, 0.0, "Red # on Yellow Polygon Faces");
	    HC_Open_Segment ("");
		HC_Set_Text_Alignment (">*");
	        HC_Insert_Text (0.99, 0.0, 0.0, "Cyan Face, Blue Edge Circle");
	    HC_Close_Segment ();
	    HC_Insert_Text (0.2, 0.1, 0.0, "Magenta Text");
	    HC_Insert_Text (-0.2, 0.0, 0.0, "Blue Marker");
	    HC_Insert_Text (-0.6, 0.1, 0.0, "Thin Green .... Polyline");
	    HC_Insert_Text (-0.99, 0.0, 0.0, "Wide Red -.-. Line");
	HC_Close_Segment ();
	HC_Open_Segment ("objects");
	    HC_Set_Heuristics ("quick moves");
	    HC_Open_Segment ("line");
		HC_Set_Color ("lines = red");
		HC_Set_Line_Pattern ("-.-.");
		HC_Set_Line_Weight (4.0);
		HC_Insert_Line (-0.9, 0.9, 0.0, -0.7, 0.25, 0.1);
	    HC_Close_Segment ();
	    HC_Open_Segment ("polyline");
		HC_Set_Color ("lines = green");
		HC_Set_Line_Pattern ("....");
		HC_Insert_Polyline (4, polyline);
	    HC_Close_Segment ();
	    HC_Open_Segment ("marker");
		HC_Set_Color ("markers = blue");
		HC_Set_Marker_Symbol ("X");
		HC_Set_Marker_Size (2.0);
		HC_Insert_Marker (0.0, 0.3, 0.1);
	    HC_Close_Segment ();
	    HC_Open_Segment ("text");
		HC_Set_Color ("text = magenta");
		HC_Insert_Text (0.3, 0.5, 0.1, "Hello");
	    HC_Close_Segment ();
	    HC_Open_Segment ("circle");
		HC_Set_Color ("faces = cyan, edges = blue");
		HC_Set_Visibility ("edges = on, faces = on");
		HC_Set_Edge_Weight (6.0);
		HC_Insert_Circle (circ_pt1, circ_pt2, circ_pt3);
	    HC_Close_Segment ();
	    HC_Open_Segment ("polygon faces");
		HC_Set_Color ("faces = yellow, face contrast = red");
		HC_Set_Face_Pattern ("#");
		HC_Set_Visibility ("edges = off, faces = on");
		HC_Insert_Polygon (3, polygon);
	    HC_Close_Segment ();
	    HC_Open_Segment ("polygon edges");
		HC_Set_Color ("edges = tan");
		HC_Set_Visibility ("edges = on, faces = off");
		HC_Set_Edge_Pattern ("-..-..");
		HC_Insert_Polygon (3, polygon);
		HC_Translate_Object (0.4, 0.0, 0.0);
	    HC_Close_Segment ();
	    HC_Open_Segment ("shell vertices");
		HC_Set_Color ("markers = gray");
		HC_Set_Visibility ("markers = on, edges = off, faces = off");
		HC_Insert_Shell (3, shell_pts, 4, shell_faces);
	    HC_Close_Segment ();
	    HC_Open_Segment ("shell edges");
		HC_Set_Color ("edges = turquoise");
		HC_Set_Visibility ("markers = off, edges = on, faces = off");
		HC_Translate_Object (0.4, 0.0, 0.0);
		HC_Insert_Shell (3, shell_pts, 4, shell_faces);
	    HC_Close_Segment ();
	    HC_Open_Segment ("shell faces");
		HC_Set_Color ("faces = orange");
		HC_Set_Visibility ("markers = off, edges = off, faces = on");
		HC_Translate_Object (0.8, 0.0, 0.0);
		HC_Insert_Shell (3, shell_pts, 4, shell_faces);
	    HC_Close_Segment ();
	HC_Close_Segment ();

    for (;;) {
	for (loop = 0; loop < 8; loop++) {
	    HC_QRotate_Object ("?Picture/objects", 0.0, 0.0, 45.0);
	    HC_Update_Display ();
	}
	HC_Get_Button (button);

	if (++dbcount == 4) {
	    dbcount = 0;

	    if (dub_buf) {
		dub_buf = 0;
		HC_QSet_Driver_Options ("?Picture", "no double-buffering");
	    }
	    else {
		dub_buf = 1;
		HC_QSet_Driver_Options ("?Picture", "double-buffering");
	    }
	}

	if (button[0] == 'q' || button[0] == 'Q') break;
    }
    HC_Close_Segment ();
    HC_Exit_Program ();
    return 0;
}
