//
// Copyright (c) 2005 by Tech Soft 3D, LLC.
// The information contained herein is confidential and proprietary to
// Tech Soft 3D, LLC., and considered a trade secret as defined under
// civil and criminal statutes.  Tech Soft 3D shall pursue its civil
// and criminal remedies in the event of unauthorized use or misappropriation
// of its trade secrets.  Use of this information by anyone other than
// authorized employees of Tech Soft 3D, LLC. is granted only under a
// written non-disclosure agreement, expressly prescribing the scope and
// manner of such use.
//
//

//ODA issues:
// 1)7336 : Regarding dimension support

#include <tchar.h>

#include "HDGNHelper.h"

//Hoops includes
#include "hc.h"
#include "HTools.h"
#include "HGlobals.h"
#include "HUtility.h"


OdStaticRxObject< HOdExDgnSystemServices > g_HIO_OdExDgnSystemServices ;
ODRX_NO_CONS_DEFINE_MEMBERS( hRxObject, OdRxObject )

OdSmartPtr< HDGNImporter > g_obHDGNImporter;
//Global Constants 
const double H_PI = 3.1415927;
const double LARGEVAL = 1.7E+308 ;



//Definations of static variables of HDGNImporter class
bool HDGNImporter::m_bIgnoreOffEntities = false;
bool HDGNImporter::m_bDGNImportAllModels = true;
char  HDGNImporter::m_cCurrDir[1024] = "\0";
double HDGNImporter::m_coneFactor = 1.0;
int HDGNImporter::m_totalEntities = 0;
HInputHandler* HDGNImporter::m_inputHandler = 0;
bool HDGNImporter::m_bDGNRebaselineModel = true;
VHash<HC_KEY,int> * HDGNImporter::m_hashGeomCellID = 0;
double HDGNImporter::m_dMinX = LARGEVAL ;
double HDGNImporter::m_dMinY = LARGEVAL ;
double HDGNImporter::m_dMinZ = LARGEVAL ;
bool HDGNImporter::m_bNoOffset = false;
OdDgDatabasePtr HDGNImporter::pDb ;
OdSmartPtr< XRef > HDGNImporter::m_obXRef;
bool HDGNImporter::m_bFromSmartSolid = false;
char HDGNImporter::m_cCellHeaderName[1024] = "\0";
bool HDGNImporter::m_bFromCellHeader = false;
bool HDGNImporter::m_bisFromEntity = false;
VHash<int,char*> HDGNImporter::m_hashLevelIDName = 0;
int HDGNImporter::m_iCellHeaderId = 0;
bool HDGNImporter::m_bCellHeaderHoleFlag = false;
bool HDGNImporter::m_bWorldDrawEntityFlag = false ;
HC_KEY HDGNImporter::m_hkShellKey = INVALID_KEY;
HC_KEY HDGNImporter::m_hkSolidSegKey = INVALID_KEY;
HC_KEY HDGNImporter::m_hkHoleSegKey = INVALID_KEY;
HC_KEY HDGNImporter::m_hkSegTobeUsed = INVALID_KEY;
int HDGNImporter::m_iCellHeaderOption = SINGLE_ENTITY_CELLHEADER;


//Defination of static variables of Cone class
double Cone::m_dDeviationForCone = 1;


//vinit globals
VList<VList<TreeNode*> *> m_vlistOfColumnVlist;
VList<TreeNode*> m_VlistLeafNode;
TreeNode *masterFileNode;
VList<TreeNode*> m_VlistDiscardedXref;

bool trace_tree(TreeNode *);
bool Calculate_Leaf_Count(TreeNode *);
void Create_VHash_Array();
bool Create_Discarded_Xref_List(VList<TreeNode*> pVlistXref);

OdDgImporter::OdDgImporter()
{
	OdDgDatabase::desc()->addX( hRxObject::desc(), &m_databaseimporter );
	OdDgModel::desc()->addX( hRxObject::desc(), &m_modelimporter );
	OdDgCellHeader2d::desc()->addX( hRxObject::desc(), &m_cellHeader2dimporter );
	OdDgCellHeader3d::desc()->addX( hRxObject::desc(), &m_cellHeader3dimporter );
	OdDgSolid::desc()->addX( hRxObject::desc(), &m_solidimporter );
	OdDgSurface::desc()->addX( hRxObject::desc(), &m_surfaceimporter );
	OdDgCone::desc()->addX( hRxObject::desc(), &m_coneimporter );
	OdDgLine2d::desc()->addX( hRxObject::desc(), &m_line2dimporter );
	OdDgLine3d::desc()->addX( hRxObject::desc(), &m_line3dimporter );
	OdDgLineString2d::desc()->addX( hRxObject::desc(), &m_lineString2dimporter );
	OdDgLineString3d::desc()->addX( hRxObject::desc(), &m_lineString3dimporter );
	OdDgShape2d::desc()->addX( hRxObject::desc(), &m_shape2dimporter );
	OdDgShape3d::desc()->addX( hRxObject::desc(), &m_shape3dimporter );
	OdDgEllipse2d::desc()->addX( hRxObject::desc(),&m_ellipse2dimporter);
	OdDgEllipse3d::desc()->addX( hRxObject::desc(), &m_ellipse3dimporter);
	OdDgArc2d::desc()->addX( hRxObject::desc(), &m_arc2dimporter );
	OdDgArc3d::desc()->addX( hRxObject::desc(), &m_arc3dimporter );
	OdDgComplexShape::desc()->addX( hRxObject::desc(), &m_complexShapeimporter );
	OdDgBSplineCurve2d::desc()->addX( hRxObject::desc(), &m_bSplineCurve2dimporter );
	OdDgBSplineCurve3d::desc()->addX( hRxObject::desc(), &m_bSplineCurve3dimporter );
	OdDgBSplineSurface::desc()->addX( hRxObject::desc(), &m_bSplineSurfaceimporter );
	OdDgText2d::desc()->addX( hRxObject::desc(), &m_bText2dimporter );
	OdDgText3d::desc()->addX( hRxObject::desc(), &m_bText3dimporter );
	OdDgReferenceAttachmentHeader::desc()->addX( hRxObject::desc(), &m_bReferenceHeaderimporter );
	OdDgSharedCellDefinitionTable::desc()->addX( hRxObject::desc(), &m_bSharedCellDefinitionTableimporter );
	OdDgSharedCellDefinition::desc()->addX( hRxObject::desc(), &m_bSharedCellDefinitionimporter );
	OdDgSharedCellReference::desc()->addX( hRxObject::desc(), &m_bSharedCellReferenceimporter );
	OdDgMesh::desc()->addX( hRxObject::desc(), &m_bMeshimporter );
	OdDgDimension::desc()->addX( hRxObject::desc(), &m_dimensionImporter );
	OdDgViewGroupTable::desc()->addX( hRxObject::desc(), &m_viewGroupTableImporter );
	OdDgView::desc()->addX( hRxObject::desc(), &m_viewImporter );
	OdDgViewGroup::desc()->addX( hRxObject::desc(), &m_viewGroupImporter );

	OdDgTextNode2d::desc()->addX( hRxObject::desc(), &m_textNode2dImporter );
	OdDgTextNode3d::desc()->addX( hRxObject::desc(), &m_textNode3dImporter );
};

OdDgImporter::~OdDgImporter()
{
	OdDgDatabase::desc()->delX( hRxObject::desc() );
	OdDgModel::desc()->delX( hRxObject::desc() );
	OdDgCellHeader2d::desc()->delX( hRxObject::desc() );
	OdDgCellHeader3d::desc()->delX( hRxObject::desc() );
	OdDgSolid::desc()->delX( hRxObject::desc() );
	OdDgSurface::desc()->delX( hRxObject::desc() );
	OdDgCone::desc()->delX( hRxObject::desc() );
	OdDgLine2d::desc()->delX( hRxObject::desc() );
	OdDgLine3d::desc()->delX( hRxObject::desc() );
	OdDgLineString2d::desc()->delX( hRxObject::desc() );
	OdDgLineString3d::desc()->delX( hRxObject::desc() );
	OdDgShape2d::desc()->delX( hRxObject::desc() );
	OdDgShape3d::desc()->delX( hRxObject::desc() );
	OdDgEllipse2d::desc()->delX( hRxObject::desc() );
	OdDgEllipse3d::desc()->delX( hRxObject::desc() );
	OdDgArc2d::desc()->delX( hRxObject::desc() );
	OdDgArc3d::desc()->delX( hRxObject::desc() );
	OdDgComplexShape::desc()->delX( hRxObject::desc() );
	OdDgBSplineCurve2d::desc()->delX( hRxObject::desc() );
	OdDgBSplineCurve3d::desc()->delX( hRxObject::desc() );
	OdDgBSplineSurface::desc()->delX( hRxObject::desc() );
	OdDgText2d::desc()->delX( hRxObject::desc() );
	OdDgText3d::desc()->delX( hRxObject::desc() );
	OdDgReferenceAttachmentHeader::desc()->delX( hRxObject::desc() );
	OdDgSharedCellDefinitionTable::desc()->delX( hRxObject::desc() );
	OdDgSharedCellDefinition::desc()->delX( hRxObject::desc() );
	OdDgSharedCellReference::desc()->delX( hRxObject::desc() );
	OdDgMesh::desc()->delX( hRxObject::desc() );
	OdDgDimension::desc()->delX( hRxObject::desc() );
	OdDgViewGroupTable::desc()->delX( hRxObject::desc() );
	OdDgView::desc()->delX( hRxObject::desc() );
	OdDgViewGroup::desc()->delX( hRxObject::desc() );
	OdDgTextNode2d::desc()->delX( hRxObject::desc() );
	OdDgTextNode3d::desc()->delX( hRxObject::desc() );
}



hRxObject::hRxObject()
: m_references( 0 )
{
}


void hRxObject::addRef()
{
	m_references++;
}


void hRxObject::release()
{
	m_references--;
}


long hRxObject::numRefs() const
{
	return m_references;
}

inline void condition_string_for_segment_name(char* zString)
{
	char* pIn = (char*)zString;

	while (*pIn != 0)
	{
		if (*pIn == ',')
			*pIn = ' ';
		else if (*pIn == '\'')
			*pIn = ' ';
		else if (*pIn == '\"')
			*pIn = ' ';
		else if (*pIn == '/')
			*pIn = ' ';
		else if (*pIn == '*')
			*pIn = ' ';
		else if (*pIn == '~')
			*pIn = ' ';
		else if (*pIn == '|')
			*pIn = ' ';
		else if (*pIn == '(')
			*pIn = ' ';
		else if (*pIn == ')')
			*pIn = ' ';
		pIn++;
	}
}

inline void convertToCharArray(OdString in, char* out)
{
	size_t origsize = wcslen((const wchar_t *)in.c_str()) + 1;
	size_t convertedChars = 0;
	wcstombs_s(&convertedChars, out, origsize, (const wchar_t *)in.c_str(), _TRUNCATE);
}

//converts hex string to int
inline int hexStrToInt(const char *value)
{

	struct CHexMap
	{
		TCHAR chr;
		int value;
	};
	const int HexMapL = 16;
	CHexMap HexMap[HexMapL] =
	{
		{'0', 0}, {'1', 1},
		{'2', 2}, {'3', 3},
		{'4', 4}, {'5', 5},
		{'6', 6}, {'7', 7},
		{'8', 8}, {'9', 9},
		{'A', 10}, {'B', 11},
		{'C', 12}, {'D', 13},
		{'E', 14}, {'F', 15}
	};

	TCHAR *mstr = _tcsupr(_tcsdup(value));
	TCHAR *s = mstr;
	int result = 0;
	if (*s == '0' && *(s + 1) == 'X') s += 2;	
	bool firsttime = true;
	while (*s != '\0')
	{
		bool found = false;
		for (int i = 0; i < HexMapL; i++)
		{
			if (*s == HexMap[i].chr)
			{
				if (!firsttime) result <<= 4;
				result |= HexMap[i].value;
				found = true;
				break;
			}
		}
		if (!found) break;
		s++;
		firsttime = false;
	}
	free(mstr);
	return result;
}


inline int getElementID(OdDgElementPtr elm)
{
	OdString str = elm->elementId().getHandle().ascii();
	int len = str.getLength();
	char* hstr = new char[len + 1];
	convertToCharArray(str, hstr);
	int ID = hexStrToInt(hstr);
	H_SAFE_DELETE_ARRAY(hstr);
	return ID;
}

bool getFirstchildWithAttr(OdDgElementIteratorPtr iterator, OdRxObjectPtr* object )
{
	int  counter = 0;
	for( ; !iterator->done(); iterator->step(), counter++ )
	{
		*object = iterator->item().openObject();

		if ( !(*object).isNull() )
		{
			OdString child_name = (*object)->isA()->name();
			int len = child_name.getLength();
			char* class_name = new char[len + 1];
			convertToCharArray(child_name, class_name);
			if(strcmp(class_name, "OdDgPointString3d") == 0)
			{
				continue;
			}
			if(strcmp(class_name, "OdDgCellHeader3d") == 0 || strcmp(class_name, "OdDgCellHeader2d") == 0 || strcmp(class_name, "OdDgSolid") == 0 )
			{
				bool val = false ;
				if(strcmp(class_name, "OdDgCellHeader3d") == 0)
					val = getFirstchildWithAttr(((OdDgCellHeader3dPtr)(*object))->createIterator(), object  );
				else if(strcmp(class_name, "OdDgCellHeader2d") == 0) 
					val = getFirstchildWithAttr(((OdDgCellHeader2dPtr)(*object))->createIterator(), object  );
				else if(strcmp(class_name, "OdDgSolid") == 0)
				{
					int dbg_iteratorNotAllowed = 0;
					//val = getFirstchildWithAttr(((OdDgSolidPtr)(*object))->createIterator(), object  );
				}

				H_SAFE_DELETE_ARRAY(class_name);

				if(val == true)
					return true;
			}
			else
			{
				H_SAFE_DELETE_ARRAY(class_name);
				return true;
				break;
			}

		}
	}
	return false;
}


inline void setElementMaterialProperties( OdDgGraphicsElementPtr grElm )
{
	if(!grElm.isNull())
	{
		OdUInt32 colIndex = grElm->getColorIndex();
		//ByLevel flag for element is 0xffffffff(4294967295)
		if (colIndex != 4294967295)
		{
			ODCOLORREF element_colorref = OdDgColorTable::lookupRGB(grElm->database(), grElm->getColorIndex());
			if(element_colorref != 0)
			{
				float red_col = (float)ODGETRED(element_colorref)/255.0f;
				float green_col = (float)ODGETGREEN(element_colorref)/255.0f;
				float blue_col = (float)ODGETBLUE(element_colorref)/255.0f;
				HC_Set_Color_By_Value("geometry", "RGB", red_col, green_col, blue_col );
			}
		}
	}
}

inline void setLevelMaterialProperties( OdDgGraphicsElementPtr grElm )
{
	if(!grElm.isNull())
	{
		OdDgElementId eid = grElm->getLevelId();
		OdDgTableRecordPtr pRec =  eid.openObject();
		OdDgLevelTableRecordPtr pLevel = pRec; 
		//OdUInt32 indexl = pLevel->getElementColorIndex();
		if(!pLevel.isNull())
		{
			ODCOLORREF level_colorref = OdDgColorTable::lookupRGB(pLevel->database(), pLevel->getElementColorIndex());
			if(level_colorref != 0)
			{
				float red_col = (float)ODGETRED(level_colorref)/255.0f;
				float green_col = (float)ODGETGREEN(level_colorref)/255.0f;
				float blue_col = (float)ODGETBLUE(level_colorref)/255.0f;
				HC_Set_Color_By_Value("geometry", "RGB", red_col, green_col, blue_col );
			}
		}
	}
}


bool HDGNImporter::getLevelName( OdDgGraphicsElementPtr grElm, char*& level_name )
{
	level_name = new char[10];
	strcpy(level_name, "unknown");
	if(!grElm.isNull())
	{
		OdDgElementId eid = grElm->getLevelId();
		OdDgTableRecordPtr pRec =  eid.openObject();
		OdDgLevelTableRecordPtr pLevel = pRec;

		if(!pLevel.isNull())
		{
			OdString name = pLevel->getName();
			size_t origsize = wcslen((const wchar_t *)name.c_str()) + 1;
			size_t convertedChars = 0;
			int nstrlen=name.getLength();		
			level_name = new char[nstrlen + 1];
			wcstombs_s(&convertedChars, level_name, origsize, (const wchar_t *)name.c_str(), _TRUNCATE);
			condition_string_for_segment_name(level_name);

			//Prepare vhash of level name and its EntryID
			int levelEntryID = 	pLevel->getEntryId();
			char* tempLvlName = m_hashLevelIDName.Lookup(levelEntryID);

			if(tempLvlName == 0)
			{
				m_hashLevelIDName.InsertItem(levelEntryID, level_name);
			}
		}
		return true;
	}
	else{
		return false;}

}


inline bool getVisibilityOfLevel(OdRxObjectPtr pObj)
{
	if(!pObj.isNull())
	{
		OdDgGraphicsElementPtr grElm;
		try
		{
			grElm =(OdDgGraphicsElementPtr) pObj;
		}
		catch(...)
		{
		}
		
		if(!grElm.isNull())
		{
			OdDgElementId eid = grElm->getLevelId();
			OdDgTableRecordPtr pRec =  eid.openObject();
			OdDgLevelTableRecordPtr pLevel = pRec;
			if(!pLevel.isNull())
			{
				if( pLevel->getIsDisplayedFlag() == false)
					return false;
				else
					return true;
			}
			else
				return true;
		}
		else
			return true;
	}
	else
		return true;
}

//worldDraw() code

template<class T> double OdGiCommonDraw_<T>::deviation(const OdGiDeviationType t, const OdGePoint3d& p) const 

{ //By definition, m_dDeviationForCone defines the biggest mistake of resulting mesh in 
	//compare with ideal cone.
	return m_cone.m_dDeviationForCone ; 
}

template<class T> void OdGiGeometry_<T>::pline(const OdGiPolyline& pline , OdUInt32 n1 , OdUInt32 n2 )
{
	int numPoints = pline.numVerts();		
	for(int i = 0; i < numPoints; i = i + 2)
	{
		OdGePoint2d pt1;
		OdGePoint2d pt2;
		pline.getPointAt(i, pt1);
		pline.getPointAt(i + 1, pt2);			
		HPoint hPoint1[1];
		HPoint hPoint2[1];
		m_pHDGNImporter->OdGePoint2d_2_HPoint(&pt1, hPoint1[0]);
		m_pHDGNImporter->OdGePoint2d_2_HPoint(&pt2, hPoint2[0]);
		HC_Insert_Line(hPoint1->x, hPoint1->y, hPoint1->z, hPoint2->x,hPoint2->y, hPoint2->z);
	}
}

template<class T> void OdGiGeometry_<T>::pushModelTransform(const OdGeMatrix3d& xMat)
{
	float hmatrix[] = 
	{xMat.entry[0][0],          xMat.entry[1][0],          xMat.entry[2][0],          xMat.entry[3][0] ,
	xMat.entry[0][1],          xMat.entry[1][1],          xMat.entry[2][1],          xMat.entry[3][1] ,
	xMat.entry[0][2],          xMat.entry[1][2],          xMat.entry[2][2],          xMat.entry[3][2] ,
	(xMat.entry[0][3]) - (m_pHDGNImporter->m_dMinX), (xMat.entry[1][3]) - (m_pHDGNImporter->m_dMinY), (xMat.entry[2][3]) - (m_pHDGNImporter->m_dMinZ), xMat.entry[3][3]};

	HC_Set_Modelling_Matrix(hmatrix);

}

template<class T> void OdGiGeometry_<T>::circle(const OdGePoint3d& center, double radius, const OdGeVector3d& normal)
{
	if(radius > 0)
	{
		HPoint hCenter[1];
		m_pHDGNImporter->OdGePoint3d_2_HPoint(&center, hCenter[0]);
		float hNormal[3];
		hNormal[0] = normal.x;	hNormal[1] = normal.y; hNormal[2] = normal.z;
		HC_KEY Circle_key = HC_KInsert_Circle_By_Radius(hCenter, radius, hNormal);
	
		if(m_pHDGNImporter->m_bCellHeaderHoleFlag==true && Circle_key != -1)//If Cell header has hole then convert this geometry into shell.
		{
		   m_pHDGNImporter->m_hkShellKey = HC_Generate_Shell_From_Geometry(Circle_key,"");
		   HC_Delete_By_Key(Circle_key);
		   HC_KEY hkGeoTobeCopied=INVALID_KEY;
			if(!(m_pHDGNImporter->m_bWorldDrawEntityFlag))
			{
				HC_Open_Segment_By_Key(m_pHDGNImporter->m_hkSolidSegKey);
				hkGeoTobeCopied = HC_KCopy_Geometry(m_pHDGNImporter->m_hkShellKey,".");
				HC_Close_Segment();
			}
			else
			{
			   HC_Open_Segment_By_Key(m_pHDGNImporter->m_hkHoleSegKey);
			   hkGeoTobeCopied = HC_KCopy_Geometry(m_pHDGNImporter->m_hkShellKey,".");
			   HC_Close_Segment();
			}
			(m_pHDGNImporter->m_hashGeomCellID)->InsertItem(hkGeoTobeCopied, m_pHDGNImporter->m_iCellHeaderId);
			m_pHDGNImporter->m_hkSegTobeUsed = HC_KShow_Owner_By_Key(m_pHDGNImporter->m_hkShellKey);
			HC_Delete_By_Key(m_pHDGNImporter->m_hkShellKey);
			m_pHDGNImporter->m_hkShellKey = INVALID_KEY;  	
		}      
	}
}

template<class T> void OdGiGeometry_<T>::circle(const OdGePoint3d& p1, const OdGePoint3d& p2, const OdGePoint3d& p3)
{
	HPoint hPoint1[1];
	HPoint hPoint2[1];
	HPoint hPoint3[1];
	m_pHDGNImporter->OdGePoint3d_2_HPoint(&p1, hPoint1[0]);
	m_pHDGNImporter->OdGePoint3d_2_HPoint(&p2, hPoint2[0]);
	m_pHDGNImporter->OdGePoint3d_2_HPoint(&p3, hPoint3[0]);
	HC_KEY Circle_key = HC_KInsert_Circle(hPoint1, hPoint2, hPoint3);
	
	if(m_pHDGNImporter->m_bCellHeaderHoleFlag == true && Circle_key != -1 )//If Cell header has hole then convert this geometry into shell.
	{
	   m_pHDGNImporter->m_hkShellKey = HC_Generate_Shell_From_Geometry(Circle_key,"");
	   HC_Delete_By_Key(Circle_key);
	   HC_KEY hkGeoTobeCopied=INVALID_KEY;
		if(!(m_pHDGNImporter->m_bWorldDrawEntityFlag))
		{
			HC_Open_Segment_By_Key(m_pHDGNImporter->m_hkSolidSegKey);
			hkGeoTobeCopied = HC_KCopy_Geometry(m_pHDGNImporter->m_hkShellKey,".");
			HC_Close_Segment();
		}
		else
		{
		   HC_Open_Segment_By_Key(m_pHDGNImporter->m_hkHoleSegKey);
		   hkGeoTobeCopied = HC_KCopy_Geometry(m_pHDGNImporter->m_hkShellKey,".");
		   HC_Close_Segment();
		}
		(m_pHDGNImporter->m_hashGeomCellID)->InsertItem(hkGeoTobeCopied, m_pHDGNImporter->m_iCellHeaderId);
		m_pHDGNImporter->m_hkSegTobeUsed = HC_KShow_Owner_By_Key(m_pHDGNImporter->m_hkShellKey);
		HC_Delete_By_Key(m_pHDGNImporter->m_hkShellKey);
		m_pHDGNImporter->m_hkShellKey = INVALID_KEY;  	
	}      
}

