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
* $Id: OOCPointList.cpp,v 1.6 2009-10-16 00:26:59 chad Exp $
*/

#include "OOCPointList.h"

#include "PointCloudCommon.h"
#include "PointCloudNode.h"
#include "PointCloudStreamFileToolkit.h"
#include "StreamFilePointContainer.h"

#include "vhash.h"

class LRUListNode {
	friend class LRUList;
private:
	OOCPointList *	m_ooc_point_list;
	LRUListNode *	m_prev;
	LRUListNode *	m_next;
	
public:
	LRUListNode ( OOCPointList * ooc_point_list_in = 0, LRUListNode * prev_in = 0, LRUListNode * next_in = 0 ) {
		m_ooc_point_list = ooc_point_list_in;
		m_prev = prev_in;
		m_next = next_in;
	};

	~LRUListNode () {};

	OOCPointList * GetItem () { return m_ooc_point_list; };
};

class LRUList {
private:
	LRUListNode *	m_head;
	LRUListNode *	m_tail;
	LRUListNode *	m_cursor;
	unsigned long	m_count;

public:
	LRUList () {
		m_head = 0;
		m_tail = 0;
		m_cursor = 0;
		m_count = 0;
	};

	~LRUList () {
		while (m_head) {
			LRUListNode *temp = m_head;
			m_head = m_head->m_next;
			m_count--;
			if (m_count == 0)
				assert(temp == m_tail);
			delete temp;
		}
		assert(m_count == 0);
	};

	unsigned long Count () {
		return m_count;
	};

	void AddFirst ( OOCPointList * point_list_in ) {
		LRUListNode *new_head_node = new LRUListNode(point_list_in, 0, m_head);
		if (m_head)
			m_head->m_prev = new_head_node;
		else
			m_tail = new_head_node;
		m_head = new_head_node;
		m_count++;

		point_list_in->SetLRUNode(m_head);
	};

	void AddLast ( OOCPointList * point_list_in ) {
		if (!m_head)
			return AddFirst(point_list_in);

		LRUListNode *new_tail_node = new LRUListNode(point_list_in, m_tail, 0);
		m_tail->m_next = new_tail_node;
		m_tail = new_tail_node;
		m_count++;

		point_list_in->SetLRUNode(m_tail);
	};

	void Remove ( OOCPointList * point_list_in ) {
		LRUListNode *list_node = point_list_in->GetLRUNode();
		
		if (!list_node)
			return;

	 	if (list_node->m_prev)
	 		list_node->m_prev->m_next = list_node->m_next;
	 	if (list_node->m_next)
	 		list_node->m_next->m_prev = list_node->m_prev;
	 	if (list_node == m_head)
	 		m_head = list_node->m_next;
	 	if (list_node == m_tail) {
	 		if (m_head)
	 			m_tail = list_node->m_prev;
	 		else
	 			m_tail = 0;	// m_head == 0 => m_head == m_tail
	 	}
	
	 	m_count--;
	
	 	delete list_node;
		point_list_in->SetLRUNode(0);
	};

	OOCPointList * RemoveFirst () {
		if (!m_head)
			return 0;

		LRUListNode *old_head = m_head;
		m_head = m_head->m_next;
		m_head->m_prev = 0;

		OOCPointList *old_item = old_head->GetItem();
		m_count--;

		if (!m_head)
			m_tail = 0;

		assert(old_item->GetLRUNode() == old_head);

		delete old_head;
		old_item->SetLRUNode(0);

		return old_item;
	};

	void Update ( OOCPointList * point_list_in ) {
// 		if (m_tail && point_list_in->GetLRUNode() == m_tail)
// 			return;
// 
// 		Remove(point_list_in);
// 		AddLast(point_list_in);
		if (point_list_in->GetLRUNode() == 0)
			AddLast(point_list_in);
	};

	void ResetCursor () {
		m_cursor = m_head;
	};

	void AdvanceCursor () {
		if (!m_cursor)
			return;	
			
		m_cursor = m_cursor->m_next;
	};

	OOCPointList * PeekCursor () {
		if (!m_cursor)
			return 0;
			
		return m_cursor->m_ooc_point_list;
	};

	void RemoveAtCursor () {
		if (!m_cursor)
			return;

		if (m_cursor->m_prev)
			m_cursor->m_prev->m_next = m_cursor->m_next;
		if (m_cursor->m_next)
			m_cursor->m_next->m_prev = m_cursor->m_prev;
		if (m_cursor == m_head)
			m_head = m_cursor->m_next;
		if (m_cursor == m_tail) {
			if (m_head)
				m_tail = m_cursor->m_prev;
			else
				m_tail = 0;	// m_head == 0 => m_head == m_tail
		}

		m_count--;
		m_cursor->m_ooc_point_list->SetLRUNode(0);
		LRUListNode *old_cursor = m_cursor;
		m_cursor = m_cursor->m_next;
		delete old_cursor;
	};
};

