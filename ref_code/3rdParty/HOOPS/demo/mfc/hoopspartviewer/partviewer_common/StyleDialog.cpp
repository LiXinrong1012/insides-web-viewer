// StyleDialog.cpp : implementation file
//
#include "stdafx.h"
#include "resource.h"
#include "StyleDialog.h"
#include "HoopsStyle.h"
#include "HUtilityLocaleString.h"
// MVO includes
#include "HBaseView.h"
#include "HSSelectionSet.h"
#include "HIOManager.h"

#include "TextInput.h"
#include "MainStyleWindow.h"
#include "SelectStyleWindow.h"
#include "ImageViewer.h"


 
/////////////////////////////////////////////////////////////////////////////
// CStyleDialog dialog


CStyleDialog::CStyleDialog(HBaseView * view, CWnd* pParent /*=NULL*/)
	: CDialog(CStyleDialog::IDD, pParent)
{
	m_pHView = view;
	m_CurrentlySelectedTexture = "";
	//{{AFX_DATA_INIT(CStyleDialog)
 	m_StyleName = _T("");
	m_FaceGloss = _T("");
	m_FaceTransmissionEditString = _T("");
	m_FaceMirrorEditString = _T("");
	m_ValueScaleMin = _T("");
 	m_ValueScaleMax = _T("");
	m_TextureScaleX = _T("");
	m_TextureScaleY = _T("");
	m_TextureScaleZ = _T("");
	m_bDownSampling = TRUE;
 	//}}AFX_DATA_INIT
}

CStyleDialog::~CStyleDialog()
{
    delete m_SelectedStyleWindow;   
    delete m_SelectStylesWindow;   
    delete m_ImageDisplayWindow;   
    
}
void CStyleDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStyleDialog)
	DDX_Control(pDX, IDC_MARKER_VISIBILITY_COMBO, m_MarkerVisibilityC);
	DDX_Control(pDX, IDC_LINE_VISIBILITY_COMBO, m_LineVisibilityC);
	DDX_Control(pDX, IDC_EDGE_VISIBILITY_COMBO, m_EdgeVisibilityC);
	DDX_Control(pDX, IDC_FACE_VISIBILITY_COMBO, m_FaceVisibilityC);
	DDX_Control(pDX, IDC_BUTTON_DIFFUSE_FACE_COLOR2, m_DiffuseFaceColor2);
	DDX_Control(pDX, IDC_VALUE_SCALE_MIN_EDIT, m_ValueScaleMinEdit);
	DDX_Control(pDX, IDC_VALUE_SCALE_MIN_EDIT2, m_TextureScaleXEdit);
	DDX_Control(pDX, IDC_VALUE_SCALE_MIN_EDIT3, m_TextureScaleYEdit);
	DDX_Control(pDX, IDC_VALUE_SCALE_MIN_EDIT4, m_TextureScaleZEdit);
	DDX_Control(pDX, IDC_VALUE_SCALE_MAX_EDIT, m_ValueScaleMaxEdit);
	DDX_Control(pDX, IDC_SCROLLBAR1, m_StyleScrollbar);
	DDX_Control(pDX, IDC_BUTTON_DIFFUSE_LIGHT_COLOR, m_DiffuseLightColor);
	DDX_Control(pDX, IDC_BUTTON_SPECULAR_LIGHT_COLOR, m_SpecularLightColor);
	DDX_Control(pDX, IDC_BUTTON_TRANSMISSION_MARKER_COLOR, m_TransmissionMarkerColor);
	DDX_Control(pDX, IDC_BUTTON_SPECULAR_MARKER_COLOR, m_SpecularMarkerColor);
	DDX_Control(pDX, IDC_BUTTON_DIFFUSE_MARKER_COLOR, m_DiffuseMarkerColor);
	DDX_Control(pDX, IDC_BUTTON_TRANSMISSION_EDGE_COLOR, m_TransmissionEdgeColor);
	DDX_Control(pDX, IDC_BUTTON_TRANSMISSION_LINE_COLOR, m_TransmissionLineColor);
	DDX_Control(pDX, IDC_BUTTON_SPECULAR_LINE_COLOR, m_SpecularLineColor);
	DDX_Control(pDX, IDC_BUTTON_DIFFUSE_LINE_COLOR, m_DiffuseLineColor);
	DDX_Control(pDX, IDC_BUTTON_SPECULAR_EDGE_COLOR, m_SpecularEdgeColor);
	DDX_Control(pDX, IDC_BUTTON_DIFFUSE_EDGE_COLOR, m_DiffuseEdgeColor);
	DDX_Control(pDX, IDC_BUTTON_TRANSMISSION_FACE_COLOR, m_TransmissionFaceColor);
	DDX_Control(pDX, IDC_BUTTON_SPECULAR_FACE_COLOR, m_SpecularFaceColor);
	DDX_Control(pDX, IDC_BUTTON_EMISSION_FACE_COLOR, m_EmissionFaceColor);
	DDX_Control(pDX, IDC_PLACEHOLDER3, m_ImageViewerWindow);
	DDX_Control(pDX, IDC_BUTTON_DIFFUSE_FACE_COLOR, m_DiffuseFaceColor);
	DDX_Control(pDX, IDC_PLACEHOLDER2, m_SelectStyleWindow);
	DDX_Control(pDX, IDC_PLACEHOLDER, m_MainStyleWindow);
	DDX_Text(pDX, IDC_STYLE_NAME, m_StyleName);
	DDX_Text(pDX, IDC_FACE_GLOSS, m_FaceGloss);
	DDX_Text(pDX, IDC_FACE_TRANSMISSON_EDIT, m_FaceTransmissionEditString);
	DDX_Text(pDX, IDC_FACE_MIRROR_EDIT, m_FaceMirrorEditString);
	DDX_Text(pDX, IDC_VALUE_SCALE_MIN_EDIT, m_ValueScaleMin);
	DDX_Text(pDX, IDC_VALUE_SCALE_MIN_EDIT2, m_TextureScaleX);
	DDX_Text(pDX, IDC_VALUE_SCALE_MIN_EDIT3, m_TextureScaleY);
	DDX_Text(pDX, IDC_VALUE_SCALE_MIN_EDIT4, m_TextureScaleZ);
	DDX_Text(pDX, IDC_VALUE_SCALE_MAX_EDIT, m_ValueScaleMax);
	DDX_Check(pDX, IDC_DOWNSAMPLING_CHECKBOX, m_bDownSampling);
	//}}AFX_DATA_MAP
	DDX_SliderButtonCtrl(pDX, IDC_FACE_TRANSMISSON_EDIT, m_Face_Transmission_Edit, 0);
	DDX_SliderButtonCtrl(pDX, IDC_FACE_MIRROR_EDIT, m_Face_Mirror_Edit, 0);
	DDX_SliderButtonCtrl(pDX, IDC_FACE_GLOSS, m_Face_Gloss_Edit, 0);

	DDX_Control(pDX, IDC_SCALE_SLIDER, m_ScaleSlider);
	DDX_Control(pDX, IDC_ROTATION_SLIDER, m_RotateSlider);
}


BEGIN_MESSAGE_MAP(CStyleDialog, CDialog)
	//{{AFX_MSG_MAP(CStyleDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_LOAD_IMAGE, OnLoadImage)
	ON_BN_CLICKED(IDC_RESET_TEXTURE_MATRIX, OnResetTextureMatrix)
	ON_CBN_SELCHANGE(IDC_TEXTURE_SELECTOR_COMBO, OnSelchangeTextureSelectorCombo)
	ON_CBN_SELCHANGE(IDC_PARAMETERIZATION_SOURCE, OnSelchangeParameterizationSource)
	ON_CBN_SELCHANGE(IDC_INTERPOLATION_FILTER, OnSelchangeInterpolationFilter)
	ON_CBN_SELCHANGE(IDC_IMAGE_NAME_COMBO, OnSelchangeImageNameCombo)
	ON_BN_CLICKED(IDC_BUTTON_DIFFUSE_FACE_COLOR, OnButtonDiffuseFaceColor)    
	ON_CBN_SELCHANGE(IDC_TSELECTOR_DIFFUSE_FACE_COMBO, OnSelchangeTselectorDiffuseFaceCombo)
 	ON_CBN_SELCHANGE(IDC_TSELECTOR_DIFFUSE_FACE_COMBO2, OnSelchangeTselectorDiffuseFaceCombo2)
 	ON_CBN_SELCHANGE(IDC_TSELECTOR_SPECULAR_FACE_COMBO, OnSelchangeTselectorSpecularFaceCombo)
	ON_CBN_SELCHANGE(IDC_TSELECTOR_ENVIRONMENT_FACE_COMBO, OnSelchangeTselectorEnvironmentFaceCombo)
	ON_CBN_SELCHANGE(IDC_TSELECTOR_BUMP_FACE_COMBO, OnSelchangeTselectorBumpFaceCombo)
	ON_BN_CLICKED(IDC_BUTTON_STYLE_SELECTION, OnButtonStyleSelection)
	ON_CBN_SELCHANGE(IDC_GEOM_TYPE_SELECTOR, OnSelchangeGeomTypeSelector)
	ON_BN_CLICKED(IDC_LOAD_STYLES, OnLoadStyles)
	ON_BN_CLICKED(IDC_SAVE_STYLES, OnSaveStyles)
	ON_WM_HSCROLL()
 	ON_WM_KEYDOWN()
	ON_BN_CLICKED(IDC_NEW_STYLE, OnNewStyle)
	ON_BN_CLICKED(IDC_CLONE_STYLE, OnCloneStyle)
	ON_CBN_SELCHANGE(IDC_SELECTOR_FRONTBACK, OnSelchangeSelectorFrontback)
	ON_EN_UPDATE(IDC_FACE_GLOSS, OnUpdateFaceGloss)
	ON_EN_KILLFOCUS(IDC_FACE_GLOSS, OnKillfocusFaceGloss)
	ON_WM_KEYDOWN()
	ON_BN_CLICKED(IDC_DELETE_STYLE, OnDeleteStyle)
	ON_CBN_SELCHANGE(IDC_TEX_LAYOUT, OnSelchangeTexLayout)
	ON_CBN_SELCHANGE(IDC_TEX_BLENDING_MODE, OnSelchangeTexBlendingMode)
	ON_CBN_SELCHANGE(IDC_TEX_TILING, OnSelchangeTexTiling)
	ON_BN_CLICKED(IDC_CLONE_TEXTURE, OnCloneTexture)
	ON_EN_CHANGE(IDC_FACE_TRANSMISSON_EDIT, OnChangeFaceTransmissonEdit)
	ON_EN_CHANGE(IDC_FACE_GLOSS, OnChangeFaceGloss)
	ON_EN_CHANGE(IDC_FACE_MIRROR_EDIT, OnChangeFaceMirrorEdit)
	ON_EN_CHANGE(IDC_VALUE_SCALE_MIN_EDIT, OnChangeValueScaleMinEdit)
	ON_EN_CHANGE(IDC_VALUE_SCALE_MAX_EDIT, OnChangeValueScaleMaxEdit)
	ON_CBN_SELCHANGE(IDC_DECIMATION_FILTER, OnSelchangeDecimationFilter)
	ON_BN_CLICKED(IDC_DOWNSAMPLING_CHECKBOX, OnDownsamplingCheckbox)
	ON_BN_CLICKED(IDC_GET_STYLE, OnGetStyle)
	ON_BN_CLICKED(IDC_RENAME_STYLE, OnRenameStyle)
	ON_BN_CLICKED(IDC_DELETE_IMAGE, OnDeleteImage)
	ON_BN_CLICKED(IDC_DELETE_TEXTURE, OnDeleteTexture)
	ON_CBN_CLOSEUP(IDC_FACE_VISIBILITY_COMBO, OnCloseupFaceVisibilityCombo)
	ON_CBN_CLOSEUP(IDC_EDGE_VISIBILITY_COMBO, OnCloseupEdgeVisibilityCombo)
	ON_CBN_CLOSEUP(IDC_LINE_VISIBILITY_COMBO, OnCloseupLineVisibilityCombo)
	ON_CBN_CLOSEUP(IDC_MARKER_VISIBILITY_COMBO, OnCloseupMarkerVisibilityCombo)
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_VALUE_SCALE_MIN_EDIT2, &CStyleDialog::OnEnChangeValueScaleMinEdit2)
	ON_EN_CHANGE(IDC_VALUE_SCALE_MIN_EDIT3, &CStyleDialog::OnEnChangeValueScaleMinEdit3)
	ON_EN_CHANGE(IDC_VALUE_SCALE_MIN_EDIT4, &CStyleDialog::OnEnChangeValueScaleMinEdit4)
