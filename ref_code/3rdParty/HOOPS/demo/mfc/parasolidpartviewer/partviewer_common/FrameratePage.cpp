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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/FrameratePage.cpp,v 1.29 2007-03-19 17:21:01 guido Exp $
//

// FrameratePage.cpp : implementation file
//

#include "stdafx.h"
#include "HSInclude.h"
#include "hc.h"
#include "hsolidview.h"
#include "hconstantframerate.h"
#include "HBaseModel.h"
#include "HConstantFramerate.h"
#include "FrameratePage.h"
#include "busyloddlg.h"
#include "detailpropertysheet.h"
#include "CAppSettings.h"
 
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


float	CFrameratePage::m_ScreenExtent = 1;
float	CFrameratePage::m_DistanceWeight = 0;
float	CFrameratePage::m_DivergenceWeight = 0;
float	CFrameratePage::m_WorldVolume = 0;
BOOL	CFrameratePage::m_OrderedDrawing = false;
BOOL	CFrameratePage::m_TimedUpdate = false;
UINT	CFrameratePage::m_min_framerate = 10.0f;

/////////////////////////////////////////////////////////////////////////////
// CFrameratePage property page

IMPLEMENT_DYNCREATE(CFrameratePage, CPropertyPage)

CFrameratePage::CFrameratePage(HSolidView *view) : CPropertyPage(CFrameratePage::IDD)
{
	m_buselod = true;
	m_init = false;
	m_pHView = view;
	m_pCFR = m_pHView->GetConstantFrameRateObject();
	HConstFRSimpType **sd;
	float fr;
	int length;
	mlist = 0;
	mlistLength = 0;

	m_pCFR->GetMode(&sd,&fr,&length);
	
 
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
	if (m_bconstantframerate)
		m_min_framerate = (int)fr;

	m_increase=m_pCFR->GetDetailIncMode();

 	//{{AFX_DATA_INIT(CFrameratePage)
 	//}}AFX_DATA_INIT
}

CFrameratePage::~CFrameratePage()
{
}

void CFrameratePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFrameratePage)
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
	DDX_Text(pDX, IDC_EDIT_WORLD_VOLUME_WEIGHT, m_WorldVolume);
	DDX_Check(pDX, IDC_CHECK_ENABLE_ORDERED_DRAW, m_OrderedDrawing);
	DDX_Check(pDX, IDC_CHECK_ENABLE_TIMED_UPDATE, m_TimedUpdate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFrameratePage, CPropertyPage)
	//{{AFX_MSG_MAP(CFrameratePage)
	ON_BN_CLICKED(IDC_CHECK_CONSTANTFRAMERATE, OnCheckConstantframerate)
	ON_BN_CLICKED(IDC_CHECK_USELOD, OnCheckUselod)
	ON_BN_CLICKED(IDC_RADIO_ALLOW_INCREASEALWAYS, OnRadioAllowIncreasealways)
	ON_EN_CHANGE(IDC_EDIT_MINIMUM_FRAMERATE, OnChangeEditMinimumFramerate)
	ON_BN_CLICKED(IDC_CHECK_THRESHOLD, OnCheckThreshold)
	ON_BN_CLICKED(IDC_USEBOUNDINGBOXES, OnUseboundingboxes)
	ON_BN_CLICKED(IDC_RADIO_ALLOWNOINCREASE, OnRadioAllownoincrease)
	ON_BN_CLICKED(IDC_RADIO_ALLOWINCREASEONCE, OnRadioAllowincreaseonce)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

 
/////////////////////////////////////////////////////////////////////////////
// CFrameratePage message handlers


void CFrameratePage::OnCheckConstantframerate() 
{
	SetModified(true);
	UpdateData(TRUE);
	EnableItems();

}

void CFrameratePage::OnCheckUselod() 
{
	UpdateData(TRUE);
	SetModified(true);
	if (m_buselod)	
 		AfxMessageBox(_T("Enabling Level of Detail will require preprocessing time for the model!"));
 	EnableItems();
 
}


