//
// (C) Copyright 1995-1996,1998-2004 by Autodesk, Inc.
//
//    This program is copyrighted by Autodesk, Inc. and is  licensed
//    to you under the following conditions.  You may not distribute
//    or  publish the source code of this program in any form.   You
//    may  incorporate this code in object form in derivative  works
//    provided  such  derivative  works  are  (i.) are  designed and 
//    intended  to  work  solely  with  Autodesk, Inc. products, and 
//    (ii.)  contain  Autodesk's  copyright  notice  "(C)  Copyright  
//    1995-1996 by Autodesk, Inc."
//
//    AUTODESK  PROVIDES THIS PROGRAM "AS IS" AND WITH  ALL  FAULTS.
//    AUTODESK  SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF  MER-
//    CHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK,  INC.
//    DOES  NOT  WARRANT THAT THE OPERATION OF THE PROGRAM  WILL  BE
//    UNINTERRUPTED OR ERROR FREE.

// HDWGHelper.CPP

#include "HDWGHelper.h"

// RealDWG Toolkit includes
#include "acdb.h"
#include "adesk.h"
#include "acgi.h"
#include "acestext.h"
#include "acgiutil.h"
#include "acgimaterial.h"
#include "acutmem.h"
#include "achapi.h"

#include "dbmain.h"
#include "dbents.h"
#include "dbsymtb.h"
#include "dbents.h"
#include "dbelipse.h"
#include "dbspline.h"
#include "dbhatch.h"
#include "dblead.h"
#include "dbray.h"
#include "dbxline.h"
#include "dbmline.h"
#include "dbbody.h"
#include "dbimage.h"
#include "dbregion.h"
#include "dbsol3d.h"
#include "dbfcf.h"
#include "dbproxy.h"
#include "dbapserv.h"
#include "dbmstyle.h"
#include "dbmaterial.h"
#include "dbgroup.h"
#include "dbdict.h"

#include "gelnsg3d.h"
#include "rxobject.h"
#include "rxregsvc.h" 

// HOOPS includes
#include "hc.h"
#include "HTools.h"

// Standard includes
//#include <assert.h>
//#include <math.h>
//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
//#include <time.h>
//#include <wchar.h>

// HOOPS/MVO includes
#include "HDB.h"
#include "HUtilityLocaleString.h"
#include "HUtilityGeometryCreation.h"
#include "HIOUtilityDWG.h"
#include "HBaseView.h"

#include "vlist.h"

// NOTE: REALDWG SDK FILE achapi.h REQUIRES 'UINT' WHICH SEEMS TO BE NON-STANDARD C/C++ DATATYPE AND IS 
// DEFINED IN windef.h. I COULDN'T INCLUDE THAT FILE DIRECTLY HERE BECAUSE OF WEIRD COMPILER ERRORS. INCLUDING
// windows.h SOLVES THE PROBLEM, BUT MAKES THIS CODE WINDOWS-ONLY. THAT SHOULD BE FINE - IF REALDWG ITSELF DOESN'T
// SUPPORT ANYTHING ELSE. Pavan T. (22nd Oct 07)
//#include <windows.h>
//#include "achapi.h" 

///////////////

wchar_t * h_dwg_wcsdup(wchar_t const * const wcs)
{
	size_t len = wcslen(wcs) + 10;
	wchar_t * retval = (wchar_t*)malloc(sizeof(wchar_t) * len);
	wcscpy(retval, wcs);
	return retval;
}

HDWGImporter::HDWGImporter(HIOUtilityDWG* pDWGInputHandler)
			 : m_pDWGInputHandler(pDWGInputHandler)
{
	m_pConnectivityInfo = 0; 
	m_pDWGTextureDirectory = 0; 
	m_bDrawWireframe = true;
	m_bIs3D = false;
	m_bIs2DEntity = false;
	m_Deviation = 10.0;
	m_bImportXData = false;
	m_bImportWireframeForBrep = false;
	m_numIsolines = 0;
	m_listRegAppNames = 0;
	m_listEntityType=0;
	m_wmin[0] = m_wmin[1] = m_wmin[2] = 0.0;
	m_wmax[0] = m_wmax[1] = m_wmax[2] = 0.0;
	m_nLine_count = 0;
	m_nPoint_count = 0;
	m_nPloyLine_count = 0;
	m_nCircle_count = 0;
	m_nArc_count = 0;
	
	m_nSolid_count = 0;
	m_nSolid3D_count = 0;
	m_nGroup_count = 0;
	m_nPloygon_count = 0;
	m_nShell_count = 0;
	m_nText_count = 0;

	m_fileName = NULL;
	layer_record.empty();
	group_record.empty();
	entity_record.empty();
	block_ref_record.empty();
	m_BlockRefIndex = -1;
	m_listDWGLayouts = 0;
	m_bAttachDWGHandles=false;
	m_bImportAllLayouts = false;
	m_bCleanVpList = false;
	m_bAmIsolidHatch = false;
	m_pInputOptions = NULL;
	m_dGlobalScaleFactor = 1;
	m_bIsSHXFont = false;
	m_bDWGInsertMeshesAsShells = false;
	m_bDisableDWGDrawOrder = false;
}

HDWGImporter::~HDWGImporter()
{
	if(m_fileName)
		free(const_cast<wchar_t*>(m_fileName));
	std::map<int, wchar_t*>::iterator itr;
	for(itr = layer_record.begin(); itr != layer_record.end(); itr++)
	{
		if(itr->second)
			free(itr->second);
	}
	layer_record.clear();
	for(itr = group_record.begin(); itr != group_record.end(); itr++)
	{
		if(itr->second)
			free(itr->second);
	}
	group_record.clear();
	for(itr = entity_record.begin(); itr != entity_record.end(); itr++)
	{
		if(itr->second)
			free(itr->second);
	}
	entity_record.clear();

	for(itr = block_ref_record.begin(); itr != block_ref_record.end(); itr++)
	{
		if(itr->second)
			free(itr->second);
	}
	block_ref_record.clear();
}

bool HDWGImporter::get_entity_rgb(AcDbEntity *pEnt, const AcDbLayerTableRecord *pLayerTableRecord, float& red, float& green, float& blue, bool& is_by_block, bool for_blk_ref)
{
	is_by_block = false;

	// Get the RGB first
	Adesk::UInt16 color_idx = pEnt->colorIndex();
	AcCmColor cm_color = pEnt->color();

	// color is BYLAYER
	if(color_idx == 256 )
	{
        if (pLayerTableRecord)
        {
			cm_color = pLayerTableRecord->color();
			color_idx = cm_color.colorIndex();
			wchar_t *lName;
			lName = pEnt->layer();
			if(for_blk_ref == true && color_idx == 7 && !(wcsicmp(L"0", lName)))
			{
				acdbFree(lName);
				return false;
			}
			acdbFree(lName);
        }
	}

	// color is DEFAULT
	if(color_idx == 257)
	{
		// Should we set a database color since we have created this 
		// database ourselves and default cecolor is 256 (which is confusing as hell)
		// for now let this pass and draw in BLACK
		AcDbDatabase* pDatabase = acdbHostApplicationServices()->workingDatabase();
		color_idx = pDatabase->cecolor().colorIndex(); 
		cm_color = pDatabase->cecolor();
	}


	// NOTE: 0 is actually color BY BLOCK. Which means (from ObjectARX docs):
	//
	// "Entities inherit the color of the current block reference that 
	//  points to the block table record that the entity resides in, or black/white 
	//  if the entity resides directly in the model space or paper space block table record"
	
	if(color_idx == 0 )
	{
		is_by_block = true;
		return true;
	}

	// Finally we think we have got an RGB here
	Adesk::UInt32 RGBM_byte = AcCmEntityColor::lookUpRGB(color_idx);

	red = (float) GetRValueFromRGBM(RGBM_byte)/255.0f;
	green = (float) GetGValueFromRGBM(RGBM_byte)/255.0f;
	blue = (float) GetBValueFromRGBM(RGBM_byte)/255.0f;

	return true;
}

void HDWGImporter::get_entity_transparency(AcDbEntity *pEnt, const AcDbLayerTableRecord *pLayerTableRecord, int &alpha_value, bool& is_by_block )
{	
	is_by_block = false;
	alpha_value = 255;
	
	// Get the alpha (transparency)
	AcCmTransparency ent_transparency = pEnt->transparency(); 
	 
	// transparency is BYLAYER
	if(ent_transparency.isByLayer())
	{
        if (pLayerTableRecord)
        {
			ent_transparency = pLayerTableRecord->transparency();
        }
	}

	// NOTE: 0 is actually transparency BY BLOCK. Which means (from ObjectARX docs):
	//
	// "Entities inherit the transparency of the current block reference that 
	//  points to the block table record that the entity resides in,
	
	if(ent_transparency.isByBlock())
	{
		is_by_block = true;
		return;
	}

	alpha_value = ent_transparency.alpha();
	return;
}

void HDWGImporter::get_entity_visibility(AcDbEntity *pEnt, const AcDbLayerTableRecord *pLayerTableRecord, bool& is_visible )
{	
	is_visible = true;

	// From ObjectARX documentation:
	// If you specify that an entity is invisible, it will be invisible regardless 
	// of other settings in the database. Other factors can also cause an entity to be invisible. 
	// For example, an entity will not be displayed if its layer is turned off or frozen. 
	// The value of AcDb::Visibility can be either kInvisible or kVisible. 

	if( pEnt->visibility() == AcDb::kInvisible )
	{
		is_visible = false;
		return;
	}
	if (pLayerTableRecord)
	{
		if( (pLayerTableRecord->isFrozen() == true) || (pLayerTableRecord->isOff() == true) )
			is_visible = false;
	}
	return;
}

void HDWGImporter::get_entity_line_weight(AcDbEntity *pEnt, const AcDbLayerTableRecord *pLayerTableRecord, float& ret_line_weight, bool& is_by_block)
{
	is_by_block = false;
	ret_line_weight = 0.0f;

	AcDb::LineWeight line_weight = pEnt->lineWeight();

	// If the line weight is by block, then just ignore it.
	// Because we know that in that case it is going to be inherited
	if(line_weight == AcDb::kLnWtByLayer )
	{
		if (pLayerTableRecord)
		{
			line_weight = pLayerTableRecord->lineWeight();
		}
	}

	if(line_weight == AcDb::kLnWtByBlock )
	{
		is_by_block = true;
		return;
	}

	if( line_weight == AcDb::kLnWtByLwDefault )
	{
		//AcDbDatabase* pDatabase = acdbHostApplicationServices()->workingDatabase();
		//line_weight = pDatabase->celweight();
		// the line wt is LWDEFAULT. there must be some way to query this from ACAD
		// but till we get to know that, let's assume it to be 0.25 mm (which is LWDEFAULT's initial value)
		line_weight = H_LWDEFAULT;
	}

	// this is just for precaution. we should never get in here.
	if( line_weight < 0 )
		return;

	// now we know that we have got some real number

	//char weight_str[MVO_BUFFER_SIZE];
	ret_line_weight = line_weight * H_MM_TO_POINTS/100.0f;

	//ret_line_weight = ceil(ret_line_weight);
}


struct data_AcDbMTextFragments{
	HDWGImporter* pDWGImporter;
	AcDbMText*	  pAcDbMText;
};

int callback_AcDbMTextFragments(AcDbMTextFragment *frag, void *param)
{
	data_AcDbMTextFragments* pData = (data_AcDbMTextFragments*) param;
	if(!pData)
		return 0;

	HDWGImporter* pImporter = pData->pDWGImporter;
	if(pImporter)
	{
		pImporter->importAcDbMTextFragment(frag, pData->pAcDbMText);
		return 1;
	}
	else
		return 0;
}

