/*
* Copyright (c) 2009 by Tech Soft 3D, LLC.
* The information contained herein is confidential and proprietary to
* Tech Soft 3D, LLC., and considered a trade secret as defined under
* civil and criminal statutes.	 Tech Soft 3D shall pursue its civil
* and criminal remedies in the event of unauthorized use or misappropriation
* of its trade secrets.  Use of this information by anyone other than
* authorized employees of Tech Soft 3D, LLC. is granted only under a
* written non-disclosure agreement, expressly prescribing the scope and
* manner of such use.
*
* $Id: H3DXHelper.cpp,v 1.11 2011-01-17 17:59:22 guido Exp $
*/

#include <stdio.h>
#include <windows.h>

static int const _NAME = ('n') | ('a' << 8) | ('m' << 16) | ('e' << 24);

#define INT2bool(int_value)  (int_value > 0) ?  true: false

#define INITIALIZE_A3D_API
#include <A3DSDKIncludes.h>

#define USE_INSTANCING
#include "H3DXHelper.h"

// HOOPS includes
#include "hc.h"
#include "hcd.h"
#include "HTools.h"

// Standard includes
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <tchar.h>
#include <wchar.h>

// HOOPS/MVO includes
#include "HDB.h"
#include "HBaseView.h"
#include "HUtilityLocaleString.h"
#include "HUtilityGeometryCreation.h"
#include "HIOUtility3DX.h"
#include <magick/api.h>

#include "vlist.h"
#include "vhash.h"
#include "varray.h"

#include <windows.h>

#define MAKE_INT_VERSION(a,b) (a * 100 + b)

//#define GENERATE_LOG_FILE

#ifdef GENERATE_LOG_FILE
char * a3d_translation_log_file = "C:/translation.log";
FILE * a3d_translation_log_fp = NULL;

A3DInt32 a3d_message_function(A3DUTF8Char * message)
{
	fwprintf(a3d_translation_log_fp, ((wchar_t const *)H_WCS(message).encodedText()));
	return 0;
}

A3DInt32 a3d_warning_function(A3DUTF8Char * code, A3DUTF8Char * message)
{
	fprintf(a3d_translation_log_fp, H_FORMAT_TEXT("WARNING #%s:", (char const *)code));
	return a3d_message_function(message);
}

A3DInt32 a3d_error_function(A3DUTF8Char * code, A3DUTF8Char * message)
{
	fprintf(a3d_translation_log_fp, H_FORMAT_TEXT("ERROR #%s:", (char const *)code));
	return a3d_message_function(message);
}
#endif // GENERATE_LOG_FILE

//#define DEBUG_MARKUP_TYPES
#ifdef DEBUG_MARKUP_TYPES
#define stringify(name) # name

char const * markupTypes[] = {
	stringify(kA3DMarkupTypeUnknown),
	stringify(kA3DMarkupTypeText),
	stringify(kA3DMarkupTypeDimension),
	stringify(kA3DMarkupTypeArrow),
	stringify(kA3DMarkupTypeBalloon),
	stringify(kA3DMarkupTypeCircleCenter),
	stringify(kA3DMarkupTypeCoordinate),
	stringify(kA3DMarkupTypeDatum),
	stringify(kA3DMarkupTypeFastener),
	stringify(kA3DMarkupTypeGdt),
	stringify(kA3DMarkupTypeLocator),
	stringify(kA3DMarkupTypeMeasurementPoint),
	stringify(kA3DMarkupTypeRoughness),
	stringify(kA3DMarkupTypeWelding),
	stringify(kA3DMarkupTypeTable),
	stringify(kA3DMarkupTypeOther)
};

char const * markupSubTypes[] = {
	stringify(kA3DMarkupSubTypeUnknown),
	stringify(kA3DMarkupSubTypeEnumMax)
};

char const * markupDatumSubTypes[] = {
	"DATUM_SUBTYPE_ERROR",
	stringify(kA3DMarkupSubTypeDatumIdent),
	stringify(kA3DMarkupSubTypeDatumTarget),
	stringify(kA3DMarkupSubTypeDatumEnumMax)
};

char const * markupDimensionSubTypes[] = {
	"DIMENSION_SUBTYPE_ERROR",
	stringify(kA3DMarkupSubTypeDimensionDistance),
	stringify(kA3DMarkupSubTypeDimensionDistanceOffset),
	stringify(kA3DMarkupSubTypeDimensionDistanceCumulate),
	stringify(kA3DMarkupSubTypeDimensionChamfer),
	stringify(kA3DMarkupSubTypeDimensionSlope),
	stringify(kA3DMarkupSubTypeDimensionOrdinate),
	stringify(kA3DMarkupSubTypeDimensionRadius),
	stringify(kA3DMarkupSubTypeDimensionRadiusTangent),
	stringify(kA3DMarkupSubTypeDimensionRadiusCylinder),
	stringify(kA3DMarkupSubTypeDimensionRadiusEdge),
	stringify(kA3DMarkupSubTypeDimensionDiameter),
	stringify(kA3DMarkupSubTypeDimensionDiameterTangent),
	stringify(kA3DMarkupSubTypeDimensionDiameterCylinder),
	stringify(kA3DMarkupSubTypeDimensionDiameterEdge),
	stringify(kA3DMarkupSubTypeDimensionDiameterCone),
	stringify(kA3DMarkupSubTypeDimensionLength),
	stringify(kA3DMarkupSubTypeDimensionLengthCurvilinear),
	stringify(kA3DMarkupSubTypeDimensionLengthCircular),
	stringify(kA3DMarkupSubTypeDimensionAngle),
	stringify(kA3DMarkupSubTypeDimensionEnumMax)
};

char const * markupGdtSubTypes[] = {
	"GDT_SUBTYPE_ERROR",
	stringify(kA3DMarkupSubTypeGdtFcf),
	stringify(kA3DMarkupSubTypeGdtEnumMax)
};

char const * markupWeldingSubTypes[] = {
	"WELDING_SUBTYPE_ERROR",
	stringify(kA3DMarkupSubTypeWeldingLine),
	stringify(kA3DMarkupSubTypeWeldingSpot),
	stringify(kA3DMarkupSubTypeWeldingEnumMax)
};

char const * markupOtherSubTypes[] = {
	"OTHER_SUBTYPE_ERROR",
	stringify(kA3DMarkupSubTypeOtherSymbolUser),
	stringify(kA3DMarkupSubTypeOtherSymbolUtility),
	stringify(kA3DMarkupSubTypeOtherSymbolCustom),
	stringify(kA3DMarkupSubTypeOtherGeometricReference),
	stringify(kA3DMarkupSubTypeOtherEnumMax)
};
#endif // DEBUG_MARKUP_TYPES

H3DXImporter::H3DXImporter(HIOUtility3DX* p3DXInputHandler)
			 : m_p3DXInputHandler(p3DXInputHandler), m_fileName(0)
{}


H3DXImporter::~H3DXImporter()
{
	delete [] m_fileName;
}





static A3DInt32 SetLicense()
{
	const A3DUTF8Char* pcCustomerKey = "PLEASE: Put your Customer Key here";
	const A3DUTF8Char* pcVariableKey= "PLEASE: Put your Variable Key here";
	A3DInt32 iRet=A3D_SUCCESS;

    iRet =A3DLicPutLicense(A3DLicPutLicenseFile,pcCustomerKey,pcVariableKey);
 	return iRet;
}



A3DInt32 H3DXImporter::CreateAndPushCascadedAttributesFace(const A3DRiRepresentationItem* pRepItem,
											const A3DTessBase* pTessBase,
											const A3DTessFaceData* psTessFaceData,
											A3DUns32 uiFaceIndex,
											const A3DMiscCascadedAttributes* pFatherAttr,
											A3DMiscCascadedAttributes** ppAttr,
											A3DMiscCascadedAttributesData* psAttrData)
{
	A3DInt32 iRet = A3DMiscCascadedAttributesCreate(ppAttr);
	iRet = A3DMiscCascadedAttributesPushTessFace(*ppAttr, pRepItem, pTessBase, psTessFaceData, uiFaceIndex, pFatherAttr);

	A3D_INITIALIZE_DATA(A3DMiscCascadedAttributesData, (*psAttrData));

	iRet = A3DMiscCascadedAttributesGet(*ppAttr, psAttrData);

	return iRet;
}

A3DInt32 H3DXImporter::CreateAndPushCascadedAttributes(const A3DRootBaseWithGraphics* pBase,
										const A3DMiscCascadedAttributes* pFatherAttr,
										A3DMiscCascadedAttributes** ppAttr,
										A3DMiscCascadedAttributesData* psAttrData)
{
	A3DInt32 iRet = A3DMiscCascadedAttributesCreate(ppAttr);
	iRet = A3DMiscCascadedAttributesPush(*ppAttr, pBase, pFatherAttr);

	A3D_INITIALIZE_DATA(A3DMiscCascadedAttributesData, (*psAttrData));

 	iRet = A3DMiscCascadedAttributesGet(*ppAttr, psAttrData);

  	return iRet;
}

void H3DXImporter::parseRiSet(A3DRiSet* p, A3DMiscCascadedAttributes* pFatherAttr, double modelscale)
{
	A3DMiscCascadedAttributes* pAttr;
	A3DMiscCascadedAttributesData sAttrData;
	A3DInt32 iRet = CreateAndPushCascadedAttributes(p, pFatherAttr, &pAttr, &sAttrData);

	A3DRiSetData sData;
	A3D_INITIALIZE_DATA(A3DRiSetData, sData);

	iRet = A3DRiSetGet(p, &sData);

	if (iRet == A3D_SUCCESS) {
		for(A3DUns32 ui = 0; ui<sData.m_uiRepItemsSize; ui++)
			parseRI(sData.m_ppRepItems[ui], pAttr, modelscale);

		A3DRiSetGet(NULL, &sData);
	} 
 
	A3DMiscCascadedAttributesDelete(pAttr);
	A3DMiscCascadedAttributesGet(NULL, &sAttrData);
}



void H3DXImporter::SetMaterial(	A3DMiscCascadedAttributesData *attr)
{
 	A3DInt32 iRet;

	A3DUns8 opaque_value = attr->m_sStyle.m_ucTransparency;
	if(opaque_value < 255){
		double transmission = 1 - opaque_value/255.0;
		HC_Set_Color(H_FORMAT_TEXT("transmission = (r = %f g = %f b = %f)", transmission, transmission, transmission));
	}

	if(attr->m_sStyle.m_bMaterial){
		A3DGraphMaterialData materialdata;
		A3D_INITIALIZE_DATA(A3DGraphMaterialData, materialdata);

		iRet = A3DGlobalGetGraphMaterialData(attr->m_sStyle.m_uiRgbColorIndex, &materialdata); 	
		A3DBool is_texture = false;
		A3DGlobalIsMaterialTexture(attr->m_sStyle.m_uiRgbColorIndex, &is_texture);
		if (is_texture){
			A3DGraphRgbColorData diffusecolor;
			A3D_INITIALIZE_DATA(A3DGraphRgbColorData, diffusecolor);

			iRet = A3DGlobalGetGraphRgbColorData(materialdata.m_uiDiffuse, &diffusecolor);

			A3DGraphTextureApplicationData adata;
			A3D_INITIALIZE_DATA(A3DGraphTextureApplicationData, adata);

			A3DGlobalGetGraphTextureApplicationData(attr->m_sStyle.m_uiRgbColorIndex, &adata);

			A3DGraphTextureDefinitionData tdata;
			A3D_INITIALIZE_DATA(A3DGraphTextureDefinitionData, tdata);

			A3DGlobalGetGraphTextureDefinitionData(adata.m_uiTextureDefinitionIndex, &tdata);
			if (tdata.m_uiMappingAttributes & kA3DTextureMappingSphericalReflection)
				HC_Set_Color(H_FORMAT_TEXT("faces = (diffuse = (r=%f g=%f b=%f), environment = texture_%d, mirror = (r = 0.5 g = 0.5 b = 0.5))", diffusecolor.m_dRed, diffusecolor.m_dGreen, diffusecolor.m_dBlue,
				adata.m_uiTextureDefinitionIndex));
			else
				HC_Set_Color(H_FORMAT_TEXT("faces = (diffuse = (r=%f g=%f b=%f) texture_%d)", 
				diffusecolor.m_dRed, diffusecolor.m_dGreen, diffusecolor.m_dBlue, adata.m_uiTextureDefinitionIndex));
		}
		else {
			A3DGraphRgbColorData diffusecolor;
			A3D_INITIALIZE_DATA(A3DGraphRgbColorData, diffusecolor);

			iRet = A3DGlobalGetGraphRgbColorData(materialdata.m_uiDiffuse, &diffusecolor);
			if(iRet == A3D_SUCCESS)
				HC_Set_Color(H_FORMAT_TEXT("geometry = (diffuse = (r=%f g=%f b=%f))", diffusecolor.m_dRed, diffusecolor.m_dGreen, diffusecolor.m_dBlue));

			A3DGraphRgbColorData specularcolor;
			A3D_INITIALIZE_DATA(A3DGraphRgbColorData, specularcolor);

			iRet = A3DGlobalGetGraphRgbColorData(materialdata.m_uiSpecular, &specularcolor);
			if(iRet == A3D_SUCCESS)
				HC_Set_Color(H_FORMAT_TEXT("geometry = (specular = (r=%f g=%f b=%f))", specularcolor.m_dRed, specularcolor.m_dGreen, specularcolor.m_dBlue));		
		}
	}
	else {
		A3DGraphRgbColorData colordata;
		A3D_INITIALIZE_DATA(A3DGraphRgbColorData, colordata);

 		iRet = A3DGlobalGetGraphRgbColorData(attr->m_sStyle.m_uiRgbColorIndex, &colordata); 				
		if (!iRet)
 			HC_Set_Color_By_Value("geometry", "rgb", colordata.m_dRed, colordata.m_dGreen,colordata.m_dBlue);	
	}
}


void H3DXImporter::AddVertexColor(HPoint *face, A3DUns8 *vertexarray, int &vcpos, bool invert, bool decrement)
{
	float *v = (float *)face;

	for (int i=0;i<3;i++)	
	{
		for (int j=0;j<3;j++)
		{
			if (!invert)
 				v[i*3+j] = vertexarray[vcpos++]/255.0f;
			else
 				v[(2-i)*3+j] = vertexarray[vcpos++]/255.0f;
		}
	}
	if (decrement)
		vcpos-=6;
}


void H3DXImporter::BuildShell(A3DTess3D* p, A3DRiRepresentationItem* pRepItem, A3DMiscCascadedAttributes* pFatherAttr, A3DTessBaseData *tessbasedata, double modelscale)
{
	
	int face1[3];
	int face2[3];
	int face3[3];
	double unit_scale;
	if (m_body_scale >= 0.0)
		unit_scale = m_body_scale * modelscale;
	else 
		unit_scale = 1.0;
	HC_KEY vertexkey, edgekey;

	HC_KEY toplevel = HC_KOpen_Segment(".");

	if (!m_bMergeFaces && m_bHasBrepStructure)
	{
		vertexkey = HC_KCreate_Segment("vertices");		
		edgekey = HC_KCreate_Segment("edges");
	}
	HC_Close_Segment();


	vlist_reset_cursor(m_brepfacelist);
	m_edgematcher->StartEdgeIteration();
	
	A3DTess3DData tess3ddata;
	A3D_INITIALIZE_DATA(A3DTess3DData, tess3ddata);

	A3DInt32 iRet = A3DTess3DGet(p, &tess3ddata);

 	A3DRootBaseWithGraphicsData tempdata;
	A3D_INITIALIZE_DATA(A3DRootBaseWithGraphicsData, tempdata);

	A3DRootBaseWithGraphicsGet(pRepItem,&tempdata);
 	
	A3DGraphicsData tempdata2;
	A3D_INITIALIZE_DATA(A3DGraphicsData, tempdata2);

	A3DGraphicsGet(tempdata.m_pGraphics,&tempdata2);

	if (iRet == A3D_SUCCESS ) {

		int pnum = tessbasedata->m_uiCoordSize/3;

		//HPoint const * const points = (HPoint const*)tessbasedata->m_pdCoords;
		HPoint * const points = new HPoint[pnum];
		for (int i = 0; i < pnum; ++i){
			points[i].Set(tessbasedata->m_pdCoords[i*3], tessbasedata->m_pdCoords[i*3+1],tessbasedata->m_pdCoords[i*3+2]);
		}

		int nnum = tess3ddata.m_uiNormalSize/3;
		//HPoint const * const normals = (HPoint const*)tess3ddata.m_pdNormals;//new HPoint[nnum];
		HPoint * const normals = new HPoint[nnum];
		for (int i = 0; i < nnum; ++i){
			normals[i].Set(tess3ddata.m_pdNormals[i*3], tess3ddata.m_pdNormals[i*3+1],tess3ddata.m_pdNormals[i*3+2]);
		}

		int tcnum = tess3ddata.m_uiTextureCoordSize/2;
		//HPoint const * const texcor = (HPoint const*)tess3ddata.m_pdTextureCoords;//new HPoint[tcnum];
		HPoint * const texcor = new HPoint[tcnum];
		for (int i = 0; i < tcnum; ++i){
			texcor[i].Set(tess3ddata.m_pdTextureCoords[i*2], tess3ddata.m_pdTextureCoords[i*2+1],0);
		}
 
		A3DGraphicsData grfx;
		A3D_INITIALIZE_DATA(A3DGraphicsData, grfx);

		A3DInt32 iRet  = A3DGraphicsGet(p, &grfx);
	
		A3DMiscCascadedAttributesData attdata;
		A3D_INITIALIZE_DATA(A3DMiscCascadedAttributesData, attdata);

		A3DMiscCascadedAttributesGet(pFatherAttr, &attdata);
 			
		if (attdata.m_bShow) {
			A3DUns32 uiNumberOfFaces	= tess3ddata.m_uiFaceTessSize;

			A3DUns32 *tindices = tess3ddata.m_puiTriangulatedIndexes;
			bool segment_open = false;
			for (A3DUns32 face_index = 0; face_index < uiNumberOfFaces; ++face_index) {
				if(segment_open){
					HC_Close_Segment();
				}
				HC_KEY facekey = HC_KOpen_Segment(H_FORMAT_TEXT("Shell %d", HDB::GetUniqueID()));
				BREP_Face *brep_face;
				if (!m_bMergeFaces && m_bHasBrepStructure)
				{
					brep_face = m_TopologyManager->AddFace(facekey);
					void *brepface = vlist_peek_cursor(m_brepfacelist);
					if (brepface)
					{
						vlist_advance_cursor(m_brepfacelist);
						if (m_pConnector)
							m_pConnector->AddConnection(facekey, brepface);
					}
					HC_Set_User_Data(_NAME, "face", 5);
				}

				segment_open = true;
				HShellWrapper myshell(INVALID_KEY);
				myshell.BeginAddFaces(pnum);
				A3DTessFaceData& sTessFaceData = tess3ddata.m_psFaceTessData[face_index];

				A3DMiscCascadedAttributes* pAttr;
				A3DMiscCascadedAttributesData sAttrData;
				CreateAndPushCascadedAttributesFace(pRepItem, p, &sTessFaceData, face_index, pFatherAttr, &pAttr, &sAttrData);
				SetMaterial(&sAttrData);
				A3DMiscCascadedAttributesDelete(pAttr);
				A3DMiscCascadedAttributesGet(NULL, &sAttrData);

				int index = 0, swire = sTessFaceData.m_uiStartWire;
				VArray<HPoint> w(250);
				w.SetCount(0);
				 
				if (!m_bMergeFaces && m_bHasBrepStructure)
					HC_Open_Segment_By_Key(edgekey);
				for (A3DUns32 j = 0; j < sTessFaceData.m_uiSizesWiresSize; ++j){
					w.SetCount(0);
					
					A3DUns32 size  = sTessFaceData.m_puiSizesWires[j] & ~(kA3DTessFaceDataWireIsNotDrawn | kA3DTessFaceDataWireIsClosing);
					A3DUns32 flags = sTessFaceData.m_puiSizesWires[j] & (kA3DTessFaceDataWireIsNotDrawn | kA3DTessFaceDataWireIsClosing);


					if ((m_bMergeFaces || !m_bHasBrepStructure) && (flags & kA3DTessFaceDataWireIsNotDrawn) ){
						index += size;
						continue;
					}

					bool endLoop = false;  /* I have no idea what this is for.  It is NOT a flag telling us to connect the first and last points of the line. */
					if (flags & kA3DTessFaceDataWireIsClosing)
						endLoop = true;
					
					w.EnsureSize(size);
					
					for (A3DUns32 k = 0; k < size; ++k){				
						w.Append(points[tess3ddata.m_puiWireIndexes[swire+index++]/3]);
					}
					
 					if (w.Count() > 1){
			
						HC_KEY linekey = HC_KInsert_Polyline(w.Count(), &w[0]);						
						if (!m_bMergeFaces && m_bHasBrepStructure)
						{
							HC_KEY origkey;
							void *origid;
							bool uniqueedge = m_edgematcher->NextEdge(linekey, origkey, &origid);
							A3DInt32 iRet;
							if (origid)
							{
							if (m_pConnector)
								m_pConnector->AddConnection(linekey, origid);


							BREP_Edge *edge = brep_face->AddCoEdge(m_TopologyManager, origid, origkey);						
							
							A3DTopoEdgeData sData;
							A3D_INITIALIZE_DATA(A3DTopoEdgeData, sData);

							iRet = A3DTopoEdgeGet((A3DTopoEdge *)origid, &sData);
							
							A3DTopoUniqueVertexData sData2;
							A3D_INITIALIZE_DATA(A3DTopoUniqueVertexData, sData2);

							A3DTopoUniqueVertexData sData3;
							A3D_INITIALIZE_DATA(A3DTopoUniqueVertexData, sData3);

 							if (sData.m_pStartVertex)
							{
								HC_KEY key = m_TopologyManager->FindVertex(sData.m_pStartVertex);
								if (key == INVALID_KEY)
								{
									HPoint vp;
									A3DEEntityType eType;
									A3DInt32 iErr = A3DEntityGetType(sData.m_pStartVertex, &eType);
									if (eType == kA3DTypeTopoMultipleVertex)
									{
										A3DTopoMultipleVertexData mdata;
										A3D_INITIALIZE_DATA(A3DTopoMultipleVertexData, mdata);

										iRet = A3DTopoMultipleVertexGet(sData.m_pStartVertex, &mdata);

										vp.Set(mdata.m_pPts[0].m_dX * unit_scale, mdata.m_pPts[0].m_dY * unit_scale,mdata.m_pPts[0].m_dZ * unit_scale);
	 									HC_Open_Segment_By_Key(vertexkey);
										for (unsigned int i=1;i<mdata.m_uiSize;i++)
										{
 											vp.Add(mdata.m_pPts[i].m_dX * unit_scale, mdata.m_pPts[i].m_dY * unit_scale,mdata.m_pPts[i].m_dZ * unit_scale);
											vp/=2.0f;
										}
			 							HC_Close_Segment();
 									}

									else
									{
 										iRet = A3DTopoUniqueVertexGet(sData.m_pStartVertex, &sData2);
										vp.Set(sData2.m_sPoint.m_dX * unit_scale, sData2.m_sPoint.m_dY * unit_scale,sData2.m_sPoint.m_dZ * unit_scale);
									}

 									HC_Open_Segment_By_Key(vertexkey);
									key = m_TopologyManager->AddVertex(sData.m_pStartVertex,vp);									
									HC_Close_Segment();
									if (m_pConnector)
										m_pConnector->AddConnection(key, sData.m_pStartVertex);
								}
								edge->m_vertex1 = key;
							}
							
							if (sData.m_pEndVertex)
							{
								HC_KEY key = m_TopologyManager->FindVertex(sData.m_pEndVertex);
							
								if (key == INVALID_KEY)
								{
									HPoint vp;
									A3DEEntityType eType;
									A3DInt32 iErr = A3DEntityGetType(sData.m_pEndVertex, &eType);

									if (eType == kA3DTypeTopoMultipleVertex)
									{
										A3DTopoMultipleVertexData mdata;
										A3D_INITIALIZE_DATA(A3DTopoMultipleVertexData, mdata);

										iRet = A3DTopoMultipleVertexGet(sData.m_pEndVertex, &mdata);

										vp.Set(mdata.m_pPts[0].m_dX * unit_scale, mdata.m_pPts[0].m_dY * unit_scale,mdata.m_pPts[0].m_dZ * unit_scale);
	 									HC_Open_Segment_By_Key(vertexkey);
										for (unsigned int i=1;i<mdata.m_uiSize;i++)
										{
 											vp.Add(mdata.m_pPts[i].m_dX * unit_scale, mdata.m_pPts[i].m_dY * unit_scale,mdata.m_pPts[i].m_dZ * unit_scale);
											vp/=2.0f;
										}
			 							HC_Close_Segment();

 									}

									else
									{
 										iRet = A3DTopoUniqueVertexGet(sData.m_pEndVertex, &sData2);
										vp.Set(sData2.m_sPoint.m_dX * unit_scale, sData2.m_sPoint.m_dY * unit_scale,sData2.m_sPoint.m_dZ * unit_scale);
									}

 									HC_Open_Segment_By_Key(vertexkey);
									key = m_TopologyManager->AddVertex(sData.m_pEndVertex,vp);
									HC_Close_Segment();
									if (m_pConnector)
										m_pConnector->AddConnection(key, sData.m_pStartVertex);

								}
								edge->m_vertex2 = key;
							}
							}
 

 							if (!uniqueedge)
							{
								HC_Delete_By_Key(linekey);
							}
						}
 
					}
				}
				if (!m_bMergeFaces && m_bHasBrepStructure)
					HC_Close_Segment();

				int cursizes = 0;
				int tpos = sTessFaceData.m_uiStartTriangulated;

				bool hasVertexColor = INT2bool(sTessFaceData.m_uiRGBAVerticesSize);
				int vcpos = 0;
				HPoint face4[3];
				if (sTessFaceData.m_usUsedEntitiesFlags & kA3DTessFaceDataTriangle){				 				
					int numtriangles = sTessFaceData.m_puiSizesTriangulated[cursizes++];
					
					for (int i = 0; i < numtriangles; ++i){
 						face1[0] = tindices[tpos+1]/3;
						face2[0] = tindices[tpos]/3;
						tpos+=2;
						face1[1] = tindices[tpos+1]/3;
						face2[1] = tindices[tpos]/3;
						tpos+=2;
						face1[2] = tindices[tpos+1]/3;
						face2[2] = tindices[tpos]/3;
						tpos+=2;
						myshell.AddNextFaceWithDistinctNormals(points, normals, face1, face2, 3);
					}
				}

				if (sTessFaceData.m_usUsedEntitiesFlags & kA3DTessFaceDataTriangleFan){							 				
					int numstripes = sTessFaceData.m_puiSizesTriangulated[cursizes++];	 			
					for (int stripe = 0;stripe < numstripes;stripe++){
						int numpoints = sTessFaceData.m_puiSizesTriangulated[cursizes++];
						int tpos2=tpos;
	
						for (int i = 0; i < numpoints-1; ++i){

 							if (!(i % 2) || 1){
								face1[0] = tindices[tpos+1]/3;
								face2[0] = tindices[tpos]/3;
								face1[1] = tindices[tpos2+1]/3;
								face2[1] = tindices[tpos2]/3;
								tpos2+=2;
								face1[2] = tindices[tpos2+1]/3;
								face2[2] = tindices[tpos2]/3;							
							}
							else {
								face1[2] = tindices[tpos+1]/3;
								face2[2] = tindices[tpos]/3;
								face1[1] = tindices[tpos2+1]/3;
								face2[1] = tindices[tpos2]/3;
								tpos2+=2;
								face1[0] = tindices[tpos2+1]/3;
								face2[0] = tindices[tpos2]/3;							
							}

							myshell.AddNextFaceWithDistinctNormals(points, normals, face1, face2, 3);
						}
						tpos += numpoints*2;
					}
				}


				if (sTessFaceData.m_usUsedEntitiesFlags & kA3DTessFaceDataTriangleStripe) {				 				
					int numstripes = sTessFaceData.m_puiSizesTriangulated[cursizes++];	 			
					for (int stripe = 0; stripe < numstripes; ++stripe)
					{			
						int numpoints = sTessFaceData.m_puiSizesTriangulated[cursizes++];
						int vcpos2 = vcpos;
						int tpos2=tpos;			
						for (int i = 0; i < numpoints-2; ++i) {
 							if (!(i % 2)) {
								face1[0] = tindices[tpos2+1]/3;
								face2[0] = tindices[tpos2]/3;
								tpos2+=2;
								face1[1] = tindices[tpos2+1]/3;
								face2[1] = tindices[tpos2]/3;
								tpos2+=2;
								face1[2] = tindices[tpos2+1]/3;
								face2[2] = tindices[tpos2]/3;
								if (hasVertexColor)								
									AddVertexColor(face4, sTessFaceData.m_pucRGBAVertices, vcpos2,false, true);
 								tpos2-=2;
							}
							else {
								face1[2] = tindices[tpos2+1]/3;
								face2[2] = tindices[tpos2]/3;
								tpos2+=2;
								face1[1] = tindices[tpos2+1]/3;
								face2[1] = tindices[tpos2]/3;
								tpos2+=2;
								face1[0] = tindices[tpos2+1]/3;
								face2[0] = tindices[tpos2]/3;
								tpos2-=2;
								if (hasVertexColor)
									AddVertexColor(face4, sTessFaceData.m_pucRGBAVertices, vcpos2,true, true);
							}

							if (hasVertexColor)
								myshell.AddNextFaceWithDistinctNormalsAndColor(points, normals,face1,face2,face4,3);
							else
								myshell.AddNextFaceWithDistinctNormals(points, normals, face1, face2, 3);
						}
						tpos+=numpoints*2;	
						vcpos +=numpoints * 3;
					}
				}

				if (sTessFaceData.m_usUsedEntitiesFlags & kA3DTessFaceDataTriangleOneNormal) {
					
					int numtriangles = sTessFaceData.m_puiSizesTriangulated[cursizes++];
					if (numtriangles>1)
						numtriangles = numtriangles;
					for (int i = 0; i < numtriangles; ++i) {
						int tposstart = tpos;
						++tpos;
 						face1[0] = tindices[tpos]/3;
						face2[0] = tindices[tposstart]/3;
						++tpos;
						face1[1] = tindices[tpos]/3;
						face2[1] = tindices[tposstart]/3;
						++tpos;
						face1[2] = tindices[tpos]/3;
						face2[2] = tindices[tposstart]/3;
						++tpos;
						myshell.AddNextFaceWithDistinctNormals(points, normals, face1, face2, 3);
					}
				}

				if (sTessFaceData.m_usUsedEntitiesFlags & kA3DTessFaceDataTriangleFanOneNormal){		

					bool NormalSingle;
					int numstripes = sTessFaceData.m_puiSizesTriangulated[cursizes++];	 			
					for (int stripe = 0; stripe < numstripes; ++stripe)
					{			
						if (sTessFaceData.m_puiSizesTriangulated[cursizes] & kA3DTessFaceDataNormalSingle)
							NormalSingle = true;
						else
							NormalSingle = false;
						int numpoints = sTessFaceData.m_puiSizesTriangulated[cursizes] & ~kA3DTessFaceDataNormalSingle;
						++cursizes;
						
						int tpos2=tpos;						
						if (!NormalSingle){
							tpos+=2;
							for (int i = 0; i < numpoints-1; ++i){
 								if (!(i % 2)){
									face1[0] = tindices[tpos+1]/3;
									face2[0] = tindices[tpos]/3;
									face1[1] = tindices[tpos2+1]/3;
									face2[1] = tindices[tpos2]/3;
									tpos2+=2;
									face1[2] = tindices[tpos2+1]/3;
									face2[2] = tindices[tpos2]/3;						
								}
								else
								{
									face1[2] = tindices[tpos+1]/3;
									face2[2] = tindices[tpos]/3;
									face1[1] = tindices[tpos2+1]/3;
									face2[1] = tindices[tpos2]/3;
									tpos2+=2;
									face1[0] = tindices[tpos2+1]/3;
									face2[0] = tindices[tpos2]/3;					
								}

								myshell.AddNextFaceWithDistinctNormals(points, normals, face1, face2, 3);
							}
							tpos+=numpoints*2;
						}
						else {
							tpos2 += 2;
							for (int i = 0; i < numpoints-2; ++i) {
 								if (!(i % 2) || 1) {
									face1[0] = tindices[tpos+1]/3;
									face2[0] = tindices[tpos]/3;
									face1[1] = tindices[tpos2]/3;
									face2[1] = tindices[tpos]/3;
									++tpos2;
									face1[2] = tindices[tpos2]/3;
									face2[2] = tindices[tpos]/3;						
								}
								else {
									face1[2] = tindices[tpos+1]/3;
									face2[2] = tindices[tpos]/3;
									face1[1] = tindices[tpos2]/3;
									face2[1] = tindices[tpos]/3;
									++tpos2;
									face1[0] = tindices[tpos2]/3;
									face2[0] = tindices[tpos]/3;							
								}

								myshell.AddNextFaceWithDistinctNormals(points, normals, face1, face2, 3);
							}
							tpos += (numpoints+1);
						}
					}				
				}
				
				if (sTessFaceData.m_usUsedEntitiesFlags & kA3DTessFaceDataTriangleStripeOneNormal) {
					//size = size & ~kA3DTessFaceDataWireIsNotDrawn;
					bool NormalSingle;
					int numstripes = sTessFaceData.m_puiSizesTriangulated[cursizes++];	 			
					for (int stripe = 0; stripe < numstripes; ++stripe){

						if (sTessFaceData.m_puiSizesTriangulated[cursizes] & kA3DTessFaceDataNormalSingle)

							NormalSingle = true;
						else
							NormalSingle = false;
						int numpoints = sTessFaceData.m_puiSizesTriangulated[cursizes] & ~kA3DTessFaceDataNormalSingle;
						++cursizes;
						int tpos2=tpos;
						if (!NormalSingle){
							for (int i = 0; i < numpoints-2; ++i){
 								if (!(i % 2)){
									face1[0] = tindices[tpos2+1]/3;
									face2[0] = tindices[tpos2]/3;
									tpos2+=2;
									face1[1] = tindices[tpos2+1]/3;
									face2[1] = tindices[tpos2]/3;
									tpos2+=2;
									face1[2] = tindices[tpos2+1]/3;
									face2[2] = tindices[tpos2]/3;
									tpos2-=2;
								}
								else{
									face1[2] = tindices[tpos2+1]/3;
									face2[2] = tindices[tpos2]/3;
									tpos2+=2;
									face1[1] = tindices[tpos2+1]/3;
									face2[1] = tindices[tpos2]/3;
									tpos2+=2;
									face1[0] = tindices[tpos2+1]/3;
									face2[0] = tindices[tpos2]/3;
									tpos2-=2;
								}

								myshell.AddNextFaceWithDistinctNormals(points, normals, face1, face2, 3);
							}
							tpos+=numpoints*2;
						}
						else{
							tpos2++;
							for (int i = 0; i < numpoints-2; ++i){
 								if (!(i % 2)){
									face1[0] = tindices[tpos2]/3;
									face2[0] = tindices[tpos]/3;
									tpos2++;
									face1[1] = tindices[tpos2]/3;
									face2[1] = tindices[tpos]/3;
									tpos2++;
									face1[2] = tindices[tpos2]/3;
									face2[2] = tindices[tpos]/3;
									tpos2--;
								}
								else{
									face1[2] = tindices[tpos2]/3;
									face2[2] = tindices[tpos]/3;
									tpos2++;
									face1[1] = tindices[tpos2]/3;
									face2[1] = tindices[tpos]/3;
									tpos2++;
									face1[0] = tindices[tpos2]/3;
									face2[0] = tindices[tpos]/3;
									tpos2--;
								}

								myshell.AddNextFaceWithDistinctNormals(points, normals, face1, face2, 3);
							}
							tpos+=(numpoints+1);
						}

					}				
				}
				
				if (sTessFaceData.m_usUsedEntitiesFlags & kA3DTessFaceDataPolyfaceTextured)
					continue;
			
				if (sTessFaceData.m_usUsedEntitiesFlags & kA3DTessFaceDataTriangleTextured){
					int numtriangles = sTessFaceData.m_puiSizesTriangulated[cursizes++];
					
				
					int tcindexsize = sTessFaceData.m_uiTextureCoordIndexesSize;
					int adnum = 2 + tcindexsize;
					for (int i = 0; i < numtriangles; ++i)
					{
 						face1[0] = tindices[tpos+1+tcindexsize]/3;
						face2[0] = tindices[tpos]/3;
						face3[0] = tindices[tpos+1]/2;
						tpos += adnum;
						face1[1] = tindices[tpos+1+tcindexsize]/3;
						face2[1] = tindices[tpos]/3;
						face3[1] = tindices[tpos+1]/2;
						tpos += adnum;
						face1[2] = tindices[tpos+1+tcindexsize]/3;
						face2[2] = tindices[tpos]/3;
						face3[2] = tindices[tpos+1]/2;
						tpos += adnum;
						myshell.AddNextFaceWithDistinctNormalsAndTexture(points, normals, texcor, face1, face2, face3, 3);
					}
				}

				if (sTessFaceData.m_usUsedEntitiesFlags & kA3DTessFaceDataTriangleFanTextured)
					continue;

				if (sTessFaceData.m_usUsedEntitiesFlags & kA3DTessFaceDataTriangleStripeTextured)
				{
					int tcindexsize = sTessFaceData.m_uiTextureCoordIndexesSize;
					int adnum = 2 + tcindexsize;

 					int numstripes = sTessFaceData.m_puiSizesTriangulated[cursizes++];	 			
					for (int stripe = 0; stripe < numstripes; ++stripe)
					{			
						int numpoints = sTessFaceData.m_puiSizesTriangulated[cursizes++];
						int tpos2=tpos;			
						for (int i = 0; i < numpoints-2; ++i) {
							if (!(i % 2)) {
								face1[0] = tindices[tpos2+tcindexsize+1]/3;
								face2[0] = tindices[tpos2]/3;
								face3[0] = tindices[tpos2+1]/2;
								tpos2+=adnum;
								face1[1] = tindices[tpos2+tcindexsize+1]/3;
								face2[1] = tindices[tpos2]/3;
								face3[1] = tindices[tpos2+1]/2;
								tpos2+=adnum;
								face1[2] = tindices[tpos2+tcindexsize+1]/3;
								face2[2] = tindices[tpos2]/3;
								face3[2] = tindices[tpos2+1]/2;
								tpos2-=adnum;
							}
							else {
								face1[2] = tindices[tpos2+tcindexsize+1]/3;
								face2[2] = tindices[tpos2]/3;
								face3[2] = tindices[tpos2+1]/2;
								tpos2+=adnum;
								face1[1] = tindices[tpos2+tcindexsize+1]/3;
								face2[1] = tindices[tpos2]/3;
								face3[1] = tindices[tpos2+1]/2;
								tpos2+=adnum;
								face1[0] = tindices[tpos2+tcindexsize+1]/3;
								face2[0] = tindices[tpos2]/3;
								face3[0] = tindices[tpos2+1]/2;
								tpos2-=adnum;
							}

							myshell.AddNextFaceWithDistinctNormalsAndTexture(points, normals, texcor, face1, face2, face3, 3);
						}
						tpos+=numpoints*adnum;
					}
				}
				if (sTessFaceData.m_usUsedEntitiesFlags & kA3DTessFaceDataTriangleOneNormalTextured)
					continue;

				if (sTessFaceData.m_usUsedEntitiesFlags & kA3DTessFaceDataTriangleFanOneNormalTextured)
					continue;

				if (sTessFaceData.m_usUsedEntitiesFlags & kA3DTessFaceDataTriangleStripeOneNormalTextured)
					continue;

				myshell.Regenerate(INVALID_KEY, false, true);	
				
				if (myshell.m_plen == 0)
					HC_Delete_By_Key(myshell.m_Key);

 				myshell.EndAddFaces();

				HC_Close_Segment();
				segment_open = false;
 			}
			if(segment_open){
				HC_Close_Segment();
			}
		}
	

		A3DTess3DGet(NULL, &tess3ddata);
		
		delete [] points;
		delete [] normals;
		delete [] texcor;

		if (m_bMergeFaces || !m_bHasBrepStructure)
			HC_Optimize_Segment_Tree(".", "merge shells = on, reorganize = color");
	}
}



