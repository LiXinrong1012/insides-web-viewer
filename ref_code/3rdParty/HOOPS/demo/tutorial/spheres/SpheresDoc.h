// SpheresDoc.h : interface of the CSpheresDoc class, derived from CHoopsDoc
// Adds application specific New/Open document member functions 

#if !defined(AFX_CSpheresDoc_H__FCA603FC_1694_11D2_B736_00805F85736F__INCLUDED_)
#define AFX_CSpheresDoc_H__FCA603FC_1694_11D2_B736_00805F85736F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// SpheresDoc.h : header file
//

#include "CHoopsDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CSpheresDoc document

class CSpheresDoc : public CHoopsDoc
{
protected:
	CSpheresDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CSpheresDoc)

// Attributes
public:


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpheresDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSpheresDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CSpheresDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSpheresDoc_H__FCA603FC_1694_11D2_B736_00805F85736F__INCLUDED_)