void HDWGImporter::importAcDbMText(AcDbMText *pAcDbMText)
{
	// may be we can do this without exploding and use
	// HOOPS per-character font attributes feature - Rajesh B (18-May-06)
	data_AcDbMTextFragments user_data;
	user_data.pDWGImporter = this;
	user_data.pAcDbMText = pAcDbMText;
	pAcDbMText->explodeFragments(callback_AcDbMTextFragments, (void*)&user_data);
}



Adesk::Boolean HDWGImporter::import_circle(const AcGePoint3d& center,
										   const double radius,
										   const AcGeVector3d& normal,
										   AcDbEntity* pDatabaseEntity
										   ) const
{ 
	if( !m_bDrawWireframe )
		return Adesk::kFalse;

	// Moving this implementation to before worldDraw because we don't know how to 
	// get the thickness (in which case we have to draw a cylinder) - Pavan T (29-03-2006)
	/*
	if (h_thickness == 0)
	{
		AcGeVector3d Wx(1, 0, 0);
		AcGeVector3d Wy(0, 1, 0);
		AcGeVector3d Wz(0, 0, 1);
		AcGeVector3d Ax,Ay,Az;

		if ((fabs (normal.x) < 1.0f/64.0f) && (fabs (normal.y) < 1.0f/64.0f))
			Ax = Wy.crossProduct(normal);
		else
			Ax = Wz.crossProduct(normal);

		Ax.normalize();

		Ay = normal.crossProduct(Ax);
		Ay.normalize();

		Az = normal;

		double cos_X_alpha = Wx.dotProduct(Ax);
		double cos_X_beta  = Wy.dotProduct(Ax);
		double cos_X_theta = Wz.dotProduct(Ax);

		float h_major[3];
		h_major[0] = (float) (center.x + radius*cos_X_alpha);
		h_major[1] = (float) (center.y + radius*cos_X_beta);
		h_major[2] = (float) (center.z + radius*cos_X_theta);


		double cos_Y_alpha = Wx.dotProduct(Ay);
		double cos_Y_beta  = Wy.dotProduct(Ay);
		double cos_Y_theta = Wz.dotProduct(Ay);

		float h_minor[3];
		h_minor[0] = (float) (center.x + radius*cos_Y_alpha);
		h_minor[1] = (float) (center.y + radius*cos_Y_beta);
		h_minor[2] = (float) (center.z + radius*cos_Y_theta);

		float h_center[3];
		h_center[0] = (float)center.x;
		h_center[1] = (float)center.y;
		h_center[2] = (float)center.z;

		// Insert_Circle_By_Radius would have been much easier to use, but it inserts
		// a circular disc, which is not what we want here.
		HC_KEY circle_key = HC_Insert_Elliptical_Arc (h_center, h_major, h_minor, 0.0f, 1.0f);

		if(m_pConnectivityInfo)
			m_pConnectivityInfo->AddConnection(circle_key, pDatabaseEntity);
	}
	*/

	return Adesk::kFalse;
}

//////////////////////////////////////////
//  Implementation of CustomWorldGeometry
ACRX_NO_CONS_DEFINE_MEMBERS(HAcGiWorldGeometry,AcGiWorldGeometry)
HAcGiWorldGeometry::HAcGiWorldGeometry(HAcGiWorldDraw*	pWorldDraw)
{
	m_pHAcGiWorldDraw = pWorldDraw;  // store a back pointer to worldDraw object that instantiates
	// this worldGeometry object.
}

HAcGiWorldGeometry::~HAcGiWorldGeometry()
{
}

// Captures circle info from Autocad and inserts a HOOPS circle
Adesk::Boolean  HAcGiWorldGeometry::circle(const AcGePoint3d& center,
										   const double radius,
										   const AcGeVector3d& normal
										   ) const
{
	return m_pHAcGiWorldDraw->GetHDWGImporter()->import_circle(center, radius, normal, 
													m_pHAcGiWorldDraw->GetCurrentEntity());
}

Adesk::Boolean  HAcGiWorldGeometry::circle(const AcGePoint3d& pt1,
										   const AcGePoint3d& pt2,
										   const AcGePoint3d& pt3
										   ) const
{
	return m_pHAcGiWorldDraw->GetHDWGImporter()->import_circle(pt1, pt2, pt3, 
													m_pHAcGiWorldDraw->GetCurrentEntity());
}

Adesk::Boolean  HAcGiWorldGeometry::circularArc(const AcGePoint3d& center,
												const double radius,
												const AcGeVector3d& normal,
												const AcGeVector3d& startVector,
												const double sweepAngle,
												const AcGiArcType arcType
												) const
{
	return m_pHAcGiWorldDraw->GetHDWGImporter()->import_circular_arc(	
												center, radius, normal, 
												startVector, sweepAngle, arcType, 
												m_pHAcGiWorldDraw->GetCurrentEntity() );
}

Adesk::Boolean  HAcGiWorldGeometry::circularArc   (const AcGePoint3d& start,
												   const AcGePoint3d& point,
												   const AcGePoint3d& end,
												   const AcGiArcType arcType
												   ) const
{
	return m_pHAcGiWorldDraw->GetHDWGImporter()->import_circular_arc(
																start, point, 
																end, arcType, 
																m_pHAcGiWorldDraw->GetCurrentEntity());
}

Adesk::Boolean  HAcGiWorldGeometry::polyline  (const Adesk::UInt32 nbPoints,
											   const AcGePoint3d* pVertexList,
											   const AcGeVector3d* pNormal,
											   Adesk::LongPtr lBaseSubEntMarker) const
{
	AcDbEntity* pDatabaseEntity =	m_pHAcGiWorldDraw->GetCurrentEntity();
	if(((AcDb2dPolyline*)pDatabaseEntity)->thickness() != 0.0)
	{
		(m_pHAcGiWorldDraw->GetHDWGImporter())->setIs2dEntity(false);
	}
	return m_pHAcGiWorldDraw->GetHDWGImporter()->import_polyline( 
														nbPoints, pVertexList,
														pNormal, lBaseSubEntMarker, 
														m_pHAcGiWorldDraw->GetCurrentEntity());
}

//************************************************************************************************************************//
				//// TODO : Write detail definition- sumitK [01/06/09]//

 Adesk::Boolean  HAcGiWorldGeometry::polyline(const AcGiPolyline& polylineObj) const {return Adesk::kFalse;}	
 Adesk::Boolean   HAcGiWorldGeometry::polyPolyline (Adesk::UInt32 nbPolylines,
                                          const AcGiPolyline* pPolylines) const{return Adesk::kFalse;}			
 Adesk::Boolean   HAcGiWorldGeometry::polyPolygon(const Adesk::UInt32 numPolygonIndices,
                                    const Adesk::UInt32* numPolygonPositions,
                                    const AcGePoint3d* polygonPositions,
                                    const Adesk::UInt32* numPolygonPoints,
                                    const AcGePoint3d* polygonPoints,
                                    const AcCmEntityColor* outlineColors,
                                    const AcGiLineType* outlineTypes,
                                    const AcCmEntityColor* fillColors ,
                                    const AcCmTransparency* fillOpacities ) const {return Adesk::kFalse;} 
 Adesk::Boolean   HAcGiWorldGeometry::image(const AcGiImageBGRA32& imageSource,
                                  const AcGePoint3d& position,
                                  const AcGeVector3d& u, //orientation and magnitude of width
                                  const AcGeVector3d& v, //orientation and magnitude of height
                                  TransparencyMode transparencyMode = kTransparency8Bit
                                  ) const {return Adesk::kFalse;}
 Adesk::Boolean   HAcGiWorldGeometry::rowOfDots(int count,
                          const AcGePoint3d&     start,
                          const AcGeVector3d&     step
                         ) const {return Adesk::kFalse;}
 Adesk::Boolean   HAcGiWorldGeometry::ellipticalArc(const AcGePoint3d&         center,
                                  const AcGeVector3d&        normal,
                                  double                     majorAxisLength,
                                  double                     minorAxisLength,
                                  double                     startDegreeInRads,
                                  double                     endDegreeInRads,
                                  double                     tiltDegreeInRads,
                                  AcGiArcType                arcType = kAcGiArcSimple
                                  ) const {return Adesk::kFalse;}

 //************************************************************************************************************************//

Adesk::Boolean HAcGiWorldGeometry::polypoint(const Adesk::UInt32 nbPoints,
								 const AcGePoint3d* pVertexList,
								 const AcGeVector3d* pNormal,
								 const Adesk::LongPtr * pSubEntMarkers) const
{
	return m_pHAcGiWorldDraw->GetHDWGImporter()->import_polypoint( 
													nbPoints, pVertexList,
													pNormal, pSubEntMarkers, 
													m_pHAcGiWorldDraw->GetCurrentEntity());

}

Adesk::Boolean  HAcGiWorldGeometry::polygon(const Adesk::UInt32 nbPoints,
											const AcGePoint3d* pVertexList
											) const
{
	return m_pHAcGiWorldDraw->GetHDWGImporter()->import_polygon(nbPoints, pVertexList, 
													m_pHAcGiWorldDraw->GetCurrentEntity());
}

Adesk::Boolean  HAcGiWorldGeometry::mesh  (const Adesk::UInt32 rows,
										   const Adesk::UInt32 columns,
										   const AcGePoint3d* pVertexList,
										   const AcGiEdgeData* pEdgeData,
										   const AcGiFaceData* pFaceData,
										   const AcGiVertexData* pVertexData,
										   const bool bAutoGenerateNormals
										   ) const
{
	return m_pHAcGiWorldDraw->GetHDWGImporter()->import_mesh(rows, columns, pVertexList,
															 pEdgeData, pFaceData, pVertexData,
															 bAutoGenerateNormals, 
															 m_pHAcGiWorldDraw->GetCurrentEntity());

}

Adesk::Boolean  HAcGiWorldGeometry::shell (const Adesk::UInt32 nbVertex,
										   const AcGePoint3d* pVertexList,
										   const Adesk::UInt32 faceListSize,
										   const Adesk::Int32* pFaceList,
										   const AcGiEdgeData* pEdgeData,
										   const AcGiFaceData* pFaceData ,
										   const AcGiVertexData* pVertexData,
										   const struct resbuf* pResBuf,
										   const bool bAutoGenerateNormals
										   ) const


{
	return m_pHAcGiWorldDraw->GetHDWGImporter()->import_shell( nbVertex, pVertexList,
															faceListSize, pFaceList,
															pEdgeData, pFaceData,
															pVertexData, pResBuf, bAutoGenerateNormals, 
															m_pHAcGiWorldDraw->GetCurrentEntity());
}

Adesk::Boolean  HAcGiWorldGeometry::text  (const AcGePoint3d& position,
										   const AcGeVector3d& normal,
										   const AcGeVector3d& direction,
										   const double height,
										   const double width,
										   const double oblique,
										   const ACHAR* pMsg
										   ) const
{
	// ALERT: RealDWG docs misguides on the pMsg. Here's what it says
	// A copy of the text string is used in pMsg, so the calling application is responsible for the memory of the string passed in.
	// DO NOT delete pMsg - you will get an assertion bomb thrown - Rajesh B (20-Feb-08)

	return m_pHAcGiWorldDraw->GetHDWGImporter()->import_text(position, normal, direction,
															height, width, oblique, pMsg, 
															m_pHAcGiWorldDraw->GetCurrentEntity());
}

