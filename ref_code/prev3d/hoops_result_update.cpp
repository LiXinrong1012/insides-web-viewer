#include "HoopsUpdator.h"
#include "precore/appearance.h"
#include "precore/precore_data.h"
#include "precore/itemlist.h"
#include "precore/modeldocument.h"
#include "precore/BaseItemHelper.h"
#include "precore/DataExchangeAPI.h"

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
#include "precore/DynamicResultItem.h"
#include "precore/femappearanceitem.h"

#include "BaseItemPosHelper.h"
#include "Hoops3DConfiguration.h"
#include "BaseItemDrawHelper.h"

// hoops related
#include "HDB.h"
#include "HIOManager.h"

using namespace osg;
using namespace Base;

static void _insert_arrow_line(double x0,double y0,double z0,double x1,double y1,double z1,double scale)
{
	osg::Vec3f vec3(x1,y1,z1);
	double len=vec3.length();
	if(len*scale<1e-6)
		return;

	ShapeInput shapeInput;
	shapeInput._keyName="ArrowLine";
	shapeInput._paras.push_back(x0);
	shapeInput._paras.push_back(y0);
	shapeInput._paras.push_back(z0);
	shapeInput._paras.push_back(x1/len);
	shapeInput._paras.push_back(y1/len);
	shapeInput._paras.push_back(z1/len);
	shapeInput._paras.push_back(scale*len);

	ShapeManager::instance()->importShape(&shapeInput);
}
static void _insert_arrow_line_test(double x0,double y0,double z0,double x1,double y1,double z1,double x2,double y2,double z2,double scale)
{
	osg::Vec3f vec3(x1,y1,z1);
	double len=vec3.length();
	if(len*scale<1e-6)
		return;

	//·½Ïò
	osg::Vec3f orientation(x2-x0,y2-y0,z2-z0);
	float length = x2*x2+y2*y2+z2*z2;

	ShapeInput shapeInput;
	shapeInput._keyName="ArrowLine";
	shapeInput._paras.push_back(x0);
	shapeInput._paras.push_back(y0);
	shapeInput._paras.push_back(z0);
	shapeInput._paras.push_back(x1/len);
	shapeInput._paras.push_back(y1/len);
	shapeInput._paras.push_back(z1/len);
	shapeInput._paras.push_back(x2/length);
	shapeInput._paras.push_back(y2/length);
	shapeInput._paras.push_back(z2/length);
	shapeInput._paras.push_back(scale*len);

	ShapeManager::instance()->importShape(&shapeInput);
}
static void _insert_arrow_line2(double x0,double y0,double z0,double x1,double y1,double z1,double scale)
{
	_insert_arrow_line(x0,y0,z0,x1,y1,z1,scale);
	HC_Set_Visibility("faces=on");
	HC_Set_Visibility("edges=off");
	HC_Set_Visibility("vertex=off");
}

void _RU_Draw_CenterMass(IResultItem* resultItem)
{
	HC_Open_Segment("_center");
	HC_Flush_Contents(".","everything");
	HC_Set_Visibility("edge=off");
	HC_Set_Visibility("vertex=off");

	double *a=NULL;
	if(resultItem->connectedItem()->getCategory()==TDY_PRE_CATE_FEMPART)
	{
		int tmpCOMIndex=0;
		if(resultItem->subSectionName(0,1)=="COM")
			tmpCOMIndex=1;
		double* a=resultItem->getData(0,tmpCOMIndex);
	}
	else 
	{
		if(resultItem->sectionName(1)=="COM")
			a=resultItem->getData(1);
		else
			a=resultItem->getData(0);
	}


	Hoops3DConfiguration* tmp=Hoops3DConfiguration::instance();
	if(tmp->getShowMassCenter() && a){
		double centerSize=tmp->getMassCenterSize();

		ShapeInput shapeInput;
		shapeInput._paras.push_back(centerSize);
		shapeInput._paras.push_back(centerSize);
		shapeInput._paras.push_back(centerSize);
		shapeInput._keyName="Sphere";
		ShapeManager::instance()->importShape(&shapeInput);


		HoopsUltility::setModelMatrix_Pos(a[0],a[1],a[2]);
	}
	HC_Close_Segment();
}

