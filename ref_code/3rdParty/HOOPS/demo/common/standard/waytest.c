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
 * $Id: waytest.c,v 1.3 2006-08-07 20:38:49 stage Exp $
 */

#include "hc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Used to create a series of 20 windows,
 * 5 across, and 4 from top to bottom
 */
void size_window (
    int		position1,
    int		position2,
    char	*window_pattern) {
    double	left, right, top, bottom;

    switch (position1) {
	case 1: {
	    left  = -1.0;
	    right = -0.6;
	}   break;

	case 2: {
	    left  = -0.6;
	    right = -0.2;
	}   break;

	case 3: {
	    left  = -0.2;
	    right =  0.2;
	}   break;

	case 4: {
	    left  =  0.2;
	    right =  0.6;
	}   break;

	case 5: {
	    left  =  0.6;
	    right =  1.0;
	}   break;

	default: {
	    left  = -1.0;
	    right =  1.0;
	}
    }
    switch (position2) {
	case 1: {
	    top    =  1.0;
	    bottom =  0.5;
	}   break;

	case 2: {
	    top    =  0.5;
	    bottom =  0.0;
	}   break;

	case 3: {
	    top    =  0.0;
	    bottom = -0.5;
	}   break;

	case 4: {
	    top    = -0.5;
	    bottom = -1.0;
	}   break;

	default: {
	    top    =  1.0;
	    bottom = -1.0;
	}
    }
    HC_Set_Window (left, right, bottom, top);
    HC_Set_Window_Pattern (window_pattern);
    if (strcmp (window_pattern, "clear") == 0)
	HC_Set_Color ("windows = red");
}

/*
 * Used to set the three attributes this program
 * is intended to test in unison:
 *    hidden surfaces (on or off)
 *    technology (standard or software frame buffer)
 *    hidden surface removal algorithm (5 to choose from)
 */
void set_three (
    char	*hidden_surfaces,
    char	*technology,
    char	*hidden_surface_algorithm) {
    char	command[256];

    if (strcmp (hidden_surfaces, "on") == 0)
	HC_Set_Heuristics ("hidden surfaces");
    else
	HC_Set_Heuristics ("no hidden surfaces");

    sprintf (command, "technology = %s", technology);
    HC_Set_Rendering_Options (command);

    sprintf (command, "hsra = %s", hidden_surface_algorithm);
    HC_Set_Rendering_Options (command);

    if (strcmp (technology, "software frame buffer") == 0)
	technology = "sfb";
    HC_Open_Segment ("");
	HC_Set_Text_Font ("size = 0.01 sru");
	sprintf (command, "%s, %s, %s",
		 hidden_surfaces,
		 technology,
		 hidden_surface_algorithm);
	HC_Insert_Text (0.0, -0.9, 0.0, command);
    HC_Close_Segment ();
}

/*
 * Creates 5 windows across using a different
 * hidden surface removal algorithm in each one.
 */
void try_each_hsr (
    int		row_number,
    char	*window_pattern,
    char	*hidden_surfaces,
    char	*technology) {

    HC_Open_Segment ("");
	size_window (1, row_number, window_pattern);
	HC_Include_Segment ("?include library/metafile");
	set_three (hidden_surfaces, technology, "hardware Z buffer");
    HC_Close_Segment ();
    HC_Open_Segment ("");
	size_window (2, row_number, window_pattern);
	HC_Include_Segment ("?include library/metafile");
	set_three (hidden_surfaces, technology, "painters");
    HC_Close_Segment ();
    HC_Open_Segment ("");
	size_window (3, row_number, window_pattern);
	HC_Include_Segment ("?include library/metafile");
	set_three (hidden_surfaces, technology, "priority");
    HC_Close_Segment ();
    HC_Open_Segment ("");
	size_window (4, row_number, window_pattern);
	HC_Include_Segment ("?include library/metafile");
	set_three (hidden_surfaces, technology, "software Z buffer");
    HC_Close_Segment ();
    HC_Open_Segment ("");
	size_window (5, row_number, window_pattern);
	HC_Include_Segment ("?include library/metafile");
	set_three (hidden_surfaces, technology, "Z sort only");
    HC_Close_Segment ();
}

/*
 * Used to create the 20 windows and set the
 * combinations of attributes
 */
void draw_using_all_combinations (
    char	*sw_frame_buffer_options,
    char	*window_pattern) {
    char	command[256];

    sprintf (command,
	     "software frame buffer options = (color depth = %s)",
	     sw_frame_buffer_options);
    HC_Set_Rendering_Options (command);

    try_each_hsr (1, window_pattern, "on",  "standard");
    try_each_hsr (2, window_pattern, "on",  "software frame buffer");
    try_each_hsr (3, window_pattern, "off", "standard");
    try_each_hsr (4, window_pattern, "off", "software frame buffer");
}

/*
 * Test using a particular combination of software frame buffer
 * option and window color. Show the user, wait for input, and
 * destroy what's been shown.
 */
void display_as (
    char	*sw_frame_buffer_option,
    char	*window_pattern) {
    char	message[256];

    HC_Open_Segment ("scene");
	HC_Set_Window (-1.0, 1.0, -0.9, 0.9);
	draw_using_all_combinations (sw_frame_buffer_option, window_pattern);
    HC_Close_Segment ();
    HC_Open_Segment ("legend");
	HC_Set_Window (-1.0, 1.0, -1.0, -0.9);
	sprintf (message,
		 "color depth = %s, window pattern = %s",
		 sw_frame_buffer_option,
		 window_pattern);
	HC_Insert_Text (0.0, 0.0, 0.0, message);
    HC_Close_Segment ();
    HC_Pause ();

    HC_Delete_Segment ("scene");
    HC_Delete_Segment ("legend");
}

/*
 * Since the software frame buffer stuff can be done in two different
 * modes, we simply try everything twice - once in each mode.
 */
int main (
    int		argc,
    char	**argv) {

    HC_Open_Segment ("?include library/metafile");
	HC_Read_Metafile (argc > 1 ? argv[1] : "spring",
			  ".",
			  "restore state");
    HC_Close_Segment ();

    HC_Open_Segment ("?picture");
	HC_Open_Segment ("title");
	    HC_Set_Window (-1.0, 1.0, 0.9, 1.0);
	    HC_Insert_Text (0.0, 0.0, 0.0,
		"Way Test - Draw a Metafile Every Which Way You Can");
	HC_Close_Segment ();

	display_as ("match device", "solid");
	display_as ("full color",   "solid");
	display_as ("match device", "clear");
	display_as ("full color",   "clear");
    HC_Close_Segment ();
    HC_Exit_Program ();
    return 0;
}
