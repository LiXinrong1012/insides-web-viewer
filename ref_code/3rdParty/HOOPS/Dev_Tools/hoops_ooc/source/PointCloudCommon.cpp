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
 * $Id: PointCloudCommon.cpp,v 1.26 2010-05-04 22:42:42 chad Exp $
 */

#include "PointCloudCommon.h"

#include "PointCloudIndex.h"
#include "PointCloudStreamFileToolkit.h"

#include "vhash.h"
#include "vlist.h"

#include <string.h>
#include <time.h>

/*****************************************************************************************************/

void alter * OOCMemoryObject::operator new ( size_t size, PointCloudWorld * pcw ) throw () {
	if (pcw->m_raw_memory_usage + pcw->m_read_memory_usage >= pcw->m_max_memory_usage)
		return 0;
	pcw->m_raw_memory_usage += size;
	void *p = malloc(size);
	pcw->m_pointer_size_hash->InsertItem(p, size);
	return p;
}

void alter * OOCMemoryObject::operator new [] ( size_t size, PointCloudWorld * pcw ) throw () {
	if (pcw->m_raw_memory_usage + pcw->m_read_memory_usage >= pcw->m_max_memory_usage)
		return 0;
	pcw->m_raw_memory_usage += size;
	void *p = malloc(size);
	pcw->m_pointer_size_hash->InsertItem(p, size);
	return p;
}

void OOCMemoryObject::operator delete ( void alter * p, PointCloudWorld * pcw ) throw () {
	size_t stored_size;
	if (pcw->m_pointer_size_hash->RemoveItem(p, &stored_size) == VHASH_STATUS_FAILED)
		assert(0);
	pcw->m_raw_memory_usage -= stored_size;
	free(p);
}

void OOCMemoryObject::operator delete [] ( void alter * p, PointCloudWorld * pcw ) throw () {
	size_t stored_size;
	if (pcw->m_pointer_size_hash->RemoveItem(p, &stored_size) == VHASH_STATUS_FAILED)
		assert(0);
	pcw->m_raw_memory_usage -= stored_size;
	free(p);
}

/*****************************************************************************************************/

RGBColor::RGBColor ( unsigned char red_in, unsigned char green_in, unsigned char blue_in ) {
	red = red_in;
	green = green_in;
	blue = blue_in;
}

RGBColor::RGBColor ( float red_in, float green_in, float blue_in ) {
	red = (unsigned char) (red_in / 255.0f);
	green = (unsigned char) (green_in / 255.0f);
	blue = (unsigned char) (blue_in / 255.0f);
}

RGBColor::RGBColor ( RGBColor const & rgb_in ) {
	red = rgb_in.red;
	green = rgb_in.green;
	blue = rgb_in.blue;
}

RGBColor::~RGBColor () {}

/*****************************************************************************************************/

PCPoint::PCPoint ( float xx, float yy, float zz, float ii, unsigned char rr, unsigned char gg, unsigned char bb
#ifdef POINT_CLOUD_VERTEX_NORMALS
				   , float xn, float yn, float zn 
#endif // POINT_CLOUD_VERTEX_NORMALS
				   ) {
	pt = APoint(xx, yy, zz);
	intensity = ii;
	rgb_color = RGBColor(rr, gg, bb);
	vfield = PCPOINT_VALIDITY_ALL_VALID;
#ifdef POINT_CLOUD_VERTEX_NORMALS
	normal = APoint(xn, yn, zn);
#endif // POINT_CLOUD_VERTEX_NORMALS
}


PCPoint::PCPoint ( PCPoint const * new_pt ) {
	Initialize(new_pt);
}

PCPoint::PCPoint ( PCPoint const & new_pt ) {
	Initialize(&new_pt);
}

void PCPoint::Initialize ( PCPoint const * new_pt ) {
	pt = new_pt->pt;
	intensity = new_pt->intensity;
	rgb_color = new_pt->rgb_color;
	vfield = new_pt->vfield;
#ifdef POINT_CLOUD_VERTEX_NORMALS
	normal = new_pt->normal;
#endif // POINT_CLOUD_VERTEX_NORMALS
}

PCPoint::~PCPoint () {}

PCPoint & PCPoint::operator = ( PCPoint const & rhs ) {
	Initialize(&rhs);
	return *this;
}

/*****************************************************************************************************/

