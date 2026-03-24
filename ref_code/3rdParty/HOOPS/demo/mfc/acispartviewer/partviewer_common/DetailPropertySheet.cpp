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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/DetailPropertySheet.cpp,v 1.13 2006-08-07 20:38:55 stage Exp $
//

// DetailPropertySheet.cpp : implementation file
//

#include "stdafx.h"
#include "HSInclude.h"

#include "frameratepage.h"
#include "lodpage.h"
#include "HSolidView.h"
#include "HBaseModel.h"
#include "DetailPropertySheet.h"
#include "busyloddlg.h"
 
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDetailPropertySheet

IMPLEMENT_DYNAMIC(CDetailPropertySheet, CPropertySheet)

CDetailPropertySheet::CDetailPropertySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{

}

CDetailPropertySheet::CDetailPropertySheet(LPCTSTR pszCaption,HSolidView *view, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{	
	m_pHView = view;
	char opt[MVO_BUFFER_SIZE];
	char lodon[MVO_BUFFER_SIZE];
	char token[MVO_BUFFER_SIZE];
	HC_KEY	keys[2];

	keys[0] = m_pHView->GetModelKey();
	keys[1] = m_pHView->GetViewKey();

	HC_PShow_One_Net_Rendering_Opti(2, keys, "lodo", opt);
	HC_PShow_One_Net_Rendering_Opti(2, keys, "lod", lodon);


	int c=0;
  	
	m_levels=1;
	m_falloff=0.3f;
	m_clamp=0;
	for (;;)
	{
		char item[MVO_BUFFER_SIZE];
		char value[MVO_BUFFER_SIZE];
		if (!HC_Parse_String(opt,",",c,token))
			break;
		HC_Parse_String(token,"=",0,item);
		HC_Parse_String(token,"=",1,value);
		strlwr(item);
		if (strcmp("levels",item)==0)
			m_levels = atoi(value);
//	let's set the default in this case to be 30%
		if (strcmp("ratio",item)==0)
			m_falloff = (float)atof(value);
		if (strcmp("clamp",item)==0)
			m_clamp = atoi(value);
		if (strcmp("on",lodon)==0)
			m_lod = true;
		else
			m_lod = false;
		c++;
	}
	if (m_clamp<0)
		m_clamp=0;
}

CDetailPropertySheet::~CDetailPropertySheet()
{
}


BEGIN_MESSAGE_MAP(CDetailPropertySheet, CPropertySheet)
	//{{AFX_MSG_MAP(CDetailPropertySheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(ID_APPLY_NOW,OnApply)
	ON_BN_CLICKED(IDOK,OnOK)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDetailPropertySheet message handlers


void CDetailPropertySheet::OnOK()
{


	CBusyLodDlg *	busy = 0;
	busy = new CBusyLodDlg();
				busy->Create(IDD_BUSYLODDLG);
				busy->ShowWindow(SW_SHOW);	

	int count = GetPageCount();
	for (int i=0;i<count;i++) 
		GetPage(i)->OnOK();	
  
	EndDialog(1);
	delete busy;

}

void CDetailPropertySheet::OnApply()
{
	CBusyLodDlg *	busy = 0;
	busy = new CBusyLodDlg();
				busy->Create(IDD_BUSYLODDLG);
				busy->ShowWindow(SW_SHOW);	
	GetActivePage()->UpdateData(true);
	
	int count = GetPageCount();
	for (int i=0;i<count;i++)
	{
		
	
 		//	GetActivePage()->UpdateData(true);
		//	int index = GetActiveIndex();
		switch(i)
		{
		case 0:	
			if (((CFrameratePage *)GetPage(i))->m_init)
				((CFrameratePage *)(GetPage(i)))->ApplyData();
			break;
		case 1:	
			if (((CLodPage *)GetPage(i))->m_init)
				((CLodPage *)(GetPage(i)))->ApplyData();
			break;
		}
		GetPage(i)->SetModified(false);
	}
	delete busy;
	
}
