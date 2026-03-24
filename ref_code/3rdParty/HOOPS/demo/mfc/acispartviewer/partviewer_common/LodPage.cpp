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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/LodPage.cpp,v 1.26 2007-03-19 17:21:51 guido Exp $
//

// LodPage.cpp : implementation file
//

#include "stdafx.h"
#include "HSInclude.h"
#include "hsolidview.h"
#include "hconstantframerate.h"
#include "HBaseModel.h"
#include "HConstantFramerate.h"
#include "LodPage.h"
#include "detailpropertysheet.h"
#include "busyloddlg.h"
#include "HUtilityLocaleString.h"
 
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLodPage property page

IMPLEMENT_DYNCREATE(CLodPage, CPropertyPage)

CLodPage::CLodPage(HSolidView *view) : CPropertyPage(CLodPage::IDD)
{
	m_init = false;
	m_pHView = view;
 	m_pCFR = m_pHView->GetConstantFrameRateObject();
	m_bShowDelayDialog = false;

 	//{{AFX_DATA_INIT(CLodPage)
	m_clampvalue = 0;
	m_maxclamp = _T("");
	m_HighQualityLod = FALSE;
	//}}AFX_DATA_INIT
}

CLodPage::~CLodPage()
{
}

void CLodPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLodPage)
	DDX_Slider(pDX, IDC_CLAMPSLIDER, m_clampvalue);
	DDX_Text(pDX, IDC_MAXCLAMP, m_maxclamp);
	DDX_Check(pDX, IDC_HIGH_QUALITY_LODS, m_HighQualityLod);
	//}}AFX_DATA_MAP
}




BEGIN_MESSAGE_MAP(CLodPage, CPropertyPage)
	//{{AFX_MSG_MAP(CLodPage)
	ON_CBN_SELCHANGE(IDC_DETAILLEVELCOMBO, OnSelchangeCombo)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_DOCLAMP, OnDoclamp)
	ON_CBN_SELCHANGE(IDC_FALLOFFCOMBO, OnSelchangeCombo)
	ON_CBN_SELCHANGE(IDC_CLAMPCOMBO, OnSelchangeCombo)
	ON_BN_CLICKED(IDC_HIGH_QUALITY_LODS, OnHighQualityLods)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

 
 
 

void CLodPage::OnSelchangeCombo() 
{
	SetModified(true);
	int levels;
	float falloff;
 	CComboBox *cbox = (CComboBox *)GetDlgItem(IDC_DETAILLEVELCOMBO);
	int sel = cbox->GetCurSel();
	TCHAR text[MVO_BUFFER_SIZE];
	cbox->GetLBText(sel,text);
	levels = atoi(H_ASCII_TEXT(text));
	cbox =(CComboBox *)GetDlgItem(IDC_FALLOFFCOMBO);
	sel = cbox->GetCurSel();
 	cbox->GetLBText(sel,text);
	falloff = (float)atof(H_ASCII_TEXT(text));
  	_itot(levels,text,10);
  	m_maxclamp = text;
	if (m_clampvalue>=levels)
		m_clampvalue = levels-1;
	if (levels==0)
	{
		GetDlgItem(IDC_CLAMPSLIDER)->EnableWindow(0);
		GetDlgItem(IDC_MINCLAMP)->EnableWindow(0);
		GetDlgItem(IDC_MAXCLAMP)->EnableWindow(0);
	}
	else
	{
		GetDlgItem(IDC_CLAMPSLIDER)->EnableWindow(1);
		GetDlgItem(IDC_MINCLAMP)->EnableWindow(1);
		GetDlgItem(IDC_MAXCLAMP)->EnableWindow(1);
	}

	UpdateData(false);
   
 	m_levels = levels;
  	m_falloff = falloff; 	
	((CSliderCtrl *)GetDlgItem(IDC_CLAMPSLIDER))->SetRange(0,levels,true);
	

}
 

 
 
void CLodPage::OnOK() 
{

	if (m_init)
	{
		ApplyData(false);
		CDialog::OnOK();	
	}
}

void CLodPage::OnCancel() 
{
	CDialog::OnOK();	

}