template<class T> void OdGiGeometry_<T>::circularArc(const OdGePoint3d& center,
		double radius,
		const OdGeVector3d& normal,
		const OdGeVector3d& startVector,
		double sweepAngle,
		OdGiArcType arcType = kOdGiArcSimple)
{

	HPoint hcentre[1];
	m_pHDGNImporter->OdGePoint3d_2_HPoint(&center, hcentre[0]);

	HPoint startPoint[1];
	startPoint[0].x = hcentre[0].x + startVector.x;
	startPoint[0].y = hcentre[0].y + startVector.y;
	startPoint[0].z = hcentre[0].z + startVector.z;


	OdGeVector3d endVector = ((OdGeVector3d)startVector).rotateBy(sweepAngle,normal);
	HPoint endPoint[1];
	endPoint[0].x = hcentre[0].x + endVector.x;
	endPoint[0].y = hcentre[0].y + endVector.y;
	endPoint[0].z = hcentre[0].z + endVector.z;

	// workaround : sweepAngle/2 is empirical in following statement...should be relooked in future
	OdGeVector3d midVector = ((OdGeVector3d)startVector).rotateBy(sweepAngle/2,normal);

	HPoint midPoint[1];
	midPoint[0].x = hcentre[0].x + midVector.x;
	midPoint[0].y = hcentre[0].y + midVector.y;
	midPoint[0].z = hcentre[0].z + midVector.z;

	HC_Insert_Circular_Arc(startPoint, midPoint, endPoint);

}

template<class T> void OdGiGeometry_<T>::circularArc(const OdGePoint3d& start,
		const OdGePoint3d& point,
		const OdGePoint3d& end,
		OdGiArcType arcType = kOdGiArcSimple)
{
	HPoint hPoint1[1];
	HPoint hPoint2[1];
	HPoint hPoint3[1];
	m_pHDGNImporter->OdGePoint3d_2_HPoint(&start, hPoint1[0]);
	m_pHDGNImporter->OdGePoint3d_2_HPoint(&point, hPoint2[0]);
	m_pHDGNImporter->OdGePoint3d_2_HPoint(&end, hPoint3[0]);

	HC_Insert_Circular_Arc(hPoint1, hPoint2, hPoint3);
}

template<class T> void OdGiGeometry_<T>::polyline(OdInt32 nbPoints,const OdGePoint3d* pVertexList,const OdGeVector3d* pNormal = NULL,OdGsMarker lBaseSubEntMarker = -1) 
{
	HPoint* hPoints =  new HPoint[nbPoints];
	for(int i = 0; i < nbPoints; i++)
	{
		m_pHDGNImporter->OdGePoint3d_2_HPoint(&pVertexList[i], hPoints[i]);

	}
	HC_Insert_Polyline(nbPoints, hPoints);
	H_SAFE_DELETE_ARRAY(hPoints);
}

template<class T> void OdGiGeometry_<T>::polygon(OdInt32 nbPoints, const OdGePoint3d* pVertexList)
{
	HPoint* hPoints =  new HPoint[nbPoints];
	for(int i = 0; i < nbPoints; i++)
	{
		m_pHDGNImporter->OdGePoint3d_2_HPoint(&pVertexList[i], hPoints[i]);
	}

	HC_KEY Polygon_key = HC_KInsert_Polygon(nbPoints, hPoints);

	H_SAFE_DELETE_ARRAY(hPoints);
	
	if(m_pHDGNImporter->m_bCellHeaderHoleFlag == true && Polygon_key != -1)//If Cell header has hole then convert this geometry into shell.
	{
       m_pHDGNImporter->m_hkShellKey = HC_Generate_Shell_From_Geometry(Polygon_key,"");
	   HC_Delete_By_Key(Polygon_key);
	   HC_KEY hkGeoTobeCopied = INVALID_KEY;
		if(!(m_pHDGNImporter->m_bWorldDrawEntityFlag))
		{
			HC_Open_Segment_By_Key(m_pHDGNImporter->m_hkSolidSegKey);
			hkGeoTobeCopied = HC_KCopy_Geometry(m_pHDGNImporter->m_hkShellKey,".");
			HC_Close_Segment();
		}
		else
		{
		   HC_Open_Segment_By_Key(m_pHDGNImporter->m_hkHoleSegKey);
		   hkGeoTobeCopied = HC_KCopy_Geometry(m_pHDGNImporter->m_hkShellKey,".");
		   HC_Close_Segment();
		}
		(m_pHDGNImporter->m_hashGeomCellID)->InsertItem(hkGeoTobeCopied, m_pHDGNImporter->m_iCellHeaderId);
		m_pHDGNImporter->m_hkSegTobeUsed = HC_KShow_Owner_By_Key(m_pHDGNImporter->m_hkShellKey);
		HC_Delete_By_Key(m_pHDGNImporter->m_hkShellKey);
		m_pHDGNImporter->m_hkShellKey=INVALID_KEY;  	
	}        
		
}

template<class T> void OdGiGeometry_<T>::mesh(OdInt32 rows,
		OdInt32 columns,
		const OdGePoint3d* pVertexList,
		const OdGiEdgeData* pEdgeData = NULL,
		const OdGiFaceData* pFaceData = NULL,
		const OdGiVertexData* pVertexData = NULL)
{
	HPoint* hVertex = new HPoint[rows*columns]; 
	for(int i = 0; i < (rows*columns); i++)
	{
		m_pHDGNImporter->OdGePoint3d_2_HPoint(&pVertexList[i], hVertex[i]);
	}
	HC_KEY Mesh_key =  HC_KInsert_Mesh(rows, columns, hVertex);
	H_SAFE_DELETE_ARRAY(hVertex);
	if(m_pHDGNImporter->m_bCellHeaderHoleFlag == true && Mesh_key != -1)//If Cell header has hole then convert this geometry into shell.
	{
       m_pHDGNImporter->m_hkShellKey = HC_Generate_Shell_From_Geometry(Mesh_key,"");
	   HC_Delete_By_Key(Mesh_key);
	   HC_KEY hkGeoTobeCopied=INVALID_KEY;
		if(!(m_pHDGNImporter->m_bWorldDrawEntityFlag))
		{
			HC_Open_Segment_By_Key(m_pHDGNImporter->m_hkSolidSegKey);
			hkGeoTobeCopied=HC_KCopy_Geometry(m_pHDGNImporter->m_hkShellKey,".");
			HC_Close_Segment();
		}
		else
		{
		   HC_Open_Segment_By_Key(m_pHDGNImporter->m_hkHoleSegKey);
		   hkGeoTobeCopied=HC_KCopy_Geometry(m_pHDGNImporter->m_hkShellKey,".");
		   HC_Close_Segment();
		}
		(m_pHDGNImporter->m_hashGeomCellID)->InsertItem(hkGeoTobeCopied, m_pHDGNImporter->m_iCellHeaderId);
		m_pHDGNImporter->m_hkSegTobeUsed = HC_KShow_Owner_By_Key(m_pHDGNImporter->m_hkShellKey);
		HC_Delete_By_Key(m_pHDGNImporter->m_hkShellKey);
		m_pHDGNImporter->m_hkShellKey = INVALID_KEY;  	
	}      
}

template<class T> void OdGiGeometry_<T>::shell(OdInt32 nbVertex,
		const OdGePoint3d* pVertexList,
		OdInt32 faceListSize,
		const OdInt32* pFaceList,
		const OdGiEdgeData* pEdgeData,
		const OdGiFaceData* pFaceData,
		const OdGiVertexData* pVertexData )
{
	//appendWire()->shell(nbVertex, pVertexList, faceListSize, pFaceList, pEdgeData, pFaceData, pVertexData);

	if(m_pHDGNImporter->m_bFromSmartSolid )
		m_pHDGNImporter->m_bNoOffset = true;

	HPoint* hPoints = new HPoint[nbVertex];
	for(int i =0; i < nbVertex; i++)
	{
		m_pHDGNImporter->OdGePoint3d_2_HPoint(&pVertexList[i], hPoints[i]);

	}

	int* flist = new int[faceListSize];

	for ( int j =0; j < faceListSize; j++)
	{
		flist[j] = pFaceList[j];
	}

	HC_Insert_Shell(nbVertex, hPoints, faceListSize, flist);

	H_SAFE_DELETE_ARRAY(flist);

	H_SAFE_DELETE_ARRAY(hPoints);

	if(m_pHDGNImporter->m_bFromSmartSolid)
		m_pHDGNImporter->m_bNoOffset = false;


}

template<class T> void OdGiGeometry_<T>::text(const OdGePoint3d& position,
		const OdGeVector3d& normal, const OdGeVector3d& direction,
		double height, double width, double oblique, const OdString& msg)
{
	size_t origsize = wcslen((const wchar_t *)msg) + 1;
	size_t convertedChars = 0;
	char* text = new char[origsize];
	wcstombs_s(&convertedChars, text, origsize, (const wchar_t *)msg, _TRUNCATE);

	HPoint hpos[1];
	m_pHDGNImporter->OdGePoint3d_2_HPoint(&position, hpos[0]);

	HC_Insert_Text( hpos[0].x, hpos[0].y, hpos[0].z, text);
	HC_Set_Text_Font("size = 0.75 oru,transforms = on");
	H_SAFE_DELETE_ARRAY(text);

}

template<class T> void OdGiGeometry_<T>::text(const OdGePoint3d& position,
		const OdGeVector3d& normal, const OdGeVector3d& direction,
		const OdChar* msg, OdInt32 length, bool raw, const OdGiTextStyle* pTextStyle)
{
	size_t origsize = wcslen((const wchar_t *)msg) + 1;
	size_t convertedChars = 0;
	char* text = new char[origsize];
	wcstombs_s(&convertedChars, text, origsize, (const wchar_t *)msg, _TRUNCATE);

	HPoint hpos[1];
	m_pHDGNImporter->OdGePoint3d_2_HPoint(&position, hpos[0]);

	HC_Insert_Text( hpos[0].x, hpos[0].y, hpos[0].z, text);
	HC_Set_Text_Font("size = 0.75 oru,transforms = on");
	H_SAFE_DELETE_ARRAY(text);

}

template<class T> void OdGiGeometry_<T>::ray(const OdGePoint3d& first, const OdGePoint3d& second)
{
	HPoint hFirst[1];
	m_pHDGNImporter->OdGePoint3d_2_HPoint(&first,hFirst[0]); 
	HPoint hSecond[1];
	m_pHDGNImporter->OdGePoint3d_2_HPoint(&second,hSecond[0]); 
	HC_Insert_Line( hFirst[0].x, hFirst[0].y, hFirst[0].z, hSecond[0].x, hSecond[0].y, hSecond[0].z);
}

template<class T> void OdGiGeometry_<T>::xline(const OdGePoint3d& p1, const OdGePoint3d& p2)
{
	HPoint hFirst[1];
	m_pHDGNImporter->OdGePoint3d_2_HPoint(&p1,hFirst[0]); 
	HPoint hSecond[1];
	m_pHDGNImporter->OdGePoint3d_2_HPoint(&p2,hSecond[0]); 
	HC_Insert_Line( hFirst[0].x, hFirst[0].y, hFirst[0].z, hSecond[0].x, hSecond[0].y, hSecond[0].z);
}

template<class T> void OdGiGeometry_<T>::ellipArc(const OdGeEllipArc3d& arc,
		const OdGePoint3d* pEndPointsOverrides = 0,
		OdGiArcType arcType = kOdGiArcSimple)
{
	if(arcType == kOdGiArcSimple)
		m_arc3d.importAsEllipticalArc(arc, false);
	else
		m_arc3d.importAsEllipticalArc(arc, true);

}

template<class T> void OdGiGeometry_<T>::worldLine(const OdGePoint3d pnts[2])
{
	HPoint hFirst[1];
	m_pHDGNImporter->OdGePoint3d_2_HPoint(&pnts[0],hFirst[0]); 
	HPoint hSecond[1];
	m_pHDGNImporter->OdGePoint3d_2_HPoint(&pnts[1],hSecond[0]); 
	HC_Insert_Line( hFirst[0].x, hFirst[0].y, hFirst[0].z, hSecond[0].x, hSecond[0].y, hSecond[0].z);
}
//Worlddraw End

void HDGNImporter::importXData (OdResBufPtr pRb)
{
	if ( pRb.get() )
	{
		char* userOption = new char[3];
		strcpy(userOption, " ");
		strcat(userOption, "\"");		

		for ( ; !pRb.isNull(); pRb = pRb->next() ) 
		{
			
			int resType = pRb->restype();
			OdString rbStr;
			switch ( OdDxfCode::_getType(resType) )
			{
			case OdDxfCode::Name:
			case OdDxfCode::String:
				rbStr.format(L"%ls", pRb->getString().c_str());
				break;
			case OdDxfCode::Bool:
				rbStr.format(L"%ls", (pRb->getBool() ? L"<true>" : L"<false>"));
				break;
			case OdDxfCode::Integer8:
				rbStr.format(L"%d", pRb->getInt8());
				break;
			case OdDxfCode::Integer16:
				rbStr.format(L"%d", pRb->getInt16());
				break;
			case OdDxfCode::Integer32:
				rbStr.format(L"%d", pRb->getInt32());
				break;
			case OdDxfCode::Double:
			case OdDxfCode::Angle:
				rbStr.format(L"%f", pRb->getDouble());
				break;
			case OdDxfCode::Point:
				{
					OdGePoint3d pt = pRb->getPoint3d();
					rbStr.format(L"Point(%f, %f, %f)", pt.x, pt.y, pt.z );
				}
				break;
			case OdDxfCode::BinaryChunk:
				{
					OdBinaryData data = pRb->getBinaryChunk();
					rbStr.format(L"BinaryChunk (Size = %d)", data.size());
				}
				break;
			case OdDxfCode::LayerName:
				rbStr.format(L"%ls", pRb->getString().c_str());
				break;
			case OdDxfCode::Handle:
				rbStr.format(L"%ls", pRb->getHandle().ascii().c_str());
				break;
			default:
				ODA_FAIL_ONCE();
				rbStr = L"<Unknown type>";
			}
			int nstrlength=rbStr.getLength();
			
			char*  tempStr = new char[nstrlength + 1];
			convertToCharArray(rbStr, tempStr);
			size_t nuseroptionlen=strlen(userOption);
			
			char* tempUserOption = new char[nstrlength+nuseroptionlen + 2];
			strcpy(tempUserOption,userOption);
			H_SAFE_DELETE_ARRAY(userOption);
			
			userOption = new char[nstrlength+nuseroptionlen + 4];
			strcpy(userOption,tempUserOption);
			H_SAFE_DELETE_ARRAY(tempUserOption);

			strcat(userOption,tempStr);
			strcat(userOption, " ");			
			H_SAFE_DELETE_ARRAY(tempStr);
		}

		strcat(userOption, " ");
		strcat(userOption, "\"");
		HC_Set_User_Options(userOption);		
		size_t nlen=strlen(userOption);
        H_SAFE_DELETE_ARRAY(userOption); 
	}
}

void HDGNImporter::iterateElm( OdDgElementIteratorPtr iterator, bool visibilityProcessing, bool checkProgress,int CHeaderid)
{
	//
	int	counter = 0;
	OdRxObjectPtr object;
	//OdSmartPtr<HDGNImporter> importer;

	for( ; !iterator->done(); iterator->step(), counter++ )
	{
		object = iterator->item().openObject();
	    g_obHDGNImporter = HDGNImporter::cast( object );
		
		if ( !g_obHDGNImporter.isNull() )
		{

			if(visibilityProcessing)
			{
						
				if(m_bIgnoreOffEntities)
				{
					OdDgGraphicsElementPtr grElm = (OdDgGraphicsElementPtr) object;
					if(grElm->getInvisibleFlag())
						continue;


					OdRxObjectPtr objectForVisSetting;

					if(object->isKindOf(OdDgCellHeader3d::desc()))
					{
						OdDgCellHeader3dPtr element = object;
						getFirstchildWithAttr(element->createIterator(), &objectForVisSetting);
					}
					else if(object->isKindOf(OdDgCellHeader2d::desc()))
					{
						OdDgCellHeader2dPtr element = object;
						getFirstchildWithAttr(element->createIterator(), &objectForVisSetting);
					}
					else
					{
						objectForVisSetting = object;
					}
					if(!getVisibilityOfLevel(objectForVisSetting))
						continue;
				}
			}
            if(CHeaderid!=0)//This condition is very very important to load correct Cellheader id of 
			{               //the geometry that is going to be imported further.(ofcourse if present)
                m_iCellHeaderId=CHeaderid;
			}   
		
			//Depending on the content of the importer object, corresponding entities import function is called
			//(import is virtual function) : Mustafa B
			g_obHDGNImporter->import( object );

			if(checkProgress)
			{
				float progressVal = m_inputHandler->GetInputPercentProgress() + (1.0f/m_totalEntities);

				//debug code
				/*char delbuffer[1024];
				sprintf(delbuffer,"%f",progressVal);
				m_inputHandler->ReportInputInformation(delbuffer);*/

				m_inputHandler->ReportInputPercentProgress(progressVal);

			}
		}
   	}
}

OdDgModelPtr HDGNImporter::getActiveModel(OdDgDatabasePtr pDatabase)
{
	OdDgElementId activeModelID = pDatabase->getActiveModelId();
	OdDbHandle modelhandle = activeModelID.getHandle();
	OdString activeModel = modelhandle.ascii();

	OdDgModelTablePtr pModelTable = pDatabase->getModelTable();

	OdDgElementIteratorPtr pIter = pModelTable->createIterator();
	for ( ; !pIter->done(); pIter->step() )
	{
		OdString tempModel;
		OdDgModelPtr pModel;
		{
			pModel = OdDgModel::cast( pIter->item().openObject() );
		//	OdString modelName = pModel->getName();

			OdUInt32 modelEntryID = pModel->getEntryId();
			OdDgElementId tempID = pModelTable->getAt(modelEntryID);
			OdDbHandle temphandle = tempID.getHandle();
			tempModel = temphandle.ascii();
		}
		if(tempModel.compare(activeModel) == 0 )//if current model is active model 
		{
			if ( pModel.get() )
			{
				return pModel;
			}
		}
	}
}


void Database::import( OdRxObjectPtr object )
{
	pDb = object;
	if(m_bDGNImportAllModels)
	{
		OdDgElementId activeModelID = pDb->getActiveModelId();
		OdDbHandle modelhandle = activeModelID.getHandle();
		OdString activeModel = modelhandle.ascii();
		OdDgModelTablePtr pModelTable = pDb->getModelTable();
		OdDgElementIteratorPtr pIter = pModelTable->createIterator();
		for ( ; !pIter->done(); pIter->step() )
		{
			OdString tempModel;
			OdDgModelPtr pModel;
			{
				pModel = OdDgModel::cast( pIter->item().openObject() );
				OdString modelName = pModel->getName();

				OdUInt32 modelEntryID = pModel->getEntryId();
				OdDgElementId tempID = pModelTable->getAt(modelEntryID);
				OdDbHandle temphandle = tempID.getHandle();
				tempModel = temphandle.ascii();
			}

			if ( pModel.get() )
			{

				OdSmartPtr< Model > pModelimporter = pModel;
				OdString activeModelName = pModel->getName();

				int nstrlen=activeModelName.getLength();
				char* hactiveModelName = new char[nstrlen + 1];
				convertToCharArray(activeModelName, hactiveModelName);
				char* segName = new char[strlen("Model_") + nstrlen + 1];
				sprintf(segName, "Model_%s", hactiveModelName);
				H_SAFE_DELETE_ARRAY(hactiveModelName);

				char temp[MVO_BUFFER_SIZE];
				sprintf(temp, "Layout=%s",segName);

				HC_Open_Segment(segName);
				{
					pModelimporter->import( pModel.get() );
					HC_Set_Unicode_Options((unsigned short const*)H_UTF16(temp).encodedText());
					if(tempModel.compare(activeModel) != 0 )//if current model is active model 
					{
						HC_Set_Visibility("off");
						HC_Set_Heuristics("exclude bounding");
						HC_Set_Rendering_Options("Attribute Lock = visibility");
					}
				}
				HC_Close_Segment();

				H_SAFE_DELETE_ARRAY(segName);
			}
		}
	}
	else
	{
		OdDgModelPtr pModel = getActiveModel(pDb);

		OdSmartPtr< Model > pModelimporter = pModel;
		OdString activeModelName = pModel->getName();

		int nstrlen=activeModelName.getLength();
		char* hactiveModelName = new char[nstrlen + 1];
		convertToCharArray(activeModelName, hactiveModelName);
		char* segName = new char[strlen("Model_") + nstrlen + 1];
		sprintf(segName, "Model_%s", hactiveModelName);
		H_SAFE_DELETE_ARRAY(hactiveModelName);
		HC_Open_Segment(segName);
		{
			pModelimporter->import( pModel.get() );
		}
		HC_Close_Segment();
		H_SAFE_DELETE_ARRAY(segName);
	}
}


void Model::import( OdRxObjectPtr object )
{
	OdDgModelPtr element = object;

	if(m_bDGNRebaselineModel)
	{
		m_dMinX = m_dMinY = m_dMinZ = LARGEVAL ;
		OdGeExtents3d extent;
		try
		{
			OdResult res = element->getGeomExtents(extent);
		}
		catch(...){

		}
		bool isExtentValid = extent.isValidExtents();

		if(isExtentValid)
		{
			if(m_dMinX >  extent.minPoint().x)
				m_dMinX =  extent.minPoint().x;
			if(m_dMinY > extent.minPoint().y)
				m_dMinY = extent.minPoint().y;
			if(m_dMinZ > extent.minPoint().z)
				m_dMinZ = extent.minPoint().z;

		}
		else
		{
			m_dMinX = m_dMinY = m_dMinZ = 0;
		}

	}
	else
	{
		m_dMinX = m_dMinY = m_dMinZ = 0;
	}

	//iterate all graphics elements
	iterateElm( element->createGraphicsElementsIterator(), true, true);

	//Commented below lines and now importing only active group
	//Please see the Issue No. 13191 for more details.
	/*
	//table of named views
	OdRxObjectPtr                  view_object;
	view_object = pDb->getViewGroupTable();

	if( !view_object.isNull() )
	{
		//OdSmartPtr< HDGNImporter > viewIterator;
		g_obHDGNImporter = view_object;
		g_obHDGNImporter->import( view_object );
	}
	*/


	OdDgElementId idActiveViewGroup = pDb->getActiveViewGroupId();
	OdDbHandle hdActiveViewGroup    = idActiveViewGroup.getHandle();
	OdString strActiveViewGroup		= hdActiveViewGroup.ascii();
	OdDgViewGroupPtr pRec			= idActiveViewGroup.openObject();
	OdRxObjectPtr	view_object = pRec;

	if( !view_object.isNull() )
	{
		
		g_obHDGNImporter = view_object;
		g_obHDGNImporter->import( view_object );
	}

}


