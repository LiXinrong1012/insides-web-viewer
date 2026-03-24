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
// $Header: /files/homes/master/cvs/hoops_master/parasolidpartviewer/PSTopolBrowserDlg.h,v 1.5 2006-08-07 20:38:55 stage Exp $
//

#if !defined(AFX_PSTOPOLBROWSERDLG_H__0F52A9F2_CCBE_11D3_818F_0050042DF1E4__INCLUDED_)
#define AFX_PSTOPOLBROWSERDLG_H__0F52A9F2_CCBE_11D3_818F_0050042DF1E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TopolBrowserDlg.h : header file
//
#include "resource.h"
#include "HSolidView.h"
#include "HSolidModel.h"
#include "TopolBrowserDlg.h"
  

 

class CPSTopolBrowserDlg : public CTopolBrowserDlg
{
// Construction
public:
	CPSTopolBrowserDlg(CWnd* pParent = NULL,HSolidView * View = 0) : CTopolBrowserDlg(pParent,View) {}   // standard constructor
 	bool HighlightSelection(); 
 protected:

 	PK_ATTDEF_t m_name_attdef;
	HTREEITEM InsertItemInTree(PK_ENTITY_t entity,const char* basetext,HTREEITEM position);
	void UpdateInfoWindow(PK_ENTITY_t entity);
	void  FillItems(PK_ENTITY_t entity,HTREEITEM item);
 
 

 	BOOL OnInitDialog();
	virtual bool BuildTopolTree();
 	void OnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult);
 	void OnAnnotate();
 	void OnFacevisibility();
  
};




  




//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOPOLBROWSERDLG_H__0F52A9F2_CCBE_11D3_818F_0050042DF1E4__INCLUDED_)
