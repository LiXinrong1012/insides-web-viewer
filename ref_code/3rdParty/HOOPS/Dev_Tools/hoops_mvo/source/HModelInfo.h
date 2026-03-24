//
// Copyright (c) 2000 by Tech Soft 3D, LLC.
// The information contained herein is confidential and proprietary to
// Tech Soft 3D, LLC., and considered a trade secret as defined under
// civil and criminal statutes.  Tech Soft 3D shall pursue its civil
// and criminal remedies in the event of unauthorized use or misappropriation
// of its trade secrets.  Use of this information by anyone other than
// authorized employees of Tech Soft 3D, LLC. is granted only under a
// written non-disclosure agreement, expressly prescribing the scope and
// manner of such use.
//
// $Header: /files/homes/master/cvs/hoops_master/hoops_mvo/source/HModelInfo.h,v 1.36 2009-04-10 02:02:42 nathan Exp $
//
#ifndef _HMODELINFO_H
#define _HMODELINFO_H

#ifdef H_PACK_8
#pragma pack(push)
#pragma pack(8)
#endif

#include "HTools.h"

//! The HModelInfo class computes and stores model information.
/*! 
  HModelInfo encapusulates information associated with a model. It provides routines that search and compute the 
  contents of a given HOOPS sub-tree.  Classes that implement custom model information routines should be derived from 
  HModelInfo.
*/
class MVO_API HModelInfo 
{

public:
	/*! Constructs an HModelInfo object. */
	HModelInfo (HC_KEY segment_key = INVALID_KEY) {m_SegmentKey=segment_key;ResetCounters();};
	virtual ~HModelInfo () {;};

	/*!
		ComputeModelInfo performs a contents search on a Hoops sub-tree.  The search begins at the segment passed with the 
		argument list and continues into and all of the direct and included sub-segments, counting each type of geometric 
		primitive in these segments.  Geometry totals can be accessed through the HModelInfo Get routines, or manipulated 
		by derived classes. 
		\param segment_key   The key of segment where the search should start.
	*/
 	virtual void ComputeModelInfo (HC_KEY segment_key=INVALID_KEY, bool recurse=true);

	/*! \return The sum of all faces in meshes and shells plus the polygon total.  */
	int			GetTotalFaces( void ) { return m_TotalFaces; }	
	/*! \return The sum of all vertices in meshes, each shell face and all polygons. */
	int			GetTotalVertices( void ) { return m_TotalVertices; }
	/*! \return The result of (total_vertices/total_faces - 2) * total_faces. */
	int			GetTotalTriangles( void ) { return m_TotalTriangles; }
	/*! \return The total tristrip count. */
	int			GetTotalTristrips( void ) { return m_TotalTristrips; }
	/*! \return The sum of all segments in the model. */
	int			GetTotalSegments( void ) { return m_TotalSegments; }
	/*! \return The sum of all circles in the model. */
	int			GetTotalCircle( void ) { return m_TotalCircle; }
	/*! \return The sum of all circular arcs in the model. */
	int			GetTotalCircularArc( void ) { return m_TotalCircularArc; }
	/*! \return The sum of all circular chords in the model. */
	int			GetTotalCircularChord( void ) { return m_TotalCircularChord; }
	/*! \return The sum of all circular wedges in the model. */
	int			GetTotalCircularWedge( void ) { return m_TotalCircularWedge; }
	/*! \return The sum of all ellipses in the model. */
	int			GetTotalEllipse( void ) { return m_TotalEllipse; }
	/*! \return The sum of all elliptical arcs in the model. */
	int			GetTotalEllipticalArc( void ) { return m_TotalEllipticalArc; }
	/*! \return The sum of all grids in the model. */
	int			GetTotalGrid( void ) { return m_TotalGrid; }
	/*! \return The sum of all images in the model. */
	int			GetTotalImage( void ) { return m_TotalImage; }
	/*! \return The sum of all includes in the model. */
	int			GetTotalIncludes( void ) { return m_TotalIncludes; }
	/*! \return The sum of all includer of the model. */
	int			GetTotalIncluders( void ) { return m_TotalIncluders; }
	/*! \return The sum of all lines in the model. */
	int			GetTotalLine( void ) { return m_TotalLine; }
	/*! \return The sum of all markers in the model. */
	int			GetTotalMarker( void ) { return m_TotalMarker; }
	/*! \return The sum of all meshes in the model. */
	int			GetTotalMesh( void ) { return m_TotalMesh; }
	/*! \return The sum of all polygons in the model. */
	int			GetTotalPolygon( void ) { return m_TotalPolygon; }
	/*! \return The sum of all polylines in the model. */
	int			GetTotalPolyline( void ) { return m_TotalPolyline; }
	/*! \return The sum of all shells in the model. */
	int			GetTotalShell( void ) { return m_TotalShell; }
	/*! \return The sum of all string cursors in the model. */
	int			GetTotalStringCursor( void ) { return m_TotalStringCursor; }
	/*! \return The sum of all text strings in the model. */
	int			GetTotalText( void ) { return m_TotalText; }
	/*! \return The sum of all modelling matrices in the model. */
	int			GetTotalMatrices( void ) { return m_TotalMatrices; }
	/*! \return The sum of all spot lights in the model. */
	int			GetTotalSpotLight( void ) { return m_TotalSpotLight; }
	/*! \return The sum of all distant lights in the model. */
	int			GetTotalDistantLight( void ) { return m_TotalDistantLight; }
	/*! \return The sum of all local lights in the model. */
	int			GetTotalLocalLight( void ) { return m_TotalLocalLight; }
	/*! \return The sum of all cutting planes in the model. */
	int			GetTotalCuttingPlane( void ) { return m_TotalCuttingPlane; }
	/*! \return The sum of all cylinders in the model. */
	int			GetTotalCylinders( void ) { return m_TotalCylinders; }
	/*! \return The sum of all polycylinders in the model. */
	int			GetTotalPolyCylinders( void ) { return m_TotalPolyCylinders; }
	/*! \return The sum of all spheres in the model. */
	int			GetTotalSpheres( void ) { return m_TotalSpheres; }
	/*! \return The sum of all NURBS curves in the model. */
	int			GetTotalNURBSCurves( void ) { return m_TotalNURBSCurves; }
	/*! \return The sum of all NURBS surfaces in the model. */
	int			GetTotalNURBSSurfaces( void ) { return m_TotalNURBSSurfaces; }
	/*! \return The sum of all references in the model. */
	int			GetTotalReferences( void ) { return m_TotalReferences; }
	/*! \return The sum of all infinite lines in the model. */
	int			GetTotalInfiniteLines( void ) {return m_TotalInfiniteLines; }
	/*! \return The sum of all infinite rays in the model. */
	int			GetTotalInfiniteRays( void ) {return m_TotalInfiniteRays; }
	/*! \return The sum of all other items in the model (SHOULD ALWAYS BE ZERO). */
	int			GetTotalOthers( void ) { return m_TotalOthers; }	

protected:

