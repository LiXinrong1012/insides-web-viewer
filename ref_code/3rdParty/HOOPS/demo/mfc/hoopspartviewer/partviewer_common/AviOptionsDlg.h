#if !defined(AFX_AVIOPTIONSDLG_H__EFE7B65E_ED53_46E4_80F7_901556A2B738__INCLUDED_)
#define AFX_AVIOPTIONSDLG_H__EFE7B65E_ED53_46E4_80F7_901556A2B738__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AviOptionsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAviOptionsDlg dialog

class CAviOptionsDlg : public CDialog
{
// Construction
public:
	CAviOptionsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAviOptionsDlg)
	enum { IDD = IDD_AVIOPTIONS_DIALOG };
	int		m_AVIWidth;
	int		m_AVIHeight;
	int		m_AVIEndTick;
	int		m_AVIStartTick;
	int		m_AVIResolution;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAviOptionsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAviOptionsDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AVIOPTIONSDLG_H__EFE7B65E_ED53_46E4_80F7_901556A2B738__INCLUDED_)
