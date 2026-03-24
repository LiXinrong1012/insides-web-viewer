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
// $Header: /files/homes/master/cvs/hoops_master/qthoopsrefapp_4/HQSegmentTree.h,v 1.3 2006-08-07 20:38:58 stage Exp $
//


#ifndef HQSEGMENTTREE_H
#define HQSEGMENTTREE_H

#include <QWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include "hc.h"

class HQSegmentItem;

class HQSegmentTree : public QTreeWidget {

    Q_OBJECT

	public:

	HQSegmentTree(QWidget * p);
	~HQSegmentTree();
	
	void Construct(HC_KEY base_key);

	HQSegmentItem * InsertItemInTree(HC_KEY key, HQSegmentItem * parent_item);
	void SelectItem(HQSegmentItem * item);	
//	HQSegmentItem* GetRootItem();
	HQSegmentItem* GetSelectedItem();
//	HQSegmentItem* FindItemByKey(long data);
	long GetItemData(HQSegmentItem * item);
	void SetItemImage(HQSegmentItem * item, int image_index, int selected_image_index);
	HQSegmentItem * InsertItem(HQSegmentItem * parent, const char * label, 
			int image_index, int selected_image_index, long item_data, bool expanded);
	HQSegmentItem * last_selected;
	void ContextMenu(HQSegmentItem * item, int menu_type);

	public slots:
	void item_clicked (QTreeWidgetItem * i);
	void item_double_clicked (QTreeWidgetItem * i);
	void item_right_clicked (QTreeWidgetItem * i, const QPoint & p, int c);
	void item_selection_changed(QTreeWidgetItem * i); 
};

class HQSegmentItem : public QTreeWidgetItem {

	public:
	HQSegmentItem(HQSegmentTree * parent, QString label, int image_index, 
			int selected_image_index, long data, bool expanded);
	HQSegmentItem(HQSegmentItem * parent, QString label, int image_index, 
			int selected_image_index, long data, bool expanded);

	void SetImage(int index);
	void ItemEvent(int event);

	long data;
	int index;
	int selected_index;
};


#endif


