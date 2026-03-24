// EditLightsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "HSInclude.h"
#include "EditLightsDlg.h"
#include "HSolidView.h"
#include "HUtilityLocaleString.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditLightsDlg dialog


CEditLightsDlg::CEditLightsDlg(HBaseView* pHSolidView, CWnd* pParent /*=NULL*/)
	: CDialog(CEditLightsDlg::IDD, pParent)
{
	assert( pHSolidView );
	m_pHView = pHSolidView;

	//{{AFX_DATA_INIT(CEditLightsDlg)
	m_LightStatus = -1;
	m_bFollowCamera = FALSE;
	//}}AFX_DATA_INIT
}


void CEditLightsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditLightsDlg)
	DDX_Control(pDX, IDC_COMBO_LIGHT_NAMES, m_LightsCombo);
	DDX_Radio(pDX, IDC_EDITLIGHTS_ON, m_LightStatus);
	DDX_Check(pDX, IDC_LIGHT_FOLLOW_CAMERA, m_bFollowCamera);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditLightsDlg, CDialog)
	//{{AFX_MSG_MAP(CEditLightsDlg)
	ON_BN_CLICKED(IDC_BUTTON_LIGHT_COLOR, OnButtonLightColor)
	ON_BN_CLICKED(IDC_BUTTON_ADD_LIGHT, OnButtonAddLight)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE_LIGHT, OnButtonRemoveLight)
	ON_BN_CLICKED(IDC_EDITLIGHTS_ON, OnEditlightsOn)
	ON_BN_CLICKED(IDC_EDITLIGHTS_OFF, OnEditlightsOff)
	ON_CBN_SELCHANGE(IDC_COMBO_LIGHT_NAMES, OnSelchangeComboLightNames)
	ON_BN_CLICKED(IDC_LIGHT_FOLLOW_CAMERA, OnLightFollowCamera)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditLightsDlg message handlers


BOOL CEditLightsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// Search for all the segments underneath 
	// View\Scene\lights\PartViewerLights\StaticLights and
	// View\Scene\lights\PartViewerLights\DynamicLights 

	m_LightsCombo.ResetContent();

	char	type[MVO_BUFFER_SIZE];
	HC_KEY	lite_seg_key = 0;
	HC_Open_Segment_By_Key(m_pHView->GetLightsKey());
		// insert the default light first
		int default_lite_pos = insert_light_in_combo( m_pHView->GetLightsKey(), "Default");
		HC_Open_Segment("PartViewerLights/StaticLights");
			HC_Begin_Contents_Search ("...", "segment");
			while( HC_Find_Contents(type, &lite_seg_key)) 
				insert_light_in_combo( lite_seg_key );
			HC_End_Contents_Search ();
		HC_Close_Segment();

		HC_Open_Segment("PartViewerLights/DynamicLights");
			HC_Begin_Contents_Search ("...", "segment");
			while( HC_Find_Contents(type, &lite_seg_key)) 
				insert_light_in_combo( lite_seg_key );
			HC_End_Contents_Search ();
		HC_Close_Segment();

	HC_Close_Segment();

	// Set the current combo selection to default light
	m_LightsCombo.SetCurSel(default_lite_pos);
	// update the switch and follow camera check box for the default light in combo
	update_switch();
	update_follow_camera_ctrl();

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

int CEditLightsDlg::insert_light_in_combo( HC_KEY lightSegmentKey, char* lightName )
{
	// Get the name for this light
	char new_name[MVO_BUFFER_SIZE];
	if( !lightName )
		get_new_name(new_name);
	else
		strcpy( new_name, lightName );

	// Add this new light to the combo
	int new_lite_index = m_LightsCombo.AddString( H_TEXT(new_name));
	m_LightsCombo.SetItemData( new_lite_index, (DWORD) lightSegmentKey );

	return new_lite_index;
}

