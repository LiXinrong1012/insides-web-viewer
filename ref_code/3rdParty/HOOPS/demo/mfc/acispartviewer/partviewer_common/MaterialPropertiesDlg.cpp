// MaterialPropertiesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "MaterialPropertiesDlg.h"
#include "HUtilityLocaleString.h"
// MVO includes
#include "HBaseView.h"
#include "HSelectionSet.h"
#include "HIOManager.h"

#define TEXTURE_DATA_SEGMENT		"TSA Image Data"
#define SCRATCH_SEGMENT				"scratch segment"


/////////////////////////////////////////////////////////////////////////////
// MaterialPropertiesDlg dialog


MaterialPropertiesDlg::MaterialPropertiesDlg(HBaseView * pHView, CWnd* pParent /*=NULL*/)
	: CDialog(MaterialPropertiesDlg::IDD, pParent)
{
	m_pHView = pHView;
	m_pSelectionList = 0;
	m_SelNum = 0;
	//{{AFX_DATA_INIT(MaterialPropertiesDlg)
	m_FaceColorMode = -1;
	m_nFaceTransparency = 0;
	m_csTextureSourceFile = "";
	m_csTextureType = "diffuse";
	m_csTextureParamSource = "world";
	//}}AFX_DATA_INIT
}

MaterialPropertiesDlg::~MaterialPropertiesDlg()
{
    delete [] m_pSelectionList;
}
 
void MaterialPropertiesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MaterialPropertiesDlg)
	DDX_Control(pDX, IDC_BUTTON_FACE_COLOR, m_FaceColorButton);
	DDX_Radio(pDX, IDC_RADIO_FACE_COLOR, m_FaceColorMode);
	DDX_Text(pDX, IDC_EDIT_FACE_TRANSPARENCY, m_nFaceTransparency);
	DDV_MinMaxInt(pDX, m_nFaceTransparency, 0, 100);
	DDX_CBString(pDX, IDC_COMBO_TEX_TYPE, m_csTextureType);
	DDX_CBString(pDX, IDC_COMBO_TEX_PARAM_SOURCE, m_csTextureParamSource);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MaterialPropertiesDlg, CDialog)
	//{{AFX_MSG_MAP(MaterialPropertiesDlg)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE_TEXTURES, OnButtonBrowseTextures)
	ON_BN_CLICKED(IDC_RADIO_FACE_COLOR, OnRadioFaceColor)
	ON_BN_CLICKED(IDC_RADIO_FACE_TEXTURE, OnRadioFaceTexture)
	ON_BN_CLICKED(IDMATERIALAPPLY, OnMaterialapply)
	ON_CBN_SELCHANGE(IDC_COMBO_TEX_TYPE, OnSelchangeComboTextureType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MaterialPropertiesDlg message handlers
BOOL MaterialPropertiesDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_bFirst = true;
	if( !ValidateSelection() )
		return FALSE;


	m_FaceColorButton.currentcolor = RGB(0, 255, 0);
	set_face_color_mode(eColor);
	
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_COLOR_SEL_TRANSPARENCY))->SetRange(0, 100);


	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void MaterialPropertiesDlg::OnButtonBrowseTextures() 
{
	CString filter = _T("");
	CString def_ext = _T(".jpg");

	if(HDB::GetHIOManager()->GetInputHandler("jpg"))
		filter += _T("Jpeg Files (*.jpeg;*.jpg;)|*.jpeg;*.jpg;|");
	else
		def_ext = _T(".hsf");

	if(HDB::GetHIOManager()->GetInputHandler("bmp"))
		filter += _T("BMP Files (*.bmp)|*.bmp|");

	if(HDB::GetHIOManager()->GetInputHandler("gif"))
		filter += _T("GIF Files (*.gif)|*.gif|");

	if(HDB::GetHIOManager()->GetInputHandler("png"))
		filter += _T("PNG Files (*.png)|*.png|");

	if(HDB::GetHIOManager()->GetInputHandler("tiff"))
		filter += _T("Tiff Files (*.tiff;*.tif;)|*.tiff;*.tif;|");

	filter += _T("HOOPS File (*.hsf;*.hmf)|*.hsf;*.hmf||");

	TCHAR cur_dir[MVO_BUFFER_SIZE];
	GetCurrentDirectory(MVO_BUFFER_SIZE, cur_dir);
	CFileDialog my_dlg(TRUE, def_ext, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter , NULL);
	my_dlg.m_ofn.lpstrInitialDir = cur_dir;

	if (my_dlg.DoModal() == IDOK)
		m_csTextureSourceFile = my_dlg.GetPathName();
	
}

