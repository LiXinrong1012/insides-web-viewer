// VisualizeDoc.h : interface of the CVisualizeDoc class, derived from CHoopsDoc
// Adds application specific New/Open document member functions 

#if !defined(AFX_CVisualizeDoc_H__FCA603FC_1694_11D2_B736_00805F85736F__INCLUDED_)
#define AFX_CVisualizeDoc_H__FCA603FC_1694_11D2_B736_00805F85736F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// VisualizeDoc.h : header file
//

#include "CHoopsDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CVisualizeDoc document

class CVisualizeDoc : public CHoopsDoc
{
protected:
	CVisualizeDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CVisualizeDoc)

// Attributes
public:


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVisualizeDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CVisualizeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CVisualizeDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CVisualizeDoc_H__FCA603FC_1694_11D2_B736_00805F85736F__INCLUDED_)


