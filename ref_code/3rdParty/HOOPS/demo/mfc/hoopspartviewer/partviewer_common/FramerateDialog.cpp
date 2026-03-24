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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/FramerateDialog.cpp,v 1.24 2008-03-19 21:43:28 covey Exp $
//

// FrameRateDialog.cpp : implementation file
//

#include "stdafx.h"
#include "HBaseModel.h"
#include "FrameRateDialog.h"
#include "HConstantFrameRate.h"
#include "HUtilityLocaleString.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFrameRateDialog dialog


CFrameRateDialog::CFrameRateDialog(CWnd* pParent /*=NULL*/, HConstantFrameRate*	cframerate)
	: CDialog(CFrameRateDialog::IDD, pParent)
{
	HConstFRSimpType **sd;
	float fr;
	int length;

	m_pCFR = cframerate;
	cframerate->GetMode(&sd,&fr,&length);
	
 
	m_bconstantframerate = sd ? 1 : 0;
	for (int i=0;i<length;i++)
	{
		if (sd[i]->GetType() == ConstFRSolidBBoxType)
			m_bboundingboxes = true;
		if (sd[i]->GetType() == ConstFRLodClampType || sd[i]->GetType()==
			ConstFRLodThresholdType)
			{
				m_buselod = 1;
				if (sd[i]->GetType() == ConstFRLodThresholdType)
					m_bthreshold = true;

		}
	}
	m_min_framerate = (int)fr;
	m_increase=cframerate->GetDetailIncMode();

//	((CButton *)GetDlgItem(IDC_CHECK_USELOD))->SetState(0);
 
}


void CFrameRateDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFrameRateDialog)
	DDX_Check(pDX, IDC_CHECK_CONSTANTFRAMERATE, m_bconstantframerate);
	DDX_Check(pDX, IDC_CHECK_USELOD, m_buselod);
	DDX_Text(pDX, IDC_EDIT_MINIMUM_FRAMERATE, m_min_framerate);
	DDV_MinMaxUInt(pDX, m_min_framerate, 1, 60);
	DDX_Check(pDX, IDC_CHECK_THRESHOLD, m_bthreshold);
	DDX_Radio(pDX, IDC_RADIO_ALLOWNOINCREASE, m_increase);
	DDX_Check(pDX, IDC_USEBOUNDINGBOXES, m_bboundingboxes);
	DDX_Text(pDX, IDC_EDIT_SCREEN_EXTENT_WEIGHT, m_ScreenExtent);
	DDX_Text(pDX, IDC_EDIT_DISTANCE_WEIGHT, m_DistanceWeight);
	DDX_Text(pDX, IDC_EDIT_DIVERGENCE_WEIGHT, m_DivergenceWeight);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFrameRateDialog, CDialog)
	//{{AFX_MSG_MAP(CFrameRateDialog)
	ON_BN_CLICKED(IDC_CHECK_CONSTANTFRAMERATE, OnCheckConstantframerate)
	ON_BN_CLICKED(IDC_CHECK_USELOD, OnCheckUselod)
	ON_BN_CLICKED(IDC_RADIO_ALLOW_INCREASEALWAYS, OnRadioAllowIncreasealways)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFrameRateDialog message handlers

BOOL CFrameRateDialog::OnInitDialog() 
{
	CDialog::OnInitDialog(); 
	EnableItems();
 
	HBaseView *phView= m_pCFR->GetView();

	char opt[MVO_BUFFER_SIZE];
	char token[MVO_BUFFER_SIZE];

	int c=0;
	int levels=1;
	float ratio=0.3f;

	int i;

	HC_KEY	keys[2];

	keys[0] = phView->GetModelKey();
	keys[1] = phView->GetViewKey();


	HC_PShow_One_Net_Rendering_Opti(2, keys, "lodo", opt);


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
			levels = atoi(value);
//	let's set the default in this case to be 30%
//		if (strcmp("ratio",item)==0)
//			ratio = (float)atof(value);
		c++;
	}
	TCHAR text[MVO_BUFFER_SIZE];

	CComboBox *cbox =(CComboBox *)GetDlgItem(IDC_FALLOFFCOMBO);
	for (i=1;i<10;i++)
	{
		TCHAR text[MVO_BUFFER_SIZE];
		_stprintf(text,_T("%0.2f"),0.1*i);
		cbox->AddString(text);
	}	

	_stprintf(text,_T("%0.2f"),ratio);
 	cbox->SelectString(0,text);

	cbox =(CComboBox *)GetDlgItem(IDC_DETAILLEVELCOMBO);
	for (i=1;i<5;i++)
	{
		TCHAR text[MVO_BUFFER_SIZE];
		_stprintf(text,_T("%d"),i);
		cbox->AddString(text);
	}	

	_itot(levels,text,10);
	cbox->SelectString(0,text);

 
 	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFrameRateDialog::OnCheckConstantframerate() 
{
	UpdateData(TRUE);
	EnableItems();

}