void FindFileNameWithoutDirectory ( wchar_t const * file_name_in, wchar_t alter * directory_path, wchar_t alter * file_name_with_extension ) {
	if (directory_path == 0 && file_name_with_extension == 0)
		return;

	wchar_t const *file_name = wcsrchr(file_name_in, L'/');

	if (file_name) {
		if (directory_path != 0) {
			wcscpy(directory_path, file_name_in);
			directory_path[file_name - file_name_in] = L'\0';
		}
		if (file_name_with_extension != 0) {
			file_name++;
			wcscpy(file_name_with_extension, file_name);
		}
	}
	else {
		if (directory_path != 0) {
			directory_path[0] = L'\0';
		}
		if (file_name_with_extension != 0) {
			wcscpy(file_name_with_extension, file_name_in);
		}
	}
}

void FindFileNameWithoutExtension ( wchar_t const * file_name_in, wchar_t alter * file_name_no_extension, wchar_t alter * extension ) {
	if (file_name_no_extension == 0 && extension == 0)
		return;
	
	wchar_t const *tmp_ext = wcsrchr(file_name_in, L'.');
	if (extension != 0)
		wcscpy(extension, tmp_ext + 1);
	if (file_name_no_extension != 0) {
		wcscpy(file_name_no_extension, file_name_in);
		file_name_no_extension[tmp_ext - file_name_in] = L'\0';
	}
}

void FindFileNameWithoutExtensionOrDirectory ( wchar_t const * file_name_in, wchar_t alter * directory_path, 
											   					wchar_t alter * file_name_no_extension, wchar_t alter * extension ) {
	if (directory_path == 0 && file_name_no_extension == 0 && extension == 0)
		return;
	
	wchar_t const *file_name = wcsrchr(file_name_in, L'/');

	if (file_name) {
		if (file_name_no_extension != 0 || extension != 0)
			FindFileNameWithoutExtension(file_name + 1, file_name_no_extension, extension);
		if (directory_path != 0) {
			wcscpy(directory_path, file_name_in);
			directory_path[file_name - file_name_in] = L'\0';
		}
	}
	else {
		if (file_name_no_extension != 0 || extension != 0)
			FindFileNameWithoutExtension(file_name_in, file_name_no_extension, extension);
		if (directory_path != 0) {
			directory_path[0] = L'\0';
		}
	}
}

// Note: This function returns a string in static buffer
//       -- depending on how the function is used, e.g., in printf statements, this may cause issues
char * PrettifyInteger ( uint64_t n ) {
	static char retbuf[1024];
	char *p = &retbuf[sizeof(retbuf) - 1];
	int i = 0;

	*p = '\0';
	do {
		if (i % 3 == 0 && i != 0)
			*--p = ',';
		*--p = '0' + (char)(n % 10);
		n /= 10;
		i++;
	} while (n != 0);

	return p;
}

/*****************************************************************************************************/

PointCloudWorld::PointCloudWorld () {
	m_ooc_file_name = 0;
	m_ooc_file_dir = 0;
	m_ooc_file_dir_len = 0;
	m_node_dir_prefix = 0;
	m_node_dir_prefix_len = 0;

	m_point_cloud_file_list = 0;
	m_debug_fp = NULL;
	m_max_shell_size = -1;
	m_max_memory_usage = 0;
	m_subsample = 0.0;
	m_has_culling_bbox = false;
	m_culling_bbox[0] = m_culling_bbox[1] = m_culling_bbox[2] = m_culling_bbox[3] = m_culling_bbox[4] = m_culling_bbox[5] = 0.0f;
	m_overwrite = false;
	m_randomize = true;
	m_raw_memory_usage = 0;
	m_pointer_size_hash = 0;
	m_read_memory_usage = 0;

	m_please_update = false;

	m_populate_data = 0;
}

PointCloudWorld::~PointCloudWorld () {
	if (m_ooc_file_name)
		delete [] m_ooc_file_name;
	if (m_ooc_file_dir)
		delete [] m_ooc_file_dir;
	if (m_node_dir_prefix)
		delete [] m_node_dir_prefix;
	if (m_populate_data)
		delete m_populate_data;
	if (m_point_cloud_file_list) {
		m_point_cloud_file_list->MapFunction(DeleteFileName, 0);
		delete m_point_cloud_file_list;
	}
	if (m_debug_fp)
		fclose(m_debug_fp);
	if (m_pointer_size_hash)
		delete m_pointer_size_hash;
}

