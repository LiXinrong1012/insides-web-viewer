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
// $Header: /files/homes/master/cvs/hoops_master/shared/qt4_common/HQWidget.cpp,v 1.71 2010-12-03 20:07:24 simon Exp $
//


#include <stdlib.h>
#include <stdio.h>
#include <map>

// qt includes
#include <QEvent>
#include <QMessageBox>
#include <QMouseEvent>
#include <QCoreApplication>
#include <QApplication>
#include <QHash>
#include <QColormap>
#include <QAbstractButton>



#if IS_OSX
#include <Carbon/Carbon.h>
#include <AGL/agl.h>
#endif

// hoops_mvo includes
#include "HBaseOperator.h"
#include "HDB.h"
#include "HBaseView.h"
#include "HEventInfo.h"
#include "HEventManager.h"
// hoops
#include "hc.h"
#include "vhash.h"
#include "vlist.h"


#if IS_X11
// a mess of X
#include <X11/IntrinsicP.h>
#include <X11/StringDefs.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>
#include <X11/Xmu/StdCmap.h>

#include <QX11Info>

#if USE_GLX_VISUAL
#define INT8  dummy_INT8
#define INT32 dummy_INT32

#include <GL/glx.h>

#undef  INT8
#undef  INT32

#ifdef HPUX_SYSTEM
#include <dl.h>
#else
#include <dlfcn.h>
#endif

#endif //USE_GLX_VISUAL


#endif // IS_X11


#include "HQWidget.h"

// this needs to be created first in the application
extern HDB * m_pHDB;


HQWidget::HQWidget( QWidget *parent, QString const & name, Qt::WFlags f, int aa)
#if defined(IS_OSX) && defined(USE_MDI)
    : QGLWidget(parent,0, f) 
#else
    : QWidget(parent, f) 
#endif
{
    initDone = false;
	ignore_update = false;

	//setAttribute(Qt::WA_NoSystemBackground);
	setAttribute(Qt::WA_PaintOnScreen);
	setBackgroundRole( QPalette::NoRole);

	if ( this == 0 ) {
		QMessageBox::information( 0, "Qt HOOPS Viewer","HQWidget: Paint device cannot be null");
    }

    if (this->devType() != QInternal::Widget &&
		this->devType() != QInternal::Pixmap ) {
			QMessageBox::information( 0, "Qt HOOPS Viewer","HQWidget: Unsupported paint device type");
        }


    m_pHBaseModel = 0;
    m_pHView = 0; 

	my_clip_override=0;
    my_colormap=0;
    my_windowid=0;
    my_have_gl_visual = false;
    my_aa = aa;

#if defined(IS_OSX) && defined(USE_MDI)
	AGLContext temp = aglGetCurrentContext();
	makeCurrent();
	//glInit();
	my_qgl_context = aglGetCurrentContext();
	aglSetCurrentContext(temp);
#endif

    // this does all the work for palettes and windowid

    if(streq(m_pHDB->GetDriverType(), "opengl")){

	setup_window(true);
	
	if(!my_have_gl_visual){

	    QMessageBox::information( 0, "Qt HOOPS Viewer",
	    	"Sorry OpenGL is not available");
#if IS_X11
	    m_pHDB->SetDriverType("x11");
#else
	    m_pHDB->SetDriverType("msw");
#endif
	}

    }else
	setup_window(false);
}

HQWidget::~HQWidget()
{

}

QPaintEngine* HQWidget::paintEngine() const{
	return NULL;
}

void * HQWidget::GetColorMap()
{
	return my_colormap;
}

void * HQWidget::GetWindowId()
{
	return my_windowid;
}

#if defined(IS_OSX) && defined(USE_MDI)
void * HQWidget::GetQGLContext()
{
	return my_qgl_context;
}
#endif

void * HQWidget::GetClipOverride()
{
	return my_clip_override;
}