void View::import(OdRxObjectPtr object)
{
	OdDgViewPtr element = object;
	OdUInt16 viewIndex = element->getIndex();
	//OdString str = element->getName();

	if(viewIndex != 0)
		return;

	OdDgElementIteratorPtr pIter = element->createIterator();
	int counter = 0;
	for(pIter->start(); !pIter->done(); pIter->step())
	{
		if(counter != 0)
			return;

		counter++;
		OdDgElementPtr SubElement = pIter->item().openObject();

		if(SubElement->isKindOf(OdDgLevelMask::desc()))
		{
			OdDgLevelMaskPtr levelmask = SubElement;

			OdUInt32 maxEntryId = levelmask->getMaxLevelEntryId();
			int countLevels = m_hashLevelIDName.Count();
			for( OdUInt32 i=1; i <= maxEntryId; i++)
			{
				char* levelName = m_hashLevelIDName.Lookup(i);
				if(levelName)
				{
					bool isLevelVisible = levelmask->getLevelIsVisible(i) ;
					if(isLevelVisible == false)
					{
						HC_KEY key = -1;
						char type[64];
						char fullSegPath[1024];
						HC_Begin_Segment_Search("...");
						while(HC_Find_Segment(fullSegPath))
						{
							char* segname = new char[strlen(fullSegPath) + 1];
							{
								char* dir = new char[strlen(fullSegPath) + 1];
								HUtility::FindFileNameAndDirectory(fullSegPath, dir, segname);
								H_SAFE_DELETE_ARRAY(dir);
							}
							if (stricmp(segname, levelName) == 0)
							{
								H_SAFE_DELETE_ARRAY(segname);
								if(m_bIgnoreOffEntities == true)
								{
									HC_Delete_Segment(fullSegPath);
								}
								else
								{
									HC_Open_Segment(fullSegPath);
									HC_Set_Visibility("everything = off");
									HC_Close_Segment();
								}
							}
						}

						HC_End_Segment_Search ();
					}
				}

			}
		}
	}
}


void ViewGroup::import( OdRxObjectPtr object )
{
	OdDgViewGroupPtr element = object;
	iterateElm(element->createIterator(), false, false);

}

void ViewGroupTable::import(OdRxObjectPtr object)
{
	OdDgViewGroupTablePtr element = object;
	iterateElm(element->createIterator(), false, false);
}


//This function is written to subtract hole shapes form solid shapes cominng from 
//2d/3d CellHeaders only 
void HDGNImporter::importCellheaderWithHoleAttr()
{

	int cnt = m_hashGeomCellID->Count();	
	if(cnt>0)//if Cellheader 2d/3d contains solid/hole shapes then perform operation ,if it is empty then leave it.
	{
		VHash<HC_KEY,int>::PairList * pl = m_hashGeomCellID->GetPairList();   
		HC_KEY *ShellArray = new HC_KEY[cnt];
		int *Shell_Elementid = new int[cnt];
		int ctr=0;
		for(int i=0; i<(int)pl->Count(); i++)//load the vhash in to local data types
		{
			ShellArray[i] = pl->NthItem(i)->Key();
			Shell_Elementid[i] = pl->NthItem(i)->Item();	

		}           
		struct vlist_s * pCellidPointer = new_vlist(malloc, free);

		START_LIST_ITERATION(int,  pCellidPointer)
			delete temp;
		END_LIST_ITERATION(pCellidPointer)

		vlist_flush(pCellidPointer);

		vlist_add_last(pCellidPointer,&Shell_Elementid[0]);

		int nCount=0;
		for(int i=1;i<cnt;i++)//The cellheader_id's No. in Shell_Elementid are coming repetedly for each shell.	               
		{                     //Load them in to vlist in non repeated fashion. It will be easy to compare. 
			bool bAddflag=true;
			int v1;
			START_LIST_ITERATION(int, pCellidPointer)
				v1 = *temp;
			if(v1==Shell_Elementid[i] && bAddflag == true)
			{
				bAddflag=false;

			}
			END_LIST_ITERATION(pCellidPointer) 

			if(bAddflag==true)
				vlist_add_last(pCellidPointer,&Shell_Elementid[i]);  

			nCount=vlist_count(pCellidPointer);
		}

		int nindex=0;
		nCount=vlist_count(pCellidPointer);
		int *CellHeaders=new int[nCount];
		START_LIST_ITERATION(int, pCellidPointer)//Load vlist into local data type array.
			CellHeaders[nindex]=*temp;
		nindex++;
		END_LIST_ITERATION(pCellidPointer)
			vlist_flush(pCellidPointer);	

		HC_KEY added_shells = HC_KOpen_Segment("added_shells");//These 2 segments are required to load 
		HC_Close_Segment();                                   //Shells to be added & sutracted.   
		HC_KEY subtracted_shells = HC_KOpen_Segment("subtracted_shells");
		HC_Close_Segment();
		HC_KEY seg_key;

		for(int i=0;i<nCount;i++)//Take each CellHeader id.  
		{
			int geo_count=0;
			for(int j=0;j<cnt;j++)//Load the Shells which are having same cellheader id's, 
			{                    // into 2 segments as per hole/solid.  
				if(CellHeaders[i]==Shell_Elementid[j])
				{
					HC_KEY Owner_Key=HC_KShow_Owner_By_Key(ShellArray[j]);
					if(Owner_Key==m_hkSolidSegKey)
					{
						seg_key=added_shells;
					}
					else if(Owner_Key==m_hkHoleSegKey)
					{
						seg_key=subtracted_shells;
					}

					HC_Open_Segment_By_Key(seg_key);
					HC_Copy_Geometry(ShellArray[j],"."); 
					HC_Close_Segment();
					geo_count++;
				}
			}
			char chTypeSearchName[128];
			HC_KEY added_shell_key=INVALID_KEY;
			HC_KEY subtracted_shell_key=INVALID_KEY;

			HC_Open_Segment_By_Key(added_shells);//Merge all solid shells into one Shell.
			HUtility::Merge_Shells(true,true,true);
			HC_Begin_Contents_Search (".","shell");
			HC_Find_Contents (chTypeSearchName, &added_shell_key);	
			HC_End_Contents_Search();
			HC_Close_Segment();

			HC_Open_Segment_By_Key(subtracted_shells);//Merge all hole shells into one Shell.
			HUtility::Merge_Shells(true,true,true);
			HC_Begin_Contents_Search (".","shell");
			HC_Find_Contents (chTypeSearchName, &subtracted_shell_key);	
			HC_End_Contents_Search();
			HC_Close_Segment(); 

			int vcount1=0,flist_Count1=0,vcount2=0,flist_Count2=0;
			HPoint *hpts1, *hpts2;
			int *flist1, *flist2;	

			if(added_shell_key!=INVALID_KEY)//If no shell is present then  don't load the shell
			{
				HC_Show_Shell_Size(added_shell_key,&vcount1,&flist_Count1);		
				hpts1=new HPoint[vcount1];
				flist1=new int[flist_Count1];
				HC_Show_Shell(added_shell_key,&vcount1,hpts1,&flist_Count1,flist1);	  
			}
			else
			{
				vcount1=0;
				flist_Count1=0;
				hpts1=new HPoint[vcount1];
				flist1=new int[flist_Count1];
			}	 

			if(subtracted_shell_key!=INVALID_KEY)//If no shell is present then  don't load the shell
			{
				HC_Show_Shell_Size(subtracted_shell_key,&vcount2,&flist_Count2);		
				hpts2=new HPoint[vcount2];
				flist2=new int[flist_Count2];
				HC_Show_Shell(subtracted_shell_key,&vcount2,hpts2,&flist_Count2,flist2);	   
			}
			else
			{
				vcount2=0;
				flist_Count2=0;
				hpts2=new HPoint[vcount2];
				flist2=new int[flist_Count2];
			}

			if(vcount1==0 && flist_Count1==0)//If no shell is present in "added_shells" segment then
			{                               // to avoid shell in "subtracted_shells"  with only(-ve) facelist,   
				vcount1=vcount2;            // load this shell as added shell. 
				vcount2=0;
				flist_Count1=flist_Count2;
				flist_Count2=0;
				hpts1=new HPoint[vcount1];
				flist1=new int[flist_Count1];
				HC_Show_Shell(subtracted_shell_key,&vcount1,hpts1,&flist_Count1,flist1);	 

			} 

			//Merge the 2 shells manually(one with (+ve)facelist & one with(-ve)facelist) to create resultant shell. 
			int NewShell_vcount = vcount1 + vcount2;
			int NewShell_facecount = flist_Count1 + flist_Count2;

			HPoint *NewShell_Points = new HPoint[NewShell_vcount];
			int *NewShell_facelist = new int[NewShell_facecount];

			for(int i=0;i<vcount1;i++)
				NewShell_Points[i]=hpts1[i];
			for(int i=0;i<vcount2;i++)
				NewShell_Points[vcount1+i]=hpts2[i];

			delete[] hpts1; 
			delete[] hpts2; 
			int Shell_face_count=0;
			while(Shell_face_count<flist_Count2)
			{
				int i=0;
				int ncount= flist2[Shell_face_count]+1; 
				flist2[Shell_face_count]=flist2[Shell_face_count]*(-1);
				i++;			
				while(i<ncount)
				{
					flist2[Shell_face_count+i]=flist2[Shell_face_count+i]+vcount1;
					i++;
				}
				Shell_face_count=Shell_face_count+ncount;
			}	

			for(int i=0;i<flist_Count1;i++)
			{
				NewShell_facelist[i]=flist1[i];
			}

			for(int i=0;i<flist_Count2;i++)
			{
				NewShell_facelist[flist_Count1+i]=flist2[i];
			}

			delete[] flist1;	
			delete[] flist2;				

			HC_Open_Segment_By_Key(m_hkSegTobeUsed); 
				HC_KEY hkresultant_shellkey = HC_KInsert_Shell(NewShell_vcount,NewShell_Points,NewShell_facecount,NewShell_facelist);		
			HC_Close_Segment(); 

			delete[] NewShell_Points; 
			delete[] NewShell_facelist;

			HC_Open_Segment_By_Key(added_shells);
				HC_Flush_Contents(".","everything");
			HC_Close_Segment();

			HC_Open_Segment_By_Key(subtracted_shells);
				HC_Flush_Contents(".","everything");
			HC_Close_Segment();

		}//End of loop which loads m_iCellHeaderId.    

		delete[]CellHeaders;   
		HC_Delete_By_Key(added_shells);     
		HC_Delete_By_Key(subtracted_shells);

		HC_Open_Segment_By_Key(m_hkSolidSegKey);
			HC_Flush_Contents(".","everything");
		HC_Close_Segment();

		HC_Open_Segment_By_Key(m_hkHoleSegKey);
			HC_Flush_Contents(".","everything");
		HC_Close_Segment();	

		delete[] Shell_Elementid; 
		delete[] ShellArray;
		delete pl;		 
	}
}
//{
//				
//    int cnt= m_hashGeomCellID->Count();	
//	if(cnt>0)//if Cellheader 2d/3d contains solid/hole shapes then perform operation ,if it is empty then leave it.
//	{
//	VHash<HC_KEY,int>::PairList * pl = m_hashGeomCellID->GetPairList();   
//	HC_KEY *ShellArray=new HC_KEY[cnt];
//	int *Shell_Elementid=new int[cnt];
//	int ctr=0;
//	for(int i=0; i<(int)pl->Count(); i++)//load the vhash in to local data types
//	{
//		ShellArray[i] = pl->NthItem(i)->Key();
//		Shell_Elementid[i] = pl->NthItem(i)->Item();		
//	}
//  struct vlist_s * pCellidPointer= new_vlist(malloc, free);
//  START_LIST_ITERATION(int,  pCellidPointer)
//  delete temp;
//  END_LIST_ITERATION(pCellidPointer)
//  vlist_flush(pCellidPointer);
//  vlist_add_last(pCellidPointer,&Shell_Elementid[0]);
//  int nCount=0;
//   for(int i=1;i<cnt;i++)//The cellheader_id's No. in Shell_Elementid are coming repetedly for each shell.	               
//   {                     //Load them in to vlist in non repeated fashion. It will be easy to compare. 
//      bool bAddflag=true;
//	  int v1;
//      START_LIST_ITERATION(int,  pCellidPointer)
//      v1=*temp;
//      if(v1==Shell_Elementid[i]&&bAddflag==true)
//	  {
//		  bAddflag=false;		  
//	  }
//      END_LIST_ITERATION(pCellidPointer)
//	  if(bAddflag==true)
//      vlist_add_last(pCellidPointer,&Shell_Elementid[i]);  
//	  nCount=vlist_count(pCellidPointer);
//   }
//		  
//	int nindex=0;
//	nCount=vlist_count(pCellidPointer);
//	int *CellHeaders=new int[nCount];
//	START_LIST_ITERATION(int, pCellidPointer)//Load vlist into local data type array.
//	CellHeaders[nindex]=*temp;
//	nindex++;
//	END_LIST_ITERATION(pCellidPointer)
//    vlist_flush(pCellidPointer);	
//
//	HC_KEY added_shells_key= HC_KOpen_Segment("added_shells_key");//These 2 segments are required to load 
//	HC_Close_Segment();                                   //Shells to be added & sutracted.   
//	HC_KEY subtracted_shells= HC_KOpen_Segment("subtracted_shells");
//	HC_Close_Segment();
//	HC_KEY seg_key;
//
//	for(int i=0;i<nCount;i++)//Take each CellHeader id.  
//	   {
//		   int geo_count=0;
//		   for(int j=0;j<cnt;j++)//Load the Shells which are having same cellheader id's, 
//		   {                    // into 2 segments as per hole/solid.  
//			   if(CellHeaders[i]==Shell_Elementid[j])
//			   {
//				   HC_KEY Owner_Key=HC_KShow_Owner_By_Key(ShellArray[j]);
//					   if(Owner_Key==m_hkSolidSegKey)
//					   {
//                         seg_key=added_shells_key;
//					   }
//					   else if(Owner_Key==m_hkHoleSegKey)
//					   {
//                         seg_key=subtracted_shells;
//					   }
//					  
//                       HC_Open_Segment_By_Key(seg_key);
//				          HC_Copy_Geometry(ShellArray[j],"."); 						  
//				       HC_Close_Segment();
//					   HC_Delete_By_Key(ShellArray[j]);      
//					   geo_count++;
//			   }
//		   }
//		  char chTypeSearchName[MVO_BUFFER_SIZE];
//		  HC_KEY added_shell_key=INVALID_KEY;
//		  HC_KEY subtracted_shell_key=INVALID_KEY;
//		  HPoint added_shells_Max,added_shells_Min;
//		  HPoint subtracted_shells_Max,subtracted_shells_Min;
//
//		  HC_Open_Segment_By_Key(added_shells_key);//Merge all solid shells into one Shell.
//		   HUtility::Merge_Shells(true,true,true);
//			HC_Begin_Contents_Search (".","shell");
//			HC_Find_Contents (chTypeSearchName, &added_shell_key);	
//			HC_End_Contents_Search();
//			HC_Compute_Circumcuboid(".",&added_shells_Max,&added_shells_Min);
//		  HC_Close_Segment();
//		  float xdiff,ydiff,zdiff;
//		  xdiff=added_shells_Max.x-added_shells_Min.x;
//		  ydiff=added_shells_Max.y-added_shells_Min.y;
//		  zdiff=added_shells_Max.z-added_shells_Min.z;
//		  float added_shells_dist=sqrt((xdiff*xdiff)+(ydiff*ydiff)+(zdiff*zdiff));
//		  HC_Open_Segment_By_Key(subtracted_shells);//Merge all hole shells into one Shell.
//		   HUtility::Merge_Shells(true,true,true);
//			HC_Begin_Contents_Search (".","shell");
//			HC_Find_Contents (chTypeSearchName, &subtracted_shell_key);	
//			HC_End_Contents_Search();
//            HC_Compute_Circumcuboid(".",&subtracted_shells_Max,&subtracted_shells_Min);
//		  HC_Close_Segment(); 
//          xdiff=subtracted_shells_Max.x-subtracted_shells_Min.x;
//		  ydiff=subtracted_shells_Max.y-subtracted_shells_Min.y;
//		  zdiff=subtracted_shells_Max.z-subtracted_shells_Min.z;
//		  float subtracted_shells_dist=sqrt((xdiff*xdiff)+(ydiff*ydiff)+(zdiff*zdiff));
//		  if(subtracted_shells_dist>=added_shells_dist)
//		  {
//             HC_Open_Segment_By_Key(added_shells_key);
//				 HC_Copy_Geometry(subtracted_shell_key,".");
//				 HUtility::Merge_Shells(true,true,true);
//				 HC_Begin_Contents_Search (".","shell");
//				 HC_Find_Contents (chTypeSearchName, &added_shell_key);	
//				 HC_End_Contents_Search();
//			 HC_Close_Segment();
//
//			 HC_Open_Segment_By_Key(m_hkSegTobeUsed); 	
//				HC_Copy_Geometry(added_shell_key,".");
//			 HC_Close_Segment();  
//		  }
//		  else
//		  {
//			     int vcount1=0,flist_Count1=0,vcount2=0,flist_Count2=0;
//				 HPoint *hpts1, *hpts2;
//				 int *flist1, *flist2;	
//				 if(added_shell_key!=INVALID_KEY)//If no shell is present then  don't load the shell
//				 {
//				   HC_Show_Shell_Size(added_shell_key,&vcount1,&flist_Count1);		
//				   hpts1=new HPoint[vcount1];
//				   flist1=new int[flist_Count1];
//				   HC_Show_Shell(added_shell_key,&vcount1,hpts1,&flist_Count1,flist1);	  
//				 }
//				 else
//				 {
//					 vcount1=0;
//					 flist_Count1=0;
//					 hpts1=new HPoint[vcount1];
//					 flist1=new int[flist_Count1];
//				 }	 
//				
//				 if(subtracted_shell_key!=INVALID_KEY)//If no shell is present then  don't load the shell
//				 {
//				   HC_Show_Shell_Size(subtracted_shell_key,&vcount2,&flist_Count2);		
//				   hpts2=new HPoint[vcount2];
//				   flist2=new int[flist_Count2];
//				   HC_Show_Shell(subtracted_shell_key,&vcount2,hpts2,&flist_Count2,flist2);	   
//				 }
//				 else
//				 {
//					 vcount2=0;
//					 flist_Count2=0;
//					 hpts2=new HPoint[vcount2];
//					 flist2=new int[flist_Count2];
//				 }
//			  //    if(vcount1==0&&flist_Count1==0)//If no shell is present in "added_shells_key" segment then
//				 //{                               // to avoid shell in "subtracted_shells"  with only(-ve) facelist,   
//					// vcount1=vcount2;            // load this shell as added shell. 
//					// vcount2=0;
//					// flist_Count1=flist_Count2;
//					// flist_Count2=0;
//					// hpts1=new HPoint[vcount1];
//				 //    flist1=new int[flist_Count1];
//				 //    HC_Show_Shell(subtracted_shell_key,&vcount1,hpts1,&flist_Count1,flist1);	 
//
//				 //} 				 
//				 //Merge the 2 shells manually(one with (+ve)facelist & one with(-ve)facelist) to create resultant shell. 
//				 int NewShell_vcount=vcount1+vcount2;
//				 int NewShell_facecount=flist_Count1+flist_Count2;
//				 HPoint *NewShell_Points=new HPoint[NewShell_vcount];
//				 int *NewShell_facelist=new int[NewShell_facecount];
//				 for(int i=0;i<vcount1;i++)
//				  NewShell_Points[i]=hpts1[i];
//				 for(int i=0;i<vcount2;i++)
//				   NewShell_Points[vcount1+i]=hpts2[i];
//				 delete[] hpts1; 
//				 delete[] hpts2; 
//				 int Shell_face_count=0;
//				while(Shell_face_count<flist_Count2)
//				 {
//					  int i=0;
//					  int ncount= flist2[Shell_face_count]+1; 
//					  flist2[Shell_face_count]=flist2[Shell_face_count]*(-1);
//					  i++;			
//					  while(i<ncount)
//					  {
//						  flist2[Shell_face_count+i]=flist2[Shell_face_count+i]+vcount1;
//						  i++;
//					  }
//					   Shell_face_count=Shell_face_count+ncount;
//				 }	
//				 for(int i=0;i<flist_Count1;i++)
//				  NewShell_facelist[i]=flist1[i];
//				 for(int i=0;i<flist_Count2;i++)
//				   NewShell_facelist[flist_Count1+i]=flist2[i];
//				 delete[] flist1;	
//				 delete[] flist2;				
//
//				 HC_Open_Segment_By_Key(m_hkSegTobeUsed); 
//					 HC_KEY hkresultant_shellkey= HC_KInsert_Shell(NewShell_vcount,NewShell_Points,NewShell_facecount,NewShell_facelist);		
//				 HC_Close_Segment();  
//				  delete[] NewShell_Points; 
//				 delete[] NewShell_facelist;
//		  }
//		 HC_Open_Segment_By_Key(added_shells_key);
//		 HC_Flush_Contents(".","everything");
//	     HC_Close_Segment();
//		 HC_Open_Segment_By_Key(subtracted_shells);
//		 HC_Flush_Contents(".","everything");
//	     HC_Close_Segment();
//	   }//End of loop which loads m_iCellHeaderId.    
//	 delete[]CellHeaders;   
//     HC_Delete_By_Key(added_shells_key);     
//     HC_Delete_By_Key(subtracted_shells);
//	 HC_Open_Segment_By_Key(m_hkSolidSegKey);
//	 HC_Flush_Contents(".","everything");
//     HC_Close_Segment();
//	 HC_Open_Segment_By_Key(m_hkHoleSegKey);
//	 HC_Flush_Contents(".","everything");
//     HC_Close_Segment();	
//	 delete[] Shell_Elementid; 
//	 delete[] ShellArray;
//	 delete pl;		 
// }
//}
//This function copies the shell into m_hkSolidSegKey/m_hkHoleSegKey as per its hole flag & deletes the 
// previously created geometry. Ofcourse this previously created geometry is not required at all.
// Insert the newly copied geo. key & cellheader id in vhashlist. 
bool HDGNImporter::AddGeometryInList(bool bflag)
{
    if(m_hkShellKey!=INVALID_KEY)
	{
		HC_KEY hkGeoTobeCopied=INVALID_KEY;
		if(!bflag)
		{
			HC_Open_Segment_By_Key(m_hkSolidSegKey);
			hkGeoTobeCopied=HC_KCopy_Geometry(m_hkShellKey,".");
			HC_Close_Segment();
		}
		else
		{
           HC_Open_Segment_By_Key(m_hkHoleSegKey);
		   hkGeoTobeCopied=HC_KCopy_Geometry(m_hkShellKey,".");
		   HC_Close_Segment();
		}
	    m_hashGeomCellID->InsertItem(hkGeoTobeCopied,m_iCellHeaderId);
		m_hkSegTobeUsed=HC_KShow_Owner_By_Key(m_hkShellKey);
		HC_Delete_By_Key(m_hkShellKey);
		m_hkShellKey=INVALID_KEY;        
		return true;
	}
	return false;	
}