void H3DXImporter::BuildWires(A3DTess3D* p, A3DRiRepresentationItem* pRepItem, A3DMiscCascadedAttributes* pFatherAttr, A3DTessBaseData *tessbasedata)
{
	A3DTess3DWireData sData;
	A3D_INITIALIZE_DATA(A3DTess3DWireData, sData);

	A3DMiscCascadedAttributesData aData;
	A3D_INITIALIZE_DATA(A3DMiscCascadedAttributesData, aData);

	A3DInt32 iRet = A3DTess3DWireGet(p, &sData);
	if (iRet == A3D_SUCCESS ) {
		A3DTess3DWireGet(NULL, &sData);
//		HC_Set_Visibility("lines = on");
		HC_DInsert_Polyline(tessbasedata->m_uiCoordSize/3, tessbasedata->m_pdCoords);

  		iRet = A3DMiscCascadedAttributesGet(pFatherAttr, &aData);
 		SetMaterial(&aData);

	} 
}



void H3DXImporter::getMarkupTesselation(const A3DTessBaseData *psTessBaseData, const A3DTessMarkupData *psTessMarkupData,
		PmiPolylineArray & out_polylines, PmiStringArray & out_strings, PmiTextAttributesArray & out_text_attributes)
{
	A3DInt32 iRet = A3D_SUCCESS;

	if (psTessMarkupData->m_uiCodesSize == 0)
		return;

#define DEFAULT_OFFSET {\
	pData += *(puiStart+1); \
	puiStart += (uiCount+1);\
}

#define MAKE_OFFSET(CountInt, CountFloats) {\
	pData += CountFloats;\
	puiStart +=(CountInt+1);\
}

	unsigned int uiCount = 0;

	const A3DDouble *pData = psTessBaseData->m_pdCoords;
	const A3DUns32 *puiStart = &psTessMarkupData->m_puiCodes[0];
	const A3DUns32 *puiEnd = &psTessMarkupData->m_puiCodes[psTessMarkupData->m_uiCodesSize-1];

	A3DFontKeyData sFontKeyData;
	A3D_INITIALIZE_DATA(A3DFontKeyData, sFontKeyData);

	A3DGraphRgbColorData sRgbColorData;
	A3D_INITIALIZE_DATA(A3DGraphRgbColorData, sRgbColorData);

	A3DGraphVPicturePatternData sPicturePatternData;
	A3D_INITIALIZE_DATA(A3DGraphVPicturePatternData, sPicturePatternData);

	PMI::RGBColor color(1, 1, 1);
	PMI::TextAttributes attributes;

	float cmatrix[16];
	HC_Compute_Identity_Matrix(cmatrix);
	VFloatArray pline(100);

	char temp[1024] = {""};
	for (; puiStart < puiEnd; ++puiStart)
	{
		uiCount = *puiStart & kA3DMarkupIntegerMask;

		if (*puiStart & kA3DMarkupIsExtraData)
		{
			switch(A3D_DECODE_EXTRA_DATA(*puiStart))
			{
			case 0 :  //pattern
				{

				DEFAULT_OFFSET;
				}
				break;

			case 1 :  //picture
				{

				DEFAULT_OFFSET;
				}
				break;

			case 2 :  //triangles
				{

				DEFAULT_OFFSET;
				}
				break;

			case 3 :  //picture
				{

				DEFAULT_OFFSET;
				}
				break;

			case 6 :  //faceview  
				{
				// this is used to ensure that the PMI coming through is always screen aligned
				DEFAULT_OFFSET;
				}
				break;

			case 7 :  //framedraw  
				{
				DEFAULT_OFFSET;
					break;
				// this defines a matrix 
				if (*(puiStart+1) > 0)
				{
					MAKE_OFFSET(0,3);
				}
				else
				{
					MAKE_OFFSET(0,0);
				}


			//	DEFAULT_OFFSET;
				}
				break;

			case 8 :  //fixed size  
				{
				// this defines the size of an object which has a view independent size
				DEFAULT_OFFSET;
				}
				break;


			case 9 :  //symbol  
				{
					A3DGlobalGetGraphVPicturePatternData(*(puiStart + 2), &sPicturePatternData);
					BuildMarkup(sPicturePatternData.m_pMarkupTess,0,0,(A3DTessBaseData *)psTessBaseData);
 
				// this is an image which will be texture mapped to a 3d quad
				DEFAULT_OFFSET;
				}
				break;

			case 11 :  //color
				{
					A3DGlobalGetGraphRgbColorData(*(puiStart + 2), &sRgbColorData);
					color.Set(sRgbColorData.m_dRed, sRgbColorData.m_dGreen, sRgbColorData.m_dBlue);
				
					
					DEFAULT_OFFSET;
				}
				break;

			case 12 :  //line stipple
				{

				DEFAULT_OFFSET;
				}
				break;

			case 13 :  //font
				{
					
					sFontKeyData.m_iFontFamilyIndex = *(puiStart + 2);
					sFontKeyData.m_iFontStyleIndex = (*(puiStart + 3) & kA3DFontKeyStyle) >> 24;
					sFontKeyData.m_iFontSizeIndex = (*(puiStart + 3) & kA3DFontKeySize) >> 12;\
					sFontKeyData.m_cAttributes =  (A3DInt8) (*(puiStart+3) & kA3DFontKeyAttrib);

					A3DFontData fontdata;
					A3D_INITIALIZE_DATA(A3DFontData, fontdata);

					A3DGlobalFontKeyGet(&sFontKeyData, &fontdata);

					attributes.SetFontSize(fontdata.m_uiSize * 0.6f);
					attributes.SetFontName(fontdata.m_pcFamilyName);

					A3DGlobalFontKeyGet(NULL, &fontdata);
			
					DEFAULT_OFFSET;
				}
				break;

			case 14 :  //text
				{
					A3DUns32 uiTextIndex = *(puiStart+2);
					A3DUTF8Char *pcBuffer = NULL;
					if (uiTextIndex < psTessMarkupData->m_uiTextsSize)
						pcBuffer = psTessMarkupData->m_ppcTexts[uiTextIndex];

					H_UTF8 utf8;
					utf8.encodedText(pcBuffer);

					attributes.SetRGBColor(color);

					out_strings.push_back(PMI::String(utf8));

					DEFAULT_OFFSET;
				}
				break;

			case 15 :  //points
				{

				DEFAULT_OFFSET;
				}
				break;


			case 16 :  //polygon
				{

				DEFAULT_OFFSET;
				}
				break;


			case 17 :  //line width
				{

				DEFAULT_OFFSET;
				}
				break;

			default:
				DEFAULT_OFFSET;
			}
		}
		else if (*puiStart & kA3DMarkupIsMatrix)
		{
			if (*(puiStart+1) > 0)
			{
				float m[16];

 				for (int i = 0; i < 16; ++i)
					m[i] = pData[i];				

				PMI::Orientation orientation;
				orientation.SetMatrix(m);

				attributes.SetOrientation(orientation);

				MAKE_OFFSET(0,16);
			}
			else
			{
				out_text_attributes.push_back(attributes);

				MAKE_OFFSET(0,0);
			}
		}
		else
		{
			int kSize = *(puiStart+1);
			pline.EnsureSize(kSize);
			
			for (int i = 0; i < kSize; ++i)
				pline[i] = pData[i];

			PMI::Polyline pmi_polyline;
			pmi_polyline.SetPoints(kSize / 3, (float *)pline);
			pmi_polyline.SetRGBColor(color);

			out_polylines.push_back(pmi_polyline);

			DEFAULT_OFFSET;
		}
	}

#undef DEFAULT_OFFSET
#undef MAKE_OFFSET

//	return iRet;
}


void H3DXImporter::BuildMarkup(A3DTess3D* p, A3DRiRepresentationItem* pRepItem, A3DMiscCascadedAttributes* pFatherAttr, A3DTessBaseData *tessbasedata)
{
	A3DTessMarkupData sData;
	A3D_INITIALIZE_DATA(A3DTessMarkupData, sData);

	A3DInt32 iRet = A3DTessMarkupGet(p, &sData);
	if (iRet == A3D_SUCCESS ) {

		PmiPolylineArray polylines;
		PmiStringArray strings;
		PmiTextAttributesArray text_attributes;
		getMarkupTesselation(tessbasedata, &sData, polylines, strings, text_attributes);
		A3DTessMarkupGet(NULL, &sData);
	} 

}

static void InvertImage(unsigned char *imagebuffer, int width, int height, bool rgba)
{
	unsigned char *row = new unsigned char[width * 4];
	for (int y=0;y<height/2;y++)
	{
 			int w;
			if (rgba)
				w = 4;
			else
				w = 3;
			
			memcpy(row, imagebuffer + (width * (height-1-y) * w), width *w);
			memcpy(imagebuffer + (width * (height-1-y) * w), imagebuffer + (width * w * y), 
				width * w);
			memcpy(imagebuffer + (width * w * y), row, width * w);
 	}
}



void H3DXImporter::parseTess(A3DTessBase* p, A3DRiRepresentationItem* pRepItem, 
				  A3DMiscCascadedAttributes* pFatherAttr, double modelscale)
{
 	if (p == NULL) {
		return;
	}

	A3DTessBaseData sData;
	A3D_INITIALIZE_DATA(A3DTessBaseData, sData);

	A3DInt32 iRet = A3DTessBaseGet(p, &sData);
	if (iRet == A3D_SUCCESS){
 
		A3DEEntityType eType;
		A3DInt32 iErr = A3DEntityGetType(p, &eType);

		if (iErr == A3D_SUCCESS) {
			switch(eType) {
				case kA3DTypeTess3D:
 					BuildShell(p, pRepItem, pFatherAttr, &sData, modelscale);
					break;
				case kA3DTypeTess3DWire:
					BuildWires(p, pRepItem, pFatherAttr, &sData);
					break;
				case kA3DTypeTessMarkup:
					BuildMarkup(p, pRepItem, pFatherAttr, &sData);
					break;
				}
		}

		A3DTessBaseGet(NULL, &sData);
	}

}

void H3DXImporter::parseBrepData(A3DTopoBrepData* p)
{	
	A3DTopoBrepDataData sData;
	A3D_INITIALIZE_DATA(A3DTopoBrepDataData, sData);

	A3DInt32 iRet = A3DTopoBrepDataGet(p, &sData);
	if (iRet == A3D_SUCCESS) {
		for(A3DUns32 ui = 0; ui < sData.m_uiConnexSize; ui++)
			parseConnex(sData.m_ppConnexes[ui], p);

		A3DTopoBrepDataGet(NULL, &sData);
	} 
 
}


void H3DXImporter::parseConnex(A3DTopoConnex* p, A3DTopoBrepData* p2)
{	
	
	m_bHasBrepStructure = true;
	A3DTopoConnexData sData;
	A3D_INITIALIZE_DATA(A3DTopoConnexData, sData);

	A3DInt32 iRet = A3DTopoConnexGet(p, &sData);
	if (iRet == A3D_SUCCESS) {
		for (unsigned int ui=0;ui<sData.m_uiShellSize;ui++)
		{
 			parseShell(sData.m_ppShells[ui]);
		}
	}
}

void H3DXImporter::parseShell(A3DTopoShell* p, bool invert)
{	

	A3DTopoShellData sData;
	A3D_INITIALIZE_DATA(A3DTopoShellData, sData);

	A3DInt32 iRet = A3DTopoShellGet(p, &sData);
	if (iRet == A3D_SUCCESS) {
		
		for(A3DUns32 ui = 0; ui < sData.m_uiFaceSize; ui++)
		{
			parseFace(sData.m_ppFaces[ui]);
	 	}		
		
		m_PartFaces = new A3DTopoFace*[sData.m_uiFaceSize];
		for (unsigned int i=0;i<sData.m_uiFaceSize;i++)
			m_PartFaces[i] = sData.m_ppFaces[i];
 
		A3DTopoShellGet(NULL, &sData);
	} 
 }

void H3DXImporter::parseFace(A3DTopoFace* p)
{	

	A3DTopoFaceData sData;
	A3D_INITIALIZE_DATA(A3DTopoFaceData, sData);

	vlist_add_last(m_brepfacelist,  p);
	A3DInt32 iRet = A3DTopoFaceGet(p, &sData);
	if (iRet == A3D_SUCCESS) {

		for(A3DUns32 ui = 0; ui < sData.m_uiLoopSize; ui++)
		{
 			parseLoop(sData.m_ppLoops[ui]);
 		}

		A3DTopoFaceGet(NULL, &sData);
	} 
 }

void H3DXImporter::parseLoop(A3DTopoLoop* p)
{	

	A3DTopoLoopData sData;
	A3D_INITIALIZE_DATA(A3DTopoLoopData, sData);

	A3DInt32 iRet = A3DTopoLoopGet(p, &sData);
	if (iRet == A3D_SUCCESS) {
		
		for(A3DUns32 ui = 0; ui < sData.m_uiCoEdgeSize; ui++)
		{
 			parseCoEdge(sData.m_ppCoEdges[ui]);
		}
		A3DTopoLoopGet(NULL, &sData);
	} 
 }

void H3DXImporter::parseCoEdge(A3DTopoCoEdge* p)
{		
	A3DTopoCoEdgeData sData;
	A3D_INITIALIZE_DATA(A3DTopoCoEdgeData, sData);

	A3DInt32 iRet = A3DTopoCoEdgeGet(p, &sData);
	if (iRet == A3D_SUCCESS) {

		if (sData.m_pEdge)
		{
			m_edgematcher->AddModellerEdge((void *)sData.m_pEdge);
			parseEdge(sData.m_pEdge);			
		}
		A3DTopoCoEdgeGet(NULL, &sData);
	} 
 }

void H3DXImporter::parseEdge(A3DTopoEdge* p)
{	
	A3DTopoEdgeData sData;
	A3D_INITIALIZE_DATA(A3DTopoEdgeData, sData);

	A3DInt32 iRet = A3DTopoEdgeGet(p, &sData);
	if (iRet == A3D_SUCCESS) {


		if (sData.m_pStartVertex)
		{
 			parseVertex(sData.m_pStartVertex);			
		}

		if (sData.m_pEndVertex)
		{
 			parseVertex(sData.m_pEndVertex);			
		}

		A3DTopoEdgeGet(NULL, &sData);
	} 
 }


void H3DXImporter::parseVertex(A3DTopoVertex* p)
{	
	A3DEEntityType eType;
	A3DInt32 iRet=A3DEntityGetType(p, &eType);

	if (iRet == A3D_SUCCESS)
	{
		switch (eType)
		{
		case kA3DTypeTopoMultipleVertex:
			parseMultipleVertex(p);
			break;
		case kA3DTypeTopoUniqueVertex:
			parseUniqueVertex(p);
			break;
		default:
			break;
		}
	}
 }


