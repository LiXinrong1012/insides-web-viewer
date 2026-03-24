// MainStyleWindow.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "MainStyleWindow.h"
#include "HUtilityGeometryCreation.h"
#include "HoopsStyle.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static int s_windowcounter = 0;
/////////////////////////////////////////////////////////////////////////////
// MainStyleWindow

MainStyleWindow::MainStyleWindow(HoopsStyleLibrary *slib)
{
    m_pStyleLibrary = slib;
}

MainStyleWindow::~MainStyleWindow()
{
    delete m_pStyleViewer;
    HC_Delete_By_Key(thiskey);
}


BEGIN_MESSAGE_MAP(MainStyleWindow, CWnd)
	//{{AFX_MSG_MAP(MainStyleWindow)
	ON_WM_CREATE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// MainStyleWindow message handlers
#define	DEBUG_NO_WINDOWS_HOOK		0x00000040
int MainStyleWindow::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	char dopt[MVO_BUFFER_SIZE];
	char name[MVO_BUFFER_SIZE];
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;	
	sprintf(name, "/driver/opengl/mainsphere%d", s_windowcounter++);
 	thiskey = HC_KOpen_Segment(name);	
        HC_Set_Visibility("faces = on, edges = off, lines = off, markers = off");
	m_pStyleViewer = new HoopsStyleViewer(m_pStyleLibrary);
	m_pStyleViewer->Create();
 	sprintf (dopt, "disable input = all, use window id = %s%p", H_EXTRA_POINTER_FORMAT, this->m_hWnd);
	HC_Set_Driver_Options(dopt);
 	HC_Set_Rendering_Options("hlro = (face displacement = 5, visibility = off, pattern = 1, dim factor = 0.6)");		
	HC_Set_Rendering_Options("hsra = hzb, technology = standard");
	HC_Set_Driver_Options("debug = 0x01000000, fixed colors = 216, double-buffering, no gamma correction");
	HC_Set_Heuristics("no partial erase");
	HC_Set_Rendering_Options("no display lists");

 	HC_Close_Segment();	
  	return 0;

}

void MainStyleWindow::OnPaint() 
{	
	HC_Control_Update_By_Key (thiskey, "redraw everything");

	HC_Update_Display();
	this->ValidateRect(0);
	return;
	// Do not call CWnd::OnPaint() for painting messages
}


void MainStyleWindow::SetStyle(HoopsStyle *style) 
{
    m_pStyleViewer->SetStyle(style);
}

HoopsStyle * MainStyleWindow::GetStyle()
{
    return m_pStyleViewer->GetStyle();
}


void MainStyleWindow::UpdateWindow()
{
  GetStyleViewer()->ShowGeometry();
 
}