#pragma once

#include "prev3d/prev3d_global.h"
#include "prev3dcore/basehqwidget.h"
#include <QSharedPointer>

#include "base/ParametersManager.h"

#include "precore/modeldocumentlistener.h"
#include "precore/ResultDocument.h"

namespace INSIDES{
	class IResultItem;
	class IResults;
	class BaseItem;
	
}

class SetWindowColorDialog;

using namespace INSIDES;


class ModelViewManager;
class ResultViewManager;
class EigenViewManager;
class ViewManager;
class TrackPath;
class ContourDisplaySelectorDialog;

enum trackType{TRACK_POSITION_POSTRUE,TRACK_POSITION,TRACK_POSTRUE};

class PREV3D_EXPORT PreHQWidget :
	public BaseHQWidget
	, public ModelDocumentListener
	, public IResultListener
	, public Base::IParametersModificationListener
{
	Q_OBJECT;

public:
	PreHQWidget(QWidget* parent, QString const & name=QString() ,  
		QString const & FileName = 0); 
	virtual ~PreHQWidget(void);

	QWeakPointer<ViewManager>	getViewManager()const;

	QVariant getTreeItemData(BaseItem* baseItem,int index);
	bool setTreeItemData(BaseItem* baseItem,int index,const QVariant& data);

	bool saveState(QDataStream& out);
	bool loadState( QDataStream& in);

	///记录选中的为第几节点由PreSelectionSet调用
	int getSelectSubNode()const{return _selectSubNode;}
	void setSelectSubNode(int n){_selectSubNode = n ;}

	long getTimeKey();
	void setTimePostion(float x,float y);
protected:
	/// 当模型被重致后发送
	virtual void doc_ModelReseted(BaseItem* rootItem);
	/// 显示的根节点改变后发送
	virtual void doc_RootItemChanged(BaseItem* currentRoot,BaseItem* oldRoot);

	virtual void res_ResultsDeleted();
	virtual void res_ResultsLoaded(IResults* results);

	virtual bool parameterChanged(Base::ParametersGroup* parameterManager, 
		const Base::ParameterItem* newParameter,const Base::ParameterItem* oldParameter );


public slots:
	/// Reload view according to current document status and document
	void reload();
	void redraw();


	void onSelect();
	void onSelectRegion();
	
	/// 设置为全能型的视图操作
	void onSetOmniControl();

	void testMaterialSelector();

	void onSigSetSelect(long key,int count,const int* faces,const int* vertex1,const int* vertex2);

	/// 点击添加相机跟随，Jerry, 2014.5.20
	void onAddCameraTrack(trackType type);
	///跟随位置和姿态
	void trackPositionAndPosture();
	///跟随位置
	void trackPostion();
	///跟随姿态
	void trackPosture();

	/// 点击使坐标系的Axis跟选中Marker的相同
	void onSetAxisMarker();

	/// 点击添加轨迹线
	void onAddTrackPath();
	TrackPath* addTrackPath(BaseItem* item);
	///点击添加node轨迹线
	TrackPath* addNodePath(BaseItem* item);

	/// 显示Legend相关操作
	void onDisplayLegendMenu();
	void onDisplaySelectMenu();
	void onDisplayPickMenu();
	void onAddOneLegend();
	void onAddOneContour();
	void onClearContour();

	void onAddSectionSurface();
	bool getSectionParas(QList<double>& d1Poitns,QList<double>& d1Params);
	void onAddAllSectionSurface();

	void addFrameView();
	void clearAllFrameViews();

	void saveTrackPathsState(QDataStream* pathData);
	void loadTrackPathsState(QDataStream* pathData);

	void loadHoops3DConfigData(QDataStream* hoopsData);

	//void saveBackgroundColor(QDataStream* colorData);
	//void loadBackgroundColor(QDataStream* colorData);
protected slots:
	void onContourItemAdding(IResultItem* resultItem,int secIndex,int subSecIndex,int subsubSecIndex,bool onlyUseCurrent);

	void copy();
	void paste();

	void setPickEntity();
	void setPickFace();
	void setPickElement();
	void setPickNode();

	void onEditPaths();

	void showSegmentBrowser();
	///测距
	void onMeasureDistance();
	void onOrbitVertical();
	///显示速率
	void onShowVelocity();
	void onHideVelocity();
	void showHideTimeLabel();
	void translateTime();
	void onSetWindowColor();
	void onOptions();
	void onCreateSphere();
	void onCreateCuboit();
	void testHoopsMaterial();
protected:
	virtual void Init();
	void initSelection();

	virtual void initContextMenu();

	ModelViewManager* getModelViewManager(){return _modelViewManager.data();}
	ResultViewManager* getResultViewManager(){return _resultViewManager.data();}

	void setShowVelocity(bool showOrHide);

	void flushSize();
	void initAppLogo();

	void testCreateCylinder(HMaterialLibrary& hmat,const QString& material,const QString& environment,const QString& ambient,const QString& specular,const QString& emission ,int gloss,const QString& diffuse, HC_KEY key=NULL);
private:
	QSharedPointer<ModelViewManager> _modelViewManager;
	QSharedPointer<ResultViewManager> _resultViewManager;
	QSharedPointer<EigenViewManager>	_eigenViewManager;
	ContourDisplaySelectorDialog*		_contourDisplaySelectorWidget;

	QList<QSharedPointer<ResultViewManager> >  _resultFrameViewList;
	
	int				_displayStatus;
	int				_selectSubNode;
	SetWindowColorDialog* _setWindowColorDialog;
	
};

