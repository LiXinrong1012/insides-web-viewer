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
// $Header: /files/homes/master/cvs/hoops_master/hoops_mfc/source/CHoopsDoc.cpp,v 1.9 2009-09-17 19:00:19 evan Exp $
//

// CHoopsDoc.cpp : implementation of the CHoopsDoc class
// 

#include "stdafx.h"
#include "CHoopsApp.h"

#include "CHoopsDoc.h"
#include "HBaseModel.h"


//extern CQuickApp theApp;	// the one and only application object

/////////////////////////////////////////////////////////////////////////////
// CHoopsDoc

IMPLEMENT_DYNCREATE(CHoopsDoc, CDocument)

BEGIN_MESSAGE_MAP(CHoopsDoc, CDocument)
	//{{AFX_MSG_MAP(CHoopsDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHoopsDoc construction/destruction

CHoopsDoc::CHoopsDoc()
{
	m_pHoopsModel = NULL;	// initialize the Hoops model object ptr
	m_include_key = 0L;
}


CHoopsDoc::~CHoopsDoc()
{
}


/////////////////////////////////////////////////////////////////////////////
// CHoopsDoc serialization

void CHoopsDoc::Serialize(CArchive& ar)
{
}

/////////////////////////////////////////////////////////////////////////////
// CHoopsDoc diagnostics

#ifdef _DEBUG
void CHoopsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHoopsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHoopsDoc commands

BOOL CHoopsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}


#ifdef _UNICODE
BOOL CHoopsDoc::OnOpenDocument(wchar_t const * lpszPathName) 
{
	if (!CDocument::OnOpenDocument((LPCTSTR)lpszPathName))
		return FALSE;
	
	return TRUE;
}
#ifdef H_USHORT_OVERLOAD
BOOL CHoopsDoc::OnOpenDocument(unsigned short const * lpszPathName) 
{
	if (!CDocument::OnOpenDocument((LPCTSTR)lpszPathName))
		return FALSE;
	
	return TRUE;
}
#endif
#else
BOOL CHoopsDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	return TRUE;
}
#endif
