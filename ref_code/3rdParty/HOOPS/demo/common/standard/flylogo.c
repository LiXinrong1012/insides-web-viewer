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
 * $Id: flylogo.c,v 1.8 2010-10-26 21:29:09 jason Exp $
 */

/*
 * See the important NOTE below.
 */

typedef struct {
    float x, y, z;
} Point;
#define HT_POINT Point;
#include "hc.h"
#include "hc_standalone.h"

#include <stdlib.h>
#include <math.h>

int main (int argc, char **argv) {
    int		pcount;
    Point	*points;
    int         flist_length;
    int         *face_list;
    HC_KEY      light;
    float       theta;
    char	*message;

    HC_Open_Segment ("?picture");

    	HC_Set_Driver_Options("double-buffering, special events");

	if (argc > 1)
	    message = argv[1];
	else
	    message = "Hoops";

	/*
	 * NOTE:  You should set the font "name" here to
	 *        be a font with an outline representation,
	 *        such as a TrueType, Adobe Type 1, or Speedo Font.
	 *	  If you comment out the name specification below,
	 *        you could also set it externally in HOOPS_TEXT_FONT.
	 *        The program will not operate without this setting.
	 */
	HC_Set_Text_Font ("name = Arial, size = 120 pt");

	/* Determine if the font even has an outline */
        {
 	    char	    font_name[256];
	    char	    outlineable[256];

            HC_Show_One_Net_Text_Font ("name", font_name);
	    HC_Show_Font_Info (".", font_name, "outlineable", outlineable);
	    if (outlineable[0] != 'y')
		HC_Exit_Program ();
        }

	/* Find out how much space we'll need */
	HC_Compute_Text_Outline_Size (".", message, &pcount, &flist_length);
	if (pcount <= 0)
	    HC_Exit_Program ();

	/* Get some arrays to hold the glyphs' geometric data */
	face_list = (int *)malloc (flist_length * sizeof (int));
	points = (Point *)malloc (pcount * sizeof (Point));

	/* Get that geometric data for some text string */
	HC_Compute_Text_Outline (".", message, &pcount, &points[0],
				 &flist_length, &face_list[0]);
	if (pcount <= 0)
	    HC_Exit_Program ();

	/*
	 * Now do something interesting with the glyphs...
	 */
#if 0
	HC_Set_Rendering_Options("lighting=phong");
#endif
	HC_Set_Color ("faces = (red, gloss = 60), windows = black, lights = white, edges=yellow");
	HC_Set_Visibility ("edges, no markers");
	HC_Set_Visibility ("lights=no edges");
	HC_Set_Heuristics ("no hidden surfaces");

	HC_Open_Segment ("letters"); {
	    Point           center;
	    float           radius;

	    /* See how handy?  It's already in shell format */
	    HC_KEY key = HC_KInsert_Shell (pcount, &points[0], flist_length, &face_list[0]);

	    HC_Open_Geometry(key);
	    HC_Open_Face(0);
		HC_Set_Normal(0,0,-1);
	    HC_Close_Face();
	    HC_Close_Geometry(); 

	    free (face_list);
	    free (points);

	    /* HC_Write_Metafile (".", "flying.hmf", ""); */

	    /* Center it and scale it to fit in the window */
	    HC_Compute_Circumsphere (".", &center, &radius);
	    if (radius > 0.0f) {
		HC_Translate_Object (-center.x, -center.y, -center.z);
		HC_Scale_Object (1.0 / (double)radius,
				 1.0 / (double)radius,
				 1.0);
	    }
	} HC_Close_Segment ();

	/* Light up the scene */
	{
	    Point           position;
	    Point           target;

	    position.x = 0.15f;
	    position.y = 0.0f;
	    position.z = -1.0f;
	    target.x = 0.0f;
	    target.y = 0.0f;
	    target.z = 0.0f;

	    light = HC_KInsert_Spot_Light (&position, &target, "");
	}

	/* Play the spotlight across the letters */
	HC_Enable_Selection_Events ("?locater", "?picture");
	HC_Enable_Button_Events ("?keyboard", "anything");
	theta = 0.0f;
	while (!HC_Check_For_Events ()) {
	    HC_Move_Light_Target (light,
				  -1.5 * cos (theta),
				  0.3 * sin (theta * 2.0),
				  0.0);
	    HC_Update_Display ();
	    theta += 0.05f;
	}
    HC_Close_Segment ();

    HC_Exit_Program ();
    return 0;
}
