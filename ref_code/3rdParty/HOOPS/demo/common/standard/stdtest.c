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
 * $Id: stdtest.c,v 1.61 2010-10-26 21:29:09 jason Exp $
 */

/*
 * So you want to run standard test - well here's how it works:
 * After the humorous introductory screen (which appears for 4 seconds),
 * a description of the testing environment appears. This description
 * includes device information (based on the driver and hardware in
 * use) and HOOPS environment variable settings. Other than any variables
 * specific to the platform (e.g. HOOPS_FILES for extended DOS), the
 * only environment variable required to run STDTEST is HOOPS_PICTURE.
 * There are 14 tests that you can run. Execution continues from one test
 * to the next by simply hitting return. To run a specific test or to
 * run tests in a different order, you click on the button for that test.
 * To terminate the program, you can hit return until testing advances
 * to the quit button, click on quit, or type "q" at almost any time.
 * It's just that easy. Here are the purposes of the tests:
 *
 *  1. windows - tests draw_dc_rectangle
 *  2. polylines - tests draw_dc_polyline or draw_3d_polyline (if implemented)
 *  3. markers - tests draw_dc_dot, draw_dc_ellipse, draw_dc_outline_ellipse,
 *                and / or draw_dc_marker (if implemented)
 *  4. polygons - tests draw_dc_face in conjunction with draw_dc_polyline
 *                or draw_3d_polygon (if implemented)
 *  5. text - tests draw_dc_text
 *  6. images - tests draw_dc_*_rasters (multiple rasters in one call)
 *  7. shells - tests various drawing routines including draw_dc_*_rasters
 *                (one raster per call) or draw_3d_tristrip (if implemented)
 *  8. colors - tests color handling via draw_dc_face or draw_3d_polygon
 *  9. clipping - tests that hard clip limits are obeyed via draw_dc_rectangle,
 *                draw_dc_face, draw_dc_polyline, and in particular
 *                draw_dc_text and draw_dc_outline_ellipse / draw_dc_dot
 * 10. projections - tests projection handling (only useful for 3D drivers)
 * 11. handedness - tests face culling for those drivers that cull
 * 12. lighting - tests lighting for those drivers that do lighting, but
 *                also tests culling for those drivers that cull based on
 *                the direction of a normal
 * 13. input - tests request_keyboard (request_location is tested by using
 *                the mouse with the program)
 * 14. nurbs curves - tests view dependent/view independent, 
 *                curve trimming. and budgets
 * 15. nurbs surfaces - tests various trimming options, weights, knots
 * 16. cylinders - ensures that cylinders work with all combinations of world
 *                and polygon handedness, exercises the various options for endcap
 *                visibility
 *
 * Upon completion of each test, 2 numbers are provided: time to execute
 * measured in seconds (which appears in the lower right) and
 * allocated / in-use memory measured in K (which apears in the lower left).
 *
 * In addition to the 14 tests, there are 6 option buttons that allow
 * you to test with some common HOOPS options:
 * 1. reset - makes sure the driver survives a call to HC_Reset_System
 *            tests start_device getting called after a stop_device
 * 2. subscreen - tests that get_outer_window does a screen clear
 * 3. dbuffer - tests double buffered drawing for all tests
 * 4. black and white - tests black and white drawing for all tests
 *                      except those with lights and images
 * 5. graph - allows viewing of timing and memory usage results
 */

#include "hc.h"
#include "hc_standalone.h"
#include "hic.h"
#include "hversion.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>



#ifndef USE_NO_GL


#ifdef OSX_SYSTEM

# undef OS_INLINE
# define OS_INLINE static __inline__ /* workaround for a problem in agl headers */
# include <AGL/agl.h>
# include <OpenGL/gl.h>
# include <OpenGL/glu.h>
# include <Carbon/Carbon.h>

#else

#ifdef WINDOWS_SYSTEM
#	ifndef WIN32_LEAN_AND_MEAN
#		define WIN32_LEAN_AND_MEAN
#	endif
# include <windows.h>
#endif

# include <GL/gl.h>
# include <GL/glu.h>

#endif
#endif

#include "stdtest.h"

#ifdef UNIX_SYSTEM
#include <unistd.h>
#endif

#define EXTRA_POINTER_FORMAT extra_pointer_format()

#define NUM_RESULTS	14


/* convex clipping */
#define	SIDES	5
#define DTR(x)	((x)*3.1415927/180.0)

enum button_numbers {
	NO_TEST,
	WINDOWS,
	POLYLINES,
	MARKERS,
	POLYGONS,
	TEXT,
	IMAGES,
	SHELLS,
	COLORS,
	CLIPPING,
	PROJECTIONS,
	HANDEDNESS,
	LIGHTING,
	HINPUT,
	NURBS_CURVES,
	NURBS_SURFACES,
	CYLINDERS,
	CONVEX_CLIPPING,
	QUIT,
	RESET,
	SUBSCREEN,
	DOUBLE_BUFFER,
	BLACK_WHITE,
	GRAPHS,
	METAFILES
};

static char *labels[] = {
	"show.info",
	"windows",
	"polylines",
	"markers",
	"polygons",
	"text",
	"images",
	"shells",
	"colors",
	"clipping",
	"projections",
	"handedness",
	"lighting",
	"input"};

/* more convex clipping */
static	HIC_Convex_Clip_Region	const *ccr;
static	HIC_DC_Point			pent[256];

static	HIC_RGB	mask	= {0.85f, 0.85f, 0.85f};
static	HIC_RGB	pink	= {1.00f, 0.75f, 0.75f};
static	HIC_RGB	lgray	= {0.75f, 0.75f, 0.75f};
static	HIC_RGB	lblue	= {0.75f, 0.75f, 1.00f};

/* timing */
static Vertex	results[NUM_RESULTS + 2];
static float	results_max;
/* allocated memory */
static Vertex	results2[NUM_RESULTS + 2];
static float	results2_max;
/* in use memory */
static Vertex	results3[NUM_RESULTS + 2];

/* image output globals */
int     b_image_out = 0;
int     image_file_format = RAW_ASCII;
int     image_source = HOOPS_SW;
int     driver_type = DEFAULT_DRIVER;
int     frbuf_width, frbuf_height;
char    image_file_root[4096];
char    image_file_name[4096];
char    temp_file_name[4096];
char    *driver_name;
char    unixtime[256];


/* hardcopy output */
int b_hpgl_out = 0;
int b_hpgl2_out = 0;

void insert_square (
    float	x1,
    float	y1,
    float	x2,
    float	y2) {
    Vertex	vector[4];

    vector[0].x = x1;  vector[0].y = y1;  vector[0].z = 0.0f;
    vector[1].x = x1;  vector[1].y = y2;  vector[1].z = 0.0f;
    vector[2].x = x2;  vector[2].y = y2;  vector[2].z = 0.0f;
    vector[3].x = x2;  vector[3].y = y1;  vector[3].z = 0.0f;
    HC_Insert_Polygon (4, vector);
}

void insert_triangle (
    float	x1,
    float	y1,
    float	x2,
    float	y2,
    float	x3,
    float	y3) {
    Vertex	vector[4];

    vector[0].x = x1;  vector[0].y = y1;  vector[0].z = 0.0f;
    vector[1].x = x2;  vector[1].y = y2;  vector[1].z = 0.0f;
    vector[2].x = x3;  vector[2].y = y3;  vector[2].z = 0.0f;
    HC_Insert_Polygon (3, vector);
}

void insert_star (
    float		x,
    float		y,
    float		r1,
    float		r2) {
    Vertex		vector[12];
    int	i;

    for (i = 0; i <= S_NUMBER; i += 2) {
	vector[i].x = x + r1 * (float)sin (S_ANGLE * i);
	vector[i].y = y + r1 * (float)cos (S_ANGLE * i);
        vector[i].z = 0.0f;
    }
    for (i = 1; i <= S_NUMBER; i += 2) {
	vector[i].x = x + r2 * (float)sin (S_ANGLE * i);
	vector[i].y = y + r2 * (float)cos (S_ANGLE * i);
	vector[i].z = 0.0f;
    }
    HC_Insert_Polygon (S_NUMBER, vector);
}

void insert_pyramid (void) {
    Vertex	data[4];

    data[0].x =  0.0f; data[0].y =  0.0f; data[0].z =  0.0f;
    data[1].x = -0.8f; data[1].y =  0.8f; data[1].z =  0.3f;
    data[2].x =  0.8f; data[2].y =  0.8f; data[2].z =  0.3f;
    data[3].x =  0.0f; data[3].y =  0.0f; data[3].z =  0.0f;
    HC_Insert_Polygon (4, data);

    data[0].x =  0.0f; data[0].y =  0.0f; data[0].z =  0.0f;
    data[1].x = -0.8f; data[1].y =  0.8f; data[1].z =  0.3f;
    data[2].x = -0.8f; data[2].y = -0.8f; data[2].z =  0.3f;
    data[3].x =  0.0f; data[3].y =  0.0f; data[3].z =  0.0f;
    HC_Insert_Polygon (4, data);

    data[0].x =  0.0f; data[0].y =  0.0f; data[0].z =  0.0f;
    data[1].x =  0.8f; data[1].y =  0.8f; data[1].z =  0.3f;
    data[2].x =  0.8f; data[2].y = -0.8f; data[2].z =  0.3f;
    data[3].x =  0.0f; data[3].y =  0.0f; data[3].z =  0.0f;
    HC_Insert_Polygon (4, data);

    data[0].x =  0.0f; data[0].y =  0.0f; data[0].z =  0.0f;
    data[1].x = -0.8f; data[1].y = -0.8f; data[1].z =  0.3f;
    data[2].x =  0.8f; data[2].y = -0.8f; data[2].z =  0.3f;
    data[3].x =  0.0f; data[3].y =  0.0f; data[3].z =  0.0f;
    HC_Insert_Polygon (4, data);
}

void insert_shell (void) {
    Vertex	data[5];
    int		face[16];

    data[0].x =  0.0f; data[0].y =   0.0f; data[0].z =  0.0f;
    data[1].x =  0.8f; data[1].y =   0.8f; data[1].z =  0.3f;
    data[2].x = -0.8f; data[2].y =   0.8f; data[2].z =  0.3f;
    data[3].x = -0.8f; data[3].y =  -0.8f; data[3].z =  0.3f;
    data[4].x =  0.8f; data[4].y =  -0.8f; data[4].z =  0.3f;

    face[0]  = 3;
    face[1]  = 0;
    face[2]  = 2;
    face[3]  = 1;
    face[4]  = 3;
    face[5]  = 0;
    face[6]  = 3;
    face[7]  = 2;
    face[8]  = 3;
    face[9]  = 0;
    face[10] = 4;
    face[11] = 3;
    face[12] = 3;
    face[13] = 0;
    face[14] = 1;
    face[15] = 4;
    HC_Insert_Shell (5, data, 16, face);
}

void insert_mesh (void) {
    Vertex	data[9];

    data[0].x  = -0.9f; data[0].y  =  0.0f; data[0].z  = -0.9f;
    data[1].x  = -0.9f; data[1].y  =  0.0f; data[1].z  =  0.0f;
    data[2].x  = -0.9f; data[2].y  =  0.0f; data[2].z  =  0.9f;
    data[3].x  =  0.0f; data[3].y  =  0.9f; data[3].z  = -0.9f;
    data[4].x  =  0.0f; data[4].y  =  0.9f; data[4].z  =  0.0f;
    data[5].x  =  0.0f; data[5].y  =  0.9f; data[5].z  =  0.9f;
    data[6].x  =  0.9f; data[6].y  =  0.0f; data[6].z  = -0.9f;
    data[7].x  =  0.9f; data[7].y  =  0.0f; data[7].z  =  0.0f;
    data[8].x  =  0.9f; data[8].y  =  0.0f; data[8].z  =  0.9f;
    HC_Insert_Mesh (3, 3, data);
}

void insert_shape (void) {
    Vertex	data[11];

    data[0].x  = -0.9f; data[0].y  = -0.7f; data[0].z  =  0.0f;
    data[1].x  = -0.6f; data[1].y  =  0.9f; data[1].z  =  0.0f;
    data[2].x  =  0.6f; data[2].y  =  0.9f; data[2].z  =  0.0f;
    data[3].x  =  0.9f; data[3].y  = -0.7f; data[3].z  =  0.0f;
    data[4].x  =  0.1f; data[4].y  = -0.7f; data[4].z  =  0.0f;
    data[5].x  =  0.2f; data[5].y  = -0.3f; data[5].z  =  0.0f;
    data[6].x  =  0.6f; data[6].y  = -0.3f; data[6].z  =  0.0f;
    data[7].x  =  0.0f; data[7].y  =  0.7f; data[7].z  =  0.0f;
    data[8].x  = -0.6f; data[8].y  = -0.3f; data[8].z  =  0.0f;
    data[9].x  = -0.2f; data[9].y  = -0.3f; data[9].z  =  0.0f;
    data[10].x = -0.1f; data[10].y = -0.7f; data[10].z =  0.0f;
    HC_Insert_Polygon (11, data);
}

void insert_doily (void) {
    int	i,
			j;
    float		x[D_NUMBER],
			y[D_NUMBER];

    for (i = 0; i < D_NUMBER; i++) {
	x[i] = RADIUS * (float)sin (D_ANGLE * i);
	y[i] = RADIUS * (float)cos (D_ANGLE * i);
	for (j = i; j < D_NUMBER; j++) {
	    x[j] = RADIUS * (float)sin (D_ANGLE * j);
	    y[j] = RADIUS * (float)cos (D_ANGLE * j);
	    HC_Insert_Line ((double)x[i], (double)y[i], 0.0,
			    (double)x[j], (double)y[j], 0.0);
	}
    }
}

void insert_circle (
    float	x,
    float	y,
    float	r) {
    Vertex	vector[3];

    vector[0].x = x + r; vector[0].y = y;     vector[0].z = 0.0f;
    vector[1].x = x;     vector[1].y = y + r; vector[1].z = 0.0f;
    vector[2].x = x - r; vector[2].y = y;     vector[2].z = 0.0f;
    HC_Insert_Circle (&vector[0], &vector[1], &vector[2]);
}

void insert_ellipse (
    float	x,
    float	y,
    float	r1,
    float	r2) {
    Vertex	vector[3];

    vector[0].x = x;      vector[0].y = y;      vector[0].z = 0.0f;
    vector[1].x = x + r1; vector[1].y = y;      vector[1].z = 0.0f;
    vector[2].x = x;      vector[2].y = y + r2; vector[2].z = 0.0f;
    HC_Insert_Ellipse (&vector[0], &vector[1], &vector[2]);
}

void insert_cylinders( )
{
    float p1[3] = {  0.2f,  0.2f,  0 };
    float p2[3] = { -0.2f,  0.2f,  1 };
    float p3[3] = {  0.2f,     0,  0 };
    float p4[3] = { -0.2f,     0,  0 };
    float p5[3] = {  0.2f, -0.2f,  0 };
    float p6[3] = { -0.2f, -0.2f, -1 };
	float radius = 0.075f;
	char *tempstr;

	HC_Open_Segment( "" );
		tempstr = "none";
		HC_Translate_Object( -0.5, -0.5, 0 );
		HC_Insert_Cylinder( p1, p2, radius, tempstr );
		HC_Insert_Cylinder( p3, p4, radius, tempstr );
		HC_Insert_Cylinder( p5, p6, radius, tempstr );
		HC_Insert_Text( 0, 0.4f, 0, tempstr );
	HC_Close_Segment();
	HC_Open_Segment( "" );
		tempstr = "first";
		HC_Translate_Object(  0.5, -0.5, 0 );
		HC_Insert_Cylinder( p1, p2, radius, tempstr );
		HC_Insert_Cylinder( p3, p4, radius, tempstr );
		HC_Insert_Cylinder( p5, p6, radius, tempstr );
		HC_Insert_Text( 0, 0.4f, 0, tempstr );
	HC_Close_Segment();
	HC_Open_Segment( "" );
		tempstr = "second";
		HC_Translate_Object( -0.5,  0.5, 0 );
		HC_Insert_Cylinder( p1, p2, radius, tempstr );
		HC_Insert_Cylinder( p3, p4, radius, tempstr );
		HC_Insert_Cylinder( p5, p6, radius, tempstr );
		HC_Insert_Text( 0, 0.4f, 0, tempstr );
	HC_Close_Segment();
	HC_Open_Segment( "" );
		tempstr = "both";
		HC_Translate_Object(  0.5,  0.5, 0 );
		HC_Insert_Cylinder( p1, p2, radius, tempstr );
		HC_Insert_Cylinder( p3, p4, radius, tempstr );
		HC_Insert_Cylinder( p5, p6, radius, tempstr );
		HC_Insert_Text( 0, 0.4f, 0, tempstr );
	HC_Close_Segment();
}

/*
 * cw = clockwise
 * flt = front left top
 */
void insert_cw_flt_cube_sides (void) {
    Vertex	vertex[4];

    HC_Open_Segment ("front");
	/* front (clockwise) */
	HC_Set_Color ("faces = green");
	vertex[0].x = -0.65f; vertex[0].y = -0.65f; vertex[0].z =  0.65f;
	vertex[1].x = -0.65f; vertex[1].y =  0.65f; vertex[1].z =  0.65f;
	vertex[2].x =  0.65f; vertex[2].y =  0.65f; vertex[2].z =  0.65f;
	vertex[3].x =  0.65f; vertex[3].y = -0.65f; vertex[3].z =  0.65f;
	HC_Insert_Polygon (4, vertex);
    HC_Close_Segment ();

    HC_Open_Segment ("left");
	/* left side (clockwise) */
	HC_Set_Color ("faces = green");
	vertex[0].x = -0.65f; vertex[0].y = -0.65f; vertex[0].z = -0.65f;
	vertex[1].x = -0.65f; vertex[1].y =  0.65f; vertex[1].z = -0.65f;
	vertex[2].x = -0.65f; vertex[2].y =  0.65f; vertex[2].z =  0.65f;
	vertex[3].x = -0.65f; vertex[3].y = -0.65f; vertex[3].z =  0.65f;
	HC_Insert_Polygon (4, vertex);
    HC_Close_Segment ();

    HC_Open_Segment ("top");
	/* top (clockwise) */
	HC_Set_Color ("faces = green");
	vertex[0].x = -0.65f; vertex[0].y =  0.65f; vertex[0].z =  0.65f;
	vertex[1].x = -0.65f; vertex[1].y =  0.65f; vertex[1].z = -0.65f;
	vertex[2].x =  0.65f; vertex[2].y =  0.65f; vertex[2].z = -0.65f;
	vertex[3].x =  0.65f; vertex[3].y =  0.65f; vertex[3].z =  0.65f;
	HC_Insert_Polygon (4, vertex);
    HC_Close_Segment ();
}

/*
 * ccw = counter clockwise
 * brb = back right bottom
 */
void insert_ccw_brb_cube_sides (void) {
    Vertex	vertex[4];

    HC_Open_Segment ("back");
	/* back (counter clockwise) */
	HC_Set_Color ("faces = blue");
	vertex[0].x =  0.65f; vertex[0].y = -0.65f; vertex[0].z = -0.65f;
	vertex[1].x =  0.65f; vertex[1].y =  0.65f; vertex[1].z = -0.65f;
	vertex[2].x = -0.65f; vertex[2].y =  0.65f; vertex[2].z = -0.65f;
	vertex[3].x = -0.65f; vertex[3].y = -0.65f; vertex[3].z = -0.65f;
	HC_Insert_Polygon (4, vertex);
    HC_Close_Segment ();

    HC_Open_Segment ("right");
	/* right side (counter clockwise) */
	HC_Set_Color ("faces = blue");
	vertex[0].x =  0.65f; vertex[0].y = -0.65f; vertex[0].z =  0.65f;
	vertex[1].x =  0.65f; vertex[1].y =  0.65f; vertex[1].z =  0.65f;
	vertex[2].x =  0.65f; vertex[2].y =  0.65f; vertex[2].z = -0.65f;
	vertex[3].x =  0.65f; vertex[3].y = -0.65f; vertex[3].z = -0.65f;
	HC_Insert_Polygon (4, vertex);
    HC_Close_Segment ();

    HC_Open_Segment ("bottom");
	/* bottom (counter clockwise) */
	HC_Set_Color ("faces = blue");
	vertex[0].x =  0.65f; vertex[0].y = -0.65f; vertex[0].z =  0.65f;
	vertex[1].x =  0.65f; vertex[1].y = -0.65f; vertex[1].z = -0.65f;
	vertex[2].x = -0.65f; vertex[2].y = -0.65f; vertex[2].z = -0.65f;
	vertex[3].x = -0.65f; vertex[3].y = -0.65f; vertex[3].z =  0.65f;
	HC_Insert_Polygon (4, vertex);
    HC_Close_Segment ();
}

/*
 * ccw = counter clockwise
 * flt = front left top
 */
void insert_ccw_flt_cube_sides (void) {
    Vertex	vertex[4];

    HC_Open_Segment ("front");
	/* front (counter clockwise) */
	HC_Set_Color ("faces = blue");
	vertex[0].x = -0.65f; vertex[0].y = -0.65f; vertex[0].z =  0.65f;
	vertex[1].x =  0.65f; vertex[1].y = -0.65f; vertex[1].z =  0.65f;
	vertex[2].x =  0.65f; vertex[2].y =  0.65f; vertex[2].z =  0.65f;
	vertex[3].x = -0.65f; vertex[3].y =  0.65f; vertex[3].z =  0.65f;
	HC_Insert_Polygon (4, vertex);
    HC_Close_Segment ();

    HC_Open_Segment ("left");
	/* left side (counter clockwise) */
	HC_Set_Color ("faces = blue");
	vertex[0].x = -0.65f; vertex[0].y = -0.65f; vertex[0].z = -0.65f;
	vertex[1].x = -0.65f; vertex[1].y = -0.65f; vertex[1].z =  0.65f;
	vertex[2].x = -0.65f; vertex[2].y =  0.65f; vertex[2].z =  0.65f;
	vertex[3].x = -0.65f; vertex[3].y =  0.65f; vertex[3].z = -0.65f;
	HC_Insert_Polygon (4, vertex);
    HC_Close_Segment ();

    HC_Open_Segment ("top");
	/* top (counter clockwise) */
	HC_Set_Color ("faces = blue");
	vertex[0].x = -0.65f; vertex[0].y =  0.65f; vertex[0].z =  0.65f;
	vertex[1].x =  0.65f; vertex[1].y =  0.65f; vertex[1].z =  0.65f;
	vertex[2].x =  0.65f; vertex[2].y =  0.65f; vertex[2].z = -0.65f;
	vertex[3].x = -0.65f; vertex[3].y =  0.65f; vertex[3].z = -0.65f;
	HC_Insert_Polygon (4, vertex);
    HC_Close_Segment ();
}

/*
 * cw = clockwise
 * bw = back right bottom
 */
void insert_cw_brb_cube_sides (void) {
    Vertex	vertex[4];

    HC_Open_Segment ("back");
	/* back (clockwise) */
	HC_Set_Color ("faces = green");
	vertex[0].x =  0.65f; vertex[0].y = -0.65f; vertex[0].z = -0.65f;
	vertex[1].x = -0.65f; vertex[1].y = -0.65f; vertex[1].z = -0.65f;
	vertex[2].x = -0.65f; vertex[2].y =  0.65f; vertex[2].z = -0.65f;
	vertex[3].x =  0.65f; vertex[3].y =  0.65f; vertex[3].z = -0.65f;
	HC_Insert_Polygon (4, vertex);
    HC_Close_Segment ();

    HC_Open_Segment ("right");
	/* right side (clockwise) */
	HC_Set_Color ("faces = green");
	vertex[0].x =  0.65f; vertex[0].y = -0.65f; vertex[0].z =  0.65f;
	vertex[1].x =  0.65f; vertex[1].y = -0.65f; vertex[1].z = -0.65f;
	vertex[2].x =  0.65f; vertex[2].y =  0.65f; vertex[2].z = -0.65f;
	vertex[3].x =  0.65f; vertex[3].y =  0.65f; vertex[3].z =  0.65f;
	HC_Insert_Polygon (4, vertex);
    HC_Close_Segment ();

    HC_Open_Segment ("bottom");
	/* bottom (clockwise) */
	HC_Set_Color ("faces = green");
	vertex[0].x =  0.65f; vertex[0].y = -0.65f; vertex[0].z =  0.65f;
	vertex[1].x = -0.65f; vertex[1].y = -0.65f; vertex[1].z =  0.65f;
	vertex[2].x = -0.65f; vertex[2].y = -0.65f; vertex[2].z = -0.65f;
	vertex[3].x =  0.65f; vertex[3].y = -0.65f; vertex[3].z = -0.65f;
	HC_Insert_Polygon (4, vertex);
    HC_Close_Segment ();
}

void insert_cube_center_marker (void) {
    HC_Open_Segment ("marker");
	HC_Set_Color ("markers = red");
	HC_Insert_Marker (0.0, 0.0, 0.0);
	HC_Set_Marker_Symbol ("@");
	HC_Set_Marker_Size (0.5);
    HC_Close_Segment ();
}

int colored (void) {
    char	value[64];

    HC_QShow_One_Net_Driver_Option ("?my_picture", "force black-and-white", value);
    if (strcmp (value, "on") == 0)
	return FALSE;
    else
	return TRUE;
}