END_MESSAGE_MAP()

 
 




void CStyleDialog::LoadImageFromDisk()
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

	CString TextureSourceShortName;
	if (my_dlg.DoModal() == IDOK)
	{
		m_csTextureSourceFile = my_dlg.GetPathName();
		TextureSourceShortName = my_dlg.GetFileName();
		if (TextureSourceShortName.Find(_T(".")) != -1)
		    TextureSourceShortName = TextureSourceShortName.Left(TextureSourceShortName.Find(_T(".")));
	}

    if( m_csTextureSourceFile.IsEmpty() )
    {
 		return;
    }

    bool b_ret = true;
    HC_KEY image_key = INVALID_KEY;

    // create a scratch scratch segment to read the source file
    HC_Open_Segment_By_Key( m_pHView->GetModelKey() );       
 	        HC_KEY temp_seg = HC_KOpen_Segment("");
		HC_Set_Visibility("everything = off");
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
		input_options.m_bLocal = true;
		char imagename[MVO_BUFFER_SIZE];
		strcpy(imagename, H_ASCII_TEXT(TextureSourceShortName));
		input_options.m_pImageName = imagename;
		HFileInputResult result = InputFail;
			
		if (reader) {
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

    if (streq(file_ext, "hsf") || streq(file_ext,"hmf") && b_ret)
    {
 		HC_Open_Segment_By_Key(temp_seg);
	    HC_Begin_Contents_Search("...", "images");
	    HC_KEY key;
	    while (HUtility::FindContents(key))
	    {
		char imagename[MVO_BUFFER_SIZE];
		strcpy(imagename,"");
		HoopsTexture::GetImageName(key, imagename);
 		CString in = H_ASCII_TEXT(imagename);
		if (in == "")
			generate_unique_name(in);

		CopyImages(key, in);
	    }
	    HC_End_Contents_Search();
	    HC_Close_Segment();		
    }
    else
    {    
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
      	b_ret = (bool)MoveImages(image_key, TextureSourceShortName);
    }
    }
    HC_Delete_By_Key(temp_seg);

    return;
}





bool CStyleDialog::CopyImages(HC_KEY image_key, CString name)
{
    
// copy this image to TEXTURE_DATA_SEGMENT with a unique name
    float position[3];
    int   size[2];
    char  fmt[MVO_BUFFER_SIZE];
    HPixelRGBA * image_data;
    
    HC_Show_Image_Size( image_key, &position[0], &position[1], &position[2],
	fmt, &size[0], &size[1]);

    image_data = new HPixelRGBA[size[0] * size[1]];
    HC_Show_Image( image_key, &position[0], &position[1], &position[2],
	fmt, &size[0], &size[1], image_data);
    HC_Delete_By_Key(image_key);
    // DAMN. Can't even get something as simple as the format of the image that easy
    CString image_specs(fmt);
    int name_index = image_specs.Find( ',' );
    if( name_index != -1 )
	image_specs = image_specs.Left( name_index  );	// get everything except name 
 
    CString image_name = name;
     image_specs = image_specs + ", local, name = " + image_name;	// attach new name    
    // we have the image data, insert in our TEXTURE_DATA_SEGMENT
    HoopsStyle *currentstyle = m_SelectedStyleWindow->GetStyle();
    HC_Open_Segment_By_Key(currentstyle->GetStyleLibrary()->GetTextureKey());
   
    HC_Insert_Image( position[0], position[1], position[2], H_ASCII_TEXT(image_specs), size[0], size[1], image_data );
     // define a texture with this image and chosen parameters
    CString texture_name, texture_specs;
    texture_name = image_name;
    texture_name.MakeLower();
    texture_specs.Format(_T("source = %s, parameter source = world, down-sampling = on, decimation filter = mipmap,  value scale = (0.0,1.0), tiling = repeat"), image_name);
    HC_Set_Rendering_Options ("perspective correction");
    HC_Define_Local_Texture( H_ASCII_TEXT(texture_name), H_ASCII_TEXT(texture_specs));
    CString tname = "faces = (diffuse = red " + texture_name + ", specular = grey)";
     m_CurrentlySelectedTexture = texture_name;
    HC_Close_Segment();
    
  
    delete [] image_data;
    return true;
    
}

bool CStyleDialog::MoveImages(HC_KEY image_key, CString name)
{
    
// copy this image to TEXTURE_DATA_SEGMENT with a unique name
    float position[3];
    int   size[2];
    char  fmt[MVO_BUFFER_SIZE];
     
    HC_Show_Image_Size( image_key, &position[0], &position[1], &position[2],
	fmt, &size[0], &size[1]);

     // DAMN. Can't even get something as simple as the format of the image that easy
    CString image_specs(fmt);
    int name_index = image_specs.Find( ',' );
    if( name_index != -1 )
	image_specs = image_specs.Left( name_index  );	// get everything except name 
 
    CString image_name = name;
     image_specs = image_specs + ", local, name = " + image_name;	// attach new name    
    // we have the image data, insert in our TEXTURE_DATA_SEGMENT
    HoopsStyle *currentstyle = m_SelectedStyleWindow->GetStyle();
    HC_Open_Segment_By_Key(currentstyle->GetStyleLibrary()->GetTextureKey());
    char tempimagename[4096];
    char tempimagename2[4096];
    HoopsTexture::GetImageName(image_key,tempimagename);
    HC_KEY tempimagekey;
    bool clash = false;
    HC_Begin_Contents_Search(".", "images");
    while (HUtility::FindContents(tempimagekey))
    {
        HoopsTexture::GetImageName(tempimagekey,tempimagename2);
	if (strcmp(tempimagename, tempimagename2) == 0)
	    clash = true;

    }
    HC_End_Contents_Search();
    if (!clash)
	HC_Move_By_Key(image_key,".");
    else
	HC_Delete_By_Key(image_key);
      // define a texture with this image and chosen parameters
    CString texture_name, texture_specs;
    texture_name = image_name;
    texture_name.MakeLower();
    texture_specs.Format(_T("source = %s, parameter source = world, down-sampling = on, decimation filter = mipmap,  value scale = (0.0,1.0), tiling = repeat"), image_name);
    HC_Set_Rendering_Options ("perspective correction");
    HC_Define_Local_Texture( H_ASCII_TEXT(texture_name), H_ASCII_TEXT(texture_specs));
    CString tname = "faces = (diffuse = red " + texture_name + ", specular = grey)";
     m_CurrentlySelectedTexture = texture_name;
    HC_Close_Segment();
    
  
     return true;
    
}



BOOL CStyleDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	 CRect r;
	CString windowclass =  AfxRegisterWndClass(CS_OWNDC|CS_DBLCLKS|CS_HREDRAW|CS_VREDRAW);


        m_SelectStyleWindow.GetWindowRect(&r);
	ScreenToClient(&r);
 
	m_SelectStylesWindow = new SelectStyleWindow(this, m_pHView);
	m_SelectStylesWindow->Create(windowclass,_T("Test2"), WS_CHILD | WS_VISIBLE | WS_OVERLAPPED, r, this, 3457,0);
	m_SelectStylesWindow->ShowWindow(SW_SHOW);

        m_ImageViewerWindow.GetWindowRect(&r);
	ScreenToClient(&r);
 
	m_ImageDisplayWindow = new CImageViewer(this);
	m_ImageDisplayWindow->Create(windowclass,_T("Test3"), WS_CHILD | WS_VISIBLE | WS_OVERLAPPED, r, this, 3458,0);
	m_ImageDisplayWindow->ShowWindow(SW_SHOW);


         m_MainStyleWindow.GetWindowRect(&r);
	ScreenToClient(&r);
 
	m_SelectedStyleWindow = new MainStyleWindow(m_SelectStylesWindow->GetStyleLibrary());
	m_SelectedStyleWindow->Create(windowclass,_T("Test"), WS_CHILD | WS_VISIBLE | WS_OVERLAPPED, r, this, 3456,0);
	m_SelectedStyleWindow->ShowWindow(SW_SHOW);


	if (m_SelectStylesWindow->GetCurrentStyle())
	{
		m_SelectedStyleWindow->SetStyle(m_SelectStylesWindow->GetCurrentStyle());
		SetMainStyle(m_SelectStylesWindow->GetCurrentStyle());

	}
   

	GatherColorData();
	UpdateVisibility();
	CComboBox *cbox = (CComboBox *)GetDlgItem(IDC_GEOM_TYPE_SELECTOR);
	cbox->SetCurSel(2);
 
	cbox = (CComboBox *)GetDlgItem(IDC_SELECTOR_FRONTBACK);
	cbox->SetCurSel(0);
	m_bFrontBack = FACES_COLOR;
	m_SelectedStyleWindow->UpdateWindow();
//	Create(IDD_QUERYDIALOG);
	// TODO: Add extra initialization here
	m_StyleScrollbar.SetScrollRange(0,m_SelectStylesWindow->GetStyleNum()-1);	
	m_DiffuseFaceColor.SetParentDialog(this);
	m_DiffuseFaceColor2.SetParentDialog(this);
	m_SpecularFaceColor.SetParentDialog(this);
	m_EmissionFaceColor.SetParentDialog(this);
 	m_TransmissionFaceColor.SetParentDialog(this);
	m_DiffuseEdgeColor.SetParentDialog(this);
	m_SpecularEdgeColor.SetParentDialog(this);
 	m_TransmissionEdgeColor.SetParentDialog(this);
	m_DiffuseLineColor.SetParentDialog(this);
	m_SpecularLineColor.SetParentDialog(this);
 	m_TransmissionLineColor.SetParentDialog(this);
	m_DiffuseMarkerColor.SetParentDialog(this);
	m_SpecularMarkerColor.SetParentDialog(this);
 	m_TransmissionMarkerColor.SetParentDialog(this);
	m_DiffuseLightColor.SetParentDialog(this);
	m_SpecularLightColor.SetParentDialog(this);

	m_Face_Gloss_Edit.SetRange (1, 100);
	GatherColorData();

 	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CStyleDialog::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
}

void CStyleDialog::SetMainStyle(HoopsStyle *style)
{
    m_SelectedStyleWindow->SetStyle(style);
    m_SelectStylesWindow->SetStyle(style);
    m_SelectedStyleWindow->UpdateWindow();
    GatherColorData();
    UpdateTexturePane();    
    UpdateVisibility();

	UpdateTextureMatrixSliders();
    UpdateData(true);
    
    char sname[MVO_BUFFER_SIZE];
    strcpy(sname,"");

    if (style)
	style->GetName(sname);
    m_StyleName = H_TEXT(sname);
    UpdateData(false);

    HC_Update_Display();
}




bool CStyleDialog::generate_unique_name(CString& retNewName)
{
	time_t ltime;
	time( &ltime );
	retNewName.Format(_T("m-%ld"), ltime );
	return true;
}

static void GetColor(HoopsStyle *currentstyle, HPoint *rgb, char *type, char *channel)
{
    ColorItem *citem = currentstyle->GetColorItem(type, channel);
	if (citem->m_bColorSet)
		rgb->Set(citem->m_color.x * 255.0f, citem->m_color.y * 255.0f, citem->m_color.z * 255.0f);
	else
		rgb->Set(0.0f,0.0f,0.0f);

}

 