void HQWidget::AdjustAxisWindow()
{
 	m_pHView->AdjustAxisWindow( 80 );
}

void HQWidget::paintEvent( QPaintEvent * e)
{
	if(ignore_update)
		return;
#ifdef IS_OSX
   QWidget * tl = topLevelWidget();

    QPoint gtb = tl->mapToGlobal(QPoint(0,tl->size().height()));
    QPoint gwb = mapToGlobal(QPoint(0,size().height()));

    //outer window
    use_clip_override[0]=tl->pos().x();
    use_clip_override[1]=tl->pos().y();
    //use_clip_override[2]=tl->size().width();
    //use_clip_override[3]=tl->size().height();
    use_clip_override[2]=tl->frameGeometry().width();
    use_clip_override[3]=tl->frameGeometry().height();

    //widget
    use_clip_override[4]=gwb.x()-gtb.x();
    use_clip_override[5]=gtb.y()-gwb.y();
    use_clip_override[6]=frameGeometry().width();
    use_clip_override[7]=frameGeometry().height();
    
#if 0
printf("paint %p %d %d %d %d %d %d %d %d\n",
    (void*)this,
    use_clip_override[0],
    use_clip_override[1],
    use_clip_override[2],
    use_clip_override[3],
    use_clip_override[4],
    use_clip_override[5],
    use_clip_override[6],
    use_clip_override[7]);
#endif
#endif
	// If any HOOPS error windows come up during this Init call, (such as the no license message)
	// then a paint event gets called again, which calls this Init function again before it has
	// finished...  which leads to trouble.  So we use this event filter (defined in HQWidget) that
	// blocks all paint events, then we remove it at the end of this call.

	if ( !initDone ) {
		installEventFilter(this);
		Init();
		removeEventFilter(this);
		initDone = true;
	}
	else{
		setAttribute(Qt::WA_NoSystemBackground);
	}
	
	AdjustAxisWindow();
	
	if (m_pHView)
		HC_Control_Update_By_Key(m_pHView->GetViewKey(), "redraw everything");
	m_pHView->SetCameraChanged();

	m_pHView->Update();

}


bool HQWidget::eventFilter(QObject* obj, QEvent* ev){
	if (ev->type() == QEvent::Paint){
		return true;
	}
	else{
		return QObject::eventFilter(obj, ev);
	}
}

void HQWidget::resizeEvent( QResizeEvent * e)
{
#ifdef IS_OSX
   QWidget * tl = topLevelWidget();

    QPoint gtb = tl->mapToGlobal(QPoint(0,tl->size().height()));
    QPoint gwb = mapToGlobal(QPoint(0,size().height()));

    //outer window
    use_clip_override[0]=tl->pos().x();
    use_clip_override[1]=tl->pos().y();
    use_clip_override[2]=tl->size().width();
    use_clip_override[3]=tl->size().height();

    //widget
    use_clip_override[4]=gwb.x()-gtb.x();
    use_clip_override[5]=gtb.y()-gwb.y();
    use_clip_override[6]=size().width();
    use_clip_override[7]=size().height();
    
#if 0
printf("resize %p %d %d %d %d %d %d %d %d\n",
    (void*)this,
    use_clip_override[0],
    use_clip_override[1],
    use_clip_override[2],
    use_clip_override[3],
    use_clip_override[4],
    use_clip_override[5],
    use_clip_override[6],
    use_clip_override[7]);
#endif
#endif
	
    if ( initDone ) {
		AdjustAxisWindow();
		if (m_pHView)
			HC_Control_Update_By_Key(m_pHView->GetViewKey(), "redraw everything");
		m_pHView->SetCameraChanged();
	}


}


void HQWidget::focusInEvent(QFocusEvent* e)
{
	if ( initDone ) {
		AdjustAxisWindow();
		if (m_pHView)
			HC_Control_Update_By_Key(m_pHView->GetViewKey(), "redraw everything");
		m_pHView->SetCameraChanged();
	}
}


