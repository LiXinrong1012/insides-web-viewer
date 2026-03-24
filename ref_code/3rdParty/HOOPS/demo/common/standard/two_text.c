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
 * $Id: two_text.c,v 1.5 2010-10-26 21:29:09 jason Exp $
 */

#include "hc.h"
#include "hc_standalone.h"
#include <stdio.h>
#include <string.h>


int main () 
{
    char event[100];
    char driver[100], window1[100], window2[100];
    char *cp;

    HC_Show_Alias( "?picture", driver );
    HC_Delete_Segment ("?picture");
    /* strip everything past the final slash */
    cp = strrchr (driver, '/');
    cp[1] = '\0';
    strcpy( window1, driver );
    strcpy( window2, driver );
    #ifdef _MSC_VER
	strcat( window1, "window1" );
	strcat( window2, "window2" );
    #else
	strcat( window1, ":0+0" );
	strcat( window2, ":0+1" );
    #endif

    HC_Open_Segment (window1);
	HC_Set_Driver_Options("subscreen = (-0.5, 0, -0.5, 0)");
	HC_Set_Color ("windows = black, text = white");
	HC_Set_Text_Font ("size = 32 pt");
	HC_Set_Text_Font ("name = roman");
	HC_Insert_Text (0.0, 0.0, 0.0, window1);
    HC_Close_Segment ();

    HC_Open_Segment (window2);
	HC_Set_Driver_Options("subscreen = (0, 0.5, -0.5, 0)");
	HC_Set_Color ("windows = black, text = white");
	HC_Set_Text_Font ("size = 32 pt");
	HC_Set_Text_Font ("name = roman");
	HC_Insert_Text (0.0, 0.0, 0.0, window2);
    HC_Close_Segment ();

    HC_Update_Display();

    /* receive input from the keyboard from either window */
    HC_Enable_Button_Events (window1, "anything");
    HC_Enable_Button_Events (window2, "anything");
    HC_Await_Event (event);
    HC_Delete_Segment (window1);
    HC_Update_Display();
    HC_Await_Event (event);
    HC_Delete_Segment (window2);
    HC_Update_Display();

    HC_Exit_Program ();
    return 0;
}