void H3DXImporter::parseMultipleVertex(A3DTopoMultipleVertex* p)
{
	A3DTopoMultipleVertexData sData;
	A3D_INITIALIZE_DATA(A3DTopoMultipleVertexData, sData);

	A3DInt32 iRet = A3DTopoMultipleVertexGet(p, &sData);
	if (iRet == A3D_SUCCESS)
	{
//		parsePoints("m_pPts", sData.m_uiSize, sData.m_pPts);
	}
}

void H3DXImporter::parseUniqueVertex(A3DTopoUniqueVertex* p)
{
	A3DTopoUniqueVertexData sData;
	A3D_INITIALIZE_DATA(A3DTopoUniqueVertexData, sData);

	A3DInt32 iRet = A3DTopoUniqueVertexGet(p, &sData);
	if (iRet == A3D_SUCCESS)
	{
//		parsePoint(sData.m_sPoint);
	}
}


void H3DXImporter::parseBody(A3DTopoBody* p)
{	
	A3DTopoBodyData sData;
	A3D_INITIALIZE_DATA(A3DTopoBodyData, sData);

	A3DInt32 iRet = A3DTopoBodyGet(p, &sData);
	if (iRet == A3D_SUCCESS) {
		parseContext(sData.m_pContext);
		A3DTopoBodyGet(NULL, &sData);
	} 
 
 }

void H3DXImporter::parseContext(A3DTopoContext* p)
{	
	A3DTopoContextData sData;
	A3D_INITIALIZE_DATA(A3DTopoContextData, sData);

	A3DInt32 iRet = A3DTopoContextGet(p, &sData);
	if (iRet == A3D_SUCCESS) {
		A3DTopoContextGet(NULL, &sData);
	} 

}

void H3DXImporter::parseRiBrepModel(A3DRiBrepModel* p)
{
	A3DRiBrepModelData sData;
	A3D_INITIALIZE_DATA(A3DRiBrepModelData, sData);

	A3DInt32 iRet = A3DRiBrepModelGet(p, &sData);
	if (iRet == A3D_SUCCESS) {
        A3DTopoBody *topoBody = reinterpret_cast<A3DTopoBody *>(sData.m_pBrepData);
        A3DTopoBodyData topoBodyData;
		A3D_INITIALIZE_DATA(A3DTopoBodyData, topoBodyData);

        iRet = A3DTopoBodyGet(topoBody, &topoBodyData);

        A3DTopoContextData topoContextData;
		A3D_INITIALIZE_DATA(A3DTopoContextData, topoContextData);

        iRet = A3DTopoContextGet(topoBodyData.m_pContext, &topoContextData);
       
        if (topoContextData.m_bHaveScale)
            m_body_scale = topoContextData.m_dScale;


		if (!m_bMergeFaces)
			parseBrepData(sData.m_pBrepData);

		A3DRiBrepModelGet(NULL, &sData);
	} 
}

void H3DXImporter::SetMatrix(A3DMiscCartesianTransformation *trans)
{
	A3DMiscCartesianTransformationData sData2;
	A3D_INITIALIZE_DATA(A3DMiscCartesianTransformationData, sData2);

	A3DUns32 iErr = A3DMiscCartesianTransformationGet(trans, &sData2);			
	if (iErr != A3D_SUCCESS){
		return;
	}

	HPoint v1(sData2.m_sXVector.m_dX, sData2.m_sXVector.m_dY,sData2.m_sXVector.m_dZ);
	HPoint v2(sData2.m_sYVector.m_dX, sData2.m_sYVector.m_dY,sData2.m_sYVector.m_dZ), v3;
	if (sData2.m_ucBehaviour & 4)
		HC_Compute_Cross_Product(&v2, &v1, &v3);
	else
		HC_Compute_Cross_Product(&v1, &v2, &v3);
	float matrix[16] = {
		v1.x, v1.y, v1.z, 0,
		v2.x, v2.y, v2.z, 0,
		v3.x, v3.y, v3.z, 0,
		0,
		0,
		0,
		1,
	};
	
	
 	HC_Set_Modelling_Matrix(matrix); 		
 	HC_Scale_Object(sData2.m_sScale.m_dX,sData2.m_sScale.m_dY,sData2.m_sScale.m_dZ);
	HC_Translate_Object(sData2.m_sOrigin.m_dX,sData2.m_sOrigin.m_dY,sData2.m_sOrigin.m_dZ);
   
	A3DMiscCartesianTransformationGet( NULL, &sData2 );
}	

void H3DXImporter::SetMatrix2(A3DMiscCartesianTransformationData sData2)
{
	HPoint v1(sData2.m_sXVector.m_dX, sData2.m_sXVector.m_dY,sData2.m_sXVector.m_dZ);
	HPoint v2(sData2.m_sYVector.m_dX, sData2.m_sYVector.m_dY,sData2.m_sYVector.m_dZ), v3;
	HC_Compute_Cross_Product(&v1, &v2, &v3);
	float matrix[16] = {
		v1.x, v1.y, v1.z, 0,
		v2.x, v2.y, v2.z, 0,
		v3.x, v3.y, v3.z, 0,
		sData2.m_sOrigin.m_dX,
		sData2.m_sOrigin.m_dY,
		sData2.m_sOrigin.m_dZ,
		1,
	};

	HC_Set_Modelling_Matrix(matrix); 		
}	



void H3DXImporter::parseRiCSys(A3DRiCoordinateSystem* p)
{
	A3DRiCoordinateSystemData sData;
	A3D_INITIALIZE_DATA(A3DRiCoordinateSystemData, sData);

	A3DInt32 iRet = A3DRiCoordinateSystemGet(p, &sData);
	
	if (iRet == A3D_SUCCESS ) {
		if (sData.m_pTransformation)
		{ 	
			SetMatrix(sData.m_pTransformation);		
		}	
		A3DRiCoordinateSystemGet(NULL, &sData);
 	} 
 
}

void H3DXImporter::parseRiPointSet(A3DRiPointSet* p)
{
	A3DRiPointSetData sData;
	A3D_INITIALIZE_DATA(A3DRiPointSetData, sData);

	A3DInt32 iRet = A3DRiPointSetGet(p, &sData);

	if (iRet == A3D_SUCCESS) {
		for(unsigned int i = 0; i < sData.m_uiSize; ++i){
			HC_Insert_Marker(sData.m_pPts[i].m_dX, sData.m_pPts[i].m_dY, sData.m_pPts[i].m_dZ);
		}
		A3DRiPointSetGet(NULL, &sData);
	} 
}

void H3DXImporter::parseRiCurve(A3DRiCurve* p)
{	
	A3DRiCurveData sData;
	A3D_INITIALIZE_DATA(A3DRiCurveData, sData);

	A3DInt32 iRet = A3DRiCurveGet(p, &sData);
	if (iRet == A3D_SUCCESS) {
		A3DRiCurveGet(NULL, &sData);
	} 
}


void H3DXImporter::parseRI(A3DRiRepresentationItem* p, A3DMiscCascadedAttributes* pFatherAttr, double modelscale)
{
	m_bHasBrepStructure = false;

	m_edgematcher->Restart();
	A3DMiscCascadedAttributes* pAttr;
	A3DMiscCascadedAttributesData sAttrData;
	A3DInt32 iRet = CreateAndPushCascadedAttributes(p, pFatherAttr, &pAttr, &sAttrData);
	A3DRootBaseData rootBase;
	A3D_INITIALIZE_DATA(A3DRootBaseData, rootBase);

	A3DRootBaseGet(p, &rootBase);

	if (sAttrData.m_bShow)
	{
		HC_Open_Segment(H_FORMAT_TEXT("Representation Item %d", HDB::GetUniqueID()));
		if (rootBase.m_pcName){
			H_UTF8 utf8;
			utf8.encodedText(rootBase.m_pcName);
			HC_Set_User_Data(_NAME, utf8.encodedText(), utf8.length() +1);
		}
		else {
			HC_Set_User_Data(_NAME, "node", 5);
		}
		parseAttributes(p);

		A3DEEntityType eType;

		iRet = A3DEntityGetType(p, &eType);

		switch(eType) {
		case kA3DTypeRiSet:
			parseRiSet(p, pAttr, modelscale);
		break;

		case kA3DTypeRiBrepModel:
			parseRiBrepModel(p);
		break;

		case kA3DTypeRiCurve:
			parseRiCurve(p);
			break;
		case kA3DTypeMiscCartesianTransformation:
		case kA3DTypeMiscEntityReference:
			iRet = iRet;
			break;
		case kA3DTypeRiCoordinateSystem:
			iRet = iRet;
			break;
		case kA3DTypeRiPointSet:
			parseRiPointSet(p);
		break;

#if 0
		case kA3DTypeRiDirection:
			parseRiDirection(p, father);
			break;
		case kA3DTypeRiCurve:
			parseRiCurve(p, father);
			break;
		case kA3DTypeRiCoordinateSystem:
			parseRiCSys(p, father);
			break;
		case kA3DTypeRiPlane:
			parseRiPlane(p, father);
			break;
		case kA3DTypeRiBrepModel:
			parseRiBrepModel(p, father);
			break;		
		case kA3DTypeRiPolyBrepModel:
			parseRiPolyBrepModel(p, father);
			break;
#endif
  		}

	 
		A3DRiRepresentationItemData sData;
		A3D_INITIALIZE_DATA(A3DRiRepresentationItemData, sData);	

		iRet = A3DRiRepresentationItemGet(p, &sData);
		if (iRet == A3D_SUCCESS) {
			parseTess(sData.m_pTessBase, p, pAttr, modelscale);
			parseRiCSys(sData.m_pCoordinateSystem);
			A3DRiRepresentationItemGet(NULL, &sData); // delete sData
		} 

		HC_Close_Segment();	
	}

	A3DMiscCascadedAttributesDelete(pAttr);
	A3DMiscCascadedAttributesGet(NULL, &sAttrData);
}


void H3DXImporter::treatReferenceOnTopology(A3DEntity* pEntity, const A3DMkpMarkup *pMarkup)
{
	A3DMiscReferenceOnTopologyData sData;
	A3D_INITIALIZE_DATA(A3DMiscReferenceOnTopologyData, sData);

	A3DInt32 iRet = A3DMiscReferenceOnTopologyGet(pEntity, &sData);
	if (iRet == A3D_SUCCESS)
	{
		for (A3DUns32 ui=0;ui<sData.m_uiSize;ui++)
		{
			if (m_PartFaces && m_pConnector && m_pPMIConnector)
			{
				vlist_t *entitylist = new_vlist(malloc, free);
				m_pConnector->GetHoopsEntities(m_PartFaces[sData.m_puiAdditionalIndexes[ui]], entitylist);
				START_LIST_ITERATION(HC_KEY, entitylist)
				{
					m_pPMIConnector->AddConnection((HC_KEY)temp, (void *)pMarkup);
				}
				END_LIST_ITERATION(entitylist);
				delete_vlist(entitylist);
 			}
 		}		
 		iRet = A3DMiscReferenceOnTopologyGet(NULL, &sData);
	}	
}

void H3DXImporter::treatReference(A3DEntity* pEntity, const A3DMkpMarkup *pMarkup)
{
	A3DEEntityType eType;
	A3DInt32 iRet = A3DEntityGetType(pEntity,&eType);
	switch (eType)
	{
	case kA3DTypeMkpMarkup:
		break;
	case kA3DTypeMiscReferenceOnTopology:
		treatReferenceOnTopology(pEntity, pMarkup);
		break;
	default:
		break;
	}	
}


void H3DXImporter::traverseMarkup(const A3DMkpMarkup *pMarkup)
{
	A3DMkpMarkupData sData;
	A3D_INITIALIZE_DATA(A3DMkpMarkupData, sData);

	HC_KEY markup_key;

	HC_Open_Segment_By_Key(m_markup_segment);
	{
		markup_key = HC_KOpen_Segment(H_FORMAT_TEXT("Markup %d", HDB::GetUniqueID()));
		{
			HC_Set_User_Options("hobject = pmi_markup, markup = true");
		}
		HC_Close_Segment();
	}
	HC_Close_Segment();

	if (m_pConnector)	
		m_pConnector->AddConnection(markup_key, (void *)pMarkup);

	A3DMkpMarkupGet(pMarkup, &sData);

	PMI::Entity * entity = 0;

	switch (sData.m_eType)
	{
		case kA3DMarkupTypeDatum:
		{
			entity = new PMI::DatumEntity(markup_key);
			PMI::DatumEntity * datum = (PMI::DatumEntity *)entity;
			
			switch (sData.m_eSubType)
			{
				case kA3DMarkupSubTypeDatumIdent:
					datum->SetDatumType(PMI::Datum::Identifier);
					break;
				case kA3DMarkupSubTypeDatumTarget:
					datum->SetDatumType(PMI::Datum::Target);
					break;
				default:
					datum->SetDatumType(PMI::Datum::Unknown);
			}
		} break;

		case kA3DMarkupTypeDimension:
		{
			entity = new PMI::DimensionEntity(markup_key);
			PMI::DimensionEntity * dimension = (PMI::DimensionEntity *)entity;

			dimension->SetDimensionType(PMI::Dimension::UnknownType);

			switch (sData.m_eSubType)
			{
				case kA3DMarkupSubTypeDimensionAngle:
					dimension->SetDimensionSubType(PMI::Dimension::AngleSubType);
					break;
				case kA3DMarkupSubTypeDimensionChamfer:
					dimension->SetDimensionSubType(PMI::Dimension::ChamferSubType);
					break;
				case kA3DMarkupSubTypeDimensionDiameter:
				case kA3DMarkupSubTypeDimensionDiameterCone:
				case kA3DMarkupSubTypeDimensionDiameterCylinder:
				case kA3DMarkupSubTypeDimensionDiameterEdge:
				case kA3DMarkupSubTypeDimensionDiameterTangent:
					dimension->SetDimensionSubType(PMI::Dimension::DiameterSubType);
					break;
				case kA3DMarkupSubTypeDimensionDistance:
				case kA3DMarkupSubTypeDimensionDistanceCumulate:
				case kA3DMarkupSubTypeDimensionDistanceOffset:
					dimension->SetDimensionSubType(PMI::Dimension::DistanceSubType);
					break;
				case kA3DMarkupSubTypeDimensionLength:
				case kA3DMarkupSubTypeDimensionLengthCircular:
				case kA3DMarkupSubTypeDimensionLengthCurvilinear:
					dimension->SetDimensionSubType(PMI::Dimension::LengthSubType);
					break;
				case kA3DMarkupSubTypeDimensionRadius:
				case kA3DMarkupSubTypeDimensionRadiusCylinder:
				case kA3DMarkupSubTypeDimensionRadiusEdge:
				case kA3DMarkupSubTypeDimensionRadiusTangent:
					dimension->SetDimensionSubType(PMI::Dimension::RadiusSubType);
					break;
				case kA3DMarkupSubTypeDimensionSlope:
					dimension->SetDimensionSubType(PMI::Dimension::SlopeSubType);
					break;
				default:
					dimension->SetDimensionSubType(PMI::Dimension::UnknownSubType);
			}
		} break;

		case kA3DMarkupTypeGdt:
		{
			// current data coming out of 3DX for FCFs makes it quite difficult to accurately determine components
			// of a FCF, so we just insert a generic entity (just text strings and polylines, no extra information)
			entity = new PMI::GenericEntity(markup_key);
		} break;

		case kA3DMarkupTypeRoughness:
		{
			entity = new PMI::RoughnessEntity(markup_key);

			PMI::RoughnessEntity * roughness = (PMI::RoughnessEntity *)entity;

			roughness->SetObtentionType(PMI::Roughness::Obtention::Unknown);
			roughness->SetApplicabilityType(PMI::Roughness::Applicability::Unknown);
			roughness->SetModeType(PMI::Roughness::Mode::Unknown);
		} break;

		case kA3DMarkupTypeText:
		{
			entity = new PMI::NoteEntity(markup_key);
		} break;

		default:
		{
			entity = new PMI::GenericEntity(markup_key);
		}
	}

	PmiPolylineArray leader_lines;
	for (unsigned int i = 0; i < sData.m_uiLeadersSize; i++)
	{
		PmiPolylineArray ith_leader_line;
		getLeaderLines(sData.m_ppLeaders[i], ith_leader_line);
		leader_lines.insert(leader_lines.end(), ith_leader_line.begin(), ith_leader_line.end());
	}

	if (leader_lines.size())
		entity->SetLeaderLines(leader_lines.size(), &leader_lines[0]);

#ifdef DEBUG_MARKUP_TYPES
	HC_Open_Segment_By_Key(markup_key);
	{
		HC_Set_User_Options(H_FORMAT_TEXT("markup_type = %s", markupTypes[sData.m_eType]));
		char const ** specificMarkupSubTypes;
		switch (sData.m_eType) {
			case kA3DMarkupTypeDatum: {
				specificMarkupSubTypes = markupDatumSubTypes;
			} break;

			case kA3DMarkupTypeDimension: {
				specificMarkupSubTypes = markupDimensionSubTypes;
			} break;

			case kA3DMarkupTypeGdt: {
				specificMarkupSubTypes = markupGdtSubTypes;
			} break;

			case kA3DMarkupTypeWelding: {
				specificMarkupSubTypes = markupWeldingSubTypes;
			} break;

			case kA3DMarkupTypeOther: {
				specificMarkupSubTypes = markupOtherSubTypes;
			} break;

			default: {
				specificMarkupSubTypes = markupSubTypes;
			}
		}
		HC_Set_User_Options(H_FORMAT_TEXT("markup_subtype = %s", specificMarkupSubTypes[sData.m_eSubType]));
	}
	HC_Close_Segment();
#endif // DEBUG_MARKUP_TYPES

	if (GetDLLVersion() >= 202)
	{
		for (unsigned int j=0;j<sData.m_uiLinkedItemsSize;j++)
		{	
			A3DMiscMarkupLinkedItemData sData2;
			A3D_INITIALIZE_DATA(A3DMiscMarkupLinkedItemData, sData2);

			A3DInt32 iErr = A3DMiscMarkupLinkedItemGet(sData.m_ppLinkedItems[j], &sData2);

 			if (sData2.m_pReference)
				treatReference(sData2.m_pReference, pMarkup);

			A3DMiscMarkupLinkedItemGet(NULL, &sData2);
 		}
	}

	A3DTessBaseData sBaseData;
	A3D_INITIALIZE_DATA(A3DTessBaseData, sBaseData);

	A3DTessBaseGet(sData.m_pTessellation, &sBaseData);

	A3DMkpMarkupGet(NULL, &sData);

	A3DTessMarkupData sMarkupData;
	A3D_INITIALIZE_DATA(A3DTessMarkupData, sMarkupData);

	A3DTessMarkupGet(sData.m_pTessellation, &sMarkupData);

	PmiPolylineArray polylines;
	PmiStringArray strings;
	PmiTextAttributesArray text_attributes;

	getMarkupTesselation(&sBaseData, &sMarkupData, polylines, strings, text_attributes);

	A3DTessMarkupGet(NULL, &sMarkupData);
	A3DTessBaseGet(NULL, &sBaseData);

	if (polylines.size())
	{
		PMI::Frame frame;
		frame.SetPolylines(polylines.size(), &polylines[0]);
		entity->SetFrame(frame);
	}

	assert(strings.size() == text_attributes.size());
	unsigned int count = strings.size();

	switch (entity->GetType())
	{
		case PMI::DatumType:
		{
			PMI::DatumEntity * datum = (PMI::DatumEntity *)entity;
		
			if (count)
				datum->SetLabels(count, &strings[0], &text_attributes[0]);
		} break;

		case PMI::DimensionType:
		{
			PMI::DimensionEntity * dimension = (PMI::DimensionEntity *)entity;

			if (count)
				dimension->SetStrings(count, &strings[0], &text_attributes[0]);
		} break;

		case PMI::GenericType:
		{
			PMI::GenericEntity * generic = (PMI::GenericEntity *)entity;

			if (count)
				generic->SetStrings(count, &strings[0], &text_attributes[0]);
		} break;

		case PMI::NoteType:
		{
			PMI::NoteEntity * note = (PMI::NoteEntity *)entity;

			if (count)
				note->SetStrings(count, &strings[0], &text_attributes[0]);
		} break;

		case PMI::RoughnessType:
		{
			PMI::RoughnessEntity * roughness = (PMI::RoughnessEntity *)entity;

			if (count)
				roughness->SetFields(count, &strings[0], &text_attributes[0]);
		} break;
	}

	m_pmi_entities.push_back(*entity);

	delete entity;
}



void H3DXImporter::getLeaderLines(const A3DMkpLeader *pMarkup, PmiPolylineArray & out_leader_lines)
{
	A3DMkpLeaderData sData;
	A3D_INITIALIZE_DATA(A3DMkpLeaderData, sData);

	A3DMkpLeaderGet(pMarkup, &sData);

	A3DTessBaseData sBaseData;
	A3D_INITIALIZE_DATA(A3DTessBaseData, sBaseData);

	A3DTessBaseGet(sData.m_pTessellation, &sBaseData);

	A3DTessMarkupData sMarkupData;
	A3D_INITIALIZE_DATA(A3DTessMarkupData, sMarkupData);

	A3DInt32 iErr = A3DTessMarkupGet(sData.m_pTessellation, &sMarkupData);
	if (!iErr && sData.m_pTessellation)
	{
		PmiStringArray strings;
		PmiTextAttributesArray text_attributes;

		getMarkupTesselation(&sBaseData, &sMarkupData, out_leader_lines, strings, text_attributes);
	}

	A3DTessMarkupGet(NULL, &sMarkupData);
	A3DTessBaseGet(NULL, &sBaseData);
 	A3DMkpLeaderGet(NULL, &sData);
}


void H3DXImporter::traverseAnnotationItem(const A3DMkpAnnotationItem *pAnnot)
{
	A3DMkpAnnotationItemData sData;
	A3D_INITIALIZE_DATA(A3DMkpAnnotationItemData, sData);

	A3DMkpAnnotationItemGet(pAnnot, &sData);

	HC_KEY tester = 0;
	int res = vhash_lookup_item(m_annotationhash, (void *)sData.m_pMarkup, (void **)&tester);
	if (!(res == VHASH_STATUS_SUCCESS))
	{			
		vhash_insert_item(m_annotationhash, (void *)sData.m_pMarkup, (void *)tester);
		m_AnnotationCounter++;
		traverseMarkup(sData.m_pMarkup);
	}
}



void H3DXImporter::traverseAnnotationSet(const A3DMkpAnnotationSet *pAnnot)
{
	A3DMkpAnnotationSetData sData;
	A3D_INITIALIZE_DATA(A3DMkpAnnotationSetData, sData);

	A3DMkpAnnotationSetGet(pAnnot, &sData);
	for (A3DUns32 i = 0; i < sData.m_uiAnnotationsSize; ++i)
	{
		HC_KEY tester = 0;
 		int res = vhash_lookup_item(m_annotationhash, (void *)sData.m_ppAnnotations[i] ,  (void **)&tester);
		if (!(res == VHASH_STATUS_SUCCESS))
		{			
			vhash_insert_item(m_annotationhash, (void *)sData.m_ppAnnotations[i]  , (void *)tester);
			traverseAnnotation(sData.m_ppAnnotations[i]);
		}
 	}

	A3DMkpAnnotationSetGet(NULL, &sData);
}

void H3DXImporter::traverseAnnotationReference(const A3DMkpAnnotationReference *pAnnot)
{
	A3DMkpAnnotationReferenceData sData;
	A3D_INITIALIZE_DATA(A3DMkpAnnotationReferenceData, sData);

	A3DMkpAnnotationReferenceGet(pAnnot, &sData);
	if (GetDLLVersion() >= 202)
	{

		for (unsigned int i=0;i<sData.m_uiLinkedItemsSize;i++)
		{
			A3DMiscMarkupLinkedItemData sData2;
			A3D_INITIALIZE_DATA(A3DMiscMarkupLinkedItemData, sData2);

			A3DInt32 iErr = A3DMiscMarkupLinkedItemGet(sData.m_ppLinkedItems[i], &sData2);
  		}
	}

	A3DMkpAnnotationReferenceGet(NULL, &sData);
}


void  H3DXImporter::parseAttributes(const A3DEntity* pEntity)
{
	A3DRootBaseData rootbaseData;
	A3D_INITIALIZE_DATA(A3DRootBaseData, rootbaseData);

	A3DInt32 iRet = A3DRootBaseGet(pEntity,&rootbaseData);

	for (unsigned int i=0;i<rootbaseData.m_uiSize;i++)
	{
		char text[MVO_BUFFER_SIZE];		
		A3DMiscAttributeData attributeData;
		A3D_INITIALIZE_DATA(A3DMiscAttributeData, attributeData);

		A3DMiscAttributeGet(rootbaseData.m_ppAttributes[i],&attributeData);
		if (attributeData.m_bTitleIsInt)
			sprintf(text, "Title%d = %d", i, attributeData.m_pcTitle);
		else
			sprintf(text, "Title%d = `%s`", i,attributeData.m_pcTitle);
		HC_Set_User_Options(text);
		for (unsigned int j=0;j<attributeData.m_uiSize;j++)
		{
			if (attributeData.m_pSingleAttributesData[j].m_pcTitle || attributeData.m_pSingleAttributesData[j].m_pcData)
			{
				char title[MVO_BUFFER_SIZE];
				if (!attributeData.m_pSingleAttributesData[j].m_pcTitle)
					strcpy(title,"NoTitle");
				else
					strcpy(title,attributeData.m_pSingleAttributesData[j].m_pcTitle);
				
				if (attributeData.m_pSingleAttributesData[j].m_eType == kA3DModellerAttributeTypeString)									
					sprintf(text, "%s%d-%d = `%s`", title, i, j, attributeData.m_pSingleAttributesData[j].m_pcData);				
				else  if (attributeData.m_pSingleAttributesData[j].m_eType == kA3DModellerAttributeTypeInt)
					sprintf(text, "%s%d-%d = %d", title, i, j,(int)attributeData.m_pSingleAttributesData[j].m_pcData);

				HC_Set_User_Options(text);
			}
		}
	}
}


void H3DXImporter::traverseAnnotation(const A3DMkpAnnotationEntity *pAnnot)
{
	A3DEEntityType eType;
	A3DInt32 iErr = A3DEntityGetType(pAnnot, &eType);
	HC_Open_Segment(H_FORMAT_TEXT("Annotation %d", HDB::GetUniqueID()));
	{
		switch (eType)
		{
			case kA3DTypeMkpAnnotationItem:
				traverseAnnotationItem(pAnnot);
				break;
			case kA3DTypeMkpAnnotationReference:
				traverseAnnotationReference(pAnnot);
				break;
			case kA3DTypeMkpAnnotationSet:
				traverseAnnotationSet(pAnnot);
				break;
			default:
				break;
		}
	}
	HC_Close_Segment();
}

