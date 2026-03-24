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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/LodDialog.cpp,v 1.7 2006-08-07 20:38:55 stage Exp $
//

// LodDialog.cpp : implementation file
//

#include "stdafx.h"
#include "LodDialog.h"
#include "LodSlider.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLodDialog dialog


CLodDialog::CLodDialog(CWnd* pParent /*=NULL*/, HBaseView* view)
	: CDialog(CLodDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLodDialog)
	m_threshold = new LodSlider(this);
	m_threshold_display = 20;
	//}}AFX_DATA_INIT

	m_pHView = view;
}


CLodDialog::~CLodDialog()
{
	if (m_threshold)
		delete m_threshold;
}

void CLodDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLodDialog)
	DDX_Control(pDX, IDC_SLIDER1, *m_threshold);
	DDX_Text(pDX, IDC_EDIT1, m_threshold_display);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLodDialog, CDialog)
	//{{AFX_MSG_MAP(CLodDialog)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLodDialog message handlers

void CLodDialog::OnClose() 
{

	ShowWindow(SW_HIDE);	
//	CDialog::OnClose();

}