void CFrameRateDialog::OnCheckUselod() 
{
	UpdateData(TRUE);

	if (m_buselod)	
 		AfxMessageBox(_T("Enabling Level of Detail will require preprocessing time for the model!"));

 	EnableItems();
}


void CFrameRateDialog::EnableItems()
{
		if (!m_bconstantframerate)	
	{
		GetDlgItem(IDC_CHECK_USELOD)->EnableWindow(0);
 		GetDlgItem(IDC_EDIT_MINIMUM_FRAMERATE)->EnableWindow(0);	
		GetDlgItem(IDC_STATIC_DESIRED)->EnableWindow(0);
		GetDlgItem(IDC_STATIC_FPS)->EnableWindow(0);
		GetDlgItem(IDC_CHECK_THRESHOLD)->EnableWindow(0);
		GetDlgItem(IDC_RADIO_ALLOWNOINCREASE)->EnableWindow(0);
		GetDlgItem(IDC_RADIO_ALLOWINCREASEONCE)->EnableWindow(0);
		GetDlgItem(IDC_RADIO_ALLOW_INCREASEALWAYS)->EnableWindow(0);
		GetDlgItem(IDC_USEBOUNDINGBOXES)->EnableWindow(0);
		GetDlgItem(IDC_DETAILLEVELCOMBO)->EnableWindow(0);
		GetDlgItem(IDC_FALLOFFCOMBO)->EnableWindow(0);

	}
		else
		{
		GetDlgItem(IDC_CHECK_USELOD)->EnableWindow(1);
 		GetDlgItem(IDC_EDIT_MINIMUM_FRAMERATE)->EnableWindow(1);
		GetDlgItem(IDC_STATIC_DESIRED)->EnableWindow(1);
		GetDlgItem(IDC_STATIC_FPS)->EnableWindow(1);
		GetDlgItem(IDC_CHECK_THRESHOLD)->EnableWindow(1);
		GetDlgItem(IDC_RADIO_ALLOWNOINCREASE)->EnableWindow(1);
		GetDlgItem(IDC_RADIO_ALLOW_INCREASEALWAYS)->EnableWindow(1);
		GetDlgItem(IDC_RADIO_ALLOWINCREASEONCE)->EnableWindow(1);
		GetDlgItem(IDC_DETAILLEVELCOMBO)->EnableWindow(1);
		GetDlgItem(IDC_FALLOFFCOMBO)->EnableWindow(1);


		if (m_buselod)
		{
			GetDlgItem(IDC_USEBOUNDINGBOXES)->EnableWindow(1);
			GetDlgItem(IDC_CHECK_THRESHOLD)->EnableWindow(1);
			GetDlgItem(IDC_DETAILLEVELCOMBO)->EnableWindow(1);
			GetDlgItem(IDC_FALLOFFCOMBO)->EnableWindow(1);

		}
		else
		{
			GetDlgItem(IDC_CHECK_THRESHOLD)->EnableWindow(0);
			GetDlgItem(IDC_USEBOUNDINGBOXES)->EnableWindow(0);
			GetDlgItem(IDC_DETAILLEVELCOMBO)->EnableWindow(0);
			GetDlgItem(IDC_FALLOFFCOMBO)->EnableWindow(0);

		}

		}
}

void CFrameRateDialog::OnRadioAllowIncreasealways() 
{
	AfxMessageBox(_T("This option may result in undesired oscillation between different detail levels for some models!"));
}

void CFrameRateDialog::OnOK() 
{
	CComboBox *cbox =(CComboBox *)GetDlgItem(IDC_DETAILLEVELCOMBO);
	int sel = cbox->GetCurSel();
	TCHAR text[MVO_BUFFER_SIZE];
	cbox->GetLBText(sel,text);
	m_levels = atoi(H_ASCII_TEXT(text));
	cbox =(CComboBox *)GetDlgItem(IDC_FALLOFFCOMBO);
	sel = cbox->GetCurSel();
 	cbox->GetLBText(sel,text);
	m_falloff = (float)atof(H_ASCII_TEXT(text));
	
	CDialog::OnOK();
}
