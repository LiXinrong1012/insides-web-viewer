
#include "prefem/JMeshGroup.h"
#include "prefem/Mesh_Func.h"
#include "prefem/DBStruct.h"
#include <algorithm>
#include <tchar.h>

DWORD map[3][2] = { {0,1}, {1,2}, {2,0} };
DWORD mapquad[4][2] = { {0,1}, {1,2}, {2,3}, {3,0} };

VersionInfo JMeshGroupManager::min_read_version = { 1, 0, 0, 0 } ;
VersionInfo JMeshGroup::min_read_version = { 1, 1, 0, 0 } ;

bool ReadDB_Groups_1_0_0(FILE *fp,JMeshGroupManager *pGroups, JMesh* pMesh, JMesh* pTestMesh);

//DWORD JMeshGroup::HashId_Elem(void *pData)
//{
//	PP_ELEMENT *pElem = (PP_ELEMENT *)pData;
//	return pElem->EID;
//}
//
//DWORD JMeshGroup::HashId_Node(void *pData)
//{
//	PP_NODE *pNode = (PP_NODE *)pData;
//	return pNode->NID;
//}

JMeshGroup::JMeshGroup(JMesh * pMesh):/*thisObjMemMgr(4092),
	m_ElemHash(100000,HashId_Elem,NULL,&(thisObjMemMgr)),
	m_NodeHash(100000,HashId_Node,NULL,&(thisObjMemMgr)),*/
	m_pMesh(pMesh), m_Segment(-1L), m_HKey3D(-1L), m_HKey2D(-1L), m_HKey1D(-1L), m_HKeyElemLine(-1L)
{
	m_bFull = false;
	m_Type = ELEMENT_GROUP;
	m_arSurface3D = NULL;
	m_arSurface2D = NULL;
	m_arSurface1D = NULL;

	m_dwSurface3D = 0;
	m_dwSurface2D = 0;
	m_dwSurface1D = 0;


	//setHoopsName( newGUID() );
	m_Color[0] = 0.0;
	m_Color[1] = 0.5;
	m_Color[2] = 0.8;
	m_iTestType = 0;

}


JMeshGroup::JMeshGroup( const JMeshGroup& other )
{
	DeepCopy(*this,other);
}


JMeshGroup::~JMeshGroup(void)
{
	Clear();
}



/************************************************************************/
/* Function: Create Face outside and inside
	comment: Each face is triangle. Will be stored in m_arSurface3D (3D)
	and m_arSurface2D(2D).
                                                                        */
