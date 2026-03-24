// AnalysisDoc.h : interface of the CAnalysisDoc class, derived from CHoopsDoc
// Adds application specific New/Open document member functions 

#if !defined(AFX_CAnalysisDoc_H__FCA603FC_1694_11D2_B736_00805F85736F__INCLUDED_)
#define AFX_CAnalysisDoc_H__FCA603FC_1694_11D2_B736_00805F85736F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// AnalysisDoc.h : header file
//

#include "CHoopsDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CAnalysisDoc document

class CAnalysisDoc : public CHoopsDoc
{
protected:
	CAnalysisDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CAnalysisDoc)

// Attributes
public:


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnalysisDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAnalysisDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CAnalysisDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAnalysisDoc_H__FCA603FC_1694_11D2_B736_00805F85736F__INCLUDED_)