void CEditLightsDlg::OnButtonLightColor() 
{
	// Get the current selected light and get it color to preset the color dialog
	int cur_sel = m_LightsCombo.GetCurSel();
	assert( cur_sel >= 0 );
	if( cur_sel < 0 )
		return;

	HC_KEY cur_lite_seg_key = (HC_KEY) m_LightsCombo.GetItemData(cur_sel);

	// Get the user's choice of color for this light
	float red_col;
	float green_col;
	float blue_col;
	COLORREF cur_color(RGB(1, 1, 1));
	// Get the existing color on this light and preset it
	HC_Open_Segment_By_Key(cur_lite_seg_key);
		if (HC_Show_Existence("color"))
		{
			char types[MVO_BUFFER_SIZE], color_space[MVO_BUFFER_SIZE];
			HC_Show_Color_By_Value(types, color_space, &red_col, &green_col, &blue_col );
			cur_color = RGB( (int)(red_col*255.0), (int)(green_col*255.0), (int)(blue_col*255.0) );
		}
	HC_Close_Segment();

	CColorDialog color_dlg( cur_color );
	if( color_dlg.DoModal() != IDOK )
		return;

	COLORREF user_color = color_dlg.GetColor();
	red_col = (float)GetRValue(user_color)/255.0f;
	green_col = (float)GetGValue(user_color)/255.0f;
	blue_col = (float)GetBValue(user_color)/255.0f;


	// set the color of this segment
	HC_Open_Segment_By_Key(cur_lite_seg_key);
		HC_Set_Color_By_Value("everything", "RGB", red_col, green_col, blue_col );
	HC_Close_Segment();

	HC_Update_Display();

}

//======================================================================
//	Author :Rajesh B			Created : 3/21/2001 5:50:16 PM
//======================================================================
//	Function :CEditLightsDlg::OnButtonAddLight
//	Description :	Adds a new segment under 
//					View\Scene\lights\PartViewerLights\StaticLights called 
//					LIGHTn with all the default values set. Upates the
//					lights combo box selecting the latest light added
//	Return :void	-	
//	Parameters :
//	Note :
//======================================================================
void CEditLightsDlg::OnButtonAddLight() 
{
	// Get the current camera position
	HPoint	position, target, up;
	float	width, height;
	char    projection[MVO_BUFFER_SIZE];

	HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
		HC_Show_Net_Camera (&position, &target, &up, 
			&width, &height, projection);
	HC_Close_Segment();

	// Insert a new light segment with default values set it
	HC_Open_Segment_By_Key(m_pHView->GetLightsKey());
		HC_Open_Segment("PartViewerLights");
			// TODO: STATIC OR DYNAMIC BY DEFAULT?
			HC_Open_Segment("StaticLights");
				
				char new_name[MVO_BUFFER_SIZE];
				get_new_name(new_name);
				HC_KEY new_lite_seg = HC_KOpen_Segment(new_name);

 						HC_KInsert_Local_Light(position.x - target.x, 
										 position.y - target.y, 
										 position.z - target.z);

				// set the defaults
			    char default_color[MVO_BUFFER_SIZE];
				get_default_color(default_color);
				HC_Set_Color(default_color);

				char default_vis[MVO_BUFFER_SIZE];
				get_default_visibility(default_vis);
				HC_Set_Visibility(default_vis);

				HC_Close_Segment();
			HC_Close_Segment();
		HC_Close_Segment();
	HC_Close_Segment();

	// Add this new light to the combo
	int new_lite_index = m_LightsCombo.AddString( H_TEXT(new_name) );
	m_LightsCombo.SetItemData( new_lite_index, (DWORD) new_lite_seg );

	// set this as current selection so that the
	// rest of the dialog box controls get tuned
	m_LightsCombo.SetCurSel( new_lite_index );
	update_switch();
	update_follow_camera_ctrl();

	HC_Update_Display();

	UpdateData(FALSE);

}


