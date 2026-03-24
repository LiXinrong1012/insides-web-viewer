
#include "stdafx.h"
#include "resource.h"
#include "PDFExportDlg.h"
#include "HIOUtilityPDF.h"


IMPLEMENT_DYNAMIC(CPDFExportDlg, CDialog)
CPDFExportDlg::CPDFExportDlg(wchar_t const * const filename)
	: CDialog(CPDFExportDlg::IDD, NULL)
{
	HOutputHandler * u3d = HDB::GetHIOManager()->GetOutputHandler("u3d");
	m_u3d = (u3d ? true : false);

	HOutputHandler * prc = HDB::GetHIOManager()->GetOutputHandler("prc");
	m_prc = (prc ? true : false);

	HOutputHandler * avi = HDB::GetHIOManager()->GetOutputHandler("avi");
	m_avi = (avi ? true : false);

	if(wcslen(filename) > 0){
		m_bNativeFile = true;
		wchar_t ext[50] = {L""};
		HUtility::FindFileNameExtension(filename, ext, 50);

		if(HDB::GetHIOManager()->GetInputHandler("prc") == HDB::GetHIOManager()->GetInputHandler(ext)){
			m_bAdobe = true;
		}
		else {
			m_bAdobe = false;
		}
	}
	else {
		m_bNativeFile = false;
		m_bAdobe = false;
	}
}

CPDFExportDlg::~CPDFExportDlg()
{
}

bool CPDFExportDlg::came_from_adobe() const {
	return m_bAdobe;
}

void CPDFExportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPDFExportDlg, CDialog)
	ON_BN_CLICKED(IDC_RADIO_2DPDF, OnBnClickedRadio2dpdf)
	ON_BN_CLICKED(IDC_RADIO_3DPDF, OnBnClickedRadio3dpdf)
	ON_BN_CLICKED(IDC_RADIO_PORTFOLIO, CPDFExportDlg::OnBnClickedRadioPortfolio)
	ON_BN_CLICKED(IDC_PDF_BUTTON1, CPDFExportDlg::Button1)
	ON_BN_CLICKED(IDC_PDF_INC_2D, CPDFExportDlg::OnBnClickedPdfInc2d)
	ON_BN_CLICKED(IDC_PDF_INC_3D, CPDFExportDlg::OnBnClickedPdfInc3d)
	ON_BN_CLICKED(IDC_PDF_INC_NATIVE, CPDFExportDlg::OnBnClickedPdfIncNative)
	ON_BN_CLICKED(IDC_PDF_INC_AVI, CPDFExportDlg::OnBnClickedPdfIncAVI)
END_MESSAGE_MAP()

int CPDFExportDlg::DoModal(HPDFOptions *options)
{
	m_pOptions = options;
	int retval = CDialog::DoModal();
	return retval;
}

void CPDFExportDlg::OnBnClickedRadio2dpdf()
{
	m_pOptions->OutputType(H_PDF_OUTPUT_2D);
	m_pOptions->Output2d(true);
	EnablePortfolioSection(false);
}

void CPDFExportDlg::OnBnClickedRadio3dpdf()
{
	m_pOptions->OutputType(H_PDF_OUTPUT_3D);
	m_pOptions->Output3d(true);
	EnablePortfolioSection(false);
}

void CPDFExportDlg::OnBnClickedRadioPortfolio()
{
	m_pOptions->OutputType(H_PDF_OUTPUT_PORTFOLIO);
	m_pOptions->Output3d(false);
	m_pOptions->Output2d(false);
	EnablePortfolioSection(true);
}

BOOL CPDFExportDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CButton * radio_2d  = (CButton*)GetDlgItem(IDC_RADIO_2DPDF);
	radio_2d->SetCheck(true);

	CButton * radio_3d  = (CButton*)GetDlgItem(IDC_RADIO_3DPDF);
	radio_3d->EnableWindow(m_u3d || m_prc);

	EnablePortfolioSection(false);

	UpdateData(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
void CPDFExportDlg::ShowFileOpenDlg(int edit_id)
{
	CString def_ext = _T(".*");
	CString filter = _T("");
	CFileDialog fodlg(TRUE, def_ext, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOREADONLYRETURN,
		filter, NULL);

	TCHAR cur_dir[MVO_BUFFER_SIZE];
	GetCurrentDirectory(MVO_BUFFER_SIZE, cur_dir);
	fodlg.m_ofn.lpstrInitialDir = cur_dir;
	if (fodlg.DoModal() != IDOK)
		return;

	CEdit * editbox = (CEdit*)GetDlgItem(edit_id);
	editbox->SetWindowText(fodlg.GetPathName());
	m_pOptions->EmbeddedFile(edit_id, (__wchar_t const*)H_WCS(fodlg.GetPathName()).encodedText());
}

void CPDFExportDlg::Button1()
{
	ShowFileOpenDlg(IDC_PDF_EDIT1);
}

void CPDFExportDlg::EnablePortfolioSection(bool const enable)
{
	CButton * btn  = (CButton*)GetDlgItem(IDC_PDF_INC_2D);
	btn->EnableWindow(enable);

	btn = (CButton*)GetDlgItem(IDC_PDF_INC_3D);
	btn->EnableWindow(enable && (m_bAdobe || m_u3d || m_prc));
	
	btn = (CButton*)GetDlgItem(IDC_PDF_INC_NATIVE);
	btn->EnableWindow(enable && m_bNativeFile);
	
	btn = (CButton*)GetDlgItem(IDC_PDF_INC_AVI);
	btn->EnableWindow(enable && m_avi);

	btn = (CButton*)GetDlgItem(IDC_PDF_BUTTON1);
	btn->EnableWindow(enable);

	CEdit * edit = (CEdit*)GetDlgItem(IDC_PDF_EDIT1);
	edit->EnableWindow(enable);
}

void CPDFExportDlg::OnBnClickedPdfInc2d()
{
	CButton* btn = (CButton*)GetDlgItem(IDC_PDF_INC_2D);
	m_pOptions->Output2d(btn->GetCheck() == 1);
}

void CPDFExportDlg::OnBnClickedPdfInc3d()
{
	CButton* btn = (CButton*)GetDlgItem(IDC_PDF_INC_3D);
	m_pOptions->Output3d(btn->GetCheck() == 1);
}

void CPDFExportDlg::OnBnClickedPdfIncNative()
{
	CButton* btn = (CButton*)GetDlgItem(IDC_PDF_INC_NATIVE);
	m_pOptions->OutputNative(btn->GetCheck() == 1);
}

void CPDFExportDlg::OnBnClickedPdfIncAVI()
{
	CButton* btn = (CButton*)GetDlgItem(IDC_PDF_INC_AVI);
	m_pOptions->OutputAVI(btn->GetCheck() == 1);
}
