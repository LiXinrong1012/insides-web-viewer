#pragma once

#include "prefem/prefem_def.h"
#include "prefem/JMesh.h"
#include "prefem/DBStruct.h"
#include <list>
#include <vector>

enum GOURP_TYPE{
	NODE_GROUP,
	ELEMENT_GROUP,
	TEST_NODE_GROUP,
	TEST_ELEMENT_GROUP
};

typedef std::vector<int> IdList;

class JMeshGroup
{
public:
	JMeshGroup(JMesh * pMesh=NULL);
	~JMeshGroup(void);

	JMeshGroup(const JMeshGroup& other);
	JMeshGroup& operator=(const JMeshGroup& other);

	static VersionInfo  min_read_version ;
	bool Write( FILE * fp );
	bool Read( FILE * fp );

	IdList & getElems(){ return m_ElemList; }
	IdList & getNodes(){ return m_NodeList; }

	//static VUDWORD HashId_Elem(void *pData);
	//static VUDWORD HashId_Node(void *pData);
	//void getElems(VHash **ppElemsHash)
	//{*ppElemsHash = &m_ElemHash;}
	//void getNodes(VHash **ppNodesHash)
	//{*ppNodesHash = &m_NodeHash;}
	bool Full() const { return m_bFull; }
	void Full(bool val) { m_bFull = val; }

	DWORD getId() const { return m_Id; }
	void setId(DWORD val) { m_Id = val; }

	GOURP_TYPE getType() const { return m_Type; }
	void setType(GOURP_TYPE val) { m_Type = val; }

	void setName(const QString& name){m_sName=name;}
	QString getName(){ return m_sName; }
	QString getHoopsName() { return m_HoopsName; }
	void setHoopsName(const QString& val) { m_HoopsName=val	; }

	JMesh * getMesh() const { return m_pMesh; }
	void setMesh(JMesh * val) { m_pMesh = val; }

	PP_SURFACE* GetSurface3D() { return m_arSurface3D; }
	PP_SURFACE* GetSurface2D() { return m_arSurface2D; }
	PP_SURFACE* GetSurface1D() { return m_arSurface1D; }
	PP_SURFACE*	GetSurface(int dimension);

	DWORD GetSurface3DCnt() { return m_dwSurface3D; }
	DWORD GetSurface2DCnt() { return m_dwSurface2D; }
	DWORD GetSurface1DCnt() { return m_dwSurface1D; }

	DWORD GetSurfaceCnt(int dimension);

	void SetSurface3D( PP_SURFACE* pSurface ) { m_arSurface3D = pSurface; }
	void SetSurface2D( PP_SURFACE* pSurface ) { m_arSurface2D = pSurface; }
	void SetSurface1D( PP_SURFACE* pSurface ) { m_arSurface1D = pSurface; }

	void SetSurface3DCnt( DWORD dwN ) { m_dwSurface3D = dwN; }
	void SetSurface2DCnt( DWORD dwN ) { m_dwSurface2D = dwN; }
	void SetSurface1DCnt( DWORD dwN)  { m_dwSurface1D = dwN; }

	BOOL CreateFace();
	bool CreateLine();


	long Segment() const { return m_Segment; }
	void Segment(long val) { m_Segment = val; }
	long HKey1D() const { return m_HKey1D; }
	void HKey1D(long val) { m_HKey1D = val; }
	long HKey2D() const { return m_HKey2D; }
	void HKey2D(long val) { m_HKey2D = val; }
	long HKey3D() const { return m_HKey3D; }
	void HKey3D(long val) { m_HKey3D = val; }
	long HKeyElemLine() const { return m_HKeyElemLine; }
	void HKeyElemLine(long val) { m_HKeyElemLine = val; }
	long HKeyNode() const { return m_HKeyNode; }
	void HKeyNode(long val) { m_HKeyNode = val; }
	const float* getColor() const { return &m_Color[0]; }
	void setColor(float *val) { 
		for (int i=0;i<3;i++)
		{
			m_Color[i] = val[i];
		}
	}
	void UpdateListNode(int* arNewNode);
private:
	static void DeepCopy(JMeshGroup& dst,const JMeshGroup& src);
	void Clear();


	GOURP_TYPE m_Type;
	bool m_bFull;
	DWORD m_Id;
	QString m_sName;
	QString m_HoopsName;

	IdList m_ElemList; //单元索引号
	IdList m_NodeList;	// 节点索引号
	
	//VMemMgr	 thisObjMemMgr;
	int m_iTestType;

	//VHash m_ElemHash;	
	//VHash m_NodeHash;

	// Mesh
	JMesh * m_pMesh;

	// Surface
	PP_SURFACE*	m_arSurface3D;
	PP_SURFACE*	m_arSurface2D;
	PP_SURFACE* m_arSurface1D;

	// Count
	DWORD		m_dwSurface3D;
	DWORD		m_dwSurface2D;
	DWORD		m_dwSurface1D;

	// Hoops HC_KEY
	long m_Segment;
	long m_HKey3D, m_HKey2D, m_HKey1D, m_HKeyElemLine, m_HKeyNode;
	float m_Color[3];
};

#define GROUP_COLOR_COUNT 39
typedef std::vector<JMeshGroup *> MeshGroupList;

class JMeshGroupManager
{
public:
	JMeshGroupManager();
	~JMeshGroupManager();

	JMeshGroupManager(const JMeshGroupManager& other);
	JMeshGroupManager& operator=(const JMeshGroupManager& other);
	
	static VersionInfo  min_read_version ;
	bool Write(TCHAR* filename);
	bool Read(TCHAR* filename, JMesh* pMesh, JMesh* pTestMesh);

	void removeAll();
	JMeshGroup * createMeshGroup(JMesh * pMesh,int groupId=-1);
	void removeMeshGroup(JMeshGroup * pGroup);
	MeshGroupList& getGroupList(){
		return m_List;
	}
	JMeshGroup * getGroupById(int id);
	JMeshGroup * findGroupBySegment(long key);
	JMeshGroup * getDefaultGroup(){ return m_pDefaultGroup; }
	void setDefaultGroup(JMeshGroup * val) { m_pDefaultGroup = val; }
	DWORD MaxGroupId() const { return m_MaxGroupId; }
	void MaxGroupId(DWORD val) { m_MaxGroupId = val; }
	JMeshGroup * FindElem( int iEle, int meshType, JMeshGroup * pExceptGroup=NULL );
protected:
	static float GROUP_COLOR[GROUP_COLOR_COUNT];
private:
	MeshGroupList	m_List;
	DWORD			m_MaxGroupId;
	JMeshGroup *	m_pDefaultGroup;

	void DeepCopy(JMeshGroupManager& dst,const JMeshGroupManager& src);
};

//////////////////////////////////////////////////////////////////////////
// Read DB
struct VB_DB_GroupS_1_0_0
{
	DWORD GroupNum;
};

struct VB_DB_Group_Entity_1_0_0
{
	int m_Type;
	DWORD m_Id;
	TCHAR m_sName[512];
	char m_HoopsName[512];
	DWORD nodeCnt, elementCnt;

};

struct VB_DB_Group_Entity_1_1_0
{
	int m_Type;
	bool m_bTestCreate;   //const 20121121
	DWORD m_Id;
	TCHAR m_sName[512];
	char m_HoopsName[512];
	DWORD nodeCnt, elementCnt;
	float m_Color[3];
};

bool ReadDB_GroupEntity_1_0_0( FILE * fp, JMeshGroup* pGroup );

bool ReadDB_GroupEntity_1_1_0( FILE * fp, JMeshGroup* pGroup );