void MaterialPropertiesDlg::OnRadioFaceColor() 
{
	set_face_color_mode(eColor);
}

void MaterialPropertiesDlg::OnRadioFaceTexture() 
{
	set_face_color_mode(eTexture);
}

void MaterialPropertiesDlg::OnOK() 
{
	UpdateData(TRUE);

 
	// unfortunately, we have to deselect everything before we 
	// apply any new material properties. If we don't do it, the 
	// unhighlist mechanism in MVO will trample our changes. So, 
	// grab all the selection in an array and deselect - Rajesh B (26-Sept-03)
	OnMaterialapply();


	CDialog::OnOK();
}

bool MaterialPropertiesDlg::set_face_color_mode(ColorMode new_fc_mode)
{
	if( new_fc_mode == m_FaceColorMode )
		return true;

	m_FaceColorMode = new_fc_mode;
	update_face_color_controls();

	return true;
}

void MaterialPropertiesDlg::switch_face_color_controls( bool on_off )
{
	CWnd* p_face_clr_btn = GetDlgItem(IDC_BUTTON_FACE_COLOR);
	if( p_face_clr_btn )
		p_face_clr_btn->EnableWindow(on_off);
}

void MaterialPropertiesDlg::switch_face_texture_controls( bool on_off )
{
	CWnd* p_txt_brw_btn = GetDlgItem(IDC_BUTTON_BROWSE_TEXTURES);
	if( p_txt_brw_btn )
		p_txt_brw_btn->EnableWindow(on_off);

	CWnd* p_txt_type = GetDlgItem(IDC_COMBO_TEX_TYPE);
	if( p_txt_type )
		p_txt_type->EnableWindow(on_off);

	CWnd* p_txt_ps = GetDlgItem(IDC_COMBO_TEX_PARAM_SOURCE);
	if( p_txt_ps )
	{
		if( m_csTextureType == "environment" )
			p_txt_ps->EnableWindow(FALSE);
		else
			p_txt_ps->EnableWindow(on_off);
	}

}

void MaterialPropertiesDlg::update_face_color_controls()
{
	if( m_FaceColorMode == eColor )
	{
		switch_face_color_controls(true);
		switch_face_texture_controls(false);
	}
	else if( m_FaceColorMode == eTexture )
	{
		switch_face_color_controls(false);
		switch_face_texture_controls(true);
	}
	else
		// this mode is not valid
		assert(0);
}


void MaterialPropertiesDlg::update_texture_controls()
{
	CWnd* p_txt_ps = GetDlgItem(IDC_COMBO_TEX_PARAM_SOURCE);
	if( m_csTextureType == "environment" )
	{
		m_csTextureParamSource = "reflection";
		if( p_txt_ps )
			p_txt_ps->EnableWindow(FALSE);
	}
	else
	{
		if( p_txt_ps )
			p_txt_ps->EnableWindow(TRUE);
	}
}



bool MaterialPropertiesDlg::get_face_color_specs(CString& ret_specs)
{
	if( m_FaceColorMode == eColor )
	{
		COLORREF clr = m_FaceColorButton.currentcolor;
		ret_specs.Format(_T(" faces = (diffuse=(R=%1.4f G=%1.4f B=%1.4f)) "), 
				    ((float)GetRValue(clr))/255.0f,  ((float)GetGValue(clr))/255.0f,  ((float)GetBValue(clr))/255.0f );
	}
	else if( m_FaceColorMode == eTexture )
	{
		CString texture_name;
		if( !get_texture(texture_name) )
			return false;
	    ret_specs.Format(_T("faces = (%s = %s, mirror = grey)"), m_csTextureType, texture_name);
	}
	else
		// invalid mode
		assert(0);

	if( m_nFaceTransparency != 0 )
	{
	    float alpha = m_nFaceTransparency*0.01f;   // 100% transparent is alpha 1
	    CString transp;
	    transp.Format(_T(", face = (transmission=(R=%1.4f G=%1.4f B=%1.4f)) "), alpha, alpha, alpha );
	    ret_specs = ret_specs + transp;
	}

	return true;
}