Adesk::Boolean  HAcGiWorldGeometry::text  (const AcGePoint3d& position,
										   const AcGeVector3d& normal,
										   const AcGeVector3d& direction,
										   const ACHAR* pMsg,
										   const Adesk::Int32 length,
										   const Adesk::Boolean raw,
										   const AcGiTextStyle &pTextStyle
										   ) const
{
	// ALERT: RealDWG docs misguides on the pMsg. Here's what it says
	// A copy of the text string is used in pMsg, so the calling application is responsible for the memory of the string passed in.
	// DO NOT delete pMsg - you will get an assertion bomb thrown - Rajesh B (20-Feb-08)

	return m_pHAcGiWorldDraw->GetHDWGImporter()->import_text(position, normal, direction,
														pMsg, length, raw, pTextStyle, 
														m_pHAcGiWorldDraw->GetCurrentEntity());
}

Adesk::Boolean  HAcGiWorldGeometry::pline(const AcDbPolyline& lwBuf,
										  Adesk::UInt32 fromIndex,
										  Adesk::UInt32 numSegs
										  ) const
{
	if(lwBuf.thickness() != 0.0)
	{
		m_pHAcGiWorldDraw->GetHDWGImporter()->setIs2dEntity(false);
	}
	return m_pHAcGiWorldDraw->GetHDWGImporter()->import_pline(lwBuf, fromIndex, numSegs, 
														m_pHAcGiWorldDraw->GetCurrentEntity());
}

Adesk::Boolean  HAcGiWorldGeometry::ray(const AcGePoint3d& rays_starting_point,
										const AcGePoint3d& a_different_ray_point
										) const
{
	return Adesk::kFalse;
}

Adesk::Boolean  HAcGiWorldGeometry::xline(const AcGePoint3d& one_xline_point,
										  const AcGePoint3d& a_different_xline_point
										  ) const
{
	return Adesk::kFalse;
}

void HAcGiWorldGeometry::getModelToWorldTransform(AcGeMatrix3d &pMatrix) const
{
	return;
}

void HAcGiWorldGeometry::getWorldToModelTransform(AcGeMatrix3d &pMatrix) const
{
	return;
}

void HAcGiWorldGeometry::setExtents(AcGePoint3d *pNewExtents) const
{
	return;
}

Adesk::Boolean HAcGiWorldGeometry::pushModelTransform(const AcGeVector3d & vNormal)
{
	return Adesk::kFalse;
}

Adesk::Boolean HAcGiWorldGeometry::pushModelTransform(const AcGeMatrix3d & xMat)
{
	return Adesk::kFalse;
}

Adesk::Boolean HAcGiWorldGeometry::popModelTransform()
{
	return Adesk::kFalse;
}

Adesk::Boolean  HAcGiWorldGeometry::draw(AcGiDrawable*) const
{
	return Adesk::kFalse;
}

Adesk::Boolean  HAcGiWorldGeometry::pushClipBoundary(AcGiClipBoundary * pBoundary)
{
	return Adesk::kFalse;
}

void HAcGiWorldGeometry::popClipBoundary()
{
}
AcGeMatrix3d HAcGiWorldGeometry::pushPositionTransform (AcGiPositionTransformBehavior behavior, const AcGePoint3d& offset){AcGeMatrix3d mat3d; return mat3d.setToIdentity();}
AcGeMatrix3d HAcGiWorldGeometry::pushPositionTransform (AcGiPositionTransformBehavior behavior, const AcGePoint2d& offset){AcGeMatrix3d mat3d; return mat3d.setToIdentity();}
AcGeMatrix3d HAcGiWorldGeometry::pushScaleTransform (AcGiScaleTransformBehavior behavior, const AcGePoint3d& extents) {AcGeMatrix3d mat3d; return mat3d.setToIdentity();} 
AcGeMatrix3d HAcGiWorldGeometry::pushScaleTransform (AcGiScaleTransformBehavior behavior, const AcGePoint2d& extents){AcGeMatrix3d mat3d; return mat3d.setToIdentity();}
AcGeMatrix3d HAcGiWorldGeometry::pushOrientationTransform (AcGiOrientationTransformBehavior behavior) {AcGeMatrix3d mat3d; return mat3d.setToIdentity();}


////////////////////////////////////////////
//  Implementation of CustomWorldDraw class

ACRX_NO_CONS_DEFINE_MEMBERS(HAcGiWorldDraw,AcGiWorldDraw)

HAcGiWorldDraw::HAcGiWorldDraw(HDWGImporter* pDWGImporter, AcDbEntity* pAcDbEntity)
: m_pDWGImporter(pDWGImporter), m_pAcDbEntity(pAcDbEntity) 
{
	mpContext		  = new HAcGiContext;
	mpSubEntityTraits = new HAcGiSubEntityTraits;
	mpWorldGeometry   = new HAcGiWorldGeometry(this);
	mRegenType		  = kAcGiHideOrShadeCommand;
}

HAcGiWorldDraw::~HAcGiWorldDraw()
{
	delete mpSubEntityTraits;
	delete mpWorldGeometry;
	delete mpContext;
}

AcGiRegenType HAcGiWorldDraw::regenType() const
{
	return	mRegenType;
}

void HAcGiWorldDraw::setRegenType(const AcGiRegenType& new_regen_type)
{
	mRegenType = new_regen_type;
}

Adesk::Boolean HAcGiWorldDraw::regenAbort() const
{
	return	Adesk::kFalse;
}

AcGiSubEntityTraits& HAcGiWorldDraw::subEntityTraits() const
{
	return *mpSubEntityTraits;
}

AcGiGeometry *			HAcGiWorldDraw::rawGeometry() const
{
	return mpWorldGeometry;
}

AcGiWorldGeometry&      HAcGiWorldDraw::geometry() const
{
	return *mpWorldGeometry;
}

Adesk::Boolean          HAcGiWorldDraw::isDragging() const
{
	return Adesk::kFalse;
}

double HAcGiWorldDraw::deviation(const AcGiDeviationType, const AcGePoint3d&) const
{
	if( m_pDWGImporter )
		return m_pDWGImporter->get_deviation();
	else
		return 10;
}

Adesk::UInt32 HAcGiWorldDraw::numberOfIsolines() const
{
	if( m_pDWGImporter )
		return m_pDWGImporter->get_num_isolines();
	else
		return 0;
}

AcGiContext *  HAcGiWorldDraw::context()
{
	return mpContext;
}

HDWGImporter* HAcGiWorldDraw::GetHDWGImporter() const
{
	return m_pDWGImporter;
}

AcDbEntity* HAcGiWorldDraw::GetCurrentEntity() const
{
	return m_pAcDbEntity;
}

void HAcGiWorldDraw::setDeviation(double dev)
{
	if(m_pDWGImporter)
		m_pDWGImporter->set_deviation(dev);
}

/////////////////////////////////////////////////
//  Implementation of HAcGiSubEntityTraits object
ACRX_NO_CONS_DEFINE_MEMBERS(HAcGiSubEntityTraits,AcGiSubEntityTraits)

HAcGiSubEntityTraits::HAcGiSubEntityTraits()
{
	mColorIndex = 5;
	mMarkerId	= 1;
	mFillType	= kAcGiFillAlways;
}

HAcGiSubEntityTraits::~HAcGiSubEntityTraits() 
{
}

void HAcGiSubEntityTraits::setColor(const Adesk::UInt16 color)
{
	mColorIndex = color;
}

void HAcGiSubEntityTraits::setTrueColor(const AcCmEntityColor& color)
{
	mTrueColor = color;
}

void HAcGiSubEntityTraits::setLayer(const AcDbObjectId layerId)
{
	mLayerId = layerId;	
}

void HAcGiSubEntityTraits::setLineType(const AcDbObjectId linetypeId)
{
	mLinetypeId = linetypeId;
}

void HAcGiSubEntityTraits::setSelectionMarker(const Adesk::LongPtr markerId)
{
	mMarkerId = markerId;
}

void HAcGiSubEntityTraits::setFillType(const AcGiFillType fillType)
{
	mFillType = fillType;
}

void HAcGiSubEntityTraits::setLineWeight(const AcDb::LineWeight lw)
{
	mLineWeight = lw;
}

void HAcGiSubEntityTraits::setLineTypeScale(double dScale)
{
	mLineTypeScale = dScale;
}

Adesk::UInt16 HAcGiSubEntityTraits::color() const
{
	return	 mColorIndex;
}

AcCmEntityColor HAcGiSubEntityTraits::trueColor() const
{
	return mTrueColor;
}

AcDbObjectId HAcGiSubEntityTraits::layerId() const
{
	return mLayerId;
}

AcDbObjectId HAcGiSubEntityTraits::lineTypeId() const
{
	return mLinetypeId;
}

AcGiFillType HAcGiSubEntityTraits::fillType() const
{
	return 	mFillType;
}

AcDb::LineWeight HAcGiSubEntityTraits::lineWeight() const
{
	return mLineWeight;
}

double HAcGiSubEntityTraits::lineTypeScale() const
{
	return mLineTypeScale;
}

void   HAcGiSubEntityTraits::setThickness(double dThickness)
{
	mThickness = dThickness;
}

double HAcGiSubEntityTraits::thickness() const
{
	return mThickness;
}

//  Implementation of HAcGiContext
ACRX_NO_CONS_DEFINE_MEMBERS(HAcGiContext,AcGiContext)
HAcGiContext::HAcGiContext()
{
}

HAcGiContext::~HAcGiContext()
{
}

Adesk::Boolean HAcGiContext::isPsOut() const
{
	return Adesk::kFalse;
}

Adesk::Boolean HAcGiContext::isPlotGeneration() const
{
	return Adesk::kFalse;
}

AcDbDatabase*  HAcGiContext::database() const
{
	return acdbHostApplicationServices()->workingDatabase();
}

bool HAcGiContext::isBoundaryClipping() const
{
	return false;
}

///////////////////////////////////////
//Implementation of CustomViewPortDraw class
HAcGiViewportDraw::HAcGiViewportDraw(HDWGImporter* pDWGImporter, AcDbEntity* pAcDbEntity)
: m_pDWGImporter(pDWGImporter), m_pAcDbEntity(pAcDbEntity) 
{
	mpVp 			  =	new HAcGiViewport();
	mpContext		  = new HAcGiContext;
	mpSubEntityTraits = new HAcGiSubEntityTraits;
	mpVpGeometry	  =	new HAcGiViewportGeometry(this);
	mRegenType		  = kAcGiHideOrShadeCommand;
}
HAcGiViewportDraw::~HAcGiViewportDraw()
{
	delete mpContext;
	delete mpSubEntityTraits;
	delete mpVpGeometry;
	delete mpVp;

}
HAcGiViewportGeometry::HAcGiViewportGeometry(HAcGiViewportDraw* pViewportDraw)
{
	//store a back pointer to worldDraw object that instantiates
	// this worldGeometry object.		Sumit k 18 mar 09
	m_pHAcgiViewportDraw = pViewportDraw;	
}
HAcGiViewportGeometry::~HAcGiViewportGeometry()
{

}
HAcGiViewport::HAcGiViewport()
{

}
HAcGiViewport::~HAcGiViewport()
{

}
AcGiViewport& HAcGiViewportDraw::viewport() const
{	
	return *mpVp;
}
AcGiViewportGeometry& HAcGiViewportDraw::geometry() const
{
	return *mpVpGeometry;
}
Adesk::UInt32 HAcGiViewportDraw::sequenceNumber() const
{
	return 0;
}
Adesk::Boolean  HAcGiViewportDraw::isValidId(const Adesk::ULongPtr acgiId) const
{
	return Adesk::kFalse;
}
AcDbObjectId   HAcGiViewportDraw::viewportObjectId() const
{
	return mpObjId;
}
AcGiRegenType HAcGiViewportDraw::regenType() const
{
	return	mRegenType;
}
AcGiSubEntityTraits& HAcGiViewportDraw::subEntityTraits() const
{
	return *mpSubEntityTraits;
}
AcGiGeometry *	HAcGiViewportDraw::rawGeometry() const
{
	return mpVpGeometry;
}
AcGiContext *  HAcGiViewportDraw::context()
{
	return mpContext;
}
HDWGImporter* HAcGiViewportDraw::GetHDWGImporter() const
{
	return m_pDWGImporter;
}