void insert_mapped8_image (void) {
    int			i, j;
    unsigned char	pixels[100][100];

    /* define the image based on the map */
    for (i = 0; i < 100; ++i)
	for (j = 0; j < 100; ++j)
	    pixels[j][i] = 1;
    for (i = 0; i < 100; ++i) {
	for (j = 0; j < 5; ++j)
	    pixels[j][i] = 0;
	for (j = 10; j < 15; ++j)
	    pixels[j][i] = 0;
	for (j = 20; j < 25; ++j)
	    pixels[j][i] = 0;
	for (j = 30; j < 35; ++j)
	    pixels[j][i] = 0;
	for (j = 40; j < 45; ++j)
	    pixels[j][i] = 0;
	for (j = 50; j < 55; ++j)
	    pixels[j][i] = 0;
	for (j = 60; j < 65; ++j)
	    pixels[j][i] = 0;
	for (j = 70; j < 75; ++j)
	    pixels[j][i] = 0;
	for (j = 80; j < 85; ++j)
	    pixels[j][i] = 0;
	for (j = 90; j < 95; ++j)
	    pixels[j][i] = 0;
    }
    for (i = 0; i < 25; ++i) {
	for (j = 0; j < 25; ++j) {
	    pixels[j][i] = 0;
	    pixels[j][99 - i] = 1;
	    pixels[99 - j][i] = 2;
	    pixels[99 - j][99 - i] = 0;
	}
    }

    /* make 1 instance of the image */
    HC_Insert_Image (0.0, 0.0, 0.0,
		     "mapped 8, name = image",
		     100, 100, (void *)pixels);
}

void segment (HIC_Rendition const * nr, HIC_Segment_Info const * si) {
    HIC_Int_Rectangle const	*rect = HIC_Show_Window_Extent(nr);
    float			cx = (float)0.5 * (rect->left + rect->right),
				cy = (float)0.5 * (rect->bottom + rect->top);
    float			hw = (float)0.5 * (rect->right - rect->left),
				hh = (float)0.5 * (rect->top - rect->bottom);
    float			rad = (float)0.75 * ((hw < hh) ? hw : hh);
    HIC_Rendition const *		r;
    int				i;

    /* define the convex clip region (a pentagon) */
    for (i=0; i<SIDES+1; i++) {
		pent[i].x = (float)(cx + rad * sin (DTR(360.0/SIDES*i)));
		pent[i].y = (float)(cy + rad * cos (DTR(360.0/SIDES*i)));
		pent[i].z = (float)0.0;
    }
    ccr = HIC_New_Convex_Clip_Region (nr, SIDES, pent);

    /* draw a polyline to show where it is */
    r = HIC_New_Rendition (nr);
	HIC_Set_Line_Color (r, &mask);
	HIC_Draw_DC_Polyline (r, SIDES+1, pent);
    HIC_Free_Rendition (r);

    /* continue drawing */
    HIC_Draw_Segment (nr, si);

    HIC_Free_Convex_Clip_Region (ccr);
}

void image (HIC_Rendition const * nr, HIC_Segment_Info const * si) {

	HIC_Rendition const * r;

	r = HIC_New_Rendition (nr);
	HIC_Set_Convex_Clip_Region (r, ccr);
	HIC_Draw_Segment (r, si);
	HIC_Free_Rendition (r);
}


void polyline (HIC_Rendition const * nr, int count, HIC_DC_Point const * p) {
    HIC_Rendition const * r;

    /* show original in lighter color */
    r = HIC_New_Rendition (nr);
	HIC_Set_Line_Color (r, &lgray);
	HIC_Draw_DC_Polyline (r, count, p);
    HIC_Free_Rendition (r);

    /* show clipped version */
    r = HIC_New_Rendition (nr);
	HIC_Set_Convex_Clip_Region (r, ccr);
	HIC_Draw_DC_Polyline (r, count, p);
    HIC_Free_Rendition (r);
}

void edge (HIC_Rendition const * nr, int count, HIC_DC_Point const * p) {
    HIC_Rendition const * r;

    /* show original in different color */
    r = HIC_New_Rendition (nr);
	HIC_Set_Line_Color (r, &pink);
	HIC_Draw_DC_Polyline (r, count, p);
    HIC_Free_Rendition (r);

    /* show clipped version */
    r = HIC_New_Rendition (nr);
	HIC_Set_Convex_Clip_Region (r, ccr);
	HIC_Draw_DC_Polyline (r, count, p);
    HIC_Free_Rendition (r);
}

void face (HIC_Rendition const * nr, int count, HIC_DC_Point const * p) {
    HIC_Rendition const * r;

    /* show original in lighter color */
    r = HIC_New_Rendition (nr);
	HIC_Set_Face_Color (r, &lblue);
	HIC_Draw_DC_Face (r, count, p);
    HIC_Free_Rendition (r);

    /* show clipped version */
    r = HIC_New_Rendition (nr);
	HIC_Set_Convex_Clip_Region (r, ccr);
	HIC_Draw_DC_Face (r, count, p);
    HIC_Free_Rendition (r);
}

void gouraud_triangle (HIC_Rendition const * nr, HIC_DC_Point const * p, HIC_RGBAS32 const * c) {
    HIC_Rendition const * r;
    HIC_RGBAS32	xc[3];
    int i;

    /* show original in lighter color */
    for (i=0; i<3; i++) {
		xc[i] = HIC_Pack_RGBAS32(
					((HIC_Unpack_RGBAS32_Red(c[i]) + 3*255) >> 2),
					((HIC_Unpack_RGBAS32_Green(c[i]) + 3*255) >> 2),
					((HIC_Unpack_RGBAS32_Blue(c[i]) + 3*255) >> 2),
					HIC_Unpack_RGBAS32_Alpha(c[i]));
    }
    HIC_Draw_DC_Gouraud_Triangle (nr, p, xc);

    /* show clipped version */
    r = HIC_New_Rendition (nr);
	HIC_Set_Convex_Clip_Region (r, ccr);
	HIC_Draw_DC_Gouraud_Triangle (r, p, c);
    HIC_Free_Rendition (r);
}

void text (HIC_Rendition const * nr, HIC_Text_Info const * ti) {
    HIC_Rendition const * r;

    /* show original in lighter color */
    r = HIC_New_Rendition (nr);
	HIC_Set_Text_Color (r, &lgray);
	HIC_Draw_Text (r, ti);
    HIC_Free_Rendition (r);

    /* show clipped version */
    r = HIC_New_Rendition (nr);
	HIC_Set_Convex_Clip_Region (r, ccr);
	HIC_Draw_Text (r, ti);
    HIC_Free_Rendition (r);
}


void parents_advisory (void) {
    HC_Print_Version ();
    HC_Open_Segment ("?my_picture");
	HC_Set_Text_Font ("size = 0.04 sru");
	HC_Insert_Text (0.0, 0.1, 0.0,
			"Due to this program's graphic nature, ");
	HC_Insert_Text (0.0, -0.1, 0.0,
			"viewer discretion is advised.");
	HC_Get_Wakeup (4.0);
	HC_Flush_All_Events ();
	HC_Flush_Geometry (".");
    HC_Close_Segment ();
}

void setup_window_structure (void) {
    char	info[256];
    float	y,
		size;

    HC_Open_Segment ("?style library/danger");
	HC_Set_Color ("window contrast = red");
    HC_Close_Segment ();

    HC_Open_Segment ("?style library/toggle");
	HC_Set_Color ("window contrast = blue");
    HC_Close_Segment ();

    HC_Open_Segment ("?style library/special");
	HC_Set_Color ("window contrast = green");
    HC_Close_Segment ();

    HC_Open_Segment ("?my_picture");
	HC_Define_System_Options ("obsolete checking, no bounding volumes");
	HC_Set_Driver_Options ("no force black-and-white");
	if (b_image_out) {
		HC_Set_Driver_Options ("subscreen = (-1.0, 1.0, -1.0, 1.0)");
	}
	HC_Set_Heuristics ("related selection limit = 0");

	HC_Set_Camera_Projection ("stretched");
	HC_Set_Text_Font ("size = 0.013 sru");
	HC_Set_Color ("windows = white, text = black");

	HC_Set_Selectability ("off");

	HC_Open_Segment ("title");
	    HC_Set_Text_Font ("size = 0.04 sru");
	    HC_Set_Window (-1.0, 1.0, 0.9, 1.0);
	    HC_Set_Heuristics ("no hidden surfaces");
	    HC_Insert_Text (0.0, 0.0, 0.0, "Standard Test");
	    HC_Open_Segment ("");
		HC_Set_Text_Font ("size = 0.01 sru");
		HC_Set_Text_Alignment ("<");
		HC_Insert_Text (-1.0, 0.0, 0.0,
				"Tech Soft Graphics Development");
	    HC_Close_Segment ();
	    HC_Open_Segment ("");
		HC_Set_Text_Font ("size = 0.01 sru");
		HC_Set_Text_Alignment (">");
		HC_Insert_Text (1.0, 0.0, 0.0, "$Revision: 1.61 $");
	    HC_Close_Segment ();
	HC_Close_Segment ();
	HC_Open_Segment ("draw");
	{
	    RGB		pcolors[3];
	    int		i;

	    HC_Set_Window (-1.0, 0.8, -0.9, 0.9);
	    for (i = 0; i < 3; ++i) {
		pcolors[i].r = pcolors[i].g = pcolors[i].b = 0.0f;
	    }
	    if (colored ())
		pcolors[0].r = pcolors[1].g = pcolors[2].b = 1.0f;
	    HC_Set_Color_Map_By_Value ("rgb", 3, pcolors);
	    HC_Set_Selectability ("windows = on");
	}
	HC_Close_Segment ();
	HC_Open_Segment ("buttons");
	    HC_Set_Window (0.8, 1.0, -0.9, 0.9);
	    HC_Set_Window_Frame ("off");
	    HC_Set_Heuristics ("no clipping, no hidden surfaces");
	    HC_Set_Selectability ("windows = on");
#define NUM_BUTTONS 26 /* legend counts as 2 */
	    size = (1.0f - (-1.0f)) / (float)NUM_BUTTONS;
	    y = 1.0f;
	    HC_Open_Segment ("windows");
		HC_Set_Window (-1.0, 1.0, y - size, y);
		y -= size;
		HC_Insert_Text (0.0, 0.0, 0.0, "windows");
	    HC_Close_Segment ();
	    HC_Open_Segment ("polylines");
		HC_Set_Window (-1.0, 1.0, (double)(y - size), (double)y);
		y -= size;
		HC_Insert_Text (0.0, 0.0, 0.0, "polylines");
	    HC_Close_Segment ();
	    HC_Open_Segment ("markers");
		HC_Set_Window (-1.0, 1.0, (double)(y - size), (double)y);
		y -= size;
		HC_Insert_Text (0.0, 0.0, 0.0, "markers");
	    HC_Close_Segment ();
	    HC_Open_Segment ("polygons");
		HC_Set_Window (-1.0, 1.0, (double)(y - size), (double)y);
		y -= size;
		HC_Insert_Text (0.0, 0.0, 0.0, "polygons");
	    HC_Close_Segment ();
	    HC_Open_Segment ("text");
		HC_Set_Window (-1.0, 1.0, (double)(y - size), (double)y);
		y -= size;
		HC_Insert_Text (0.0, 0.0, 0.0, "text");
	    HC_Close_Segment ();
	    HC_Open_Segment ("images");
		HC_Set_Window (-1.0, 1.0, (double)(y - size), (double)y);
		y -= size;
		HC_Insert_Text (0.0, 0.0, 0.0, "images");
	    HC_Close_Segment ();
	    HC_Open_Segment ("shells");
		HC_Set_Window (-1.0, 1.0, (double)(y - size), (double)y);
		y -= size;
		HC_Insert_Text (0.0, 0.0, 0.0, "shells");
	    HC_Close_Segment ();
	    HC_Open_Segment ("colors");
		HC_Set_Window (-1.0, 1.0, (double)(y - size), (double)y);
		y -= size;
		HC_Insert_Text (0.0, 0.0, 0.0, "colors");
	    HC_Close_Segment ();
	    HC_Open_Segment ("clipping");
		HC_Set_Window (-1.0, 1.0, (double)(y - size), (double)y);
		y -= size;
		HC_Insert_Text (0.0, 0.0, 0.0, "clipping");
	    HC_Close_Segment ();
	    HC_Open_Segment ("projections");
		HC_Set_Window (-1.0, 1.0, (double)(y - size), (double)y);
		y -= size;
		HC_Insert_Text (0.0, 0.0, 0.0, "projections");
	    HC_Close_Segment ();
	    HC_Open_Segment ("handedness");
		HC_Set_Window (-1.0, 1.0, (double)(y - size), (double)y);
		y -= size;
		HC_Insert_Text (0.0, 0.0, 0.0, "handedness");
	    HC_Close_Segment ();
	    HC_Open_Segment ("lighting");
		HC_Set_Window (-1.0, 1.0, (double)(y - size), (double)y);
		y -= size;
		HC_Insert_Text (0.0, 0.0, 0.0, "lighting");
	    HC_Close_Segment ();
	    HC_Open_Segment ("input");
		HC_Set_Window (-1.0, 1.0, (double)(y - size), (double)y);
		y -= size;
		HC_Insert_Text (0.0, 0.0, 0.0, "input");
	    HC_Close_Segment ();
		HC_Open_Segment ("nurbs_curves");
		HC_Set_Window (-1.0, 1.0, (double)(y - size), (double)y);
		y -= size;
		HC_Insert_Text (0.0, 0.0, 0.0, "NURBS curves");
	    HC_Close_Segment ();
	    HC_Open_Segment ("nurbs_surfaces");
		HC_Set_Window (-1.0, 1.0, (double)(y - size), (double)y);
		y -= size;
		HC_Insert_Text (0.0, 0.0, 0.0, "NURBS surfaces");
	    HC_Close_Segment ();
	    HC_Open_Segment ("cylinders");
		HC_Set_Window (-1.0, 1.0, (double)(y - size), (double)y);
		y -= size;
		HC_Insert_Text (0.0, 0.0, 0.0, "cylinders");
	    HC_Close_Segment ();
	    HC_Open_Segment ("convex_clipping");
		HC_Set_Window (-1.0, 1.0, (double)(y - size), (double)y);
		y -= size;
		HC_Insert_Text (0.0, 0.0, 0.0, "convex clipping");
	    HC_Close_Segment ();
	    HC_Open_Segment ("quit");
		HC_Set_Window (-1.0, 1.0, (double)(y - size), (double)y);
		y -= size;
		HC_Style_Segment ("?style library/danger");
		HC_Insert_Text (0.0, 0.0, 0.0, "QUIT");
	    HC_Close_Segment ();

	    HC_Open_Segment ("legend");
		HC_Set_Window (-1.0, 1.0, (double)(y - (size * 2)), (double)y);
		HC_Set_Selectability ("windows = off");
		y -= (size * 2);
		HC_Set_Text_Font ("size = 0.012 sru");
		HC_Open_Segment ("");
		    HC_Set_Text_Alignment ("<");
		    HC_Insert_Text (-0.9,  0.7, 0.0, "HOOPS:");
		    HC_Insert_Text (-0.9,  0.2, 0.0, "A.I.R.:");
		    HC_Insert_Text (-0.9, -0.2, 0.0, "I.M.:");
		    HC_Insert_Text (-0.9, -0.7, 0.0, "Kanji:");
		HC_Close_Segment ();
		HC_Open_Segment ("");
		    HC_Set_Text_Alignment (">");
		    HC_Show_System_Info ("hoops version", info);
		    HC_Insert_Text (0.9, 0.7, 0.0, info);
		    HC_Show_System_Info ("a.i.r. version", info);
		    if (strcmp (info, "not available") != 0)
			HC_Insert_Text (0.9, 0.2, 0.0, info);
		    else
			HC_Insert_Text (0.9, 0.2, 0.0, "N/A");
		    HC_Show_System_Info ("i.m. version", info);
		    if (strcmp (info, "not available") != 0)
			HC_Insert_Text (0.9, -0.2, 0.0, info);
		    else
			HC_Insert_Text (0.9, -0.2, 0.0, "N/A");
		    HC_Show_System_Info ("kanji present", info);
		    HC_Insert_Text (0.9, -0.7, 0.0, info);
		HC_Close_Segment ();
	    HC_Close_Segment ();

	    HC_Open_Segment ("reset");
		HC_Set_Window (-1.0, 1.0, (double)(y - size), (double)y);
		y -= size;
		HC_Style_Segment ("?style library/danger");
		HC_Insert_Text (0.0, 0.0, 0.0, "RESET");
	    HC_Close_Segment ();
	    HC_Open_Segment ("subscreen");
		HC_Set_Window (-1.0, 1.0, (double)(y - size), (double)y);
		y -= size;
		HC_Style_Segment ("?style library/toggle");
		HC_Set_Window_Pattern ("//");
		HC_Insert_Text (0.0, 0.0, 0.0, "subscreen");
		HC_Set_User_Options ("action=reduce");
	    HC_Close_Segment ();
	    HC_Open_Segment ("double buffer");
		HC_Set_Window (-1.0, 1.0, (double)(y - size), (double)y);
		y -= size;
		HC_Style_Segment ("?style library/toggle");
		HC_Set_Window_Pattern ("//");
		HC_Insert_Text (0.0, 0.0, 0.0, "dbuffer");
	    HC_Close_Segment ();
	    HC_Open_Segment ("black and white");
		HC_Set_Window (-1.0, 1.0, (double)(y - size), (double)y);
		y -= size;
		HC_Style_Segment ("?style library/toggle");
		HC_Set_Window_Pattern ("//");
		HC_Insert_Text (0.0, 0.0, 0.0, "black & white");
	    HC_Close_Segment ();
	    HC_Open_Segment ("graph");
		HC_Set_Window (-1.0, 1.0, (double)(y - size), (double)y);
		y -= size;
		HC_Style_Segment ("?style library/special");
		HC_Insert_Text (0.0, 0.0, 0.0, "graph");
	    HC_Close_Segment ();
	    HC_Open_Segment ("metafile");
		HC_Set_Window (-1.0, 1.0, (double)(y - size), (double)y);
		y -= size;
		HC_Style_Segment ("?style library/special");
		HC_Insert_Text (0.0, 0.0, 0.0, "metafile");
	    HC_Close_Segment ();
	    HC_QSet_Window_Frame ("*", "on");
	    HC_QUnSet_Window_Frame ("legend");
	HC_Close_Segment ();
	HC_Open_Segment ("memory");
	    HC_Set_Window (-1.0, -0.8, -1.0, -0.9);
	    HC_Set_Heuristics ("no clipping, no hidden surfaces");
	HC_Close_Segment ();
	HC_Open_Segment ("results");
	    HC_Set_Window (-0.8, 0.8, -1.0, -0.9);
	    HC_Set_Heuristics ("no hidden surfaces");
	    HC_Set_Text_Font ("size = 0.02 sru");
	HC_Close_Segment ();
	HC_Open_Segment ("time");
	    HC_Set_Window (0.8, 1.0, -1.0, -0.9);
	    HC_Set_Heuristics ("no clipping, no hidden surfaces");
	HC_Close_Segment ();
    HC_Close_Segment ();

    HC_Define_Alias ("?title",   "?my_picture/title");
    HC_Define_Alias ("?draw",    "?my_picture/draw");
    HC_Define_Alias ("?buttons", "?my_picture/buttons");
    HC_Define_Alias ("?memory",  "?my_picture/memory");
    HC_Define_Alias ("?results", "?my_picture/results");
    HC_Define_Alias ("?time",    "?my_picture/time");

	/* have to do this because internally ?keyboard is */
	/* set to ?picture -- go figure */
	HC_UnDefine_Alias ("?keyboard");
    HC_Define_Alias ("?keyboard", "?my_picture");

}


void identify_test (
    char	*segment) {

    HC_QUnSet_Color ("?buttons/*");
    HC_QSet_Color (segment, "windows = red, text = white");
    HC_Flush_Contents ("?draw", "geometry,cameras,lights");

    HC_QUnSet_Window_Frame ("?draw");
	HC_Create_Segment ("?draw/have at least one segment");
    HC_Delete_Segment ("?draw/*");

    /* nothing may exist under include */
    HC_Define_System_Options ("no warnings, no errors");
	HC_Create_Segment ("?include library/have at least one segment");
    HC_Delete_Segment ("?include library/*");
    HC_Define_System_Options ("warnings, errors");

    HC_Flush_Contents ("?memory",  "geometry");
    HC_Flush_Contents ("?results", "geometry");
    HC_Flush_Contents ("?time",    "geometry");
    HC_Relinquish_Memory ();
}

void post_memory (
    int		index) {
    long	allocated,
		in_use;
    char	string[256];

    HC_Show_Memory_Usage (&allocated, &in_use);

    results2[index].y = (float)allocated / 1024.0f;
    if (results2[index].y > results2_max)
	results2_max = results2[index].y;
    results3[index].y = (float)in_use / 1024.0f;

    HC_Open_Segment ("?memory");
	HC_Flush_Contents (".", "geometry");
	sprintf (string,
		 "%0.1f/%0.1f K",
		 results2[index].y,
		 results3[index].y);
	HC_Insert_Text (0.0, 0.0, 0.0, string);
    HC_Close_Segment ();
}

void post_time (
    int		index,
    float	start_time,
    float	stop_time) {
    char	string[256];

    results[index].y = stop_time - start_time;
    if (results[index].y > results_max)
	results_max = results[index].y;

    HC_Open_Segment ("?time");
	HC_Flush_Contents (".", "geometry");
	sprintf (string,
		 "%0.2f secs",
		 results[index].y);
	HC_Insert_Text (0.0, 0.0, 0.0, string);
    HC_Close_Segment ();
}

void post_results (
    char	*message) {

   /*
    * redundant flush in case update interrupts prevents the
    * one in identify_test from occurring
    */
    HC_Open_Segment ("?results");
	HC_Flush_Contents (".", "geometry");
	HC_Insert_Text (0.0, 0.25, 0.0, message);
    HC_Close_Segment ();
}

const char* extra_pointer_format(void)
{
	char buffer[1024];

	sprintf (buffer, "%p", (void*) buffer);
	if (buffer[0] == '0' && buffer[1] == 'x')
		return "";
	else 
		return "0x";

}


int raw_write (HC_KEY image_key, int width, int height, int binary)
{
        int		row=0,col=0;
        char	temp[256];
		char	*rawfile;

        FILE *fp;

        Pixel *image_row;
        Pixel *pixel;

        image_row = (Pixel *) malloc (width * sizeof(Pixel));
		rawfile = (char *) malloc (strlen(unixtime)+strlen("_")+strlen(image_file_name)+strlen(".raw")+1);

        if (binary){

				sprintf (rawfile, "%s-%s.rwb", unixtime, image_file_name);
                /* binary header info */
                fp = fopen (rawfile, "wb");

				fwrite (&width, sizeof(int), 1, fp);
				fwrite (&height, sizeof(int), 1, fp);
					/* binary image info */
				for (row = 0; row < height; ++row) {
					HC_Show_Partial_Image (image_key, 0, row, width, 1, image_row);
					pixel = image_row;
					for (col = 0; col < width; ++col) {
						fwrite (pixel, sizeof(Pixel), 1, fp);
						++pixel;
					}
				}
				fclose (fp);
				free(rawfile);
				free(image_row);
				return 1;
        }

		sprintf (rawfile, "%s-%s.raw", unixtime, image_file_name);

        /* ascii header info */
        fp = fopen (rawfile, "wt");
		sprintf (temp, "%d %d\n", width, height);
		fputs (temp, fp);

		/* ascii image info */
		for (row = 0; row < height; ++row) {
				HC_Show_Partial_Image (image_key, 0, row, width, 1, image_row);
				pixel = image_row;
				for (col = 0; col < width; ++col) {
						sprintf (temp, "%d ", pixel->r);
						fputs (temp, fp);
						sprintf (temp, "%d ", pixel->g);
						fputs (temp, fp);
						sprintf (temp, "%d\n", pixel->b);
						fputs (temp, fp);
						++pixel;
				}
		}
        fclose (fp);
		free (rawfile);
		free (image_row);
        return 1;

} /* raw_write */


void my_ogl_finish_picture(
	HIC_Rendition const * nr,
	bool swap_buffers)
{

	char	format[80];
    int		i=0, j=0, width, height, success;

	Pixel	*data, *flip, *pixel;
	HC_KEY	key;

	/* use IM's opinion even though it lies about width */
	width = HIC_Show_Device_Pixels_X(nr);
	height = HIC_Show_Device_Pixels_Y(nr);
	/* this fudge factor must be explainable */
	width += 9;

	/* hard wire the image size causes clipping*/
	/*
	width = 1280;
	height = 960;
	*/

	/* use the global from export_image */
	/*
	width = frbuf_width;
	height = frbuf_height;
	*/

	/* create a place to store the image and zero the block */
	data = (Pixel *) malloc (width * height * sizeof(Pixel)); 
	pixel = data;
	j = width * height;

	for (i = 0; i < j; i++){
		pixel->r = 0;
		pixel->g = 0;
		pixel->b = 0;
		++pixel;	
	}

    HIC_Finish_Picture( nr, swap_buffers );

#ifndef USE_NO_GL
	glReadBuffer(GL_FRONT);
	glReadPixels( 
		0, 0,
		width, height,
		GL_RGB,
		GL_UNSIGNED_BYTE,
		data);
#endif

	/* ogl and HOOPS data order is flipped */
	flip = (Pixel *) malloc (width * height * sizeof(Pixel)); 
	for (i = 0; i < height; i++) {
		for (j=0; j < width; j++) {

			flip[(i*width) + j].r = data[((height - 1 - i)*width)+j].r;
			flip[(i*width) + j].g = data[((height - 1 - i)*width)+j].g;
			flip[(i*width) + j].b = data[((height - 1 - i)*width)+j].b;
		}
	}


	/* create a HOOPS image from the frame buffer data */
	HC_Open_Segment ("/export");
		sprintf (format, "RGB,name=%s", image_file_name);
		key = HC_KInsert_Image (0.0, 0.0, 0.0, format, width, height, flip);
	HC_Close_Segment ();

	
	/* write binary or ascii file */
	success = raw_write (key, width, height, image_file_format);

	HC_Flush_Contents ("/export", "everything");
	HC_Delete_Segment ("/export");
 
	free(flip);
	free(data);
}


