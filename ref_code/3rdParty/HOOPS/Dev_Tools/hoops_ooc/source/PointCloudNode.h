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
 * $Id: PointCloudNode.h,v 1.5 2009-03-11 17:53:32 chad Exp $
 */

#ifndef POINTCLOUDNODE_H
#define POINTCLOUDNODE_H

#ifndef _MSC_VER
#include <unistd.h>
#endif

#include "BStream.h"
#include "BOpcodeHandler.h"
#include "PointCloudCommon.h"

class TK_Point_Cloud_Node: public TK_User_Data {
private:
	PCPoint *	m_point_list;
	int			m_num_points;
	int			m_current_point;
	int			m_sub_stage;

public:
	TK_Point_Cloud_Node ();
	~TK_Point_Cloud_Node ();
	
	TK_Status Read ( BStreamFileToolkit & tk ) alter;
	TK_Status Execute ( BStreamFileToolkit & tk ) alter;
	
	TK_Status Write ( BStreamFileToolkit & tk ) alter;
	TK_Status Interpret ( BStreamFileToolkit & tk, ID_Key key, int variant = 0 ) alter;
	
	void Reset () alter;

	void SetPointList ( int num_points_in, PCPoint * point_list_in ) {
		m_num_points = num_points_in;
		m_point_list = point_list_in;
	};
};

#endif // POINTCLOUDNODE_H
