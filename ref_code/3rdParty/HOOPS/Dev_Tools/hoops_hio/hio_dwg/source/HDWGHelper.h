// (C) Copyright 1996,1998 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//
// HDWGHelper.H

#ifndef HDWG_HELPER_H_
#define HDWG_HELPER_H_ 1

#ifdef H_PACK_8
#pragma pack(push)
#pragma pack(8)
#endif


//#include <wchar.h>
#include <map>
#include <vector>

#include "acgi.h"
#include "hc.h"
#include "HTools.h"
#include "HUtility.h"

#include "BStream.h"
#include "BOpcodeShell.h"

#include "sorttab.h "

#include "windows.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "time.h"

#include "dbimage.h"
#include "imgdef.h"
#include "imgent.h"

#include "dbobjptr.h"
#include "acdblmgr.h"
#include "dbmleader.h"	// For AcDbMLeader
#include "dbspfilt.h"	// For Clips on blockref
#include "dbole.h"



#define _t(str) L##str
typedef unsigned int        UINT;



class HInputHandlerOptions;
class HIOConnectorDWG;
class HIOUtilityDWG;

class AcDbMText;
struct AcDbMTextFragment;
class AcDbCircle;
class AcDbLeader;
class AcDbMLeader;
class AcDbDimension;
class AcDbMaterial;
class AcDbPoint;
class AcDbMInsertBlock;
class AcDbLine;
class AcDbXline;
class AcDbRay;
class AcDbPolygonMesh;

#ifdef WIN32
class AcDbTable;
#endif 

typedef int  BOOL;

// Functions to condition strings form database to be used as segment name.
void condition_string_for_segment_name(char* zString);
void condition_string_for_segment_name(wchar_t* zString);
void condition_string_for_user_options(char* zString);
void condition_string_for_user_options(wchar_t* zString);
void condition_string_for_special_characters(wchar_t* zString);

// To get the rectangle from bounding box
void Get_Image_Rectangle_For_Shell(AcDbRasterImage* pEnt, HPoint * Rect);
// AcDbRatsterImage import Functions
void InsertClipRegion(AcDbRasterImage* pEnt, BStreamFileToolkit * pBStreamtk = 0);
int GetImageFileName(AcDbRasterImageDef* ImageDef, char * pFilePath, char * pImageName) ;
// Camera settings in viewports
int GetCameraForInitialView(HCamera &camera , AcDbViewportTableRecord* pRecord);
/*! Set default render mode for active view */
void SetRenderMode(HInputHandlerOptions * pInputOptions, AcDbViewportTableRecord* pRecord);
// text transformation matrix
void GetModelingMatrixForText(float my_center[], float my_path1[], float my_norm1[], float h_matrix_trans[]);
// For Stream Writing
TK_Status WriteObject(BBaseOpcodeHandler * handler, BStreamFileToolkit * tk, FILE * fp, char * buffer, int size); 
// For Getting Layout views and clip regions
void get_layout_data(AcDbObjectId viewPortId,AcDbDatabase *pAcDbDatabase,HPoint *ClipPoint,float *matrix,int *no_ClipPoint,AcCmEntityColor* entityColor, bool * is_On);
// Convert to lower case
void ConverToLower(char * to_lower);
// Check for file existance
bool hio_dwg_check_file_exist(const wchar_t * full_filepath);
// For Clips on BlockRefs
BOOL insertClip(AcDbBlockReference * ref, BStreamFileToolkit * pBStreamtk = 0);
// Checking for invalid entities (having large and invalid values)
bool CheckForInvalidExtents(AcDbEntity * pEnt);


// define HIODWG_IMPORT_POINTS if you want to import the 0 dimensional entities viz. AcDbPoint etc.
//#define HIODWG_IMPORT_POINTS

#define HDWG_PI			((double)3.14159265358979323846)
#define HDWG_F_PI		((float)HDWG_PI)
#define H_MM_TO_POINTS	2.83465f
#define H_LWDEFAULT		AcDb::kLnWt025;
#define HDWG_MATERIALS_LIBRARY_SEGMENT	"DWG_MATERIALS_STYLE_LIBRARY"
#define HIODWG_SCRATCH_SEGMENT			"/include library/dwg_scratch_segment"

#define GetBValueFromRGBM(rgbm)      ((unsigned char)(rgbm))
#define GetGValueFromRGBM(rgbm)      ((unsigned char)((unsigned long)(rgbm)>>8))
#define GetRValueFromRGBM(rgbm)      ((unsigned char)((unsigned long)(rgbm)>>16))
#define GetMValueFromRGBM(rgbm)      ((unsigned char)((unsigned long)(rgbm)>>24))

#define countof(array)	sizeof(array)/sizeof(array[0])
#define nEntNames		countof(EntityList)


#define MARKER_OPCODE_START_FILL			-1
#define MARKER_OPCODE_RESTART_FILL			-2
#define MARKER_OPCODE_END_FILL				-3
#define MARKER_OPCODE_ELLIPSE				-4
#define MARKER_OPCODE_CIRCULAR_ARC			-5
#define MARKER_OPCODE_INFINITE_LINE			-6
#define MARKER_OPCODE_INFINITE_RAY			-7
#define MARKER_OPCODE_START_CONTRAST_COLOR	-8
#define MARKER_OPCODE_START_NORMAL_COLOR	-9
#define MARKER_OPCODE_START_RGB_COLOR		-10
#define MARKER_OPCODE_START_INDEXED_COLOR	-11
#define MARKER_OPCODE_TERMINATE 0
#define MARKER_OPCODE_POINT		1
#define MARKER_OPCODE_LINE_2	2
#define MARKER_OPCODE_LINE_3	3
#define MARKER_OPCODE_LINE_4	4
#define MARKER_OPCODE_LINE_5	5
#define MARKER_OPCODE_LINE_6	6
#define MARKER_OPCODE_LINE_7	7
#define MARKER_OPCODE_LINE_8	8
#define MARKER_OPCODE_LINE_9	9
#define MARKER_OPCODE_LINE_10	10
#define MARKER_OPCODE_LINE_11	11
#define MARKER_OPCODE_LINE_12	12
#define MARKER_OPCODE_LINE_13	13


const char PDMODE_4[] = // a half sized vertical bar (upper half)
	{
		100, 0, 0,   
		MARKER_OPCODE_LINE_2,	0, 0, 
								0, 100, 
		MARKER_OPCODE_TERMINATE
	};

const char PDMODE_34[] = // a circle with + sign. + spills outside the circle
	{
		100, 0, 0,   
		MARKER_OPCODE_LINE_2,	-100, 0, 
								 100, 0, 
		MARKER_OPCODE_LINE_2,	  0, -100, 
								  0,  100, 
		MARKER_OPCODE_ELLIPSE,	-60, -60, 60, 60,

		MARKER_OPCODE_TERMINATE
	};

const char PDMODE_35[] = // a circle with x sign. x spills outside the circle
	{
		100, 0, 0,   
		MARKER_OPCODE_LINE_2,	-100, -100, 
								 100,  100, 
		MARKER_OPCODE_LINE_2,	-100,  100, 
								 100, -100, 
		MARKER_OPCODE_ELLIPSE,	-100, -100, 100, 100,

		MARKER_OPCODE_TERMINATE
	};

const char PDMODE_36[] = // a circle over a half-vertical-bar
	{
		100, 0, 0,   
		MARKER_OPCODE_LINE_2,	0, 0, 
								0, 100, 
		MARKER_OPCODE_ELLIPSE,	-100, -100, 100, 100,

		MARKER_OPCODE_TERMINATE
	};

const char PDMODE_66[] = // a square over + sign (+ spilling out a bit)
	{
		100, 0, 0,   
		MARKER_OPCODE_LINE_2,	-100, 0, 
								 100, 0, 
		MARKER_OPCODE_LINE_2,	  0, -100, 
								  0,  100, 
		MARKER_OPCODE_LINE_5,	-60, -60,	-60, 60,
								 60, 60,	60, -60, -60, -60,
		MARKER_OPCODE_TERMINATE
	};

const char PDMODE_68[] = // a square over half-vertical-bar
	{
		100, 0, 0,   
		MARKER_OPCODE_LINE_2,	0, 0, 
								0, 100, 
		MARKER_OPCODE_LINE_5,	-100, -100,	-100, 100,
								 100, 100,	100, -100,-100, -100,
		MARKER_OPCODE_TERMINATE
	};

const char PDMODE_96[] = // a square and a circle over a dot
	{
		100, 0, 0,   
		MARKER_OPCODE_ELLIPSE,	-100, -100, 100, 100, 
		MARKER_OPCODE_LINE_5,	-100, -100,	-100, 100,
								 100, 100,	100, -100,-100, -100,
		MARKER_OPCODE_POINT,	0, 0,
		MARKER_OPCODE_TERMINATE
	};

