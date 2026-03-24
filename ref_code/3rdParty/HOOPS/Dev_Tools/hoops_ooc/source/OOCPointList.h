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
* $Id: OOCPointList.h,v 1.5 2009-10-16 00:26:59 chad Exp $
*/

#ifndef OOCPOINTLIST_H
#define OOCPOINTLIST_H

class PointCloudWorld;
class StreamFilePointContainer;
class PCPoint;
template <typename T> class BSPItem;
class LRUList;
class LRUListNode;
class BackingFileData;
template <typename T> class VList;
typedef VList<BackingFileData *> BFDList;
class TempFileToolkit;


class OOCPointList {
public:
	OOCPointList ( PointCloudWorld * pcw_in, StreamFilePointContainer * container_in );
	~OOCPointList ();

	bool Append ( PCPoint * new_point, bool should_compare = false );
	
	void SetLRUNode ( LRUListNode * lru_node_in ) { m_lru_node = lru_node_in; };
	LRUListNode * GetLRUNode () { return m_lru_node; };
	
	PCPoint * operator [] ( int const location );

	void GetPointList ( int & count_out, PCPoint *& point_list_out );

private:
	void EnsureSize ();
	void EnsurePointsInMemory ( bool allow_appending = false );
	void CacheLRULists ();

	PointCloudWorld *			m_pcw;
	StreamFilePointContainer *	m_container;
	PCPoint *					m_point_list;
	int							m_total_count;
	int							m_current_count;
	int							m_size;
	bool						m_can_cache;
	LRUListNode *				m_lru_node;

	BFDList *					m_bfd_list;

	static LRUList *			m_lru_point_list_list;
	static unsigned long		m_ref_count;
	static TempFileToolkit *	m_temp_file_tk;
};

#endif // OOCPOINTLIST_H
