// SelectStyleWindow.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "SelectStyleWindow.h"
#include "HUtilityGeometryCreation.h"
#include "HoopsStyle.h"
#include "StyleDialog.h"
#include "HBaseView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
static int s_windowcounter;
/////////////////////////////////////////////////////////////////////////////
// SelectStyleWindow

SelectStyleWindow::SelectStyleWindow(CStyleDialog *owner, HBaseView *view)
{
    m_pOwnerDialog = owner;
    m_pHView = view;
}

SelectStyleWindow::~SelectStyleWindow()
{
    delete m_pStyleSelector;
    HC_Delete_By_Key(m_ViewKey);
}


BEGIN_MESSAGE_MAP(SelectStyleWindow, CWnd)
	//{{AFX_MSG_MAP(SelectStyleWindow)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
// MainStyleWindow message handlers
#define	DEBUG_NO_WINDOWS_HOOK		0x00000040



/////////////////////////////////////////////////////////////////////////////
// SelectStyleWindow message handlers

int SelectStyleWindow::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	char dopt[MVO_BUFFER_SIZE];
	char name[MVO_BUFFER_SIZE];
	sprintf(name, "/driver/opengl/selectsphere%d", s_windowcounter++);

	m_ViewKey = HC_KOpen_Segment(name);		
 	sprintf (dopt, "disable input = all, use window id = %s%p", H_EXTRA_POINTER_FORMAT, this->m_hWnd);
	HC_Set_Driver_Options(dopt);
 	HC_Set_Rendering_Options("hlro = (face displacement = 5, visibility = off, pattern = 1, dim factor = 0.6)");		
	HC_Set_Rendering_Options("hsra = hzb, technology = standard");
	HC_Set_Driver_Options("debug = 0x01000000,fixed colors = 216, double-buffering, no gamma correction");
 	HC_Close_Segment();	
	HC_Control_Update_By_Key (m_ViewKey, "redraw everything");

  	HC_Open_Segment_By_Key(m_ViewKey);
            HC_Set_Visibility("faces = on, edges = off, lines = off, markers = off");

	HoopsStyleLibrary *slib = new HoopsStyleLibrary();
	HC_Open_Segment_By_Key(m_pHView->GetModelKey());	
	slib->Create("styles");
	HC_Close_Segment();

	HC_Open_Segment_By_Key(slib->GetKey());
	HC_Open_Segment("default");
//	HC_Set_Color("faces = (diffuse = (blue, red), specular = yellow)");
 	HC_Close_Segment();
	/*
	HC_Open_Segment("blue");
	HC_Set_Color("faces = (diffuse = blue)");
	HC_Close_Segment();
	
	HC_Open_Segment("extra");
	HC_Set_Color("faces = (diffuse = dark blue)");
	HC_Close_Segment();
	*/
	/*
	    
	HC_Open_Segment("black");
	HC_Set_Color("faces = (diffuse = black)");
	HC_Close_Segment();
	HC_Open_Segment("white");
	HC_Set_Color("faces = (diffuse = white)");
	HC_Close_Segment();
	*/
	HC_Close_Segment();
	m_pStyleSelector = new HoopsStyleSelector(slib);
	m_pStyleSelector->GatherStyles();
	m_pStyleSelector->DrawStyles();
	HC_Close_Segment();
//	SetupStyles();
 

	return 0;
}

 

void SelectStyleWindow::OnPaint() 
{
	HC_Control_Update_By_Key (m_ViewKey, "redraw everything");

	HC_Update_Display();
	this->ValidateRect(0);
	return;
}

void SelectStyleWindow::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	HoopsStyle * style = m_pStyleSelector->SelectStyles(point.x, point.y);
	if (style)
	{	
	    m_pStyleSelector->DrawStyles();
	    m_pOwnerDialog->SetMainStyle(style);
	}
	CWnd::OnLButtonDown(nFlags, point);
}

void SelectStyleWindow::UpdateWindow(bool noset)
{
  	m_pStyleSelector->DrawStyles(noset);
 	HC_Update_Display();

}


HoopsStyle * SelectStyleWindow::GetCurrentStyle()
{
    return (m_pStyleSelector->GetSelectedStyle());
}


int SelectStyleWindow::GetStyleNum()
{
    return (m_pStyleSelector->GetStyleNum());
}
int SelectStyleWindow::GetPosition()
{
    return (m_pStyleSelector->GetPosition());
}


void SelectStyleWindow::Scroll(int s)
{
    m_pStyleSelector->Scroll(s);

}

HoopsStyleLibrary *SelectStyleWindow::GetStyleLibrary()
{ 
    return (m_pStyleSelector->GetStyleLibrary()); 

}



void SelectStyleWindow::RefreshStyleList()
{
	m_pStyleSelector->GatherStyles();
	UpdateWindow();
}


HoopsStyle * SelectStyleWindow::GetStyleByName(const char *name)
{
    return (m_pStyleSelector->GetStyleByName(name));

}


void SelectStyleWindow::SetStyle(HoopsStyle *temp)
{
    m_pStyleSelector->SetSelectedStyle(temp);

}

int SelectStyleWindow::GetNumStyles()
{
    return m_pStyleSelector->GetNumStyles();
}

