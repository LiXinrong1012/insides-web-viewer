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
// $Header: /files/homes/master/cvs/hoops_master/qthoopsrefapp_4/HQSegmentTree.cpp,v 1.4 2008-12-18 00:02:20 chad Exp $
//


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#ifdef check
#undef check
#endif

#include <QtCore>
#include <QtGui>

#include "HUtility.h"
#include "HQApplication.h"
#include "HQSegmentTree.h"

#include "hc.h"


//////////////////////////////////////////////////////////////////
// HQSegmentTree
HQSegmentTree::HQSegmentTree(QWidget * p):QTreeWidget(p) 
{
	header()->hide();
	setFrameStyle(QFrame::StyledPanel|QFrame::Sunken);
	setLineWidth(2);
	setMinimumWidth(1);
	setMinimumHeight(1);
	setRootIsDecorated(true);
//	setShowToolTips(true);
//	setTreeStepSize(16);
//	setItemMargin(0);
//	addColumn("item");
	setColumnCount(1);
	QStringList headers;
	headers << tr("Segment Hierarchy");
	setHeaderLabels(headers);

	last_selected=0;

	connect(this, SIGNAL(clicked(QListViewItem*)), this, SLOT(item_clicked(QListViewItem*))); 
	connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(item_double_clicked(QTreeWidgetItem*))); 
	connect(this, SIGNAL(rightButtonClicked(QListViewItem*, const QPoint &, int)), this, SLOT(item_right_clicked(QListViewItem*,const QPoint &,int))); 
	connect(this, SIGNAL(selectionChanged(QListViewItem*)), this, SLOT(item_selection_changed(QListViewItem*))); 

}

HQSegmentTree::~HQSegmentTree()
{
	;
}

HQSegmentItem * HQSegmentTree::InsertItem(HQSegmentItem * parent, const char * label, 
									  int image_index, int selected_image_index, 
									  long item_data, bool expanded)
{	
	HQSegmentItem * item;

	if( !parent)
		item = new HQSegmentItem(this, label, image_index, selected_image_index, item_data, expanded);
	else
		item = new HQSegmentItem(parent, label, image_index, selected_image_index, item_data, expanded);

	return item;
}


void HQSegmentTree::SelectItem(HQSegmentItem * item)
{
	if(!item)
		clearSelection();
	else
		setItemSelected(item, true);
}

HQSegmentItem* HQSegmentTree::GetSelectedItem()
{
	return (HQSegmentItem*) currentItem();
}

/*
HQSegmentItem* HQSegmentTree::GetRootItem()
{
    QListViewItemIterator it(this);
	HQSegmentItem* item = (HQSegmentItem*) it.current();
	return item;
}


HQSegmentItem* HQSegmentTree::FindItemByKey(long data)
{
    QListViewItemIterator it(this);
	for ( ; it.current(); ++it ) {
		  HQSegmentItem* item = (HQSegmentItem*) it.current();
		  if(item->data == data) 
		  	return item;
	} 
	return 0;
}
*/

long HQSegmentTree::GetItemData(HQSegmentItem * item)
{
	return item->data;
}

void HQSegmentTree::SetItemImage(HQSegmentItem * item, int image_index, int selected_image_index)
{
	item->index = image_index;
	item->selected_index = selected_image_index;
	if(isItemSelected(item))
		item->SetImage(item->selected_index);
	else
		item->SetImage(item->index);
}

void HQSegmentTree::item_clicked(QTreeWidgetItem * i)
{
	if(!i) return; 
//	HQSegmentItem * item = (HQSegmentItem *)i;
//	_Module.TreeItemEvent(item->data, TREE_ITEM_LBTN_CLK);
}

void HQSegmentTree::item_double_clicked(QTreeWidgetItem * i)
{
	if(!i) return; 
	HQSegmentItem * item = (HQSegmentItem *)i;
	//item->setOpen(true); 
	setItemExpanded(item, true);

//	_Module.TreeItemEvent(item->data, TREE_ITEM_LBTN_DBLCLK);
}

void HQSegmentTree::item_right_clicked(QTreeWidgetItem * i, const QPoint & p, int c)
{
	if(!i) return; 
//	HQSegmentItem * item = (HQSegmentItem *)i;
//	_Module.TreeItemEvent(item->data, TREE_ITEM_RBTN_CLK);
}

void HQSegmentTree::ContextMenu(HQSegmentItem * item, int menu_type)
{
}

void HQSegmentTree::item_selection_changed(QTreeWidgetItem * i)
{
	HQSegmentItem * item = (HQSegmentItem *)i;
	item->SetImage(item->selected_index);
	if(last_selected)
		last_selected->SetImage(last_selected->index);
	last_selected=item;

	QRect r(visualItemRect(last_selected));	
	if(r.height() == -1){

		bool need_update=false;

		QTreeWidgetItem *parent=last_selected->parent();
		while(parent){
			if(!isItemExpanded(parent)){
				setItemExpanded(parent, true);
				need_update=true;
			}
			parent=parent->parent();
		}
		if(need_update)
			//updateContents();
			update();
		//int y = itemPos(last_selected);
		//ensureVisible(0,y,0,10000);
	}

}


HQSegmentItem::HQSegmentItem(HQSegmentTree * parent, QString label, int in_index, int in_selected_index, long in_data, bool expanded)
	:QTreeWidgetItem(parent) 
{
	index = in_index;
	selected_index = in_selected_index;
	data = in_data;
	SetImage(index);
	//if(expanded) setOpen(true); 
}

HQSegmentItem::HQSegmentItem(HQSegmentItem * parent, QString label, int in_index, int in_selected_index, long in_data, bool expanded)
	:QTreeWidgetItem(parent) 
{
	index = in_index;
	selected_index = in_selected_index;
	data = in_data;
	SetImage(index);
	//if(expanded) setOpen(true); 
}

void HQSegmentItem::SetImage(int index)
{
//	char icon_name[4096];
//	setPixmap(0,*EQMainWindow::GetMainWindow()->GetPixmap(icon_name));
}

void HQSegmentTree::Construct(HC_KEY base_key)
{
	assert( base_key != INVALID_KEY );

	InsertItemInTree( base_key, 0);
}

//this function inserts a new item into the tree control with it's name (if available) and the tagid
HQSegmentItem * HQSegmentTree::InsertItemInTree(HC_KEY key, HQSegmentItem * parent_item)
{
	HQSegmentItem * item = 0;
	char type[4096];	
	char label[4096];

	HC_Show_Key_Type(key, type);
	if (strstr(type, "segment"))
	{
 		HC_Show_Segment(key, label);
		HC_Parse_String(label,"/",-1,label);
		item = InsertItem( parent_item, label, 0, 0, (long) key, false );
		item->setText(0, label);

		HC_Open_Segment_By_Key(key);
			HC_Begin_Contents_Search(".","segment, include, shell, mesh");
				HC_KEY child_key = INVALID_KEY;
				while (HC_Find_Contents(type, &child_key))
					InsertItemInTree(child_key, item);
			HC_End_Contents_Search();
		HC_Close_Segment();
	}
	else if(strstr(type, "include"))
	{
		sprintf(label, "Include (%ld)", key);
		item = InsertItem( parent_item, label, 0, 0, (long) key, false );

		HC_KEY include_seg_key = HC_KShow_Include_Segment(key);
		InsertItemInTree( include_seg_key, item );
	}
	else
	{
		sprintf(label, "%s (%ld)", type, key);
		item = InsertItem( parent_item, label, 0, 0, (long) key, false );
	}

	return item;
}



