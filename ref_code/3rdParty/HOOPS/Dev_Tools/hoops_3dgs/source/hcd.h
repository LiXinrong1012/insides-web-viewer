/*
 * Copyright (c) 1998 by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.	 Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: hcd.h,v 1.20 2010-08-26 16:01:44 jason Exp $
 */

#ifndef HCD_DEFINED
#define HCD_DEFINED

#include "hc.h"

#ifdef _MSC_VER
#	if defined (BUILDING_HCD_INTERNALS)
#		define HD_API __declspec(dllexport)
#	else
#		define HD_API __declspec(dllimport)
#	endif
#else
#		define HD_API
#endif


#ifndef HCD_POINT
#  define HCD_POINT void
#endif

/* start by defining the macros necessary to intercept some calls */ 
#define HC_Delete_By_Key(a0) HC_DDelete_By_Key(a0) 
#define HC_Delete_Segment(a0) HC_DDelete_Segment(a0)
#define HC_Flush_By_Key(a0) HC_DFlush_By_Key(a0)
#define HC_Flush_Contents(a0,a1) HC_DFlush_Contents(a0,a1)
#define HC_Flush_Geometry(a0) HC_DFlush_Contents(a0,"geometry");

/* this one is no longer necessary (the functionality moved into 
 * HC_Reset_System) but provided for backward compatibility */
#define HC_DReset_System()

 /*	 */

/* prototypes for the intercepted calls */
HC_EXTERNAL HD_API void HC_CDECL HC_DDelete_By_Key HC_PROTO ((HC_KEY));
HC_EXTERNAL HD_API void HC_CDECL HC_DDelete_Segment HC_PROTO ((const char *));
HC_EXTERNAL HD_API void HC_CDECL HC_DFlush_By_Key HC_PROTO ((HC_KEY));
HC_EXTERNAL HD_API void HC_CDECL HC_DFlush_Contents HC_PROTO ((
				const char *, const char *));

/* prototypes for the new calls */

/* Compute Routines */
HC_EXTERNAL HD_API void HC_CDECL HC_DCompute_Optimized_Shell HC_PROTO ((
				int, const HCD_POINT *, const float *, int, const int *, const char *, int *, HCD_POINT *, int *, int *, int *, int *));
#define HC_DCompute_Minimized_Shell(a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10) HC_DCompute_Optimized_Shell(a0,a1,NULL,a2,a3,a4,a5,a6,a7,a8,a9,a10)
HC_EXTERNAL HD_API HC_BOOLEAN HC_CDECL HC_DCompute_Coordinates HC_PROTO ((
				const char *, const char *, const HCD_POINT *, const char *, HCD_POINT *));
HC_EXTERNAL HD_API void HC_CDECL HC_DCompute_Transformed_Points HC_PROTO ((
				int, const HCD_POINT *, const double *, HCD_POINT *));


/* NURBS Curves */
HC_EXTERNAL HD_API HC_KEY HC_CDECL HC_DQKInsert_NURBS_Curve HC_PROTO ((
				const char *, int, int, const HCD_POINT *, 
				const double *, const double *, double, double));
HC_EXTERNAL HD_API void HC_CDECL HC_DEdit_NURBS_Curve HC_PROTO (( 
				HC_KEY, int, int, int, int, const HCD_POINT *, const double *, const double* ));
HC_EXTERNAL HD_API void HC_CDECL HC_DShow_NURBS_Curve HC_PROTO (( 
				HC_KEY, int *, int *, HCD_POINT *, double *, double *, double *, double *));
#define HC_DInsert_NURBS_Curve(a0,a1,a2,a3,a4,a5,a6) ((void) HC_DQKInsert_NURBS_Curve(".",a0,a1,a2,a3,a4,a5,a6))
#define HC_DQInsert_NURBS_Curve(a0,a1,a2,a3,a4,a5,a6,a7) ((void) HC_DQKInsert_NURBS_Curve(a0,a1,a2,a3,a4,a5,a6,a7))
#define HC_DKInsert_NURBS_Curve(a0,a1,a2,a3,a4,a5,a6) HC_DQKInsert_NURBS_Curve(".",a0,a1,a2,a3,a4,a5,a6)

