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
// $Header: /files/homes/master/cvs/hoops_master/mfc_simple/simpleDoc.h,v 1.3 2006-08-07 20:38:55 stage Exp $
//

// simpleDoc.h : interface of the CSimpleDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIMPLEDOC_H__F258079F_CACF_11D3_ABF4_0050046769B1__INCLUDED_)
#define AFX_SIMPLEDOC_H__F258079F_CACF_11D3_ABF4_0050046769B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSimpleDoc : public CDocument
{
protected: // create from serialization only
	CSimpleDoc();
	DECLARE_DYNCREATE(CSimpleDoc)

// Attributes
public:
	const char*		GetModelSegment( void ) { return (const char*)m_sModelSegment; }

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimpleDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSimpleDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSimpleDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	char	m_sModelSegment[1024];

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMPLEDOC_H__F258079F_CACF_11D3_ABF4_0050046769B1__INCLUDED_)
