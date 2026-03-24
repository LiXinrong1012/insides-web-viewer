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
// $Header: /files/homes/master/cvs/hoops_master/qthoopsrefapp_4/HQApplication.h,v 1.32 2009-09-10 17:56:52 conor Exp $
//


#ifndef HQAPPLICATION_H
#define HQAPPLICATION_H

#include <qmainwindow.h>
#include <qevent.h>

#include "HQPrintDlg.h"
#include "HQSegmentBrowserFrame.h"

class QToolButton;
class MyHQWidget;
class HQToolButton;
class HQSegmentBrowserFrame;
class HQPrintDlg;

class HQApplication : public QMainWindow
{
    Q_OBJECT
public:
    HQApplication(QApplication * p, QString const & filename = "");
    HQApplication(QString const & filename, int aa = 0);
	~HQApplication();

    void RunPrintDialog(MyHQWidget * w);

	void OnFullscreen(bool on);	
	QAction* homeAct;
	QAction* undoAct;
	QAction* redoAct;
private slots:
 
    void myclose();				
    void load();
    void about();
    void SetToolbarState(bool is_on);
    void new_window();
	void OnViewLevelOfDetailZro();
	void OnViewLevelOfDetailOne();
	void OnViewLevelOfDetailTwo();
	void SetUpMenus();

	/*Anti-aliasing*/
	void OnAntiAlias0x();
	void OnAntiAlias2x();
	void OnAntiAlias4x();
	void OnAntiAlias8x();
	void OnAntiAliasOff();

	void OnExtraSlot1();
	void OnExtraSlot2();
	void OnExtraSlot3();
	void OnExtraSlot4();
	void OnExtraSlot5();

	void OnStaticModel();
	void OnSegLevDisplayLists();

private:

    void load(QString const & filename);

	

    QToolBar * standard_toolbar;
    QToolBar * std_views_toolbar;
    QToolBar * markup_txt_toolbar;
    QToolBar * tools_toolbar;
	QToolBar * undo_toolbar;

    static HQPrintDlg * print_dlg;

    MyHQWidget * my_widget;
	QString last_directory;

    void CreateToolbars();

protected:
    static int count;
    static QApplication * myparent;
    void closeEvent( QCloseEvent * );
	HQSegmentBrowserFrame *segBrowser;

    void CreatePixmaps();

    static QPixmap * tsaIcon;
    static QPixmap * pageIcon;
    static QPixmap * openIcon;
    static QPixmap * printIcon;
    static QPixmap * zoomextentsIcon;
    static QPixmap * zoomwindowIcon;
    static QPixmap * orbitIcon;
    static QPixmap * zoomIcon;
    static QPixmap * panIcon;
    static QPixmap * walkIcon;
    static QPixmap * selectIcon;
    static QPixmap * selectwindowIcon;
    static QPixmap * sphereIcon;
    static QPixmap * coneIcon;
    static QPixmap * cylinderIcon;
    static QPixmap * nurbsIcon;
    static QPixmap * nurb3dIcon;
    static QPixmap * translateIcon;
    static QPixmap * rotateIcon;
    static QPixmap * subtractIcon;
    static QPixmap * intersectIcon;
    static QPixmap * unionIcon;
    static QPixmap * clashDetectIcon;

    // icons for standard views toolbar buttons
    static QPixmap * frontIcon;
    static QPixmap * backIcon;
    static QPixmap * topIcon;
    static QPixmap * bottomIcon; 
    static QPixmap * leftIcon;
    static QPixmap * rightIcon;
    static QPixmap * isoIcon;

    // icons for markup toolbar buttons
    static QPixmap * freehandmkpIcon;
    static QPixmap * rectanglemkpIcon;
    static QPixmap * circlemkpIcon;
    static QPixmap * textmkpIcon; 
    static QPixmap * savemkp1Icon;
    static QPixmap * savemkp2Icon;

    // icons for tools toolbar buttons
    static QPixmap * annotateIcon;
    static QPixmap * distanceIcon;
    static QPixmap * cuttingplaneIcon;
    static QPixmap * queryIcon; 
    static QPixmap * animateIcon;

