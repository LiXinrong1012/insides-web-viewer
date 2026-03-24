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
 * $Id: PointCloudIndex.h,v 1.27 2010-10-19 22:05:02 chad Exp $
 */

#ifndef POINTCLOUDINDEX_H
#define POINTCLOUDINDEX_H

#include "hmutex.h"


#include "BStream.h"
#include "BOpcodeHandler.h"

#include "PointCloudCommon.h"

#include "varray.h"
#include "vbsp.h"
#include "vlist.h"

#include "hc.h"
#include "hic.h"

int const		LOD_POINT_COUNT_CUTOFF		= 500;

class StreamFilePointContainer;
class PointCloudStreamFileToolkit;

typedef BSPNodeMetadata<PCPoint *, StreamFilePointContainer> BSPMetadata;
typedef VArray<PCPoint> PointList;
typedef VList<PointList *> PointListList;
typedef VList<int> PropagationList;
typedef VArray<TreeTraversal> SegmentList;
typedef VArray<float> BBoxList;
typedef VArray<unsigned int> MasterNodeDataList;

class PointCloudMasterNode;

// this stores data when 
class PointCloudIndexNodeData {
protected:
	PointCloudWorld *				m_pcw;
	wchar_t *						m_index_file_name;	
	StreamFilePointContainer * 		m_container;	   			// the container we are currently working with (possibly null)
	float							m_bbox[6];		   			// the bounding box we are currently working with
	unsigned int					m_fid;						// file id of current node
	unsigned int					m_offset;					// file offset for current node
	unsigned int					m_num_bytes;				// size of file for current node
	PointCloudStreamFileToolkit * 	m_index_tk;			   		// toolkit for writing out the index
	PointCloudStreamFileToolkit * 	m_node_tk;					// toolkit for writing out the nodes
	TreeTraversal					m_traversal_state;			// traversal state when walking BSP
	BSPMetadata *					m_node_metadata;			// BSP node metadata
	int								m_node_shell_size;			// number of points to (try to) have at each node
	int								m_node_shell_cutoff;		// minimum number of points to have in a node, otherwise, 
																//   collapse into parent
	PointListList					m_lod_point_list_list; 		// list of lod point lists (one per parent node)
	PointList 						m_node_point_list;			// list of points that are living in a particular node
	PropagationList					m_propagation_amount;		// number of points to propagate upward
	SegmentList						m_segment_list;				// list of segments in OOC file
	BBoxList						m_bbox_list;				// list of bboxes for external references
	MasterNodeDataList				m_mnd_list;					// list of file id's, file offsets and file sizes for each node
	VCharArray						m_node_buffer;
	float							m_min_intensity;
	float							m_max_intensity;

	int								m_rand48_seed;
	static float					m_uniform_rand[1024];

	uint64_t						m_nodes_processed;
	uint64_t						m_num_files_written;

	PointCloudMasterNode *			m_pcmn;

	float unirand ();
	
public:
	PointCloudIndexNodeData ( PointCloudWorld * pcw_in, float min_intensity_in, float max_intensity_in );
	~PointCloudIndexNodeData ();
	
	void SetContainer ( StreamFilePointContainer * container_in ) alter { m_container = container_in; };
	StreamFilePointContainer * GetContainer () const { return m_container; };
	
	void SetBBox ( float const bbox_in[6] ) alter { memcpy(m_bbox, bbox_in, 6 * sizeof(float)); };
	void GetBBox ( float alter bbox_out[6] ) const { memcpy(bbox_out, m_bbox, 6 * sizeof(float)); };

	void GetMasterNodeData ( unsigned int & alter fid_out, unsigned int & alter offset_out, unsigned int & alter num_bytes_out ) {
		fid_out = m_fid;
		offset_out = m_offset;
		num_bytes_out = m_num_bytes;
	};
	
	bool GetIsEnteringNode () const { return ((m_traversal_state % 2) == 0); };
	
	TreeTraversal GetTreeTraversalState () const { return m_traversal_state; };
	void SetTreeTraversalState ( TreeTraversal traversal_state_in ) alter { m_traversal_state = traversal_state_in; };

	void SetBSPNodeMetadata ( BSPMetadata * node_metadata_in ) alter { m_node_metadata = node_metadata_in; };

	void Update () alter;
	void ExportPointCloudIndex () alter;
	
	// TODO: this should probably be a const function
	void GetNodePointList ( PointList *& node_point_list_out ) { node_point_list_out = &m_node_point_list; };

	float GetMinIntensity () const { return m_min_intensity; };
	float GetMaxIntensity () const { return m_max_intensity; };
};

class NodeData {
public:
	NodeData ( PointCloudWorld * pcw ) 
		: m_pcw(pcw), m_fid(0), m_offset(0), m_num_bytes(0)
		{};
	~NodeData () {};

	PointCloudWorld * GetWorld () { return m_pcw; };

	void SetFileID ( unsigned int fid_in ) { m_fid = fid_in; };
	unsigned int GetFileID () { return m_fid; };

	void SetOffset ( unsigned int offset_in ) { m_offset = offset_in; };
	unsigned int GetOffset () { return m_offset; };

