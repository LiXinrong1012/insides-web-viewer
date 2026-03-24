//
// Copyright (c) 2000 by Tech Soft 3D, LLC.
// The information contained herein is confidential and proprietary to
// Tech Soft 3D, LLC., and considered a trade secret as defined under
// civil and criminal statutes.  Tech Soft 3D shall pursue its civil
// and criminal remedies in the event of unauthorized use or misappropriation
// of its trade secrets.  Use of this information by anyone other than
// authorized employees of Tech Soft 3D, LLC. is granted only under a
// written non-disclosure agreement, expressly prescribing the scope and
// manner of such use.
//
// $Header: /files/homes/master/cvs/hoops_master/hoops_stream/source/HStream.cpp,v 1.46 2010-10-22 19:24:17 trask Exp $
//


#include "HStream.h"
#include "BInternal.h"


////////////////////////////////////////////////////////////////////////////////



TK_Status HStreamFileToolkit::Write_Stream_File () {
#ifndef HSTREAM_READONLY
    char                    block[TK_DEFAULT_BUFFER_SIZE];
    int                     limit = TK_DEFAULT_BUFFER_SIZE;
    TK_Status               status = TK_Normal;
    int                     amount = -1;
    TK_Progress_Callback    callback = 0;
    void *                  value = 0;
    unsigned HLONG			expected = 0;
    int						open_count_start, open_count_end;

    HC_Begin_Open_Segment_Search();
      HC_Show_Open_Segment_Count (&open_count_start);
    HC_End_Open_Segment_Search ();

    if (PeekTagIndex() != 0)
        return Error ("toolkit needs Restart() before file write");
        

    if (GetLogging()) {
        char const *            logfile = GetLogFile();

        if (logfile == null)
            logfile = "hsf_export_log.txt";

        if (OpenLogFile (logfile, "w") != TK_Normal)
            return TK_Error;
    }

    limit = GetBufferLimit();

	if ((status = OpenFile (m_wfilename, true)) != TK_Normal)
		return status;

    if ((callback = GetProgressCallback()) != 0) {
        expected = (unsigned HLONG)CountObjects ();
        value = GetProgressValue();
    }

    do {
        status = GenerateBuffer (block, limit, amount);

        if (status == TK_Error) {
            // whatever...
            break;
        }

        if (WriteBuffer (block, amount) != TK_Normal)
            break;

        if (callback) {
            if (!(*callback) (ObjectsSoFar(), (long)expected, value)) {
                status = TK_Abort;
                break;
            }
        }
    } while (status != TK_Complete);

    CloseFile ();

    if (GetLogging())
        CloseLogFile();

    Restart();

    HC_Begin_Open_Segment_Search();
      HC_Show_Open_Segment_Count (&open_count_end);
    HC_End_Open_Segment_Search ();

    if (status == TK_Error) {
		while (open_count_end > open_count_start) {
			HC_Close_Segment();
			open_count_end--;
		}
    }
    else if (open_count_start != open_count_end)
		status = Error ("internal error: unmatched open or close segment");

    return status;
#else
    return Error (stream_readonly);
#endif
}




TK_Status HTK_Write_Stream_File (char const * filename, HStreamFileToolkit * tk) {
	if (tk == null)
		return HTK_Write_Stream_File (filename);

    tk->SetFilename (filename);       

    return tk->Write_Stream_File ();
}

TK_Status HTK_Write_Stream_File (char const * filename, int flags) {
    HStreamFileToolkit *    tk;
    TK_Status               status;

    tk = new HStreamFileToolkit;

    tk->SetFilename (filename);       
    tk->SetWriteFlags (flags);       

    status = tk->Write_Stream_File ();

    delete tk;

    return status;
}

#ifdef _MSC_VER
TK_Status HTK_Write_Stream_File (unsigned short const * filename, HStreamFileToolkit * tk) {
	return HTK_Write_Stream_File((wchar_t const*)filename, tk);
}
#endif

TK_Status HTK_Write_Stream_File (wchar_t const * filename, HStreamFileToolkit * tk) {
	if (tk == null)
		return HTK_Write_Stream_File (filename);

	tk->SetFilename (filename);       

	return tk->Write_Stream_File ();
}

#ifdef _MSC_VER
TK_Status HTK_Write_Stream_File (unsigned short const * filename, int flags) {
	return HTK_Write_Stream_File((wchar_t const*)filename, flags);
}
#endif

