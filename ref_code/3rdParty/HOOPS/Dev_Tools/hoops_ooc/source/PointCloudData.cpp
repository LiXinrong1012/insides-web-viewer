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
 * $Id: PointCloudData.cpp,v 1.25 2010-01-07 01:04:16 chad Exp $
 */

#include "PointCloudData.h"

#include "PointCloudStreamFileToolkit.h"
#include "PointCloudNode.h"
#include "StreamFilePointContainer.h"
#include "PointCloudIndex.h"

#include "hc.h"

#include "vlist.h"

#include <limits.h>

/*****************************************************************************************************/

#define is_exponent_marker(ch) (ch == 'E' || ch == 'e')

static int parse_sign ( char ** str );
static void parse_float_number_part ( char ** str, double * number, int * length );
static void parse_decimal_number_part ( char ** str, double * number );
static int parse_int_number_part ( char ** str, long * number );

double my_atof ( char const * src ) {
	int		sign, exp_sign;
	int		length_before_point;
	double	after_point;			/* Number after decimal point and before exp */
	long	exponent;
	double	exp_log,exp_val;
	char *	tmp_src;
	double	result_number;

	tmp_src = (char *)src;

	while (tmp_src[0] == ' ')
		tmp_src++;					/* skip spaces */

	sign = parse_sign(&tmp_src);

	int overflow = 0;
	parse_float_number_part(&tmp_src, &result_number, &length_before_point);

	if (*tmp_src == '.') {
		tmp_src++;
		parse_decimal_number_part(&tmp_src, &after_point);
		result_number += after_point;
	}
	else if (length_before_point == 0)	{
		return 0.0;
	}

	if (is_exponent_marker(*tmp_src)) {
		tmp_src++;
		exp_sign = parse_sign(&tmp_src);
		overflow |= parse_int_number_part(&tmp_src, &exponent);

		exp_log = 10.0; 
		exp_val = 1.0;

		while (1) {
			if (exponent & 1) {
				exp_val *= exp_log;
				exponent--;
			}

			if (!exponent)
				break;

			exp_log *= exp_log;
			exponent >>= 1;
		}

		if (exp_sign < 0)
			result_number *= exp_val;
		else
			result_number /= exp_val;
	}

	if (sign > 0)
		result_number = -result_number;

	if (overflow)
		return 0.0;

	return result_number;
}


static int parse_sign ( char ** str ) {
	if (**str == '-') {
		(*str)++;
		return 1;
	}

	if (**str == '+')
		(*str)++;

	return -1;
}

/* Get number which may be separated with ',' */
static void parse_float_number_part ( char ** str, double * number, int * length ) {
	*number = 0;
	*length = 0;

	while (1) {
		while ((**str) >= '0' && (**str) <= '9' ) {
			(*length)++;
			*number = (*number * 10) + (**str - '0');
			(*str)++;
		}
    
		if (**str != ',')
			return;
		(*str)++;
	}
}

static void parse_decimal_number_part ( char ** str, double * number ) {
	double exp_log;

	*number = 0;
	exp_log = 1 / 10.0;
	while ((**str) >= '0' && (**str) <= '9' ) {
		*number += (**str - '0') * exp_log;
		exp_log /= 10;
		(*str)++;
	}
}

/* Parses int for exponent */
static int parse_int_number_part ( char ** str, long * number ) {
	*number = 0;
	while ((**str) >= '0' && (**str) <= '9' ) {
		if (*number >= LONG_MAX)
			return 1;						/* Don't overflow */
		*number = (*number * 10) + **str - '0';
		(*str)++;
	}

	return 0;
}

static int fast_textscan ( char * text, float & f1, float & f2, float & f3, float & f4, int & f5, int & f6, int & f7 ) {
	int i;
	int g = 0;
	int fn = 0;
	char chunk[129];

	while (1) {
		i = 0;
		while (1) {
			chunk[i++] = text[g++];
			if (text[g] == ' ' || text[g] == '\t' || text[g] == 0 || 
				(text[g] != '-' && text[g] != '+' && text[g] != '.' && text[g] != 'e' && text[g] != 'E' &&
				 (text[g] < '0'  || text[g] > '9')))
			{
				if (chunk[i - 1] < '0' || chunk[i - 1] > '9')
					i = 0;

 				chunk[i] = 0;

				if (text[g] != 0 && i == 0)
					continue;

				break;
			}
		}

		if (i == 0) {
			assert(text[g] == 0);
			break;
		}

		if (fn == 0)
			f1 = (float)my_atof(chunk);
		else if (fn == 1)
			f2 = (float)my_atof(chunk);
		else if (fn == 2)
			f3 = (float)my_atof(chunk);
		else if (fn == 3)
			f4 = (float)my_atof(chunk);
 		else if (fn == 4)
			f5 = (int)my_atof(chunk);
  		else if (fn == 5)
			f6 = (int)my_atof(chunk);
  		else if (fn == 6)
			f7 = (int)my_atof(chunk);
 		
		fn++;
		if (text[g] == 0)
			break;
		g++;
	}

	return fn;
}

