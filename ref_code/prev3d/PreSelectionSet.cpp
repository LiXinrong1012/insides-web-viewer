//
// Copyright (c) 2000 by Tech Soft 3D, LLC.
// The information contained herein is confidential and proprietary to
// Tech Soft 3D, LLC., and considered a trade secret as defined under
// civil and criminal statutes.  Tech Soft 3D shall pursue its civil
// and criminal remedies in the event of unauthorized use or misappropriation
// of its trade secrets.  Use of this information by anyone other than
// authorized employees of Tech Soft 3D, LLC. is granted only under a
// written non-disclosure agreement, expressly prescribing the scope and
// manner of such use.
//
// $Header: /files/homes/master/cvs/hoops_master/qthoopsrefapp_4/PreSelectionSet.cpp,v 1.7 2009-09-10 17:56:52 conor Exp $
//


#include "PreSelectionSet.h"
#include "HTools.h"
#include "HBaseView.h"

#include <string.h>

#include "Base/Console.h"
#include "ViewManager.h"
#include "precore/projectselector.h"
#include "precore/appearance.h"
#include "precore/IResultItem.h"
#include "precore/FlexResultItem.h"
#include "precore/precore_data.h"

#include "prefem/prefem_def.h"
#include "PreHQWidget.h"

using namespace Base;
using namespace INSIDES;

PreSelectionSet::PreSelectionSet(HBaseView* view,PreHQWidget* hqWidget)
	:HSelectionSet(view)
	,m_HQWidget(hqWidget)
{
	//m_SelectLevel = EntitySelectLevel;
	//m_SelectionMode=NormalSelectionMode;

	//this->SetHighlightMode(HSelectionHighlightMode::InverseTransparency);

	myProjectSelector()->attachSupplier(this);
}

PreSelectionSet::~PreSelectionSet()
{
	myProjectSelector()->disattachSupplier(this);
}


void PreSelectionSet::ss_onSetSelection_protected( const BaseItemSelection& selects)
{
	this->DeSelectAll();
	ViewManager* viewManager=m_HQWidget->getViewManager().data();
	if(viewManager){
		foreach(BaseItem* test, selects){
			HC_KEY key=viewManager->getHCKey(test);
			if(key!=-1){
				MySelect(key,0,NULL,true);
			}
		}
	}
	m_pView->Update();
}

void PreSelectionSet::ss_onSetSelectionNodes_protected( const SelectionNodeElem& selection )
{
	this->DeSelectAll();
	QWeakPointer<ViewManager> m_ViewManager=m_HQWidget->getViewManager();
	if(selection.resultItem && m_ViewManager && selection.indices.size()!=0){
		AppearanceItem* appItem=m_ViewManager.data()->getAppearance(selection.resultItem->connectedItem());
		int indicesN=selection.indices.size();
		if(appItem){
			QScopedArrayPointer<int> face(new int[indicesN]);
			QScopedArrayPointer<int> vertex2(new int[indicesN]);
			
			for(int i=0;i<indicesN;++i){
				face[i]=-1;
				vertex2[i]=-1;
			}
			for(int d=0;d<3;++d){
				HC_KEY key=appItem->getHCSubKey(d);
				if(key!=-1)
					SelectSubentity(key,0,NULL,indicesN,face.data(),selection.indices.data(),vertex2.data(),false);
			}
		}
	}
	this->GetView()->Update();
}

static QVector<int> _get_face_list(PP_SURFACE*surf,int count,const SelectionNodeElem& selection)
{
	QVector<int> re;
	for(int i=0;i<count;++i){
		const PP_SURFACE& curr=surf[i];
		int eid=curr.getEID();
		if(selection.indices.contains(eid))
			re.push_back(i);
	}
	return re;
}

int* getInvalidArray(int n)
{
	static QVector<int> tmp;
	while(n>tmp.size())
		tmp.push_back(-1);
	return tmp.data();
}