TK_Status HTK_Write_Stream_File (wchar_t const * filename, int flags) {
	HStreamFileToolkit *    tk;
	TK_Status               status;

	tk = new HStreamFileToolkit;

	tk->SetFilename (filename);       
	tk->SetWriteFlags (flags);       

	status = tk->Write_Stream_File ();

	delete tk;

	return status;
}


TK_Status HTK_Write_Stream_File (char const * filename, int flags, HStreamFileToolkit * tk) {
    if (tk != null)
	{
		TK_Status status;
		int old_flags=tk->GetWriteFlags();
		
		if(!old_flags)
			tk->SetWriteFlags(flags);

        status=HTK_Write_Stream_File (filename, tk);

		tk->SetWriteFlags(old_flags);

		return status;
	}
    else
        return HTK_Write_Stream_File (filename, flags);
}




///////////////////////////////////////////////////////////////////////////////////////////////////


// wrapper around base reader, with a few extra Hoops-specific checks

TK_Status HTK_Read_Stream_File (char const * filename, HStreamFileToolkit * tk) {
    TK_Status               status = TK_Normal;
    int                     open_count_start, open_count_end;

    if (tk == null)
        return HTK_Read_Stream_File (filename);

    HC_Begin_Open_Segment_Search();
     HC_Show_Open_Segment_Count (&open_count_start);
    HC_End_Open_Segment_Search ();


    status = TK_Read_Stream_File (filename, tk);


    if (!tk->HeaderCommentSeen())
        status = tk->Error("header comment was never processed (thus format version is uncertain)");

    HC_Begin_Open_Segment_Search();
     HC_Show_Open_Segment_Count (&open_count_end);
    HC_End_Open_Segment_Search ();
    if (status == TK_Error) {
        while (open_count_end > open_count_start) {
            HC_Close_Segment();
            open_count_end--;
        }
    }
    else if (open_count_start != open_count_end)
        status = tk->Error("invalid hsf data or internal error: unmatched open or close segment");


    return status;
}


TK_Status HTK_Read_Stream_File (char const * filename, int flags) {
    HStreamFileToolkit *    tk;
    TK_Status               status;

    tk = new HStreamFileToolkit;
    tk->SetReadFlags (flags);      

    status = HTK_Read_Stream_File (filename, tk);

    delete tk;

    return status;
}

#ifdef _MSC_VER
TK_Status HTK_Read_Stream_File (unsigned short const * filename, HStreamFileToolkit * tk) {
	return HTK_Read_Stream_File((wchar_t const *) filename, tk);
}
#endif

TK_Status HTK_Read_Stream_File (wchar_t const * filename, HStreamFileToolkit * tk) {
	TK_Status               status = TK_Normal;
	int                     open_count_start, open_count_end;

	if (tk == null)
		return HTK_Read_Stream_File (filename);

	HC_Begin_Open_Segment_Search();
	 HC_Show_Open_Segment_Count (&open_count_start);
	HC_End_Open_Segment_Search ();


	status = TK_Read_Stream_File (filename, tk);


	if (!tk->HeaderCommentSeen())
		status = tk->Error("header comment was never processed (thus format version is uncertain)");

	HC_Begin_Open_Segment_Search();
	 HC_Show_Open_Segment_Count (&open_count_end);
	HC_End_Open_Segment_Search ();
	if (status == TK_Error) {
		while (open_count_end > open_count_start) {
			HC_Close_Segment();
			open_count_end--;
		}
	}
	else if (open_count_start != open_count_end)
		status = tk->Error("invalid hsf data or internal error: unmatched open or close segment");


		return status;
}

#ifdef _MSC_VER
TK_Status HTK_Read_Stream_File (unsigned short const * filename, int flags) {
	return HTK_Read_Stream_File((wchar_t const *) filename, flags);
}
#endif



TK_Status HTK_Read_Stream_File (wchar_t const * filename, int flags) {
	HStreamFileToolkit *    tk;
	TK_Status               status;

	tk = new HStreamFileToolkit;
	tk->SetReadFlags (flags);      

	status = HTK_Read_Stream_File (filename, tk);

	delete tk;

	return status;
}



TK_Status HTK_Read_Stream_File (char const * filename, int flags, HStreamFileToolkit * tk) {
    if (tk != null)
        return HTK_Read_Stream_File (filename, tk);
    else
        return HTK_Read_Stream_File (filename, flags);
}