void CFrameratePage::EnableItems()
{
	SetModified(true);

	SetModified(true);
		if (!m_bconstantframerate)	
	{
		GetDlgItem(IDC_CHECK_USELOD)->EnableWindow(0);
// 		GetDlgItem(IDC_EDIT_MINIMUM_FRAMERATE)->EnableWindow(0);	
		GetDlgItem(IDC_STATIC_DESIRED)->EnableWindow(0);
		GetDlgItem(IDC_STATIC_FPS)->EnableWindow(0);
		GetDlgItem(IDC_CHECK_THRESHOLD)->EnableWindow(0);
		GetDlgItem(IDC_RADIO_ALLOWNOINCREASE)->EnableWindow(0);
		GetDlgItem(IDC_RADIO_ALLOWINCREASEONCE)->EnableWindow(0);
		GetDlgItem(IDC_RADIO_ALLOW_INCREASEALWAYS)->EnableWindow(0);
		GetDlgItem(IDC_USEBOUNDINGBOXES)->EnableWindow(0);
 
	}
		else
		{
		GetDlgItem(IDC_CHECK_USELOD)->EnableWindow(1);
// 		GetDlgItem(IDC_EDIT_MINIMUM_FRAMERATE)->EnableWindow(1);
		GetDlgItem(IDC_STATIC_DESIRED)->EnableWindow(1);
		GetDlgItem(IDC_STATIC_FPS)->EnableWindow(1);
		GetDlgItem(IDC_CHECK_THRESHOLD)->EnableWindow(1);
		GetDlgItem(IDC_RADIO_ALLOWNOINCREASE)->EnableWindow(1);
		GetDlgItem(IDC_RADIO_ALLOW_INCREASEALWAYS)->EnableWindow(1);
		GetDlgItem(IDC_RADIO_ALLOWINCREASEONCE)->EnableWindow(1);
 

		if (m_buselod)
		{
			GetDlgItem(IDC_USEBOUNDINGBOXES)->EnableWindow(1);
			GetDlgItem(IDC_CHECK_THRESHOLD)->EnableWindow(1);
 
		}
		else
		{
			GetDlgItem(IDC_CHECK_THRESHOLD)->EnableWindow(0);
			GetDlgItem(IDC_USEBOUNDINGBOXES)->EnableWindow(0);
 
		}

		}
}

void CFrameratePage::OnRadioAllowIncreasealways() 
{
	SetModified(true);
 	AfxMessageBox(_T("This option may result in undesired oscillation between different detail levels for some models!"));
  	
}

void CFrameratePage::OnOK() 
{
    UpdateData(TRUE);
    ApplyData();
    HC_Open_Segment_By_Key(m_pHView->GetModelKey());
    if (HC_Show_Existence("rendering options"))
	HC_UnSet_Rendering_Options();
    HC_Close_Segment();
    
    CDialog::OnOK();
}

