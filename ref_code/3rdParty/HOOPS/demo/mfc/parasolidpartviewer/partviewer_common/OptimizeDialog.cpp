// OptimizeDialog.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "OptimizeDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptimizeDialog dialog


COptimizeDialog::COptimizeDialog(CWnd* pParent /*=NULL*/)
	: CDialog(COptimizeDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(COptimizeDialog)
	m_ExpandIncludes = TRUE;
	m_DiscardUserData = TRUE;
	m_CollapseMatrices = TRUE;
	m_MergeShells = TRUE;
	m_Reorganize = 2;
	//}}AFX_DATA_INIT
}


void COptimizeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptimizeDialog)
	DDX_Check(pDX, IDC_OPT_EXPAND_INCLUDES, m_ExpandIncludes);
	DDX_Check(pDX, IDC_OPT_DISCARD_USER_DATA, m_DiscardUserData);
	DDX_Check(pDX, IDC_OPT_COLLAPSE_MATRICES, m_CollapseMatrices);
	DDX_Check(pDX, IDC_OPT_MERGE_SHELLS, m_MergeShells);
	DDX_Radio(pDX, IDC_REORGANIZE_COLOR_SPATIAL, m_Reorganize);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptimizeDialog, CDialog)
	//{{AFX_MSG_MAP(COptimizeDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptimizeDialog message handlers

BOOL COptimizeDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
 	// TODO: Add extra initialization here
	UpdateData(false);

 	
 	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

 

void COptimizeDialog::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}