const char PDMODE_97[] = // a square and a circle
	{
	100, 0, 0,   
		MARKER_OPCODE_ELLIPSE,	-100, -100, 100, 100, 
		MARKER_OPCODE_LINE_5,	-100, -100,	-100, 100,
								 100, 100,	100, -100,-100, -100,
		MARKER_OPCODE_TERMINATE
	};

const char PDMODE_98[] = // a square and a circle over + (spillage of +)
	{
		100, 0, 0,   
		MARKER_OPCODE_LINE_2,	-100, 0, 
								 100, 0, 
		MARKER_OPCODE_LINE_2,	  0, -100, 
								  0,  100, 
		MARKER_OPCODE_LINE_5,	-60, -60,	-60, 60,
								 60, 60,	60, -60, -60, -60,
		MARKER_OPCODE_ELLIPSE,	-60, -60, 60, 60, 
		MARKER_OPCODE_TERMINATE
	};

const char PDMODE_99[] = // a square and a circle over a cross
	{
		100, 0, 0,   
		MARKER_OPCODE_LINE_2,	-100, -100, 
								 100,  100, 
		MARKER_OPCODE_LINE_2,	-100,  100, 
								 100, -100, 
		MARKER_OPCODE_LINE_5,	-100, -100,	-100, 100,
								 100, 100,	100, -100, -100, -100,
		MARKER_OPCODE_ELLIPSE,	-100, -100, 100, 100, 
		MARKER_OPCODE_TERMINATE
	};

const char PDMODE_100[] = // a square and a circle over a half-vertical-bar
	{
		100, 0, 0,   
		MARKER_OPCODE_ELLIPSE,	-100, -100, 100, 100,
		MARKER_OPCODE_LINE_2,	   0,  0, 
								   0,  100, 
		MARKER_OPCODE_LINE_5,	-100, -100,	-100, 100,
								 100, 100,	100, -100, -100, -100,
		MARKER_OPCODE_ELLIPSE,	-100, -100, 100, 100,
		MARKER_OPCODE_TERMINATE
	};


struct HIODWG_GLYPH
{
	Adesk::Int16 iSymbolPDMODE;			// PDMODE value (Ref. to AutoCAD command reference
	char *pSymbolName;					// Corresponding HOOPS marker symbol name or glyph name
	const char *pSymbolDefinition;		// Glyph definition array. 0 for standard HOOPS markers
	unsigned int nSybolDefinitionSize;	// Size of Glyph definition array. 0 for standard HOOPS markers
	int opcode_index;			// Corresponding opcode enum.
};

static HIODWG_GLYPH GlyphTable[] =
{
	0,	".",			0,				0,					TKO_Marker_Dot,
	2,	"+",			0,				0,					TKO_Marker_Plus,	
	3,	"x",			0,				0,					TKO_Marker_X,
	4,	"PDMODE_4",		PDMODE_4,		countof(PDMODE_4),	-1,

	32,	"(.)",			0,				0,					TKO_Marker_Circle_Dot,
	33, "O",			0,				0,					TKO_Marker_Circle ,
	34,	"PDMODE_34",	PDMODE_34,		countof(PDMODE_34),	-1,
	35, "PDMODE_35",	PDMODE_35,		countof(PDMODE_35),	-1,
	36, "PDMODE_36",	PDMODE_36,		countof(PDMODE_36),	-1,

	64, "[.]",			0,				0,					TKO_Marker_Box_Dot,
	65, "[]",			0,				0,					TKO_Marker_Box,
	66, "PDMODE_66",	PDMODE_66,		countof(PDMODE_66),	-1,
	67, "[x]",			0,				0,					TKO_Marker_Box_X ,
	68, "PDMODE_68",	PDMODE_68,		countof(PDMODE_68),	-1,

	96,		"PDMODE_96",	PDMODE_96,	countof(PDMODE_96),	-1,
	97,		"PDMODE_97",	PDMODE_97,	countof(PDMODE_97),	-1,
	98,		"PDMODE_98",	PDMODE_98,	countof(PDMODE_98),	-1,
	99,		"PDMODE_99",	PDMODE_99,	countof(PDMODE_99),	-1,
	100,	"PDMODE_100",	PDMODE_100,	countof(PDMODE_100),-1
};



struct ENTNAMES
{
	const wchar_t *pName;
	void (* func)(AcDbEntity *);
};

static ENTNAMES EntityList[] =
{
	// import explicitly
	L"AcDbBlockReference",               0,	//0
	L"AcDbMInsertBlock",					0,	//1

	// import both shaded & wireframe modes
	L"AcDbBlockTableRecord",             0,  //2                                          
	L"AcDb3dSolid",                      0,	//3
	L"AcDbBody",                         0,	//4
	L"AcDbFace",                         0,	//5
	L"AcDbRegion",                       0,	//6
	L"AcDbShape",                        0,	//7
	L"AcDbSolid",                        0,	//8
	L"AcDbFace",                         0,	//9
	L"AcDbPolyFaceMesh",                 0,	//10
	L"AcDbPolygonMesh",                  0,	//11
	L"AcDbExtrudedSurface",				0,	//12

	// import wireframe mode only
	L"AcDbHatch",                       0,	//13
	L"AcDbMText",                       0,	//14
	L"AcDbText",                        0,	//15
	L"AcDbCurve",						0,	//16
	L"AcDb2dPolyline",					0,	//17
	L"AcDb3dPolyline",					0,	//18
	L"AcDbArc",						    0,	//19
	L"AcDbCircle",						0,	//20
	L"AcDbEllipse",						0,	//21
	L"AcDbLeader",						0,	//22
	L"AcDbLine",						0,	//23
	L"AcDbPolyline",					0,	//24
	L"AcDbRay",							0,	//25
	L"AcDbSpline",						0,	//26
	L"AcDbXline",						0,	//27
	L"AcDbVertex",                      0,	//28
	L"AcDb2dVertex",					0,	//29
	L"AcDb3dPolylineVertex",			0,	//30
	L"AcDbMline",                       0,	//31
	L"AcDbPoint",                       0,	//32
	L"AcDbPolyFaceMeshVertex",		    0,	//33
	L"AcDbPolygonMeshVertex",           0,	//34
	L"AcDbBlockBegin",                  0,	//35
	L"AcDbBlockEnd",                    0,	//36
	L"AcDbFcf",                         0,	//37
	L"AcDbFrame",                       0,	//38
	L"AcDbOleFrame",					0,	//39
	L"AcDbOle2Frame",					0,	//40
	L"AcDbRasterImage",                 0,	//41
	L"AcDbZombieEntity",                0,	//42
	L"AcDbSequenceEnd",                 0,	//43
	L"AcDbAttribute",				    0,	//44
	L"AcDbTrace",                       0,	//45
	L"AcDbFaceRecord",					0,	//46
	L"AcDbViewport",                    0,	//47
	L"AcDb2LineAngularDimension",		0,	//48
	L"AcDb3PointAngularDimension",		0,	//49
	L"AcDbAlignedDimension",			0,	//50
	L"AcDbDiametricDimension",			0,	//51
	L"AcDbOrdinateDimension",			0,	//52
	L"AcDbRadialDimension",				0,  //53
	L"AcDbRotatedDimension",			0,  //54
	L"AcDbArcDimension",				0,  //55
	L"AcDbDimension",					0,  //56
	L"AcDbTable",						0,	//57
	L"AcDbWipeout",						0,	//58
	
	// DON'T import: things which I don't think make sense for importing to HOOPS
	// for example attribute definitions - they do have some visual representation
	// which we don't want to draw
	L"AcDbAttributeDefinition",			0,	//59
	L"AecDbSlab",						0,	//60

};


// Base class DWG Importer. Implements common activities viz. ACAD database traversal etc.
class HDWGImporter
{
public:
	HDWGImporter(HIOUtilityDWG* pDWGInputHandler);
	virtual ~HDWGImporter();

	// must have functions for any DWG Importers - Import DWG File or AcDbDatabase
	virtual bool importDWGFile(const wchar_t * FileName, HC_KEY modelKey, HInputHandlerOptions * pInputOptions = 0) = 0;
	virtual bool importDWGDatabase(AcDbDatabase* pAcDbDatabase, HC_KEY modelKey, HInputHandlerOptions * pInputOptions = 0) = 0;

	virtual void importAcDbMTextFragment(AcDbMTextFragment* pAcDbMTextFragment, AcDbMText* pOrigAcDbMText) = 0;

	void  extrude_profile_along_line(const int& nProfilePoints, 
									const HPoint* pStartProfilePoints,
									HPoint* pDirection, const int& nExtrudeLength) const;

	virtual Adesk::Boolean import_circle(	const AcGePoint3d& pt1, 
									const AcGePoint3d& pt2, 
									const AcGePoint3d& pt3,
									AcDbEntity* pDatabaseEntity) const = 0;

