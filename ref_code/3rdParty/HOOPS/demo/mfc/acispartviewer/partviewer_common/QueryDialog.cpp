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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/QueryDialog.cpp,v 1.6 2006-08-07 20:38:55 stage Exp $
//

// CQueryDialog.cpp : implementation of the CQueryDialog class
//

#include "stdafx.h"
#include "QueryDialog.h"
 
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQueryDialog dialog


CQueryDialog::CQueryDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CQueryDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CQueryDialog)
	m_QueryTextValue = _T("");
	//}}AFX_DATA_INIT
}

void CQueryDialog::SetText(char* querytext)
{
	m_QueryTextValue = querytext;
	UpdateData(FALSE);
}

void CQueryDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQueryDialog)
	DDX_Text(pDX, IDC_QUERY_TEXT, m_QueryTextValue);
	DDV_MaxChars(pDX, m_QueryTextValue, 2048);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CQueryDialog, CDialog)
	//{{AFX_MSG_MAP(CQueryDialog)
	ON_WM_CLOSE()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQueryDialog message handlers


BOOL CQueryDialog::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::OnCommand(wParam, lParam);
}

void CQueryDialog::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	ShowWindow(SW_HIDE);	
//	CDialog::OnClose();
}

BOOL CQueryDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
//	Create(IDD_QUERYDIALOG);
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

