//
// Copyright (c) 2002 by Tech Soft 3D, LLC.
// The information contained herein is confidential and proprietary to
// Tech Soft 3D, LLC., and considered a trade secret as defined under
// civil and criminal statutes.  Tech Soft 3D shall pursue its civil
// and criminal remedies in the event of unauthorized use or misappropriation
// of its trade secrets.  Use of this information by anyone other than
// authorized employees of Tech Soft 3D, LLC. is granted only under a
// written non-disclosure agreement, expressly prescribing the scope and
// manner of such use.
//
// $Header: /files/homes/master/cvs/hoops_master/Hoops3dStreamCtrl/source/AppearanceDlg.h,v 1.7 2006-08-07 20:38:46 stage Exp $
//

#ifndef __APPEARANCEDLG_H_
#define __APPEARANCEDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>
#define BOOL2bool(TRUE_Or_FALSE)	\
	(( TRUE_Or_FALSE == TRUE ) ? true : false)

#define bool2BOOL(true_or_false)	\
	(( true_or_false == true ) ? TRUE : FALSE )

/////////////////////////////////////////////////////////////////////////////
// CAppearanceDlg
class CAppearanceDlg : 
	public CAxDialogImpl<CAppearanceDlg>
{
public:
	CAppearanceDlg()
	{
	     m_default_bottom_color = RGB(0,0,0);
	     m_default_top_color = RGB(1,1,1);
	     m_default_selection_color = RGB(1,1,0);
	     m_bDefaultForceSoftware = false;	    
	}

	~CAppearanceDlg()
	{
	}

	enum { IDD = IDD_APPEARANCEDLG };

BEGIN_MSG_MAP(CAppearanceDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	COMMAND_HANDLER(IDC_BUTTON_COLOR_BACKGROUND_BOTTOM, BN_CLICKED, OnClickedButton_color_background_bottom)
	COMMAND_HANDLER(IDC_BUTTON_COLOR_BACKGROUND_TOP, BN_CLICKED, OnClickedButton_color_background_top)
	COMMAND_HANDLER(IDC_BUTTON_COLOR_SELECTION, BN_CLICKED, OnClickedButton_color_selection)
	COMMAND_HANDLER(IDC_FORCE_SOFTWARE, BN_CLICKED, OnClickedButton_force_software)
	COMMAND_HANDLER(IDC_RESET, BN_CLICKED, OnClickedButton_reset)
 	MESSAGE_HANDLER(WM_DRAWITEM, OnDrawItem)
 	COMMAND_HANDLER(IDOK, BN_CLICKED, OnOK)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{

		HWND button = GetDlgItem(IDC_FORCE_SOFTWARE);
		SendMessage(button, BM_SETCHECK,m_bForceSoftware,0);
		return 1;  // Let the system set the focus
	}

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		HWND button = GetDlgItem(IDC_FORCE_SOFTWARE);
		m_bForceSoftware = BOOL2bool((int)SendMessage(button, BM_GETCHECK,0,0));
		EndDialog(wID);
		return IDOK;
	}

	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
	LRESULT OnClickedButton_color_background_bottom(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
 		ChooseBkColor(m_bottom_color);
		// TODO : Add Code for control notification handler.
		return 0;
	}
	LRESULT OnClickedButton_color_background_top(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		// TODO : Add Code for control notification handler.
		ChooseBkColor(m_top_color);
		return 0;

	}
	LRESULT OnClickedButton_color_selection(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		// TODO : Add Code for control notification handler.
		ChooseBkColor(m_selection_color);
		return 0;

	}
	LRESULT OnClickedButton_force_software(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		// TODO : Add Code for control notification handler.
	
		/*
		if (!::IsWindowEnabled(button))
		    ::EnableWindow(button, true);
		else
		    ::EnableWindow(button, false);
		    */
//		ChooseBkColor(m_top_color);

		return 0;

	}
	
	LRESULT OnClickedButton_reset(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
	 
	    m_bottom_color = m_default_bottom_color;
	    m_top_color = m_default_top_color;
	    m_selection_color = m_default_selection_color;
	    m_bForceSoftware = m_bDefaultForceSoftware;
	    HWND button = GetDlgItem(IDC_FORCE_SOFTWARE);
    	    SendMessage(button, BM_SETCHECK,m_bForceSoftware,0);
	    
	    ::InvalidateRect(m_hWnd, 0, true);

		return 0;

	}

	bool CAppearanceDlg::ChooseBkColor(COLORREF &cr);


	COLORREF m_bottom_color;	
	COLORREF m_top_color;
	COLORREF m_selection_color;

	COLORREF m_default_bottom_color;	
	COLORREF m_default_top_color;
	COLORREF m_default_selection_color;
	bool m_bForceSoftware;
	bool m_bDefaultForceSoftware;
 

 	LRESULT OnDrawItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{	

		RECT r;
 		HWND button = GetDlgItem(IDC_BUTTON_COLOR_BACKGROUND_TOP);
 		::GetWindowRect(button, &r);
		HDC dc= ::GetDC(button);		
		HBRUSH brush = CreateSolidBrush(RGB(GetRValue(m_top_color),GetGValue(m_top_color),GetBValue(m_top_color)));
  		HBRUSH *pOldBrush = (HBRUSH *)SelectObject(dc, brush);
		Rectangle(dc, 0+2,0+2,r.right-r.left-2,r.bottom-r.top-2);
		SelectObject(dc, pOldBrush);

		button = GetDlgItem(IDC_BUTTON_COLOR_BACKGROUND_BOTTOM);
 		::GetWindowRect(button, &r);
		dc= ::GetDC(button);		
 		brush = CreateSolidBrush(RGB(GetRValue(m_bottom_color),GetGValue(m_bottom_color),GetBValue(m_bottom_color)));
  		pOldBrush = (HBRUSH *)SelectObject(dc, brush);
		Rectangle(dc, 0+2,0+2,r.right-r.left-2,r.bottom-r.top-2);
		SelectObject(dc, pOldBrush);

		
		button = GetDlgItem(IDC_BUTTON_COLOR_SELECTION);
 		::GetWindowRect(button, &r);
		dc= ::GetDC(button);		
 		brush = CreateSolidBrush(RGB(GetRValue(m_selection_color),GetGValue(m_selection_color),GetBValue(m_selection_color)));
  		pOldBrush = (HBRUSH *)SelectObject(dc, brush);
		Rectangle(dc, 0+2,0+2,r.right-r.left-2,r.bottom-r.top-2);
		SelectObject(dc, pOldBrush);

		// TODO : Add Code for message handler. Call DefWindowProc if necessary.
		return 0;
	}
};

#endif //__APPEARANCEDLG_H_