/************************************************************************/
BOOL JMeshGroup::CreateFace()
{	
	// Get Count of Surface
	DWORD nTID, nLink, dwLB, nTri;
	DWORD i,j;

	/////////////////////////
	// Counting Loop
	m_dwSurface3D = 0;
	m_dwSurface2D = 0;

	DWORD m_dwElement = m_pMesh->GetElementCnt();
	PP_ELEMENT* m_arElement = m_pMesh->GetElement();
	PP_ELTYPE* m_ElType = m_pMesh->GetElType();
	DWORD* m_arElementLink = m_pMesh->GetElementLink();

	// Element surface
	int tmpElemCount=m_ElemList.size();
	for(int j=0;j<tmpElemCount;++j)
	{	
		int i=m_ElemList[j];

		nTID = m_arElement[i].TID;
		
		if( m_ElType[nTID].dwDim == 3 ) // 3D Element
		{
			nLink = m_ElType[nTID].dwLinkCnt;
			for(j=0;j<nLink;j++){
				dwLB = m_arElementLink[ m_arElement[i].LSI + j ];
				if( dwLB == DW_NONE || (!m_bFull &&std::find(m_ElemList.begin(), m_ElemList.end(), getLowBit5(dwLB)) == m_ElemList.end())
					/*m_ElemHash.getById(m_arElement[GET_DW_LOBIT5(dwLB)].EID) == NULL*/ )
				{
					//{
					//	nTri = 0;
					//	switch( m_ElType[nTID].dwFaceType[j] ){
					//	case EL_TRI3: 						
					//	case EL_TRI6: 
					//		nTri = 1; break;
					//	case EL_QUAD4: 
					//	case EL_QUAD8: 
					//		nTri = 2; break;
					//	}
					//}
					m_dwSurface3D += 1;
				}
			}
		}
		else if( m_ElType[nTID].dwDim == 2 )	// 2D Element
		{
			//nTri = 0;
			//{
			//	switch( m_arElement[i].TID ){
			//	case EL_TRI3: 
			//	case EL_TRI6: 
			//		nTri = 1; break;
			//	case EL_QUAD4: 
			//	case EL_QUAD8: 
			//		nTri = 2; break;
			//	}
			//}
			m_dwSurface2D += 1;
		}
	}

	/////////////////////////
	// Create Surface Loop
	DELETE_ARRAY(m_arSurface3D)
	DELETE_ARRAY(m_arSurface2D)
	
	m_arSurface3D = new PP_SURFACE[m_dwSurface3D];

	m_arSurface2D = new PP_SURFACE[m_dwSurface2D];

	DWORD dwCnt3D = 0;
	DWORD dwCnt2D = 0;

//	DWORD nGID;
	DWORD nElNode[4];

	for(int ttt=0;ttt<tmpElemCount;++ttt)
	{	
		int i=m_ElemList[ttt];
		nTID = m_arElement[i].TID;
		if( m_ElType[nTID].dwDim == 3 ) 
		{
			nLink = m_ElType[nTID].dwLinkCnt;
			for(j=0;j<nLink;j++){
				dwLB = m_arElementLink[ m_arElement[i].LSI + j ];
				if( dwLB == DW_NONE || (!m_bFull && std::find(m_ElemList.begin(), m_ElemList.end(), getLowBit5(dwLB)) == m_ElemList.end())
					/*m_ElemHash.getById(m_arElement[GET_DW_LOBIT5(dwLB)].EID) == NULL*/ )
				{			
					{
						switch( m_ElType[nTID].dwFaceType[j] ){
						case EL_TRI3: 
						case EL_TRI6: 
							m_arSurface3D[dwCnt3D].TID = m_ElType[nTID].dwFaceType[j];
							m_arSurface3D[dwCnt3D].setEIDAndFaceDir(j,i);

							nElNode[0] = m_ElType[nTID].dwFaceNode[j][0];
							nElNode[1] = m_ElType[nTID].dwFaceNode[j][1];
							nElNode[2] = m_ElType[nTID].dwFaceNode[j][2];
							nElNode[3] = DW_NONE;
							
							m_arSurface3D[dwCnt3D].ElNode[0] = nElNode[0];
							m_arSurface3D[dwCnt3D].ElNode[1] = nElNode[1];
							m_arSurface3D[dwCnt3D].ElNode[2] = nElNode[2];
							m_arSurface3D[dwCnt3D].ElNode[3] = nElNode[3];
							//GetTriNormal( m_arSurface3D[dwCnt3D].Normal, 
							//	m_arNode[ m_arElementNode[m_arElement[i].NSI + nElNode[0] ] ].xyz,
							//	m_arNode[ m_arElementNode[m_arElement[i].NSI + nElNode[1] ] ].xyz,
							//	m_arNode[ m_arElementNode[m_arElement[i].NSI + nElNode[2] ] ].xyz );
							dwCnt3D++;
							break;
						case EL_QUAD4:
						case EL_QUAD8: 
							// 1
							m_arSurface3D[dwCnt3D].TID = m_ElType[nTID].dwFaceType[j];
							m_arSurface3D[dwCnt3D].setEIDAndFaceDir(j,i);

							nElNode[0] = m_ElType[nTID].dwFaceNode[j][0];
							nElNode[1] = m_ElType[nTID].dwFaceNode[j][1];
							nElNode[2] = m_ElType[nTID].dwFaceNode[j][2];
							nElNode[3] = m_ElType[nTID].dwFaceNode[j][3];
							
							m_arSurface3D[dwCnt3D].ElNode[0] = nElNode[0];
							m_arSurface3D[dwCnt3D].ElNode[1] = nElNode[1];
							m_arSurface3D[dwCnt3D].ElNode[2] = nElNode[2];
							m_arSurface3D[dwCnt3D].ElNode[3] = nElNode[3];
							//GetTriNormal( m_arSurface3D[dwCnt3D].Normal, 
							//	m_arNode[ m_arElementNode[m_arElement[i].NSI + nElNode[0] ] ].xyz,
							//	m_arNode[ m_arElementNode[m_arElement[i].NSI + nElNode[1] ] ].xyz,
							//	m_arNode[ m_arElementNode[m_arElement[i].NSI + nElNode[2] ] ].xyz );
							dwCnt3D++;
							break;
						}
					}
				}
			}
		}
		else if( m_ElType[nTID].dwDim == 2 ) 
		{
			
			{
				switch( m_arElement[i].TID ){
				case EL_TRI3: 
				case EL_TRI6: 
					m_arSurface2D[dwCnt2D].TID = m_arElement[i].TID;
					m_arSurface2D[dwCnt2D].EID = i;

					nElNode[0] = 0;
					nElNode[1] = 1;
					nElNode[2] = 2;
					nElNode[3] = DW_NONE;
							
					m_arSurface2D[dwCnt2D].ElNode[0] = nElNode[0];
					m_arSurface2D[dwCnt2D].ElNode[1] = nElNode[1];
					m_arSurface2D[dwCnt2D].ElNode[2] = nElNode[2];
					m_arSurface2D[dwCnt2D].ElNode[3] = nElNode[3];
					//GetTriNormal( m_arSurface2D[dwCnt2D].Normal, 
					//	m_arNode[ m_arElementNode[m_arElement[i].NSI + nElNode[0] ] ].xyz,
					//	m_arNode[ m_arElementNode[m_arElement[i].NSI + nElNode[1] ] ].xyz,
					//	m_arNode[ m_arElementNode[m_arElement[i].NSI + nElNode[2] ] ].xyz );
					dwCnt2D++;
					break;	
				case EL_QUAD4:
				case EL_QUAD8:
					// 1
					m_arSurface2D[dwCnt2D].TID = m_arElement[i].TID;
					m_arSurface2D[dwCnt2D].EID = i;

					nElNode[0] = 0;
					nElNode[1] = 1;
					nElNode[2] = 2;
					nElNode[3] = 3;
							
					m_arSurface2D[dwCnt2D].ElNode[0] = nElNode[0];
					m_arSurface2D[dwCnt2D].ElNode[1] = nElNode[1];
					m_arSurface2D[dwCnt2D].ElNode[2] = nElNode[2];
					m_arSurface2D[dwCnt2D].ElNode[3] = nElNode[3];
					//GetTriNormal( m_arSurface2D[dwCnt2D].Normal, 
					//	m_arNode[ m_arElementNode[m_arElement[i].NSI + nElNode[0] ] ].xyz,
					//	m_arNode[ m_arElementNode[m_arElement[i].NSI + nElNode[1] ] ].xyz,
					//	m_arNode[ m_arElementNode[m_arElement[i].NSI + nElNode[2] ] ].xyz );
					dwCnt2D++;
					break;
				}
			}
		}
	}

	return TRUE;
}

