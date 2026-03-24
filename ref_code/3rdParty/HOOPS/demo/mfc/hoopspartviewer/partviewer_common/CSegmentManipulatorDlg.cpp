// CSegmentManipulatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "CSegmentManipulatorDlg.h"
#include "HBaseView.h"
#include "HIMManager.h" 
#include "HUtilityLocaleString.h"
/////////////////////////////////////////////////////////////////////////////
// CSegmentManipulatorDlg dialog


CSegmentManipulatorDlg::CSegmentManipulatorDlg(CWnd* pParent /*=NULL*/, HC_KEY startsegment, HBaseView * view)
	: CDialog(CSegmentManipulatorDlg::IDD, pParent)
{
	m_segmentkey = startsegment;
	m_pView = view;
	//{{AFX_DATA_INIT(CSegmentManipulatorDlg)
	m_currentsegment = _T("");
	m_renderingoptions = _T("");
	m_visibility = _T("");
 	m_color = _T("");
	m_inserttext = _T("");
	m_aligntoview = FALSE;
	m_textfont = _T("");
	m_switchtosubsegment = FALSE;
	m_filename = _T("");
	m_selectability = _T("");
	//}}AFX_DATA_INIT
}


void CSegmentManipulatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSegmentManipulatorDlg)
	DDX_Text(pDX, IDC_SMAN_CURRENT_SEGMENT, m_currentsegment);
	DDX_Text(pDX, IDC_SMAN_RENDERING_OPTIONS, m_renderingoptions);
	DDX_Text(pDX, IDC_SMAN_VISIBILITY, m_visibility);
 	DDX_Text(pDX, IDC_SMAN_COLOR, m_color);
	DDX_Text(pDX, IDC_SMAN_INSERT_TEXT, m_inserttext);
	DDX_Check(pDX, IDC_CHECK_ALIGN_TO_VIEW, m_aligntoview);
	DDX_Text(pDX, IDC_SMAN_TEXT_FONT, m_textfont);
 	DDX_Text(pDX, IDC_SMAN_LOAD_FILE, m_filename);
	DDX_Text(pDX, IDC_SMAN_SELECTABILITY, m_selectability);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSegmentManipulatorDlg, CDialog)
	//{{AFX_MSG_MAP(CSegmentManipulatorDlg)
	ON_BN_CLICKED(IDC_SMAN_RENDERING_OPTIONS_APPLY, OnSmanRenderingOptionsApply)
	ON_BN_CLICKED(IDC_SMAN_VISIBILITY_APPLY, OnSmanVisibilityApply)
 	ON_BN_CLICKED(IDC_SMAN_CURRENT_SEGMENT_APPLY, OnSmanCurrentSegmentApply)
	ON_BN_CLICKED(IDC_SMAN_COLOR_APPLY, OnSmanColorApply)
	ON_BN_CLICKED(IDC_SMAN_INSERT_TEXT_APPLY, OnSmanInsertTextApply)
	ON_BN_CLICKED(IDC_SMAN_TEXT_FONT_APPLY, OnSmanTextFontApply)
	ON_BN_CLICKED(IDC_SMAN_LOAD_FILE_BROWSE, OnSmanLoadFileBrowse)
	ON_BN_CLICKED(IDC_SMAN_LOAD_FILE_APPLY, OnSmanLoadFileApply)
	ON_BN_CLICKED(IDC_SMAN_SELECTABILITY_APPLY, OnSmanSelectabilityApply)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSegmentManipulatorDlg message handlers