void CFrameratePage::OnCancel() 
{
    HC_Open_Segment_By_Key(m_pHView->GetModelKey());
    if (HC_Show_Existence("rendering options"))
	HC_UnSet_Rendering_Options();
    HC_Close_Segment();
    
    CDialog::OnCancel();
}


 
void CFrameratePage::ApplyData()
{
  	if (m_bconstantframerate)
	{

			// if we have an opengl card then don't do the wireframe case since OpenGL cards
			// do not typically provide good wireframe acceleration
#if 0
			if (m_buselod)
			{							 			
				if (!m_bthreshold)
				{
					if (m_bboundingboxes)
						m_pCFR->Init((float)m_min_framerate);   
					else
					{
 						//HConstFRSimpType **mlist=new HConstFRSimpType *[4];						
						cleanupSimpList();
						mlist=new HConstFRSimpType *[3];
						mlistLength = 2;
 						mlist[0] = new HFrNoSimp;
						mlist[1] = new HFrLodThreshold(0,6);
			 	
						if (streq(m_pHView->GetDriverType(), "opengl") || streq(m_pHView->GetDriverType(), "direct3d"))	{			
 							m_pCFR->Init((float)m_min_framerate, mlist, 2);   
							mlistLength = 2;
						}
						else
						{
							mlist[2] = new HFrWireframe(1,1);
 							m_pCFR->Init((float)m_min_framerate, mlist, 3); 
							mlistLength = 3;
						}
					}
				}
				else
				{
					if (streq(m_pHView->GetDriverType(), "opengl") || streq(m_pHView->GetDriverType(), "direct3d"))				
					{
 						//HConstFRSimpType **mlist=new HConstFRSimpType *[3];						
						cleanupSimpList();
						mlist=new HConstFRSimpType *[3];		
						mlistLength = 2;
						mlist[0] = new HFrNoSimp;
						mlist[1] = new HFrLodThreshold(0,6);
  						if (m_bboundingboxes)
						{
							mlist[2] = new HFrSolidBBox;						
							m_pCFR->Init((float)m_min_framerate, mlist, 3);   
							mlistLength = 3;
						}
						else{
							m_pCFR->Init((float)m_min_framerate, mlist, 2);   
							mlistLength = 2;
						}

					}
					else
					{							
 						//HConstFRSimpType **mlist=new HConstFRSimpType *[4];						
						cleanupSimpList();
						mlist=new HConstFRSimpType *[4];
						mlistLength = 3;
						mlist[0] = new HFrNoSimp;
						mlist[1] = new HFrLodThreshold(0,6);
						mlist[2] = new HFrWireframe(1,1);						
	 					if (m_bboundingboxes)
						{ 
							mlist[3] = new HFrSolidBBox;						
							m_pCFR->Init((float)m_min_framerate, mlist, 4);   
							mlistLength = 4;
						}
						else{
							m_pCFR->Init((float)m_min_framerate, mlist, 3);   
							mlistLength = 3;
						}
					}
				}
					//this is optional to precalculate the LOD settings..
				
 
			}
			else
			{

				if (streq(m_pHView->GetDriverType(), "opengl") || streq(m_pHView->GetDriverType(), "direct3d"))				
				{
 					//HConstFRSimpType **mlist=new HConstFRSimpType *[2];						
					cleanupSimpList();
					mlist=new HConstFRSimpType *[2];
					mlistLength = 2;
					mlist[0] = new HFrNoSimp;
  					mlist[1] = new HFrSolidBBox(0,1);						

 					m_pCFR->Init((float)m_min_framerate,mlist,2);


				}
				else
				{
 					//HConstFRSimpType **mlist=new HConstFRSimpType *[3];						
					cleanupSimpList();
					mlist=new HConstFRSimpType *[3];						
					mlistLength = 3;
					mlist[0] = new HFrNoSimp;
 					mlist[1] = new HFrWireframe;						
					mlist[2] = new HFrSolidBBox(0,1);						
 					m_pCFR->Init((float)m_min_framerate,mlist,3);


				}
			}
#endif
			cleanupSimpList();
			mlist=new HConstFRSimpType *[2];						
			mlistLength = 2;
			int cs = CAppSettings::CullingThreshold / 5-1;
			m_pHView->SetCullingThreshold(0);
			mlist[0] = new HFrNoSimp(0,0);
			mlist[1] = new HFrExtent(0,cs);
			m_pCFR->Init((float)m_min_framerate,mlist,2);

			m_pCFR->SetDetailIncMode((DetailChangeMode)m_increase);
			m_pCFR->SetDetailIncOnIdleMode(NoDetailChange);
			m_pCFR->AdjustDefaultDetailLevelToModel();
			m_pCFR->Start();	
 		
		}	
		else
		{
			m_pCFR->Stop();	
			m_pCFR->Shutdown();  
			cleanupSimpList();
		}
		HC_Open_Segment_By_Key(m_pHView->GetSceneKey());

		char text[MVO_BUFFER_SIZE];
		if (m_OrderedDrawing)
		{
			HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
			sprintf (text, 
				"ordered drawing = on, ordered weights = (world volume = %f, screen extent = %f, distance = %f, divergence = %f)",
				m_WorldVolume, m_ScreenExtent, m_DistanceWeight, m_DivergenceWeight);
			HC_Set_Heuristics(text);
 			HC_Close_Segment();
		}
		else
		{
			if (HC_Show_Existence ("heuristics = ordered drawing"))
				HC_UnSet_One_Heuristic("ordered drawing");

		}
		HC_Close_Segment();

		if (m_TimedUpdate)
			m_pHView->SetMaximumUpdateTime(1.0f / m_min_framerate);
		else
			m_pHView->SetMaximumUpdateTime(0.0f);

}

 
BOOL CFrameratePage::OnInitDialog() 
{
	m_init = true;
	CPropertyPage::OnInitDialog();

 	EnableItems();
 
	HBaseView *phView= m_pCFR->GetView();

	char opt[MVO_BUFFER_SIZE];
	char token[MVO_BUFFER_SIZE];
	HC_KEY	keys[2];

	keys[0] = phView->GetModelKey();
	keys[1] = phView->GetViewKey();


	HC_PShow_One_Net_Rendering_Opti(2, keys, "lodo", opt);


	int c=0;
	int levels=1;
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
 
 

 
 	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}	
 

void CFrameratePage::OnChangeEditMinimumFramerate() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	SetModified(true);
	
}

void CFrameratePage::OnCheckThreshold() 
{
	// TODO: Add your control notification handler code here
	SetModified(true);
	
}

void CFrameratePage::OnUseboundingboxes() 
{
	// TODO: Add your control notification handler code here
	SetModified(true);
	
}

void CFrameratePage::OnRadioAllownoincrease() 
{
	// TODO: Add your control notification handler code here
	SetModified(true);
	
}

void CFrameratePage::OnRadioAllowincreaseonce() 
{
	// TODO: Add your control notification handler code here
	SetModified(true);
	
}

void CFrameratePage::cleanupSimpList(){

	for (int i=0;i<mlistLength;i++){
			delete mlist[i];
	}

	delete [] mlist;

	mlistLength = 0;
	mlist = 0;

}
