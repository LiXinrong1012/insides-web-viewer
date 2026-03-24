// DWFExportOptionsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "HIOManager.h"
#include "DWFExportOptionsDlg.h"
#include "HIOUtilityDwfExport.h"


// CDWFExportOptionsDlg dialog

IMPLEMENT_DYNAMIC(CDWFExportOptionsDlg, CDialog)
CDWFExportOptionsDlg::CDWFExportOptionsDlg(HOutputHandlerOptions* pOuputHandlerOptions,
										   CWnd* pParent /*=NULL*/)
	                 : CDialog(CDWFExportOptionsDlg::IDD, pParent)
{
	m_pOptions = pOuputHandlerOptions;

	m_nExportFormat = -1;
	m_fPageWidth	= -1;
	m_fPageHeight	= -1;
	m_fResolution		= -1;
}

CDWFExportOptionsDlg::~CDWFExportOptionsDlg()
{
}

void CDWFExportOptionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDWFExportOptionsDlg)
	DDX_Radio(pDX, IDC_RADIO_EXPORT_FORMAT, m_nExportFormat);
	DDX_Text(pDX, IDC_EDIT_WINDOW_WIDTH, m_fPageWidth);
	DDV_MinMaxFloat(pDX, m_fPageWidth, 0.f, 100.f);
	DDX_Text(pDX, IDC_EDIT_WINDOW_HEIGHT, m_fPageHeight);
	DDV_MinMaxFloat(pDX, m_fPageHeight, 0.f, 100.f);
	DDX_Text(pDX, IDC_EDIT_RESOLUTION, m_fResolution);
	DDV_MinMaxFloat(pDX, m_fResolution, 0.f, 1000.f);
	//}}AFX_DATA_MAP

}


BEGIN_MESSAGE_MAP(CDWFExportOptionsDlg, CDialog)
	ON_BN_CLICKED(IDC_RADIO_EXPORT_FORMAT, OnBnClickedRadioExportFormat2D)
	ON_BN_CLICKED(IDC_RADIO_FORMAT_3D, OnBnClickedRadioExportFormat3D)
END_MESSAGE_MAP()


// CDWFExportOptionsDlg message handlers

BOOL CDWFExportOptionsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_fPageWidth	= 8.5f;
	m_fPageHeight	= 11.0f;
	m_fResolution	= 75.0f;

	set_export_format(e3D);

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDWFExportOptionsDlg::set_export_format(ExportFormat eNewFormat)
{
	if( m_nExportFormat == eNewFormat )
		return;

	m_nExportFormat = eNewFormat;

	if( eNewFormat == e3D )
	{
		// enable 3D options
		
		// disable 2D options 
		switch_2D_options(false);
	}
	else if( eNewFormat == e2D )
	{
		// enable 2D options
		switch_2D_options(true);

		// disable 3D options
	}
	else
		// this mode does not exist
		assert(0);
}

void CDWFExportOptionsDlg::switch_2D_options(bool enable)
{
	CWnd* p_paper_width  = GetDlgItem(IDC_EDIT_WINDOW_WIDTH);
	if(p_paper_width)
		p_paper_width->EnableWindow(enable);

	CWnd* p_paper_height = GetDlgItem(IDC_EDIT_WINDOW_HEIGHT);
	if(p_paper_height)
		p_paper_height->EnableWindow(enable);

	CWnd* p_res	= GetDlgItem(IDC_EDIT_RESOLUTION);
	if(p_res)
		p_res->EnableWindow(enable);
}


void CDWFExportOptionsDlg::OnBnClickedRadioExportFormat2D()
{
	set_export_format(e2D);
}

void CDWFExportOptionsDlg::OnBnClickedRadioExportFormat3D()
{
	set_export_format(e3D);
}


void CDWFExportOptionsDlg::OnOK() 
{
	UpdateData(TRUE);

	if(m_pOptions)
	{
		m_pOptions->m_b3dOutput = (m_nExportFormat == e3D) ? true : false;
		//m_pOptions->m_Window_Width = m_fPageWidth;
		//m_pOptions->m_Window_Height= m_fPageHeight;
		//m_pOptions->m_Image_Dpi = m_fResolution;
	}

	CDialog::OnOK();
}

