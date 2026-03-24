#if !defined(AFX_OPTIMIZEDIALOG_H__3D4494EB_68B6_423C_A70D_32D8576A4F04__INCLUDED_)
#define AFX_OPTIMIZEDIALOG_H__3D4494EB_68B6_423C_A70D_32D8576A4F04__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptimizeDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COptimizeDialog dialog

class COptimizeDialog : public CDialog
{
// Construction
public:
	COptimizeDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COptimizeDialog)
	enum { IDD = IDD_OPTIMIZE_SEGMENT_DIALOG };
	BOOL	m_ExpandIncludes;
	BOOL	m_DiscardUserData;
	BOOL	m_CollapseMatrices;
	BOOL	m_MergeShells;
	int		m_Reorganize;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptimizeDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COptimizeDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIMIZEDIALOG_H__3D4494EB_68B6_423C_A70D_32D8576A4F04__INCLUDED_)