/* NURBS Surfaces */
HC_EXTERNAL HD_API HC_KEY HC_CDECL HC_DQKInsert_NURBS_Surface HC_PROTO ((
				const char *, int, int, int, int, 
				const HCD_POINT *, const double *, const double *, const double *));
HC_EXTERNAL HD_API void HC_CDECL HC_DEdit_NURBS_Surface HC_PROTO (( 
				HC_KEY, int, int, int, int, int, int, int, int, const HCD_POINT *, const double *, const double*, const double* )); 
HC_EXTERNAL HD_API void HC_CDECL HC_DShow_NURBS_Surface HC_PROTO (( 
				HC_KEY, int *, int *, int *, int *, HCD_POINT *, double *, double *, double *));
#define HC_DInsert_NURBS_Surface(a0,a1,a2,a3,a4,a5,a6, a7) ((void) HC_DQKInsert_NURBS_Surface(".",a0,a1,a2,a3,a4,a5,a6,a7))
#define HC_DQInsert_NURBS_Surface(a0,a1,a2,a3,a4,a5,a6,a7, a8) ((void) HC_DQKInsert_NURBS_Surface(a0,a1,a2,a3,a4,a5,a6,a7,a8))
#define HC_DKInsert_NURBS_Surface(a0,a1,a2,a3,a4,a5,a6, a7) HC_DQKInsert_NURBS_Curve(".",a0,a1,a2,a3,a4,a5,a6,a7)
#define HC_DEdit_NURBS_Surface_Points(a0,a1,a2,a3) HC_DEdit_NURBS_Surface(a0,a1,0,0,0,a2,0,0,0,a3,NULL,NULL,NULL)
#define HC_DEdit_NURBS_Surface_Weights(a0,a1,a2,a3) HC_DEdit_NURBS_Surface(a0,0,a1,0,0,0,a2,0,0,NULL,a3,NULL,NULL)
#define HC_DEdit_NURBS_Surface_Knots(a0,a1,a2,a3,a4,a5,a6) HC_DEdit_NURBS_Surface(a0,0,0,a1,a2,0,0,a3,a4,NULL,NULL,a5,a6)

/* Shells */
HC_EXTERNAL HD_API HC_KEY HC_CDECL HC_DQKInsert_Shell HC_PROTO ((
				const char *, int, const HCD_POINT *, int, const int *));
HC_EXTERNAL HD_API void HC_CDECL HC_DEdit_Shell_Points HC_PROTO ((
				HC_KEY, int, int, int, const HCD_POINT *));
HC_EXTERNAL HD_API void HC_CDECL HC_DShow_Shell HC_PROTO ((
				HC_KEY, int *, HCD_POINT *, int *, int *));
#define HC_DInsert_Shell(a0,a1,a2,a3) ((void) HC_DQKInsert_Shell(".",a0,a1,a2,a3))
#define HC_DQInsert_Shell(a0,a1,a2,a3,a4) ((void) HC_DQKInsert_Shell(a0,a1,a2,a3,a4))
#define HC_DKInsert_Shell(a0,a1,a2,a3) HC_DQKInsert_Shell(".",a0,a1,a2,a3)

/* Grids */
HC_EXTERNAL HD_API HC_KEY HC_CDECL HC_DQKInsert_Grid HC_PROTO ((
				const char *, const char *, const HCD_POINT *, const HCD_POINT *, const HCD_POINT *, int, int));
HC_EXTERNAL HD_API void HC_CDECL HC_DShow_Grid HC_PROTO ((
				HC_KEY, char *, HCD_POINT *, HCD_POINT *, HCD_POINT *, int *, int *));
#define HC_DInsert_Grid(a0,a1,a2,a3,a4,a5) ((void) HC_DQKInsert_Grid(".",a0,a1,a2,a3,a4,a5))
#define HC_DQInsert_Grid(a0,a1,a2,a3,a4,a5,a6) ((void) HC_DQKInsert_Grid(a0,a1,a2,a3,a4,a5,a6))
#define HC_DKInsert_Grid(a0,a1,a2,a3,a4,a5) HC_DQKInsert_Grid(".",a0,a1,a2,a3,a4,a5)