bool JMeshGroup::CreateLine()
{
	DWORD m_dwElement = m_pMesh->GetElementCnt();
	PP_ELEMENT* m_arElement = m_pMesh->GetElement();
	PP_ELTYPE* m_ElType = m_pMesh->GetElType();
	DWORD* m_arElementLink = m_pMesh->GetElementLink();

	PP_ELTYPE* elType;
	int edgeCount=0;
	// Element surface
	int tmpElemCount=m_ElemList.size();
	for(int j=0;j<tmpElemCount;++j)
	{	
		int i=m_ElemList[j];
		int nTID = m_arElement[i].TID;
		elType=&m_ElType[nTID];


		if(elType->dwDim == 1 ) // 1D Element
			edgeCount+=elType->dwEdgeCnt;
	}

	if(edgeCount==0)
		return true;

	DELETE_ARRAY(m_arSurface1D);
	m_dwSurface1D=edgeCount;
	m_arSurface1D=new PP_SURFACE[m_dwSurface1D];
	edgeCount=0;
	for(int j=0;j<tmpElemCount;++j)
	{	
		int i=m_ElemList[j];

		int nTID = m_arElement[i].TID;
		elType=&m_ElType[nTID];

		if(elType->dwDim == 1 ){ // 1D Element
			int eCount=elType->dwEdgeCnt;
			for(int e=0;e<eCount;++e){
				m_arSurface1D[edgeCount].TID=EL_LINE2;
				m_arSurface1D[edgeCount].EID =i;
				m_arSurface1D[edgeCount].ElNode[0]=elType->dwEdgeNode[e][0];
				m_arSurface1D[edgeCount].ElNode[1]=elType->dwEdgeNode[e][1];
				edgeCount++;
			}
		}
	}


	return true;
}

