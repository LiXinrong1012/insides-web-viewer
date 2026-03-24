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
 * $Id: PointCloudStreamFileToolkit.cpp,v 1.18 2010-05-04 22:42:42 chad Exp $
 */

#include "PointCloudStreamFileToolkit.h"

#include <sys/stat.h>
#include <errno.h>

#include "PointCloudCommon.h"
#include "PointCloudData.h"
#include "PointCloudNode.h"
#include "PointCloudNodeRandomized.h"

#include "BOpcodeShell.h"

/*****************************************************************************************************/

PointCloudStreamFileToolkit::PointCloudStreamFileToolkit ( PointCloudWorld * pcw_in, unsigned int max_file_size_in ) {
	m_pcw = pcw_in;
	m_stream_buffer = 0;
	m_write_file_name = 0;
	m_point_cloud_stream_file = 0;
	m_limit = 0;


	m_block = 0;
	SetBufferLimit(TK_DEFAULT_BUFFER_SIZE);
	m_current_opcode = 0;
	m_amount_pending = 0;
	m_amount_written = 0;
	m_amount_read = 0;
	if (max_file_size_in == 0)
		m_max_file_size = OOC_MAX_FILE_SIZE;
	else
		m_max_file_size = max_file_size_in;
	m_split_file_count = 0;
	m_can_pause = true;
	m_can_iterate = false;

}

PointCloudStreamFileToolkit::~PointCloudStreamFileToolkit () {
	delete [] m_block;

	delete [] m_write_file_name;
	delete [] m_point_cloud_stream_file;
}

void PointCloudStreamFileToolkit::SetBufferLimit ( int buffer_limit_in ) alter {
	m_buffer_limit = (buffer_limit_in > 0 ? buffer_limit_in : TK_DEFAULT_BUFFER_SIZE);
	delete [] m_block;
	m_block = new char [m_buffer_limit];
}

// this resets our internal opcode list
void PointCloudStreamFileToolkit::ResetOpcodes () alter {
	m_opcodes.TrimSize(1);
	m_opcodes.Pop();
}

// this adds an opcode handler to our internal list so the writer knows to write that particular opcode
void PointCloudStreamFileToolkit::SetOpcodeHandler ( int which, BBaseOpcodeHandler * handler ) alter {
	bool add_to_opcode_list = true;
	for ( int i = 0 ; i < m_opcodes.Count() ; ++i ) {
		if (m_opcodes[i] == which) {
			add_to_opcode_list = false;
			break;
		}
	}
	if (add_to_opcode_list)
		m_opcodes.Append(which);
	BStreamFileToolkit::SetOpcodeHandler(which, handler);
}

