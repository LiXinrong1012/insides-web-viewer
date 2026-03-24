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
// $Header: /files/homes/master/cvs/hoops_master/qthoopsrefapp_4/MyHQWidget.h,v 1.60 2009-12-17 22:34:28 reuben Exp $
//


#ifndef MYHQWIDGET_H
#define MYHQWIDGET_H

#include <QLabel>
#include <QWidget>
#include <QMenu>
#include <QSlider>
#include <QToolButton>
#include <QDialog> 
#include <QIcon>
#include <QString>
#include <QObject>
#include <QToolBar>
#include <QTreeWidgetItem>

#include "HQWidget.h"
#include "HQFrameRateDlg.h"
#include "HStream.h"
#include "HQApplication.h"

class HQWindowColorPickerDlg;
class MyHQWidget;
class HQSegmentBrowserFrame;
class HOpMoveHandle;
class HQNewFrameRateDialog;


class MyHQWidget : public HQWidget
{
    Q_OBJECT
public:

    MyHQWidget( QWidget* parent, HQApplication* app, QString const & name = "", int aa = 0, QString const & FileName = "", 
			HQSegmentBrowserFrame *segBrowser=0);
    ~MyHQWidget();

	void SetQueryDialogText(char* message);
	void ShowQueryDialog();

	//these function create our local menus
	QMenu * GetManipulateMenu();
	QMenu * GetCreateMenu();
	QMenu * GetSelectionMenu();
	QMenu * GetViewMenu();
	QMenu * GetToolMenu();

	void SetHasInitialView(bool has_init_view);

	static void ProcessFilters(QString & filters, const char * file_types);

signals:
	void load_successful();

public slots:

    void OnLoad();
	void OnSaveFileAs();
	void OnPrint();
	void OnPrintPage(QString const & filename);
	void OnClear();

	void OnXyPlane();
	void OnXzPlane();
	void OnYzPlane();

	void OnApertureSelect();
	void OnWindowSelect();
	void OnDeleteSelectionList(); 

	void OnOrthographic();
	void OnPerspective();

	void OnTranslate();

	void OnWireframe();
	void OnFlatShaded();
	void OnGouraudShaded();
	void OnPhongShaded();
	void OnHiddenLine();
	void OnHiddenLineFast();
	void OnSilhouette();
	void OnWireframeWithSilhouette();
	void OnShadedWireframe();
	void OnVertices();
	void OnShadedVertices();

	void OnColorIndexInterpolation();
	void OnColorInterpolation(); 
	void OnGenerateSampleData(); 

	void OnZoom();
	void OnZoomToExtents();
	void OnZoomToWindow();
	void OnRotate(); 
	void OnOrbit();
	void OnPan();
	void OnWalk();
	void OnSmoothTransition();

	void OnViewLevelOfDetail();
	void OnViewLevelOfDetailOptions();
	void OnViewLevelOfDetailThreshold();

	void OnViewFrameRateOptions();
	void OnViewFROptsChange();
	void OnFRTimerDone();

	void OnViewDisplayLists();

	void OnViewPolygonHandednessRight();
	void OnViewPolygonHandednessLeft();
	void OnViewPolygonHandednessNone();

	void OnViewCoordinateSystemLeftHanded();
	void OnViewCoordinateSystemRightHanded();
	void OnOverlappedText();

	void OnViewBackplaneCullingOn();
	void OnViewBackplaneCullingOff();

	void OnCreateSphere(); 
	void OnCreateCone(); 
	void OnCreateCylinder(); 
	void OnCreateNurbs3D();
	void OnCreateNurbsCurve();

	void OnWindowBackgroundColor();


	void OnToolsVisibilityEdges();
	void OnToolsVisibilityLines();
	void OnToolsVisibilityFaces();
	void OnToolsVisibilityLights();
	void OnToolsVisibilityMarkers();
	void OnToolsVisibilityCuttingLines();
	void OnToolsVisibilityCuttingFaces();
	void OnToolsVisibilityCuttingPlanes();
	void OnToolsVisibilityText(); 
	void OnToolsVisibilityAxis(); 
	void OnToolsVisibilityBoundingBox(); 
	void OnToolsVisibilityLightFollows(); 
	void OnToolsVisibilityShadows(); 

