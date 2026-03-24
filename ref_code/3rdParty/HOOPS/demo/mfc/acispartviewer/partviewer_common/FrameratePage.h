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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/FrameratePage.h,v 1.12 2007-03-19 17:21:01 guido Exp $
//

#if !defined(AFX_FRAMERATEPAGE_H__28514FF1_36CA_11D4_8204_0050042DF1E4__INCLUDED_)
#define AFX_FRAMERATEPAGE_H__28514FF1_36CA_11D4_8204_0050042DF1E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "resource.h"
// FrameratePage.h : header file
//
#include "HConstantFramerate.h"

/////////////////////////////////////////////////////////////////////////////
// CFrameratePage dialog
class HSolidView;
class HConstantFrameRate;


 
class CFrameratePage : public CPropertyPage
{
	DECLARE_DYNCREATE(CFrameratePage)

// Construction
public:
	CFrameratePage(HSolidView *view = 0);
	~CFrameratePage();
	HSolidView *m_pHView;
	HConstantFrameRate *m_pCFR;
	bool m_init;
 
	// Dialog Data
	//{{AFX_DATA(CFrameratePage)
	enum { IDD = IDD_FRAMERATEDIALOG };
	BOOL	m_bconstantframerate;
	BOOL	m_buselod;
	static UINT	m_min_framerate;
	BOOL	m_bthreshold;
	int		m_increase;
	BOOL	m_bboundingboxes;
	static float	m_ScreenExtent;
	static float	m_DistanceWeight;
	static float	m_DivergenceWeight;
	static float	m_WorldVolume;
	static BOOL	m_OrderedDrawing;
	static BOOL	m_TimedUpdate;
	//}}AFX_DATA
	void  ApplyData();

private:
	HConstFRSimpType	**mlist;
	int					mlistLength;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CFrameratePage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
 	void EnableItems();
	void cleanupSimpList();
	// Generated message map functions
	//{{AFX_MSG(CFrameratePage)
 	afx_msg void OnCheckConstantframerate();
	afx_msg void OnCheckUselod();
	afx_msg void OnRadioAllowIncreasealways();
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEditMinimumFramerate();
	afx_msg void OnCheckThreshold();
	afx_msg void OnUseboundingboxes();
	afx_msg void OnRadioAllownoincrease();
	afx_msg void OnRadioAllowincreaseonce();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
 
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FRAMERATEPAGE_H__28514FF1_36CA_11D4_8204_0050042DF1E4__INCLUDED_)