bool MaterialPropertiesDlg::get_texture(CString& retTextureName)
{
    // validate
    if( m_csTextureSourceFile.IsEmpty() )
    {
		AfxMessageBox(_T("No file selected as texture source. Please select a file or set color instead of texture"));
		return false;
    }

    bool b_ret = true;
    HC_KEY image_key = INVALID_KEY;

    // create a scratch scratch segment to read the source file
    HC_Open_Segment_By_Key( m_pHView->GetModelKey() );
        HC_Open_Segment(TEXTURE_DATA_SEGMENT);
	    HC_Set_Visibility("everything = off");
	        HC_KEY temp_seg = HC_KOpen_Segment(SCRATCH_SEGMENT);
		HC_Close_Segment();
	HC_Close_Segment();
    HC_Close_Segment();


    // read the source file in to the scratch
    char file_ext[MVO_BUFFER_SIZE];
    HUtility::FindFileNameExtension( H_ASCII_TEXT(m_csTextureSourceFile), file_ext );
    if( streq(file_ext, "hsf") )
    {
        HC_Open_Segment_By_Key(temp_seg);
	    HStreamFileToolkit * tk = new HStreamFileToolkit();
 	    TK_Status status = HTK_Read_Stream_File (H_ASCII_TEXT(m_csTextureSourceFile), tk); 
		(void) status;
	    delete tk;
	HC_Close_Segment();
    }
    else if( streq(file_ext, "hmf") )
    {
        HC_Open_Segment_By_Key(temp_seg);
	    HC_Read_Metafile(H_ASCII_TEXT(m_csTextureSourceFile), ".", "restore state = textures"); 
        HC_Close_Segment();
    }
    else if (
		streq(file_ext, "png") ||
		streq(file_ext, "jpeg") || 
	    streq(file_ext, "jpg") || 
	    streq(file_ext, "bmp") || 
	    streq(file_ext, "tif") || 
	    streq(file_ext, "tiff") )
    {
		HInputHandler *reader = HDB::GetHIOManager()->GetInputHandler(file_ext);
		HInputHandlerOptions input_options;
		HFileInputResult result = InputFail;
			
		if(reader) {
			result = reader->FileInputToImageKey(H_ASCII_TEXT(m_csTextureSourceFile), &image_key, temp_seg, &input_options);
		}
		if( result != InputOK )
		{
			AfxMessageBox(_T("Failed to read the image file. Please choose a different file as texture source"));
			b_ret = false;
		}
    }
    else
    {
    	AfxMessageBox(_T("Unrecognized file extension. Please choose a different file as texture source"));
		b_ret = false;
    }

    // find out the first image in 'scratch' segment
    if( b_ret && image_key == INVALID_KEY )
    {
	char type[MVO_BUFFER_SIZE];
	int n_images;
	HC_Open_Segment_By_Key(temp_seg);
	    HC_Begin_Contents_Search ("./...", "images");
		HC_Show_Contents_Count (&n_images);
		if( n_images < 1 )
		{
		    AfxMessageBox(_T("No images found in the file. Please choose a different file as texture source"));
		    b_ret = false;
		}
		else
		    HC_Find_Contents (type, &image_key);

	    HC_End_Contents_Search ();
	HC_Close_Segment();
    }

    if( b_ret )
    {
    	// copy this image to TEXTURE_DATA_SEGMENT with a unique name
        float position[3];
        int   size[2];
        char  fmt[MVO_BUFFER_SIZE];
		HPixelRGB * image_data;

		HC_Show_Image_Size( image_key, &position[0], &position[1], &position[2],
						fmt, &size[0], &size[1]);

		image_data = new HPixelRGB[size[0] * size[1]];
			HC_Show_Image( image_key, &position[0], &position[1], &position[2],
							fmt, &size[0], &size[1], image_data);

		// DAMN. Can't even get something as simple as the format of the image that easy
		CString image_specs(fmt);
		int name_index = image_specs.Find( ',' );
		if( name_index != -1 )
			image_specs = image_specs.Left( name_index  );	// get everything except name
		CString image_name;
		generate_unique_name(image_name);
		image_specs = image_specs + ", name = " + image_name;	// attach new name

		// we have the image data, insert in our TEXTURE_DATA_SEGMENT
		HC_Open_Segment_By_Key( m_pHView->GetModelKey() );
			HC_Open_Segment(TEXTURE_DATA_SEGMENT);
				HC_Insert_Image( position[0], position[1], position[2],  
								 H_ASCII_TEXT(image_specs), size[0], size[1], image_data );
			HC_Close_Segment();
		HC_Close_Segment();

		// define a texture with this image and chosen parameters
		CString texture_name, texture_specs;
		texture_name = image_name + "_texture";
//  		if (strcmp(m_csType, "environment") == 0)
//			texture_specs.Format("source = %s, parameter source = reflection vector, layout = spherical", image_name, m_csType);
//		else
    		texture_specs.Format(_T("source = %s, parameter source = %s, decimation filter = mipmap"), image_name, m_csTextureParamSource);

		HC_Open_Segment_By_Key( m_pHView->GetModelKey() );
			HC_Set_Rendering_Options ("perspective correction");
			HC_Define_Local_Texture( H_ASCII_TEXT(texture_name), H_ASCII_TEXT(texture_specs));
		HC_Close_Segment();

		retTextureName = texture_name;
		delete [] image_data;
		b_ret = true;
    }

    // cleanup the scratch
    HC_Delete_By_Key(temp_seg);

    return b_ret;
}