AcDbEntity* HAcGiViewportDraw::GetCurrentEntity() const
{
	return m_pAcDbEntity;
}


////Implementation of CustomViewPortGeometry class --- SumitK - 17 mar 09
Adesk::Boolean  HAcGiViewportGeometry::polylineEye(const Adesk::UInt32 nbPoints,
                                const AcGePoint3d* pPoints) const
{
	return m_pHAcgiViewportDraw->GetHDWGImporter()->import_polygon(nbPoints, pPoints, 
													m_pHAcgiViewportDraw->GetCurrentEntity());
};
Adesk::Boolean  HAcGiViewportGeometry::polygonEye(const Adesk::UInt32 nbPoints,
                                const AcGePoint3d* pPoints) const 
{
	return m_pHAcgiViewportDraw->GetHDWGImporter()->import_polygon(nbPoints, pPoints, 
													m_pHAcgiViewportDraw->GetCurrentEntity());
};
Adesk::Boolean  HAcGiViewportGeometry::polylineDc(const Adesk::UInt32 nbPoints,
                                const AcGePoint3d* pPoints) const
{
	return m_pHAcgiViewportDraw->GetHDWGImporter()->import_polygon(nbPoints, pPoints, 
													m_pHAcgiViewportDraw->GetCurrentEntity());
};
Adesk::Boolean  HAcGiViewportGeometry::polygonDc(const Adesk::UInt32 nbPoints,
                                const AcGePoint3d* pPoints) const 
{
	return m_pHAcgiViewportDraw->GetHDWGImporter()->import_polygon(nbPoints, pPoints, 
													m_pHAcgiViewportDraw->GetCurrentEntity());
};
Adesk::Boolean  HAcGiViewportGeometry::rasterImageDc(
                const AcGePoint3d& origin,
                const AcGeVector3d& u,
                const AcGeVector3d& v,
                const AcGeMatrix2d& pixelToDc,
                AcDbObjectId entityId,
                AcGiImageOrg imageOrg,
                Adesk::UInt32 imageWidth,
                Adesk::UInt32 imageHeight,
                Adesk::Int16 imageColorDepth,
                Adesk::Boolean transparency,
                ImageSource source,
                const AcGeVector3d& unrotatedU,
                const AcGiImageOrg origionalImageOrg,
                const AcGeMatrix2d& unrotatedPixelToDc,
                const Adesk::UInt32 unrotatedImageWidth,
                const Adesk::UInt32 unrotatedImageHeight
				) const {return Adesk::kFalse;};

Adesk::Boolean  HAcGiViewportGeometry::ownerDrawDc(
                long                       vpnumber, 
                long                       left, 
                long                       top, 
                long                       right, 
                long                       bottom, 
                const OwnerDraw*           pOwnerDraw
                ) const {return Adesk::kFalse;};

Adesk::Boolean  HAcGiViewportGeometry::ownerDraw3d(
                AcGePoint3d&               minBounds,
                AcGePoint3d&               maxBounds,
                OwnerDraw3d*               pOwnerDraw
                ) const  { return Adesk::kFalse; };
	void HAcGiViewportGeometry::getModelToWorldTransform(AcGeMatrix3d&) const {return;};
    void HAcGiViewportGeometry::getWorldToModelTransform(AcGeMatrix3d&) const {return;};

	Adesk::Boolean HAcGiViewportGeometry::pushModelTransform(const AcGeVector3d & vNormal) {return Adesk::kFalse;};// Uses arbitrary Axis algorythm
    Adesk::Boolean HAcGiViewportGeometry::pushModelTransform(const AcGeMatrix3d & xMat) {return Adesk::kFalse;};
    Adesk::Boolean HAcGiViewportGeometry::popModelTransform() {return Adesk::kFalse;};
	//TODO: Write detail Definition - SumitK[01/06/09]
	AcGeMatrix3d HAcGiViewportGeometry::pushPositionTransform (AcGiPositionTransformBehavior behavior, const AcGePoint3d& offset){AcGeMatrix3d mat3d; return mat3d.setToIdentity();}
	AcGeMatrix3d HAcGiViewportGeometry::pushPositionTransform (AcGiPositionTransformBehavior behavior, const AcGePoint2d& offset){AcGeMatrix3d mat3d; return mat3d.setToIdentity();}
	AcGeMatrix3d HAcGiViewportGeometry::pushScaleTransform (AcGiScaleTransformBehavior behavior, const AcGePoint3d& extents) {AcGeMatrix3d mat3d; return mat3d.setToIdentity();} 
	AcGeMatrix3d HAcGiViewportGeometry::pushScaleTransform (AcGiScaleTransformBehavior behavior, const AcGePoint2d& extents){AcGeMatrix3d mat3d; return mat3d.setToIdentity();} 
	AcGeMatrix3d HAcGiViewportGeometry::pushOrientationTransform (AcGiOrientationTransformBehavior behavior) {AcGeMatrix3d mat3d; return mat3d.setToIdentity();}



    // For drawing various primitives.
    //
    Adesk::Boolean  HAcGiViewportGeometry::circle(const AcGePoint3d& center,
                                   const double radius,
                                   const AcGeVector3d& normal) const 
	{
		return m_pHAcgiViewportDraw->GetHDWGImporter()->import_circle(center, radius, normal, 
													m_pHAcgiViewportDraw->GetCurrentEntity());
	};

    Adesk::Boolean  HAcGiViewportGeometry::circle(const AcGePoint3d& pt1, const AcGePoint3d& pt2,
                                   const AcGePoint3d& pt3) const 
	{
		return m_pHAcgiViewportDraw->GetHDWGImporter()->import_circle(pt1, pt2, pt3, 
													m_pHAcgiViewportDraw->GetCurrentEntity());

	};

    Adesk::Boolean  HAcGiViewportGeometry::circularArc(const AcGePoint3d& center,
                                   const double radius,
                                   const AcGeVector3d& normal,
                                   const AcGeVector3d& startVector,
                                   const double sweepAngle,
                                   const AcGiArcType arcType) const 
	{
		return m_pHAcgiViewportDraw->GetHDWGImporter()->import_circular_arc(	
												center, radius, normal, 
												startVector, sweepAngle, arcType, 
												m_pHAcgiViewportDraw->GetCurrentEntity() );
	};

    Adesk::Boolean  HAcGiViewportGeometry::circularArc(const AcGePoint3d& start,
                                   const AcGePoint3d& point,
                                   const AcGePoint3d& end,
                                   const AcGiArcType arcType ) const 
	{
		return m_pHAcgiViewportDraw->GetHDWGImporter()->import_circular_arc(
																start, point, 
																end, arcType, 
																m_pHAcgiViewportDraw->GetCurrentEntity());
	};
      
    Adesk::Boolean  HAcGiViewportGeometry::polyline(const Adesk::UInt32 nbPoints,
                                   const AcGePoint3d* pVertexList,
                                   const AcGeVector3d* pNormal,
                                   Adesk::LongPtr lBaseSubEntMarker) const 
	{
		return m_pHAcgiViewportDraw->GetHDWGImporter()->import_polyline( 
														nbPoints, pVertexList,
														pNormal, lBaseSubEntMarker, 
														m_pHAcgiViewportDraw->GetCurrentEntity());
	};
      
	//TODO : Write detail definition -SumitK[01/06/09]
	/*Adesk::Boolean  HAcGiViewportGeometry::polyPolygon(const Adesk::UInt32 numPolygonIndices,
									const Adesk::UInt32* numPolygonPositions,
									const AcGePoint3d* polygonPositions,
									const Adesk::UInt32* numPolygonPoints,
									const AcGePoint3d* polygonPoints,
									const AcCmEntityColor* outlineColors = NULL,
									const AcGiLineType* outlineTypes = NULL,
									const AcCmEntityColor* fillColors = NULL,
									const AcCmTransparency* fillOpacities = NULL) const  {return Adesk::kTrue;}
	Adesk::Boolean  HAcGiViewportGeometry::polyline(const AcGiPolyline& polylineObj) const {return Adesk::kTrue;}

    Adesk::Boolean  HAcGiViewportGeometry::polyPolyline (Adesk::UInt32 nbPolylines,
                                          const AcGiPolyline* pPolylines) const {return Adesk::kTrue;}
	Adesk::Boolean  HAcGiViewportGeometry::image(const AcGiImageBGRA32& imageSource,
						  const AcGePoint3d& position,
						  const AcGeVector3d& u, //orientation and magnitude of width
						  const AcGeVector3d& v, //orientation and magnitude of height
						  TransparencyMode transparencyMode = kTransparency8Bit
						  ) const {return Adesk::kTrue;}
	Adesk::Boolean  HAcGiViewportGeometry::rowOfDots(int count,
								  const AcGePoint3d&     start,
								  const AcGeVector3d&     step
								 ) const {return Adesk::kTrue;}
	Adesk::Boolean  HAcGiViewportGeometry::ellipticalArc(const AcGePoint3d&         center,
									  const AcGeVector3d&        normal,
									  double                     majorAxisLength,
									  double                     minorAxisLength,
									  double                     startDegreeInRads,
									  double                     endDegreeInRads,
									  double                     tiltDegreeInRads,
									  AcGiArcType                arcType = kAcGiArcSimple
									  ) const {return Adesk::kTrue;}

	*/
      
    Adesk::Boolean  HAcGiViewportGeometry::polygon(const Adesk::UInt32 nbPoints,
                                   const AcGePoint3d* pVertexList) const 
	{
		return m_pHAcgiViewportDraw->GetHDWGImporter()->import_polygon(nbPoints, pVertexList, 
													m_pHAcgiViewportDraw->GetCurrentEntity());
	};

    Adesk::Boolean  HAcGiViewportGeometry::mesh(const Adesk::UInt32 rows,
                                 const Adesk::UInt32 columns,
                                 const AcGePoint3d* pVertexList,
                                 const AcGiEdgeData* pEdgeData,
                                 const AcGiFaceData* pFaceData,
                                 const AcGiVertexData* pVertexData,
                                 const bool bAutoGenerateNormals
                                 ) const 
	{
		return m_pHAcgiViewportDraw->GetHDWGImporter()->import_mesh(rows, columns, pVertexList,
															 pEdgeData, pFaceData, pVertexData,
															 bAutoGenerateNormals, 
															 m_pHAcgiViewportDraw->GetCurrentEntity());
	};

    Adesk::Boolean  HAcGiViewportGeometry::shell(const Adesk::UInt32 nbVertex,
                                 const AcGePoint3d* pVertexList,
                                 const Adesk::UInt32 faceListSize,
                                 const Adesk::Int32* pFaceList,
                                 const AcGiEdgeData* pEdgeData,
                                 const AcGiFaceData* pFaceDataL,
                                 const AcGiVertexData* pVertexData,
                                 const struct resbuf* pResBuf ,
                                 const bool bAutoGenerateNormals
                                 ) const 
	{
		return m_pHAcgiViewportDraw->GetHDWGImporter()->import_shell( nbVertex, pVertexList,
															faceListSize, pFaceList,
															pEdgeData, pFaceDataL,
															pVertexData, pResBuf, bAutoGenerateNormals, 
															m_pHAcgiViewportDraw->GetCurrentEntity());
	};
      
    Adesk::Boolean  HAcGiViewportGeometry::text(const AcGePoint3d& position,
                                 const AcGeVector3d& normal,
                                 const AcGeVector3d& direction,
                                 const double height,
                                 const double width,
                                 const double oblique,
                                 const ACHAR* pMsg) const 
	{
	// ALERT: RealDWG docs misguides on the pMsg. Here's what it says
	// A copy of the text string is used in pMsg, so the calling application is responsible for the memory of the string passed in.
	// DO NOT delete pMsg - you will get an assertion bomb thrown - Rajesh B (20-Feb-08)

		return m_pHAcgiViewportDraw->GetHDWGImporter()->import_text(position, normal, direction,
															height, width, oblique, pMsg, 
															m_pHAcgiViewportDraw->GetCurrentEntity());
	};

    Adesk::Boolean  HAcGiViewportGeometry::text(const AcGePoint3d& position,
                                 const AcGeVector3d& normal,
                                 const AcGeVector3d& direction,
                                 const ACHAR* pMsg,
                                 const Adesk::Int32 length,
                                 const Adesk::Boolean raw,
                                 const AcGiTextStyle &pTextStyle
                                 ) const 
	{
		// ALERT: RealDWG docs misguides on the pMsg. Here's what it says
		// A copy of the text string is used in pMsg, so the calling application is responsible for the memory of the string passed in.
		// DO NOT delete pMsg - you will get an assertion bomb thrown - Rajesh B (20-Feb-08)

		return m_pHAcgiViewportDraw->GetHDWGImporter()->import_text(position, normal, direction,
														pMsg, length, raw, pTextStyle, 
														m_pHAcgiViewportDraw->GetCurrentEntity());
	};

    Adesk::Boolean  HAcGiViewportGeometry::xline(const AcGePoint3d&,
                                  const AcGePoint3d&) const {return Adesk::kFalse;};

    Adesk::Boolean  HAcGiViewportGeometry::ray(const AcGePoint3d&,
                                const AcGePoint3d&) const {return Adesk::kFalse;};

    Adesk::Boolean  HAcGiViewportGeometry::pline(const AcDbPolyline& lwBuf,
                                  Adesk::UInt32 fromIndex,
                                  Adesk::UInt32 numSegs
                                  ) const 
	{
		return m_pHAcgiViewportDraw->GetHDWGImporter()->import_pline(lwBuf, fromIndex, numSegs, 
														m_pHAcgiViewportDraw->GetCurrentEntity());
	};

    Adesk::Boolean  HAcGiViewportGeometry::draw(AcGiDrawable*) const {return Adesk::kFalse;};

    Adesk::Boolean  HAcGiViewportGeometry::pushClipBoundary(AcGiClipBoundary * pBoundary) {return Adesk::kFalse;};
	void HAcGiViewportGeometry::popClipBoundary() {return;};



	///////////// Custom ViewportDraw class implemetation SumitK 18 mar 09


	void HAcGiViewport::getModelToEyeTransform(AcGeMatrix3d&) const {return;};
	void HAcGiViewport::getEyeToModelTransform(AcGeMatrix3d&) const {return;};
	void HAcGiViewport::getWorldToEyeTransform(AcGeMatrix3d&) const {return;};
	void HAcGiViewport::getEyeToWorldTransform(AcGeMatrix3d&) const {return;};

	Adesk::Boolean HAcGiViewport::isPerspective() const { return Adesk::kFalse; };
	Adesk::Boolean HAcGiViewport::doPerspective(AcGePoint3d&) const { return Adesk::kFalse; };
	Adesk::Boolean HAcGiViewport::doInversePerspective(AcGePoint3d&) const { return Adesk::kFalse; };

	void HAcGiViewport::getNumPixelsInUnitSquare(const AcGePoint3d& givenWorldpt,
							  AcGePoint2d& pixelArea,
							  bool includePerspective) const { return ; };

	void HAcGiViewport::getCameraLocation(AcGePoint3d& location) const {return;};
	void HAcGiViewport::getCameraTarget(AcGePoint3d& target) const {return;};
	void HAcGiViewport::getCameraUpVector(AcGeVector3d& upVector) const {return;};

	Adesk::ULongPtr HAcGiViewport::viewportId() const { return Adesk::kFalse; };
	Adesk::Int16  HAcGiViewport::acadWindowId() const { return Adesk::kFalse; };
	void HAcGiViewport::getViewportDcCorners(AcGePoint2d& lower_left,
								  AcGePoint2d& upper_right) const {return;};

	Adesk::Boolean HAcGiViewport::getFrontAndBackClipValues(Adesk::Boolean& clip_front,
									 Adesk::Boolean& clip_back,
									 double& front,
									 double& back) const { return Adesk::kFalse; };
	double HAcGiViewport::linetypeScaleMultiplier() const {return 0.0;};
	double HAcGiViewport::linetypeGenerationCriteria() const {return 0.0;};


