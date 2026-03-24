#pragma once

#include "General_Tools/Version.h"

enum VB_DB_ENTITY_TYPE
{
	VB_DB_NONE,
	VB_DB_GS , 
	VB_DB_MODEL,
	VB_DB_BODY,
	VB_DB_FACE,
	VB_DB_EDGE,
	VB_DB_VERTEX,
	VB_DB_ELEMENT,
	VB_DB_NODE,
	VB_DB_ATTRIBUTES,
	VB_DB_MESH_CONTROL_PARAM,
	VB_DB_LOAD,
	VB_DB_PROPERTY,
	VB_DB_MATERAILS,
	VB_DB_ABAQSTEPS,
	VB_DB_COORDINATE,
	VB_DB_HEADER,
	VB_DB_NASTRANOP,
	VB_DB_ANALYSIS, // jdk 2006.2.14
	VB_DB_CAD_ID,
	VB_DB_SET,
	VB_DB_MERGED_SET,
	VB_DB_ENTITY_SET,
	VB_DB_ELEMENT_EDGES,
	VB_DB_CONNECTION,
	VB_DB_GROUP,
	VB_DB_MESH,
	VB_DB_CAE_RESULT,
	VB_DB_TEST_RESULT,
} ;

//struct VersionInfo
//{
//	int major ;
//	int minor ;
//	int sub  ;
//
//	int build ;
//};

struct VB_DB_ENTITY
{
	VB_DB_ENTITY_TYPE  dbType ;
	long  dbSize ;
	VersionInfo dbVersion;
	//int   dbWMajor, dbWMinor, dbWSub, dbWBuild ;
	//int	  dbRMinMajor, dbRMinMinor, dbRMinSub, dbRMinBuild ;
	unsigned long  dbRes1, dbRes2 ;
};

struct VB_DB_HEADER_DATA
{
	TCHAR cDocName[1024] ; // document name or file nmae 
};

struct VB_DB_HEADER_DATA_1_0_0
{
	TCHAR cDocName[1024] ; // document name or file nmae 
};

// version defendable structures 
//{
struct VB_DB_ENTITY_GS
{
	int nTotalModels ;
};

struct VB_DB_ENTITY_MODEL
{
	unsigned long nId ;
	TCHAR	 cName[1024] ;
	unsigned long	nTotalNodes ;
	unsigned long	nTotalElements ;
	unsigned long	nTotalBodies ;
	unsigned long	nTotalFaces ;
	unsigned long	nTotalEdges ;
	unsigned long	nTotalVertices ;
	unsigned long	nMaxElementId ;
	unsigned long	nMaxNodeId ;
	unsigned long	nMaxEntityId ;
	unsigned long   nCadIdHashEntities ;
};

struct VB_DB_ENTITY_BODY
{
	unsigned long nId ;
	TCHAR	cName[1024] ;
	float	fColor[3] ;
	int		bSolidBody ;
	unsigned long nTotalFaces, nTotalEdges, nTotalVertices ;
	unsigned long nTotalSolidNodes, nTotalSolidElements ;
	unsigned long nStartSolidElementId, nStartSolidNodeId ;
	long matId;
	int iTargOrProj;
};

struct VB_DB_ENTITY_FACE
{
	unsigned long nId ;
	unsigned long nTotalElements ;
};

struct VB_DB_ENTITY_EDGE
{
	unsigned long nId ;
	unsigned long nTotalBarElements ;
};

struct VB_DB_ENTITY_VERTEX
{
	unsigned long nId ;
	unsigned long nNodeId ;
	unsigned long nElementId ;
};

//struct VB_DB_ENTITY_NODE
//{
//	unsigned long nId ;
//	VNODE_FLAGS nFlags ;
//	double  xyz[3] ;
//};
//
//struct VB_DB_ENTITY_ELEMENT
//{
//	unsigned long nId ;
//	ElementType  eType ;
//	VELEM_FLAGS  eFlags ;
//};

struct VB_DB_ENTITY_CAD_ID
{
	unsigned long entityId;
	unsigned long cadId;
};

//////////////////////////////////////////////////////////////////////////
// material
struct VB_DB_MATERIALS 
{
	DWORD materialNum;
	DWORD FieldTableNum;
};

struct VB_DB_MATERIAL_ENT
{
	/*DWORD m_Id;*/
	TCHAR m_Name[256];
	//WORD m_Type;
	//WORD m_subType;
};