static int viewcount = 0;
void H3DXImporter::traverseView(const A3DMkpView *pView)
{
	A3DMkpViewData sData;
	A3D_INITIALIZE_DATA(A3DMkpViewData, sData);

	A3DSurfPlaneData sData2;
	A3D_INITIALIZE_DATA(A3DSurfPlaneData, sData2);

	char text[256];

	sprintf(text, "view%d", viewcount++);
	HC_KEY mainview = HC_KOpen_Segment(text);
	{
		HC_Set_Visibility("lines = on, text = on");

		A3DMkpViewGet(pView, &sData);
		
		A3DSurfPlaneGet(sData.m_pPlane, &sData2);

		m_AnnotationCounter = 0;
		assert(m_pmi_entities.size() == 0);

 		for (unsigned int i=0;i<sData.m_uiAnnotationsSize;i++)
		{
			HC_KEY tester = 0;
			int res = vhash_lookup_item(m_annotationhash, (void *)sData.m_ppAnnotations[i] ,  (void **)&tester);
			if (!(res == VHASH_STATUS_SUCCESS))
			{			
 				vhash_insert_item(m_annotationhash, (void *)sData.m_ppAnnotations[i]  , (void *)tester);
				traverseAnnotation(sData.m_ppAnnotations[i]);
			}
 		}
	}
	HC_Close_Segment();

	if (!m_AnnotationCounter)
		HC_Delete_By_Key(mainview);

	if (m_pmi_entities.size())
	{
		PMI::ViewEntity view(mainview);

		A3DRootBaseData rootbaseData;
		A3D_INITIALIZE_DATA(A3DRootBaseData, rootbaseData);

		A3DInt32 iRet = A3DRootBaseGet(pView, &rootbaseData);

		if (rootbaseData.m_pcName)
		{
			H_UTF8 utf8;
			utf8.encodedText(rootbaseData.m_pcName);

			view.SetName(PMI::String(utf8));
		}

		iRet = A3DRootBaseGet(NULL, &rootbaseData);

		if (sData.m_pSceneDisplayParameters)
		{
			A3DGraphSceneDisplayParametersData sceneData;
			A3D_INITIALIZE_DATA(A3DGraphSceneDisplayParametersData, sceneData);

			iRet = A3DGraphSceneDisplayParametersGet(sData.m_pSceneDisplayParameters, &sceneData);

			if (sceneData.m_pCamera)
			{
				PMI::Camera cam;
				A3DGraphCameraData camData;
				A3D_INITIALIZE_DATA(A3DGraphCameraData, camData);

				iRet = A3DGraphCameraGet(sceneData.m_pCamera, &camData);

				PMI::Point cam_pos(camData.m_sLocation.m_dX, camData.m_sLocation.m_dY, camData.m_sLocation.m_dZ);
				PMI::Point cam_tar(camData.m_sLookAt.m_dX, camData.m_sLookAt.m_dY, camData.m_sLookAt.m_dZ);
				PMI::Point cam_upv(camData.m_sUp.m_dX, camData.m_sUp.m_dY, camData.m_sUp.m_dZ);
				float cam_f_w = 0;
				float cam_f_h = 0;
				char const * cam_proj = (camData.m_bOrthographic ? "orthographic" : "perspective");

				if (camData.m_bOrthographic)
				{
					PMI::Point tp;
					PMI::Point v;
					PMI::Point view_vec = cam_tar - cam_pos;
					float neg_origin[16] = { 0 };
					float pos_origin[16] = { 0 };
					float matrix[16] = { 0 };

					HC_Compute_Translation_Matrix(-cam_pos.x, -cam_pos.y, -cam_pos.z, neg_origin);
					HC_Compute_Translation_Matrix(cam_pos.x, cam_pos.y, cam_pos.z, pos_origin);

					HC_Compute_Offaxis_Rotation(cam_upv.x, cam_upv.y, cam_upv.z, camData.m_dXFovy * 0.5, matrix);
					HC_Compute_Matrix_Product(neg_origin, matrix, matrix);
					HC_Compute_Matrix_Product(matrix, pos_origin, matrix);
					HC_Compute_Transformed_Points(1, &cam_tar, matrix, &tp);

					v = tp - cam_pos;

					double n_dot_t = HC_Compute_Dot_Product(&view_vec, &cam_tar);
					double n_dot_p = HC_Compute_Dot_Product(&view_vec, &cam_pos);
					double n_dot_v = HC_Compute_Dot_Product(&view_vec, &v);
					float t = (float)((n_dot_t - n_dot_p) / n_dot_v);

					PMI::Point fa = cam_pos + v * t;
					PMI::Point fb = cam_tar * 2 - fa;
					PMI::Point dv = fb - fa;

					cam_f_w = sqrt(dv.x * dv.x + dv.y * dv.y + dv.z * dv.z);

					PMI::Point view_cross_up;

					HC_Compute_Cross_Product(&view_vec, &cam_upv, &view_cross_up);

					HC_Compute_Offaxis_Rotation(view_cross_up.x, view_cross_up.y, view_cross_up.z, camData.m_dYFovy * 0.5, matrix);
					HC_Compute_Matrix_Product(neg_origin, matrix, matrix);
					HC_Compute_Matrix_Product(matrix, pos_origin, matrix);
					HC_Compute_Transformed_Points(1, &cam_tar, matrix, &tp);

					v = tp - cam_pos;

					n_dot_t = HC_Compute_Dot_Product(&view_vec, &cam_tar);
					n_dot_p = HC_Compute_Dot_Product(&view_vec, &cam_pos);
					n_dot_v = HC_Compute_Dot_Product(&view_vec, &v);
					t = (float)((n_dot_t - n_dot_p) / n_dot_v);

					fa = cam_pos + v * t;
					fb = cam_tar * 2 - fa;
					dv = fb - fa;

					cam_f_h = sqrt(dv.x * dv.x + dv.y * dv.y + dv.z * dv.z);					
				}
				else
				{
					cam_f_w = camData.m_dXFovy;
					cam_f_h = camData.m_dYFovy;
				}

				view.SetCamera(cam_pos, cam_tar, cam_upv, cam_f_w, cam_f_h, cam_proj);

				iRet = A3DGraphCameraGet(NULL, &camData);
			}

			iRet = A3DGraphSceneDisplayParametersGet(NULL, &sceneData);
		}

		view.SetAssociatedEntities(m_pmi_entities.size(), &m_pmi_entities[0]);
		m_pmi_entities.clear();

		HC_Open_Segment_By_Key(mainview);
		{
			float matrix[16] = { 0 };
			float inv_matrix[16] = { 0 };

			SetMatrix2(sData2.m_sTrsf);
			HC_Show_Modelling_Matrix(matrix);
			HC_UnSet_Modelling_Matrix();

			HC_Compute_Matrix_Inverse(matrix, inv_matrix);

			HPoint min_max[2];

			HC_Compute_Circumcuboid(".", &min_max[0], &min_max[1]);

			HC_Compute_Transformed_Points(2, min_max, inv_matrix, min_max);

			min_max[0].z = 0;
			min_max[0].z = 0;

			HPoint delta = min_max[1] - min_max[0];
			float min_x = min_max[0].x - delta.x / 6;
			float min_y = min_max[0].y - delta.y / 6;
			float max_x = min_max[1].x + delta.x / 6;
			float max_y = min_max[1].y + delta.y / 6;

			PMI::Point frame_points[5] = { PMI::Point(min_x, min_y, 0), PMI::Point(max_x, min_y, 0), PMI::Point(max_x, max_y, 0),
					PMI::Point(min_x, max_y, 0), PMI::Point(min_x, min_y, 0) };

			PMI::Polyline frame_polyline;
			PMI::Frame view_frame;

			HC_Compute_Transformed_Points(5, frame_points, matrix, frame_points);

			HC_Define_Line_Style("myLineStyle", "3.0 oru dash, 3.0 oru blank");

			frame_polyline.SetPoints(5, frame_points);
			frame_polyline.SetRGBColor(1, 1, 0); // yellow
			frame_polyline.SetLinePattern("myLineStyle");
			view_frame.SetPolylines(1, &frame_polyline);

			view.SetFrame(view_frame);
		}
		HC_Close_Segment();
	}

	A3DSurfPlaneGet(NULL, &sData2);
	A3DMkpViewGet(NULL, &sData);
}

void H3DXImporter::parsePart(A3DAsmPartDefinition* p, A3DMiscCascadedAttributes* pFatherAttr, double modelscale)
{
 	A3DRootBaseData rootBase;
	A3D_INITIALIZE_DATA(A3DRootBaseData, rootBase);

	A3DRootBaseGet(p, &rootBase);

	HC_Open_Segment(H_FORMAT_TEXT("Part %d", HDB::GetUniqueID()));
	if (rootBase.m_pcName)
	{
		H_UTF8 utf8;
		utf8.encodedText(rootBase.m_pcName);
		HC_Set_User_Data(_NAME, utf8.encodedText(), utf8.length() +1);
	}
	else {
		HC_Set_User_Data(_NAME, "node", 5);
	}

	parseAttributes(p);

	A3DMiscCascadedAttributes* pAttr;
	A3DMiscCascadedAttributesData sAttrData;

	A3DInt32 iRet = CreateAndPushCascadedAttributes(p, pFatherAttr, &pAttr, &sAttrData);

	A3DAsmPartDefinitionData sData;
	A3D_INITIALIZE_DATA(A3DAsmPartDefinitionData, sData);

	iRet = A3DAsmPartDefinitionGet(p, &sData);

	if (iRet == A3D_SUCCESS) {
	
		unsigned int i;

	
		m_PartFaces = 0;
		m_body_scale = -1.0;

		m_brepfacelist = new_vlist(malloc,free);
		for (A3DUns32 ui = 0; ui < sData.m_uiRepItemsSize; ++ui)
			parseRI(sData.m_ppRepItems[ui], pAttr, modelscale);
		delete_vlist(m_brepfacelist);		
		
 
		

		for (i = 0; i < sData.m_uiViewsSize; ++i)
			traverseView(sData.m_ppViews[i]);

		// deal only with remaining markups not attached to a view
		assert(m_pmi_entities.size() == 0);

		for (i = 0; i < sData.m_uiAnnotationsSize; ++i)
		{
			HC_KEY tester = 0;
			int res = vhash_lookup_item(m_annotationhash, (void *)sData.m_ppAnnotations[i], (void **)&tester);
			if (!(res == VHASH_STATUS_SUCCESS))
			{
				tester = 1;
				vhash_insert_item(m_annotationhash, (void *)sData.m_ppAnnotations[i], (void *)tester);
				traverseAnnotation(sData.m_ppAnnotations[i]);			
			}
 		}
		
		if (m_pmi_entities.size())
		{
			for (unsigned int j = 0; j < m_pmi_entities.size(); j++)
			{
				HC_KEY annotation_key = m_pmi_entities[j].GetSegmentKey();

				if (annotation_key != INVALID_KEY)
					HC_Include_Segment_By_Key(annotation_key);
			}

			m_pmi_entities.clear();
		}

		A3DAsmPartDefinitionGet(NULL, &sData);

		delete [] m_PartFaces;
	} 
 
	HC_Close_Segment();

	A3DMiscCascadedAttributesDelete(pAttr);
	A3DMiscCascadedAttributesGet(NULL, &sAttrData);
}

A3DInt32 H3DXImporter::productOccurrenceGetExternalData(A3DAsmProductOccurrenceData const * psPOccData,
													   A3DAsmProductOccurrence *& pExternalData)
{
	if (psPOccData == NULL)
		return A3D_ERROR;

	A3DInt32 iRet = A3D_SUCCESS;

	if (psPOccData->m_pExternalData == NULL && psPOccData->m_pPrototype != NULL)
	{
		A3DAsmProductOccurrenceData sProductPrototypeData;
		A3D_INITIALIZE_DATA(A3DAsmProductOccurrenceData, sProductPrototypeData);

		iRet = A3DAsmProductOccurrenceGet(psPOccData->m_pPrototype, &sProductPrototypeData);

		iRet = productOccurrenceGetExternalData(&sProductPrototypeData, pExternalData);

		iRet = A3DAsmProductOccurrenceGet(NULL, &sProductPrototypeData);
	}
	else
		pExternalData = psPOccData->m_pExternalData;

	return iRet;
}

A3DInt32 H3DXImporter::productOccurrenceGetLocation(A3DAsmProductOccurrenceData const * psPOccData,
												   A3DMiscCartesianTransformation *& pLocation)
{
	if (psPOccData == NULL)
		return A3D_ERROR;

	A3DInt32 iRet = A3D_SUCCESS;

	A3DAsmProductOccurrence * pExternal = NULL;
	iRet = productOccurrenceGetExternalData(psPOccData, pExternal);
	if (pExternal != NULL)
	{
		A3DAsmProductOccurrenceData sExternalDataData;
		A3D_INITIALIZE_DATA(A3DAsmProductOccurrenceData, sExternalDataData);

		iRet = A3DAsmProductOccurrenceGet(pExternal, &sExternalDataData);

		if (sExternalDataData.m_pLocation != NULL)
			pLocation = sExternalDataData.m_pLocation;

		iRet = A3DAsmProductOccurrenceGet(NULL, &sExternalDataData);
	}
	else if (psPOccData->m_pLocation == NULL && psPOccData->m_pPrototype != NULL)
	{
		A3DAsmProductOccurrenceData sPrototypeData;
		A3D_INITIALIZE_DATA(A3DAsmProductOccurrenceData, sPrototypeData);

		iRet = A3DAsmProductOccurrenceGet(psPOccData->m_pPrototype, &sPrototypeData);

		A3DMiscCartesianTransformation * pPrototypeLocation = NULL;
		iRet = productOccurrenceGetLocation(&sPrototypeData, pPrototypeLocation);
		pLocation = pPrototypeLocation;

		iRet = A3DAsmProductOccurrenceGet(NULL, &sPrototypeData);
	}
	else
		pLocation = psPOccData->m_pLocation;

	return iRet;
}

bool H3DXImporter::prototypeGetPartRecursive(A3DAsmProductOccurrence * prototype, 
											 A3DMiscCascadedAttributes * pAttr, 
											 double modelscale,
											 bool use_external_data)
{
	bool added_part = false;

	if (prototype == NULL)
		return false;

#ifdef USE_INSTANCING
	POccurrenceKeyHash::status hash_status = (use_external_data ?
												m_dead_external_part_hash.LookupItem(prototype) :
												m_dead_part_hash.LookupItem(prototype));

	// if the item was in a dead hash, that path contains no geometry
	if (hash_status == POccurrenceKeyHash::Success)
		return false;

	HC_KEY prototype_key = INVALID_KEY;
		
	hash_status = (use_external_data ? 
					m_external_part_key_hash.LookupItem(prototype, &prototype_key) :
					m_part_key_hash.LookupItem(prototype, &prototype_key));

	if (hash_status == POccurrenceKeyHash::Failed)
	{
		HC_Open_Segment_By_Key(m_modelKey);
		{
			HC_Open_Segment("model_include");
			{
				prototype_key = HC_KCreate_Segment(H_FORMAT_TEXT("Prototype GPR %d", HDB::GetUniqueID()));
			}
			HC_Close_Segment();
		}
		HC_Close_Segment();
	}

	HC_KEY include_key = HC_KInclude_Segment_By_Key(prototype_key);

	if (hash_status == POccurrenceKeyHash::Success)
		return true;

	HC_Open_Segment_By_Key(prototype_key);
#endif // USE_INSTANCING

	A3DAsmProductOccurrenceData sProductPrototypeData;
	A3D_INITIALIZE_DATA(A3DAsmProductOccurrenceData, sProductPrototypeData);

	A3DInt32 iRet = A3DAsmProductOccurrenceGet(prototype, &sProductPrototypeData);

	if (!use_external_data && sProductPrototypeData.m_pPart)
	{
		parsePart(sProductPrototypeData.m_pPart, pAttr, modelscale);
		added_part = true;
	}
	else if (use_external_data && sProductPrototypeData.m_pExternalData)
	{
		A3DAsmProductOccurrenceData sData;
		A3D_INITIALIZE_DATA(A3DAsmProductOccurrenceData, sData);

		iRet = A3DAsmProductOccurrenceGet(sProductPrototypeData.m_pExternalData, &sData);

		if (sData.m_pPart)
		{
			parsePart(sData.m_pPart, pAttr, modelscale);
			added_part = true;
		}

		iRet = A3DAsmProductOccurrenceGet(NULL, &sData);
	}
	else
	{
		added_part = prototypeGetPartRecursive(sProductPrototypeData.m_pPrototype, pAttr, modelscale, use_external_data);
	}

	iRet = A3DAsmProductOccurrenceGet(NULL, &sProductPrototypeData);

#ifdef USE_INSTANCING
	HC_Close_Segment();

	if (added_part)
	{
		(use_external_data ?
			m_external_part_key_hash.InsertItem(prototype, prototype_key) :
			m_part_key_hash.InsertItem(prototype, prototype_key));
	}
	else
	{
		HC_Delete_By_Key(include_key);
		HC_Delete_By_Key(prototype_key);

		(use_external_data ?
			m_dead_external_part_hash.InsertItem(prototype) :
			m_dead_part_hash.InsertItem(prototype));
	}
#endif // USE_INSTANCING

	return added_part;
}

void H3DXImporter::productOccurrenceGetPart(A3DAsmProductOccurrenceData const * psPOccData, 
											A3DMiscCascadedAttributes * pAttr, 
											double modelscale)
{
	if (psPOccData == NULL)
		return;

	A3DInt32 iRet = A3D_SUCCESS;

	if (psPOccData->m_pPart != NULL)
	{
		parsePart(psPOccData->m_pPart, pAttr, modelscale);
		return;
	}

	if (prototypeGetPartRecursive(psPOccData->m_pPrototype, pAttr, modelscale, false))
		return;

	if (psPOccData->m_uiPOccurrencesSize == 0)
	{
		if (psPOccData->m_pExternalData)
		{
			A3DAsmProductOccurrenceData sData;
			A3D_INITIALIZE_DATA(A3DAsmProductOccurrenceData, sData);

			iRet = A3DAsmProductOccurrenceGet(psPOccData->m_pExternalData, &sData);

			if (sData.m_pPart)
				parsePart(sData.m_pPart, pAttr, modelscale);

			iRet = A3DAsmProductOccurrenceGet(NULL, &sData);
		}
		else
		{
			prototypeGetPartRecursive(psPOccData->m_pPrototype, pAttr, modelscale, true);
		}
	}
}

bool H3DXImporter::prototypeGetOccurrencesRecursive(A3DAsmProductOccurrence * prototype,
													A3DMiscCascadedAttributes * pAttr,
													double modelscale)
{
	bool added_occurrences = false;

	if (prototype == NULL)
		return false;

#ifdef USE_INSTANCING
	POccurrenceKeyHash::status hash_status = m_dead_poccurrence_hash.LookupItem(prototype);

	// if the item was in a dead hash, that path contains no geometry
	if (hash_status == POccurrenceKeyHash::Success)
		return false;

	HC_KEY prototype_key = INVALID_KEY;

	hash_status = m_poccurrence_key_hash.LookupItem(prototype, &prototype_key);

	if (hash_status == POccurrenceKeyHash::Failed)
	{
		HC_Open_Segment_By_Key(m_modelKey);
		{
			HC_Open_Segment("model_include");
			{
				prototype_key = HC_KCreate_Segment(H_FORMAT_TEXT("Prototype GOR %d", HDB::GetUniqueID()));
			}
			HC_Close_Segment();
		}
		HC_Close_Segment();
	}

	HC_KEY include_key = HC_KInclude_Segment_By_Key(prototype_key);

	if (hash_status == POccurrenceKeyHash::Success)
		return true;

	HC_Open_Segment_By_Key(prototype_key);
#endif // USE_INSTANCING

	A3DAsmProductOccurrenceData sProductPrototypeData;
	A3D_INITIALIZE_DATA(A3DAsmProductOccurrenceData, sProductPrototypeData);

	A3DInt32 iRet = A3DAsmProductOccurrenceGet(prototype, &sProductPrototypeData);

	if (sProductPrototypeData.m_uiPOccurrencesSize)
	{
		for (unsigned int ui = 0; ui < sProductPrototypeData.m_uiPOccurrencesSize; ui++)
			parsePOccurrence(sProductPrototypeData.m_ppPOccurrences[ui], pAttr, modelscale);

		added_occurrences = true;
	}
	else
	{
		added_occurrences = prototypeGetOccurrencesRecursive(sProductPrototypeData.m_pPrototype, pAttr, modelscale);
	}

#ifdef USE_INSTANCING
	HC_Close_Segment();

	if (added_occurrences)
	{
		m_poccurrence_key_hash.InsertItem(prototype, prototype_key);
	}
	else
	{
		HC_Delete_By_Key(include_key);
		HC_Delete_By_Key(prototype_key);

		m_dead_poccurrence_hash.InsertItem(prototype);
	}
#endif // USE_INSTANCING

	return added_occurrences;
}

void H3DXImporter::productOccurrenceGetChildren(A3DAsmProductOccurrenceData const * psPOccData,
												A3DMiscCascadedAttributes * pAttr,
												double modelscale)
{
	if (psPOccData == NULL)
		return;

	bool added_occurrences = false;

	if (psPOccData->m_uiPOccurrencesSize)
	{
		for (unsigned int ui = 0; ui < psPOccData->m_uiPOccurrencesSize; ui++)
			parsePOccurrence(psPOccData->m_ppPOccurrences[ui], pAttr, modelscale);

		added_occurrences = true;
	}
	else
	{
		added_occurrences = prototypeGetOccurrencesRecursive(psPOccData->m_pPrototype, pAttr, modelscale);
	}

	A3DAsmProductOccurrence * pExternal = NULL;
	A3DInt32 iRet = productOccurrenceGetExternalData(psPOccData, pExternal);
	if (pExternal != NULL)
	{
		A3DAsmProductOccurrenceData sExternalDataData;
		A3D_INITIALIZE_DATA(A3DAsmProductOccurrenceData, sExternalDataData);

		iRet = A3DAsmProductOccurrenceGet(pExternal, &sExternalDataData);

		if (added_occurrences)
			parsePOccurrence(pExternal, pAttr, modelscale);
		else
			productOccurrenceGetChildren(&sExternalDataData, pAttr, modelscale);

		iRet = A3DAsmProductOccurrenceGet(NULL, &sExternalDataData);
	}
}
 
void H3DXImporter::parsePOccurrence(A3DAsmProductOccurrence * p, 
									A3DMiscCascadedAttributes * pFatherAttr, 
									double modelscale)
{ 
	A3DRootBaseData rootBase;
	A3D_INITIALIZE_DATA(A3DRootBaseData, rootBase);

	A3DRootBaseGet(p, &rootBase);	

	HC_Open_Segment(H_FORMAT_TEXT("Product Occurrence %d", HDB::GetUniqueID()));
	{
		parseAttributes(p);

		A3DMiscCascadedAttributes* pAttr;
		A3DMiscCascadedAttributesData sAttrData;
		A3DInt32 iRet = CreateAndPushCascadedAttributes(p, pFatherAttr, &pAttr, &sAttrData);
		SetMaterial(&sAttrData);

		A3DAsmProductOccurrenceData sData;
		A3D_INITIALIZE_DATA(A3DAsmProductOccurrenceData, sData);

		iRet = A3DAsmProductOccurrenceGet(p, &sData);
		modelscale = (sData.m_bUnitFromCAD ? sData.m_dUnit : 1.0);

		if (iRet == A3D_SUCCESS)
		{
			A3DMiscCartesianTransformation * pLocation = NULL;
			iRet = productOccurrenceGetLocation(&sData, pLocation);

			if (pLocation)
				SetMatrix(pLocation);

			if (rootBase.m_pcName)
			{
				H_UTF8 utf8;
				utf8.encodedText(rootBase.m_pcName);
				HC_Set_User_Data(_NAME, utf8.encodedText(), utf8.length() +1);
			}
			else {
				HC_Set_User_Data(_NAME, "part", 5);
			}

			productOccurrenceGetPart(&sData, pAttr, modelscale);
			productOccurrenceGetChildren(&sData, pAttr, modelscale);

			assert(m_pmi_entities.size() == 0);

			for (unsigned int i = 0; i < sData.m_uiAnnotationsSize; ++i)
				traverseAnnotation(sData.m_ppAnnotations[i]);

 			if (m_pmi_entities.size())
			{
				HC_Open_Segment("pmi");	
				HC_Set_Visibility("lines = on, text = on");

				for (unsigned int j = 0; j < m_pmi_entities.size(); j++)
				{
					HC_KEY annotation_key = m_pmi_entities[j].GetSegmentKey();

					if (annotation_key != INVALID_KEY)
						HC_Include_Segment_By_Key(annotation_key);
				}
				HC_Close_Segment();

				m_pmi_entities.clear();
			}

			A3DAsmProductOccurrenceGet(NULL, &sData);
			
		}
		
		A3DMiscCascadedAttributesDelete(pAttr);
		A3DMiscCascadedAttributesGet(NULL, &sAttrData);
			
	}
	HC_Close_Segment();
}

void H3DXImporter::PopulateTextures()						
{
	InitializeMagick(".");

	HC_Set_Visibility("image = off");

	A3DGlobal * pGlobal = NULL;
	A3DInt32 iRet = A3DGlobalGetPointer(&pGlobal);

	A3DGlobalData globalData;
	A3D_INITIALIZE_DATA(A3DGlobalData, globalData);

	iRet = A3DGlobalGet(pGlobal, &globalData);

	/* This while loop is loading all the images. */
	VArray<unsigned char> pixels;
	A3DGraphPictureData image_data;
	A3D_INITIALIZE_DATA(A3DGraphPictureData, image_data);

	for (unsigned int ui = 0; ui < globalData.m_uiPicturesSize; ui++)
 	{
		iRet = A3DGlobalGetGraphPictureData(ui, &image_data);

		if (image_data.m_eFormat == kA3DPictureBitmapRgbaByte)
		{
	 		InvertImage(image_data.m_pucBinaryData, image_data.m_uiPixelWidth, image_data.m_uiPixelHeight,  true);
			HC_Insert_Image (0.0, 0.0, 0.0, H_FORMAT_TEXT("rgba, name = image %u", ui), image_data.m_uiPixelWidth, image_data.m_uiPixelHeight, image_data.m_pucBinaryData);		
		}
		else if (image_data.m_eFormat == kA3DPictureBitmapRgbByte)
		{
	 		InvertImage(image_data.m_pucBinaryData, image_data.m_uiPixelWidth, image_data.m_uiPixelHeight,  false);
			HC_Insert_Image (0.0, 0.0, 0.0, H_FORMAT_TEXT("rgb, name = image %u", ui), image_data.m_uiPixelWidth, image_data.m_uiPixelHeight, image_data.m_pucBinaryData);
		}
		else
		{
			ExceptionInfo exception;
			GetExceptionInfo(&exception);
			ImageInfo * image_info = CloneImageInfo((ImageInfo *) NULL);
			Image * image = BlobToImage(image_info, (void *)image_data.m_pucBinaryData, image_data.m_uiSize, &exception);

			unsigned long width = image->magick_columns;
			unsigned long height = image->magick_rows;
			pixels.EnsureSize(width*height*4);  

			ExportImagePixels(image, 0, 0, width, height, "RGBA", CharPixel, &pixels[0], &exception);
			DestroyImage(image);
			DestroyImageInfo(image_info);
			DestroyExceptionInfo(&exception);

			HC_Insert_Image (0.0, 0.0, 0.0, H_FORMAT_TEXT("rgba, name = image %u", ui), width, height, &pixels[0]);
		}
	}

	A3DGraphTextureDefinitionData tdata;
	A3D_INITIALIZE_DATA(A3DGraphTextureDefinitionData, tdata);

	for (unsigned int ui = 0; ui < globalData.m_uiTextureDefinitionsSize; ui++)
	{
		iRet = A3DGlobalGetGraphTextureDefinitionData(ui, &tdata);

		H_FORMAT_TEXT texture_options("source = image %u", tdata.m_uiPictureIndex);

		if (tdata.m_uiMappingAttributes & kA3DTextureMappingSphericalReflection)
		{
			texture_options.Append(", parameterization source = reflection vector");
		}
		else
		{
			texture_options.Append(", parameterization source = uv");
		}

		HC_Define_Local_Texture(H_FORMAT_TEXT("texture_%u", ui), texture_options);
	}

    DestroyMagick(); 
}