    static QPixmap * ani_backIcon;
    static QPixmap * ani_play_pauseIcon;
    static QPixmap * ani_stopIcon;

	// icons for undo toolbar buttons
	static QPixmap * homeIcon;
    static QPixmap * undoIcon;
    static QPixmap * redoIcon;

    QToolButton * page_button;
    QToolButton * open_button;
    QToolButton * print_button;
    QToolButton * zoom_extents_button;
    QToolButton * zoom_window_button;
    QToolButton * orbit_button;
    QToolButton * zoom_button;
    QToolButton * pan_button;
    QToolButton * walk_button;
    QToolButton * select_button;
    QToolButton * select_window_button;
    QToolButton * sphere_button;
    QToolButton * cone_button;
    QToolButton * cylinder_button;
    QToolButton * nurbs_button;
    QToolButton * nurb3d_button;
    QToolButton * translate_button;
    QToolButton * rotate_button;
    QToolButton * subtract_button;
    QToolButton * intersect_button;
    QToolButton * union_button;

    // buttons on standard views toolbar
    QToolButton * front_button;
    QToolButton * back_button;
    QToolButton * top_button;
    QToolButton * bottom_button;
    QToolButton * left_button;
    QToolButton * right_button;
    QToolButton * iso_button;

    // buttons on markup toolbar
    QToolButton * freehand_mkp_button;
    QToolButton * rectangle_mkp_button;
    QToolButton * circle_mkp_button;
    QToolButton * text_mkp_button;
    HQToolButton * save_mkp1_button;
    HQToolButton * save_mkp2_button;

    // buttons on tools toolbar
    QToolButton * annotate_button;
    QToolButton * distance_button;
    QToolButton * cuttingplane_button;
    QToolButton * query_button; 
    QToolButton * animate_button;


    QToolButton * ani_back_button;
    QToolButton * ani_play_pause_button;
    QToolButton * ani_stop_button;

	QAction* orbitAct;
	QAction* zoomAct;
	QAction* panAct;
	QAction* zWindowAct;
	QAction* zExtentsAct;
	QAction* smoothTransAct;
	QAction* newAct;
	QAction* openAct;
	QAction* loadAct;
	//QAction* streamAct;
	QAction* clearAct;
	QAction* clientAct;
	QAction* printAct;
	QAction* saveAct;
	QAction* closeAct;
	QAction* exitAct;
	QAction* walkAct;
	QAction* selectAct;
	QAction* selectWindowAct;
	QAction* nurbsCurveAct;
	QAction* sphereAct;
	QAction* coneAct;
	QAction* cylinderAct;
	QAction* nurb3dAct;
	QAction* translateAct;
	QAction* rotateAct;
	QAction* frontAct;
	QAction* backAct;
	QAction* topAct;
	QAction* bottomAct;
	QAction* rightAct;
	QAction* leftAct;
	QAction* isoAct;
	QAction* freehandAct;
	QAction* rectangleAct;
	QAction* circleAct;
	QAction* textAct;
	QAction* savemkp1Act;
	QAction* savemkp2Act;
	QAction* annotateAct;
	QAction* distanceAct;
	QAction* cuttingAct;
	QAction* twoSidedAct;
	QAction* threeSidedAct;
	QAction* queryAct;
	QAction* animateAct;
	QAction* aniBackAct;
	QAction* aniPlayPauseAct;
	QAction* aniStopAct;
	QAction* clashDetectAct;

	QAction* aperature_m;
	QAction* window_select_m;
	QAction* orthographic_m;
	QAction* perspective_m;
	QAction* right_hand;
	QAction* left_hand ;
	QAction* none_hand ;
	QAction* csys_right_m;
	QAction* csys_left_m ;
	QAction* bpl_on_m ;
	QAction* bpl_off_m;
	QAction* gen_lods;
	QAction* lod_zro ;
	QAction* lod_one ;
	QAction* lod_two ;
	QAction* static_m;
	QAction* segdisplaylists_m;
	QAction* display_m;

	QAction* aa0xAct ;
	QAction* aa2xAct ;
	QAction* aa4xAct ;
	QAction* aa8xAct ;
	QAction* aaOffAct ;
	int aa_level ;


};

#endif 


