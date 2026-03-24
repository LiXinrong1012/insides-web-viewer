// AnalysisHQWidget.h - public interface for the HOOPS/Qt class AnalysisHQWidget 
// 
// More about this class 
//
// $Header: /files/homes/master/cvs/hoops_master/analysis/AnalysisHQWidget.h,v 1.2 2007-11-20 00:54:18 chad Exp $
  
#ifndef ANALYSISHQWIDGET_H 
#define ANALYSISHQWIDGET_H 

// Qt Includes 
#include <QLabel> 
#include <QWidget> 
#include <QMenu> 
#include <QSlider> 

// HOOPS/Qt Includes 
#include "HQWidget.h" 
  
#define DEBUG_PRINT_DIALOG				0x00000002

class AnalysisHQWidget : public HQWidget 
{ 

 Q_OBJECT 

public: 

	AnalysisHQWidget(QWidget* parent, const char* name ,  
	  const char * FileName = 0); 
	~AnalysisHQWidget(); 

	bool	m_bDisplayIsolines;
	bool	m_bColorInterpolation;

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

	void OnSelectByWindow();
	void OnDeleteSelection() ;

	void OnRenderModeGouraudShaded() ;
	void OnRenderModeHiddenLine() ;
	void OnRenderModeWireframe() ;

	void OnMapData() ;
	void OnDisplayIsolines() ;
	void OnColorInterpolation() ;
	void OnDisplayQuadInterpolate() ;
	void OnAnimateColormap() ;

protected: 

	void Init(); 


private: 

	void load(const char * filename); 

}; 
  

#endif 