PointCloudStatus PointCloudStreamFileToolkit::Generate_OOC_File () alter {
	delete [] m_point_cloud_stream_file;
	
	wchar_t logging_str[4096];

	m_pcw->LogMessage("Input point cloud file(s):");

	wchar_t const *point_cloud_file;
	m_pcw->GetPointCloudFileList()->ResetCursor();
	while ((point_cloud_file = m_pcw->GetPointCloudFileList()->PeekCursor()) != 0) {
		swprintf(logging_str, 4096, L"\t\"%ls\"", point_cloud_file);
		m_pcw->LogMessage(logging_str);
		m_pcw->GetPointCloudFileList()->AdvanceCursor();
	}
	m_pcw->LogMessage("\n");
	
	swprintf(logging_str, 4096, L"Maximum shell size: %d\nMemory usage will be capped at %ld MB\n", m_pcw->GetMaxShellSize(), m_pcw->GetMaxMemoryUsage());
	m_pcw->LogMessage(logging_str);

	m_point_cloud_stream_file = new wchar_t [m_pcw->GetStreamFileNameSize() + 1];
	m_pcw->GetStreamFileName(m_point_cloud_stream_file);

	wchar_t *stream_file_output_directory = new wchar_t [m_pcw->GetStreamFileNameSize() + 1];
	FindFileNameWithoutDirectory(m_point_cloud_stream_file, stream_file_output_directory);

	swprintf(logging_str, 4096, L"Binary copy of file will be placed here: \"%ls\"", stream_file_output_directory);
	m_pcw->LogMessage(logging_str);

	bool skip_binary_file_generation = false;
	if (wmkdir(stream_file_output_directory)) {
		if (errno == EEXIST) {
			if (m_pcw->GetOverwriteExistingFiles()){
				swprintf(logging_str, 4096, L"Overwriting existing files in \"%ls\"", stream_file_output_directory);
				m_pcw->LogMessage(logging_str);
			}
			else {
				swprintf(logging_str, 4096, L"Directory \"%ls\" already exists.\nEither move, delete or allow overwriting to continue.\n", stream_file_output_directory);
				m_pcw->LogMessage(logging_str);
				return PRE_PROCESS_SETUP_FAILURE;
			}
//#ifdef _DEBUG
			FILE *test_stream_file_fp = wfopen(m_point_cloud_stream_file, L"rb");
			if (test_stream_file_fp) {
				fclose(test_stream_file_fp);
				wchar_t *metadata_file_name = new wchar_t [m_pcw->GetStreamMetadataFileNameSize() + 1];
				m_pcw->GetStreamMetadataFileName(metadata_file_name);
				FILE *test_metadata_file_fp = wfopen(metadata_file_name, L"r");
				if (test_metadata_file_fp) {
					fclose(test_metadata_file_fp);
					swprintf(logging_str, 4096, L"DEBUG: Using existing files in \"%ls\"", stream_file_output_directory);
					m_pcw->LogMessage(logging_str);
					skip_binary_file_generation = true;
				}
				delete [] metadata_file_name;
			}
//#endif
		}
		else {
			swprintf(logging_str, 4096, L"Problem creating stream file directory: %s\n%ls\n", strerror(errno), stream_file_output_directory);
			m_pcw->LogMessage(logging_str);
			return PRE_PROCESS_SETUP_FAILURE;
		}
	}
	m_pcw->LogMessage("\n");

	delete [] stream_file_output_directory;

	// numbers are meaningless - just needed to get path to nodes directory
	//   (http://www.research.att.com/~njas/sequences/A060843)
	float temp_bbox[6] = { 1, 6, 21, 107, 4.717687e7f, 8.690333e15f };
	wchar_t *temp_node_file = new wchar_t [m_pcw->GetNodeFileNameSize() + 1];
	m_pcw->GetFullNodeFileName(temp_bbox, temp_node_file);
	wchar_t *node_file_output_directory = new wchar_t [m_pcw->GetNodeFileNameSize() + 1];
	FindFileNameWithoutDirectory(temp_node_file, node_file_output_directory);

	swprintf(logging_str, 4096, L"Nodes referenced by OOC file will be placed here: \"%ls\"", node_file_output_directory);
	m_pcw->LogMessage(logging_str);
	
	if (wmkdir(node_file_output_directory)) {
		if (errno == EEXIST) {
			if (m_pcw->GetOverwriteExistingFiles()) {
				swprintf(logging_str, 4096, L"Overwriting existing files in \"%ls\"", node_file_output_directory);
				m_pcw->LogMessage(logging_str);
			}
			else {
				swprintf(logging_str, 4096, L"Directory \"%ls\" already exists.\nEither move, delete or allow overwriting to continue.\n", node_file_output_directory);
				m_pcw->LogMessage(logging_str);
				return PRE_PROCESS_SETUP_FAILURE;
			}
		}
		else {
			swprintf(logging_str, 4096, L"Problem creating node file directory: %s\n%ls\n", strerror(errno), node_file_output_directory);
			m_pcw->LogMessage(logging_str);
			return PRE_PROCESS_SETUP_FAILURE;
		}
	}

	delete [] temp_node_file;
	delete [] node_file_output_directory;
	
	SetBufferLimit(OOC_BUFFER_CHUNK_SIZE);
	SetOpcodeHandler(TKE_Start_User_Data, new TK_Point_Cloud_Data(m_pcw));
	
	TK_Status status = TK_Normal;
	
	m_pcw->LogMessage("\n");
	m_pcw->LogMessage("Computing bounding and generating binary version of file", true);
	if (!skip_binary_file_generation && (status = Initial_Pass()) != TK_Complete) {
		m_pcw->LogMessage("Failed.\n\n", true);
		return PRE_PROCESS_FIRST_PASS_FAILURE;
	}
	m_pcw->LogMessage("Done.\n\n", true);

	if ((status = Second_Pass()) != TK_Complete)
		return PRE_PROCESS_SECOND_PASS_FAILURE;
	
	return PRE_PROCESS_SUCCESS;
}

