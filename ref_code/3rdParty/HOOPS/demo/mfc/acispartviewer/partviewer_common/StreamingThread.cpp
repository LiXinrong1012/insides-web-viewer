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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/StreamingThread.cpp,v 1.36 2008-11-21 20:37:17 jason Exp $
//

#include "stdafx.h"
#include "StreamingThread.h"
#include "HSInclude.h"

#include "HStream.h"
#include "hsolidmodel.h"
#include "CSolidHoopsView.h"
#include "HErrorManager.h"
#include "HSolidView.h"
#include "CSolidHoopsApp.h"

unsigned int HStreamFileReadingThread(LPVOID pParam)
{
	CSolidHoopsApp * app = (CSolidHoopsApp *) AfxGetApp();
	
    int  amount;
	TK_Status status = TK_Normal;
	CSolidHoopsView *pCSHView = (CSolidHoopsView *)pParam;
	HSolidView* pHView = (HSolidView*) pCSHView->m_pHView;
	HSolidModel * pModel = (HSolidModel*) pHView->GetModel();
	HStreamFileToolkit * tk = pModel->GetStreamFileTK();
	pCSHView->m_hStreamBufferAccessEvent = CreateEvent( NULL, TRUE, TRUE, NULL );
	assert( pCSHView->m_hStreamBufferAccessEvent );
	bool shutting_down = false;

	int const STREAM_BUFF_SIZE = 1024*64;
	char file_buffer[STREAM_BUFF_SIZE];

    while (1) 
	{

		while (HErrorManager::GetDialogRunning())
			Sleep(100);
		// wait for the main thread to complete it's parsing
 		while(1)
		{
			// if main thread has parsed, go ahead for next read
			DWORD wait_ret = MsgWaitForMultipleObjects(1, &pCSHView->m_hStreamBufferAccessEvent, FALSE, INFINITE, 0);
			if( (wait_ret - WAIT_OBJECT_0) == 0 )
				break;
		}
		if (app->ShuttingDown())
			break;

		if (pCSHView->m_cease)
			break;

        status = tk->ReadBuffer (file_buffer, STREAM_BUFF_SIZE, amount);

		if (status != TK_Normal)
		{ 
			break;
		}

	
		pHView->EmitHSFData( ".", file_buffer, STREAM_BUFF_SIZE);

		// set nonsignaled state on event. The main thread is suppose to signal 
		// the state back up again once it is done with parsing of buffer - Rajesh B
		ResetEvent( pCSHView->m_hStreamBufferAccessEvent );

		if( !pCSHView->m_cease && ::IsWindow(((CWnd *)pCSHView)->GetSafeHwnd()) ){
			((CWnd *)pCSHView)->PostMessage(WM_NEW_STREAM_FILE_BUFFER, (WPARAM)file_buffer, STREAM_BUFF_SIZE);
		}
		else {
			shutting_down = true;
			break;
		}

	}

	if( !shutting_down && !app->ShuttingDown()){
		((CWnd *)pCSHView)->PostMessage(WM_READING_THREAD_COMPLETED, 0, 0);
	}

	// do not call HC_ call from this thread!!!
	//pHView->FlushProgressBar();
	if( pCSHView->m_hStreamBufferAccessEvent )
	{
		CloseHandle(pCSHView->m_hStreamBufferAccessEvent);
		pCSHView->m_hStreamBufferAccessEvent = 0;
	}
	return 0;
}
