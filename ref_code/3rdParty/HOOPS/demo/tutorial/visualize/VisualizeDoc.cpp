// VisualizeDoc.cpp : implementation of CVisualizeDoc
//

#include "StdAfx.h"
#include "Resource.h"

#include "Visualize.h"
#include "VisualizeDoc.h"

#include "HVisualizeModel.h"
#include "HUtility.h"
#include "HUtilityLocaleString.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CVisualizeDoc

IMPLEMENT_DYNCREATE(CVisualizeDoc, CHoopsDoc)


BEGIN_MESSAGE_MAP(CVisualizeDoc, CHoopsDoc)
	//{{AFX_MSG_MAP(CVisualizeDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



CVisualizeDoc::CVisualizeDoc()
{
	m_pHoopsModel = 0;
}


CVisualizeDoc::~CVisualizeDoc()
{
	if (m_pHoopsModel)
	{
		delete m_pHoopsModel;
		m_pHoopsModel = 0;
	}
}


// user has created a new document
BOOL CVisualizeDoc::OnNewDocument()
{
	if (!CHoopsDoc::OnNewDocument())
		return FALSE;

	// delete the HVisualizeModel object if there is already one
	if(m_pHoopsModel)
	{
		delete m_pHoopsModel;
		m_pHoopsModel = NULL;
	}

	// create a new HVisualizeModel object for this Document
	m_pHoopsModel = new HVisualizeModel();
	m_pHoopsModel->Init();

	if (!m_pHoopsModel)
		return FALSE;

	return TRUE;
}


BOOL CVisualizeDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CHoopsDoc::OnOpenDocument(lpszPathName))
		return FALSE;

	// delete the HVisualizeModel object if there is already one
	if(m_pHoopsModel)
	{
		delete m_pHoopsModel;
		m_pHoopsModel = NULL;
	}
	
	// create a new HVisualizeModel object for this Document
	m_pHoopsModel = new HVisualizeModel();
	m_pHoopsModel->Init();

	if (((HVisualizeModel *)m_pHoopsModel)->Read(H_ASCII_TEXT(lpszPathName)) != InputOK)
		return FALSE;

	return TRUE;
}




BOOL CVisualizeDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CHoopsDoc::OnSaveDocument(lpszPathName);
}



/////////////////////////////////////////////////////////////////////////////
// CVisualizeDoc diagnostics

#ifdef _DEBUG
void CVisualizeDoc::AssertValid() const
{
	CHoopsDoc::AssertValid();
}

void CVisualizeDoc::Dump(CDumpContext& dc) const
{
	CHoopsDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVisualizeDoc serialization

void CVisualizeDoc::Serialize(CArchive& ar)
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



