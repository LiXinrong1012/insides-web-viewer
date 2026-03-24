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
 * $Id: PointCloudCommon.h,v 1.26 2010-05-04 22:42:42 chad Exp $
 */

#ifndef POINTCLOUDCOMMON_H
#define POINTCLOUDCOMMON_H

#include <wchar.h>
#include "utf_utils.h"
#include "PointCloud.h"

#ifdef _MSC_VER
#pragma warning(disable: 4996) // don't complain about stdio string functions
#define uint64_t unsigned __int64
#else
#define wmkdir(a) wmkdir(a, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)
#include <stdint.h>
#endif

#ifndef streq
#define streq(a,b) 		(!strcmp(a,b))
#endif // streq

#ifndef wcseq
#define wcseq(a,b)		(!wcscmp(a,b))
#endif // wcseq

#ifndef wcsieq
#ifdef _MSC_VER
#define wcsieq(a,b)		(!wcsicmp(a,b))
#else
#define wcsieq(a,b)		(!wcscasecmp(a,b))
#endif
#endif

#ifndef nobreak
#define nobreak
#endif // nobreak

#ifndef alter
#define alter
#endif // alter

#ifndef INVALID_KEY
#define INVALID_KEY (-1L)
#endif // INVALID_KEY

//#define POINT_CLOUD_VERTEX_NORMALS
//#define POINT_CLOUD_RGBA
//#define ENABLE_COMPRESSION
#define THREADED_PREPROCESS

unsigned int const		OOC_FORMAT_VERSION			= 1;

size_t const			OOC_BUFFER_CHUNK_SIZE		= 16777216;		// 16 MB
int const				OOC_TOOLKIT_BUFFER_SIZE		= 262144;		// 256 KB
size_t const			NUM_BYTES_IN_MEGABYTE		= 1048576;		// 1 MB
unsigned int const		OOC_MAX_FILE_SIZE			= 2147483648U;	// 2 GB
int const				DEFAULT_MAX_SHELL_SIZE		= 10000;
size_t const			DEFAULT_MAX_MEMORY_USAGE	= 512;			// 512 MB
int const				THREAD_POINT_BUFFER_SIZE	= 200000;
unsigned int const		MAX_NUMBER_OPEN_FILES		= 128;

// float epsilon
double const 			FEPSILON 					= 1e-7; 

class PointCloudWorld;

class OOCMemoryObject {
public:
	virtual ~OOCMemoryObject () = 0;

	static void alter *	operator new ( size_t size, PointCloudWorld * pcw ) throw ();
	static void alter * operator new [] ( size_t size, PointCloudWorld * pcw ) throw ();
	static void operator delete ( void alter * p, PointCloudWorld * pcw ) throw ();
	static void operator delete [] ( void alter * p, PointCloudWorld * pcw ) throw ();
};

// enum for the different types of point cloud files
enum PointCloudFileType {
	NONE,		// no file extension
	UNKNOWN,	// unknown file extension
	PTX,
	PTS,
	XYZ
};

class RGBColor {
public:
	unsigned char red, green, blue;

	RGBColor ( unsigned char red_in = 0, unsigned char green_in = 0, unsigned char blue_in = 0 );
	RGBColor ( float red_in, float green_in, float blue_in );
	RGBColor ( RGBColor const & rgb_in );

	~RGBColor ();
};

unsigned char const PCPOINT_VALIDITY_INVALID			= 0x00;
unsigned char const PCPOINT_VALIDITY_XYZ				= 0x01;
unsigned char const PCPOINT_VALIDITY_INTENSITY			= 0x02;
unsigned char const PCPOINT_VALIDITY_RGB				= 0x04;
unsigned char const PCPOINT_VALIDITY_GRAY_SCALE_POINT	= PCPOINT_VALIDITY_XYZ | PCPOINT_VALIDITY_INTENSITY;
unsigned char const PCPOINT_VALIDITY_RGB_POINT			= PCPOINT_VALIDITY_XYZ | PCPOINT_VALIDITY_RGB;
unsigned char const PCPOINT_VALIDITY_ALL_VALID			= PCPOINT_VALIDITY_XYZ | PCPOINT_VALIDITY_RGB | PCPOINT_VALIDITY_INTENSITY;

class APoint {
public:
	float x, y, z;
	
	APoint ( float xx = 0.0f, float yy = 0.0f, float zz = 0.0f ) : x(xx), y(yy), z(zz) {}
};

class PCPoint {
protected:
	void Initialize ( PCPoint const * new_pt );
	
public:
	APoint			pt;		
	float			intensity;
	RGBColor		rgb_color;
	unsigned char	vfield;
#ifdef POINT_CLOUD_VERTEX_NORMALS
	APoint			normal;
#endif // POINT_CLOUD_VERTEX_NORMALS

	PCPoint ( float xx = 0.0f, float yy = 0.0f, float zz = 0.0f, float ii = 0, 
			  unsigned char rr = 0, unsigned char gg = 0, unsigned char bb = 0
#ifdef POINT_CLOUD_VERTEX_NORMALS
			  , float xn = 0.0f, float yn = 0.0f, float zn = 0.0f 
#endif // POINT_CLOUD_VERTEX_NORMALS
			  );
	PCPoint ( PCPoint const * new_pt );
	PCPoint ( PCPoint const & new_pt );
	
	PCPoint & operator = ( PCPoint const & rhs );

	~PCPoint ();
};

void FindFileNameWithoutDirectory ( wchar_t const * file_name_in, wchar_t alter * directory_path = 0, wchar_t alter * file_name_with_extension = 0 );
void FindFileNameWithoutExtension ( wchar_t const * file_name_in, wchar_t alter * file_name_no_extension = 0, wchar_t alter * extension = 0 );
void FindFileNameWithoutExtensionOrDirectory ( wchar_t const * file_name_in, wchar_t alter * directory_path = 0, 
											   wchar_t alter * file_name_no_extension = 0, wchar_t alter * extension = 0 );
