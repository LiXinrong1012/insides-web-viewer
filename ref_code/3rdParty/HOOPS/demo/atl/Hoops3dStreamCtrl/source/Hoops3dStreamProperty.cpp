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
// $Header: /files/homes/master/cvs/hoops_master/Hoops3dStreamCtrl/source/Hoops3dStreamProperty.cpp,v 1.9 2006-08-07 20:38:46 stage Exp $
//
#include "stdafx.h"
#include "Hoops3dStream.h"
#include "Hoops3dStreamProperty.h"
#include "Hoops3dStreamCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CHoops3dStreamProperty

CHoops3dStreamProperty::CHoops3dStreamProperty() 
{
	m_dwTitleID = IDS_TITLEHoops3dStreamProperty;
	m_dwHelpFileID = IDS_HELPFILEHoops3dStreamProperty;
	m_dwDocStringID = IDS_DOCSTRINGHoops3dStreamProperty;
	_tcscpy(m_filename,_T(""));
	m_embed = false;
}
LRESULT CHoops3dStreamProperty::Apply()
{
	::GetWindowText(GetDlgItem(IDC_EDIT_FILENAME), m_filename, MVO_BUFFER_SIZE);
	
	ATLTRACE(_T("CHoops3dStreamProperty::Apply\n"));
	for (UINT i = 0; i < m_nObjects; i++)
	{
		IHoops3dStreamCtrl *pH = NULL;
		m_ppUnk[i]->QueryInterface(IID_IHoops3dStreamCtrl, (void **)&pH);
		pH->put_Filename(CComBSTR(m_filename));
		pH->put_Embed(m_embed);
		pH->Release();
		// Do something interesting here
		// ICircCtl* pCirc;
		// m_ppUnk[i]->QueryInterface(IID_ICircCtl, (void**)&pCirc);
		// pCirc->put_Caption(CComBSTR("something special"));
		// pCirc->Release();
	}
	m_bDirty = FALSE;
	return S_OK;
}

LRESULT CHoops3dStreamProperty::OnClickedBrowse(WORD hNotifyCode, WORD wID, HWND hWNdCtl, BOOL &bHandled)
{	
    
	if(CHoops3dStreamCtrl::ShowFileDialog2(m_filename, MVO_BUFFER_SIZE) == S_OK)
	{
		SetDirty(true);
		::SetWindowText(GetDlgItem(IDC_EDIT_FILENAME), m_filename);
	}
	return S_OK;
	
}

 

LRESULT CHoops3dStreamProperty::OnClickedEmbed(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	SetDirty(true);
	m_embed = (::IsDlgButtonChecked(m_hWnd, IDC_EMBED) != 0);
	return 0;
}


LRESULT  CHoops3dStreamProperty::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_nObjects > 0 )
	{
		IHoops3dStreamCtrl *pH = NULL;
		m_ppUnk[0]->QueryInterface(IID_IHoops3dStreamCtrl, (void **)&pH);
		CComBSTR filename(m_filename);
		pH->get_Filename(&filename);
		::SetWindowText(GetDlgItem(IDC_EDIT_FILENAME), m_filename);
		pH->Release();
		SetDirty(FALSE);
	}
	return 0;
}