void CSegmentManipulatorDlg::FillEditBoxes()
{
	char text[MVO_BUFFER_SIZE];
	HC_Show_Segment(m_segmentkey, text);
	m_currentsegment = text;
	HC_Open_Segment_By_Key(m_segmentkey);
	if (HC_Show_Existence("visibility"))
		HC_Show_Visibility(text);
	else
		strcpy(text, "");
	m_visibility = text;
	if (HC_Show_Existence("rendering options"))
		HC_Show_Rendering_Options(text);
	else
		strcpy(text, "");
 	m_renderingoptions = text;

	if (HC_Show_Existence("color"))
		HC_Show_Color(text);
	else
		strcpy(text, "");
	m_color = text;

	if (HC_Show_Existence("text font"))
		HC_Show_Text_Font(text);
	else
		strcpy(text, "");
	m_textfont = text;

	if (HC_Show_Existence("selectability"))
		HC_Show_Selectability(text);
	else
		strcpy(text, "");
	m_selectability = text;

	HC_Close_Segment();	
	UpdateData(false);
 
 
}

BOOL CSegmentManipulatorDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	FillEditBoxes();

 	// TODO: Add extra initialization here
 	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSegmentManipulatorDlg::OnSmanRenderingOptionsApply() 
{
	UpdateData(true);
	HC_Open_Segment_By_Key(m_segmentkey);
	if (strcmp(H_ASCII_TEXT(m_renderingoptions), "") == 0)
	{
		if (HC_Show_Existence("rendering options"))
			HC_UnSet_Rendering_Options();
	}
	else
		HC_Set_Rendering_Options(H_ASCII_TEXT(m_renderingoptions));
	HC_Set_Text_Alignment("<");
	HC_Close_Segment();
	m_pView->Update();

	
}

void CSegmentManipulatorDlg::OnSmanVisibilityApply() 
{
	UpdateData(true);
	HC_Open_Segment_By_Key(m_segmentkey);
	if (strcmp(H_ASCII_TEXT(m_visibility), "") == 0)
	{
		if (HC_Show_Existence("visibility"))
			HC_UnSet_Visibility();
	}
	else
		HC_Set_Visibility(H_ASCII_TEXT(m_visibility));
	HC_Close_Segment();
	m_pView->Update();
}

 
void CSegmentManipulatorDlg::OnSmanCurrentSegmentApply() 
{
	UpdateData(true);
	m_segmentkey = HC_KOpen_Segment(H_ASCII_TEXT(m_currentsegment));
	HC_Close_Segment();
	FillEditBoxes();
 	m_pView->Update();
}

void CSegmentManipulatorDlg::OnSmanColorApply() 
{
	UpdateData(true);
	HC_Open_Segment_By_Key(m_segmentkey);
	if (strcmp(H_ASCII_TEXT(m_color), "") == 0)
	{
		if (HC_Show_Existence("color"))
			HC_UnSet_Color();
	}
	else
		HC_Set_Color(H_ASCII_TEXT(m_color));
	HC_Close_Segment();
	m_pView->Update();	
}


static void GetMatrixFromCamera(HPoint position, HPoint target, HPoint up_vector, float *matrix)
{
    HPoint view_vector, view_vector2;
    view_vector.Set(target.x-position.x, target.y-position.y, target.z-position.z);
    view_vector2 = view_vector;
 
    HC_Compute_Normalized_Vector(&view_vector, &view_vector);
    HC_Compute_Normalized_Vector(&up_vector, &up_vector);

    HPoint cross1;

    HC_Compute_Cross_Product(&up_vector, &view_vector, &cross1);

    matrix[0] = cross1.x;
    matrix[1] = cross1.y;
    matrix[2] = cross1.z;
    matrix[3] = 0.0f;

    HPoint cross2;

    HC_Compute_Cross_Product(&view_vector, &cross1, &cross2);

    matrix[4] = cross2.x;
    matrix[5] = cross2.y;
    matrix[6] = cross2.z;
    matrix[7] = 0.0f;

    matrix[8] = view_vector.x;
    matrix[9] = view_vector.y;
    matrix[10] = view_vector.z;
    matrix[11] = 0.0f;
    
    matrix[12] = 0;
    matrix[13] = 0;
    matrix[14] = 0;
    matrix[15] = 1.0f;
}
void DecodeText (const char *intext, char *outtext)
{
	int ii=0;
	for (int i=0;i<(int)strlen(intext);i++)
	{
		if (intext[i] == '\\' && intext[i+1] == 'n')
		{
			outtext[ii++] = 10;
			i++;
		}
		else
			outtext[ii++] = intext[i];
	}
	outtext[ii] = 0;
}
		
