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
 * $Id: env.c,v 1.3 2006-08-07 20:38:49 stage Exp $
 */

#include "hc.h"
#include <string.h>
#include <stdio.h>

int main () {
    int	fv = 1, ev = 0, mv = 0;
    float mirror = 0.8f;
    char tempstr[256];

    HC_Open_Segment ("?Include library/texture1");
	HC_Read_Metafile ("sphere_bar", ".", "");
    HC_Close_Segment ();

    HC_Define_Texture ("sphere_bar env", "source=sphere_bar,parameterization source=reflection normal");

    HC_Open_Segment ("?Picture");
	HC_Set_Color ("window=green, ambient = white"); 
	HC_Insert_Distant_Light (-1.0, 1.0, -1.0);
	HC_Open_Segment ("object");
	    HC_Read_Metafile ("urn", ".", "");
	    HC_Set_Color ("faces=(red, specular=blue, environment=sphere_bar env)");
	    sprintf( tempstr, "mirror=(r=%f g=%f b=%f)", mirror, mirror, mirror );
	    HC_Set_Color ( tempstr );
	    HC_Set_Rendering_Options ("no color interpolation, no color index interpolation");
	    HC_Set_Visibility ("no edges, no markers, lights");
	    HC_Set_Rendering_Options ( "lighting interpolation = gouraud" );

	    while (1) {
		char	type[80];

		HC_Get_Button (type);

		if (!strcmp (type, "Q") || !strcmp (type, "q"))
		    HC_Exit_Program ();
		else if (!strcmp (type, "up arrow"))
		    HC_Rotate_Object (5.0,  0.0,  0.0);
		else if (!strcmp (type, "down arrow"))
		    HC_Rotate_Object (-5.0,  0.0,  0.0);
		else if (!strcmp (type, "left arrow"))
		    HC_Rotate_Object (0.0,  5.0,  0.0);
		else if (!strcmp (type, "right arrow"))
		    HC_Rotate_Object (0.0, -5.0,  0.0);
		else if (!strcmp (type, "["))
		    HC_Rotate_Object (0.0,  0.0,  5.0);
		else if (!strcmp (type, "]"))
		    HC_Rotate_Object (0.0,  0.0, -5.0);
		else if (!strcmp (type, "f"))
		    HC_Set_Visibility ((fv = !fv) ? "faces=on" : "faces=off");
		else if (!strcmp (type, "e"))
		    HC_Set_Visibility ((ev = !ev) ? "edges=on" : "edges=off");
		else if (!strcmp (type, "m"))
		    HC_Set_Visibility ((mv = !mv) ? "markers=on" : "markers=off");
		else if (!strcmp (type, "I")) {
		    mirror += 0.1f;
		    if( mirror > 1 ) mirror = 1;
		    sprintf( tempstr, "mirror=(r=%f g=%f b=%f)", mirror, mirror, mirror );
		    HC_Set_Color ( tempstr );
		}
		else if (!strcmp (type, "i")) {
		    mirror -= 0.1f;
		    if( mirror < 0 ) mirror = 0;
		    sprintf( tempstr, "mirror=(r=%f g=%f b=%f)", mirror, mirror, mirror );
		    HC_Set_Color ( tempstr );
		}
	    }
    /* no need to close anything.  We'll never exit from the above loop */
    return 0; /* just to keep the compiler happy */
}