char * PrettifyInteger ( uint64_t n );

class PointCloudIndexPopulateData;

template <typename T1, typename T2> class VHash;
template <typename T> class VList;

typedef VList<wchar_t *> PointCloudFileList;

class PointCloudWorld {
	friend class OOCMemoryObject;

public:
	PointCloudWorld ();
	~PointCloudWorld ();
	
	// sets up various variables for pre-processing and/or loading the point cloud
	void Initialize ( wchar_t const * ooc_file_in );

	wchar_t const * GetOOCFileName () const { return m_ooc_file_name; };
	
	/********************************************************************************/
	/*					Pre-processing functions/settings							*/	
	/********************************************************************************/

	PointCloudStatus PreProcess ();

	size_t GetNodeFileNameSize ();
	void GetFullNodeFileName ( float bbox_in[6], wchar_t * node_file_name_out );
	void GetNodeDirectoryPrefix ( wchar_t * node_dir_prefix_out );
	void GetNodeFileName ( float bbox_in[6], wchar_t * node_file_name_out );
	void GetTempFileName ( unsigned int fid_in, wchar_t * temp_file_name_out );
	void GetMasterNodeFileName ( unsigned int fid_in, wchar_t * master_node_file_name_out );

	size_t GetStreamFileNameSize ();
	void GetStreamFileName ( wchar_t * stream_file_name_out );

	size_t GetStreamMetadataFileNameSize ();
	void GetStreamMetadataFileName ( wchar_t * stream_metadata_file_name_out );

	size_t GetIndexFileNameSize ();
	void GetIndexFileName ( wchar_t * index_file_name_out );

	void SetOOCFormatVersion ( unsigned int in_version ) { m_ooc_format_version = in_version; };
	unsigned int GetOOCFormatVersion () { return m_ooc_format_version; };

	PointCloudFileList * GetPointCloudFileList ();

	void AddPointCloudFile ( wchar_t const * point_cloud_file_in );

	void SetLoggingFile ( wchar_t const * log_file_name = 0 );
	void LogMessage ( wchar_t const * log_string, bool should_timestamp = false );
	void LogMessage ( char const * log_string, bool should_timestamp = false );

	void SetMaxShellSize ( int max_shell_size_in ) { m_max_shell_size = max_shell_size_in; };
	int GetMaxShellSize () { return m_max_shell_size; };

	void SetSubSamplePercentage ( double subsample_in ) { m_subsample = subsample_in; };
	double GetSubSamplePercentage () { return m_subsample; };

	void SetCullingBoundingBox ( float const culling_bbox_in[6] ) { 
		m_has_culling_bbox = true;
		memcpy(m_culling_bbox, culling_bbox_in, 6 * sizeof(float));
	};
	bool GetHasCullingBoundingBox () { return m_has_culling_bbox; };
	void GetCullingBoundingBox ( float alter culling_bbox_out[6] ) { memcpy(culling_bbox_out, m_culling_bbox, 6 * sizeof(float)); };

	void SetOverwriteExistingFiles ( bool overwrite_in ) { m_overwrite = overwrite_in; };
	bool GetOverwriteExistingFiles () { return m_overwrite; };

	void SetRandomizePoints ( bool randomize_in ) { m_randomize = randomize_in; };
	bool GetRandomizePoints () { return m_randomize; };

	// expects value in MB
	void SetMaxMemoryUsage ( size_t max_memory_usage_in );
	// returns value in MB
	size_t GetMaxMemoryUsage () const { return m_max_memory_usage / NUM_BYTES_IN_MEGABYTE; };
	double GetCurrentMemoryUsage () const { return (double)m_raw_memory_usage / (double)NUM_BYTES_IN_MEGABYTE; };
	void SetReadMemoryUsage ( size_t rm ) { m_read_memory_usage = rm; }

	/********************************************************************************/
	/*						OOC loading functions/settings							*/
	/********************************************************************************/

	PointCloudStatus Load ();
	
	void SetNodeDirectoryPrefix ( wchar_t const * node_dir_prefix_in );
	// size_t GetNodeFileNameSize (); -- same as pre-processing function call
	void GetNodeFileName ( wchar_t const * relative_node_file_name, wchar_t * full_node_file_name_out );

	void SetLoadType ( LoadType load_type_in ) { m_load_type = load_type_in; };
	LoadType GetLoadType () { return m_load_type; };

	PointCloudIndexPopulateData * GetPopulateData ();

	bool PleaseUpdate ( bool need_update = false ) alter;
	
private:
	static void DeleteFileName ( wchar_t * filename, void * user_data );

	wchar_t *						m_ooc_file_name;
	wchar_t * 						m_ooc_file_dir;
	size_t							m_ooc_file_dir_len;
	wchar_t *						m_node_dir_prefix;
	size_t							m_node_dir_prefix_len;
	unsigned int					m_ooc_format_version;
	
	PointCloudFileList *			m_point_cloud_file_list;
	FILE *							m_debug_fp;
	int								m_max_shell_size;
	double							m_subsample;
	bool							m_has_culling_bbox;
	float							m_culling_bbox[6];
	bool							m_overwrite;
	bool							m_randomize;
	size_t							m_max_memory_usage;
	size_t							m_raw_memory_usage;
	VHash<void *, size_t> *			m_pointer_size_hash;

	LoadType						m_load_type;
	PointCloudIndexPopulateData *	m_populate_data;
	bool							m_please_update;
	size_t							m_read_memory_usage;

};

#endif // POINTCLOUDCOMMON_H
