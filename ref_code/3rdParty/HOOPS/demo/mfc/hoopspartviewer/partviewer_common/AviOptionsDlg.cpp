// AviOptionsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "AviOptionsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAviOptionsDlg dialog


CAviOptionsDlg::CAviOptionsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAviOptionsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAviOptionsDlg)
	m_AVIWidth = 320;
	m_AVIHeight = 200;
	m_AVIEndTick = 0;
	m_AVIStartTick = 0;
	m_AVIResolution = 100;
	//}}AFX_DATA_INIT
}


void CAviOptionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAviOptionsDlg)
	DDX_Text(pDX, IDC_AVI_WIDTH, m_AVIWidth);
	DDX_Text(pDX, IDC_AVI_HEIGHT, m_AVIHeight);
	DDX_Text(pDX, IDC_AVI_ENDTICK, m_AVIEndTick);
	DDX_Text(pDX, IDC_AVI_STARTTICK, m_AVIStartTick);
	DDX_Text(pDX, IDC_AVI_RESOLUTION, m_AVIResolution);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAviOptionsDlg, CDialog)
	//{{AFX_MSG_MAP(CAviOptionsDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAviOptionsDlg message handlers