void CEditLightsDlg::OnButtonRemoveLight() 
{
	// Get the current selected light
	int cur_sel = m_LightsCombo.GetCurSel();
	assert( cur_sel >= 0 );
	if( cur_sel < 0 )
		return;

	// just get the item data which is key for the light segment
	HC_KEY lite_seg_key = (HC_KEY) m_LightsCombo.GetItemData(cur_sel);

	// user can't delete the default light
	if( lite_seg_key == m_pHView->GetLightsKey() )
	{
		AfxMessageBox(_T("Cannot delete the default light"));
		return;
	}

	HC_Delete_By_Key( lite_seg_key );

	// Delete this light entry from the combo
	m_LightsCombo.DeleteString( cur_sel );

	// Set the next item as current sel, if this was not the last item
	int items_left = m_LightsCombo.GetCount();
	if( cur_sel <  items_left )
		m_LightsCombo.SetCurSel( cur_sel );
	else
		m_LightsCombo.SetCurSel( cur_sel-1 );

	update_switch();
	update_follow_camera_ctrl();

	HC_Update_Display();
	UpdateData(FALSE);

}


//======================================================================
//	Author :Rajesh B			Created : 3/22/2001 3:17:46 PM
//======================================================================
//	Function :CEditLightsDlg::OnEditlightsOn
//	Description :	Switches the current selected light ON
//	Return :void	-	
//	Parameters :
//	Note :
//======================================================================
void CEditLightsDlg::OnEditlightsOn() 
{
	switch_light( true );
	HC_Update_Display();
}

//======================================================================
//	Author :Rajesh B			Created : 3/22/2001 3:33:33 PM
//======================================================================
//	Function :CEditLightsDlg::OnEditlightsOff
//	Description :	Switches the current selected light OFF
//	Return :void	-	
//	Parameters :
//	Note :
//======================================================================
void CEditLightsDlg::OnEditlightsOff() 
{
	switch_light( false );
	HC_Update_Display();
}


//======================================================================
//	Author :Rajesh B			Created : 3/22/2001 3:57:34 PM
//======================================================================
//	Function :		CEditLightsDlg::OnSelchangeComboLightNames
//	Description :	Analyses the current selection and sets the 
//					other controls of the dialog box
//	Return :void	-	
//	Parameters :
//	Note :
//======================================================================
void CEditLightsDlg::OnSelchangeComboLightNames() 
{
	// Get the current selected light
	int cur_sel = m_LightsCombo.GetCurSel();
	assert( cur_sel >= 0 );
	if( cur_sel < 0 )
		return;

	// Set "on/off" radio buttons by analyzing the visibility 
	// of the segment
 	update_switch();
	update_follow_camera_ctrl();

	// TODO: IF IT IS DEFAULT LIGHT, DISABLE THE "REMOVE BUTTON"
	// TODO: SET "LIGHT FOLLOWS CAMERA" CHECK BOX
	UpdateData(FALSE);
	
}


//======================================================================
//	Author :Rajesh B			Created : 3/23/2001 11:35:17 AM
//======================================================================
//	Function :		CEditLightsDlg::OnLightFollowCamera
//	Description :	Sets the follow camera attribute for the light 
//					segment
//	Return :void	-	
//	Parameters :
//	Note :
//======================================================================
void CEditLightsDlg::OnLightFollowCamera() 
{
	UpdateData(TRUE);

	// Get the current selected light
	int cur_sel = m_LightsCombo.GetCurSel();
	assert( cur_sel >= 0 );
	if( cur_sel < 0 )
		return;

	// get the item data which is key for the light segment
	HC_KEY lite_seg_key = (HC_KEY) m_LightsCombo.GetItemData(cur_sel);

	// if this is default light, use HBaseView method to set the attribute
	if( lite_seg_key == m_pHView->GetLightsKey() )
	{
		if( m_bFollowCamera )
			m_pHView->SetLightFollowsCamera(true);
		else
			m_pHView->SetLightFollowsCamera(false);
	}
	else
	{
		HC_Open_Segment_By_Key(m_pHView->GetLightsKey());
			HC_Open_Segment("PartViewerLights");
			if( m_bFollowCamera )
			{
				// move this segment under "DynamicLights" so that view can understand
				// it and rotate
				HC_Move_By_Key( lite_seg_key, "DynamicLights");
				HC_Open_Segment_By_Key( lite_seg_key );
					HC_Set_User_Options("follow_camera = true");
				HC_Close_Segment();
			}
			else
			{
				// move this segment under "DynamicLights" so that view can understand
				// it and rotate
				HC_Move_By_Key( lite_seg_key, "StaticLights");
				HC_Open_Segment_By_Key( lite_seg_key );
					HC_Set_User_Options("follow_camera = false");
				HC_Close_Segment();
			}
			HC_Close_Segment();
		HC_Close_Segment();	
	}

}


