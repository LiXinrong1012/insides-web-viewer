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
 * $Id: PointCloudMasterNode.cpp,v 1.3 2010-05-04 22:42:42 chad Exp $
 */

#include "PointCloudMasterNode.h"

#include <assert.h>

PointCloudMasterNode::PointCloudMasterNode ( PointCloudWorld * pcw_in, unsigned int master_node_size_in ) {
	m_pcw = pcw_in;
	m_bpos = 0;

	m_master_node_size = OOC_MAX_FILE_SIZE;
	if (master_node_size_in != 0)
		m_master_node_size = master_node_size_in;

	m_fpos = 0;
	
	m_fid = 0;
	m_file = NULL;
}

PointCloudMasterNode::~PointCloudMasterNode () {
	if (m_bpos) { 
		if (m_file == NULL) {
    		wchar_t *master_node_file_name = new wchar_t [m_pcw->GetNodeFileNameSize() + 1];	
    		m_pcw->GetMasterNodeFileName(m_fid, master_node_file_name);
    		m_file = wfopen(master_node_file_name, L"wb");
			assert(m_file != NULL);
    		delete [] master_node_file_name;
		}

		fwrite(m_buffer, 1, m_bpos, m_file);
	}

	assert(m_file != NULL);
	fclose(m_file);
}

void PointCloudMasterNode::ConcatenateNode ( VCharArray & in_node_buffer, unsigned int alter & out_file_id, 
	unsigned int alter & out_offset, unsigned int alter & out_num_bytes )
{
	out_num_bytes = in_node_buffer.Count();

	if (m_fpos + m_bpos + out_num_bytes > m_master_node_size) {
		fwrite(m_buffer, 1, m_bpos, m_file);
		m_fpos += m_bpos;

		fclose(m_file);
		m_file = NULL;
		m_fpos = 0;
		m_fid++;
		m_bpos = 0;
	}

	out_file_id = m_fid;
	out_offset = m_fpos + m_bpos;

	unsigned int num_bytes_written = out_num_bytes;
	if (m_bpos + out_num_bytes > OOC_BUFFER_CHUNK_SIZE)
		num_bytes_written = OOC_BUFFER_CHUNK_SIZE - m_bpos;

	memcpy(m_buffer + m_bpos, (char *)in_node_buffer, num_bytes_written);

	m_bpos += num_bytes_written; 

	if (num_bytes_written < out_num_bytes) {
		assert(m_bpos == OOC_BUFFER_CHUNK_SIZE);

		if (m_file == NULL) {
    		wchar_t *master_node_file_name = new wchar_t [m_pcw->GetNodeFileNameSize() + 1];	
    		m_pcw->GetMasterNodeFileName(m_fid, master_node_file_name);
    		m_file = wfopen(master_node_file_name, L"wb");
			assert(m_file != NULL);
    		delete [] master_node_file_name;
    	}
                                                                                                 
    	fwrite(m_buffer, 1, m_bpos, m_file);
    	m_fpos += m_bpos;

		m_bpos = 0;

		assert(out_num_bytes - num_bytes_written < OOC_BUFFER_CHUNK_SIZE);
		memcpy(m_buffer, (char *)in_node_buffer + num_bytes_written, out_num_bytes - num_bytes_written);

		m_bpos += out_num_bytes - num_bytes_written;
	}
}

