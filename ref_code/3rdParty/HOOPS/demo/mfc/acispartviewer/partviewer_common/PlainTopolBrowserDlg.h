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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/PlainTopolBrowserDlg.h,v 1.10 2006-08-07 20:38:55 stage Exp $
//

#if !defined(AFX_PLAINTOPOLBROWSERDLG_H__0F52A9F2_CCBE_11D3_818F_0050042DF1E4__INCLUDED_)
#define AFX_PLAINTOPOLBROWSERDLG_H__0F52A9F2_CCBE_11D3_818F_0050042DF1E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "TopolBrowserDlg.h"

class HSolidModel;
class CTopolBrowserDlg;

 
/////////////////////////////////////////////////////////////////////////////
// CTopolBrowserDlg dialog

class CPlainTopolBrowserDlg : public CTopolBrowserDlg
{
// Construction
public:
	CPlainTopolBrowserDlg(CWnd* pParent = NULL,HSolidView * View = 0) : CTopolBrowserDlg(pParent,View) {}   // standard constructor
	bool HighlightSelection();
   
  
// Implementation
protected:

	HSolidModel *model; 

	virtual bool BuildTopolTree();
	HTREEITEM InsertItemInTree(long entity,const char* basetext,HTREEITEM position);
	void UpdateInfoWindow(long entity);
	void  FillItems(long entity,HTREEITEM item);
  
 	BOOL OnInitDialog();

 	void OnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult);
 	void OnAnnotate();
 	void OnFacevisibility();

	// Generated message map functions
	//{{AFX_MSG(CPlainTopolBrowserDlg)
	afx_msg void OnItemexpandingTree1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

 
 
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOPOLBROWSERDLG_H__0F52A9F2_CCBE_11D3_818F_0050042DF1E4__INCLUDED_)

