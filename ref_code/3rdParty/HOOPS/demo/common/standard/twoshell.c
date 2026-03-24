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
 * $Id: twoshell.c,v 1.2 2006-08-07 20:38:49 stage Exp $
 */

#include "hc.h"
#include <math.h>

#define RES       300
#define PI        3.141592654f
#define DIVISIONS (float)RES * 14.0f * PI
typedef struct    {float x, y, z;} Point;

void calculate_conic_point (
    float theta,
    float phi,
    float rho,
    float xyscale,
    float zposneg,
    Point *ptptr) {

    ptptr->x = rho * (float)cos (theta) * (float)sin (phi) * xyscale;
    ptptr->y = rho * (float)sin (theta) * (float)sin (phi) * xyscale;
    ptptr->z = rho * zposneg * (float)cos (phi);
}

void insert_hollow_hemisphere (void) {
   Point       pts[RES*5];
   int	       list[RES*5], index = 1;
   float       theta, phi;
   int         iii, jjj = 1, column, ring, total_pts;
   int	       numcols, numrings, facesize = 5;
   int         facelist_size, first_ring_end;
   float       phi_inc = PI / 18.0f;
   float       phi_max = PI / 3.0f;
   float       theta_inc = PI / 18.0f;
   float       theta_max = 2.0f * PI;

   numcols = (int)  (theta_max / theta_inc);
   numrings = (int) (phi_max / phi_inc);

   calculate_conic_point (0.0f, 0.0f, 1.0f, 1.0f, -1.0f, &pts[0]);

   for (ring = 1; ring < numrings; ring++){
      phi = (float)ring * phi_inc;
      for (column = 0; column < numcols; column++){
         theta = (float)column * theta_inc;
         calculate_conic_point (theta, phi, 1.0f, 1.0f, -1.0f, &pts[index]);
         index++;
      }
   }
   total_pts = index;
   facelist_size = numcols * (numrings - 1) * facesize;
   first_ring_end = (numcols - 1) * facesize;

   for (iii = 0; iii < facelist_size; iii += facesize) {
      list[iii] = facesize - 1;
      if (iii <= first_ring_end) {	/* for first ring with 1 point */
         list[iii + 1] = 0;
         list[iii + 2] = iii/facesize + 1;
         if (iii == first_ring_end)   list[iii + 3] = 1;
         else                         list[iii + 3] = list[iii + 2] + 1;
         list[iii + 4] = 0;
      }
      else {
         list[iii + 1] = jjj;
         list[iii + 2] = jjj + numcols;
         if (((jjj % numcols) == 0)) {
            list[iii + 3] = list[iii+2] - (numcols-1);
            list[iii + 4] = list[iii+1] - (numcols-1);
            jjj = list[iii + 3];
         }
         else {
            list[iii + 3] = list[iii+2] + 1;
            list[iii + 4] = jjj + 1;
            ++jjj;
         }
      }
   }
   HC_Insert_Shell (total_pts, pts, facelist_size, list);
}

void insert_cone (void) {
   Point       pts[RES];
   int         facelist_size, facelist[RES*10], ii;
   float       theta, phi, p;

   phi = PI / 4.0f;

   for (ii = 0; ii < RES; ++ii) {
      p = (float)ii / 250.0f;
      theta = (float)ii / DIVISIONS;
      calculate_conic_point (theta, phi, p, 1.0f, 1.0f, &pts[ii]);
   }
   HC_Compute_Convex_Hull (RES, pts, &facelist_size, facelist);
   HC_Insert_Shell (RES, pts, facelist_size, facelist);

   for (ii = 0; ii < 100; ++ii) {
      p = (float)ii / 75.0f;
      theta = (float)ii / DIVISIONS;
      calculate_conic_point (theta, phi, p, 1.03f, 1.0f, &pts[ii]);
      if (p > (RES / 250.0f)) 
	break;
   }
   HC_Insert_Polyline (ii, pts);
}

int main () {
   HC_Open_Segment ("?picture");
      HC_Set_Visibility ("markers = off, edges = off");
      HC_Insert_Distant_Light (1.0, 1.0, -1.0);
      HC_Set_Camera_Position (0.0, 0.0, -10.0);

      HC_Open_Segment ("conic shell");
         HC_Set_Color ("faces =  peach");
         insert_cone ();
         HC_Scale_Object (0.5, 0.5, 0.5);
         HC_Rotate_Object (75.0, 0.0, 0.0);
         HC_Translate_Object (0.0, 0.0, 1.5);
      HC_Close_Segment ();

      HC_Open_Segment ("mussel shell");
         HC_Set_Color ("faces = aquamarine");
         insert_hollow_hemisphere ();
         HC_Scale_Object (0.75, 0.75, 0.75);
         HC_Rotate_Object (-105.0, 0.0, 0.0);
         HC_Translate_Object (1.2, 0.0, -0.5);
      HC_Close_Segment ();
   HC_Close_Segment ();

   HC_Pause ();
   HC_Exit_Program ();
   return 0;
}
