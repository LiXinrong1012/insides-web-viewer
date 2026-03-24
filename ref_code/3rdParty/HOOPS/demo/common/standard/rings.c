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
 * $Id: rings.c,v 1.3 2006-08-07 20:38:49 stage Exp $
 */

#include "hc.h"
#include <math.h>
#include <stdlib.h>

#define	PI	3.1415926536f
#define	DTR(x)	(((float)x)*PI/180.0f)

typedef struct point {
    float	x, y, z;
} Point;

void toroid (void) {
    float	golden;
    float	cx, cy, cz;
    int		ii, jj, kk;
    float	angle;
    float	cosa, sina;
    Point	basis1, basis2;
    Point	array[37*25];
    Point	normals[37*25];
    Point	*point = array;
    Point	*norm = normals;
    HC_KEY	key;


    /*
    ** first create a stretched toroid lying in the XY plane.  it will
    ** be longer in the X direction, and its cross-section will be circular
    ** (the cross section would vary if we simply scaled a normal torus)
    */

    golden = (float)(sqrt (5) + 1.0f) * 0.5f;		/* a nice ratio */

    cz = 0.0f;
    for (ii = 0; ii <= 360; ii += 10) {
	angle = DTR (ii);
	cx = golden * (float)cos (angle);
	cy = (float)sin (angle);

	/*
	** the basis vectors for the section at this point need to be
	** based on the slope of the ellipse here.
	*/

	/* this one is easy (and already normalized) */
	basis1.x = 0.0f;
	basis1.y = 0.0f;
	basis1.z = 1.0f;

	/* but... */
	basis2.y = golden * (float)sin (angle);
	basis2.x = (float)cos (angle);
	basis2.z = 0.0f;

	HC_Compute_Normalized_Vector (&basis2, &basis2);

	/* now draw a circular section */
	for (jj = 0; jj <= 360; jj += 15) {
	    angle = DTR (jj);
	    cosa = (float)cos (angle);
	    sina = (float)sin (angle);

	    point->x = cx + 0.2f * (cosa * basis1.x + sina * basis2.x);
	    point->y = cy + 0.2f * (cosa * basis1.y + sina * basis2.y);
	    point->z = cz + 0.2f * (cosa * basis1.z + sina * basis2.z);
	    point++;

	    norm->x = cosa * basis1.x + sina * basis2.x;
	    norm->y = cosa * basis1.y + sina * basis2.y;
	    norm->z = cosa * basis1.z + sina * basis2.z;
	    norm++;
	}

    }

    key = HC_KInsert_Mesh (37, 25, array);

    HC_Open_Geometry (key);
    norm = normals;
    kk = 0;
    for (ii = 0; ii <= 360; ii += 10) {
	for (jj = 0; jj <= 360; jj += 15) {
	    HC_Open_Vertex (kk++);
	      HC_Set_Normal (norm->x, norm->y, norm->z);
	    HC_Close_Vertex ();
	    norm++;
	}
    }
    HC_Close_Geometry ();
}


int main (int argc,
	  char **argv) {
    HC_Open_Segment ("?Include Library/toroid");
	toroid ();
    HC_Close_Segment ();

    HC_Open_Segment ("?Picture");
      HC_Set_Rendering_Options ("lighting interpolation");
      HC_Set_Heuristics ("no concave polygons");
      HC_Set_Color ("window = black");
      HC_Open_Segment ("rings");
	HC_Set_Visibility ("edges = off, markers = off");
	HC_Open_Segment ("one");
	    HC_Set_Color ("face = red");
	    HC_Include_Segment ("?Include Library/toroid");
	HC_Close_Segment ();
	HC_Open_Segment ("two");
	    HC_Set_Color ("face = green");
	    HC_Include_Segment ("?Include Library/toroid");
	    HC_Rotate_Object (90.0, 0.0, 90.0);
	HC_Close_Segment ();
	HC_Open_Segment ("three");
	    HC_Set_Color ("face = (diffuse = blue, transmission = gray)");
	    HC_Include_Segment ("?Include Library/toroid");
	    HC_Rotate_Object (90.0, 90.0, 0.0);
	HC_Close_Segment ();
      HC_Close_Segment ();

    HC_Set_Camera_By_Volume ("p", -2.0, 2.0, -2.0, 2.0);
    HC_Orbit_Camera (35.0, 25.0);
    HC_Insert_Distant_Light (1.0, 1.5, -0.8);

    if (argc > 1) {
	int rots = atoi (argv[1]);

	HC_Set_Driver_Options ("double-buffering");
	while (rots--) {
	    HC_QRotate_Object ("rings", 0.0, 4.0, 2.0);
	    HC_Update_Display ();
	}
    }
    else
	HC_Pause ();

    HC_Exit_Program ();
    return 0;
}