void OutputPRCPDF(wchar_t const * file_name,
				  wchar_t const * prc_name,				
 				  float field_of_view,
				  HC_KEY modelkey);

#define PDF_INCHES(x) (float)(72*(x))
#define PDF_POINTS(x) (float)(x)
#include <sys/stat.h>


bool H3DXImporter::Import(const wchar_t * FileName, HC_KEY modelKey, HInputHandlerOptions * pInputOptions)
{
	A3DInt32 iRet;

	if (!A3DSDKLoadLibrary())
		return false;

	SetLicense();

	iRet = A3DDllGetVersion(&m_iMajorVersion, &m_iMinorVersion);

	iRet = A3DDllInitialize(A3D_DLL_MAJORVERSION, A3D_DLL_MINORVERSION);

#ifdef GENERATE_LOG_FILE
	a3d_translation_log_fp = fopen(a3d_translation_log_file, "w");
	A3DDllSetCallbacksReport(a3d_message_function, a3d_warning_function, a3d_error_function);
#endif // GENERATE_LOG_FILE

	if (MAKE_INT_VERSION(A3D_DLL_MAJORVERSION, A3D_DLL_MINORVERSION) > GetDLLVersion())
	{
		pInputOptions->m_bPRCWrongVersion = true;
		return false;
	}
	
	m_TopologyManager = 0;
	m_edgematcher = new BREP_Edge_Matcher;
	m_modelKey = modelKey;
	m_bHasBrepStructure =  false;
	m_bMergeFaces = pInputOptions->m_bPRCMergeFaces;
	m_pConnector = pInputOptions->m_pConnector;
	m_pPMIConnector = pInputOptions->m_pPRCPMIConnector;
	H3DXOptions *h3dx_options = reinterpret_cast<H3DXOptions *>(pInputOptions->m_pExtendedData);
	A3DAsmModelFile *p = 0;

	delete [] m_fileName;
	m_fileName = new wchar_t[wcslen(FileName)+1];
	wcscpy(m_fileName, FileName);
	wchar_t drive[_MAX_DRIVE] = {L""};
	wchar_t dir[_MAX_DIR] = {L""};
	wchar_t fname[_MAX_FNAME] = {L""};
	wchar_t ext[_MAX_EXT] = {L""};
	
	_wsplitpath((FileName), drive, dir, fname, ext);


	if (!pInputOptions->m_pPRCAsmModelFile)
	{
		A3DRWParamsLoadData sReadParam;
		A3D_INITIALIZE_DATA(A3DRWParamsLoadData, sReadParam);
		sReadParam.m_sGeneral.m_bReadSolids = true;
		sReadParam.m_sGeneral.m_bReadSurfaces = true;
		sReadParam.m_sGeneral.m_bReadWireframes = true;
		sReadParam.m_sGeneral.m_bReadPmis = true;
		sReadParam.m_sGeneral.m_bReadAttributes = true;
		sReadParam.m_sGeneral.m_bReadHiddenObjects = true;
		sReadParam.m_sGeneral.m_bReadConstructionAndReferences = false;
		sReadParam.m_sGeneral.m_bReadActiveFilter = true;
		sReadParam.m_sGeneral.m_bReadDrawings = false;
		sReadParam.m_sGeneral.m_eReadGeomTessMode = kA3DReadGeomAndTess;
		sReadParam.m_sGeneral.m_eDefaultUnit = kA3DUnitUnknown;
		sReadParam.m_sPmi.m_bAlwaysSubstituteFont = true;
		sReadParam.m_sPmi.m_pcSubstitutionFont = "TS3D";
		sReadParam.m_sTessellation.m_eTessellationLevelOfDetail = kA3DTessLODMedium;
		sReadParam.m_sMultiEntries.m_bLoadDefault = false;

		iRet = A3DAsmModelFileLoadFromFile((A3DUTF8Char const *)H_UTF8(FileName).encodedText(), &sReadParam, &p);

		if (iRet == A3D_LOAD_MISSING_COMPONENTS && p)
			m_p3DXInputHandler->ReportInputInformation("WARNING: CAD file missing components");

		if (iRet == A3D_LOAD_MULTI_MODELS_CADFILE)
		{
			if (!pInputOptions->m_pPRCMultiModelSelectionCallback)
				return false;

			m_name_array.SetCount(0);
			m_type_array.SetCount(0);

			A3DAsmModelFileData mfData;
			A3D_INITIALIZE_DATA(A3DAsmModelFileData, mfData);

			iRet = A3DAsmModelFileGet(p, &mfData);
			
			A3DAsmProductOccurrenceData sRootProductOccurrenceData;
			A3D_INITIALIZE_DATA(A3DAsmProductOccurrenceData, sRootProductOccurrenceData);

			iRet = A3DAsmProductOccurrenceGet(mfData.m_ppPOccurrences[0], &sRootProductOccurrenceData);

			A3DAsmProductOccurrenceData sProductOccurrenceData;
			A3D_INITIALIZE_DATA(A3DAsmProductOccurrenceData, sProductOccurrenceData);

			A3DRootBaseData sRootBaseData;
			A3D_INITIALIZE_DATA(A3DRootBaseData, sRootBaseData);

			iRet = A3DRootBaseGet(mfData.m_ppPOccurrences[0], &sRootBaseData);

			char * container_name = new char [strlen(sRootBaseData.m_pcName) + 1];
			strcpy(container_name, sRootBaseData.m_pcName);

			m_name_array.Append(container_name);

			iRet = A3DRootBaseGet(NULL, &sRootBaseData);

			for (A3DUns32 i = 0; i < sRootProductOccurrenceData.m_uiPOccurrencesSize; i++)
			{
				iRet = A3DAsmProductOccurrenceGet(sRootProductOccurrenceData.m_ppPOccurrences[i], &sProductOccurrenceData);

				if (sProductOccurrenceData.m_uiProductFlags & A3D_PRODUCT_FLAG_CONFIG)
				{
					iRet = A3DRootBaseGet(sRootProductOccurrenceData.m_ppPOccurrences[i], &sRootBaseData);

					char * config_name = new char [strlen(sRootBaseData.m_pcName) + 1];
					strcpy(config_name, sRootBaseData.m_pcName);

					m_name_array.Append(config_name);

					if (sProductOccurrenceData.m_uiProductFlags & A3D_PRODUCT_FLAG_DEFAULT)
					{
						m_default_entry_index = (int)(i + 1);
					}

					iRet = A3DRootBaseGet(NULL, &sRootBaseData);
				}

				iRet = A3DAsmProductOccurrenceGet(NULL, &sProductOccurrenceData);
			}

			int config_selection = 0;
			// the first entry in the name and type list is for the "container" - it is not a configuration/model
			pInputOptions->m_pPRCMultiModelSelectionCallback(m_name_array[0], m_name_array.Count() - 1, m_name_array + 1, config_selection);
			config_selection++; // we add 1 to compensate for first "container" element

			if (config_selection == 0)
				config_selection = m_default_entry_index;

			sReadParam.m_sMultiEntries.m_bLoadDefault = false;
			sReadParam.m_sMultiEntries.m_uiEntriesSize = 1;
			sReadParam.m_sMultiEntries.m_ppcEntries = (A3DUTF8Char **)&m_name_array[config_selection];

			iRet = A3DAsmModelFileLoadFromFile((A3DUTF8Char const *)H_UTF8(FileName).encodedText(), &sReadParam, &p);

			for (int i = 0; i < m_name_array.Count(); i++)
				delete [] m_name_array[i];

			for (int i = 0; i < m_type_array.Count(); i++)
				delete [] m_type_array[i];
		}

		if (iRet != A3D_LOAD_MISSING_COMPONENTS && iRet != A3D_SUCCESS)
			return false;
	 
		if (h3dx_options && h3dx_options->m_pAsmModelFile)
			h3dx_options->m_pAsmModelFile = p;
		pInputOptions->m_pPRCAsmModelFile = p;
		if (!pInputOptions->m_pPRCTopologyManager)
			m_TopologyManager = new BREP_Topology();
		else
 			m_TopologyManager = pInputOptions->m_pPRCTopologyManager;

		if (!pInputOptions->m_bPRCCreatePRCFileOnly)
		{
			A3DAsmModelFileData mfData;
			A3D_INITIALIZE_DATA(A3DAsmModelFileData, mfData);

			iRet = A3DAsmModelFileGet(p, &mfData);
			
			m_part_key_hash.Flush();
			m_dead_part_hash.Flush();
			m_external_part_key_hash.Flush();
			m_dead_external_part_hash.Flush();
			m_poccurrence_key_hash.Flush();
			m_dead_poccurrence_hash.Flush();
			m_annotationhash = new_vhash(10, malloc, free);		
			HC_Open_Segment_By_Key(m_modelKey);
			{
				PopulateTextures();

				A3DRootBaseData sData;
				A3D_INITIALIZE_DATA(A3DRootBaseData, sData);

				A3DRootBaseGet(p, &sData);

				H_UTF8 tmp;
				tmp.format("`%s`", sData.m_pcName);
				HC_Open_Segment((const char *)tmp.encodedText());
				{
					m_markup_segment = HC_KOpen_Segment("all_markup");
					{
						HC_Set_Visibility("everything = off");
						HC_Set_Heuristics("exclude bounding");
					}
					HC_Close_Segment();

					A3DMiscCascadedAttributes* pAttr;
					A3DInt32 iRet = A3DMiscCascadedAttributesCreate(&pAttr);

					A3DMiscCascadedAttributesData sAttrData;
					A3D_INITIALIZE_DATA(A3DMiscCascadedAttributesData, sAttrData);

 					iRet = A3DMiscCascadedAttributesGet(pAttr, &sAttrData);

					for (A3DUns32 i = 0; i < mfData.m_uiPOccurrencesSize; ++i)
						parsePOccurrence(mfData.m_ppPOccurrences[i], pAttr, (mfData.m_bUnitFromCAD ? mfData.m_dUnit : 1.0));
					
					A3DMiscCascadedAttributesDelete(pAttr);

				}
				HC_Close_Segment();

			}
			HC_Close_Segment();

			m_part_key_hash.Flush();
			m_dead_part_hash.Flush();
			m_external_part_key_hash.Flush();
			m_dead_external_part_hash.Flush();
			m_poccurrence_key_hash.Flush();
			m_dead_poccurrence_hash.Flush();
			delete_vhash(m_annotationhash);
 		}
	}
	if (pInputOptions->m_pPRCAsmModelFile)
		p = pInputOptions->m_pPRCAsmModelFile;

	if ((h3dx_options && h3dx_options->m_bSaveToPDF) || pInputOptions->m_bPRCCreatePRCFileOnly) {
		wchar_t outfilename[4096];
		wchar_t outfilenamepdf[4096];
		swprintf(outfilename, L"%ls%ls%ls.prc", drive, dir, fname);
		swprintf(outfilenamepdf, L"%ls%ls%ls_prc.pdf", drive, dir, fname);

		A3DRWParamsExportPrcData params;
		A3D_INITIALIZE_DATA(A3DRWParamsExportPrcData, params);
		params.m_bCompressBrep = false;
		params.m_bCompressTessellation = false;
		params.m_eCompressBrepType = kA3DCompressionLow;
		A3DRWParamsPrcWriteHelper * helper = NULL;

		iRet = A3DAsmModelFileExportToPrcFile(p, &params, (A3DUTF8Char const *)H_UTF8(outfilename).encodedText(), &helper);
		
		OutputPRCPDF(outfilenamepdf, outfilename, 30, m_modelKey);
	}


	if (!pInputOptions->m_pPRCTopologyManager)
		delete m_TopologyManager;

	delete m_edgematcher;
	delete [] m_fileName;
	m_fileName =0;

#ifdef GENERATE_LOG_FILE
	fclose(a3d_translation_log_fp);
	a3d_translation_log_fp = NULL;
#endif // GENERATE_LOG_FILE

	if (iRet != A3D_SUCCESS)
		return false;


	return true;
}



class H3DXPoster
{
public:
	/*! Constructs an H3DXPoster object. */
	H3DXPoster(){
		left = right = bottom = top = compressed_length = length = width = height = 0;
		compressed_data = data = (unsigned char*)0;
	}

	~H3DXPoster(){
		if(data)
			delete [] data;
		if(compressed_data)
			delete [] compressed_data;
	}
	/*! The image bounding in inches.*/
	float left, right, bottom, top;

	/*! The image width and height in pixels. */
	int width, height;
	/*! The uncompressed length of the image. */
	int length;
	/*! The length of image data after compression. */
	int compressed_length;
	/*! The uncompressed image data. */
	unsigned char * data;
	/*! The compressed image data. */
	unsigned char * compressed_data;
};

void HPRCPosterStream(H3DXPoster * poster,
					 float width, float height)
{
	float SubscreenXmin = -1.0f;
	float SubscreenXmax = 1.0f;
	float SubscreenYmin = -1.0f;
	float SubscreenYmax = 1.0f;

	float window_ar = width/height;
	float page_ar = width/height;
	
#if 1
	SubscreenYmin = -page_ar/window_ar;
	SubscreenYmax = page_ar/window_ar;
#else
	SubscreenXmin = -window_ar/page_ar;
	SubscreenXmax = window_ar/page_ar;
#endif
	
	/* this is the poster size in pixels */
	poster->width = (int)((width + 6.5)*100*(SubscreenXmax-SubscreenXmin));
	poster->height = (int)((height + 8)*100*(SubscreenYmax-SubscreenYmin));

	poster->length = poster->width * poster->height * 3;
	poster->data = new unsigned char[poster->length];

	memset(poster->data, 255, poster->length);
//	poster->compressed_length = poster->length;
//	poster->compressed_data = new unsigned char[poster->compressed_length];
//	if(!HUtility::ZlibCompress(poster->length, poster->data, poster->compressed_length, poster->compressed_data)){
//		if(poster->compressed_data) delete [] poster->compressed_data;
//		poster->compressed_data = (unsigned char*)0;
//		poster->compressed_length = 0;
//	}

	poster->left = 0;
	poster->right = width;
	poster->bottom = 0;
	poster->top = height;
}

class H3DX3d
{
public:
	/*! Constructs an H3DX3d object. */
	H3DX3d(){
		compressed_length = length = 0;
		compressed_data = data = (unsigned char*)0;
	}

	~H3DX3d(){
		if(data)
			delete [] data;
		if(compressed_data)
			delete [] compressed_data;
	}
	/*! The length of the uncompressed data. */
	int length;
	/*! The length of the compressed data. */
	int compressed_length;
	/*! The prc data. */
	unsigned char * data;
	/*! The compressed prc data. */
	unsigned char * compressed_data;
};

void GetPRCStream(H3DX3d * prc, wchar_t const * prc_file)
{
	struct _stat64i32 stat_buf;
	int error = _wstat(prc_file, &stat_buf);

	FILE * file = wfopen(prc_file, L"rb");
	if(!error && file){
		prc->length = (int)stat_buf.st_size;
		prc->data = new unsigned char[prc->length];
		if(prc->data){
			fread(prc->data, prc->length, 1, file);
			//prc->compressed_length = prc->length;
			//prc->compressed_data = new unsigned char[prc->compressed_length];
			//if(!HUtility::ZlibCompress(prc->length, prc->data, prc->compressed_length, prc->compressed_data)){
			//	if(prc->compressed_data) delete [] prc->compressed_data;
			//	prc->compressed_data = (unsigned char*)0;
			//	prc->compressed_length = 0;
			//}
		}
	}

	if(file) fclose(file);
}


void OutputPRCPDF(wchar_t const * file_name,
				  wchar_t const * prc_name,			
				  float field_of_view,
				  HC_KEY modelkey) 
{


	float camera_matrix[16];

	HC_Open_Segment_By_Key(modelkey);
	HPoint min, max;
	HC_Compute_Circumcuboid(".", &min, &max);

	HPoint center = (max + min) / 2.0f;

	HPoint diagonalVector = max-min;

	float camera_target_distance = HC_Compute_Vector_Length(&diagonalVector) * 2.5f;

	HC_Close_Segment();
		 
	HC_Compute_Identity_Matrix(camera_matrix);
	HC_Compute_Translation_Matrix(
		center.x,
		center.y,
		center.z -camera_target_distance,
		camera_matrix);



	/* Get prc model */
	char const pdf_header[] = {
		"%%PDF-1.7\n\n"
	};
	char const info_obj[] = {
		"1 0 obj\n"
		"<< /Producer (HOOPS 3D PRC PDF) /CreationDate (D:%d%02d%02d%02d%02d%02d) >>\n"
		"endobj\n\n"
	};
	char const catalog_obj[] = {
		"2 0 obj\n"
		"<< /Type /Catalog /Pages 3 0 R >>\n"
		"endobj\n\n"
	};
	char const pages_obj[] = {
		"3 0 obj\n"
		"<< /Type /Pages /Count 1 /Kids [ 5 0 R ] >>\n"
		"endobj\n\n"
	};
	char const resources_obj[] = {
		"4 0 obj\n"
		"<< /ProcSet [/PDF /Text] /Font << /F1 14 0 R >> >>\n"
		"endobj\n\n"
	};
	char const page_obj[] = {
		"5 0 obj\n"
		"<< /Type /Page /Parent 3 0 R /MediaBox [0 0 %g %g] "
		"/Contents 6 0 R /Resources 4 0 R /Annots [ 8 0 R ] >>\n"
		"endobj\n\n"
	};
	char const * page_content_obj[] = {
		"%% Page Content Stream\n"
		"6 0 obj\n"
		"<< /Length 7 0 R >>\n"
		"stream\n",

		"endstream\n"
		"endobj\n\n"
	};
	char const page_content_stream[] = {"/F1 16 Tf BT "
		"%g %g Td (Filename: %s) Tj "
		"0 -20 Td (Date: %s) Tj "
		"0 -20 Td (Creator: HOOPS 3D Application Framework) Tj "
		"ET"
	};
	char const page_content_length[] = {
		"7 0 obj\n"
		"%d\n"
		"endobj\n\n"
	};
	/* /A in /3DA should be set to /XA for eXplicit Activate of
	   /PO for activate the 3d on Page Open.  /3DD is a reference to
	   the prc stream.  /AP is a reference to the prc appearance xobject
	   which is what is shown when the prc model is not active.  */
	char const prc_annot[] = {
		"%% PRC annotation\n"
		"8 0 obj\n"
		"<< /Type /Annot /Subtype /3D /3DD 12 0 R /P 5 0 R "
		"/AP << /N 9 0 R >> "
		"/3DV (HOOPS View) "
		"/3DA << /DIS /I /AIS /I /A /%s >> "
		"/Rect [%g %g %g %g] >>\n"
		"endobj\n\n"
	};
	char const * poster_obj[] = {
		"%% prc Poster Object\n"
		"9 0 obj\n "
		"<< /Type /XObject "
		"/Subtype /Form "
		"/FormType 1 "
		"/Resources << /ProcSet [/PDF /ImageC] /XObject << /PosterImage 11 0 R >> >> "
		"/BBox [0 0 %g %g] "
		"/Length 10 0 R >>\n"
		"stream\n",

		"endstream\n"
		"endobj\n\n"
	};
	char const poster_content_stream[] = {"q %g 0 0 %g %g %g cm /PosterImage Do Q"};
	char const poster_content_length[] = {
		"10 0 obj\n"
		"%d\n"
		"endobj\n\n"
	};
	char const * poster_image_obj[] = {
		"%% prc Poster Stream\n"
		"11 0 obj\n"
		"<< /Type /XObject "
		"/Subtype /Image "
		"/BitsPerComponent 8 "
		"/ColorSpace /DeviceRGB "
		"/Filter [%s] "
		"/Width %d /Height %d "
		"/Length %d >>\n"
		"stream\n",

		"endstream\n"
		"endobj\n\n"
	};
	H3DXPoster poster;
	char const * prc_obj[] = {
		"%% PRC Model\n"
		"12 0 obj\n"
		"<< /VA [ 13 0 R ] "
		"/Type /3D "
		"/Subtype /PRC "
		"/OnInstantiate 15 0 R "
		"/Filter [%s] "
		"/Length %d >>\n"
		"stream\n",

		"endstream\n"
		"endobj\n\n"
	};
	H3DX3d prc;
	char const view_obj[] = {
		"%% Default view of the prc stream\n"
		"13 0 obj \n"
		"<< /Type /3DView /XN (HOOPS View) /IN (HOOPS View) "
		"/MS /M "
		"/C2W [%0.3f %0.3f %0.3f %0.3f %0.3f %0.3f %0.3f %0.3f %0.3f %0.3f %0.3f %0.3f] "
		"/P %s "
		"/CO %f "
		"/BG << /Type /3DBG /Subtype /SC /CS /DeviceRGB /C [0.25 0.25 0.25] >> "
		"/LS << /Type /3DLightingScheme /Subtype /CAD >> "
		">>\n"
		"endobj\n\n"
	};
	char const ortho_proj[] = {"<< /Subtype /O /OS %g >>"};
	char const persp_proj[] = {"<< /Subtype /P /FOV %g /PS /W>>"};
	char const font_obj[] = {
		"14 0 obj\n"
		"<< "
		"/Type /Font "
		"/Subtype /Type1 "
		"/Name /F1 "
		"/BaseFont /Helvetica "
		"/Encoding /MacRomanEncoding "
		">>\n"
		"endobj\n\n"
	};
	char const *init_script_obj[] = {
		"15 0 obj\n"
		"<< "
		"/Length %d "
		"/Filter [%s] "
		">> "
		"stream\n",
		"endstream\n"
		"endobj\n\n"
	};
	char init_script[] = {
		"//get the first animation in the scene and create control vars\n"
		"firstAnimation			= scene.animations.getByIndex(0);\n"
		"firstAnimation.speed	= 3;\n"
		"firstAnimation.oneFrame	= 1 / firstAnimation.framesPerSecond;\n"
		"firstAnimation.reverse	= false;\n"
		"scene.activateAnimation(firstAnimation);\n"


		"//add menu items for triggering animations ============================================================\n"
		"//menuName(str)		= menu to which the new item will be assigned\n"
		"//menuItemName(str) = variable name that you will access in JS\n"
		"//label(str)		= string that the user will see\n"
		"//menuItemType(str) = is either ?default?or ?checked?\n"
		"//checked(bool)		= is the state of a checked menu item.\n"
		"//addCustomMenuItem(menuItemName, label, menuItemType, checked);\n"
		"runtime.addCustomMenuItem(    \"faster\", \"Faster (Right Arrow) - Play Animation Faster\",    \"default\",       0);\n"
		"runtime.addCustomMenuItem(    \"slower\", \"Slower (Left Arrow)  - Play Animation Slower\",    \"default\",       0);\n"
		"runtime.addCustomMenuItem(   \"reverse\", \"Play animation in reverse\",					   \"checked\",       0);\n"
		"runtime.addCustomMenuItem( \"showprops\", \"Show Animation Properties (Acrobat Pro Only)\",    \"default\",       0);\n"


		"//menu handler to control speed, show props ===================================\n"
		"myMenuHandler			= new MenuEventHandler();\n"
		"myMenuHandler.onEvent	= function(event)\n"
		"{\n"
		"	if (event.menuItemName == \"faster\")\n"
		"	{\n"
		"		firstAnimation.speed++;\n"
		"		console.println(\"firstAnimation.speed = \" + (firstAnimation.speed * 0.1));\n"
		"	}\n"
		"	else if (event.menuItemName == \"slower\")\n"
		"	{\n"
		"		firstAnimation.speed--;\n"
		"		if ( firstAnimation.speed < 1 )\n"
		"		{\n"
		"			firstAnimation.speed = 1;\n"
		"		}\n"
		"		console.println(\"firstAnimation.speed = \" + (firstAnimation.speed * 0.1));\n"
		"	}\n"
		"	else if (event.menuItemName == \"showprops\")\n"
		"	{\n"
		"		printlnProps();\n"
		"	}\n"
		"	else if (event.menuItemName == \"reverse\")\n"
		"	{\n"
		"		if (event.menuItemChecked)\n"
		"		{\n"
		"			firstAnimation.reverse = true;\n"
		"		}\n"
		"		else\n"
		"		{\n"
		"			firstAnimation.reverse = false;\n"
		"		}\n"
		"	}\n"
		"}\n"
		"//Register with app\n"
		"runtime.addEventHandler(myMenuHandler);\n"


		"//key handler to control speed, show props ==================================\n"
		"myKeyHandler = new KeyEventHandler();\n"
		"myKeyHandler.onKeyDown = true;\n"
		"myKeyHandler.onEvent = function(event)\n"
		"{\n"
		"	switch(event.characterCode)\n"
		"	{\n"
		"		case 29: //right arrow\n"
		"			firstAnimation.speed++;\n"
		"			console.println(\"firstAnimation.speed = \" + (firstAnimation.speed * 0.1));\n"
		"			break;\n"

		"		case 28: //left arrow\n"
		"			firstAnimation.speed--;\n"
		"			if ( firstAnimation.speed < 1 )\n"
		"			{\n"
		"				firstAnimation.speed = 1;\n"
		"			}\n"
		"			console.println(\"firstAnimation.speed = \" + (firstAnimation.speed * 0.1));\n"
		"			break;\n"
		"	}\n"
		"}\n"
		"//register and process\n"
		"runtime.addEventHandler(myKeyHandler);\n"


		"//run the animation using a TimeEventHandler()=================\n"
		"myTimer			= new TimeEventHandler();\n"
		"myTimer.onEvent	= function(event)\n"
		"{\n"
		"	if (!firstAnimation.reverse)\n"
		"	{\n"
		"		firstAnimation.currentTime += firstAnimation.oneFrame * (firstAnimation.speed * 0.1);\n"
		"		if (firstAnimation.currentTime >= firstAnimation.endTime)\n"
		"		{\n"
		"			firstAnimation.currentTime = firstAnimation.startTime;\n"
		"		}\n"
		"	}\n"
		"	else\n"
		"	{\n"
		"		firstAnimation.currentTime -= firstAnimation.oneFrame * (firstAnimation.speed * 0.1);\n"
		"		if (firstAnimation.currentTime <= firstAnimation.startTime)\n"
		"		{\n"
		"			firstAnimation.currentTime = firstAnimation.endTime;\n"
		"		}\n"
		"	}\n"

		"	//may not be necessary to call this\n"
		"	//scene.update();\n"
		"}\n"
		"runtime.addEventHandler(myTimer);\n"


		"function printlnProps()\n"
		"{\n"
		"	console.println(\"==== Animation Properties ====\");\n"
		"	console.println(\"firstAnimation.name            = \" + firstAnimation.name);\n"
		"	console.println(\"firstAnimation.length          = \" + firstAnimation.length);\n"
		"	console.println(\"firstAnimation.startTime       = \" + firstAnimation.startTime);\n"
		"	console.println(\"firstAnimation.endTime         = \" + firstAnimation.endTime);\n"
		"	console.println(\"firstAnimation.currentTime     = \" + firstAnimation.currentTime);\n"
		"	console.println(\"firstAnimation.framesPerSecond = \" + firstAnimation.framesPerSecond);\n"
		"	console.println(\"firstAnimation.speed           = \" + (firstAnimation.speed * 0.1) + \" (user var)\");\n"
		"	console.println(\"\");\n"
		"	console.println(\"Use context menu (or arrow keys) to change animation speed,\");\n"
		"	console.println(\"and display these properties.\");\n"
		"	console.println(\"==============================\");\n"
		"}\n"
		"printlnProps();\n"
	};
	char const xref_table[] = {
		"xref\n"
		"0 16\n"
		"0000000000 65535 f \n"
		"%010ld 00000 n \n"
		"%010ld 00000 n \n"
		"%010ld 00000 n \n"
		"%010ld 00000 n \n"
		"%010ld 00000 n \n"
		"%010ld 00000 n \n"
		"%010ld 00000 n \n"
		"%010ld 00000 n \n"
		"%010ld 00000 n \n"
		"%010ld 00000 n \n"
		"%010ld 00000 n \n"
		"%010ld 00000 n \n"
		"%010ld 00000 n \n"
		"%010ld 00000 n \n"
		"%010ld 00000 n \n\n"
	};	char const trailer_obj[] = {
		"trailer\n"
		"<< /Size 16 /Root 2 0 R /Info 1 0 R >>\n"
		"startxref\n"
		"%ld\n"
		"%%%%EOF"
	};

#   define OFFSET_COUNT 17
	long offsets[OFFSET_COUNT];
	int length, i = 1;
	int name_only=0;

	HPRCPosterStream(&poster, 6.5, 8);
	if(!poster.data){
		return;
	}

	/* The prc file is saved to FileName (the name of the pdf file) then read
	 * back into the buffer prc_stream.  When we open FileName again for writing
	 * the pdf file the prc data in the file is lost but is now in the buffer.
	 */
	GetPRCStream(&prc, prc_name);
	if(!prc.data){
		return;
	}

	FILE * output = wfopen(file_name, L"wb");
	if(output){
		/* Write out the PDF header */
		fprintf(output, pdf_header);
		
		/* write out the info object */
		struct tm * localtm;
		time_t now;
		time(&now);
		localtm = gmtime(&now);
		offsets[i++] = ftell(output);
		fprintf(output, info_obj, 
			localtm->tm_year +1900,
			localtm->tm_mon +1,
			localtm->tm_mday,
			localtm->tm_hour,
			localtm->tm_min,
			localtm->tm_sec); 
		
		/* write out the catalog */
		offsets[i++] = ftell(output);
		fprintf(output, catalog_obj);
		
		/* write out the pages (not page, pages!) object */
		/* It's like the root of the page tree but since there is
		   only one page here it may be confusing */
		offsets[i++] = ftell(output);
		fprintf(output, pages_obj);
		
		/* write out the resource object */
		offsets[i++] = ftell(output);
		fprintf(output, resources_obj);
		
		/* write out the page object */
		offsets[i++] = ftell(output);
		HCLOCALE(fprintf(output, page_obj,
			PDF_INCHES(8.5), PDF_INCHES(11))); 
		
		/* write out the page's content stream */
		offsets[i++] = ftell(output);
		fprintf(output, page_content_obj[0]);
		for(name_only = (int)wcslen(file_name);
			name_only >= 0 && file_name[name_only] != '\\' && file_name[name_only] != '/';
			--name_only);
		++name_only;
		char time_str[256];
		strftime(time_str, sizeof(time_str), "%B %d, %Y", localtm);
		HCLOCALE(length = fprintf(output, 
						 page_content_stream,
						 PDF_INCHES(1),
						 PDF_INCHES(2),
						 H_ASCII_TEXT(file_name +name_only),
						 time_str));
		fprintf(output, "\n");
		fprintf(output, page_content_obj[1]); 

		offsets[i++] = ftell(output);
		fprintf(output, page_content_length, length);
		
		/* write out the prc annotation object */
		offsets[i++] = ftell(output);
		HCLOCALE(fprintf(output, prc_annot,
			"PV",
			PDF_INCHES(1),
			PDF_INCHES(3),
			PDF_INCHES(7.5),
			PDF_INCHES(10)));

		/* write out the poster object */
		offsets[i++] = ftell(output);
		/* poster bounding box */
		HCLOCALE(fprintf(output, poster_obj[0],
			PDF_INCHES(6.5),
			PDF_INCHES(8)));

			HCLOCALE(length = fprintf(output, poster_content_stream, 
				PDF_INCHES(poster.right),
				PDF_INCHES(poster.top),
				PDF_INCHES(poster.left),
				PDF_INCHES(poster.bottom)));
			fprintf(output, "\n");
		fprintf(output, poster_obj[1]);

		offsets[i++] = ftell(output);
		fprintf(output, poster_content_length, length);

		/* write out the poster image data */
		offsets[i++] = ftell(output);
		if(poster.compressed_length){
			fprintf(output, poster_image_obj[0],
				"/FlateDecode",
				poster.width,
				poster.height,
				poster.compressed_length);
			fwrite(poster.compressed_data, poster.compressed_length, 1, output);
		} else {
			fprintf(output, poster_image_obj[0],
				"",
				poster.width,
				poster.height,
				poster.length);
			fwrite(poster.data, poster.length, 1, output);
		}
		fprintf(output, poster_image_obj[1]);

		/* write out the prc stream */
		offsets[i++] = ftell(output);
		if(prc.compressed_length){
			fprintf(output, prc_obj[0], "/FlateDecode", prc.compressed_length);
			fwrite(prc.compressed_data, prc.compressed_length, 1, output);
		} else {
			fprintf(output, prc_obj[0], "", prc.length);
			fwrite(prc.data, prc.length, 1, output);
		}
		fprintf(output, prc_obj[1]); 

		/* write out the view object */
		offsets[i++] = ftell(output);
		char projection_str[256];
		HCLOCALE(sprintf(projection_str, persp_proj, field_of_view));
		HCLOCALE(fprintf(output, view_obj,
			camera_matrix[0], camera_matrix[1], camera_matrix[2],
			camera_matrix[4], camera_matrix[5], camera_matrix[6],
			camera_matrix[8], camera_matrix[9], camera_matrix[10],
			camera_matrix[12], camera_matrix[13], camera_matrix[14],
			projection_str, camera_target_distance));

		offsets[i++] = ftell(output);
		fprintf(output, font_obj);

		offsets[i++] = ftell(output);
		int out_len = (int)strlen(init_script);
		HUtility::ZlibCompress(out_len, (unsigned char*)init_script, out_len, (unsigned char*)init_script);
		fprintf(output, init_script_obj[0], out_len, "/FlateDecode", init_script);
		fwrite(init_script, out_len, 1, output);
		fprintf(output, init_script_obj[1]);

		offsets[i++] = ftell(output);
		fprintf(output, xref_table, 
			offsets[1],	offsets[2],
			offsets[3],	offsets[4],
			offsets[5],	offsets[6],
			offsets[7],	offsets[8],
			offsets[9], offsets[10],
			offsets[11], offsets[12],
			offsets[13], offsets[14],
			offsets[15]
			); 

		fprintf(output, trailer_obj, offsets[16]); 
		fclose(output);
	} 

	return;
}