	Adesk::Boolean import_circle(	const AcGePoint3d& center,
									const double radius,
									const AcGeVector3d& normal,
									AcDbEntity* pDatabaseEntity
									) const;

	virtual Adesk::Boolean import_circular_arc(	const AcGePoint3d& center,
										const double radius,
										const AcGeVector3d& normal,
										const AcGeVector3d& startVector,
										const double sweepAngle,
										const AcGiArcType arcType,
										AcDbEntity* pDatabaseEntity
										) const = 0;

	virtual Adesk::Boolean import_circular_arc(	const AcGePoint3d& start,
										const AcGePoint3d& point,
										const AcGePoint3d& end,
										const AcGiArcType arcType,
										AcDbEntity* pDatabaseEntity
										) const = 0;

	virtual Adesk::Boolean import_polygon(	const Adesk::UInt32 nbPoints,
									const AcGePoint3d* pVertexList,
									AcDbEntity* pDatabaseEntity
									) const = 0;

	virtual Adesk::Boolean import_polyline(	const Adesk::UInt32 nbPoints,
									const AcGePoint3d* pVertexList,
									const AcGeVector3d* pNormal,
									Adesk::LongPtr lBaseSubEntMarker,
									AcDbEntity* pDatabaseEntity) const = 0;

	virtual Adesk::Boolean import_pline(const AcDbPolyline& lwBuf,
								Adesk::UInt32 fromIndex,
								Adesk::UInt32 numSegs,
								AcDbEntity* pDatabaseEntity) const = 0;

	Adesk::Boolean import_polypoint(const Adesk::UInt32 nbPoints,
									const AcGePoint3d* pVertexList,
									const AcGeVector3d* pNormal,
									const Adesk::LongPtr * pSubEntMarkers,
									AcDbEntity* pDatabaseEntity) const
	{ /*TODO: Implement this function*/ return Adesk::kFalse;};

	virtual Adesk::Boolean import_mesh(	const Adesk::UInt32 rows,
								const Adesk::UInt32 columns,
								const AcGePoint3d* pVertexList,
								const AcGiEdgeData* pEdgeData,
								const AcGiFaceData* pFaceData,
								const AcGiVertexData* pVertexData,
								const bool bAutoGenerateNormals,
								AcDbEntity* pDatabaseEntity
								) const = 0;

	virtual Adesk::Boolean import_shell(const Adesk::UInt32 nbVertex,
								const AcGePoint3d* pVertexList,
								const Adesk::UInt32 faceListSize,
								const Adesk::Int32* pFaceList,
								const AcGiEdgeData* pEdgeData,
								const AcGiFaceData* pFaceData ,
								const AcGiVertexData* pVertexData,
								const struct resbuf* pResBuf,
								const bool bAutoGenerateNormals,
								AcDbEntity* pDatabaseEntity
								) const = 0;

	virtual Adesk::Boolean import_text( const AcGePoint3d& position,
								const AcGeVector3d& normal,
								const AcGeVector3d& direction,
								const double height,
								const double width,
								const double oblique,
								const ACHAR* pMsg,
								AcDbEntity* pDatabaseEntity
								) const = 0;

	virtual Adesk::Boolean  import_text(	const AcGePoint3d& position,
									const AcGeVector3d& normal,
									const AcGeVector3d& direction,
									const ACHAR* pMsg,
									const Adesk::LongPtr length,
									const Adesk::Boolean raw,
									const AcGiTextStyle &pTextStyle,
									AcDbEntity* pDatabaseEntity
									) const=0 ;


	double get_deviation() const { return m_Deviation; }

	void set_deviation( double dev ) { m_Deviation = dev; }

	int get_num_isolines() const { return m_numIsolines; }

    void setIs2dEntity(bool val)  { m_bIs2DEntity = val;}

protected:

	void importAcDbPoint(AcDbPoint *pAcDbPoint);
	void importAcDbMText(AcDbMText* pAcDbMText);
	void importAcDbCircle(AcDbCircle* pAcDbCircle);
	void importAcDbMaterial(AcDbMaterial *pAcDbMaterial);
	
	virtual void importXdata(AcDbEntity *pEnt)=0;
	virtual void importXdata(resbuf *pBuf) = 0;
	void import_hyperlinks(AcDbEntity *pEnt);
	virtual void attachDWGHandle(AcDbEntity *pEnt)=0;

	virtual bool get_entity_rgb(AcDbEntity *pEnt, const AcDbLayerTableRecord *pLayerTableRecord, float& red, float& green, float& blue, bool& is_by_block, bool for_blk_ref=false);
	virtual void get_entity_transparency(AcDbEntity *pEnt, const AcDbLayerTableRecord *pLayerTableRecord, int &alpha_value, bool& is_by_block );
	virtual void get_entity_visibility(AcDbEntity *pEnt, const AcDbLayerTableRecord *pLayerTableRecord, bool& is_visible );
	virtual void get_entity_line_weight(AcDbEntity *pEnt, const AcDbLayerTableRecord *pLayerTableRecord, float& ret_line_weight, bool& is_by_block);

	HIOUtilityDWG* m_pDWGInputHandler;
	HIOConnectorDWG* m_pConnectivityInfo;
	HC_KEY	m_modelKey;
	wchar_t*	m_pDWGTextureDirectory;
	bool	m_bDrawWireframe;
	bool	m_bIs3D;
	double	m_Deviation;
	bool	m_bImportXData;
	bool	m_bImportWireframeForBrep;
	int		m_numIsolines;
	struct vlist_s* m_listRegAppNames;
	struct vlist_s* m_listEntityType;
	bool m_bAttachDWGHandles;
	bool m_bAmIsolidHatch;

	HInputHandlerOptions * m_pInputOptions;

	float m_wmin[3];
	float m_wmax[3];
	int m_nLine_count;
	int m_nPoint_count;
	int m_nCircle_count;
	int m_nArc_count;
	int m_nSolid_count;
	int m_nSolid3D_count;
	int m_nGroup_count;
	int m_nPloyLine_count;
	int m_nShell_count;
	int m_nText_count;
	int m_nPloygon_count;

	wchar_t const * m_fileName;
	std::map<int, wchar_t*> layer_record;
	std::map<int, wchar_t*> group_record;
	std::map<int, wchar_t*> entity_record;
	std::map<int, wchar_t*> block_ref_record;
	std::vector<AcDbObjectId> m_VpIdCount;
	int m_BlockRefIndex;
	struct vlist_s* m_listDWGLayouts;
	bool m_bImportAllLayouts;
	bool m_bCleanVpList;
	bool m_bIgnoreOffEntity;
	double m_dGlobalScaleFactor;
	bool	m_bIs2DEntity;
	bool m_bIsSHXFont;
	bool m_bDWGInsertMeshesAsShells;
	bool m_bDisableDWGDrawOrder;

};

// DWG import implementation for HIOUtilityDWG interface
class HDWG_3dgsImporter : public HDWGImporter
{
public:
	HDWG_3dgsImporter(HIOUtilityDWG* pDWGInputHandler) : HDWGImporter(pDWGInputHandler)
	{
		m_CurrentLayoutName = 0;
	};
	~HDWG_3dgsImporter(){;};

	virtual bool importDWGFile(const wchar_t * FileName, HC_KEY modelKey, HInputHandlerOptions * pInputOptions = 0);
	virtual bool importDWGDatabase(AcDbDatabase* pAcDbDatabase, HC_KEY modelKey, HInputHandlerOptions * pInputOptions = 0);

	virtual void importAcDbMTextFragment(AcDbMTextFragment* pAcDbMTextFragment, AcDbMText* pOrigAcDbMText);
	virtual void importAcDbDimension(AcDbDimension* pAcDbDimension);

	HC_KEY extrude_profile_along_line(const int& nProfilePoints, 
										const HPoint* pStartProfilePoints,
										HPoint* pDirection, const int& nExtrudeLength) const;


	Adesk::Boolean import_circle(	const AcGePoint3d& pt1, 
									const AcGePoint3d& pt2, 
									const AcGePoint3d& pt3,
									AcDbEntity* pDatabaseEntity) const;

	Adesk::Boolean import_circle(	const AcGePoint3d& center,
									const double radius,
									const AcGeVector3d& normal,
									AcDbEntity* pDatabaseEntity
									) const;

	Adesk::Boolean import_circular_arc(	const AcGePoint3d& center,
										const double radius,
										const AcGeVector3d& normal,
										const AcGeVector3d& startVector,
										const double sweepAngle,
										const AcGiArcType arcType,
										AcDbEntity* pDatabaseEntity
										) const;

	Adesk::Boolean import_circular_arc(	const AcGePoint3d& start,
										const AcGePoint3d& point,
										const AcGePoint3d& end,
										const AcGiArcType arcType,
										AcDbEntity* pDatabaseEntity
										) const;

