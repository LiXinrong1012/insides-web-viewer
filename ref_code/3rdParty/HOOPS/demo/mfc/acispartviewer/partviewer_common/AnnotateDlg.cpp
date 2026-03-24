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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/AnnotateDlg.cpp,v 1.7 2006-08-07 20:38:55 stage Exp $
//

// AnnotateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AnnotateDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnnotateDlg dialog


CAnnotateDlg::CAnnotateDlg(CWnd* pParent /*=NULL*/, char *txt)
	: CDialog(CAnnotateDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAnnotateDlg)
	if (txt)
		m_annotation = txt;
	else m_annotation = "";
	//}}AFX_DATA_INIT
}


void CAnnotateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAnnotateDlg)
	DDX_Text(pDX, IDC_EDIT1, m_annotation);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAnnotateDlg, CDialog)
	//{{AFX_MSG_MAP(CAnnotateDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnnotateDlg message handlers