static A3DCrvBase * createCircle(A3DDouble const radius)
{
	A3DCrvCircle* pCrvCircle = NULL;

	A3DCrvCircleData sData;
	A3D_INITIALIZE_DATA(A3DCrvCircleData, sData);

	sData.m_dRadius = radius;

	sData.m_sParam.m_dCoeffA = 1.0;
	sData.m_sParam.m_dCoeffB = 0.0;
	sData.m_sParam.m_sInterval.m_dMin = 0.0;
	sData.m_sParam.m_sInterval.m_dMax = 360;

	sData.m_sTrsf.m_ucBehaviour = kA3DTransformationIdentity;

	A3DInt32 iRet = A3DCrvCircleCreate(&sData, &pCrvCircle);

	return pCrvCircle;
}

static A3DTopoCoEdge * createTopoCoEdge(A3DCrvBase * p)
{
	A3DTopoCoEdge * ppCoEdge = NULL;

	A3DTopoCoEdgeData sData;
	A3D_INITIALIZE_DATA(A3DTopoCoEdgeData, sData);

	sData.m_pUVCurve = p;
	//sData.m_pEdge = q;

	A3DInt32 iRet = A3DTopoCoEdgeCreate(&sData, &ppCoEdge);

	return ppCoEdge;
}

static A3DTopoLoop * createTopoLoop(A3DDouble const radius)
{
	A3DTopoLoop* pTopoLoop = NULL;

	A3DCrvBase* p = createCircle(radius);
	A3DTopoCoEdge* q = createTopoCoEdge(p);

	A3DTopoLoopData sData;
	A3D_INITIALIZE_DATA(A3DTopoLoopData, sData);

	sData.m_ppCoEdges = &q;
	sData.m_uiCoEdgeSize = 1;

	sData.m_ucOrientationWithSurface = 1;

	A3DInt32 iRet = A3DTopoLoopCreate(&sData, &pTopoLoop);

	return pTopoLoop;
}

static A3DSurfBase * createCylinder()
{
	A3DSurfCylinder* pSurfCylinder = NULL;

	A3DSurfCylinderData sData;
	A3D_INITIALIZE_DATA(A3DSurfCylinderData, sData);

	sData.m_sParam.m_sUVDomain.m_sMin.m_dX = 0.0;
	sData.m_sParam.m_sUVDomain.m_sMin.m_dY = 0.0;
	sData.m_sParam.m_sUVDomain.m_sMax.m_dX = 360.0;
	sData.m_sParam.m_sUVDomain.m_sMax.m_dY = 40.0;

	// Parameters go from -1 to +1 in both directions
	sData.m_sParam.m_dUCoeffA = 1.0 / (sData.m_sParam.m_sUVDomain.m_sMax.m_dX / 2);
	sData.m_sParam.m_dUCoeffB = -1.0;
	sData.m_sParam.m_dVCoeffA = 1.0 / (sData.m_sParam.m_sUVDomain.m_sMax.m_dY / 2);
	sData.m_sParam.m_dVCoeffB = -1.0;
	sData.m_sParam.m_bSwapUV = FALSE;
	sData.m_sTrsf.m_ucBehaviour = kA3DTransformationIdentity;

	sData.m_dRadius = 10.0;

	A3DInt32 iRet = A3DSurfCylinderCreate(&sData, &pSurfCylinder);

	return pSurfCylinder;
}

static A3DTopoFace * createTopoFace()
{
	A3DTopoFace* pTopoFace = NULL;

	A3DDouble outerradius = 0.5;
	A3DDouble innerradius = 0.4;
	A3DTopoLoop* loops[2];
	loops[0] = createTopoLoop(outerradius);
	loops[1] = createTopoLoop(innerradius);

	A3DTopoFaceData sData;
	A3D_INITIALIZE_DATA(A3DTopoFaceData, sData);

	sData.m_ppLoops = loops;
	sData.m_uiLoopSize = 2;
	sData.m_uiOuterLoopIndex = 0;

	A3DSurfBase * p = createCylinder();
	sData.m_pSurface = p;

	A3DInt32 iRet = A3DTopoFaceCreate(&sData, &pTopoFace);

	return pTopoFace;
}

static A3DTopoShell * createTopoShell()
{
	A3DTopoShell* pTopoShell = NULL;

	A3DTopoFace* p = createTopoFace();

	A3DTopoShellData sData;
	A3D_INITIALIZE_DATA(A3DTopoShellData, sData);

	sData.m_ppFaces = &p;
	sData.m_uiFaceSize = 1;

	A3DUns8 orient = 1;
	sData.m_pucOrientationWithShell = &orient;

	A3DInt32 iRet = A3DTopoShellCreate(&sData, &pTopoShell);

	return pTopoShell;
}

static A3DTopoConnex * createTopoConnex()
{
	A3DTopoConnex* pTopoConnex = NULL;

	A3DTopoShell* p = createTopoShell();

	A3DTopoConnexData sData;
	A3D_INITIALIZE_DATA(A3DTopoConnexData, sData);

	sData.m_ppShells = &p;
	sData.m_uiShellSize = 1;

	A3DInt32 iRet = A3DTopoConnexCreate(&sData, &pTopoConnex);

	return pTopoConnex;
}

static A3DTopoBrepData * createTopoBrep()
{
	A3DTopoBrepData * pTopoBrepData = NULL;

	A3DTopoConnex * p = createTopoConnex();

	A3DTopoBrepDataData sData;
	A3D_INITIALIZE_DATA(A3DTopoBrepDataData, sData);

	sData.m_ppConnexes = &p;
	sData.m_uiConnexSize = 1;

	A3DInt32 iRet = A3DTopoBrepDataCreate(&sData, &pTopoBrepData);

	return pTopoBrepData;
}


A3DTess3D* H3DXExporter::createShellTesselation(HC_KEY shellkey, bool &needsColorMap)
{
	bool m_bDeleteTemporaryShell = false;
	char type[MVO_BUFFER_SIZE];
	HC_Show_Key_Type(shellkey, type);
	if (strcmp(type, "shell") != 0)
	{
		m_bDeleteTemporaryShell = true;
		HC_Open_Segment("/gtemp");
		shellkey = HC_Generate_Shell_From_Geometry(shellkey,"");
		HC_Close_Segment();
	}
	int plen, flen, tslen;
	int i;
	A3DUns32 facetSize = 0;
 	HC_Show_Shell_By_Tristrips_Size(shellkey, &plen, &tslen, &flen);
	if (plen == 0 || (tslen == 0 && flen == 0))
		return 0;
 	HPoint *plist = new HPoint[plen];
	HPoint *nlist = new HPoint[plen];
	HPoint *vertexColorList = new HPoint[plen];
	float *vplist = 0;
	float *indexList = new float[plen];
	int *flist = new int[flen];
	int *tslist = new int[tslen];
	

	HC_Show_Shell_By_Tristrips(shellkey, &plen, plist,&tslen, tslist, &flen, flist);

	

//	HC_Show_Shell(shellkey, &plen, plist, &flen, flist);
	HC_Open_Geometry(shellkey);
	for (i = 0;i<plen;i++)
	{
		HC_Open_Vertex(i);
		HC_Show_Net_Normal(&nlist[i].x, &nlist[i].y, &nlist[i].z);		
		HC_Close_Vertex();
	}
	

	char color[MVO_BUFFER_SIZE];
	bool indexColorExists = false;
	bool vertexColorExists = false;
	bool vpExists = false;
	HC_Open_Vertex(0);
	 if (HC_Show_Existence("color"))
	 {		 
			HC_Show_One_Color("faces",color);
			if (color[0] == '#')
				indexColorExists = true;
			else 
				vertexColorExists = true;
	 }

	 if (!indexColorExists)
	 {
 		vpExists = INT2bool(HC_Show_Existence("vertex parameter"));
 	 }
	HC_Close_Vertex();

	HC_Close_Geometry();

	int vplength;
	if (vpExists)	
	{
		HC_MShow_Vertex_Parameter_Size(shellkey,&vplength);
		vplist = new float[vplength*plen];
		HC_MShow_Vertex_Parameters(shellkey, 0,plen,&vplength, vplist);
	}
		 
	if (indexColorExists)
	{
		HC_MShow_Vertex_Colors_By_FInd(shellkey,"faces",0,plen,indexList);
		for (int i=0;i<plen;i++)
		{
			indexList[i] = indexList[i] / (float)m_ColorMapCount;
		}
	}
	
	if (vertexColorExists)
	{
		HC_MShow_Vertex_Colors_By_Value(shellkey,"faces",0,plen,vertexColorList);		
	}


	A3DTessBaseData sTessBaseData;
	A3D_INITIALIZE_DATA(A3DTessBaseData, sTessBaseData);

	sTessBaseData.m_uiCoordSize = plen * 3;
	sTessBaseData.m_pdCoords = (A3DDouble*)malloc(sTessBaseData.m_uiCoordSize * sizeof(A3DDouble));

	A3DTess3DData sTess3DData;
	A3D_INITIALIZE_DATA(A3DTess3DData, sTess3DData);

	sTess3DData.m_uiNormalSize = 3 * plen;
	sTess3DData.m_pdNormals = (A3DDouble*)malloc(sTess3DData.m_uiNormalSize * sizeof(A3DDouble));


	if (vpExists || indexColorExists)
	{
		sTess3DData.m_uiTextureCoordSize = 2 * plen;
		sTess3DData.m_pdTextureCoords = (A3DDouble*)malloc(sTess3DData.m_uiTextureCoordSize * sizeof(A3DDouble));
	}

	int j=0, jj=0,jjj=0;
	for (i=0;i<plen;i++)
	{
		sTessBaseData.m_pdCoords[j++] = plist[i].x;
		sTessBaseData.m_pdCoords[j++] = plist[i].y;
		sTessBaseData.m_pdCoords[j++] = plist[i].z;
		sTess3DData.m_pdNormals[jj++] = nlist[i].x;
		sTess3DData.m_pdNormals[jj++] = nlist[i].y;
		sTess3DData.m_pdNormals[jj++] = nlist[i].z;
		if (vpExists)
		{
			sTess3DData.m_pdTextureCoords[jjj++] = vplist[i*vplength];
			sTess3DData.m_pdTextureCoords[jjj++] = vplist[i*vplength+1];
		}
		else if (indexColorExists)
		{
			sTess3DData.m_pdTextureCoords[jjj++] = 0;
			sTess3DData.m_pdTextureCoords[jjj++] = indexList[i];
		}
	}
	

	

	int numstrips = 0;

	facetSize = 0;
	j=0;
	while (1)
	{
		int fl = tslist[j++];
		j+=fl;		
  		numstrips++;
		if (j>=tslen)
			break;
	}


	A3DTessFaceData sTessFaceData;
	A3D_INITIALIZE_DATA(A3DTessFaceData, sTessFaceData);

	if (vertexColorExists)
	{
		sTessFaceData.m_bIsRGBA = false;
		sTessFaceData.m_uiRGBAVerticesSize = (tslen - numstrips) * 3;
		sTessFaceData.m_pucRGBAVertices = (A3DUns8*)malloc(sTessFaceData.m_uiRGBAVerticesSize * sizeof(A3DUns8));
	}

	if (vpExists || indexColorExists)
	{
		sTessFaceData.m_usUsedEntitiesFlags = kA3DTessFaceDataTriangleStripeTextured;
		sTessFaceData.m_uiTextureCoordIndexesSize = 1;
		sTess3DData.m_uiTriangulatedIndexSize = (tslen - numstrips) * 3;
	}
	else
	{
 		sTessFaceData.m_usUsedEntitiesFlags = kA3DTessFaceDataTriangleStripe; 
		sTess3DData.m_uiTriangulatedIndexSize = (tslen - numstrips) * 2;
	}

	sTess3DData.m_puiTriangulatedIndexes = (A3DUns32*)malloc(sTess3DData.m_uiTriangulatedIndexSize * sizeof(A3DUns32));

	sTessFaceData.m_uiSizesTriangulatedSize = numstrips + 1; /* size of the next array */
	sTessFaceData.m_puiSizesTriangulated = (A3DUns32*)malloc(sTessFaceData.m_uiSizesTriangulatedSize * sizeof(A3DUns32));
	sTessFaceData.m_puiSizesTriangulated[0] = numstrips;
	sTessFaceData.m_uiStartTriangulated = 0;
 

	int f= 0;
	j=0;
	int vcc=0;
	int currentstrip = 1;
	while (1)
	{
		int fl = tslist[j++];
		sTessFaceData.m_puiSizesTriangulated[currentstrip] = fl;
		for (int k=0;k<fl;k++)
		{
 			sTess3DData.m_puiTriangulatedIndexes[f++] = tslist[j] * 3;
			if (vpExists || indexColorExists)
	 			sTess3DData.m_puiTriangulatedIndexes[f++] = tslist[j] * 2;
 			sTess3DData.m_puiTriangulatedIndexes[f++] = tslist[j] * 3;
			if (vertexColorExists)
			{
				sTessFaceData.m_pucRGBAVertices[vcc++] = vertexColorList[tslist[j]].x * 255.0f;
				sTessFaceData.m_pucRGBAVertices[vcc++] = vertexColorList[tslist[j]].y * 255.0f;
				sTessFaceData.m_pucRGBAVertices[vcc++] = vertexColorList[tslist[j]].z * 255.0f;
			}
			j++;
		}
		currentstrip++;
 		if (j>=tslen)
			break;
	}
	
		// so, only one face 
		sTess3DData.m_uiFaceTessSize = 1;
		sTess3DData.m_psFaceTessData = &sTessFaceData;
		A3DTess3D* pTess3D = NULL;
		A3DInt32 iRet = A3DTess3DCreate(&sTess3DData, &pTess3D);
		iRet = A3DTessBaseSet(pTess3D, &sTessBaseData);
		
		if (m_bDeleteTemporaryShell)
			HC_Delete_By_Key(shellkey);

		needsColorMap = indexColorExists;

		delete [] plist;
		delete [] nlist;
		delete [] vertexColorList;
		delete [] vplist;
		delete [] indexList;
		delete [] flist;
		delete [] tslist;
		if (sTessFaceData.m_pucRGBAVertices)
			free(sTessFaceData.m_pucRGBAVertices);
		free(sTessBaseData.m_pdCoords);
		free(sTess3DData.m_pdNormals);
		free (sTess3DData.m_puiTriangulatedIndexes);
		free (sTessFaceData.m_puiSizesTriangulated);
		free (sTess3DData.m_pdTextureCoords);

		if (vertexColorExists || indexColorExists)
			m_VertexColorFound = true;
	return pTess3D;
}


A3DTess3D* H3DXExporter::createLineTesselation(HC_KEY polylinekey)
{
	int plen;
	int i;
	A3DUns32 facetSize = 0;
	char type[4096];
	HC_Show_Key_Type(polylinekey, type);
	HPoint *plist;
	if (strcmp(type, "line") == 0)
	{
		plen = 2;
		plist = new HPoint[2];
		HC_Show_Line(polylinekey, &plist[0].x, &plist[0].y,&plist[0].z,
			&plist[1].x, &plist[1].y,&plist[1].z);
	}
	else if (strcmp(type, "polyline") == 0)
	{
	
		HC_Show_Polyline_Count( polylinekey, &plen);
  
		plist = new HPoint[plen];
		HC_Show_Polyline(polylinekey, &plen, plist);
	}
	else
	{
		HC_Compute_Polyline_From_Curve_Size(polylinekey, "", &plen);
		plist = new HPoint[plen];
		HC_Compute_Polyline_From_Curve(polylinekey, "",&plen, plist);
	}


	A3DTessBaseData sTessBaseData;
	A3D_INITIALIZE_DATA(A3DTessBaseData, sTessBaseData);

	sTessBaseData.m_uiCoordSize = plen * 3;
	sTessBaseData.m_pdCoords = (A3DDouble*)malloc(sTessBaseData.m_uiCoordSize * sizeof(A3DDouble));

	int j=0;
	for (i=0;i<plen;i++)
	{
		sTessBaseData.m_pdCoords[j++] = plist[i].x;
		sTessBaseData.m_pdCoords[j++] = plist[i].y;
		sTessBaseData.m_pdCoords[j++] = plist[i].z;
 	}

	A3DTess3DWireData sTess3DWireData;
	A3D_INITIALIZE_DATA(A3DTess3DWireData, sTess3DWireData);

	A3DTess3DWire* pTess3D = NULL;
	A3DInt32 iRet = A3DTess3DWireCreate(&sTess3DWireData, &pTess3D);
	iRet = A3DTessBaseSet(pTess3D, &sTessBaseData);
		
	free (sTessBaseData.m_pdCoords);
	delete [] plist;
	return pTess3D;
}


bool H3DXExporter::IsEnvironmentTexture(char *texturename)
{
	bool found = false;
	HC_KEY segmentkey;
 	HC_Open_Segment_By_Key(m_modelKey);
	HC_Begin_Contents_Search("...", "segments");
	while (HUtility::FindContents(segmentkey))
	{
		HC_Open_Segment_By_Key(segmentkey);
		float dummy[3];
		char texture[4096];
		char options[4096];
 		HC_Show_Net_Explicit_Color("faces", "environment", dummy, texture, options);
		if (strcmp(texture,"") != 0)
		{
			char texturestring[MVO_BUFFER_SIZE];
			FindTexture(texture, texturestring);
// 			HUtility::DecipherTextureString(texturestring, texture);
			if (strstr(texturestring, texture))
			{
				found = true;
 			}
		}
		HC_Close_Segment();
		if (found)
			break;
	}
	HC_End_Contents_Search();
	HC_Close_Segment();
	return found;
}
 


bool H3DXExporter::FindTexture(char *texturename, char *definition)
{
	char texturename2[MVO_BUFFER_SIZE];
	bool found = false;
	HC_KEY segmentkey;

	HC_Begin_Texture_Search();
	while (HC_Find_Texture(texturename2))
	{
		if (strcmp(texturename, texturename2) == 0)
		{
			found = true;
			HC_Show_Texture(texturename, definition);	
		}
		if (found)
			break;
	}
	HC_End_Texture_Search();

	if (found)
		return found;


	HC_Open_Segment_By_Key(m_modelKey);
	HC_Begin_Local_Texture_Search();
	while (HC_Find_Texture(texturename2))
	{
		if (strcmp(texturename, texturename2) == 0)
		{
			found = true;
			HC_Show_Local_Texture(texturename, definition);	
		}
		if (found)
			break;
	}
	HC_End_Texture_Search();
	HC_Close_Segment();
	if (found)
		return found;


 	HC_Open_Segment_By_Key(m_modelKey);

	HC_Begin_Contents_Search("...", "segments");
	while (HUtility::FindContents(segmentkey))
	{
		HC_Open_Segment_By_Key(segmentkey);
		HC_Begin_Local_Texture_Search();
		while (HC_Find_Texture(texturename2))
		{
			if (strcmp(texturename, texturename2) == 0)
			{
				found = true;
				HC_Show_Local_Texture(texturename, definition);	
			}
			if (found)
				break;
		}
		HC_End_Texture_Search();
		HC_Close_Segment();
		if (found)
			break;
	}
	HC_End_Contents_Search();
	HC_Close_Segment();
	return found;
}









				

