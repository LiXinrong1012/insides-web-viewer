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
// $Header: /files/homes/master/cvs/hoops_master/mfc_simple/simpleDoc.cpp,v 1.3 2006-08-07 20:38:55 stage Exp $
//

// simpleDoc.cpp : implementation of the CSimpleDoc class
//

#include "stdafx.h"
#include "simple.h"

#include "simpleDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CSimpleApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSimpleDoc

IMPLEMENT_DYNCREATE(CSimpleDoc, CDocument)

BEGIN_MESSAGE_MAP(CSimpleDoc, CDocument)
	//{{AFX_MSG_MAP(CSimpleDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimpleDoc construction/destruction

CSimpleDoc::CSimpleDoc()
{
	// TODO: add one-time construction code here

}

CSimpleDoc::~CSimpleDoc()
{
}

BOOL CSimpleDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

    int count = theApp.IncrementCounter();

    sprintf (m_sModelSegment, "/include library/model%d", count);

    HC_Open_Segment (m_sModelSegment);
		HC_Insert_Text(0.0,0.0,0.0, "This is a simple MFC based application \nwhich only uses HOOPS/3dGS");
		HC_Set_Text_Alignment("*^|");
	HC_Close_Segment();

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

BOOL CSimpleDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	char extension[1024]; 
	unsigned int i;

	extension[0] = '\0';
	HC_Parse_String(lpszPathName, ".", -1, extension);

	// make it lower case
	for(i = 0; i < strlen(extension); i++)
     	extension[i] = (char) tolower(extension[i]);

	if(!strcmp(extension, "hmf"))
	{
		int count = theApp.IncrementCounter();
		sprintf (m_sModelSegment, "/include library/model%d", count);

		HC_Open_Segment (m_sModelSegment);
			HC_Read_Metafile(lpszPathName, ".", "follow cross-references");
		HC_Close_Segment();

		return TRUE;
	}
	else
	{
		// 3dGS only supports reading HMFs
		return FALSE;
	}
}




/////////////////////////////////////////////////////////////////////////////
// CSimpleDoc serialization

void CSimpleDoc::Serialize(CArchive& ar)
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

/////////////////////////////////////////////////////////////////////////////
// CSimpleDoc diagnostics

#ifdef _DEBUG
void CSimpleDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSimpleDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSimpleDoc commands
