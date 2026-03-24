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
 * $Id: bvolume.c,v 1.3 2010-10-26 21:29:09 jason Exp $
 */

#include "hc.h"
#include "hc_standalone.h"
#include <stdio.h>
#include <string.h>

#define ROWS 50
#define COLS 50

#define TRUE  1
#define FALSE 0

int main (int argc, char **argv) {
    int		row, col, keep_testing;

    HC_Open_Segment ("?include library/star");
	HC_Scale_Object (1.0/ROWS, 1.0/COLS, 1.0);
	HC_Insert_Line (-1.0, -1.0, 0.0, 1.0, 1.0, 0.0);
	HC_Insert_Line (-1.0,  1.0, 0.0, 1.0, -1.0, 0.0);
	HC_Insert_Line ( 0.0, -1.0, 0.0, 0.0, 1.0, 0.0);
	HC_Insert_Line (-1.0,  0.0, 0.0, 1.0, 0.0, 0.0);
    HC_Close_Segment ();

    HC_Open_Segment ("?picture");
	HC_Set_Color ("windows = black, window contrast = white");
	HC_Set_Camera_Projection ("stretched");
	for (row = 0; row < ROWS; ++row) {
	    HC_Open_Segment ("");
		HC_Set_Color_By_Value ("lines", "hls",
				       360.0 * row / ROWS, 0.5, 1.0);
		for (col = 0; col < COLS; ++col) {
		    HC_Open_Segment ("");
			HC_Translate_Object (2.0 * row / ROWS - 1.0,
					     2.0 * col / COLS - 1.0, 0.0);
			HC_Include_Segment ("?include library/star");
		    HC_Close_Segment ();
		}
	    HC_Close_Segment ();
	}

	HC_Enable_Selection_Events ("?picture", "?picture");
	HC_Enable_Button_Events ("?picture", "anything");
	HC_Set_Selectability ("v");

	keep_testing = TRUE;
	while (keep_testing) {
	    char	event[256];

	    HC_Await_Event (event);

	    if (strcmp (event, "none") == 0) {
	    	HC_Exit_Program ();
	    }

	    if (!strcmp (event, "button")) {
		char	button[256];
		float	start_time, stop_time;
		int	i;

		HC_Show_Button (button);
		switch (button[0]) {
		  case 'i':
		  case 'I':
		    HC_Zoom_Camera (1.01);
		    break;

		  case 'o':
		  case 'O':
		    HC_Zoom_Camera (1.0 / 1.01);
		    break;

		  case 'r':
		  case 'R':
		    HC_UnSet_Camera ();
		    break;

		  case 't':
		  case 'T':
		    HC_UnSet_Camera ();
		    HC_Define_System_Options ("no bounding volumes");
		    HC_Update_Display ();

		    HC_Show_Time (&start_time);
		    for (i = 0; i < 10; i++) {
			HC_Zoom_Camera (1.25);
			HC_Update_Display ();
		    }
		    HC_Show_Time (&stop_time);
		    printf ("Bounding volumes OFF: %f seconds\n",
			    stop_time - start_time);
		    fflush (stdout);

		    HC_UnSet_Camera ();
		    HC_Define_System_Options ("bounding volumes");
		    HC_Update_Display ();

		    HC_Show_Time (&start_time);
		    for (i = 0; i < 10; i++) {
			HC_Zoom_Camera (1.25);
			HC_Update_Display ();
		    }
		    HC_Show_Time (&stop_time);
		    printf ("Bounding volumes ON:  %f seconds\n",
			    stop_time - start_time);
		    fflush (stdout);
		    break;

		  case 'q':
		  case 'Q':
		    keep_testing = FALSE;
		    break;
		}
	    }
	    else if (!strcmp (event, "selection")) {
		float	junkf;
		float	x0, x1, y0, y1;

		HC_Show_Selection_Location (&junkf, &junkf, &x0, &y0, &junkf);
		HC_Set_Selectability ("^*");
		event[0] = '\0';
		while (event[0] != '^') {
		    char	junks[256];
		    int		junki;

		    HC_Await_Event (event);
		    HC_Show_Selection_Source (junks, junks, event, &junki);
		    HC_Show_Selection_Location (&junkf, &junkf, &x1, &y1, &junkf);
		    HC_Dolly_Camera ((double)(x0 - x1), (double)(y0 - y1), 0.0);
		}
		HC_Set_Selectability ("v");
	    }
	}
    HC_Close_Segment ();
    HC_Exit_Program ();
    return 0;
}
