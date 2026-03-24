#include "TDYSectionSurface.h"

#include "precore/FEMPartBaseItem.h"
#include "precore/FlexResultItem.h"
#include "prefem/JFEMPart.h"
#include "prefem/JMesh.h"
#include "prefem/prefem_def.h"
#include "RotVecMath.h"

TDYSectionSurface::TDYSectionSurface( FlexResultItem* flexResultItem )
	:_flexResultItem(flexResultItem)
{

}

TDYSectionSurface::~TDYSectionSurface(void)
{
}

//void TDYSectionSurface::updateDataSection( FlexResultItem* newResultItem )
//{
//	// 设置数据类别；
//	newResultItem->setSection(0,*_flexResultItem->getSection(0));
//	newResultItem->setSection(1,*_flexResultItem->getSection(1));
//	newResultItem->setSection(2,*_flexResultItem->getSection(2));
//	newResultItem->updateSection();
//}

void TDYSectionSurface::updateDataSection( FlexResultItem* newResultItem )
{
	// 设置数据类别；
	newResultItem->setSection(0,*_flexResultItem->getSection(0));
	newResultItem->setSection(1,*_flexResultItem->getSection(1));
	newResultItem->setSection(2,*_flexResultItem->getSection(2));
	newResultItem->updateSection();
}

void TDYSectionSurface::generateNode1D(FlexResultItem* pResult, int iStartNodeIdx,
	const double* pos, const double* phi, const double* F, const double* M)
{
	double area = _section1DParams[0] ;
	double Ixx  = _section1DParams[1] ;
	double Iyy  = _section1DParams[2] ;
	double Izz  = _section1DParams[3] ;
	QList<double>& secNodeList=_section1DPoints;
	int nodeSize=secNodeList.size()/2;
	double relpos[3], globalpos[3], A[9] ;
	RotVecMath::Get_A(A, (double*)phi) ;

	double stress[6] ; 

	for ( int i = 0; i < nodeSize;++i){

		double* nodePosData=pResult->getNodeData(0,iStartNodeIdx+i);
		double* nodeStressData=pResult->getNodeData(1,iStartNodeIdx+i);
		relpos[0] = 0 ;
		relpos[1] = secNodeList[2*i] ;
		relpos[2] = secNodeList[2*i+1] ;

		for (int m = 0; m < 3; m++)
		{
			globalpos[m] = pos[m] ;
			for (int j = 0; j < 3; j++)
				globalpos[m] += A[m*3+j] * relpos[j] ;
		}

		nodePosData[0]=globalpos[0];
		nodePosData[1]=globalpos[1];
		nodePosData[2]=globalpos[2];
		if ( F != NULL && M != NULL )
		{
			nodeStressData[0]=stress[0] = F[0]/area + M[1]/Iyy*relpos[2] + M[2]/Izz*relpos[1] ;
			nodeStressData[1]=stress[1] = 0 ;
			nodeStressData[2]=stress[2] = 0 ;
			nodeStressData[3]=stress[3] = F[1]/area ;
			nodeStressData[4]=stress[4] = 0 ;
			nodeStressData[5]=stress[5] = F[2]/area ;
		}
		else
		{
			memset(nodeStressData,0,sizeof(double)*6); 
		}
	}
}