struct VB_DB_MATERIAL_ISO_ELASTIC
{
	double m_E;	//!< 弹性模量
	double m_G;
	double m_Possion; //!< 泊松比
	double m_Density; //!< 密度
};
struct VB_DB_MATERIAL_2DOrth
{
	float mfval[18];
};

struct VB_DB_MATERIAL_2DAniso
{
	float m_G11;
	float m_G12;
	float m_G13; 
	float m_G22; 
	float m_G23;
	float m_G33;
	float m_Density;
	float m_A1;
	float m_A2;
	float m_A3;
	float m_Tref;
	float m_GE;
	float m_ST;
	float m_SC;
	float m_SS;
	DWORD m_MCSID;
};

struct VB_DB_MATERIAL_FIELDTABLE_ENT
{
	//DWORD id;
	//WORD mType;
	WORD row;
	WORD column;
	WORD TableDataArrayLength;
};
//////////////////////////////////////////////////////////////////////////

struct VB_DB_LOADS 
{
	DWORD loadNum;
	DWORD loadCaseNum;
	DWORD LBCGroupNum;
};
//////////////////////////////////////////////////////////////////////////
struct VB_DB_COORDINATES 
{
	DWORD coordinateNum;

};

struct VB_DB_COORDINATE_ENTITY
{
	//DWORD Id;
	char Name[1024];
	WORD m_Type;
	DWORD m_RefCoodID;
	double m_dPoints[3][3];
};
//////////////////////////////////////////////////////////////////////////
struct VB_DB_PROPERTIES
{
	DWORD propertyNum;

};

struct VB_DB_PROPERTIES_1_0_0
{
	DWORD propertyNum;

};

struct VB_DB_PSOLID
{
	char Name[256];
	DWORD MID;
	DWORD m_nCORDM;
};

struct VB_DB_PSOLID_1_0_0
{
	char Name[256];
	DWORD MID;
	DWORD m_nCORDM;
};

struct VB_DB_PBAR
{
	char Name[256];
	DWORD  m_nMID;
	float  m_fA;
	float  m_fI1;
	float  m_fI2;
	float  m_fJ;
	float  m_fNSM;

	float  m_fC1;
	float  m_fC2;
	float  m_fD1;
	float  m_fD2;
	float  m_fE1;
	float  m_fE2;
	float  m_fF1;
	float  m_fF2;

	float  m_fK1;
	float  m_fK2;
	float  m_fI12;

	float  cbarX[3];
	int    cbarG;

	int     m_nPA;
	int     m_nPB;

	float   m_fW1A;
	float   m_fW2A;
	float   m_fW3A;
	float   m_fW1B;
	float   m_fW2B;
	float   m_fW3B;

};

struct VB_DB_PBAR_1_0_0
{
	char Name[256];
	DWORD  m_nMID;
	float  m_fA;
	float  m_fI1;
	float  m_fI2;
	float  m_fJ;
	float  m_fNSM;

	float  m_fC1;
	float  m_fC2;
	float  m_fD1;
	float  m_fD2;
	float  m_fE1;
	float  m_fE2;
	float  m_fF1;
	float  m_fF2;

	float  m_fK1;
	float  m_fK2;
	float  m_fI12;

	float  cbarX[3];
	int    cbarG;

	int     m_nPA;
	int     m_nPB;

	float   m_fW1A;
	float   m_fW2A;
	float   m_fW3A;
	float   m_fW1B;
	float   m_fW2B;
	float   m_fW3B;
};

struct VB_DB_PBARL
{
	char Name[256];
	DWORD  m_nMID;
	int    m_SecType;
	float  m_DIM[20];
	float  m_fNSM;

	float  cbarX[3];
	int    cbarG;

	int     m_nPA;
	int     m_nPB;

	float   m_fW1A;
	float   m_fW2A;
	float   m_fW3A;
	float   m_fW1B;
	float   m_fW2B;
	float   m_fW3B;
};

struct VB_DB_PBARL_1_0_0
{
	char Name[256];
	DWORD  m_nMID;
	int    m_SecType;
	float  m_DIM[20];
	float  m_fNSM;

	float  cbarX[3];
	int    cbarG;

	int     m_nPA;
	int     m_nPB;

	float   m_fW1A;
	float   m_fW2A;
	float   m_fW3A;
	float   m_fW1B;
	float   m_fW2B;
	float   m_fW3B;
};

struct VB_DB_PROD
{
	char Name[256];
	DWORD  m_nMID;
	float  m_fA;
	float  m_fJ;
	float  m_fC;
	float  m_fNSM;
};

struct VB_DB_PROD_1_0_0
{
	char Name[256];
	DWORD  m_nMID;
	float  m_fA;
	float  m_fJ;
	float  m_fC;
	float  m_fNSM;
};

