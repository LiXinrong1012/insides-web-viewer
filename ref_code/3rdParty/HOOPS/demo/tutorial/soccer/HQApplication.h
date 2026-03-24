// HQApplication.h - Public interface for HOOPS/Qt class HQApplication 
// 
// About this class 
#ifndef HQAPPLICATION_H 
#define HQAPPLICATION_H 

// Qt Headers 
#include <QMainWindow> 
#include <QEvent> 

class QToolButton;
class QWorkspace;

class HQApplication : public QMainWindow 
{ 
 Q_OBJECT 

public: 

    HQApplication(QApplication * p, const char * filename = 0);
	HQApplication(const char * filename); 
	~HQApplication();  

private slots: 

	void myclose();  
	void new_window();  
	void load(); 
	void about();

	void MDIOnPrint();
	void MDIOnSaveFileAs();
	void MDIOnZoomToExtents();
	void MDIOnZoomToWindow();
	void MDIOnOrbit();
	void MDIOnZoom();
	void MDIOnPan();
	void MDIOnSelect();
	void MDIOnSelectByWindow();
	void MDIOnCreateSphere();
	void MDIOnCreateCone();
	void MDIOnCreateCylinder();	
	void MDIOnRunMyCode() ;
private: 

	void load(const char * filename); 
	QToolBar * tools; 

	//used with MDI only
	QWorkspace * qws;
	struct vhash_s * wh; 

protected: 

	static int count;
    static QApplication * myparent;
    void closeEvent( QCloseEvent * );

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
    static QPixmap * selectIcon;
    static QPixmap * selectwIcon;
    static QPixmap * sphereIcon;
    static QPixmap * coneIcon;
    static QPixmap * cylinderIcon;
    static QPixmap * deletelayerIcon;
    static QPixmap * rectanglemkpIcon;
	static QPixmap * runmycodeIcon ;


    QAction * newAct;
    QAction * openAct;
    QAction * printAct;
    QAction * zExtentsAct;
    QAction * zWindowAct;
    QAction * orbitAct;
    QAction * zoomAct;
    QAction * panAct;
    QAction * selectAct;
    QAction * selectWindowAct;
    QAction * sphereAct;
    QAction * coneAct;
    QAction * cylAct;
	QAction * runAct ;
    QAction * deleteLayerAct;
    QAction * rectMarkupAct;

}; 

#endif  

