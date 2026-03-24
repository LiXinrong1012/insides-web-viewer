#include "FEMPartBaseItem.h"
#include "precore_data.h"
#include "pretdy/TDYParameters.h"
#include "ParametersBaseItem.h"
#include "DataExchangeAPI.h"
#include <QHash>
#include "femappearanceitem.h"


namespace INSIDES
{

FEMPartBaseItem::FEMPartBaseItem(void)
{
	_classType=TDY_PRE_ITEMCLASS_FEMPART;
	setCategory(TDY_PRE_CATE_FEMPART);

	FEMAppearanceItem* femApp=new FEMAppearanceItem();
	setAppearance(femApp);

	//_appearnce.setVisibilityType(AppearanceItem::Edge,AppearanceItem::Visual);
	//_appearnce.setVisibilityType(AppearanceItem::Marker,AppearanceItem::Visual);
	//_appearnce.setVisibilityType(AppearanceItem::Vertex,AppearanceItem::Visual);
}


FEMPartBaseItem::~FEMPartBaseItem(void)
{
}

void FEMPartBaseItem::copyTo( BaseItem* item ) const
{
	if(item==this)
		return;

	if(item->getClassType()!=TDY_PRE_ITEMCLASS_FEMPART)
		return;

	BaseItem::copyTo(item);
	FEMPartBaseItem* dst=(FEMPartBaseItem*)item;
	dst->_FEMPart=this->_FEMPart;
	dst->_sNodeList=this->_sNodeList;
	dst->_sElementList=this->_sElementList;
}

void FEMPartBaseItem::updateInteralMesh()
{
	QHash<QString,int> String2ElemType;
	String2ElemType["TBEAM"]=EL_LINE2;
	String2ElemType["EBEAM"]=EL_LINE2;
	String2ElemType["TBEAM_E0"]=EL_LINE2;
	String2ElemType["VBEAM"]=EL_LINE2;
	String2ElemType["CABLE"]=EL_LINE2;
	String2ElemType["VCABLE"]=EL_LINE2;
	String2ElemType["TRIP"]=EL_TRI3;
	String2ElemType["QUAD"]=EL_QUAD4;
	String2ElemType["SHELL"]=EL_QUAD4;
	String2ElemType["PLATE"]=EL_QUAD4;

	String2ElemType["SHBEAM2"]=EL_LINE2;

	_FEMPart.Clear();
	int nodeCount=_sNodeList.size();
	int elemCount=_sElementList.size();
	const TDYParameters* paras=DataExchangeAPI::getRelatedParameters(this);

	if( (nodeCount==0) && (elemCount==0) )
		return;

	/// create nodes first
	QHash<int,int> idMap;
	PP_NODE* nodePtr=NULL;
	if(nodeCount>0){
		nodePtr=new PP_NODE[nodeCount];
		for(int i=0;i<nodeCount;++i){
			PP_NODE& node=nodePtr[i];
			node.NID=_sNodeList[i].id;
			DataExchangeAPI::String2Vec<float>(paras,_sNodeList[i].QG,node.xyz,3);
			idMap[node.NID]=i;
		}
		_FEMPart.m_Mesh.SetNode(nodePtr);
	}
	_FEMPart.m_Mesh.SetNodeCnt(nodeCount);

	// second set elements
	PP_ELEMENT* elemPtr=NULL;
	QVector<DWORD>	elemNodes;
	int tmpNodes[20];

	if(elemCount>0){
		elemPtr=new PP_ELEMENT[elemCount];
		memset(elemPtr,0,sizeof(PP_ELEMENT)*elemCount);
		for(int i=0;i<elemCount;++i){
			PP_ELEMENT* elem=&elemPtr[i];
			elem->TID=String2ElemType[_sElementList[i].typeName];
			elem->EID=_sElementList[i].id;
			elem->NSI=elemNodes.size();
			elem->GID=_sElementList[i].groupId;
			PP_ELTYPE* elemType=_FEMPart.m_Mesh.GetElType(elem->TID);
			DataExchangeAPI::String2Vec<int>(NULL,_sElementList[i].nodeList,tmpNodes,elemType->dwNodeCnt);
			for(int j=0;j<elemType->dwNodeCnt;++j)
				elemNodes.push_back(idMap[tmpNodes[j]]);
		}
	}
	DWORD* realElemNodes=new DWORD[elemNodes.size()];
	memcpy(realElemNodes,elemNodes.constData(),sizeof(DWORD)*elemNodes.size());
	_FEMPart.m_Mesh.SetElement(elemPtr);
	_FEMPart.m_Mesh.SetElementNode(realElemNodes);

	_FEMPart.m_Mesh.SetElementNodeCnt(elemNodes.size());
	_FEMPart.m_Mesh.SetElementCnt(elemCount);
	_FEMPart.m_Mesh.CreateLink();

	int groupSize=_sElementList.size()==0?0:_sElementList[_sElementList.size()-1].groupId+1;
	for(int i=0;i<groupSize;++i)
	{
		JMeshGroup *group=_FEMPart.m_Group.createMeshGroup(&_FEMPart.m_Mesh,i);
		group->CreateFace();
		group->CreateLine();
	}


	(*this)["NODECOUNT"]=QString("%1").arg(nodeCount);
	(*this)["ELEMENTCOUNT"]=QString("%1").arg(elemCount);
}

}	// end namespace INSIDES