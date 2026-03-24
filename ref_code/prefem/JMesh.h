#pragma once
 
#include "prefem/prefem_def.h"
#include <QString>

namespace pp
{
	class DB_Handler;
	class BaseEntity;
}

class QDataStream;

class  JMesh
{
public:
	JMesh(void);
	~JMesh(void);

	JMesh(const JMesh& mesh);
	JMesh & operator =(const JMesh &other);

public:

	/// functions related to file exchange.
	bool LoadData(const QString& lpszFilePath);
	bool LoadData(QDataStream* stream);
	bool WriteData(const QString& lpszFilePath);
	bool WriteData(QDataStream* stream);
	bool WriteAsciiData(const QString& lpszFilePath);

	void SetRange();

	void Clear();
	void ResetAllCount();
	void DeleteAllData();

	// Get Function
	PP_NODE* GetNode() { return m_arNode; }
	PP_NODE* GetNode(int index){return &m_arNode[index];}

	PP_ELEMENT* GetElement() { return m_arElement; }
	PP_ELEMENT* GetElement(int index){return &m_arElement[index];} 

	DWORD* GetElementNode() { return m_arElementNode; }
	DWORD GetElementNode(int index){return m_arElementNode[index];} 

	DWORD* GetElementLink() { return m_arElementLink; }
	DWORD GetElementLink(int index){return m_arElementLink[index];}

	PP_ELTYPE* GetElType() { return m_ElType; }
	PP_ELTYPE* GetElType(int index){return &m_ElType[index];}

	DWORD GetNodeCnt() { return m_dwNode; }
	DWORD GetElementCnt() { return m_dwElement; }
	DWORD GetElementNodeCnt() { return m_dwElementNode; }
	DWORD GetElementLinkCnt() { return m_dwElementLink; }

	float* GetSizeRange() { return m_fRange; }
	float GetRangeLength();
	bool GetLoaded() { return m_bLoaded; }
	int * GetElementCheck( ) { return m_arElementCheck; }
	DWORD GetMaxNodeId();
	DWORD GetMaxElemId();

	// Set Function
	void SetNode(PP_NODE* pNode) {  DELETE_ARRAY(m_arNode) m_arNode = pNode; }
	void SetElement(PP_ELEMENT* pElement) { DELETE_ARRAY(m_arElement)  m_arElement = pElement; }
	void SetElementNode(DWORD* pElNode) { DELETE_ARRAY(m_arElementNode) m_arElementNode = pElNode; }
	void SetElementLink(DWORD* pElLink) { DELETE_ARRAY(m_arElementLink) m_arElementLink = pElLink; }

	void SetNodeCnt( DWORD dwN ) ;
	void AddNodeCnt(DWORD);
	void SetElementCnt( DWORD dwN ) { m_dwElement = dwN; }
	void SetElementNodeCnt( DWORD dwN ) { m_dwElementNode = dwN; }
	void SetElementLinkCnt( DWORD dwN ) { m_dwElementLink = dwN; }

	void SetLoaded(bool isloaded) { m_bLoaded = isloaded; }
	void SetElementCheck(int * check) { m_arElementCheck = check; }

	__forceinline BOOL CompareElementLink(DWORD dwA, DWORD dwB);
	BOOL CreateLink();

	void MakeHex();
	void resetFace(int * arElementCheck);
	DWORD getNodeIndexfromId( DWORD id );
	bool EndImportData();
	void GetElementCenter(DWORD eId, double &cX, double &cY, double &cZ);
	DWORD getElemIndexfromId( DWORD id );

	// for debug:
	void createLineMesh();
	void createShellMesh();
	void createSolidMesh();

	static void SetElemType(PP_ELTYPE* t){m_ElType=t;}
	static PP_ELTYPE* GetElemType(){return m_ElType;}

protected:
	static void DeepCopy(JMesh& dst,const JMesh& src);
	PP_NODE*		m_arNode;
	PP_ELEMENT*		m_arElement;

	// Element Accumulated Array
	DWORD*		m_arElementNode;
	DWORD*		m_arElementLink;


	// Data Count 
	DWORD		m_dwNode;
	DWORD		m_dwElement;
	DWORD		m_dwElementNode;
	DWORD		m_dwElementLink;

	// Object Viewing Range ( start(0, 1, 2), end(3, 4, 5) )
	float		m_fRange[6];
	bool		m_bLoaded;

	int* m_arElementCheck; //< i==0 normal, i!=0 dead

	// Element Type 
	static PP_ELTYPE*	m_ElType;
};