void TDYSectionSurface::init()
{
	if(!check())
		return;

	initSection1D();
	initSection2D();

	int sec1NodeSize=_section1DPoints.size()/2;
	int newNodeCnt=_beamId2RealStartID.size()*sec1NodeSize+_shellId2RealStartID.size()*2;
	int newElementCnt=_elementStartID.size();
	int newElementNodeCnt=_elementNodeList.size();
		
	if(newNodeCnt==0 || newElementCnt==0)
		return;

	FlexResultItem* newResultItem=new FlexResultItem(NULL);
	JFEMPart* pNewFEMPart=newResultItem->getFEMBaseItem()->getFEMPart();

	PP_NODE* newNodePtr=new PP_NODE[newNodeCnt];
	PP_ELEMENT* newElemPtr=new PP_ELEMENT[newElementCnt];
	DWORD*	newElemNodePtr=new DWORD[newElementNodeCnt];
	memset(newNodePtr,0,sizeof(PP_NODE)*newNodeCnt);
	memset(newElemPtr,0,sizeof(PP_ELEMENT)*newElementCnt);
	memcpy(newElemNodePtr,_elementNodeList.data(),sizeof(DWORD)*newElementNodeCnt);
	for(int i=0;i<newNodeCnt;++i)
		newNodePtr[i].NID=i+1;
	for(int i=0;i<newElementCnt;++i){
		newElemPtr[i].EID=i+1;
		newElemPtr[i].NSI=_elementStartID[i];
		newElemPtr[i].TID=_elementType[i];
	}


	pNewFEMPart->m_Mesh.SetNode(newNodePtr);
	pNewFEMPart->m_Mesh.SetNodeCnt(newNodeCnt);
	pNewFEMPart->m_Mesh.SetElement(newElemPtr);
	pNewFEMPart->m_Mesh.SetElementCnt(newElementCnt);
	pNewFEMPart->m_Mesh.SetElementNode(newElemNodePtr);
	pNewFEMPart->m_Mesh.SetElementNodeCnt(newElementNodeCnt);

	pNewFEMPart->m_Mesh.CreateLink();

	JMeshGroup *group=pNewFEMPart->m_Group.createMeshGroup(&pNewFEMPart->m_Mesh);
	group->Full(true);
	group->CreateFace();
	group->CreateLine();

	updateDataSection(newResultItem);

	_flexResultItem->setNext(newResultItem);
}



void TDYSectionSurface::update()
{
	FlexResultItem* newResultItem=_flexResultItem->getNext();
	if(!newResultItem)
		return;

	for(QMap<int,int>::Iterator b=_beamId2RealStartID.begin();
		b!=_beamId2RealStartID.end();++b){
			generateNode1D(newResultItem,b.value(),
				_flexResultItem->getNodeData(0,b.key()),
				_flexResultItem->getNodeData(1,b.key()),
				NULL,
				NULL);
	}

}

void TDYSectionSurface::generateNode2D( FlexResultItem* pResult, int iStartNodeIdx, const double* pos, const double* phi, 
	const double* F, const double* M )
{

}

void TDYSectionSurface::initSection1D()
{
	JFEMPart* pOldFEM = _flexResultItem->getFEMBaseItem()->getFEMPart() ;

	int secNodeSize=_section1DPoints.size()/2;
	int currSecNodeId=0;
	int newElemCnt=0;
	for ( int i = 0 ; i < pOldFEM->m_Mesh.GetElementCnt(); i++ )
	{
		PP_ELEMENT* pElem = pOldFEM->m_Mesh.GetElement(i) ;
		if ( pElem->TID == EL_LINE2 || pElem->TID == EL_LINE3 )
		{
			int nodeSize=2;
			if ( pElem->TID == EL_LINE3 )
				nodeSize = 3 ;

			for(int j=0;j<nodeSize;++j){
				int nodeIndex=pOldFEM->m_Mesh.GetElementNode(pElem->NSI+j);
				if(_beamId2RealStartID.find(nodeIndex)==_beamId2RealStartID.end()){
					_beamId2RealStartID[nodeIndex]=currSecNodeId;
					currSecNodeId+=secNodeSize;
				}
			}

			int nodeIndex1=pOldFEM->m_Mesh.GetElementNode(pElem->NSI);
			int nodeIndex2=pOldFEM->m_Mesh.GetElementNode(pElem->NSI+1);
			int id1=_beamId2RealStartID[nodeIndex1];
			int id2=_beamId2RealStartID[nodeIndex2];

			for(int j=0;j<secNodeSize;++j){
				_elementType.push_back(EL_QUAD4);
				_elementStartID.push_back(_elementNodeList.size());
				_elementNodeList.push_back(id1+j);
				_elementNodeList.push_back(id2+j);
				_elementNodeList.push_back(id2+(j+1)%secNodeSize);
				_elementNodeList.push_back(id1+(j+1)%secNodeSize);
			}
		}
	}

}

void TDYSectionSurface::initSection2D()
{

}

bool TDYSectionSurface::check()
{
	if(_flexResultItem->subSectionCount(1)<3)
		return false;
	return true;
}