void CStyleDialog::GatherColorData()
{
    HoopsStyle *currentstyle = m_SelectedStyleWindow->GetStyle();
    char text[MVO_BUFFER_SIZE];
    if (currentstyle)
    {    


    currentstyle->GatherColorData();


    ColorItem *citem;
    HPoint rgb;
    if (IsFrontCombo() == FRONT_COLOR)
    {    
    GetColor(currentstyle, &rgb, "front", "diffuse");
    m_DiffuseFaceColor.currentcolor = RGB(rgb.x, rgb.y, rgb.z);
    m_DiffuseFaceColor.Invalidate();

    GetColor(currentstyle, &rgb, "front", "diffuse2");
    m_DiffuseFaceColor2.currentcolor = RGB(rgb.x, rgb.y, rgb.z);
    m_DiffuseFaceColor2.Invalidate();

	GetColor(currentstyle, &rgb, "front", "specular");
     m_SpecularFaceColor.currentcolor = RGB(rgb.x, rgb.y, rgb.z);
    m_SpecularFaceColor.Invalidate();

	GetColor(currentstyle, &rgb, "front", "emission");
     m_EmissionFaceColor.currentcolor = RGB(rgb.x, rgb.y, rgb.z);
    m_EmissionFaceColor.Invalidate();


    citem = currentstyle->GetColorItem("faces", "mirror");
    m_FaceMirrorEditString.Format(_T("%d"), (int)((float)citem->m_color.x * 100.0f));
  
	GetColor(currentstyle, &rgb, "front", "transmission");
     m_TransmissionFaceColor.currentcolor = RGB(rgb.x, rgb.y, rgb.z);
    m_TransmissionFaceColor.Invalidate();
    }
    else if (IsFrontCombo() == FACES_COLOR)
    {    
	GetColor(currentstyle, &rgb, "faces", "diffuse");
    m_DiffuseFaceColor.currentcolor = RGB(rgb.x, rgb.y, rgb.z);
    m_DiffuseFaceColor.Invalidate();

	GetColor(currentstyle, &rgb, "faces", "diffuse2");
    m_DiffuseFaceColor2.currentcolor = RGB(rgb.x, rgb.y, rgb.z);
    m_DiffuseFaceColor2.Invalidate();

	GetColor(currentstyle, &rgb, "faces", "specular");
    m_SpecularFaceColor.currentcolor = RGB(rgb.x, rgb.y, rgb.z);
    m_SpecularFaceColor.Invalidate();

	GetColor(currentstyle, &rgb, "faces", "emission");
    m_EmissionFaceColor.currentcolor = RGB(rgb.x, rgb.y, rgb.z);
    m_EmissionFaceColor.Invalidate();


    citem = currentstyle->GetColorItem("faces", "mirror");
    m_FaceMirrorEditString.Format(_T("%d"), (int)((float)citem->m_color.x * 100.0f));
 
    citem = currentstyle->GetColorItem("faces", "transmission");
    rgb.Set(citem->m_color.x * 255.0f, citem->m_color.y * 255.0f, citem->m_color.z * 255.0f);
    m_TransmissionFaceColor.currentcolor = RGB(rgb.x, rgb.y, rgb.z);
    m_FaceTransmissionEditString.Format(_T("%d"), (int)((float)citem->m_color.x * 100.0f));
    m_TransmissionFaceColor.Invalidate();

    citem = currentstyle->GetColorItem("faces", "gloss");
    sprintf(text, "%d", (int)citem->m_color.x);
    m_FaceGloss = H_TEXT(text);
    UpdateData(false);
     
    }
    else
    {    
	GetColor(currentstyle,&rgb, "back", "diffuse");
    m_DiffuseFaceColor.currentcolor = RGB(rgb.x, rgb.y, rgb.z);
    m_DiffuseFaceColor.Invalidate();

 	GetColor(currentstyle,&rgb, "back", "diffuse2");
    m_DiffuseFaceColor2.currentcolor = RGB(rgb.x, rgb.y, rgb.z);
    m_DiffuseFaceColor2.Invalidate();

 	GetColor(currentstyle,&rgb, "back", "specular");
    m_SpecularFaceColor.currentcolor = RGB(rgb.x, rgb.y, rgb.z);
    m_SpecularFaceColor.Invalidate();

 	GetColor(currentstyle,&rgb, "back", "emission");
    m_EmissionFaceColor.currentcolor = RGB(rgb.x, rgb.y, rgb.z);
    m_EmissionFaceColor.Invalidate();


    citem = currentstyle->GetColorItem("back", "mirror");
    m_FaceMirrorEditString.Format(_T("%d"), (int)((float)citem->m_color.x * 100.0f));
 
 	GetColor(currentstyle,&rgb, "back", "transmission");
    m_TransmissionFaceColor.currentcolor = RGB(rgb.x, rgb.y, rgb.z);
    m_TransmissionFaceColor.Invalidate();
    }

 	GetColor(currentstyle,&rgb, "edges", "diffuse");
    m_DiffuseEdgeColor.currentcolor = RGB(rgb.x, rgb.y, rgb.z);
    m_DiffuseEdgeColor.Invalidate();

 	GetColor(currentstyle,&rgb, "edges", "specular");
    m_SpecularEdgeColor.currentcolor = RGB(rgb.x, rgb.y, rgb.z);
    m_SpecularEdgeColor.Invalidate();

 	GetColor(currentstyle,&rgb, "edges", "transmission");
    m_TransmissionEdgeColor.currentcolor = RGB(rgb.x, rgb.y, rgb.z);
    m_TransmissionEdgeColor.Invalidate();

 	GetColor(currentstyle,&rgb, "lines", "diffuse");
    m_DiffuseLineColor.currentcolor = RGB(rgb.x, rgb.y, rgb.z);
    m_DiffuseLineColor.Invalidate();

 	GetColor(currentstyle,&rgb, "lines", "specular");
    m_SpecularLineColor.currentcolor = RGB(rgb.x, rgb.y, rgb.z);
    m_SpecularLineColor.Invalidate();

 	GetColor(currentstyle,&rgb, "lines", "transmission");
    m_TransmissionLineColor.currentcolor = RGB(rgb.x, rgb.y, rgb.z);
    m_TransmissionLineColor.Invalidate();


 	GetColor(currentstyle,&rgb, "markers", "diffuse");
    m_DiffuseMarkerColor.currentcolor = RGB(rgb.x, rgb.y, rgb.z);
    m_DiffuseMarkerColor.Invalidate();

 	GetColor(currentstyle,&rgb, "markers", "specular");
    m_SpecularMarkerColor.currentcolor = RGB(rgb.x, rgb.y, rgb.z);
    m_SpecularMarkerColor.Invalidate();

 	GetColor(currentstyle,&rgb, "markers", "transmission");
    m_TransmissionMarkerColor.currentcolor = RGB(rgb.x, rgb.y, rgb.z);
    m_TransmissionMarkerColor.Invalidate();

 	GetColor(currentstyle,&rgb, "lights", "diffuse");
    m_DiffuseLightColor.currentcolor = RGB(rgb.x, rgb.y, rgb.z);
    m_DiffuseLightColor.Invalidate();

 	GetColor(currentstyle,&rgb, "lights", "specular");
    m_SpecularLightColor.currentcolor = RGB(rgb.x, rgb.y, rgb.z);
    m_SpecularLightColor.Invalidate();

    }
    UpdateData(false);

}


void CStyleDialog::SelectTexture(CString texname)
{
    CComboBox *cbox = (CComboBox *)GetDlgItem(IDC_TEXTURE_SELECTOR_COMBO);

    if (texname == "" || cbox->FindString(-1,texname) == CB_ERR)
    {
	cbox->SetCurSel(0); 
	int index = cbox->GetCurSel();
	if (index != CB_ERR)
	    cbox->GetLBText(index, m_CurrentlySelectedTexture);	
    }
    else
    {
	int sel = cbox->FindString(-1,texname);
	cbox->SetCurSel(sel);
	m_CurrentlySelectedTexture = texname;
    }
}




void CStyleDialog::OnLoadImage() 
{
    LoadImageFromDisk();
    m_SelectedStyleWindow->GetStyle()->GatherTextureData();
    UpdateTexturePane();
 	// TODO: Add your control notification handler code here
	
}

void CStyleDialog::UpdateParamSource(HoopsStyle *style)
{
	HoopsTexture *tex = style->GetTextureByName(H_ASCII_TEXT(m_CurrentlySelectedTexture));
        CComboBox *cbox = (CComboBox *)GetDlgItem(IDC_PARAMETERIZATION_SOURCE);

	if (tex)
	{
 	    int sel = cbox->FindString(-1,H_TEXT(tex->GetParameterizationSource()));
	    cbox->SetCurSel(sel);
	}
	else
	{
	    int sel = cbox->FindString(-1,_T("<emtpy>"));
	    cbox->SetCurSel(sel);
	}

	

}
void CStyleDialog::UpdateInterpolationFilter(HoopsStyle *style)
{
	HoopsTexture *tex = style->GetTextureByName(H_ASCII_TEXT(m_CurrentlySelectedTexture));
        CComboBox *cbox = (CComboBox *)GetDlgItem(IDC_INTERPOLATION_FILTER);
	if (tex)
	{
 	    int sel = cbox->FindString(-1,H_TEXT(tex->GetInterpolationFilter()));
	    cbox->SetCurSel(sel);
	}
	else
	{
	    int sel = cbox->FindString(-1,_T("<emtpy>"));
	    cbox->SetCurSel(sel);

	}

}
void CStyleDialog::UpdateDecimationFilter(HoopsStyle *style)
{
	HoopsTexture *tex = style->GetTextureByName(H_ASCII_TEXT(m_CurrentlySelectedTexture));
        CComboBox *cbox = (CComboBox *)GetDlgItem(IDC_DECIMATION_FILTER);
	if (tex)
	{
 	    int sel = cbox->FindString(-1,H_TEXT(tex->GetDecimationFilter()));
	    cbox->SetCurSel(sel);
	}
	else
	{
	    int sel = cbox->FindString(-1,_T("<emtpy>"));
	    cbox->SetCurSel(sel);

	}

}

void CStyleDialog::UpdateDownsampling(HoopsStyle *style)
{
	HoopsTexture *tex = style->GetTextureByName(H_ASCII_TEXT(m_CurrentlySelectedTexture));
        CComboBox *cbox = (CComboBox *)GetDlgItem(IDC_DECIMATION_FILTER);
		(void) cbox;
	if (tex && tex->GetDownsamplingSet())
	{
	    m_bDownSampling = tex->GetDownsampling();
	}
	else
	{
	    m_bDownSampling = true;
 
	}
	UpdateData(false);


}

void CStyleDialog::UpdateLayout(HoopsStyle *style)
{
	HoopsTexture *tex = style->GetTextureByName(H_ASCII_TEXT(m_CurrentlySelectedTexture));
        CComboBox *cbox = (CComboBox *)GetDlgItem(IDC_TEX_LAYOUT);
	if (tex)
	{
 	    int sel = cbox->FindString(-1,H_TEXT(tex->GetLayout()));
	    cbox->SetCurSel(sel);
	}
	else
	{
	    int sel = cbox->FindString(-1,_T("<emtpy>"));
	    cbox->SetCurSel(sel);

	}

}
void CStyleDialog::UpdateTiling(HoopsStyle *style)
{
	HoopsTexture *tex = style->GetTextureByName(H_ASCII_TEXT(m_CurrentlySelectedTexture));
        CComboBox *cbox = (CComboBox *)GetDlgItem(IDC_TEX_TILING);
	if (tex)
	{
 	    int sel = cbox->FindString(-1,H_TEXT(tex->GetTiling()));
	    cbox->SetCurSel(sel);
	}
	else
	{
	    int sel = cbox->FindString(-1,_T("<emtpy>"));
	    cbox->SetCurSel(sel);

	}

}

void CStyleDialog::UpdateBlendingMode(HoopsStyle *style)
{
	HoopsTexture *tex = style->GetTextureByName(H_ASCII_TEXT(m_CurrentlySelectedTexture));
        CComboBox *cbox = (CComboBox *)GetDlgItem(IDC_TEX_BLENDING_MODE);
	if (tex)
	{
 	    int sel = cbox->FindString(-1,H_TEXT(tex->GetBlendingMode()));
	    cbox->SetCurSel(sel);
	}
	else
	{
	    int sel = cbox->FindString(-1,_T("<emtpy>"));
	    cbox->SetCurSel(sel);

	}

}

void CStyleDialog::UpdateValueScale(HoopsStyle *style)
{

	HoopsTexture *tex = style->GetTextureByName(H_ASCII_TEXT(m_CurrentlySelectedTexture));
 	if (tex && tex->GetValueScaleSet())
	{
	    char text[MVO_BUFFER_SIZE];
 		sprintf(text, "%f", tex->GetValueScaleMin());
		m_ValueScaleMin = text;
		sprintf(text, "%f", tex->GetValueScaleMax());
		m_ValueScaleMax = text;
		UpdateData(false);
 
	}
	else
	{
 		m_ValueScaleMin = _T("");
  		m_ValueScaleMax = _T("");
		UpdateData(false);
	}

}