	void OnToolsTextTransformsOff();
	void OnToolsTextTransformsOn();
	void OnToolsTextTransformsPosition(); 
	void OnToolsTextFontArial();
	void OnToolsTextFontRoman();
	void OnToolsTextFontStroked();

	void OnQuickmovesDefault();
	void OnQuickmovesOverlay();
	void OnQuickmovesXOR();
	void OnQuickmovesSpriting();

	void OnDisplayStats();
	void OnDisplayTimeStats();
	
	void OnObjectClash();

	void OnSubtract();
	void OnUnion();
	void OnIntersect();
	void OnEdgeSelectLevel();
	void OnFaceSelectLevel();
	void OnBodySelectLevel();
	void OnSegmentSelectLevel();
	void OnEntitySelectLevel();

	void OnFrontView();
	void OnBackView();
	void OnTopView();
	void OnBottomView();
	void OnLeftView();
	void OnRightView();
	void OnIsometricView();


	void OnFreehandMarkup();
	void OnRectangleMarkup();
	void OnCircleMarkup();
	void OnTextMarkup();
	void OnSaveMarkup1(bool save);
	void OnSaveMarkup2(bool save);


	void OnAnnotateModel();
	void OnMeasureDistance();
	void OnCreateCuttingPlane();
	void OnCreateTwosideSection();
	void OnCreateThreesideSection();
	void OnQuery();
	void OnAnimate();

	void OnAnimateBack();
	void OnAnimatePlayPause();
	void OnAnimateStop();

	void OnSegmentBrowser();

	void OnHome();
	void OnUpdateHome();
	void OnUndo();
	void OnUpdateUndo();
	void OnRedo();
	void OnUpdateRedo();
	void OnUpdateAll();

	/*menu stuff*/	
	void UpdateMenus();
	void OnRightClickTransparency();

	/*Anti-aliasing*/
	void OnAntiAliasText();
	void OnAntiAliasLinesEdges();
	void OnAntiAliasOff();

	void OnFullscreen();


protected:
	bool event( QEvent* ev);
	void SetupView();	
	void Init();

	void OnRightButtonDown(QMouseEvent * e = 0);
	void OnMidButtonDblClk(QMouseEvent * e = 0);

	void LocalSetOperator(HBaseOperator * op);
private:

	void load(QString const & filename);

	bool m_edges;
	bool m_faces;
	bool m_lines;
	bool m_lights;
	bool m_markers;
	bool m_text;
	bool m_color_index_int;
	bool m_color_int;
	bool m_axis_on;
	bool m_light_follows;
	bool m_shadows_on;
	bool m_bounding_on;
	bool m_has_initial_view;
	bool fullscreen_on;

	QMenu *m, *aa;
	QAction *m_aaoff, *m_aatext, *m_aalines, *m_fullscreen;

	void dropEvent(QDropEvent*);
	void dragEnterEvent(QDragEnterEvent*);



	bool m_aa_lines;
	bool m_aa_text;
	bool m_aa_onoff;
	int  m_aa;

	QLabel * query_dialog;

	// LOD dialog
	QWidget * lod_control;
	QSlider * lod_slider;
	QLabel * lod_label;

	// Frame Rate dialog
	//HQFrameRateDlg * framerate_dlg;
	HQNewFrameRateDialog*		new_frame_rate_dlg;

	// Background Color Picker Dialog 
	HQWindowColorPickerDlg * wnd_color_picker_dlg;

	//timer
	QTimer * FRtimer;

	//menu stuff	
	void CreateMenus();
	
	QMenu * manipulate_menu;
	int orbit_m;	
	int zoom_m;
	int pan_m;
	int zoomw_m;
	int zoome_m;
	int smootht_m;

	QMenu *create_menu;
	int sphere_m;
	int cylinder_m;
	int cone_m;
	int cutting_m;
	int nurbs3d_m;
	int nurbs_m;
	int text_m;

	QMenu *selection_menu;
	int aperature_m;
	int window_select_m;

	QMenu *tools_menu;
	int segment_browser_m;

	QMenu *view_menu;
	int orthographic_m;
	int perspective_m;
	int lod_m;
	int lodcontrol_m;
	int framerate_m;
	int framerateopts_m;
	int display_m;
	int animate_m;
	int data_m;
	int window_color_m;

	QMenu *hand_menu;
	int right_m;
	int left_m;
	int none_m;

	QMenu *csys_menu;
	int csys_right_m;
	int csys_left_m;