void HQWidget::focusOutEvent(QFocusEvent* e)
{
	if ( initDone ) {
		AdjustAxisWindow();
		if (m_pHView)
			HC_Control_Update_By_Key(m_pHView->GetViewKey(), "redraw everything");
		m_pHView->SetCameraChanged();
	}
}


// button mappings
unsigned long HQWidget::MapFlags( unsigned long state )
{
	unsigned long flags=0;

	/*map the qt events state to MVO*/
	if(state & Qt::LeftButton) flags|=MVO_LBUTTON;
	if(state & Qt::RightButton) flags|=MVO_RBUTTON;
	if(state & Qt::MidButton) flags|=MVO_MBUTTON;
	if(state & Qt::SHIFT) flags|=MVO_SHIFT;
	if(state & Qt::CTRL) flags|=MVO_CONTROL;

	return flags;
}

void HQWidget::mouseDoubleClickEvent( QMouseEvent * e)
{
    if(e->button() == Qt::LeftButton) 
	OnLeftButtonDblClk(e);
    else if(e->button() == Qt::RightButton) 
	OnRightButtonDblClk(e);
    else{
	    if(e->button() == Qt::MidButton) 
		OnMidButtonDblClk(e);
	}
}

void HQWidget::mousePressEvent( QMouseEvent * e)
{
#if 0
	QPoint p = mapTo(topLevelWidget(), pos());
	QPoint gp(e->globalX(), e->globalY());
printf("%d %d %d %d %d %d\n", p.x(), p.y(), e->x(), e->y(), gp.x(), gp.y());
#endif
    if(e->button() == Qt::LeftButton)
	OnLeftButtonDown(e);
    else if(e->button() == Qt::RightButton) 
	OnRightButtonDown(e);
    else {
	if(e->button() == Qt::MidButton) 
	    OnMidButtonDown(e);
    }
}

void HQWidget::mouseReleaseEvent( QMouseEvent * e)
{
#if 0
	QPoint p = mapTo(topLevelWidget(), pos());
	QPoint gp(e->globalX(), e->globalY());
printf("%d %d %d %d %d %d\n", p.x(), p.y(), e->x(), e->y(), gp.x(), gp.y());
#endif
    if(e->button() == Qt::LeftButton)
	OnLeftButtonUp(e);
    else if(e->button() == Qt::RightButton) 
	OnRightButtonUp(e);
    else {
	if(e->button() == Qt::MidButton) 
	    OnMidButtonUp(e);
    }
}


void HQWidget::OnLeftButtonDown(QMouseEvent * e)
{
    if (m_pHView) {
	HEventInfo event(m_pHView);

        unsigned long flags=MapFlags(e->buttons()|e->modifiers ());
	event.SetPoint(HE_LButtonDown, e->x(), e->y(), flags);
	HLISTENER_EVENT(HMouseListener, m_pHView->GetEventManager(), OnLButtonDown(event))

    }
}

void HQWidget::OnLeftButtonUp(QMouseEvent * e)
{
    if (m_pHView) {
	HEventInfo event(m_pHView);

        unsigned long flags=MapFlags(e->buttons()|e->modifiers ());
	event.SetPoint(HE_LButtonUp, e->x(), e->y(), flags);
	HLISTENER_EVENT(HMouseListener, m_pHView->GetEventManager(), OnLButtonUp(event))

    }
}

void HQWidget::OnLeftButtonDblClk(QMouseEvent * e)
{
    if (m_pHView) {
	HEventInfo event(m_pHView);

        unsigned long flags=MapFlags(e->buttons()|e->modifiers ());
	event.SetPoint(HE_LButtonDblClk, e->x(), e->y(), flags);
	HLISTENER_EVENT(HMouseListener, m_pHView->GetEventManager(), OnLButtonDblClk(event))

    }
}