void PreSelectionSet::ss_onSetSelectionElements_protected( const SelectionNodeElem& selection )
{
	this->DeSelectAll();

	QWeakPointer<ViewManager> m_ViewManager=m_HQWidget->getViewManager();

	if(selection.resultItem && m_ViewManager && selection.indices.size()!=0){
		AppearanceItem* appItem=m_ViewManager.data()->getAppearance(selection.resultItem->connectedItem());
		int indicesN=selection.indices.size();
		if(appItem){
			FlexResultItem* flexResultItem=(FlexResultItem*)selection.resultItem;
			JMeshGroup* meshGroup=flexResultItem->getFEMBaseItem()->getFEMPart()->m_Group.getGroupList()[0];

			for(int d=0;d<3;++d){
				HC_KEY key=appItem->getHCSubKey(d);
				if(key!=-1 && meshGroup->GetSurfaceCnt(d)!=0){
					//QVector<int> faceList=_get_face_list(meshGroup->GetSurface(d),meshGroup->GetSurfaceCnt(d),selection);
					QVector<int> faceList;
					faceList.push_back(0);
					faceList.push_back(1);
					QVector<int> v1;v1<<0<<4;
					QVector<int> v2;v2<<1<<-1;
					int s=faceList.size();
					if(faceList.size()>0)
						SelectSubentity(key,0,NULL,faceList.size(),
							faceList.data(),
							v1.data(),
							v2.data(),
							//getInvalidArray(s),
							//getInvalidArray(s),
							false);
				}
			}
		}
	}
	this->GetView()->Update();
}


void PreSelectionSet::updateSelectionEntity()
{
	int size=this->GetSize();
	QWeakPointer<ViewManager> m_ViewManager=m_HQWidget->getViewManager();
	BaseItem* tmpEntity;
	QList<BaseItem*> entities;
	for(int i=0;i<size;++i){
		HC_KEY select=this->GetAt(i);
		tmpEntity=getRelatedBaseItem(select);

		if(tmpEntity){
			entities.push_back(tmpEntity);
		}
	}
	//if(entities.size()!=0)
	this->ss_notifySetSelection(entities);
}

BaseItem* PreSelectionSet::getRelatedBaseItem( HC_KEY key )
{
	static char	keyType[MVO_BUFFER_SIZE];
	HC_Show_Key_Type(key, keyType);

	QWeakPointer<ViewManager> m_ViewManager=m_HQWidget->getViewManager();
	if(!streq("segment", keyType))
		key=HC_KShow_Owner_By_Key(key);

	BaseItem* tmpEntity;
	for(int i=0;i<3;++i){
		tmpEntity=m_ViewManager.data()->getBaseItem(key);
		//当此层没有找到对应的Entity时，继续向上搜索一层，解决Cylinder,Sphere,Cone等不得鼠标拾取的问题。2012.8.30.Jerry
		if(!tmpEntity){
			HC_Open_Segment_By_Key(key);
			key=HC_Open_Segment("..");
			HC_Close_Segment();
			HC_Close_Segment();
		}
		else
			break;
	}
	return tmpEntity;
}

void PreSelectionSet::updateSelectionNodeElem()
{

}

void PreSelectionSet::updateProjectSelection()
{
	int size=this->GetSize();
	if(size==0)
		return;

	switch(myProjectSelector()->getSelectionType())
	{
	case ProjectSelector::ST_Entity:
		updateSelectionEntity();
		break;;
	case ProjectSelector::ST_Node:
	case ProjectSelector::ST_Element:
		updateSelectionNodeElem();
		break;
	}

}
void PreSelectionSet::MySelect( HC_KEY key, int num_include_keys,HC_KEY* include_keys,bool emit_message/*=true*/ )
{
	char	keyType[MVO_BUFFER_SIZE];

	if (GetSelectionLevel() == HSelectSegment) // nonzero if NOT a segment
	{
		// the key is to a geometric entity.  If we are in segment selection mode,
		// then we need to get the key to its parent segment.

		HC_Show_Key_Type(key, keyType);

		if (!streq("segment", keyType))
		{
			char segname[MVO_BUFFER_SIZE];
			HC_KEY segkey;

			segkey = HC_KShow_Owner_By_Key(key);
			HC_Show_Owner_By_Key(key, segname);

			// climb up one more level if this is the temporary highlight key
			if( IsHighlightSegment(segkey) )
			{
				segkey = HC_KShow_Owner_By_Key(segkey);
				HC_Show_Owner_By_Key(segkey, segname);
			}
			key=segkey;
		}
	}

	HSelectionSet::Select(key, num_include_keys, include_keys, emit_message);
}
void PreSelectionSet::Select(HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message)
{
	MySelect(key,num_include_keys,include_keys,emit_message);

	if(!this->getSubject()->isOperating()){
		updateProjectSelection();
	}
	
}


