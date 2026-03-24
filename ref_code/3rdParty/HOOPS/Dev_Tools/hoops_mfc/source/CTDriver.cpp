
#include "stdafx.h"
#include "CTDriver.h"
#include "HDB.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


BEGIN_MESSAGE_MAP(CTDriver, CWnd)
	ON_WM_TIMER()
END_MESSAGE_MAP()


CTDriver::CTDriver( int milliseconds )
{
    m_nTimer = 0;
    m_milliseconds = milliseconds;

    Init();
}


CTDriver::~CTDriver()
{
	KillTimer();
}


BOOL CTDriver::DestroyWindow()
{
	KillTimer();
	return CWnd::DestroyWindow();
}



int CTDriver::Init()
{
    // This is my invented formula to receive windows messages (esp. the timer messages)
    // in a non-window class (this one) I just register some class and create a window of 0 dimensions
    // This works cool - Rajesh B
    CString strWndClass = AfxRegisterWndClass(0);
    if( !Create(strWndClass, _T("ctdriver"), WS_CHILD, CRect(0, 0, 0, 0), this, 0) )
        return 0;
    return 1;
}


void CTDriver::StartTimer( )
{
    int timer_id = 1;
    do {
        m_nTimer = CWnd::SetTimer( timer_id, m_milliseconds, 0 );
        timer_id++;
    } while( m_nTimer == 0 && timer_id < 50 );
}

void CTDriver::KillTimer()
{
    // kill the timer if it was set
    if( m_nTimer != 0 && GetSafeHwnd())
    {
        CWnd::KillTimer(m_nTimer);
        m_nTimer = 0;
    }
}



#if (_MSC_VER < 1400)
void CTDriver::OnTimer(UINT nIDEvent)
#else
void CTDriver::OnTimer(UINT_PTR nIDEvent)
#endif
{
    float time;

    if (nIDEvent == m_nTimer) {
        HC_Show_Time( &time );

        HDB::GetHTManager()->Tick( time );
    }
}

BOOL CTDriver::PreCreateWindow(CREATESTRUCT& cs)
{
    cs.style = WS_OVERLAPPEDWINDOW;
    cs.cx = 0;
    cs.cy = 0;
    return CWnd::PreCreateWindow(cs);
}


