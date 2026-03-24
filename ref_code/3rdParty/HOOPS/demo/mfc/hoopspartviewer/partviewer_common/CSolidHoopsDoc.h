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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/CSolidHoopsDoc.h,v 1.27 2010-06-01 19:58:04 reuben Exp $
//

// CSolidHoopsDoc.h : interface of the CSolidHoopsDoc class, derived from CHoopsDoc
// Adds application specific New/Open document member functions 

#if !defined(AFX_CSOLIDHOOPSDOC_H__FCA603FC_1694_11D2_B736_00805F85736F__INCLUDED_)
#define AFX_CSOLIDHOOPSDOC_H__FCA603FC_1694_11D2_B736_00805F85736F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif 
#include "CHoopsDoc.h"
#include "HStream.h"
#include "FileLoadProgressDlg.h"

class CSolidHoopsDoc : public CHoopsDoc
{
protected:
	CSolidHoopsDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CSolidHoopsDoc)

	bool m_bReadSimpleHsf;
	bool m_bDeferFileReadForView;
	CFileLoadProgressDlg *m_ProgressDlg;

// Attributes
public:

	bool IsFileReadDeferedForView(){ return m_bDeferFileReadForView; };
 	bool m_bIsPsf;
	bool dictionary_loaded;
	bool m_bStreamInProgress;
	TK_Status reading_mode;

	TCHAR filename[MVO_BUFFER_SIZE];

// Operations
public:

	void SetReadSimpleHsfFlag(bool flag);
	bool GetReadSimpleHsfFlag(){ return m_bReadSimpleHsf; }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSolidHoopsDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSolidHoopsDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CSolidHoopsDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSOLIDHOOPSDOC_H__FCA603FC_1694_11D2_B736_00805F85736F__INCLUDED_)