void PointCloudWorld::Initialize ( wchar_t const * ooc_file_in ) {
	if (m_ooc_file_name)
		delete [] m_ooc_file_name;
	if (m_ooc_file_dir)
		delete [] m_ooc_file_dir;
	if (m_node_dir_prefix)
		delete [] m_node_dir_prefix;

	size_t ooc_file_in_size = wcslen(ooc_file_in);
	m_ooc_file_dir = new wchar_t [ooc_file_in_size + 1];
	m_node_dir_prefix = new wchar_t [ooc_file_in_size + 1];

	m_ooc_file_name = new wchar_t [ooc_file_in_size + 1];
	wcscpy(m_ooc_file_name, ooc_file_in);

	wchar_t *c = m_ooc_file_name;
	while (*c != 0) {
		*c = (*c == L'\\' ? L'/' : *c);
		c++;
	}
 	
	FindFileNameWithoutDirectory(m_ooc_file_name, m_ooc_file_dir, m_node_dir_prefix);

	if ((m_ooc_file_dir_len = wcslen(m_ooc_file_dir)) == 0) {
		swprintf(m_ooc_file_dir, 2, L".");
		m_ooc_file_dir_len = wcslen(m_ooc_file_dir);
	}

	c = m_node_dir_prefix;
	while (*c != 0) {
		*c = (*c == L'.' ? L'_' : *c);
		c++;
	}
	m_node_dir_prefix_len = wcslen(m_node_dir_prefix);
}

/********************************************************************************/
/*					Pre-processing functions/settings							*/	
/********************************************************************************/

PointCloudStatus PointCloudWorld::PreProcess () {
	// check validity of settings
	if (GetPointCloudFileList()->Count() == 0) {
		LogMessage("\n--- No file name(s) specified. ---\n");
		return PRE_PROCESS_SETUP_FAILURE;
	}
	if (m_subsample < 0.0 || m_subsample > 1.0) {
		LogMessage("\n--- Must specify subsample percentage X such that 0.0 < X <= 1.0. ---\n");
		return PRE_PROCESS_SETUP_FAILURE;
	}
	if (m_has_culling_bbox && 
		(m_culling_bbox[3] - m_culling_bbox[0] < FEPSILON || m_culling_bbox[4] - m_culling_bbox[1] < FEPSILON || m_culling_bbox[5] - m_culling_bbox[2] < FEPSILON)) 
	{
		LogMessage("\n--- Invalid culling bounding box. ---\n");
		return PRE_PROCESS_SETUP_FAILURE;
	}

	// set up defaults
	if (m_max_shell_size <= 0) {
		LogMessage(H_FORMAT_TEXT("+++ Using default max shell size of %d", DEFAULT_MAX_SHELL_SIZE));
		SetMaxShellSize(DEFAULT_MAX_SHELL_SIZE);
	}
	if (m_max_memory_usage == 0) {
		LogMessage(H_FORMAT_TEXT("+++ Using default max memory usage of %ld MB", DEFAULT_MAX_MEMORY_USAGE));
		SetMaxMemoryUsage(DEFAULT_MAX_MEMORY_USAGE);
	}
	if (m_ooc_file_name == 0) {
		LogMessage("+++ Using default output file name.");
		Initialize(m_point_cloud_file_list->PeekFirst());
	}

	LogMessage("");

	// warn if valid, but potentially bad options are specified
	if (m_max_memory_usage < DEFAULT_MAX_MEMORY_USAGE * NUM_BYTES_IN_MEGABYTE) {
		LogMessage("\n--- Low memory usage amount may increase amount of time for preprocess. ---\n");
	}
	if (m_max_shell_size < DEFAULT_MAX_SHELL_SIZE) {
		LogMessage("\n--- Small shell size may increase amount of time for preprocess. ---\n");
	}

	PointCloudStreamFileToolkit tk(this);

	return tk.Generate_OOC_File();
}

size_t PointCloudWorld::GetNodeFileNameSize () {
	// m_ooc_file_dir + '/' + m_node_dir_prefix + '_nodes/' + [temp_]?AAAAAAAA_BBBBBBBB_CCCCCCCC_DDDDDDDD_EEEEEEEE_FFFFFFFF.node
	//   where AAAAAAAA = binary representation of min_x (bbox[0])
	//   where BBBBBBBB = binary representation of min_y (bbox[1])
	//   where CCCCCCCC = binary representation of min_z (bbox[2])
	//   where DDDDDDDD = binary representation of max_x (bbox[3])
	//   where EEEEEEEE = binary representation of max_y (bbox[4])
	//   where FFFFFFFF = binary representation of max_z (bbox[5])
	return m_ooc_file_dir_len + 1 + m_node_dir_prefix_len + 7 + 63;
}