bool JMeshGroup::Write( FILE * fp )
{
	//if( !fp )
	//	return false;

	//fwrite( &min_read_version, sizeof(VersionInfo), 1, fp );
	//VB_DB_Group_Entity GroupEntityDB;
	//GroupEntityDB.m_Id = m_Id;
	//GroupEntityDB.m_Type = m_Type;
	//_tcscpy(GroupEntityDB.m_sName, m_sName );
	//strcpy(GroupEntityDB.m_HoopsName, m_HoopsName);
	//GroupEntityDB.nodeCnt = m_NodeList.size();
	//GroupEntityDB.elementCnt = m_ElemList.size();
	//int i;
	//for (i=0; i<3; i++)
	//{
	//	GroupEntityDB.m_Color[i] = m_Color[i];
	//}

	//DWORD* nodes = new DWORD[GroupEntityDB.nodeCnt];
	//for(int i=0;i<GroupEntityDB.nodeCnt;i++)
	//	nodes[i] = m_NodeList[i];
	//DWORD* elements = new DWORD[GroupEntityDB.elementCnt];
	//for(int i=0;i<GroupEntityDB.elementCnt;i++)
	//	elements[i] = m_ElemList[i];


	//fwrite( &GroupEntityDB, sizeof(VB_DB_Group_Entity), 1, fp );
	//fwrite( nodes, sizeof(DWORD), GroupEntityDB.nodeCnt, fp );
	//fwrite( elements, sizeof(DWORD), GroupEntityDB.elementCnt, fp );
	//delete []nodes;
	//delete []elements;

	return true;
}


bool JMeshGroup::Read( FILE * fp )
{
	if( !fp )
		return false;
	bool bStatus = false ;

	VersionInfo version;
	fread(&version, sizeof(VersionInfo), 1, fp) ;
	if( version.major == 1 && version.minor == 0 && version.sub == 0 && version.build == 0 )
	{
		bStatus = ReadDB_GroupEntity_1_0_0(fp, this);
	}
	else if( version.major == 1 && version.minor == 1 && version.sub == 0 && version.build == 0 )
	{
		bStatus = ReadDB_GroupEntity_1_1_0(fp, this);
	}
	if (bStatus)
	{
		CreateFace();
	}
	return bStatus;
}

void JMeshGroup::UpdateListNode( int* arNewNode )
{
	for(int i=0; i<m_NodeList.size();i++)
	{
		m_NodeList[i] = arNewNode[m_NodeList[i]];
	}
	CreateFace();
}

JMeshGroup& JMeshGroup::operator=( const JMeshGroup& other )
{
	if(this == &other)
		return *this;
	
	Clear();
	DeepCopy(*this,other);
	return *this;
}

void JMeshGroup::DeepCopy( JMeshGroup& dst,const JMeshGroup& src )
{
	dst.m_Type=src.m_Type;
	dst.m_bFull=src.m_bFull;
	dst.m_Id=src.m_Id;
	dst.m_sName=src.m_sName;
	dst.m_HoopsName=src.m_HoopsName;

	dst.m_ElemList=src.m_ElemList;
	dst.m_NodeList=src.m_NodeList;

	dst.m_iTestType=src.m_iTestType;

	dst.m_pMesh=src.m_pMesh;

	dst.m_dwSurface1D=src.m_dwSurface1D;
	dst.m_dwSurface2D=src.m_dwSurface2D;
	dst.m_dwSurface3D=src.m_dwSurface3D;

	// Hoops HC_KEY
	//long m_Segment;
	//long m_HKey3D, m_HKey2D, m_HKey1D, m_HKeyElemLine, m_HKeyNode;
	//float m_Color[3];
	dst.m_arSurface1D=NULL;
	dst.m_arSurface2D=NULL;
	dst.m_arSurface3D=NULL;

	if(dst.m_dwSurface1D>0){
		dst.m_arSurface1D=new PP_SURFACE[dst.m_dwSurface1D];
		memcpy(dst.m_arSurface1D,src.m_arSurface1D,sizeof(PP_SURFACE)*dst.m_dwSurface1D);
	}

	if(dst.m_dwSurface2D>0){
		dst.m_arSurface2D=new PP_SURFACE[dst.m_dwSurface2D];
		memcpy(dst.m_arSurface2D,src.m_arSurface2D,sizeof(PP_SURFACE)*dst.m_dwSurface2D);
	}
	if(dst.m_dwSurface3D>0){
		dst.m_arSurface3D=new PP_SURFACE[dst.m_dwSurface3D];
		memcpy(dst.m_arSurface3D,src.m_arSurface3D,sizeof(PP_SURFACE)*dst.m_dwSurface3D);
	}
}