void CellHeader3d::import( OdRxObjectPtr object )
{

	char* levelName ;

	OdDgCellHeader3dPtr element = object;

	OdArray<shellStore> shells;
	OdWiresWorldGeometry wwd(shells);

	//Set to avoid the cash in worldDraw() function.
	//Please see the Issue No.13207 for more detail. 
	OdGiContextDumper ctx((OdDbDatabase*)element->database());
	wwd.setContext(&ctx);

	int elmID = getElementID(element);	
	
	m_iCellHeaderId=elmID;	
	
	OdString elmName = element->getName();
	int elmName_len = elmName.getLength();
	char* name = new char[elmName_len + 1];
	convertToCharArray(elmName, name);

	if(strcmp(name, "Smart Solid") == 0 || strcmp(name, "Feature Solid") == 0 || strcmp(name, "SMSLD ") == 0 )
	{
		char* segname = new char[strlen("_") + MAX_DIGIT_SIZE + elmName_len + 1];
		sprintf(segname, "%s_%d", name,elmID);

		H_SAFE_DELETE_ARRAY(name);

		if(m_bFromCellHeader == true && m_iCellHeaderOption == SINGLE_ENTITY_CELLHEADER)
		{
			if(element->getInvisibleFlag() == false /*&& getVisibilityOfLevel(element) == true*/ )
			{

				HC_Open_Segment(segname);
				{
					m_bFromSmartSolid = true;

					m_bWorldDrawEntityFlag=element->getHoleFlag();
					element->worldDraw(&wwd);				
					m_bWorldDrawEntityFlag=false;

					m_bFromSmartSolid = false;

					//HUtility::Merge_Shells(true, true, true, false);
					importXData(element->getXDataLinkage());
				}
				HC_Close_Segment();

			}
			H_SAFE_DELETE_ARRAY(segname);

			return;
		}

		OdRxObjectPtr child_object;

		//Get first child with attached attributes and get its material properties
		getFirstchildWithAttr(element->createIterator(), &child_object );

		OdDgGraphicsElementPtr child_elm;
		try
		{
			child_elm = (OdDgGraphicsElementPtr)child_object;
		}
		catch(...)
		{

		}
		if(!child_elm.isNull())
		{
			bool bIfptrRequired = 	getLevelName(child_elm, levelName);
			HC_Open_Segment(levelName);			
			{
				if(!bIfptrRequired)
					H_SAFE_DELETE_ARRAY(levelName);

				setLevelMaterialProperties(child_elm);

				//check visibility of level
				if(!getVisibilityOfLevel(child_object))
					HC_Set_Visibility("everything = off");

				HC_Open_Segment(segname);
				{
					if(element->getInvisibleFlag())
						HC_Set_Visibility("everything = off");

					setElementMaterialProperties( child_elm );

					m_bFromSmartSolid = true;
					m_bWorldDrawEntityFlag = element->getHoleFlag();		
					element->worldDraw(&wwd);
					m_bWorldDrawEntityFlag=false;
					//HUtility::Merge_Shells(true, true, true, false);
					m_bFromSmartSolid = false;

					importXData(element->getXDataLinkage());

					if(m_bFromCellHeader == true && m_iCellHeaderOption == BREAK_CELLHEADER)
						HC_Set_User_Options(m_cCellHeaderName);
				}
				HC_Close_Segment();

			}
			HC_Close_Segment();
		}

		H_SAFE_DELETE_ARRAY(segname);

	}
	else// This else block is for cell header element
	{
		H_SAFE_DELETE_ARRAY(name);

		//This block is for cell inside cell
		{
			if(m_bFromCellHeader == true /*&& m_iCellHeaderOption == SINGLE_ENTITY_CELLHEADER*/)
			{
				if(element->getInvisibleFlag() == false )
				{
					iterateElm(element->createIterator(), true, false,elmID);////passing elemid is required here to know the exact elmId of geometry.
				}

				return;
			}
		}

		//For Parent Cell Header flush out the list  
		
        m_hashGeomCellID->Flush();
		 

		if(m_iCellHeaderOption == SINGLE_ENTITY_CELLHEADER || m_iCellHeaderOption == OPT_CELLHEADER)
		{
			OdRxObjectPtr child_object;
			getFirstchildWithAttr(element->createIterator(), &child_object);
			OdDgGraphicsElementPtr child_elm;

			try
			{
				child_elm = (OdDgGraphicsElementPtr)child_object;
			}
			catch(...)
			{

			}

			if(!child_elm.isNull())
			{
				bool bIfptrRequired = getLevelName(child_elm, levelName);
			    HC_Open_Segment(levelName);			
			      {
				     if(!bIfptrRequired)
					     H_SAFE_DELETE_ARRAY(levelName);

					if(m_iCellHeaderOption ==SINGLE_ENTITY_CELLHEADER) 
						setLevelMaterialProperties(child_elm);

					//check visibility of level
					char segname[100];

					if(!getVisibilityOfLevel(child_object))
						HC_Set_Visibility("everything = off");

					sprintf(segname, "cellheader3d_%d", elmID);

					HC_Open_Segment(segname);
					{
						if(element->getInvisibleFlag())
							HC_Set_Visibility("everything = off");

						if(m_iCellHeaderOption ==SINGLE_ENTITY_CELLHEADER) 
							setElementMaterialProperties( child_elm );

						m_bCellHeaderHoleFlag = element->getHoleFlag(); 
												
						m_bFromCellHeader = true;
						//passing elemid is required here to know the exact elmId of geometry.
						iterateElm(element->createIterator(), true, false,elmID);
						if(m_bCellHeaderHoleFlag)//If cellheader has hole then only call the following function.
						{
							importCellheaderWithHoleAttr();
						}

						m_bFromCellHeader = false;

						m_bCellHeaderHoleFlag = false;
  
						HC_Optimize_Segment_Tree (".", "collapse matrices = on, reorganize=color= on");

					}
					HC_Close_Segment();
				}
				HC_Close_Segment();
			}
		}
		else if(m_iCellHeaderOption == BREAK_CELLHEADER)
		{
			if(element->getInvisibleFlag() == false)
			{
				if(m_bFromCellHeader == false)
				{
					int elmID = getElementID(element);
					sprintf(m_cCellHeaderName, "cellheader3d_%d", elmID);
				}
				m_bFromCellHeader = true;
				iterateElm(element->createIterator(), true, false);	
				m_bFromCellHeader = false;
			}
		}
	
	}
}

void CellHeader2d::import( OdRxObjectPtr object )
{
	char* levelName;

	OdDgCellHeader2dPtr element = object;

	OdArray<shellStore> shells;
	OdWiresWorldGeometry wwd(shells);

	int elmID = getElementID(element);	
	
	m_iCellHeaderId=elmID;	
	
	OdString elmName = element->getName();
	int elmName_len = elmName.getLength();
	char* name = new char[elmName_len + 1];
	convertToCharArray(elmName, name);

	if(strcmp(name, "Smart Solid") == 0 || strcmp(name, "Feature Solid") == 0 || strcmp(name, "SMSLD ") == 0 )
	{
		char* segname = new char[strlen("_") + MAX_DIGIT_SIZE + elmName_len + 1];
		sprintf(segname, "%s_%d", name,elmID);

		H_SAFE_DELETE_ARRAY(name);

		if(m_bFromCellHeader == true && m_iCellHeaderOption == SINGLE_ENTITY_CELLHEADER)
		{
			if(element->getInvisibleFlag() == false /*&& getVisibilityOfLevel(element) == true*/ )
			{

				HC_Open_Segment(segname);
				{
					m_bFromSmartSolid = true;
					m_bWorldDrawEntityFlag=element->getHoleFlag();
					element->worldDraw(&wwd);				
					m_bWorldDrawEntityFlag=false;
					m_bFromSmartSolid = false;
					//HUtility::Merge_Shells(true, true, true, false);
					importXData(element->getXDataLinkage());
				}
				HC_Close_Segment();
				
			}
			H_SAFE_DELETE_ARRAY(segname);

			return;
		}

		OdRxObjectPtr child_object;

		//Get first child with attached attributes and get its material properties
		getFirstchildWithAttr(element->createIterator(), &child_object );

		OdDgGraphicsElementPtr child_elm;
		try
		{
			child_elm = (OdDgGraphicsElementPtr)child_object;
		}
		catch(...)
		{

		}
		if(!child_elm.isNull())
		{
			bool bIfptrRequired = getLevelName(child_elm, levelName);
			HC_Open_Segment(levelName);			
			{
				if(!bIfptrRequired)
					H_SAFE_DELETE_ARRAY(levelName);

				setLevelMaterialProperties(child_elm);

				//check visibility of level
				if(!getVisibilityOfLevel(child_object))
					HC_Set_Visibility("everything = off");

				HC_Open_Segment(segname);
				{
					if(element->getInvisibleFlag())
						HC_Set_Visibility("everything = off");

					setElementMaterialProperties( child_elm );

					m_bFromSmartSolid = true;
					m_bWorldDrawEntityFlag = element->getHoleFlag();					
					element->worldDraw(&wwd);
					m_bWorldDrawEntityFlag=false;
					//HUtility::Merge_Shells(true, true, true, false);
					m_bFromSmartSolid = false;

					importXData(element->getXDataLinkage());

					if(m_bFromCellHeader == true && m_iCellHeaderOption == BREAK_CELLHEADER)
						HC_Set_User_Options(m_cCellHeaderName);
				}
				HC_Close_Segment();

			}
			HC_Close_Segment();
		}

		H_SAFE_DELETE_ARRAY(segname);

	}
	else// This else block is for cell header element
	{
		H_SAFE_DELETE_ARRAY(name);

		//This block is for cell inside cell
		{
			if(m_bFromCellHeader == true /*&& m_iCellHeaderOption == SINGLE_ENTITY_CELLHEADER*/)
			{
				if(element->getInvisibleFlag() == false )
				{
					iterateElm(element->createIterator(), true, false,elmID);////passing elemid is required here to know the exact elmId of geometry.
				}

				return;
			}
		}

		//For Parent Cell Header flush out the list  
         m_hashGeomCellID->Flush();

		if(m_iCellHeaderOption == SINGLE_ENTITY_CELLHEADER || m_iCellHeaderOption == OPT_CELLHEADER)
		{
			OdRxObjectPtr child_object;
			getFirstchildWithAttr(element->createIterator(), &child_object);
			OdDgGraphicsElementPtr child_elm;

			try
			{
				child_elm = (OdDgGraphicsElementPtr)child_object;
			}
			catch(...)
			{

			}

			if(!child_elm.isNull())
			{
				bool bIfptrRequired = getLevelName(child_elm, levelName);
			    HC_Open_Segment(levelName);			
			      {
				    if(!bIfptrRequired)
					  H_SAFE_DELETE_ARRAY(levelName);

					if(m_iCellHeaderOption ==SINGLE_ENTITY_CELLHEADER) 
						setLevelMaterialProperties(child_elm);

					//check visibility of level
					char segname[100];

					if(!getVisibilityOfLevel(child_object))
						HC_Set_Visibility("everything = off");

					sprintf(segname, "cellheader2d_%d", elmID);

					HC_Open_Segment(segname);
					{
						if(element->getInvisibleFlag())
							HC_Set_Visibility("everything = off");

						if(m_iCellHeaderOption ==SINGLE_ENTITY_CELLHEADER) 
							setElementMaterialProperties( child_elm );

						m_bCellHeaderHoleFlag = element->getHoleFlag(); 
												
						m_bFromCellHeader = true;
						//passing elemid is required here to know the exact elmId of geometry.
						iterateElm(element->createIterator(), true, false,elmID);
						if(m_bCellHeaderHoleFlag)//If cellheader has hole then only call the following function.
						{
							importCellheaderWithHoleAttr();
						}

						m_bFromCellHeader = false;

						m_bCellHeaderHoleFlag = false;
  
						HC_Optimize_Segment_Tree (".", "collapse matrices = on, reorganize=color= on");

					}
					HC_Close_Segment();
				}
				HC_Close_Segment();
			}
		}
		else if(m_iCellHeaderOption == BREAK_CELLHEADER)
		{
			if(element->getInvisibleFlag() == false)
			{
				if(m_bFromCellHeader == false)
				{
					int elmID = getElementID(element);
					sprintf(m_cCellHeaderName, "cellheader2d_%d", elmID);
				}
				m_bFromCellHeader = true;
				iterateElm(element->createIterator(), true, false);	
				m_bFromCellHeader = false;
			}
		}
	
	}
}


void Solid::import( OdRxObjectPtr object )
{
	OdDgSolidPtr element = object;
	int elmID = getElementID(element);

	char* segname = new char[strlen("plain_solid_") + MAX_DIGIT_SIZE + 1];
	sprintf(segname, "plain_solid_%d", elmID);

	if(m_bFromCellHeader == true && m_iCellHeaderOption == SINGLE_ENTITY_CELLHEADER)
	{
		if(!element->getInvisibleFlag())
		{
			OdArray<shellStore> shells;
			OdWiresWorldGeometry wwd(shells);
			HC_Open_Segment(segname);
			m_bWorldDrawEntityFlag=element->getHoleFlag();
			element->worldDraw(&wwd);
			m_bWorldDrawEntityFlag=false;
			//HUtility::Merge_Shells(true, true, true, false);
			importXData(element->getXDataLinkage());

			HC_Close_Segment();
		}
		return;
	}

	//iterator object itself points to the immediate child element 
	//so one need not call iterator->step(): Mustafa Bohari-[12-05-2008]

	//Get Solid's first child and get its material properties
	/*OdDgElementIteratorPtr iterator = element->createIterator();
	OdRxObjectPtr child_object = iterator->item().openObject();
	OdDgGraphicsElementPtr child_elm = child_object;*/ // Teigha

	char* levelName ;
	bool bIfptrRequired = getLevelName(element, levelName);
	HC_Open_Segment(levelName);			
	{
		if(!bIfptrRequired)
			H_SAFE_DELETE_ARRAY(levelName);
		setLevelMaterialProperties(element);//child_elm : Teigha

		//check visibility of level
		if(!getVisibilityOfLevel(object))//child_object : Teigha
			HC_Set_Visibility("everything = off");

		HC_Open_Segment(segname);
		{
			if(element->getInvisibleFlag())
				HC_Set_Visibility("everything = off");

			setElementMaterialProperties( element );//child_elm : Teigha

			OdArray<shellStore> shells;
			OdWiresWorldGeometry wwd(shells);
			m_bWorldDrawEntityFlag=element->getHoleFlag();
			element->worldDraw(&wwd);
			m_bWorldDrawEntityFlag=false;
			//HUtility::Merge_Shells(true, true, true, false);

			importXData(element->getXDataLinkage());

			if(m_bFromCellHeader == true && m_iCellHeaderOption == BREAK_CELLHEADER)
				HC_Set_User_Options(m_cCellHeaderName);
		}
		HC_Close_Segment();

	}
	HC_Close_Segment();
	H_SAFE_DELETE_ARRAY(segname);
}


void Surface::import( OdRxObjectPtr object )
{
	OdDgSurfacePtr element = object;
	int elmID = getElementID(element);

	char* segname = new char[strlen("surface_") + MAX_DIGIT_SIZE + 1];
	sprintf(segname, "surface_%d", elmID);

	if(m_bFromCellHeader == true && m_iCellHeaderOption == SINGLE_ENTITY_CELLHEADER)
	{
		if(!element->getInvisibleFlag())
		{
			OdArray<shellStore> shells;
			OdWiresWorldGeometry wwd(shells);
			HC_Open_Segment(segname);
			m_bWorldDrawEntityFlag=element->getHoleFlag();
			element->worldDraw(&wwd);
			m_bWorldDrawEntityFlag=false;
			//HUtility::Merge_Shells(true, true, true, false);
			importXData(element->getXDataLinkage());
			HC_Close_Segment();
		}
		return;
	}

	//iterator object itself points to the immediate child element 
	//so one need not call iterator->step(): Mustafa Bohari-[12-05-2008]

	//Get Surface's first child and get its material properties
	/*OdDgElementIteratorPtr iterator = element->createIterator();
	OdRxObjectPtr child_object = iterator->item().openObject();
	OdDgGraphicsElementPtr child_elm = child_object;*/ // Teigha

	char* levelName ;
	bool bIfptrRequired = getLevelName(element, levelName);
	HC_Open_Segment(levelName);			
	{
		if(!bIfptrRequired)
			H_SAFE_DELETE_ARRAY(levelName);
		setLevelMaterialProperties(element);//child_elm : Teigha

		if(!getVisibilityOfLevel(object))//child_object : Teigha
			HC_Set_Visibility("everything = off");

		HC_Open_Segment(segname);
		{
			if(element->getInvisibleFlag())
				HC_Set_Visibility("everything = off");

			setElementMaterialProperties( element );//child_elm : Teigha

			OdArray<shellStore> shells;
			OdWiresWorldGeometry wwd(shells);
			m_bWorldDrawEntityFlag=element->getHoleFlag();
			element->worldDraw(&wwd);
			m_bWorldDrawEntityFlag=false;
			//HUtility::Merge_Shells(true, true, true, false);

			importXData(element->getXDataLinkage());

			if(m_bFromCellHeader == true && m_iCellHeaderOption == BREAK_CELLHEADER)
				HC_Set_User_Options(m_cCellHeaderName);
		}
		HC_Close_Segment();
	}
	HC_Close_Segment();
    H_SAFE_DELETE_ARRAY(segname);
}


void Cone::import( OdRxObjectPtr object )
{

	OdDgConePtr element = object;
	{
		double r1 = element->getRadius1();
		//double r2 = element->getRadius2();
		//double avgr = (r1 + r2)/2;
		m_dDeviationForCone = r1/m_coneFactor;
		
	}
	int elmID = getElementID(element);

	char* segname = new char[strlen("cone_") + MAX_DIGIT_SIZE + 1];
	sprintf(segname, "cone_%d", elmID);

	if(m_bFromCellHeader == true && m_iCellHeaderOption == SINGLE_ENTITY_CELLHEADER)
	{
		if(!element->getInvisibleFlag())
		{
			OdArray<shellStore> shells;
			OdWiresWorldGeometry wwd(shells);
			HC_Open_Segment(segname);
			m_bWorldDrawEntityFlag=element->getHoleFlag();
			element->worldDraw(&wwd);
			m_bWorldDrawEntityFlag=false;
			//HUtility::Merge_Shells(true, true, true, false);

			importXData(element->getXDataLinkage());
			HC_Close_Segment();
		}
	}
	else
	{
		char* levelName;
		bool bIfptrRequired = getLevelName(element, levelName);
		HC_Open_Segment(levelName);			
		{
			if(!bIfptrRequired)
				H_SAFE_DELETE_ARRAY(levelName);
			setLevelMaterialProperties(element);
			if(!getVisibilityOfLevel(object))
				HC_Set_Visibility("everything = off");

			HC_Open_Segment(segname);
			{
				if(element->getInvisibleFlag())
					HC_Set_Visibility("everything = off");

				setElementMaterialProperties( element );

				OdArray<shellStore> shells;
				OdWiresWorldGeometry wwd(shells);
				m_bWorldDrawEntityFlag=element->getHoleFlag();
				element->worldDraw(&wwd);
				m_bWorldDrawEntityFlag=false;
				//HUtility::Merge_Shells(true, true, true, false);
				importXData(element->getXDataLinkage());

				if(m_bFromCellHeader == true && m_iCellHeaderOption == BREAK_CELLHEADER)
					HC_Set_User_Options(m_cCellHeaderName);
			}
			HC_Close_Segment();

		}
		HC_Close_Segment();
		H_SAFE_DELETE_ARRAY(segname); 
	}

	//as this is static reset it to 1 after done with cone import
	m_dDeviationForCone = 1;
}

void Mesh::import( OdRxObjectPtr object )
{

	OdDgMeshPtr element = object;
	int elmID = getElementID(element);
	
	char* segname = new char[strlen("Mesh_") + MAX_DIGIT_SIZE + 1];
	sprintf(segname, "Mesh_%d", elmID);

	if(m_bFromCellHeader == true && m_iCellHeaderOption == SINGLE_ENTITY_CELLHEADER)
	{
		if(!element->getInvisibleFlag())
		{
			OdArray<shellStore> shells;
			OdWiresWorldGeometry wwd(shells);
			HC_Open_Segment(segname);
			m_bWorldDrawEntityFlag = element->getHoleFlag();
			element->worldDraw(&wwd);
			m_bWorldDrawEntityFlag = false;
			//HUtility::Merge_Shells(true, true, true, false);
			importXData(element->getXDataLinkage());
			HC_Close_Segment();
		}
		return;
	}

	char* levelName;
	bool bIfptrRequired = getLevelName(element, levelName);
	HC_KEY dell =HC_KOpen_Segment(levelName);			
	{
		if(!bIfptrRequired)
			H_SAFE_DELETE_ARRAY(levelName);
		setLevelMaterialProperties(element);
		if(!getVisibilityOfLevel(object))
			HC_Set_Visibility("everything = off");

		HC_Open_Segment(segname);
		{
			if(element->getInvisibleFlag())
				HC_Set_Visibility("everything = off");

			setElementMaterialProperties( element );

			OdArray<shellStore> shells;
			OdWiresWorldGeometry wwd(shells);
			m_bWorldDrawEntityFlag=element->getHoleFlag();
			element->worldDraw(&wwd);
			m_bWorldDrawEntityFlag=false;
			//HUtility::Merge_Shells(true, true, true, false);

			importXData(element->getXDataLinkage());

			if(m_bFromCellHeader == true && m_iCellHeaderOption == BREAK_CELLHEADER)
				HC_Set_User_Options(m_cCellHeaderName);
		}
		HC_Close_Segment();
	}
	HC_Close_Segment();
	H_SAFE_DELETE_ARRAY(segname);
}


void ComplexShape::import( OdRxObjectPtr object )
{
	OdDgComplexShapePtr element = object;
	int elmID = getElementID(element);

	char* segname = new char[strlen("complex_shape_") + MAX_DIGIT_SIZE + 1];
	sprintf(segname, "complex_shape_%d",elmID); 
	bool isHole = element->getHoleFlag();


	if(m_bFromCellHeader == true && m_iCellHeaderOption == SINGLE_ENTITY_CELLHEADER)
	{
		if(!element->getInvisibleFlag())
		{
			OdArray<shellStore> shells;
			OdWiresWorldGeometry wwd(shells);
			m_hkShellKey=INVALID_KEY;
			HC_Open_Segment(segname);
			m_bWorldDrawEntityFlag=element->getHoleFlag();
			element->worldDraw(&wwd);
			m_bWorldDrawEntityFlag=false;			
			importXData(element->getXDataLinkage());
			HC_Close_Segment();
		}
		return;
	}

	char* levelName;
	bool bIfptrRequired = getLevelName(element, levelName);
	HC_Open_Segment(levelName);			
	{
		if(!bIfptrRequired)
			H_SAFE_DELETE_ARRAY(levelName);
		setLevelMaterialProperties(element);

		if(!getVisibilityOfLevel(object))
			HC_Set_Visibility("everything = off");

		HC_Open_Segment(segname);
		{
			if(element->getInvisibleFlag())
				HC_Set_Visibility("everything = off");

			setElementMaterialProperties(element);
			OdArray<shellStore> shells;
			OdWiresWorldGeometry wwd(shells);

			if(isHole == false)
			{   
				m_bWorldDrawEntityFlag=element->getHoleFlag();
				element->worldDraw(&wwd);
				m_bWorldDrawEntityFlag=false;
				//HUtility::Merge_Shells(true, true, true, false);
			}
			else if(isHole == true)
				iterateElm(element->createIterator(), false, false);

			importXData(element->getXDataLinkage());

			if(m_bFromCellHeader == true && m_iCellHeaderOption == BREAK_CELLHEADER)
				HC_Set_User_Options(m_cCellHeaderName);
		}
		HC_Close_Segment();
	}
	HC_Close_Segment();
    H_SAFE_DELETE_ARRAY(segname);
}