void CSegmentManipulatorDlg::OnSmanInsertTextApply() 
{
	UpdateData(true);
  	HPoint p,t,u;
  	HC_Open_Segment_By_Key(m_pView->GetSceneKey());		
		HC_Show_Net_Camera_Position(&p.x, &p.y, &p.z);
 		HC_Show_Net_Camera_Target(&t.x, &t.y, &t.z);
		HC_Show_Net_Camera_Up_Vector(&u.x, &u.y, &u.z);
 		HC_Close_Segment();
	HPoint p2, t2, u2;
	float matx[16];
	GetMatrixFromCamera(p,t,u, matx);

	HC_Open_Segment_By_Key(m_pView->GetModelKey());
	HC_Open_Segment("cameratext");
		HC_Set_Camera_Field(2,2);
		HC_Set_Camera_Projection("perspective");
		HC_Set_Handedness("left");
		HC_Set_Camera_Position(0,0,-1);
		HC_Set_Camera_Target(0,0,4);
		int noscale = 1;
		HC_Set_User_Index(H_DISABLE_SCALE_MAGIC, (void *)noscale);

 	HC_Close_Segment();
	HC_Close_Segment();
	HC_Open_Segment_By_Key(m_segmentkey);
	HC_Flush_Contents(".", "everything");
 
//	if (m_aligntoview)
 		HC_Set_Text_Font("name = arial, transforms = off");
//		HImSetCallback("draw text","HImUtility_draw_text_infront");

//		HC_Set_Modelling_Matrix(matx);
		char outtext[MVO_BUFFER_SIZE];
	DecodeText(H_ASCII_TEXT(m_inserttext), outtext);
	HC_Insert_Text(0,0,0,outtext);
	HC_Close_Segment();

	m_pView->Update();
}
 
  

void CSegmentManipulatorDlg::OnSmanTextFontApply() 
{
	UpdateData(true);

	HC_Open_Segment_By_Key(m_segmentkey);
		if (strcmp(H_ASCII_TEXT(m_textfont), "") == 0)
		{
			if (HC_Show_Existence("text font"))
				HC_UnSet_Text_Font();
		}
		else
			HC_Set_Text_Font(H_ASCII_TEXT(m_textfont));
	HC_Close_Segment();

	m_pView->Update();		
}

void CSegmentManipulatorDlg::OnSmanLoadFileBrowse() 
{

	CString filter, def_file_ext;
 
    filter = "HOOPS File (*.hsf;*.hmf)|*.hsf;*.hmf||";
	def_file_ext = ".hsf";
 
 
	CFileDialog my_dlg(TRUE, def_file_ext, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter , NULL);
	if (my_dlg.DoModal() == IDOK)	
		 m_filename = my_dlg.GetPathName();
	UpdateData(false);
}

void CSegmentManipulatorDlg::OnSmanLoadFileApply() 
{
	UpdateData(true);

	HC_Open_Segment_By_Key(m_segmentkey);
		HStreamFileToolkit * tk = new HStreamFileToolkit();
		HTK_Read_Stream_File (H_ASCII_TEXT(m_filename), tk); 
	HC_Close_Segment();

	delete tk;
}

void CSegmentManipulatorDlg::OnSmanSelectabilityApply() 
{
	UpdateData(true);

	HC_Open_Segment_By_Key(m_segmentkey);
		if (strcmp(H_ASCII_TEXT(m_selectability), "") == 0)
		{
			if (HC_Show_Existence("selectability"))
				HC_UnSet_Selectability();
		}
		else
			HC_Set_Selectability(H_ASCII_TEXT(m_selectability));
	HC_Close_Segment();

	m_pView->Update();		
}
