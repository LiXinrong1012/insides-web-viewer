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
 * $Id: track.c,v 1.4 2010-10-26 21:29:09 jason Exp $
 */

#include "hc.h"
#include "hc_standalone.h"

int main () {
    char		what[100];
    float		x, y, z, whocares;

    HC_Insert_Text (0.0, -0.9, 0.0, "click to the left of red line to end");
    HC_Set_Line_Pattern ("- - - -");
    HC_Set_Color ("lines = red");
    HC_Insert_Line (-0.9, 1.0, 0.0, -0.9, -1.0, 0.0);
    HC_Set_Line_Pattern ("----");
    HC_Set_Color ("lines = black");
    do {
	HC_Get_Selection (&what[0]);
	HC_Show_Selection_Location (&whocares, &whocares, &x, &y, &z);
	HC_Insert_Ink ((double)x, (double)y, (double)z);
    } while (x > -0.9f);
    HC_Exit_Program ();
    return 0;
}