void Set_LStyle(int LStyle)
{
	switch(LStyle)
	{
	case 1:
		HC_Set_Line_Pattern("finedot");
		break;

	case 2:
		HC_Set_Line_Pattern(".");
		break;

	case 3:
		HC_Set_Line_Pattern("- ");
		break;

	case 4:
		{
			const char dgn_4_glyph[] = {5, 0, 0, 2, -3, 0, 1, 0, 1, 4,  0, 0};
			HC_Define_Glyph("dgn_4_glyph", sizeof(dgn_4_glyph),  dgn_4_glyph);
			HC_Define_Line_Style("dgn_4_line_style", "12 pixels dgn_4_glyph");
			HC_Set_Line_Pattern("dgn_4_line_style");
		}
		break;

	case 5:
		HC_Set_Line_Pattern("...");
		break;

	case 6:
		{
			const char dgn_6_glyph[] = {8, 0, 0, 2, -4, 0, 2, 0, 1, 5, 0, 1, 8, 0, 0};
			HC_Define_Glyph("dgn_6_glyph", sizeof(dgn_6_glyph),  dgn_6_glyph);
			HC_Define_Line_Style("dgn_6_line_style", "12 pixels dgn_6_glyph");
			HC_Set_Line_Pattern("dgn_6_line_style");
		}

		break;

	case 7:
		HC_Set_Line_Pattern(".-");
		break;


	}
}

inline void HDGNImporter::setLineStyleAndWt(OdDgGraphicsElementPtr grElm)
{
	OdUInt32 LStyle = grElm->getLineStyleEntryId();
	Set_LStyle(LStyle);
	OdUInt32 LWeight = grElm->getLineWeight();
	if(LWeight >= 0 && LWeight <= 31)
		HC_Set_Line_Weight(LWeight);
}

void Line2d::import( OdRxObjectPtr object )
{

	OdDgLine2dPtr element = object;
	OdGePoint2d   start_pt, end_pt;

	HPoint* h_line_pts = new HPoint[2];
	start_pt = element->getStartPoint( );
	end_pt = element->getEndPoint( );
	OdGePoint2d_2_HPoint(&start_pt, h_line_pts[0]);
	OdGePoint2d_2_HPoint(&end_pt, h_line_pts[1]);

	char* segname = new char[strlen("line2d_") + MAX_DIGIT_SIZE + 1];
	int elmID = getElementID(element);
	sprintf(segname, "line2d_%d",elmID); 


	if(m_bFromCellHeader == true && m_iCellHeaderOption == SINGLE_ENTITY_CELLHEADER)
	{
		if(!element->getInvisibleFlag())
		{
			HC_Open_Segment(segname);
			HC_Insert_Polyline(2, h_line_pts);
			HC_Close_Segment();
		}
		H_SAFE_DELETE_ARRAY(h_line_pts);
		return;
	}

	char* levelName;

	bool bIfptrRequired = getLevelName(element, levelName);
	HC_Open_Segment(levelName);			
	{
		if(!bIfptrRequired)
			H_SAFE_DELETE_ARRAY(levelName);
		setLevelMaterialProperties(element);

		if(!getVisibilityOfLevel(object))
			HC_Set_Visibility("everything = off");

		HC_Open_Segment(segname);
		{
			if(element->getInvisibleFlag())
				HC_Set_Visibility("everything = off");

			setElementMaterialProperties( element );

			HC_Insert_Polyline(2, h_line_pts);

			if(m_bFromCellHeader == false)
				setLineStyleAndWt(element);

			importXData(element->getXDataLinkage());

			if(m_bFromCellHeader == true && m_iCellHeaderOption == BREAK_CELLHEADER)
				HC_Set_User_Options(m_cCellHeaderName);

		}
		HC_Close_Segment();

	}
	HC_Close_Segment();

	H_SAFE_DELETE_ARRAY(h_line_pts);
    H_SAFE_DELETE_ARRAY(segname); 
}

void Line3d::import( OdRxObjectPtr object )
{

	OdDgLine3dPtr element = object;

	OdGePoint3d   start_pt, end_pt;

	HPoint* h_line_pts = new HPoint[2];
	start_pt = element->getStartPoint( );
	end_pt = element->getEndPoint( );
	OdGePoint3d_2_HPoint(&start_pt, h_line_pts[0]);
	OdGePoint3d_2_HPoint(&end_pt, h_line_pts[1]);

	char* segname = new char[strlen("line3d_") + MAX_DIGIT_SIZE + 1];
	int elmID = getElementID(element);
	sprintf(segname, "line3d_%d",elmID); 

	if(m_bFromCellHeader == true && m_iCellHeaderOption == SINGLE_ENTITY_CELLHEADER)
	{
		if(!element->getInvisibleFlag())
		{
			HC_Open_Segment(segname);
			HC_Insert_Polyline(2, h_line_pts);
			HC_Close_Segment();

		}
		H_SAFE_DELETE_ARRAY(h_line_pts);
		return;
	}

	char* levelName;

	bool bIfptrRequired = getLevelName(element, levelName);
	HC_Open_Segment(levelName);			
	{
		if(!bIfptrRequired)
			H_SAFE_DELETE_ARRAY(levelName);
		setLevelMaterialProperties(element);

		if(!getVisibilityOfLevel(object))
			HC_Set_Visibility("everything = off");



		HC_Open_Segment(segname);
		{
			if(element->getInvisibleFlag())
				HC_Set_Visibility("everything = off");

			setElementMaterialProperties( element );

			HC_Insert_Polyline(2, h_line_pts);

			if(m_bFromCellHeader == false)
				setLineStyleAndWt(element);

			importXData(element->getXDataLinkage());

			if(m_bFromCellHeader == true && m_iCellHeaderOption == BREAK_CELLHEADER)
				HC_Set_User_Options(m_cCellHeaderName);
		}
		HC_Close_Segment();

	}
	HC_Close_Segment();

	H_SAFE_DELETE_ARRAY(h_line_pts);
    H_SAFE_DELETE_ARRAY(segname);
}

void LineString2d::import( OdRxObjectPtr object )
{

	OdDgLineString2dPtr element = object;
	OdGePoint2d         point;
	int                 i, j = element->getVerticesCount();

	HPoint* h_line_pts = new HPoint[j];
	for( i = 0; i < j; i++ )
	{
		point = element->getVertexAt( i );

		OdGePoint2d_2_HPoint(&point, h_line_pts[i]);
	}

	char* segname = new char[strlen("lineString2d_") + MAX_DIGIT_SIZE + 1];
	int elmID = getElementID(element);
	sprintf(segname, "lineString2d_%d",elmID); 

	if(m_bFromCellHeader == true && m_iCellHeaderOption == SINGLE_ENTITY_CELLHEADER)
	{
		if(!element->getInvisibleFlag())
		{
			HC_Open_Segment(segname);
			HC_Insert_Polyline(j, h_line_pts);
			HC_Close_Segment();
		}
		H_SAFE_DELETE_ARRAY(h_line_pts);
		return;
	}

	char* levelName;

	bool bIfptrRequired = getLevelName(element, levelName);
	HC_Open_Segment(levelName);			
	{
		if(!bIfptrRequired)
			H_SAFE_DELETE_ARRAY(levelName);
		setLevelMaterialProperties(element);

		if(!getVisibilityOfLevel(object))
			HC_Set_Visibility("everything = off");

		HC_Open_Segment(segname);
		{
			if(element->getInvisibleFlag())
				HC_Set_Visibility("everything = off");

			setElementMaterialProperties(element);

			HC_Insert_Polyline(j, h_line_pts);

			if(m_bFromCellHeader == false)
				setLineStyleAndWt(element);

			importXData(element->getXDataLinkage());

			if(m_bFromCellHeader == true && m_iCellHeaderOption == BREAK_CELLHEADER)
				HC_Set_User_Options(m_cCellHeaderName);
		}
		HC_Close_Segment();
	}
	HC_Close_Segment();

	H_SAFE_DELETE_ARRAY(h_line_pts);
	H_SAFE_DELETE_ARRAY(segname);
}


void LineString3d::import( OdRxObjectPtr object )
{

	OdDgLineString3dPtr element = object;
	OdGePoint3d         point;
	int                 i, j = element->getVerticesCount();

	HPoint* h_line_pts = new HPoint[j];
	for( i = 0; i < j; i++ )
	{
		point = element->getVertexAt( i );

		OdGePoint3d_2_HPoint(&point, h_line_pts[i]);
	}

	char* segname = new char[strlen("lineString3d_") + MAX_DIGIT_SIZE + 1];
	int elmID = getElementID(element);
	sprintf(segname, "lineString3d_%d",elmID); 


	if(m_bFromCellHeader == true && m_iCellHeaderOption == SINGLE_ENTITY_CELLHEADER)
	{
		if(!element->getInvisibleFlag())
		{
			HC_Open_Segment(segname);
			HC_Insert_Polyline(j, h_line_pts);
			HC_Close_Segment();
		}
		H_SAFE_DELETE_ARRAY(h_line_pts);
		return;
	}

	char* levelName;

	bool bIfptrRequired = getLevelName(element, levelName);
	HC_Open_Segment(levelName);			
	{
		if(!bIfptrRequired)
			H_SAFE_DELETE_ARRAY(levelName);
		setLevelMaterialProperties(element);

		if(!getVisibilityOfLevel(object))
			HC_Set_Visibility("everything = off");


		HC_Open_Segment(segname);
		{
			if(element->getInvisibleFlag())
				HC_Set_Visibility("everything = off");

			setElementMaterialProperties(element);

			HC_Insert_Polyline(j, h_line_pts);

			if(m_bFromCellHeader == false)
				setLineStyleAndWt(element);

			importXData(element->getXDataLinkage());

			if(m_bFromCellHeader == true && m_iCellHeaderOption == BREAK_CELLHEADER)
				HC_Set_User_Options(m_cCellHeaderName);
		}
		HC_Close_Segment();
	}
	HC_Close_Segment();

	H_SAFE_DELETE_ARRAY(h_line_pts);
	H_SAFE_DELETE_ARRAY(segname);
}

void Shape2d::import( OdRxObjectPtr object )
{

	OdDgShape2dPtr element = object;
	OdGePoint2d         point;
	int                 i, j = element->getVerticesCount();

	HPoint* h_line_pts = new HPoint[j];
	for( i = 0; i < j; i++ )
	{
		point = element->getVertexAt( i );

		OdGePoint2d_2_HPoint(&point, h_line_pts[i]);
	}

	char* segname = new char[strlen("shape2d_") + MAX_DIGIT_SIZE + 1];
	int elmID = getElementID(element);
	sprintf(segname, "shape2d_%d",elmID); 

	if(m_bFromCellHeader == true && m_iCellHeaderOption == SINGLE_ENTITY_CELLHEADER)
	{
		if(!element->getInvisibleFlag())
		{
			HC_Open_Segment(segname);
			{
				//It seems that in Microstation, shapes are always closed elements and by rule that all closed 
				//elements are drawn filled in shaded mode in Microstation, I am not paying any heed to ishole 
				//property and inserting them as polygons: Mustafa Bohari[2-12-2008]

				//HC_Insert_Polygon(j, h_line_pts);
                HC_KEY hkPolygon_Key =  HC_KInsert_Polygon(j, h_line_pts);
			   if(m_bCellHeaderHoleFlag && hkPolygon_Key != -1)//If Cell header has hole then convert this geometry into shell.
				{
				   m_hkShellKey=HC_Generate_Shell_From_Geometry(hkPolygon_Key,"");
				   HC_Delete_By_Key(hkPolygon_Key);
				   AddGeometryInList(element->getHoleFlag());
				}         
			}
			HC_Close_Segment();

		}

		H_SAFE_DELETE_ARRAY(h_line_pts);
		return;
	}

	char* levelName;

	bool bIfptrRequired = getLevelName(element, levelName);
	HC_Open_Segment(levelName);			
	{
		if(!bIfptrRequired)
			H_SAFE_DELETE_ARRAY(levelName);
		setLevelMaterialProperties(element);

		if(!getVisibilityOfLevel(object))
			HC_Set_Visibility("everything = off");

		HC_Open_Segment(segname);
		{
			if(element->getInvisibleFlag())
				HC_Set_Visibility("everything = off");

			setElementMaterialProperties(element);

			//It seems that in Microstation, shapes are always closed elements and by rule that all closed 
			//elements are drawn filled in shaded mode in Microstation, I am not paying any heed to ishole 
			//property and inserting them as polygons: Mustafa Bohari[2-12-2008]

			 HC_Insert_Polygon(j, h_line_pts);
			
			if(m_bFromCellHeader == false)
				setLineStyleAndWt(element);

			importXData(element->getXDataLinkage());

			if(m_bFromCellHeader == true && m_iCellHeaderOption == BREAK_CELLHEADER)
				HC_Set_User_Options(m_cCellHeaderName);
		}
		HC_Close_Segment();
	}
	HC_Close_Segment();

	H_SAFE_DELETE_ARRAY(h_line_pts);
	H_SAFE_DELETE_ARRAY(segname);
}

void Shape3d::import( OdRxObjectPtr object )
{

	OdDgShape3dPtr element = object;
	OdGePoint3d         point;
	int                 i, j = element->getVerticesCount();

	HPoint* h_line_pts = new HPoint[j];
	for( i = 0; i < j; i++ )
	{
		point = element->getVertexAt( i );

		OdGePoint3d_2_HPoint(&point, h_line_pts[i]);
	}
	char* segname = new char[strlen("shape3d_") + MAX_DIGIT_SIZE + 1];
	int elmID = getElementID(element);
	sprintf(segname, "shape3d_%d",elmID); 


	if(m_bFromCellHeader == true && m_iCellHeaderOption == SINGLE_ENTITY_CELLHEADER)
	{
		if(!element->getInvisibleFlag())
		{
			HC_Open_Segment(segname);
			{

				//It seems that in Microstation, shapes are always closed elements and by rule that all closed 
				//elements are drawn filled in shaded mode in Microstation, I am not paying any heed to ishole 
				//property and inserting them as polygons: Mustafa Bohari[2-12-2008]

				HC_KEY hkPolygon_Key = HC_KInsert_Polygon(j, h_line_pts);
				 if(m_bCellHeaderHoleFlag == true && hkPolygon_Key != -1)//If Cell header has hole then convert this geometry into shell.
					{
					   m_hkShellKey=HC_Generate_Shell_From_Geometry(hkPolygon_Key,"");
					   HC_Delete_By_Key(hkPolygon_Key);
					   AddGeometryInList(element->getHoleFlag());
					}  
			}
			HC_Close_Segment();

		}
		H_SAFE_DELETE_ARRAY(h_line_pts);
		return;
	}

	char* levelName;

	bool bIfptrRequired = getLevelName(element, levelName);
	HC_Open_Segment(levelName);			
	{
		if(!bIfptrRequired)
			H_SAFE_DELETE_ARRAY(levelName);
		setLevelMaterialProperties(element);

		if(!getVisibilityOfLevel(object))
			HC_Set_Visibility("everything = off");

		HC_Open_Segment(segname);
		{
			if(element->getInvisibleFlag())
				HC_Set_Visibility("everything = off");

			setElementMaterialProperties(element);


			//It seems that in Microstation, shapes are always closed elements and by rule that all closed 
			//elements are drawn filled in shaded mode in Microstation, I am not paying any heed to ishole 
			//property and inserting them as polygons: Mustafa Bohari[2-12-2008]

		 HC_Insert_Polygon(j, h_line_pts);
			
          
			if(m_bFromCellHeader == false)
				setLineStyleAndWt(element);

			importXData(element->getXDataLinkage());

			if(m_bFromCellHeader == true && m_iCellHeaderOption == BREAK_CELLHEADER)
				HC_Set_User_Options(m_cCellHeaderName);
		}
		HC_Close_Segment();
	}
	HC_Close_Segment();

	H_SAFE_DELETE_ARRAY(h_line_pts);
    H_SAFE_DELETE_ARRAY(segname);
}

void Arc2d::importAsEllipticalArc(OdGeEllipArc2d ellipArc, double rot_angle, bool isClosed)
{
	OdGePoint2d centre =ellipArc.center();
	HPoint horigin[1];
	OdGePoint2d_2_HPoint(&centre, horigin[0]);

	OdGeVector2d major_axis = ellipArc.majorAxis();
	OdGeVector2d minor_axis = ellipArc.minorAxis();
	double major_radius = ellipArc.majorRadius();
	double minor_radius = ellipArc.minorRadius();

	float major_intersection[3];
	float minor_intersection[3];

	if(m_bNoOffset == false)
	{
		major_intersection[0] = ((float)(centre.x + major_axis.x*major_radius)) - m_dMinX; 
		major_intersection[1] = ((float)(centre.y + major_axis.y*major_radius)) - m_dMinY; 
		major_intersection[2] = 0.0f ;

		minor_intersection[0] = ((float)(centre.x + minor_axis.x*minor_radius)) - m_dMinX; 
		minor_intersection[1] = ((float)(centre.y + minor_axis.y*minor_radius)) - m_dMinY;
		minor_intersection[2] = 0.0f;
	}
	else
	{
		major_intersection[0] = centre.x + major_axis.x*major_radius;
		major_intersection[1] = centre.y + major_axis.y*major_radius;
		major_intersection[2] = 0.0f;

		minor_intersection[0] = centre.x + minor_axis.x*minor_radius;
		minor_intersection[1] = centre.y + minor_axis.y*minor_radius; 
		minor_intersection[2] = 0.0f;
	}

	double start_angle = (ellipArc.startAng())/(2*H_PI);
	double end_angle = (ellipArc.endAng())/(2*H_PI);
	//No need to apply in modification of start_angle & end_angle is required here because the horigin, start_angle,end_angle
	//major_intersection, minor_intersection parameters get automatically modified in dgn when rotation is applied.

	/*start_angle = start_angle + rot_angle;
	end_angle = end_angle + rot_angle;*/

	while(start_angle<0)	
		start_angle = 1 + start_angle;

	while(end_angle > 1)
		end_angle =  end_angle - 1;

	//Here check is required for start_angle to be >1 & end_angle to be <1.(0-1means 0 to 360 degrees)
	while(start_angle > 1)	
		start_angle = start_angle-1;

	while(end_angle < 0)	
		end_angle = 1+ end_angle;

	if(isClosed)
	{
	  HC_KEY hkEllipseKey = HC_KInsert_Ellipse(horigin, major_intersection, minor_intersection);
	  if(m_bCellHeaderHoleFlag && hkEllipseKey != -1)//If Cell header has hole then convert this geometry into shell.
		{
		   m_hkShellKey=HC_Generate_Shell_From_Geometry(hkEllipseKey,"");
		   HC_Delete_By_Key(hkEllipseKey);			   
		}    
	}
	else
	{
		if(start_angle != end_angle)
			HC_Insert_Elliptical_Arc(horigin, major_intersection, minor_intersection, start_angle, end_angle);
	}
}

void Arc3d::importAsEllipticalArc(OdGeEllipArc3d ellipArc, bool isClosed)
{
	OdGePoint3d centre =ellipArc.center();
	HPoint horigin[1];
	OdGePoint3d_2_HPoint(&centre, horigin[0]);

	OdGeVector3d major_axis = ellipArc.majorAxis();

	OdGeVector3d minor_axis = ellipArc.minorAxis();
	double major_radius = ellipArc.majorRadius();
	double minor_radius = ellipArc.minorRadius();

	float major_intersection[3];
	float minor_intersection[3];


	if( m_bNoOffset == false)
	{
		major_intersection[0] = ((float)(centre.x + major_axis.x*major_radius)) - m_dMinX;
		major_intersection[1] = ((float)(centre.y + major_axis.y*major_radius)) - m_dMinY; 
		major_intersection[2] = ((float)(centre.z + major_axis.z*major_radius)) - m_dMinZ;

		minor_intersection[0] = ((float)(centre.x + minor_axis.x*minor_radius)) - m_dMinX;
		minor_intersection[1] = ((float)(centre.y + minor_axis.y*minor_radius)) - m_dMinY;
		minor_intersection[2] = ((float)(centre.z + minor_axis.z*minor_radius)) - m_dMinZ;
	}
	else
	{
		major_intersection[0] = ((float)(centre.x + major_axis.x*major_radius)) ;
		major_intersection[1] = ((float)(centre.y + major_axis.y*major_radius));
		major_intersection[2] = ((float)(centre.z + major_axis.z*major_radius)) ;

		minor_intersection[0] = ((float)(centre.x + minor_axis.x*minor_radius)) ;
		minor_intersection[1] = ((float)(centre.y + minor_axis.y*minor_radius));
		minor_intersection[2] = ((float)(centre.z + minor_axis.z*minor_radius));

	}

	double start_angle = (ellipArc.startAng())/(2*H_PI);
	double end_angle = (ellipArc.endAng())/(2*H_PI);

	while(start_angle < 0)
		start_angle = 1 + start_angle;

	while(end_angle > 1)
		end_angle =  end_angle - 1;

	//Here check is required for start_angle to be >1 & end_angle to be <1.(0-1means 0 to 360 degrees).
	//while loop is rquired because the angle may be greater than 720 degrees.
	while(start_angle > 1)
		start_angle = start_angle-1;

	while(end_angle < 0)
		end_angle = 1+ end_angle;

	if(isClosed)
	{
	 HC_KEY hkEllipseKey = HC_KInsert_Ellipse(horigin, major_intersection, minor_intersection);
     if(m_bCellHeaderHoleFlag && hkEllipseKey != -1)//If Cell header has hole then convert this geometry into shell.
		{
		   m_hkShellKey=HC_Generate_Shell_From_Geometry(hkEllipseKey,"");
		   HC_Delete_By_Key(hkEllipseKey);			   
		}    
	} 
	else
	{
		if(start_angle != end_angle)
			HC_Insert_Elliptical_Arc(horigin, major_intersection, minor_intersection, start_angle, end_angle);
	}

}



void Arc2d::import( OdRxObjectPtr object )
{

	OdDgArc2dPtr element = object;
	OdGeEllipArc2d ellipArc = element->getEllipArc();
	double rot_angle = element->getRotationAngle();
	rot_angle = rot_angle/(2 * H_PI);


	char* segname = new char[strlen("arc2d_") + MAX_DIGIT_SIZE + 1];
	int elmID = getElementID(element);
	sprintf(segname, "arc2d_%d",elmID);

	if(m_bFromCellHeader == true && m_iCellHeaderOption == SINGLE_ENTITY_CELLHEADER)
	{
		if(!element->getInvisibleFlag())
		{
			HC_Open_Segment(segname);
			importAsEllipticalArc(ellipArc, rot_angle, false);
			HC_Close_Segment();
			/*if(m_bCellHeaderHoleFlag)
			 AddGeometryInList(element->getHoleFlag());*/
		}
		return;
	}

	char* levelName ;
	bool bIfptrRequired = getLevelName(element, levelName);
	HC_Open_Segment(levelName);			
	{
		if(!bIfptrRequired)
			H_SAFE_DELETE_ARRAY(levelName);
		setLevelMaterialProperties(element);

		if(!getVisibilityOfLevel(object))
			HC_Set_Visibility("everything = off");

		HC_Open_Segment(segname);
		{
			if(element->getInvisibleFlag())
				HC_Set_Visibility("everything = off");
			setElementMaterialProperties(element);

			importAsEllipticalArc(ellipArc, rot_angle, false);

			if(m_bFromCellHeader == false)
				setLineStyleAndWt(element);

			importXData(element->getXDataLinkage());

			if(m_bFromCellHeader == true && m_iCellHeaderOption == BREAK_CELLHEADER)
				HC_Set_User_Options(m_cCellHeaderName);
		}
		HC_Close_Segment();

		HC_Close_Segment();
	}
    H_SAFE_DELETE_ARRAY(segname);
}