struct VB_DB_PSHELL
{
	char Name[256];
	DWORD  m_nMID1;
	float  m_fT;
	DWORD  m_nMID2;
	float  m_f12IT3;
	DWORD  m_nMID3;
	float  m_fTST;
	float  m_fNSM;

	float  m_fZ1;
	float  m_fZ2;
	int    m_nMID4;
};

struct VB_DB_PELAS
{
	char Name[256];
	float  m_K;
	float  m_S;
	float  m_GE;
	DWORD m_C1;
	DWORD m_C2;
};

struct VB_DB_PELAS_1_0_0
{
	char Name[256];
	float  m_K;
	float  m_S;
	float  m_GE;
	DWORD m_C1;
	DWORD m_C2;
};

struct VB_DB_PFAST
{
	char Name[256];
	float  m_diameter;
	long  m_CID;
	DWORD  m_Flag;
	float  m_K[6];
	float  m_Mass;
	float  m_Ge;
};

struct VB_DB_PFAST_1_0_0
{
	char Name[256];
	float  m_diameter;
	long  m_CID;
	DWORD  m_Flag;
	float  m_K[6];
	float  m_Mass;
	float  m_Ge;
};

struct VB_DB_PSHELL_1_0_0
{
	char Name[256];
	DWORD  m_nMID1;
	float  m_fT;
	DWORD  m_nMID2;
	float  m_f12IT3;
	DWORD  m_nMID3;
	float  m_fTST;
	float  m_fNSM;

	float  m_fZ1;
	float  m_fZ2;
	int    m_nMID4;
};

//////////////////////////////////////////////////////////////////////////

struct VB_DB_Connection_1_0_0
{
	DWORD ConnectionNum;
	DWORD ConnectionCaseNum;
};

struct VB_DB_RBE2_1_0_0
{
	TCHAR Name[256];
	DWORD m_CMdof;
	DWORD m_MasterGId;
	DWORD m_SlaveGid;
};

struct VB_DB_ConnectionS
{
	DWORD ConnectionNum;
	DWORD ConnectionCaseNum;
};

struct VB_DB_Connection_RBE2
{
	TCHAR Name[256];
	DWORD m_CMdof;
	DWORD m_MasterGId;
	DWORD m_SlaveGid;
};

struct VB_DB_Connection_RBE3
{
	TCHAR Name[256];
	DWORD m_CMdof;
	DWORD m_CNdof;
	float m_fWeight;
	DWORD m_MasterGId;
	DWORD m_SlaveGid;
};

struct VB_DB_RBE3_1_0_0
{
	TCHAR Name[256];
	DWORD m_CMdof;
	DWORD m_CNdof;
	float m_fWeight;
	DWORD m_MasterGId;
	DWORD m_SlaveGid;
};

struct VB_DB_Connection_CONM2
{
	TCHAR Name[256];
	DWORD   m_CID;
	DWORD   m_G;
	float   m_Mass;
	float   m_X1;
	float   m_X2;
	float   m_X3;
	float   m_I11;
	float   m_I21;
	float   m_I22;
	float   m_I31;
	float   m_I32;
	float   m_I33;
	DWORD m_MasterGId;
	DWORD m_SlaveGid;
};

struct VB_DB_CONM2_1_0_0
{
	TCHAR Name[256];
	DWORD   m_CID;
	DWORD   m_G;
	float   m_Mass;
	float   m_X1;
	float   m_X2;
	float   m_X3;
	float   m_I11;
	float   m_I21;
	float   m_I22;
	float   m_I31;
	float   m_I32;
	float   m_I33;
	DWORD m_MasterGId;
	DWORD m_SlaveGid;
};

struct VB_DB_Connection_FAST
{
	TCHAR Name[256];
	DWORD PID;
	WORD fastType;
	DWORD IDA;
	DWORD IDB;
	DWORD Gs;
	DWORD GA;
	DWORD GB;
};

struct VB_DB_FAST_1_0_0
{
	TCHAR Name[256];
	DWORD PID;
	WORD fastType;
	DWORD IDA;
	DWORD IDB;
	DWORD Gs;
	DWORD GA;
	DWORD GB;
};

struct VB_DB_GroupS
{
	DWORD GroupNum;
};

struct VB_DB_Group_Entity
{
	int m_Type;
	DWORD m_Id;
	TCHAR m_sName[512];
	char m_HoopsName[512];
	DWORD nodeCnt, elementCnt;
	float m_Color[3];
};