/*****************************************************************************************************/

class BackingFileData {
public:
	unsigned int	m_fid;
	size_t			m_pos;
	int				m_count;
};

class TempFileToolkit {
public:
	TempFileToolkit ( PointCloudWorld * pcw_in ) {
		m_pcw = pcw_in;
		m_fp = NULL;
		m_new_file = true;
		m_nfid = 0;
		m_cofid = 0;
		m_fpos = 0;
		m_bpos = 0;
	};

	~TempFileToolkit () {
		if (m_fp)
			fclose(m_fp);

		wchar_t *temp_file_name = new wchar_t [m_pcw->GetNodeFileNameSize() + 1];

		for ( unsigned int i = 0 ; i <= m_nfid ; i++ ) {
			m_pcw->GetTempFileName(i, temp_file_name);
			wremove(temp_file_name);
		}

		delete [] temp_file_name;
	};

	void Write ( int count_in, PCPoint * points_in, BackingFileData * bfd_out ) {
		if (m_fpos + m_bpos > OOC_MAX_FILE_SIZE)
			Flush();

		char *point_buffer = reinterpret_cast<char *>(points_in);
		size_t point_buffer_size = count_in * sizeof(PCPoint);
		size_t amount_written = point_buffer_size;
		
		if (m_bpos + point_buffer_size > OOC_BUFFER_CHUNK_SIZE)
			amount_written = OOC_BUFFER_CHUNK_SIZE - m_bpos;

		bfd_out->m_fid = m_nfid;
		bfd_out->m_pos = m_fpos + m_bpos;
		bfd_out->m_count = count_in;

		memcpy(m_buffer + m_bpos, point_buffer, amount_written);
		m_bpos += amount_written;

		if (m_bpos == OOC_BUFFER_CHUNK_SIZE) {
			Flush();

			if (amount_written < point_buffer_size) {
				m_bpos += point_buffer_size - amount_written;
				assert(m_bpos < OOC_BUFFER_CHUNK_SIZE);
				memcpy(m_buffer, point_buffer + amount_written, m_bpos);
			}
		}

	};

	void Read ( BackingFileData * bfd_in, int & count_out, PCPoint * points_out ) {
		if (m_fp && m_bpos)
			Flush();

		if (m_fp == NULL || m_cofid != bfd_in->m_fid) {
			if (m_fp)
				fclose(m_fp);

			m_cofid = bfd_in->m_fid;
			wchar_t *temp_file_name = new wchar_t [m_pcw->GetNodeFileNameSize() + 1];
			m_pcw->GetTempFileName(m_cofid, temp_file_name);

			m_fp = wfopen(temp_file_name, L"ab+");

			delete [] temp_file_name;
		}

		fseek(m_fp, (long)bfd_in->m_pos, SEEK_SET);

		count_out = bfd_in->m_count;
		char *point_buffer = reinterpret_cast<char *>(points_out);
		size_t point_buffer_size = bfd_in->m_count * sizeof(PCPoint);
		size_t amount_read = point_buffer_size;

		if (bfd_in->m_pos + point_buffer_size > OOC_MAX_FILE_SIZE)
			amount_read = OOC_MAX_FILE_SIZE - bfd_in->m_pos;

		size_t actual_amount_read = fread(point_buffer, 1, amount_read, m_fp);
		assert(actual_amount_read == amount_read);

		if (amount_read < point_buffer_size) {
			fclose(m_fp);
			m_fp = NULL;

			wchar_t *temp_file_name = new wchar_t [m_pcw->GetNodeFileNameSize() + 1];
			m_cofid++;
			assert(m_cofid == bfd_in->m_fid + 1);
			m_pcw->GetTempFileName(m_cofid, temp_file_name);
		
			m_fp = wfopen(temp_file_name, L"ab+");

			delete [] temp_file_name;

			assert(m_fp != NULL);
			fseek(m_fp, 0, SEEK_SET);
			actual_amount_read = fread(point_buffer + amount_read, 1, point_buffer_size - amount_read, m_fp);
			assert(actual_amount_read == point_buffer_size - amount_read);
		}
	};