void HQWidget::OnMidButtonDown(QMouseEvent * e)
{
    if (m_pHView) {
	HEventInfo event(m_pHView);

        unsigned long flags=MapFlags(e->buttons()|e->modifiers ());
	event.SetPoint(HE_MButtonDown, e->x(), e->y(), flags);
	HLISTENER_EVENT(HMouseListener, m_pHView->GetEventManager(), OnMButtonDown(event))

    }
}

void HQWidget::OnMidButtonUp(QMouseEvent * e)
{
    if (m_pHView) {
	HEventInfo event(m_pHView);

        unsigned long flags=MapFlags(e->buttons()|e->modifiers ());
	event.SetPoint(HE_MButtonUp, e->x(), e->y(), flags);
	HLISTENER_EVENT(HMouseListener, m_pHView->GetEventManager(), OnMButtonUp(event))

    }
}

void HQWidget::OnMidButtonDblClk(QMouseEvent * e)
{
    if (m_pHView) {
	HEventInfo event(m_pHView);

        unsigned long flags=MapFlags(e->buttons()|e->modifiers ());
	event.SetPoint(HE_MButtonDblClk, e->x(), e->y(), flags);
	HLISTENER_EVENT(HMouseListener, m_pHView->GetEventManager(), OnMButtonDblClk(event))

    }
}

void HQWidget::OnRightButtonDown(QMouseEvent * e)
{
    if (m_pHView) {
	HEventInfo event(m_pHView);

        unsigned long flags=MapFlags(e->buttons()|e->modifiers ());
	event.SetPoint(HE_RButtonDown, e->x(), e->y(), flags);
	HLISTENER_EVENT(HMouseListener, m_pHView->GetEventManager(), OnRButtonDown(event))

    }
}


void HQWidget::OnRightButtonUp(QMouseEvent * e)
{
    if (m_pHView) {
	HEventInfo event(m_pHView);

        unsigned long flags=MapFlags(e->buttons()|e->modifiers ());
	event.SetPoint(HE_RButtonUp, e->x(), e->y(), flags);
	HLISTENER_EVENT(HMouseListener, m_pHView->GetEventManager(), OnRButtonUp(event))

    }
}

void HQWidget::wheelEvent(QWheelEvent * e)
{
    if (m_pHView) {
	HEventInfo event(m_pHView);
  	event.SetMouseWheelDelta(e->delta());
        unsigned long flags=MapFlags(e->buttons()|e->modifiers ());
	event.SetPoint(HE_RButtonUp, e->x(), e->y(), flags);
 	HLISTENER_EVENT(HMouseListener, m_pHView->GetEventManager(), OnMouseWheel(event))

    }
}


void HQWidget::OnRightButtonDblClk(QMouseEvent * e)
{
    if (m_pHView) {
	HEventInfo event(m_pHView);

        unsigned long flags=MapFlags(e->buttons()|e->modifiers ());
	event.SetPoint(HE_RButtonDblClk, e->x(), e->y(), flags);
	HLISTENER_EVENT(HMouseListener, m_pHView->GetEventManager(), OnRButtonDblClk(event))

    }
}

void HQWidget::mouseMoveEvent(QMouseEvent * e)
{

#if 0
	QPoint p = mapTo(topLevelWidget(), pos());
	QPoint gp(e->globalX(), e->globalY());
printf("%d %d %d %d %d %d\n", p.x(), p.y(), e->x(), e->y(), gp.x(), gp.y());
#endif
	if (m_pHView) {
		HEventInfo	event(m_pHView);

#if 0
printf("%d %d\n", e->x(), e->y());
#endif
		unsigned long flags=MapFlags(e->buttons()|e->modifiers());
		event.SetPoint(HE_MouseMove, e->x(), e->y(), flags);
		HLISTENER_EVENT(HMouseListener, m_pHView->GetEventManager(), OnMouseMove(event))
	}
}

