// ImageViewer.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ImageViewer.h"
#include "HoopsStyle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
static int s_windowcounter;
/////////////////////////////////////////////////////////////////////////////
// CImageViewer

CImageViewer::CImageViewer(CStyleDialog *owner)
{
    m_pOwnerDialog = owner;

}

CImageViewer::~CImageViewer()
{
    HC_Delete_By_Key(thiskey);
}


BEGIN_MESSAGE_MAP(CImageViewer, CWnd)
	//{{AFX_MSG_MAP(CImageViewer)
	ON_WM_CREATE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CImageViewer message handlers


int CImageViewer::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{

    char dopt[MVO_BUFFER_SIZE];
    char name[MVO_BUFFER_SIZE];
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;	
	sprintf(name, "/driver/opengl/imagewindow%d", s_windowcounter++);

 	thiskey = HC_KOpen_Segment(name);	
  	sprintf (dopt, "disable input = all, use window id = %s%p", H_EXTRA_POINTER_FORMAT, this->m_hWnd);
	HC_Set_Driver_Options(dopt);
 	HC_Set_Rendering_Options("hlro = (face displacement = 5, visibility = off, pattern = 1, dim factor = 0.6)");		
	HC_Set_Rendering_Options("hsra = hzb, technology = standard");
	HC_Set_Driver_Options("debug = 0x01000000, fixed colors = 216, double-buffering, no gamma correction");
	HC_Set_Camera_Position(0,0,8);
	HC_Set_Camera_Target(0,0,0);
	HC_Set_Camera_Field(2,2);
	HC_Set_Camera_Projection("stretched");
 	HC_Close_Segment();	
  	return 0;
}

void CImageViewer::OnPaint() 
{	
	HC_Control_Update_By_Key (thiskey, "redraw everything");

	HC_Update_Display();
	this->ValidateRect(0);
	return;
}


void CImageViewer::SetImage(HoopsTexture *tex)
{
	if (tex)
	{	
	CRect rect;
	GetWindowRect(rect);
	HC_Open_Segment_By_Key(thiskey);
	tex->ShowImage(rect.right - rect.left, rect.bottom - rect.top);
	HC_Close_Segment();
	HC_Update_Display();
	}

}