void PointCloudWorld::GetFullNodeFileName ( float bbox_in[6], wchar_t * node_file_name_out ) {
	swprintf(node_file_name_out, GetNodeFileNameSize() + 1, L"%ls/%ls_nodes/%08x_%08x_%08x_%08x_%08x_%08x.node", m_ooc_file_dir, m_node_dir_prefix,
		*(unsigned int *)(bbox_in + 0), *(unsigned int *)(bbox_in + 1), *(unsigned int *)(bbox_in + 2),
		*(unsigned int *)(bbox_in + 3), *(unsigned int *)(bbox_in + 4), *(unsigned int *)(bbox_in + 5));
}

void PointCloudWorld::GetNodeDirectoryPrefix ( wchar_t * node_dir_prefix_out ) {
	swprintf(node_dir_prefix_out, GetNodeFileNameSize() + 1, L"%ls", m_node_dir_prefix);
}

void PointCloudWorld::GetNodeFileName ( float bbox_in [6], wchar_t * node_file_name_out ) {
	swprintf(node_file_name_out, GetNodeFileNameSize() + 1, L"%08x_%08x_%08x_%08x_%08x_%08x.node",
			 *(unsigned int *)(bbox_in + 0), *(unsigned int *)(bbox_in + 1), *(unsigned int *)(bbox_in + 2),
			 *(unsigned int *)(bbox_in + 3), *(unsigned int *)(bbox_in + 4), *(unsigned int *)(bbox_in + 5));
}

void PointCloudWorld::GetTempFileName ( unsigned int fid_in, wchar_t * temp_file_name_out ) {
	swprintf(temp_file_name_out, GetNodeFileNameSize() + 1, L"%ls/%ls_nodes/temp_%u.node", m_ooc_file_dir, m_node_dir_prefix, fid_in);
}

void PointCloudWorld::GetMasterNodeFileName ( unsigned int fid_in, wchar_t * master_node_file_name_out ) {
	swprintf(master_node_file_name_out, GetNodeFileNameSize() + 1, L"%ls/%ls_nodes/master_node_%u.node", m_ooc_file_dir, m_node_dir_prefix, fid_in);
}

size_t PointCloudWorld::GetStreamFileNameSize () {
	// m_ooc_file_dir + '/' + m_node_dir_prefix + '_stream_files/' + m_node_dir_prefix + '.pcsf'
	return m_ooc_file_dir_len + 1 + m_node_dir_prefix_len + 14 + m_node_dir_prefix_len + 5;
}

void PointCloudWorld::GetStreamFileName ( wchar_t * stream_file_name_out ) {
	swprintf(stream_file_name_out, GetStreamFileNameSize() + 1, L"%ls/%ls_stream_files/%ls.pcsf", m_ooc_file_dir, m_node_dir_prefix, m_node_dir_prefix);
}

size_t PointCloudWorld::GetStreamMetadataFileNameSize () {
	// m_ooc_file_dir + '/' + m_node_dir_prefix + '_stream_files/metadata.txt'
	return m_ooc_file_dir_len + 1 + m_node_dir_prefix_len + 26;
}

void PointCloudWorld::GetStreamMetadataFileName ( wchar_t * stream_metadata_file_name_out ) {
	swprintf(stream_metadata_file_name_out, GetStreamMetadataFileNameSize() + 1, L"%ls/%ls_stream_files/metadata.txt", m_ooc_file_dir, m_node_dir_prefix);
}

size_t PointCloudWorld::GetIndexFileNameSize () {
	// m_ooc_file_dir + '/' + m_node_dir_prefix + '.ooc'	
	return m_ooc_file_dir_len + 1 + m_node_dir_prefix_len + 4;	
}

void PointCloudWorld::GetIndexFileName ( wchar_t * index_file_name_out ) {
	swprintf(index_file_name_out, GetIndexFileNameSize() + 1, L"%ls/%ls.ooc", m_ooc_file_dir, m_node_dir_prefix);	
}

PointCloudFileList * PointCloudWorld::GetPointCloudFileList () {
	if (!m_point_cloud_file_list)
		m_point_cloud_file_list = new PointCloudFileList(); 
	return m_point_cloud_file_list;
}