PointCloudStatus PointCloudStreamFileToolkit::Read_OOC_File () alter {
	TK_Status status = Read_Stream_File(m_pcw->GetOOCFileName());
	if (status == TK_Complete)
		return LOAD_SUCCESS;
	else
		return LOAD_FAILURE;
}

// this is a pared down version of BStreamFileToolkit::Read_Stream_File
//   - basically those elements present in BStreamFileToolkit::Read_Stream_File which are not required have been removed
TK_Status PointCloudStreamFileToolkit::Read_Stream_File ( wchar_t const * stream_file_in ) alter {
    TK_Status 	status = TK_Normal;
    bool      	version_mismatch = false;
    int      	base_stream_flags;
	int		  	version;

    if (GetLogging()) {
        char const *logfile = GetLogFile();

        if (logfile == 0)
            logfile = "pcsf_import_log.txt";

        if (OpenLogFile(logfile, "w") != TK_Normal)
            return TK_Error;
    }

    m_limit = GetBufferLimit();
    base_stream_flags = GetReadFlags();

	if ((status = OpenFile(stream_file_in)) != TK_Normal)
		return status;
	
    do {
		m_suppress_errors = false;
		
		int amount;
		
		if (ReadBuffer(m_block, m_limit, amount) != TK_Normal)
			break;

		m_amount_read += amount;

		if (m_amount_read == m_max_file_size) {
			SplitFile(stream_file_in);
			m_amount_read = 0;
		}
		
		if ((version = ParseVersion(m_block)) != 0) {
			if (version > TK_File_Format_Version) {
				version_mismatch = true;
				int temp_base_stream_flags = base_stream_flags | TK_Ignore_Version;
				SetReadFlags(temp_base_stream_flags);
			}
		}
		
		if (version_mismatch) {
			try {
				status = ParseBuffer(m_block, amount);
				if (status == TK_Error) {
					status = TK_Version;
					break;
				}
			}
			catch (...) {
				status = TK_Version;
				break;
			}
		}
		else {
			status = ParseBuffer(m_block, amount);
			if (status == TK_Error)
				break;
		}
		
		if (status == TK_Error)
			break;

    } while (status != TK_Complete);

    if (GetLogging())
        CloseLogFile();

	CloseFile();

	if (m_amount_read == 0 && m_split_file_count > 0)
		wremove(stream_file_in);

    SetReadFlags(base_stream_flags);   // restore in case we tried Ignore_Version

    return status;
}

TK_Status PointCloudStreamFileToolkit::Write_Stream_File ( wchar_t const * in_file_name, PointCloudStreamFileWriteMode in_write_mode ) alter {
	TK_Status status = TK_Normal;

	assert(m_write_file_name == 0);

	m_write_mode = in_write_mode;
	size_t file_name_len = wcslen(in_file_name);
	m_write_file_name = new wchar_t [file_name_len + 1];
	wcscpy(m_write_file_name, in_file_name);

	status = Write_Stream_Data();

	delete [] m_write_file_name;
	m_write_file_name = 0;

	return status;
}

TK_Status PointCloudStreamFileToolkit::Write_Stream_Buffer ( VCharArray * out_buffer ) alter {
	TK_Status status = TK_Normal;

	assert(m_stream_buffer == 0);
	m_stream_buffer = out_buffer;

	status = Write_Stream_Data();

	m_stream_buffer = 0;

	return status;
}

