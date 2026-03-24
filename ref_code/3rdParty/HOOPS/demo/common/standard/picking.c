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
 * $Id: picking.c,v 1.4 2010-10-26 21:29:09 jason Exp $
 */

#include "hc.h"
#include "hc_standalone.h"
#include <math.h>
#include <string.h>

typedef struct {float x, y, z;} Point;

#define BY_POLYGON (-1)
#define BY_POLYLINE 1

#define FIGURE_SIZE 8

int main (
    int		argc,
    char	**argv) {
    int		count = FIGURE_SIZE;
    Point	pts[FIGURE_SIZE];
    int		mode = BY_POLYGON;

    pts[0].x =  -0.5f;  pts[0].y = -0.25f; pts[0].z = 0.0f;
    pts[1].x =  -0.5f;  pts[1].y =  0.25f; pts[1].z = 0.0f;
    pts[2].x =  -0.25f; pts[2].y =  0.5f;  pts[2].z = 0.0f;
    pts[3].x =   0.25f; pts[3].y =  0.5f;  pts[3].z = 0.0f;
    pts[4].x =   0.5f;  pts[4].y =  0.25f; pts[4].z = 0.0f;
    pts[5].x =   0.5f;  pts[5].y = -0.25f; pts[5].z = 0.0f;
    pts[6].x =   0.25f; pts[6].y = -0.5f;  pts[6].z = 0.0f;
    pts[7].x =  -0.25f; pts[7].y = -0.5f;  pts[7].z = 0.0f;

    HC_Open_Segment ("?style library/selected");
        HC_Set_Color ("geometry = red");
    HC_Close_Segment ();

    HC_Open_Segment ("?picture");
	HC_Set_Heuristics ("concave polygons");
        HC_Set_Color ("windows = black, window contrast = white");
        HC_Open_Segment ("work area");
            HC_Set_Window (-1.0, 1.0, -0.8, 1.0);
            HC_Set_Heuristics ("concave polygons, intersecting polygons");
            HC_Set_Color ("geometry = green");
            HC_Open_Segment ("victim");
                HC_Insert_Polygon (count, pts);
                HC_Scale_Object (0.1, 0.1, 0.1);
            HC_Close_Segment ();
            HC_Open_Segment ("aperture");
                HC_Set_Color ("white");
                HC_Open_Segment ("figure");
                    HC_Set_Visibility ("edges = off");
                    HC_Insert_Polyline (count, pts);
                    HC_Insert_Polygon (count, pts);
                    HC_Scale_Object (0.7, 0.7, 0.7);
                HC_Close_Segment ();
            HC_Close_Segment ();
	HC_Close_Segment ();
        HC_Open_Segment ("message area");
            HC_Set_Selectability ("off");
            HC_Set_Window (-1.0, 1.0, -1.0, -0.8);
            HC_Set_Color ("text = white");
            HC_Insert_Text (0.0, 0.5, 0.0,
			    "Drag the white selector.");
            HC_Insert_Text (0.0, -0.5, 0.0,
			    "Hit 'Q' to quit, or any other key to toggle mode.");
        HC_Close_Segment ();
    HC_Close_Segment ();

    HC_Enable_Button_Events ("?keyboard", "anything");
    HC_Enable_Selection_Events ("?locater", "?picture");

    for (;;) {
	HC_KEY	key;
	int	junki;
	float	junkf;
	float	xc, yc, zc;
	char	type[256];
	float	transform[4][4];
	Point	pixel_pts[FIGURE_SIZE];
	int	got_one;

	HC_QSet_Selectability ("?picture/work area",
			       "window = v*, geometry = off");
	HC_Await_Event (type);

	if (strcmp (type, "none") == 0) {
	    HC_Exit_Program ();
	}

	HC_QSet_Selectability ("?picture/work area", "off");

	if (!strcmp (type, "button")) {
	    HC_Show_Button (type);
	    if (!strcmp (type, "Q") || !strcmp (type, "q"))
		HC_Exit_Program ();
	    else
		mode = -mode;

	    if (mode == BY_POLYGON)
		HC_QSet_Visibility ("?picture/work area/aperture",
				    "faces = on, lines = off");
	    else
		HC_QSet_Visibility ("?picture/work area/aperture",
				    "faces = off, lines = on");
	}
	else {
	    /*
	     * Move the aperture to the position of the mouse
	     */
	    HC_Open_Segment ("?picture/work area/aperture");
	        HC_UnSet_Modelling_Matrix ();
	        HC_Show_Selection_Position (&junkf, &junkf, &junkf,
					    &xc, &yc, &zc);
	        HC_Translate_Object (xc, yc, zc);
		HC_Update_Display ();
	    HC_Close_Segment ();
	}

	/*
	 * Restore victim to its unhighlighted state
	 */
	HC_Flush_Contents ("?picture/work area/victim/...", "styles");

	/*
	 * Select the victim
	 */
	HC_Compute_Transform ("?picture/work area/aperture/figure",
			      "object",
			      "outer window",
			      &transform[0][0]);
	HC_Compute_Transformed_Points (count, (float *)pts, &transform[0][0],
				       (float *)pixel_pts);

	HC_QSet_Selectability ("?picture/work area/victim", "geometry = on");

	if (mode == BY_POLYGON)
	    got_one = HC_Compute_Selection_By_Polygon ("?picture", "", "v",
						       count,
						       (float *)pixel_pts);
	else
	    got_one = HC_Compute_Selection_By_Polylin ("?picture", "", "v",
						       count,
						       (float *)pixel_pts);

	HC_QSet_Selectability ("?picture/work area/victim", "geometry = off");

	if (got_one > 0) {
	    do {
		char	type[256];

		HC_Show_Selection_Element (&key, &junki, &junki, &junki);
		HC_Show_Key_Type (key, type);
		if (strcmp (type, "segment")) {
		    key = HC_KShow_Owner_By_Key (key);
		    HC_Open_Segment_By_Key (key);
			HC_Style_Segment ("?style library/selected");
		    HC_Close_Segment ();
		}
	    } while (HC_Find_Related_Selection ());
	}

    }
    return 0;
}