/* Meshes */
HC_EXTERNAL HD_API HC_KEY HC_CDECL HC_DQKInsert_Mesh HC_PROTO ((
				const char *, int, int, const HCD_POINT *));
HC_EXTERNAL HD_API void HC_CDECL HC_DEdit_Mesh HC_PROTO ((
				HC_KEY, int, int, int, int, const HCD_POINT *));
HC_EXTERNAL HD_API void HC_CDECL HC_DShow_Mesh HC_PROTO ((
				HC_KEY, int *, int *, HCD_POINT *));
#define HC_DInsert_Mesh(a0,a1,a2) ((void) HC_DQKInsert_Mesh(".",a0,a1,a2))
#define HC_DQInsert_Mesh(a0,a1,a2,a3) ((void) HC_DQKInsert_Mesh(a0,a1,a2,a3))
#define HC_DKInsert_Mesh(a0,a1,a2) HC_DQKInsert_Mesh(".",a0,a1,a2)

/* Polylines */
HC_EXTERNAL HD_API HC_KEY HC_CDECL HC_DQKInsert_Polyline HC_PROTO ((
				const char *, int, const HCD_POINT *));
HC_EXTERNAL HD_API void HC_CDECL HC_DEdit_Polyline HC_PROTO ((
				HC_KEY, int, int, int, const HCD_POINT *));
HC_EXTERNAL HD_API void HC_CDECL HC_DShow_Polyline HC_PROTO ((
				HC_KEY, int *, HCD_POINT *));
#define HC_DInsert_Polyline(a0,a1) ((void) HC_DQKInsert_Polyline(".",a0,a1))
#define HC_DQInsert_Polyline(a0,a1,a2) ((void) HC_DQKInsert_Polyline(a0,a1,a2))
#define HC_DKInsert_Polyline(a0,a1) HC_DQKInsert_Polyline(".",a0,a1)

HC_EXTERNAL HD_API HC_KEY HC_CDECL HC_DQKInsert_Ink HC_PROTO ((
				const char *, double, double, double));
#define HC_DInsert_Ink(a0,a1,a2) ((void)HC_DQKInsert_Ink(".",a0,a1,a2))
#define HC_DQInsert_Ink(a0,a1,a2,a3) ((void)HC_DQKInsert_Ink(a0,a1,a2,a3))
#define HC_DKInsert_Ink(a0,a1,a2) HC_DQKInsert_Ink(".",a0,a1,a2)
#define HC_DQRestart_Ink(a0) HC_QRestart_Ink(a0)
#define HC_DRestart_Ink HC_Restart_Ink


/* Lines */
HC_EXTERNAL HD_API HC_KEY HC_CDECL HC_DQKInsert_Line HC_PROTO ((
				const char *, double, double, double, double, double, double));
HC_EXTERNAL HD_API void HC_CDECL HC_DShow_Line HC_PROTO ((
				HC_KEY, double *, double *, double *, double *, double *, double *));
#define HC_DInsert_Line(a0,a1,a2,a3,a4,a5) ((void) HC_DQKInsert_Line(".",a0,a1,a2,a3,a4,a5))
#define HC_DQInsert_Line(a0,a1,a2,a3,a4,a5,a6) ((void) HC_DQKInsert_Line(a0,a1,a2,a3,a4,a5,a6))
#define HC_DKInsert_Line(a0,a1,a2,a3,a4,a5) HC_DQKInsert_Line(".",a0,a1,a2,a3,a4,a5)

/* Polygons */
HC_EXTERNAL HD_API HC_KEY HC_CDECL HC_DQKInsert_Polygon HC_PROTO ((
				const char *, int, const HCD_POINT *));
HC_EXTERNAL HD_API void HC_CDECL HC_DEdit_Polygon HC_PROTO ((
				HC_KEY, int, int, int, const HCD_POINT *));
