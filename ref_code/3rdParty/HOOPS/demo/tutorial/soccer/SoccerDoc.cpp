// SoccerDoc.cpp : implementation of CSoccerDoc
//

#include "StdAfx.h"
#include "Resource.h"

#include "Soccer.h"
#include "SoccerDoc.h"

#include "HSoccerModel.h"
#include "HUtility.h"
#include "HUtilityLocaleString.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CSoccerDoc

IMPLEMENT_DYNCREATE(CSoccerDoc, CHoopsDoc)


BEGIN_MESSAGE_MAP(CSoccerDoc, CHoopsDoc)
	//{{AFX_MSG_MAP(CSoccerDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



CSoccerDoc::CSoccerDoc()
{
	m_pHoopsModel = 0;
}


CSoccerDoc::~CSoccerDoc()
{
	if (m_pHoopsModel)
	{
		delete m_pHoopsModel;
		m_pHoopsModel = 0;
	}
}


/*! user has created a new document; we'll create a starting model here */
BOOL CSoccerDoc::OnNewDocument()
{
	if (!CHoopsDoc::OnNewDocument())
		return FALSE;

	// create a new HSoccerModel object for this Document
	m_pHoopsModel = new HSoccerModel();
	m_pHoopsModel->Init();

	if (!m_pHoopsModel)
		return FALSE;

	return TRUE;
}

/*! open an existing document */
BOOL CSoccerDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CHoopsDoc::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// create a new HSoccerModel object for this Document
	m_pHoopsModel = new HSoccerModel();
	m_pHoopsModel->Init();

	if (((HSoccerModel *)m_pHoopsModel)->Read(H_ASCII_TEXT(lpszPathName)) != InputOK)
		return FALSE;

	return TRUE;
}



/*! save the document */
BOOL CSoccerDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CHoopsDoc::OnSaveDocument(lpszPathName);
}



/////////////////////////////////////////////////////////////////////////////
// CSoccerDoc diagnostics

#ifdef _DEBUG
void CSoccerDoc::AssertValid() const
{
	CHoopsDoc::AssertValid();
}

void CSoccerDoc::Dump(CDumpContext& dc) const
{
	CHoopsDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSoccerDoc serialization

void CSoccerDoc::Serialize(CArchive& ar)
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



