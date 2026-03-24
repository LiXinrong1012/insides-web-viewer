// SpheresDoc.cpp : implementation of CSpheresDoc
//

#include "StdAfx.h"
#include "Resource.h"

#include "Spheres.h"
#include "SpheresDoc.h"

#include "HSpheresModel.h"
#include "HUtility.h"
#include "HUtilityLocaleString.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CSpheresDoc

IMPLEMENT_DYNCREATE(CSpheresDoc, CHoopsDoc)


BEGIN_MESSAGE_MAP(CSpheresDoc, CHoopsDoc)
	//{{AFX_MSG_MAP(CSpheresDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



CSpheresDoc::CSpheresDoc()
{
}


CSpheresDoc::~CSpheresDoc()
{
	H_SAFE_DELETE(m_pHoopsModel);
}


// user has created a new document
BOOL CSpheresDoc::OnNewDocument()
{
	if (!CHoopsDoc::OnNewDocument())
		return FALSE;

	// create a new HSpheresModel object for this Document
	m_pHoopsModel = new HSpheresModel();
	m_pHoopsModel->Init();

	if (!m_pHoopsModel)
		return FALSE;

	return TRUE;
}


BOOL CSpheresDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CHoopsDoc::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// create a new HSpheresModel object for this Document
	m_pHoopsModel = new HSpheresModel();
	m_pHoopsModel->Init();

	if (((HSpheresModel *)m_pHoopsModel)->Read(H_ASCII_TEXT(lpszPathName)) != InputOK)
		return FALSE;

	return TRUE;
}




BOOL CSpheresDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CHoopsDoc::OnSaveDocument(lpszPathName);
}



/////////////////////////////////////////////////////////////////////////////
// CSpheresDoc diagnostics

#ifdef _DEBUG
void CSpheresDoc::AssertValid() const
{
	CHoopsDoc::AssertValid();
}

void CSpheresDoc::Dump(CDumpContext& dc) const
{
	CHoopsDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSpheresDoc serialization

void CSpheresDoc::Serialize(CArchive& ar)
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