	Adesk::Boolean import_polygon(	const Adesk::UInt32 nbPoints,
									const AcGePoint3d* pVertexList,
									AcDbEntity* pDatabaseEntity
									) const;

	Adesk::Boolean import_polyline(	const Adesk::UInt32 nbPoints,
									const AcGePoint3d* pVertexList,
									const AcGeVector3d* pNormal,
									Adesk::LongPtr lBaseSubEntMarker,
									AcDbEntity* pDatabaseEntity) const;

	Adesk::Boolean import_pline(const AcDbPolyline& lwBuf,
								Adesk::UInt32 fromIndex,
								Adesk::UInt32 numSegs,
								AcDbEntity* pDatabaseEntity) const;

	Adesk::Boolean import_polypoint(const Adesk::UInt32 nbPoints,
									const AcGePoint3d* pVertexList,
									const AcGeVector3d* pNormal,
									const Adesk::LongPtr * pSubEntMarkers,
									AcDbEntity* pDatabaseEntity) const
									{ /*TODO: Implement this function*/ return Adesk::kFalse;};

	Adesk::Boolean import_mesh(	const Adesk::UInt32 rows,
								const Adesk::UInt32 columns,
								const AcGePoint3d* pVertexList,
								const AcGiEdgeData* pEdgeData,
								const AcGiFaceData* pFaceData,
								const AcGiVertexData* pVertexData,
								const bool bAutoGenerateNormals,
								AcDbEntity* pDatabaseEntity
								) const;

	Adesk::Boolean import_shell(const Adesk::UInt32 nbVertex,
								const AcGePoint3d* pVertexList,
								const Adesk::UInt32 faceListSize,
								const Adesk::Int32* pFaceList,
								const AcGiEdgeData* pEdgeData,
								const AcGiFaceData* pFaceData ,
								const AcGiVertexData* pVertexData,
								const struct resbuf* pResBuf,
								const bool bAutoGenerateNormals,
								AcDbEntity* pDatabaseEntity
								) const;

	Adesk::Boolean import_text( const AcGePoint3d& position,
								const AcGeVector3d& normal,
								const AcGeVector3d& direction,
								const double height,
								const double width,
								const double oblique,
								const ACHAR* pMsg,
								AcDbEntity* pDatabaseEntity
								) const;

	Adesk::Boolean  import_text(	const AcGePoint3d& position,
									const AcGeVector3d& normal,
									const AcGeVector3d& direction,
									const ACHAR* pMsg,
									const Adesk::LongPtr length,
									const Adesk::Boolean raw,
									const AcGiTextStyle &pTextStyle,
									AcDbEntity* pDatabaseEntity
									) const;
	
	HC_KEY import_text(	float my_center[], 
						float my_path1[], 
						float my_norm1[], 
						wchar_t const * text,
						const char* alignment 
						) const; // deprecated 
	
	HC_KEY apply_transforms_and_insert_text(float my_center[], 
											float my_path1[], 
											float my_norm1[], 
											wchar_t const * text,
											const char* alignment 
											) const;

private:

	void importAcDbEntity(AcDbEntity* pEnt, HC_KEY parent_seg = INVALID_KEY, bool for_blk_ref=false);
	void importAcDbEntity(AcDbEntity *pEnt, const bool& draw_shaded, 
						  HC_KEY parent_seg = INVALID_KEY, bool for_blk_ref=false);

	void importAcDbBlockReference(AcDbBlockReference *pAcDbBlockReference, HC_KEY parent_seg = INVALID_KEY, int mib_col=0, int mib_row=0);
	void importAcDbMInsertBlock(AcDbMInsertBlock *pAcDbMInsertBlock,HC_KEY parent_seg);

	void importAcDbPoint(AcDbPoint *pAcDbPoint);
	void importAcDbCircle(AcDbCircle* pAcDbCircle);
	void importAcDbMaterial(AcDbMaterial *pAcDbMaterial, AcGiMapper mapper);
	void importLBGEData();
	void importAcDbLine(AcDbLine *pAcDbLine);
	void importAcDbXline(AcDbXline* pXline);
	void importAcDbRay(AcDbRay* pRay);
	void importAcDbViewport(AcDbViewport* pViewport);
	void importAcDbRasterImage(AcDbRasterImage* pEnt);
	void importAcDbMLeader(AcDbMLeader* pEnt);
	#ifdef WIN32
	void importAcDbTable(AcDbTable* pAcDbTable);
	#endif 
    void importXdata(AcDbEntity *pEnt);	
	void importBlockTableRecord(AcDbBlockTableRecord* pRecord);
	void attachDWGHandle(AcDbEntity *pEnt);

	void get_entity_material_style(AcDbEntity* pEnt, const AcDbLayerTableRecord *pLayerTableRecord, HC_KEY& style_key);

	virtual void importXdata(resbuf *pBuf);
	void import_hyperlinks(AcDbEntity *pEnt);
	void set_marker_settings(const Adesk::Int16 db_pdmode, const double db_pdsize );

	void import_entity_linetype(AcDbEntity *pEnt, const AcDbLayerTableRecord *pLayerTableRecord);
	void import_entity_linetype(const AcDbObjectId& pLinetypeId, double linetype_scale);
	void import_layout(AcDbDatabase *pAcDbDatabase);
	void update_layout_list(AcDbDatabase* pAcDbDatabase);
	void set_initial_view_for_model_space(AcDbDatabase* pAcDbDatabase);
	void InsertMaskRegion(AcDbRasterImage* pEnt);


	HC_KEY GetBlockTableRecordSegmentFromId(const AcDbObjectId& blockTableRecordID, bool& isNew);
	HC_KEY GetBlockTableRecordSegmentForEntity(AcDbEntity *pEnt);
	

	wchar_t* m_CurrentLayoutName;
	std::map<void * , HC_KEY> m_Segments_map;
	std::map<void * , HC_KEY>::const_iterator m_keymap_ieterator;

	// For progress bar
	int m_nTotalEntities;
	int m_nCurrentEntityCount;
	void GetNoOfEntitiesForProgressBar(AcDbDatabase* pAcDbDatabase);

	friend class HDrawOrderHandler;

};

class HDWG_BStreamImporter : public HDWGImporter
{
public:
	HDWG_BStreamImporter(HIOUtilityDWG* pDWGInputHandler, bool is_xref);
	~HDWG_BStreamImporter();

	///////////////
	// Bstream Toolkit 
	BStreamFileToolkit *m_pBStreamtk;
	char *m_pBStreamBuffer;
	int m_nBStreamBuffSize;
	int m_nBStreamBuffCount;
	FILE *m_pHSFFile;
	struct vhash_s * m_vhash_StyleSegName_IsPresentFlag;
	struct vhash_s * m_vhash_SegName_IsPresentFlag;
	///////////////

	virtual bool importDWGFile(const wchar_t * FileName, HC_KEY modelKey, HInputHandlerOptions * pInputOptions = 0);
	virtual bool importXRefs(AcDbDatabase* pHostDb, HC_KEY modelKey, HInputHandlerOptions * pInputOptions);
	virtual bool importDWGDatabase(AcDbDatabase* pAcDbDatabase, HC_KEY modelKey, HInputHandlerOptions * pInputOptions = 0);

	virtual void  importAcDbMTextFragment(AcDbMTextFragment* pAcDbMTextFragment, AcDbMText* pOrigAcDbMText);
	virtual void importAcDbDimension(AcDbDimension* pAcDbDimension);
	void  extrude_profile_along_line(const int& nProfilePoints, 
										const HPoint* pStartProfilePoints,
										HPoint* pDirection, const int& nExtrudeLength) const;

	Adesk::Boolean  import_circle(	const AcGePoint3d& pt1, 
		const AcGePoint3d& pt2, 
		const AcGePoint3d& pt3,
		AcDbEntity* pDatabaseEntity) const;

	Adesk::Boolean  import_circle(	const AcGePoint3d& center,
		const double radius,
		const AcGeVector3d& normal,
		AcDbEntity* pDatabaseEntity
		) const;

	Adesk::Boolean  import_circular_arc(	const AcGePoint3d& center,
		const double radius,
		const AcGeVector3d& normal,
		const AcGeVector3d& startVector,
		const double sweepAngle,
		const AcGiArcType arcType,
		AcDbEntity* pDatabaseEntity
		) const;

	Adesk::Boolean  import_circular_arc(	const AcGePoint3d& start,
		const AcGePoint3d& point,
		const AcGePoint3d& end,
		const AcGiArcType arcType,
		AcDbEntity* pDatabaseEntity
		) const;

	Adesk::Boolean import_polygon(	const Adesk::UInt32 nbPoints,
		const AcGePoint3d* pVertexList,
		AcDbEntity* pDatabaseEntity
		) const;

