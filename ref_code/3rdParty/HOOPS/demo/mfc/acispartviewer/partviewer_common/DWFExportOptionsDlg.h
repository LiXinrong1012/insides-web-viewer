#if !defined(DWFEXPORTOPTIONSDLG__INCLUDED_RAJESH_B__20060424__1346__)
#define DWFEXPORTOPTIONSDLG__INCLUDED_RAJESH_B__20060424__1346__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// forward declarations
class HOutputHandlerOptions;


// CDWFExportOptionsDlg dialog

class CDWFExportOptionsDlg : public CDialog
{
	DECLARE_DYNAMIC(CDWFExportOptionsDlg)

	enum ExportFormat
	{
		e2D,
		e3D
	};


public:
	CDWFExportOptionsDlg(HOutputHandlerOptions* pOuputHandlerOptions, CWnd* pParent = NULL);   // standard constructor
	virtual ~CDWFExportOptionsDlg();

// Dialog Data
	enum { IDD = IDD_DWF_EXPORT_OPTIONS };

	int m_nExportFormat;
	float m_fPageWidth;
	float m_fPageHeight;
	float m_fResolution;

protected:

	void set_export_format(ExportFormat eNewFormat);
	void switch_2D_options(bool enable);

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	HOutputHandlerOptions * m_pOptions;

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnBnClickedRadioExportFormat2D();
	afx_msg void OnBnClickedRadioExportFormat3D();
};


#endif // DWFEXPORTOPTIONSDLG__INCLUDED_RAJESH_B__20060424__1346__