void CStyleDialog::UpdateImageName(HoopsStyle *style)
{
        CComboBox *cbox = (CComboBox *)GetDlgItem(IDC_IMAGE_NAME_COMBO);
	cbox->ResetContent();
	HC_Open_Segment_By_Key(m_SelectStylesWindow->GetStyleLibrary()->GetTextureKey());
 	HC_Begin_Contents_Search("...", "images");
	HC_KEY imagekey;
	char imagename[MVO_BUFFER_SIZE];
	while (HUtility::FindContents(imagekey))
	{
	    HoopsTexture::GetImageName(imagekey, imagename);    
	    cbox->AddString(H_TEXT(imagename));

	}
	HC_End_Contents_Search();
	HC_Close_Segment();

	
	HoopsTexture *tex = style->GetTextureByName(H_ASCII_TEXT(m_CurrentlySelectedTexture));
	if (tex)
	{
 	    int sel = cbox->FindString(-1,H_TEXT(tex->GetSource()));
	    cbox->SetCurSel(sel);
	}

	m_ImageDisplayWindow->SetImage(tex);
	

}
void CStyleDialog::OnResetTextureMatrix() 
{
    if (m_SelectedStyleWindow->GetStyle())
    {         
		HoopsStyle *style = m_SelectedStyleWindow->GetStyle();
		HC_Open_Segment_By_Key(style->GetKey());
		if (HC_Show_Existence("texture matrix"))
			HC_UnSet_Texture_Matrix();
		HC_Close_Segment();
		m_RotateSlider.SetPos(0);
		m_ScaleSlider.SetPos(50);
	}
	UpdateData(true);
	m_pHView->Update();
 	// TODO: Add your control notification handler code here
	
}


void CStyleDialog::UpdateTextureMatrixSliders()
{
	float matrix[16];
    if (m_SelectedStyleWindow->GetStyle())
    {         
		HoopsStyle *style = m_SelectedStyleWindow->GetStyle();
		HC_Open_Segment_By_Key(style->GetKey());
		if (HC_Show_Existence("texture matrix"))
		{
			HC_Show_Texture_Matrix(matrix);
			float scale = matrix[10];
			float rotate;
 			if (matrix[1] >=0)
				rotate = acos(matrix[0]/scale) * (180.0f / 3.141592);
			else
				rotate = (180.0f - acos(matrix[0]/scale) * (180.0f / 3.141592)) + 180.0f;
			m_RotateSlider.SetPos(rotate/360 * 100);
			if (scale == 1.0f)
				m_ScaleSlider.SetPos(50);
			else if (scale < 1.0f)
			{				
					m_ScaleSlider.SetPos(sqrt(scale * 2500));
			}
			else
					m_ScaleSlider.SetPos(sqrt(scale * 2500.0f));
 

 

		}
		else
		{
			m_RotateSlider.SetPos(0);
			m_ScaleSlider.SetPos(50);
		}
		HC_Close_Segment();
	}
}

void CStyleDialog::UpdateTexturePane()
{
    if (m_SelectedStyleWindow->GetStyle())
    {    
    m_SelectedStyleWindow->GetStyle()->GatherTextureData();
    
    HoopsStyle *style = m_SelectedStyleWindow->GetStyle();

    CComboBox *cbox = (CComboBox *)GetDlgItem(IDC_TEXTURE_SELECTOR_COMBO);

    cbox->ResetContent();
    style->StartTextureIteration();
    while (1)
    {
	HoopsTexture *tex = style->GetNextTexture();
	if (!tex)
	    break;
	cbox->AddString(H_TEXT(tex->GetName()));
    }
    SelectTexture(m_CurrentlySelectedTexture);
    
    CComboBox *pmsourcebox = (CComboBox *)GetDlgItem(IDC_PARAMETERIZATION_SOURCE);
	(void) pmsourcebox;
    UpdateParamSource(style);
    UpdateInterpolationFilter(style);
    UpdateDecimationFilter(style);
    UpdateDownsampling(style);
    UpdateLayout(style);
    UpdateTiling(style);
    UpdateBlendingMode(style);
    UpdateImageName(style);            
    UpdateValueScale(style);            
    UpdateStyleTextureCombos();
    }
     
}







void CStyleDialog::SelectStyleTexture(char *texname, int id)
{
    CComboBox *cbox = (CComboBox *)GetDlgItem(id);

    if (!texname || strcmp(texname,"") == 0 || cbox->FindString(-1,H_TEXT(texname)) == CB_ERR)
    {
	cbox->SetCurSel(0); 
    }
    else
    {
	int sel = cbox->FindString(-1,H_TEXT(texname));
	cbox->SetCurSel(sel);
    }
}


void CStyleDialog::UpdateStyleTextureCombo(int id)
{
    m_SelectedStyleWindow->GetStyle()->GatherTextureData();

    HoopsStyle *style = m_SelectedStyleWindow->GetStyle();

    CComboBox *cbox = (CComboBox *)GetDlgItem(id);

    cbox->ResetContent();
    style->StartTextureIteration();
    cbox->AddString(_T("<empty>"));

    while (1)
    {
	HoopsTexture *tex = style->GetNextTexture();
	if (!tex)
	    break;
	cbox->AddString(H_TEXT(tex->GetName()));
    }


	// Find the longest string in the combo box and set the width.
	CString str;
	CSize   sz;
	int     dx=0;
	CDC*    pDC = cbox->GetDC();
 	for (int i=0;i < cbox->GetCount();i++)
	{
	   cbox->GetLBText( i, str );
	   sz = pDC->GetTextExtent(str);

	   if (sz.cx > dx)
		  dx = sz.cx;
	}
	cbox->ReleaseDC(pDC);

	// Adjust the width for the vertical scroll bar and the left and right border.
	dx += ::GetSystemMetrics(SM_CXVSCROLL) + 2*::GetSystemMetrics(SM_CXEDGE);

	// Set the width of the list box so that every item is completely visible.
	cbox->SetDroppedWidth(dx);

}
 
void CStyleDialog::UpdateStyleTextureCombos()
{
    ColorItem *citem = m_SelectedStyleWindow->GetStyle()->GetColorItem("faces", "diffuse");
    UpdateStyleTextureCombo(IDC_TSELECTOR_DIFFUSE_FACE_COMBO);
    SelectStyleTexture(citem->m_texture,IDC_TSELECTOR_DIFFUSE_FACE_COMBO);
    
    citem = m_SelectedStyleWindow->GetStyle()->GetColorItem("faces", "diffuse2");
    UpdateStyleTextureCombo(IDC_TSELECTOR_DIFFUSE_FACE_COMBO2);
    SelectStyleTexture(citem->m_texture,IDC_TSELECTOR_DIFFUSE_FACE_COMBO2);

    citem = m_SelectedStyleWindow->GetStyle()->GetColorItem("faces", "specular");
    UpdateStyleTextureCombo(IDC_TSELECTOR_SPECULAR_FACE_COMBO);
    SelectStyleTexture(citem->m_texture,IDC_TSELECTOR_SPECULAR_FACE_COMBO);

    citem = m_SelectedStyleWindow->GetStyle()->GetColorItem("faces", "environment");
    UpdateStyleTextureCombo(IDC_TSELECTOR_ENVIRONMENT_FACE_COMBO);
    SelectStyleTexture(citem->m_texture,IDC_TSELECTOR_ENVIRONMENT_FACE_COMBO);

    citem = m_SelectedStyleWindow->GetStyle()->GetColorItem("faces", "bump");
    UpdateStyleTextureCombo(IDC_TSELECTOR_BUMP_FACE_COMBO);
    SelectStyleTexture(citem->m_texture,IDC_TSELECTOR_BUMP_FACE_COMBO);
}



    

void CStyleDialog::OnSelchangeTextureSelectorCombo() 
{
	CComboBox *cbox = (CComboBox *)GetDlgItem(IDC_TEXTURE_SELECTOR_COMBO);
	int sel = cbox->GetCurSel();
 	if (sel != CB_ERR)
	    cbox->GetLBText(sel, m_CurrentlySelectedTexture);	
	UpdateTexturePane();
	
}

void CStyleDialog::OnSelchangeParameterizationSource() 
{
	HoopsStyle *style = m_SelectedStyleWindow->GetStyle();
	
	CComboBox *cbox = (CComboBox *)GetDlgItem(IDC_PARAMETERIZATION_SOURCE);
	int sel = cbox->GetCurSel();
	CString psource;
 	if (sel != CB_ERR)
	    cbox->GetLBText(sel, psource);	
	HoopsTexture *tex = style->GetTextureByName(H_ASCII_TEXT(m_CurrentlySelectedTexture));
	if (tex)
	{
		tex->SetParameterizationSource(H_ASCII_TEXT(psource));
		HC_Control_Update("/", "redraw everything");
		HC_Update_Display();
	}

}

void CStyleDialog::OnSelchangeInterpolationFilter() 
{
	HoopsStyle *style = m_SelectedStyleWindow->GetStyle();
	
	CComboBox *cbox = (CComboBox *)GetDlgItem(IDC_INTERPOLATION_FILTER);
	int sel = cbox->GetCurSel();
	CString psource;
 	if (sel != CB_ERR)
	    cbox->GetLBText(sel, psource);	
	HoopsTexture *tex = style->GetTextureByName(H_ASCII_TEXT(m_CurrentlySelectedTexture));
	if (tex)
	{
		tex->SetInterpolationFilter(H_ASCII_TEXT(psource));
		HC_Control_Update("/", "redraw everything");
		HC_Update_Display();
	}

	
}

void CStyleDialog::OnSelchangeImageNameCombo() 
{
	HoopsStyle *style = m_SelectedStyleWindow->GetStyle();
	
	CComboBox *cbox = (CComboBox *)GetDlgItem(IDC_IMAGE_NAME_COMBO);
	int sel = cbox->GetCurSel();
	CString psource;
 	if (sel != CB_ERR)
	    cbox->GetLBText(sel, psource);	
	HoopsTexture *tex = style->GetTextureByName(H_ASCII_TEXT(m_CurrentlySelectedTexture));
	if (tex)
	{
		tex->SetSource(H_ASCII_TEXT(psource));
		UpdateTexturePane();
		HC_Control_Update("/", "redraw everything");
		HC_Update_Display();
	}
}

void CStyleDialog::OnButtonDiffuseFaceColor() 
{
    int i;
    i=0;
;	// TODO: Add your control notification handler code here
	
}


void CStyleDialog::ColorButtonClicked(int id, float r, float g, float b, bool undefine)
{
    HoopsStyle *style = m_SelectedStyleWindow->GetStyle();

    if (id == IDC_BUTTON_DIFFUSE_FACE_COLOR)
    {    
	if (m_bFrontBack == FACES_COLOR)
 	    style->SetColor("faces", "diffuse", r,g,b, undefine);	
	else if (m_bFrontBack == FRONT_COLOR)
 	    style->SetColor("front", "diffuse", r,g,b, undefine);	
	else
 	    style->SetColor("back", "diffuse", r,g,b, undefine);	

	style->SetColor("cut face", "diffuse", r,g,b, undefine);	

    }
    if (id == IDC_BUTTON_DIFFUSE_FACE_COLOR2)
    {    
	if (m_bFrontBack == FACES_COLOR)
 	    style->SetColor("faces", "diffuse2", r,g,b, undefine);	
	else if (m_bFrontBack == FRONT_COLOR)
 	    style->SetColor("front", "diffuse2", r,g,b, undefine);	
	else
 	    style->SetColor("back", "diffuse2", r,g,b, undefine);	

    }
    if (id == IDC_BUTTON_SPECULAR_FACE_COLOR)
    {    
	if (IsFrontCombo() == FRONT_COLOR)
 	    style->SetColor("faces", "specular", r,g,b, undefine);	
	else 	if (IsFrontCombo() == BACK_COLOR)
 	    style->SetColor("back", "specular", r,g,b, undefine);	
	else
 	    style->SetColor("faces", "specular", r,g,b, undefine);	

    }
    if (id == IDC_BUTTON_EMISSION_FACE_COLOR)
    {    
	if (IsFrontCombo() == FRONT_COLOR)
 	    style->SetColor("faces", "emission", r,g,b, undefine);	
	else 	if (IsFrontCombo() == BACK_COLOR)
 	    style->SetColor("back", "emission", r,g,b, undefine);	
	else
 	    style->SetColor("faces", "emission", r,g,b, undefine);	

    }

    if (id == IDC_BUTTON_MIRROR_FACE_COLOR)
    {    
	if (m_bFrontBack == FACES_COLOR)
 	    style->SetColor("faces", "mirror", r,g,b, undefine);	
	else if (m_bFrontBack == FRONT_COLOR)
 	    style->SetColor("front", "mirror", r,g,b, undefine);	
	else
 	    style->SetColor("back", "mirror", r,g,b, undefine);	

	style->SetColor("cut face", "mirror", r,g,b, undefine);	

    }
    if (id == IDC_BUTTON_TRANSMISSION_FACE_COLOR)
    {    
	if (m_bFrontBack == FACES_COLOR)
 	    style->SetColor("faces", "transmission", r,g,b, undefine);	
	else if (m_bFrontBack == FRONT_COLOR)
 	    style->SetColor("front", "transmission", r,g,b, undefine);	
	else
 	    style->SetColor("back", "transmission", r,g,b, undefine);	
    }
    if (id == IDC_BUTTON_DIFFUSE_EDGE_COLOR)
    {    
 	style->SetColor("edges", "diffuse", r,g,b, undefine);	
    }
    if (id == IDC_BUTTON_SPECULAR_EDGE_COLOR)
    {    
 	style->SetColor("edges", "specular", r,g,b, undefine);	
    }
    if (id == IDC_BUTTON_TRANSMISSION_EDGE_COLOR)
    {    
 	style->SetColor("edges", "transmission", r,g,b, undefine);	
    }

    if (id == IDC_BUTTON_DIFFUSE_LINE_COLOR)
    {    
 	style->SetColor("lines", "diffuse", r,g,b, undefine);	
    }
    if (id == IDC_BUTTON_SPECULAR_LINE_COLOR)
    {    
 	style->SetColor("lines", "specular", r,g,b, undefine);	
    }
    if (id == IDC_BUTTON_TRANSMISSION_LINE_COLOR)
    {    
 	style->SetColor("lines", "transmission", r,g,b, undefine);	
    }
    
    if (id == IDC_BUTTON_DIFFUSE_MARKER_COLOR)
    {    
 	style->SetColor("markers", "diffuse", r,g,b, undefine);	
    }
    if (id == IDC_BUTTON_SPECULAR_MARKER_COLOR)
    {    
 	style->SetColor("markers", "specular", r,g,b, undefine);	
    }
    if (id == IDC_BUTTON_TRANSMISSION_MARKER_COLOR)
    {    
 	style->SetColor("markers", "transmission", r,g,b, undefine);	
    }
    if (id == IDC_BUTTON_DIFFUSE_LIGHT_COLOR)
    {    
 	style->SetColor("lights", "diffuse", r,g,b, undefine);	
    }
    if (id == IDC_BUTTON_SPECULAR_LIGHT_COLOR)
    {    
 	style->SetColor("lights", "specular", r,g,b, undefine);	
    }

 HC_Control_Update("/", "redraw everything");
	HC_Update_Display();
	GatherColorData();
}
 