TK_Status PointCloudStreamFileToolkit::Write_Stream_Data () alter {
	TK_Status 	status = TK_Normal;
	int 		amount = 0;
	bool		file_mode = true;

	if (!m_write_file_name && !m_stream_buffer)
		return Error("no buffer or file to write to");

	if (m_write_file_name && m_stream_buffer)
		return Error("must specify file *OR* buffer to write to, not both");

	file_mode = (m_write_file_name ? true : false);
	
    if (PeekTagIndex() != 0)
        return Error("toolkit needs Restart() before file write");
	
    if (GetLogging()) {
        char const *logfile = GetLogFile();
		
        if (logfile == 0)
            logfile = "pcsf_export_log.txt";
		
        if (OpenLogFile(logfile, "w") != TK_Normal)
            return TK_Error;
    }
	
	if (file_mode) {
		if (m_write_mode == Standard)
			status = OpenFile(m_write_file_name, true);
		else if (m_write_mode == Append) {
			if (m_file == NULL) {
				status = OpenFileForAppend(m_write_file_name);
				PositionFile(m_amount_written);
			}
			// otherwise, the file handle should still be valid
		}
		else
			return Error("invalid write mode specified");
	}
	
	if (status != TK_Normal)
		return status;
	
    do {
		char *remaining_block = m_block + m_amount_pending;
		m_limit = GetBufferLimit() - m_amount_pending;
		
        status = GenerateBuffer(remaining_block, m_limit, amount);
		
		if (status == TK_Pause)
			m_amount_pending += amount;
		
        if (status == TK_Error || status == TK_Pause)
            break;

		amount += m_amount_pending;
		m_amount_pending = 0;
 
		if (file_mode) {
			if (m_amount_written + amount > m_max_file_size) {
				m_amount_pending = m_amount_written + amount - m_max_file_size;
				m_split_buffer.AppendArray(m_block + amount - m_amount_pending, m_amount_pending);
			}
		
			if (WriteBuffer(m_block, amount - m_amount_pending) != TK_Normal)
				break;
		
			m_amount_written += amount - m_amount_pending;
			
			if (m_amount_pending) {
				SplitFile(m_write_file_name, true);
				m_amount_written = 0;
				memcpy(m_block, m_split_buffer, m_split_buffer.Count());
				m_split_buffer.SetCount(0);

				// NOTE: we are assuming that m_buffer_limit < m_max_file_size
				if (status == TK_Complete)
					WriteBuffer(m_block, m_amount_pending);
			}
		}
		else {
			m_stream_buffer->AppendArray(m_block, amount);

			m_amount_written += amount;
		}
    } while (status != TK_Complete);
	
	if (file_mode) {
		// only close the file if we won't be appending to it (or an error occurred)
		if (status != TK_Pause)
			CloseFile();
	}
	
    if (GetLogging())
        CloseLogFile();
	
    return status;	
}

TK_Status PointCloudStreamFileToolkit::Finalize_Stream_File ( wchar_t const * stream_file_out ) alter {
	TK_Status status = TK_Complete;
	
	m_can_pause = false;
	
	if (m_amount_pending)
		status = Write_Stream_File(stream_file_out, Append);
	
	return status;
}

void PointCloudStreamFileToolkit::Stream_File_Iteration ( wchar_t const * stream_file_out ) alter {
	// we're already ready to iterate
	if (m_can_iterate)
		return;
	
	// dump whatever opcodes haven't written out yet to disk
	TK_Status status = Finalize_Stream_File(stream_file_out);
	
	if (status != TK_Complete)
		assert(0);
	
	status = Read_Stream_File(stream_file_out);
	
	if (status != TK_Complete)
		assert(0);
	
	m_can_iterate = true;
}

TK_Status PointCloudStreamFileToolkit::Initial_Pass () alter {
	Restart();
	return Write_Stream_File(m_point_cloud_stream_file);
}

TK_Status PointCloudStreamFileToolkit::Second_Pass () alter {
	Restart();
	return Read_Stream_File(m_point_cloud_stream_file);
}