static std::map<unsigned int,bool> key_states;

void HQWidget::keyPressEvent ( QKeyEvent * e )
{
	unsigned int nChar;

// Remove this once we move to QT 4.2 or later on Solaris
#ifdef SOLARIS_SYSTEM
	nChar = e->text().toAscii()[0];
#else
	nChar = e->nativeVirtualKey();
#endif

	if (m_pHView) {
		HEventInfo  event(m_pHView);
		HBaseOperator *op = m_pHView->GetCurrentOperator();

		if (op) {
			unsigned long flags=MapFlags(e->modifiers());

			event.SetKey(HE_KeyDown, nChar, (unsigned int)1, flags);			
			HLISTENER_EVENT(HMouseListener, m_pHView->GetEventManager(), OnKeyDown(event))
		}
	}

	key_states[nChar] = true;	
}

void HQWidget::keyReleaseEvent ( QKeyEvent * e )
{
	unsigned int nChar;

// Remove this once we move to QT 4.2 or later on Solaris
#ifdef SOLARIS_SYSTEM
	nChar = e->text().toAscii()[0];
#else
	nChar = e->nativeVirtualKey();
#endif

	if (m_pHView) {
		HEventInfo  event(m_pHView);
		HBaseOperator *op = m_pHView->GetCurrentOperator();

		if (op) {
			unsigned long flags=MapFlags(e->modifiers());
			
			event.SetKey(HE_KeyUp, nChar, (unsigned int)1, flags);
			HLISTENER_EVENT(HMouseListener, m_pHView->GetEventManager(), OnKeyUp(event))
		}
	}
		
	key_states[nChar] = false;
}


// this is overloaded by the child class
void HQWidget::Init()
{
	
}


#if IS_WIN
void HQWidget::setup_window(bool use_gl)
{
	my_windowid= (void *)((QWidget *) this)->winId();
	my_colormap=0;
	my_have_gl_visual = use_gl;
}
#endif

#if IS_OSX
void HQWidget::setup_window(bool use_gl)
{
	my_windowid = (void *)winId();
	my_clip_override = (void*)use_clip_override;
	my_have_gl_visual = use_gl;
	/*
	my_colormap=0;
	*/
}
#endif

#if IS_X11
// below is the ugly stuff for X11 window id and palette

#ifdef __cplusplus
#   define get_visual_class(vis_ptr)    ((vis_ptr)->c_class)
#else
#   define get_visual_class(vis_ptr)    ((vis_ptr)->class)
#endif

#define INITIAL_VALUE       (-1)