void Arc3d::import( OdRxObjectPtr object )
{

	OdDgArc3dPtr element = object;
	OdGeEllipArc3d ellipArc = element->getEllipArc();

	char* segname = new char[strlen("arc3d_") + MAX_DIGIT_SIZE + 1];
	int elmID = getElementID(element);
	sprintf(segname, "arc3d_%d",elmID); 

	if(m_bFromCellHeader == true && m_iCellHeaderOption == SINGLE_ENTITY_CELLHEADER)
	{
		if(!element->getInvisibleFlag())
		{
			HC_Open_Segment(segname);
			importAsEllipticalArc(ellipArc, false);
			HC_Close_Segment();
			/*if(m_bCellHeaderHoleFlag)
			 AddGeometryInList(element->getHoleFlag());*/
		}
		return;
	}

	char* levelName;
	bool bIfptrRequired = getLevelName(element, levelName);
	HC_Open_Segment(levelName);			
	{
		if(!bIfptrRequired)
			H_SAFE_DELETE_ARRAY(levelName);
		setLevelMaterialProperties(element);

		if(!getVisibilityOfLevel(object))
			HC_Set_Visibility("everything = off");


		HC_Open_Segment(segname);
		{
			if(element->getInvisibleFlag())
				HC_Set_Visibility("everything = off");

			setElementMaterialProperties(element);

			importAsEllipticalArc(ellipArc, false);

			if(m_bFromCellHeader == false)
				setLineStyleAndWt(element);

			importXData(element->getXDataLinkage());

			if(m_bFromCellHeader == true && m_iCellHeaderOption == BREAK_CELLHEADER)
				HC_Set_User_Options(m_cCellHeaderName);
		}
		HC_Close_Segment();


	}
	HC_Close_Segment();
    H_SAFE_DELETE_ARRAY(segname);
}

void Ellipse2d::import( OdRxObjectPtr object )
{

	OdDgEllipse2dPtr element = object;
	OdGeEllipArc2d ellipArc;
	ellipArc = element->getEllipArc( );
	double rot_angle = element->getRotationAngle();
	rot_angle = rot_angle/(2 * H_PI);

	char* segname = new char[strlen("ellipse2d_") + MAX_DIGIT_SIZE + 1];
	int elmID = getElementID(element);
	sprintf(segname, "ellipse2d_%d",elmID); 

	if(HDGNImporter::m_bFromCellHeader == true && m_iCellHeaderOption == SINGLE_ENTITY_CELLHEADER)
	{
		if(!element->getInvisibleFlag())
		{
			HC_Open_Segment(segname);
			importAsEllipticalArc(ellipArc, rot_angle, true);
			HC_Close_Segment();
			if(m_bCellHeaderHoleFlag)
				HDGNImporter::AddGeometryInList(element->getHoleFlag());
		}
		return;
	}

	char* levelName;
	bool bIfptrRequired = getLevelName(element, levelName);
	HC_Open_Segment(levelName);			
	{
		if(!bIfptrRequired)
			H_SAFE_DELETE_ARRAY(levelName);
		setLevelMaterialProperties(element);

		if(!getVisibilityOfLevel(object))
			HC_Set_Visibility("everything = off");

		HC_Open_Segment(segname);
		{
			if(element->getInvisibleFlag())
				HC_Set_Visibility("everything = off");

			setElementMaterialProperties(element);

			importAsEllipticalArc(ellipArc, rot_angle, true);

			if(HDGNImporter::m_bFromCellHeader == false)
				HDGNImporter::setLineStyleAndWt(element);

			HDGNImporter::importXData(element->getXDataLinkage());

			if(HDGNImporter::m_bFromCellHeader == true && m_iCellHeaderOption == BREAK_CELLHEADER)
				HC_Set_User_Options(m_cCellHeaderName);
		}
		HC_Close_Segment();
	}
	HC_Close_Segment();
    H_SAFE_DELETE_ARRAY(segname);
}

void Ellipse3d::import( OdRxObjectPtr object )
{

	OdDgEllipse3dPtr element = object;

	OdGeEllipArc3d ellipArc = element->getEllipArc();

	char* segname = new char[strlen("ellipse3d_") + MAX_DIGIT_SIZE + 1];
	int elmID = getElementID(element);
	sprintf(segname, "ellipse3d_%d",elmID); 

	if(HDGNImporter::m_bFromCellHeader == true && m_iCellHeaderOption == SINGLE_ENTITY_CELLHEADER)
	{
		if(!element->getInvisibleFlag())
		{
			HC_Open_Segment(segname);
			importAsEllipticalArc(ellipArc, true);
			HC_Close_Segment();
			if(m_bCellHeaderHoleFlag)
				HDGNImporter::AddGeometryInList(element->getHoleFlag());
		}
		return;
	}

	char* levelName;
	bool bIfptrRequired = getLevelName(element, levelName);
	HC_Open_Segment(levelName);			
	{
		if(!bIfptrRequired)
			H_SAFE_DELETE_ARRAY(levelName);
		setLevelMaterialProperties(element);

		if(!getVisibilityOfLevel(object))
			HC_Set_Visibility("everything = off");

		HC_Open_Segment(segname);
		{
			if(element->getInvisibleFlag())
				HC_Set_Visibility("everything = off");

			setElementMaterialProperties(element);

			importAsEllipticalArc(ellipArc, true);

			if(HDGNImporter::m_bFromCellHeader == false)
				HDGNImporter::setLineStyleAndWt(element);

			HDGNImporter::importXData(element->getXDataLinkage());

			if(HDGNImporter::m_bFromCellHeader == true && m_iCellHeaderOption == BREAK_CELLHEADER)
				HC_Set_User_Options(m_cCellHeaderName);
		}
		HC_Close_Segment();
	}
	HC_Close_Segment();
    H_SAFE_DELETE_ARRAY(segname);
}

void BSpline::getUniformKnots(bool isClosed, int totalKnots, int order, float*& hKnots)
{
	//if knotCount == 0, then spline is uniform and we will have to deduce knots ourself 
	//rule is-
	//open splines: Leading and trailing knot vectors have multiplicity = order
	//closed splines: the first [order] steps (between knots) and last [order] steps are equal
	// for example, to construct knots vector for a spline with 5 poles and order = 3, we could build 'some like Microstation does':
	//for an open spline: 0 0 0 1 2 3 3 3
	//for closed spline: 0 1 2 3 4 5 6 7 8 9. -Mustafa Bohari[19-MAY-2008]

	//float* hKnots = new float[totalKnots];
	if(isClosed)
	{
		for( int i = 0; i < totalKnots; i++)
			hKnots[i] = i;
	}
	else
	{
		for( int i = 0; i < order; i++)
			hKnots[i] = 0;

		int penultimateKnot = 0;
		for(int i = 1; i <= (totalKnots - (2*order)); i++)
		{
			hKnots[order + i - 1] = i;
			penultimateKnot = i;
		}

		for( int i = 0; i < order; i++)
		{
			hKnots[totalKnots - 1 - i] = penultimateKnot + 1;
		}

	}
}

void BSplineCurve2d::import( OdRxObjectPtr object )
{

	OdDgBSplineCurve2dPtr element = object;
	char* segname = new char[strlen("BSpline_curve2d_") + MAX_DIGIT_SIZE + 1];
	char* levelName;

	if(m_bFromCellHeader == false || m_iCellHeaderOption != SINGLE_ENTITY_CELLHEADER)
	{
		bool bIfptrRequired = getLevelName(element, levelName);
		HC_Open_Segment(levelName);			
		if(!bIfptrRequired)
				H_SAFE_DELETE_ARRAY(levelName);
	}
	{
		if(m_bFromCellHeader == false || m_iCellHeaderOption != SINGLE_ENTITY_CELLHEADER)
		{
			setLevelMaterialProperties(element);

			if(!getVisibilityOfLevel(object))
				HC_Set_Visibility("everything = off");

		}
		int elmID = getElementID(element);
		sprintf(segname, "BSpline_curve2d_%d",elmID); 
		HC_Open_Segment(segname);
		{
			if(m_bFromCellHeader == false || m_iCellHeaderOption != SINGLE_ENTITY_CELLHEADER)
			{
				if(element->getInvisibleFlag())
					HC_Set_Visibility("everything = off");

				setElementMaterialProperties(element);
			}
			OdUInt8 order = element->getOrder();
			int degree = order - 1;
			OdUInt32 poleCount = element->getPolesCount();
			HPoint* hPoles = 0;

			bool isClosed = element->getClosedFlag();
			int pole_counter = poleCount;

			if(isClosed)
			{
				poleCount =  poleCount + degree;
			}

			unsigned int totalKnots = order + poleCount;

			//Get Poles
			hPoles = new HPoint[poleCount];

			for(int i = 0; i < pole_counter; i++)
			{
				OdGePoint2d poles =	element->getPole(i);
				OdGePoint2d_2_HPoint(&poles, hPoles[i]); 
			}

			//A periodic B-spline is a B-spline which closes on itself. This requires that the first degree(n) control points are
			//identical to the last n, and the first n parameter intervals in the knot vector are identical to the last n
			//intervals
			//If B-spline is closed then add the first (order-1) poles to the end
			// this makes the curve closed : Mustafa Bohari[16-MAY-2008]
			if(isClosed)
			{
				for( int i = 0; i < degree; i++)
				{
					OdGePoint2d poles =	element->getPole(i);
					OdGePoint2d_2_HPoint(&poles, hPoles[pole_counter + i]) ;
				}

			}

			//Get knots
			OdUInt32 knotCount = element->getKnotsCount();
			float* hKnots = new float[totalKnots];

			if(knotCount == 0 || knotCount < totalKnots)
			{
				getUniformKnots(isClosed, totalKnots, order, hKnots);
			}
			else
			{
				for (unsigned int i = 0; i < totalKnots; i++)
				{
					hKnots[i] = element->getKnot(i);
				}
			}

			bool isRational = element->getRationalFlag();
			float* hWeights = 0;
			if(isRational)
			{
				hWeights= new float[poleCount];
				for(unsigned int i = 0; i < poleCount; i++)
				{
					hWeights[i] = element->getWeight(i);
				}
			}

			HC_Insert_NURBS_Curve ( degree, poleCount, hPoles, hWeights, hKnots, 0, 1);

			H_SAFE_DELETE_ARRAY(hPoles);
			H_SAFE_DELETE_ARRAY(hKnots);
			H_SAFE_DELETE_ARRAY(hWeights);

			importXData(element->getXDataLinkage());

			if(m_bFromCellHeader == true && m_iCellHeaderOption == BREAK_CELLHEADER)
				HC_Set_User_Options(m_cCellHeaderName);

		}
		HC_Close_Segment();
	}
	if(m_bFromCellHeader == false || m_iCellHeaderOption != SINGLE_ENTITY_CELLHEADER)
		HC_Close_Segment();
	H_SAFE_DELETE_ARRAY(segname);
}

void BSplineCurve3d::import( OdRxObjectPtr object )
{

	OdDgBSplineCurve3dPtr element = object;
	char* segname = new char[strlen("BSpline_curve3d_") + MAX_DIGIT_SIZE + 1];
	char* levelName;
	if(m_bFromCellHeader == false || m_iCellHeaderOption != SINGLE_ENTITY_CELLHEADER)
	{
		bool bIfptrRequired = getLevelName(element, levelName);
		HC_Open_Segment(levelName);		
		if(!bIfptrRequired)
			H_SAFE_DELETE_ARRAY(levelName);
	}
	{
		if(m_bFromCellHeader == false || m_iCellHeaderOption != SINGLE_ENTITY_CELLHEADER)
		{
			setLevelMaterialProperties(element);

			if(!getVisibilityOfLevel(object))
				HC_Set_Visibility("everything = off");

		}
		int elmID = getElementID(element);
		sprintf(segname, "BSpline_curve3d_%d",elmID); 
		HC_Open_Segment(segname);
		{
			if(m_bFromCellHeader == false || m_iCellHeaderOption != SINGLE_ENTITY_CELLHEADER)
			{
				if(element->getInvisibleFlag())
					HC_Set_Visibility("everything = off");

				setElementMaterialProperties(element);
			}

			OdUInt8 order = element->getOrder();
			int degree = order - 1;

			OdUInt32 poleCount = element->getPolesCount();
			HPoint* hPoles = 0;

			bool isClosed = element->getClosedFlag();
			int pole_counter = poleCount;
			if(isClosed)
			{
				poleCount =  poleCount + degree;
			}

			unsigned int totalKnots = order + poleCount;

			hPoles = new HPoint[poleCount];

			for(int i = 0; i < pole_counter; i++)
			{
				OdGePoint3d poles =	element->getPole(i);
				OdGePoint3d_2_HPoint(&poles,hPoles[i]);
			}

			//If B-spline is closed then add the first (order-1) poles to the end
			// this makes the curve closed : Mustafa Bohari[16-MAY-2008]
			if(isClosed)
			{
				for( int i = 0; i < (order - 1); i++)
				{
					OdGePoint3d poles =	element->getPole(i);
					OdGePoint3d_2_HPoint(&poles,hPoles[pole_counter + i]);
				}

			}

			OdUInt32 knotCount = element->getKnotsCount();
			float* hKnots = new float[totalKnots];; 

			if(knotCount == 0 || knotCount < totalKnots)
			{
				getUniformKnots(isClosed, totalKnots, order, hKnots);
			}
			else
			{
				for (unsigned int i = 0; i < totalKnots; i++)
				{
					hKnots[i] = element->getKnot(i);
				}
			}

			bool isRational = element->getRationalFlag();
			float* hWeights = 0;
			if(isRational)
			{
				hWeights= new float[poleCount];
				for(unsigned int i = 0; i < poleCount; i++)
				{
					hWeights[i] = element->getWeight(i);
				}

			}

			HC_Insert_NURBS_Curve ( order-1, poleCount, hPoles, hWeights, hKnots, 0, 1);


			H_SAFE_DELETE_ARRAY(hPoles);
			H_SAFE_DELETE_ARRAY(hKnots);
			H_SAFE_DELETE_ARRAY(hWeights);

			importXData(element->getXDataLinkage());

			if(m_bFromCellHeader == true && m_iCellHeaderOption == BREAK_CELLHEADER)
				HC_Set_User_Options(m_cCellHeaderName);

		}
		HC_Close_Segment();
	}
	if(m_bFromCellHeader == false || m_iCellHeaderOption != SINGLE_ENTITY_CELLHEADER)
		HC_Close_Segment();
    H_SAFE_DELETE_ARRAY(segname);
}

void BSplineSurface::import( OdRxObjectPtr object )
{

	OdDgBSplineSurfacePtr element = object;
	char* segname = new char[strlen("BSpline_surface_") + MAX_DIGIT_SIZE + 1];
	char* levelName;

	if(m_bFromCellHeader == false || m_iCellHeaderOption != SINGLE_ENTITY_CELLHEADER)
	{
		bool bIfptrRequired = getLevelName(element, levelName);
		HC_Open_Segment(levelName);				
		if(!bIfptrRequired)
			H_SAFE_DELETE_ARRAY(levelName);
	}
	{
		if(m_bFromCellHeader == false || m_iCellHeaderOption != SINGLE_ENTITY_CELLHEADER)
		{
			setLevelMaterialProperties(element);
			if(!getVisibilityOfLevel(object))
				HC_Set_Visibility("everything = off");

		}

		int elmID = getElementID(element);
		sprintf(segname, "BSpline_surface_%d",elmID); 
		HC_Open_Segment(segname);
		{
			if(m_bFromCellHeader == false || m_iCellHeaderOption != SINGLE_ENTITY_CELLHEADER)
			{
				if(element->getInvisibleFlag())
					HC_Set_Visibility("everything = off");

				setElementMaterialProperties(element);
			}

			//Get degree
			OdUInt8 Uorder = element->getOrderU();
			OdUInt8 Vorder = element->getOrderV();

			//Get poles
			OdUInt32 UpoleCount =	element->getPolesCountU();
			OdUInt32 VpoleCount =	element->getPolesCountV();
			int poleCount = UpoleCount*VpoleCount;

			HPoint* hPoles = new HPoint[poleCount];

			for(unsigned int i = 0; i < VpoleCount; i++)
			{
				for(unsigned int j = 0; j < UpoleCount; j++)
				{
					OdGePoint3d poles =	element->getPole(j, i);
					OdGePoint3d_2_HPoint(&poles, hPoles[UpoleCount*i+j]);
				}

			}

			//Get  U knots
			OdUInt32 UknotCount = element->getKnotsCountU();
			//bool isFullKnotsU = element->getStoreFullKnotsUFlag();
			int UknotCount_needed =  Uorder +  UpoleCount;
			int UknotCount_diff = UknotCount_needed - UknotCount;
			bool fillLastUKnot = false;
			if((UknotCount_diff%2) != 0)
			{
				UknotCount_diff = UknotCount_diff -1;
				fillLastUKnot = true;
			}
			float*  hUKnots = new float[UknotCount_needed];

			// We need total knots = order + poleCount , but knots obtained from Dgn are less,
			//So we are goint to repeat 0 and 1 at the start and end of knorArray
			//knotCount_needed/2 no. of times for knots in U, V direction: Mustafa Bohari[16-MAY-2008]

			if(UknotCount > 0)
			{
				//Separate the UKnots
				float* UKnots = new float[UknotCount];

				for (unsigned int i = 0; i < UknotCount; i++)
				{
					UKnots[i] = element->getKnotU(i);
				}

				//Repeat 0 and 1 UknotCount_diff/2 no. of times

				for( int i = 0; i < UknotCount_diff/2; i++)
				{
					hUKnots[i] = 0;
					hUKnots[(UknotCount_needed - 1) - i] = 1;
				}

				//Now store the remaining knots got in UKnots
				for (unsigned int i = 0; i < UknotCount; i++)
				{
					hUKnots[UknotCount_diff/2 + i] = UKnots[i];
				}

				if(fillLastUKnot == true)
				{
					hUKnots[(UknotCount_needed - 2)] = 1;
				}
				H_SAFE_DELETE_ARRAY(UKnots);

			}

			if(UknotCount == 0)
			{
				bool isClosedU = element->getClosedUFlag();
				getUniformKnots(isClosedU, UknotCount_needed, Uorder, hUKnots);  
			}

			////Get  V knots
			OdUInt32 VknotCount = element->getKnotsCountV();
			//bool isFullKnotsV = element->getStoreFullKnotsVFlag();

			int VknotCount_needed =  Vorder +  VpoleCount;
			int VknotCount_diff = VknotCount_needed - VknotCount;
			bool fillLastVKnot = false;
			if((VknotCount_diff%2) != 0)
			{
				VknotCount_diff = VknotCount_diff -1;
				fillLastVKnot = true;
			}
			float* hVKnots = new float[VknotCount_needed];

			if(VknotCount > 0)
			{
				//Separate the VKnots
				float* VKnots = new float[VknotCount];

				for (unsigned int i = 0; i < VknotCount; i++)
				{
					VKnots[i] = element->getKnotV(i);
				}

				//Repeat first and last kknot UknotCount_diff/2 no of times
				for( int i = 0; i < VknotCount_diff/2; i++)
				{
					hVKnots[i] = 0;
					hVKnots[(VknotCount_needed - 1) - i] = 1;
				}

				//Now store the remaining knots got in UKnots
				for (unsigned int i = 0; i < VknotCount; i++)
				{
					hVKnots[VknotCount_diff/2 + i] = VKnots[i];
				}

				if(fillLastVKnot == true)
				{
					hVKnots[(VknotCount_needed - 2)] = 1;
				}

				H_SAFE_DELETE_ARRAY(VKnots);

			}

			if(VknotCount == 0)
			{
				bool isClosedV = element->getClosedVFlag();
				getUniformKnots(isClosedV, VknotCount_needed, Vorder, hVKnots);  
			}

			//Get weights
			bool isRational = element->getRationalFlag();
			float* hWeights = 0;

			if(isRational)
			{
				hWeights= new float[poleCount];
				for( unsigned int i =0; i < VpoleCount; i++)
				{
					for (unsigned int j = 0; j < UpoleCount; j++)
					{
						hWeights[UpoleCount*i + j] = element->getWeight(j, i);
					}
				}
			}

			//Hoops u v parameters are inverse to that of Dgn and hence pass the v param first and then u
			HC_KEY nurbs_surf_key = HC_KInsert_NURBS_Surface(Vorder-1,Uorder-1,VpoleCount,UpoleCount, 
				hPoles, hWeights, hVKnots, hUKnots );
			/* if(m_bCellHeaderHoleFlag==true)
				{
				   m_hkShellKey=HC_Generate_Shell_From_Geometry(nurbs_surf_key,"");
				   HC_Delete_By_Key(nurbs_surf_key);
				   AddGeometryInList(element->getHoleFlag());
				}        */

			if( nurbs_surf_key != -1)
			{
				int nBounds = element->getBoundariesCount();
				bool isHole_bsurf = element->getHoleFlag();
				for(int nBoundary = 0; nBoundary < nBounds; nBoundary++)
				{
					int nPoints = element->getBoundaryVerticesCount(nBoundary);
					//HPoint* trimPoints = new HPoint[ nPoints ];
					float* htrimPoints = new float[ nPoints*2 ];
					for(int i = 0; i < nPoints; i++)
					{
						OdGePoint2d point =	element->getBoundaryVertex(nBoundary, i);
						htrimPoints[2*i]     = point.y;
						htrimPoints[2*i + 1] = point.x;
					}

					// insert the trim curve
					HC_Open_Geometry( nurbs_surf_key );
					HC_Trim_NURBS_Surface_By_Poly( nPoints, htrimPoints );

					/*if(isHole_bsurf == false)
						HC_Set_Trim_Operation( 0, "remove" );
					else
						HC_Set_Trim_Operation( 0, "keep" );*/

					//Assuming first boundary is always visible and others are invisible. Eventum Issue Id: 13442

					//To Do:
					// From ODA bug ID 8058:
					// 1. It seems that first visible boundary solution will not work for all cases.
					// ODA has suggested to use following method to find holes and trims by using following way-
					// 2. we check all boundaries and mark all boundary contours that are
					// inside of other contours. So, we get one visible boundary contour.

					if(nBounds > 1)
					{
						if(isHole_bsurf)
						{
							if(nBoundary >= 1)
							{
								HC_Set_Trim_Operation( 0, "remove" );
							}
							else
							{
								HC_Set_Trim_Operation( 0, "keep" );
							}
						}

					}
					else
					{

						if(isHole_bsurf == false)
							HC_Set_Trim_Operation( 0, "remove" );
						else
							HC_Set_Trim_Operation( 0, "keep" );
					}


					HC_Close_Geometry();

					H_SAFE_DELETE_ARRAY(htrimPoints);
				}
			}


			H_SAFE_DELETE_ARRAY(hPoles);
			H_SAFE_DELETE_ARRAY(hWeights);
			H_SAFE_DELETE_ARRAY(hVKnots);
			H_SAFE_DELETE_ARRAY(hUKnots);

			importXData(element->getXDataLinkage());

			if(m_bFromCellHeader == true && m_iCellHeaderOption == BREAK_CELLHEADER)
				HC_Set_User_Options(m_cCellHeaderName);

		}
		HC_Close_Segment();
	}
	if(m_bFromCellHeader == false || m_iCellHeaderOption != SINGLE_ENTITY_CELLHEADER)
		HC_Close_Segment();
	H_SAFE_DELETE_ARRAY(segname);
}

