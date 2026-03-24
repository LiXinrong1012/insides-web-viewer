#ifndef MAIN_UI_H
#define MAIN_UI_H

#include <QtGui/QMainWindow>
#include "ui_main_ui.h"
#include "precore/modeldocument.h"
#include "base/ParametersManager.h"

#include "ribbonwindow.h"

#include "localserver.h"

class ModelTreeModel;
class PreHQWidget;

class QCheckBox;
class QDoubleSpinBox;

class IExchangeFile2;

namespace Base{
	class AnimationControlWidget;
	class View;
	class DoubleLineEdit;
}
using Base::View;

class main_ui : public RibbonWindow
	,public Base::IParametersModificationListener
	,public IMessageListener
{
	Q_OBJECT

public:
	main_ui(QWidget *parent = 0, Qt::WFlags flags = 0,const QString& tdyFileName=QString(),
		const QString& serverName=QString());
	~main_ui();

	virtual void onMessageReceived(const ViewerSocketToServerMessage& mess);

protected:
	void keyPressEvent(QKeyEvent* event);
	virtual bool parameterChanged(Base::ParametersGroup* parameterManager,
		const Base::ParameterItem* newParameter,const Base::ParameterItem* oldParameter);
	void closeEvent(QCloseEvent* event);

private:
	void createAction();
	void createRibbon();
	void createMenuFile();
	void createQuickAccessBar();
	void createStatusBar();

	private slots:
		void onNew();
		void onSave();
		void onOpen();
		void onExportTDY();

		void loadStartupFileName();
		void onImportTDY(const QString& fileName);
		void onFreshModel();	/// 重新读入模型
		void onImportTDY();
		void onImportTDY_Debug();
		void onCloseAllWindows();
		void onGoIn();
		void onGoOut();
		void onConfiguration();
		void onActiveViewChanged(View* view);



		void onLoadSimpleData();
		void onLoadSimpleEigen();


		void onReset();
		void onFinishedLoadingRes();

		void onSaveState();
		void onLoadState();
		void onSaveStateAs();
		void onLoadStateFrom();

		void onViewFull(bool checked);
		void onViewNone();
		void onViewModelTree();
		void onViewViewAll();

		void showConstraintStateChanged(int b);
		void showFEMMarkerStateChanged(int b);
		void showMassCenterStateChanged(int b);
		void showInitialStateChanged(int b);
		void showIMarkerStateChanged(int b);
		void showJMarkerStateChanged(int b);

		void spinSizeConstraintValueChanged(double v);
		void spinSizeMarkerValueChanged(double v);
		void spinSizeForceScaleValueChanged(double v);
		void spinSizeMassCenterValueChanged(double v);
		void spinSizeShellEdgeValueChanged(double v);
		void spinSizeShellVertexValueChanged(double v);
		void spinSizeEigenDisplayScaleValueChanged(double v);

private:
	Ui::main_uiClass ui;
	INSIDES::ModelDocument*		_document;
	ModelTreeModel*		_modeltreeModel;
	Qtitan::RibbonPage*	_hotRibbonPage;	//Current hot ribbon page.by Jerry, 2014.8.5
	//PreHQWidget*		_hoopsView;
	QString				_startupFileName;
	QFileInfo			_tdyModelFile;
	LocalServer*		_localServer;

	QAction *addAction;
	QAction *undoAction;
	QAction *redoAction;
	QMenu*	_menuExport;

	/// 文件相关操作
	QAction* _actionFileNew;
	QAction* _actionFileSave;
	QAction* _actionFileNewTDY;
	QAction* _actionFileFreshTDY;
	QAction* _actionFileExit;

	// 模型相关操作
	QAction* _actionLoadTDYResult;
	QAction* _actionLoadTDYEig;
	QAction* _actionSaveLayout;
	QAction* _actionLoadLayout;
	QAction* _actionSaveLayoutAs;
	QAction* _actionLoadLayoutFrom;
	QAction* _actionGoInto;
	QAction* _actionGoOut;

	// 视图相关
	QAction* _actionViewFull;
	QAction* _actionViewNone;
	QAction* _actionViewModel;
	QAction* _actionViewAll;

	// 树相关操作
	QAction* _actionEditParameters;
	QAction* _actionResetModel;

	IExchangeFile2*	_importTDY;
	Base::AnimationControlWidget* _animationControlWidget;
	Qt::WindowStates _stateWindow;
	Qt::WindowStates _stateWindow2;

	QCheckBox*	_cbShowConstraint;
	QCheckBox*	_cbShowFEMMarker;
	QCheckBox*	_cbShowMassCenter;
	QCheckBox*	_cbShowInitial;
	QCheckBox*	_cbShowIMarker;
	QCheckBox*	_cbShowJMarker;

	Base::DoubleLineEdit*	_spinSizeContraint;
	Base::DoubleLineEdit* _spinSizeForceScale;
	Base::DoubleLineEdit* _spinSizeMarker;
	Base::DoubleLineEdit* _spinSizeMassCenter;
	Base::DoubleLineEdit* _spinSizeShellEdge;
	Base::DoubleLineEdit* _spinSizeShellVertex;
	Base::DoubleLineEdit* _spinSizeEigenDisplayScale;

	void createActions();
	void loadModelTreePlugin();

	/// 初始化默认的参数列表
	void initDefaultParameters();
	
	void readSetting();
	void writeSetting();
	void loadPlugins();
	void load3rdPartyShapes();
	void loadViewPlugins();

	void createGroupModel(Qtitan::RibbonGroup& page);
	void createGroupState(Qtitan::RibbonGroup& page);
	void createGroupShowHide(Qtitan::RibbonGroup& page);
	void createGroupAnimation(Qtitan::RibbonGroup& page);
	void createGroupSettings(Qtitan::RibbonGroup& page);
	void createGroupView(Qtitan::RibbonGroup& page);
	void createGroupShowHideOneItem(Qtitan::RibbonGroup& page,QCheckBox** checkBox,const QString& name, const char* slotName,const QString& paraName);
	void createGroupSize(Qtitan::RibbonGroup& page);
	void createGroupSizeOneItem(Qtitan::RibbonGroup& page,const QString& label, 
		Base::DoubleLineEdit** spinBoxxx,const QString& paraName, const char* slotName);

};

#endif // MAIN_UI_H
