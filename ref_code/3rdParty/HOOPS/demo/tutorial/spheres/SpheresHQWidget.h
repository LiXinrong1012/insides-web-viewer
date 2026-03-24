// SpheresHQWidget.h - public interface for the HOOPS/Qt class SpheresHQWidget 
// 
// More about this class 
  
#ifndef SPHERESHQWIDGET_H 
#define SPHERESQWIDGET_H 

// Qt Includes 
#include <QLabel> 
#include <QWidget> 
#include <QMenu> 
#include <QSlider> 

// HOOPS/Qt Includes 
#include "HQWidget.h" 

#define DEBUG_PRINT_DIALOG				0x00000002

#include "HIOUtilitySpheres.h"
  

class SpheresHQWidget : public HQWidget 
{ 

 Q_OBJECT 

public: 

	SpheresHQWidget(QWidget* parent, const char* name ,  
	  const char * FileName = 0); 
	~SpheresHQWidget(); 

public slots: 

    void OnLoad();
	void OnSaveFileAs();
	void OnPrint();

	void OnZoomToExtents();
	void OnZoomToWindow();

	void OnZoom();
	void OnOrbit();
	void OnPan();
	void OnObjectRotate();

	void OnCreateSphere(); 
	void OnCreateCone(); 
	void OnCreateCylinder();

	void OnRunMyCode() ;

	void OnSelectByWindow();

	void OnRenderModeShaded();
	void OnRenderModeHiddenline();
	void OnRenderModeWireframe();

	void OnChangeMaterial();
	void OnAnnotate(); 

protected: 

	void SetupView() ;
	void Init(); 

private: 

	void load(const char * filename); 

	//  must be static since SpheresHQWidget is instantiated for each document loaded
	static HIOUtilitySpheres * m_pIOUtilitySpheres;

}; 
  


#endif 