void CLodPage::ApplyData(bool SetClamp)
{
 		static int oldlevels=-1;
 		static int oldhighquality= -1;
		static float oldfalloff=-1.0;
		static bool olddoclamp = false;
		CBusyLodDlg *	busy = 0;
		char cval[MVO_BUFFER_SIZE];	

	 	int levels = m_levels;
  		float falloff = m_falloff; 	
  		int clamp = m_clamp;

	
		UpdateData(TRUE);
		
		if (oldlevels!=levels || oldfalloff!=falloff || oldhighquality!=m_HighQualityLod)
			{
				if (m_bShowDelayDialog)
				{
					busy = new CBusyLodDlg();
					busy->Create(IDD_BUSYLODDLG);
					busy->ShowWindow(SW_SHOW);	
				}
		}

		HC_Open_Segment_By_Key(m_pHView->GetModelKey());					
		
										
 			sprintf(cval, "lod, lodo =(clamp = %d, preprocess)", clamp);

	
			if (SetClamp)
  			    HC_Set_Rendering_Options(cval);     
 
		HC_Close_Segment();


		HC_Open_Segment_By_Key(m_pHView->GetModelKey());					
												
			if (oldlevels!=levels || oldfalloff!=falloff || oldhighquality!=m_HighQualityLod)
			{
				char quality[MVO_BUFFER_SIZE];
				if (m_HighQualityLod)
				    strcpy(quality, "nice");
				else
				    strcpy(quality, "fast");

				sprintf(cval, "levels = %d,ratio = %0.1f, preprocess, algorithm = %s", levels, falloff, quality);
				oldfalloff = falloff;
				oldlevels = levels;	
				oldhighquality = m_HighQualityLod;
				HC_Regenerate_LOD(".", cval);
//				HC_Set_Rendering_Options(cval);
			}
						
		HC_Close_Segment();

		HC_Control_Update_By_Key(m_pHView->GetViewKey(),"redraw everything");	
		HC_Update_Display();

		delete busy;
}

 
BOOL CLodPage::OnInitDialog() 
{
	m_init = true;

	CPropertyPage::OnInitDialog();
	m_levels = 2;
	m_falloff = 0.5f;
	m_clamp = 0;
   
	
	TCHAR text[MVO_BUFFER_SIZE];

	CComboBox *cbox = (CComboBox *)GetDlgItem(IDC_FALLOFFCOMBO);
	int i;
	for (i=0;i<10;i++)
	{
		TCHAR text[MVO_BUFFER_SIZE];
		_stprintf(text,_T("%0.2f"),0.1*i);
		int item = cbox->AddString(text);
		(void) item;
	}	

	_stprintf(text,_T("%0.2f"),m_falloff);
 	cbox->SelectString(0,text);

	cbox =(CComboBox *)GetDlgItem(IDC_DETAILLEVELCOMBO);
	for (i = 0;i < 8;i++)
	{
		TCHAR text[MVO_BUFFER_SIZE];
		_stprintf(text,_T("%d"),i);
		int item = cbox->AddString(text);
		(void) item;
	}	

	_itot(m_levels, text, 10);
	cbox->SelectString(0, text);

	_itot(m_levels, text, 10);

	CSliderCtrl * cslider = (CSliderCtrl *)GetDlgItem(IDC_CLAMPSLIDER);
	cslider->SetRange(0,m_levels,true);
	m_clampvalue = m_clamp;
 	m_maxclamp = text;
  
	if (m_levels==0)
	{
		GetDlgItem(IDC_CLAMPSLIDER)->EnableWindow(0);
		GetDlgItem(IDC_MINCLAMP)->EnableWindow(0);
		GetDlgItem(IDC_MAXCLAMP)->EnableWindow(0);
	}
	else
	{
		GetDlgItem(IDC_CLAMPSLIDER)->EnableWindow(1);
		GetDlgItem(IDC_MINCLAMP)->EnableWindow(1);
		GetDlgItem(IDC_MAXCLAMP)->EnableWindow(1);
	}


	UpdateData(false);   
 	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}	
 

void CLodPage::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
 	// TODO: Add your message handler code here and/or call default
	UpdateData(TRUE);

 
	m_clamp = m_clampvalue;
	SetModified(true);
	m_bShowDelayDialog = true;
	ApplyData();	
	m_bShowDelayDialog = false;
	CPropertyPage::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CLodPage::OnDoclamp() 
{
	UpdateData(true);
	if (m_levels <=1)
	{
		GetDlgItem(IDC_CLAMPSLIDER)->EnableWindow(0);
		GetDlgItem(IDC_MINCLAMP)->EnableWindow(0);
		GetDlgItem(IDC_MAXCLAMP)->EnableWindow(0);
	}
	else
	{
		GetDlgItem(IDC_CLAMPSLIDER)->EnableWindow(1);
		GetDlgItem(IDC_MINCLAMP)->EnableWindow(1);
		GetDlgItem(IDC_MAXCLAMP)->EnableWindow(1);
	}
	
}

void CLodPage::OnHighQualityLods() 
{
    SetModified(true);
	
}