static void get_best_visual (
	Display     *display,
	XVisualInfo *visual) {
	XVisualInfo     f_template;
	XVisualInfo *   visuals;
	int         visual_count;
	int     best = INITIAL_VALUE;

	/*
	* Get a list of the deepest possible visuals
	*/
	f_template.screen = DefaultScreen (display);
	f_template.depth = 24;

	do
		visuals = XGetVisualInfo (display, VisualScreenMask | VisualDepthMask,
		&f_template, &visual_count);
		while(! (visual_count > 0 || --f_template.depth == 0));

	while(! (visual_count-- == 0)) {

		if (visuals[visual_count].depth > 8) {
			switch (get_visual_class (&visuals[visual_count])) {
			case TrueColor: {
			best = visual_count;
			}   break;

			case DirectColor: {
			if (best == INITIAL_VALUE ||
			get_visual_class (&visuals[best]) == PseudoColor ||
			get_visual_class (&visuals[best]) == StaticColor ||
			get_visual_class (&visuals[best]) == GrayScale ||
			get_visual_class (&visuals[best]) == StaticGray)
			best = visual_count;
			}   break;

			case PseudoColor: {
			if (best == INITIAL_VALUE ||
			get_visual_class (&visuals[best]) == StaticColor ||
			get_visual_class (&visuals[best]) == GrayScale ||
			get_visual_class (&visuals[best]) == StaticGray)
			best = visual_count;
			}   break;

			case StaticColor: {
			if (best == INITIAL_VALUE ||
			get_visual_class (&visuals[best]) == GrayScale ||
			get_visual_class (&visuals[best]) == StaticGray)
			best = visual_count;
			}   break;

			case GrayScale: {
			if (best == INITIAL_VALUE ||
			get_visual_class (&visuals[best]) == StaticGray)
			best = visual_count;
			}   break;

			case StaticGray: {
			if (best == INITIAL_VALUE)
			best = visual_count;
			}   break;
			}
			}
			else {
			switch (get_visual_class (&visuals[visual_count])) {
			case PseudoColor: {
			best = visual_count;
			}   break;

			case StaticColor: {
			if (best == INITIAL_VALUE ||
			get_visual_class (&visuals[best]) == TrueColor ||
			get_visual_class (&visuals[best]) == DirectColor ||
			get_visual_class (&visuals[best]) == GrayScale ||
			get_visual_class (&visuals[best]) == StaticGray)
			best = visual_count;
			}   break;

			case TrueColor: {
			if (best == INITIAL_VALUE ||
			get_visual_class (&visuals[best]) == DirectColor ||
			get_visual_class (&visuals[best]) == GrayScale ||
			get_visual_class (&visuals[best]) == StaticGray)
			best = visual_count;
			}   break;

			case DirectColor: {
			if (best == INITIAL_VALUE ||
			get_visual_class (&visuals[best]) == GrayScale ||
			get_visual_class (&visuals[best]) == StaticGray)
			best = visual_count;
			}   break;

			case GrayScale: {
			if (best == INITIAL_VALUE ||
			get_visual_class (&visuals[best]) == StaticGray)
			best = visual_count;
			}   break;

			case StaticGray: {
			if (best == INITIAL_VALUE)
			best = visual_count;
			}   break;
			}/*switch*/
		}/*if*/
	} while (--visual_count >= 0);/*until*/

	if (best != INITIAL_VALUE) {
		//*visual = visuals[best].visual;
		memcpy((void*)visual, (void*) &(visuals[best]), sizeof(XVisualInfo));
		XFree ((char *) visuals);
	} 
}


// colormap accounting for x11
// the msdev browser show this in err it's in #ifdef IS_X11
// please return to your regularly sceduled programming
struct CMapEntry {
    CMapEntry( Colormap m, bool a ) : cmap(m), alloc(a) {}
   ~CMapEntry();
    Colormap cmap;
    bool     alloc;
};

CMapEntry::~CMapEntry()
{
    if ( alloc )
		XFreeColormap( QX11Info::display(), cmap );

}

static QHash<int, CMapEntry*>* cmap_dict = 0;


static void cleanup_cmaps()
{

    if ( !cmap_dict ) return;

	/*XXX cleanup CmapEntry*/
    delete(cmap_dict);
    cmap_dict = 0;
}

static Colormap choose_cmap( Display *dpy, XVisualInfo *vi )
{
    if ( !cmap_dict ) {
		cmap_dict = new QHash<int, CMapEntry*>;
		qAddPostRoutine (cleanup_cmaps);
	}
	
	CMapEntry *x = cmap_dict->value(vi->visualid);

	// found colormap for visual
	if ( x )	
		return x->cmap;

	Colormap cmap = 0;

	bool alloc = false;
	XStandardColormap *c;
	int n, i;

	// is this the delault vis 
	if ( vi->visual==DefaultVisual(dpy,vi->screen) )
		return DefaultColormap( dpy, vi->screen );

	// try to find a shared colormap
	if ( !cmap ) {
		if ( XmuLookupStandardColormap(dpy,vi->screen,vi->visualid,vi->depth,
				   XA_RGB_DEFAULT_MAP,FALSE,TRUE) ) {
			if ( XGetRGBColormaps(dpy,RootWindow(dpy,vi->screen),&c,&n,
				  XA_RGB_DEFAULT_MAP) ) {

				i = 0;
				while ( i < n && cmap == 0 ) {
					if ( c[i].visualid == vi->visualid )
					cmap = c[i].colormap;
					i++;
				}

				XFree( (char *)c );
			}
		}
	}

	// no shared cmap found
    if ( !cmap ) {
		cmap = XCreateColormap( dpy, RootWindow(dpy,vi->screen), vi->visual,
				AllocNone );
		alloc = TRUE;
    }

	// add our new colormap to the lookup for next time
    x = new CMapEntry( cmap, alloc );
    cmap_dict->insert(vi->visualid, x);

    return cmap;
}



