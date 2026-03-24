/*
 * Copyright (c) 2009 by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.	 Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: StreamFilePointContainer.h,v 1.7 2009-10-16 00:26:59 chad Exp $
 */

#ifndef STREAMFILEPOINTCONTAINER_H
#define STREAMFILEPOINTCONTAINER_H

#include "vlist.h"
#include "vhash.h"

#include "vbsp.h"

#include "PointCloudCommon.h"

class OOCPointList;

class PointBSPItem : public BSPItem<PCPoint *> {
public:
	PointBSPItem ( PCPoint * cpt_in = 0 );
	
	virtual ~PointBSPItem ();
	
	virtual PCPoint * GetItem () { return m_cpt; };
	PCPoint const * GetItem () const { return m_cpt; };
	virtual float const * GetItemBounds () { return m_bounds; };
	
	void Initialize ( PCPoint * cpt_in );
	
protected:
	PCPoint * 	m_cpt;
	float		m_bounds[6];
};

class StreamFilePointContainer : public BSPNodeItemContainer<PCPoint *> {
public:
	// BSPNodeItemContainer inherited functions

	StreamFilePointContainer ( float const bbox_in[6], int depth_in, void * container_data_in );
	virtual ~StreamFilePointContainer ();
	
	virtual bool AddItem ( PCPoint * item, float const item_bounds[6] = 0 );
	virtual int Count () { return m_num_points; };
	
	class iterator : public BSPNodeItemContainer<PCPoint *>::iterator {
	public:
		iterator ( OOCPointList * ooc_point_list_in = 0, int index_in = 0 );
		
		// pre-increment
		iterator operator ++ ();
		// post-increment
		iterator operator ++ ( int );
		
		bool operator == ( iterator const & rhs );
		bool operator != ( iterator const & rhs );
		
		virtual PointBSPItem * operator * ();
		
		iterator operator = ( iterator rhs );
		
	protected:
		OOCPointList * 	m_ooc_point_list;
		int				m_index;
		PointBSPItem 	m_cpt_bsp_item;
	};
	
	iterator begin ();
	iterator end ();

	// Class-specific functions

	void GetPointList ( int & count_out, PCPoint *& point_list_out );

	void DeletePointList ();
	
	void GetBBox ( float alter * bbox_out ) {
		memcpy(bbox_out, this->m_bbox, 6 * sizeof(float));
	};
	
protected:
	float				m_bbox[6];
	int					m_depth;
	PointCloudWorld * 	m_pcw;
	OOCPointList *		m_ooc_point_list;
	int					m_num_points;
	bool				m_should_compare;
};

#endif // STREAMFILEPOINTCONTAINER_H