/////////////////// Macros to define the declared members(using ACRX_DECLARE_MEMBERS IN .H) of the base class.///////
/////////////////	Removing will cause linker erros. SK 18 mar 09  //////////////////////////////////////////////////
ACRX_DEFINE_MEMBERS(HAcGiViewportDraw);
ACRX_DEFINE_MEMBERS(HAcGiViewportGeometry);
ACRX_DEFINE_MEMBERS(HAcGiViewport);

#if 0
void HDWGImporter::importAcDbDictionary(AcDbDictionary *pDictionary)
{
	AcDbDictionaryIterator *pIter;
	AcDbObject *pObj;
	pIter = pDictionary->newIterator();

	while (!pIter->done())
	{
		//_print(L"        %s\n"), pIter->name() ? pIter->name() : L"???") );
		if (pIter->getObject(pObj, AcDb::kForRead) == Acad::eOk)
		{
			if( pObj->isA() == AcDbMaterial::desc() )
				importAcDbMaterial((AcDbMaterial*)pObj);
			pObj->close();
		}
		pIter->next();
	}
	delete pIter;
}
#endif 

// Functions to condition strings form database to be used as segment name.

static inline wchar_t* StringToHex(wchar_t data)
{
wchar_t tmp[64];
wchar_t* hex = new wchar_t[6]; 
hex[0] = L'';
int value = (int)(data);
swprintf(tmp,L"%x",value);
wcscat(hex,tmp);
wchar_t* ret = _wcsdup(hex);
H_SAFE_DELETE_ARRAY(hex);
return ret;
}

//void condition_string_for_segment_name(char* zString)
//{
//	char* pIn = (char*)zString;
//
//	while (*pIn != 0)
//	{
//		if (*pIn == ',')
//			*pIn = ' ';
//		else if (*pIn == '\'')
//			*pIn = ' ';
//		else if (*pIn == '\"')
//			*pIn = ' ';
//		else if (*pIn == '/')
//			*pIn = ' ';
//		else if (*pIn == '*')
//			*pIn = ' ';
//		else if (*pIn == '~')
//			*pIn = ' ';
//		else if (*pIn == '|')
//			*pIn = ' ';
//		else if (*pIn == '(')
//			*pIn = ' ';
//		else if (*pIn == ')')
//			*pIn = ' ';
//		
//		pIn++;
//	}
//}

// Looks for special characters and replaces them with space.
// As well as Unicode characters are replaced
// their equivalent Hexadecimal values. This is done because hoops does not support
// Unicode characters in segment names. This cures - issue 9112 // ASHISH.S. 14/04/2009
//void condition_string_for_segment_name(wchar_t* zString)
//{
//	bool isUnichar = false;
//	bool isSpecialChar = false;
//	wchar_t pIn[MVO_BUFFER_SIZE] = L"";
//	int i = 0, j = 0;
//	while (zString[i] != 0)
//	{
//		switch(zString[i])
//		{
//			case ',':
//			case '\'':
//			case '\"':
//			case '/':
//			case '*':
//			case '~':
//			case '|':
//			case '!':
//			case '=':
//			case ')':
//			case '(':
//			case '`':
//			case '@':
//			isSpecialChar = true;
//			break;
//
//			default:
//				{
//				if(zString[i]>127 && zString[i]<=255)
//					isSpecialChar = true;
//				else if(zString[i] > 255)
//					isUnichar = true;
//				}
//				break;
//		}
//
//		if(isSpecialChar)
//		{
//			pIn[j++] = L' ';
//		}
//		else if(isUnichar)
//		{
//			wchar_t * temp = StringToHex(zString[i]);
//			SIZE_T count = wcslen(temp);
//			wcscat(pIn, temp);
//			j = j+count;
//		}
//		else
//		{
//			pIn[j++] = zString[i];
//		}
//		
//
//		isUnichar = false;
//		isSpecialChar = false;
//		i++;
//	}
//	
//	swprintf(zString,L"%s",pIn);
//}

void condition_string_for_segment_name(char* zString)
{
	int i = 0;
	int j = 0;

	bool isSpecialChar = false;
	char pIn[MVO_BUFFER_SIZE] = "";
	while (zString[j] != 0)
	{
		switch(zString[j])
		{
			case ',':
			case '\'':
			case '\"':
			case '/':
			case '*':
			case '~':
			case '|':
			case '!':
			case '=':
			case ')':
			case '(':
			case '`':
			case '@':
				
				isSpecialChar = true;
				break;
		}

		if(!isSpecialChar)
		{
           pIn[i] = zString[j];
		   i++;
		}
		j++;
		isSpecialChar = false;
	}		
	sprintf(zString,"%s",pIn);
}

void condition_string_for_segment_name(wchar_t* zString)
{
	
	int i = 0;
	int j = 0;

	bool isSpecialChar = false;
	bool isUnichar = false;
	wchar_t pIn[MVO_BUFFER_SIZE] = L"";
	while (zString[j] != 0)
	{
		switch(zString[j])
		{
			case ',':
			case '\'':
			case '\"':
			case '/':
			case '*':
			case '~':
			case '|':
			case '!':
			case '=':
			case ')':
			case '(':
			case '`':
			case '@':				
				isSpecialChar = true;
				break;

			default:
			{
				if(zString[i]>127 && zString[i]<=255)
					isSpecialChar = true;
				else if(zString[i] > 255)
					isUnichar = true;
			}
		}

		if(isUnichar)
		{
			wchar_t * temp = StringToHex(zString[j]);
			SIZE_T count = wcslen(temp);
			wcscat(pIn, temp);
			i = i + count;
		}
		else if(!isSpecialChar)
		{
           pIn[i] = zString[j];
		   i++;
		}		 
		j++;
		isSpecialChar = false;
		isUnichar = false;
	}		
	swprintf(zString,L"%s",pIn);
	
	//else do nothing
	
}

//void condition_string_for_user_options(char* zString)
//{
//	char* pIn = (char*)zString;
//
//	while (*pIn != 0)
//	{
//		if (*pIn == '\'')
//			*pIn = ' ';
//		else if (*pIn == '\"')
//			*pIn = ' ';
//		else if (*pIn == '/')
//			*pIn = ' ';
//		pIn++;
//	}
//}
//
//void condition_string_for_user_options(wchar_t* zString)
//{
//	wchar_t* pIn = (wchar_t*)zString;
//
//	while (*pIn != 0)
//	{
//		if (*pIn == L'\'')
//			*pIn = L' ';
//		else if (*pIn == L'\"')
//			*pIn = L' ';
//		else if (*pIn == L'/')
//			*pIn = L' ';
//		pIn++;
//	}
//}

