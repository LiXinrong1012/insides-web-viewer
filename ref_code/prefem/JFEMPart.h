#pragma once

#include "prefem/JMesh.h"
#include "prefem/JMeshGroup.h"
#include <vector>

class  JFEMPart
{
public:
	JFEMPart(void);
	~JFEMPart(void);

	void Clear();

	DWORD	m_Id;
	QString m_Name;	

	JMesh m_Mesh;
	JMeshGroupManager m_Group;
};

typedef std::vector<JFEMPart *> CAEPartList;

class  CCAE_Part_Manager
{
public:
	CCAE_Part_Manager(void);
	~CCAE_Part_Manager(void);

	CAEPartList m_PartList;

	void removeAll(){};
	JMeshGroup * createPart(JMesh * pMesh){return NULL;};
	void removePart(JFEMPart * pPart){};
	CAEPartList& getPartList(){
		return m_PartList;
	}
	JFEMPart * getPartById(int id){return NULL;};

};