/*****************************************************************************************************/ 

THREAD_FUNCTION ( m_point_process_function ) {
	TK_Point_Cloud_Data *pcd = THREAD_FUNCTION_DATA(TK_Point_Cloud_Data *);

	while (1) {
		bool done = false;

 		LOCK_MUTEX(pcd->m_point_buffer_list_mutex);
		PointBuffer_t *temp = pcd->m_point_buffer_list->PeekFirst();
		if (!temp && pcd->m_no_more_points)		
			done = true;						
		UNLOCK_MUTEX(pcd->m_point_buffer_list_mutex);

		if (done)
			break;

		if (!temp) {
			MILLI_SECOND_SLEEP(10);
		}
		else {
			for ( int i = 0 ; i < temp->m_count ; i++ ) {
				PCPoint *m_cpt = &(temp->m_buffer[i]);
				float bounds[6] = { m_cpt->pt.x, m_cpt->pt.y, m_cpt->pt.z, m_cpt->pt.x, m_cpt->pt.y, m_cpt->pt.z };
				pcd->m_point_bsp->Insert(m_cpt, bounds);
			}

			LOCK_MUTEX(pcd->m_point_buffer_list_mutex);
			pcd->m_bytes_used -= (sizeof(PCPoint) * temp->m_count);
			pcd->m_point_buffer_list->RemoveFirst();
			UNLOCK_MUTEX(pcd->m_point_buffer_list_mutex);

 			delete [] temp->m_buffer;
			delete temp;
 		}
	}

	return 0;
}

/*****************************************************************************************************/ 

TK_Point_Cloud_Data::TK_Point_Cloud_Data ( PointCloudWorld * pcw_in ) {
	m_pcw = pcw_in;

	m_index_file_name = new wchar_t [m_pcw->GetIndexFileNameSize() + 1];
	m_pcw->GetIndexFileName(m_index_file_name);

	m_current_point_cloud_file = NULL;
	m_point_cloud_file_type = NONE;

	m_read_buffer = new char [OOC_BUFFER_CHUNK_SIZE];
	m_point_bsp = 0;
}

TK_Point_Cloud_Data::~TK_Point_Cloud_Data () {
	if (m_read_buffer)
		delete [] m_read_buffer;
	if (m_index_file_name)
		delete [] m_index_file_name;
	if (m_point_bsp)
		delete m_point_bsp;
}