void _RU_RigidPos(ResultUpdatePara* para,IResultItem* resultItem,AppearanceItem* appItem)
{
	BaseItem* item=resultItem->connectedItem();
	assert(item);

	double* a=resultItem->getData(0,0);

	osg::Quat quat;
	BaseItemPosHelper::Phi2Quat(&a[3],quat);
	Vec3d pos(a[0],a[1],a[2]);

	osg::Matrixf matrix;
	matrix.preMultTranslate(pos);
	matrix.preMultRotate(quat);

	HC_Set_Modelling_Matrix(matrix.ptr());


	// draw velocity
	HC_Open_Segment("vel");
	HC_Flush_Contents(".","everything");
	if(appItem->_showVelocity){
		osg::Matrixf tmp=osg::Matrixf::inverse(matrix);
		HC_Set_Modelling_Matrix(tmp.ptr());

		double scale=Hoops3DConfiguration::instance()->getVelocityScale();
		_insert_arrow_line2(a[0],a[1],a[2],a[6],a[7],a[8],scale);
	}
	HC_Close_Segment();
}

void _RU_Force(ResultUpdatePara* para, IResultItem* resultItem, AppearanceItem* appItem)
{
	HC_Flush_Geometry(".");
	
	double * a=resultItem->getData(0,0);
	double scale=Hoops3DConfiguration::instance()->getForceScale();
	int sectionCount=resultItem->sectionCount();
	int datalength=resultItem->getDataLength();
	for(int i=0;i<sectionCount;i+=3){
		a=resultItem->getData(i);
		_insert_arrow_line(a[0],a[1],a[2],a[3],a[4],a[5],scale);
	}
	//_insert_arrow_line_test(a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7],a[8],scale);
}

void _RU_Contact_Force(ResultUpdatePara* para, IResultItem* resultItem,AppearanceItem* appItem)
{
	HC_Flush_Geometry(".");
	if(resultItem->getClassType()!=TDY_POST_ITEMCLASS_DYNAMICRIGID)
		return;

	DynamicResultItem* dynamicResultItem=(DynamicResultItem*)resultItem;
	int pieceCount=dynamicResultItem->getPieceCount();

	double * a=resultItem->getData(0,0);
	double scale=Hoops3DConfiguration::instance()->getForceScale();

	for(int i=0;i<pieceCount;++i)
	{
		int delta=dynamicResultItem->getDataLength()*i;
			
		_insert_arrow_line(a[1+delta],a[2+delta],a[3+delta],a[4+delta],a[5+delta],a[6+delta],scale);
		_insert_arrow_line(a[1+delta],a[2+delta],a[3+delta],a[7+delta],a[8+delta],a[9+delta],scale);
	}

}
void _RU_AssemblyPos(ResultUpdatePara* para,IResultItem* resultItem,AppearanceItem* appItem)
{
	BaseItem* item=resultItem->connectedItem();
	assert(item);

	_RU_Draw_CenterMass(resultItem);
}