HC_EXTERNAL HD_API void HC_CDECL HC_DShow_Polygon HC_PROTO ((
				HC_KEY, int *, HCD_POINT *));
#define HC_DInsert_Polygon(a0,a1) ((void)HC_DQKInsert_Polygon(".",a0,a1))
#define HC_DQInsert_Polygon(a0,a1,a2) ((void)HC_DQKInsert_Polygon(a0,a1,a2))
#define HC_DKInsert_Polygon(a0,a1) HC_DQKInsert_Polygon(".",a0,a1)

/* Markers */
HC_EXTERNAL HD_API HC_KEY HC_CDECL HC_DQKInsert_Marker HC_PROTO ((
				const char *, double, double, double));
HC_EXTERNAL HD_API void HC_CDECL HC_DShow_Marker HC_PROTO ((
				HC_KEY, double *, double *, double *));
#define HC_DInsert_Marker(a0,a1,a2) ((void)HC_DQKInsert_Marker(".",a0,a1,a2))
#define HC_DQInsert_Marker(a0,a1,a2,a3) ((void)HC_DQKInsert_Marker(a0,a1,a2,a3))
#define HC_DKInsert_Marker(a0,a1,a2) HC_DQKInsert_Marker(".",a0,a1,a2)

/* Cylinders */
HC_EXTERNAL HD_API HC_KEY HC_CDECL HC_DQKInsert_Cylinder HC_PROTO ((
				const char *, const HCD_POINT *, const HCD_POINT *, const double, const char *));
HC_EXTERNAL HD_API void HC_CDECL HC_DShow_Cylinder HC_PROTO ((
				HC_KEY, HCD_POINT *, HCD_POINT *, double *, char *));
#define HC_DInsert_Cylinder(a0,a1,a2,a3) ((void)HC_DQKInsert_Cylinder(".",a0,a1,a2,a3))
#define HC_DQInsert_Cylinder(a0,a1,a2,a3,a4) ((void)HC_DQKInsert_Cylinder(a0,a1,a2,a3,a4))
#define HC_DKInsert_Cylinder(a0,a1,a2,a3) HC_DQKInsert_Cylinder(".",a0,a1,a2,a3)


/* Circles */
HC_EXTERNAL HD_API HC_KEY HC_CDECL HC_DQKInsert_Circle HC_PROTO ((
				const char *, const HCD_POINT *, const HCD_POINT *, const HCD_POINT *));
HC_EXTERNAL HD_API void HC_CDECL HC_DShow_Circle HC_PROTO ((
				HC_KEY, HCD_POINT *, HCD_POINT *, HCD_POINT *));
#define HC_DInsert_Circle(a0,a1,a2) ((void)HC_DQKInsert_Circle(".",a0,a1,a2))
#define HC_DQInsert_Circle(a0,a1,a2,a3) ((void)HC_DQKInsert_Circle(a0,a1,a2,a3))
#define HC_DKInsert_Circle(a0,a1,a2) HC_DQKInsert_Circle(".",a0,a1,a2)



/* Circular Arcs */
HC_EXTERNAL HD_API HC_KEY HC_CDECL HC_DQKInsert_Circular_Arc HC_PROTO ((
				const char *, const HCD_POINT *, const HCD_POINT *, const HCD_POINT *));
HC_EXTERNAL HD_API void HC_CDECL HC_DShow_Circular_Arc HC_PROTO ((
				HC_KEY, HCD_POINT *, HCD_POINT *, HCD_POINT *));
#define HC_DInsert_Circular_Arc(a0,a1,a2) ((void)HC_DQKInsert_Circular_Arc(".",a0,a1,a2))
#define HC_DQInsert_Circular_Arc(a0,a1,a2,a3) ((void)HC_DQKInsert_Circular_Arc(a0,a1,a2,a3))
#define HC_DKInsert_Circular_Arc(a0,a1,a2) HC_DQKInsert_Circular_Arc(".",a0,a1,a2)

