// AnalysisDoc.cpp : implementation of CAnalysisDoc
//

#include "StdAfx.h"
#include "Resource.h"

#include "Analysis.h"
#include "AnalysisDoc.h"
#include "AnalysisView.h"

#include "HAnalysisModel.h"
#include "HUtility.h"
#include "HUtilityLocaleString.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CAnalysisDoc

IMPLEMENT_DYNCREATE(CAnalysisDoc, CHoopsDoc)


BEGIN_MESSAGE_MAP(CAnalysisDoc, CHoopsDoc)
	//{{AFX_MSG_MAP(CAnalysisDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



CAnalysisDoc::CAnalysisDoc()
{
	m_pHoopsModel = 0;
}


CAnalysisDoc::~CAnalysisDoc()
{
	if (m_pHoopsModel)
	{
		delete m_pHoopsModel;
		m_pHoopsModel = 0;
	}
}


// user has created a new document
BOOL CAnalysisDoc::OnNewDocument()
{
	if (!CHoopsDoc::OnNewDocument())
		return FALSE;


	// delete the HAnalysisModel object if there is already one
	if(m_pHoopsModel)
	{
		delete m_pHoopsModel;
		m_pHoopsModel = NULL;
	}

	// create a new HAnalysisModel object for this Document
	m_pHoopsModel = new HAnalysisModel();
	m_pHoopsModel->Init();

	if (!m_pHoopsModel)
		return FALSE;

	return TRUE;
}


BOOL CAnalysisDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CHoopsDoc::OnOpenDocument(lpszPathName))
		return FALSE;


	// delete the HAnalysisModel object if there is already one
	if(m_pHoopsModel)
	{
		delete m_pHoopsModel;
		m_pHoopsModel = NULL;
	}
	
	// create a new HAnalysisModel object for this Document
	m_pHoopsModel = new HAnalysisModel();
	m_pHoopsModel->Init();

	if (((HAnalysisModel *)m_pHoopsModel)->Read(H_ASCII_TEXT(lpszPathName)) != InputOK)
		return FALSE;

	return TRUE;
}




BOOL CAnalysisDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CHoopsDoc::OnSaveDocument(lpszPathName);
}



/////////////////////////////////////////////////////////////////////////////
// CAnalysisDoc diagnostics

#ifdef _DEBUG
void CAnalysisDoc::AssertValid() const
{
	CHoopsDoc::AssertValid();
}

void CAnalysisDoc::Dump(CDumpContext& dc) const
{
	CHoopsDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAnalysisDoc serialization

void CAnalysisDoc::Serialize(CArchive& ar)
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