void export_image(char *name) {

	char	format[80], option[80];
	char    tempstr[128];
    int		i=0, j=0, width, height, success;

	HC_KEY	key;
	Pixel	*data, *pixel;
	Vertex	wul,wlr;

	if (image_source == OGL_HW) {

		sprintf (image_file_name, "%s-opengl", name);

		HC_Show_Device_Info( "?my_picture", "pixels", tempstr );
		sscanf( tempstr, "%d, %d", &frbuf_width, &frbuf_height );

		HC_Open_Segment ("?driver/opengl/temp_window");
			HC_Set_Camera_Projection ("stretched");
			HC_Set_Text_Font ("size = 0.01 sru");
			HC_Set_Callback ("finish picture = my ogl finish picture");
			HC_QUnSet_Window("?draw");
			HC_Include_Segment ("?draw");
		HC_Close_Segment();
		HC_Update_Display();

		HC_QSet_Window ("?draw",-1.0, 0.8, -0.9, 0.9);
   
		HC_Delete_Segment ("?driver/opengl/temp_window");

		return;
	}

	sprintf (image_file_name, "%s-image", name);
	
	/* determine size of the image */
	/* draw window is (-1.0, 0.8, -0.9, 0.9) */
	wul.x  = -1.0f;
	wul.y  =  0.8f;
	wul.z  =  0.0f;

	wlr.x =  0.9f;
	wlr.y = -0.9f;
	wlr.z =  0.0f;

	/* for now, we'll hard wire the sw image size instead of using the stuff below */
	width = 1024;
	height = 768;

/*
	if (HC_Compute_Coordinates ("?my_picture", "outer window", &wul,"local pixels",&pul) &&
		HC_Compute_Coordinates ("?my_picture", "outer window", &wlr,"local pixels",&plr)) {

		width = (int)((plr.x - pul.x));
		height = (int)((plr.y - pul.y));
	}
	else {
		width = (int)(1280.0f / 3.0f);
		height = (int)(1024.0f / 3.0f);
	}

*/


	/* create a place to store the image and zero the block */
	data = (Pixel *) malloc (width * height * sizeof(Pixel)); 
	pixel = data;
	j = width * height;

	for (i = 0; i < j; i++){
		pixel->r = 0;
		pixel->g = 0;
		pixel->b = 0;
		++pixel;	
	}

	/* create the image */
	HC_Open_Segment ("/export");
		sprintf (format, "RGB,name=%s", image_file_name);
		key = HC_KInsert_Image (0.0, 0.0, 0.0, format, width, height, data);
	HC_Close_Segment ();

	/* capture the main window into the image */
	HC_Open_Segment ("?driver/image/export");

		sprintf (option, "use window id = %s%p", EXTRA_POINTER_FORMAT, (void*)(HC_KEY)key);
		HC_Set_Driver_Options (option);
		/* HC_Set_Visibility("text=off"); */
		HC_Set_Camera_Projection ("stretched");
		HC_Set_Text_Font ("size = 0.01 sru");

		/* unset window before include or there will be two on the draw segment */
		HC_QUnSet_Window("?draw");
    	HC_Include_Segment ("?draw");
	HC_Close_Segment ();
	
	/* this temporarily stomps other windows with the draw window*/
	HC_Update_Display ();
	
	HC_QSet_Window ("?draw",-1.0, 0.8, -0.9, 0.9);
	
	/* write binary or ascii file */
	success = raw_write (key, width, height, image_file_format);

	HC_Flush_Contents ("/export", "everything");
	HC_Flush_Contents ("?driver/image/export", "everything");
	HC_Delete_Segment ("/export");
	HC_Delete_Segment ("?driver/image/export");

	free (data);

} /* export_image */


void export_hpgl(char *name) {

	char hpgl_file[1020];

	/* capture the main window into the image */
	if (b_hpgl_out)
		sprintf (hpgl_file, "?driver/hpgl/%s.hp", name);
	else 
		sprintf (hpgl_file, "?driver/hpgl2/%s.hp2", name);


	HC_Open_Segment (hpgl_file);

		HC_Set_Camera_Projection ("stretched");
		HC_Set_Text_Font ("size = 0.01 sru");

		/* unset window before include or there will be two on the draw segment */
		HC_QUnSet_Window ("?draw");
    	HC_Include_Segment ("?draw");
	HC_Close_Segment ();

	HC_Update_Display();

	HC_QSet_Window ("?draw", -1.0, 0.8, -0.9, 0.9);

	HC_Flush_Contents (hpgl_file, "everything");
	HC_Delete_Segment (hpgl_file);

}

void init (void) {

	char    expansion[1024];
	int     i;
	time_t  tp;

	time (&tp);
	sprintf (unixtime, "%ld", tp);

    HC_Show_Pathname_Expansion ("?picture", expansion);
    HC_Delete_Segment("?picture");
    HC_UnDefine_Alias("?picture");

    switch (driver_type) {

	case OGL: {
	    #ifdef WINDOWS_SYSTEM
		    HC_Define_Alias ("?my_picture", "?driver/opengl/window0");
		    HC_Create_Segment ("?my_picture");
	    #endif
	    #ifdef UNIX_SYSTEM
		    HC_Define_Alias ("?my_picture", "?driver/opengl/:0.0");
		    HC_Create_Segment ("?my_picture");
	    #endif

	    HC_Open_Segment("?my_picture");
		HC_Set_Rendering_Options("hsra=hzb");
		HC_Set_Driver_Options ("double-buffering");
	    HC_Close_Segment();

	}   break;

	case MSW: {
	    HC_Define_Alias ("?my_picture", "?driver/msw/window0");

	    HC_Open_Segment("?my_picture");
		HC_Set_Rendering_Options("hsra=szb");
		HC_Set_Driver_Options ("no double-buffering");
	    HC_Close_Segment();
	}   break;

	case X11: {
	    HC_Define_Alias ("?my_picture", "?driver/x11/:0.0");
	    HC_Open_Segment("?my_picture");
		HC_Set_Rendering_Options("hsra=szb");
		HC_Set_Driver_Options ("no double-buffering");
	    HC_Close_Segment();
	}	break;
	
	case DEFAULT_DRIVER: {
	    HC_Define_Alias ("?my_picture", expansion);
	    HC_Create_Segment ("?my_picture");
	}

    }

    /* timing results */
    for (i = 0; i < (NUM_RESULTS + 2); i++) {
	results[i].x = (float)i;
	results[i].y = 0.0f;
	results[i].z = 0.0f;
    }
    results[0].x = results[1].x;
    results[NUM_RESULTS + 1].x = results[NUM_RESULTS].x;
    /* fudged so the polygon has at least some height */
    results[0].y = results[NUM_RESULTS + 1].y = -0.001f;
    results_max = -1.0f;

    /* allocated and in use memory results */
    for (i = 0; i < (NUM_RESULTS + 2); i++) {
	results2[i].x = results3[i].x = results[i].x;
	results2[i].y = results3[i].y = results[i].y;
	results2[i].z = results3[i].z = 0.0f;
    }
    results2_max = -1.0f;

	HC_Define_Callback_Name ("segment", segment);
	HC_Define_Callback_Name ("image segment", image);
    HC_Define_Callback_Name ("polyline", polyline);
    HC_Define_Callback_Name ("edge", edge);
    HC_Define_Callback_Name ("face", face);
    HC_Define_Callback_Name ("gouraud triangle", gouraud_triangle);
    HC_Define_Callback_Name ("text", text);
	HC_Define_Callback_Name ("my ogl finish picture", my_ogl_finish_picture);

	setup_window_structure();
}


void show_execution_context (void) {
    float	start_time,
		stop_time,
		y,
		ydelta;
    int		i;


    HC_QSet_Color ("?buttons/*", "windows = white, text = black");
    HC_Update_Display ();

    HC_Show_Time (&start_time);
    HC_Open_Segment ("?draw/execution info");
	HC_Set_Text_Font ("size = 0.02 sru");
	HC_Open_Segment ("left");
	    HC_Set_Color ("text = black");
	    HC_Set_Text_Alignment ("<");
	HC_Close_Segment ();
	HC_Open_Segment ("right");
	    HC_Set_Color ("text = red");
	    HC_Set_Text_Alignment (">");
	HC_Close_Segment ();
	HC_Open_Segment ("titles");
	    HC_Set_Color ("text = blue");
	HC_Close_Segment ();
	HC_Open_Segment ("center");
	    HC_Set_Color ("text = black");
	    HC_Set_Text_Font ("size = 0.01 sru");
	HC_Close_Segment ();
	HC_Open_Segment ("center red");
	    HC_Set_Color ("text = red");
	    HC_Set_Text_Font ("size = 0.01 sru");
	HC_Close_Segment ();

	ydelta = 1.9f / (float)((NUM_CHOICES / 2) + NUM_VARIABLES + 3);
	y = 0.95f;

	HC_QInsert_Text ("titles", 0.0, (double)y, 0.0, "Device Info");
	y -= ydelta;
	for (i = 0; i < NUM_CHOICES; i++) {
	    char descriptor[256];
	    char answer[256];

	    sprintf (descriptor, "%s :", choices[i]);
	    HC_Show_Device_Info ("?my_picture", choices[i], answer);
	    if (strlen (answer) == 0)
		sprintf (answer, "%s", "<none>");

	    if (i % 2 == 0) {
		HC_QInsert_Text ("left",  -0.9, (double)y, 0.0, descriptor);
		HC_QInsert_Text ("right", -0.2, (double)y, 0.0, answer);
	    }
	    else {
		HC_QInsert_Text ("left",  0.2, (double)y, 0.0, descriptor);
		HC_QInsert_Text ("right", 0.9, (double)y, 0.0, answer);
		y -= ydelta;
	    }
	}

	y -= (ydelta * 2);
	HC_QInsert_Text ("titles",
			 0.0, (double)y, 0.0,
			 "Environment Variables");
	y -= ydelta;
	for (i = 0; i < NUM_VARIABLES; i++) {
	    char out[300];
	    char buf[256];

	    if (HC_Show_Environment (variables[i], buf)) {
		sprintf (out,
			 "%s : %s",
			 variables[i],
			 buf);
		HC_QInsert_Text ("center red", 0.0, (double)y, 0.0, out);
	    }
	    else {
		sprintf (out,
			 "%s : <undefined>",
			 variables[i]);
		HC_QInsert_Text ("center", 0.0, (double)y, 0.0, out);
	    }
	    y -= ydelta;
	}
    HC_Close_Segment ();
    HC_Update_Display ();
    HC_Show_Time (&stop_time);

    post_memory (1);
    post_results ("Environment variables may be overridden by program statements");
    post_time (1, start_time, stop_time);

}


void test_windows (void) {
    int	i;
    float	x,
			y;
    float		start_time,
			stop_time;

    identify_test ("?buttons/windows");
    HC_Update_Display ();

    HC_Open_Segment ("?include library/2 lines");
	HC_Set_Color ("lines = blue");
	HC_Set_Line_Weight (2.0);
	HC_Insert_Line (-1.0, -1.0, 0.0, 1.0,  1.0, 0.0);
	HC_Insert_Line (-1.0,  1.0, 0.0, 1.0, -1.0, 0.0);
    HC_Close_Segment ();

    HC_Show_Time (&start_time);
    HC_QSet_Window_Frame ("?draw", "off");
    HC_Open_Segment ("?draw/window patterns/top left");
	HC_Set_Rendering_Options ("technology = standard");
	HC_Set_Color ("window contrast = red, window = black");
	HC_Set_Window (-1.0, 0.0, 0.0, 1.0);
	HC_Set_Window_Frame ("on");
	HC_Set_Heuristics ("no hidden surfaces");
	HC_Open_Segment ("window set");
	    HC_Set_Color ("window contrast = red, window = white, text = black");
	    i = 0;
	    for (x = 0.35f; x > -0.86f; x -= WIDTH + GAP) {
		for (y = -0.9f; y < 0.8f; y += HEIGHT + GAP) {
		    HC_Open_Segment ("");
			HC_Set_Window ((double)x,
				       (double)(x + WIDTH),
				       (double)y,
				       (double)(y + HEIGHT));
			HC_Set_Window_Pattern (pattern[i]);
			HC_Open_Segment ("");
			    HC_Set_Window (-0.75, 0.75, -0.15, 0.15);
			    HC_Set_Window_Pattern ("Solid");
			    HC_Set_Window_Frame ("off");
			    HC_Insert_Text (0.0, 0.0, 0.0, pattern[i]);
			HC_Close_Segment ();
		    HC_Close_Segment ();
		    ++i;
		}
	    }
	HC_Close_Segment ();
    HC_Close_Segment ();
    HC_Open_Segment ("?draw/window patterns/top right");
	HC_Set_Rendering_Options ("technology = software frame buffer");
	HC_Set_Color ("window contrast = red, window = black");
	HC_Set_Window (0.0, 1.0, 0.0, 1.0);
	HC_Set_Window_Frame ("on");
	HC_Set_Heuristics ("no hidden surfaces");
	HC_Include_Segment ("?draw/window patterns/top left/window set");
    HC_Close_Segment ();
    HC_Open_Segment ("?draw/window patterns/bottom left");
	HC_Set_Rendering_Options ("technology = standard");
	HC_Set_Color ("window contrast = red, window = black");
	HC_Set_Window (-1.0, 0.0, -1.0, 0.0);
	HC_Set_Window_Frame ("off");
	HC_Set_Heuristics ("no hidden surfaces");
	HC_Include_Segment ("?draw/window patterns/top left/window set");
    HC_Close_Segment ();
    HC_Open_Segment ("?draw/window patterns/bottom right");
	HC_Set_Rendering_Options ("technology = software frame buffer");
	HC_Set_Color ("window contrast = red, window = black");
	HC_Set_Window (0.0, 1.0, -1.0, 0.0);
	HC_Set_Window_Frame ("off");
	HC_Set_Heuristics ("no hidden surfaces");
	HC_Include_Segment ("?draw/window patterns/top left/window set");
    HC_Close_Segment ();
    HC_Open_Segment ("?draw/clear window top left");
	HC_Set_Rendering_Options ("technology = standard");
	HC_Set_Window (-0.8, -0.2, 0.2, 0.8);
	HC_Set_Window_Pattern ("clear");
	HC_Set_Color ("window contrast = green");
	HC_Set_Window_Frame ("on");
	HC_Set_Heuristics ("no hidden surfaces");
	HC_Include_Segment ("?include library/2 lines");
    HC_Close_Segment ();
    HC_Open_Segment ("?draw/clear window top right");
	HC_Set_Rendering_Options ("technology = software frame buffer");
	HC_Set_Window (0.2, 0.8, 0.2, 0.8);
	HC_Set_Window_Pattern ("clear");
	HC_Set_Color ("window contrast = green");
	HC_Set_Window_Frame ("on");
	HC_Set_Heuristics ("no hidden surfaces");
	HC_Include_Segment ("?include library/2 lines");
    HC_Close_Segment ();
    HC_Open_Segment ("?draw/clear window bottom left");
	HC_Set_Rendering_Options ("technology = standard");
	HC_Set_Window (-0.8, -0.2, -0.8, -0.2);
	HC_Set_Window_Pattern ("clear");
	HC_Set_Color ("window contrast = green");
	HC_Set_Window_Frame ("off");
	HC_Set_Heuristics ("no hidden surfaces");
	HC_Include_Segment ("?include library/2 lines");
    HC_Close_Segment ();
    HC_Open_Segment ("?draw/clear window bottom right");
	HC_Set_Rendering_Options ("technology = software frame buffer");
	HC_Set_Window (0.2, 0.8, -0.8, -0.2);
	HC_Set_Window_Pattern ("clear");
	HC_Set_Color ("window contrast = green");
	HC_Set_Window_Frame ("off");
	HC_Set_Heuristics ("no hidden surfaces");
	HC_Include_Segment ("?include library/2 lines");
    HC_Close_Segment ();
    HC_Update_Display ();
    HC_Show_Time (&stop_time);

    post_memory (2);
    post_results ("top/bottom = frames on/off, left/right = technology standard/software frame buffer");
    post_time (2, start_time, stop_time);

    if (b_hpgl_out || b_hpgl2_out) {
		sprintf (temp_file_name, "%s-windows", image_file_root);
		export_hpgl (temp_file_name);
    }	

    if (b_image_out) {
		sprintf (temp_file_name, "%s-windows", image_file_root);
		export_image (temp_file_name);
    }

}

void test_polylines (void) {
    int	i;
    float		x, y,
			size,
			start_time,
			stop_time;
    Vertex		points[4];
    Vertex		arc[3];
    char		label[32];

    identify_test ("?buttons/polylines");
    HC_Update_Display ();

    for (i = 0; i < 4; i++) {
	points[i].x = points[i].y = points[i].z = 0.0f;
    }
    points[0].x = -0.9f;
    points[3].x = 0.9f;

    HC_Show_Time (&start_time);
    HC_Open_Segment ("?draw/line weights and colors");
	HC_Set_Window (-1.0, 0.0, 0.0, 1.0);
	HC_Set_Heuristics ("no hidden surfaces");
	size = 1.0f;
	y = -0.9f;
	for (i = 0; i < NUM_COLORS; ++i) {
	    HC_Open_Segment ("");
	        HC_Set_Color (color[i]);
                HC_Set_Line_Weight ((double)size);
		size += 1.0f;
		points[0].y = points[2].y = points[3].y = y;
		HC_Insert_Polyline (4, points);
            HC_Close_Segment ();
	    y += 1.8f / (float)(NUM_COLORS - 1);
        }
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/line patterns and weights");
	HC_Set_Window (-1.0, 0.0, -1.0, 0.0);
	HC_Set_Color ("text = red");
	HC_Set_Text_Alignment (">");
	HC_Set_Text_Font ("size = 0.01 sru");
	y = -0.9f;
	for (i = 0; i < NUM_LINE_PATTERNS; ++i) {
	    HC_Open_Segment ("");
		HC_Set_Line_Pattern (line_pattern[i]);
		HC_Insert_Text (-0.77, (double)y, 0.0, line_pattern[i]);
		HC_Open_Segment ("");
		    HC_Insert_Line (-0.75, (double)y, 0.0,
				     0.35, (double)y, 0.0);
		HC_Close_Segment ();
		HC_Open_Segment ("");
		    HC_Set_Line_Weight (5.0);
		    HC_Insert_Line (0.4,  (double)y, 0.0,
				    0.95, (double)y, 0.0);
		HC_Close_Segment ();
	    HC_Close_Segment ();
	    y += 1.8f / (float)(NUM_LINE_PATTERNS - 1);
	}
    HC_Close_Segment ();

    HC_Show_Time (&start_time);
    HC_Open_Segment ("?draw/caps and joins");
	HC_Set_Window (0.0, 1.0, 0.0, 1.0);
	HC_Set_Heuristics ("no hidden surfaces");
	HC_Set_Line_Weight (11.0);
	i = 0;
        for (x = 0.475f; x > -1.2f; x -= WIDTH + (GAP + 0.1f)) {
            for (y = -0.85f; y < 0.8f; y += HEIGHT + GAP) {
                HC_Open_Segment ("");
                    HC_Set_Color (color[i]);
		    HC_Set_Color ("text = black");
		    sprintf (label, "%s", capjoin[i]);
                    HC_Set_Line_Pattern (capjoin[i++]);
		    points[0].x = x;
		    points[0].y = y + HEIGHT - 0.04f;
		    points[1].x = x + WIDTH - 0.03f;
		    points[1].y = y + HEIGHT - 0.04f;
		    points[2].x = x;
		    points[2].y = y + 0.02f;
		    points[3].x = x + WIDTH - 0.03f;
		    points[3].y = y + 0.02f;
		    HC_Insert_Polyline (4, points);
		    HC_Open_Segment ("");
			HC_Set_Color (color[i]);
			HC_Set_Line_Weight (1.0);
			HC_Insert_Polyline (4, points);
		    HC_Close_Segment ();
                    HC_Insert_Text ((double)(x + WIDTH / 2),
				    (double)(y - GAP / 2),
				    0.0,
				    label);
                HC_Close_Segment ();
            }
        }
	HC_Insert_Text (0.0, -0.95, 0.0, "Cap and Join");
    HC_Close_Segment ();

    arc[0].z = 0.0f;
    arc[1].z = 0.0f;
    arc[2].z = 0.0f;
    HC_Open_Segment ("?draw/arc patterns and weights");
	HC_Set_Window (0.0, 1.0, -1.0, 0.0);
	y = -0.9f;
	size = 1.0f;
	for (i = 0; i < NUM_LINE_PATTERNS; ++i) {
	    HC_Open_Segment ("");
	        HC_Set_Color (color[i]);
                HC_Set_Line_Weight ((double)size);
		HC_Set_Line_Pattern (line_pattern[i]);
		HC_Open_Segment ("");
		    arc[0].x = -0.35f;
		    arc[0].y = y;
		    arc[1].x = 0.0f;
		    arc[1].y = y + 0.35f;
		    arc[2].x = 0.35f;
		    arc[2].y = y;
		    HC_Insert_Circular_Arc (&arc[0], &arc[1], &arc[2]);
		    HC_Translate_Object (-0.5, 0.0, 0.0);
		HC_Close_Segment ();
		HC_Open_Segment ("");
		    arc[0].x = 0.0f;
		    /* arc[0].y = y; */
		    arc[1].x = 0.25f;
		    arc[1].y = y;
		    arc[2].x = 0.0f;
		    arc[2].y = y + 0.15f;
		    HC_Insert_Elliptical_Arc (&arc[0], &arc[1], &arc[2],
					      0.0, 0.5);
		    HC_Translate_Object (0.5, 0.0, 0.0);
		HC_Close_Segment ();
	    HC_Close_Segment ();
	    y += 1.8f / (float)(NUM_LINE_PATTERNS - 1);
	    size += 1.0f;
	}
	HC_Insert_Text (-0.5, -0.95, 0.0, "Circular Arc");
	HC_Insert_Text (0.5, -0.95, 0.0, "Elliptical Arc");
    HC_Close_Segment ();
    HC_Update_Display ();

    HC_Show_Time (&stop_time);

    post_memory (3);
    post_results ("polylines (weights/colors, caps/joins, colors/patterns, patterns/weights)");
    post_time (3, start_time, stop_time);

    if (b_hpgl_out || b_hpgl2_out) {
		sprintf (temp_file_name, "%s-polylines", image_file_root);
		export_hpgl (temp_file_name);
    }

    if (b_image_out) {
		sprintf (temp_file_name, "%s-polylines", image_file_root);
		export_image (temp_file_name);
    }

}