bool MaterialPropertiesDlg::generate_unique_name(CString& retNewName)
{
	time_t ltime;
	time( &ltime );
	retNewName.Format(_T("material%ld"), ltime );
	return true;
}



bool MaterialPropertiesDlg::ValidateSelection()
{
	assert(m_pHView);
	HSelectionSet * sel_set = m_pHView->GetSelection();
	assert(sel_set);

	// we should have some selection
	int n_sel = sel_set->GetSize();
	if( n_sel < 1 )
	{
		AfxMessageBox(_T("No segments selected. Please select and try again"));
		return false;
	}

	// all of the selection should be segments-only
	char type[MVO_BUFFER_SIZE];
	for (int j = 0; j < n_sel; j++ )
	{
		// assume it's a segment
		HC_KEY key = sel_set->GetAt(j);
		HC_Show_Key_Type(key, type);
		if (!strstr(type, "segment"))
		{
			AfxMessageBox(_T("Only segments must be selected. Please try again"));
			return false;
		}
	}

	return true;
}


void MaterialPropertiesDlg::OnMaterialapply() 
{

	UpdateData(TRUE);
	
	CString fc_specs;
	if( !get_face_color_specs(fc_specs) )
	    return;
	
	if (m_bFirst)
	{
	    m_bFirst = false;
	    
	    HSelectionSet * sel_set = m_pHView->GetSelection();
	    assert(sel_set);
	    m_SelNum = sel_set->GetSize();
	    m_pSelectionList = new HC_KEY[m_SelNum];
	    for (int i = 0; i < m_SelNum; i++ )
		m_pSelectionList[i] = sel_set->GetAt(i);
	    sel_set->DeSelectAll();
	    m_pHView->Update();
	}


	for (int j = 0; j < m_SelNum; j++ )
	{
		// assume it's a segment
		HC_Open_Segment_By_Key( m_pSelectionList[j] );
		    if (HC_Show_Existence("color"))
			HC_UnSet_Color();
			HC_Set_Color(H_ASCII_TEXT(fc_specs));
		HC_Close_Segment();
	}
	m_pHView->Update();
	
}


void MaterialPropertiesDlg::OnSelchangeComboTextureType() 
{
	UpdateData(TRUE);
	update_texture_controls();
	UpdateData(FALSE);
}




/////////////////////////////////////////////////////////////////////////////
// CameraNearLimitDlg dialog


CameraNearLimitDlg::CameraNearLimitDlg(HBaseView * pHView, CWnd* pParent /*=NULL*/)
	: CDialog(CameraNearLimitDlg::IDD, pParent)
{
	m_pHView = pHView;
	//{{AFX_DATA_INIT(CameraNearLimitDlg)
	m_fCameraNearLimit = 0.0f;
	m_fLightScaleFactor = 1.0f;
	//}}AFX_DATA_INIT
}


void CameraNearLimitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CameraNearLimitDlg)
	DDX_Text(pDX, IDC_EDIT_CAMERA_NEAR_LIMIT, m_fCameraNearLimit);
	DDX_Text(pDX, IDC_EDIT_LIGHT_SCALE_FACTOR, m_fLightScaleFactor);
	DDV_MinMaxFloat(pDX, m_fCameraNearLimit, -1.f, 1.f);
	DDV_MinMaxFloat(pDX, m_fLightScaleFactor, 0.1f, 100.f);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CameraNearLimitDlg, CDialog)
	//{{AFX_MSG_MAP(CameraNearLimitDlg)
	ON_BN_CLICKED(IDAPPLY, OnApply)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CameraNearLimitDlg message handlers

BOOL CameraNearLimitDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_fCameraNearLimit=CAppSettings::NearCameraLimit/100000.f;
	m_fLightScaleFactor=CAppSettings::LightScaleFactor/100000.f;
	
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CameraNearLimitDlg::OnApply() 
{
	BOOL result = UpdateData(TRUE);

	if( result )
	{
		CAppSettings::NearCameraLimit = m_fCameraNearLimit*100000;
		CAppSettings::LightScaleFactor = m_fLightScaleFactor*100000;

		HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
			HC_Set_Camera_Near_Limit(m_fCameraNearLimit);
		HC_Close_Segment();
		m_pHView->Update();
	}
}


void CameraNearLimitDlg::OnOK() 
{
	OnApply();
	CDialog::OnOK();
}