void PointCloudWorld::AddPointCloudFile ( wchar_t const * point_cloud_file_in ) {
	wchar_t *point_cloud_file_copy = new wchar_t [wcslen(point_cloud_file_in) + 1];
	wcscpy(point_cloud_file_copy, point_cloud_file_in);

	// we use accessor function since it creates the list if it doesn't exist
	GetPointCloudFileList()->AddLast(point_cloud_file_copy);
}

void PointCloudWorld::SetLoggingFile ( wchar_t const * log_file_name ) {
	if (m_debug_fp)
		fclose(m_debug_fp);

	if (log_file_name == 0) {
		size_t actual_log_file_name_size = (m_ooc_file_dir_len > 0 ? m_ooc_file_dir_len + 1 : 1 + 1);
		actual_log_file_name_size += 16; // 'ooc_log_file.txt'
		wchar_t *actual_log_file_name = new wchar_t [actual_log_file_name_size + 1];
		swprintf(actual_log_file_name, actual_log_file_name_size + 1, L"%ls/%ls", (m_ooc_file_dir_len > 0 ? m_ooc_file_dir : L"."), L"ooc_log_file.txt");
		m_debug_fp = wfopen(actual_log_file_name, L"w");
		delete [] actual_log_file_name;
	}
	else
		m_debug_fp = wfopen(log_file_name, L"w");

	if (m_debug_fp == NULL)
		assert(0);
}

void PointCloudWorld::LogMessage ( wchar_t const * log_string, bool should_timestamp ) {
	if (should_timestamp) {
		time_t raw_time;
		struct tm *timeinfo;

		time(&raw_time);
		timeinfo = localtime(&raw_time);

		char timestamp[80];
		strftime(timestamp, 80, "%c -- ", timeinfo);

		fprintf(stdout, "%s", timestamp);
		if (m_debug_fp)
			fprintf(m_debug_fp, "%s", timestamp);
	}

	fprintf(stdout, "%s\n", H_UTF8(log_string).encodedText());
	if (m_debug_fp)
		fwprintf(m_debug_fp, L"%ls\n", log_string);
	
	if (m_debug_fp)
		fflush(m_debug_fp);
}

void PointCloudWorld::LogMessage ( char const * log_string, bool should_timestamp ) {
	LogMessage(H_WCS(log_string).encodedText(), should_timestamp);
}

void PointCloudWorld::SetMaxMemoryUsage ( size_t max_memory_usage_in ) {
	m_max_memory_usage = max_memory_usage_in * NUM_BYTES_IN_MEGABYTE;
	if (m_pointer_size_hash == 0)
		m_pointer_size_hash = new VHash<void *, size_t>();
}

void PointCloudWorld::DeleteFileName ( wchar_t * filename, void * user_data ) {
	delete [] filename;
}

/********************************************************************************/
/*						OOC loading functions/settings							*/
/********************************************************************************/

PointCloudStatus PointCloudWorld::Load () {
	PointCloudStreamFileToolkit tk(this);

	tk.SetOpcodeHandler(TKE_Open_Segment, new TK_Point_Cloud_Index_Open_Segment(this));
	tk.SetOpcodeHandler(TKE_Close_Segment, new TK_Point_Cloud_Index_Close_Segment(this));

	return tk.Read_OOC_File();
}

void PointCloudWorld::SetNodeDirectoryPrefix ( wchar_t const * node_dir_prefix_in ) {
	if (m_node_dir_prefix)
		delete [] m_node_dir_prefix;

	m_node_dir_prefix_len = wcslen(node_dir_prefix_in);
	m_node_dir_prefix = new wchar_t [m_node_dir_prefix_len + 1];
	
	wcscpy(m_node_dir_prefix, node_dir_prefix_in);
}

void PointCloudWorld::GetNodeFileName ( wchar_t const * relative_node_file_name, wchar_t * full_node_file_name_out ) {
	swprintf(full_node_file_name_out, GetNodeFileNameSize() + 1, L"%ls/%ls_nodes/%ls", m_ooc_file_dir, m_node_dir_prefix, relative_node_file_name);
}

PointCloudIndexPopulateData * PointCloudWorld::GetPopulateData () { 
	if (!m_populate_data)
		m_populate_data = new PointCloudIndexPopulateData(this);
	return m_populate_data; 
}

bool PointCloudWorld::PleaseUpdate ( bool need_update ) {
	bool was_update = m_please_update;
	m_please_update = need_update;
	return was_update;
}