void CStyleDialog::OnSelchangeTselectorDiffuseFaceCombo() 
{
	HoopsStyle *style = m_SelectedStyleWindow->GetStyle();
	
	CComboBox *cbox = (CComboBox *)GetDlgItem(IDC_TSELECTOR_DIFFUSE_FACE_COMBO);
	int sel = cbox->GetCurSel();
	CString psource;
 	if (sel != CB_ERR)
	    cbox->GetLBText(sel, psource);
	if (IsFrontCombo() == FACES_COLOR)
	    style->SetTexture("faces", "diffuse", (H_ASCII_TEXT(psource)));
	else if (IsFrontCombo() == FRONT_COLOR)
	    style->SetTexture("front", "diffuse", (H_ASCII_TEXT(psource)));
	else
	    style->SetTexture("back", "diffuse", (H_ASCII_TEXT(psource)));
    style->SetTexture("cut face", "diffuse", (H_ASCII_TEXT(psource)));

 	HC_Control_Update("/", "redraw everything");
	HC_Update_Display();
	
}


void CStyleDialog::OnSelchangeTselectorDiffuseFaceCombo2() 
{
	HoopsStyle *style = m_SelectedStyleWindow->GetStyle();
	
	CComboBox *cbox = (CComboBox *)GetDlgItem(IDC_TSELECTOR_DIFFUSE_FACE_COMBO2);
	int sel = cbox->GetCurSel();
	CString psource;
 	if (sel != CB_ERR)
	    cbox->GetLBText(sel, psource);
	if (IsFrontCombo() == FACES_COLOR)
	    style->SetTexture("faces", "diffuse2", (H_ASCII_TEXT(psource)));
	else if (IsFrontCombo() == FRONT_COLOR)
	    style->SetTexture("front", "diffuse2", (H_ASCII_TEXT(psource)));
	else
	    style->SetTexture("back", "diffuse2", (H_ASCII_TEXT(psource)));
 	HC_Control_Update("/", "redraw everything");
	HC_Update_Display();
	
}

void CStyleDialog::OnSelchangeTselectorSpecularFaceCombo() 
{
	HoopsStyle *style = m_SelectedStyleWindow->GetStyle();
	
	CComboBox *cbox = (CComboBox *)GetDlgItem(IDC_TSELECTOR_SPECULAR_FACE_COMBO);
	int sel = cbox->GetCurSel();
	CString psource;
 	if (sel != CB_ERR)
	    cbox->GetLBText(sel, psource);
	if (IsFrontCombo() == FACES_COLOR)
	    style->SetTexture("faces", "specular", (H_ASCII_TEXT(psource)));
	else if (IsFrontCombo() == FRONT_COLOR)
	    style->SetTexture("front", "specular", (H_ASCII_TEXT(psource)));
	else
	    style->SetTexture("back", "specular", (H_ASCII_TEXT(psource)));
	HC_Control_Update("/", "redraw everything");
	HC_Update_Display();
		
}

void CStyleDialog::OnSelchangeTselectorEnvironmentFaceCombo() 
{
	HoopsStyle *style = m_SelectedStyleWindow->GetStyle();
	
	CComboBox *cbox = (CComboBox *)GetDlgItem(IDC_TSELECTOR_ENVIRONMENT_FACE_COMBO);
	int sel = cbox->GetCurSel();
	CString psource;
 	if (sel != CB_ERR)
	    cbox->GetLBText(sel, psource);
	if (IsFrontCombo() == FACES_COLOR)
	    style->SetTexture("faces", "environment", (H_ASCII_TEXT(psource)));
	else if (IsFrontCombo() == FRONT_COLOR)
	    style->SetTexture("front", "environment", (H_ASCII_TEXT(psource)));
	else
	    style->SetTexture("back", "environment", (H_ASCII_TEXT(psource)));
 
    style->SetTexture("cut face", "environment", (H_ASCII_TEXT(psource)));

	  
	if (IsFrontCombo() == FACES_COLOR)
 	    style->SetColor("faces", "mirror", 1,1,1, false);	
	else if (IsFrontCombo() == FRONT_COLOR)
 	    style->SetColor("front", "mirror", 1,1,1, false);	
	else
 	    style->SetColor("back", "mirror", 1,1,1, false);	
	style->SetColor("cut face", "mirror", 1,1,1, false);	
       
    GatherColorData();
	HC_Control_Update("/", "redraw everything");
	HC_Update_Display();

	
}

void CStyleDialog::OnSelchangeTselectorBumpFaceCombo() 
{
	HoopsStyle *style = m_SelectedStyleWindow->GetStyle();
	
	CComboBox *cbox = (CComboBox *)GetDlgItem(IDC_TSELECTOR_BUMP_FACE_COMBO);
	int sel = cbox->GetCurSel();
	CString psource;
 	if (sel != CB_ERR)
	    cbox->GetLBText(sel, psource);
	if (IsFrontCombo() == FACES_COLOR)
	    style->SetTexture("faces", "bump", (H_ASCII_TEXT(psource)));
	else if (IsFrontCombo() == FRONT_COLOR)
	    style->SetTexture("front", "bump", (H_ASCII_TEXT(psource)));
	else
	    style->SetTexture("back", "bump", (H_ASCII_TEXT(psource)));
 

	         
    GatherColorData();
	HC_Control_Update("/", "redraw everything");
	HC_Update_Display();

	
}

void CStyleDialog::ApplyVisibility(char *geom, char *onoff)
{
    char text[MVO_BUFFER_SIZE];
    HC_Open_Segment_By_Key(m_SelectedStyleWindow->GetStyle()->GetKey());
	if (onoff)
	{
	    sprintf(text,"%s = %s", geom, onoff);
	    HC_Set_Visibility(text);
	}
	else
		HC_UnSet_One_Visibility(geom);
    HC_Close_Segment();
     
    HC_Update_Display();
    UpdateData(true);

}

void CStyleDialog::OnFaceVisibilityOn() 
{
     ApplyVisibility("faces", "on");
	
}

void CStyleDialog::OnFaceVisibilityOff() 
{
     ApplyVisibility("faces", "off");
	
}

void CStyleDialog::OnFaceVisibilityUndefined() 
{
     ApplyVisibility("faces", 0);
	
}

 
void CStyleDialog::UpdateOneVisibility(char *geom, CComboBox &res)
{
    HoopsStyle *style = m_SelectedStyleWindow->GetStyle();
    if (style)
    {    
    switch(style->ShowVisibility(geom))
    {
    case VISIBILITY_ON:
	res.SetCurSel(1);
	break;
    case VISIBILITY_OFF:
	res.SetCurSel(0);
	break;
    case VISIBILITY_UNDEFINED:
	res.SetCurSel(2);
	break;

    }
  
    }

    UpdateData(false);
}
void CStyleDialog::UpdateVisibility()
{
    UpdateOneVisibility("faces", m_FaceVisibilityC);
    UpdateOneVisibility("edges", m_EdgeVisibilityC);
    UpdateOneVisibility("lines", m_LineVisibilityC);
    UpdateOneVisibility("markers", m_MarkerVisibilityC);

}

void CStyleDialog::OnEdgeVisibilityOn() 
{
       ApplyVisibility("edges", "on");	
}

void CStyleDialog::OnEdgeVisibilityUndefined() 
{
     ApplyVisibility("edges", 0);	
}

void CStyleDialog::OnEdgeVisibilityOff() 
{
     ApplyVisibility("edges", "off");
}



void CStyleDialog::OnLineVisibilityOff() 
{
       ApplyVisibility("lines", "off");	
	
}

void CStyleDialog::OnLineVisibilityOn() 
{
       ApplyVisibility("lines", "on");	
	
}

void CStyleDialog::OnLineVisibilityUndefined() 
{
       ApplyVisibility("lines", 0);	
	
}

void CStyleDialog::OnMarkerVisibilityOff() 
{
       ApplyVisibility("markers", "off");	
	
}

void CStyleDialog::OnMarkerVisibilityOn() 
{
       ApplyVisibility("markers", "on");	
	
}

void CStyleDialog::OnMarkerVisibilityUndefined() 
{
       ApplyVisibility("markers", 0);	
	
}

