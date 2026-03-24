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
 * $Header: /files/homes/master/cvs/hoops_master/standard/spriting.c,v 1.4 2006-08-07 20:38:49 stage Exp $
 */

#include <stdio.h>
#include <stdlib.h>

#include "hc.h"

float p1[] = {-1,-1,0, 0,0,-1,  1,-1,0 };
float p2[] = { 1,-1,0, 0,0,-1,  1, 1,0 };
float p3[] = { 1, 1,0, 0,0,-1, -1, 1,0 };
float p4[] = {-1, 1,0, 0,0,-1, -1,-1,0 };

float w1[] = {-1,-1,0, 0,0,-1,  1,-1,0 };
float w2[] = { 1,-1,0, 0,0,-1,  1, 1,0 };
float w3[] = { 1, 1,0, 0,0,-1, -1, 1,0 };
float w4[] = {-1, 1,0, 0,0,-1, -1,-1,0 };



int main () {
    float l,b;
    float red = 0.3f, green = 0.5f, blue = 0.8f;
    int i;

    HC_Open_Segment ("?Picture");
	HC_Insert_Distant_Light (-0.3, 0.4, -1.0);
	HC_Set_Driver_Options( "double buffering" );

	HC_Open_Segment ("spikes");
	    for (l = -1.0f; l < 1.0f; l += 0.1f) {
		for (b = -1.0f; b < 1.0f; b += 0.1f) {
		    HC_Open_Segment ("");
		      HC_Set_Color_By_Value ("geometry", "rgb", red, green, blue);
		      HC_Scale_Object (0.1f, 0.1f, 1 );
		      HC_Translate_Object (l, b, 0);
		      for ( i = 0 ; i < 10 ; i++ ) {
			HC_Insert_Polygon (3, p1);
			HC_Insert_Polygon (3, p2);
			HC_Insert_Polygon (3, p3);
			HC_Insert_Polygon (3, p4);
		      }
		    HC_Close_Segment ();
		    red *= 33.97f;	red += .183f;	red -= (int)red;
		    green *= 45.35f;	green += .678f;	green -= (int)green;
		    blue *= 76.28f;	blue += .927f;	blue -= (int)blue;
		}
	    }
	HC_Close_Segment ();

	HC_Open_Segment ("the sprite");
	    HC_Scale_Object (0.3f, 0.3f, 1 );
	    HC_Translate_Object (0.8f, 0.05f, 0 );
	    HC_Set_Color ("red");
	    HC_Insert_Polygon (3, w1);
	    HC_Insert_Polygon (3, w2);
	    HC_Insert_Polygon (3, w3);
	    HC_Insert_Polygon (3, w4);
	HC_Close_Segment ();

	HC_Open_Segment ("the sprite");

	  for(;;)
	  {
	    /* first normal so you have a basis for comparison */
	    HC_Set_Heuristics ("no quick moves");
	    for ( i = 0 ; i < 2 ; i++ ) {
	        HC_Rotate_Object (0, 0, 10);
	        HC_Update_Display ();
	    }

	    /* then with spriting */
	    HC_Set_Heuristics ("quick moves=spriting");
	    for ( i = 0 ; i < 50 ; i++ ) {
	        HC_Rotate_Object (0, 0, 10);
	        HC_Update_Display ();
	    }
	    HC_Pause();
	  }

	HC_Close_Segment (); /* the sprite */
    HC_Close_Segment (); /* ?Picture */

	return EXIT_SUCCESS;
}

