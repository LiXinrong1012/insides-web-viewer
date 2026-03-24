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
 * $Id: surfunct.c,v 1.2 2006-08-07 20:38:49 stage Exp $
 */

/*
 * This file is slightly different from what's printed in the cookbook.
 * It has been updated to correspond to the latest changes to HOOPS.
 */

#include "hc.h"
#include <math.h>

#ifdef MSW
#    define N 40
#else
#define N      60
#endif

#define HDOMAIN 6.0

typedef struct {
   float x, y, z;
}  Point;

Point   pt[N][N];

int main () {
   int            ii, jj;
   float          spacing = (float)HDOMAIN / (float)(N - 1);

   HC_Open_Segment ("?picture");
      HC_Set_Heuristics ("hidden surfaces");
      HC_Set_Rendering_Options ("hsr algorithm = z-sort only");
      HC_Set_Visibility ("edges = off, markers = off");
      HC_Set_Color ("red");

      HC_Set_Camera_By_Volume ("perspective", 0.0, HDOMAIN,
                                              0.0, HDOMAIN);
      HC_Orbit_Camera (0.0, -60.0);
      HC_Orbit_Camera (20.0, 0.0);

      HC_Insert_Distant_Light (0.0, 0.0, -1.0);

      for (ii = 0; ii < N; ++ii) {
         for (jj = 0; jj < N; ++jj) {
            pt[ii][jj].x = ii * spacing;
            pt[ii][jj].y = jj * spacing;
            pt[ii][jj].z = 0.7f * (float)sin (pt[ii][jj].x) *
                        (float)sin (3.0f * pt[ii][jj].y);
         }
      }
      HC_Insert_Mesh (N, N, pt);
   HC_Close_Segment ();
   HC_Pause ();

   HC_Exit_Program ();
   return 0;
}
