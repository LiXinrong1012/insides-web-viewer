#pragma once

#include "prev3dcore/qt4_common/HQWidget.h" // HOOPS/Qt Includes 

// Qt Includes 
#include <QLabel> 
#include <QWidget> 
#include <QMenu> 
#include <QSlider> 


#define DEBUG_PRINT_DIALOG				0x00000002

class BaseHQWidget : public HQWidget 
{ 

	Q_OBJECT 

public: 

	BaseHQWidget(QWidget* parent, QString const & name=QString() ,  
		QString const & FileName = 0); 
	~BaseHQWidget(); 


	QAction* getActionOpOrbit(){return _acOpOrbit;}
	QAction* getActionOpPan(){return _acOpPan;}

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


		// Visibility
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

		// Render mode
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

		/// View type
		void OnFrontView();
		void OnBackView();
		void OnTopView();
		void OnBottomView();
		void OnLeftView();
		void OnRightView();
		void OnIsometricView();
		void OnRotate90View();
		void onRotateMinus90View();
		void onRotate30View(){RotateView(30);}
		void onRotateMinus30View(){RotateView(-30);}
		void OnRotateXView();

protected: 

	void SetupView();  
	void Init(); 
	void RotateView(double angle);
	void LocalSetOperator(HBaseOperator * op);


	virtual void OnRightButtonDown(QMouseEvent * e = 0);
	virtual void keyPressEvent ( QKeyEvent * e );

	void initParameters();

	void saveCameraState(QDataStream* out);
	void loadCameraState(QDataStream* in);



	QMenu*	_mainContextMenu;
	QMenu*	_menuVisibility;
	QMenu*	_menuRenderMode;
	QMenu*	_menuViewType;
	QMenu*	_menuBaseOperator;

	QAction* _acOpOrbit;
	QAction* _acOpPan;

	HCamera	_defaultCamera;

	virtual void initContextMenu();
	void initMenuVisibility();
	void initMenuRenderMode();
	void initMenuViewType();
	void initMenuBaseOperator();

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
}; 


