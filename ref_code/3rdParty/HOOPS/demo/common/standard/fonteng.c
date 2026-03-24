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
 * $Id: fonteng.c,v 1.2 2006-08-07 20:38:49 stage Exp $
 */

#include "hc.h"
#include <stdio.h>

void show_it (
    char	*file_name) {
    char	buffer[128];

    HC_Open_Segment ("which one");
	HC_Flush_Geometry (".");
	HC_Set_Window (-1.0, 1.0, -1.0, -0.8);
	sprintf (buffer, "name = %s", file_name);
	HC_Insert_Text (0.0, 0.0, 0.0, file_name);
    HC_Close_Segment ();

    HC_Open_Segment ("font");
	HC_Flush_Geometry (".");
	HC_Set_Window (-1.0, 1.0, -0.8, 1.0);
	sprintf (buffer, "name = %s", file_name);
	HC_Set_Text_Font (buffer);
	HC_Open_Segment ("");
	    HC_Insert_Text (-0.7, 0.6, 0.0, "abcdefghijklmnopqrstuvwxyz");
	    HC_Insert_Text (-0.7, 0.3, 0.0, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	    HC_Insert_Text (-0.7, 0.0, 0.0, "No rotation");
	HC_Close_Segment ();
	HC_Open_Segment ("");
	    HC_Set_Text_Font ("transforms = full");
	    HC_Insert_Text (0.7, -0.3, 0.0, "abcdefghijklmnopqrstuvwxyz");
	    HC_Insert_Text (0.7, -0.6, 0.0, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	    HC_Insert_Text (0.7, -0.9, 0.0, "Rotate Object (45.0, 45.0, 45.0)");
	    HC_Rotate_Object (45.0, 45.0, 45.0);
	HC_Close_Segment ();
    HC_Close_Segment ();
    HC_Pause ();
}

int main () {
    HC_Open_Segment ("?picture");
	HC_Set_Window_Frame ("off");

	HC_Open_Segment ("message");
	    HC_Set_Window (-1.0, 1.0, 0.8, 1.0);
	    HC_Insert_Text (0.0, 0.0, 0.0, "Hit Enter to Continue");
	HC_Close_Segment ();

	HC_Open_Segment ("area");
	    HC_Set_Window (-1.0, 1.0, -1.0, 0.8);
	    show_it ("amie.pfa");
	    show_it ("cave.pfa");
	    show_it ("curly.pfa");
	    show_it ("haeberli.pfa");
	    show_it ("honesty.pfa");
	    show_it ("inja.pfa");
	    show_it ("rock.pfa");
	    show_it ("sorority.pfa");
	    show_it ("strokey.pfa");
	    show_it ("wingding.ttf");
	HC_Close_Segment ();
    HC_Close_Segment ();
    HC_Exit_Program ();
    return 0;
}