	void Flush () {
		if (m_fp == NULL || m_cofid != m_nfid) {
			if (m_fp)
				fclose(m_fp);

			wchar_t *temp_file_name = new wchar_t [m_pcw->GetNodeFileNameSize() + 1];
			m_pcw->GetTempFileName(m_nfid, temp_file_name);
			
			if (m_new_file)
				wremove(temp_file_name);	
			m_fp = wfopen(temp_file_name, L"ab+");

			m_cofid = m_nfid;

			m_new_file = false;
			
			delete [] temp_file_name;
		}

		// no-op needed for synchronization because we are reading and writing to the same stream
		fseek(m_fp, 0, SEEK_CUR);

		size_t amount_written = m_bpos;
		if (m_bpos > OOC_MAX_FILE_SIZE - m_fpos) 
			amount_written = OOC_MAX_FILE_SIZE - m_fpos;

		assert(m_fp != NULL);
		size_t actual_amount_written = fwrite(m_buffer, 1, amount_written, m_fp);
		assert(ferror(m_fp) == 0);
		assert(actual_amount_written == amount_written);

		m_fpos += amount_written;

		if (m_fpos == OOC_MAX_FILE_SIZE) {
			fclose(m_fp);
			m_fp = NULL;
			m_new_file = true;
			m_nfid++;
			m_fpos = 0;
		}
		
		if (amount_written < m_bpos) {
			wchar_t *temp_file_name = new wchar_t [m_pcw->GetNodeFileNameSize() + 1];
			m_pcw->GetTempFileName(m_nfid, temp_file_name);

			if (m_new_file)
				wremove(temp_file_name);	
			m_fp = wfopen(temp_file_name, L"ab+");

			m_cofid = m_nfid;

			m_new_file = false;

			delete [] temp_file_name;

			actual_amount_written = fwrite(m_buffer + amount_written, 1, m_bpos - amount_written, m_fp);
			assert(ferror(m_fp) == 0);
			assert(actual_amount_written == m_bpos - amount_written);

			m_fpos += m_bpos - amount_written;
		}

		m_bpos = 0;
	};

private:
	PointCloudWorld *	m_pcw;
	FILE *				m_fp;
	bool				m_new_file;
	unsigned int		m_nfid;
	unsigned int		m_cofid;
	size_t				m_fpos;
	size_t				m_bpos;
	char				m_buffer[OOC_BUFFER_CHUNK_SIZE];
};

/*****************************************************************************************************/

// static member initialization
LRUList *			OOCPointList::m_lru_point_list_list		= 0;
unsigned long		OOCPointList::m_ref_count				= 0;
TempFileToolkit *	OOCPointList::m_temp_file_tk			= 0;

/*****************************************************************************************************/

OOCPointList::OOCPointList ( PointCloudWorld * pcw_in, StreamFilePointContainer * container_in ) {
	m_pcw = pcw_in;
	m_container = container_in;
	m_point_list = 0;
	m_total_count = 0;
	m_current_count = 0;
	m_size = 625;
	m_can_cache = true;
	m_lru_node = 0;
	m_bfd_list = new BFDList();

	if (m_ref_count == 0) {
		m_lru_point_list_list = new LRUList();
		m_temp_file_tk = new TempFileToolkit(m_pcw);
	}

	m_ref_count++;
}

OOCPointList::~OOCPointList () {
	m_lru_point_list_list->Remove(this);

	if (m_point_list) {
		OOCMemoryObject::operator delete[](m_point_list, m_pcw);
		m_point_list = 0;
	}

	assert(m_point_list == 0);

	m_bfd_list->DeleteItems();
	delete m_bfd_list;

	m_ref_count--;

	if (m_ref_count == 0) {
		delete m_lru_point_list_list;
		delete m_temp_file_tk;
	}
}

bool OOCPointList::Append ( PCPoint * new_point, bool should_compare ) {
	if (should_compare && m_total_count)
		EnsurePointsInMemory();

	bool should_add = true;

	if (should_compare) {
		for ( int i = 0 ; i < m_total_count ; i++ ) {
			if (fabs(m_point_list[i].pt.x - new_point->pt.x) < FEPSILON &&
				fabs(m_point_list[i].pt.y - new_point->pt.y) < FEPSILON &&
				fabs(m_point_list[i].pt.z - new_point->pt.z) < FEPSILON)
			{
				should_add = false;
				break;
			}
		}

		m_can_cache = true;
	}

	if (should_add) {
		EnsureSize();

		m_point_list[m_current_count] = *new_point;

		m_current_count++;
		m_total_count++;
	}

	return should_add;
}

PCPoint * OOCPointList::operator [] ( int const location ) {
	if (location < m_total_count) {
		EnsurePointsInMemory();
		return m_point_list + location;
	}
	
	return 0;
}

void OOCPointList::GetPointList ( int & count_out, PCPoint *& point_list_out ) {
	EnsurePointsInMemory();
	count_out = m_total_count;
	point_list_out = m_point_list;
}

