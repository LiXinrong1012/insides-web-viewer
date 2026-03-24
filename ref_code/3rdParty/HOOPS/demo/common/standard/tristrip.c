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
 * $Id: tristrip.c,v 1.6 2010-10-26 21:29:09 jason Exp $
 */

/*
 * WARNING: HOOPS I.M. is needed to compile this program.
 */

#include "hc.h"
#include "hc_standalone.h"
#include "hic.h"
#include <stdio.h>
#include <string.h>

HIC_RGB colors[5000];
float rgb[3];
float find[5000];
int   mode;

void tristrip (
    HIC_Rendition const	*r,
    HIC_Tristrip const	*ts) {

    if (mode == 0)
		HIC_Draw_3D_Tristrip (r, ts);
    else {
		HIC_Tristrip const *nts = HIC_New_Tristrip (ts);

		switch (mode) {
			case 1:
			break;

			case 2:
			HIC_Set_Tristrip_Face_Colors (nts, colors);
			break;

			case 3:
			HIC_Set_Tristrip_Vertex_Colors (nts, colors);
			break;

			case 4:
			HIC_Set_Tristrip_Vertex_Findices (nts, find);
			HIC_Set_Tristrip_Findex_Color_Interpolation (nts, 0);
			break;

			case 5:
			HIC_Set_Tristrip_Vertex_Findices (nts, find);
			HIC_Set_Tristrip_Findex_Color_Interpolation (nts, 1);
			break;
		}

		HIC_Draw_3D_Tristrip (r, nts);
		HIC_Free_Tristrip (nts);
    }
}

void polyedge (
    HIC_Rendition const	*r,
    HIC_Polyedge const	*pe) {

    if (mode == 0)
		HIC_Draw_3D_Polyedge (r, pe);
    else {
		HIC_Polyedge const *npe = HIC_New_Polyedge (pe);

		switch (mode) {
			case 1:
			break;

			case 2:
			HIC_Set_Polyedge_Edge_Colors (npe, colors);
			break;

			case 3:
			HIC_Set_Polyedge_Vertex_Colors (npe, colors);
			break;

			case 4:
			HIC_Set_Polyedge_Vertex_Findices (npe, find);
			HIC_Set_Polyedge_Findex_Color_Interpolation (npe, 0);
			break;

			case 5:
			HIC_Set_Polyedge_Vertex_Findices (npe, find);
			HIC_Set_Polyedge_Findex_Color_Interpolation (npe, 1);
			break;
		}

		HIC_Draw_3D_Polyedge (r, npe);
		HIC_Free_Polyedge (npe);
    }
}

void polymarker (
    HIC_Rendition const	*r,
    HIC_Polymarker const	*pm) {

    if (mode == 0)
		HIC_Draw_3D_Polymarker (r, pm);
    else {
		HIC_Polymarker const *npm = HIC_New_Polymarker (pm);

		switch (mode) {
			case 1:
			break;

			case 2:
			case 3:
			HIC_Set_Polymarker_Vertex_Colors (npm, colors);
			break;

			case 4:
			HIC_Set_Polymarker_Vertex_Findices (npm, find);
			HIC_Set_Polymarker_Findex_Color_Interpolation (npm, 0);
			break;

			case 5:
			HIC_Set_Polymarker_Vertex_Findices (npm, find);
			HIC_Set_Polymarker_Findex_Color_Interpolation (npm, 1);
			break;
		}

		HIC_Draw_3D_Polymarker (r, npm);
		HIC_Free_Polymarker (npm);
    }
}

void pause (void) {
    char	dummy[32];

    HC_Await_Event (dummy);
    	
    if (strcmp (dummy, "none") == 0) {
      	HC_Exit_Program ();
    }

    if (dummy[0] == 'b') {
		HC_Show_Button (dummy);
		if (dummy[0] == 'q')
			HC_Exit_Program ();
    }
}

