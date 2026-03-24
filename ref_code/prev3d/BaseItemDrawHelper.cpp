#include "BaseItemDrawHelper.h"
#include "HoopsUpdator.h"
#include "precore/appearance.h"
#include "precore/precore_data.h"
#include "precore/itemlist.h"
#include "precore/modeldocument.h"
#include "precore/DataExchangeAPI.h"

#include "base/Console.h"
#include "base/ShapeDef.h"
#include "base/AppConfiguration.h"
#include "base/ParametersManager.h"

#include "osg/Vec3d"
#include "osg/Quat"
#include "osg/Matrixd"
#include "osg/Matrixf"

#include "coresps/HoopsUltility.h"
#include "coresps/ShapeManager.h"

#include "BaseItemPosHelper.h"
#include "Hoops3DConfiguration.h"
#include "precore/BaseItemHelper.h"

// hoops related
#include "HDB.h"
#include "HIOManager.h"

using namespace INSIDES;

void BaseItemDrawHelper::drawFEMPartNodeID(int nodeCount,void* nodexyz1,void* nodes1)
{
	HPoint* nodexyz=(HPoint*)nodexyz1;
	PP_NODE* nodes=(PP_NODE*)nodes1;
	// draw node ID
	if(Hoops3DConfiguration::instance()->getShowFEMNodeID())
	{
		HC_Flush_Contents(".","text");
		double size=Hoops3DConfiguration::instance()->getFEMNodeIDSize();
		HC_Set_Text_Size(size);
		HC_Set_Text_Alignment("<v");
		for(int i=0;i<nodeCount;++i){
			static char tmp[100];
			itoa(nodes[i].NID,tmp,10);
			HC_Insert_Text(nodexyz[i].x,nodexyz[i].y,nodexyz[i].z,tmp);
		}
	}
}

static HC_KEY _update_model_fempart_surface(JMesh* mesh,int surfaceCount,PP_SURFACE* surfaces)
{
	if(surfaceCount==0)
		return -1;

	int nodeCount=mesh->GetNodeCnt();
	PP_NODE* nodes=mesh->GetNode();
	PP_ELEMENT* elems=mesh->GetElement();

	HPoint *nodexyz= new HPoint[nodeCount];

	for (int i = 0; i < nodeCount; ++i)
	{
		PP_NODE& node = nodes[i];
		nodexyz[i].Set(node.x(),node.y(),node.z());
	}

	int flistsize = 0;
	for (int j = 0; j < surfaceCount; ++j)
	{
		PP_SURFACE &surf = surfaces[j];
		switch(surf.TID)
		{
		case EL_LINE2:
			flistsize+=3;
			break;
		case EL_TRI3:
		case EL_TRI6:
			flistsize+=4;
			break;;
		case EL_QUAD4:
		case EL_QUAD8:
			flistsize+=5;
			break;;
		}
	}

	int* facelist = new int[flistsize];
	int curr = 0;
	for (int j = 0; j < surfaceCount; ++j)
	{
		PP_SURFACE &surf = surfaces[j];
		int type = surf.TID;
		int elementId=surf.getEID();
		PP_ELEMENT& elem = elems[elementId];
		if ((type == EL_TRI3) ||
			(type == EL_TRI6))
		{
			facelist[curr++] = 3;
			facelist[curr++] = (int)mesh->GetElementNode(elem.NSI + surf.ElNode[0]);
			facelist[curr++] = (int)mesh->GetElementNode(elem.NSI + surf.ElNode[1]);
			facelist[curr++] = (int)mesh->GetElementNode(elem.NSI + surf.ElNode[2]);
		}
		else if ((type == EL_QUAD4) ||
			(type == EL_QUAD8))
		{
			facelist[curr++] = 4;
			facelist[curr++] = (int)mesh->GetElementNode(elem.NSI + surf.ElNode[0]);
			facelist[curr++] = (int)mesh->GetElementNode(elem.NSI + surf.ElNode[1]);
			facelist[curr++] = (int)mesh->GetElementNode(elem.NSI + surf.ElNode[2]);
			facelist[curr++] = (int)mesh->GetElementNode(elem.NSI + surf.ElNode[3]);
		}	
		else if(type==EL_LINE2)
		{
			facelist[curr++] = 2;
			facelist[curr++] = (int)mesh->GetElementNode(elem.NSI + surf.ElNode[0]);
			facelist[curr++] = (int)mesh->GetElementNode(elem.NSI + surf.ElNode[1]);
		}
	}

	HC_KEY shellkey=HC_Insert_Shell((int)nodeCount, nodexyz, flistsize, facelist);
	//group->HKey2D(shellkey);

	// draw node ID

	if(Hoops3DConfiguration::instance()->getShowFEMNodeID())
	{
		double size=Hoops3DConfiguration::instance()->getFEMNodeIDSize();
		HC_Set_Text_Size(size);
		HC_Set_Text_Alignment("<v");
		for(int i=0;i<nodeCount;++i){
			static char tmp[100];
			itoa(nodes[i].NID,tmp,10);
			HC_Insert_Text(nodexyz[i].x,nodexyz[i].y,nodexyz[i].z,tmp);
		}
	}


	delete []facelist;
	delete []nodexyz;
	return shellkey;
}


void BaseItemDrawHelper::drawFEMPart(INSIDES::FEMPartBaseItem* femItem ,INSIDES::AppearanceItem* appItem)
{
	Hoops3DConfiguration* tmp=Hoops3DConfiguration::instance();
	HC_Set_Edge_Weight(tmp->getShellEdgeSize());

		
	float a=tmp->getShellVertexSize();
	HC_Set_Variable_Marker_Size(QString("%1 wsu").arg(a).toStdString().c_str());

	JFEMPart* femPart=femItem->getFEMPart();
	JMesh* mesh=&femPart->m_Mesh;


	int groupCount=femPart->m_Group.getGroupList().size();
	for(int i=0;i<groupCount;++i){
		JMeshGroup* group=(femPart->m_Group.getGroupList()[i]);
		appItem->setHCSubKey(0,_update_model_fempart_surface(mesh,group->GetSurface1DCnt(),group->GetSurface1D()));
		appItem->setHCSubKey(1,_update_model_fempart_surface(mesh,group->GetSurface2DCnt(),group->GetSurface2D()));
		appItem->setHCSubKey(2,_update_model_fempart_surface(mesh,group->GetSurface3DCnt(),group->GetSurface3D()));
	}
}