void CStyleDialog::OnButtonStyleSelection() 
{
    HoopsStyle *style = m_SelectedStyleWindow->GetStyle();
    HSelectionSet *selection = (HSelectionSet *)m_pHView->GetSelection();

    HC_KEY *keys = new HC_KEY[selection->GetSize()];
 
    int size = selection->GetSize();
	int i;
    for (i=0;i<size;i++)
    {
		keys[i] = selection->GetAt(i);	
    }
    selection->DeSelectAll();

    for (i=0;i<size;i++)
    {
		keys[i] = HUtility::GrabSegment(keys[i]);
		HC_Open_Segment_By_Key(keys[i]);
		if (HC_Show_Existence("visibility"))
			HC_UnSet_Visibility();

		else if (HC_Show_Existence("color"))
			HC_UnSet_Color();
		HC_Close_Segment();
		style->Style(keys[i]);
    }

#ifdef ACIS

	int r=0,g=0,b=0;
	double transmission, transparency;
    ColorItem *citem, *citem_trans;

    citem = style->GetColorItem("faces", "diffuse");
	if( citem->m_bColorSet )
	{
		r = citem->m_color.x * 255;
		g = citem->m_color.y * 255;
		b = citem->m_color.z * 255;
	}

    citem_trans = style->GetColorItem("faces", "transmission");
	if( citem_trans->m_bColorSet )
	{
		transmission = citem_trans->m_color.x;
	}


	KERN_CLASS_TYPEDEF e_sel_class = ((HSSelectionSet *)m_pHView->GetSelection())->GetSelectLevel();

	if ( e_sel_class != BODY_TYPE )
	{
    	AfxMessageBox(_T("Can only set color on Body of ACIS models."));
		H_SAFE_DELETE_ARRAY( keys);
		m_pHView->Update();
		return;
	}

    for ( i= 0; i < size; i++)
	{
		HC_KEY current_key = keys[i];
//		SetColor( current_key, (float)r/255.0f, (float)g/255.0f, (float)b/255.0f );
		Color( current_key, "", 0, 0, (float)r/255.0f, (float)g/255.0f, (float)b/255.0f, true );

		ENTITY* entity = HA_Compute_Entity_Pointer(current_key, e_sel_class);
		if (entity)
		{
			//set and check color
			rgb_color acis_user_col((double)r/255.0, (double)g/255.0, (double)b/255.0);
			outcome o = api_rh_set_entity_rgb( entity, acis_user_col );
			logical inherited = FALSE;
			logical found = FALSE;
			o = api_rh_get_entity_rgb( entity, acis_user_col, inherited, found);
			CHECK_OUTCOME(o);

			//set and check transparency
			ENTITY_LIST list;
			list.add( entity, true);
			o = api_rh_set_material_transp( list, 1.0-transmission );
			o = api_rh_get_material_transp( entity, transparency);
			CHECK_OUTCOME(o);
		}
	}

#endif  //ACIS

#ifdef PARASOLID

    PK_BODY_t body;
    char *color_attrib_name = "SDL/TYSA_COLOUR";
    char *transp_attrib_name = "SDL/TYSA_TRANSLUCENCY";
    PK_ATTDEF_t color_attdef;
    PK_ATTDEF_t transp_attdef;
    PK_ATTRIB_t color_attrib;
    PK_ATTRIB_t transp_attrib;
	PK_ERROR_code_t pk_error;
    int field_no = 0;
    int  n_doubles = 3;
    double doubles[3];
	double transmission;

	 // Find the tag of the system defined color attribute definition
    pk_error = PK_ATTDEF_find( color_attrib_name, &color_attdef );

	// Find the tag of the system defined tranparency attribute definition
    pk_error = PK_ATTDEF_find( transp_attrib_name, &transp_attdef );
 
    for ( i= 0; i < size; i++)
	{
		HC_KEY current_key = keys[i];

		double red=0,green=0,blue=0;
		ColorItem *citem, *citem_trans;
		citem = style->GetColorItem("faces", "diffuse");

		if( citem->m_bColorSet )
		{
			red = citem->m_color.x;
			green = citem->m_color.y;
			blue = citem->m_color.z;
		}
		// Assign the color value
		doubles[0] = red;
		doubles[1] = green;
		doubles[2] = blue;

		citem_trans = style->GetColorItem("faces", "transmission");
		if( citem_trans->m_bColorSet )
		{
			transmission = citem_trans->m_color.x;
		}

		body = HP_Compute_TagID( current_key, PK_CLASS_body);
		
		PK_BODY_type_t body_type;
		pk_error = PK_BODY_ask_type( body, &body_type);

		int n_faces;
		PK_FACE_t *faces;
		pk_error = PK_BODY_ask_faces( body, &n_faces, &faces);
		if( pk_error )
		{
			H_SAFE_DELETE_ARRAY( keys);
			m_pHView->Update();
			return;
		}
		for( int j=0; j<n_faces; j++)
		{
			// check if face has a color attribute
			pk_error = PK_ENTITY_ask_first_attrib( faces[j], color_attdef, &color_attrib );
			if( color_attrib == PK_ENTITY_null )
			{
				// Create a color attibute on the face
				pk_error = PK_ATTRIB_create_empty( faces[j], color_attdef, &color_attrib );
			}
			// Apply the color to the face
			pk_error = PK_ATTRIB_set_doubles( color_attrib, field_no, n_doubles, doubles );

			// check if face has a transparency attribute
			pk_error = PK_ENTITY_ask_first_attrib( faces[j], transp_attdef, &transp_attrib );
			if( transp_attrib == PK_ENTITY_null )
			{
				// Create a transparency attibute on the face
				pk_error = PK_ATTRIB_create_empty( faces[j], transp_attdef, &transp_attrib );
			}
			// Apply the transparency to the face
			pk_error = PK_ATTRIB_set_doubles( transp_attrib, field_no, 1, &transmission );
		}
		PK_MEMORY_free( faces);
	}
#endif  //PARASOLID

    H_SAFE_DELETE_ARRAY( keys);
    m_pHView->Update();
}

void CStyleDialog::Color(HC_KEY key, char* seg_path, HC_KEY include_key, HC_KEY includer_key, 
							float r, float g, float b, bool recurse, bool emit_message)
{  
    char keytype[MVO_BUFFER_SIZE];
	HC_KEY seg_key;
    bool include = false;
	int i, path_len;

    HC_Show_Key_Type(key, keytype);
    if (strstr(keytype, "segment"))
	{
		seg_key = key;

		path_len = (int)strlen(seg_path);
		for (i = 0; i < path_len; i++)
		{
			if (seg_path[i] == '<')
				include = true;
		}


		if ((include) && (include_key) && (includer_key))
		{
			HC_Delete_By_Key(include_key);					// remove the original include link
			
			HC_Open_Segment_By_Key(includer_key);
			 seg_key = HC_KCopy_Segment(seg_path, "tmp");	// copy the included segment
			HC_Close_Segment();
		}
		
		HC_Open_Segment_By_Key(seg_key);
			HC_Set_Color_By_Value("faces,edges,lines", "RGB", r, g, b );

			if( recurse )
			{
				HC_KEY child;
				char child_type[MVO_BUFFER_SIZE];
				HC_Begin_Contents_Search (".", "segment, include");
				while (HC_Find_Contents (child_type, &child) )
				{
					if (strcmp(child_type,"include")==0)
					{
 						HC_KEY ikey = HC_KShow_Include_Segment(child);
						Color( ikey, "", 0, 0, r, g, b, recurse, emit_message);
					}
					else
						Color( child, "", 0, 0, r, g, b, recurse, emit_message);
				}
				HC_End_Contents_Search();
			}
		HC_Close_Segment();

    }
    else 
	{
        seg_key = HC_KShow_Owner_By_Key(key);

		HC_Open_Segment_By_Key(seg_key);
		 HC_Open_Segment("");   
		  HC_Set_Color_By_Value("faces,edges,lines", "RGB", r, g, b );
		  HC_Move_By_Key(key, ".");
		 HC_Close_Segment();
		HC_Close_Segment();	

    }
}

	

void CStyleDialog::OnSelchangeGeomTypeSelector() 
{
    HoopsStyle *style = m_SelectedStyleWindow->GetStyle();
    CComboBox *cbox = (CComboBox *)GetDlgItem(IDC_GEOM_TYPE_SELECTOR);
    int sel = cbox->GetCurSel();
    CString psource;
    if (sel != CB_ERR)
        cbox->GetLBText(sel, psource);
	
	if( psource == "Plane")
		style->SetStyleGeometry(STYLE_GEOMETRY_PLANE);
	else if (psource == "Cube")
        style->SetStyleGeometry(STYLE_GEOMETRY_CUBE);
    else
		style->SetStyleGeometry(STYLE_GEOMETRY_SPHERE);
        

    UpdateWindows();
    HC_Update_Display();
 	
}

void CStyleDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_RotateSlider.m_hWnd == pScrollBar->m_hWnd)
	{
   		int hpos = m_RotateSlider.GetPos();
		switch (nSBCode)
		{
		case SB_THUMBPOSITION:
		case SB_THUMBTRACK:
			hpos = nPos;
  			break;
		case SB_LINERIGHT:
			hpos++;	

 			break;
		case SB_LINELEFT:
			hpos--;
	 
			break;
		case SB_RIGHT:
			m_RotateSlider.SetPos(nPos);	
				 
 			break;
		case SB_LEFT:
			m_RotateSlider.SetPos(0);	
			break;
		case SB_PAGELEFT:    // Scroll one page left.
			{  
    			int max = m_RotateSlider.GetRangeMax();
				hpos = max(0, hpos - (max/3));	 			
			}
			break;
		case SB_PAGERIGHT:    // Scroll one page left.
			{
    			int max = m_RotateSlider.GetRangeMax();
				hpos = min(max, hpos + (max/3));
	 			
			}
			break;					
		}
		m_RotateSlider.SetPos(hpos);
		

		int spos = m_ScaleSlider.GetPos();
		float scale;
		if (spos == 0)
			spos = 1;
		if (spos < 50)
			scale = 1.0f/ ((50.0f/spos) * (50.0f/spos));
		else if (spos > 50)
			scale = (spos/50.0f)* (spos/50.0f);
		else 
			scale = 1.0f;
		SetTextureMatrix(scale, hpos/100.0f * 360.0f);		
	}
	else if (m_ScaleSlider.m_hWnd == pScrollBar->m_hWnd )
	{
   		int hpos = m_ScaleSlider.GetPos();
		switch (nSBCode)
		{
		case SB_THUMBPOSITION:
		case SB_THUMBTRACK:
			hpos = nPos;
  			break;
		case SB_LINERIGHT:
			hpos++;	

 			break;
		case SB_LINELEFT:
			hpos--;
	 
			break;
		case SB_RIGHT:
			m_ScaleSlider.SetPos(nPos);	
				 
 			break;
		case SB_LEFT:
			m_ScaleSlider.SetPos(0);	
			break;
		case SB_PAGELEFT:    // Scroll one page left.
			{  
    			int max = m_ScaleSlider.GetRangeMax();
				hpos = max(0, hpos - (max/3));	 			
			}
			break;
		case SB_PAGERIGHT:    // Scroll one page left.
			{
    			int max = m_ScaleSlider.GetRangeMax();
				hpos = min(max, hpos + (max/3));
	 			
			}
			break;					
		}
		int rpos = m_RotateSlider.GetPos();
		float rotate = rpos/100.0f * 360.0f;
		m_ScaleSlider.SetPos(hpos);
		if (hpos == 0)
			hpos = 1;
		if (hpos < 50)
			SetTextureMatrix(1.0f/ ((50.0f/hpos) * (50.0f/hpos)),rotate);
		else if (hpos > 50)
			SetTextureMatrix((hpos/50.0f)* (hpos/50.0f),rotate);
		else 
			SetTextureMatrix(1,rotate);


//		m_SelectStylesWindow->Scroll(hpos);
//		UpdateWindows();
	}
	else
	{
  	int hpos = m_StyleScrollbar.GetScrollPos();
	switch (nSBCode)
	{
	case SB_THUMBPOSITION:
	case SB_THUMBTRACK:
	    hpos = nPos;
  		break;
	case SB_LINERIGHT:
		hpos++;	

 		break;
	case SB_LINELEFT:
		hpos--;
 
	    break;
	case SB_RIGHT:
		pScrollBar->SetScrollPos(nPos);	
			 
 		break;
	case SB_LEFT:
		pScrollBar->SetScrollPos(0);	
		break;
	case SB_PAGELEFT:    // Scroll one page left.
		{  
     	    		int max = m_StyleScrollbar.GetScrollLimit();
			hpos = max(0, hpos - (max/3));
 			
		}
		break;
	case SB_PAGERIGHT:    // Scroll one page left.
		{
     	    		int max = m_StyleScrollbar.GetScrollLimit();
			hpos = min(max, hpos + (max/3));
 			
		}
		break;					
	}
	pScrollBar->SetScrollPos(hpos);
	m_SelectStylesWindow->Scroll(hpos);
	UpdateWindows();
	}
 
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
	
}


void CStyleDialog::UpdateWindows()
{
    m_SelectedStyleWindow->UpdateWindow();
    m_SelectStylesWindow->UpdateWindow();
   
}





void CStyleDialog::LoadStyleLibrary()
{

	CString filter;
	CString def_ext;

    filter = "HOOPS File (*.hsf;*.hmf)|*.hsf;*.hmf||";
	def_ext = ".hsf";
 
	TCHAR cur_dir[MVO_BUFFER_SIZE];
	GetCurrentDirectory(MVO_BUFFER_SIZE, cur_dir);
	CFileDialog my_dlg(TRUE, def_ext, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter , NULL);
	my_dlg.m_ofn.lpstrInitialDir = cur_dir;

	CString TextureSourceShortName;
	if (my_dlg.DoModal() == IDOK)
	{
		m_csTextureSourceFile = my_dlg.GetPathName();
		TextureSourceShortName = my_dlg.GetFileName();
	}

    if( m_csTextureSourceFile.IsEmpty() )
    {
 		return;
    }

    bool b_ret = true;
/*
    // create a scratch scratch segment to read the source file
    HC_Open_Segment_By_Key( m_pHView->GetModelKey() );       
 	        HC_KEY temp_seg = HC_KOpen_Segment("");
		HC_Set_Visibility("everything = off");
 		HC_Close_Segment();
    HC_Close_Segment();
    */

    //HC_KEY temp_seg = m_SelectStylesWindow->GetStyleLibrary()->GetKey();
    HC_KEY temp_seg = m_pHView->GetModelKey();

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
    else
    {
    	AfxMessageBox(_T("Unrecognized file extension. Please choose a different file as texture source"));
		b_ret = false;
    }

   

    if( b_ret )
    {
     
    }
 //   HC_Delete_By_Key(temp_seg);

    return;
}