void test_NURBS_curves (void) {

/* TODO remove */	
/*	const	float	control_pts1[] = {-1.16779f, -0.513514f, 0.0f,
				 -0.323728f, -0.794914f, 0.0f,
				 0.445761f, -0.507154f, 0.0f,
				 1.53389f, 0.220986f,  0.0f,
				 };
	const  float	control_pts2[]	=	{-1.37457f, 0.141494f, 0.0f,
				 -0.886438f, 0.90461f, 0.0f,
				 -0.357626f, 0.151033f, 0.0f,
				 0.0661016f, 0.936407f,  0.0f,
				 0.615252f, 0.189189f,  0.0f,	
				 1.06949f, 0.965024f,  0.0f,
				 1.56779f, 0.195548f,  0.0f,
				};
*/
	const	float	control_pts3[] = {18.0f, 9.0f, 8.0f,
				 18.0f, 39.0f, 8.0f,
				 -2.0f, 39.0f, 8.0f,
				 -2.0f, 9.0f,  8.0f,
				 -2.0f, -21.0f,  8.0f,	
				 18.0f, -21.0f,  8.0f,
				 18.0f, 9.0f, 8.0f};
	const	float	knots[] = {0, 0, 0, 0, 0.5f, 0.5f, 0.5f, 1, 1, 1, 1};
	const	float	weights[] = {1, 0.333333f, 0.333333f, 1, 0.333333f, 0.333333f, 1};

	float control_pts_sin360[360*3];
	float control_pts_sin10[10*3];
	float x, dx;
	int i;
	char *tempstr;

	x = -0.75f;
	dx = 1.5f/(360-1);
	for( i = 0 ; i < 360 ; i++ ) {
		control_pts_sin360[ i*3 + 0 ] = x;
		control_pts_sin360[ i*3 + 1 ] = 0.5f * (float)sin(x*3);
		control_pts_sin360[ i*3 + 2 ] = 0;
		x += dx;
	}

	x = -0.75f;
	dx = 1.5f/(10-1);
	for( i = 0 ; i < 10 ; i++ ) {
		control_pts_sin10[ i*3 + 0 ] = x;
		control_pts_sin10[ i*3 + 1 ] = (0.5f * (float)sin(x*3)) - 0.1f;
		control_pts_sin10[ i*3 + 2 ] = 0;
		x += dx;
	}

    identify_test ("?buttons/NURBS_curves");

	HC_Open_Segment ("?draw/scene/curvetest");
		HC_Set_Visibility("lines = on, markers = on");
		HC_Set_Color( "markers=blue" );
		HC_Set_Marker_Symbol( "." );
		HC_Open_Segment ("ul");
			HC_Set_Window (-1, 0, 0, 1);
			HC_Set_Rendering_Options ("nurbs curve = (view dependent)");
			HC_Open_Segment ("ulul");
				HC_Set_Window (-1, 0, 0, 1);
				HC_Insert_Text (0, 0.9, 0, "View Dependent");
				HC_Insert_Text (0, 0.75f, 0, "Degree 2");
				HC_Open_Segment ("large");
					HC_Set_Color ("lines=red,text=red");
					HC_Insert_Shell( 360, control_pts_sin360, 0, NULL );
					HC_Insert_NURBS_Curve (2, 360, control_pts_sin360, NULL, NULL, 0, 1);
					HC_Insert_Text (0,-0.75, 0, "CP Count = 360");
				HC_Close_Segment();
				HC_Open_Segment ("small");
					HC_Set_Color ("lines=green, text=green");
					HC_Insert_Shell( 10, control_pts_sin10, 0, NULL );
					HC_Insert_NURBS_Curve (2, 10, control_pts_sin10, NULL, NULL, 0, 1);
					HC_Insert_Text (0,-0.9, 0, "CP Count = 10");
				HC_Close_Segment ();
			HC_Close_Segment();
			HC_Open_Segment ("ulur");
				HC_Set_Window (0, 1, 0, 1);
				HC_Insert_Text (0, 0.9, 0, "View Dependent");
				HC_Insert_Text (0, 0.75f, 0, "Degree 3");
				HC_Open_Segment ("large");
					HC_Set_Color ("lines=red,text=red");
					HC_Insert_Shell( 360, control_pts_sin360, 0, NULL );
					HC_Insert_NURBS_Curve (3, 360, control_pts_sin360, NULL, NULL, 0, 1);
					HC_Insert_Text (0,-0.75, 0, "CP Count = 360");
				HC_Close_Segment();
				HC_Open_Segment ("small");
					HC_Set_Color ("lines=green, text=green");
					HC_Insert_Shell( 10, control_pts_sin10, 0, NULL );
					HC_Insert_NURBS_Curve (3, 10, control_pts_sin10, NULL, NULL, 0, 1);
					HC_Insert_Text (0,-0.9, 0, "CP Count = 10");
				HC_Close_Segment ();
			HC_Close_Segment();
			HC_Open_Segment ("ulll");
				HC_Set_Window (-1, 0, -1, 0.0);
				HC_Insert_Text (0, 0.9, 0, "View Dependent");
				HC_Insert_Text (0, 0.75f, 0, "Degree 5");
				HC_Open_Segment ("large");
					HC_Set_Color ("lines=red,text=red");
					HC_Insert_Shell( 360, control_pts_sin360, 0, NULL );
					HC_Insert_NURBS_Curve (5, 360, control_pts_sin360, NULL, NULL, 0, 1);
					HC_Insert_Text (0,-0.75, 0, "CP Count = 360");
				HC_Close_Segment();
				HC_Open_Segment ("small");
					HC_Set_Color ("lines=green, text=green");
					HC_Insert_Shell( 10, control_pts_sin10, 0, NULL );
					HC_Insert_NURBS_Curve (5, 10, control_pts_sin10, NULL, NULL, 0, 1);
					HC_Insert_Text (0,-0.9, 0, "CP Count = 10");
				HC_Close_Segment ();
			HC_Close_Segment();
			HC_Open_Segment ("ullr");
				HC_Set_Window (0, 1, -1, 0.0);
				HC_Insert_Text (0, 0.9, 0, "View Dependent");
				HC_Set_Window_Pattern ("clear");
				HC_Insert_Text (0, 0.75f, 0, "Degree 8");
				HC_Open_Segment ("large");
					HC_Set_Color ("lines=red,text=red");
					HC_Insert_Shell( 360, control_pts_sin360, 0, NULL );
					HC_Insert_NURBS_Curve (8, 360, control_pts_sin360, NULL, NULL, 0, 1);
					HC_Insert_Text (0,-0.75, 0, "CP Count = 360");
				HC_Close_Segment();
				HC_Open_Segment ("small");
					HC_Set_Color ("lines=green, text=green");
					HC_Insert_Shell( 10, control_pts_sin10, 0, NULL );
					HC_Insert_NURBS_Curve (8, 10, control_pts_sin10, NULL, NULL, 0, 1);
					HC_Insert_Text (0,-0.9, 0, "CP Count = 10");
				HC_Close_Segment ();
			HC_Close_Segment();
		HC_Close_Segment ();

		HC_Open_Segment ("ur");
			HC_Set_Window (0, 1, 0, 1);
			HC_Set_Rendering_Options ("nurbs curve = (view independent)");
			HC_Set_Rendering_Options ("nurbs curve = (budget = 25)");
			HC_Open_Segment ("label");
				HC_Set_Camera_Projection ("stretched");
				HC_Insert_Text (0, -0.9, 0, "View Independent, Budget = 25");
			HC_Close_Segment ();
			HC_Open_Segment ("degree2");
				HC_Open_Segment ("large");
					HC_Set_Color ("lines=red,text=red");
					HC_Set_Visibility("lines = on");
					HC_Insert_Shell( 360, control_pts_sin360, 0, NULL );
					HC_Insert_NURBS_Curve (2, 360, control_pts_sin360, NULL, NULL, 0, 1);
				HC_Close_Segment();
				HC_Open_Segment ("small");
					HC_Set_Color ("lines=green, text=green");
					HC_Insert_Shell( 10, control_pts_sin10, 0, NULL );
					HC_Insert_NURBS_Curve (2, 10, control_pts_sin10, NULL, NULL, 0, 1);
				HC_Close_Segment ();
			HC_Close_Segment();
		HC_Close_Segment ();
		HC_Open_Segment ("ll");
			HC_Set_Window (-1, 0, -1, 0.0);
			HC_Insert_Text (0, -0.9, 0, "view independent budgets");
			HC_Open_Segment("");
				HC_Set_Text_Alignment( "<" );
				HC_Set_Rendering_Options( "nurbs curve = (view independent)" );
				HC_Open_Segment ("");
					HC_Translate_Object( 0.5, 0.6, 0 );
					tempstr = "nurbs curve = (budget = 4, no continued budget)";
					HC_Set_Rendering_Options( tempstr );
					HC_Open_Segment( "curve" );
						HC_Scale_Object( 0.02f, 0.02f, 0.02f );
						HC_Insert_NURBS_Curve (3, 7, control_pts3, weights, knots, 0.05f, 0.95f);
					HC_Close_Segment();
					HC_Insert_Text (-1.4, 0, 0, tempstr);
				HC_Close_Segment();
				HC_Open_Segment ("");
					HC_Set_Color( "red" );
					HC_Translate_Object( 0.5, 0.2, 0 );
					tempstr = "nurbs curve = (budget = 10, continued budget = 3)";
					HC_Set_Rendering_Options( tempstr );
					HC_Open_Segment( "curve" );
						HC_Scale_Object( 0.02f, 0.02f, 0.02f );
						HC_Insert_NURBS_Curve (3, 7, control_pts3, weights, knots, 0.05f, 0.95f);
					HC_Close_Segment();
					HC_Insert_Text (-1.4,0,0, tempstr);
				HC_Close_Segment();
				HC_Open_Segment ("");
					HC_Translate_Object( 0.5, -0.2, 0 );
					tempstr = "nurbs curve = (budget = 30, no continued budget)";
					HC_Set_Rendering_Options( tempstr );
					HC_Open_Segment( "curve" );
						HC_Scale_Object( 0.02f, 0.02f, 0.02f );
						HC_Insert_NURBS_Curve (3, 7, control_pts3, weights, knots, 0.05f, 0.95f);
					HC_Close_Segment();
					HC_Insert_Text (-1.4, 0, 0, tempstr);
				HC_Close_Segment();
				HC_Open_Segment ("");
					HC_Set_Color( "red" );
					HC_Translate_Object( 0.5, -0.6, 0 );
					tempstr = "nurbs curve = (budget = 30, continued budget = 10)";
					HC_Set_Rendering_Options( tempstr );
					HC_Open_Segment( "curve" );
						HC_Scale_Object( 0.02f, 0.02f, 0.02f );
						HC_Insert_NURBS_Curve (3, 7, control_pts3, weights, knots, 0.05f, 0.95f);
					HC_Close_Segment();
					HC_Insert_Text (-1.4,0,0, tempstr);
				HC_Close_Segment();
			HC_Close_Segment();
		HC_Close_Segment ();
		HC_Open_Segment ("lr");
			HC_Set_Window (0, 1, -1, 0.0);
			HC_Open_Segment("trimmed");
				HC_Set_Color("red");
				HC_Set_Line_Weight (5);
				HC_Insert_Text (0, -0.9f, 0, "trimmed to [0.58, 0.66]");
				HC_Open_Segment( "curve" );
					HC_Scale_Object( 0.02f, 0.02f, 0.02f );
					HC_Insert_Shell( 7, control_pts3, 0, NULL );
					HC_Insert_NURBS_Curve (3, 7, control_pts3, weights, knots, 0.58f, 0.66f);
				HC_Close_Segment();
			HC_Close_Segment();
			HC_Open_Segment("untrimmed");
				HC_Set_Color("black");
				HC_Set_Line_Weight (1);
				HC_Insert_Text (0, -0.75f, 0, "untrimmed");
				HC_Open_Segment( "curve" );
					HC_Scale_Object( 0.02f, 0.02f, 0.02f );
					HC_Insert_Shell( 7, control_pts3, 0, NULL );
					HC_Insert_NURBS_Curve (3, 7, control_pts3, weights, knots, 0, 1);
				HC_Close_Segment();
			HC_Close_Segment();
		HC_Close_Segment ();
	HC_Close_Segment();
    HC_Update_Display ();

    if (b_hpgl_out || b_hpgl2_out) {
		sprintf (temp_file_name, "%s-NURBS_curves", image_file_root);
		export_hpgl (temp_file_name);
    }

    if (b_image_out) {
		sprintf (temp_file_name, "%s-NURBS_curves", image_file_root);
		export_image (temp_file_name);
    }

} /* end function test_NURBS_curves */

void test_markers (void) {
    int	i;
    int	j;
    float	x,
			y;
    float		size,
			start_time,
			stop_time;

    identify_test ("?buttons/markers");
    HC_Update_Display ();

    HC_Show_Time (&start_time);
    HC_Open_Segment ("?draw/markers");
	{
#	ifndef countof
#	    define countof(x) (sizeof(x) / sizeof(x[0]))
#	endif
	const char marker_pound[] = {100, 0, 0,   2, -38, 87, -38, -87, 2, 38, 87, 38, -87,
						     2, 87, -38, -87, -38, 2, 87, 38, -87, 38, 0};
	const char marker_wide_plus[] = {100, 0, 0,   13, 100, 25, 100, -25, 25, -25, 25, -100, -25, -100,
							     -25, -25, -100, -25, -100, 25, -25, 25, -25, 100,
							     25, 100, 25, 25, 100, 25, 0};
	const char marker_open_arrow[] = {100, 0, 0,   3, 83, -100, 0, 100, -83, -100, 0};
	const char marker_closed_arrow[] = {100, 0, 0,   4, 83, -100, 0, 100, -83, -100, 83, -100, 0};
	const char marker_vertical_bar[] = {100, 0, 0,   2, 0, 87, 0, -87, 0};
	const char marker_half_arrow_left[] = {100, 0, 0,   2, 100, 100, -87, -87, 0};
	const char marker_half_arrow_right[] = {100, 0, 0,   2, -100, 100, 87, -87, 0};
	const char marker_wide_arrow[] = {100, 0, 0,   4, 0, 100, -100, -100, 100, -100, 0, 100, 0};
	const char marker_double_arrow[] = {100, 0, 0,   8, -100, 0, 0, 0, 100, -100, -100, -100,
								0, 0, 100, 0, 0, 100, -100, 0, 0};
	const char marker_letter_y[] = {100, 0, 0,   2, -63, 87, 0, 0, 2, 0, 0, 63, 87, 2, 0, 0, 0, -87, 0};
	const char marker_letter_z[] = {100, 0, 0,   4, -63, 87, 63, 87, -63, -87, 63, -87, 0};

	HC_Define_Glyph("#", countof(marker_pound), marker_pound);
	HC_Define_Glyph("++", countof(marker_wide_plus), marker_wide_plus);
	HC_Define_Glyph("/ \\", countof(marker_open_arrow), marker_open_arrow);
	HC_Define_Glyph("/_\\", countof(marker_closed_arrow), marker_closed_arrow);
	HC_Define_Glyph("|", countof(marker_vertical_bar), marker_vertical_bar);
	HC_Define_Glyph("/", countof(marker_half_arrow_left), marker_half_arrow_left);
	HC_Define_Glyph("\\", countof(marker_half_arrow_right), marker_half_arrow_right);
	HC_Define_Glyph("/__\\", countof(marker_wide_arrow), marker_wide_arrow);
	HC_Define_Glyph("/_^_\\", countof(marker_double_arrow), marker_double_arrow);
	HC_Define_Glyph("y", countof(marker_letter_y), marker_letter_y);
	HC_Define_Glyph("z", countof(marker_letter_z), marker_letter_z);
	}
	HC_Set_Heuristics ("no hidden surfaces");
	x = -0.97f;
	for (i = 0; i < NUM_MARKERS; i++) {
	    size = 0.0f;
	    y = -0.95f;
	    for (j = 0; j < NUM_COLORS; j++) {
		HC_Open_Segment ("");
		    HC_Set_Marker_Symbol (symbol[i]);
		    HC_Insert_Marker ((double)x, (double)y, 0.0);
		    HC_Set_Color (color[j]);
		    HC_Set_Marker_Size ((double)size);
		HC_Close_Segment ();
		size += 0.125f;
		y += (2.0f / (float)NUM_COLORS);
	    }
	    x += (2.0f / (float)NUM_MARKERS);
	}
    HC_Close_Segment ();
    HC_Update_Display ();
    HC_Show_Time (&stop_time);

    post_memory (4);
    post_results ("markers in various sizes and colors");
    post_time (4, start_time, stop_time);

    if (b_hpgl_out || b_hpgl2_out) {
		sprintf (temp_file_name, "%s-markers", image_file_root);
		export_hpgl (temp_file_name);
    }

    if (b_image_out) {
		sprintf (temp_file_name, "%s-markers", image_file_root);
		export_image (temp_file_name);
    }
}

void test_polygons (void) {
    int	i;
    float	x, y;
    char		label[80];
    float		start_time,
			stop_time;

    identify_test ("?buttons/polygons");
    HC_Update_Display ();

    HC_Open_Segment ("?include library/shape");
	HC_Set_Heuristics ("concave polygons");
	insert_shape ();
    HC_Close_Segment ();
    HC_Open_Segment ("?include library/ellipse");
	insert_ellipse (0.0f, 0.0f, 0.25f, 0.45f);
    HC_Close_Segment ();
    HC_Open_Segment ("?include library/circle");
	insert_circle (0.0f, 0.25f, 0.45f);
    HC_Close_Segment ();
    HC_Open_Segment ("?include library/set");
	HC_Open_Segment ("");
	    HC_Set_Color ("faces = red, edges = blue");
	    HC_Include_Segment ("?include library/shape");
	    HC_Translate_Object (-1.25, 0.0, 0.0);
	    HC_Scale_Object (0.75, 0.75, 1.0);
	HC_Close_Segment ();
	HC_Open_Segment ("");
	    HC_Set_Color ("faces = blue, edges = green");
	    HC_Include_Segment ("?include library/ellipse");
	HC_Close_Segment ();
	HC_Open_Segment ("");
	    HC_Set_Color ("faces = green, edges = red");
	    HC_Include_Segment ("?include library/circle");
	    HC_Translate_Object (1.0, -0.25, 0.0);
	HC_Close_Segment ();
    HC_Close_Segment ();

    HC_Show_Time (&start_time);
    HC_Open_Segment ("?draw/polygons");
	HC_Set_Window (-1.0, -0.33, -1.0, 1.0);
	HC_Set_Heuristics ("no hidden surfaces, concave polygons");
	HC_Set_Camera_Projection ("perspective");
	HC_Set_Color ("text = black, windows = white");

	for (i = 0; i < NUM_VISIBILITIES; i++) {
	    HC_Open_Segment ("");
		HC_Set_Window (-1.0, 1.0, 0.5 - 0.5 * i, 1.0 - 0.5 * i);
		HC_Set_Visibility (visibilities1[i]);
		HC_Insert_Text (0.0, -0.85, 0.0, visibilities1[i]);
		HC_Include_Segment ("?include library/set");
	    HC_Close_Segment ();
	}
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/patterned polygons");
	HC_Set_Window (-0.33, 0.33, 0.0, 1.0);
	HC_Set_Heuristics ("no hidden surfaces, concave polygons");
	HC_Set_Camera_Projection ("perspective");
	HC_Set_Visibility ("faces = on, edges = off");
	HC_Insert_Text (0.0, 0.95, 0.0, "Face Color, Face Pattern");
	i = 0;
        for (x = 0.475f; x > -1.2f; x -= WIDTH + (GAP + 0.1f)) {
            for (y = -0.85f; y < 0.8f; y += HEIGHT + GAP) {
                HC_Open_Segment ("");
		    sprintf (label, "%s, %s", color[i], pattern[i]);
                    HC_Set_Color (color[i]);
		    HC_Set_Color ("text = black");
                    HC_Set_Face_Pattern (pattern[i++]);
		    if (i < 4)
			insert_triangle (x,
					 y,
					 x + WIDTH / 2.0f,
					 y + HEIGHT,
					 x + WIDTH,
					 y);
		    else if (i < 7)
			insert_square (x,
				       y,
				       x + WIDTH,
				       y + HEIGHT);
		    else
			insert_star (x + WIDTH / 2.0f,
				     y + HEIGHT / 2.0f,
				     0.275f,
				     0.1f);
                    HC_Insert_Text ((double)(x + WIDTH / 2.0f),
				    (double)(y - GAP / 2.0f),
				    0.0,
				    label);
                HC_Close_Segment ();
            }
        }
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/patterned edge polygons");
	HC_Set_Window (-0.33, 0.33, -1.0, 0.0);
	HC_Set_Heuristics ("no hidden surfaces, concave polygons");
	HC_Set_Camera_Projection ("perspective");
	HC_Set_Visibility ("faces = off, edges = on");
	HC_Insert_Text (0.0, 0.95, 0.0, "Edge Pattern");
	HC_Set_Color ("text = black, edges = blue");
	i = 0;
        for (x = 0.475f; x > -1.2f; x -= WIDTH + (GAP + 0.1f)) {
            for (y = -0.85f; y < 0.8f; y += HEIGHT + GAP) {
                HC_Open_Segment ("");
		    sprintf (label, "%s", line_pattern[i]);
                    HC_Set_Edge_Pattern (line_pattern[i++]);
		    if (i < 4)
			insert_triangle (x,
					 y,
					 x + WIDTH / 2.0f,
					 y + HEIGHT,
					 x + WIDTH,
					 y);
		    else if (i < 7)
			insert_square (x,
				       y,
				       x + WIDTH,
				       y + HEIGHT);
		    else
			insert_star (x + WIDTH / 2.0f,
				     y + HEIGHT / 2.0f,
				     0.275f,
				     0.1f);
                    HC_Insert_Text ((double)(x + WIDTH / 2.0f),
				    (double)(y - GAP / 2.0f),
				    0.0,
				    label);
                HC_Close_Segment ();
            }
        }
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/wide edged polygons");
	HC_Set_Window (0.33, 1.0, -1.0, 1.0);
	HC_Set_Heuristics ("no hidden surfaces");
	HC_Set_Camera_Projection ("perspective");
	HC_Set_Color ("faces = red, edges = blue, text = black");
	HC_Set_Visibility (visibilities1[3]);
	HC_Open_Segment ("");
	    HC_Set_Window (-1.0, 1.0, 0.5, 1.0);
	    HC_Set_Edge_Weight (0.0);
	    HC_Insert_Text (0.0, -0.85, 0.0, "edge weight = 0 (shows as 1)");
	    HC_Include_Segment ("?include library/set");
	HC_Close_Segment ();
	HC_Open_Segment ("");
	    HC_Set_Window (-1.0, 1.0, 0.0, 0.5);
	    HC_Set_Edge_Weight (2.0);
	    HC_Insert_Text (0.0, -0.85, 0.0, "edge weight = 2");
	    HC_Include_Segment ("?include library/set");
	HC_Close_Segment ();
	HC_Open_Segment ("");
	    HC_Set_Window (-1.0, 1.0, -0.5, 0.0);
	    HC_Set_Edge_Weight (3.0);
	    HC_Insert_Text (0.0, -0.85, 0.0, "edge weight = 3");
	    HC_Include_Segment ("?include library/set");
	HC_Close_Segment ();
	HC_Open_Segment ("");
	    HC_Set_Window (-1.0, 1.0, -1.0, -0.5);
	    HC_Set_Edge_Weight (5.0);
	    HC_Insert_Text (0.0, -0.85, 0.0, "edge weight = 5");
	    HC_Include_Segment ("?include library/set");
	HC_Close_Segment ();
    HC_Close_Segment ();
    HC_Update_Display ();
    HC_Show_Time (&stop_time);

    post_memory (5);
    post_results ("polygon, ellipse, circle (visibilities, colors, face/edge patterns, & edge weights)");
    post_time (5, start_time, stop_time);

    if (b_hpgl_out || b_hpgl2_out) {
		sprintf (temp_file_name, "%s-polygons", image_file_root);
		export_hpgl (temp_file_name);
    }

    if (b_image_out) {
		sprintf (temp_file_name, "%s-polygons", image_file_root);
		export_image (temp_file_name);
    }
}

void test_cylinders (void) {

	/* TODO remove */
    /*int steps = 500;*/

	identify_test ("?buttons/cylinders");

	HC_Open_Segment("?draw/scene");

		HC_Set_Color ("faces=green");

		HC_Open_Segment( "ul" );
			HC_Set_Window (-1.0, -0.33, 0.0, 1.0);
			HC_Set_Rendering_Options("hsra=hidden line");
			HC_Insert_Text (0.0, -0.90, 0.0, "hidden line");
			insert_cylinders( );
		HC_Close_Segment();

		HC_Open_Segment( "uc" );
			HC_Set_Window (-0.33, 0.33, 0.0, 1.0);
			HC_Insert_Distant_Light( 0, 1, 0 );
			HC_Set_Rendering_Options( "lighting interpolation = gouraud" );
			HC_Set_Heuristics( "polygon handedness = left" );
			insert_cylinders( );
			HC_Insert_Text (0.0, -0.90, 0.0, "polygon handedness = left");
		HC_Close_Segment();

		HC_Open_Segment( "ur" );
			HC_Set_Window (0.33, 1.0, 0.0, 1.0);
			HC_Insert_Distant_Light( 0, 1, 0 );
			HC_Set_Heuristics( "polygon handedness = right" );
			insert_cylinders( );
			HC_Insert_Text (0.0, -0.90, 0.0, "polygon handedness = right");
		HC_Close_Segment();

		HC_Open_Segment( "ll" );
			HC_Set_Window (-1.0, -0.33, -1.0, 0.0);
			HC_Insert_Distant_Light( 0, 1, 0 );
			HC_Set_Heuristics( "no polygon handedness" );
			insert_cylinders( );
			HC_Insert_Text (0.0, -0.90, 0.0, "no polygon handedness");
		HC_Close_Segment();

		HC_Open_Segment( "lc" );
			HC_Set_Window (0.33, 1.0, -1.0, 0.0);
			HC_Set_Rendering_Options( "no lighting interpolation" );
			insert_cylinders( );
			HC_Insert_Text (0.0, -0.90, 0.0, "unlit");
		HC_Close_Segment();

		HC_Open_Segment( "lr" );
			HC_Set_Window (-0.33, 0.33, -1.0, 0.0);
			HC_Insert_Distant_Light( 0, 1, 0 );
			HC_Set_Color ("faces=transmission=grey");
			insert_cylinders( );
			HC_Insert_Text (0.0, -0.90, 0.0, "transparent");
		HC_Close_Segment();

	HC_Close_Segment();
    
    if (b_hpgl_out || b_hpgl2_out) {
		sprintf (temp_file_name, "%s-cylinders", image_file_root);
		export_hpgl (temp_file_name);
    }

    if (b_image_out) {
		sprintf (temp_file_name, "%s-cylinders", image_file_root);
		export_image (temp_file_name);
    }
}

