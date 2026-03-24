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
 * $Id: popup.c,v 1.4 2010-10-26 21:29:09 jason Exp $
 */

#include "hc.h"
#include "hc_standalone.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

#define Pi              (3.141592f)
#define RADIUS          (0.9f)
#define NUMBER          (36)
#define ANGLE           (2.0f * Pi / (float)NUMBER)

int main () {
		char	selection[100];
		char	previous[100];
    static	char	*buttons[] = {"first", "second", "third", "fourth",
				      "exit", 0};
		int	which, total;
	        float	height;
		float	xw, yw, xc, yc, zc;
		float	left, right, bottom, top;
		char	locater[100], picture[100], action[10];

    HC_Open_Segment ("?Picture");
	HC_Set_Driver_Options ("subscreen stretching");
	{
	    int     i,
				j;
	    float   x[NUMBER],
				y[NUMBER];

	    for (i = 0; i < NUMBER; i++) {
		x[i] = RADIUS * (float)sin(ANGLE * i);
		y[i] = RADIUS * (float)cos(ANGLE * i);
		for (j = i; j < NUMBER; j++) {
		    x[j] = RADIUS * (float)sin(ANGLE * j);
		    y[j] = RADIUS * (float)cos(ANGLE * j);
		    HC_Insert_Line ((double)x[i],
				    (double)y[i],
				    0.0,
				    (double)x[j],
				    (double)y[j],
				    0.0);
		}
	    }
	}
	HC_Set_Selectability ("windows = v^");
	HC_Set_Color ("windows = face contrast = black, geometry = window contrast = white");
	HC_Set_Text_Size (2.0);

        HC_Open_Segment ("popup");
	    HC_Set_Window (-1.0, 1.0, -1.0, 1.0);	/* until known for real */
	    HC_Set_Visibility ("windows = off");
	    HC_Set_Selectability ("windows = *^");
	    HC_Set_Text_Size (0.5);
	    total = 0;
	    while (buttons[total] != 0)
		++total;
	    height = 2.0f / (float) total;
	    which = 0;
	    do {
		HC_Open_Segment (buttons[which]);
		    HC_Set_Window (-1., 1., 1-(which+1)*height, 1-which*height);
		    HC_Insert_Text (0., 0., 0., buttons[which]);
		HC_Close_Segment ();
	    }
	    while (++which < total);
	HC_Close_Segment ();

	do {
	    int status;
	    do {
		HC_Get_Selection (selection);
		HC_Show_Selection_Source (locater, picture, action, &status);
	    } while (strcmp (action, "v") != 0);

	    HC_Show_Selection_Location (&xw, &yw, &xc, &yc, &zc);
	    HC_Set_Selectability ("windows = off");

	    HC_Open_Segment ("popup");
		top = yw + 0.05f;
		if (top > 1.0f)
		    top = 1.0f;
		bottom = top - 0.12f * (float)total;
		if (bottom < -1)
		    top += -1.0f - bottom, bottom = -1.0f;

		right = xw + 0.1f;
		if (right > 1)
		    right = 1.0f;
		left = right - 0.2f;
		if (left < -1)
		    right += -1.0f - left, left = -1.0f;

		HC_Set_Window (left, right, bottom, top);
		HC_Set_Visibility ("windows = on");
		HC_QSet_Color (buttons[0], "windows = red");
		HC_QUnSet_Color ("*");

		HC_QSet_Color (buttons[0], "windows = white, text = window contrast = black");
		strcpy (previous, buttons[0]);
		do {
		    int status;

		    HC_Get_Selection (selection);

		    if (strcmp (selection, previous) != 0) {
			HC_QUnSet_Color (previous);
			HC_QSet_Color (selection, "windows = white, text = window contrast = black");
			strcpy (previous, selection);
		    }

		    HC_Show_Selection_Source (locater, picture, action, &status);
		} while (strcmp (action, "^") != 0);

		HC_Set_Visibility ("windows = off");
	    HC_Close_Segment ();
	    HC_Set_Selectability ("windows = on");
	} while (strcmp (selection, "exit") != 0);

	HC_Get_Wakeup (1.0);
	putchar ('\7');
    HC_Close_Segment ();
    HC_Exit_Program();
    return 0;
}
