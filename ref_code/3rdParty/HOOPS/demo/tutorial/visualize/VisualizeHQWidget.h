// VisualizeHQWidget.h - public interface for the HOOPS/Qt class VisualizeHQWidget 
// 
// More about this class 
  
#ifndef VISUALIZEHQWIDGET_H 
#define VISUALIZEHQWIDGET_H 

// Qt Includes 
#include <QLabel> 
#include <QWidget> 
#include <QMenu> 
#include <QSlider> 

// HOOPS/Qt Includes 
#include "HQWidget.h" 

#include "HTManager.h"
class HTClient;

#define DEBUG_NO_WINDOWS_HOOK				0x00000040 
#define DEBUG_16BIT_ZBUFFER					0x00200000 
#define DEBUG_PRINT_DIALOG					0x00000002

class VisualizeHQWidget : public HQWidget 
{ 

 Q_OBJECT 

public: 

	VisualizeHQWidget(QWidget* parent, const char* name ,  
	  const char * FileName = 0); 
	~VisualizeHQWidget(); 

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
	
	void OnBuildLODs();        //!< Create Levels of Detail for the model
	void OnLOD1();             //!< Clamp to LOD level 1
	void OnLOD2();             //!< Clamp to LOD level 2
	void OnLODOriginal();      //!< Draw the original, full resolution model
	void OnEnableFramerate();  //!< Enable constant framerate logic
	void OnDisableFramerate(); //!< Disable constant framerate logic
	void OnWalkOperator();     //!< Set the current operator to HOpCameraWalk

protected: 

	void SetupView() ;
	void Init(); 


private: 

	void load(const char * filename); 

}; 
  

#endif 