void condition_string_for_user_options(char* zString)
{
	int i = 0;
	int j = 0;

	bool isSpecialChar = false;
	while (zString[j] != 0)
	{
		switch(zString[j])
		{
			case ',':
			case '\'':
			case '\"':
			case '/':
			case '*':
			case '~':
			case '|':
			case '!':
			case '=':
			case ')':
			case '(':
			case '`':
			case '@':		
				
				isSpecialChar = true;
				break;
		}

		if(isSpecialChar)
			break; // if there is only one special character, that's enough
		j++;
	}

	if(isSpecialChar)
	{
		i = 0;
		j = 0;		
		char pIn[MVO_BUFFER_SIZE] = "";
		pIn[i++] = '`';
		while (zString[j] != 0)
		{	
			pIn[i++] = zString[j];	
			j++;
		}
		pIn[i++] = '`';
		sprintf(zString,"%s",pIn);
	}
	//else do nothing


}

void condition_string_for_user_options(wchar_t* zString)
{
		int i = 0;
	int j = 0;

	bool isSpecialChar = false;
	while (zString[j] != 0)
	{
		switch(zString[j])
		{
			case ',':
			case '\'':
			case '\"':
			case '/':
			case '*':
			case '~':
			case '|':
			case '!':
			case '=':
			case ')':
			case '(':
			case '`':
			case '@':
				
				isSpecialChar = true;
				break;
		}

		if(isSpecialChar)
			break; // if there is only one special character, that's enough
		j++;
	}

	if(isSpecialChar)
	{
		i = 0;
		j = 0;		
		wchar_t pIn[MVO_BUFFER_SIZE] = L"";
		pIn[i++] = '`';
		while (zString[j] != 0)
		{	
			pIn[i++] = zString[j];	
			j++;
		}
		pIn[i++] = '`';
		swprintf(zString,L"%s",pIn);
	}
	//else do nothing
	
}





// Check for special chars like degree, diameter symbols, and replace
// with equivalent ascii values.
void condition_string_for_special_characters(wchar_t* zString)
{
	size_t str_len = wcslen(zString);
	//wchar_t pIn[MVO_BUFFER_SIZE] = L"";
	wchar_t* pIn = new wchar_t[str_len + 1];
	wcscpy(pIn, L"");

	size_t i=0,j=0;
	while (i < str_len)
	{
		if(zString[i]==L'%'&& zString[i+1]==L'%')
		{
			if(zString[i+2]==L'd' || zString[i+2]==L'D')
			{
				pIn[j]=186;
				i=i+2;
			}
			else if(zString[i+2]==L'p' || zString[i+2]==L'P')
			{
				pIn[j]=177;
				i=i+2;
			}
			else if(zString[i+2]==L'c' || zString[i+2]==L'C')
			{
				pIn[j]=216;
				i=i+2;
			}
			else if(zString[i+2]==L'u' || zString[i+2]==L'U')
			{
				// underlined, not handled yet
				j--;
				i=i+2;
			}
			else if(zString[i+2]==L'%')
			{
				pIn[j]=L'%';
				i=i+2;
			} 
			
			else 
			{
				int ctr=0;
				int digit=0; 
				while(ctr<3)
				{
					if(47<(int)zString[i+2+ctr]&&(int)zString[i+2+ctr]<58)
						digit++;
					ctr++;

				}
				if(digit==3)
				{     
					int no=((int)zString[i+2]-48)*100+((int)zString[i+3]-48)*10+((int)zString[i+4]-48);    
					pIn[j]=no;
					i=i+4;
				}
			}

		} 
		else
		{
			if(zString[i]!=L'%')
				pIn[j]=zString[i];
		}
		i++;
		j++;
	} 
	pIn[j] = L'\0';
	swprintf(zString,L"%s",pIn);
	delete [] pIn;
}
// Convert to lower case
void ConverToLower(char * to_lower)
{
	int i = 0;

	for(i = 0; i < (int)strlen(to_lower); i++)
	{
		to_lower[i] = tolower(to_lower[i]);
	}
	to_lower[i] = '\0';
}

bool hio_dwg_check_file_exist(const wchar_t * full_filepath)
{
    FILE* fp;
    fp = wfopen(full_filepath,L"r");
    if(fp!=NULL)
    {
        fclose(fp);
        return true;
    }
    else
    {
        return false;
    }
}

// Draw order methods
int HDrawOrderHandler::Open()
{
	// there was too many lines here for getting AcDbSortentsTable, this got reduced after getting ADN's response on 1252004 (ADN issue No.)
	// and 10651 (ts3d support log).
	Acad::ErrorStatus es = m_pRecord->getSortentsTable(m_pObj, AcDb::kForRead);

	if(es == Acad::eOk)
	{
		//debug
		m_pObj->getFullDrawOrder(objArray);
		//debug
		return 1;
	}

	AcDbObjectId owner_id = m_pRecord->id();
	AcDbObjectId ext_id = m_pRecord->extensionDictionary();
	if(AcDbObjectId::kNull == ext_id)
	{
		return 0;
	}

	AcDbDictionary *pExt;
	AcDbObject * pObj;
	es = acdbOpenObject( pExt, ext_id, AcDb::kForRead );
	if (Acad::eOk != es)
		return 0;

	if (Acad::eOk != pExt->getAt( L"ACAD_SORTENTS", pObj, AcDb::kForRead ))
	{
		if (Acad::eOk != pExt->upgradeOpen())
		{
			pExt->close();
			return 0;
		}
		AcDbSortentsTable *pSt = new AcDbSortentsTable;
		if (NULL == pSt)
		{
			pExt->close();
			return 0;
		}

		AcDbObjectId new_id;
		if (Acad::eOk != pExt->setAt( L"ACAD_SORTENTS", pSt, new_id ))
		{
			delete pSt;
			pExt->close();
			return 0;
		}
		pSt->setBlockId( owner_id );
		pObj = pSt;
	}

	pExt->close();

	if (!pObj->isKindOf( AcDbSortentsTable::desc() ))
	{
		pObj->close();
		pObj = NULL;
		return 0;
	}
	m_pObj = (AcDbSortentsTable *)pObj;
	
	// debug
	m_pObj->getFullDrawOrder(objArray);
	// debug

	return 1;
}

int HDrawOrderHandler::GetDrawOrder(AcDbEntity *pEnt)
{
	if(m_pObj == NULL)
		return -1;
	else
	{
		//AcDbHandle draw_order_handle;

		//m_pObj->getSortHandle(pEnt->objectId(), draw_order_handle);
		//int draw_order = draw_order_handle.low();

		int draw_order = 0;
		draw_order = objArray.find(pEnt->id());
		return draw_order;
	}
}
void HDrawOrderHandler::Close()
{
	if(m_pObj != NULL)
		m_pObj->close();
}

int HDrawOrderHandler::CheckDrawOrderAndSetVisibility(AcDbEntity *pEnt, HC_KEY block_key, HDWG_3dgsImporter * importer)
{
	// Draw order settings starts
	// Look for draw order if not asked to ignore them. 
	char entity_segment_name[MVO_BUFFER_SIZE]="";
	
	if(	pEnt->isA() != AcDbBlockReference::desc() && pEnt->isA() != AcDbMInsertBlock::desc() 
		&& pEnt->isA() != AcDbAttributeDefinition::desc())
	{
	
		// To set the draw order for each entity segment
		int drawOrder = this->GetDrawOrder(pEnt);
		if(drawOrder >= 0)
		{
			drawOrder = drawOrder +1;
			sprintf(entity_segment_name, "entity_%p", pEnt);
			// debug
			float depth_range = 0.0;
			char depthRange_opts[128] = "";
			depth_range = 1.0/(float)drawOrder;


			sprintf(depthRange_opts,"depth range = (%f,1.0)", depth_range );

			HC_Open_Segment_By_Key(block_key);
			{
				//HC_QSet_Priority(entity_segment_name, drawOrder);
				HC_Open_Segment(entity_segment_name);
				{
					HC_Set_Rendering_Options(depthRange_opts);
				}
				HC_Close_Segment();
			}
			HC_Close_Segment();
		}

	}
	// Draw order settings ends
	return 1;
}

int HDrawOrderHandler::CheckDrawOrderAndSetVisibility(AcDbEntity *pEnt, TK_Open_Segment * include_seg_handler, HDWG_BStreamImporter * importer)
{
	// Draw order settings starts
	// Look for draw order if not asked to ignore them. 
	char entity_segment_name[MVO_BUFFER_SIZE]="";

	if(	pEnt->isA() != AcDbBlockReference::desc() && pEnt->isA() != AcDbMInsertBlock::desc() 
		&& pEnt->isA() != AcDbAttributeDefinition::desc())
	{

		// To set the draw order for each entity segment
		int drawOrder = this->GetDrawOrder(pEnt);
		if(drawOrder >= 0)
		{
			drawOrder = drawOrder + 1;
			float depth_range = 1.0;
			depth_range = 1.0/(float)drawOrder;


			sprintf(entity_segment_name, "entity_%p", pEnt);

			importer->STREAM_Open_Segment(include_seg_handler->GetSegment());
			{
				importer->STREAM_Open_Segment(entity_segment_name);
				{
					TK_Rendering_Options * rendering_handler = new TK_Rendering_Options;
					rendering_handler->SetMask(TKO_Rendo_Extended, TKO_Rendo_Depth_Range);
					rendering_handler->SetValue(TKO_Rendo_Extended, TKO_Rendo_Depth_Range);
					rendering_handler->SetDepthRange(depth_range,1.0);
					importer->STREAM_Write_Object((BBaseOpcodeHandler *)rendering_handler);
				}
				importer->STREAM_Close_Segment();
			}
			importer->STREAM_Close_Segment();
		}

	}
	return 1;
}

void Get_Image_Rectangle_For_Shell(AcDbRasterImage* pEnt, HPoint * Rect)
{
	AcGePoint3d     insertion;
	AcGeVector3d    u, v;

	pEnt->getOrientation(insertion, u, v);

	double width_Rect = u.length();
	double height_Rect = v.length();
	HPoint insertionPt(insertion.x,insertion.y, insertion.z);

	double angle = u.angleTo(AcGeVector3d::kXAxis);

	//// this is to get 360 degrees angle.
    AcGeVector3d cross_prod;
    cross_prod = AcGeVector3d::kXAxis.crossProduct(u);
	if(cross_prod.z < 0.0)
		angle = 2*HUtility::PI - angle;

	Rect[0].x = 0;
	Rect[0].y = 0;
	Rect[0].z = 0;

	Rect[1].x = width_Rect; 
	Rect[1].y = 0;
	Rect[1].z = 0;

	Rect[2].x = width_Rect;
	Rect[2].y = height_Rect;
	Rect[2].z = 0;

	Rect[3].x = 0;
	Rect[3].y = height_Rect;
	Rect[3].z = 0;

	float Matrix[16];
	// Rotate
	double degrees = angle*180/HUtility::PI;
	HC_Compute_Rotation_Matrix(0.0,0.0,degrees, Matrix);
	HC_Compute_Transformed_Points(4, Rect, Matrix, Rect);

	// Transform
	HC_Compute_Translation_Matrix(insertionPt.x, insertionPt.y, insertionPt.z, Matrix);
	HC_Compute_Transformed_Points(4, Rect, Matrix, Rect);

	return;
}
int GetImageFileName(AcDbRasterImageDef* ImageDef, char * pFilePath, char * pImageName) 
{

	 ACHAR FilePath[MVO_BUFFER_SIZE]= L"";
	 swprintf(FilePath,L"%s", ImageDef->activeFileName());

	 // Image name.
		TCHAR* ImageName = 0;
		AcDbObjectId dictId = AcDbRasterImageDef::imageDictionary(acdbHostApplicationServices()->workingDatabase());
		if (dictId.asOldId() != 0) {
			AcDbDictionary* pRasDict = 0;
			if (acdbOpenObject(pRasDict, dictId, AcDb::kForRead) == Acad::eOk) {
				pRasDict->nameAt(ImageDef->id(), ImageName);
				pRasDict->close();
			}
		}
	 if(!wcslen(FilePath))
	 {
		  swprintf(FilePath,L"%s", ImageDef->sourceFileName());
		  return 0;
	 }

	 sprintf(pImageName, "%s", H_ASCII_TEXT(ImageName));
	 sprintf(pFilePath, "%s", H_ASCII_TEXT(FilePath));

	 return 1;
}