//======================================================================
//	Author :Rajesh B			Created : 3/23/2001 2:31:58 PM
//======================================================================
//	Function :		CEditLights::RepositionLights
//	Description :	Searches for all light segments under "DynamicLights"
//					segments and moves them with to the new camera position
//	Return :void	-	
//	Parameters :
//			HBaseView* pBaseView	-	
//	Note :
//======================================================================
void CEditLightsDlg::RepositionLights( HBaseView* pBaseView )
{
	assert( pBaseView );

	// Retrieve the current camera position
	HPoint	position, target, up;
	float	width, height;
	char    projection[MVO_BUFFER_SIZE];

	HC_Open_Segment_By_Key(pBaseView->GetSceneKey());
		HC_Show_Net_Camera (&position, &target, &up, 
			&width, &height, projection);
	HC_Close_Segment();


	// Search for it in View\Scene\lights\PartViewerLights\DynamicLights
	char	type[MVO_BUFFER_SIZE];
	HC_KEY	tmp_key;
 
	HC_Open_Segment_By_Key(pBaseView->GetLightsKey());
		HC_Open_Segment("PartViewerLights/DynamicLights");
			HC_Begin_Contents_Search ("...", "light");
				while( HC_Find_Contents(type, &tmp_key)) 
				{	
					HC_Move_Light_Position( tmp_key, 
								position.x - target.x, 
								position.y - target.y, 
								position.z - target.z);
				}

			HC_End_Contents_Search ();
		HC_Close_Segment();
	HC_Close_Segment();
}




//======================================================================
//	Author :Rajesh B			Created : 3/22/2001 3:36:51 PM
//======================================================================
//	Function :		CEditLightsDlg::switch_light
//	Description :	Set's the visibility of currently selected light
//					segment
//	Return :void	-	
//	Parameters :
//			bool bIsOn	-	true to set on, false to set off
//	Note :
//======================================================================
void CEditLightsDlg::switch_light(bool bIsOn)
{
	// Get the current selected light
	int cur_sel = m_LightsCombo.GetCurSel();
	assert( cur_sel >= 0 );
	if( cur_sel < 0 )
		return;

	// get the item data which is key for the light segment
	HC_KEY lite_seg_key = (HC_KEY) m_LightsCombo.GetItemData(cur_sel);

	// set it's visibility on
	HC_Open_Segment_By_Key(lite_seg_key);
	if(bIsOn)
		HC_Set_Visibility("on");
	else
		HC_Set_Visibility("off");
	HC_Close_Segment();
}


//======================================================================
//	Author :Rajesh B			Created : 3/21/2001 5:49:00 PM
//======================================================================
//	Function :		CEditLightsDlg::get_default_color
//	Description :	returns the default color for new lights that
//					are to be added. My choice was white...
//	Return :void	-	
//	Parameters :
//			char* retColorStr	-	
//	Note :
//======================================================================
void CEditLightsDlg::get_default_color(char* retColorStr)
{
    sprintf(retColorStr, "everything = blue");
}

void CEditLightsDlg::get_default_visibility(char* retVisibilityStr)
{
    sprintf(retVisibilityStr, "on");
}