/* Circular Chords */
HC_EXTERNAL HD_API HC_KEY HC_CDECL HC_DQKInsert_Circular_Chord HC_PROTO ((
				const char *, const HCD_POINT *, const HCD_POINT *, const HCD_POINT *));
HC_EXTERNAL HD_API void HC_CDECL HC_DShow_Circular_Chord HC_PROTO ((
				HC_KEY, HCD_POINT *, HCD_POINT *, HCD_POINT *));
#define HC_DInsert_Circular_Chord(a0,a1,a2) ((void)HC_DQKInsert_Circular_Chord(".",a0,a1,a2))
#define HC_DQInsert_Circular_Chord(a0,a1,a2,a3) ((void)HC_DQKInsert_Circular_Chord(a0,a1,a2,a3))
#define HC_DKInsert_Circular_Chord(a0,a1,a2) HC_DQKInsert_Circular_Chord(".",a0,a1,a2)

/* Circular Wedges */
HC_EXTERNAL HD_API HC_KEY HC_CDECL HC_DQKInsert_Circular_Wedge HC_PROTO ((
				const char *, const HCD_POINT *, const HCD_POINT *, const HCD_POINT *));
HC_EXTERNAL HD_API void HC_CDECL HC_DShow_Circular_Wedge HC_PROTO ((
				HC_KEY, HCD_POINT *, HCD_POINT *, HCD_POINT *));
#define HC_DInsert_Circular_Wedge(a0,a1,a2) ((void)HC_DQKInsert_Circular_Wedge(".",a0,a1,a2))
#define HC_DQInsert_Circular_Wedge(a0,a1,a2,a3) ((void)HC_DQKInsert_Circular_Wedge(a0,a1,a2,a3))
#define HC_DKInsert_Circular_Wedge(a0,a1,a2) HC_DQKInsert_Circular_Wedge(".",a0,a1,a2)

/* Ellipses */
HC_EXTERNAL HD_API HC_KEY HC_CDECL HC_DQKInsert_Ellipse HC_PROTO ((
				const char *, const HCD_POINT *, const HCD_POINT *, const HCD_POINT *));
HC_EXTERNAL HD_API void HC_CDECL HC_DShow_Ellipse HC_PROTO ((
				HC_KEY, HCD_POINT *, HCD_POINT *, HCD_POINT *));
#define HC_DInsert_Ellipse(a0,a1,a2) ((void)HC_DQKInsert_Ellipse(".",a0,a1,a2))
#define HC_DQInsert_Ellipse(a0,a1,a2,a3) ((void)HC_DQKInsert_Ellipse(a0,a1,a2,a3))
#define HC_DKInsert_Ellipse(a0,a1,a2) HC_DQKInsert_Ellipse(".",a0,a1,a2)


/* Elliptical Arcs */
HC_EXTERNAL HD_API HC_KEY HC_CDECL HC_DQKInsert_Elliptical_Arc HC_PROTO ((
				const char *, const HCD_POINT *, const HCD_POINT *, const HCD_POINT *, double, double));
HC_EXTERNAL HD_API void HC_CDECL HC_DShow_Elliptical_Arc HC_PROTO ((
				HC_KEY, HCD_POINT *, HCD_POINT *, HCD_POINT *, double *, double *));
#define HC_DInsert_Elliptical_Arc(a0,a1,a2,a3,a4) ((void) HC_DQKInsert_Elliptical_Arc(".",a0,a1,a2,a3,a4))
#define HC_DQInsert_Elliptical_Arc(a0,a1,a2,a3,a4,a5) ((void) HC_DQKInsert_Elliptical_Arc(a0,a1,a2,a3,a4,a5))
#define HC_DKInsert_Elliptical_Arc(a0,a1,a2,a3,a4) HC_DQKInsert_Elliptical_Arc(".",a0,a1,a2,a3,a4)


/* Cutting Planes */
HC_EXTERNAL HD_API HC_KEY HC_CDECL HC_DQKInsert_Cutting_Plane HC_PROTO ((
				const char *, double, double, double, double));
HC_EXTERNAL HD_API void HC_CDECL HC_DShow_Cutting_Plane HC_PROTO ((
				HC_KEY, double *, double *, double *, double *));
