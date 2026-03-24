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
 * $Id: crayons.c,v 1.2 2006-08-07 20:38:49 stage Exp $
 */

#include "hc.h"
#include <math.h>
#include <string.h>

#define SET_POINT10(d, x0, y0, z0, x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4, x5, y5, z5, x6, y6, z6, x7, y7, z7, x8, y8, z8, x9, y9, z9) \
		d[0].x = (float)(x0); \
		d[0].y = (float)(y0); \
		d[0].z = (float)(z0); \
		d[1].x = (float)(x1); \
		d[1].y = (float)(y1); \
		d[1].z = (float)(z1); \
		d[2].x = (float)(x2); \
		d[2].y = (float)(y2); \
		d[2].z = (float)(z2); \
		d[3].x = (float)(x3); \
		d[3].y = (float)(y3); \
		d[3].z = (float)(z3); \
		d[4].x = (float)(x4); \
		d[4].y = (float)(y4); \
		d[4].z = (float)(z4); \
		d[5].x = (float)(x5); \
		d[5].y = (float)(y5); \
		d[5].z = (float)(z5); \
		d[6].x = (float)(x6); \
		d[6].y = (float)(y6); \
		d[6].z = (float)(z6); \
		d[7].x = (float)(x7); \
		d[7].y = (float)(y7); \
		d[7].z = (float)(z7); \
		d[8].x = (float)(x8); \
		d[8].y = (float)(y8); \
		d[8].z = (float)(z8); \
		d[9].x = (float)(x9); \
		d[9].y = (float)(y9); \
		d[9].z = (float)(z9); \

#define SET_POINT6(d, x0, y0, z0, x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4, x5, y5, z5) \
		d[0].x = (float)(x0); \
		d[0].y = (float)(y0); \
		d[0].z = (float)(z0); \
		d[1].x = (float)(x1); \
		d[1].y = (float)(y1); \
		d[1].z = (float)(z1); \
		d[2].x = (float)(x2); \
		d[2].y = (float)(y2); \
		d[2].z = (float)(z2); \
		d[3].x = (float)(x3); \
		d[3].y = (float)(y3); \
		d[3].z = (float)(z3); \
		d[4].x = (float)(x4); \
		d[4].y = (float)(y4); \
		d[4].z = (float)(z4); \
		d[5].x = (float)(x5); \
		d[5].y = (float)(y5); \
		d[5].z = (float)(z5);

#define SET_POINT4(d, x0, y0, z0, x1, y1, z1, x2, y2, z2, x3, y3, z3) \
		d[0].x = (float)(x0); \
		d[0].y = (float)(y0); \
		d[0].z = (float)(z0); \
		d[1].x = (float)(x1); \
		d[1].y = (float)(y1); \
		d[1].z = (float)(z1); \
		d[2].x = (float)(x2); \
		d[2].y = (float)(y2); \
		d[2].z = (float)(z2); \
		d[3].x = (float)(x3); \
		d[3].y = (float)(y3); \
		d[3].z = (float)(z3);

#define SET_POINT3(d, x0, y0, z0, x1, y1, z1, x2, y2, z2) \
		d[0].x = (float)(x0); \
		d[0].y = (float)(y0); \
		d[0].z = (float)(z0); \
		d[1].x = (float)(x1); \
		d[1].y = (float)(y1); \
		d[1].z = (float)(z1); \
		d[2].x = (float)(x2); \
		d[2].y = (float)(y2); \
		d[2].z = (float)(z2);

#define	TWOPI	6.2857142f