void JMeshGroup::Clear()
{
	DELETE_ARRAY(m_arSurface3D)
	DELETE_ARRAY(m_arSurface2D)
	DELETE_ARRAY(m_arSurface1D);
	m_dwSurface1D=0;
	m_dwSurface2D=0;
	m_dwSurface3D=0;
}

DWORD JMeshGroup::GetSurfaceCnt( int dimension )
{
	switch(dimension){
	case 0:
		return GetSurface1DCnt();
	case 1:
		return GetSurface2DCnt();
	case 2:
		return GetSurface3DCnt();
	}
	return 0;
}

PP_SURFACE* JMeshGroup::GetSurface( int dimension )
{
	switch(dimension){
	case 0:
		return GetSurface1D();
	case 1:
		return GetSurface2D();
	case 2:
		return GetSurface3D();
	}
	return NULL;
}



//////////////////////////////////////////////////////////////////////////
bool ReadDB_GroupEntity_1_0_0( FILE * fp, JMeshGroup* pGroup )
{
	//if( !fp || !pGroup )
	//	return false ;
	////	bool status = false ;
	//long lStatus = 0 ;
	//VB_DB_Group_Entity_1_0_0 dbgroup;
	//lStatus = fread( &dbgroup, sizeof(VB_DB_Group_Entity_1_0_0), 1, fp );
	//if( lStatus  != 1 )
	//	return false ;
	//pGroup->setName(dbgroup.m_sName);
	//pGroup->setId(dbgroup.m_Id);
	//pGroup->setType((GOURP_TYPE)dbgroup.m_Type);
	//pGroup->setHoopsName(dbgroup.m_HoopsName);

	//IdList & nodeList = pGroup->getNodes();
	//DWORD* nodes = new DWORD[dbgroup.nodeCnt];
	//fread(nodes, sizeof(DWORD), dbgroup.nodeCnt, fp);
	//for(int i=0;i<dbgroup.nodeCnt;i++)
	//	nodeList.push_back(nodes[i]);
	//IdList & elemList = pGroup->getElems();
	//DWORD* elements = new DWORD[dbgroup.elementCnt];
	//fread(elements, sizeof(DWORD), dbgroup.elementCnt, fp);
	//for(int i=0;i<dbgroup.elementCnt;i++)
	//	elemList.push_back(elements[i]);

	
	return true;
}

bool ReadDB_GroupEntity_1_1_0( FILE * fp, JMeshGroup* pGroup )
{
	//if( !fp || !pGroup )
	//	return false ;
	////	bool status = false ;
	//long lStatus = 0 ;
	//VB_DB_Group_Entity_1_1_0 dbgroup;
	//lStatus = fread( &dbgroup, sizeof(VB_DB_Group_Entity_1_1_0), 1, fp );
	//if( lStatus  != 1 )
	//	return false ;
	//pGroup->setName(dbgroup.m_sName);
	//pGroup->setId(dbgroup.m_Id);
	//pGroup->setType((GOURP_TYPE)dbgroup.m_Type);
	//pGroup->setHoopsName(dbgroup.m_HoopsName);
	//pGroup->setColor(dbgroup.m_Color);

	//IdList & nodeList = pGroup->getNodes();
	//DWORD* nodes = new DWORD[dbgroup.nodeCnt];
	//fread(nodes, sizeof(DWORD), dbgroup.nodeCnt, fp);
	//for(int i=0;i<dbgroup.nodeCnt;i++)
	//	nodeList.push_back(nodes[i]);
	//IdList & elemList = pGroup->getElems();
	//DWORD* elements = new DWORD[dbgroup.elementCnt];
	//fread(elements, sizeof(DWORD), dbgroup.elementCnt, fp);
	//for(int i=0;i<dbgroup.elementCnt;i++)
	//	elemList.push_back(elements[i]);


	return true;
}


