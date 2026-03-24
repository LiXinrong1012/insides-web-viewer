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
 * $Id: test.h,v 1.5 2006-08-07 20:38:49 stage Exp $
 */

#ifndef HOOPS_TEST_DEFINED
#   define HOOPS_TEST_DEFINED

#ifndef TRUE
#  define TRUE -1
#endif

#ifndef FALSE
#  define FALSE 0
#endif

#define WIDTH 0.5f
#define HEIGHT 0.5f
#define GAP 0.1f

#define RAW_BINARY 1
#define RAW_ASCII 0

#define OGL_HW 1
#define OGL_SW 2
#define HOOPS_SW 0

#define OGL 0
#define MSW 1
#define X11 2
#define DEFAULT_DRIVER 3

#define NUM_CHOICES 32
static char *choices[] = {
		    "driver type",
		    "colors",
		    "driver version",
		    "max colors",
		    "display",
		    "planes",
		    "display type",
		    "current colormap ID",
		    "exists",
		    "hardware lights",
		    "started",
		    "gouraud shading",
		    "alive",
		    "gouraud lighting",
		    "windowing system",
		    "phong lighting",
		    "current window ID",
		    "pixels",
		    "current window ID 2",
		    "max pixels",
		    "keyboard",
		    "pixel aspect ratio",
		    "locater",
		    "window aspect ratio",
		    "locater type",
		    "resolution",
		    "locater buttons",
		    "max size",
		    "hardware cutting planes",
		    "size",
		    "double buffer",
		    "Z buffer depth"};

#define NUM_VARIABLES 18
static char *variables[] = {
		    "HOOPS_APPLICATION",
		    "HOOPS_COLORS",
		    "HOOPS_DRIVER_DIRECTORY",
		    "HOOPS_DRIVER_OPTIONS",
		    "HOOPS_FONT_DIRECTORY",
		    "HOOPS_HARDCOPY",
		    "HOOPS_HARDCOPY_OPTIONS",
		    "HOOPS_HEURISTICS",
		    "HOOPS_KEYBOARD",
		    "HOOPS_LICENSE",
		    "HOOPS_LOCATER",
		    "HOOPS_METAFILE_DIRECTORY",
		    "HOOPS_PICTURE",
		    "HOOPS_PICTURE_OPTIONS",
		    "HOOPS_RENDERING_OPTIONS",
		    "HOOPS_SYSTEM_OPTIONS",
		    "HOOPS_TEXT_FONT",
		    "HOOPS_VISIBILITY"};

typedef struct {
    float	x, y, z;
} Vertex;

typedef struct {
    float	r, g, b;
} RGB;

typedef struct {
    float	u, v, w;
} Parameter;

typedef struct {
	unsigned char r, g, b;
} Pixel;

#define	Pi		(3.141592f)
#define	S_NUMBER	8
#define	S_ANGLE		(2.0f * Pi / (float)S_NUMBER)

#define RADIUS		0.8f
#define D_NUMBER	36
#define D_ANGLE		(2.0f * Pi / (float)D_NUMBER)

#endif /* HOOPS_TEST_DEFINED */
