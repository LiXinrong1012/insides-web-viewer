// SoccerHQWidget.h - public interface for the HOOPS/Qt class SoccerHQWidget 
// 
// More about this class 
  
#ifndef SOCCERHQWIDGET_H 
#define SOCCERHQWIDGET_H 

// Qt Includes 
#include <QLabel> 
#include <QWidget> 
#include <QMenu> 
#include <QSlider> 

// HOOPS/Qt Includes 
#include "HQWidget.h" 

#define DEBUG_PRINT_DIALOG				0x00000002

class SoccerHQWidget : public HQWidget 
{ 

 Q_OBJECT 

public: 

	SoccerHQWidget(QWidget* parent, const char* name ,  
	  const char * FileName = 0); 
	~SoccerHQWidget(); 
  

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

	void OnRunMyCode() ;

	void OnSelect();
	void OnSelectByWindow();
	
	void OnDeleteLayers(); 
	void OnCreateRectangle(); 

protected: 

	void SetupView() ;
	void Init(); 


private: 

	void load(const char * filename); 




}; 
  

#endif 