	/*! <b>For internal use only.</b>

		Initializes the number of primitives in a the count to zero.  Used internally by 
		ComputeModelInfo(), but can be useful in derived classes.
	*/ 
	virtual void ResetCounters();

	/*! <b>For internal use only.</b>

		Increments the number of primitives in a given count.  Used internally by ComputeModelInfo(), but
		can be used in derived classes.  
		\param item_type Type of the primitive to increment in the count (see HC_Begin_Contents_Search for types)
		\param item_key HOOPS key to any geometry.  In this case, "key" is used only for polygons, shells, and 
		meshes in order to calculate the sub-primitives and increment their numbers.
	*/
  	virtual void IncrementCounter (char * item_type, HC_KEY item_key); 
	/*! <b>For internal use only.</b>*/
	virtual void ComputeSegmentContents(HC_KEY the_key, bool recurse=true); 

	HC_KEY		m_SegmentKey;		 //!< <b>For internal use only</b>

	int			m_TotalFaces;		 //!< <b>For internal use only.</b>		
	int			m_TotalVertices;	 //!< <b>For internal use only.</b>		
	int			m_TotalTriangles;	 //!< <b>For internal use only.</b>
	int			m_TotalTristrips;	 //!< <b>For internal use only.</b>
	int			m_TotalSegments;	 //!< <b>For internal use only.</b>

	int			m_TotalCircle;		 //!< <b>For internal use only.</b>
	int			m_TotalCircularArc;	 //!< <b>For internal use only.</b>
	int			m_TotalCircularChord;	 //!< <b>For internal use only.</b>

	int			m_TotalCircularWedge;	//!< <b>For internal use only.</b>
	int			m_TotalEllipse;			//!< <b>For internal use only.</b>
	int			m_TotalEllipticalArc;	//!< <b>For internal use only.</b>
	int			m_TotalGrid;			//!< <b>For internal use only.</b>
	int			m_TotalImage;			//!< <b>For internal use only.</b>
	int			m_TotalIncludes;		//!< <b>For internal use only.</b>
	int			m_TotalIncluders;		//!< <b>For internal use only.</b>
	int			m_TotalLine;			//!< <b>For internal use only.</b>		
	int			m_TotalMarker;			//!< <b>For internal use only.</b>
	int			m_TotalMesh;			//!< <b>For internal use only.</b>
	int			m_TotalPolygon;			//!< <b>For internal use only.</b>
	int			m_TotalPolyline;		//!< <b>For internal use only.</b>
	int			m_TotalShell;			//!< <b>For internal use only.</b>
	int			m_TotalStringCursor;	//!< <b>For internal use only.</b>
	int			m_TotalText;			//!< <b>For internal use only.</b>
	int			m_TotalMatrices;		//!< <b>For internal use only.</b>
   	
   	int			m_TotalSpotLight;		//!< <b>For internal use only.</b>
   	int			m_TotalDistantLight;	//!< <b>For internal use only.</b>
	int			m_TotalLocalLight;		//!< <b>For internal use only.</b>

	int			m_TotalCuttingPlane;	//!< <b>For internal use only.</b>

	int			m_TotalPolyCylinders;	//!< <b>For internal use only.</b>
	int			m_TotalCylinders;		//!< <b>For internal use only.</b>
	int			m_TotalSpheres;			//!< <b>For internal use only.</b>
	int			m_TotalNURBSCurves;		//!< <b>For internal use only.</b>
	int			m_TotalNURBSSurfaces;	//!< <b>For internal use only.</b>
	int			m_TotalReferences;		//!< <b>For internal use only.</b>
	int			m_TotalInfiniteLines;	//!< <b>For internal use only.</b>
	int			m_TotalInfiniteRays;	//!< <b>For internal use only.</b>

	int			m_TotalOthers;			//!< <b>For internal use only.</b>

};


#ifdef H_PACK_8
#pragma pack(pop)
#endif

#endif