//////////////////////////////////////////////////////////////////////////
JMeshGroupManager::JMeshGroupManager(  ) 
{
	m_MaxGroupId = 0;
	m_pDefaultGroup = NULL;
}

JMeshGroupManager::JMeshGroupManager( const JMeshGroupManager& other )
{
	DeepCopy(*this,other);
}

JMeshGroupManager::~JMeshGroupManager()
{
	removeAll();
}

void JMeshGroupManager::removeAll()
{
	MeshGroupList::iterator itr;
	for (itr = m_List.begin(); itr!=m_List.end(); itr++)
	{
		JMeshGroup * pGroup = (*itr);
		delete pGroup;
	}
	m_List.clear();
}

JMeshGroup * JMeshGroupManager::createMeshGroup(JMesh * pMesh,int groupId)
{
	if(!pMesh)
		return NULL;

	int nNum = m_List.size();	
	JMeshGroup * pNewGroup = new JMeshGroup(pMesh);
	pNewGroup->setId(groupId);
	pNewGroup->setName(QString("Group%1").arg(groupId));
	pNewGroup->setColor(GROUP_COLOR+((nNum*3)%(GROUP_COLOR_COUNT)));
	m_List.push_back(pNewGroup);

	if(groupId==-1){
		pNewGroup->Full(true);
		pNewGroup->setName("GroupDefault");
		return pNewGroup;
	}

	int elemCount=pMesh->GetElementCnt();
	for(int i=0;i<elemCount;++i){
		PP_ELEMENT* elem=pMesh->GetElement(i);
		if(elem->GID==groupId)
			pNewGroup->getElems().push_back(i);
	}

	return pNewGroup;
}

void JMeshGroupManager::removeMeshGroup( JMeshGroup * pGroup )
{
	MeshGroupList::iterator itr;
	for (itr = m_List.begin(); itr!=m_List.end(); itr++)
	{
		if( pGroup == (*itr) )
		{
			m_List.erase(itr);
			delete pGroup;
			return;
		}
	}
}

JMeshGroup * JMeshGroupManager::findGroupBySegment( long key )
{
	MeshGroupList::iterator itr;
	for (itr = m_List.begin(); itr!=m_List.end(); itr++)
	{
		if( key == (*itr)->Segment() )
		{
			return (*itr);
		}
	}
	return NULL;
}

bool JMeshGroupManager::Write( TCHAR* filename )
{
	//FILE * fp;
	//fp = _tfopen(filename, _T("wb")) ;
	//if( !fp )
	//	return false;

	//unsigned long		ulSize = 0 ;
	//VB_DB_ENTITY		dbEntity ;
	//VersionInfo			version ;

	//version = getVersion() ;

	//dbEntity.dbType   = VB_DB_GROUP;
	//dbEntity.dbSize   = sizeof(VB_DB_ENTITY) ; // temporary size
	//dbEntity.dbVersion = version;
	//dbEntity.dbRes1		 = 0 ;
	//dbEntity.dbRes2		 = 0 ;
	//fwrite((TCHAR*)&dbEntity, sizeof(VB_DB_ENTITY), 1, fp) ;

	//VB_DB_GroupS dbGroups;
	//dbGroups.GroupNum = m_List.size();
	//MeshGroupList::iterator itr = m_List.begin();
	//int i=0;

	////dbConnections.ConnectionCaseNum = allConnectionCasesHash.udwCount;
	//fwrite( &dbGroups, sizeof(VB_DB_GroupS), 1, fp );

	//itr = m_List.begin();
	//while ( itr != m_List.end() ) {
	//	(*itr)->Write(fp);
	//	itr++;
	//}

	//// recalculate the db size
	//ulSize = ftell(fp) ;
	//rewind(fp) ;
	//ulSize = ulSize - sizeof(VB_DB_ENTITY) ;

	//dbEntity.dbType   = VB_DB_GROUP ;
	//dbEntity.dbSize   = ulSize ;		// original data size 
	//dbEntity.dbVersion = version;
	//dbEntity.dbRes1		 = 0 ;
	//dbEntity.dbRes2		 = 0 ;

	//fwrite((TCHAR*)&dbEntity, sizeof(VB_DB_ENTITY), 1, fp) ;	
	//fclose(fp);

	return true;
}

