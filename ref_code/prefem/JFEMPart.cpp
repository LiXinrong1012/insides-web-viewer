#include "JFEMPart.h"


JFEMPart::JFEMPart(void)
{
	//m_Mesh.createLineMesh();
	//JMeshGroup* newGroup=m_Group.createMeshGroup(&m_Mesh);
	//newGroup->Full(true);
	//newGroup->CreateFace();
	//newGroup->CreateLine();
}


JFEMPart::~JFEMPart(void)
{
}

void JFEMPart::Clear()
{
	m_Mesh.Clear();
	m_Group.removeAll();
}

//////////////////////////////////////////////////////////////////////////
CCAE_Part_Manager::CCAE_Part_Manager( void )
{

}

CCAE_Part_Manager::~CCAE_Part_Manager( void )
{

}