TK_Status PointCloudStreamFileToolkit::GenerateBuffer ( char * buffer, int size, int alter & written ) alter {
	TK_Status status = TK_Complete;
	
	if ((status = PrepareBuffer(buffer, size)) != TK_Normal)
		goto finish;
	
	switch (BStreamFileToolkit::m_stage) {
		case 0: {
			if (m_current_object != m_default_object) {
				status = TK_Error;
				goto finish;
			}
			
			// make sure we write out version info
			m_current_object = new TK_Header();
			
			if ((status = m_current_object->Write(*this)) != TK_Normal)
				goto finish;
			
			delete m_current_object;
			m_current_object = 0;
			m_current_opcode = 0;

			BStreamFileToolkit::m_substage = 0;
			BStreamFileToolkit::m_stage++;
		} nobreak;
			
		case 1: {
			while (m_current_opcode < m_opcodes.Count()) {
				// make sure current object is up-to-date in case of context switch
				m_current_object = opcode_handler(m_opcodes[m_current_opcode]);
				
				switch (BStreamFileToolkit::m_substage) {
					case 0: {
						if ((status = m_current_object->Interpret(*this, -1)) != TK_Normal)
							goto finish;
							
						BStreamFileToolkit::m_substage++;
					} nobreak;
					
					case 1: {
						if ((status = m_current_object->Write(*this)) != TK_Normal)
							goto finish;
							
						m_current_opcode++;
						BStreamFileToolkit::m_substage = 0;
					} break;
					
					default: {
						status = TK_Error;
						goto finish;
					}
				}
			}
			
			BStreamFileToolkit::m_stage++;
		} nobreak;
			
		case 2: {
			m_current_object = opcode_handler(TKE_Termination);
			
			if ((status = m_current_object->Write(*this)) != TK_Normal)
				goto finish;
			
			status = TK_Complete;
			
			m_current_object->Reset();
			m_current_object = m_default_object;
			
			BStreamFileToolkit::m_stage = -1;
		} break;
			
		default:
			status = TK_Error;
	}
	
finish:
	written = CurrentBufferLength();
	
	// TK_Revisit => need to run through opcodes again, but pause writing for the moment
	// TK_Abort => need to create a split file
	if (status == TK_Revisit) {
		BStreamFileToolkit::m_substage = 0;
		m_current_opcode = 0;
		status = TK_Pause;
	}
	
	return status;
}

int PointCloudStreamFileToolkit::GetSplitFileNameSize ( wchar_t const * file_name_in ) {
	// split file name = original file name + '.' + m_split_file_count
	return static_cast<int>(wcslen(file_name_in) + 1 + m_split_file_count);
}

void PointCloudStreamFileToolkit::GetSplitFileName ( wchar_t const * file_name_in, wchar_t * file_name_out ) {
	swprintf(file_name_out, GetSplitFileNameSize(file_name_in) + 1, L"%ls.%d", file_name_in, m_split_file_count);
}

TK_Status PointCloudStreamFileToolkit::SplitFile ( wchar_t const * name, bool write_flag ) alter {
	CloseFile();
	m_split_file_count++;
	TK_Status status = TK_Normal;
	
	if ((status = OpenFile(name, write_flag)) != TK_Normal)
		return status;
	
	return status;
}

TK_Status PointCloudStreamFileToolkit::OpenFile ( wchar_t const * name, bool write_flag ) alter {
	wchar_t const *actual_file_name = 0;
	wchar_t *split_file_name = 0;
	
	if (m_split_file_count == 0)
		actual_file_name = name;
	else {
		split_file_name = new wchar_t [GetSplitFileNameSize(name) + 1];
		GetSplitFileName(name, split_file_name);
		actual_file_name = split_file_name;
	}
	
	TK_Status status = BStreamFileToolkit::OpenFile(actual_file_name, write_flag);
	
	if (split_file_name)
		delete [] split_file_name;
		
	return status;
}

TK_Status PointCloudStreamFileToolkit::OpenFileForAppend ( wchar_t const * name ) alter {
	wchar_t const *actual_file_name = 0;
	wchar_t *split_file_name = 0;
	
	if (m_split_file_count == 0)
		actual_file_name = name;
	else {
		split_file_name = new wchar_t [GetSplitFileNameSize(name) + 1];
		GetSplitFileName(name, split_file_name);
		actual_file_name = split_file_name;
	}
	
	if ((m_file = wfopen(actual_file_name, L"rb+")) == NULL)
		return Error("file open error");
	SetFilename(actual_file_name);
	
	if (split_file_name)
		delete [] split_file_name;
	
	return TK_Normal;
}

TK_Status PointCloudStreamFileToolkit::GetFilePosition ( long & pos ) const {
	FILE *fp = (FILE *)m_file;
	
	if (fp == NULL)
		return Error("no file open");
	
	if ((pos = ftell(fp)) < 0)
		return Error(H_FORMAT_TEXT("file position failure : %s", strerror(errno)));
	
	return TK_Normal;
}

void PointCloudStreamFileToolkit::SoftRestart () alter {
	if (m_file != 0)
		CloseFile();
}

void PointCloudStreamFileToolkit::Restart () alter {
	m_limit = 0;
	
	// TODO: Move these to PointCloudStreamFileToolkitState::Restart?
	m_amount_pending = 0;
	m_amount_written = 0;
	m_split_file_count = 0;
	m_can_pause = true;
	m_can_iterate = false;
	
	BStreamFileToolkit::Restart();
}