	Adesk::Boolean  import_polyline(	const Adesk::UInt32 nbPoints,
		const AcGePoint3d* pVertexList,
		const AcGeVector3d* pNormal,
		Adesk::LongPtr lBaseSubEntMarker,
		AcDbEntity* pDatabaseEntity) const;

	Adesk::Boolean  import_pline(const AcDbPolyline& lwBuf,
		Adesk::UInt32 fromIndex,
		Adesk::UInt32 numSegs,
		AcDbEntity* pDatabaseEntity) const;

	Adesk::Boolean import_polypoint(const Adesk::UInt32 nbPoints,
									const AcGePoint3d* pVertexList,
									const AcGeVector3d* pNormal,
									const Adesk::LongPtr * pSubEntMarkers,
									AcDbEntity* pDatabaseEntity) const
									{ /*TODO: Implement this function*/ return Adesk::kFalse;};

	Adesk::Boolean  import_mesh(	const Adesk::UInt32 rows,
		const Adesk::UInt32 columns,
		const AcGePoint3d* pVertexList,
		const AcGiEdgeData* pEdgeData,
		const AcGiFaceData* pFaceData,
		const AcGiVertexData* pVertexData,
		const bool bAutoGenerateNormals,
		AcDbEntity* pDatabaseEntity
		) const;

	Adesk::Boolean  import_shell(const Adesk::UInt32 nbVertex,
		const AcGePoint3d* pVertexList,
		const Adesk::UInt32 faceListSize,
		const Adesk::Int32* pFaceList,
		const AcGiEdgeData* pEdgeData,
		const AcGiFaceData* pFaceData ,
		const AcGiVertexData* pVertexData,
		const struct resbuf* pResBuf,
		const bool bAutoGenerateNormals,
		AcDbEntity* pDatabaseEntity
		) const;

	Adesk::Boolean  import_text( const AcGePoint3d& position,
		const AcGeVector3d& normal,
		const AcGeVector3d& direction,
		const double height,
		const double width,
		const double oblique,
		const ACHAR* pMsg,
		AcDbEntity* pDatabaseEntity
		) const;

	Adesk::Boolean  import_text(	const AcGePoint3d& position,
		const AcGeVector3d& normal,
		const AcGeVector3d& direction,
		const ACHAR* pMsg,
		const Adesk::LongPtr length,
		const Adesk::Boolean raw,
		const AcGiTextStyle &pTextStyle,
		AcDbEntity* pDatabaseEntity
		) const;

	HC_KEY apply_transforms_and_insert_text(float my_center[], 
											float my_path1[], 
											float my_norm1[], 
											wchar_t const * text,
											const int alignment) const;

	inline BOOL	GetConnectivityCompression()			{ return bConnectivityCompression; };
	inline void	SetConnectivityCompression(BOOL val)			{ bConnectivityCompression = val; }
	inline BOOL	GetVertexCompression()			{ return bVertexCompression; }
	inline void	SetVertexCompression(BOOL val)			{ bVertexCompression = val; }
	inline BOOL	GetNormalCompression()			{ return bNormalCompression; }
	inline void	SetNormalCompression(BOOL val)			{ bNormalCompression = val; }
	inline BOOL	GetImageCompression()			{ return bImageCompression; }
	inline void	SetImageCompression(BOOL val)			{ bImageCompression = val; }
	inline int	GetVertexCompressionBits()			{ return m_VertexCompressionBits; }
	inline void	SetVertexCompressionBits(int val)			{ m_VertexCompressionBits = val; }
	inline int	GetNormalCompressionBits()			{ return m_NormalCompressionBits; }
	inline void	SetNormalCompressionBits(int val)			{ m_NormalCompressionBits = val; }
	inline int	GetImageCompressionValue()			{ return m_ImageCompressionValue; }
	inline void	SetImageCompressionValue(int val)			{ m_ImageCompressionValue = val; }


protected:

	void  importAcDbEntity(AcDbEntity* pEnt, TK_Open_Segment* parent_seg = NULL, bool for_blk_ref=false);
	void  importAcDbEntity(AcDbEntity *pEnt, const bool& draw_shaded, 
						   TK_Open_Segment* parent_seg = NULL, bool for_blk_ref=false);


	void  importBlockTable(AcDbBlockTable* pBlockTable);
	void importAcDbMInsertBlock(AcDbMInsertBlock *pAcDbMInsertBlock,TK_Open_Segment * Open_seg_handler);
	//void  importAcDbBlockReference(AcDbBlockReference *pAcDbBlockReference, HC_KEY parent_seg = INVALID_KEY);
	void  importAcDbBlockReference(AcDbBlockReference *pAcDbBlockReference, TK_Open_Segment* Open_seg_handler = NULL,
															int mib_col = 0 , int mib_row = 0);

	void importAcDbPoint(AcDbPoint *pAcDbPoint);
	void  importAcDbCircle(AcDbCircle* pAcDbCircle);
	void  importAcDbMaterial(AcDbMaterial *pAcDbMaterial, AcGiMapper mapper);
	void importLBGEData();
	void importAcDbLine(AcDbLine *pAcDbLine);
	void importAcDbXline(AcDbXline* pXline);
	void importAcDbRay(AcDbRay* pRay);
	void importBlockTableRecord(AcDbBlockTableRecord* pRecord);
	void importAcDbViewport(AcDbViewport* pViewport);
	void importAcDbRasterImage(AcDbRasterImage* pEnt);
	void importAcDbMLeader(AcDbMLeader* pEnt);
	#ifdef WIN32
	void importAcDbTable(AcDbTable* pAcDbTable);
	#endif 

	void importXdata(AcDbEntity *pEnt);
	void attachDWGHandle(AcDbEntity *pEnt);
	void  get_entity_material_style(AcDbEntity* pEnt, const AcDbLayerTableRecord *pLayerTableRecord, TK_Open_Segment* &parent_seg);
	TK_Open_Segment*  GetBlockTableRecordSegmentFromId(const AcDbObjectId& blockTableRecordID, bool& isNew);
	TK_Open_Segment*  GetBlockTableRecordSegmentForEntity(AcDbEntity *pEnt);

	//void bstream_CreateWireframeCircleWithEllipse(const HPoint &x1, const HPoint &x2, const HPoint &x3 );

	virtual void importXdata(resbuf *pBuf);
	void  import_hyperlinks(AcDbEntity *pEnt);
	void set_marker_settings(const Adesk::Int16 db_pdmode,const double db_pdsize );
	void import_entity_linetype(AcDbEntity *pEnt, const AcDbLayerTableRecord *pLayerTableRecord);
	void import_entity_linetype(const AcDbObjectId& pLinetypeId, double linetype_scale);
	void InsertMaskRegion(AcDbRasterImage* pEnt);
	void import_layout(AcDbDatabase *pAcDbDatabase);
	void update_layout_list(AcDbDatabase* pAcDbDatabase);
	void set_initial_view_for_model_space(AcDbDatabase* pAcDbDatabase);

	BOOL bConnectivityCompression;
	BOOL bVertexCompression;
	BOOL bNormalCompression;
	BOOL bImageCompression;
	int m_VertexCompressionBits;
	int m_NormalCompressionBits;
	int m_ImageCompressionValue;
	bool m_bMergeEntityShells;
	time_t	m_mtImportStart;
	wchar_t * m_pFileName;
	bool	m_bAmIXref;
	bool m_bScratchSegOpen;
	wchar_t *m_pXref_hsf_path;
	mutable bool m_bShellWithFaceColor;

	
	private:
	// small fuctions for opening/ closing segments, visibility, heuristics, 
	// unicode/user opts settings, etc.
    // Functions to reduce code size - perform TK operations
    int STREAM_Open_Segment(TK_Open_Segment* open_seg_handler, const char * segname) const;
	int STREAM_Open_Segment(const char * segname) const;
	int STREAM_Close_Segment() const;
	int STREAM_Set_Visibility(TKO_Geometry_Bits Geom_Bit, bool ifOn) const;
	int STREAM_Set_Heuristics(TKO_Heuristic_Bits Heuristic_Bit) const;
	int STREAM_Write_Object(BBaseOpcodeHandler * handler) const;
	static struct _stat m_MasterHsfFileTime;

	std::map<void * , const char *> m_Segments_map;
	std::map<void * ,const char *>::const_iterator m_iterator_segmap;

	friend class HDrawOrderHandler;
};

// Custom worldDraw object is sent in a call to the 
// entitiy's worldDraw function.  The entity will then
// end up calling the worldGeometry class's shell function.
// In this case, the HAcGiWorldGeometry's shell member
// function will be called.
class HAcGiWorldDraw : public AcGiWorldDraw 
{
public:

    ACRX_DECLARE_MEMBERS(HAcGiWorldDraw);