#define HC_DInsert_Cutting_Plane(a0,a1,a2,a3) ((void)HC_DQKInsert_Cutting_Plane(".",a0,a1,a2,a3))
#define HC_DQInsert_Cutting_Plane(a0,a1,a2,a3,a4) ((void)HC_DQKInsert_Cutting_Plane(a0,a1,a2,a3,a4))
#define HC_DKInsert_Cutting_Plane(a0,a1,a2,a3) HC_DQKInsert_Cutting_Plane(".",a0,a1,a2,a3)

/* Images */
HC_EXTERNAL HD_API HC_KEY HC_CDECL HC_DQKInsert_Image HC_PROTO ((
				const char *, double, double, double, const char *, int, int, const HC_PIXEL *));
HC_EXTERNAL HD_API void HC_CDECL HC_DMove_Image HC_PROTO ((
				HC_KEY, double, double, double));
HC_EXTERNAL HD_API void HC_CDECL HC_DShow_Image HC_PROTO ((
				HC_KEY, double *, double *, double *, char *, int *, int *, HC_PIXEL *));
#define HC_DInsert_Image(a0,a1,a2,a3,a4,a5,a6)	((void) HC_DQKInsert_Image(".",a0,a1,a2,a3,a4,a5,a6))
#define HC_DQInsert_Image(a0,a1,a2,a3,a4,a5,a6,a7) ((void) HC_DQKInsert_Image(a0,a1,a2,a3,a4,a5,a6,a7))
#define HC_DKInsert_Image(a0,a1,a2,a3,a4,a5,a6) HC_DQKInsert_Image(".",a0,a1,a2,a3,a4,a5,a6)

/* Local Lights */
HC_EXTERNAL HD_API HC_KEY HC_CDECL HC_DQKInsert_Local_Light HC_PROTO ((
				const char *, double, double, double));
HC_EXTERNAL HD_API void HC_CDECL HC_DShow_Local_Light HC_PROTO ((
				HC_KEY, double *, double *, double *));
#define HC_DInsert_Local_Light(a0,a1,a2) ((void)HC_DQKInsert_Local_Light(".",a0,a1,a2))
#define HC_DQInsert_Local_Light(a0,a1,a2,a3) ((void)HC_DQKInsert_Local_Light(a0,a1,a2,a3))
#define HC_DKInsert_Local_Light(a0,a1,a2) HC_DQKInsert_Local_Light(".",a0,a1,a2)

/* Spot Lights */
HC_EXTERNAL HD_API HC_KEY HC_CDECL HC_DQKInsert_Spot_Light HC_PROTO ((
				const char *, const HCD_POINT *, const HCD_POINT *, const char *));
HC_EXTERNAL HD_API void HC_CDECL HC_DShow_Spot_Light HC_PROTO ((
				HC_KEY, HCD_POINT *, HCD_POINT *, char *));
#define HC_DInsert_Spot_Light(a0,a1,a2) ((void)HC_DQKInsert_Spot_Light(".",a0,a1,a2))
#define HC_DQInsert_Spot_Light(a0,a1,a2,a3) ((void)HC_DQKInsert_Spot_Light(a0,a1,a2,a3))
#define HC_DKInsert_Spot_Light(a0,a1,a2) HC_DQKInsert_Spot_Light(".",a0,a1,a2)

/* Distant Lights */
HC_EXTERNAL HD_API HC_KEY HC_CDECL HC_DQKInsert_Distant_Light HC_PROTO ((
				const char *, double, double, double));
HC_EXTERNAL HD_API void HC_CDECL HC_DMove_Distant_Light HC_PROTO ((
				HC_KEY, double, double, double));
HC_EXTERNAL HD_API void HC_CDECL HC_DShow_Distant_Light HC_PROTO ((
				HC_KEY, double *, double *, double *));