void TextNode2d::import( OdRxObjectPtr object )
{
	OdDgTextNode2dPtr element = object;
	char* segname = new char[strlen("text_node2d_") + MAX_DIGIT_SIZE + 1];
	char* levelName ;

	if(m_bFromCellHeader == false || m_iCellHeaderOption != SINGLE_ENTITY_CELLHEADER)
	{
		bool bIfptrRequired = getLevelName(element, levelName);
		HC_Open_Segment(levelName);				
		if(!bIfptrRequired)
			H_SAFE_DELETE_ARRAY(levelName);
	}
	{
		if(m_bFromCellHeader == false || m_iCellHeaderOption != SINGLE_ENTITY_CELLHEADER)
		{

			setLevelMaterialProperties(element);
			if(!getVisibilityOfLevel(object))
				HC_Set_Visibility("everything = off");
		}
		int elmID = getElementID(element);
		sprintf(segname, "text_node2d_%d", elmID);
		HC_Open_Segment(segname);
		{
			if(m_bFromCellHeader == false || m_iCellHeaderOption != SINGLE_ENTITY_CELLHEADER)
			{
				if(element->getInvisibleFlag())
					HC_Set_Visibility("everything = off");

				setElementMaterialProperties( element );
			}


			m_bisFromEntity = true;
			iterateElm(element->createIterator(), false, false);

		}
		HC_Close_Segment();

	}
	if(m_bFromCellHeader == false || m_iCellHeaderOption != SINGLE_ENTITY_CELLHEADER)
		HC_Close_Segment();
    H_SAFE_DELETE_ARRAY(segname);
}

void TextNode3d::import( OdRxObjectPtr object )
{
	OdDgTextNode3dPtr element = object;
	char* segname = new char[strlen("text_node3d_") + MAX_DIGIT_SIZE + 1];
	char* levelName ;

	if(m_bFromCellHeader == false || m_iCellHeaderOption != SINGLE_ENTITY_CELLHEADER)
	{
		bool bIfptrRequired = getLevelName(element, levelName);
		HC_Open_Segment(levelName);			
		if(!bIfptrRequired)
			H_SAFE_DELETE_ARRAY(levelName);
	}
	{
		if(m_bFromCellHeader == false || m_iCellHeaderOption != SINGLE_ENTITY_CELLHEADER)
		{

			setLevelMaterialProperties(element);
			if(!getVisibilityOfLevel(object))
				HC_Set_Visibility("everything = off");
		}
		int elmID = getElementID(element);
		sprintf(segname, "text_node3d_%d", elmID);
		HC_Open_Segment(segname);
		{
			if(m_bFromCellHeader == false || m_iCellHeaderOption != SINGLE_ENTITY_CELLHEADER)
			{
				if(element->getInvisibleFlag())
					HC_Set_Visibility("everything = off");

				setElementMaterialProperties( element );
			}


			m_bisFromEntity = true;
			iterateElm(element->createIterator(), false, false);

		}
		HC_Close_Segment();

	}
	if(m_bFromCellHeader == false || m_iCellHeaderOption != SINGLE_ENTITY_CELLHEADER)
		HC_Close_Segment();
	H_SAFE_DELETE_ARRAY(segname);
}


void Text2d::import( OdRxObjectPtr object )
{

	OdDgText2dPtr element = object;
	char* segname = new char[strlen("text2d_") + MAX_DIGIT_SIZE + 1];
	char* levelName;
	bool islevelSegOpen = false;

	if(m_bFromCellHeader == false || m_iCellHeaderOption != SINGLE_ENTITY_CELLHEADER)
	{
		if(!m_bisFromEntity)
		{
			bool bIfptrRequired = getLevelName(element, levelName);
			HC_Open_Segment(levelName);				
			if(!bIfptrRequired)
				H_SAFE_DELETE_ARRAY(levelName);
			islevelSegOpen = true;

			setLevelMaterialProperties(element);
			if(!getVisibilityOfLevel(object))
				HC_Set_Visibility("everything = off");
		}
	}
	{

		int elmID = getElementID(element);
		sprintf(segname, "text2d_%d", elmID);
		HC_Open_Segment(segname);
		{
			if(m_bFromCellHeader == false || m_iCellHeaderOption != SINGLE_ENTITY_CELLHEADER)
			{
				if(element->getInvisibleFlag())
					HC_Set_Visibility("everything = off");

				setElementMaterialProperties( element );
			}

			OdGePoint2d org = element->getOrigin();
			HPoint hOrg[1];
			OdGePoint2d_2_HPoint(&org, hOrg[0]);
			//Get Text string
			OdString text =	element->getText();
			char htext[1024];
			convertToCharArray(text, htext);

			HC_Insert_Text(org.x-m_dMinX, org.y-m_dMinY, 0, htext);


			// Get Font name
			OdDgFontTablePtr pFontTable = element->database()->getFontTable();
			OdDgFontTableRecordPtr pFont = pFontTable->getFont(element->getFontEntryId());
			char hTextSpecs[1024];
			if (!pFont.isNull())
			{
				OdString fontName = pFont->getName();
				convertToCharArray(fontName, htext);
				sprintf(hTextSpecs,"name = %s", htext);
				HC_Set_Text_Font(hTextSpecs);
			}

			//Get Text height
			double height = element->getHeight();
			if( height > 0.0 )
			{
				sprintf(hTextSpecs, "size = %f oru", (float) height );
				HC_Set_Text_Font(hTextSpecs);
			}

			//Get other Text style
			bool isItalics = element->getSlantFlag();
			if(isItalics)
				HC_Set_Text_Font("italic = on");

			bool isUnderLined = element->getUnderlineFlag();
			if(isUnderLined)
				HC_Set_Text_Font("underline = on");

			bool isBold = element->getBoldFlag();
			if(isBold)
				HC_Set_Text_Font("bold = on");


			double angle_rad=element->getRotation();
			double angle_deg=angle_rad*(180/H_PI);			
			char* rotation_angle = new char[strlen("rotation=") + MAX_DIGIT_SIZE + 1];
			sprintf(rotation_angle,"rotation=%f",angle_deg);
			HC_Set_Text_Font(rotation_angle);
			H_SAFE_DELETE_ARRAY(rotation_angle);
			double y = tan(angle_rad);

			HC_Set_Text_Path(1.0,y,0.0);
			//Anil end

			OdDg::TextJustification txtAlgn = element->getJustification();
			if(txtAlgn == 7)
				//HC_Set_Text_Alignment("**");

				/*by default
				HC_Set_Text_Alignment("<");*/

				importXData(element->getXDataLinkage());

			if(m_bFromCellHeader == true && m_iCellHeaderOption == BREAK_CELLHEADER)
				HC_Set_User_Options(m_cCellHeaderName);

		}
		HC_Close_Segment();

	}
	if(islevelSegOpen)
		HC_Close_Segment();
    H_SAFE_DELETE_ARRAY(segname);
}


void Text3d::import( OdRxObjectPtr object )
{
	OdDgText3dPtr element = object;

	char* segname = new char[strlen("text3d_") + MAX_DIGIT_SIZE + 1];
	char* levelName ;
	bool isLevelSegOpen = false;

	if(m_bFromCellHeader == false || m_iCellHeaderOption != SINGLE_ENTITY_CELLHEADER)
	{
		if(!m_bisFromEntity)
		{
			bool bIfptrRequired = getLevelName(element, levelName);
			HC_Open_Segment(levelName);				
			if(!bIfptrRequired)
				H_SAFE_DELETE_ARRAY(levelName);
			isLevelSegOpen = true;
			setLevelMaterialProperties(element);
			if(!getVisibilityOfLevel(object))
				HC_Set_Visibility("everything = off");
		}
	}
	{
		int elmID = getElementID(element);
		sprintf(segname, "text3d_%d", elmID);
		HC_Open_Segment(segname);
		{
			if(m_bFromCellHeader == false || m_iCellHeaderOption != SINGLE_ENTITY_CELLHEADER)
			{
				if(element->getInvisibleFlag())
					HC_Set_Visibility("everything = off");

				setElementMaterialProperties( element );
			}

			OdGePoint3d org = element->getOrigin();
			HPoint hOrg[1];
			OdGePoint3d_2_HPoint(&org, hOrg[0]);
			//Get Text string
			OdString text =	element->getText();
			char htext[1024];
			convertToCharArray(text, htext);

			HC_Insert_Text(hOrg[0].x, hOrg[0].y, hOrg[0].z, htext);

			// Get Font name
			OdDgFontTablePtr pFontTable = element->database()->getFontTable();
			OdDgFontTableRecordPtr pFont = pFontTable->getFont(element->getFontEntryId());
			char hTextSpecs[1024];
			if (!pFont.isNull())
			{
				OdString fontName = pFont->getName();
				convertToCharArray(fontName, htext);
				sprintf(hTextSpecs,"name = %s", htext);
				HC_Set_Text_Font(hTextSpecs);
			}

			//Get Text height
			double height = element->getHeight();
			if( height > 0.0 )
			{
				sprintf(hTextSpecs, "size = %f oru", (float) height );
				HC_Set_Text_Font(hTextSpecs);
			}

			//Get other Text style
			bool isItalics = element->getSlantFlag();
			if(isItalics)
				HC_Set_Text_Font("italic = on");

			bool isUnderLined = element->getUnderlineFlag();
			if(isUnderLined)
				HC_Set_Text_Font("underline = on");

			bool isBold = element->getBoldFlag();
			if(isBold)
				HC_Set_Text_Font("bold = on");

			importXData(element->getXDataLinkage());

			if(m_bFromCellHeader == true && m_iCellHeaderOption == BREAK_CELLHEADER)
				HC_Set_User_Options(m_cCellHeaderName);

		}
		HC_Close_Segment();

	}
	if(isLevelSegOpen)
		HC_Close_Segment();
    H_SAFE_DELETE_ARRAY(segname); 
}