void H3DXExporter::AddTexture(HC_KEY imagekey)
{

	A3DUns32 pictureIndex;
	A3DUns32 texturedefinitionIndex, textureapplicationIndex;
	int width, height;
	char imagename[MVO_BUFFER_SIZE];
	bool rgba = false;
	float dummy;
	bool isColormap = false;
	A3DUns8 *imagebuffer;
	char text[MVO_BUFFER_SIZE];

	char type[MVO_BUFFER_SIZE];
	HC_Show_Key_Type(imagekey, type);
	if (strcmp(type, "segment") == 0)
	{
		isColormap = true;
		HC_Open_Segment_By_Key(imagekey);
		HPoint map[256];
		char colorspace[MVO_BUFFER_SIZE];
		int count, count_orig;
		HC_Show_Color_Map_By_Value(colorspace, &count_orig, map);
		HC_Close_Segment();
		if (count_orig < 16)
			count = 16;
		else
			count = count_orig;

			imagebuffer = (A3DUns8 *)malloc(count * 3);

		for (int i=0;i<count_orig;i++)
		{
			imagebuffer[i*3] = map[i].x * 255;
			imagebuffer[i*3+1] = map[i].y * 255;
			imagebuffer[i*3+2] = map[i].z * 255;
		}
		for (int i=count_orig;i<count;i++)
		{
			imagebuffer[i*3] = 0;
			imagebuffer[i*3+1] = 0;
			imagebuffer[i*3+2] = 0;
		}


		width = 1;
		height = count;
		m_ColorMapCount = count;
		int keytoint = (int)imagekey;
		sprintf(imagename, "colormap%d", keytoint);
  	}
	else
	{

		HC_Show_Image_Size(imagekey, &dummy, &dummy, &dummy, text, &width, &height);
	
		imagebuffer = (A3DUns8 *)malloc(width * height * 4);
		HC_Show_Image(imagekey, &dummy, &dummy, &dummy, text, &width, &height, imagebuffer);


 		if (strstr(text, "rgba"))
			rgba = true;
 		InvertImage(imagebuffer, width, height,  rgba);

  		HC_Show_Image_Name(imagekey, imagename);
	}
	
	A3DGraphPictureData sGraphPictureData;
	A3D_INITIALIZE_DATA(A3DGraphPictureData, sGraphPictureData);

	if (rgba)
	{
		sGraphPictureData.m_eFormat = kA3DPictureBitmapRgbaByte;
		sGraphPictureData.m_uiSize = width * height * 4;
	}
	else
	{
		sGraphPictureData.m_eFormat = kA3DPictureBitmapRgbByte;
		sGraphPictureData.m_uiSize = width * height * 3;
	}
	sGraphPictureData.m_uiPixelHeight = height;
	sGraphPictureData.m_uiPixelWidth = width;
	sGraphPictureData.m_pucBinaryData = (A3DUns8 *)imagebuffer;

	A3DInt32 iRet = A3DGlobalInsertGraphPicture(&sGraphPictureData, &pictureIndex);

	A3DGraphTextureDefinitionData sGraphTextureDefinitionData;
	A3D_INITIALIZE_DATA(A3DGraphTextureDefinitionData, sGraphTextureDefinitionData);

	sGraphTextureDefinitionData.m_uiPictureIndex = pictureIndex;
	sGraphTextureDefinitionData.m_ucTextureDimension = 2;
	sGraphTextureDefinitionData.m_eMappingType = kA3DTextureMappingTypeStored;
	sGraphTextureDefinitionData.m_eMappingOperator = kA3DTextureMappingOperatorUnknown;
	sGraphTextureDefinitionData.m_eTextureWrappingModeS = kA3DTextureWrappingModeRepeat;
	sGraphTextureDefinitionData.m_eTextureWrappingModeT = kA3DTextureWrappingModeRepeat;
 	sGraphTextureDefinitionData.m_eTextureFunction =  kA3DTextureFunctionReplace;

	if (IsEnvironmentTexture(imagename))
		sGraphTextureDefinitionData.m_uiMappingAttributes = kA3DTextureMappingSphericalReflection;
	else
		sGraphTextureDefinitionData.m_uiMappingAttributes = kA3DTextureMappingDiffuse;

	sGraphTextureDefinitionData.m_uiMappingAttributesIntensitySize = 1 ;
	sGraphTextureDefinitionData.m_pdMappingAttributesIntensity = new A3DDouble[1];

	sGraphTextureDefinitionData.m_pdMappingAttributesIntensity [0] =  1.0 ;
	sGraphTextureDefinitionData.m_uiMappingAttributesComponentsSize = 1 ;
	sGraphTextureDefinitionData.m_eTextureAlphaTest = kA3DTextureAlphaTestUnknown;
	sGraphTextureDefinitionData.m_pucMappingAttributesComponents =  new A3DUns8[1];
	sGraphTextureDefinitionData.m_pucMappingAttributesComponents[0] =  kA3DTextureMappingComponentsRgb;
	A3DGraphTextureTransformation *mytransf = NULL;

	iRet = A3DGlobalInsertGraphTextureDefinition(&sGraphTextureDefinitionData,&texturedefinitionIndex);	


	A3DUns32 IndexColor;
	float r = 0.2f,g = 0.6f,b = 0.4f;
	A3DGraphRgbColorData sRgbColorData;
	A3D_INITIALIZE_DATA(A3DGraphRgbColorData, sRgbColorData);

	sRgbColorData.m_dBlue = b;
	sRgbColorData.m_dRed = r;
	sRgbColorData.m_dGreen = g;
	iRet = A3DGlobalInsertGraphRgbColor(&sRgbColorData, &IndexColor);


	A3DUns32 IndexMaterial;
	A3DGraphMaterialData sMaterialData;
	A3D_INITIALIZE_DATA(A3DGraphMaterialData, sMaterialData);

	sMaterialData.m_uiDiffuse = IndexColor;
	sMaterialData.m_uiSpecular = IndexColor;
	sMaterialData.m_uiEmissive = IndexColor;
	sMaterialData.m_uiAmbient = IndexColor;

	iRet = A3DGlobalInsertGraphMaterial(&sMaterialData,&IndexMaterial);


	A3DGraphTextureApplicationData sGraphTextureApplicationData;
	A3D_INITIALIZE_DATA(A3DGraphTextureApplicationData, sGraphTextureApplicationData);

	sGraphTextureApplicationData.m_uiTextureDefinitionIndex = texturedefinitionIndex;
	sGraphTextureApplicationData.m_uiMaterialIndex = IndexMaterial;
	sGraphTextureApplicationData.m_uiNextTextureApplicationIndex = A3D_DEFAULT_MATERIAL_INDEX;
	iRet = A3DGlobalInsertGraphTextureApplication(&sGraphTextureApplicationData,&textureapplicationIndex);

	vhash_insert_string_key_item(m_texturehash, imagename  , (void *)textureapplicationIndex);

	free (imagebuffer);
	iRet = iRet;
}
	


  




void H3DXExporter::gatherTextures(HC_KEY segmentkey)
{

	HC_Open_Segment_By_Key(segmentkey);

	HC_Begin_Contents_Search("...", "images, segments");
	
	char type[MVO_BUFFER_SIZE];
	HC_KEY key;
	while (HC_Find_Contents(type, &key))
	{
		if (strcmp(type, "segment") == 0)
		{
			HC_Open_Segment_By_Key(key);
			bool colormapfound = INT2bool(HC_Show_Existence("color map"));
			HC_Close_Segment();
			if (colormapfound)
				AddTexture(key);
		}
		else if (strcmp(type, "image") == 0)
		{
			AddTexture(key);
		}
	}
	HC_End_Contents_Search();
	HC_Close_Segment();
}



void H3DXExporter::FindCorrespondingColormap(HC_KEY segmentkey, char *textout)
{
	HC_KEY foundkey = INVALID_KEY;
	while (1)
	{
		HC_Open_Segment_By_Key(segmentkey);
		if (HC_Show_Existence("color map"))
			foundkey = segmentkey;
		HC_Close_Segment();
		if (foundkey != INVALID_KEY || segmentkey == HC_KCreate_Segment("/"))
			break;
		segmentkey = HC_KShow_Owner_By_Key(segmentkey);
	}
	int keytoint = (int)segmentkey;
	sprintf(textout, "colormap%d", keytoint);
}





void H3DXExporter::SetColor(A3DRootBaseWithGraphics* pBase, HC_KEY segmentkey, bool needsColorMap, bool hasColor, bool isVisible, bool faceColor)
{
 		A3DUns32 IndexColor;
		A3DInt32 iRet;
		bool hasTexture = false;
 		float r,g,b;
		float matrix[16];
		HC_Open_Segment_By_Key(segmentkey);
 		float rgb[3];
		float tra[3];
		float dummy[3];
		char texture[4096];
		char options[4096];
		char dummytext[4096];
		HC_Show_Net_Modelling_Matrix(matrix);
		char color[4096];
		HC_Show_Net_Color(color);
		HC_Show_Segment(segmentkey, dummytext);
		char colortype[MVO_BUFFER_SIZE];
		if (faceColor)
			strcpy(colortype,"faces");
		else
			strcpy(colortype,"lines");
		HC_Show_Net_Explicit_Color(colortype, "diffuse color", rgb, texture, options);
		HC_Show_Net_Explicit_Color(colortype, "diffuse texture", dummy, texture, options);
		if (strcmp(texture,"") == 0)
			HC_Show_Net_Explicit_Color(colortype, "environment", dummy, texture, options);
		HC_Show_Net_Explicit_Color(colortype, "transmission", tra, dummytext, options);
  		HC_Close_Segment();				
			
		if (needsColorMap)
		{
			hasTexture = true;
			char text[MVO_BUFFER_SIZE];
			HC_Show_Segment(segmentkey, text);
			FindCorrespondingColormap(segmentkey, text);
			vhash_lookup_string_key_item(m_texturehash, text ,  (void **)&IndexColor);
		}			
		else if (strcmp(texture,"") != 0)
		{
			char texturestring[MVO_BUFFER_SIZE];
			FindTexture(texture, texturestring);
			HUtility::DecipherTextureString(texturestring, texture);
			hasTexture = true;
			vhash_lookup_string_key_item(m_texturehash, texture ,  (void **)&IndexColor);
		}
		else
		{
			r = rgb[0];
			g = rgb[1];
			b = rgb[2];
			A3DGraphRgbColorData sRgbColorData;
			A3D_INITIALIZE_DATA(A3DGraphRgbColorData, sRgbColorData);

			sRgbColorData.m_dBlue = b;
			sRgbColorData.m_dRed = r;
			sRgbColorData.m_dGreen = g;
			iRet = A3DGlobalInsertGraphRgbColor(&sRgbColorData, &IndexColor);
		}

//			A3DUns32 IndexMaterial;
//			A3DGraphMaterialData sMaterialData;
//			A3D_INITIALIZE_DATA(sMaterialData);
//			sMaterialData.m_uiDiffuse = IndexColor;
//			iRet = A3DGlobalInsertGraphMaterial(&sMaterialData,&IndexMaterial);


  		A3DUns32 IndexStyle;
		A3DGraphStyleData sGraphStyleData;
		A3D_INITIALIZE_DATA(A3DGraphStyleData, sGraphStyleData);

		sGraphStyleData.m_bMaterial = hasTexture;
		sGraphStyleData.m_uiRgbColorIndex = IndexColor;
		if (tra[0] != 0.0f)
		{
			sGraphStyleData.m_bIsTransparencyDefined = true;
			sGraphStyleData.m_ucTransparency = 255 - ((float)tra[0] * 255.0f);
		}

		iRet = A3DGlobalInsertGraphStyle(&sGraphStyleData, &IndexStyle);


		A3DGraphics    *pGraphics;
		A3DGraphicsData  sGraphicsData;
		A3D_INITIALIZE_DATA(A3DGraphicsData, sGraphicsData);

		if (hasColor)
			sGraphicsData.m_uiStyleIndex = IndexStyle;
		else
			sGraphicsData.m_uiStyleIndex = -1;

		sGraphicsData.m_uiLayerIndex = 0;
		if (!isVisible)		
			sGraphicsData.m_usBehaviour =  kA3DGraphicsSonHeritShow |  kA3DGraphicsSonHeritTransparency;
		else
			sGraphicsData.m_usBehaviour =  kA3DGraphicsShow |  kA3DGraphicsSonHeritTransparency;

		iRet = A3DGraphicsCreate(&sGraphicsData,&pGraphics);

		A3DRootBaseWithGraphicsData sRootBaseWithGraphicsData;
		A3D_INITIALIZE_DATA(A3DRootBaseWithGraphicsData, sRootBaseWithGraphicsData);

		sRootBaseWithGraphicsData.m_pGraphics = pGraphics;
		if (hasColor || needsColorMap || !isVisible)
			 iRet = A3DRootBaseWithGraphicsSet(pBase, &sRootBaseWithGraphicsData);
		iRet = iRet;
}

A3DRiRepresentationItem * H3DXExporter::createRI(HC_KEY key, bool hasColor, bool lineVisibility, bool faceVisibility,bool isInclude)
{

	bool bLineColor = false;
	char type[MVO_BUFFER_SIZE];
	bool needsColorMap = false;
	HC_Show_Key_Type(key, type);
	HC_KEY segmentkey = HC_KShow_Owner_By_Key(key);
	A3DTess3D * pTess3D = 0;
	A3DRiRepresentationItem *pRI = NULL;
	if (strcmp(type, "polyline") == 0 || strcmp(type, "line") == 0 || strcmp(type, "circular arc") == 0 ||
		strcmp(type, "ellipse") == 0 || strcmp(type, "elliptical arc") == 0)
	{	
		if (!lineVisibility && faceVisibility)
			goto endCreateRI;
		bLineColor = true;
		pTess3D = createLineTesselation(key);			
		A3DRiPolyWireData sPolyBrepModelData;
		A3D_INITIALIZE_DATA(A3DRiPolyWireData, sPolyBrepModelData);

		A3DRiPolyWireCreate(&sPolyBrepModelData, &pRI);
	}
	else
	{
		if (!faceVisibility && lineVisibility)
			goto endCreateRI;		
		pTess3D = createShellTesselation(key, needsColorMap);
		A3DRiPolyBrepModelData sPolyBrepModelData;
		A3D_INITIALIZE_DATA(A3DRiPolyBrepModelData, sPolyBrepModelData);

		sPolyBrepModelData.m_bIsClosed = FALSE;
		A3DRiPolyBrepModelCreate(&sPolyBrepModelData, &pRI);
	}

	if (needsColorMap || (isInclude && hasColor) || (bLineColor && hasColor))
		SetColor(pRI, segmentkey, needsColorMap, hasColor, (lineVisibility || faceVisibility), !bLineColor);


		A3DRiRepresentationItemData sRiData;
		A3D_INITIALIZE_DATA(A3DRiRepresentationItemData, sRiData);

		sRiData.m_pTessBase = pTess3D;
		A3DRiRepresentationItemSet(pRI, &sRiData);
 
endCreateRI: ;
		return pRI;		
}


A3DAsmProductOccurrence * H3DXExporter::createInclude(HC_KEY key, bool hasColor)
{

	A3DAsmProductOccurrence* includedOccurence = NULL;

 	HC_KEY included_segment = HC_KShow_Include_Segment(key);
	int res = vhash_lookup_item(m_instancehash, (void *)included_segment ,  (void **)&includedOccurence);
	if (!(res == VHASH_STATUS_SUCCESS))
	{
		includedOccurence = createOccurrenceRecursive(included_segment, false, true, true, true);
 		vhash_insert_item(m_instancehash, (void *)included_segment  , (void *)includedOccurence);

	}
	return includedOccurence;

//	A3DAsmProductOccurrence* pProductOccurrence = NULL;
//	A3DAsmProductOccurrenceData sData2;
//	A3D_INITIALIZE_DATA(sData2);
//	sData2.m_pPrototype = includedOccurence;
//	A3DInt32 iRet = A3DAsmProductOccurrenceCreate(&sData2, &pProductOccurrence);

//	return pProductOccurrence;

}



static void ExtractFontInfo(char *text, char *fontname, float &size)
{
	char *fontnamestart = strstr(text,"name=");
	char *sizestart = strstr(text,"size=");
	memcpy(fontname,fontnamestart+5,sizestart-fontnamestart-1-5);
	fontname[sizestart-fontnamestart-5] = 0;

	char *sizeend = strstr(text," oru");
	char temp[256];
	memcpy(temp,sizestart+5,sizeend - sizestart-5);
	temp[sizeend - sizestart-5] = 0;
	size = atof(temp);
	
 
}


A3DTessMarkup * H3DXExporter::createTesselation(HC_KEY segmentkey)
{
	A3DInt32 iRet;
 	VArray<A3DUns32> tesselationCodes(4096);
 	VArray<A3DDouble> tesselationCoordinates(4096);
 	VArray<A3DUTF8Char *> textCharacters(4096);
 
	int codepos = 0;
	int coordpos = 0;
	int textpos = 0;

	A3DTessMarkup* tesselationItem = NULL;

	A3DTessBaseData sTessBaseData;
	A3D_INITIALIZE_DATA(A3DTessBaseData, sTessBaseData);

	A3DTessMarkupData sData;
	A3D_INITIALIZE_DATA(A3DTessMarkupData, sData);

	HC_KEY stkey, skey, polylinekey;
	HC_Open_Segment_By_Key(segmentkey);
	HC_Begin_Contents_Search(".", "segments");
	while (HUtility::FindContents(stkey))
	{
		char pathname[4096];
		char segmentname[4096];
		HC_Show_Segment(stkey, pathname);
		HC_Parse_String(pathname, "/", -1, segmentname);

  		if (strcmp(segmentname, "frame") == 0  || strcmp(segmentname, "leader") == 0)
		{
			HC_Open_Segment_By_Key(stkey);
			HC_Begin_Contents_Search(".", "segments");
			while (HUtility::FindContents(skey))
			{
				HC_Open_Segment_By_Key(skey);
				HC_Begin_Contents_Search(".", "polyline");
				while (HUtility::FindContents(polylinekey))
				{
					HPoint points[4096];
					int plen;
					HC_Show_Polyline(polylinekey,&plen, points);
					tesselationCodes[codepos++] = 0;				
					tesselationCodes[codepos++] = plen * 3;
					for (int i=0;i<plen;i++)
					{
						tesselationCoordinates[coordpos++] = points[i].x;
						tesselationCoordinates[coordpos++] = points[i].y;
						tesselationCoordinates[coordpos++] = points[i].z;
					}
 				}
				HC_End_Contents_Search();
				HC_Close_Segment();
			}
			HC_End_Contents_Search();
			HC_Close_Segment();
  		}
		else if (strcmp(segmentname, "text") == 0)
		{
			HC_Open_Segment_By_Key(stkey);
			HC_Begin_Contents_Search(".", "segments");
			while (HUtility::FindContents(skey))
			{
				HC_Show_Segment(skey, pathname);
				HC_Parse_String(pathname, "/", -1, segmentname);
 				HC_KEY skey2;
				HC_Open_Segment_By_Key(skey);
				HC_Begin_Contents_Search(".", "segments");
				while (HUtility::FindContents(skey2))
				{


					char textfont[4096];
					char fontname[4096];
					float fontsize;
					HC_Open_Segment_By_Key(skey2);
					HC_Show_Text_Font(textfont);
					ExtractFontInfo(textfont, fontname, fontsize);

					A3DFontKeyData sFontKeyData;
					A3D_INITIALIZE_DATA(A3DFontKeyData, sFontKeyData);

					A3DFontData sFontData;
					A3D_INITIALIZE_DATA(A3DFontData, sFontData);
 

					sFontData.m_cAttributes = 0;
					sFontData.m_eCharset = kA3DCharsetRoman;

					sFontData.m_pcFamilyName = (A3DUTF8Char *)malloc(sizeof( A3DUTF8Char) * strlen(fontname)+64);
					strcpy(sFontData.m_pcFamilyName, fontname);
 					sFontData.m_uiSize = fontsize * 1.66666f;

					iRet = A3DGlobalFontKeyCreate(&sFontData,&sFontKeyData);

					delete [] sFontData.m_pcFamilyName;
					sFontData.m_cAttributes = 1;
					sFontData.m_eCharset = kA3DCharsetRoman;
					
					float matrix[16];

					A3DUns32 test = A3D_ENCODE_EXTRA_DATA(kA3DMarkupFontMask,2);
					tesselationCodes[codepos++]  = A3D_ENCODE_EXTRA_DATA(kA3DMarkupFontMask,2);
					tesselationCodes[codepos++] = 0;				
					tesselationCodes[codepos++] = sFontKeyData.m_iFontFamilyIndex;				
					tesselationCodes[codepos++] = sFontKeyData.m_cAttributes + (sFontKeyData.m_iFontSizeIndex << 12) + (sFontKeyData.m_iFontStyleIndex << 12);			

					HC_Show_Modelling_Matrix(matrix);
					tesselationCodes[codepos++] = kA3DMarkupIsMatrix + 5;				
					tesselationCodes[codepos++] = 18;				
					for (int i=0;i<16;i++)
						tesselationCoordinates[coordpos++] = matrix[i];

					HC_KEY textkey;
					HC_Begin_Contents_Search(".", "text");
					while (HUtility::FindContents(textkey))
					{
						float d;
						char text[4096];
						HC_Show_Text(textkey, &d, &d, &d, text);
						float xfrac, yfrac;
						float xfrac2, yfrac2;

						HC_Open_Segment_By_Key(m_pView->GetSceneKey());
						HC_Open_Segment("textdummy");
						HC_Set_Text_Font(textfont);
						HC_Compute_Text_Extent_With_Encoding(".","utf8", text, &xfrac, &yfrac);
						HC_Compute_Text_Extent_With_Encoding(".","utf8", "X", &xfrac2, &yfrac2);

						HPoint p(xfrac,yfrac,0);
						HPoint p2(0,0,0);
						HC_Compute_Coordinates(".", "local window",&p, "local pixels",&p);
						HC_Compute_Coordinates(".", "local window",&p2, "local pixels",&p2);
						HPoint p3 = p - p2;

						p3.x = (float)fontsize/yfrac2 * xfrac;
						p3.y = (float)fontsize/yfrac2 * yfrac;

						HC_Close_Segment();
						HC_Delete_Segment("textdummy");
						HC_Close_Segment();

						tesselationCodes[codepos++]  = A3D_ENCODE_EXTRA_DATA(kA3DMarkupTextMask,1);
						tesselationCodes[codepos++]  = 2;
						tesselationCodes[codepos++]  = textpos;	
						tesselationCoordinates[coordpos++] =fabs(p3.x) * 1.6666f;
						tesselationCoordinates[coordpos++] = fabs(p3.y) * 1.6666f;

						textCharacters[textpos] = (A3DUTF8Char *)malloc(sizeof( A3DUTF8Char) * (strlen(text)+100));
						strcpy(textCharacters[textpos],text);
						textpos++;
	 					
					}
					HC_End_Contents_Search();

					HC_Close_Segment();
					tesselationCodes[codepos++] = kA3DMarkupIsMatrix;	
					tesselationCodes[codepos++] = 0;	

				}
				HC_End_Contents_Search();
				HC_Close_Segment();
				
				}
			HC_End_Contents_Search();
			HC_Close_Segment();
			
		}
	}
	HC_End_Contents_Search();
	HC_Close_Segment();
	

	sTessBaseData.m_uiCoordSize = coordpos;
	sTessBaseData.m_pdCoords = &tesselationCoordinates[0];

	sData.m_puiCodes = &tesselationCodes[0];
	sData.m_uiCodesSize = codepos;
	sData.m_ppcTexts = &textCharacters[0];
	sData.m_uiTextsSize = textpos;

 	iRet = A3DTessMarkupCreate(&sData, &tesselationItem);
	iRet = A3DTessBaseSet(tesselationItem, &sTessBaseData);

	A3DTessMarkupData sMarkupData;
	A3D_INITIALIZE_DATA(A3DTessMarkupData, sMarkupData);

	iRet = A3DTessMarkupGet(tesselationItem, &sMarkupData);

	for (int i=0;i<textpos;i++)	
		delete [] sData.m_ppcTexts[i];

	return tesselationItem;
}
			



A3DMkpAnnotationEntity * H3DXExporter::createPMI(HC_KEY segmentkey)
{

	A3DInt32 iRet;

	A3DMkpAnnotationItem* annotationItem = NULL;

	A3DMkpAnnotationItemData sData;
	A3D_INITIALIZE_DATA(A3DMkpAnnotationItemData, sData);


	A3DMkpMarkup* markupItem = NULL;
	A3DMkpMarkupData sDataMarkup;
	A3D_INITIALIZE_DATA(A3DMkpMarkupData, sDataMarkup);
	
	char pmitype[4096];
	char pmisubtype[4096];
	HC_Open_Segment_By_Key(segmentkey);
	HUtility::ShowOneUserOption("pmi_type", pmitype);
 	if (strcmp(pmitype,"dimension") == 0)
	{
		sDataMarkup.m_eType  = kA3DMarkupTypeDimension;
		HUtility::ShowOneUserOption("dimension_subtype", pmisubtype);
	
		if (strcmp(pmisubtype,"distance") == 0)
			sDataMarkup.m_eSubType = kA3DMarkupSubTypeDimensionDistance;
		else if (strcmp(pmisubtype,"distanceoffset") == 0)
			sDataMarkup.m_eSubType = kA3DMarkupSubTypeDimensionDistanceOffset;
		else if (strcmp(pmisubtype,"distancecumulate") == 0)
			sDataMarkup.m_eSubType = kA3DMarkupSubTypeDimensionDistanceCumulate;
		else if (strcmp(pmisubtype,"chamfer") == 0)
			sDataMarkup.m_eSubType = kA3DMarkupSubTypeDimensionChamfer;
		else if (strcmp(pmisubtype,"slope") == 0)
			sDataMarkup.m_eSubType = kA3DMarkupSubTypeDimensionSlope;
		else if (strcmp(pmisubtype,"ordinate") == 0)
			sDataMarkup.m_eSubType = kA3DMarkupSubTypeDimensionOrdinate;
		else if (strcmp(pmisubtype,"radius") == 0)
			sDataMarkup.m_eSubType = kA3DMarkupSubTypeDimensionRadius;
		else if (strcmp(pmisubtype,"radiustangent") == 0)
			sDataMarkup.m_eSubType = kA3DMarkupSubTypeDimensionRadiusTangent;
		else if (strcmp(pmisubtype,"radiuscylinder") == 0)
			sDataMarkup.m_eSubType = kA3DMarkupSubTypeDimensionRadiusCylinder;
		else if (strcmp(pmisubtype,"radiusedge") == 0)
			sDataMarkup.m_eSubType = kA3DMarkupSubTypeDimensionRadiusEdge;
		else if (strcmp(pmisubtype,"diameter") == 0)
			sDataMarkup.m_eSubType = kA3DMarkupSubTypeDimensionDiameter;
		else if (strcmp(pmisubtype,"diametertangent") == 0)
			sDataMarkup.m_eSubType = kA3DMarkupSubTypeDimensionDiameterTangent;
		else if (strcmp(pmisubtype,"diametercylinder") == 0)
			sDataMarkup.m_eSubType = kA3DMarkupSubTypeDimensionDiameterCylinder;
		else if (strcmp(pmisubtype,"diameteredge") == 0)
			sDataMarkup.m_eSubType = kA3DMarkupSubTypeDimensionDiameterEdge;
		else if (strcmp(pmisubtype,"diametercone") == 0)
			sDataMarkup.m_eSubType = kA3DMarkupSubTypeDimensionDiameterCone;
		else if (strcmp(pmisubtype,"length") == 0)
			sDataMarkup.m_eSubType = kA3DMarkupSubTypeDimensionLength;
		else if (strcmp(pmisubtype,"lengthcurvilinear") == 0)
			sDataMarkup.m_eSubType = kA3DMarkupSubTypeDimensionLengthCurvilinear;
		else if (strcmp(pmisubtype,"lengthcircular") == 0)
			sDataMarkup.m_eSubType = kA3DMarkupSubTypeDimensionLengthCircular;
		else if (strcmp(pmisubtype,"angle") == 0)
			sDataMarkup.m_eSubType = kA3DMarkupSubTypeDimensionAngle;
		else if (strcmp(pmisubtype,"enummax") == 0)
			sDataMarkup.m_eSubType = kA3DMarkupSubTypeDimensionEnumMax;
	}
	else if (strcmp(pmitype,"text") == 0)
		sDataMarkup.m_eType  = kA3DMarkupTypeText;
	else if (strcmp(pmitype,"arrow") == 0)
		sDataMarkup.m_eType  = kA3DMarkupTypeArrow;
	else if (strcmp(pmitype,"balloon") == 0)
		sDataMarkup.m_eType  = kA3DMarkupTypeBalloon;
	else if (strcmp(pmitype,"balloon") == 0)
		sDataMarkup.m_eType  = kA3DMarkupTypeBalloon;
	else if (strcmp(pmitype,"balloon") == 0)
		sDataMarkup.m_eType  = kA3DMarkupTypeBalloon;
	else if (strcmp(pmitype,"circlecenter") == 0)
		sDataMarkup.m_eType  = kA3DMarkupTypeCircleCenter;
	else if (strcmp(pmitype,"coordinate") == 0)
		sDataMarkup.m_eType  = kA3DMarkupTypeCoordinate;
	else if (strcmp(pmitype,"datum") == 0)
	{
		sDataMarkup.m_eType  = kA3DMarkupTypeDatum;
		HUtility::ShowOneUserOption("datum_subtype", pmisubtype);
	
		if (strcmp(pmisubtype,"ident") == 0)
			sDataMarkup.m_eSubType = kA3DMarkupSubTypeDatumIdent;
		else if (strcmp(pmisubtype,"target") == 0)
			sDataMarkup.m_eSubType = kA3DMarkupSubTypeDatumTarget;
		else if (strcmp(pmisubtype,"enummax") == 0)
			sDataMarkup.m_eSubType = kA3DMarkupSubTypeDatumEnumMax;
	}
	else if (strcmp(pmitype,"fastener") == 0)
		sDataMarkup.m_eType  = kA3DMarkupTypeFastener;
	else if (strcmp(pmitype,"fcf") == 0)
	{
		sDataMarkup.m_eType  = kA3DMarkupTypeGdt;
		sDataMarkup.m_eSubType = kA3DMarkupSubTypeGdtFcf;
	}
	else if (strcmp(pmitype,"gdt") == 0)
	{
		sDataMarkup.m_eType  = kA3DMarkupTypeGdt;
		HUtility::ShowOneUserOption("gdt_subtype", pmisubtype);
	
		if (strcmp(pmisubtype,"fcf") == 0)
			sDataMarkup.m_eSubType = kA3DMarkupSubTypeGdtFcf;
		else if (strcmp(pmisubtype,"enummax") == 0)
			sDataMarkup.m_eSubType = kA3DMarkupSubTypeGdtEnumMax;
	}
	else if (strcmp(pmitype,"locator") == 0)
		sDataMarkup.m_eType  = kA3DMarkupTypeLocator;
	else if (strcmp(pmitype,"measurementpoint") == 0)
		sDataMarkup.m_eType  = kA3DMarkupTypeMeasurementPoint;
	else if (strcmp(pmitype,"roughness") == 0)
		sDataMarkup.m_eType  = kA3DMarkupTypeRoughness;
	else if (strcmp(pmitype,"welding") == 0)
	{
		sDataMarkup.m_eType  = kA3DMarkupTypeWelding;
		HUtility::ShowOneUserOption("welding_subtype", pmisubtype);
	
		if (strcmp(pmisubtype,"line") == 0)
			sDataMarkup.m_eSubType = kA3DMarkupSubTypeWeldingLine;
		else if (strcmp(pmisubtype,"spot") == 0)
			sDataMarkup.m_eSubType = kA3DMarkupSubTypeWeldingSpot;
		else if (strcmp(pmisubtype,"enummax") == 0)
			sDataMarkup.m_eSubType = kA3DMarkupSubTypeWeldingEnumMax;
	}
	else if (strcmp(pmitype,"table") == 0)
		sDataMarkup.m_eType  = kA3DMarkupTypeTable;
	else if (strcmp(pmitype,"other") == 0)
	{
		sDataMarkup.m_eType  = kA3DMarkupTypeOther;
		HUtility::ShowOneUserOption("other_subtype", pmisubtype);
	
		if (strcmp(pmisubtype,"symboluser") == 0)
			sDataMarkup.m_eSubType = kA3DMarkupSubTypeOtherSymbolUser;
		else if (strcmp(pmisubtype,"symbolutility") == 0)
			sDataMarkup.m_eSubType = kA3DMarkupSubTypeOtherSymbolUtility;
		else if (strcmp(pmisubtype,"symbolcustom") == 0)
			sDataMarkup.m_eSubType = kA3DMarkupSubTypeOtherSymbolCustom;
		else if (strcmp(pmisubtype,"geometricreference") == 0)
			sDataMarkup.m_eSubType = kA3DMarkupSubTypeOtherGeometricReference;
		else if (strcmp(pmisubtype,"enummax") == 0)
			sDataMarkup.m_eSubType = kA3DMarkupSubTypeOtherEnumMax;
	}




	HC_Close_Segment();

	sDataMarkup.m_pTessellation = createTesselation(segmentkey);
 	iRet = A3DMkpMarkupCreate(&sDataMarkup, &markupItem);


//	sData.m_pMarkup

	sData.m_pMarkup = markupItem;
 	iRet = A3DMkpAnnotationItemCreate(&sData, &annotationItem);
	return annotationItem;

#if 0
	A3DEEntityType eType;
	A3DInt32 iErr = A3DEntityGetType(pAnnot, &eType);
	HC_Open_Segment(H_FORMAT_TEXT("Annotation %d", HDB::GetUniqueID()));
	{
		switch (eType)
		{
			case kA3DTypeMkpAnnotationItem:
				traverseAnnotationItem(pAnnot);
				break;
			case kA3DTypeMkpAnnotationReference:
				traverseAnnotationReference(pAnnot);
				break;
			case kA3DTypeMkpAnnotationSet:
				traverseAnnotationSet(pAnnot);
				break;
			default:
				break;
		}
	}
	HC_Close_Segment();
#endif
}