	HAcGiWorldDraw(HDWGImporter* pDWGImporter, AcDbEntity* pAcDbEntity);
	virtual ~HAcGiWorldDraw();

    virtual AcGiRegenType           regenType() const;
    virtual Adesk::Boolean          regenAbort() const;
    virtual AcGiSubEntityTraits&    subEntityTraits() const;
	virtual AcGiGeometry *			rawGeometry() const;
    virtual AcGiWorldGeometry&      geometry() const;
    virtual Adesk::Boolean          isDragging() const;
    virtual double                  deviation(const AcGiDeviationType, const AcGePoint3d&) const;
    virtual Adesk::UInt32           numberOfIsolines() const;	
	virtual AcGiContext *			context();

	void					        setDeviation(double);
	void							setRegenType(const AcGiRegenType&);

	HDWGImporter*					GetHDWGImporter() const;
	AcDbEntity*						GetCurrentEntity() const;

private:

	AcGiSubEntityTraits*	mpSubEntityTraits;
	AcGiWorldGeometry*		mpWorldGeometry;
	AcGiContext*			mpContext;
	AcGiRegenType			mRegenType;

	HDWGImporter*			m_pDWGImporter;
	AcDbEntity*				m_pAcDbEntity;
};

// AcGiContext abstracts out the commonality between 
// AcGiViewportDraw and AcGiWorldDraw. This allows you 
// to code graphics routines in terms of AcGiContext that 
// will work in either case. To maintain their original signatures,
// AcGiWorldDraw and AcGiViewportDraw now derive from AcGiContext.
// Only the database member function is implemented.  
class HAcGiContext : public AcGiContext
{
public:

	ACRX_DECLARE_MEMBERS(HAcGiContext);
	HAcGiContext();
	virtual ~HAcGiContext();

	Adesk::Boolean          isPsOut() const;
    Adesk::Boolean          isPlotGeneration() const;
    AcDbDatabase *          database() const;
    bool					isBoundaryClipping() const;

};

// This class contains the view independent, model coordinate,
// 3D geometry methods for our custom world geometry class. 
class HAcGiWorldGeometry: public AcGiWorldGeometry 
{ 
public:

    ACRX_DECLARE_MEMBERS(HAcGiWorldGeometry);

	HAcGiWorldGeometry(HAcGiWorldDraw* pWorldDraw);
	~HAcGiWorldGeometry();

	virtual Adesk::Boolean  draw(AcGiDrawable*) const;

    virtual Adesk::Boolean  circle	(const AcGePoint3d& center,
									const double radius,
									const AcGeVector3d& normal
									) const;

    virtual Adesk::Boolean  circle (const AcGePoint3d& pt1,
									const AcGePoint3d& pt2,
									const AcGePoint3d& pt3
									) const;

    virtual Adesk::Boolean  circularArc(const AcGePoint3d& center,
										const double radius,
										const AcGeVector3d& normal,
										const AcGeVector3d& startVector,
										const double sweepAngle,
										const AcGiArcType arcType = kAcGiArcSimple
										) const;

    virtual Adesk::Boolean  circularArc(const AcGePoint3d& start,
										const AcGePoint3d& point,
										const AcGePoint3d& end,
										const AcGiArcType arcType = kAcGiArcSimple
										) const;
      
    virtual Adesk::Boolean  polyline	(const Adesk::UInt32 nbPoints,
										const AcGePoint3d* pVertexList,
										const AcGeVector3d* pNormal = NULL,
										Adesk::LongPtr lBaseSubEntMarker = -1) const;

	virtual Adesk::Boolean  polyline(const AcGiPolyline& polylineObj) const ;

	virtual  Adesk::Boolean  polyPolyline (Adesk::UInt32 nbPolylines,
											  const AcGiPolyline* pPolylines) const;			
	virtual  Adesk::Boolean  polyPolygon(const Adesk::UInt32 numPolygonIndices,
										const Adesk::UInt32* numPolygonPositions,
										const AcGePoint3d* polygonPositions,
										const Adesk::UInt32* numPolygonPoints,
										const AcGePoint3d* polygonPoints,
										const AcCmEntityColor* outlineColors = NULL,
										const AcGiLineType* outlineTypes = NULL,
										const AcCmEntityColor* fillColors = NULL,
										const AcCmTransparency* fillOpacities = NULL) const ;
	virtual  Adesk::Boolean  image(const AcGiImageBGRA32& imageSource,
									  const AcGePoint3d& position,
									  const AcGeVector3d& u, //orientation and magnitude of width
									  const AcGeVector3d& v, //orientation and magnitude of height
									  TransparencyMode transparencyMode
									  ) const ;
	virtual  Adesk::Boolean  rowOfDots(int count,
							  const AcGePoint3d&     start,
							  const AcGeVector3d&     step
							 ) const ;
	virtual  Adesk::Boolean  ellipticalArc(const AcGePoint3d&         center,
									  const AcGeVector3d&        normal,
									  double                     majorAxisLength,
									  double                     minorAxisLength,
									  double                     startDegreeInRads,
									  double                     endDegreeInRads,
									  double                     tiltDegreeInRads,
									  AcGiArcType                arcType
									  ) const ;

	virtual Adesk::Boolean polypoint(const Adesk::UInt32 nbPoints,
									   const AcGePoint3d* pVertexList,
									   const AcGeVector3d* pNormal = NULL,
									   const Adesk::LongPtr * pSubEntMarkers = NULL) const;

    virtual Adesk::Boolean  polygon(const Adesk::UInt32 nbPoints,
									const AcGePoint3d* pVertexList
									) const;

    virtual Adesk::Boolean  mesh   (const Adesk::UInt32 rows,
									const Adesk::UInt32 columns,
									const AcGePoint3d* pVertexList,
									const AcGiEdgeData* pEdgeData = NULL,
									const AcGiFaceData* pFaceData = NULL,
									const AcGiVertexData* pVertexData = NULL,
									const bool bAutoGenerateNormals = true
									) const;

    virtual Adesk::Boolean  shell(const Adesk::UInt32 nbVertex,
                                 const AcGePoint3d* pVertexList,
                                 const Adesk::UInt32 faceListSize,
                                 const Adesk::Int32* pFaceList,
                                 const AcGiEdgeData* pEdgeData = NULL,
                                 const AcGiFaceData* pFaceData = NULL,
                                 const AcGiVertexData* pVertexData = NULL,
                                 const struct resbuf* pResBuf = NULL,
								 const bool bAutoGenerateNormals = true
                                 ) const;
	
      
    virtual Adesk::Boolean  text	(const AcGePoint3d& position,
									const AcGeVector3d& normal,
									const AcGeVector3d& direction,
									const double height,
									const double width,
									const double oblique,
									const ACHAR* pMsg
									) const;

    virtual Adesk::Boolean  text(const AcGePoint3d& position,
								const AcGeVector3d& normal,
								const AcGeVector3d& direction,
								const ACHAR* pMsg,
								const Adesk::Int32 length,
								const Adesk::Boolean raw,
								const AcGiTextStyle &pTextStyle
								) const;
	  

    virtual Adesk::Boolean  xline  (const AcGePoint3d& one_xline_point,
									const AcGePoint3d& a_different_xline_point
									) const;

    virtual Adesk::Boolean  ray(const AcGePoint3d& rays_starting_point,
								const AcGePoint3d& a_different_ray_point
								) const;

    virtual Adesk::Boolean  pline(const AcDbPolyline& lwBuf,
                                  Adesk::UInt32 fromIndex = 0,
                                  Adesk::UInt32 numSegs = 0
                                  ) const;

	virtual void getModelToWorldTransform(AcGeMatrix3d &pMatrix) const;
	virtual void getWorldToModelTransform(AcGeMatrix3d &pMatrix) const;
	virtual void setExtents(AcGePoint3d *pNewExtents) const;

	virtual Adesk::Boolean pushModelTransform(const AcGeVector3d & vNormal);// Uses arbitrary Axis algorythm
	virtual Adesk::Boolean pushModelTransform(const AcGeMatrix3d & xMat);
	virtual Adesk::Boolean popModelTransform();

    virtual Adesk::Boolean  pushClipBoundary(AcGiClipBoundary * pBoundary);
    virtual void			popClipBoundary();
	virtual AcGeMatrix3d pushPositionTransform (AcGiPositionTransformBehavior behavior, const AcGePoint3d& offset); 
    virtual AcGeMatrix3d pushPositionTransform (AcGiPositionTransformBehavior behavior, const AcGePoint2d& offset); 
    virtual AcGeMatrix3d pushScaleTransform (AcGiScaleTransformBehavior behavior, const AcGePoint3d& extents);
    virtual AcGeMatrix3d pushScaleTransform (AcGiScaleTransformBehavior behavior, const AcGePoint2d& extents);
    virtual AcGeMatrix3d pushOrientationTransform (AcGiOrientationTransformBehavior behavior);

private:

	// Back pointer stored to the WorldDraw object.  This class
	// uses it to store the ShellData when the shell member
	// function is called.
	HAcGiWorldDraw*	m_pHAcGiWorldDraw;
};


// This class applies attributes to subsequently drawn AcGi geometry
// primitives.
class HAcGiSubEntityTraits: public AcGiSubEntityTraits 
{ 
public:

    ACRX_DECLARE_MEMBERS(HAcGiSubEntityTraits);

	HAcGiSubEntityTraits();
	~HAcGiSubEntityTraits();

    virtual void setColor(const Adesk::UInt16 color);
    virtual void setTrueColor(const AcCmEntityColor& color);
    virtual void setLayer(const AcDbObjectId layerId);
    virtual void setLineType(const AcDbObjectId linetypeId);
    virtual void setSelectionMarker(const Adesk::LongPtr markerId);
    virtual void setFillType(const AcGiFillType fillType);
    virtual void setLineWeight(const AcDb::LineWeight lw);
    virtual void setLineTypeScale(double dScale = 1.0);


    virtual Adesk::UInt16       color() const;
	virtual AcCmEntityColor		trueColor() const;
    virtual AcDbObjectId        layerId() const;
    virtual AcDbObjectId        lineTypeId() const;
    virtual AcGiFillType        fillType() const;
    virtual AcDb::LineWeight    lineWeight() const;
    virtual double				lineTypeScale() const;

    virtual void   setThickness(double dThickness);
    virtual double thickness() const;

private:

	Adesk::UInt16	mColorIndex;
	AcCmEntityColor mTrueColor;
	AcDbObjectId	mLayerId;
	AcDbObjectId	mLinetypeId;
	Adesk::LongPtr	mMarkerId;
	AcGiFillType	mFillType;	
	AcDb::LineWeight  mLineWeight;
	double			mLineTypeScale;
	double			mThickness;
};

// Some entities (particularly custom entities from AEC etc.) are viewport entities 
// They don't have any visual reprentation in world (worldDraw fails), but they 
// have a specific representation in viewport. Hence we are deriving from ViewportDraw
//  --- SK 17 mar 09

class HAcGiViewportDraw : public AcGiViewportDraw
{
public:
	ACRX_DECLARE_MEMBERS(HAcGiViewportDraw);
	HAcGiViewportDraw(HDWGImporter* pDWGImporter, AcDbEntity* pAcDbEntity);
	~HAcGiViewportDraw();
	
    virtual AcGiViewport&        viewport() const;
    virtual AcGiViewportGeometry& geometry() const;
    virtual Adesk::UInt32        sequenceNumber() const;
    virtual Adesk::Boolean       isValidId(const Adesk::ULongPtr acgiId) const;
    virtual AcDbObjectId         viewportObjectId() const;

	virtual AcGiRegenType           regenType() const ;
	virtual Adesk::Boolean          regenAbort() const {return Adesk::kFalse;};
    virtual AcGiSubEntityTraits&    subEntityTraits() const ;
    virtual AcGiGeometry *   rawGeometry() const ;
    virtual Adesk::Boolean          isDragging() const {return Adesk::kFalse;};

    // This function operates against the current active viewport
    //
    virtual double                deviation(const AcGiDeviationType, const AcGePoint3d&) const {return 0.00;};
	virtual Adesk::UInt32           numberOfIsolines() const {return 0;};
    
    virtual AcGiContext *      context();

	HDWGImporter*					GetHDWGImporter() const;
	AcDbEntity*						GetCurrentEntity() const;

private:
	AcGiViewport* mpVp;
	AcGiViewportGeometry* mpVpGeometry;
	AcDbObjectId mpObjId;

	AcGiSubEntityTraits*	mpSubEntityTraits;
	AcGiContext*			mpContext;
	AcGiRegenType			mRegenType;

	HDWGImporter*			m_pDWGImporter;
	AcDbEntity*				m_pAcDbEntity;

};

class HAcGiViewportGeometry : public AcGiViewportGeometry
{
public:
	 ACRX_DECLARE_MEMBERS(HAcGiViewportGeometry);
	 HAcGiViewportGeometry(HAcGiViewportDraw* pViewportDraw);
	 ~HAcGiViewportGeometry();
    virtual Adesk::Boolean  polylineEye(const Adesk::UInt32 nbPoints,
                                const AcGePoint3d* pPoints) const ;
    virtual Adesk::Boolean  polygonEye(const Adesk::UInt32 nbPoints,
                                const AcGePoint3d* pPoints) const ;

    virtual Adesk::Boolean  polylineDc(const Adesk::UInt32 nbPoints,
                                const AcGePoint3d* pPoints) const;
    virtual Adesk::Boolean  polygonDc(const Adesk::UInt32 nbPoints,
                                const AcGePoint3d* pPoints) const ;


    virtual Adesk::Boolean  rasterImageDc(
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
				) const;

    virtual Adesk::Boolean  ownerDrawDc(
                long                       vpnumber, 
                long                       left, 
                long                       top, 
                long                       right, 
                long                       bottom, 
                const OwnerDraw*           pOwnerDraw
                ) const;

    virtual Adesk::Boolean  ownerDraw3d(
                AcGePoint3d&               minBounds,
                AcGePoint3d&               maxBounds,
                OwnerDraw3d*               pOwnerDraw
                ) const  ;


    // Coordinate transformations.
    //
	virtual void getModelToWorldTransform(AcGeMatrix3d&) const ;
    virtual void getWorldToModelTransform(AcGeMatrix3d&) const ;

	virtual Adesk::Boolean pushModelTransform(const AcGeVector3d & vNormal) ;// Uses arbitrary Axis algorythm
    virtual Adesk::Boolean pushModelTransform(const AcGeMatrix3d & xMat) ;
    virtual Adesk::Boolean popModelTransform() ;

	virtual AcGeMatrix3d pushPositionTransform (AcGiPositionTransformBehavior behavior, const AcGePoint3d& offset); 
    virtual AcGeMatrix3d pushPositionTransform (AcGiPositionTransformBehavior behavior, const AcGePoint2d& offset); 
    virtual AcGeMatrix3d pushScaleTransform (AcGiScaleTransformBehavior behavior, const AcGePoint3d& extents);
    virtual AcGeMatrix3d pushScaleTransform (AcGiScaleTransformBehavior behavior, const AcGePoint2d& extents);
    virtual AcGeMatrix3d pushOrientationTransform (AcGiOrientationTransformBehavior behavior);
	

    // For drawing various primitives.
    //
    virtual Adesk::Boolean  circle(const AcGePoint3d& center,
                                   const double radius,
                                   const AcGeVector3d& normal) const ;

    virtual Adesk::Boolean  circle(const AcGePoint3d&, const AcGePoint3d&,
                                   const AcGePoint3d&) const ;

    virtual Adesk::Boolean  circularArc(const AcGePoint3d& center,
                                   const double radius,
                                   const AcGeVector3d& normal,
                                   const AcGeVector3d& startVector,
                                   const double sweepAngle,
                                   const AcGiArcType arcType = kAcGiArcSimple) const ;

    virtual Adesk::Boolean  circularArc(const AcGePoint3d& start,
                                   const AcGePoint3d& point,
                                   const AcGePoint3d& end,
                                   const AcGiArcType arcType = kAcGiArcSimple) const ;
      
    virtual Adesk::Boolean  polyline(const Adesk::UInt32 nbPoints,
                                   const AcGePoint3d* pVertexList,
                                   const AcGeVector3d* pNormal = NULL,
                                   Adesk::LongPtr lBaseSubEntMarker = -1) const ;
      
	virtual Adesk::Boolean  polyline(const AcGiPolyline& polylineObj) const {return Adesk::kTrue;}

    virtual Adesk::Boolean  polyPolyline (Adesk::UInt32 nbPolylines,
                                          const AcGiPolyline* pPolylines) const {return Adesk::kTrue;}
	virtual Adesk::Boolean  polyPolygon(const Adesk::UInt32 numPolygonIndices,
									const Adesk::UInt32* numPolygonPositions,
									const AcGePoint3d* polygonPositions,
									const Adesk::UInt32* numPolygonPoints,
									const AcGePoint3d* polygonPoints,
									const AcCmEntityColor* outlineColors = NULL,
									const AcGiLineType* outlineTypes = NULL,
									const AcCmEntityColor* fillColors = NULL,
									const AcCmTransparency* fillOpacities = NULL) const {return Adesk::kTrue;}
	virtual Adesk::Boolean  image(const AcGiImageBGRA32& imageSource,
						  const AcGePoint3d& position,
						  const AcGeVector3d& u, //orientation and magnitude of width
						  const AcGeVector3d& v, //orientation and magnitude of height
						  TransparencyMode transparencyMode = kTransparency8Bit
						  ) const {return Adesk::kTrue;}
	virtual Adesk::Boolean  rowOfDots(int count,
								  const AcGePoint3d&     start,
								  const AcGeVector3d&     step
								 ) const {return Adesk::kTrue;}
    virtual Adesk::Boolean  ellipticalArc(const AcGePoint3d&         center,
                                      const AcGeVector3d&        normal,
                                      double                     majorAxisLength,
                                      double                     minorAxisLength,
                                      double                     startDegreeInRads,
                                      double                     endDegreeInRads,
                                      double                     tiltDegreeInRads,
                                      AcGiArcType                arcType = kAcGiArcSimple
                                      ) const {return Adesk::kTrue;}
      