void HQWidget::setup_window(bool use_gl)
{
	Colormap cmap;
	XVisualInfo	visual;

	bool visible = isVisible();

    if (visible) hide();

    Display * dpy = QX11Info::display();

    XVisualInfo *vi = 0;

#if USE_GLX_VISUAL

    if(use_gl){

	int index = 0;
	static int dbvisual[32];
	dbvisual[index++] = GLX_RGBA;
	dbvisual[index++] = GLX_RED_SIZE; 
	dbvisual[index++] = 1;
	dbvisual[index++] = GLX_GREEN_SIZE; 
	dbvisual[index++] = 1;
	dbvisual[index++] = GLX_BLUE_SIZE; 
	dbvisual[index++] = 1;
	dbvisual[index++] = GLX_DEPTH_SIZE; 
	dbvisual[index++] = 1;
	if(this->my_aa){
		dbvisual[index++] = GLX_SAMPLE_BUFFERS_ARB; 
		dbvisual[index++] = 1;
	}
	dbvisual[index++] = GLX_DOUBLEBUFFER;
	dbvisual[index]   = None;

#ifdef NO_DYNAMIC_OPENGL
	vi = glXChooseVisual(dpy, DefaultScreen(dpy), dbvisual);
#else
#ifdef HPUX_SYSTEM
	auto shl_t library_handle;

	library_handle = shl_load("libGL.sl",
	    BIND_NONFATAL|BIND_DEFERRED|DYNAMIC_PATH|BIND_VERBOSE, 0L);

	if(library_handle) {

	    typedef XVisualInfo* (* routine_t)(Display* dpy, int screen, int* attribList);
		routine_t routine;

	    shl_findsym(&library_handle, "glXChooseVisual", TYPE_PROCEDURE, &routine);

	    if (!routine) {
		shl_unload(library_handle);
	    }else{

		vi = routine(dpy, DefaultScreen(dpy), dbvisual);
	    }
	}

#else
	auto void * library_handle;

	library_handle = dlopen("libGL.so", RTLD_LAZY);

	if(library_handle) {

	    typedef XVisualInfo* (* routine_t)(Display* dpy, int screen, int* attribList);
		routine_t routine;

	    routine = (routine_t) dlsym(library_handle, "glXChooseVisual");

	    if (!routine) {
		dlclose(library_handle);
	    }else{

		vi = routine(dpy, DefaultScreen(dpy), dbvisual);
	    }
	}
#endif /*HPUX_SYSTEM*/
#endif /*NO_DYNAMIC_OPENGL*/
    }
#endif /*USE_GLX_VISUAL*/

    
    if(vi == 0){
	    // get our own X visual
	    get_best_visual(dpy, &visual);
	    vi = &visual;
    }else{

	    my_have_gl_visual = true;
    }

    XSetWindowAttributes a;

    // find best colormap
    cmap = choose_cmap( dpy, vi );

    a.colormap = cmap;
    QPalette q;
    QColormap qcm = QColormap::instance();
    
    a.background_pixel = qcm.pixel(q.color(backgroundRole()));
    a.border_pixel = qcm.pixel(Qt::black);

    Window p = RootWindow( dpy, DefaultScreen(dpy) );
    if ( parentWidget() )
		p = parentWidget()->winId();

    Window w = XCreateWindow( dpy, p,  x(), y(), width(), height(),
			      0, vi->depth, InputOutput,  vi->visual,
			      CWBackPixel|CWBorderPixel|CWColormap, &a );

#if 0
	XWindowAttributes aa;
	XGetWindowAttributes(dpy, w, &aa);
#endif

    //record for later
    my_windowid=(void*)w;
				  
    Window wtl = topLevelWidget()->winId();
    Window *cmw;
    Window *cmwret;
    int count;

    if ( XGetWMColormapWindows(dpy, wtl,&cmwret,&count) ){

		cmw = new Window[count+1];
        memcpy( (char *)cmw, (char *)cmwret, sizeof(Window)*count );

		XFree( (char *)cmwret );

		int i;
		for ( i=0; i<count; i++ ) {
			if ( cmw[i] == winId() ) {		// replace old window
			cmw[i] = w;
			break;
			}
	}

	if ( i >= count )			// append new window
	    cmw[count++] = w;
    } else {
		count = 1;
		cmw = new Window[count];
		cmw[0] = w;
    }

    XSetWMColormapWindows( dpy, topLevelWidget()->winId(), cmw, count );
    delete [] cmw;

    XFlush(dpy);

    create( w );

    if ( visible ) show();

    XFlush(dpy);

	//record for later
	my_colormap = (void*)cmap;
}