bool JMeshGroupManager::Read( TCHAR* filename, JMesh* pMesh, JMesh* pTestMesh )
{
	//FILE *fp = 0 ;

	//fp = _tfopen(filename, _T("rb")) ;
	//if( ! fp )
	//	return false ;

	//bool bStatus = false ;

	//unsigned long		ulSize = 0 ;
	//VB_DB_ENTITY		dbEntity ;
	//VersionInfo			version  ;

	//version = getVersion() ;

	//fread(&dbEntity, sizeof(VB_DB_ENTITY), 1, fp) ;

	//if( dbEntity.dbVersion.major == 1 && dbEntity.dbVersion.minor == 0 && dbEntity.dbVersion.sub == 0 && dbEntity.dbVersion.build == 0 )
	//{
	//	bStatus = ReadDB_Groups_1_0_0(fp, this, pMesh, pTestMesh);

	//	if( ! bStatus )
	//	{
	//		fclose(fp) ;
	//		return bStatus ;
	//	}
	//}
	//else
	//{
	//	fclose(fp) ;
	//	return false ;
	//}

	//fclose(fp) ;

	//return bStatus;
	return true;
}

JMeshGroup * JMeshGroupManager::FindElem( int iEle, int meshType, JMeshGroup * pExceptGroup )
{
	MeshGroupList::iterator itr;
	for (itr = m_List.begin(); itr!=m_List.end(); itr++)
	{
		JMeshGroup * pGroup = (*itr);
		if (pExceptGroup == pGroup)
		{
			continue;
		}
		{
			IdList & elemList = pGroup->getElems();
			if (std::find(elemList.begin(), elemList.end(), iEle) != elemList.end())
			{
				return pGroup;
			}
		}
	}
	return NULL;
}

float JMeshGroupManager::GROUP_COLOR[GROUP_COLOR_COUNT] = {0,0,1,   0, 0.333333f, 1,   0, 0.666667f, 1,
	0,1,1,   0, 1,  0.666667f,  0, 1, 0.333333f,
	0,1,0,   0.333333f, 1, 0,   0.666667f, 1, 0,
	1,1,0,   1, 0.666667f, 0,   1, 0.333333f, 0,
	1,0,0};

JMeshGroup * JMeshGroupManager::getGroupById( int id )
{
	MeshGroupList::iterator itr;
	for (itr = m_List.begin(); itr!=m_List.end(); itr++)
	{
		JMeshGroup * pGroup = (*itr);
		if (pGroup->getId() == id)
		{
			return pGroup;
		}
	}
	return NULL;
}

JMeshGroupManager& JMeshGroupManager::operator=( const JMeshGroupManager& other )
{
	if(this==&other)
		return *this;

	removeAll();
	DeepCopy(*this,other);
	return *this;
}

void JMeshGroupManager::DeepCopy( JMeshGroupManager& dst,const JMeshGroupManager& src )
{
	dst.m_MaxGroupId=src.m_MaxGroupId;
	for(int i=0;i<src.m_List.size();++i){
		JMeshGroup* newMesh=new JMeshGroup(*src.m_List[i]);
		dst.m_List.push_back(newMesh);
		if(src.m_List[i]==src.m_pDefaultGroup){
			dst.m_pDefaultGroup=dst.m_List[i];
		}
	}
}

//////////////////////////////////////////////////////////////////////////

bool ReadDB_Groups_1_0_0(FILE *fp,JMeshGroupManager *pGroups, JMesh* pMesh, JMesh* pTestMesh)
{
	if( !fp || !pGroups )
		return false ;
	bool status = false ;
	long lStatus = 0 ;
	VB_DB_GroupS_1_0_0 dbGroups;
	lStatus = fread( &(dbGroups), sizeof(VB_DB_GroupS_1_0_0), 1, fp );
	if( lStatus  != 1 )
		return false ;
	DWORD i=0; 
	for( i=0; i<dbGroups.GroupNum; i++ )
	{
		JMeshGroup * pGroupEnt;
		{
			pGroupEnt = pGroups->createMeshGroup(pMesh);
		}
		status = pGroupEnt->Read(fp);
		if( ! status )
			return status ;
		
		if( pGroupEnt->getId() > pGroups->MaxGroupId() )
			pGroups->MaxGroupId( pGroupEnt->getId() );
		
	}

	return true;
}