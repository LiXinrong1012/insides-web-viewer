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
// $Header: /files/homes/master/cvs/hoops_master/Hoops3dStreamCtrl/source/AppearanceDlg.cpp,v 1.5 2006-08-07 20:38:46 stage Exp $
//
#include "stdafx.h"
#include "AppearanceDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CAppearanceDlg


bool CAppearanceDlg::ChooseBkColor(COLORREF &cr)
{

	CHOOSECOLOR cc;
	static  COLORREF custom[16];
  
	cc.lStructSize = sizeof(CHOOSECOLOR);
	cc.hwndOwner = m_hWnd;
	cc.hInstance = 0;
	cc.rgbResult = RGB(0,0,0);
	cc.lpCustColors = custom;
	cc.Flags = CC_RGBINIT;
	cc.lCustData = 0;
	cc.lpfnHook = 0;
	cc.lpTemplateName = 0;

 
	if (::ChooseColor(&cc))
	{
		cr = cc.rgbResult;
		Invalidate();
		 return true;
	}
	else
		return false;
}