void PreSelectionSet::DeSelect(HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message)
{
	char	keyType[MVO_BUFFER_SIZE];

	if ( GetSelectionLevel() == HSelectSegment) // nonzero if NOT a segment
	{
		// the key is to a geometric entity.  If we are in segment selection mode,
		// then we need to get the key to its parent segment.

		HC_Show_Key_Type(key, keyType);

		if (!streq("segment", keyType))
		{
			key = HC_KShow_Owner_By_Key(key);
			// climb up one more level if this is the temporary highlight key
			if( IsHighlightSegment(key) )
				key = HC_KShow_Owner_By_Key(key);
		}

	}

	HSelectionSet::DeSelect(key, num_include_keys, include_keys, emit_message);
}


bool PreSelectionSet::IsSelected(HC_KEY key, int num_include_keys, HC_KEY * include_keys)
{
	char	keyType[MVO_BUFFER_SIZE];

	if (GetSelectionLevel() == HSelectSegment) // nonzero if NOT a segment
	{
		// the key is to a geometric entity.  If we are in segment selection mode,
		// then we need to get the key to its parent segment.

		HC_Show_Key_Type(key, keyType);

		if (!streq("segment", keyType))
		{
			key = HC_KShow_Owner_By_Key(key);

			// climb up one more level if this is the temporary highlight key
			if( IsHighlightSegment(key) )
				key = HC_KShow_Owner_By_Key(key);
		}

	}

	return HSelectionSet::IsSelected(key, num_include_keys, include_keys);

}

// NOTE: This function is depricated
void PreSelectionSet::Select(HC_KEY key, const char* segpath, HC_KEY include_key, HC_KEY includer_key, bool emit_message)
{
	char	keyType[MVO_BUFFER_SIZE];

	if (GetSelectionLevel() == HSelectSegment) // nonzero if NOT a segment
	{
		// the key is to a geometric entity.  If we are in segment selection mode,
		// then we need to get the key to its parent segment.
		HC_Show_Key_Type(key, keyType);

		if (!streq("segment", keyType))
			key = HC_KShow_Owner_By_Key(key);
	}

	HSelectionSet::Select(key, segpath, include_key, includer_key, emit_message);

	if (emit_message)
		m_pView->EmitSelectMessage(key,true);
	updateProjectSelection();
}

void PreSelectionSet::Select( HSelectionItem * new_sel, bool emit_message /*= false*/ )
{
	HSelectionSet::Select(new_sel,emit_message);
}



void PreSelectionSet::DeSelect(HC_KEY key, bool emit_message)
{
	char	keyType[MVO_BUFFER_SIZE];

	if (GetSelectionLevel() == HSelectSegment) // nonzero if NOT a segment
	{
		// the key is to a geometric entity.  If we are in segment selection mode,
		// then we need to get the key to its parent segment.
		HC_Show_Key_Type(key, keyType);

		if (!streq("segment", keyType))
			key = HC_KShow_Owner_By_Key(key);	
	}

	HSelectionSet::DeSelect(key);

	if (emit_message)
		m_pView->EmitSelectMessage(key,false);
		
	updateProjectSelection();

}

void PreSelectionSet::SelectSubentity( HC_KEY key, int num_include_keys, HC_KEY * include_keys, 
	int count, const int * faces/*=0*/, const int * vertex1/*=0*/, const int * vertex2/*=0*/, bool emit_message/*=false*/ )
{
	m_HQWidget->setSelectSubNode(*vertex1);

	ProjectSelector::SelectionType selectionType=myProjectSelector()->getSelectionType();
	if( (selectionType==ProjectSelector::ST_Node)
		|| (selectionType==ProjectSelector::ST_Element))
	{
		BaseItem* selectedItem=getRelatedBaseItem(key);
		if(selectedItem && selectedItem->getCategory()==TDY_PRE_CATE_FEMPART){
			if(selectionType==ProjectSelector::ST_Node){
				SelectionNodeElem selectionNodes;
				selectionNodes.item=selectedItem;
				selectionNodes.indices.push_back(vertex1[0]);
				this->ss_notifySetSelectionNodes(selectionNodes);
			}
			else{
				SelectionNodeElem selectionNodes;
				selectionNodes.item=selectedItem;
				selectionNodes.indices.push_back(faces[0]);
				this->ss_notifySetSelectionElements(selectionNodes);
			}

		}
	}


	HSelectionSet::SelectSubentity(key,num_include_keys,include_keys,count,faces,vertex1,vertex2,emit_message);
}



