int main (int argc, char **argv) {
    float	hls[3];
    int		ii;
    float	center[3], radius;

    if (argc <= 2 || !sscanf (argv[2], "%f", &radius))
	radius = 0.035f;

    hls[0] = 0.0f;
    hls[1] = 0.5f;
    hls[2] = 1.0f;

    for (ii = 0; ii < 5000; ii++) {
		HC_Compute_Color_By_Value ("hls", hls, "rgb", rgb);
		colors[ii].red = rgb[0];
		colors[ii].green = rgb[1];
		colors[ii].blue = rgb[2];
		if ((hls[0] += (float)ii) > 50000.0f)
			hls[0] = 0.0f;

		find[ii] = radius * (float)ii;
    }

    HC_Define_Callback_Name ("tristrip", tristrip);
    HC_Define_Callback_Name ("polyedge", polyedge);
    HC_Define_Callback_Name ("polymarker", polymarker);

    HC_Open_Segment ("?Include Library/urn");
	HC_Read_Metafile (argc > 1 ? argv[1] : "urn", ".", "restore state");
    HC_Close_Segment ();

    HC_Open_Segment ("?Picture");
	HC_Set_Callback ("draw 3d tristrips = tristrip");
	HC_Set_Callback ("draw 3d polyedges = polyedge");
	HC_Set_Callback ("draw 3d polymarkers = polymarker");
	HC_Set_Color_Map ("red, yellow, green, cyan, blue, white");
	HC_Set_Color ("window = gray, text = white");
	HC_Set_Marker_Symbol ("[*]");
	HC_Set_Marker_Size (0.25);
	HC_Rotate_Object (-20.0, 0.0, 0.0);

	HC_Compute_Circumsphere ("?Include Library/urn", center, &radius);
	if (radius > 0) {
	    HC_Set_Camera_Position ((double)center[0],
				    (double)center[1],
				    (double)(center[2] - radius * 5.0f));
	    HC_Set_Camera_Target ((double)center[0],
				  (double)center[1],
				  (double)center[2]);
	    HC_Set_Camera_Field ((double)radius * 2.0,
				 (double)radius * 2.0);
	}

	HC_Open_Segment ("upper left");
	    HC_Set_Window (-1.0, 0.0, 0.0, 1.0);
	    HC_Insert_Distant_Light (1.0, 1.0, -1.0);
	    HC_Set_Visibility ("no edges, no markers");
	    HC_Include_Segment ("?Include Library/urn");
	    HC_Insert_Text (0.0, 1.6, 0.0, "faces only");
	HC_Close_Segment ();

	HC_Open_Segment ("upper right");
	    HC_Set_Window (0.0, 1.0, 0.0, 1.0);
	    HC_Insert_Distant_Light (1.0, 1.0, -1.0);
	    HC_Set_Visibility ("no faces, no markers");
	    HC_Include_Segment ("?Include Library/urn");
	    HC_Insert_Text (0.0, 1.6, 0.0, "edges only");
	HC_Close_Segment ();

	HC_Open_Segment ("lower left");
	    HC_Set_Window (-1.0, 0.0, -1.0, 0.0);
	    HC_Insert_Distant_Light (1.0, 1.0, -1.0);
	    HC_Set_Visibility ("no faces, no edges");
	    HC_Include_Segment ("?Include Library/urn");
	    HC_Insert_Text (0.0, 1.6, 0.0, "markers only");
	HC_Close_Segment ();

	HC_Open_Segment ("lower right");
	    HC_Set_Window (0.0, 1.0, -1.0, 0.0);
	    HC_Insert_Distant_Light (1.0, 1.0, -1.0);
	    HC_Set_Callback ("draw 3d polyedges = null");
	    HC_Set_Visibility ("edges = mesh quads only, no markers");
	    HC_Set_Rendering_Options ("debug = 0x0400");
	    HC_Include_Segment ("?Include Library/urn");
	    HC_Insert_Text (0.0, 1.6, 0.0, "faces and quad edges");
	HC_Close_Segment ();

	HC_Enable_Button_Events ("?Keyboard", "anything");
	HC_Enable_Location_Events ("?Locater", "?Picture", "v");

	HC_Set_Visibility ("no lights");
	for (mode = 1; mode < 6; mode++) {
	    HC_Control_Update ("*", "redraw everything");
	    pause ();
	}

	HC_Set_Visibility ("lights");
	HC_Set_Rendering_Options ("no lighting interpolation");
	for (mode = 0; mode < 6; mode++) {
	    HC_Control_Update ("*", "redraw everything");
	    pause ();
	}

	HC_Set_Rendering_Options ("lighting interpolation");
	for (mode = 0; mode < 6; mode++) {
	    HC_Control_Update ("*", "redraw everything");
	    pause ();
	}
    HC_Close_Segment ();
    return 0;
}
