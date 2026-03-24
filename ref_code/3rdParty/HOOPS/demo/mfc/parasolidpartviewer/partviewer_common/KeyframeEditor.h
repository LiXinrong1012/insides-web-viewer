#if !defined(AFX_KEYFRAMEEDITOR_H__E93555A6_4BE2_4174_8058_6BA3F3315F26__INCLUDED_)
#define AFX_KEYFRAMEEDITOR_H__E93555A6_4BE2_4174_8058_6BA3F3315F26__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// KeyframeEditor.h : header file
//
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// CKeyframeEditor dialog

class HBaseView;
class HBhvAnimation;
class CSolidHoopsView;


class CDlgToolBar : public CToolBar 
{   
 
protected:                
	// Generated message map functions
	//{{AFX_MSG(CDlgToolBar)
	afx_msg LRESULT OnIdleUpdateCmdUI(WPARAM wParam, LPARAM);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};        

class CKeyframeEditor : public CDialog, public HAnimationListener
{
// Construction
public:
	CKeyframeEditor(CWnd* pParent = NULL, HBaseView *view = 0);   // standard constructor
	void UpdateButtonStates();
	void UpdateBhvState(bool inv);
	HBhvAnimation *	GetActiveAnimation(); 
	void PlayToTick();
	bool GetRecordMode() { return m_bRecordMode; }
	int KeyframeEditorExistsQuery(bool &res);
	int KeyframeAddedEvent();

// Dialog Data
	//{{AFX_DATA(CKeyframeEditor)
	enum { IDD = IDD_KEYFRAME };
	CScrollBar	m_VerticalScrollbar;
	CScrollBar	m_HorizontalScrollbar;
	int		m_cameratype;
	BOOL	m_update_view;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKeyframeEditor)
	public:
 	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:


	int m_activeKeyframe;
 	void DrawBox(CDC *dc, int xpos, int ypos, int r, int g, int b);
	void DrawBox(CDC *dc, int xpos, int ypos, int length, int r, int g, int b);

 	void DrawNewBoxes(CDC *dc);

//	void DrawOuterBox(CDC *dc, int xpos, int length);
	void DrawOuterBox(CDC *dc, int xpos1, int xpos2, int ypos1, int ypos2);
 

	void GetScrollbarPosition(int &pos, int &vpos);
	int CalculateKeyframeFromMousePosition(int mousex); 
	int CalculateYFromMousePosition(int mousey);
	bool IsInTextField(int posx, int posy);
	bool IsInEditor(int posx, int posy);
	bool IsAboveEditor(int posx, int posy);
	void AdjustKeyframe(int x, int y, int delta, bool doall, bool relative);

	CDlgToolBar m_wndToolBar;


	HBaseView *m_pHView;
	CSolidHoopsView *m_pSolidHoopsView;
	int m_framerange[2];
	int m_anirange[2];
	int m_framerangesav[2];
	int m_anirangesav[2];
	bool m_lbuttondown;
	bool m_bRecordMode;
	HBhvAnimation *m_animationlist[256];
	int m_animationnum;
	int m_boxx;
	bool m_bDragMode;
	int m_LatestDrag;
	int m_FirstDragX;
	int m_FirstDragY;

	void InvalidateBoxes();


	// Generated message map functions
	//{{AFX_MSG(CKeyframeEditor)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnActivate( UINT nState, CWnd* pWndOther, BOOL bMinimized );
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDeleteAnimations();
	afx_msg void OnDeleteKeyframes();
	afx_msg void OnDuplicateLast();
	afx_msg void OnDuplicateNext();
	afx_msg void OnButtonCopy();
	afx_msg void OnButtonPaste();
 	afx_msg void OnMakeCameraKeyframe();
	afx_msg void OnMakeLinear();
	afx_msg void OnMakeFollowPath();
	afx_msg void OnMakeSpline();
	afx_msg void OnManipulator();
	afx_msg void OnMakeAttswitchKfr();
	afx_msg void OnActivateSelection();
	afx_msg void OnAxisRotKeyframe();
	afx_msg void OnBhvReload();
	afx_msg void OnBhvWalk();
	afx_msg void OnSelchangeZoomcombo();
	afx_msg void OnSelchangeTextzoom();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnBhvEditxml();
 	afx_msg void OnTesterid();
	afx_msg void OnBhvDragmode();
	afx_msg void OnUpdateBhvDragmode(CCmdUI* pCmdUI);
	afx_msg void OnBhvCameraPosMode();
	afx_msg void OnUpdateBhvCameraPosMode(CCmdUI* pCmdUI);
	afx_msg void OnBhvCameraTargetMode();
	afx_msg void OnUpdateBhvCameraTargetMode(CCmdUI* pCmdUI);
	afx_msg void OnBhvUpdateView();
	afx_msg void OnUpdateBhvUpdateView(CCmdUI* pCmdUI);
	afx_msg void OnBhvMagnify1x();
	afx_msg void OnUpdateBhvMagnify1x(CCmdUI* pCmdUI);
	afx_msg void OnBhvMagnify2x();
	afx_msg void OnUpdateBhvMagnify2x(CCmdUI* pCmdUI);
	afx_msg void OnBhvMagnify4x();
	afx_msg void OnUpdateBhvMagnify4x(CCmdUI* pCmdUI);
	afx_msg void OnBhvMagnify8x();
	afx_msg void OnUpdateBhvMagnify8x(CCmdUI* pCmdUI);
	afx_msg BOOL OnToolTipText(UINT nID, NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBhvAutomaticRecord();
	afx_msg void OnBhvRecordCamera();
	afx_msg void OnUpdateBhvAutomaticRecord(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBhvRecordCamera(CCmdUI* pCmdUI);
	afx_msg void OnBhvDrawCurve();
	afx_msg void OnBhvDrawCurveRot();
	afx_msg void OnMakeCollision();
	afx_msg void OnExportAVI();
	afx_msg void OnCancel();
	//}}AFX_MSG
#ifdef _M_AMD64
	afx_msg void OnTimer(UINT_PTR nIDEvent);
#else
	afx_msg void OnTimer(UINT nIDEvent);
#endif
	DECLARE_MESSAGE_MAP()

		
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KEYFRAMEEDITOR_H__E93555A6_4BE2_4174_8058_6BA3F3315F26__INCLUDED_)