#define HC_DInsert_Distant_Light(a0,a1,a2) ((void)HC_DQKInsert_Distant_Light(".",a0,a1,a2))
#define HC_DQInsert_Distant_Light(a0,a1,a2,a3) ((void)HC_DQKInsert_Distant_Light(a0,a1,a2,a3))
#define HC_DKInsert_Distant_Light(a0,a1,a2) HC_DQKInsert_Distant_Light(".",a0,a1,a2)


/* Text */
HC_EXTERNAL HD_API HC_KEY HC_CDECL HC_DQKInsert_Text HC_PROTO ((
				const char *, double, double, double, const char *));
HC_EXTERNAL HD_API void HC_CDECL HC_DShow_Text HC_PROTO ((
				HC_KEY, double *, double *, double *, char *));
#define HC_DInsert_Text(a0,a1,a2,a3) ((void)HC_DQKInsert_Text(".",a0,a1,a2,a3))
#define HC_DQInsert_Text(a0,a1,a2,a3,a4) ((void)HC_DQKInsert_Text(a0,a1,a2,a3,a4))
#define HC_DKInsert_Text(a0,a1,a2,a3) HC_DQKInsert_Text(".",a0,a1,a2,a3)


HC_EXTERNAL HD_API HC_KEY HC_CDECL HC_DQKInsert_Text_With_Encoding HC_PROTO ((
				const char *, double, double, double, const char *, const void *));
HC_EXTERNAL HD_API void HC_CDECL HC_DShow_Text_With_Encoding HC_PROTO ((
				HC_KEY, double *, double *, double *, char *, void *));
#define HC_DInsert_Text_With_Encoding(a0,a1,a2,a3,a4) ((void)HC_DQKInsert_Text_With_Encoding(".",a0,a1,a2,a3,a4))
#define HC_DQInsert_Text_With_Encoding(a0,a1,a2,a3,a4,a5) ((void)HC_DQKInsert_Text_With_Encoding(a0,a1,a2,a3,a4,a5))
#define HC_DKInsert_Text_With_Encoding(a0,a1,a2,a3,a4) HC_DQKInsert_Text_With_Encoding(".",a0,a1,a2,a3,a4)

HC_EXTERNAL HD_API void HC_CDECL HC_DSet_Camera HC_PROTO ((
				const HCD_POINT *, const HCD_POINT *, const HCD_POINT *, double, double, const char * ));
HC_EXTERNAL HD_API void HC_CDECL HC_DSet_Camera_Position HC_PROTO ((
				double, double, double ));
HC_EXTERNAL HD_API void HC_CDECL HC_DSet_Camera_Target HC_PROTO ((
				double, double, double ));
HC_EXTERNAL HD_API void HC_CDECL HC_DSet_Camera_Up_Vector HC_PROTO ((
				double, double, double ));
HC_EXTERNAL HD_API void HC_CDECL HC_DSet_Camera_Field HC_PROTO ((
				double, double ));
HC_EXTERNAL HD_API void HC_CDECL HC_DShow_Camera HC_PROTO ((
				HCD_POINT *, HCD_POINT *, HCD_POINT *, double *, double *, char * ));
HC_EXTERNAL HD_API void HC_CDECL HC_DShow_Camera_Position HC_PROTO ((
				double *, double *, double * ));
HC_EXTERNAL HD_API void HC_CDECL HC_DShow_Camera_Target HC_PROTO ((
				double *, double *, double * ));
HC_EXTERNAL HD_API void HC_CDECL HC_DShow_Camera_Up_Vector HC_PROTO ((
				double *, double *, double * ));
HC_EXTERNAL HD_API void HC_CDECL HC_DShow_Camera_Field HC_PROTO ((
				double *, double * ));
HC_EXTERNAL HD_API HC_KEY HC_CDECL HC_DKCompute_Boolean_Shell HC_PROTO ((
		int, const HCD_POINT *, const HC_POINT *, int, const int *, int, const HCD_POINT *, const HC_POINT *, int, const int *, const char *,
		const HC_POINT *, const HC_POINT *, const unsigned short *, const unsigned short *));
 
HC_EXTERNAL HD_API int HC_DShow_Existence_By_Key HC_PROTO (( 
		HC_KEY ));

#endif /* HCD_DEFINED */