	void SetByteCount ( unsigned int num_bytes_in ) { m_num_bytes = num_bytes_in; };
	unsigned int GetByteCount () { return m_num_bytes; };

protected:
	PointCloudWorld *	m_pcw;
	unsigned int		m_fid;
	unsigned int		m_offset;
	unsigned int 		m_num_bytes;
};

class KeyDataPair {
public:
	KeyDataPair ( PointCloudWorld * pcw, HC_KEY segment_key, NodeData * node_data ) 
		: m_pcw(pcw), m_segment_key(segment_key), m_node_data(node_data)
		{};
	~KeyDataPair () {};

	PointCloudWorld * GetWorld () { return m_pcw; };
	HC_KEY GetSegmentKey () { return m_segment_key; };
	NodeData * GetNodeData () { return m_node_data; };

protected:
	PointCloudWorld *	m_pcw;
	HC_KEY				m_segment_key;
	NodeData *			m_node_data;
};

typedef VList<KeyDataPair *> KeyDataList;
typedef VList<NodeData *> NodeDataList;
typedef VHash<HThreadID, PointCloudStreamFileToolkit *> ThreadToolkitHash;
typedef VHash<HThreadID, VCharArray *> ThreadWorkBufferHash;
typedef VHash<HThreadID, FILE **> ThreadFileHandleHash;

class PointCloudIndexPopulateData {
public:
	PointCloudIndexPopulateData ( PointCloudWorld * pcw_in );
	virtual ~PointCloudIndexPopulateData ();
	
	KeyDataList * GetKeyDataList () const { return m_key_data_list; };
	NodeDataList * GetNodeDataList () const { return m_node_data_list; };
	PointCloudStreamFileToolkit * GetNodeToolkit ( HThreadID id = 0 );
	char * GetWorkBuffer ( HThreadID id, unsigned int num_bytes );
	
	void LockKeyDataList();
	void UnlockKeyDataList();

	FILE * GetFilePointer ( HThreadID id, unsigned int i );

	volatile int		m_key_data_list_thread_exiting;
	HM_Semaphore		m_key_data_list_semaphore;
	HMutex				m_key_data_list_mutex;
	HMutex				m_master_node_mutex;
	PointCloudWorld *	m_pcw;

protected:
	static void PopulateCleanup ( KeyDataPair * key_data_pair, void * user_data );
	static void FileHandleCleanup ( FILE ** file_handles, HThreadID id, void const * const user_data );

	KeyDataList * 			m_key_data_list;
	HThreadHandle *			m_key_data_list_thread;
	NodeDataList *			m_node_data_list;
	ThreadToolkitHash * 	m_node_tk_hash;
	ThreadWorkBufferHash *	m_work_buffer_hash;
	ThreadFileHandleHash *	m_file_handle_hash;
};

// this signals a new segment/node in the index and outputs the corresponding bounding box for the segment/node
class TK_Point_Cloud_Index_Open_Segment : public TK_Open_Segment {
protected:
	PointCloudWorld *			m_pcw;
	int							m_meta_stage;
	int							m_meta_sub_stage;
	PointCloudIndexNodeData * 	m_node_data;
	bool						m_skip_writing;
	float						m_bbox[6];
	int							m_node_dir_prefix_len;
	char *						m_node_dir_prefix;
	static bool					m_has_defined_callback;
	
public:	
	TK_Point_Cloud_Index_Open_Segment ( PointCloudWorld * pcw_in, PointCloudIndexNodeData * node_data_in = 0 );
	~TK_Point_Cloud_Index_Open_Segment ();
	
	TK_Status Read ( BStreamFileToolkit & tk ) alter;
	TK_Status Execute ( BStreamFileToolkit & tk ) alter;
	
	TK_Status Write ( BStreamFileToolkit & tk ) alter;
	TK_Status Interpret ( BStreamFileToolkit & tk, ID_Key key, int variant = 0 ) alter;
	
	void Reset () alter;
};

// this signals the end of a segment/node in the index
class TK_Point_Cloud_Index_Close_Segment : public TK_Close_Segment {
protected:
	PointCloudWorld *			m_pcw;
	int							m_meta_stage;
	int							m_meta_sub_stage;
	PointCloudIndexNodeData * 	m_node_data;
	bool						m_skip_writing;
	unsigned int				m_fid;
	unsigned int				m_offset;
	unsigned int 				m_num_bytes;
	
public:
	TK_Point_Cloud_Index_Close_Segment ( PointCloudWorld * pcw_in, PointCloudIndexNodeData * node_data_in = 0 );
	~TK_Point_Cloud_Index_Close_Segment ();
	
	TK_Status Read ( BStreamFileToolkit & tk ) alter;
	TK_Status Execute ( BStreamFileToolkit & tk ) alter;
	
	TK_Status Write ( BStreamFileToolkit & tk ) alter;
	TK_Status Interpret ( BStreamFileToolkit & tk, ID_Key key, int variant = 0 ) alter;
	
	void Reset () alter;
};

void PopulateNode ( HIC_Rendition const * nr, HC_KEY key );
void LoadNode ( KeyDataPair * key_data_pair );

#endif // POINTCLOUDINDEX_H