void OOCPointList::EnsureSize () {
	m_lru_point_list_list->Update(this);

	if (m_point_list && m_current_count < m_size)
		return;

	if (m_current_count == m_size)
		m_size = (2 * m_size >= m_pcw->GetMaxShellSize() ? m_pcw->GetMaxShellSize() : 2 * m_size);

	PCPoint *old_point_list = m_point_list;

	if ((m_point_list = reinterpret_cast<PCPoint *>(OOCMemoryObject::operator new[](m_size * sizeof(PCPoint), m_pcw))) == 0) {
		CacheLRULists();
		if ((m_point_list = reinterpret_cast<PCPoint *>(OOCMemoryObject::operator new[](m_size * sizeof(PCPoint), m_pcw))) == 0)
			assert(0);
	}

	if (old_point_list) {
		memcpy(m_point_list, old_point_list, m_current_count * sizeof(PCPoint));
		OOCMemoryObject::operator delete[](old_point_list, m_pcw);
	}
}

void OOCPointList::EnsurePointsInMemory ( bool allow_appending ) {
	m_lru_point_list_list->Update(this);
	m_can_cache = false;

	if (m_point_list && m_current_count == m_total_count)
		return;

	PCPoint *old_point_list = m_point_list;

	if (allow_appending) {
		if (m_current_count == m_size)
			m_size = (2 * m_size >= m_pcw->GetMaxShellSize() ? m_pcw->GetMaxShellSize() : 2 * m_size);
	}
	else
		m_size = m_total_count;

	if ((m_point_list = reinterpret_cast<PCPoint *>(OOCMemoryObject::operator new[](m_size * sizeof(PCPoint), m_pcw))) == 0) {
		CacheLRULists();
		if ((m_point_list = reinterpret_cast<PCPoint *>(OOCMemoryObject::operator new[](m_size * sizeof(PCPoint), m_pcw))) == 0)
			assert(0);
	}

	assert(m_bfd_list->Count() > 0);

	BackingFileData *bfd;
	int bfd_count = 0;
	while (bfd = m_bfd_list->RemoveFirst()) {
		int ith_count;
		m_temp_file_tk->Read(bfd, ith_count, m_point_list + bfd_count);
		bfd_count += ith_count;
		
		delete bfd;
	}

	assert(bfd_count + m_current_count == m_total_count);

	if (old_point_list) {
		memcpy(m_point_list + bfd_count, old_point_list, m_current_count * sizeof(PCPoint));
		OOCMemoryObject::operator delete[](old_point_list, m_pcw);	
	}

	m_current_count = m_total_count;
}

void OOCPointList::CacheLRULists () {
// 	unsigned long half_lru_point_list_list_count = (unsigned long)((((double)m_lru_point_list_list->Count()) + 0.5)/ 2.0);
// 
// 	while (half_lru_point_list_list_count > 0) {
// 		OOCPointList *lru_point_list = m_lru_point_list_list->RemoveFirst();
// 
// 		BackingFileData *bfd = new BackingFileData(); // we'll free this later
// 		assert(lru_point_list->m_current_count > 0 && lru_point_list->m_point_list);
// 		m_temp_file_tk->Write(lru_point_list->m_current_count, lru_point_list->m_point_list, bfd);
// 		lru_point_list->m_bfd_list->AddLast(bfd);
// 
// 		OOCMemoryObject::operator delete[](lru_point_list->m_point_list, m_pcw);
// 		lru_point_list->m_point_list = 0;
// 		lru_point_list->m_current_count = 0;
// 		lru_point_list->m_size = 625;
// 
// 		half_lru_point_list_list_count--;
// 	}

	OOCPointList *current_point_list;
	m_lru_point_list_list->ResetCursor();
	while (current_point_list = m_lru_point_list_list->PeekCursor()) {
		if (current_point_list == this || !current_point_list->m_can_cache /*|| current_point_list->m_current_count <= 2500*/) {
			m_lru_point_list_list->AdvanceCursor();
			continue;
		}

		BackingFileData *bfd = new BackingFileData(); // we'll free this later
		assert(current_point_list->m_current_count > 0 && current_point_list->m_point_list);
		m_temp_file_tk->Write(current_point_list->m_current_count, current_point_list->m_point_list, bfd);
		current_point_list->m_bfd_list->AddLast(bfd);

		OOCMemoryObject::operator delete[](current_point_list->m_point_list, m_pcw);
		current_point_list->m_point_list = 0;
		current_point_list->m_current_count = 0;
		current_point_list->m_size = 625;

		// this will advance cursor to next node for us
		m_lru_point_list_list->RemoveAtCursor();
	}
}
