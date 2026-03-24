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
 * $Id: capjoin.c,v 1.4 2010-10-26 21:29:09 jason Exp $
 */

#include "hc.h"
#include "hc_standalone.h"
#include "string.h"

char pat[] = "|--->";
float l[3][3] = {
	{-1.0f, 0.0f, 0.0f},
	{0.5f, 0.0f, 0.0f},
	{-0.5f, 0.9f, 0.0f}};

int main () {
    char	event[32];
    float	weight = 35.0f;

    HC_Open_Segment ("/tmp");
	HC_Insert_Polyline (3, l);
    HC_Close_Segment ();

    HC_Open_Segment ("?Picture");
	HC_Open_Segment ("line");
	    HC_Set_Window (-1.0, 1.0, -0.7, 1.0);
	    HC_Set_Camera_Projection ("o");
	    HC_Set_Line_Pattern (pat);
	    HC_Open_Segment ("heavy");
		HC_Set_Line_Weight (weight);
		HC_Include_Segment ("/tmp");
		HC_Translate_Object (0.0, 0.0, 0.1);
	    HC_Close_Segment ();
	    HC_Open_Segment ("thin");
		HC_Set_Color ("red");
		HC_Include_Segment ("/tmp");
	    HC_Close_Segment ();
	    HC_Set_Selectability ("v*");
	HC_Close_Segment ();
	HC_Open_Segment ("legend");
	    HC_Set_Window (-1.0, 1.0, -1.0, -0.7);
	    HC_Set_Color ("window = black, text = white");
	    HC_Set_Camera_Projection ("stretched");
	    HC_Set_Text_Font ("size = 0.015 sru");
	    HC_Open_Segment ("");
		HC_Set_Text_Alignment ("<");
		HC_Insert_Text (-1.0,  0.8, 0.0, "| == flat cap");
		HC_Insert_Text (-1.0,  0.0, 0.0, "[ == square cap");
		HC_Insert_Text (-1.0, -0.8, 0.0, "( == round cap");
	    HC_Close_Segment ();
	    HC_Open_Segment ("");
		HC_Insert_Text (-0.33,  0.8, 0.0, "] == butt join");
		HC_Insert_Text (-0.33,  0.0, 0.0, "> == mitre join");
		HC_Insert_Text (-0.33, -0.8, 0.0, ") == round join");
		HC_Insert_Text (0.33,  0.2, 0.0, "Click");
		HC_Insert_Text (0.33,  0.0, 0.0, "to move");
		HC_Insert_Text (0.33, -0.2, 0.0, "endpoint");
	    HC_Close_Segment ();
	    HC_Open_Segment ("");
		HC_Set_Text_Alignment (">");
		HC_Insert_Text (1.0,  0.8,  0.0, "- == decrease weight");
		HC_Insert_Text (1.0,  0.48, 0.0, "+ == increase weight");
		HC_Insert_Text (1.0,  0.16, 0.0, "s == solid");
		HC_Insert_Text (1.0, -0.16, 0.0, "d == dashed");
		HC_Insert_Text (1.0, -0.48, 0.0, ". == dotted");
		HC_Insert_Text (1.0, -0.8,  0.0, "q == quit");
	    HC_Close_Segment ();
	    HC_Set_Selectability ("off");
	HC_Close_Segment ();

	HC_Enable_Button_Events ("?Keyboard", "anything");
	HC_Enable_Selection_Events ("?Locater", "?Picture");

	for (;;) {
	    HC_Await_Event (event);

	    if (strcmp (event, "none") == 0) {
	    	HC_Exit_Program ();
	    }

	    switch (event[0]) {
		case 'b': {
		    char	button[32];

		    HC_Show_Button (button);
		    switch (button[0]) {
			case '|':
			case '[':
			case '(':	pat[0] = button[0];	break;

			case ']':
			case '>':
			case ')':	pat[4] = button[0];	break;

			case '+':	HC_QSet_Line_Weight ("?Picture/line/heavy",
							     (double)(weight += 1.0f));
					break;

			case '-':	if (weight > 2.0f)
					    weight -= 1.0f;
					HC_QSet_Line_Weight ("?Picture/line/heavy",
							     (double)weight);
					break;

			case 's':	pat[1] = pat[2] = pat[3] = '-';
					break;

			case 'd':	pat[1] = pat[3] = '-';
					pat[2] = ' ';
					break;

			case '.':	pat[1] = pat[2] = pat[3] = '.';
					break;

			case 'q':	HC_Exit_Program ();
		    }

		    HC_QSet_Line_Pattern ("?Picture/line", pat);
		}   break;

		case 's': {
		    float	x, y, d;

		    HC_Show_Selection_Location (&d, &d, &x, &y, &d);

		    l[2][0] = x;
		    l[2][1] = y;

		    HC_Flush_Geometry ("/tmp");
		    HC_QInsert_Polyline ("/tmp", 3, l);
		}   break;
	    }
	}
    HC_Close_Segment ();
    return 0;
}