TK_Status TK_Point_Cloud_Data::Read ( BStreamFileToolkit & tk ) alter {
	TK_Status status = TK_Normal;

	switch (m_stage) {
		case 0: {
			// initialize variables, read metadata file
			wchar_t *metadata_file_name = new wchar_t [m_pcw->GetStreamMetadataFileNameSize() + 1];
			m_pcw->GetStreamMetadataFileName(metadata_file_name);

			FILE *metadata_fp;

			if ((metadata_fp = wfopen(metadata_file_name, L"r")) == NULL)
				return tk.Error("Problem opening metadata file");

			delete [] metadata_file_name;

			fscanf(metadata_fp, "%llu\n%f\t%f\t%f\t%f\t%f\t%f\n%f\t%f\n", 
				   &m_valid_point_count,
				   m_std_bbox + 0, m_std_bbox + 1, m_std_bbox + 2, m_std_bbox + 3, m_std_bbox + 4, m_std_bbox + 5,
				   &m_min_intensity, &m_max_intensity);

			fclose(metadata_fp);

			H_FORMAT_TEXT logging_str = H_FORMAT_TEXT("Point cloud contains %s points.\n", PrettifyInteger(m_valid_point_count));
			m_pcw->LogMessage(logging_str);

			logging_str = H_FORMAT_TEXT("Bounding box (min_x, min_y, min_z, max_x, max_y, max_z):\n(%f, %f, %f, %f, %f, %f)\n\n",
										m_std_bbox[0], m_std_bbox[1], m_std_bbox[2], m_std_bbox[3], m_std_bbox[4], m_std_bbox[5]);
			m_pcw->LogMessage(logging_str);

			if (m_pcw->GetHasCullingBoundingBox()) {
				m_pcw->GetCullingBoundingBox(m_std_bbox);
				logging_str = H_FORMAT_TEXT("Points outside the following bounding box will be excluded:\n(%f, %f, %f, %f, %f, %f)\n\n",
											m_std_bbox[0], m_std_bbox[1], m_std_bbox[2], m_std_bbox[3], m_std_bbox[4], m_std_bbox[5]);
				m_pcw->LogMessage(logging_str);
			}

			m_need_to_subsample = false;
			if (m_pcw->GetSubSamplePercentage() > FEPSILON && (1.0 - m_pcw->GetSubSamplePercentage()) > FEPSILON) {
				logging_str = H_FORMAT_TEXT("Point cloud will be sub-sampled to %.1f %%\n\n", 100.0 * m_pcw->GetSubSamplePercentage());
				m_pcw->LogMessage(logging_str);
				srand(2009092116);
				m_need_to_subsample = true;
			}

			logging_str = H_FORMAT_TEXT("Spatially sorting point cloud...");
			m_pcw->LogMessage(logging_str, true);

			m_num_points_sorted = 0;
			m_sub_stage = 0;
			m_stage++;
		} nobreak;
			
		case 1: {
			switch (m_sub_stage) {
				case 0: {
					m_initial_pass = true;
					m_eof = false;
					m_no_more_reads = false;
					m_num_points_remaining = m_valid_point_count;

#ifdef THREADED_PREPROCESS
					m_point_buffer = new PointBuffer_t;
					m_point_buffer->m_buffer = new PCPoint [THREAD_POINT_BUFFER_SIZE];
					m_point_buffer->m_count = 0;

					m_bytes_used = 0;
					m_no_more_points = false;

					m_current_point_buffer_size = THREAD_POINT_BUFFER_SIZE;

					CREATE_MUTEX(m_point_buffer_list_mutex);
					m_point_buffer_list = new PointBufferList();
#endif // THREADED_PREPROCESS

#ifdef ENABLE_COMPRESSION
					PointCloudStreamFileToolkit *pcsftk = static_cast<PointCloudStreamFileToolkit *>(&tk);
					if ((status = pcsftk->start_decompression()) != TK_Normal)
						return status;
#endif // ENABLE_COMPRESSION
					
					m_sub_sub_stage = 0;
					m_sub_stage++;
				} nobreak;
					
				case 1: {
					while (!m_eof) {
						switch (m_sub_sub_stage) {
							case 0: {
								m_cpt = PCPoint();
								
								m_sub_sub_stage++;
							} nobreak;
								
							case 1: {
								if ((status = GetData(tk, reinterpret_cast<float *>(&m_cpt.pt), 3)) != TK_Normal)
									return status;
								
								m_sub_sub_stage++;
							} nobreak;
								
							case 2: {
								if ((status = GetData(tk, m_cpt.intensity)) != TK_Normal)
									return status;
								
								m_sub_sub_stage++;
							} nobreak;
								
							case 3: {
								if ((status = GetData(tk, reinterpret_cast<unsigned char *>(&m_cpt.rgb_color), 3)) != TK_Normal)
									return status;
								
								m_sub_sub_stage++;
							} nobreak;						
								
							case 4: {
								if ((status = GetData(tk, reinterpret_cast<unsigned char &>(m_cpt.vfield))) != TK_Normal)
									return status;
								
								m_sub_sub_stage++;
							} nobreak;

#ifdef POINT_CLOUD_VERTEX_NORMALS
							case 5: {
								if ((status = GetData(tk, reinterpret_cast<float *>(&m_cpt.normal), 3)) != TK_Normal)
									return status;

								m_sub_sub_stage++;
							} nobreak;
								
							case 6: {
#else
							case 5: {
#endif // POINT_CLOUD_VERTEX_NORMALS
								m_num_points_remaining--;

								// Note: we do bounding box culling *then* sub-sampling -- if either is specified in isolation, it makes
								//   no difference, if both are specified together, this ordering may give different results than if we
								//   did sub-sampling and then bounding box culling
								if ((m_cpt.pt.x > m_std_bbox[0] || fabs(m_cpt.pt.x - m_std_bbox[0]) < FEPSILON) &&
									(m_cpt.pt.y > m_std_bbox[1] || fabs(m_cpt.pt.y - m_std_bbox[1]) < FEPSILON) &&
									(m_cpt.pt.z > m_std_bbox[2] || fabs(m_cpt.pt.z - m_std_bbox[2]) < FEPSILON) &&
									(m_cpt.pt.x < m_std_bbox[3] || fabs(m_cpt.pt.x - m_std_bbox[3]) < FEPSILON) &&
									(m_cpt.pt.y < m_std_bbox[4] || fabs(m_cpt.pt.y - m_std_bbox[4]) < FEPSILON) &&
									(m_cpt.pt.z < m_std_bbox[5] || fabs(m_cpt.pt.z - m_std_bbox[5]) < FEPSILON) &&
									(!m_need_to_subsample || ((double)rand() / (double)RAND_MAX <= m_pcw->GetSubSamplePercentage())))
								{
									if (m_point_bsp == 0)
									{
										m_point_bsp = new PointCloudBSP(m_std_bbox, -1, m_pcw->GetMaxShellSize(), true, 0.45f, 0.55f, 12, m_pcw);
#ifdef THREADED_PREPROCESS
										CREATE_THREAD(m_point_process_thread, m_point_process_function, this);
#endif // THREADED_PREPROCESS
									}

									if (m_num_points_remaining == 0)
										m_eof = true;

#ifdef THREADED_PREPROCESS
									m_point_buffer->m_buffer[m_point_buffer->m_count++] = m_cpt;
									
									if (m_point_buffer->m_count == m_current_point_buffer_size || m_eof) {
				 						LOCK_MUTEX(m_point_buffer_list_mutex);
										m_point_buffer_list->AddLast(m_point_buffer);
										
										m_bytes_used += (sizeof(PCPoint) * m_point_buffer->m_count);
										if (m_eof)
											m_no_more_points = true;
   										UNLOCK_MUTEX(m_point_buffer_list_mutex);	
										m_pcw->SetReadMemoryUsage(m_bytes_used);

										size_t total_memory_usage = m_bytes_used + (size_t)(m_pcw->GetCurrentMemoryUsage() * NUM_BYTES_IN_MEGABYTE);
										while (total_memory_usage >  m_pcw->GetMaxMemoryUsage() * NUM_BYTES_IN_MEGABYTE ||
											m_bytes_used >  (m_pcw->GetMaxMemoryUsage() / 2) * NUM_BYTES_IN_MEGABYTE)																													
										{
											total_memory_usage = m_bytes_used + (size_t)(m_pcw->GetCurrentMemoryUsage() * NUM_BYTES_IN_MEGABYTE);
											MILLI_SECOND_SLEEP(50);
										}
 
										if (!m_eof) {
											m_point_buffer = new PointBuffer_t;
											m_point_buffer->m_buffer = new PCPoint [THREAD_POINT_BUFFER_SIZE];
 											m_point_buffer->m_count = 0;
											m_current_point_buffer_size = THREAD_POINT_BUFFER_SIZE;

											if (m_point_buffer->m_buffer == 0) {
												while (1) {
													m_current_point_buffer_size /= 2;
													m_point_buffer->m_buffer = new PCPoint [m_current_point_buffer_size];
		 											
 													if (m_point_buffer->m_buffer)
														break;
												}
												
												MILLI_SECOND_SLEEP(5000);
 											}
										}
 									}
#else
									float bounds[6] = { m_cpt.pt.x, m_cpt.pt.y, m_cpt.pt.z, m_cpt.pt.x, m_cpt.pt.y, m_cpt.pt.z };
									m_point_bsp->Insert(&m_cpt, bounds);
								
#endif // THREADED_PREPROCESS
									m_num_points_sorted++;
									if (m_num_points_sorted % 1000000 == 0) {
										char temp[1024];
										char logging_str[4096] = { 0 };
										sprintf(temp, "%s M points / ", PrettifyInteger(m_num_points_sorted / 1000000));
										strcat(logging_str, temp);
										sprintf(temp, "%.2lf MB / ", m_pcw->GetCurrentMemoryUsage());
										strcat(logging_str, temp);
										sprintf(temp, "%d levels / ", m_point_bsp->GetCurrentDepth());
										strcat(logging_str, temp);
										sprintf(temp, "%s culled", PrettifyInteger(m_point_bsp->GetCulledCount()));
										strcat(logging_str, temp);
										
										m_pcw->LogMessage(logging_str, true);
									}
								}

								m_sub_sub_stage = 0; // this should be zero, we will only be exiting if we're at the end of the file
													 //   otherwise we keep reading and inserting into the BSP
							} break;
								
							default:
								return TK_Error;
						}
					}
					
					m_sub_stage++;
				} nobreak;
					
				case 2: {
#ifdef THREADED_PREPROCESS
					JOIN_THREAD(m_point_process_thread);
					m_point_process_thread = 0;
					
					DESTROY_MUTEX(m_point_buffer_list_mutex);

					assert(m_point_buffer_list->Count() == 0);
					delete m_point_buffer_list;
					m_point_buffer_list = 0;

					m_bytes_used = 0;
					m_pcw->SetReadMemoryUsage(0);
#endif // THREADED_PREPROCESS

#ifdef ENABLE_COMPRESSION
					PointCloudStreamFileToolkit *pcsftk = static_cast<PointCloudStreamFileToolkit *>(&tk);
					if ((status = pcsftk->stop_decompression()) != TK_Normal)
						return status;
#endif // ENABLE_COMPRESSION
					H_FORMAT_TEXT logging_str = H_FORMAT_TEXT("\t\t\tSorted %s points.", PrettifyInteger(m_num_points_sorted));
					m_pcw->LogMessage(logging_str);
					logging_str = H_FORMAT_TEXT("\t\t\tGenerated %s nodes.", PrettifyInteger(m_point_bsp->GetNodeCount()));
					m_pcw->LogMessage(logging_str);
					m_pcw->LogMessage("Done.\n\n", true);
					
					logging_str = H_FORMAT_TEXT("Starting OOC file generation...");
					m_pcw->LogMessage(logging_str, true);
					
					PointCloudIndexNodeData node_data(m_pcw, m_min_intensity, m_max_intensity);
					m_point_bsp->PerNodeMapFunction(ExportPointCloudIndexNodes, &node_data);
					node_data.ExportPointCloudIndex();
					
					logging_str = H_FORMAT_TEXT("Done.\n");
					m_pcw->LogMessage(logging_str, true);
					
					m_sub_stage = -1;
				} break;
					
				default:
					return TK_Error;
			}
			
			m_stage++;
		} nobreak;
			
		case 2: {
			unsigned char stop_code;
			if ((status = GetData(tk, stop_code)) != TK_Normal)
				return status;
			
			if (stop_code != TKE_Stop_User_Data)
				return tk.Error("Corrupt/invalid file");
			
			m_stage = -1;
		} break;
			
		default:
			status = TK_Error;
	}
	
	return status;
}

TK_Status TK_Point_Cloud_Data::Execute ( BStreamFileToolkit & tk ) alter {
	TK_Status status = TK_Normal;
	// TODO: eliminate this function?
	return status;
}

TK_Status TK_Point_Cloud_Data::Write ( BStreamFileToolkit & tk ) alter {
	TK_Status status = TK_Normal;
	switch (m_stage) {
		case 0: {
			if ((status = PutOpcode(tk, 0)) != TK_Normal)
				return status;
				
			m_sub_stage = 0;
			m_stage++;
		} nobreak;
		
		case 1: {
			// initialize various data structures with default values
			m_std_bbox[0] = 0.0f; m_std_bbox[1] = 0.0f; m_std_bbox[2] = 0.0f;
			m_std_bbox[3] = 0.0f; m_std_bbox[4] = 0.0f; m_std_bbox[5] = 0.0f;
			m_min_intensity = 0.0f; 
			m_max_intensity = 0.0f;
			
			m_pcw->GetPointCloudFileList()->ResetCursor();
			m_valid_point_count = 0;
			m_initial_pass = true; 

#ifdef ENABLE_COMPRESSION
			PointCloudStreamFileToolkit *pcsftk = static_cast<PointCloudStreamFileToolkit *>(&tk);
			if ((status = pcsftk->start_compression()) != TK_Normal)
				return status;
#endif // ENABLE_COMPRESSION

			m_stage++;
		} nobreak;

		case 2: {
			wchar_t const *current_file_name;
			while ((current_file_name = m_pcw->GetPointCloudFileList()->PeekCursor()) != 0) {
				if (m_current_point_cloud_file == NULL) {
					m_current_point_cloud_file = wfopen(current_file_name, L"r");
					if (m_current_point_cloud_file == NULL)
						return tk.Error("Problem opening point cloud file");

					wchar_t *extension = new wchar_t [wcslen(current_file_name) + 1];
					FindFileNameWithoutExtension(current_file_name, 0, extension);
					if (wcsieq(extension, L"pts"))
						m_point_cloud_file_type = PTS;
					else if (wcsieq(extension, L"ptx"))
						m_point_cloud_file_type = PTX;
					else if (wcsieq(extension, L"xyz"))
						m_point_cloud_file_type = XYZ;
					else
						m_point_cloud_file_type = UNKNOWN;
					delete [] extension;

					if (m_point_cloud_file_type == NONE)
						return tk.Error("No point cloud passed in");
					else if (m_point_cloud_file_type == UNKNOWN)
						return tk.Error("Uknown point cloud file type");

					uint64_t num_points;	// total number of points in the file (according to the file)
					m_line_number = 0;

					if (m_point_cloud_file_type == PTX) {
						int i;

						// read in number of columns and rows
						for ( i = 0 ; i < 2 ; i++ ) {
							uint64_t row_col_num;
							fgets(m_read_buffer, OOC_BUFFER_CHUNK_SIZE, m_current_point_cloud_file);
							sscanf(m_read_buffer, "%llu", &row_col_num);
							(i == 0) ? num_points = row_col_num : num_points *= row_col_num;
						}

						// get translation, and rotation (discard - grabbed below)
						for ( i = 0 ; i < 4 ; i++ )
							fgets(m_read_buffer, OOC_BUFFER_CHUNK_SIZE, m_current_point_cloud_file);

						// get the modeling m_matrix (duplicates of data above)
						for ( i = 0 ; i < 4 ; i++ ) {
							fgets(m_read_buffer, OOC_BUFFER_CHUNK_SIZE, m_current_point_cloud_file);
							sscanf(m_read_buffer, "%f%*c%f%*c%f%*c%f", &(m_matrix[4*i]), &(m_matrix[4*i + 1]), &(m_matrix[4*i + 2]), &(m_matrix[4*i + 3]));
						}

						m_line_number += 10;
					}
					else if (m_point_cloud_file_type == PTS) {
						// read in the point count
						fgets(m_read_buffer, OOC_BUFFER_CHUNK_SIZE, m_current_point_cloud_file);
						sscanf(m_read_buffer, "%llu", &num_points);

						m_line_number += 1;
					}
					else if (m_point_cloud_file_type == XYZ) {
						// nothing to be done -- no additional data
					}

					m_read_position = 0;
					m_eof = false; 
					m_no_more_reads = false;

					m_sub_stage = 0;
				}

				long line_len = 0;
				char *new_line_pos;
				float x = 0.0f, y = 0.0f, z = 0.0f, a = 0.0f;
				int b = 0, c = 0, d = 0, result;
#			ifdef POINT_CLOUD_VERTEX_NORMALS
				float xn = 0.0f, yn = 0.0f, zn = 0.0f;
#			endif // POINT_CLOUD_VERTEX_NORMALS
				
				while (1) {
					switch (m_sub_stage) {
						case 0: {
							// we never read in more than OOC_BUFFER_CHUNK_SIZE bytes so long is big enough
							m_amount_read = (long)fread(m_read_buffer + m_read_position, 1, OOC_BUFFER_CHUNK_SIZE - m_read_position, m_current_point_cloud_file);
							
							if (m_amount_read == 0 && feof(m_current_point_cloud_file))
								break;
							
							m_amount_read += m_read_position;
							if (m_amount_read < OOC_BUFFER_CHUNK_SIZE)
								m_no_more_reads = true;
							
							m_read_position = 0;
							
							m_sub_stage++;
							m_sub_sub_stage = 0;
						} nobreak;
							
						case 1: {
							do {
								switch (m_sub_sub_stage) {
									case 0: {
										x = 0.0f; y = 0.0f; z = 0.0f; a = 0.0f;
										b = 0; c = 0; d = 0;
#									ifdef POINT_CLOUD_VERTEX_NORMALS
										xn = yn = zn = 0.0f;
#									endif // POINT_CLOUD_VERTEX_NORMALS
										
										new_line_pos = strchr(m_read_buffer + m_read_position, '\n');
										if (new_line_pos == 0)
											m_eof = true;
										else {
											line_len = (long)(new_line_pos - (m_read_buffer + m_read_position));
											m_read_buffer[m_read_position + line_len] = '\0';

											if (m_read_buffer[m_read_position + line_len - 1] == '\r')
												m_read_buffer[m_read_position + line_len - 1] = '\0';
										}
										m_line_number++;
#									ifdef POINT_CLOUD_VERTEX_NORMALS
										result = sscanf(m_read_buffer + m_read_position, "%f%*c%f%*c%f%*c%f%*c%d%*c%d%*c%d%*c%f%*c%f%*c%f", 
														&x, &y, &z, &a, &b, &c, &d, &xn, &yn, &zn);
#									else
										result = fast_textscan(m_read_buffer + m_read_position, x, y, z, a, b, c, d);
//										result = sscanf(m_read_buffer + m_read_position, "%f%*c%f%*c%f%*c%f%*c%d%*c%d%*c%d", &x, &y, &z, &a, &b, &c, &d);
#									endif // POINT_CLOUD_VERTEX_NORMALS
										if (result == EOF) 
											return tk.Error(H_FORMAT_TEXT("Failed to parse line # %s:\n\t%s\nin file %ls", PrettifyInteger(m_line_number), m_read_buffer, current_file_name));
										if (!m_eof)
											m_read_position += line_len + 1;
										if (m_read_position >= m_amount_read && m_no_more_reads)
											m_eof = true;
#									ifdef POINT_CLOUD_VERTEX_NORMALS						
										m_cpt = PCPoint(x, y, z, (int)a, (unsigned char)b, (unsigned char)c, (unsigned char)d, xn, yn, zn);
#									else
										m_cpt = PCPoint(x, y, z, a, (unsigned char)b, (unsigned char)c, (unsigned char)d);
#									endif // POINT_CLOUD_VERTEX_NORMALS
										
										if (fabs(x) < 1e-8 && fabs(y) < 1e-8 && fabs(z) < 1e-8 && fabs(a - 0.5f) < 1e-8 && b == 0 && c == 0 && d == 0)
											m_cpt.vfield = PCPOINT_VALIDITY_INVALID;
										else {
											if (result == 3)
												m_cpt.vfield = PCPOINT_VALIDITY_XYZ;
											else if (result == 4)
												m_cpt.vfield = PCPOINT_VALIDITY_GRAY_SCALE_POINT;
											else if (result == 6)
												m_cpt.vfield = PCPOINT_VALIDITY_RGB_POINT;
#										ifdef POINT_CLOUD_VERTEX_NORMALS
											else if (result == 10)
#										else
											else if (result == 7)
#										endif // POINT_CLOUD_VERTEX_NORMALS
												m_cpt.vfield = PCPOINT_VALIDITY_ALL_VALID;
											else
												m_cpt.vfield = PCPOINT_VALIDITY_INVALID;
										}
										
										if (m_cpt.vfield & PCPOINT_VALIDITY_XYZ) {
											m_valid_point_count++;
											
											APoint temp(x, y, z);
											// if we have a PTX file, apply the transformation m_matrix
											if (m_point_cloud_file_type == PTX) {
												HC_Compute_Transformed_Points(1, &temp, m_matrix, &temp);
											}
											m_cpt.pt = temp;
											
											if (m_initial_pass) {
												m_min_intensity = a;
												m_max_intensity = a;
												m_std_bbox[0] = m_cpt.pt.x; m_std_bbox[1] = m_cpt.pt.y; m_std_bbox[2] = m_cpt.pt.z;
												m_std_bbox[3] = m_cpt.pt.x; m_std_bbox[4] = m_cpt.pt.y; m_std_bbox[5] = m_cpt.pt.z;
												m_initial_pass = false;
											}
											else {
												if (a < m_min_intensity)
													m_min_intensity = a;
												if (a > m_max_intensity)
													m_max_intensity = a;
												if (m_cpt.pt.x < m_std_bbox[0])
													m_std_bbox[0] = m_cpt.pt.x;
												if (m_cpt.pt.y < m_std_bbox[1])
													m_std_bbox[1] = m_cpt.pt.y;
												if (m_cpt.pt.z < m_std_bbox[2])
													m_std_bbox[2] = m_cpt.pt.z;
												if (m_cpt.pt.x > m_std_bbox[3])
													m_std_bbox[3] = m_cpt.pt.x;
												if (m_cpt.pt.y > m_std_bbox[4])
													m_std_bbox[4] = m_cpt.pt.y;
												if (m_cpt.pt.z > m_std_bbox[5])
													m_std_bbox[5] = m_cpt.pt.z;
											}
										}
										m_sub_sub_stage++;
									} nobreak;
										
									case 1: {
										if ((m_cpt.vfield & PCPOINT_VALIDITY_XYZ) && (status = PutData(tk, reinterpret_cast<float const *>(&m_cpt.pt), 3)) != TK_Normal)
											return status;
										
										m_sub_sub_stage++;
									} nobreak;
										
									case 2: {
										if ((m_cpt.vfield & PCPOINT_VALIDITY_XYZ) && (status = PutData(tk, m_cpt.intensity)) != TK_Normal)
											return status;
											
										m_sub_sub_stage++;
									} nobreak;
											
									case 3: {
										if ((m_cpt.vfield & PCPOINT_VALIDITY_XYZ) && (status = PutData(tk, reinterpret_cast<unsigned char const *>(&m_cpt.rgb_color), 3)) != TK_Normal)
											return status;
											
										m_sub_sub_stage++;
									} nobreak;
											
									case 4: {
										if ((m_cpt.vfield & PCPOINT_VALIDITY_XYZ) && (status = PutData(tk, m_cpt.vfield)) != TK_Normal)
											return status;
											
#								ifndef POINT_CLOUD_VERTEX_NORMALS
										m_sub_sub_stage = 0;
									} break;
#								else
										m_sub_sub_stage++;
									} nobreak;

									case 5: {
										if ((m_cpt.vfield & PCPOINT_VALIDITY_XYZ) && (status = PutData(tk, reinterpret_cast<float const *>(&m_cpt.normal), 3)) != TK_Normal)
											return status;

										m_sub_sub_stage = 0;
									} break;
#								endif // POINT_CLOUD_VERTEX_NORMALS									
									default:
										return tk.Error("Problem writing out binary version of point cloud");
								}

								if (m_eof)
									break;
							} while (m_read_position + 1024 < OOC_BUFFER_CHUNK_SIZE && m_read_position < m_amount_read);
							
							// we need to read in another chunk of the buffer
							m_sub_stage = 0;
						} break;
							
						default:
							return tk.Error("Problem parsing original point cloud");
					}
					
					if (m_eof)
						break;
					
					strncpy(m_read_buffer, m_read_buffer + m_read_position, OOC_BUFFER_CHUNK_SIZE - m_read_position);
					m_read_position = OOC_BUFFER_CHUNK_SIZE - m_read_position;	
				}
			
				if (m_eof) {
					fclose(m_current_point_cloud_file);
					m_current_point_cloud_file = NULL;
				}

				m_pcw->GetPointCloudFileList()->AdvanceCursor();
			}

			m_stage++;
		} nobreak;

		case 3: {
#ifdef ENABLE_COMPRESSION
			PointCloudStreamFileToolkit *pcsftk = static_cast<PointCloudStreamFileToolkit *>(&tk);
			if ((status = pcsftk->stop_compression()) != TK_Normal)
				return status;
#endif // ENABLE_COMPRESSION

			// write out metadata which consists of:
			//   - valid point count
			//   - computed bounding box
			//   - min and max intensities seen in file
			wchar_t *metadata_file_name = new wchar_t [m_pcw->GetStreamMetadataFileNameSize() + 1];
			m_pcw->GetStreamMetadataFileName(metadata_file_name);

			FILE *metadata_fp;

			if ((metadata_fp = wfopen(metadata_file_name, L"w")) == NULL)
				return tk.Error("Problem creating metadata file");

			delete [] metadata_file_name;

			fprintf(metadata_fp, "%llu\n%f\t%f\t%f\t%f\t%f\t%f\n%f\t%f\n", 
					m_valid_point_count,
					m_std_bbox[0], m_std_bbox[1], m_std_bbox[2], m_std_bbox[3], m_std_bbox[4], m_std_bbox[5], 
					m_min_intensity, m_max_intensity);
		
			fclose(metadata_fp);

			m_stage++;
		} nobreak;
		
		case 4: {
            if ((status = PutData (tk, (unsigned char)TKE_Stop_User_Data)) != TK_Normal)
                return status;
 
            m_stage = -1;
        } break;

        default:
			status = TK_Error;
	}
	
	return status;
}

TK_Status TK_Point_Cloud_Data::Interpret ( BStreamFileToolkit & tk, ID_Key key, int variant ) alter {
	TK_Status status = TK_Normal;
	// TODO: currently unused
	return status;
}

void TK_Point_Cloud_Data::Reset () alter {
	// TODO: currently unused
	TK_User_Data::Reset();
}

VBSPStatus TK_Point_Cloud_Data::ExportPointCloudIndexNodes ( TreeTraversal state, StreamFilePointContainer * container, 
															 BSPNodeMetadata<PCPoint *, StreamFilePointContainer> * node_metadata, void * user_data ) {
	PointCloudIndexNodeData *node_data = (PointCloudIndexNodeData *)user_data;
	
	node_data->SetContainer(container);
	node_data->SetTreeTraversalState(state);
	node_data->SetBSPNodeMetadata(node_metadata);
	node_data->Update();
	
	return VBSP_STATUS_CONTINUE;
}
