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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/CSolidHoopsDoc.cpp,v 1.61 2009-06-16 00:25:02 nathan Exp $
//

// CSolidHoopsDoc.cpp : implementation file
//

#include "stdafx.h"

#include "HSInclude.h"

#include "CSolidHoopsApp.h"
#include "CSolidHoopsDoc.h"

#include "HSolidModel.h"
#include "HUtilityLocaleString.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CSolidHoopsApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSolidHoopsDoc

IMPLEMENT_DYNCREATE(CSolidHoopsDoc, CHoopsDoc)



BEGIN_MESSAGE_MAP(CSolidHoopsDoc, CHoopsDoc)
	//{{AFX_MSG_MAP(CSolidHoopsDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()







CSolidHoopsDoc::CSolidHoopsDoc()
{
	m_pHoopsModel = 0;
 	m_bDeferFileReadForView = false;
	m_bIsPsf = false;
	dictionary_loaded = false;
	m_bReadSimpleHsf = false;
	reading_mode = TK_Normal;
	m_bStreamInProgress = false;
}


CSolidHoopsDoc::~CSolidHoopsDoc()
{

	if (m_bReadSimpleHsf)
		m_pHoopsModel->GetStreamFileTK()->CloseFile();
	
	if (m_pHoopsModel)
	{
		delete m_pHoopsModel;
		m_pHoopsModel = 0;
	}
	HC_Update_Display();
}


// user has created a new document
BOOL CSolidHoopsDoc::OnNewDocument()
{
	if (!CHoopsDoc::OnNewDocument())
		return FALSE;
	// create a new HSolidModel object for this Document
	m_pHoopsModel = new HSolidModel();
	m_pHoopsModel->Init();

	if (!m_pHoopsModel)
		return false;

	return true;
}


// user has opened an HMF or XMT file
BOOL CSolidHoopsDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	char extension[MVO_BUFFER_SIZE];
	HUtility::FindFileNameExtension(H_ASCII_TEXT(lpszPathName), extension);

	theApp.LoadFileOptions(lpszPathName);
	
	// create a new HSolidModel object for this Document
	m_pHoopsModel = new HSolidModel();
	if (!m_pHoopsModel)
		return FALSE;

	m_pHoopsModel->Init();
	m_pHoopsModel->SetObjectCheck(CAppSettings::bRestoreAnnotations);


	//treat hsf+ as an hsf
	if ( streq(extension,"hsf+") )
		extension[3]=0;

	_tcscpy(filename, lpszPathName);

	if (streq(extension,"hsf") || streq(extension, KERN_STREAM_FILE)) 
	{
		// check if user wants to read simplified hsf and we can read it
		// the condition to be able to read is, the file must have dictionary saved in
		// And to peek in and check if dictionary is - the only one way is to read the header
		if( CAppSettings::bReadSimpleHsf )
		{
			// create a temporary stream toolkit object and read the header
			int header_size = 1024;	// arbitary
			int header_read = 0;	// arbitary
			char header[MVO_BUFFER_SIZE];
			BStreamFileToolkit header_reader;
			header_reader.OpenFile( (const char *)lpszPathName );
			header_reader.ReadBuffer( header, 1024, header_read );
			header_reader.ParseBuffer( header, header_size );
			if( (header_reader.GetWriteFlags() & TK_Generate_Dictionary) == TK_Generate_Dictionary)
				SetReadSimpleHsfFlag( true );
			else
				AfxMessageBox(_T("Dictionary not found. Unable to read file in simplified mode.\nPlease use File Settings dialog to export the dictionary while generating hsf file."));

			header_reader.CloseFile();
		}

		m_bDeferFileReadForView = true;
			
 

#ifndef HOOPS_ONLY
		if (streq(extension, KERN_STREAM_FILE))
		{
			((HSolidModel *) m_pHoopsModel)->m_bSolidData = true;
			((HSolidModel *) m_pHoopsModel)->m_bSolidModel = true;
		}
		else
#endif
			((HSolidModel *) m_pHoopsModel)->m_bSolidModel = false;
	}

	else if(streq(extension, "dwf"))
	{
		CAppSettings::RenderMode=HRenderGouraudWithLines;
		m_bDeferFileReadForView = true;
	}
	// read the file (HMF or XMT) into the Model Object
	else if(streq(extension, "hmf"))
	{		
		m_bDeferFileReadForView = true;
	}
	else if(streq(extension, "skp"))
	{		
		m_bDeferFileReadForView = true;
	}
	else
	{
		// NOTE: Having lines on turns out to be a great pain for large DWG files
		// Let the default rendermode rule - until we find a way to distinguish a 2D from 3D model
		// - Rajesh B (06-Sep-07)
		if(/*streq(extension, "dwg") ||*/ streq(extension,"dgn"))
			CAppSettings::RenderMode=HRenderGouraudWithLines;

 		m_bDeferFileReadForView = true;
 	}

	return TRUE;
}




BOOL CSolidHoopsDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CHoopsDoc::OnSaveDocument(lpszPathName);
}



/////////////////////////////////////////////////////////////////////////////
// CSolidHoopsDoc diagnostics

#ifdef _DEBUG
void CSolidHoopsDoc::AssertValid() const
{
	CHoopsDoc::AssertValid();
}

void CSolidHoopsDoc::Dump(CDumpContext& dc) const
{
	CHoopsDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSolidHoopsDoc serialization

void CSolidHoopsDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}



void CSolidHoopsDoc::SetReadSimpleHsfFlag(bool flag)
{ 
	if( flag )
	{
		reading_mode = TK_Pause;
		m_bReadSimpleHsf = true;
	}
	else
	{
		reading_mode = TK_Normal;
		m_bReadSimpleHsf = flag; 
	}
}
