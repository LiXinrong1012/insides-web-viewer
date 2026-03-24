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
 * $Id: PointCloudData.h,v 1.14 2009-11-06 02:03:01 chad Exp $
 */

#ifndef POINTCLOUDDATA_H
#define POINTCLOUDDATA_H

#include <stdio.h>
#include <wchar.h>
#include <string.h>
#ifndef _MSC_VER
#include <unistd.h>
#endif

#include "BStream.h"
#include "BOpcodeHandler.h"

#include "PointCloudCommon.h"
#include "vbsp.h"

class PointCloudStreamFileToolkit;
class StreamFilePointContainer;
class ExtractionData;

typedef VBSP<PCPoint *, StreamFilePointContainer> PointCloudBSP;

#ifdef THREADED_PREPROCESS
#include "hmutex.h"

typedef struct PointBuffer_s{
	PCPoint *	m_buffer;
	int			m_count;
} PointBuffer_t;

template <typename T> class VList;
typedef VList<PointBuffer_t *> PointBufferList;
#endif // THREADED_PREPROCESS

// opcode for parsing the point cloud file, saving out the point data as a binary stream file and reading that stream file back in 
//   for purposes of spatial subdivision
class TK_Point_Cloud_Data : public TK_User_Data {
private:
	PointCloudWorld *		m_pcw;							// "global" PointCloudWorld instance
	FILE *					m_current_point_cloud_file;		// file pointer to current point cloud to be parsed
	char * 					m_read_buffer;					// buffer used for reading in pieces of original point cloud
	wchar_t *				m_index_file_name;				// file name of top-level point cloud index file
	PointCloudFileType		m_point_cloud_file_type;		// original point cloud file type
	float 					m_std_bbox[6];					// bounding box based on the entire point cloud
	float 					m_min_intensity;				// minimum intensity found in point cloud
	float 					m_max_intensity;				// maximum intensity found in point cloud
	float 					m_matrix[16];					// transformation matrix which may not get used depending on file type
	size_t 					m_read_position;				// current position in our internal buffer;
	size_t 					m_amount_read;					// how much data is in our internal buffer;
	bool 					m_success;						// flag indicating results of parsing text
	bool 					m_initial_pass;					// flag indicating initial pass
	bool					m_eof;							// flag indicating there is no more data to examine (end-of-file)o
	bool					m_no_more_reads;				// flag indicating we've read the entire file 
															//   (though it probably hasn't all been processed yet)
	PCPoint					m_cpt;							// a point extracted from the original point cloud
	uint64_t				m_line_number;					// current line number
	uint64_t 				m_valid_point_count;			// number of valid points encountered in the file
	uint64_t 				m_num_points_remaining;			// number of points left to process
	bool					m_need_to_subsample;			// whether or not we need to sub-sample
	uint64_t				m_num_points_sorted;			// number of points actually sorted (may be less than the total number of points in the
															//   point cloud if sub-sampling or bounding box culling is used)

	// we need the BSP to be public if we are doing threaded loading
#ifdef THREADED_PREPROCESS
public:
#endif // THREADED_PREPROCESS

	PointCloudBSP *			m_point_bsp;					// BSP for storing spatially sorted points

#ifdef THREADED_PREPROCESS
private:
#endif // THREADED_PREPROCESS

	off_t 					m_metadata_offset;				// file offset for metadata
	off_t 					m_current_file_position;		// current file position
	                    			            			 
	int 					m_sub_stage;					// sub stage 
	int 					m_sub_sub_stage;				// sub sub stage
	bool 					m_flush_buffer;					// flag to signify we need to flush the buffer (necessary for 
															//   situations where we want to reposition the file pointer, 
															//   but potentially have data that hasn't been written out yet 
															//   because the read/write buffer is not full).             		
	
	static VBSPStatus ExportPointCloudIndexNodes ( TreeTraversal state, StreamFilePointContainer * container, 
												   BSPNodeMetadata<PCPoint *, StreamFilePointContainer> * node_metadata, void * user_data );
	
public:
	TK_Point_Cloud_Data ( PointCloudWorld * pcw_in );
	~TK_Point_Cloud_Data ();
	
	TK_Status Read ( BStreamFileToolkit & tk ) alter;
	TK_Status Execute ( BStreamFileToolkit & tk ) alter;
	
	TK_Status Write ( BStreamFileToolkit & tk ) alter;
	TK_Status Interpret ( BStreamFileToolkit & tk, ID_Key key, int variant = 0 ) alter;
	
	void Reset () alter;
	
	inline void GetBoundingBox ( float alter bbox_out[6] ) const {
		memcpy(bbox_out, m_std_bbox, 6 * sizeof(float));
	};
	
	inline float GetMinIntensity () const { return m_min_intensity; };
	inline float GetMaxIntensity () const { return m_max_intensity; };

#ifdef THREADED_PREPROCESS
	PointBuffer_t *			m_point_buffer;
	PointBufferList *		m_point_buffer_list;
	HMutex					m_point_buffer_list_mutex;
	HThreadHandle			m_point_process_thread;
	size_t					m_bytes_used;
	int						m_current_point_buffer_size;
	bool					m_no_more_points;
#endif // THREADED_PREPROCESS           
};

#endif // POINTCLOUDDATA_H
