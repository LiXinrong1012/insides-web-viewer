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
 * $Id: trangeom.c,v 1.3 2006-08-07 20:38:49 stage Exp $
 */

typedef	struct {float x, y, z;}	Point;
#define	HC_POINT	Point

#include "hc.h"

#define N          100
#define BIG_NUMBER 1e6f

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int main () {
   Point   inpts[N], outpts[N];
   int     i, n;
   float   xcenter, ycenter, zcenter;
   float   xscale, yscale, zscale;
   float   xmin, ymin, zmin;
   float   xmax, ymax, zmax;
   float   factor;
   char    type[256];
   HC_KEY  key;
   float   scale[4][4], rotate[4][4], translate[4][4],
           tmp[4][4], final[4][4];

   HC_Open_Segment ("/tmp");
      HC_Read_Metafile ("bottle1", ".", "");
   HC_Close_Segment ();

   HC_Open_Segment ("?picture/glass");
      HC_Set_Color ("faces = white");
      HC_Create_Segment ("new geometry");
   HC_Close_Segment ();
   HC_Define_Alias ("?new object", "?picture/glass/new geometry");

   xmin = ymin = zmin =  BIG_NUMBER;
   xmax = ymax = zmax = -BIG_NUMBER;

   HC_Begin_Contents_Search ("/tmp", "polygons");
      while (HC_Find_Contents (type, &key)) {
         HC_Show_Polygon_Count (key, &n);
         if (n < N) {
            HC_Show_Polygon (key, &n, inpts);
            for (i = 0; i < n; ++i) {
               xmin = MIN (xmin, inpts[i].x);
               xmax = MAX (xmax, inpts[i].x);
               ymin = MIN (ymin, inpts[i].y);
               ymax = MAX (ymax, inpts[i].y);
               zmin = MIN (zmin, inpts[i].z);
               zmax = MAX (zmax, inpts[i].z);
            }
         }
      }
   HC_End_Contents_Search ();

   xcenter = (xmin + xmax) * 0.5f;
   ycenter = (ymin + ymax) * 0.5f;
   zcenter = (zmin + zmax) * 0.5f;
   xscale = (xmax - xmin);
   yscale = (ymax - ymin);
   zscale = (zmax - zmin);
   factor = 2.0f / MAX (xscale, MAX (yscale, zscale));

   HC_Compute_Translation_Matrix ((double)-xcenter,
				  (double)-ycenter,
				  (double)-zcenter,
				  &translate[0][0]);
   HC_Compute_Scale_Matrix ((double)factor,
			    (double)factor, 
			    (double)factor, 
			    &scale[0][0]);
   HC_Compute_Matrix_Product (&translate[0][0], &scale[0][0], &tmp[0][0]);
   HC_Compute_Rotation_Matrix (-110.0, 0.0, 0.0, &rotate[0][0]);
   HC_Compute_Matrix_Product (&tmp[0][0], &rotate[0][0], &final[0][0]);

   HC_Begin_Contents_Search ("/tmp", "polygons");
      while (HC_Find_Contents (type, &key)) {
         HC_Show_Polygon_Count (key, &n);
         if (n < N) {
            HC_Show_Polygon (key, &n, inpts);
            HC_Compute_Transformed_Points (n, inpts, &final[0][0], outpts);
            HC_QInsert_Polygon ("?new object", n, outpts);
         }
      }
   HC_End_Contents_Search ();

   HC_Write_Metafile ("?new object", "newcham", "");
   HC_Pause ();

   HC_Exit_Program ();
   return 0;
}