void test_text (void) {
    float	y,
		size,
		start_time,
		stop_time;
    char	label[80];
    char	family_name[256];
    char	data[256];
    int		i, found_font;
    Vertex	grid, ref1, ref2;

    identify_test ("?buttons/text");
    HC_Update_Display ();

    HC_Show_Time (&start_time);
    HC_Open_Segment ("?draw/text");
	HC_Set_Heuristics ("no hidden surfaces");
        HC_Open_Segment ("");
	    HC_Set_Window (-1.0, -0.1, -0.2, 1.0);
	    HC_Set_Streaming_Mode ("on");
	    HC_Insert_Text (0.0, 0.95, 0.0, "Text sizes in SRU");
	    HC_Insert_Text (-0.6, -0.95, 0.0, "default size tolerance");
	    HC_Insert_Text (0.6, -0.95, 0.0, "no size tolerance");
	    size = 0.01f;
	    i = 0;
	    for (y = -0.85f; y < 0.75f; y += 0.2f) {
		HC_Set_Color (color[i]);
		sprintf (label, "size = %0.2f sru", size);
		HC_Set_Text_Font (label);
		sprintf (label, "%0.2f", size);
		HC_Insert_Text (-0.6, (double)y, 0.0, label);
		size += 0.01f;
		i++;
	    }
	    HC_Set_Text_Font ("no size tolerance");
	    size = 0.01f;
	    i = 0;
	    for (y = -0.85f; y < 0.75f; y += 0.2f) {
		HC_Set_Color (color[i]);
		sprintf (label, "size = %0.2f sru", size);
		HC_Set_Text_Font (label);
		sprintf (label, "%0.2f", size);
		HC_Insert_Text (0.6, (double)y, 0.0, label);
		size += 0.01f;
		i++;
	    }
        HC_Close_Segment ();

	HC_Open_Segment ("");
	    HC_Set_Window (-0.1, 1.0, 0.0, 1.0);
	    HC_Set_Text_Font ("size = 0.06 wru");
	    HC_Set_Color ("text = red");
	    HC_Open_Segment ("");
		HC_Set_Text_Alignment ("<");
		HC_Open_Segment ("");
		    HC_Set_Text_Font ("name = roman");
		    HC_Insert_Text (-1.0, 0.9, 0.0, "Roman");
		HC_Close_Segment ();
		HC_Open_Segment ("");
		    HC_Set_Text_Font ("name = sans serif");
		    HC_Insert_Text (-1.0, 0.7, 0.0, "Sans Serif");
		HC_Close_Segment ();
		HC_Open_Segment ("");
		    HC_Set_Text_Font ("name = typewriter");
		    HC_Insert_Text (-1.0, 0.5, 0.0, "Typewriter");
		HC_Close_Segment ();
		HC_Open_Segment ("");
		    HC_Set_Text_Font ("name = stroked");
		    HC_Insert_Text (-1.0, 0.3, 0.0, "Stroked");
		HC_Close_Segment ();
		HC_Open_Segment ("");
		    HC_Set_Text_Font ("name = system default");
		    HC_Insert_Text (-1.0, 0.1, 0.0, "System Default");
		HC_Close_Segment ();
		HC_Open_Segment ("");
		    HC_Set_Text_Font ("name = Newfield");
		    HC_Insert_Text (-1.0, -0.1, 0.0, "Newfield");
		HC_Close_Segment ();
		HC_Open_Segment ("");
		    HC_Set_Text_Font ("name = Enfield");
		    HC_Insert_Text (-1.0, -0.3, 0.0, "Enfield");
		HC_Close_Segment ();
		HC_Open_Segment ("");
		    HC_Set_Text_Font ("name = Brooktondale");
		    HC_Insert_Text (-1.0, -0.5, 0.0, "Brooktondale");
		HC_Close_Segment ();
		HC_Open_Segment ("");
		    HC_Set_Text_Font ("name = Kuma");
		    HC_Insert_Text (-1.0, -0.7, 0.0, "Kuma");
		HC_Close_Segment ();
		HC_Open_Segment ("");
		{
		    char	yes_or_no[32];
			HC_Set_Text_Font ("name = Kuma");/*needed until kuma -> unicode*/
		    HC_Show_System_Info ("kanji present", yes_or_no);
		    if (strcmp (yes_or_no, "yes") == 0)
			HC_Insert_Text_With_Encoding (-1.0, -0.9, 0.0, "EUC",
			    "EUC: \310\364\363\310\306\360\302\316\270\370\273\312");
		    else
			HC_Insert_Text (-1.0, -0.9, 0.0, "no HOOPS Kanji");
		}
		HC_Close_Segment ();
	    HC_Close_Segment ();
	    HC_Open_Segment ("");
		HC_Set_Text_Alignment (">");
		HC_Open_Segment ("");
		    HC_Set_Text_Font ("name = amie.pfa");
		    HC_Insert_Text (1.0, 0.9, 0.0, "AMIE.PFA");
		HC_Close_Segment ();
		HC_Open_Segment ("");
		    HC_Set_Text_Font ("name = cave.pfa");
		    HC_Insert_Text (1.0, 0.7, 0.0, "CAVE.PFA");
		HC_Close_Segment ();
		HC_Open_Segment ("");
		    HC_Set_Text_Font ("name = curly.pfa");
		    HC_Insert_Text (1.0, 0.5, 0.0, "CURLY.PFA");
		HC_Close_Segment ();
		HC_Open_Segment ("");
		    HC_Set_Text_Font ("name = haeberli.pfa");
		    HC_Insert_Text (1.0, 0.3, 0.0, "HAEBERLI.PFA");
		HC_Close_Segment ();
		HC_Open_Segment ("");
		    HC_Set_Text_Font ("name = honesty.pfa");
		    HC_Insert_Text (1.0, 0.1, 0.0, "HONESTY.PFA");
		HC_Close_Segment ();
		HC_Open_Segment ("");
		    HC_Set_Text_Font ("name = inja.pfa");
		    HC_Insert_Text (1.0, -0.1, 0.0, "INJA.PFA");
		HC_Close_Segment ();
		HC_Open_Segment ("");
		    HC_Set_Text_Font ("name = rock.pfa");
		    HC_Insert_Text (1.0, -0.3, 0.0, "ROCK.PFA");
		HC_Close_Segment ();
		HC_Open_Segment ("");
		    HC_Set_Text_Font ("name = sorority.pfa");
		    HC_Insert_Text (1.0, -0.5, 0.0, "SORORITY.PFA");
		HC_Close_Segment ();
		HC_Open_Segment ("");
		    HC_Set_Text_Font ("name = strokey.pfa");
		    HC_Insert_Text (1.0, -0.7, 0.0, "STROKEY.PFA");
		HC_Close_Segment ();
		HC_Open_Segment ("");
		    HC_Set_Text_Font ("name = wingding.ttf");
		    HC_Insert_Text (1.0, -0.9, 0.0, "WIGD.TF");
		HC_Close_Segment ();
	    HC_Close_Segment ();
	HC_Close_Segment ();

	HC_Open_Segment ("");
	    HC_Set_Window (-0.7, 1.0, -1.0, -0.2);
	    HC_Set_Color ("lines = green, edges = green, markers = red");
	    HC_Set_Text_Font ("size = 0.05 wru");
	    HC_Set_Marker_Symbol ("@");
	    HC_Set_Marker_Size (0.125);
	    HC_Set_Streaming_Mode ("on");

	    HC_Set_Visibility ("faces = off, edges = on, text = on");
	    grid.x = 0.3f; grid.y = 0.3f; grid.z = 1.0f;
	    ref1.x = 0.6f; ref1.y = 0.3f; ref1.z = 1.0f;
	    ref2.x = 0.3f; ref2.y = 0.6f; ref2.z = 1.0f;
	    HC_Insert_Grid ("quadrilateral", &grid, &ref1, &ref2, 2, 2);

	    HC_Set_Text_Alignment ("^>");
	    HC_Insert_Text (0.9, 0.9, 0.0, "^>");
	    HC_Set_Text_Alignment ("*>");
	    HC_Insert_Text (0.9, 0.6, 0.0, "*>");
	    HC_Set_Text_Alignment ("v>");
	    HC_Insert_Text (0.9, 0.3, 0.0, "v>");

	    HC_Set_Text_Alignment ("^*");
	    HC_Insert_Text (0.6, 0.9, 0.0, "^*");
	    HC_Set_Text_Alignment ("*");
	    HC_Insert_Text (0.6, 0.6, 0.0, "*");
	    HC_Set_Text_Alignment ("v*");
	    HC_Insert_Text (0.6, 0.3, 0.0, "v*");

	    HC_Set_Text_Alignment ("<^");
	    HC_Insert_Text (0.3, 0.9, 0.0, "<^");
	    HC_Set_Text_Alignment ("<*");
	    HC_Insert_Text (0.3, 0.6, 0.0, "<*");
	    HC_Set_Text_Alignment ("<v");
	    HC_Insert_Text (0.3, 0.3, 0.0, "<v");

	    HC_Show_One_Net_Text_Font ("name", family_name);
	    HC_Show_Font_Info ("?my_picture", family_name, "rotatable", data);
	    if (strcmp (data, "yes") != 0) {
		HC_Begin_Font_Search ("?my_picture", "family");
		    while (HC_Find_Font (family_name)) {
			char	*cp, data[256];

			HC_Show_Font_Info ("?my_picture", family_name,
							   "rotatable", data);
			cp = family_name;
			while (*cp){
			    *cp = (char)tolower ((int)*cp);
				++cp;
			}

			if ((strcmp (data, "yes") == 0) &&
			    (strcmp (family_name, "amie.pfa") != 0)) {
			    HC_Show_Font_Info ("?my_picture", family_name,
					       "defined", data);
			    if (strcmp (data, "yes") != 0) {
				sprintf (data, "name = %s", family_name);
				HC_Set_Text_Font (data);
				break;
			    }
			}
		    }
		HC_End_Font_Search ();
	    }
	    HC_Set_Text_Font ("rotation = follow path, size = 0.06 wru");
	    HC_Set_Text_Alignment ("<v");
	    HC_Insert_Text (-0.8, -0.8, 0.0, "     Default Path=(1.0,0.0,0.0)");
	    HC_Set_Text_Path (1.0, 0.5, 0.0);
	    HC_Insert_Text (-0.8, -0.8, 0.0, "     Path=(1.0,0.5,0.0)");
	    HC_Set_Text_Path (0.5, 1.0, 0.0);
	    HC_Insert_Text (-0.8, -0.8, 0.0, "     Path=(0.5,1.0,0.0)");
	    HC_Set_Text_Path (0.0, 1.0, 0.0);
	    HC_Insert_Text (-0.8, -0.8, 0.0, "     Path=(0.0,1.0,0.0)");

	    HC_Insert_Line (0.8, -0.3, 1.0, 0.2, -0.3, 1.0);
	    HC_Insert_Line (0.5, -0.8, 1.0, 0.5, 0.2, 1.0);

	    HC_Set_Text_Alignment (">");
	    HC_Set_Text_Path (1.0, 0.0, 0.0);
	    HC_Insert_Text (0.8, -0.3, 0.0, "XyZzY");
	    HC_Insert_Marker (0.8, -0.3, 0.0);
	    HC_Set_Text_Alignment ("^");
	    HC_Set_Text_Path (0.0, 1.0, 0.0);
	    HC_Insert_Text (0.5, 0.2, 0.0, "XyZzY");
	    HC_Insert_Marker (0.5, 0.2, 0.0);
	    HC_Set_Text_Alignment ("<");
	    HC_Set_Text_Path (-1.0, 0.0, 0.0);
	    HC_Insert_Text (0.2, -0.3, 0.0, "XyZzY");
	    HC_Insert_Marker (0.2, -0.3, 0.0);
	    HC_Set_Text_Alignment ("v");
	    HC_Set_Text_Path (0.0, -1.0, 0.0);
	    HC_Insert_Text (0.5, -0.8, 0.0, "XyZzY");
	    HC_Insert_Marker (0.5, -0.8, 0.0);
	HC_Close_Segment ();

	HC_Open_Segment ("");
	    HC_Set_Window (-0.1, 1.0, -0.2, 0.0);
	    HC_Set_Color ("text = blue");
	    HC_Set_Streaming_Mode ("on");
	    found_font = FALSE;
	    HC_Begin_Font_Search ("?my_picture", "family");
		while (HC_Find_Font (family_name)) {
		    char	data[256], *cp;

		    HC_Show_Font_Info ("?my_picture", family_name,
				       "slantable", data);
			cp = (char*)family_name;
			while (*cp){
			    *cp = (char)tolower ((int)*cp);
				++cp;
			}

		    if ((strcmp (data, "yes") == 0) &&
			(strcmp (family_name, "amie.pfa") != 0)) {
			HC_Show_Font_Info ("?my_picture", family_name,
					   "defined", data);
			if (strcmp (data, "yes") != 0) {
			    sprintf (data, "name = %s", family_name);
			    HC_Set_Text_Font (data);
			    found_font = TRUE;
			    break;
			}
		    }
		}
	    HC_End_Font_Search ();
	    HC_Set_Text_Font ("size = 10 pt");
	    if (!found_font)
		sprintf (data, "size = 10 pt");
	    else
		sprintf (data, "size = 10 pt (%s)", family_name);
	    HC_Insert_Text (0.0, 0.5f, 0.0, data);
	    HC_Set_Text_Alignment ("<");
	    HC_Set_Text_Font ("slant = 20");
	    HC_Insert_Text (-0.9, -0.5, 0.0, "slant = 20");
	    HC_Set_Text_Alignment (">");
	    HC_Set_Text_Font ("slant = -20");
	    HC_Insert_Text (0.9, -0.5, 0.0, "slant = -20");
	HC_Close_Segment ();
	HC_Open_Segment ("");
	    HC_Set_Window (-1.0, -0.7, -1.0, -0.2);
	    HC_Open_Segment ("");
		HC_Set_Text_Font ("size = 0.03 oru");
		HC_Insert_Text (0.0, 0.6, 0.0, "0.03 oru");
	    HC_Close_Segment ();
	    HC_Open_Segment ("");
		HC_Set_Text_Font ("size = 0.03 sru");
		HC_Insert_Text (0.0, 0.2, 0.0, "0.03 sru");
	    HC_Close_Segment ();
	    HC_Open_Segment ("");
		HC_Set_Text_Font ("size = 0.03 wru");
		HC_Insert_Text (0.0, -0.2, 0.0, "0.03 wru");
	    HC_Close_Segment ();
	    HC_Open_Segment ("");
		HC_Set_Text_Font ("size = 12 pt");
		HC_Insert_Text (0.0, -0.6, 0.0, "12 pt");
	    HC_Close_Segment ();
	HC_Close_Segment ();
    HC_Close_Segment ();
    HC_Update_Display ();
    HC_Show_Time (&stop_time);

    post_memory (6);
    post_results ("text (color and sizes, families, 1st rotatable, slanting, rotation, alignment)");
    post_time (6, start_time, stop_time);

    if (b_hpgl_out || b_hpgl2_out) {
		sprintf (temp_file_name, "%s-text", image_file_root);
		export_hpgl (temp_file_name);
    }
	
    if (b_image_out) {
		sprintf (temp_file_name, "%s-text", image_file_root);
		export_image (temp_file_name);
    } 
}


void test_images (void) {
    float		start_time,
			stop_time;

    identify_test ("?buttons/images");
    HC_QSet_Driver_Options ("?my_picture", "no fixed colors");
    HC_Update_Display ();

    HC_Open_Segment ("?include library/image");
	insert_mapped8_image ();
    HC_Close_Segment ();

    HC_Show_Time (&start_time);
    HC_Open_Segment ("?draw/image/left");
	HC_Set_Color ("window = black");
	HC_Set_Window (-0.95, -0.05, -0.95, -0.05);
	HC_Set_Window_Frame ("off");
	HC_Set_Heuristics ("no hidden surfaces");
	HC_Set_Camera_By_Volume ("orthographic", -50.0, 50.0, -50.0, 50.0);

	/* make 3 instances of the image */
	HC_Open_Segment ("");
	    HC_Include_Segment ("?include library/image");
	HC_Close_Segment ();
	HC_Open_Segment ("");
	    HC_Include_Segment ("?include library/image");
	    HC_Translate_Object (-55.0, -55.0, 0.0);
	HC_Close_Segment ();
	HC_Open_Segment ("");
	    HC_Include_Segment ("?include library/image");
	    HC_Translate_Object (55.0, 55.0, 0.0);
	HC_Close_Segment ();
    HC_Close_Segment ();
    HC_Open_Segment ("?draw/image/right");
	HC_Set_Rendering_Options ("technology = software frame buffer");
	HC_Set_Color ("window = black, text = white");
	HC_Set_Window (0.05, 0.95, -0.95, -0.05);
	HC_Set_Window_Frame ("off");
	HC_Set_Heuristics ("no hidden surfaces");
	HC_Open_Segment ("");
	    HC_Include_Segment ("?include library/image");
	HC_Close_Segment ();
	HC_Open_Segment ("");
	    HC_Include_Segment ("?include library/image");
	    HC_Translate_Object (-0.5, -0.5, 0.0);
	HC_Close_Segment ();
	HC_Open_Segment ("");
	    HC_Include_Segment ("?include library/image");
	    HC_Translate_Object (0.5, 0.5, 0.0);
	HC_Close_Segment ();
	HC_Insert_Text (0.0, -0.9, 0.0, "software frame buffer");
    HC_Close_Segment ();
    HC_Update_Display ();

    {
	HC_KEY		key;
	float		x, y, z;
	int		w, h, size_x, size_y;
	char		format[80];
	unsigned char	*data;
	char		option[80];
	Vertex		world_upper_left,
			world_lower_right,
			pixels_upper_left,
			pixels_lower_right;

	/* determine size of an image that's 1/3 of the window */
	world_upper_left.x  = -1.0f;
	world_upper_left.y  =  1.0f;
	world_upper_left.z  =  0.0f;
	world_lower_right.x =  1.0f;
	world_lower_right.y = -1.0f;
	world_lower_right.z =  0.0f;
	if (HC_Compute_Coordinates ("?my_picture",
				    "world",
				    &world_upper_left,
				    "outer pixels",
				    &pixels_upper_left) &&
	    /* figure out how big to make the image */
	    HC_Compute_Coordinates ("?my_picture",
				    "world",
				    &world_lower_right,
				    "outer pixels",
				    &pixels_lower_right)) {
	    size_x = (int)((pixels_lower_right.x -
			    pixels_upper_left.x) / 3.0f);
	    size_y = (int)((pixels_lower_right.y -
			    pixels_upper_left.y) / 3.0f);
	}
	else {
	    /* should never fail, just in case */
	    size_x = (int)(1280.0f / 3.0f);
	    size_y = (int)(1024.0f / 3.0f);
	}

	/* create a place to store the image */
	data = (unsigned char *) malloc (
		   (unsigned int)size_x *
		   (unsigned int)size_y * 3 *
		   sizeof (unsigned char));
	{
	    int i, j;

	    j = size_x * size_y * 3;
	    for (i = 0; i < j; i++)
		data[i] = 0;
	}

	HC_Open_Segment ("/null");
	    key = HC_KInsert_Image (0.0, 0.0, 0.0, "RGB",
				    size_x, size_y, data);
	HC_Close_Segment ();

	/* capture what's in ?picture into the image */
	HC_Open_Segment ("?driver/image/snapshot");

		sprintf (option, "use window id = %s%p", EXTRA_POINTER_FORMAT, (void*)(HC_KEY)key);
	    HC_Set_Driver_Options (option);
	    HC_Include_Segment ("?my_picture");
	HC_Close_Segment ();
	HC_Update_Display ();

	/* dump the data from HOOPS into a local array */
	HC_Show_Image (key, &x, &y, &z, format, &w, &h, data);
	HC_Delete_Segment ("?driver/image/snapshot");
	HC_Delete_Segment ("/null");
	HC_Update_Display ();

	/* insert the image back into HOOPS in its own window */
	HC_Open_Segment ("?draw/captured");
	    HC_Set_Window (-1.0, 1.0, 0.05, 0.95);
	    HC_Set_Window_Frame ("off");
	    HC_Insert_Image (0.0, 0.0, 0.0, format, w, h, data);
	HC_Close_Segment ();
	HC_Update_Display ();
	free (data);
    }
    HC_Show_Time (&stop_time);

    post_memory (7);
    post_results ("upper: screen image, lower: 3 red-green-blue images in a black window");
    post_time (7, start_time, stop_time);

	/*	we won't export an image of 'images' because test_images 
		allocates size based on the screen resolution.
		Therefore it's dangerous to export images with a static size
		(like 1400x1050) because we can end up freeing a larger 
		memory block than we allocated, which causes a HOOPS internal
		error.
    if (b_image_out) {
		sprintf (temp_file_name, "%s-images", image_file_root);
		export_image (temp_file_name);
    }
	*/
    if (b_hpgl_out || b_hpgl2_out) {
		sprintf (temp_file_name, "%s-images", image_file_root);
		export_hpgl (temp_file_name);
    }
	
}

void test_shells (void) {
    int	i;
    char		value[80], label[80];
    float		x,
			y,
			start_time,
			stop_time;

    identify_test ("?buttons/shells");
    HC_QSet_Driver_Options ("?my_picture", "no fixed colors");

    HC_Open_Segment ("?include library/shell");
        HC_QShow_One_Net_Rendering_Opti ("?my_picture", "hsr algorithm", value);
        if (strcmp (value, "painters") == 0 ||
	    strcmp (value, "hardware z buffer") == 0)
	    HC_Set_Rendering_Options ("face displacement = 1100");
	HC_Set_Color ("faces = red, edges = blue, markers = black");
	HC_Set_Marker_Symbol ("@");
	HC_Set_Marker_Size (0.25);
	insert_shell ();
    HC_Close_Segment ();

    HC_Open_Segment ("?include library/mesh");
        HC_QShow_One_Net_Rendering_Opti ("?my_picture", "hsr algorithm", value);
        if (strcmp (value, "painters") == 0 ||
	    strcmp (value, "hardware z buffer") == 0)
	    HC_Set_Rendering_Options ("face displacement = 1100");
	HC_Set_Color ("faces = red, edges = blue, markers = black");
	HC_Set_Marker_Symbol ("@");
	HC_Set_Marker_Size (0.25);
	insert_mesh ();
	HC_Rotate_Object (45.0, 0.0, 0.0);
	HC_Translate_Object (0.0, -0.2, 0.0);
    HC_Close_Segment ();
    HC_Update_Display ();

    HC_Show_Time (&start_time);
    HC_Open_Segment ("?draw/shells");
	HC_Set_Window (-1.0, -0.6, -1.0, 1.0);
	HC_Set_Camera_Projection ("perspective");
	HC_Set_Color ("text = black, faces = red, markers = green, edges = blue");
	HC_Set_Marker_Symbol (".");
	HC_Set_Text_Font ("size = 0.0075 sru");
	for (i = 0; i < 4; ++i) {
	    HC_Open_Segment ("");
		HC_Set_Window (-1.0, 1.0, 0.5 - 0.5 * i, 1.0 - 0.5 * i);
		HC_Set_Visibility (visibilities2[i]);
		HC_Insert_Text (0.0, -0.85, 0.0, visibilities2[i]);
		HC_Include_Segment ("?include library/shell");
	    HC_Close_Segment ();
	}
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/patterned shells");
	HC_Set_Window (-0.6, 0.6, 0.0, 1.0);
	HC_Set_Heuristics ("no hidden surfaces, concave polygons");
	HC_Set_Camera_Projection ("perspective");
	HC_Set_Marker_Symbol ("@");
	HC_Set_Marker_Size (0.25);
	HC_Insert_Text (0.0, 0.95, 0.0,
	    "Face Color, Face Pattern (black edges, markers on)");
	i = 0;
        for (x = 0.475f; x > -1.2f; x -= WIDTH + (GAP + 0.1f)) {
            for (y = -0.85f; y < 0.8f; y += HEIGHT + GAP) {
                HC_Open_Segment ("");
		    HC_Set_Window (x, x+WIDTH, y, y+HEIGHT);
		    HC_Set_Window_Frame ("off");
		    sprintf (label, "%s, %s",
			     color[i], pattern[i]);
                    HC_Set_Color (color[i]);
		    HC_Set_Color ("edges = black, text = black");
                    HC_Set_Face_Pattern (pattern[i++]);
		    insert_shell ();
                    HC_Insert_Text (0.0, -0.85, 0.0, label);
                HC_Close_Segment ();
            }
        }
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/lit patterned shells");
	HC_Set_Window (-0.6, 0.6, -1.0, 0.0);
	HC_Set_Heuristics ("no hidden surfaces, concave polygons");
	HC_Set_Rendering_Options ("no lighting interpolation");
	HC_Set_Camera_Projection ("perspective");
	HC_Set_Marker_Symbol ("@");
	HC_Set_Marker_Size (0.25);
	HC_Insert_Text (0.0, 0.95, 0.0,
	    "Flat Lit Face Color, Face Pattern (black edges, markers off)");
	HC_Set_Visibility ("markers = off");
	i = 0;
        for (x = 0.475f; x > -1.2f; x -= WIDTH + (GAP + 0.1f)) {
            for (y = -0.85f; y < 0.8f; y += HEIGHT + GAP) {
                HC_Open_Segment ("");
		    HC_Set_Window ((double)x,
				   (double)(x + WIDTH),
				   (double)y,
				   (double)(y + HEIGHT));
		    HC_Set_Window_Frame ("off");
		    if (colored ())
			HC_Insert_Distant_Light (-1.0, 1.0, 0.0);
		    sprintf (label, "%s, %s", color[i], pattern[i]);
                    HC_Set_Color (color[i]);
		    HC_Set_Color ("edges = black, text = black");
                    HC_Set_Face_Pattern (pattern[i++]);
		    insert_shell ();
                    HC_Insert_Text (0.0, -0.85, 0.0, label);
                HC_Close_Segment ();
            }
        }
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/meshes");
	HC_Set_Window (0.6, 1.0, -1.0, 1.0);
	HC_Set_Camera_Projection ("perspective");
	HC_Set_Color ("text = black, faces = red, markers = green, edges = blue");
	HC_Set_Marker_Symbol (".");
	HC_Set_Text_Font ("size = 0.0075 sru");
	for (i = 0; i < 4; ++i) {
	    HC_Open_Segment ("");
		HC_Set_Window (-1.0, 1.0,
			       0.5 - 0.5 * (double)i, 1.0 - 0.5 * (double)i);
		HC_Set_Visibility (visibilities3[i]);
		HC_Insert_Text (0.0, -0.85, 0.0, visibilities3[i]);
		HC_Include_Segment ("?include library/mesh");
	    HC_Close_Segment ();
	}
    HC_Close_Segment ();
    HC_Update_Display ();
    HC_Show_Time (&stop_time);

    post_memory (8);
    post_results ("shells (visibility, patterns, lit patterns) and mesh (visibility)");
    post_time (8, start_time, stop_time);

    if (b_hpgl_out || b_hpgl2_out) {
		sprintf (temp_file_name, "%s-shells", image_file_root);
		export_hpgl (temp_file_name);
    }

    if (b_image_out) {
		sprintf (temp_file_name, "%s-shells", image_file_root);
		export_image (temp_file_name);
    }
}

