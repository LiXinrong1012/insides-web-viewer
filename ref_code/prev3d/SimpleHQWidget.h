// SimpleHQWidget.h - public interface for the HOOPS/Qt class SimpleHQWidget 
// 
// More about this class 

#ifndef SIMPLEHQWIDGET_H 
#define SIMPLEHQWIDGET_H 

// Qt Includes 
#include <QLabel> 
#include <QWidget> 
#include <QMenu> 
#include <QSlider> 

#include "prev3d/prev3d_global.h"
#include "prev3dcore/qt4_common/HQWidget.h" // HOOPS/Qt Includes 
// HOOPS/Qt Includes 

#define DEBUG_PRINT_DIALOG				0x00000002

class SimpleHQWidget : public HQWidget 
{ 

	Q_OBJECT 

public: 

	SimpleHQWidget(QWidget* parent, QString const & name ,  
		QString const & FileName = 0); 
	~SimpleHQWidget(); 


	public slots: 

		void OnLoad();
		void OnSaveFileAs();
		void OnPrint();

		void OnZoomToExtents();
		void OnZoomToWindow();

		void OnZoom();
		void OnOrbit();
		void OnPan();

		void OnCreateSphere(); 
		void OnCreateCone(); 
		void OnCreateCylinder();

		void OnRunMyCode(); 

		void OnClose();


protected: 

	void SetupView();  
	void Init(); 


private: 

	void load(QString const & filename); 



}; 


#endif 