void InsertClipRegion(AcDbRasterImage* pEnt, BStreamFileToolkit * pBStreamtk)
{
	if(pEnt->isClipped())
	{
		int length;
		AcGePoint3dArray vertices;
		pEnt->getVertices(vertices);
	
		length = vertices.length();
		HPoint * clipRegionPts = new HPoint[length];

		for ( int i=0; i<length; i++ )
		{
			clipRegionPts[i].Set(vertices.at(i).x, vertices.at(i).y, vertices.at(i).z);
		}

		if(!pBStreamtk)
		{
			HC_Set_Polygonal_Clip_Region(length,clipRegionPts,"world");
			//HC_Insert_Polyline(length, clipRegionPts);
		}
		else
		{
			TK_Clip_Region* clip = new TK_Clip_Region;
			clip->SetPoints(length, (float*)clipRegionPts);
			clip->SetOptions(1);	//// Set the option to 1(world):Its default value is 0(window)
			TK_Status hdwg_status = clip->Write(*pBStreamtk);
			H_ASSERT(hdwg_status == TK_Normal);
			delete clip;
		}
		delete [] clipRegionPts;
	}
}

int GetCameraForInitialView(HCamera &camera , AcDbViewportTableRecord* pRecord)
{
	AcGePoint3d  origin;
	AcGeVector3d xAxis;
	AcGeVector3d yAxis;
	double Twist = 0.0;

	Twist = pRecord->viewTwist();
	AcGePoint2d Center = pRecord->centerPoint();
	AcGePoint3d Target = pRecord->target();
	Target.set(Target.x+Center.x, Target.y+Center.y, Target.z);
	AcGeVector3d direction = pRecord->viewDirection();
	float front_distance = pRecord->frontClipDistance();
	
	// Most of the time following method gives correct camera position,
	// For some files it still doesn't work smooth.
	// For proper camera setting we need AcGsView, see ADN query - 1249967
	bool frontclipeye = pRecord->frontClipAtEye();
	AcGePoint3d Position;
	if(frontclipeye && front_distance)
		Position = Target + (direction *(- front_distance));
	else
	{
		// Since it is clear that RealDWG will not give accurate view parameters
		// to view all the geometry I am positioning camera farther based on empirical values.
		Position = Target + (direction * 1.0);
	}

	// Get up Vector.
	AcGeVector3d recordUpVect;

	if((direction.x == 0) && (direction.y == 0) )
	{
		recordUpVect = AcGeVector3d(0, 1.0, 0);
	}
	else 
	{
		AcGeVector3d viewCrossProd = direction.perpVector();
		recordUpVect = direction.crossProduct(viewCrossProd);

		recordUpVect = recordUpVect.normalize();
	}

	recordUpVect = recordUpVect.rotateBy(-Twist, direction);

	// Set for hoops camera
	camera.field_height = pRecord->height();
	camera.field_width = pRecord->width();

	camera.position.Set(Position.x, Position.y, Position.z);
	camera.target.Set(Target.x, Target.y, Target.z);
	camera.up_vector.Set(recordUpVect.x, recordUpVect.y, recordUpVect.z);

	if(pRecord->perspectiveEnabled())
		sprintf(camera.projection, "perspective");
	else
		sprintf(camera.projection, "orthographic");

	return 1;
}

void SetRenderMode(HInputHandlerOptions * pInputOptions, AcDbViewportTableRecord* pRecord)
{
	AcDbAbstractViewTableRecord::RenderMode rMode = pRecord->renderMode();
	switch(rMode)
	{
		case AcDbAbstractViewTableRecord::k2DOptimized:
		{
			//pInputOptions->m_pHBaseView->SetRenderMode(HRenderSilhouette);
			pInputOptions->m_pHBaseView->SetRenderMode(HRenderBRepWireframe);// Ashish
			break;
		}
		case AcDbAbstractViewTableRecord::kWireframe:
		{
			//pInputOptions->m_pHBaseView->SetRenderMode(HRenderWireframeWithSilhouette); 
			pInputOptions->m_pHBaseView->SetRenderMode(HRenderBRepWireframe);// Ashish
			break;
		}
		case AcDbAbstractViewTableRecord::kFlatShaded:
		case AcDbAbstractViewTableRecord::kFlatShadedWithWireframe: //In AutoCAD, its observed that line are always ON
		{
			pInputOptions->m_pHBaseView->SetRenderMode(HRenderShadedWireframe);
			break;
		}
		case AcDbAbstractViewTableRecord::kGouraudShaded:
		case AcDbAbstractViewTableRecord::kGouraudShadedWithWireframe:  //In AutoCAD, its observed that line are always ON
		{
			pInputOptions->m_pHBaseView->SetRenderMode(HRenderGouraudWithLines);
			break;
		}
		case AcDbAbstractViewTableRecord::kHiddenLine:
		{
			//pInputOptions->m_pHBaseView->SetRenderMode(HRenderHiddenLine);
			pInputOptions->m_pHBaseView->SetRenderMode(HRenderBRepHiddenLine); // Ashish
			break;
		}
		default:
		{
			pInputOptions->m_pHBaseView->SetRenderMode(HRenderGouraudWithLines);
			break;
		}
	}
}

void GetModelingMatrixForText(float my_center[], float my_path1[], float my_norm1[], float h_matrix_trans[])
{
	static AcGeVector3d old_normal_Z;
	static AcGeVector3d old_direction_X;

	// Here we are just considering the text as a coordinate system with diection as X axis, Normal as Z axis
    // and cross product of these two as Y axis. AcGeMatrix3d::alignCoordSys does rest of the job.
    // << ASHISH.S. 17/08/2009
    AcGeMatrix3d matrix_default_to_current;
    
    AcGeVector3d normal_Z(my_norm1[0], my_norm1[1], my_norm1[2]);
    AcGeVector3d direction_X(my_path1[0], my_path1[1], my_path1[2]);

	if(old_normal_Z == normal_Z && old_direction_X == direction_X)
	{
		// if direction and normal are same as last, no need to calculate by 
		// expensive matrix operations. Use last matrix and just set location.
		h_matrix_trans[12] = my_center[0];
		h_matrix_trans[13] = my_center[1];
		h_matrix_trans[14] = my_center[2];
	}
	else
	{
		// store this in old as we will refer this in next iteration
		old_normal_Z = normal_Z;
		old_direction_X = direction_X;

		// normalize before processing
		normal_Z.normalize();
		direction_X.normalize();

		AcGePoint3d Text_Location(my_center[0], my_center[1], my_center[2]); 
		AcGeVector3d crossProd_Y = normal_Z.crossProduct(direction_X);

		matrix_default_to_current = AcGeMatrix3d::alignCoordSys(AcGePoint3d::kOrigin, AcGeVector3d::kXAxis,
			AcGeVector3d::kYAxis, AcGeVector3d::kZAxis, Text_Location, direction_X, crossProd_Y, normal_Z);

		// store this in old as we will refer this in next iteration
		int k = 0;
		for(int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 4; j++)
			{
				h_matrix_trans[k] = (float)(matrix_default_to_current.entry[j][i]);
				k++;
			}
		}
	}
}

TK_Status WriteObject(BBaseOpcodeHandler * handler, BStreamFileToolkit * tk, FILE * fp,
							 char * buffer, int size) 
{
	TK_Status status;

	// ask the toolkit to write out the object; the toolkit will write out as much as
	// the current buffer can hold
	status = handler->Write(*tk);

	// if there is still more data left to write; we have to loop through 
	// generating and writing buffers of data until we're done
	while (status == TK_Pending) 
	{
		// due to compression, preparing a new buffer might immediately fill that buffer
		// so we need an extra check to possibly export that buffer and prepare a new buffer
		while (status == TK_Pending) 
		{
			// ask the toolkit how much of the buffer is currently filled
			// this will normally be the same as the buffer size that we passed in
			int count = tk->CurrentBufferLength();

			// write the current out to our file since this example deals with 
			// exporting a file; however, instead of writing to a file, the buffer of
			// data could be sent to an application data-structure, or transmitted
			// over a network ('streamed'), etc...
			fwrite(buffer, sizeof (char), count, fp);

			// tell the toolkit where it can resume writing data; in this case, we
			// can reuse the same buffer once we're done with it
			status = tk->PrepareBuffer(buffer, size);
		}

		// ask the toolkit to continue trying to write out the object's data
		status = handler->Write(*tk);
	}

	return status;
}