int main () {
    struct {
	float	x, y, z;
    } points[10];
    char	driver[32];

    /*
     *   1. CONSTRUCT ONE CRAYON THAT CAN BE REUSED MANY TIMES
     */
    HC_Open_Segment ("?include library/crayon");
    {
	static float	r = 0.35f,
			height = 9.2f;
	static int	n = 10;
	int		i;
	float		div, phi, rho;

	div = TWOPI / (float)n;
	for (i = 0; i < n; i++) {
	    phi = div * i;
	    rho = div * (i + 1);
	    /* cylinder base */
	    SET_POINT4 (points, (r * cos(phi)),
				0.0f,
				 (r * sin(phi)),

				 (r * cos(phi)),
				height - 1.0f,
				 (r * sin(phi)),

				 (r * cos(rho)),
				height -1.0f,
				 (r * sin(rho)),

				 (r * cos(rho)),
				0.0f,
				 (r * sin(rho)));
	    HC_Insert_Polygon (4, points);

	    /* upper cone */
	    SET_POINT4 (points, (0.8 * r * cos(phi)),
				height - 1.0f,
				 (0.8 * r * sin(phi)),

				 (0.3 * r * cos(phi)),
				height,
				 (0.3 * r * sin(phi)),

				 (0.3 * r * cos(rho)),
				height,
				 (0.3 * r * sin(rho)),

				 (0.8 * r * cos(rho)),
				height - 1.0f,
				 (0.8 * r * sin(rho)));
	    HC_Insert_Polygon (4, points);

	    /* base lid */
	    SET_POINT3 (points, (r * cos(phi)),
				height - 1.0f,
				 (r * sin(phi)),

				0.0f,
				height - 1.0f,
				0.0f,

				 (r * cos(rho)),
				height - 1.0f,
				 (r * sin(rho)));
	    HC_Insert_Polygon (3, points);

	    /* cone lid */
	    SET_POINT3 (points, (0.3 * r * cos(phi)),
				height,
				 (0.3 * r * sin(phi)),

				0.0f,
				height,
				0.0f,

				 (0.3 * r * cos(rho)),
				height,
				 (0.3 * r * sin(rho)));
	    HC_Insert_Polygon (3, points);
	}
    }
    HC_Close_Segment ();

    /*
     *   2. CONSTRUCT A BOX OF CRAYONS
     */
    HC_Open_Segment ("?picture");
	HC_Set_Camera_By_Volume ("perspective", 0.0, 14.0, -1.0, 15.0);
	HC_Set_Color ("window = cyan");
	HC_Update_Display ();
	HC_Show_Device_Info ("?picture", "driver type", driver);
	if (strcmp (driver, "SBX") == 0)
	    HC_Set_Driver_Options ("light scaling = 1.25");

	HC_Open_Segment ("box");
	    HC_Open_Segment ("colors");
	    {
		static char	*names[] = {
					"Apricot",
					"Aquamarine",
					"Bittersweet",
					"Black",
					"Blue Green",
					"Blue Grey",
					"Blue Violet",
					"Blue",
					"Brown",
					"Brick Red",
					"Burnt Orange",
					"Burnt Sienna",
					"Cadet Blue",
					"Carnation Pink",
					"cerulean",
					"Copper",
					"Cornflower",
					"dandelion",
					"Forest Green",
					"fuchsia",
					"Gold",
					"Goldenrod",
					"Gray",
					"Green Blue",
					"Green Yellow",
					"Green",
					"Indian Red",
					"jungle green",
					"Lavender",
					"Lemon Yellow",
					"Magenta",
					"Mahogany",
					"Maize",
					"Maroon",
					"Melon",
					"Midnite Blue",
					"Mulberry",
					"Navy Blue",
					"Olive Green",
					"Orange Red",
					"Orange Yellow",
					"Orange",
					"Orchid",
					"Peach",
					"Periwinkle",
					"Pine Green",
					"Plum",
					"Raw Sienna",
					"Raw Umber",
					"Red Orange",
					"Red Violet",
					"Red",
					"royal purple",
					"Salmon",
					"Sea Green",
					"Sepia",
					"Silver",
					"Sky Blue",
					"Spring Green",
					"Tan",
					"teal blue",
					"Thistle",
					"Turquoise Blue",
					"Violet Blue",
					"Violet Red",
					"Violet",
					"vivid tangerine",
					"White",
					"wild strawberry",
					"Yellow Green",
					"Yellow Orange",
					"Yellow"};
		int		i;

		for (i = 0; i < 72; i++) {
		    HC_Open_Segment ("");
			HC_Set_Color (names[i]);
			HC_Include_Segment ("?include library/crayon");
			HC_Translate_Object ((i % 18) * 14.0 / 18.0 + 0.35,
					     ((i / 18)) + 0.6,
					     (i / 18) + 0.5);
		    HC_Close_Segment ();
		}
		HC_Set_Visibility ("edges = off");
	    }
	    HC_Close_Segment ();

	    HC_Open_Segment ("top");
		HC_Set_Visibility ("edges = off");
		HC_Set_Color ("text = dark forest green");

		HC_Open_Segment ("dividing line");
		    HC_Set_Line_Pattern ("- -");
		    HC_Insert_Line (0.0, 9.0, -0.01, 14.0, 9.0, -0.01);
		HC_Close_Segment ();

		HC_Open_Segment ("base");
		    HC_Set_Color ("faces = dandelion");

		    /* front */
		    HC_Open_Segment ("closed");
			SET_POINT10 (points, 0.0f,  9.0f,  0.0f,
					     0.0f, 13.0f,  0.0f,
					    14.0f, 13.0f,  0.0f,
					    14.0f,  9.0f,  0.0f,
					     0.0f,  9.0f,  0.0f,
					     3.0f,  9.5f,  0.0f,
					     3.0f, 12.5f,  0.0f,
					    11.0f, 12.5f,  0.0f,
					    11.0f,  9.5f,  0.0f,
					     3.0f,  9.5f,  0.0f);
			HC_Insert_Polygon (10, points);
			HC_Set_Visibility ("off");
		    HC_Close_Segment ();
		    HC_Open_Segment ("opened");
			SET_POINT4 (points, 0.0f,  9.0f,  0.0f,
					    0.0f, 13.0f,  0.0f,
					   14.0f, 13.0f,  0.0f,
					   14.0f,  9.0f,  0.0f);
			HC_Insert_Polygon (4, points);
		    HC_Close_Segment ();

		    /* left */
		    SET_POINT4 (points, 0.0f,  9.0f,  0.0f,
				        0.0f, 13.0f,  0.0f,
				        0.0f, 13.0f,  4.0f,
				        0.0f,  9.0f,  4.0f);
		    HC_Insert_Polygon (4, points);

		    HC_Open_Segment ("");
			HC_Set_Color ("faces = gray");
			/* back */
			SET_POINT4 (points, 0.0f,  9.0f,  4.0f,
					   14.0f,  9.0f,  4.0f,
					   14.0f, 13.0f,  4.0f,
					    0.0f, 13.0f,  4.0f);
			HC_Insert_Polygon (4, points);
		    HC_Close_Segment ();

		    /* right */
		    SET_POINT4 (points, 14.0f,  9.0f,  0.0f,
				        14.0f, 13.0f,  0.0f,
				        14.0f, 13.0f,  4.0f,
				        14.0f,  9.0f,  4.0f);
		    HC_Insert_Polygon (4, points);

		    /* top */
		    SET_POINT4 (points, 0.0f, 13.0f,  0.0f,
				        0.0f, 13.0f,  4.0f,
				       14.0f, 13.0f,  4.0f,
				       14.0f, 13.0f,  0.0f);
		    HC_Insert_Polygon (4, points);
		HC_Close_Segment ();

		HC_Open_Segment ("thin stripes");
		    HC_Set_Color ("faces = forest green");
		    /* front left */
		    SET_POINT4 (points, 0.2f,  9.0f,  -0.01,
				        0.4f,  9.0f,  -0.01,
				        0.0f,  9.8f,  -0.01,
				        0.0f,  9.4f,  -0.01);
		    HC_Insert_Polygon (4, points);
		    SET_POINT4 (points, 0.6f,  9.0f,  -0.01,
				        0.8f,  9.0f,  -0.01,
				        0.0f, 10.6f,  -0.01,
				        0.0f, 10.2f,  -0.01);
		    HC_Insert_Polygon (4, points);

		    /* front right */
		    SET_POINT4 (points, 13.8f,  9.0f,  -0.01,
				        13.6f,  9.0f,  -0.01,
				        14.0f,  9.8f,  -0.01,
				        14.0f,  9.4f,  -0.01);
		    HC_Insert_Polygon (4, points);
		    SET_POINT4 (points, 13.4f,  9.0f,  -0.01,
				        13.2f,  9.0f,  -0.01,
				        14.0f, 10.6f,  -0.01,
				        14.0f, 10.2f,  -0.01);
		    HC_Insert_Polygon (4, points);
		HC_Close_Segment ();

		HC_Open_Segment ("contest stripe");
		    HC_Set_Color ("faces = orchid");
		    SET_POINT4 (points, 10.5f, 13.0f,  -0.01,
				        12.0f, 13.0f,  -0.01,
				        14.0f, 11.5f,  -0.01,
				        14.0f, 10.5f,  -0.01);
		    HC_Insert_Polygon (4, points);
		HC_Close_Segment ();

		HC_Open_Segment ("Crayola");
		    HC_Set_Color ("text = dark forest green");
		    HC_Set_Text_Font ("size = 0.09 sru");
		    HC_Scale_Object (7.0, 7.0, 1.0);
		    HC_Translate_Object (7.0, 11.0, -0.01);
		    HC_Insert_Text (0.0, 0.0, 0.0, "Crayola\256");
		HC_Close_Segment ();

		HC_Open_Segment ("72");
		    HC_Set_Text_Font ("size = 0.03 sru");
		    HC_Set_Text_Alignment ("<");
		    HC_Scale_Object (7.0, 7.0, 1.0);
		    HC_Translate_Object (0.5, 12.5, -0.01);
		    HC_Insert_Text (0.0, 0.0, 0.0, "72");
		HC_Close_Segment ();

		HC_Open_Segment ("Different Brilliant Colors");
		    HC_Set_Text_Font ("size = 0.015 sru");
		    HC_Set_Text_Alignment ("<");
		    HC_Scale_Object (7.0, 7.0, 1.0);
		    HC_Translate_Object (0.5, 12.0, -0.01);
		    HC_Insert_Text (0.0,  0.0,  0.0, "Different");
		    HC_Insert_Text (0.0, -0.05, 0.0, "Brilliant");
		    HC_Insert_Text (0.0, -0.1,  0.0, "Colors");
		HC_Close_Segment ();

		HC_Open_Segment ("No New Colors Contest");
		    HC_Set_Color ("text = white");
		    HC_Set_Text_Font ("size = 0.015 sru, rotation = follow path");
		    HC_Set_Text_Path (1.0, -0.70, 0.0);
		    HC_Scale_Object (7.0, 7.0, 1.0);
		    HC_Translate_Object (12.7, 12.15, -0.01);
		    HC_Insert_Text (0.0,  0.0, 0.0, "No New");
		    HC_Insert_Text (0.0, -0.05, 0.0, "Colors Contest");
		HC_Close_Segment ();
	    HC_Close_Segment ();

	    HC_Open_Segment ("bottom");
		HC_Set_Visibility ("edges = off");
		HC_Open_Segment ("base");
		    HC_Set_Color ("faces = dandelion");
		    /* front */
		    SET_POINT4 (points, 4.5f,  0.0f,  0.0f,
				        9.5f,  0.0f,  0.0f,
				       14.0f,  9.0f,  0.0f,
				        0.0f,  9.0f,  0.0f);
		    HC_Insert_Polygon (4, points);

		    /* left */
		    SET_POINT4 (points, 0.0f,  0.0f,  0.0f,
				        0.0f,  9.0f,  0.0f,
				        0.0f,  9.0f,  4.0f,
				        0.0f,  0.0f,  4.0f);
		    HC_Insert_Polygon (4, points);

		    /* back */
		    SET_POINT4 (points, 0.0f,  0.0f,  4.0f,
				       14.0f,  0.0f,  4.0f,
				       14.0f,  9.0f,  4.0f,
				        0.0f,  9.0f,  4.0f);
		    HC_Insert_Polygon (4, points);

		    /* right */
		    SET_POINT4 (points, 14.0f,  0.0f,  0.0f,
				        14.0f,  9.0f,  0.0f,
				        14.0f,  9.0f,  4.0f,
				        14.0f,  0.0f,  4.0f);
		    HC_Insert_Polygon (4, points);

		    /* bottom */
		    SET_POINT4 (points, 0.0f,  0.0f,  0.0f,
				        0.0f,  0.0f,  4.0f,
				       14.0f,  0.0f,  4.0f,
				       14.0f,  0.0f,  0.0f);
		    HC_Insert_Polygon (4, points);
		HC_Close_Segment ();

		HC_Open_Segment ("wide stripes");
		    HC_Set_Color ("faces = forest green");
		    SET_POINT4 (points, 0.0f,  7.0f,  -0.01,
				        0.0f,  9.0f,  -0.01,
				        4.5f,  0.0f,  -0.01,
				        3.5f,  0.0f,  -0.01);
		    HC_Insert_Polygon (4, points);

		    SET_POINT4 (points, 14.0f,  7.0f,  -0.01,
				        14.0f,  9.0f,  -0.01,
				         9.5f,  0.0f,  -0.01,
				        10.5f,  0.0f,  -0.01);
		    HC_Insert_Polygon (4, points);
		HC_Close_Segment ();

		HC_Open_Segment ("thin stripes");
		    HC_Set_Color ("faces = forest green");
		    SET_POINT4 (points, 0.2f,  9.0f,  -0.01,
				        0.4f,  9.0f,  -0.01,
				        4.9f,  0.0f,  -0.01,
				        4.7f,  0.0f,  -0.01);
		    HC_Insert_Polygon (4, points);

		    SET_POINT4 (points, 0.6f,  9.0f,  -0.01,
				        0.8f,  9.0f,  -0.01,
				        5.3f,  0.0f,  -0.01,
				        5.1f,  0.0f,  -0.01);
		    HC_Insert_Polygon (4, points);

		    SET_POINT4 (points, 13.8f,  9.0f,  -0.01,
				        13.6f,  9.0f,  -0.01,
				         9.1f,  0.0f,  -0.01,
				         9.3f,  0.0f,  -0.01);
		    HC_Insert_Polygon (4, points);

		    SET_POINT4 (points, 13.4f,  9.0f,  -0.01,
				        13.2f,  9.0f,  -0.01,
				         8.7f,  0.0f,  -0.01,
				         8.9f,  0.0f,  -0.01);
		    HC_Insert_Polygon (4, points);
		HC_Close_Segment ();

		HC_Open_Segment ("corners");
		    HC_Set_Color ("faces = dark dark forest green");
		    /* left */
		    SET_POINT3 (points, 0.0f,  7.0f,  0.0f,
				        3.5f,  0.0f,  0.0f,
				        0.0f,  0.0f,  0.0f);
		    HC_Insert_Polygon (3, points);

		    /* right */
		    SET_POINT3 (points, 14.0f,  7.0f,  0.0f,
				        10.5f,  0.0f,  0.0f,
				        14.0f,  0.0f,  0.0f);
		    HC_Insert_Polygon (3, points);
		HC_Close_Segment ();

		HC_Open_Segment ("Medium Box");
		    HC_Set_Color ("text = violet");
		    HC_Set_Text_Font ("size = 0.08 sru");
		    HC_Scale_Object (7.0, 7.0, 1.0);
		    HC_Translate_Object (7.0, 7.5, -0.01);
		    HC_Insert_Text (0.0, 0.0, 0.0, "Medium Box");
		HC_Close_Segment ();

		HC_Open_Segment ("OF CRAYONS");
		    HC_Set_Color ("text = maroon");
		    HC_Set_Text_Font ("size = 0.045 sru");
		    HC_Scale_Object (7.0, 7.0, 1.0);
		    HC_Translate_Object (7.0, 6.0, -0.01);
		    HC_Insert_Text (0.0, 0.0, 0.0, "OF CRAYONS");
		HC_Close_Segment ();

		HC_Open_Segment ("BUILT-IN SHARPENER");
		    HC_Set_Color ("text = red");
		    HC_Set_Text_Font ("size = 0.012 sru");
		    HC_Scale_Object (7.0, 7.0, 1.0);
		    HC_Translate_Object (7.0, 5.0, -0.01);
		    HC_Insert_Text (0.0, 0.0, 0.0, "BUILT-IN SHARPENER");
		HC_Close_Segment ();

		HC_Open_Segment ("72 CRAYONS");
		    HC_Set_Color ("text = forest green");
		    HC_Set_Text_Font ("transforms = on");
		    HC_Scale_Object (3.0, 7.0, 1.0);
		    HC_Translate_Object (7.0, 0.5, -0.01);
		    HC_Insert_Text (0.0, 0.0, 0.0, "72 CRAYONS");
		HC_Close_Segment ();
	    HC_Close_Segment ();
	HC_Close_Segment ();

	HC_Open_Segment ("message");
	    HC_Set_Color ("text = black");
	    HC_Set_Text_Font ("size = 0.02 sru");
	HC_Close_Segment ();
    HC_Close_Segment ();

    /*
     *   3. VIEW THE CLOSED BOX OF CRAYONS
     */
    HC_Open_Segment ("?picture");
	HC_Flush_Segment ("message");
	HC_QInsert_Text ("message",
			 7.0, -0.5, 0.0,
			 "Click to open box");
	HC_Pause ();
    HC_Close_Segment ();

    /*
     *   4. OPEN THE BOX TOP AND VIEW THE CRAYONS
     */
    HC_Open_Segment ("?picture");
	HC_Open_Segment ("box/top");
	    HC_Delete_Segment ("dividing line");
#if 0
	    HC_Delete_Segment ("base/closed");
	    HC_QUnSet_Visibility ("base/opened");
#endif
	    HC_Set_Text_Font ("transforms = on");
	    HC_Translate_Object (0.0, -9.0, -4.0);
	    HC_Rotate_Object (90.0, 0.0, 0.0);
	    HC_Translate_Object (0.0, 9.0, 4.0);
	HC_Close_Segment ();
	HC_Flush_Segment ("message");
	HC_QInsert_Text ("message",
			 7.0, -0.5, 0.0,
			"Click to make box transparent");
	HC_Pause ();
    HC_Close_Segment ();

    /*
     *   5.  MAKE THE BOX TRANSPARENT
     */
    HC_Open_Segment ("?picture");
	HC_Open_Segment ("box/top");
	    HC_Set_Visibility ("faces = off, edges = on");
	    HC_Set_Edge_Weight (3.0);
	HC_Close_Segment ();
	HC_Open_Segment ("box/bottom");
	    HC_Set_Visibility ("faces = off, edges = on");
	    HC_Set_Edge_Weight (3.0);
	HC_Close_Segment ();
	HC_Flush_Segment ("message");
	HC_QInsert_Text ("message",
			 7.0, -0.5, 0.0,
			"Click to rotate box");
	HC_Pause ();
    HC_Close_Segment ();

    /*
     *   6.  ROTATE A WIREFARME IMAGE AND THEN SHADE IT
     */
    HC_Open_Segment ("?picture");
    {
	int	i;

	HC_Flush_Segment ("message");
	HC_Set_Heuristics ("no hidden surfaces");
	HC_Open_Segment ("box");
	    HC_QSet_Visibility ("colors", "faces = off, edges = on");
	    HC_QSet_Text_Font ("bottom", "transforms = on");
	    for (i = 0; i < 45; i += 15) {
		HC_Translate_Object (-7.0, -7.0, -2.0);
		HC_Rotate_Object (-15.0, 0.0, 0.0);
		HC_Translate_Object (7.0, 7.0, 2.0);
		HC_Update_Display ();
	    }
	HC_Close_Segment ();
	HC_QInsert_Text ("message",
			 7.0, -0.5, 0.0,
			"Click to get shaded view");
	HC_Pause ();

	HC_Set_Heuristics ("hidden surfaces");
	HC_Insert_Distant_Light (1.0,  0.3, -1.0);
	HC_Insert_Distant_Light (1.0, -1.0, -1.0);
	HC_Set_Color ("ambient = black, lights = white");

	HC_QSet_Visibility ("box/colors", "faces = on, edges = off");
	HC_QSet_Visibility ("box/top",    "faces = on, edges = off");
	HC_QSet_Visibility ("box/bottom", "faces = on, edges = off");
	HC_Flush_Segment ("message");
	HC_QInsert_Text ("message",
			 7.0, -0.5, 0.0,
			"Click to end");
	HC_Pause ();
    }
    HC_Close_Segment ();

    HC_Exit_Program ();
    return 0;
}
