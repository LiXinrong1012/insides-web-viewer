#include "HoopsUpdator.h"
#include "precore/appearance.h"
#include "precore/precore_data.h"
#include "precore/itemlist.h"
#include "precore/modeldocument.h"
#include "precore/BaseItemHelper.h"
#include "precore/DataExchangeAPI.h"
#include "precore/IResults.h"

#include "base/Console.h"
#include "base/ShapeDef.h"
#include "base/ParametersManager.h"

#include "coresps/ShapeManager.h"

#include "osg/Vec3d"
#include "osg/Quat"
#include "osg/Matrixd"
#include "osg/Matrixf"
#include "coresps/HoopsUltility.h"

#include "precore/IResultItem.h"
#include "precore/FlexResultItem.h"

#include "BaseItemPosHelper.h"

// hoops related
#include "HDB.h"
#include "HIOManager.h"

using namespace osg;
using namespace Base;


static void _EU_RigidPos(IResultItem* resultItem,AppearanceItem* appItem,float scale)
{
	BaseItem* item=resultItem->connectedItem();
	assert(item);

	Vec3d initialPos,pos;
	Quat initialQuat,quat;
	int currentFrame=resultItem->getParent()->getCurrentFrame();
	if(currentFrame!=0)
		resultItem->setPos(0);

	double* originalA=resultItem->getData(0,0);
	initialPos=Vec3d(originalA[0],originalA[1],originalA[2]);
	BaseItemPosHelper::Phi2Quat(&originalA[3],initialQuat);

	if(currentFrame!=0)
	{
		resultItem->setPos(currentFrame);
		double* a=resultItem->getData(0,0);

		static double tmpPhi[3];
		tmpPhi[0]=a[3]*scale;
		tmpPhi[1]=a[4]*scale;
		tmpPhi[2]=a[5]*scale;
		BaseItemPosHelper::Phi2Quat(tmpPhi,quat);
		pos=Vec3d(a[0]*scale,a[1]*scale,a[2]*scale);
	}

	pos=initialPos+pos;
	quat=initialQuat*quat;

	osg::Matrixf newMatrix;
	newMatrix.preMultTranslate(pos);
	newMatrix.preMultRotate(quat);

	HC_Set_Modelling_Matrix(newMatrix.ptr());
}

static HPoint* _get_node_position(JMesh* mesh,IResultItem* resultItem,float scale)
{
	int nodeCount=mesh->GetNodeCnt();
	if(nodeCount==0)
		return NULL;

	PP_NODE* nodes=mesh->GetNode();
	int currentFrame=resultItem->getParent()->getCurrentFrame();
	resultItem->setPos(0);

	HPoint *nodexyz= new HPoint[nodeCount];
	double* resultdata=resultItem->getData(1,0);

	for (int i = 0; i < nodeCount; ++i)
	{
		PP_NODE& node = nodes[i];
		double* xyz=&resultdata[i*3];
		nodexyz[i].Set(xyz[0],xyz[1],xyz[2]);
	}
	if(currentFrame==0)
		return nodexyz;

	resultItem->setPos(currentFrame);
	for (int i = 0; i < nodeCount; ++i)
	{
		PP_NODE& node = nodes[i];
		double* xyz=&resultdata[i*3];
		nodexyz[i].Set(nodexyz[i].x+scale*xyz[0],nodexyz[i].y+scale*xyz[1],
			nodexyz[i].z+scale*xyz[2]);
	}
	return nodexyz;
}

static HC_KEY _update_model_fempart_surface(JMesh* mesh,int surfaceCount,PP_SURFACE* surfaces,IResultItem* resultItem,float scale)
{
	if(surfaceCount==0)
		return -1;

	int nodeCount=mesh->GetNodeCnt();
	PP_NODE* nodes=mesh->GetNode();
	PP_ELEMENT* elems=mesh->GetElement();

	HPoint *nodexyz= _get_node_position(mesh,resultItem,scale);


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

	delete []facelist;
	delete []nodexyz;
	return shellkey;
}


void _EU_FEMPart(IResultItem* resultItem,AppearanceItem* appItem,float scale)
{
	FlexResultItem* flexResultItem=(FlexResultItem*)resultItem;
	HC_Flush_Geometry(".");
	//HC_Flush_Contents(".","everything");

	//_RU_Draw_CenterMass(resultItem);

	FEMPartBaseItem* femBaseItem=flexResultItem->getFEMBaseItem();

	double* resultdata=flexResultItem->getData(1,0);


	HC_Set_Edge_Weight(3.0);
	//_update_model_instance_fempart_1d(femItem);
	JFEMPart* femPart=femBaseItem->getFEMPart();
	JMesh* mesh=&femPart->m_Mesh;


	int groupCount=femPart->m_Group.getGroupList().size();
	HC_KEY shellKey;
	for(int i=0;i<groupCount;++i){
		JMeshGroup* group=(femPart->m_Group.getGroupList()[i]);
		shellKey=_update_model_fempart_surface(mesh,group->GetSurface1DCnt(),
			group->GetSurface1D(),resultItem,scale);
		appItem->setHCSubKey(0,shellKey);
		shellKey=_update_model_fempart_surface(mesh,group->GetSurface2DCnt(),
			group->GetSurface2D(),resultItem,scale);
		appItem->setHCSubKey(1,shellKey);
		shellKey=_update_model_fempart_surface(mesh,group->GetSurface3DCnt(),
			group->GetSurface3D(),resultItem,scale);
		appItem->setHCSubKey(2,shellKey);
	}
	//HC_Set_Visibility("faces=on");
}




void registerEigenUpdatingFunctions()
{
	HoopsUpdatorSingleton* updator=HoopsUpdator();
	updator->registerEigenUpdating(TDY_PRE_CATE_FEMPART,_EU_FEMPart);
	updator->registerEigenUpdating(TDY_PRE_CATE_RIGIDPART,_EU_RigidPos);

}