//returns a matrix and Hpoint array which is used to apply modelling matrix and clip region
//on MS Include segment while importing viewports in paper_space/layout. sumitk..(13/08/08)
void get_layout_data(AcDbObjectId viewPortId,AcDbDatabase *pAcDbDatabase,HPoint *ClipPoint,float *matrix,int *no_ClipPoint,AcCmEntityColor* entityColor, bool * is_On)
{
	AcGeMatrix3d ms2PsMat, resultMat;
	//Open up the viewport 
	AcDbObjectPointer<AcDbViewport> pVp (viewPortId, AcDb::kForRead);
	if(pVp.openStatus() != Acad::eOk)
	{
	return ;
	}
	AcDbBlockTableRecordPointer pMsRecord(ACDB_MODEL_SPACE, pAcDbDatabase, AcDb::kForRead,false);
	if(pMsRecord.openStatus() == Acad::eOk)
	{
		// first get all the data
		AcGeVector3d viewDirection = pVp->viewDirection();
		AcGePoint2d centre2d = pVp->viewCenter();
		AcGePoint3d viewCenter = AcGePoint3d( centre2d.x, centre2d.y, 0);

		AcGePoint3d viewTarget = pVp->viewTarget (); 
		double twistAngle = -pVp->twistAngle(); 
		AcGePoint3d centerPoint = pVp->centerPoint(); 
		double viewHeight = pVp->viewHeight();
		double height = pVp->height();
		double width = pVp->width();
		double scaling = viewHeight / height;
		double lensLength = pVp->lensLength();
		*is_On = pVp->isOn();

		//TODO////nonRectClipEntityId() function returns the ID of the clipping entity associated with a viewport. For a clipping entity to be valid,  
		//it must be contained in the same paperspace as the viewport entity and must be one of the following types of entities:
		/// AcDbCircle ,AcDbPolyline ,AcDb2dPolyline ,AcDb3dPolyline ,AcDbEllipse ,AcDbRegion ,AcDbSpline ,AcDbFace -SumitK(19/11/2008)////////
		AcDbEntity *pEnt;
		AcDbObjectId ClipEntityId = pVp->nonRectClipEntityId();
		*entityColor = pVp->entityColor();

		if(acdbOpenObject(pEnt, ClipEntityId, AcDb::kForRead) == Acad::eOk)
		{
			if(pEnt->isKindOf(AcDbCircle::desc()))
			{
				AcDbCircle * pAcDbCircle;
				if(acdbOpenObject(pAcDbCircle, ClipEntityId, AcDb::kForRead) == Acad::eOk)
				{
					double radius = pAcDbCircle->radius();
					*entityColor = pAcDbCircle->entityColor();
					HPoint center;
					AcGePoint3d centerPoint = pAcDbCircle->center();
					center.x  = (float)centerPoint.x;
					center.y  = (float)centerPoint.y;
					center.z  = (float)centerPoint.z;
					*no_ClipPoint = 32;
					//ClipPoint = (HPoint*)realloc(ClipPoint,*no_ClipPoint);
					//ClipPoint = new HPoint[32];
					//ClipPoint = (HPoint*)malloc(*no_ClipPoint*sizeof(HPoint));
					float start_angle = (0 * float(HDWG_PI/180));
					float end_angle = (360 * float(HDWG_PI/180));
					HUtilityGeometryCreation::GeneratePointsOnCircularArc (ClipPoint,center, radius, HUtility::XY, *no_ClipPoint, 0, start_angle, end_angle);				
					pAcDbCircle->close();
				}
			}
			else if(pEnt->isKindOf(AcDbPolyline::desc()))
			{
				AcDbPolyline* pPolyine;
				if(acdbOpenObject(pPolyine, ClipEntityId, AcDb::kForRead) == Acad::eOk)
				{
					int no_pts = pPolyine->numVerts();
					*entityColor = pPolyine->entityColor();
					*no_ClipPoint = no_pts;
					//ClipPoint = (HPoint*)realloc(ClipPoint,*no_ClipPoint);
					//ClipPoint = new HPoint[no_pts];
					//ClipPoint = (HPoint*)malloc(*no_ClipPoint*sizeof(HPoint));
					for(int i = 0 ; i < no_pts; i++)
					{
						AcGePoint3d point;
						pPolyine->getPointAt(i,point);
						ClipPoint[i].x = point.x;
						ClipPoint[i].y = point.y;
						ClipPoint[i].z = point.z;
					}
					pPolyine->close();
				}
			}
			pEnt->close();
		}
		else
		{
			*no_ClipPoint = 4;
			//ClipPoint = new HPoint[4];
			//ClipPoint = (HPoint*)malloc(*no_ClipPoint*sizeof(HPoint));
			ClipPoint[0].x = centerPoint.x - width/2;
			ClipPoint[0].y = centerPoint.y - height/2;
			ClipPoint[0].z = 0.0;
			ClipPoint[1].x = centerPoint.x + width/2;
			ClipPoint[1].y = centerPoint.y - height/2;
			ClipPoint[1].z = 0.0;
			ClipPoint[2].x = centerPoint.x + width/2;
			ClipPoint[2].y = centerPoint.y + height/2;
			ClipPoint[2].z = 0.0;
			ClipPoint[3].x = centerPoint.x - width/2;
			ClipPoint[3].y = centerPoint.y + height/2;
			ClipPoint[3].z = 0.0;
		}

		// prepare the transformation
		AcGeVector3d xAxis, yAxis, zAxis;
		zAxis = viewDirection.normal();
		xAxis = AcGeVector3d::kZAxis.crossProduct( viewDirection );

		if( !xAxis.isZeroLength() ) 
		{
			xAxis.normalize();
			yAxis = zAxis.crossProduct( xAxis );
		}
		else if( zAxis.z < 0 ) 
		{
			xAxis = -AcGeVector3d::kXAxis;
			yAxis = AcGeVector3d::kYAxis;
			zAxis = -AcGeVector3d::kZAxis;
		} 
		else 
		{
			xAxis = AcGeVector3d::kXAxis;
			yAxis = AcGeVector3d::kYAxis;
			zAxis = AcGeVector3d::kZAxis;
		}

		AcGeMatrix3d dcs2wcs; // display coordinate system (DCS) to world coordinate system (WCS)
		AcGeMatrix3d ps2Dcs; // paperspace to DCS


		// First initialise with a transformation to centerPoint
		ps2Dcs = AcGeMatrix3d::translation( AcGePoint3d::kOrigin - centerPoint);

		// then scale for the view
		ps2Dcs = ps2Dcs * AcGeMatrix3d::scaling( scaling, centerPoint); 

		// then adjust to the viewCenter
		dcs2wcs = AcGeMatrix3d::translation( viewCenter - AcGePoint3d::kOrigin);

		// Then transform for the view direction 
		AcGeMatrix3d matCoords;
		matCoords.setCoordSystem( AcGePoint3d::kOrigin, xAxis, yAxis, zAxis);

		dcs2wcs = matCoords * dcs2wcs;

		// Then adjust for the viewTarget
		dcs2wcs = AcGeMatrix3d::translation( viewTarget - AcGePoint3d::kOrigin) * dcs2wcs;

		// Then the twist angle
		dcs2wcs = AcGeMatrix3d::rotation(twistAngle, zAxis, viewTarget ) *dcs2wcs;

		AcGeMatrix3d perspMat;
		if( pVp->isPerspectiveOn()) 
		{
			// we do special perspective handling
			double viewSize = viewHeight; 
			double aspectRatio = width / height;

			double adjustFactor = 1.0 / 42.0;
			double adjustedLensLength = viewSize * lensLength * sqrt ( 1.0 +
				aspectRatio * aspectRatio ) * adjustFactor;

			double eyeDistance = viewDirection.length();
			double lensDistance = eyeDistance - adjustedLensLength;


			double ed = eyeDistance;
			double ll = adjustedLensLength;
			double l = lensDistance;


			perspMat.entry[2][2] = (ll - l ) / ll;
			perspMat.entry[2][3] = l * ( ed - ll ) / ll;
			perspMat.entry[3][2] = -1.0 / ll;
			perspMat.entry[3][3] = ed / ll;  
		}
		resultMat = ps2Dcs.inverse() * perspMat * dcs2wcs.inverse();
		int k = 0;
		for(int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 4; j++)
			{
				matrix[k] = (float)(resultMat.entry[j][i]);
				k++;
			}
		}
	}
}

// Get the boundary from a Block Reference.
// Transform that boundary to the WCS.
//-------------------------------------------------------------------
BOOL insertClip(AcDbBlockReference * ref, BStreamFileToolkit * pBStreamtk)
{
	// This method is replacing old insertclip after observations in 10527.
	// ADN has provided this method almost as is. ADN ID: TS82587 
	BOOL ret = FALSE;
	// Find the clipping object (AcDbSpatialFilter) in the ExtDict of the BlockRef

	AcDbObjectId extDicId = ref->extensionDictionary();

	if( extDicId == AcDbObjectId::kNull )
		return ret;

	AcDbDictionary *extDict=NULL, *acadFilterDict=NULL;

	if (acdbOpenObject(extDict, extDicId, AcDb::kForRead) != Acad::eOk)
		return ret;
	Acad::ErrorStatus err = extDict->getAt(L"ACAD_FILTER", (AcDbObject*&)acadFilterDict, AcDb::kForRead);
	extDict->close();

	if( err != Acad::eOk )
		return ret;

	AcDbSpatialFilter *filter=NULL;
	err = acadFilterDict->getAt(L"SPATIAL", (AcDbObject*&)filter, AcDb::kForRead);
	acadFilterDict->close();

	if ( err != Acad::eOk)
		return ret;

	// Get the transform matrix stored in the XClip boundary
	AcGeMatrix3d xformInBoundary = filter->getClipSpaceToWCSMatrix( xformInBoundary );
	// and the transform of the BlockRef at the time when the Filter was set
	AcGeMatrix3d xformRefOrig = filter->getOriginalInverseBlockXform( xformRefOrig );

	// Get the transform matrix that the current BlockRef has, so, we can find the difference
	//   with the xformRefOrig
	AcGeMatrix3d refMatrix = ref->blockTransform();
	refMatrix = refMatrix.postMultBy(xformRefOrig );

	// Calculate the final transform matrix which applies to the points
	// returned from filter->getDefinition().
	AcGeMatrix3d finalMatrix = refMatrix.postMultBy(xformInBoundary);

	AcGePoint2dArray pts;
	AcGePoint3dArray pts3d;
	AcGeVector3d normal;
	double elevation = 0, frontClip = 0, backClip = 0;
	Adesk::Boolean enabled  = false;

	// Get all boundary points
	if (filter->getDefinition(pts, normal, elevation, frontClip, backClip, enabled) == Acad::eOk)
	{
		// Rectanglar boundary
		if (pts.length() == 2)
		{
			AcGePoint2d p1(pts[1].x, pts[0].y);
			AcGePoint2d p3(pts[0].x, pts[1].y);
			pts.insertAt(1, p1);
			pts.insertAt(3, p3);
		}
		// Transform all points with the transform matrix we calculated
		for(int i=0; i<pts.length(); i++)
		{
			AcGePoint2d pt2d;
			AcGePoint3d pt3d;
			pt2d = pts[i];
			pt3d[0] = pt2d[0]; pt3d[1] = pt2d[1]; pt3d[2] = 0;
			pt3d.transformBy(finalMatrix);
			pts3d.append(pt3d);
		}
	}
	// Get the new normal and new ECS information for the polyline.
	AcGeVector3d xfnorm = normal.transformBy(finalMatrix);
	AcGeMatrix3d plineECS;
	AcDbPolyline* pline = new AcDbPolyline();
	pline->setNormal(xfnorm);
	pline->getEcs(plineECS);
	delete pline; pline = NULL;
	AcGeMatrix3d plineECSInv = plineECS.inverse();
	double xfelev = 0.0;
	for (int i = 0; i < pts.length(); i++)
	{
		pts[i].x = pts3d[i].x;
		pts[i].y = pts3d[i].y;
		if (i == 0)
			xfelev = pts3d[i].z;
		// Should be identical to within roundoff
		assert(fabs(xfelev - pts3d[i].z) < 1.0e-10);
	}

	// Show the boundary
	HPoint * polyPoint = new HPoint[pts.length()];
	for(int i = 0; i < pts.length(); i++)
	{
		polyPoint[i].x = pts[i].x;
		polyPoint[i].y = pts[i].y;
		polyPoint[i].z = xfelev;
	}

	if(enabled == Adesk::kTrue)
	{
		if(!pBStreamtk)
		{
			// For 3DGS Mode
			HC_Set_Polygonal_Clip_Region(pts.length(),(HC_POINT*)polyPoint,"world");
			//HC_Insert_Polyline(pts.length(), polyPoint);
		}
		else
		{
			// For BStream Mode
			TK_Clip_Region* clip = new TK_Clip_Region;
			clip->SetPoints(pts.length(), (float*)polyPoint);
			clip->SetOptions(1);	//// Set the option to 1(world):Its default value is 0(window)
			TK_Status hdwg_status = clip->Write(*pBStreamtk);
			H_ASSERT(hdwg_status == TK_Normal);
			delete clip;
		}
	}

	delete []polyPoint;
	filter->close();
	ref->close();
	return true;
} // End of insertClip() 

// In some files (as reported in 13045), there are invalid entities with large coordinates. These
// Entities create problem while update. This is to safeguard against those entities.
// I have kept the limit as 1.0e9, might need to increase it future. ASHISH.S. 15/10/2010.
bool CheckForInvalidExtents(AcDbEntity * pEnt)
{
	// For external references no use of looking for extents.
	// I've found these two objects while testing, the list may increase or we have to apply this method for 
	// each entity while importing in Hoops. AcDbBlockReference entity shows invalid extents if it contains Xrefs.
	if (pEnt->isA() == AcDbOle2Frame::desc() || pEnt->isA() == AcDbBlockReference::desc()) 
		return true;

    AcDbExtents etxs;
    pEnt->getGeomExtents(etxs);
    if(fabs(etxs.maxPoint().x)>  1.0e9 || fabs(etxs.maxPoint().y)>  1.0e9 || fabs(etxs.maxPoint().z)>  1.0e9
        ||fabs(etxs.minPoint().x)>  1.0e9 || fabs(etxs.minPoint().y)>  1.0e9 || fabs(etxs.minPoint().z)>  1.0e9)
    {
        return false;
    }
	return true;
}