void test_NURBS_surfaces (void) {

    HC_KEY key;

    Vertex control_points[ 5 ][ 5 ] = {
	{{ 3.0f, 1.0f, 0.0f},  { 1.0f, 1.0f, 0.0f},  { 0.0f, 2.0f, 0.0f},  { -2.0f, 2.0f, 0.0f},  { -2.0f, 3.0f, 0.0f}},
	{{ 3.0f, 1.0f, 1.0f},  { 1.0f, 1.0f, 1.0f},  { 0.0f, 2.0f, 1.0f},  { -2.0f, 2.0f, 1.0f},  { -2.0f, 3.0f, 1.0f}},
	{{ 3.0f, -1.0f, 2.0f}, { 1.0f, -1.0f, 2.0f}, { 0.0f, 0.0f, 2.0f},  { -2.0f, 0.0f, 2.0f},  { -2.0f, 1.0f, 2.0f}},
	{{ 3.0f, -1.0f, 3.0f}, { 1.0f, -1.0f, 3.0f}, { 0.0f, 0.0f, 3.0f},  { -2.0f, 0.0f, 3.0f},  { -2.0f, 1.0f, 3.0f}},
	{{ 3.0f, 0.0f, 4.0f},  { 1.0f, 0.0f, 4.0f},  { 0.0f, -1.0f, 4.0f}, { -2.0f, -1.0f, 4.0f}, { -2.0f, 2.0f, 4.0f}}
    };

    float weights[ 25 ] = {
	1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f, 2.0f,
	1.0f, 1.0f, 1.0f, 2.0f, 3.0f,
	1.0f, 1.0f, 2.0f, 3.0f, 4.0f
    };


	float uniform_knots[] = {
		0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f};
/* TODO remove */
/*	float uniform_weights[] = {
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
*/
    float trimtri[8] = { 0.1f,0.1f, 0.9f,0.1f, 0.5f,0.5f, 0.5f,0.3f };
    float trimcurve[10] = { 0.0f,0.4f, 0.8f,0.4f, 0.5f,0.5f, 1.0f,1.0f, 0.0f,0.6f };
    float trimouter1[10] = { -1.0f,-2.0f, -0.5f,2.0f, 0.5f,-0.5f, 1.5f,2.0f, 2.0f,-2.0f };
    float trimouter2[10] = { -1.0f,3.0f, -0.5f,-1.0f, 0.5f,1.5f, 1.5f,-1.0f, 2.0f,3.0f };
    float tripod[3] = { 10.0f, 10.0f, 10.0f };
    float origin[3] = { 0.0f,0.0f,2.0f };
    float lpos[3] = { 0.0f,0.0f,10.0f };
    float up[3] = { 0.0f,1.0f,0.0f };
    float scenewidth = 8.0f;
    float sceneheight = 8.0f;


    identify_test ("?buttons/nurbs_surfaces");

	HC_Open_Segment("?draw/scene");
		HC_Set_Camera (tripod, origin, up, scenewidth, sceneheight, "Stretched");
		HC_Set_Rendering_Options ("lighting interpolation=(faces=gouraud)"); 
		HC_Set_Visibility ("faces, no edges, no markers");
		HC_Set_Color ("faces=green, edges=black");
		HC_Set_Text_Alignment ("v");
	HC_Close_Segment();
    
	HC_Open_Segment ("?draw/scene/ul");
        HC_Set_Window (-1.0, 0.0, 0.0, 1.0);
        HC_Insert_Local_Light (lpos[0], lpos[1], lpos[2]);
        HC_Open_Segment ("label");
            HC_Set_Camera_Projection ("stretched");
            HC_Insert_Text (0.0, -0.95, 0.0, "Basic surface and control mesh");
        HC_Close_Segment ();
        HC_Set_Visibility ("edges");

		HC_Insert_NURBS_Surface (2, 2,  5, 5,  control_points,  weights,  uniform_knots, uniform_knots);

		HC_Open_Segment ("control");
			HC_Set_Visibility ("no faces, edges=mesh quads only");
			HC_Set_Color ("edges=red");
			HC_Insert_Mesh (5, 5, control_points);
		HC_Close_Segment();
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/scene/ur");
        HC_Set_Window (0.0, 1.0, 0.0, 1.0);
        HC_Insert_Local_Light (lpos[0], lpos[1], lpos[2]);
        HC_Open_Segment ("label");
            HC_Set_Camera_Projection ("stretched");
            HC_Insert_Text (0.0, -0.95, 0.0, "Simple polygonal trim");
        HC_Close_Segment ();

		key = HC_KInsert_NURBS_Surface (2, 2,  5, 5,  control_points,  weights,  uniform_knots, uniform_knots);
		HC_Open_Geometry (key);
		HC_Trim_NURBS_Surface_By_Poly (4, trimtri);
		HC_Close_Geometry();

        HC_Open_Segment ("reference");
            HC_Set_Color ("transmission=light light gray");
            HC_Insert_NURBS_Surface (2, 2,  5, 5,  control_points,  weights,  uniform_knots, uniform_knots);
        HC_Close_Segment ();
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/scene/ll");
        HC_Set_Window (-1.0, 0.0, -1.0, 0.0);
        HC_Insert_Local_Light (lpos[0], lpos[1], lpos[2]);
        HC_Open_Segment ("label");
            HC_Set_Camera_Projection ("stretched");
            HC_Insert_Text (0.0, -0.95, 0.0, "Simple curve trim");
        HC_Close_Segment ();

		key = HC_KInsert_NURBS_Surface (2, 2,  5, 5,  control_points,  weights,  uniform_knots, uniform_knots);
		HC_Open_Geometry (key);
		HC_Trim_NURBS_Surface_By_Curve (2, 5, trimcurve, 0, 0, 0, 1);
		HC_Close_Geometry();

        HC_Include_Segment ("../ur/reference");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/scene/lr");
        HC_Set_Window (0.0, 1.0, -1.0, 0.0);
        HC_Insert_Distant_Light (lpos[0], lpos[1], lpos[2]);
        
		HC_Open_Segment ("label");
            HC_Set_Camera_Projection ("stretched");
            HC_Insert_Text (0.0, -0.95, 0.0, "Multiple outside trim curves");
        HC_Close_Segment ();
        HC_Set_Rendering_Options ("nurbs surface=trim budget=50");

		key = HC_KInsert_NURBS_Surface (2, 2,  5, 5,  control_points,  NULL, NULL, NULL );
		HC_Open_Geometry (key);
            /* Insert & delete some trims just to test */
		HC_Trim_NURBS_Surface_By_Poly (4, trimtri);
		HC_Trim_NURBS_Surface_By_Curve (2, 5, trimcurve, 0, 0, 0, 1);
        HC_Delete_Trim (0);
        HC_Delete_Trim (0);

		HC_Trim_NURBS_Surface_By_Curve (2, 5, trimouter1, 0, 0, 0, 1);
		HC_Trim_NURBS_Surface_By_Curve (2, 5, trimouter2, 0, 0, 0, 1);
		HC_Close_Geometry();

        HC_Include_Segment ("../ur/reference");
    HC_Close_Segment ();
    
    if (b_hpgl_out || b_hpgl2_out) {
		sprintf (temp_file_name, "%s-NURBS_surfaces", image_file_root);
		export_hpgl (temp_file_name);
    }

    if (b_image_out) {
		sprintf (temp_file_name, "%s-NURBS_surfaces", image_file_root);
		export_image (temp_file_name);
    }
}

void test_colors (void) {
    float		start_time,
			stop_time;
    char		buffer[64];
    long		number_of_colors;

    identify_test ("?buttons/colors");
    HC_QSet_Driver_Options ("?my_picture", "fixed colors = 0");
    HC_Update_Display ();

    HC_Show_Time (&start_time);
    HC_Open_Segment ("?draw/top");
	HC_Set_Heuristics ("no hidden surfaces");
	HC_QShow_One_Net_Driver_Option ("?my_picture", "number of colors", buffer);
	number_of_colors = atol (buffer);
	HC_Open_Segment ("colors");
	    switch (number_of_colors) {
		int	i, x, y;

		case 16: {
		    HC_Set_Camera_By_Volume ("orthographic",
					     0.0, 3.5, 0.0, 4.5);
		    HC_Set_Color ("edges = black");
		    i = 0;
		    for (y = 0; y < 3; y++)
			for (x = 0; x < 3; x++) {
			    HC_Open_Segment ("");
				sprintf (buffer, "faces = %s", color16[i]);
				HC_Set_Color (buffer);
				insert_circle ((float)x + 0.5f,
					       3.6f - (float)y,
					       0.25f);
				HC_Insert_Text ((double)x + 0.75,
						3.25 - (double)y,
						0.0,
						color16[i++]);
			    HC_Close_Segment ();
			}
		}   break;

		case 256:
		default: {
		    HC_Set_Camera_By_Volume ("orthographic",
					     0.0, 8.5, 0.0, 8.5);
		    HC_Set_Color ("edges = black");
		    i = 0;
		    for (y = 0; y < 8; y++)
			for (x = 0; x < 9; x++) {
			    HC_Open_Segment ("");
				sprintf (buffer, "faces = %s", color72[i]);
				HC_Set_Color (buffer);
				insert_circle ((float)x,
					       7.85f - (float)y,
					       0.25f);
				HC_Insert_Text ((double)x + 0.25,
						7.5 - (double)y,
						0.0,
						color72[i++]);
			    HC_Close_Segment ();
			}
		}
	    }
	HC_Close_Segment ();
    HC_Close_Segment ();
    HC_Open_Segment ("?draw/bottom");
	HC_Set_Heuristics ("no hidden surfaces, quick moves");
	HC_Include_Segment ("?draw/top/colors");
	HC_Set_Visibility ("text = off");
	HC_Translate_Object (0.5, 0.0, 0.0);
    HC_Close_Segment ();
    HC_Update_Display ();
    HC_Show_Time (&stop_time);

    post_memory (9);
    post_results ("color pairs: left = normal, right = quick moved");
    post_time (9, start_time, stop_time);

    if (b_hpgl_out || b_hpgl2_out) {
		sprintf (temp_file_name, "%s-colors", image_file_root);
		export_hpgl (temp_file_name);
    }

    if (b_image_out) {
		sprintf (temp_file_name, "%s-colors", image_file_root);
		export_image (temp_file_name);
    }
}

void test_clipping (void) {
    int	i;
    float		start_time,
			stop_time;
    Vertex		points[5];

    identify_test ("?buttons/clipping");
    HC_Update_Display ();

    HC_Show_Time (&start_time);
    HC_Open_Segment ("?draw/windows/on");
	HC_Set_Window (-1.0, 0.0, 0.0, 1.0);
	HC_Set_Window_Frame ("on");
	HC_Set_Heuristics ("no hidden surfaces");
	HC_Open_Segment ("nested");
	    for (i = 0; i < 30; ++i) {
		char    buf[64];

		HC_Open_Segment (" ");
		    sprintf (buf, "windows = %s", color[i % NUM_COLORS]);
		    HC_Set_Color (buf);
		    HC_Set_Window (-0.95, 0.95, -0.95, 0.95);
	    }
	    for (i = 0; i < 30; ++i)
		HC_Close_Segment ();
	HC_Close_Segment ();
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/geometry");
		HC_Set_Window (0.0, 1.0, 0.0, 1.0);
		HC_Set_Color ("lines = blue, markers = red");
		HC_Set_Heuristics ("no hidden surfaces");
		HC_Set_Marker_Symbol ("(.)");
		HC_Insert_Marker (-1.01, -1.01, 0.0);
		HC_Insert_Marker (-0.5,  -0.99, 0.0);
		HC_Insert_Marker (-1.01, -0.25, 0.0);
		HC_Insert_Marker (-1.01,  1.01, 0.0);
		HC_Insert_Marker (-0.5,   0.99, 0.0);
		HC_Insert_Marker (-0.99,  0.25, 0.0);
		HC_Insert_Marker ( 1.01,  1.01, 0.0);
		HC_Insert_Marker ( 0.5,   1.01, 0.0);
		HC_Insert_Marker ( 0.99,  0.25, 0.0);
		HC_Insert_Marker ( 1.01, -1.01, 0.0);
		HC_Insert_Marker ( 0.5,  -1.01, 0.0);
		HC_Insert_Marker ( 1.01, -0.25, 0.0);
		HC_Set_Text_Alignment ("*");
		HC_Insert_Text (-0.99, -0.75, 0.0, "A");
		HC_Insert_Text (-1.01,  0.75, 0.0, "A");
		HC_Insert_Text ( 0.99, -0.75, 0.0, "A");
		HC_Insert_Text ( 1.01,  0.75, 0.0, "A");
		HC_Open_Segment ("");
			HC_Set_Text_Alignment ("<");
			HC_Insert_Text (-1.1, 0.0, 0.0, "HOOPS World");
		HC_Close_Segment ();
		HC_Open_Segment ("");
			HC_Set_Text_Alignment (">");
			HC_Insert_Text (1.1, 0.0, 0.0, "HOOPS World");
		HC_Close_Segment ();
		HC_Open_Segment ("");
			HC_Set_Text_Alignment ("^");
			HC_Set_Text_Path (0.0, -1.0, 0.0);
			HC_Insert_Text (0.0, 1.1, 0.0, "HOOPS World");
		HC_Close_Segment ();
		HC_Open_Segment ("");
			HC_Set_Text_Alignment ("V");
			HC_Set_Text_Path (0.0, -1.0, 0.0);
			HC_Insert_Text (0.0, -1.1, 0.0, "HOOPS World");
		HC_Close_Segment ();
		points[0].x = -1.1f; points[0].y =  0.0f; points[0].z = 0.0f;
		points[1].x =  0.0f; points[1].y =  1.1f; points[1].z = 0.0f;
		points[2].x =  1.1f; points[2].y =  0.0f; points[2].z = 0.0f;
		points[3].x =  0.0f; points[3].y = -1.1f; points[3].z = 0.0f;
		points[4].x = -1.1f; points[4].y =  0.0f; points[4].z = 0.0f;
		HC_Insert_Polyline (5, points);
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/clipping");
		HC_Set_Heuristics ("no hidden surfaces, concave polygons");
		HC_Open_Segment ("");
			HC_Set_Color ("windows = green, faces = red, edges = blue");
			HC_Set_Window (-1.0, 0.0, -1.0, 0.0);
			HC_Set_Edge_Weight (4.0);
			insert_shape ();
			HC_Dolly_Camera (0.2, 0.0, 3.0);
		HC_Close_Segment ();

		HC_Open_Segment ("");
			HC_Set_Color ("window = blue, geometry = black");
			HC_Set_Window (0.0, 1.0, -1.0, 0.0);
			insert_doily ();
			HC_Dolly_Camera (0.0, 0.0, 3.5);
		HC_Close_Segment ();
    HC_Close_Segment ();
    HC_Update_Display ();
    HC_Show_Time (&stop_time);

    post_memory (10);
    post_results ("clipping (window, marker, text, polyline, line, polygon)");
    post_time (10, start_time, stop_time);

    if (b_hpgl_out || b_hpgl2_out) {
		sprintf (temp_file_name, "%s-clipping", image_file_root);
		export_hpgl (temp_file_name);
    }

    if (b_image_out) {
		sprintf (temp_file_name, "%s-clipping", image_file_root);
		export_image (temp_file_name);
    }
}

void test_convex_clipping (void) {

	float	p[100][3];
	float angle, c, s;
    int		i,j;
    HC_KEY	key;

	static	int		list[] = {3, 0, 1, 2};
/* TODO remove */
/*	static	float	red[3] = {1.00f, 0.00f, 0.00f};
	static	float	green[3] = {0.00f, 1.00f, 0.00f};
	static	float	pink[3]	= {1.00f, 0.80f, 0.80f};
*/
	static	float	vcolors[] = {1.0, 0.0, 0.0,
								0.0, 1.0, 0.0,
								0.0, 0.0, 1.0};

	unsigned char	image[100][100][3];


	identify_test ("?buttons/convex_clipping");

	HC_Open_Segment ("?draw/image");
		HC_Set_Window (-1.0, -0.33, 0.0, 1.0);
		HC_Insert_Text (0.0, -0.90, 0.0, "image");

		for (i=0; i<100; ++i) {
			for (j=0; j<100; ++j) {
			image[i][j][0] = (unsigned char)(i/25) * 85;
			image[i][j][1] = (unsigned char)(100+i-j) / 25 * 85;
			image[i][j][2] = (unsigned char)(j/25) * 85;
			}
		}

		HC_Open_Segment ("full");
			HC_Insert_Image (-0.6, 0.2, 0.0, "rgb", 100, 100, image);
			HC_Set_Callback ("draw segment tree = image segment");
		HC_Close_Segment ();

		/* add a faded version of the image for reference */
		for (i=0; i<100; ++i) {
			for (j=0; j<100; ++j) {
			image[i][j][0] = (image[i][j][0] + 3*255) >> 2;
			image[i][j][1] = (image[i][j][1] + 3*255) >> 2;
			image[i][j][2] = (image[i][j][2] + 3*255) >> 2;
			}
		}

		HC_Open_Segment ("faded");
			HC_Insert_Image (-0.6, 0.2, 0.0, "rgb", 100, 100, image);
		HC_Close_Segment ();

		HC_Set_Callback ("draw segment tree = segment");
	HC_Close_Segment ();


	HC_Open_Segment ("?draw/polyline");
		HC_Set_Window (-0.33, 0.33, 0.0, 1.0);

		for (i=0; i<360; i+=20) {
			angle = (float)DTR(i), c = (float)cos(angle), s = (float)sin(angle);
			HC_Insert_Line (-0.9*c, -0.9*s, 0.0, 0.9*c, 0.9*s, 0.0);
		}
		HC_Insert_Text (0.0, -0.90, 0.0, "dc polyline");

		HC_Set_Callback ("draw segment tree = segment");
		HC_Set_Callback ("draw dc polyline = polyline");
	HC_Close_Segment ();

	HC_Open_Segment ("?draw/edge");
		HC_Set_Window (0.33, 1.0, 0.0, 1.0);
		HC_Set_Visibility ("faces = off");
		HC_Set_Color ("edge = red");

		for (i=0; i<4; i++) {
			angle = (float)DTR(i*90+20), c = (float)cos(angle), s = (float)sin(angle);

			p[i][0] = (float)(-0.2 + 0.8*c);
			p[i][1] = (float)(-0.5 + 0.3*s);
			p[i][2] =  0.0f;
		}

		HC_Insert_Polygon (4, p);
		HC_Insert_Text (0.0, -0.90, 0.0, "dc edge");

		HC_Set_Callback ("draw segment tree = segment");
		HC_Set_Callback ("draw dc edge = edge");

	HC_Close_Segment ();

	HC_Open_Segment ("?draw/face");
		HC_Set_Window (-1.0, -0.33, -1.0, 0.0);
		HC_Set_Visibility ("edges = off");
		HC_Set_Color ("face = blue");

		for (i=0; i<4; i++) {
			angle = (float)DTR(i*90+20), c = (float)cos(angle), s = (float)sin(angle);

			p[i][0] = (float)(-0.2 + 0.8*c);
			p[i][1] = (float)(-0.5 + 0.3*s);
			p[i][2] =  0.0f;
		}

		HC_Insert_Polygon (4, p);
		HC_Insert_Text (0.0, -0.90, 0.0, "dc face");

		HC_Set_Callback ("draw segment tree = segment");
		HC_Set_Callback ("draw dc face = face");
	HC_Close_Segment ();

	HC_Open_Segment ("?draw/gouraud_triangle");
		HC_Set_Window (-0.33, 0.33, -1.0, 0.0);
		HC_Set_Visibility ("markers = off, edges = off");

		for (i=0; i<3; i++) {
			angle = (float)DTR(i*120+20), c = (float)cos(angle), s = (float)sin(angle);

			p[i][0] =  (float)(0.1 + 0.4*c);
			p[i][1] =  (float)(0.6 + 0.4*s);
			p[i][2] =  0.1f;
		}
		key = HC_KInsert_Shell (3, p, 4, list);
		HC_MSet_Vertex_Colors_By_Value (key, "face", 0, "rgb", 3, vcolors);
		HC_Insert_Text (0.0, -0.90, 0.0, "dc gouraud triangle");

		HC_Set_Callback ("draw segment tree = segment");
		HC_Set_Callback ("draw dc gouraud triangle = gouraud triangle");
	HC_Close_Segment ();

	HC_Open_Segment ("?draw/text");
		HC_Set_Window (0.33, 1.0, -1.0, 0.0);

		HC_Open_Segment ("");
			HC_Set_Text_Font ("name=roman");
			HC_Insert_Text (0.5, 0.20, 0.0, "Simple text string");
		HC_Close_Segment();
		HC_Open_Segment ("");
		  HC_Set_Text_Font ("name=times.ttf");
		  HC_Insert_Text (0.5, 0.07, 0.0, "A different font");
		HC_Close_Segment ();
		HC_Open_Segment ("");
		  HC_Set_Text_Font ("name=stroked");
		  HC_Insert_Text (0.5, -0.06, 0.0, "Stroked text");
		HC_Close_Segment ();
		HC_Insert_Text (0.0, -0.90, 0.0, "text");

		HC_Set_Callback ("draw segment tree = segment");
		HC_Set_Callback ("draw text = text");
	HC_Close_Segment ();

	HC_Update_Display();
    
    if (b_hpgl_out || b_hpgl2_out) {
		sprintf (temp_file_name, "%s-convex_clipping", image_file_root);
		export_hpgl (temp_file_name);
    }

    if (b_image_out) {
		sprintf (temp_file_name, "%s-convex_clipping", image_file_root);
		export_image (temp_file_name);
    }

}

void test_projections (void) {
    float	start_time,
		stop_time;

    identify_test ("?buttons/projections");

    HC_Open_Segment ("?include library/crosshair");
	HC_Set_Color ("line = blue");
	HC_Insert_Line ( 1.0,  1.0, 0.0,   1.0, -1.0, 0.0);
	HC_Insert_Line ( 1.0, -1.0, 0.0,  -1.0, -1.0, 0.0);
	HC_Insert_Line (-1.0, -1.0, 0.0,  -1.0,  1.0, 0.0);
	HC_Insert_Line (-1.0,  1.0, 0.0,   1.0,  1.0, 0.0);

	HC_Insert_Line ( 1.0, 0.0, 0.0,    0.0,  0.0, 0.0);
	HC_Insert_Line ( 1.0, 0.0, 0.0,    0.8,  0.2, 0.0);
	HC_Insert_Line ( 1.0, 0.0, 0.0,    0.8, -0.2, 0.0);

	HC_Insert_Line (-1.0, 0.0, 0.0,    0.0,  0.0, 0.0);
	HC_Insert_Line (-1.0, 0.0, 0.0,   -0.8,  0.2, 0.0);
	HC_Insert_Line (-1.0, 0.0, 0.0,   -0.8, -0.2, 0.0);

	HC_Insert_Line ( 0.0, 1.0, 0.0,    0.0,  0.0, 0.0);
	HC_Insert_Line ( 0.0, 1.0, 0.0,    0.2,  0.8, 0.0);
	HC_Insert_Line ( 0.0, 1.0, 0.0,   -0.2,  0.8, 0.0);

	HC_Insert_Line ( 0.0, -1.0, 0.0,   0.0,  0.0, 0.0);
	HC_Insert_Line ( 0.0, -1.0, 0.0,   0.2, -0.8, 0.0);
	HC_Insert_Line ( 0.0, -1.0, 0.0,  -0.2, -0.8, 0.0);

	HC_Insert_Line ( 1.0, -1.0, 0.0,   0.0,  0.0, 0.0);
	HC_Insert_Line ( 1.0, -1.0, 0.0,   0.9, -0.8, 0.0);
	HC_Insert_Line ( 1.0, -1.0, 0.0,   0.8, -0.9, 0.0);

	HC_Insert_Line (-1.0, -1.0, 0.0,   0.0,  0.0, 0.0);
	HC_Insert_Line (-1.0, -1.0, 0.0,  -0.9, -0.8, 0.0);
	HC_Insert_Line (-1.0, -1.0, 0.0,  -0.8, -0.9, 0.0);

	HC_Insert_Line ( 1.0, 1.0, 0.0,    0.0,  0.0, 0.0);
	HC_Insert_Line ( 1.0, 1.0, 0.0,    0.9,  0.8, 0.0);
	HC_Insert_Line ( 1.0, 1.0, 0.0,    0.8,  0.9, 0.0);

	HC_Insert_Line (-1.0, 1.0, 0.0,    0.0,  0.0, 0.0);
	HC_Insert_Line (-1.0, 1.0, 0.0,   -0.9,  0.8, 0.0);
	HC_Insert_Line (-1.0, 1.0, 0.0,   -0.8,  0.9, 0.0);
    HC_Close_Segment ();

    HC_Open_Segment ("?include library/ink");
	HC_Set_Color ("line = green");
	HC_Insert_Ink (-0.65, -0.65, 0.65);
	HC_Insert_Ink (-0.65,  0.65, 0.65);
	HC_Insert_Ink ( 0.65,  0.65, 0.65);
	HC_Insert_Ink ( 0.65, -0.65, 0.65);
	HC_Insert_Ink (-0.65, -0.65, 0.65);

	HC_Restart_Ink ();
	HC_Insert_Ink (-0.65, -0.65, -0.65);
	HC_Insert_Ink (-0.65,  0.65, -0.65);
	HC_Insert_Ink ( 0.65,  0.65, -0.65);
	HC_Insert_Ink ( 0.65, -0.65, -0.65);
	HC_Insert_Ink (-0.65, -0.65, -0.65);

	HC_Insert_Line (-0.65, -0.65, 0.65, -0.65, -0.65, -0.65);
	HC_Insert_Line (-0.65,  0.65, 0.65, -0.65,  0.65, -0.65);
	HC_Insert_Line ( 0.65,  0.65, 0.65,  0.65,  0.65, -0.65);
	HC_Insert_Line ( 0.65, -0.65, 0.65,  0.65, -0.65, -0.65);
    HC_Close_Segment ();
    HC_Update_Display ();

    HC_Show_Time (&start_time);
    HC_QSet_Window_Frame ("?draw", "off");
    HC_Open_Segment ("?draw/camera");
	HC_Set_Text_Font ("size = 0.0125 sru");
	HC_Set_Window_Frame ("on");
	HC_Set_Heuristics ("no hidden surfaces");

        HC_Open_Segment ("");
	    HC_Set_Window (-1.0, -0.5, -1.0, 0.0);
	    HC_Set_Camera_Projection ("orthographic");
	    HC_Include_Segment ("?include library/crosshair");
	    HC_Include_Segment ("?include library/ink");
            HC_Insert_Text (0.0, 0.0, 0.0, "Orthographic");
        HC_Close_Segment ();

        HC_Open_Segment ("");
	    HC_Set_Window (-0.5, 0.0, -1.0, 0.0);
	    HC_Set_Camera_Projection ("oblique orthographic = (20.0, 10.0)");
	    HC_Include_Segment ("?include library/crosshair");
	    HC_Include_Segment ("?include library/ink");
            HC_Insert_Text (0.0, 0.0, 0.0,
			    "Oblique Orthographic (20.0, 10.0)");
        HC_Close_Segment ();

        HC_Open_Segment ("");
	    HC_Set_Window (-1.0, -0.5, 0.0, 1.0);
	    HC_Set_Camera_Projection ("perspective");
	    HC_Include_Segment ("?include library/crosshair");
	    HC_Include_Segment ("?include library/ink");
            HC_Insert_Text (0.0, 0.0, 0.0, "Perspective");
        HC_Close_Segment ();

        HC_Open_Segment ("");
	    HC_Set_Window (-0.5, 0.0, 0.0, 1.0);
	    HC_Set_Camera_Projection ("oblique perspective = (20.0, 10.0)");
	    HC_Include_Segment ("?include library/crosshair");
	    HC_Include_Segment ("?include library/ink");
            HC_Insert_Text (0.0, 0.0, 0.0,
			    "Oblique Perspective (20.0, 10.0)");
        HC_Close_Segment ();

        HC_Open_Segment ("");
	    HC_Set_Window (0.0, 0.5, 0.0, 1.0);
	    HC_Set_Camera_Projection ("stretched");
	    HC_Include_Segment ("?include library/crosshair");
	    HC_Include_Segment ("?include library/ink");
            HC_Insert_Text (0.0, 0.0, 0.0, "Stretched");
        HC_Close_Segment ();

        HC_Open_Segment ("");
	    HC_Set_Window (0.5, 1.0, 0.0, 1.0);
	    HC_Set_Camera_Projection ("oblique stretched = (20.0, 10.0)");
	    HC_Include_Segment ("?include library/crosshair");
	    HC_Include_Segment ("?include library/ink");
            HC_Insert_Text (0.0, 0.0, 0.0,
			    "Oblique Stretched (20.0, 10.0)");
        HC_Close_Segment ();

        HC_Open_Segment ("");
	    HC_Set_Window (0.0, 1.0, -1.0, 0.0);
	    HC_Set_Window_Frame ("off");
	    HC_Set_Camera_Projection ("stretched");
	    HC_Include_Segment ("?include library/crosshair");
	    HC_Include_Segment ("?include library/ink");
            HC_Insert_Text (0.0, 0.0, 0.0, "Stretched");
            HC_Insert_Text (0.0, -0.2, 0.0, "window frame = off");
        HC_Close_Segment ();
    HC_Close_Segment ();
    HC_Update_Display ();
    HC_Show_Time (&stop_time);

    post_memory (11);
    post_results ("various projections (blue 2D and green 3D geometry)");
    post_time (11, start_time, stop_time);

    if (b_hpgl_out || b_hpgl2_out) {
		sprintf (temp_file_name, "%s-projections", image_file_root);
		export_hpgl (temp_file_name);
    }

    if (b_image_out) {
		sprintf (temp_file_name, "%s-projections", image_file_root);
		export_image (temp_file_name);
    }
}

