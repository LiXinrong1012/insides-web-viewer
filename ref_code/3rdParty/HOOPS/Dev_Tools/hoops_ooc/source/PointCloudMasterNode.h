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
 * $Id: PointCloudMasterNode.h,v 1.3 2010-05-04 22:42:42 chad Exp $
 */

#ifndef POINTCLOUDMASTERNODE_H
#define POINTCLOUDMASTERNODE_H

#include "PointCloudCommon.h"
#include "varray.h"

class PointCloudMasterNode {
private:
	PointCloudWorld * 	m_pcw;
	char 				m_buffer[OOC_BUFFER_CHUNK_SIZE];
	unsigned int 		m_bpos;
	unsigned int 		m_master_node_size;
	unsigned int 		m_fpos;
	unsigned int 		m_fid;
	FILE *				m_file;

public:
	PointCloudMasterNode ( PointCloudWorld * pcw_in, unsigned int master_node_size_in = 0 );
	~PointCloudMasterNode ();

	void ConcatenateNode ( VCharArray & in_node_buffer, unsigned int alter & out_file_id, unsigned int alter & out_offset,
		unsigned int alter & out_num_bytes );
};

#endif // POINTCLOUDMASTERNODE_H

