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
 * $Id: PointCloudNodeRandomized.h,v 1.1 2009-02-12 21:22:40 chad Exp $
 */

#ifndef POINTCLOUDNODERANDOMIZED_H
#define POINTCLOUDNODERANDOMIZED_H

#include "BStream.h"
#include "BOpcodeShell.h"

class PointCloudIndexNodeData;

class TK_Point_Cloud_Node_Randomized : public TK_Shell {
protected:
 	PointCloudIndexNodeData *	m_node_data;
	
public:
	TK_Point_Cloud_Node_Randomized ( PointCloudIndexNodeData * node_data_in = 0 );
	~TK_Point_Cloud_Node_Randomized ();
	
	TK_Status Execute ( BStreamFileToolkit & tk ) alter;
	
	TK_Status Interpret ( BStreamFileToolkit & tk, ID_Key key, int variant = 0 ) alter;
};

#endif // POINTCLOUDNODERANDOMIZED_H