void CStyleDialog::OnLoadStyles() 
{
    char text[MVO_BUFFER_SIZE];
    HC_Show_System_Options(text);
    HC_Define_System_Options("no warnings");
    LoadStyleLibrary();
    HC_Define_System_Options(text);
    m_SelectStylesWindow->RefreshStyleList();
    SetMainStyle(m_SelectStylesWindow->GetCurrentStyle());
m_StyleScrollbar.SetScrollRange(0,m_SelectStylesWindow->GetStyleNum()-1);	

    HC_Update_Display();

	// TODO: Add your control notification handler code here
	
}




void CStyleDialog::SaveStyleLibrary()
{

	CString filter;
	CString def_ext;

    filter = "HOOPS File (*.hsf;*.hmf)|*.hsf;*.hmf||";
	def_ext = ".hsf";
 
	TCHAR cur_dir[MVO_BUFFER_SIZE];
	GetCurrentDirectory(MVO_BUFFER_SIZE, cur_dir);
 	CFileDialog my_dlg(FALSE, def_ext, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOREADONLYRETURN,
						filter , NULL);

	my_dlg.m_ofn.lpstrInitialDir = cur_dir;

	CString TextureSourceShortName;
	if (my_dlg.DoModal() == IDOK)
	{
		m_csTextureSourceFile = my_dlg.GetPathName();
		TextureSourceShortName = my_dlg.GetFileName();
	}

    if( m_csTextureSourceFile.IsEmpty() )
    {
 		return;
    }

    bool b_ret = true;
/*
    // create a scratch scratch segment to read the source file
    HC_Open_Segment_By_Key( m_pHView->GetModelKey() );       
 	        HC_KEY temp_seg = HC_KOpen_Segment("");
		HC_Set_Visibility("everything = off");
 		HC_Close_Segment();
    HC_Close_Segment();
    */

    //HC_KEY temp_seg = m_SelectStylesWindow->GetStyleLibrary()->GetKey();
    HC_KEY temp_seg = m_pHView->GetModelKey();

    // read the source file in to the scratch
    char file_ext[MVO_BUFFER_SIZE];
    HUtility::FindFileNameExtension( H_ASCII_TEXT(m_csTextureSourceFile), file_ext );
    temp_seg = HC_KCreate_Segment("/tempsavstyle");
    HC_Move_By_Key(m_SelectStylesWindow->GetStyleLibrary()->GetKey(),"/tempsavstyle");

    if( streq(file_ext, "hsf") )
    {
        HC_Open_Segment_By_Key(temp_seg);
	    HStreamFileToolkit * tk = new HStreamFileToolkit();
 	    TK_Status status = HTK_Write_Stream_File(H_ASCII_TEXT(m_csTextureSourceFile), 0,tk); 
		(void) status;
	    delete tk;
	HC_Close_Segment();
    }
    else if( streq(file_ext, "hmf") )
    {
        HC_Open_Segment_By_Key(temp_seg);
	    HC_Write_Metafile(".",H_ASCII_TEXT(m_csTextureSourceFile), ""); 
        HC_Close_Segment();
    }
    else
    {
    	AfxMessageBox(_T("Unrecognized file extension. Please choose a different file as texture source"));
		b_ret = false;
    }

    HC_Open_Segment_By_Key(m_pHView->GetModelKey());
    HC_Move_By_Key(m_SelectStylesWindow->GetStyleLibrary()->GetKey(),".");
    HC_Close_Segment();
    if( b_ret )
    {
     
    }
 //   HC_Delete_By_Key(temp_seg);

    return;
}


void CStyleDialog::OnSaveStyles() 
{
    SaveStyleLibrary();
 
 	// TODO: Add your control notification handler code here
	
}

void CStyleDialog::OnNewStyle() 
{
    HoopsStyle * temp = m_SelectedStyleWindow->GetStyle();
    
    CTextInput textinput;
    textinput.m_InfoText = _T("Style Name:");
    if (textinput.DoModal() == IDOK)
    {
	
	
	HC_Open_Segment_By_Key(m_SelectStylesWindow->GetStyleLibrary()->GetKey());
	HC_Open_Segment(H_ASCII_TEXT(textinput.m_TextField)); 
	HC_Close_Segment();
	HC_Close_Segment();
	
	
	m_SelectStylesWindow->RefreshStyleList();	
	temp = m_SelectStylesWindow->GetStyleByName( H_ASCII_TEXT(textinput.m_TextField));
	if (temp)
	    SetMainStyle(temp);
 	m_SelectStylesWindow->UpdateWindow(false);


	m_StyleScrollbar.SetScrollRange(0,m_SelectStylesWindow->GetStyleNum()-1);	
	m_StyleScrollbar.SetScrollPos(m_SelectStylesWindow->GetPosition());
	HC_Update_Display(); 
    }
   
    
}

void CStyleDialog::OnCloneStyle() 
{
    HoopsStyle * temp = m_SelectedStyleWindow->GetStyle();
	if (temp)
	{
		HC_Open_Segment_By_Key(m_SelectStylesWindow->GetStyleLibrary()->GetKey());
		int i=0;
		char text[MVO_BUFFER_SIZE];
		char simpname[MVO_BUFFER_SIZE];
		temp->GetName(simpname);
		
		while (1)
		{	
			sprintf(text,"%s-%d",simpname,i++);
			if (!HUtility::SegmentExists(text))
				break;
		}
		HC_Close_Segment();
		char path[MVO_BUFFER_SIZE];
		HC_Show_Segment(temp->GetKey(), path);
		HC_Open_Segment_By_Key(m_SelectStylesWindow->GetStyleLibrary()->GetKey());
		HC_Open_Segment(text); 
		HC_Copy_Segment(path, ".");
		HC_Close_Segment();
		HC_Close_Segment();
		
		
		m_SelectStylesWindow->RefreshStyleList();	
		temp = m_SelectStylesWindow->GetStyleByName(text );
		if (temp)
			SetMainStyle(temp);
		m_SelectStylesWindow->UpdateWindow(false);
		
		
		
		m_StyleScrollbar.SetScrollRange(0,m_SelectStylesWindow->GetStyleNum()-1);	
		m_StyleScrollbar.SetScrollPos(m_SelectStylesWindow->GetPosition());
		
		HC_Update_Display(); 	
	}
}

void CStyleDialog::OnSelchangeSelectorFrontback() 
{
   
    CComboBox *cbox = (CComboBox *)GetDlgItem(IDC_SELECTOR_FRONTBACK);
    int sel = cbox->GetCurSel();
    CString psource;
    if (sel != CB_ERR)
         cbox->GetLBText(sel, psource);

    if (psource == _T("Faces"))
    	m_bFrontBack = FACES_COLOR;
    else if (psource == _T("Front"))
	m_bFrontBack = FRONT_COLOR;
    else
	m_bFrontBack = BACK_COLOR;
     GatherColorData();
}

int CStyleDialog::IsFrontCombo() 
{

   return m_bFrontBack;

}

 

void CStyleDialog::OnUpdateFaceGloss() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
    HoopsStyle * style = m_SelectedStyleWindow->GetStyle();
    bool undefined = false;
    float val;
    char text[MVO_BUFFER_SIZE];
    UpdateData(true);
    strcpy(text, H_ASCII_TEXT(m_FaceGloss));
    if (strcmp(text,"") == 0)
    {
	val = 0.0f;
	undefined = true;
    }
    else
	val = atof(text);

    if (m_bFrontBack == FACES_COLOR)
 	    style->SetColor("faces", "gloss", val,0,0, undefined);	
     
 	HC_Update_Display();
}

void CStyleDialog::OnKillfocusFaceGloss() 
{
	// TODO: Add your control notification handler code here
	
}

 

void CStyleDialog::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CStyleDialog::OnDeleteStyle() 
{
 	HoopsStyle * style = m_SelectedStyleWindow->GetStyle();
 	if (m_SelectStylesWindow->GetNumStyles() >1)
	{	
		
		HC_Delete_By_Key(style->GetKey());
		m_SelectStylesWindow->RefreshStyleList();
		SetMainStyle(m_SelectStylesWindow->GetCurrentStyle());
		m_StyleScrollbar.SetScrollRange(0,m_SelectStylesWindow->GetStyleNum()-1);	
		
		HC_Update_Display();
	}
	
	
	// TODO: Add your control notification handler code here
	
}

void CStyleDialog::OnSelchangeTexLayout() 
{
	HoopsStyle *style = m_SelectedStyleWindow->GetStyle();
	
	CComboBox *cbox = (CComboBox *)GetDlgItem(IDC_TEX_LAYOUT);
	int sel = cbox->GetCurSel();
	CString psource;
 	if (sel != CB_ERR)
	    cbox->GetLBText(sel, psource);	
	HoopsTexture *tex = style->GetTextureByName(H_ASCII_TEXT(m_CurrentlySelectedTexture));
	if (tex)
	{	
	    tex->SetLayout(H_ASCII_TEXT(psource));
	    HC_Control_Update("/", "redraw everything");
	    HC_Update_Display();
	}
	
}

void CStyleDialog::OnSelchangeTexTiling() 
{

	HoopsStyle *style = m_SelectedStyleWindow->GetStyle();
	
	CComboBox *cbox = (CComboBox *)GetDlgItem(IDC_TEX_TILING);
	int sel = cbox->GetCurSel();
	CString psource;
 	if (sel != CB_ERR)
	    cbox->GetLBText(sel, psource);	
	HoopsTexture *tex = style->GetTextureByName(H_ASCII_TEXT(m_CurrentlySelectedTexture));
	if (tex)
	{	
    	    tex->SetTiling(H_ASCII_TEXT(psource));
	    HC_Control_Update("/", "redraw everything");
	    HC_Update_Display();	
	}
}
void CStyleDialog::OnSelchangeTexBlendingMode() 
{

	HoopsStyle *style = m_SelectedStyleWindow->GetStyle();
	
	CComboBox *cbox = (CComboBox *)GetDlgItem(IDC_TEX_BLENDING_MODE);
	int sel = cbox->GetCurSel();
	CString psource;
 	if (sel != CB_ERR)
	    cbox->GetLBText(sel, psource);	
	HoopsTexture *tex = style->GetTextureByName(H_ASCII_TEXT(m_CurrentlySelectedTexture));
	if (tex)
	{	
    	    tex->SetBlendingMode(H_ASCII_TEXT(psource));
	    HC_Control_Update("/", "redraw everything");
	    HC_Update_Display();	
	}
}
void CStyleDialog::OnCloneTexture() 
{
    HoopsStyle *style = m_SelectedStyleWindow->GetStyle();
    if (style)
    {	
	HoopsTexture *tex = style->GetTextureByName(H_ASCII_TEXT(m_CurrentlySelectedTexture));
	if (tex)
	{	
	    CString uname;
	    generate_unique_name(uname);
	    tex->CloneTexture(H_ASCII_TEXT(uname));
	    m_SelectedStyleWindow->GetStyle()->GatherTextureData();
	    UpdateTexturePane();	
	}
    }
}

void CStyleDialog::OnChangeFaceTransmissonEdit() 
{
       UpdateData(TRUE);
    int percent = atoi(H_ASCII_TEXT(m_FaceTransmissionEditString));
    float p2= (float)percent/100.0f;
    

    HoopsStyle *style = m_SelectedStyleWindow->GetStyle();
	if (m_bFrontBack == FACES_COLOR)
 	    style->SetColor("faces", "transmission", p2,p2,p2, false);	
	else if (m_bFrontBack == FRONT_COLOR)
 	    style->SetColor("front", "transmission", p2,p2,p2, false);	
	else
 	    style->SetColor("back", "transmission", p2,p2,p2, false); 
	GatherColorData();	
	HC_Update_Display();
return;
   // UpdateData(true);
   

	
}

void CStyleDialog::OnChangeFaceGloss() 
{

       UpdateData(TRUE);
    int p2 = atoi(H_ASCII_TEXT(m_FaceGloss));
    
    

    HoopsStyle *style = m_SelectedStyleWindow->GetStyle();
	if (m_bFrontBack == FACES_COLOR)
 	    style->SetColor("faces", "gloss", p2,0,0, false);	
	else if (m_bFrontBack == FRONT_COLOR)
 	    style->SetColor("front", "gloss", p2,0,0, false);	
	else
 	    style->SetColor("back", "gloss", p2,0,0, false);   
	ColorItem *citem = style->GetColorItem("faces", "gloss");
	(void) citem;
	GatherColorData();	
	HC_Update_Display();
  
return;
   // UpdateData(true);
	
}