//======================================================================
//	Author :Rajesh B			Created : 3/21/2001 5:34:30 PM
//======================================================================
//	Function :		CEditLightsDlg::get_new_color
//	Description :	The new light name is "LIGHTn" where n is the number 
//					of entries in m_LightsCombo plus one
//	Return :void	-	
//	Parameters :
//			char* retNewName	-	
//	Note :
//======================================================================
void CEditLightsDlg::get_new_name(char* retNewName)
{
	// count the number of existing lights
	int n_lits = m_LightsCombo.GetCount();
    sprintf(retNewName, "LIGHT%d", n_lits);
}

//======================================================================
//	Author :Rajesh B			Created : 3/23/2001 9:36:39 AM
//======================================================================
//	Function :		CEditLightsDlg::update_switch
//	Description :	analyses the visibility of currently selected light segment and
//					sets the radio button member appropriately
//	Return :void	-	
//	Parameters :
//	Note :
//======================================================================
void CEditLightsDlg::update_switch()
{
	// Get the current selected light
	int cur_sel = m_LightsCombo.GetCurSel();
	assert( cur_sel >= 0 );
	if( cur_sel < 0 )
		return;

	// get the item data which is key for the light segment
	HC_KEY lite_seg_key = (HC_KEY) m_LightsCombo.GetItemData(cur_sel);

	char visibility[MVO_BUFFER_SIZE];
	HC_Open_Segment_By_Key(lite_seg_key);
		if (HC_Show_Existence("visibility"))
		{
			char token[MVO_BUFFER_SIZE];
			HC_Show_Visibility (visibility);
			if(HC_Parse_String(visibility," ",0,token))
			{
				if (strstr(token,"on"))
					m_LightStatus = 0;	// remember this is 0 because 'on' is first radio button
				else
					m_LightStatus = 1;
			}
		}
		else	// if there is no visibility at all, it must be on then
			m_LightStatus = 0;
	HC_Close_Segment();
}

void CEditLightsDlg::update_follow_camera_ctrl()
{
	// Get the current selected light
	int cur_sel = m_LightsCombo.GetCurSel();
	assert( cur_sel >= 0 );
	if( cur_sel < 0 )
		return;

	// get the item data which is key for the light segment
	HC_KEY lite_seg_key = (HC_KEY) m_LightsCombo.GetItemData(cur_sel);

	// if this is default light, use HBaseView method to get the attribute
	if( lite_seg_key == m_pHView->GetLightsKey() )
	{
		m_bFollowCamera = m_pHView->IsLightFollowCamera();
	}
	else
	{
		// find the user option name "follow_camera"
		HC_Open_Segment_By_Key(lite_seg_key);
			if (HC_Show_Existence("user options"))
			{
				char user_opts[MVO_BUFFER_SIZE];
 				HC_Show_One_User_Option("follow_camera", user_opts);
				if( strstr( "true", user_opts ) )
					m_bFollowCamera = true;
				else
					m_bFollowCamera = false;
			}
			else
				m_bFollowCamera = false;
		HC_Close_Segment();	
	}
	
}


//	CString light_name;
//	m_LightsCombo.GetLBText( cur_sel, light_name );
//	
//	// Search for it in View\Scene\lights\PartViewerLights and delete it
//	char	type[256];
//	HC_KEY	tmp_key;
//	bool	b_found = true;
//
//	HC_Open_Segment_By_Key(m_pHView->GetLightsKey());
//		HC_Open_Segment("PartViewerLights");
//			HC_Begin_Contents_Search ("...", "segment");
//				while( HC_Find_Contents(type, &tmp_key)) 
//				{	
//					CString found_seg_path, found_seg_name;
//					HC_Show_Segment(tmp_key, found_seg_path.GetBuffer(2056) );
//					found_seg_path.ReleaseBuffer();
//					HC_Parse_String (found_seg_path, "/", -1, found_seg_name.GetBuffer(2056));
//					if( found_seg_name.CompareNoCase( light_name ) == 0 )
//						HC_Delete_Segment( found_seg_path );
//				}
//			HC_End_Contents_Search ();
//		HC_Close_Segment();
//	HC_Close_Segment();



