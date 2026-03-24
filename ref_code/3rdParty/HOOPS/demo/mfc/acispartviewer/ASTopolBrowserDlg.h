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

#if !defined(AFX_ASTOPOLBROWSERDLG_H__RAJESH_B__200010503__1018)
#define AFX_ASTOPOLBROWSERDLG_H__RAJESH_B__200010503__1018

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// ASTopolBrowserDlg.h : header file

#include "TopolBrowserDlg.h"

class asm_model;

class CASTopolBrowserDlg : public CTopolBrowserDlg
{

public:
	CASTopolBrowserDlg(CWnd* pParent = NULL, HSolidView * View = 0) : CTopolBrowserDlg(pParent,View) {}   // standard constructor
 	virtual bool HighlightSelection(); 
	virtual void ShowSelectedItems();

protected:

 	ATTRIB* m_name_attdef;

	HTREEITEM InsertItemInTree(ENTITY* entity, const char* basetext, HTREEITEM position);
	void UpdateInfoWindow( ENTITY* entity );
	void FillItems( ENTITY* entity, HTREEITEM item );

	void FillItems( asm_model* p_asm_model, HTREEITEM item);
	void InsertComponents(asm_model *pAsmModel, HTREEITEM parentNode);
 
 	BOOL OnInitDialog();
 	void OnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult);
 	void OnAnnotate();
 	void OnFacevisibility();
	virtual bool BuildTopolTree();

private:

	bool get_model_refs_path_for_item(HTREEITEM item, entity_handle_list& model_refs_path);

  
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ASTOPOLBROWSERDLG_H__RAJESH_B__200010503__1018)