void CStyleDialog::OnChangeFaceMirrorEdit() 
{
   UpdateData(TRUE);
    int percent = atoi(H_ASCII_TEXT(m_FaceMirrorEditString));
    float p2= (float)percent/100.0f;
    

	HoopsStyle *style = m_SelectedStyleWindow->GetStyle();
	if (m_bFrontBack == FACES_COLOR)
 	    style->SetColor("faces", "mirror", p2,p2,p2, false);	
	else if (m_bFrontBack == FRONT_COLOR)
 	    style->SetColor("front", "mirror", p2,p2,p2, false);	
	else
 	    style->SetColor("back", "mirror", p2,p2,p2, false); 
	style->SetColor("cut face", "mirror", p2,p2,p2, false);	

	GatherColorData();	
	HC_Update_Display();
return;
   // UpdateData(true);
	
}

void CStyleDialog::OnChangeValueScaleMinEdit() 
{

	UpdateData(true);
	HoopsStyle *style = m_SelectedStyleWindow->GetStyle();	
 	HoopsTexture *tex = style->GetTextureByName(H_ASCII_TEXT(m_CurrentlySelectedTexture));
	if (tex)
	{	

	    tex->SetValueScaleMin(atof(H_ASCII_TEXT(m_ValueScaleMin)));
	    HC_Control_Update("/", "redraw everything");
	    HC_Update_Display();	
	}

	
}

void CStyleDialog::OnChangeValueScaleMaxEdit() 
{
	UpdateData(true);
	HoopsStyle *style = m_SelectedStyleWindow->GetStyle();	
 	HoopsTexture *tex = style->GetTextureByName(H_ASCII_TEXT(m_CurrentlySelectedTexture));
	if (tex)
	{	
	    tex->SetValueScaleMax(atof(H_ASCII_TEXT(m_ValueScaleMax)));
	    HC_Control_Update("/", "redraw everything");
	    HC_Update_Display();	
	}
	
}

void CStyleDialog::OnSelchangeDecimationFilter() 
{
	HoopsStyle *style = m_SelectedStyleWindow->GetStyle();
	
	CComboBox *cbox = (CComboBox *)GetDlgItem(IDC_DECIMATION_FILTER);
	int sel = cbox->GetCurSel();
	CString psource;
 	if (sel != CB_ERR)
	    cbox->GetLBText(sel, psource);	
	HoopsTexture *tex = style->GetTextureByName(H_ASCII_TEXT(m_CurrentlySelectedTexture));
	if (tex)
	{	

	    tex->SetDecimationFilter(H_ASCII_TEXT(psource));
	    HC_Control_Update("/", "redraw everything");
	    HC_Update_Display();
	}
	
}

void CStyleDialog::OnDownsamplingCheckbox() 
{
	UpdateData(true);
	HoopsStyle *style = m_SelectedStyleWindow->GetStyle();	
 	HoopsTexture *tex = style->GetTextureByName(H_ASCII_TEXT(m_CurrentlySelectedTexture));
	if (tex)
	{	
	    tex->SetDownsampling(BOOL2bool(m_bDownSampling));
	    HC_Control_Update("/", "redraw everything");
	    HC_Update_Display();
	}
	
}

void CStyleDialog::OnGetStyle()
{
	HoopsStyle *style = m_SelectedStyleWindow->GetStyle();
	HSelectionSet *selection = (HSelectionSet *)m_pHView->GetSelection();
	HC_KEY key, owner;

	int size = selection->GetSize();
	if (size == 1)
	{
		char color[MVO_BUFFER_SIZE]="\0", keytype[MVO_BUFFER_SIZE];
		key = selection->GetAt(0);

		if(!selection->GetReferenceSelection())
		selection->DeSelectAll();

		if (key != INVALID_KEY)
		{
			HC_Show_Key_Type(key, keytype);
			if (streq(keytype, "segment"))
				HC_Open_Segment_By_Key(key);
			else {
				owner = HC_KShow_Owner_By_Key(key);
				if (owner != INVALID_KEY)
					HC_Open_Segment_By_Key(owner);
			}

#ifdef ACIS
			KERN_CLASS_TYPEDEF e_sel_class = ((HSSelectionSet *)m_pHView->GetSelection())->GetSelectLevel();
			char segmentStr[MVO_BUFFER_SIZE];

			if (e_sel_class == BODY_TYPE)
			{
				HC_Begin_Segment_Search("*");
				while (HC_Find_Segment(segmentStr))
				{
					if (HC_QShow_Existence(segmentStr, "color"))
					{
						HC_QShow_Color(segmentStr, color);
						break;
					}
				}
				HC_End_Segment_Search();
			}
			else if (e_sel_class == EDGE_TYPE)
			{
				HC_Show_Color(color);
			}
			else
			{
				// check 1 level up for color setting (owner)
				HC_KEY ownerowner = HC_KShow_Owner_By_Key(owner);
				if (ownerowner != INVALID_KEY)
				{
					HC_Open_Segment_By_Key(ownerowner);
						if (HC_Show_Existence("color")) {
							HC_Show_Color(color);
								if(color[0]=='\0')
							HC_Show_Net_Color(color);
						}
					HC_Close_Segment();
				}
			}
#else
			if(HC_Show_Existence("color"))
				HC_Show_Color(color);
#endif
			HC_Close_Segment();
		}
		HC_Open_Segment_By_Key(style->GetKey());
			if(color[0]!='\0')
				HC_Set_Color(color);
		HC_Close_Segment();

		if(!selection->GetReferenceSelection())
		selection->Select(key, 0, 0);
	}
	GatherColorData();
	HC_Control_Update("/", "redraw everything");
	HC_Update_Display();
}

void CStyleDialog::OnRenameStyle() 
{
    HoopsStyle * temp = m_SelectedStyleWindow->GetStyle();
    
    CTextInput textinput;
    textinput.m_InfoText = _T("Style Name:");
    if (textinput.DoModal() == IDOK)
    {

  
	HUtility::RenameSegment(temp->GetKey(),  H_ASCII_TEXT(textinput.m_TextField));    
	
 	temp = m_SelectStylesWindow->GetStyleByName( H_ASCII_TEXT(textinput.m_TextField));
	if (temp)
	    SetMainStyle(temp);
 	m_SelectStylesWindow->UpdateWindow();
	
	m_StyleScrollbar.SetScrollRange(0,m_SelectStylesWindow->GetStyleNum()-1);	
	HC_Update_Display(); 
	
}
}

void CStyleDialog::OnDeleteImage() 
{
	HoopsStyle *style = m_SelectedStyleWindow->GetStyle();
	
	CComboBox *cbox = (CComboBox *)GetDlgItem(IDC_IMAGE_NAME_COMBO);
	int sel = cbox->GetCurSel();
	CString psource;
 	if (sel != CB_ERR)
	    cbox->GetLBText(sel, psource);	
	HC_KEY delkey = style->FindImage(H_ASCII_TEXT(psource));
	if (delkey != -1)
	    HC_Delete_By_Key(delkey);
//	HoopsTexture *tex = style->GetTextureByName(H_ASCII_TEXT(m_CurrentlySelectedTexture));
	
//	tex->SetSource(H_ASCII_TEXT(psource));
	UpdateTexturePane();
	HC_Control_Update("/", "redraw everything");
	HC_Update_Display();	
}

void CStyleDialog::OnDeleteTexture() 
{
	HoopsStyle *style = m_SelectedStyleWindow->GetStyle();
	
	CComboBox *cbox = (CComboBox *)GetDlgItem(IDC_IMAGE_NAME_COMBO);
	int sel = cbox->GetCurSel();
	CString psource;
 	if (sel != CB_ERR)
	    cbox->GetLBText(sel, psource);	
 
	HoopsTexture *tex = style->GetTextureByName(H_ASCII_TEXT(m_CurrentlySelectedTexture));
	(void) tex;
	style->DeleteTexture(H_ASCII_TEXT(m_CurrentlySelectedTexture));
	
//	tex->SetSource(H_ASCII_TEXT(psource));
	UpdateTexturePane();
	HC_Control_Update("/", "redraw everything");
	HC_Update_Display();		
}

void CStyleDialog::OnCloseupFaceVisibilityCombo() 
{
	// TODO: Add your control notification handler code here
	m_FaceVisibility = m_FaceVisibilityC.GetCurSel();
	switch (m_FaceVisibility)
	{	
	case 0:
		ApplyVisibility("faces", "off");	
		break;
	case 1:
		ApplyVisibility("faces", "on");	
		break;
	case 2:
		ApplyVisibility("faces", 0);	
		break;
	}
}

void CStyleDialog::OnCloseupEdgeVisibilityCombo() 
{
	// TODO: Add your control notification handler code here
	m_EdgeVisibility = m_EdgeVisibilityC.GetCurSel();
	switch (m_EdgeVisibility)
	{	
	case 0:
		ApplyVisibility("edges", "off");	
		break;
	case 1:
		ApplyVisibility("edges", "on");	
		break;
	case 2:
		ApplyVisibility("edges", 0);	
		break;
	}
	
}

void CStyleDialog::OnCloseupLineVisibilityCombo() 
{
	// TODO: Add your control notification handler code here
	m_LineVisibility = m_LineVisibilityC.GetCurSel();
	switch (m_LineVisibility)
	{	
	case 0:
		ApplyVisibility("lines", "off");	
		break;
	case 1:
		ApplyVisibility("lines", "on");	
		break;
	case 2:
		ApplyVisibility("lines", 0);	
		break;
	}
	
}

void CStyleDialog::OnCloseupMarkerVisibilityCombo() 
{
	// TODO: Add your control notification handler code here
	m_MarkerVisibility = m_MarkerVisibilityC.GetCurSel();
	switch (m_MarkerVisibility)
	{	
	case 0:
		ApplyVisibility("markers", "off");	
		break;
	case 1:
		ApplyVisibility("markers", "on");	
		break;
	case 2:
		ApplyVisibility("markers", 0);	
		break;
	}
	
}


void CStyleDialog::SetTextureMatrix(float scale, float rotation)
{
	UpdateData(true);
 	HoopsStyle *style = m_SelectedStyleWindow->GetStyle();	
	HC_Open_Segment_By_Key(style->GetKey());
	if (HC_Show_Existence("texture matrix"))
		HC_UnSet_Texture_Matrix();
	HC_Rotate_Texture(0,0,rotation);
	HC_Scale_Texture(scale,scale,scale);
	HC_Close_Segment();
	m_pHView->Update();

}

	

void CStyleDialog::OnEnChangeValueScaleMinEdit2()
{
	UpdateData(true);
	float matrix[16] = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
	HoopsStyle *style = m_SelectedStyleWindow->GetStyle();	
	HC_Open_Segment_By_Key(style->GetKey());
	if (!HC_Show_Existence("texture matrix"))
		HC_Set_Texture_Matrix(matrix);
	else
		HC_Show_Texture_Matrix(matrix);
	matrix[0] = atof(H_ASCII_TEXT(m_TextureScaleX));
	
	HC_Set_Texture_Matrix(matrix);
	HC_Close_Segment();
	m_pHView->Update();
}

void CStyleDialog::OnEnChangeValueScaleMinEdit3()
{
		UpdateData(true);
	float matrix[16] = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
	HoopsStyle *style = m_SelectedStyleWindow->GetStyle();	
	HC_Open_Segment_By_Key(style->GetKey());
	if (!HC_Show_Existence("texture matrix"))
		HC_Set_Texture_Matrix(matrix);
	else
		HC_Show_Texture_Matrix(matrix);
	matrix[5] = atof(H_ASCII_TEXT(m_TextureScaleY));
	
	HC_Set_Texture_Matrix(matrix);
	HC_Close_Segment();
	m_pHView->Update();

}

void CStyleDialog::OnEnChangeValueScaleMinEdit4()
{
		UpdateData(true);
	float matrix[16] = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
	HoopsStyle *style = m_SelectedStyleWindow->GetStyle();	
	HC_Open_Segment_By_Key(style->GetKey());
	if (!HC_Show_Existence("texture matrix"))
		HC_Set_Texture_Matrix(matrix);
	else
		HC_Show_Texture_Matrix(matrix);
	matrix[10] = atof(H_ASCII_TEXT(m_TextureScaleZ));
	
	HC_Set_Texture_Matrix(matrix);
	HC_Close_Segment();
	m_pHView->Update();

}