void construct_hsr_suite (
    char	*include_segment) {

    HC_Open_Segment ("wireframe");
	HC_Set_Window (-1.0, -0.33, 0.0, 0.9);
	HC_Set_Heuristics ("no hidden surfaces");
	HC_Set_Visibility ("faces = off, edges = on");
	HC_Set_Rendering_Options ("lighting interpolation = off");
	HC_Include_Segment (include_segment);
	HC_Insert_Text (0.0, 0.95, 0.0, "wireframe");
    HC_Close_Segment ();

    HC_Open_Segment ("hardware z buffer");
	HC_Set_Window (-0.33, 0.33, 0.0, 0.9);
	HC_Include_Segment (include_segment);
	HC_Insert_Text (0.0, 0.95, 0.0, "HW z buffer");
    HC_Close_Segment ();

    HC_Open_Segment ("painters");
	HC_Set_Window (0.33, 1.0, 0.0, 0.9);
	HC_Set_Rendering_Options ("hsr algorithm = painters");
	HC_Include_Segment (include_segment);
	HC_Insert_Text (0.0, 0.95, 0.0, "painters");
    HC_Close_Segment ();

    HC_Open_Segment ("priority");
	HC_Set_Window (-1.0, -0.33, -0.9, 0.0);
	HC_Set_Rendering_Options ("hsr algorithm = priority");
	HC_Include_Segment (include_segment);
	HC_Insert_Text (0.0, 0.95, 0.0, "priority");
    HC_Close_Segment ();

    HC_Open_Segment ("Z sort only");
	HC_Set_Window (-0.33, 0.33, -0.9, 0.0);
	HC_Set_Rendering_Options ("hsr algorithm = Z-sort only");
	HC_Include_Segment (include_segment);
	HC_Insert_Text (0.0, 0.95, 0.0, "Z sort");
    HC_Close_Segment ();

    HC_Open_Segment ("software z buffer");
	HC_Set_Window (0.33, 1.0, -0.9, 0.0);
	HC_Set_Rendering_Options ("hsr algorithm = software z-buffer");
	HC_Set_Rendering_Options ("face displacement = 32");
	HC_Include_Segment (include_segment);
	HC_Insert_Text (0.0, 0.95, 0.0, "SW z buffer");
    HC_Close_Segment ();
}

void test_handedness (void) {
    float	start_time,
		stop_time;
    Vertex	vertex[4];

    identify_test ("?buttons/handedness");

    HC_Open_Segment ("?include library/clockwise");
	vertex[0].x = -0.4f;
	vertex[0].y = -0.8f;
	vertex[0].z =  0.0f;
	vertex[1].x = -0.4f;
	vertex[1].y = -0.3f;
	vertex[1].z =  0.0f;
	vertex[2].x =  0.4f;
	vertex[2].y = -0.3f;
	vertex[2].z =  0.0f;
	vertex[3].x =  0.4f;
	vertex[3].y = -0.8f;
	vertex[3].z =  0.0f;
	HC_Insert_Polygon (4, vertex);
	HC_Insert_Text (0.0, -0.95, 0.0, "clockwise");
    HC_Close_Segment ();

    HC_Open_Segment ("?include library/clockwise labels");
	HC_Set_Text_Font ("size = 0.0075 sru");
	HC_Insert_Text (-0.5, -0.8, 0.0, "0");
	HC_Insert_Text (-0.5, -0.3, 0.0, "1");
	HC_Insert_Text ( 0.5, -0.3, 0.0, "2");
	HC_Insert_Text ( 0.5, -0.8, 0.0, "3");
    HC_Close_Segment ();

    HC_Open_Segment ("?include library/counter clockwise");
	vertex[0].x =  0.4f;
	vertex[0].y =  0.3f;
	vertex[0].z =  0.0f;
	vertex[1].x =  0.4f;
	vertex[1].y =  0.8f;
	vertex[1].z =  0.0f;
	vertex[2].x = -0.4f;
	vertex[2].y =  0.8f;
	vertex[2].z =  0.0f;
	vertex[3].x = -0.4f;
	vertex[3].y =  0.3f;
	vertex[3].z =  0.0f;
	HC_Insert_Polygon (4, vertex);
	HC_Insert_Text (0.0, 0.95, 0.0, "counter");
    HC_Close_Segment ();

    HC_Open_Segment ("?include library/counter clockwise labels");
	HC_Set_Text_Font ("size = 0.0075 sru");
	HC_Insert_Text ( 0.5, 0.3, 0.0, "0");
	HC_Insert_Text ( 0.5, 0.8, 0.0, "1");
	HC_Insert_Text (-0.5, 0.8, 0.0, "2");
	HC_Insert_Text (-0.5, 0.3, 0.0, "3");
    HC_Close_Segment ();

    HC_Open_Segment ("?include library/cube1");
	insert_cw_flt_cube_sides ();
	insert_cube_center_marker ();
	insert_ccw_brb_cube_sides ();
	HC_Rotate_Object (20.0, 20.0, 0.0);
    HC_Close_Segment ();

    HC_Open_Segment ("?include library/cube2");
	insert_ccw_flt_cube_sides ();
	insert_cube_center_marker ();
	insert_cw_brb_cube_sides ();
	HC_Rotate_Object (20.0, 20.0, 0.0);
    HC_Close_Segment ();

    HC_Open_Segment ("?include library/hsr algorithms1");
	HC_Set_Window_Frame ("off");
	HC_Set_Color ("text = black");
	construct_hsr_suite ("?include library/cube1");
    HC_Close_Segment ();

    HC_Open_Segment ("?include library/hsr algorithms2");
	HC_Set_Window_Frame ("off");
	HC_Set_Color ("text = black");
	construct_hsr_suite ("?include library/cube2");
    HC_Close_Segment ();
    HC_Update_Display ();

    HC_Show_Time (&start_time);
    HC_Open_Segment ("?draw/top one");
	HC_Set_Color ("text = black, faces = green, edges = blue, windows = white");
	HC_Set_Handedness ("left");
	HC_Set_Window (-1.0, -0.5, 0.0, 1.0);
	HC_Open_Segment ("");
	    HC_Set_Color ("text = red");
	    HC_Insert_Text (0.0, 0.95, 0.0, "general handedness = left");
	HC_Close_Segment ();
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/top one/1");
	HC_Set_Window (-1.0, -0.33, -0.95, 0.85);
	HC_Set_Window_Frame ("off");
	HC_Set_Heuristics ("no polygon handedness");
	HC_Open_Segment ("");
	    HC_Include_Segment ("?include library/clockwise");
	    HC_Include_Segment ("?include library/clockwise labels");
	HC_Close_Segment ();
	HC_Open_Segment ("");
	    HC_Include_Segment ("?include library/counter clockwise");
	    HC_Include_Segment ("?include library/counter clockwise labels");
	HC_Close_Segment ();
	HC_Insert_Text (0.0, 0.1, 0.0, "none");
	HC_Open_Segment ("");
	    HC_Set_Color ("text = red");
	    HC_Insert_Text (0.0, -0.1, 0.0, "(both?)");
	HC_Close_Segment ();
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/top one/2");
	HC_Set_Window (-0.33, 0.33, -0.95, 0.85);
	HC_Set_Window_Frame ("off");
	HC_Set_Heuristics ("polygon handedness = right");
	HC_Open_Segment ("");
	    HC_Set_Color ("faces = red, edges = red");
	    HC_Include_Segment ("?include library/clockwise");
	HC_Close_Segment ();
	HC_Open_Segment ("");
	    HC_Include_Segment ("?include library/counter clockwise");
	    HC_Include_Segment ("?include library/counter clockwise labels");
	HC_Close_Segment ();
	HC_Insert_Text (0.0, 0.1, 0.0, "right");
	HC_Open_Segment ("");
	    HC_Set_Color ("text = red");
	    HC_Insert_Text (0.0, -0.1, 0.0, "(upper?)");
	HC_Close_Segment ();
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/top one/3");
	HC_Set_Window (0.33, 1.0, -0.95, 0.85);
	HC_Set_Window_Frame ("off");
	HC_Set_Heuristics ("polygon handedness = left");
	HC_Open_Segment ("");
	    HC_Include_Segment ("?include library/clockwise");
	    HC_Include_Segment ("?include library/clockwise labels");
	HC_Close_Segment ();
	HC_Open_Segment ("");
	    HC_Set_Color ("faces = red, edges = red");
	    HC_Include_Segment ("?include library/counter clockwise");
	HC_Close_Segment ();
	HC_Insert_Text (0.0, 0.1, 0.0, "left");
	HC_Open_Segment ("");
	    HC_Set_Color ("text = red");
	    HC_Insert_Text (0.0, -0.1, 0.0, "(lower?)");
	HC_Close_Segment ();
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/bottom one");
	HC_Set_Color ("text = black, faces = green, edges = blue, windows = white");
	HC_Set_Handedness ("right");
	HC_Set_Window (-1.0, -0.5, -1.0, 0.0);
	HC_Open_Segment ("");
	    HC_Set_Color ("text = red");
	    HC_Insert_Text (0.0, 0.95, 0.0, "general handedness = right");
	HC_Close_Segment ();
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/bottom one/1");
	HC_Set_Window (-1.0, -0.33, -0.95, 0.85);
	HC_Set_Window_Frame ("off");
	HC_Set_Heuristics ("no polygon handedness");
	HC_Open_Segment ("");
	    HC_Include_Segment ("?include library/clockwise");
	    HC_Include_Segment ("?include library/clockwise labels");
	HC_Close_Segment ();
	HC_Open_Segment ("");
	    HC_Include_Segment ("?include library/counter clockwise");
	    HC_Include_Segment ("?include library/counter clockwise labels");
	HC_Close_Segment ();
	HC_Insert_Text (0.0, 0.1, 0.0, "none");
	HC_Open_Segment ("");
	    HC_Set_Color ("text = red");
	    HC_Insert_Text (0.0, -0.1, 0.0, "(both?)");
	HC_Close_Segment ();
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/bottom one/2");
	HC_Set_Window (-0.33, 0.33, -0.95, 0.85);
	HC_Set_Window_Frame ("off");
	HC_Set_Heuristics ("polygon handedness = right");
	HC_Open_Segment ("");
	    HC_Set_Color ("faces = red, edges = red");
	    HC_Include_Segment ("?include library/clockwise");
	HC_Close_Segment ();
	HC_Open_Segment ("");
	    HC_Include_Segment ("?include library/counter clockwise");
	    HC_Include_Segment ("?include library/counter clockwise labels");
	HC_Close_Segment ();
	HC_Insert_Text (0.0, 0.1, 0.0, "right");
	HC_Open_Segment ("");
	    HC_Set_Color ("text = red");
	    HC_Insert_Text (0.0, -0.1, 0.0, "(upper?)");
	HC_Close_Segment ();
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/bottom one/3");
	HC_Set_Window (0.33, 1.0, -0.95, 0.85);
	HC_Set_Window_Frame ("off");
	HC_Set_Heuristics ("polygon handedness = left");
	HC_Open_Segment ("");
	    HC_Include_Segment ("?include library/clockwise");
	    HC_Include_Segment ("?include library/clockwise labels");
	HC_Close_Segment ();
	HC_Open_Segment ("");
	    HC_Set_Color ("faces = red, edges = red");
	    HC_Include_Segment ("?include library/counter clockwise");
	HC_Close_Segment ();
	HC_Insert_Text (0.0, 0.1, 0.0, "left");
	HC_Open_Segment ("");
	    HC_Set_Color ("text = red");
	    HC_Insert_Text (0.0, -0.1, 0.0, "(lower?)");
	HC_Close_Segment ();
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/top two");
	HC_Set_Handedness ("left");
	HC_Set_Heuristics ("no polygon handedness");
	HC_Set_Window (-0.5, 0.0, 0.0, 1.0);
	HC_Include_Segment ("?include library/hsr algorithms1");
	HC_Open_Segment ("");
	    HC_Set_Color ("text = red");
	    HC_Insert_Text (0.0,  0.95, 0.0, "general handedness = left");
	    HC_Insert_Text (0.0, -0.95, 0.0, "no polygon handedness");
	HC_Close_Segment ();
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/bottom two");
	HC_Set_Handedness ("right");
	HC_Set_Heuristics ("no polygon handedness");
	HC_Set_Window (-0.5, 0.0, -1.0, 0.0);
	HC_Include_Segment ("?include library/hsr algorithms1");
	HC_Open_Segment ("");
	    HC_Set_Color ("text = red");
	    HC_Insert_Text (0.0,  0.95, 0.0, "general handedness = right");
	    HC_Insert_Text (0.0, -0.95, 0.0, "no polygon handedness");
	HC_Close_Segment ();
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/top three");
	HC_Set_Handedness ("left");
	HC_Set_Heuristics ("polygon handedness = right");
	HC_Set_Window (0.0, 0.5, 0.0, 1.0);
	HC_Include_Segment ("?include library/hsr algorithms2");
	HC_Open_Segment ("");
	    HC_Set_Color ("text = red");
	    HC_Insert_Text (0.0,  0.95, 0.0, "general handedness = left");
	    HC_Insert_Text (0.0, -0.95, 0.0, "polygon handedness = right");
	HC_Close_Segment ();
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/bottom three");
	HC_Set_Handedness ("right");
	HC_Set_Heuristics ("polygon handedness = right");
	HC_Set_Window (0.0, 0.5, -1.0, 0.0);
	HC_Include_Segment ("?include library/hsr algorithms2");
	HC_Open_Segment ("");
	    HC_Set_Color ("text = red");
	    HC_Insert_Text (0.0,  0.95, 0.0, "general handedness = right");
	    HC_Insert_Text (0.0, -0.95, 0.0, "polygon handedness = right");
	HC_Close_Segment ();
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/top four");
	HC_Set_Handedness ("left");
	HC_Set_Heuristics ("polygon handedness = left");
	HC_Set_Window (0.5, 1.0, 0.0, 1.0);
	HC_Include_Segment ("?include library/hsr algorithms1");
	HC_Open_Segment ("");
	    HC_Set_Color ("text = red");
	    HC_Insert_Text (0.0,  0.95, 0.0, "general handedness = left");
	    HC_Insert_Text (0.0, -0.95, 0.0, "polygon handedness = left");
	HC_Close_Segment ();
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/bottom four");
	HC_Set_Handedness ("right");
	HC_Set_Heuristics ("polygon handedness = left");
	HC_Set_Window (0.5, 1.0, -1.0, 0.0);
	HC_Include_Segment ("?include library/hsr algorithms1");
	HC_Open_Segment ("");
	    HC_Set_Color ("text = red");
	    HC_Insert_Text (0.0,  0.95, 0.0, "general handedness = right");
	    HC_Insert_Text (0.0, -0.95, 0.0, "polygon handedness = left");
	HC_Close_Segment ();
    HC_Close_Segment ();

    HC_Update_Display ();
    HC_Show_Time (&stop_time);

    post_memory (12);
    post_results ("general and polygonal handedness (2D and 3D)");
    post_time (12, start_time, stop_time);

    if (b_hpgl_out || b_hpgl2_out) {
		sprintf (temp_file_name, "%s-handedness", image_file_root);
		export_hpgl (temp_file_name);
    }

    if (b_image_out) {
		sprintf (temp_file_name, "%s-handedness", image_file_root);
		export_image (temp_file_name);
    }
}

void test_lighting (void) {
    float	start_time,
		stop_time;
    Vertex	position,
		target;

    identify_test ("?buttons/lighting");
    HC_QSet_Driver_Options ("?my_picture", "no fixed colors");
    HC_Define_System_Options ("no warnings");

    HC_Open_Segment ("?include library/cube1");
	insert_cw_flt_cube_sides ();
	insert_cube_center_marker ();
	insert_ccw_brb_cube_sides ();
	if (colored ())
	    HC_Insert_Distant_Light (1.0, -1.0, -3.0);
	HC_Rotate_Object (20.0, 20.0, 0.0);
    HC_Close_Segment ();

    HC_Open_Segment ("?include library/cube2");
	insert_ccw_flt_cube_sides ();
	insert_cube_center_marker ();
	insert_cw_brb_cube_sides ();
	if (colored ())
	    HC_Insert_Distant_Light (1.0, -1.0, -3.0);
	HC_Rotate_Object (20.0, 20.0, 0.0);
    HC_Close_Segment ();

    HC_Open_Segment ("?include library/hsr algorithms1");
	HC_Set_Window_Frame ("off");
	HC_Set_Color ("text = black");
	construct_hsr_suite ("?include library/cube1");
    HC_Close_Segment ();

    HC_Open_Segment ("?include library/hsr algorithms2");
	HC_Set_Window_Frame ("off");
	HC_Set_Color ("text = black");
	construct_hsr_suite ("?include library/cube2");
    HC_Close_Segment ();
    HC_Update_Display ();

    HC_Show_Time (&start_time);
    HC_Open_Segment ("?draw/distant");
	HC_Set_Window (-1.0, -0.5, -1.0, -0.5);
	HC_Set_Camera_Projection ("perspective");
	HC_Set_Color ("text = black, faces = red, edges = blue, lights = cyan");
	if (colored ())
	    HC_Insert_Distant_Light (-1.0, -0.5, -1.5);
	HC_Set_Visibility ("faces = on, edges = on");
	HC_Set_Heuristics ("no hidden surfaces");
	insert_pyramid ();
	HC_Open_Segment ("text");
	    HC_Open_Segment ("");
		HC_Set_Text_Alignment ("v");
		HC_Insert_Text (0.0, -0.97, 0.0, "gray");
	    HC_Close_Segment ();
	    HC_Open_Segment ("");
		HC_Set_Text_Path (0.0, -1.0, 0.0);
		HC_Insert_Text (-0.9, 0.0, 0.0, "cyan");
	    HC_Close_Segment ();
	    HC_Open_Segment ("");
		HC_Set_Text_Alignment ("^");
		HC_Insert_Text (0.0, 0.97, 0.0, "red violet");
	    HC_Close_Segment ();
	    HC_Open_Segment ("");
		HC_Set_Text_Path (0.0, -1.0, 0.0);
		HC_Insert_Text (0.9, 0.0, 0.0, "maroon");
	    HC_Close_Segment ();
	HC_Close_Segment ();
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/spot");
	HC_Set_Window (-1.0, -0.5, -0.5, 0.0);
	HC_Set_Camera_Projection ("perspective");
	HC_Set_Color ("text = black, faces = red, edges = blue, lights = white");
	position.x = -1.0f; position.y = -0.5f; position.z = -1.5f;
	target.x = 0.0f; target.y = 0.0f; target.z = 0.0f;
	if (colored ())
	    HC_Insert_Spot_Light (&position, &target, "");
	HC_Set_Visibility ("faces = on, edges = on, markers = off");
	HC_Set_Heuristics ("no hidden surfaces");
	HC_Set_Rendering_Options ("lighting interpolation = phong");
	insert_shell ();
	HC_Set_Text_Path (0.0, -1.0, 0.0);
	HC_Insert_Text (0.9, 0.0, 0.0, "spot");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/local");
	HC_Set_Window (-1.0, -0.5, 0.0, 0.5);
	HC_Set_Camera_Projection ("perspective");
	HC_Set_Color ("text = black, faces = red, edges = blue, lights = white");
	if (colored ())
	    HC_Insert_Local_Light (-1.0, -0.5, -1.5);
	HC_Set_Visibility ("faces = on, edges = on, markers = off");
	HC_Set_Heuristics ("no hidden surfaces");
	insert_shell ();
	HC_Set_Text_Path (0.0, -1.0, 0.0);
	HC_Insert_Text (0.9, 0.0, 0.0, "local");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/transparency");
    {
	float	x;
	int	i;
	char	buffer[256];

	HC_Set_Window (-1.0, -0.5, 0.5, 1.0);
	i = 0;
	for (x = -1.0f; x <= 1.0f; x += 0.25f) {
	    HC_Open_Segment ("");
		sprintf (buffer, "faces = %s", color[i++]);
		HC_Set_Color (buffer);
		insert_circle (x, 0.0f, 0.125f);
	    HC_Close_Segment ();
	}
	HC_Open_Segment ("");
	    HC_Set_Visibility ("markers = off, edges = off");
	    HC_Set_Color ("faces = (transmission = gray, diffuse = green)");
	    HC_Translate_Object (0.0, 0.0, -1.0);
	    insert_shell ();
	HC_Close_Segment ();
	HC_Insert_Text (0.0, 0.9, 0.0, "transparency");
    }
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/top two");
	HC_Set_Handedness ("left");
	HC_Set_Heuristics ("no polygon handedness");
	HC_Set_Window (-0.5, 0.0, 0.0, 1.0);
	HC_Include_Segment ("?include library/hsr algorithms1");
	HC_Open_Segment ("");
	    HC_Set_Color ("text = red");
	    HC_Insert_Text (0.0,  0.95, 0.0, "general handedness = left");
	    HC_Insert_Text (0.0, -0.95, 0.0, "no polygon handedness");
	HC_Close_Segment ();
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/bottom two");
	HC_Set_Handedness ("right");
	HC_Set_Heuristics ("no polygon handedness");
	HC_Set_Window (-0.5, 0.0, -1.0, 0.0);
	HC_Include_Segment ("?include library/hsr algorithms1");
	HC_Open_Segment ("");
	    HC_Set_Color ("text = red");
	    HC_Insert_Text (0.0,  0.95, 0.0, "general handedness = right");
	    HC_Insert_Text (0.0, -0.95, 0.0, "no polygon handedness");
	HC_Close_Segment ();
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/top three");
	HC_Set_Handedness ("left");
	HC_Set_Heuristics ("polygon handedness = right");
	HC_Set_Window (0.0, 0.5, 0.0, 1.0);
	HC_Include_Segment ("?include library/hsr algorithms2");
	HC_Open_Segment ("");
	    HC_Set_Color ("text = red");
	    HC_Insert_Text (0.0,  0.95, 0.0, "general handedness = left");
	    HC_Insert_Text (0.0, -0.95, 0.0, "polygon handedness = right");
	HC_Close_Segment ();
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/bottom three");
	HC_Set_Handedness ("right");
	HC_Set_Heuristics ("polygon handedness = right");
	HC_Set_Window (0.0, 0.5, -1.0, 0.0);
	HC_Include_Segment ("?include library/hsr algorithms2");
	HC_Open_Segment ("");
	    HC_Set_Color ("text = red");
	    HC_Insert_Text (0.0,  0.95, 0.0, "general handedness = right");
	    HC_Insert_Text (0.0, -0.95, 0.0, "polygon handedness = right");
	HC_Close_Segment ();
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/top four");
	HC_Set_Handedness ("left");
	HC_Set_Heuristics ("polygon handedness = left");
	HC_Set_Window (0.5, 1.0, 0.0, 1.0);
	HC_Include_Segment ("?include library/hsr algorithms1");
	HC_Open_Segment ("");
	    HC_Set_Color ("text = red");
	    HC_Insert_Text (0.0,  0.95, 0.0, "general handedness = left");
	    HC_Insert_Text (0.0, -0.95, 0.0, "polygon handedness = left");
	HC_Close_Segment ();
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/bottom four");
	HC_Set_Handedness ("right");
	HC_Set_Heuristics ("polygon handedness = left");
	HC_Set_Window (0.5, 1.0, -1.0, 0.0);
	HC_Include_Segment ("?include library/hsr algorithms1");
	HC_Open_Segment ("");
	    HC_Set_Color ("text = red");
	    HC_Insert_Text (0.0,  0.95, 0.0, "general handedness = right");
	    HC_Insert_Text (0.0, -0.95, 0.0, "polygon handedness = left");
	HC_Close_Segment ();
    HC_Close_Segment ();
    HC_Update_Display ();
    HC_Show_Time (&stop_time);

    HC_Define_System_Options ("warnings");
    post_memory (13);
    post_results ("left 3: red pyramid, left top: green transp, right: cube with culling combos");
    post_time (13, start_time, stop_time);

    if (b_hpgl_out || b_hpgl2_out) {
		sprintf (temp_file_name, "%s-lighting", image_file_root);
		export_hpgl (temp_file_name);
    }

    if (b_image_out) {
		sprintf (temp_file_name, "%s-lighting", image_file_root);
		export_image (temp_file_name);
    }
}