#endif //IS_X11


bool HQWidget::GetKeyState(unsigned int key, int &flags)
{
	return key_states.count(key) == 0 ? 0 : key_states[key];
}

struct DriverNamePair
{
	QString UiName;
	const char *DriverName;
};

#define countof(x) sizeof(x)/sizeof(x[0])

const char * HQWidget::ChooseDriver()
{
#ifdef SOLARIS_SYSTEM
	const char * driver = 0;

	switch( QMessageBox::information( 0, "Qt HOOPS Viewer", 
		"Do you want use:", "&OpenGL",
		"&X11", 
		0)) 
	{ 
		case 0:
			driver = "opengl";
			break;
		case 1:
			driver = "x11";
			break;
	}

	return driver;

#else
	const DriverNamePair DRIVERS[] = {
#ifndef IS_OSX
	{"&OpenGL","opengl"},
#endif
	{"OpenGL &2","opengl2"},
	{"&DirectX 9","dx9"},
	{"&X11","x11"},
	{"&GDI","msw"},
	{"Cocoa OpenGL", "cocoa_opengl"}
	};	

	VList<const DriverNamePair*> available;

	// Check available drivers
	for (int i = 0 ; i < countof(DRIVERS) ; i++)
	{	
		if (HC_QShow_Existence(H_FORMAT_TEXT("/driver/%s",DRIVERS[i].DriverName),"self"))	
			available.AddLast(&DRIVERS[i]);
	}	

	const char *driver = 0;

	// If there's only one driver available, use it.
	if (available.Count() == 1)	
		driver = available.PeekFirst()->DriverName;	

	// Otherwise show a pop-up with the available drivers to let the user choose one.
	else if (available.Count() > 1)
	{
		QMessageBox msgBox(QMessageBox::Question,"Qt HOOPS Viewer","Do you want to use:");

		available.ResetCursor();
		while(available.PeekCursor())
		{
			msgBox.addButton(available.PeekCursor()->UiName,QMessageBox::AcceptRole);	
			available.AdvanceCursor();
		}

		msgBox.exec();
		QString which = msgBox.clickedButton()->text();			

		for (int i = 0 ; i < countof(DRIVERS) ; i++)
		{
			if (which == DRIVERS[i].UiName)
			{
				driver = DRIVERS[i].DriverName;
				break;
			}
		}
	}

	return driver;
#endif
}
