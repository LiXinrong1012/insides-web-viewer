#if !defined(AFX_CSEGMENTMANIPULATORDLG_H__A0A8D80D_D9C0_4EBF_ABC4_CD386B6F7B76__INCLUDED_)
#define AFX_CSEGMENTMANIPULATORDLG_H__A0A8D80D_D9C0_4EBF_ABC4_CD386B6F7B76__INCLUDED_

#include "HTools.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CSegmentManipulatorDlg.h : header file
//

class HBaseView;
/////////////////////////////////////////////////////////////////////////////
// CSegmentManipulatorDlg dialog

class CSegmentManipulatorDlg : public CDialog
{
// Construction
public:
	CSegmentManipulatorDlg(CWnd* pParent = NULL, HC_KEY startsegment = -1, HBaseView *view = 0);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSegmentManipulatorDlg)
	enum { IDD = IDD_SEGMENTMANIPULATORDLG };
	CString	m_currentsegment;
	CString	m_renderingoptions;
	CString	m_visibility;
 	CString	m_color;
	CString	m_inserttext;
	BOOL	m_aligntoview;
	CString	m_textfont;
	BOOL	m_switchtosubsegment;
	CString	m_filename;
	CString	m_selectability;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSegmentManipulatorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	HBaseView *m_pView;
	void FillEditBoxes();

	HC_KEY m_segmentkey;

	// Generated message map functions
	//{{AFX_MSG(CSegmentManipulatorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSmanRenderingOptionsApply();
	afx_msg void OnSmanVisibilityApply();
 	afx_msg void OnSmanCurrentSegmentApply();
	afx_msg void OnSmanColorApply();
	afx_msg void OnSmanInsertTextApply();
	afx_msg void OnSmanTextFontApply();
	afx_msg void OnSmanLoadFileBrowse();
	afx_msg void OnSmanLoadFileApply();
	afx_msg void OnSmanSelectabilityApply();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSEGMENTMANIPULATORDLG_H__A0A8D80D_D9C0_4EBF_ABC4_CD386B6F7B76__INCLUDED_)