void test_input (void) {
    char	string[80];
    float	start_time, stop_time;

    identify_test ("?buttons/input");
    post_results ("enter some text");
    HC_Update_Display ();

    HC_Open_Segment ("?draw/image");
	insert_mapped8_image ();
	HC_Translate_Object (0.0, -0.75, 0.0);
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/text input");
	HC_Set_Window (-0.6, 0.6, -0.2, 0.2);
	HC_Set_Heuristics ("no hidden surfaces");
	HC_Set_Color ("window = black, text = white, window contrast = blue");
        HC_Set_Text_Font ("size = 0.05 sru");
    HC_Close_Segment ();
    HC_Get_String ("?draw/text input", string);

    HC_Show_Time (&start_time);
    HC_Open_Segment ("?draw/text input");
        HC_Insert_Text (0.0, 0.0, 0.0, string);
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/sideways up");
	HC_Set_Window (-0.9, -0.7, -0.8, 0.8);
	HC_Set_Heuristics ("no hidden surfaces");
	HC_Set_Color ("window = red, text = white, window contrast = blue");
        HC_Set_Text_Font ("size = 0.03 sru, rotation = 90, slant = -20");
	HC_Set_Text_Path (0.0, 1.0, 0.0);
        HC_Insert_Text (0.0, 0.0, 0.0, string);
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/sideways down");
	HC_Set_Window (0.7, 0.9, -0.8, 0.8);
	HC_Set_Heuristics ("no hidden surfaces");
	HC_Set_Color ("window = image");
        HC_Set_Text_Font ("size = 0.03 sru, rotation = 270, slant = 20");
	HC_Set_Text_Path (0.0, -1.0, 0.0);
        HC_Insert_Text (0.0, 0.0, 0.0, string);
    HC_Close_Segment ();
    HC_Update_Display ();
    HC_Show_Time (&stop_time);

    post_memory (14);
    post_results ("entered text is rotated and slanted in side windows (right window has image background)");
    post_time (14, start_time, stop_time);
}

void test_metafiles (void) {
    identify_test ("?buttons/metafile");
    post_results ("write a metafile and read it back in");
    HC_Update_Display ();

    HC_Write_Metafile ("?my_picture", "stdtest.hmf", "follow cross-references");
    HC_Read_Metafile ("stdtest.hmf", "?draw/metafile", "");
    HC_QUnSet_Camera ("?draw/metafile");
    HC_QSet_Selectability ("?draw/metafile", "off");
    HC_QSet_Rendering_Options ("?draw/metafile",
			       "attribute lock = selectability");
    post_results ("image of the screen appears in the drawing area");

	/* this is always different because the information box displays version numbers
    if (b_image_out) {
		sprintf (temp_file_name, "%s-metafiles", image_file_root);
		export_image (temp_file_name);
    }
	*/
}

void toggle_subscreen (void) {
    char	value[64];

    identify_test ("?buttons/subscreen");
    HC_Update_Display ();

    HC_Open_Segment ("?draw/text output");
	HC_Set_Text_Font ("size = 0.2 oru");
	HC_Set_Heuristics ("no hidden surfaces");
	HC_Insert_Text (0.0, 0.5, 0.0, "subscreen");
	HC_Insert_Text (0.0, 0.0, 0.0, "is now");
	HC_QShow_User_Options ("?buttons/subscreen", value);
	if (strcmp (value, "action=reduce") == 0) {
	    HC_QSet_Driver_Options ("?my_picture",
				    "subscreen = (-0.5, 0.5, -0.5, 0.5)");
	    HC_QSet_User_Options ("?buttons/subscreen", "action=enlarge");
	    HC_QSet_Window_Pattern ("?buttons/subscreen", "solid");
	    HC_Insert_Text (0.0, -0.5, 0.0, "-0.5, 0.5, -0.5, 0.5");
	}
	else {
	    HC_QSet_Driver_Options ("?my_picture",
				    "subscreen = (-1.0, 1.0, -1.0, 1.0)");
	    HC_QSet_User_Options ("?buttons/subscreen", "action=reduce");
	    HC_QSet_Window_Pattern ("?buttons/subscreen", "//");
	    HC_Insert_Text (0.0, -0.5, 0.0, "-1.0, 1.0, -1.0, 1.0");
	}
    HC_Close_Segment ();

    post_results ("toggled subscreen");
}

void toggle_double_buffer (void) {
    char	value[64];

    identify_test ("?buttons/double buffer");
    HC_Update_Display ();

    HC_Show_Device_Info ("?my_picture", "double buffer", value);
    if (strcmp (value, "none") == 0) {
	HC_QSet_Window_Pattern ("?buttons/double buffer", "//");

	HC_Open_Segment ("?draw/text output");
	    HC_Set_Text_Font ("size = 0.2 oru");
	    HC_Set_Color ("text = red");
	    HC_Set_Heuristics ("no hidden surfaces");
	    HC_Insert_Text (0.0, 0.33, 0.0, "double-buffering");
	    HC_Insert_Text (0.0, 0.0, 0.0, "is not");
	    HC_Insert_Text (0.0, -0.33, 0.0, "available");
	HC_Close_Segment ();

	post_results ("did not toggle double buffering");
    }
    else {
	HC_QShow_One_Net_Driver_Option ("?my_picture", "double-buffering", value);
	if (strcmp (value, "on") == 0) {
	    HC_QSet_Driver_Options ("?my_picture", "no double-buffering");
	    HC_QSet_Window_Pattern ("?buttons/double buffer", "//");
	}
	else {
	    HC_QSet_Driver_Options ("?my_picture", "double-buffering");
	    HC_QSet_Window_Pattern ("?buttons/double buffer", "solid");
	}

	HC_Open_Segment ("?draw/text output");
	    HC_Set_Text_Font ("size = 0.2 oru");
	    HC_Set_Heuristics ("no hidden surfaces");
	    HC_Insert_Text (0.0, 0.33, 0.0, "double-buffering");
	    HC_Insert_Text (0.0, 0.0, 0.0, "is now");
	    HC_Open_Segment ("");
		HC_Set_Color ("text = red");
		if (strcmp (value, "on") == 0)
		    HC_Insert_Text (0.0, -0.33, 0.0, "OFF");
		else
		    HC_Insert_Text (0.0, -0.33, 0.0, "ON");
	    HC_Close_Segment ();
	HC_Close_Segment ();

	post_results ("toggled double buffering");
    }
}

void toggle_black_and_white (void) {
    char	value[64];

    identify_test ("?buttons/black and white");
    HC_Update_Display ();

    HC_QShow_One_Net_Driver_Option ("?my_picture", "force black-and-white", value);
    if (strcmp (value, "on") == 0) {
	HC_QSet_Driver_Options ("?my_picture", "no force black-and-white");
	HC_QSet_Window_Pattern ("?buttons/black and white", "//");
    }
    else {
	HC_QSet_Driver_Options ("?my_picture", "force black and white");
	HC_QSet_Window_Pattern ("?buttons/black and white", "solid");
    }

    HC_Open_Segment ("?draw/text output");
	HC_Set_Text_Font ("size = 0.2 oru");
	HC_Set_Heuristics ("no hidden surfaces");
	HC_Insert_Text (0.0, 0.6, 0.0, "force");
	HC_Insert_Text (0.0, 0.2, 0.0, "black-and-white");
	HC_Insert_Text (0.0, -0.2, 0.0, "is now");
	HC_Open_Segment ("");
	    HC_Set_Color ("text = red");
	    if (strcmp (value, "on") == 0)
		HC_Insert_Text (0.0, -0.6, 0.0, "OFF");
	    else
		HC_Insert_Text (0.0, -0.6, 0.0, "ON");
	HC_Close_Segment ();
    HC_Close_Segment ();

    post_results ("toggled force black-and-white");
}

void show_device_results (void) {
    int	i, s, cap;

    identify_test ("?buttons/graph");
    HC_Update_Display ();

    HC_Open_Segment ("?draw/graph");
	HC_Set_Window_Frame ("off");
	HC_Set_Heuristics ("hidden surfaces, concave polygons");
	HC_Set_Visibility ("faces = on, edges = on");
	HC_Set_Color ("text = black, faces = red, edges = blue");
	HC_Set_Rendering_Options ("hsr algorithm = priority");
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/graph/timing");
	HC_Set_Window (-1.0, 0.0, -1.0, 1.0);
	if (results_max < 0.5f)
	    i = 0;
	else
	    i = (int)(log10 (ceil (results_max)) - 0.5f);
	s = 1;
	while (i-- > 0)
	    s *= 10;
	cap = (int)(ceil (results_max) + s - 1) / s;
	cap *= s;
	if (cap == 0)
	    cap = 1;
	HC_Set_Camera_By_Volume ("stretched",
				 -0.5,
				 (double)NUM_RESULTS + 0.5,
				 (double)cap * -0.25,
				 (double)cap * 1.25);
	HC_Insert_Polygon ((NUM_RESULTS + 2), results);
	HC_Open_Segment ("title");
	    HC_Set_Text_Font ("size = 0.02 sru");
	    HC_Insert_Text ((double)(NUM_RESULTS / 2),
			    (double)cap * 1.125,
			    0.0,
			    "Timing Results by Test");
        if (results_max == 0.0f)
	    HC_Insert_Text ((float)(NUM_RESULTS / 2),
			    0.5,
			    0.0,
			    "Timing Statistics Are Unavailable");
	HC_Close_Segment ();
	HC_Open_Segment ("y axis");
	    HC_Set_Text_Path (0.0, 1.0, 0.0);
	    HC_Set_Text_Font ("size = 0.01 sru, rotation = 90");
	    HC_Insert_Text (0.0, 0.5 * cap, 0.0, "seconds");
	HC_Close_Segment ();
	HC_Open_Segment ("lines and y values");
	    HC_Set_Line_Pattern ("- -");
	    HC_Set_Text_Path (0.25, -1.0, 0.0);
	    HC_Set_Text_Font ("size = 0.01 sru");
	    HC_Set_Text_Alignment ("<^");
	    for (i = 1; i < (NUM_RESULTS + 1); i++) {
		HC_Insert_Line ((double)i, 0.0, 0.0,
				(double)i, (double)cap, 0.0);
		HC_Insert_Text ((double)i, -0.01, 0.0, labels[i - 1]);
	    }
	HC_Close_Segment ();
	HC_Open_Segment ("lines and x values");
	    HC_Set_Line_Pattern ("- -");
	    HC_Set_Text_Font ("size = 0.01 sru");
	    HC_Set_Text_Alignment (">");
	    for (i = 0; i <= cap; i += s) {
		char	string[64];

		HC_Insert_Line (1.0, (double)i, 0.0,
				(double)NUM_RESULTS, (double)i, 0.0);
		sprintf (string, "%d", i);
		HC_Insert_Text (0.85, (double)i, 0.0, string);
	    }
	HC_Close_Segment ();
    HC_Close_Segment ();

    HC_Open_Segment ("?draw/graph/memory");
	HC_Set_Window (0.0, 1.0, -1.0, 1.0);
	if (results2_max < 0.5f)
	    i = 0;
	else
	    i = (int)(log10 (ceil (results2_max)) - 0.5f);
	s = 1;
	while (i-- > 0)
	    s *= 10;
	cap = (int)(ceil (results2_max) + s - 1) / s;
	cap *= s;
	if (cap == 0)
	    cap = 1;
	HC_Set_Camera_By_Volume ("stretched",
				 -0.5,
				 (double)NUM_RESULTS + 0.5,
				 (double)cap * -0.25,
				 (double)cap * 1.25);
	HC_Insert_Polygon (NUM_RESULTS + 2, results2);
	HC_Open_Segment ("");
	    HC_Set_Color ("faces = green");
	    HC_Insert_Polygon (NUM_RESULTS + 2, results3);
	HC_Close_Segment ();
	HC_Open_Segment ("");
	    HC_Set_Text_Font ("size = 0.02 sru");
	    HC_Insert_Text ((double)(NUM_RESULTS / 2),
			    (double)cap * 1.125,
			    0.0,
			    "Memory Use by Test");
        if (results2_max == 0.0f)
	    HC_Insert_Text ((double)(NUM_RESULTS / 2),
			    0.5,
			    0.0,
			    "Memory Statistics Unavailable");
	HC_Close_Segment ();
	HC_Open_Segment ("");
	    HC_Set_Text_Path (0.0, 1.0, 0.0);
	    HC_Set_Text_Font ("size = 0.01 sru, rotation = 90");
	    HC_Insert_Text (0.0, 0.5 * cap, 0.0, "K");
	HC_Close_Segment ();
	HC_Open_Segment ("");
	    HC_Set_Line_Pattern ("- -");
	    HC_Set_Text_Path (0.25, -1.0, 0.0);
	    HC_Set_Text_Font ("size = 0.01 sru");
	    HC_Set_Text_Alignment ("<^");
	    for (i = 1; i < (NUM_RESULTS + 1); i++) {
		HC_Insert_Line ((double)i, 0.0, 0.0,
				(double)i, (double)cap, 0.0);
		HC_Insert_Text ((double)i, -0.01, 0.0, labels[i - 1]);
	    }
	HC_Close_Segment ();
	HC_Open_Segment ("");
	    HC_Set_Line_Pattern ("- -");
	    HC_Set_Text_Font ("size = 0.01 sru");
	    HC_Set_Text_Alignment (">");
	    for (i = 0; i <= cap; i += s) {
		char	string[64];

		HC_Insert_Line (1.0, (double)i, 0.0,
				(double)NUM_RESULTS, (double)i, 0.0);
		sprintf (string, "%d", i);
		HC_Insert_Text (0.85, (double)i, 0.0, string);
	    }
	HC_Close_Segment ();
    HC_Close_Segment ();

    post_results ("timing and memory (allocated=red, in-use=green) results");
}

int driver_has_a_keyboard_or_mouse (void) {
    char answer[256];

    HC_Show_Device_Info ("?my_picture", "keyboard", answer);
    if (strcmp (answer, "yes") == 0)
	return TRUE;
    else {
	HC_Show_Device_Info ("?my_picture", "locater", answer);
	if (strcmp (answer, "yes") == 0)
	    return TRUE;
	else
	    return FALSE;
    }
}

void run_tests_based_on_user_input (void) {
    int		test_number,
		previous_test_number;
    char	selection[256];
    int		keep_testing;
    char	event[256];

    HC_Enable_Button_Events ("?my_picture", "anything");
    HC_Enable_Selection_Events ("?my_picture", "?my_picture");

    test_number = NO_TEST;
    keep_testing = TRUE;
    show_execution_context ();
    while (keep_testing) {
	previous_test_number = test_number;

	HC_Await_Event (event);

	/*
	 * decide if the user hit enter (next test)
	 * or clicked on a specific test to run and
	 * set the test number (test to run) accordingly
	 */
	if (strcmp (event, "selection") == 0) {
	    HC_Show_Selection (selection);
	    if (strcmp (selection, "windows") == 0)
		test_number = WINDOWS;
	    else if (strcmp (selection, "polylines") == 0)
		test_number = POLYLINES;
	    else if (strcmp (selection, "nurbs_curves") == 0)
		test_number = NURBS_CURVES;
	    else if (strcmp (selection, "markers") == 0)
		test_number = MARKERS;
	    else if (strcmp (selection, "polygons") == 0)
		test_number = POLYGONS;
	    else if (strcmp (selection, "cylinders") == 0)
		test_number = CYLINDERS;
	    else if (strcmp (selection, "text") == 0)
		test_number = TEXT;
	    else if (strcmp (selection, "images") == 0)
		test_number = IMAGES;
	    else if (strcmp (selection, "shells") == 0)
		test_number = SHELLS;
	    else if (strcmp (selection, "nurbs_surfaces") == 0)
		test_number = NURBS_SURFACES;
	    else if (strcmp (selection, "colors") == 0)
		test_number = COLORS;
	    else if (strcmp (selection, "clipping") == 0)
		test_number = CLIPPING;
	    else if (strcmp (selection, "convex_clipping") == 0)
		test_number = CONVEX_CLIPPING;
	    else if (strcmp (selection, "projections") == 0)
		test_number = PROJECTIONS;
	    else if (strcmp (selection, "handedness") == 0)
		test_number = HANDEDNESS;
	    else if (strcmp (selection, "lighting") == 0)
		test_number = LIGHTING;
	    else if (strcmp (selection, "input") == 0)
		test_number = HINPUT;
	    else if (strcmp (selection, "quit") == 0)
		test_number = QUIT;
	    else if (strcmp (selection, "reset") == 0)
		test_number = RESET;
	    else if (strcmp (selection, "subscreen") == 0)
		test_number = SUBSCREEN;
	    else if (strcmp (selection, "double buffer") == 0)
		test_number = DOUBLE_BUFFER;
	    else if (strcmp (selection, "black and white") == 0)
		test_number = BLACK_WHITE;
	    else if (strcmp (selection, "graph") == 0)
		test_number = GRAPHS;
	    else if (strcmp (selection, "metafile") == 0)
		test_number = METAFILES;
	    else
		test_number++;
	}
	else if (strcmp (event, "button") == 0) {
	    HC_Show_Button (selection);
	    if (strcmp (selection, "q") == 0)
		test_number = QUIT;
	    else
		test_number++;
	}
        else if (strcmp (event, "none") == 0)
	    /* Driver was killed by system */
	    HC_Exit_Program ();
	else
	    /* unexpected special event */
	    test_number = QUIT;

	/*
	 * run the desired test regardless of how
	 * test number was set above
	 */
	switch (test_number) {
	    case WINDOWS: {
		test_windows ();
	    }   break;

	    case POLYLINES: {
		test_polylines ();
	    }   break;

	    case NURBS_CURVES: {
		test_NURBS_curves ();
	    }   break;

	    case MARKERS: {
		test_markers ();
	    }   break;

	    case POLYGONS: {
		test_polygons ();
	    }   break;

	    case CYLINDERS: {
		test_cylinders ();
	    }   break;

	    case TEXT: {
		test_text ();
	    }   break;

	    case IMAGES: {
		test_images ();
	    }   break;

	    case SHELLS: {
		test_shells ();
	    }   break;

	    case NURBS_SURFACES: {
		test_NURBS_surfaces ();
	    }   break;

	    case COLORS: {
		test_colors ();
	    }   break;

	    case CLIPPING: {
		test_clipping ();
	    }   break;

	    case CONVEX_CLIPPING: {
		test_convex_clipping ();
	    }   break;

	    case PROJECTIONS: {
		test_projections ();
	    }   break;

	    case HANDEDNESS: {
		test_handedness ();
	    }   break;

	    case LIGHTING: {
		test_lighting ();
	    }   break;

	    case HINPUT: {
		test_input ();
	    }   break;

	    case QUIT:
	    default: {
		keep_testing = FALSE;
	    }   break;

	    case RESET: {
		HC_Disable_Button_Events ("?my_picture", "anything");
		HC_Disable_Selection_Events ("?my_picture", "?my_picture");

		HC_Reset_System ();

		init ();
		test_number = NO_TEST;
		show_execution_context ();
		HC_Enable_Button_Events ("?my_picture", "anything");
		HC_Enable_Selection_Events ("?my_picture", "?my_picture");
	    }   break;

	    case SUBSCREEN: {
		test_number = previous_test_number - 1;
		toggle_subscreen ();
	    }   break;

	    case DOUBLE_BUFFER: {
		test_number = previous_test_number - 1;
		toggle_double_buffer ();
	    }   break;

	    case BLACK_WHITE: {
		test_number = previous_test_number - 1;
		toggle_black_and_white ();
	    }   break;

	    case GRAPHS: {
		test_number = previous_test_number - 1;
		show_device_results ();
	    }   break;

	    case METAFILES: {
		test_number = previous_test_number - 1;
		test_metafiles ();
	    }   break;
	}
    }
    HC_Disable_Button_Events ("?my_picture", "anything");
    HC_Disable_Selection_Events ("?my_picture", "?my_picture");
    HC_Exit_Program ();
}

void run_non_input_tests_once (void) {
    show_execution_context ();
    HC_Update_Display ();

    test_windows ();
    
    test_polylines ();
    
    test_markers ();
    
    test_polygons ();
    
    test_text ();
    
    test_images ();
    
    test_shells ();
    
    test_colors ();
    
    test_clipping ();
    
    test_projections ();
    
    test_handedness ();
    
    test_lighting ();
    
    test_NURBS_curves ();
    
    test_NURBS_surfaces ();
   
    test_convex_clipping ();

    test_cylinders ();
    
    /* test_input (); */
    /* HC_Update_Display (); */

    /* toggle_subscreen (); */
    /* HC_Update_Display (); */

    /* toggle_double_buffer (); */
    /* HC_Update_Display (); */

    /* toggle_black_and_white (); */
    /* HC_Update_Display (); */

    show_device_results ();
    HC_Update_Display ();

    test_metafiles ();

    HC_Exit_Program ();
}

int main (
    int		argc,
    char	**argv) {

    int		run_interactively;
    size_t	i;
    const char	*hostname;
	char    hostname_buffer[1024];

    run_interactively = TRUE;

#ifdef UNIX_SYSTEM
    gethostname(hostname_buffer,1024);
#else
    hostname = getenv("COMPUTERNAME");
	if(hostname)
		strcpy(hostname_buffer, hostname);
    else
		hostname_buffer[0] = '\0';
#endif    

	/* in case of host.techsoft3d.com */
    for(i=0;i<strlen(hostname_buffer);i++) {

		if(hostname_buffer[i] == '.') {
			hostname_buffer[i] = '\0';	
			break;
		}
		hostname_buffer[i] = (char)tolower (hostname_buffer[i]);
	}
	
	hostname=&hostname_buffer[0];

    /* driver type */
    if (argc >= 2) {
		if (!strcmp (argv[1], "ogl")) {
			driver_type = OGL;
			driver_name = "ogl";
		}
		else if (!strcmp (argv[1], "msw")) {
			driver_type = MSW;
			driver_name = "msw";
		}
		else if (!strcmp (argv[1], "x11")) {
			driver_type = X11;
			driver_name = "x11";
		}
		else if (!strcmp (argv[1], "default")) {
			driver_type = DEFAULT_DRIVER;
			driver_name = "default";
		}
    }

	/* automation */
    if (argc >= 3) {
		if (!strncmp (argv[2], "image", 3)){
			b_image_out = 1;
		}
		else if (!strcmp (argv[2], "hpgl2")){
			b_hpgl2_out = 1;
		}
		else if (!strcmp (argv[2], "hpgl")){
			b_hpgl_out = 1;
		}
		else {
			char	option_string[64];

			HC_Define_Alias ("?picture", "?driver/printf/stdtest.out");
			strcpy (option_string, "debug = ");
			strcat (option_string, argv[2]);
			HC_QSet_Driver_Options ("/", option_string);
		}
		run_interactively = FALSE;
    }

	/* image file format */
	if (argc >= 4 && (!strncmp (argv[3], "binary",3))) {
		image_file_format = RAW_BINARY;
	}

	/* image file name  */
	if (argc >= 5) {
    		/* argv[4] should be the platform type */
		sprintf (image_file_root, "%s-%s", hostname, argv[4]);
	}
	else {
		sprintf (image_file_root, "stdtest");
	}

	/* image source */
	if (argc >= 6 && (!strncmp (argv[5], "oglhardware",4))) {
		image_source = OGL_HW;
	}

    init();

	if (!driver_has_a_keyboard_or_mouse ())
		run_interactively = FALSE;

    if (run_interactively)
		run_tests_based_on_user_input ();
    else
		run_non_input_tests_once ();

    return 0;
}