	QMenu *bpl_menu;
	int bpl_on_m;
	int bpl_off_m;

	HQApplication* m_hqapplication;

	QString deffered_filename;
        QString m_lastFile;
	HQSegmentBrowserFrame *m_segBrowser;
//	QFrame *m_segBrowser;
	HOpMoveHandle *m_pHandleOperator;

	HPoint m_PositionOnRightClick;
	HC_KEY m_KeyUnderCursor;
	float m_default_transmission;

public:
	QString last_file;
	FramerateUi::Dialog*			framerateui;
};

class HQNewFrameRateDialog : public QDialog {
	Q_OBJECT

private:
	MyHQWidget* my_hqwidget;

	public:
	HQNewFrameRateDialog(MyHQWidget* w);

	public slots:

	void accept();
};




class HQWindowColorPickerDlg : public QDialog {

    Q_OBJECT

	public:
	HQWindowColorPickerDlg(QWidget * parent, HBaseView * pBaseView);
	~HQWindowColorPickerDlg();

	public slots:
	void choose_window_top_color();
	void choose_window_bottom_color();

	void ok_clicked();
	void cancel_clicked();

	protected:
	void showEvent(QShowEvent * e);

	private:
	HBaseView * mHBaseView;

	QColor mWindowTopColor;
	QColor mWindowBottomColor;

	QFrame * color1;
	QFrame * color2;

};



// custom toolbar button to indicate if keyboard state info when mouse key was released
class HQToolButton : public QToolButton{
	Q_OBJECT

	public:
	HQToolButton ( const QIcon & iconSet, const QString & textLabel, const QString & grouptext, 
			QObject * receiver, const char * slot, QToolBar * parent, const char * name = 0 );
	virtual ~HQToolButton();

	signals:
	void Released(bool);

	protected:
	virtual void mouseReleaseEvent(QMouseEvent * e);
};



class HQSegmentTree;
class QCheckBox;
class QListViewItem;

class TK_My_Initial_View : public HTK_Camera 
{
private:
	MyHQWidget*		m_pMyWidget;

public:
	TK_My_Initial_View(MyHQWidget* pMyWidget) : HTK_Camera(TKE_View) { m_pMyWidget = pMyWidget; }

	TK_Status	Interpret(BStreamFileToolkit &tk, ID_Key key, int variant) alter;
	TK_Status   Execute (BStreamFileToolkit & tk) alter;
};

class W3D_Image : public BBaseOpcodeHandler
{
private:
	W3D_Image(const W3D_Image&);
	W3D_Image& operator=(const W3D_Image&);

protected:

	char *                  m_name;         /*!< internal use; name applied to image (if any) */
	int                     m_name_length;  /*!< internal use; Length of name */
	int                     m_size[2];
	char                    m_bpp;

	//! internal use
	void    set_name (char const * string) alter;
	//! internal use
	void    set_name (int length) alter;

public:
	/*! constructor */
	W3D_Image () : BBaseOpcodeHandler ((unsigned char)0xE0), m_name (0), m_name_length (0), m_bpp(0)
	{ m_size[0] = m_size[1] = 0; }
	~W3D_Image();

	TK_Status   Read (BStreamFileToolkit & tk) alter;
	TK_Status   Write (BStreamFileToolkit & tk) alter;
	TK_Status   Execute (BStreamFileToolkit & tk) alter;
	void        Reset (void) alter;

	/*! Sets the name of the image.  Allocates the buffer and copies the string */
	void            SetName (char const * string) alter                 { set_name (string);        }
	/*! Sets the name buffer.  Allocates a buffer large enough to hold a string of 'length' characters */
	void            SetName (int length) alter                          { set_name (length);        }
	/*! Returns the image name string */
	char const *    GetName (void) const                                { return m_name;            }
	/*! Returns the image name string buffer, which may be modified directly */
	char alter *    GetName (void) alter                                { return m_name;            }

	void            SetSize (int x, int y )                             { m_size[0] = x; m_size[1] = y ;}
	int const*      GetSize (void) const                                { return m_size;            }
	int alter*      GetSize (void) alter                                { return m_size;            }

	void            SetBitDepth( char bpp )                             { m_bpp = bpp;              }
	char const      GetBitDepth (void) const                            { return m_bpp;            }
	char alter      GetBitDepth (void) alter                            { return m_bpp;            }

};


#endif