static bool check_file_exist(const char* dir)
{
	FILE* fp;
	fp = fopen(dir,"r");
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

void SharedCellDefinitionTable::import( OdRxObjectPtr object )
{

	OdDgSharedCellDefinitionTablePtr element = object;
	iterateElm( element->createIterator(), false, false ); 
}


void SharedCellDefinition::import( OdRxObjectPtr object )
{

	OdDgSharedCellDefinitionPtr element = object;
	bool isInvisible = element->getInvisibleFlag();
	if(isInvisible == false)
	{

		HC_Open_Segment("/include library/dgndirect_shared_cell_def");
		{
			char defName[1024];
			OdString name = element->getName();
			convertToCharArray(name, defName);
			condition_string_for_segment_name(defName);

			HC_Open_Segment(defName);
			{
				setElementMaterialProperties( element );
				m_bNoOffset = true;
				iterateElm( element->createIterator(), true, false); 
				m_bNoOffset = false;

			}
			HC_Close_Segment();
		}
		HC_Close_Segment();
	}

}

void SharedCellReference::import( OdRxObjectPtr object )
{

	m_iSharedCellRefCounter++;

	if( m_iSharedCellRefCounter == 1)
	{
		//iterate table of shared cell definitions
		m_bSharedCellDefTable = true;
		//OdSmartPtr< HDGNImporter > importer;
		OdRxObjectPtr defObject = pDb->getSharedCellDefinitionTable();
		g_obHDGNImporter = defObject;
		g_obHDGNImporter->import( defObject );
		m_bSharedCellDefTable = false;
	}

	OdDgSharedCellReferencePtr element = object;

	if(m_bSharedCellDefTable == true)
	{
		char childDefName[1024];
		OdString name = element->getDefinitionName();
		convertToCharArray(name, childDefName);
		condition_string_for_segment_name(childDefName);

		char fullPathName[1024];
		sprintf(fullPathName, "/include library/dgndirect_shared_cell_def/%s", childDefName);

		HC_Open_Segment("/include library/dgndirect_shared_cell_def");
		HC_Open_Segment(childDefName);
		HC_Close_Segment();
		HC_Close_Segment();

		char* defSegment = new char[strlen(childDefName) + MAX_DIGIT_SIZE + 1];
		int refElmID = getElementID(element);
		sprintf(defSegment, "%s_%d", childDefName, refElmID);
		HC_Open_Segment(defSegment);
		{
			HC_Include_Segment(fullPathName);
			OdGeMatrix3d xMat = element->getTransformation();
			float hmatrix[] = {xMat.entry[0][0], xMat.entry[1][0], xMat.entry[2][0], xMat.entry[3][0],
				xMat.entry[0][1], xMat.entry[1][1], xMat.entry[2][1], xMat.entry[3][1],
				xMat.entry[0][2], xMat.entry[1][2], xMat.entry[2][2], xMat.entry[3][2],
				xMat.entry[0][3], xMat.entry[1][3], xMat.entry[2][3], xMat.entry[3][3]};


			HC_Set_Modelling_Matrix(hmatrix);
			OdGePoint3d origin = element->getOrigin();
			HC_Translate_Object((double)origin.x, (double)origin.y, (double)origin.z);

		}
		HC_Close_Segment();
		H_SAFE_DELETE_ARRAY(defSegment);
	}
	else if(m_bSharedCellDefTable == false)
	{
		char* segname = new char[strlen("SharedCellReference_") + MAX_DIGIT_SIZE + 1];
		char* levelName;

		if(m_bFromCellHeader == false || m_iCellHeaderOption != SINGLE_ENTITY_CELLHEADER)
		{
			bool bIfptrRequired = getLevelName(element, levelName);
			HC_Open_Segment(levelName);				
			if(!bIfptrRequired)
				H_SAFE_DELETE_ARRAY(levelName);
		}
		{
			char defName[1024];
			OdString name = element->getDefinitionName();
			convertToCharArray(name, defName);
			condition_string_for_segment_name(defName);

			if(m_bFromCellHeader == false || m_iCellHeaderOption != SINGLE_ENTITY_CELLHEADER)
			{
				setLevelMaterialProperties(element);
				if(!getVisibilityOfLevel(object))
					HC_Set_Visibility("everything = off");
			}
			int elmID = getElementID(element);
			sprintf(segname, "SharedCellReference_%d", elmID);
			HC_Open_Segment(segname);
			{
				if(m_bFromCellHeader == false || m_iCellHeaderOption != SINGLE_ENTITY_CELLHEADER)
				{
					if(element->getInvisibleFlag())
						HC_Set_Visibility("everything = off");
				}

				char* includedSeg = new char[strlen("/include library/dgnDirect_shared_cell_def/") + strlen(defName) + 1];
				sprintf(includedSeg,"/include library/dgnDirect_shared_cell_def/%s", defName);
				HC_Include_Segment(includedSeg);
				H_SAFE_DELETE_ARRAY(includedSeg);
				
				OdGeMatrix3d xMat = element->getTransformation();
				float hmatrix[] = {xMat.entry[0][0], xMat.entry[1][0], xMat.entry[2][0], xMat.entry[3][0],
					xMat.entry[0][1], xMat.entry[1][1], xMat.entry[2][1], xMat.entry[3][1],
					xMat.entry[0][2], xMat.entry[1][2], xMat.entry[2][2], xMat.entry[3][2],
					xMat.entry[0][3], xMat.entry[1][3], xMat.entry[2][3], xMat.entry[3][3]};


				HC_Set_Modelling_Matrix(hmatrix);

				OdGePoint3d origin = element->getOrigin();
				HC_Translate_Object((double)origin.x - m_dMinX, (double)origin.y - m_dMinY, (double)origin.z - m_dMinZ);

				HC_Optimize_Segment_Tree (".", "expand includes, collapse matrices");

				importXData(element->getXDataLinkage());

				if(m_bFromCellHeader == true && m_iCellHeaderOption == BREAK_CELLHEADER)
					HC_Set_User_Options(m_cCellHeaderName);

			}
			HC_Close_Segment();
		}
		if(m_bFromCellHeader == false || m_iCellHeaderOption != SINGLE_ENTITY_CELLHEADER)
			HC_Close_Segment();
		H_SAFE_DELETE_ARRAY(segname);
	}

}

void Dimension::import( OdRxObjectPtr object )
{
	OdDgDimensionPtr element = object;

	if(m_bFromCellHeader == true && m_iCellHeaderOption == SINGLE_ENTITY_CELLHEADER)
	{
		return;
	}

	char* segname = new char[strlen("dimension_") + MAX_DIGIT_SIZE + 1];
	char* levelName;

	bool bIfptrRequired = getLevelName(element, levelName);
	HC_Open_Segment(levelName);			
	{
		if(!bIfptrRequired)
			H_SAFE_DELETE_ARRAY(levelName);
		setLevelMaterialProperties(element);
		if(!getVisibilityOfLevel(object));

		int elmID = getElementID(element);
		sprintf(segname, "dimension_%d",elmID); 
		HC_Open_Segment(segname);
		{
			if(element->getInvisibleFlag())
				HC_Set_Visibility("everything = off");

			setElementMaterialProperties(element);

			//worlddraw() does not work with Teigha. needs to implement viewportdraw()
			/*OdArray<shellStore> shells;
			OdWiresWorldGeometry wwd(shells);
			element->worldDraw(&wwd);*/
			//HUtility::Merge_Shells(true, true, true, false);

			importXData(element->getXDataLinkage());

			if(m_bFromCellHeader == true && m_iCellHeaderOption == BREAK_CELLHEADER)
				HC_Set_User_Options(m_cCellHeaderName);
		}
		HC_Close_Segment();
	}
	HC_Close_Segment();
    H_SAFE_DELETE_ARRAY(segname);
}

//Non Graphics element

void XRef::fillVlistOfXref(OdDgReferenceAttachmentHeaderPtr element)
{
	bool isDisplayed = element->getDisplayFlag();

	if(isDisplayed == true)
	{
		OdString fullFileName = element->getFullFileName();

		//For Model Ref
		OdString fullModelName = element->getModelName();
		
		//////////////////////////////////


		int xref_len = fullFileName.getLength();

		char* xref = new char[xref_len + 1];
		convertToCharArray(fullFileName, xref);

		OdString FileName = element->getFileName();
		int FileName_len = FileName.getLength();
		char* onlyXrefName = new char[FileName_len + 1];
		convertToCharArray(FileName, onlyXrefName);

		if(check_file_exist(xref) == false)
		{
			xref = new char[FileName_len + strlen(m_cCurrDir) + 1];
			sprintf(xref, "%s%s", m_cCurrDir, onlyXrefName);
		}

		if(check_file_exist(xref) == true)
		{
			// 
			for(int count = 0; count < m_VlistDiscardedXref.Count(); count++)
			{
				char* name = (m_VlistDiscardedXref.NthItem(count))->GetName();
				if (strcmp(name, onlyXrefName) == 0)
				{
					H_SAFE_DELETE_ARRAY(xref);
					H_SAFE_DELETE_ARRAY(onlyXrefName);
					return;
				}
			}


			char* xrefFileName = new char[strlen(xref) + 1];
			strcpy(xrefFileName,"");
			strcpy(xrefFileName, xref);
			bool itemexist = false;
			unsigned long xrefCount = m_listOfXRefs.Count();
			for( int i = 0; i < xrefCount; i++)
			{
				char* tempStr = m_listOfXRefs.NthItem(i);
				if(stricmp(tempStr, xrefFileName) == 0)
				{
					itemexist = true;
				}
			}

			if(itemexist == false)
			{
				bool isSecondLevelXREF = isAttachedXREF(xrefFileName);

				int nestDepth = element->getNestDepth();

				//Significance of this is not clear. seems to be the nestDepth of the parent but it does not
				//match that with ustation. Need to look into this to resolve this issue completely. Mustafa B
				int baseDepth = element->getBaseNestDepth();

				if(isSecondLevelXREF && nestDepth > 0  )
				{
					m_listOfXRefsOfXRefs.AddLast(xrefFileName);
				}
				else
				{
					m_listOfXRefs.AddLast(xrefFileName);
				
				}

				//Apply the modelling matrix for XREFS here
				HC_Open_Segment(onlyXrefName);
				{
					double xrefScale = element->getEntireScale();

					OdGeMatrix3d ScaleMat;
					OdGeMatrix3d RotMat;
					OdGeMatrix3d TransMat;
					OdGeMatrix3d ResultMat;

					if(xrefScale != 1)
					{
						//HC_Scale_Object(xrefScale, xrefScale, xrefScale);
						ScaleMat.entry[0][0] = xrefScale;
						ScaleMat.entry[1][1] = xrefScale;
						ScaleMat.entry[2][2] = xrefScale;
					}

					RotMat = element->getTransformation();
					TransMat.setTranslation((const OdGeVector3d &)element->getMasterOrigin());

					ResultMat = ScaleMat * RotMat;
					ResultMat = TransMat * ResultMat;

					float hmatrix[] = { ResultMat.entry[0][0], ResultMat.entry[1][0], ResultMat.entry[2][0], ResultMat.entry[3][0],
						ResultMat.entry[0][1], ResultMat.entry[1][1], ResultMat.entry[2][1], ResultMat.entry[3][1],
						ResultMat.entry[0][2], ResultMat.entry[1][2], ResultMat.entry[2][2], ResultMat.entry[3][2],
						ResultMat.entry[0][3], ResultMat.entry[1][3], ResultMat.entry[2][3], ResultMat.entry[3][3]};


					bool isIdentity = HUtility::IsIdentityMatrix(hmatrix);

					if(isIdentity == false)
						HC_Set_Modelling_Matrix(hmatrix);
				}
				HC_Close_Segment();

			}
			else
			{
				H_SAFE_DELETE_ARRAY(xrefFileName);
			}
		}
		H_SAFE_DELETE_ARRAY(xref);
		H_SAFE_DELETE_ARRAY(onlyXrefName);
	}
}

void XRef::import( OdRxObjectPtr object )
{
	OdDgReferenceAttachmentHeaderPtr element = object;

	m_obXRef->fillVlistOfXref(element);
}


void XRef::populateXREFs()
{
	long count = m_listOfXRefs.Count();
	for(int i = 0; i < count; i++)
	{
		char* XRefDir = m_listOfXRefs.NthItem(i);
		char xrefFile[1024];
		char tempStr[1024];
		HUtility::FindFileNameAndDirectory(XRefDir, tempStr, xrefFile);

		m_inputHandler->ReportInputPercentProgress(0.0f);
		char* inputInfo = new char[strlen(") Importing XRef ") + MAX_DIGIT_SIZE + strlen(xrefFile) + 1];
		sprintf(inputInfo, "%d) Importing XRef %s", i+1, xrefFile);
		m_inputHandler->ReportInputInformation(inputInfo);
		H_SAFE_DELETE_ARRAY(inputInfo);
		m_inputHandler->ReportInputInformation("Loading XRef database");

		OdDgDatabasePtr pDbOfXref;
		pDbOfXref = g_HIO_OdExDgnSystemServices.readFile( XRefDir, Oda::kShareDenyWrite );

		if(!pDbOfXref.isNull())
		{
			m_inputHandler->ReportInputInformation("Reading XRef entities");
		
			HC_Open_Segment(xrefFile);
			{
				g_obHDGNImporter = pDbOfXref.get();

				m_totalEntities = calculateTotalEntities(pDbOfXref.get());

				g_obHDGNImporter->import( pDbOfXref.get());

			}
			HC_Close_Segment();

		}
	}
	
}


int HDGNImporter::calculateTotalEntities( OdRxObjectPtr object )
{
	int entities_count = 0;
	OdDgDatabasePtr database = object;
	OdDgElementId activeModelID = database->getActiveModelId();
	OdDbHandle modelhandle = activeModelID.getHandle();
	OdString activeModel = modelhandle.ascii();

	OdDgModelTablePtr pModelTable = database->getModelTable();

	OdDgElementIteratorPtr pIter = pModelTable->createIterator();
	for ( ; !pIter->done(); pIter->step() )
	{
		OdString tempModel;
		OdDgModelPtr pModel;
		{
			pModel = OdDgModel::cast( pIter->item().openObject() );
			OdUInt32 modelEntryID = pModel->getEntryId();
			OdDgElementId tempID = pModelTable->getAt(modelEntryID);
			OdDbHandle temphandle = tempID.getHandle();
			tempModel = temphandle.ascii();
		}
		if(tempModel.compare(activeModel) == 0)//if current model is active model
		{
			if ( pModel.get() )
			{
				//OdSmartPtr< Model > pModelimporter = pModel;
				//pModelimporter->import( pModel.get() );

				OdDgModelPtr element = pModel.get();
				//iterate all graphics elements
				{
					OdDgElementIteratorPtr iterator = element->createGraphicsElementsIterator();
					int           counter = 0;
					OdRxObjectPtr object;

					for( ; !iterator->done(); iterator->step(), counter++ )
					{

						object = iterator->item().openObject();

						OdSmartPtr<HDGNImporter> importer = HDGNImporter::cast( object );
						if ( !importer.isNull() )
						{
							if(m_bIgnoreOffEntities)
							{
								OdDgGraphicsElementPtr grElm = (OdDgGraphicsElementPtr) object;
								if(grElm->getInvisibleFlag())
									continue;
							}

							if(m_bIgnoreOffEntities)
							{
								OdRxObjectPtr objectForVisSetting;

								if(object->isKindOf(OdDgCellHeader3d::desc()))
								{
									OdDgCellHeader3dPtr element = object;
									getFirstchildWithAttr(element->createIterator(), &objectForVisSetting);
								}
								else if(object->isKindOf(OdDgCellHeader2d::desc()))
								{
									OdDgCellHeader2dPtr element = object;
									getFirstchildWithAttr(element->createIterator(), &objectForVisSetting);
								}
								else
								{
									objectForVisSetting = object;
								}
								if(!getVisibilityOfLevel(objectForVisSetting))
									continue;
							}

							entities_count++;
						}
					}
				}

			}
		}
	}
	return entities_count;
}

void HDGNImporter::resetStaticVars()
{
	//Reset the static variables to default value
	m_bDGNImportAllModels = false;
	m_bIgnoreOffEntities = false;
	strcpy(m_cCurrDir, "\0");
	m_coneFactor = 1.0;
	m_totalEntities = 0;
	m_inputHandler = 0;
	m_bDGNRebaselineModel = true;
	m_hashGeomCellID->Flush();
	m_dMinX = m_dMinY = m_dMinZ = LARGEVAL ;
	m_bNoOffset = false;
	pDb.release();
	pDb = 0;
	m_obXRef.release();
	m_obXRef = 0;
	m_bFromSmartSolid = false;
	m_cCellHeaderName[0] = '\0';
	m_bFromCellHeader = false;
	m_bisFromEntity = false;
	m_hashLevelIDName.Flush();
	m_iCellHeaderId = 0;
    m_bCellHeaderHoleFlag = false;
	m_bWorldDrawEntityFlag = false ;
	m_hkShellKey = INVALID_KEY;
	m_hkSolidSegKey = INVALID_KEY;
	m_hkHoleSegKey = INVALID_KEY;
	m_hkSegTobeUsed = INVALID_KEY;
	m_iCellHeaderOption = SINGLE_ENTITY_CELLHEADER;

}

bool HDGNImporter::importDGNFile( const char * FileName, bool isXrefPresent)
{
	char onlyFileName[1024];
	char tempStr[1024];
	HUtility::FindFileNameAndDirectory(FileName, tempStr, onlyFileName); 

	m_inputHandler->ReportInputInformation("Loading Database");

	OdDgDatabasePtr pDgnDatabase;
	pDgnDatabase = g_HIO_OdExDgnSystemServices.readFile( FileName, Oda::kShareDenyWrite );

	if(pDgnDatabase.isNull())
		return false;

	char* model_name = (char*)onlyFileName;
	condition_string_for_segment_name(model_name);
	
	HC_Open_Segment(model_name);
	{
		OdDgImporter importer;
								
		m_totalEntities = calculateTotalEntities(pDgnDatabase.get());
		m_inputHandler->ReportInputInformation("Reading entities started");

		//OdSmartPtr< HDGNImporter > database_importer;
		g_obHDGNImporter = pDgnDatabase.get();
		g_obHDGNImporter->import( pDgnDatabase.get() );

		//XREFs import
		if(isXrefPresent)
		{
			OdSmartPtr< XRef > obXRef = new XRef();
			m_obXRef = new XRef();

			OdDgModelPtr pModel = getActiveModel(pDgnDatabase);
			//XRef::import() is called from here
			iterateElm( pModel->createControlElementsIterator(), false, false );

			m_obXRef->populateXREFs();
			
			obXRef->m_listOfXRefsOfXRefs = m_obXRef->m_listOfXRefsOfXRefs;

			unsigned long xrefsOfXrefsCount = (obXRef->m_listOfXRefsOfXRefs).Count();
			if(xrefsOfXrefsCount > 0)
			{
				for(unsigned long i = 0; i < xrefsOfXrefsCount; i++)
				{
					char* xrefsOfXrefs = (obXRef->m_listOfXRefsOfXRefs).NthItem(i);
					importDGNFile(xrefsOfXrefs, true);

				}
			}
		}

		m_inputHandler->ReportInputInformation("Reading entities finished");

	}
	HC_Close_Segment();

	//reset global HDGNImporter class pointer to NULL
	g_obHDGNImporter = 0;

	return true;

}

bool HDGNImporter::isAttachedXREF(const char* FileName)
{
	bool xrefPresence = false;

	OdDgDatabasePtr pDgnDatabase;
	pDgnDatabase = g_HIO_OdExDgnSystemServices.readFile( FileName, Oda::kShareDenyWrite );

	{
		OdRxObjectPtr object = pDgnDatabase.get();
		OdDgDatabasePtr tempDB = object;
		OdDgModelPtr pModel = getActiveModel(tempDB);

		OdDgElementIteratorPtr iterator = pModel->createControlElementsIterator();
		int	counter = 0;
		OdRxObjectPtr ob;

		for( ; !iterator->done(); iterator->step(), counter++ )
		{
			ob = iterator->item().openObject();
			if(ob->isKindOf(OdDgReferenceAttachmentHeader::desc()))
			{
				OdDgReferenceAttachmentHeaderPtr pXREF = ob;

				int baseNestd = pXREF->getBaseNestDepth();//debug code

				{
					bool isDisplayed = pXREF->getDisplayFlag();

					if(isDisplayed == true)
					{
						OdString fullFileName = pXREF->getFullFileName();
						
						int xref_len = fullFileName.getLength();

						char* xref = new char[xref_len + 1];
						convertToCharArray(fullFileName, xref);

						OdString FileName = pXREF->getFileName();
						int FileName_len = FileName.getLength();
						char* onlyXrefName = new char[FileName_len + 1];
						convertToCharArray(FileName, onlyXrefName);

						if(check_file_exist(xref) == false)
						{
							xref = new char[FileName_len + strlen(m_cCurrDir) + 1];
							sprintf(xref, "%s%s", m_cCurrDir, onlyXrefName);
						}

						if(check_file_exist(xref) == true)
						{
							xrefPresence = true;
							H_SAFE_DELETE_ARRAY(xref);
							H_SAFE_DELETE_ARRAY(onlyXrefName);
							break;
						}
						H_SAFE_DELETE_ARRAY(xref);
						H_SAFE_DELETE_ARRAY(onlyXrefName);
					}

				}
			}
		}
		
		tempDB.release();
	}
	
	return xrefPresence;

}


HFileInputResult HDGNImporter::FileInputByKey(const char * FileName, HC_KEY model_key, HInputHandlerOptions * options)
{
	
	masterFileNode = new TreeNode("main");

	m_hashGeomCellID = new VHash<HC_KEY,int>;

	char* inputInfo = new char[strlen("Importing ") + strlen(FileName) + 1];
	sprintf(inputInfo, "Importing %s", FileName);
	m_inputHandler->ReportInputInformation(inputInfo);
	H_SAFE_DELETE_ARRAY(inputInfo);

	m_bDGNImportAllModels = options->m_bDGNImportAllModels;
	m_bIgnoreOffEntities =  options->m_bIgnoreOffEntities;
	m_iCellHeaderOption   =  options->m_iDGNCellHeaderOption;
	m_bDGNRebaselineModel = options->m_bDGNRebaselineModel;

	m_coneFactor	   =  options->m_coneFactor;
	if(m_coneFactor < 0)
		m_coneFactor = 0;
	else if(m_coneFactor > 100)
		m_coneFactor = 100;

	OdRxModulePtr pModule = odrxDynamicLinker()->loadModule("TG_ModelerGeometry");
	DgModelerModulePtr DgModule = DgModelerModule::cast(pModule);
	if (!DgModule.isNull())
	{
		wrTriangulationParams currentParams;
		double factor = options->m_factorForSmartSolids;
		if (factor < 0)
			factor = 0;
		else if(factor > 359)
			factor = 359;

		currentParams.normalTolerance = factor;//range is 0 to 359
		currentParams.BetweenKnots = 0;// range is 0 to 20

		DgModule->setTriangulationParams(currentParams);
	}

	pModule.release();

	bool result;

	HC_Open_Segment_By_Key(model_key);
	{
		//Define these temporary used segments for Cell headers with holes. Anil G  
		m_hkSolidSegKey= HC_KOpen_Segment("Solid Segment");
		HC_Close_Segment();
		m_hkHoleSegKey= HC_KOpen_Segment("Hole Segment");
		HC_Close_Segment();	  

		//Top level common hoops settings
		HC_Set_Heuristics("concave polygons = on, polygon handedness = right");
		HC_Set_Text_Font("transforms = on");
		HC_Set_Rendering_Options("antialias=(text)");
		HC_Set_Text_Alignment("<");
		// Default facet angle is 20 deg which proves to be insufficient for some Nurbs surfaces
		// with very fine tessellation which requires angle to be smalll to draw it correctly : Mustafa B 
		HC_Set_Rendering_Options ("nurbs surface=(maximum facet angle = 1)");
		HC_Set_Rendering_Options ("general curve=budget=50");

		//set current dir member variable m_cCurrDir to the directory of main file
		HUtility::FindFileNameAndDirectory(FileName, m_cCurrDir, 0); 

		bool isXrefPresent;

		isXrefPresent = isAttachedXREF(FileName);

		if(m_bDGNRebaselineModel )
		{
			if(isXrefPresent)
			{
				m_bDGNRebaselineModel = false;
			}
		}

		if(isXrefPresent)
		{
			
			bool bResult = chkOnlySecondLevelXref(FileName);
			if(bResult)
			{
				m_inputHandler->ReportInputInformation("Creating XREF tree");

				//code for deciding XREFs which are discarded due to parent Xrefs nest depth
				createTreeOfXrefs( FileName);
				//trace_tree(masterFileNode);//Debugging function
				Calculate_Leaf_Count(masterFileNode);
				Create_VHash_Array();

				m_inputHandler->ReportInputInformation("Creating XREF tree finished");

			}
		}
		
		result = importDGNFile(FileName, isXrefPresent);

		//Delete these temporary used segments for Cell headers with holes.    
		HC_Delete_By_Key(m_hkSolidSegKey);     
		HC_Delete_By_Key(m_hkHoleSegKey);	
	}
	HC_Close_Segment();

	resetStaticVars();
	
	
	m_vlistOfColumnVlist.Flush();
	m_VlistLeafNode.Flush();
	m_VlistDiscardedXref.Flush();
	H_SAFE_DELETE(masterFileNode);

	if(!result)
		return InputFail;
	else
		return InputOK;
	
}



bool Calculate_Leaf_Count(TreeNode *pParentNode)
{
	if(pParentNode->m_ChildNodes.Count() > 0)
	{
		for(int i=0; i< pParentNode->m_ChildNodes.Count(); i++)
		{
			Calculate_Leaf_Count(pParentNode->m_ChildNodes.NthItem(i));
		}
	}
	else
	{
		m_VlistLeafNode.AddLast(pParentNode);

	}
	return true;
}

void Create_VHash_Array()
{
	//char chName[1024];

	if(m_VlistLeafNode.Count() > 0)
	{
		for(int i=0; i< m_VlistLeafNode.Count(); i++)
		{
			VList<TreeNode*> *m_vlistOfXrefTreeNodeColumn = new VList<TreeNode*>;
			m_vlistOfXrefTreeNodeColumn->AddLast(m_VlistLeafNode.NthItem(i));
			//strcpy(chName,m_VlistLeafNode.NthItem(i)->GetName());

			TreeNode* pParentNode = m_VlistLeafNode.NthItem(i)->m_pParentNode;
			while(pParentNode != NULL)
			{
				m_vlistOfXrefTreeNodeColumn->AddLast(pParentNode);
				//strcpy(chName,pParentNode->GetName());
				pParentNode = pParentNode->m_pParentNode;
			}
			m_vlistOfColumnVlist.AddLast(m_vlistOfXrefTreeNodeColumn);

		}
	}

	for(int j = 0; j < m_vlistOfColumnVlist.Count(); j++)
	{
		VList<TreeNode*> *vlistOfIndividualColumn =  m_vlistOfColumnVlist.NthItem(j);
		
		Create_Discarded_Xref_List(vlistOfIndividualColumn);

		//Debuging code - Vinit M

		/*char *chName;
		int nNestedDepth;

		for(int i=0; i<(int)vlistOfIndividualColumn->Count(); i++)
			{
				TreeNode* pTreenode = vlistOfIndividualColumn->NthItem(i);
				chName				= vlistOfIndividualColumn->NthItem(i)->GetName();
				nNestedDepth		= vlistOfIndividualColumn->NthItem(i)->GetNestedDepth();	
			}     */      
	}

	//Debuging code - Vinit M
	/*for(int i = 0; i < m_VlistDiscardedXref.Count(); i++)
	{
		strcpy(chName, m_VlistDiscardedXref.NthItem(i)->GetName());
		int temp = 10;
	
	}*/

}



bool Create_Discarded_Xref_List(VList<TreeNode*> pVlistXref)
{
	char chName[1024];

	int nTotalListCount = pVlistXref.Count()-1;
	pVlistXref.Reverse();

	if(pVlistXref.Count() > 1)
	{
		for(int nodeDepth = 1; nodeDepth < pVlistXref.Count(); nodeDepth++)
		{
			OdUInt16 nestDepth = pVlistXref.NthItem(nodeDepth)->GetNestedDepth();
			strcpy(chName, pVlistXref.NthItem(nodeDepth)->GetName());
			if((nodeDepth < nTotalListCount) && (nestDepth < nTotalListCount))
			{
				nTotalListCount =  nestDepth +nodeDepth; 
			}
			else if(nodeDepth > nTotalListCount )
			{
				m_VlistDiscardedXref.AddLast(pVlistXref.NthItem(nodeDepth));
			}
		}
	}
	return true;
}

//Debuging code - Vinit M
//bool trace_tree(TreeNode *pParentNode)
//{
//	char chName[1024];
//	strcpy(chName,pParentNode->GetName());
//	if(pParentNode->m_ChildNodes.Count()>0)
//	{
//		for(int i=0; i< pParentNode->m_ChildNodes.Count(); i++)
//		{
//			trace_tree(pParentNode->m_ChildNodes.NthItem(i));
//		}
//	}
//	return true;
//}


bool HDGNImporter::createTreeOfXrefs( const char * FileName,TreeNode * pCurrentNode)
{
	char onlyFileName[1024];
	char chDir[1024];
	HUtility::FindFileNameAndDirectory(FileName,chDir, onlyFileName);

	if(pCurrentNode == NULL)
	{
		pCurrentNode =  masterFileNode;
	}
	
	fillTheCurrentXrefNodeValues(FileName,pCurrentNode);

	if(pCurrentNode->m_vhashOfImmediateChildXref->Count()>0)
	{
		
		VHash<char*,int>::PairList * XrefFileList = pCurrentNode->m_vhashOfImmediateChildXref->GetPairList();  
		char *pchFileName;
		int  nNestedDepth;
		for(int i=0; i<(int)XrefFileList->Count(); i++)
		{
			pchFileName	  = XrefFileList->NthItem(i)->Key();
			nNestedDepth  = XrefFileList->NthItem(i)->Item();	

			HUtility::FindFileNameAndDirectory(pchFileName,chDir, onlyFileName);

			TreeNode *pNode	= new TreeNode(onlyFileName);
			pNode->m_pParentNode = pCurrentNode;
			pNode->SetNestedDepth(nNestedDepth);
			pCurrentNode->m_ChildNodes.AddLast(pNode);
			createTreeOfXrefs(pchFileName,pNode);

		}  

	}
	return true;
}

void HDGNImporter::fillTheCurrentXrefNodeValues(const char* FileName,TreeNode *pCurrentNode)
{
	
	OdDgDatabasePtr pDgnDatabase;
	pDgnDatabase = g_HIO_OdExDgnSystemServices.readFile( FileName, Oda::kShareDenyWrite );

	{
		OdRxObjectPtr object = pDgnDatabase.get();
		OdDgDatabasePtr tempDB = object;
		OdDgModelPtr pModel = getActiveModel(tempDB);

		OdDgElementIteratorPtr iterator = pModel->createControlElementsIterator();
		int	counter = 0;
		OdRxObjectPtr ob;

		for( ; !iterator->done(); iterator->step(), counter++ )
		{
			ob = iterator->item().openObject();
			if(ob->isKindOf(OdDgReferenceAttachmentHeader::desc()))
			{
				OdDgReferenceAttachmentHeaderPtr pXREF = ob;
				{
					bool isDisplayed = pXREF->getDisplayFlag();

					if(isDisplayed == true)
					{
						OdString fullFileName = pXREF->getFullFileName();
						int xref_len = fullFileName.getLength();
						char* xref = new char[xref_len + 1];
						convertToCharArray(fullFileName, xref);
						
						
						
						OdString FileName = pXREF->getFileName();
						int FileName_len = FileName.getLength();
						char* onlyXrefName = new char[FileName_len + 1];
						convertToCharArray(FileName, onlyXrefName);

						if(check_file_exist(xref) == false)
						{
							xref = new char[FileName_len + strlen(m_cCurrDir) + 1];
							sprintf(xref, "%s%s", m_cCurrDir, onlyXrefName);
						}

						if(check_file_exist(xref) == true)
						{
							pCurrentNode->m_vhashOfImmediateChildXref->InsertItem(xref,pXREF->getNestDepth());
						}
						//H_SAFE_DELETE_ARRAY(xref);
						H_SAFE_DELETE_ARRAY(onlyXrefName);
					}

				}
			}
		}
		
		tempDB.release();
	}
	g_obHDGNImporter = 0;
}

bool HDGNImporter::chkOnlySecondLevelXref(const char* FileName)
{
	bool bResult = false;
	OdDgDatabasePtr pDgnDatabase;
	pDgnDatabase = g_HIO_OdExDgnSystemServices.readFile( FileName, Oda::kShareDenyWrite );

	{
		OdRxObjectPtr object = pDgnDatabase.get();
		OdDgDatabasePtr tempDB = object;
		OdDgModelPtr pModel = getActiveModel(tempDB);

		OdDgElementIteratorPtr iterator = pModel->createControlElementsIterator();
		int	counter = 0;
		OdRxObjectPtr ob;

		for( ; !iterator->done(); iterator->step(), counter++ )
		{
			ob = iterator->item().openObject();
			if(ob->isKindOf(OdDgReferenceAttachmentHeader::desc()))
			{
				OdDgReferenceAttachmentHeaderPtr pXREF = ob;
						{
					bool isDisplayed = pXREF->getDisplayFlag();

					if(isDisplayed == true)
					{
						OdString fullFileName = pXREF->getFullFileName();
						int xref_len = fullFileName.getLength();
						char* xref = new char[xref_len + 1];
						convertToCharArray(fullFileName, xref);
						
						OdString FileName = pXREF->getFileName();
						int FileName_len = FileName.getLength();
						char* onlyXrefName = new char[FileName_len + 1];
						convertToCharArray(FileName, onlyXrefName);

						if(check_file_exist(xref) == false)
						{
							xref = new char[FileName_len + strlen(m_cCurrDir) + 1];
							sprintf(xref, "%s%s", m_cCurrDir, onlyXrefName);
						}

						if(check_file_exist(xref) == true)
						{
							bResult = chkXrefFileLevel(xref);
							if(bResult){ break;}
						}
						//H_SAFE_DELETE_ARRAY(xref);
						H_SAFE_DELETE_ARRAY(onlyXrefName);
					}
				}
			}
		}
		
		tempDB.release();
	}
	g_obHDGNImporter = 0;
	return bResult;
}

bool HDGNImporter::chkXrefFileLevel(const char* FileName)
{
	bool bResult = false;
	OdDgDatabasePtr pDgnDatabase;
	pDgnDatabase = g_HIO_OdExDgnSystemServices.readFile(FileName, Oda::kShareDenyWrite);

	{
		OdRxObjectPtr object = pDgnDatabase.get();
		OdDgDatabasePtr tempDB = object;
		OdDgModelPtr pModel = getActiveModel(tempDB);

		OdDgElementIteratorPtr iterator = pModel->createControlElementsIterator();
		int	counter = 0;
		OdRxObjectPtr ob;

		for( ; !iterator->done(); iterator->step(), counter++ )
		{
			ob = iterator->item().openObject();
			if(ob->isKindOf(OdDgReferenceAttachmentHeader::desc()))
			{
				OdDgReferenceAttachmentHeaderPtr pXREF = ob;
				{
					bool isDisplayed = pXREF->getDisplayFlag();
					if(isDisplayed == true)
					{
						OdString fullFileName = pXREF->getFullFileName();
						int xref_len = fullFileName.getLength();
						char* xref = new char[xref_len + 1];
						convertToCharArray(fullFileName, xref);

						OdString FileName = pXREF->getFileName();
						int FileName_len = FileName.getLength();
						char* onlyXrefName = new char[FileName_len + 1];
						convertToCharArray(FileName, onlyXrefName);

						if(check_file_exist(xref) == false)
						{
							xref = new char[FileName_len + strlen(m_cCurrDir) + 1];
							sprintf(xref, "%s%s", m_cCurrDir, onlyXrefName);
						}

						if(check_file_exist(xref) == true)
						{
							bResult =  true;
							break;
						}
						//H_SAFE_DELETE_ARRAY(xref);
						H_SAFE_DELETE_ARRAY(onlyXrefName);
					}
				}
			}
		}

		tempDB.release();
	}
	g_obHDGNImporter = 0;
	return bResult;
}