static HC_KEY _update_model_fempart_surface(JMesh* mesh,int surfaceCount,
	PP_SURFACE* surfaces,double* resultdata,HC_KEY& inputShellKey)
{
	if(surfaceCount==0)
		return -1;

	if(inputShellKey==-1)	// create new shell
	{
		int nodeCount=mesh->GetNodeCnt();
		PP_NODE* nodes=mesh->GetNode();
		PP_ELEMENT* elems=mesh->GetElement();

		HPoint *nodexyz= new HPoint[nodeCount];

		for (int i = 0; i < nodeCount; ++i)
		{
			PP_NODE& node = nodes[i];
			double* xyz=&resultdata[i*3];
			nodexyz[i].Set(xyz[0],xyz[1],xyz[2]);
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
		BaseItemDrawHelper::drawFEMPartNodeID(nodeCount,nodexyz,nodes);

		delete []facelist;
		delete []nodexyz;
		inputShellKey=shellkey;
		return shellkey;
	}
	else{
		int nodeCount=mesh->GetNodeCnt();
		PP_NODE* nodes=mesh->GetNode();

		//static QVector<HPoint> tmpNodeData;
		//if(tmpNodeData.size()<nodeCount)
			//tmpNodeData.resize(max(2*tmpNodeData.size(),nodeCount));
		//HPoint *nodexyz= (HPoint*)tmpNodeData.data();

		HPoint* nodexyz=new HPoint[nodeCount];

		for (int i = 0; i < nodeCount; ++i)
		{
			PP_NODE& node = nodes[i];
			double* xyz=&resultdata[i*3];
			nodexyz[i].Set(xyz[0],xyz[1],xyz[2]);
		}


		HC_Edit_Shell_Points(inputShellKey,0,nodeCount,nodeCount,nodexyz);
		BaseItemDrawHelper::drawFEMPartNodeID(nodeCount,nodexyz,nodes);

		delete []nodexyz;
		return inputShellKey;
	}

}


void _RU_FEMPart(ResultUpdatePara* para,IResultItem* resultItem,AppearanceItem* appItem)
{
	FlexResultItem* flexResultItem=(FlexResultItem*)resultItem;
	if(flexResultItem->getNext())
		flexResultItem=flexResultItem->getNext();

	//HC_Flush_Geometry(".");
	static Matrixf matrix;
	HC_Set_Modelling_Matrix(matrix.ptr());
	//HC_Flush_Contents(".","everything");

	_RU_Draw_CenterMass(resultItem);

	FEMPartBaseItem* femBaseItem=flexResultItem->getFEMBaseItem();

	double* resultdata=flexResultItem->getNodeData(0,0);
	
	HC_Set_Edge_Weight(Hoops3DConfiguration::instance()->getShellEdgeSize());
	float a=Hoops3DConfiguration::instance()->getShellVertexSize();
	HC_Set_Variable_Marker_Size(QString("%1 wsu").arg(a).toStdString().c_str());
	//_update_model_instance_fempart_1d(femItem);
	JFEMPart* femPart=femBaseItem->getFEMPart();
	JMesh* mesh=&femPart->m_Mesh;

	FEMAppearanceItem* femAppItem=(FEMAppearanceItem*)appItem;

	int groupCount=femPart->m_Group.getGroupList().size();
	HC_KEY shellKey;
	for(int i=0;i<groupCount;++i){
		JMeshGroup* group=(femPart->m_Group.getGroupList()[i]);
		shellKey=femAppItem->getGroupHKey(i,0);
		_update_model_fempart_surface(mesh,group->GetSurface1DCnt(),group->GetSurface1D(),resultdata,shellKey);
		femAppItem->setGroupHKey(i,0,shellKey);

		shellKey=femAppItem->getGroupHKey(i,1);
		_update_model_fempart_surface(mesh,group->GetSurface2DCnt(),group->GetSurface2D(),resultdata,shellKey);
		femAppItem->setGroupHKey(i,1,shellKey);

		shellKey=femAppItem->getGroupHKey(i,2);
		_update_model_fempart_surface(mesh,group->GetSurface3DCnt(),group->GetSurface3D(),resultdata,shellKey);
		femAppItem->setGroupHKey(i,2,shellKey);
	}
	//HC_Set_Visibility("faces=on");
}




void registerResultUpdatingFunctions()
{
	HoopsUpdatorSingleton* updator=HoopsUpdator();
	updator->registerResultUpdating(TDY_PRE_CATE_RIGIDPART,_RU_RigidPos);
	updator->registerResultUpdating(TDY_PRE_CATE_FEMPART,_RU_FEMPart);
	updator->registerResultUpdating(TDY_PRE_CATE_ASSEMBLY,_RU_AssemblyPos);
	updator->registerResultUpdating(TDY_PRE_CATE_LOAD,_RU_Force);
	updator->registerResultUpdating(TDY_PRE_CATE_CONTACT,_RU_Contact_Force);

}
