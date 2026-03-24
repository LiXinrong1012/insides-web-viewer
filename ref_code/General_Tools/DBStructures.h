#ifndef DBSTRUCTURES_H
#define DBSTRUCTURES_H

/*
  DBStructures.h (Tools) and  vds_db_structures.h (vds_gs) are dependable. 

  Note: don't edit unless get permission from coordinator. 

  This will affect database (severe !). 
*/

enum VDS_DB_ENTITY_TYPE
{
	VDS_DB_NONE,
	VDS_DB_HEADER,
	VDS_DB_GS , 
	VDS_DB_MODEL,
	VDS_DB_BODY,
	VDS_DB_FACE,
	VDS_DB_EDGE,
	VDS_DB_VERTEX,
	VDS_DB_ELEMENT,
	VDS_DB_NODE,
	VDS_DB_CAD_ID,

//	VDS_DB_HEADER,
	VDS_DB_FORCES,
	VDS_DB_MARKS,
	VDS_DB_JOINTS,
	VDS_DB_CONTACTS,
	VDS_DB_RESULTS,
	VDS_DB_PLOTS,
	//	VDS_DB_MATERAILS,
//	VDS_DB_ABAQSTEPS,
//	VDS_DB_COORDINATE,
//	VDS_DB_NASTRANOP,
//	VDS_DB_SET,
//	VDS_DB_MERGED_SET,
//	VDS_DB_ENTITY_SET,
//	VDS_DB_ELEMENT_EDGES,
} ;

struct VDS_DB_HEADER_DATA_3_0_1_4
{
	char cDocName[1024] ; // document name or file nmae 
};

struct VDS_DB_HEADER_DATA
{
	char cDocName[1024] ; // document name or file nmae 
};

// version defendable structures 
//{
struct VDS_DB_ENTITY_GS
{
	int nTotalModels ;
};

struct VDS_DB_ENTITY_MODEL
{
	unsigned long nId ;
	char	 cName[1024] ;
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

struct VDS_DB_ENTITY_BODY
{
	unsigned long nId ;
	char	cName[1024] ;
	float	fColor[3] ;
	int		bSolidBody ;
	unsigned long nTotalFaces, nTotalEdges, nTotalVertices ;
	unsigned long nTotalSolidNodes, nTotalSolidElements ;
	unsigned long nStartSolidElementId, nStartSolidNodeId ;
	PG_BODYPAM BodyParameter;
	VUDWORD CmId;
};

struct VDS_DB_ENTITY_FACE
{
	unsigned long nId ;
	unsigned long nTotalElements ;
};

struct VDS_DB_ENTITY_EDGE
{
	unsigned long nId ;
	unsigned long nTotalBarElements ;
};

struct VDS_DB_ENTITY_VERTEX
{
	unsigned long nId ;
	unsigned long nNodeId ;
	unsigned long nElementId ;
};

struct VDS_DB_ENTITY_NODE
{
	unsigned long nId ;
	VNODE_FLAGS nFlags ;
	double  xyz[3] ;
};

struct VDS_DB_ENTITY_ELEMENT
{
	unsigned long nId ;
	ElementType  eType ;
	VELEM_FLAGS  eFlags ;
};

struct VDS_DB_ENTITY_CAD_ID
{
	unsigned long entityId;
	unsigned long cadId;
};

struct VDS_DB_ENTITY
{
	VDS_DB_ENTITY_TYPE  dbType ;
	long  dbSize ;
	int   dbWMajor, dbWMinor, dbWSub, dbWBuild ;
	int	  dbRMinMajor, dbRMinMinor, dbRMinSub, dbRMinBuild ;
	unsigned long  dbRes1, dbRes2 ;
};
//}

#endif 