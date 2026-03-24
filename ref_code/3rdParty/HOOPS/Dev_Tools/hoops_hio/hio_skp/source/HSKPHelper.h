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
// $Header: /files/homes/master/cvs/hoops_master/hio_skp/source/HSKPHelper.h,v 1.24 2010-06-28 14:14:15 mustafa Exp $
//

#ifndef _HSKPHELPER_H
#define _HSKPHELPER_H

#ifndef CLASS_HSKPImporter_DEF
#define CLASS_HSKPImporter_DEF


#include <atlbase.h>
#include <atlcom.h>
#include <comdef.h>
using namespace ATL;
#include "SketchUp_i.h"
#include "SketchUpAddin.h"
	

#else


#endif

#ifdef H_PACK_8
#pragma pack(push)
#pragma pack(8)
#endif

// HOOPS/MVO includes
#include "HDB.h"
#include "HIOManager.h"

#include <iostream>
#include <set>
using namespace std;


// Mesh can be created with optional UV front/back coordinates,
// and optional normal vectors. UV coordinates are
// currently Point3d's with X=U, Y=V, Z=Q.  Q will always be 1
// for affine texture transforms.
#define PolygonMeshPoints	    0
#define PolygonMeshUVQFront		1
#define PolygonMeshUVQBack	    2
#define PolygonMeshNormals      4


class HSKPImporter
{
	
private:
	
	HC_KEY m_rImageKey;
	HInputHandlerOptions m_rInputOptions;
	bool m_bIsColorByLayer;
	bool m_bIsPartofComponentOrGroup;
	OLE_COLOR m_rCompOrGroupLayerColor;
	char* m_cFaceSide;
	HInputHandler * m_pReader ;
	char m_ctexture_path[MVO_BUFFER_SIZE];
	char m_ctexture_path_back[MVO_BUFFER_SIZE];
	char m_ccolor_opts[MVO_BUFFER_SIZE];
    char m_cTextureDirectory[MVO_BUFFER_SIZE];
	//CComPtr<ISkpTextureWriter> m_pTextureWriter;
	CComPtr<ISkpTextureWriter> m_pTextureWriter;
	HC_KEY m_model_key;
	bool ignoreOffEntities;
	bool m_bSkpFitworld ;
	bool m_bImportMetadata;
	long m_totalEntities;
	bool m_bIsCompTex;//to check whether component texture is present or no
	bool m_bIsGroupTex;//to check whether group texture is present or no
	HInputHandler* m_pInputhandler;

	std::set<long> m_setTextureHandles;
	std::set<long> m_setBackTextureHandles;
	void WriteOptionsProvider(const char* title, CComPtr<ISkpNamedValues> pNVs);
	void applyMaterialOnFace(CComPtr<ISkpFace> pFace);
	bool AddtextureInScene(CComPtr<ISkpTexture> pTexture, long texture_handle, char * filename_out);
	
public:
	

	HSKPImporter(CComPtr<ISkpTextureWriter> textureWriter);
	
	~HSKPImporter();

	void setTotalEntities(CComPtr<ISkpDocument> pDoc);
	void setInputHandler(HInputHandler* val){m_pInputhandler = val;};
	
	HInputHandler* getInputHandler()
	{
		return m_pInputhandler;
	};
	void set_ignoreOffEntities(bool val){ ignoreOffEntities = val;};

	CComPtr<ISkpDocument> getSKPDatabase(const char *, CComPtr<ISkpApplication> pApp);
	void importSKPEdges(CComPtr<ISkpEntityProvider> );
	void importEdges(char* geometrySeg_name, CComPtr<ISkpEdges> pEdges, int i, int edgesIncurve_count);
	void importSKPEdgesInComponent(CComPtr<ISkpEntityProvider> );
	void importSKPFaces(CComPtr<ISkpEntityProvider>, bool fromCompOrGroup);
	void importSKPImage(CComPtr<ISkpEntityProvider>, bool fromCompOrGroup );
	void importSKPPages(CComPtr<ISkpDocument> pDoc,HInputHandlerOptions * options);
	void importSKPComponents(CComPtr<ISkpEntityProvider>, bool fromCompOrGroup );
	void importSKPGroups(CComPtr<ISkpEntityProvider>, bool fromCompOrGroup );
	void importSKPText(CComPtr<ISkpEntityProvider> );
	void setDefaultOptions(CComPtr<ISkpDocument> pDoc);
	void conditionStringForSegName(char* zString);
	void getSegName(CComPtr<ISkpDrawingElement> pDrawable, char seg_name[]);
	void setTextureDirectory();
	void defineTexture(char * filename_out, long texture_handle);
	void transformPointsFromRotationTranslate(double *angle,HPoint* axis, HPoint* points,HPoint* origin);
	void setModelKey(HC_KEY key);
	double round(double x);
	void fitToScene(HInputHandlerOptions * options);
	BOOL deleteDirectory(const TCHAR* sPath);
	BOOL isDots(const TCHAR* str);
	void set_importMetadata(bool mdata)
	{
		m_bImportMetadata = mdata;
	}


};

#ifdef H_PACK_8
#pragma pack(pop)
#endif

#endif
//#endif



