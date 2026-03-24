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
 * $Id: StreamFilePointContainer.cpp,v 1.8 2009-10-16 00:26:59 chad Exp $
 */

#include "StreamFilePointContainer.h"

#include "OOCPointList.h"
#include "PointCloudCommon.h"
#include "PointCloudNode.h"
#include "PointCloudNodeRandomized.h"

PointBSPItem::PointBSPItem ( PCPoint * cpt_in ) {
	Initialize(cpt_in);
}
	
PointBSPItem::~PointBSPItem () {}

void PointBSPItem::Initialize ( PCPoint * cpt_in ) {
	m_cpt = cpt_in;
	if (m_cpt) {
		m_bounds[0] = m_bounds[3] = m_cpt->pt.x;
		m_bounds[1] = m_bounds[4] = m_cpt->pt.y;
		m_bounds[2] = m_bounds[5] = m_cpt->pt.z;
	}
	else {
		m_bounds[0] = m_bounds[1] = m_bounds[2] = m_bounds[3] = m_bounds[4] = m_bounds[5] = 0.0f;
	}
}

/*****************************************************************************************************/

StreamFilePointContainer::StreamFilePointContainer ( float const bbox_in[6], int depth_in, void * container_data_in ) {
	memcpy(m_bbox, bbox_in, 6 * sizeof(float));
	m_depth = depth_in;
	m_pcw = reinterpret_cast<PointCloudWorld *>(container_data_in);
	m_ooc_point_list = new OOCPointList(m_pcw, this);
	m_num_points = 0;
	m_should_compare = false;

	// if the bounding box is sufficiently small, we should check for duplicate points
	float x_precision = (fabs(m_bbox[3]) < FEPSILON && fabs(m_bbox[0]) < FEPSILON ? 0.0f : 
		(m_bbox[3] - m_bbox[0]) / (fabs(m_bbox[3]) > FEPSILON ? fabs(m_bbox[3]) : fabs(m_bbox[0]))), 
		y_precision = (fabs(m_bbox[4]) < FEPSILON && fabs(m_bbox[1]) < FEPSILON ? 0.0f : 
		(m_bbox[4] - m_bbox[1]) / (fabs(m_bbox[4]) > FEPSILON ? fabs(m_bbox[4]) : fabs(m_bbox[1]))), 
		z_precision = (fabs(m_bbox[5]) < FEPSILON && fabs(m_bbox[2]) < FEPSILON ? 0.0f : 
		(m_bbox[5] - m_bbox[2]) / (fabs(m_bbox[5]) > FEPSILON ? fabs(m_bbox[5]) : fabs(m_bbox[2])));

	if (x_precision < 1e-5 && y_precision < 1e-5 && z_precision < 1e-5)
		m_should_compare = true;
}

StreamFilePointContainer::~StreamFilePointContainer () {
	if (m_ooc_point_list)
		delete m_ooc_point_list;
}
	
bool StreamFilePointContainer::AddItem ( PCPoint * m_item, float const item_bounds[6] ) {
	bool appended_item = m_ooc_point_list->Append(m_item, m_should_compare);

	if (appended_item)
		m_num_points++;

	return appended_item;
}

StreamFilePointContainer::iterator::iterator ( OOCPointList * ooc_point_list_in, int index_in ) {
	m_ooc_point_list = ooc_point_list_in;
	m_index = index_in;
	if (m_ooc_point_list)
		m_cpt_bsp_item.Initialize((*m_ooc_point_list)[m_index]);
}

StreamFilePointContainer::iterator StreamFilePointContainer::iterator::operator ++ () {
	m_index++;
	m_cpt_bsp_item.Initialize((*m_ooc_point_list)[m_index]);
	return *this;
}

StreamFilePointContainer::iterator StreamFilePointContainer::iterator::operator ++ ( int ) {
	iterator tmp(m_ooc_point_list, m_index);
	m_index++;
	m_cpt_bsp_item.Initialize((*m_ooc_point_list)[m_index]);
	return tmp;
}

bool StreamFilePointContainer::iterator::operator == ( StreamFilePointContainer::iterator const & rhs ) {
	if (m_cpt_bsp_item.GetItem() == rhs.m_cpt_bsp_item.GetItem())
		return true;
	else
		return false;
}

bool StreamFilePointContainer::iterator::operator != ( StreamFilePointContainer::iterator const & rhs ) {
	return !(*this == rhs);
}

PointBSPItem * StreamFilePointContainer::iterator::operator * () {
	return &m_cpt_bsp_item;
}

StreamFilePointContainer::iterator StreamFilePointContainer::iterator::operator = ( StreamFilePointContainer::iterator rhs ) {
	m_ooc_point_list = rhs.m_ooc_point_list;
	m_index = rhs.m_index;
	m_cpt_bsp_item.Initialize(rhs.m_cpt_bsp_item.GetItem());
	return *this;
}
	
StreamFilePointContainer::iterator StreamFilePointContainer::begin () {
	return StreamFilePointContainer::iterator(m_ooc_point_list);
}

StreamFilePointContainer::iterator StreamFilePointContainer::end () {
	return StreamFilePointContainer::iterator();
}

void StreamFilePointContainer::GetPointList ( int & count_out, PCPoint *& point_list_out ) {
	m_ooc_point_list->GetPointList(count_out, point_list_out);
}

void StreamFilePointContainer::DeletePointList () {
	delete m_ooc_point_list;
	m_ooc_point_list = 0;
}