A3DMkpView * H3DXExporter::createView(HC_KEY segmentkey)
{
	A3DInt32 iRet;
	vlist_t *pmiList = new_vlist(malloc,free);

	A3DMkpView* viewItem = NULL;

	A3DMkpViewData sData;
	A3D_INITIALIZE_DATA(A3DMkpViewData, sData);
	sData.m_bIsAnnotationView = true;
	HC_Open_Segment_By_Key(segmentkey);

	HC_KEY includekey;

	HC_Begin_Contents_Search(".", "includes");
	while (HUtility::FindContents(includekey))
	{
 			A3DMkpAnnotationEntity *annotation = createPMI(HC_KShow_Include_Segment(includekey));
			if (annotation)
				vlist_add_last(pmiList, annotation);
	}
	HC_End_Contents_Search();
	
 
	HC_KEY pkey;
	HC_Open_Segment("frame");
	HC_Begin_Contents_Search("...", "polyline");
	HUtility::FindContents(pkey);
	HC_End_Contents_Search();
	HC_Close_Segment();
	HC_Close_Segment();
	int pcount;
	HC_Show_Polyline_Count(pkey, &pcount);
	HPoint *points = new HPoint[pcount];
	HC_Show_Polyline(pkey, &pcount, points);



	A3DSurfPlane *splane;
	A3DSurfPlaneData sDataSP;
	A3D_INITIALIZE_DATA(A3DSurfPlaneData, sDataSP);
	sDataSP.m_sTrsf.m_sOrigin.m_dX = points[0].x;
	sDataSP.m_sTrsf.m_sOrigin.m_dY = points[0].y;
	sDataSP.m_sTrsf.m_sOrigin.m_dY = points[0].z;

	HPoint d = points[1] - points[0];
	HC_Compute_Normalized_Vector(&d, &d);
	sDataSP.m_sTrsf.m_sXVector.m_dX = d.x;
	sDataSP.m_sTrsf.m_sXVector.m_dY = d.y;
	sDataSP.m_sTrsf.m_sXVector.m_dZ = d.z;

	d = points[3] - points[0];
	HC_Compute_Normalized_Vector(&d, &d);
	sDataSP.m_sTrsf.m_sYVector.m_dX = d.x;
	sDataSP.m_sTrsf.m_sYVector.m_dY = d.y;
	sDataSP.m_sTrsf.m_sYVector.m_dZ = d.z;

	sDataSP.m_sTrsf.m_sScale.m_dX = sDataSP.m_sTrsf.m_sScale.m_dY = sDataSP.m_sTrsf.m_sScale.m_dZ = 1.0f;

	A3DSurfPlaneCreate(&sDataSP,&splane);
	sData.m_pPlane = splane;
	

	if (pmiList->count)
	{
		sData.m_uiAnnotationsSize = pmiList->count;
		sData.m_ppAnnotations = new A3DMkpAnnotationEntity*[pmiList->count];
		int i = 0;
		START_LIST_ITERATION(A3DMkpAnnotationEntity, pmiList);
			sData.m_ppAnnotations[i] = temp;
 			if (!temp)
				break;
			i++;
		END_LIST_ITERATION(pmiList);
	}
		
  	delete_vlist(pmiList);



 	iRet = A3DMkpViewCreate(&sData, &viewItem);

	delete [] sData.m_ppAnnotations;

	return viewItem;
}



A3DAsmPartDefinition* H3DXExporter::createPart(HC_KEY segmentkey, bool hasColor, bool lineVisibility, bool faceVisibility, bool isInclude)
{
	HC_KEY key;
	A3DAsmPartDefinition* pPartDefinition = NULL;
	vlist_t *viewList = new_vlist(malloc,free);

//	if (!lineVisibility && !faceVisibility)
//		return NULL;

	A3DAsmPartDefinitionData sData;
	A3D_INITIALIZE_DATA(A3DAsmPartDefinitionData, sData);


	int count;
	HC_Open_Segment_By_Key(segmentkey);	
	if (!lineVisibility && faceVisibility)
		HC_Begin_Contents_Search(".", "shell, nurbs surface, mesh, polygon, sphere, cylinder, reference");
	else if (!faceVisibility && lineVisibility)
		HC_Begin_Contents_Search(".", "line, polyline, circular arc, elliptical arc, ellipse, nurbs curve, reference");
	else
 		HC_Begin_Contents_Search(".", "shell, nurbs surface, mesh, sphere, polygon,cylinder, line, polyline, circular arc, elliptical arc, ellipse, nurbs curve, reference");
	HC_Show_Contents_Count(&count);  
	sData.m_uiRepItemsSize = count;
	sData.m_ppRepItems = new A3DRiRepresentationItem*[count];
	int i=0;
	while (HUtility::FindContents(key))
	{
		char keytype[MVO_BUFFER_SIZE];
		HC_Show_Key_Type(key, keytype);
	
#if 1		
		if (strcmp(keytype, "segment") == 0)	
		{
			HC_Open_Segment_By_Key(key);
			char res[4096];
			if (HUtility::ShowOneUserOption("pmi_type", res))
			{
				if (strcmp(res, "view") == 0)
				{
 					A3DMkpView *view = createView(key);
					vlist_add_last(viewList, view);

				}
			}
			HC_Close_Segment();

		}
#endif
		if (strcmp(keytype, "reference") == 0)	
		{
			HC_KEY referencekey = key;
 			key =HC_KShow_Reference_Geometry(key);
			HC_KEY okey = HC_KShow_Owner_By_Key(key);
			HC_Show_Key_Type(key, keytype);
			if (strcmp(keytype, "shell") == 0)	
			{
				HC_Show_Segment(segmentkey, keytype);
				HC_Show_Segment(okey, keytype);
				float matrix[4096];
				HC_Open_Geometry(referencekey);
				HC_Show_Modelling_Matrix(matrix);
				HC_Close_Geometry();
				HC_KEY tempkey  = HC_KOpen_Segment("/temp");
				key = HC_KCopy_Geometry(key, ".");
				HC_Close_Segment();
				HShellWrapper myshell(key);				
				HC_Compute_Transformed_Points(myshell.m_plen, myshell.m_Points, matrix, myshell.m_Points);
 				myshell.Regenerate(-1, false, true);
 				sData.m_ppRepItems[i++] = createRI(key, hasColor, lineVisibility, faceVisibility, isInclude);
				HC_Delete_By_Key(tempkey);
			}
		}
		else
			sData.m_ppRepItems[i++] = createRI(key, hasColor, lineVisibility, faceVisibility, isInclude);

	}

	HC_End_Contents_Search();
	HC_Close_Segment();




	if (viewList->count)
	{
		sData.m_uiViewsSize = viewList->count;
		sData.m_ppViews = new A3DMkpView*[viewList->count];
		i = 0;
		START_LIST_ITERATION(A3DMkpView, viewList);
		sData.m_ppViews[i] = temp;
 			if (!temp)
				break;
			i++;
		END_LIST_ITERATION(viewList);
	}


  	delete_vlist(viewList);


 	A3DInt32 iRet = A3DAsmPartDefinitionCreate(&sData, &pPartDefinition);

	delete [] sData.m_ppRepItems;
	delete [] sData.m_ppViews;
	return pPartDefinition;

 
}


static int iii;

float determinant3x3 (float *m) 
{
	return (
		m[0] * (m[1+4]*m[2+8] - m[2+4]*m[1+8]) -
		m[1] * (m[0+4]*m[2+8] - m[2+4]*m[0+8]) +
		m[2] * (m[0+4]*m[1+8] - m[1+4]*m[0+8])
	);
}


A3DAsmProductOccurrence * H3DXExporter::createOccurrenceRecursive(HC_KEY segmentkey, bool hasColor, bool lineVisibility, bool faceVisibility, bool isInclude)
{


	m_VertexColorFound = false;
	bool hasMatrix = false;
	A3DAsmProductOccurrence *prototype = NULL;
 	A3DAsmProductOccurrence* pProductOccurrence = NULL;
 	char onoff[MVO_BUFFER_SIZE];
 	HC_Open_Segment_By_Key(segmentkey);

	if (HC_Show_Existence("heuristics = exclude bounding"))
	{
		HC_Close_Segment();
		return 0;
	}
 

	vlist_t *occurenceList = new_vlist(malloc,free);
	vlist_t *pmiList = new_vlist(malloc,free);
	vlist_t *viewList = new_vlist(malloc,free);

	if (HC_Show_Existence("visibility = faces"))
	{
		HC_Show_One_Visibility("faces", onoff);
		if (strcmp(onoff, "off") == 0)
			faceVisibility = false;
	}
	if (HC_Show_Existence("visibility = lines"))
	{
		HC_Show_One_Visibility("lines", onoff);
		if (strcmp(onoff, "off") == 0)
			lineVisibility = false;
	}
	
 		
	if (HC_Show_Existence("color"))
		hasColor = true;

	HC_Begin_Contents_Search(".", "segments, includes");
	
	char type[MVO_BUFFER_SIZE];
	HC_KEY key;
	char res[4096];
	while (HC_Find_Contents(type, &key))
	{
	if (strcmp(type,"segment") == 0)
		{
			HC_Show_Segment(key, res);
			bool skip = false;
			HC_Open_Segment_By_Key(key);
			if (HC_Show_Existence("camera") || HC_Show_Existence("window") )
				skip = true;

   			if (HUtility::ShowOneUserOption("pmi_type", res) && strcmp(res, "view") == 0)
			{
 					A3DMkpView *view = createView(key);
					vlist_add_last(viewList, view);
//					skip = true;

			}
			else if (HUtility::ShowOneUserOption("pmi_type", res))
			{
 					skip = true;
					A3DMkpAnnotationEntity *annotation = createPMI(key);
					if (annotation)
						vlist_add_last(pmiList, annotation);

 			}


			HC_Close_Segment();
			if (!skip)
			{
				char segment[MVO_BUFFER_SIZE];
				HC_Show_Segment(key, segment);
				if (strstr(segment, "model_include") == 0 || isInclude)
				{
					A3DAsmProductOccurrence *occurence = createOccurrenceRecursive(key,  hasColor, lineVisibility, faceVisibility, isInclude);
					if (occurence)
						vlist_add_last(occurenceList, occurence);
				}
			}
		}
		else if (strcmp(type,"include") == 0)
		{
			bool skip = false;
			HC_Open_Segment_By_Key(HC_KShow_Include_Segment(key));
			if (HUtility::ShowOneUserOption("pmi_type", res))
			{
				if (strcmp(res, "view") != 0)
				{
 					A3DMkpAnnotationEntity *annotation = createPMI(HC_KShow_Include_Segment(key));
					if (annotation)
						vlist_add_last(pmiList, annotation);
					skip = true;
				}
			}
			HC_Close_Segment();
 
			if (!skip)
				prototype = createInclude(key,  hasColor);
 		}				

	}
	HC_End_Contents_Search();

	A3DAsmPartDefinition* partDefinition = NULL;
 	if (HC_Show_Existence("geometry"))
		partDefinition  = createPart(segmentkey, hasColor, lineVisibility, faceVisibility, isInclude);
	
	HC_Close_Segment();

 
 	A3DAsmProductOccurrenceData sData;
	A3D_INITIALIZE_DATA(A3DAsmProductOccurrenceData, sData);

 
	int count  = 0;
	START_LIST_ITERATION(A3DAsmProductOccurrence, occurenceList);
		count++;
		if (!temp)
			break;
	END_LIST_ITERATION(occurenceList);


	sData.m_uiPOccurrencesSize = count;
	sData.m_ppPOccurrences = new A3DAsmProductOccurrence*[count];
	int i = 0;
	START_LIST_ITERATION(A3DAsmProductOccurrence, occurenceList);
		sData.m_ppPOccurrences[i] = temp;
 		if (!temp)
			break;
		i++;
	END_LIST_ITERATION(occurenceList);

	delete_vlist(occurenceList);


	if (pmiList->count)
	{
		sData.m_uiAnnotationsSize = pmiList->count;
		sData.m_ppAnnotations = new A3DMkpAnnotationEntity*[pmiList->count];
		i = 0;
		START_LIST_ITERATION(A3DMkpAnnotationEntity, pmiList);
			sData.m_ppAnnotations[i] = temp;
 			if (!temp)
				break;
			i++;
		END_LIST_ITERATION(pmiList);
	}



  	delete_vlist(pmiList);

	if (viewList->count)
	{
		sData.m_uiViewsSize = viewList->count;
		sData.m_ppViews = new A3DMkpView*[viewList->count];
		i = 0;
		START_LIST_ITERATION(A3DMkpView, viewList);
		sData.m_ppViews[i] = temp;
 			if (!temp)
				break;
			i++;
		END_LIST_ITERATION(viewList);
	}

  	delete_vlist(viewList);

	HC_Open_Segment_By_Key(segmentkey);
	float matrix[16];
	A3DMiscCartesianTransformation    *pMiscCartesianTransformation = NULL;
	A3DMiscCartesianTransformationData sMiscCartesianTransformData;
	if (HC_Show_Existence("modelling matrix"))
	{
		HC_Show_Modelling_Matrix(matrix);
  		
		float det = determinant3x3(matrix);



		A3D_INITIALIZE_DATA(A3DMiscCartesianTransformationData, sMiscCartesianTransformData);

		sMiscCartesianTransformData.m_sXVector.m_dX = matrix[0];
		sMiscCartesianTransformData.m_sXVector.m_dY = matrix[1];
		sMiscCartesianTransformData.m_sXVector.m_dZ = matrix[2];

		sMiscCartesianTransformData.m_sYVector.m_dX = matrix[4];
		sMiscCartesianTransformData.m_sYVector.m_dY = matrix[5];
		sMiscCartesianTransformData.m_sYVector.m_dZ = matrix[6];

		sMiscCartesianTransformData.m_sOrigin.m_dX = matrix[12];
		sMiscCartesianTransformData.m_sOrigin.m_dY = matrix[13];
		sMiscCartesianTransformData.m_sOrigin.m_dZ = matrix[14];
 
		float scale = (float) sqrt((matrix[0]*matrix[0])
				+(matrix[1]*matrix[1])
				+(matrix[2]*matrix[2]));
		
		sMiscCartesianTransformData.m_sScale.m_dX = scale;
		sMiscCartesianTransformData.m_sScale.m_dY = scale;
		sMiscCartesianTransformData.m_sScale.m_dZ = scale;

		if (det<0)
			sMiscCartesianTransformData.m_ucBehaviour = 4;
 		A3DInt32 iRet = A3DMiscCartesianTransformationCreate(&sMiscCartesianTransformData, &pMiscCartesianTransformation);	
		sData.m_pLocation = pMiscCartesianTransformation;

	}
	HC_Close_Segment();

	sData.m_pPart = partDefinition;
	sData.m_pPrototype = prototype;	
	A3DInt32 iRet = A3DAsmProductOccurrenceCreate(&sData, &pProductOccurrence);

	HC_KEY okey = HC_KShow_Original_Key(segmentkey);
	char text[MVO_BUFFER_SIZE];
	char segmentname[MVO_BUFFER_SIZE];
	HC_Show_Segment(segmentkey,text);
	HC_Parse_String(text, "/", -1, segmentname);

	A3DRootBaseData rootBase;
	A3D_INITIALIZE_DATA(A3DRootBaseData, rootBase);

	rootBase.m_pcName = new A3DUTF8Char[256];
	if (segmentname[0] != '@')
		sprintf(rootBase.m_pcName,"%s.%p", segmentname,okey);
	else
		sprintf(rootBase.m_pcName,"%p", okey);

	A3DRootBaseSet(pProductOccurrence, &rootBase);

	SetColor(pProductOccurrence, segmentkey, false, hasColor && !m_VertexColorFound,(lineVisibility || faceVisibility));

	m_VertexColorFound = false;
	delete [] sData.m_ppPOccurrences;
	delete [] sData.m_ppAnnotations;
	delete [] sData.m_ppViews;
	delete [] rootBase.m_pcName;
	return pProductOccurrence;
}




A3DAsmProductOccurrence * H3DXExporter::createOccurrence()
{

	return createOccurrenceRecursive(m_modelKey, false, true, true, false);
}


A3DAsmModelFile * H3DXExporter::createModelFile()
{


	HC_Open_Segment_By_Key(m_modelKey);
	bool colormapfound = INT2bool(HC_Show_Existence("color map"));
	HC_Close_Segment();
	if (colormapfound)
		AddTexture(m_modelKey);

	gatherTextures(m_modelKey);

	A3DAsmModelFileData sData;
	A3D_INITIALIZE_DATA(A3DAsmModelFileData, sData);

	sData.m_uiPOccurrencesSize = 1;
	sData.m_dUnit = 1.0;
	sData.m_ppPOccurrences = new A3DAsmProductOccurrence*[1];

	sData.m_ppPOccurrences[0] = createOccurrence();
	//sData.m_ppPOccurrences[0] = 0;

	A3DAsmModelFile * pModelFile = 0;

	A3DInt32 iRet = A3DAsmModelFileCreate(&sData, &pModelFile);

	delete [] sData.m_ppPOccurrences;
	
	return pModelFile;
}

bool H3DXExporter::Export(wchar_t const * file_name, HC_KEY model_key, HOutputHandlerOptions * options)
{
	m_modelKey = model_key;

	m_pView = options->m_pHBaseView;
	if (!A3DSDKLoadLibrary())
		return false;

	SetLicense();

	A3DDllInitialize(A3D_DLL_MAJORVERSION, A3D_DLL_MINORVERSION);

	A3DAsmModelFile * pModelFile = 0;

	wchar_t extension[128];
	HUtility::FindFileNameExtension(file_name, extension);

	if (wcsieq(extension, L"iges") || wcsieq(extension, L"step") || wcsieq(extension, L"x_t"))
	{
		if (!options)
			return false;

		if (!(pModelFile = options->m_pExtendedData))
			return false;
	}

	A3DInt32 iRet = A3D_SUCCESS;

	if (wcsieq(extension, L"iges"))
	{
		A3DRWParamsExportIgesData params;
		A3D_INITIALIZE_DATA(A3DRWParamsExportIgesData, params);
		params.m_bSaveAnalyticsToNurbs = false;
		params.m_bSaveFacetedToWireframe = false;
		params.m_bSaveSolidsAsFaces = false;
		params.m_bWriteHiddenObjects = false;

		iRet = A3DAsmModelFileExportToIgesFile(pModelFile, &params, (A3DUTF8Char const *)H_UTF8(file_name).encodedText());

	}
	else if (wcsieq(extension, L"step"))
	{
		A3DRWParamsExportStepData params;
		A3D_INITIALIZE_DATA(A3DRWParamsExportStepData, params);
		params.m_eStepFormat = kA3DStepAP214;
		params.m_bSaveFacetedToWireframe = false;
		params.m_bSaveAnalyticsToNurbs = false;
		params.m_bUseShortNames = false;

		iRet = A3DAsmModelFileExportToStepFile(pModelFile, &params, (A3DUTF8Char const *)H_UTF8(file_name).encodedText());

	}
	else if (wcsieq(extension, L"x_t"))
	{
		A3DRWParamsExportParasolidData params;
		A3D_INITIALIZE_DATA(A3DRWParamsExportParasolidData, params);
		params.m_bSaveSolidsAsFaces = false;

		iRet = A3DAsmModelFileExportToParasolidFile(pModelFile, &params, (A3DUTF8Char const *)H_UTF8(file_name).encodedText());

	}
	else // just write out a prc file
	{
		A3DRWParamsExportPrcData params;
		A3D_INITIALIZE_DATA(A3DRWParamsExportPrcData, params);
		params.m_bCompressBrep = false;
		params.m_bCompressTessellation = false;
		params.m_eCompressBrepType = kA3DCompressionLow;
		A3DRWParamsPrcWriteHelper *helper = NULL;

		m_texturehash = new_vhash(10, malloc, free);
		m_instancehash = new_vhash(10, malloc, free);

		pModelFile = createModelFile();

		iRet = A3DAsmModelFileExportToPrcFile(pModelFile, &params, (A3DUTF8Char const *)H_UTF8(file_name).encodedText(), &helper);

		A3DAsmModelFileDelete(pModelFile);

		delete_vhash(m_texturehash);
		delete_vhash(m_instancehash);
	}

	return (iRet == A3D_SUCCESS);
}

void BREP_Edge_Matcher::AddModellerEdge(void *edgeid)
{
	long ppp = 0;

	int res = vhash_lookup_item(m_edgehash, (void *)edgeid , (void **)&ppp);
	if  (res == VHASH_STATUS_SUCCESS)
	{
		vlist_add_last(m_edgelist, (void *)ppp);
		vlist_add_last(m_edgeidlist, (void *)edgeid);
 	}
	else
	{
		vlist_add_last(m_edgelist, (void *)m_edgenum);
		vlist_add_last(m_edgeidlist, (void *)edgeid);
		vhash_insert_item(m_edgehash, (void *)edgeid  , (void *)m_edgenum);
  	}
	m_edgenum++;
 }

void BREP_Edge_Matcher::StartEdgeIteration()
{
	m_edgekeys = new HC_KEY[m_edgenum+1];
	m_edgenum = 1;
 	vlist_reset_cursor(m_edgelist);
}

bool BREP_Edge_Matcher::NextEdge(HC_KEY edgekey, HC_KEY &origkey, void **origid)
{
	bool ret = false;
	origkey = edgekey;
	long currentedge = (long)vlist_peek_cursor(m_edgelist);
	if (currentedge == 0)
	{
		origid = 0;
		return true;
	}
 	void *currentedgeid = (void *)vlist_peek_cursor(m_edgeidlist);
	if (!currentedge || currentedge==m_edgenum)
		ret = true;
	
	if (currentedge == m_edgenum)
		m_edgekeys[m_edgenum] = edgekey;
	else
	{
		m_edgekeys[m_edgenum] = m_edgekeys[currentedge];
		origkey =  m_edgekeys[currentedge];
	}

	vlist_advance_cursor(m_edgelist);
	vlist_advance_cursor(m_edgeidlist);
	*origid = currentedgeid;
	m_edgenum++;
	return ret;
}
  
BREP_Edge_Matcher::BREP_Edge_Matcher()
{
	m_edgenum = 1;
 	m_edgehash = new_vhash(10,malloc, free);
	m_edgelist = new_vlist(malloc, free);
	m_edgeidlist = new_vlist(malloc, free);
	m_edgekeys = 0;
}
BREP_Edge_Matcher::~BREP_Edge_Matcher()
{

	delete [] m_edgekeys;
	delete_vhash(m_edgehash);
	delete_vlist(m_edgelist);
	delete_vlist(m_edgeidlist);
}


void BREP_Edge_Matcher::Restart()
{
	vlist_flush(m_edgelist);
	vhash_flush(m_edgehash);
	vlist_flush(m_edgeidlist);

	delete [] m_edgekeys;
	m_edgekeys = 0;
	m_edgenum = 1;
 
}
 