    virtual Adesk::Boolean  polygon(const Adesk::UInt32 nbPoints,
                                   const AcGePoint3d* pVertexList) const ;

    virtual Adesk::Boolean  mesh(const Adesk::UInt32 rows,
                                 const Adesk::UInt32 columns,
                                 const AcGePoint3d* pVertexList,
                                 const AcGiEdgeData* pEdgeData = NULL,
                                 const AcGiFaceData* pFaceData = NULL,
                                 const AcGiVertexData* pVertexData = NULL,
                                 const bool bAutoGenerateNormals = true
                                 ) const ;

    virtual Adesk::Boolean  shell(const Adesk::UInt32 nbVertex,
                                 const AcGePoint3d* pVertexList,
                                 const Adesk::UInt32 faceListSize,
                                 const Adesk::Int32* pFaceList,
                                 const AcGiEdgeData* pEdgeData = NULL,
                                 const AcGiFaceData* pFaceData = NULL,
                                 const AcGiVertexData* pVertexData = NULL,
                                 const struct resbuf* pResBuf = NULL,
                                 const bool bAutoGenerateNormals = true
                                 ) const ;
      
    virtual Adesk::Boolean  text(const AcGePoint3d& position,
                                 const AcGeVector3d& normal,
                                 const AcGeVector3d& direction,
                                 const double height,
                                 const double width,
                                 const double oblique,
                                 const ACHAR* pMsg) const ;

    virtual Adesk::Boolean  text(const AcGePoint3d& position,
                                 const AcGeVector3d& normal,
                                 const AcGeVector3d& direction,
                                 const ACHAR* pMsg,
                                 const Adesk::Int32 length,
                                 const Adesk::Boolean raw,
                                 const AcGiTextStyle &pTextStyle
                                 ) const ;

    virtual Adesk::Boolean  xline(const AcGePoint3d&,
                                  const AcGePoint3d&) const ;

    virtual Adesk::Boolean  ray(const AcGePoint3d&,
                                const AcGePoint3d&) const ;

    virtual Adesk::Boolean  pline(const AcDbPolyline& lwBuf,
                                  Adesk::UInt32 fromIndex = 0,
                                  Adesk::UInt32 numSegs = 0
                                  ) const ;

    virtual Adesk::Boolean  draw(AcGiDrawable*) const ;

    virtual Adesk::Boolean          pushClipBoundary(AcGiClipBoundary * pBoundary);
	virtual void                    popClipBoundary() ;

private:
	// Back pointer stored to the ViewPortDraw object.  This class
	// uses it to store the ShellData when the shell member
	// function is called. ---- SK 18 mar 09
	HAcGiViewportDraw* m_pHAcgiViewportDraw;

};
class HAcGiViewport : public AcGiViewport
{
	public:
    ACRX_DECLARE_MEMBERS(AcGiViewport);
	HAcGiViewport();
	~HAcGiViewport();

	virtual void getModelToEyeTransform(AcGeMatrix3d&) const ;
    virtual void getEyeToModelTransform(AcGeMatrix3d&) const ;
    virtual void getWorldToEyeTransform(AcGeMatrix3d&) const ;
    virtual void getEyeToWorldTransform(AcGeMatrix3d&) const ;

    virtual Adesk::Boolean isPerspective() const ;
    virtual Adesk::Boolean doPerspective(AcGePoint3d&) const ;
    virtual Adesk::Boolean doInversePerspective(AcGePoint3d&) const ;

     virtual void getNumPixelsInUnitSquare(const AcGePoint3d& givenWorldpt,
                                  AcGePoint2d& pixelArea,
                                  bool includePerspective = true) const ;

    virtual void getCameraLocation(AcGePoint3d& location) const ;
    virtual void getCameraTarget(AcGePoint3d& target) const ;
    virtual void getCameraUpVector(AcGeVector3d& upVector) const ;

     virtual Adesk::ULongPtr viewportId() const ;
    virtual Adesk::Int16  acadWindowId() const ;
    virtual void getViewportDcCorners(AcGePoint2d& lower_left,
                                      AcGePoint2d& upper_right) const ;

    virtual Adesk::Boolean getFrontAndBackClipValues(Adesk::Boolean& clip_front,
                                         Adesk::Boolean& clip_back,
                                         double& front,
                                         double& back) const ;
    virtual double linetypeScaleMultiplier() const ;
    virtual double linetypeGenerationCriteria() const ;
};

class HDrawOrderHandler
{
public:
	HDrawOrderHandler(AcDbBlockTableRecord * pRecord, bool isblockref = false)
	{
		m_pRecord = pRecord;
		m_pObj = NULL;
		m_bIsblockRef = isblockref;
	};
	int Open();
	int GetDrawOrder(AcDbEntity *pEnt);
	int CheckDrawOrderAndSetVisibility(AcDbEntity *pEnt, HC_KEY block_key, HDWG_3dgsImporter * importer);
	int CheckDrawOrderAndSetVisibility(AcDbEntity *pEnt, TK_Open_Segment * include_seg_handler, HDWG_BStreamImporter * importer);
	void Close();
protected:
	bool m_bIsblockRef;
	AcDbBlockTableRecord * m_pRecord;
	AcDbSortentsTable* m_pObj;
	AcDbObjectIdArray objArray;


};

wchar_t * h_dwg_wcsdup(wchar_t const * const wcs);

// Inline functions for HDWG_BStreamImporter calling opcodehandlers
inline int HDWG_BStreamImporter::STREAM_Open_Segment(TK_Open_Segment* open_seg_handler, const char * seg_name) const
{
    // Caller have to delete open_seg_handler, in this version.
    open_seg_handler->SetSegment(seg_name);
    TK_Status hdwg_status = WriteObject(open_seg_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
    H_ASSERT(hdwg_status == TK_Normal);
    return 1;
}

inline int HDWG_BStreamImporter::STREAM_Open_Segment(const char * seg_name) const
{
    // Caller don't have to delete open_seg_handler, in this version.
    TK_Open_Segment* open_seg_handler = new TK_Open_Segment;
    open_seg_handler->SetSegment(seg_name);
    TK_Status hdwg_status = WriteObject(open_seg_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
    H_ASSERT(hdwg_status == TK_Normal);
    delete open_seg_handler;

    return 1;
}

inline int HDWG_BStreamImporter:: STREAM_Close_Segment() const
{
    TK_Close_Segment *close_seg_handler = new TK_Close_Segment;
    TK_Status hdwg_status = WriteObject(close_seg_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
    H_ASSERT(hdwg_status == TK_Normal);
    delete close_seg_handler;

    return 1;
}

inline int HDWG_BStreamImporter:: STREAM_Set_Visibility(TKO_Geometry_Bits Geom_Bit, bool ifOn) const
{
    //HC_Set_Visibility("off");
	TK_Visibility	*vis_handler = new TK_Visibility();
	vis_handler->SetGeometry(Geom_Bit);
	if(ifOn)
		vis_handler->SetValue(1);
	else
		vis_handler->SetValue(0);
	TK_Status hdwg_status = WriteObject(vis_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
	H_ASSERT(hdwg_status == TK_Normal);
	delete vis_handler;

    return 1;
}

inline int HDWG_BStreamImporter:: STREAM_Set_Heuristics(TKO_Heuristic_Bits Heuristic_Bit) const
{
	//HC_Set_Heuristics("xxxx");
	TK_Heuristics* heuristic_handler = new TK_Heuristics;
	heuristic_handler->SetMask( Heuristic_Bit);
	heuristic_handler->SetValue( Heuristic_Bit);
	TK_Status hdwg_status = WriteObject(heuristic_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
	H_ASSERT(hdwg_status == TK_Normal);
	delete heuristic_handler;

    return 1;
}
inline int HDWG_BStreamImporter:: STREAM_Write_Object(BBaseOpcodeHandler * handler) const
{
	TK_Status  hdwg_status = WriteObject(handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
	H_ASSERT(hdwg_status == TK_Normal);
	delete handler;

	return 1;
}

#ifdef H_PACK_8
#pragma pack(pop)
#endif

#endif


