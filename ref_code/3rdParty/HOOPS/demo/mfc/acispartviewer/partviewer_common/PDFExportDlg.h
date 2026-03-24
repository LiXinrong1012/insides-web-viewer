
#ifndef _PDFEXPORTDLG_H
#include "resource.h"
#include "HIOUtilityHOOPS.h"
// CPDFExportDlg dialog

class CPDFExportDlg : public CDialog
{
	DECLARE_DYNAMIC(CPDFExportDlg)
	bool m_u3d;
	bool m_prc;
	bool m_avi;
	bool m_bNativeFile;
	bool m_bAdobe;

public:
	CPDFExportDlg(wchar_t const * const);   // standard constructor
	virtual ~CPDFExportDlg();
	bool came_from_adobe() const;

// Dialog Data
	enum { IDD = IDD_DIALOG_PDF_EXPORT };
	enum ExportFormat
	{
		e2D,
		e3D
	};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	HPDFOptions * m_pOptions;
	void EnablePortfolioSection(bool const enable);
	void ShowFileOpenDlg(int edit_id);

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadio2dpdf();
	afx_msg void OnBnClickedRadio3dpdf();
	afx_msg int DoModal(HPDFOptions*);
	afx_msg void OnBnClickedRadioPortfolio();
	afx_msg void Button1();
	afx_msg void OnBnClickedPdfInc2d();
	afx_msg void OnBnClickedPdfInc3d();
	afx_msg void OnBnClickedPdfIncNative();
	afx_msg void OnBnClickedPdfIncAVI();

};

#define _PDFEXPORTDLG_H
#endif
