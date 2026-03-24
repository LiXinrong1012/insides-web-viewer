#include "PreHQWidget.h"
#include "ModelViewManager.h"
#include "ResultViewManager.h"
#include "EigenViewManager.h"
#include "HoopsUpdator.h"
#include "PreSelectionSet.h"
#include "BaseItemPosHelper.h"
#include "CameraTrack.h"
#include "TrackPaths.h"
#include "setwindowcolordialog.h"
#include "vieweroptionsdialog.h"
#include "appsettings.h"

#include "precore/modeldocument.h"
#include "precore/projectselector.h"
#include "precore/precore_data.h"
#include "precore/IResultItem.h"
#include "precore/BaseItemHelper.h"
#include "precore/FlexResultItem.h"


#include "Base/activeviewobject.h"
#include "base/ParametersManager.h"
#include "base/Console.h"
#include "base/AppConfiguration.h"

#include "coresps/HoopsShapeManager.h"

#include "HUtilitySubwindow2.h"
#include "HOpSelectAperture.h"
#include "HOpSelectArea.h"
#include "OmniControlOperator.h"
#include "HOpMarkupMeasure.h"
#include "HOpCameraOrbitTurntable.h"
#include "HOpObjectTranslate.h"
#include "HObjects.h"
#include "HOpCreateSphere.h"
#include "HOpCreateCone.h"
#include "HOpCreateCuboid.h"

#include "HUtilityGeometryCreation.h"
#include "HUtility.h"
#include "HIOManager.h"
#include "HDB.h"

#include "HSelectionSet.h"
#include "HSelectionItem.h"

#include "HMaterialLibrary.h"
#include "hc_legacy.h"

#include "testmaterialdialog.h"

#include "parasolid_kernel.h"
#include "hp_bridge.h"

#include "contourdisplayselectorwidget.h"
#include "contourdisplayselectordialog.h"
#include "LegendManager.h"
#include "Hoops3DConfiguration.h"

#include <osg/Matrixf>
#include <osg/Quat>
#include <osg/Vec3f>

#include <QApplication>
#include <QClipboard>
#include <QFileDialog>

#include <stdio.h>

#include "sectioninputdialog.h"
#include "pathpropertydialog.h"

#include "prev3dcore/SegmentBrowserDialog.h"

#include "pubbase/mimedata.h"

using namespace Base;

PreHQWidget::PreHQWidget( QWidget* parent, QString const & name/*=QString() */,
	QString const & FileName /*= 0*/ )
	:BaseHQWidget(parent,name,FileName)
	,_contourDisplaySelectorWidget(NULL)
	,ModelDocumentListener(20)
	,_selectSubNode(0)
	,_setWindowColorDialog(NULL)
{
	if(myResultDocument()->getResults())
		_displayStatus=ActiveViewObject::instance()->getModelStatus();
	else
		_displayStatus=ActiveViewObject::MODEL_STATUS_MODEL;

	Hoops3DConfiguration::instance();
	
	registerModelUpdatingFunctions();
	registerResultUpdatingFunctions();
	registerEigenUpdatingFunctions();

	reload();

	myResultDocument()->attachListener(this);
	myDocument()->attachListener(this);
	AppConfiguration::instance()->getParametersManager()->attach(this);
	
	

}


PreHQWidget::~PreHQWidget(void)
{
	
	_modelViewManager.clear();
	_resultViewManager.clear();
	_eigenViewManager.clear();
	_resultFrameViewList.clear();

	myResultDocument()->disattachListener(this);
	myDocument()->disattachListener(this);
	AppConfiguration::instance()->getParametersManager()->disattach(this);
}


void PreHQWidget::reload()
{
	int modelStatus=Base::ActiveViewObject::instance()->getModelStatus();

	switch(modelStatus)
	{
	case Base::ActiveViewObject::MODEL_STATUS_MODEL:
		{
			_modelViewManager=QSharedPointer<ModelViewManager>(new ModelViewManager(this));
			_modelViewManager->reset();

			_resultViewManager.clear();
			_eigenViewManager.clear();
		}
		break;
	case Base::ActiveViewObject::MODEL_STASTUS_DYNAMIC:
		{
			if(Hoops3DConfiguration::instance()->getShowInitial()){
				_modelViewManager=QSharedPointer<ModelViewManager>(new ModelViewManager(this));
				_modelViewManager->reset();
			}else
				_modelViewManager.clear();

			_resultViewManager=QSharedPointer<ResultViewManager>(new ResultViewManager(this));
			_resultViewManager->reset();

			_eigenViewManager.clear();
		}
		break;
	case Base::ActiveViewObject::MODEL_STATUS_EIGEN:
		{
			if(Hoops3DConfiguration::instance()->getShowInitial()){
				_modelViewManager=QSharedPointer<ModelViewManager>(new ModelViewManager(this));
				_modelViewManager->reset();
			}else
				_modelViewManager.clear();

			_resultViewManager.clear();

			_eigenViewManager=QSharedPointer<EigenViewManager>(new EigenViewManager(this));
			_eigenViewManager->reset();
		}
		break;
	}
}
void PreHQWidget::redraw()
{
	if(_modelViewManager)_modelViewManager->redraw();
	if(_resultViewManager)_resultViewManager->redraw();
	if(_eigenViewManager)_eigenViewManager->redraw();

	m_pHView->Update();
}

void PreHQWidget::Init()
{
	BaseHQWidget::Init();

	initSelection();
	onSetOmniControl();
	
	flushSize();
	initAppLogo();


	m_pHView->SetLightFollowsCamera(true);
}


void PreHQWidget::initAppLogo()
{
	HC_Open_Segment_By_Key(m_pHBaseModel->GetModelKey());
	// By Jianjun, 2015.6.3  up  
	HC_Set_Color("ambient down=(r=0.247059 g=0.243137 b=0.235294),ambient up=(r=0.247059 g=0.243137 b=0.235294),cut edge=white,marker=edge=line=text=(R=0 G=0 B=1),back=white,faces=(transmission=black)");
	HC_Set_Rendering_Options("lighting interpolation=(faces=gouraud),texture interpolation,color interpolation=(faces,no edges,markers)"
		",color index interpolation=(off),no lod,ambient up vector=(0,1,0)"
		",general curve=(no view dependent,budget=512,continued budget=0,max deviation=0,max angle=20,max length=0.1),cut geometry options=level=segment"
		",simple shadow=(off,plane=(0,0,-1,-0.047902),light=(0,0,1),color='( r = 1.000000 g = 0.984314 b = 0.941176)',opacity=1,resolution=64,blurring=4,no ignore transparency)"
	//	",simple reflection=(on,plane=(0,0,1,0.047902),opacity=0.5,fading,no blur,attenuation=(hither=0,yon=0))"
		",gooch options=(diffuse weight=0.5,color range=(0,2)),no force grayscale,color index interpolation options=visibility,diffuse color tint=off");

	HC_KEY itemKey=HC_Open_Segment("applogo");
	HC_Flush_Contents(".","everything");

	HPoint pos(0.0, 0.0, 1.0), target(0.0, 0.0, -1.0), up(0.0, 1.0, 0.0);
	float height=1.0;
	float width=1.0;
	HC_Set_Camera( &pos, &target, &up, width, height, "orthographic" );
	HC_Set_Handedness("right");
	HC_Set_Selectability("geometry=off");
	HC_Set_Visibility("cutting planes = off");
	HC_Set_Rendering_Options("depth range = (0,1e-4), simple shadow=off, anti-alias = text");
	HC_Set_Heuristics("no backplane culls");
	HC_Set_Camera_Projection("stretched");
	HC_Set_Color("text=red");
	HC_Set_Text_Font("size=17 pixels, size tolerance=0 points, no transforms, line spacing=1");
	//HC_Set_Text_Alignment("<^");
	HC_Set_Text_Alignment("<v");

	HC_Insert_Text( -width*0.5, -height*0.5, 0.0f,"             INSIDES Viewer\n  ");

	HC_Close_Segment(); //applogo

	HC_Close_Segment();	// model key
}


void PreHQWidget::testMaterialSelector()
{
	HTexturePickerWindow subwindow(m_pHView,0,0);

	if (!m_pHView->GetHObjectManager()->GetHObject("subwindow"))
		m_pHView->GetHObjectManager()->AddHObject(new HTexturePickerWindow(m_pHView));

	HC_Open_Segment_By_Key(m_pHView->GetModelKey());
	HC_Open_Segment_By_Key(m_pHView->GetSceneKey());
	HPoint porig, pconv;
	HPoint m_PositionOnRightClick(0,0);
	HC_Compute_Coordinates(".", "local window", &m_PositionOnRightClick, "local pixels", &pconv);
	HC_Close_Segment();

	HC_Open_Segment("HAbsoluteWindows");
	subwindow.Insert(pconv.x, 120, 400,pconv.y,"Materials",120,100);
	HC_Close_Segment();
	HC_Close_Segment();

	m_pHView->Update();	
}

QWeakPointer<ViewManager> PreHQWidget::getViewManager() const
{
	switch(_displayStatus)
	{
	case Base::ActiveViewObject::MODEL_STATUS_MODEL:
		return _modelViewManager;
	case Base::ActiveViewObject::MODEL_STASTUS_DYNAMIC:
		return _resultViewManager;
	case Base::ActiveViewObject::MODEL_STATUS_EIGEN:
		return _eigenViewManager;
	}
	return QWeakPointer<ViewManager>();
}


void PreHQWidget::initSelection()
{
	if(!m_pHView )
		return;
	// create our app-specific Selection object and initialize
	PreSelectionSet* oldSelection=(PreSelectionSet*)m_pHView->GetSelection();
	if(oldSelection)
		delete oldSelection;
	PreSelectionSet* selection=new PreSelectionSet(this->m_pHView,this);
	m_pHView->SetSelection(selection);
	(m_pHView->GetSelection())->Init();
	// set selection style.
	//selectionSet->SetSelectionEdgeWeight(5.0);
	selection->SetHighlightMode(HighlightDefault );//直接覆盖原来的。
	selection->SetSelectionLevel(HSelectSubentity);


	selection->SetSelectionEdgeWeight(5.0);
	//selection->SetSelectionMarkerSize(2.0);
	//selection->SetHighlightMode(ColoredInverseTransparency);
	//m_pHView->SetDynamicHighlighting(true);	//鼠标移过去反应。
	HC_Open_Segment_By_Key(selection->GetHighlightStyle());
	//HC_UnSet_Color();
	//HC_Set_Line_Weight(10.0);
	//HC_Set_Edge_Weight(10.0);
	
	HC_Close_Segment();
}

void PreHQWidget::onSetOmniControl()
{
	LocalSetOperator(new OmniControlOperator(m_pHView));
	m_pHView->GetSelection()->SetSelectionLevel(HSelectSegment);
}

void PreHQWidget::onSelect()
{
	m_pHView->GetSelection()->SetSelectionLevel(HSelectSegment);
}

void PreHQWidget::onSelectRegion()
{
	m_pHView->GetSelection()->SetSelectionLevel(HSelectSubentity);
}

void PreHQWidget::onSigSetSelect( long key,int count,const int* faces,const int* vertex1,const int* vertex2 )
{
	HSelectionSet* selection=m_pHView->GetSelection();
	selection->DeSelectAll();
	//int* a=(int*)faces;
	//a[0]=-1;
	//a=(int*)vertex1;
	//a[0]=1;
	//a=(int*)vertex2;
	//a[0]=1;
	selection->SelectSubentity(key,0,NULL,count,faces,vertex1,vertex2);
	m_pHView->Update();
}

void _setCameraData(osg::Vec3f& vec,double* cameraData,int startIndex)
{
	cameraData[startIndex]=vec._v[0];
	cameraData[startIndex+1]=vec._v[1];
	cameraData[startIndex+2]=vec._v[2];
}

void PreHQWidget::trackPositionAndPosture()
{
	onAddCameraTrack(TRACK_POSITION_POSTRUE);
}

void PreHQWidget::trackPostion()
{
	onAddCameraTrack(TRACK_POSITION);
}

void PreHQWidget::trackPosture()
{
	onAddCameraTrack(TRACK_POSTRUE);
}

void PreHQWidget::onAddCameraTrack(trackType type)
{
	if(!_resultViewManager)
		return;

	if(myProjectSelector()->getSelection().size()==0){
		Base::Console().Message("Select a marker first.");
		return;
	}

	BaseItem* baseItem=myProjectSelector()->getSelection()[0];
	if(baseItem->getCategory()!=TDY_PRE_CATE_MARKER){
		_resultViewManager->setCameraTrack(NULL);
		Base::Console().Message("Untracked marker");
		return;
	}

	BaseItem* rigidPart=baseItem->getParent();
	QWeakPointer<IResultItem> resultItem=myResultDocument()->getResults()->findResultItem(rigidPart);
	if(resultItem.isNull())
		return;

	resultItem.data()->setPos(0);
	HCamera camera;
	GetHoopsView()->GetCamera(&camera);

	osg::Vec3f initialPos(camera.position.x,camera.position.y,camera.position.z);
	osg::Vec3f initialTarget(camera.target.x,camera.target.y,camera.target.z);
	osg::Vec3f initialUp(camera.up_vector.x,camera.up_vector.y,camera.up_vector.z);

	osg::Matrixf matrix;
	BaseItemPosHelper::getResultRigid(resultItem.data(),matrix);

	osg::Matrixf mInvert=osg::Matrixf::inverse(matrix);
	osg::Vec3f originalPos=mInvert.preMult(initialPos);
	osg::Vec3f originalTarget=mInvert.preMult(initialTarget);
	osg::Vec3f originalUp=mInvert.preMult(initialUp);
	osg::Vec3f originalZero=mInvert.preMult(osg::Vec3f());

	int frameCount=myResultDocument()->getResults()->getFrameCount();
	CameraTrack* cameraTrack=new CameraTrack(frameCount);
	cameraTrack->setName(baseItem->getFullName());
	for(int i=0;i<frameCount;++i){
		double* cameraData=cameraTrack->getData(i);
		resultItem.data()->setPos(i);
		osg::Matrixf cM;
		BaseItemPosHelper::getResultRigid(resultItem.data(),cM);
		osg::Vec3f newPos=cM.preMult(originalPos);
		osg::Vec3f newTarget=cM.preMult(originalTarget);
		osg::Vec3f newUp=cM.preMult(originalUp);
		osg::Vec3f newZero=cM.preMult(originalZero);
		
		switch (type)
		{
		case TRACK_POSTRUE:
			{
				_setCameraData(originalPos,cameraData,0);
				_setCameraData(originalTarget,cameraData,3);
				osg::Vec3f tmp=newUp-newZero;
				_setCameraData(tmp,cameraData,6);
			}
			break;
		case TRACK_POSITION:
			{
				_setCameraData(originalPos,cameraData,0);
				_setCameraData(newTarget,cameraData,3);
				osg::Vec3f tmp=newUp-newZero;//新的
				_setCameraData(tmp,cameraData,6);
			}
			break;
		case TRACK_POSITION_POSTRUE:
			{
				_setCameraData(newPos,cameraData,0);
				_setCameraData(newTarget,cameraData,3);
				osg::Vec3f tmp=newUp-newZero;//新的
				_setCameraData(tmp,cameraData,6);
			}
			break;
		}
		
		
	}

	_resultViewManager->setCameraTrack(cameraTrack);

	Base::Console().Message("Tracked marker.");
}

void PreHQWidget::onSetAxisMarker()
{
	if(myProjectSelector()->getSelection().size()==0){
		Base::Console().Message("Select a marker first.");
		return;
	}


	HVector topVec;
	HVector frontVec;

	BaseItem* baseItem=myProjectSelector()->getSelection()[0];
	if(baseItem->getCategory()!=TDY_PRE_CATE_MARKER){
		HVector originalFrontVec(1,0,0);
		HVector originalTopVec(0,0,1);
		GetHoopsView()->SetViewAxis(&originalFrontVec,&originalTopVec);
		return;
	}

	osg::Matrixf matrix;
	BaseItemPosHelper::getGeneralItemOnOne(baseItem,matrix,myDocument()->getAssembly());
	osg::Vec3f newFront=matrix.preMult(osg::Vec3f(1,0,0));
	osg::Vec3f newTop=matrix.preMult(osg::Vec3f(0,0,1));
	osg::Vec3f newZero=matrix.preMult(osg::Vec3f(0,0,0));
	osg::Vec3f newFrontVec=newFront-newZero;
	osg::Vec3f newTopVec=newTop-newZero;
	topVec.x=newTopVec._v[0];
	topVec.y=newTopVec._v[1];
	topVec.z=newTopVec._v[2];
	frontVec.x=newFrontVec._v[0];
	frontVec.y=newFrontVec._v[1];
	frontVec.z=newFrontVec._v[2];

	topVec.Set(0.717,0.717,0);
	frontVec.Set(0.717,-0.717,0);

	GetHoopsView()->SetViewAxis(&frontVec,&topVec);
	GetHoopsView()->UpdateAxisTriad();
	GetHoopsView()->Update();
}

TrackPath* PreHQWidget::addNodePath( BaseItem* item )
{
	QWeakPointer<IResultItem> resultItem1=myResultDocument()->getResults()->findResultItem(item);
	if(resultItem1.isNull())
		return NULL;

	IResultItem* resultItem=resultItem1.data();
	FlexResultItem* flexResult=(FlexResultItem*)resultItem;

	int frameCount=myResultDocument()->getResults()->getFrameCount();
	TrackPath* trackPath=new TrackPath(frameCount);
	trackPath->setFullItemName(item->getFullName());
	trackPath->setNodeNumber(_selectSubNode);
	int count = flexResult->getSection(1)->numOfNodeOrElement;
	if(count<0)
		return NULL;

	for(int i=0;i<frameCount;++i){
		double* cameraData=trackPath->getData(i);
		resultItem->setPos(i);

		osg::Vec3f newPos;

		IResultItem::Precision* data=flexResult->getNodeElemData(1,0,_selectSubNode);
		newPos = osg::Vec3f(data[0],data[1],data[2]);
		_setCameraData(newPos,cameraData,0);
	}

	_resultViewManager->addTrackPath(trackPath);
	return trackPath;
}

void PreHQWidget::onAddTrackPath()
{
	int markerCount = myProjectSelector()->getSelection().size();
	SelectionNodeElem node = myProjectSelector()->getSelectionNodes();

	if(markerCount > 0)
	{
		for(int i=0;i<myProjectSelector()->getSelection().size();++i)
		{
			BaseItem* baseItem=myProjectSelector()->getSelection()[i];
			if(baseItem->getCategory() == TDY_PRE_CATE_MARKER)
				addTrackPath(baseItem);
			else if(baseItem->getCategory() == TDY_PRE_CATE_FEMPART)
			{
				if(node.item)
					addNodePath(node.item);
				else
					addTrackPath(baseItem);
			}
		}
	}
	else if(node.item)
		addNodePath(node.item);
	else
		Base::Console().Message("Select a node or marker first.");
}

TrackPath* PreHQWidget::addTrackPath(BaseItem* baseItem)
{
	if(baseItem->getCategory()==TDY_PRE_CATE_MARKER)
	{
		BaseItem* rigidPart=baseItem->getParent();
		QWeakPointer<IResultItem> resultItem1=myResultDocument()->getResults()->findResultItem(rigidPart);
		if(resultItem1.isNull())
			return NULL;

		IResultItem* resultItem=resultItem1.data();

		osg::Matrixf matrix;
		BaseItemPosHelper::getGeneralItem(baseItem,matrix,BaseItemHelper::getRelatedParameters(baseItem));
		osg::Vec3f markerZero=matrix.preMult(osg::Vec3f(0,0,0));

		int frameCount=myResultDocument()->getResults()->getFrameCount();
		TrackPath* trackPath=new TrackPath(frameCount);
		trackPath->setFullItemName(baseItem->getFullName());

		for(int i=0;i<frameCount;++i){
			double* cameraData=trackPath->getData(i);

			resultItem->setPos(i);
			osg::Matrixf cM;
			BaseItemPosHelper::getResultRigid(resultItem,cM);

			osg::Vec3f newPos=cM.preMult(markerZero);
			_setCameraData(newPos,cameraData,0);
		}

		_resultViewManager->addTrackPath(trackPath);
		return trackPath;

	}
	else if( (baseItem->getCategory()==TDY_PRE_CATE_FEMPART) || (baseItem->getCategory()==TDY_PRE_CATE_ASSEMBLY) )
	{
		QWeakPointer<IResultItem> resultItem1=myResultDocument()->getResults()->findResultItem(baseItem);
		if(resultItem1.isNull())
			return NULL;

		IResultItem* resultItem=resultItem1.data();

		int frameCount=myResultDocument()->getResults()->getFrameCount();
		TrackPath* trackPath=new TrackPath(frameCount);
		trackPath->setFullItemName(baseItem->getFullName());

		int tmpCOMIndex=0;
		if(resultItem->subSectionName(0,1)=="COM")
			tmpCOMIndex=1;

		for(int i=0;i<frameCount;++i){
			double* cameraData=trackPath->getData(i);
			resultItem->setPos(i);
			double* data=resultItem->getData(0,tmpCOMIndex);

			cameraData[0]=data[0];
			cameraData[1]=data[1];
			cameraData[2]=data[2];
		}

		_resultViewManager->addTrackPath(trackPath);
		return trackPath;
	}
	return NULL;
}

void PreHQWidget::onDisplayLegendMenu()
{
	QPoint globalPos =QCursor::pos();

	QMenu menu;
	QAction* ac=menu.addAction("add a legend",this,SLOT(onAddOneLegend()));
	menu.addAction(ac);

	ac=menu.addAction("add a contour...",this,SLOT(onAddOneContour()));
	menu.addAction(ac);

	ac=menu.addAction("remove all contours",this,SLOT(onClearContour()));
	menu.addAction(ac);

	menu.exec(globalPos);
}

void PreHQWidget::onDisplaySelectMenu()
{
	QPoint globalPos =QCursor::pos();

	QMenu menu;
	QAction* ac;

	QMenu * trackMenu = new QMenu("track selected marker");
	trackMenu->setIcon(QIcon(":/resources/menu/a007x16x16.png"));
	ac=trackMenu->addAction("position and posture",this,SLOT(trackPositionAndPosture()));
	ac=trackMenu->addAction("position",this,SLOT(trackPostion()));
	ac=trackMenu->addAction("posture",this,SLOT(trackPosture()));
	ac = menu.addMenu(trackMenu);

	ac=menu.addAction("add path",this,SLOT(onAddTrackPath()));
	ac->setIcon(QIcon(":/resources/menu/a008x16x16.png"));

	ac=menu.addAction("edit path ...",this,SLOT(onEditPaths()));
	//ac->setIcon(QIcon(":/resources/menu/a008x16x16.png"));

	ac=menu.addAction("set axis",this,SLOT(onSetAxisMarker()));

	ac=menu.addAction("show section",this,SLOT(onAddSectionSurface()));

	ac=menu.addAction("show all section...",this,SLOT(onAddAllSectionSurface()));

	ac=menu.addAction("add frame",this,SLOT(addFrameView()));

	ac=menu.addAction("clear all frame",this,SLOT(clearAllFrameViews()));

	ac=menu.addAction("measure distance",this,SLOT(onMeasureDistance()));
	//ac=menu.addAction("orbit vertical",this,SLOT(onOrbitVertical()));
	ac=menu.addAction("show velocity",this,SLOT(onShowVelocity()));
	ac=menu.addAction("hide velocity",this,SLOT(onHideVelocity()));
	ac=menu.addAction("set window color",this,SLOT(onSetWindowColor()));
	//ac = menu.addAction("options",this,SLOT(onOptions()));
	//ac = menu.addAction("create sphere",this,SLOT(onCreateSphere()));
	//ac = menu.addAction("create cuboid",this,SLOT(onCreateCuboit()));
	//ac = menu.addAction("test material",this,SLOT(testHoopsMaterial()));

	menu.exec(globalPos);
}

void PreHQWidget::onAddOneLegend()
{
}

void PreHQWidget::onAddOneContour()
{
	if(!_resultViewManager.isNull()){
		if(!_contourDisplaySelectorWidget)
		{
			_contourDisplaySelectorWidget=new ContourDisplaySelectorDialog(this);
			connect(_contourDisplaySelectorWidget->getWidget(),
				SIGNAL(contourItemAdding(IResultItem*,int,int,int,bool))
				,this,SLOT(onContourItemAdding(IResultItem*,int,int,int,bool)));
		}
		_contourDisplaySelectorWidget->show();
	}
}

void PreHQWidget::onClearContour()
{
	if(!_resultViewManager.isNull()){
		_resultViewManager->removeAllContour();
	}
}

void PreHQWidget::onContourItemAdding( IResultItem* resultItem,int secIndex,int subSecIndex,int subsubSecIndex,bool onlyUseCurrent )
{
	if(!_resultViewManager.isNull()){
		DisplayLegendItem item;
		item.relatedResultItem=resultItem;
		item.sectionIndex=secIndex;
		item.subSectionIndex=subSecIndex;
		item.subsubSectionIndex=subsubSecIndex;
		_resultViewManager->addOneContour(item,onlyUseCurrent);
	}
}

void PreHQWidget::res_ResultsLoaded( IResults* results )
{
	_displayStatus=ActiveViewObject::instance()->getModelStatus();
	reload();
}



void PreHQWidget::initContextMenu()
{
	BaseHQWidget::initContextMenu();

	_mainContextMenu->addSeparator();

	_mainContextMenu->addAction("hide time label",this,SLOT(showHideTimeLabel()));
	_mainContextMenu->addAction("translate",this,SLOT(translateTime()));
	
	_mainContextMenu->addAction("copy",this,SLOT(copy()));
	_mainContextMenu->addAction("paste",this,SLOT(paste()));
	_mainContextMenu->addAction("segment browser",this,SLOT(showSegmentBrowser()));

}

void PreHQWidget::copy()
{
	if(!_resultViewManager || !_resultViewManager->getTrackPaths())
		return;

	QByteArray output;
	QDataStream dataStream(&output, QIODevice::WriteOnly);
	TrackPaths* paths=_resultViewManager->getTrackPaths();
	dataStream<<*paths;

	QMimeData *mimeData = new QMimeData;
	QString mimeType = QString("application/tdypre:3dview");
	mimeData->setData(mimeType, output);

	QApplication::clipboard()->setMimeData(mimeData);
}

void PreHQWidget::paste()
{
	QString mimeType = QString("application/tdypre:3dview");
	const QMimeData* mimeData=QApplication::clipboard()->mimeData();
	if(!mimeData)
		return;
	if (mimeData->hasFormat(mimeType))
	{
		QByteArray input= mimeData->data(mimeType);
		QDataStream dataStream(&input, QIODevice::ReadOnly);
		if(_resultViewManager&& _resultViewManager->getTrackPaths()){
			TrackPaths* paths=_resultViewManager->getTrackPaths();
			dataStream>>*paths;
		}
	}
}

void PreHQWidget::onAddSectionSurface()
{
	if(myProjectSelector()->getSelection().size()==0){
		Base::Console().Message("Select a marker first.");
		return;
	}

	BaseItem* baseItem=myProjectSelector()->getSelection()[0];
	if(baseItem->getCategory()!=TDY_PRE_CATE_FEMPART 
		&& baseItem->getCategory()!=TDY_PRE_CATE_FLEXPART)
		return;

	QWeakPointer<IResultItem> resultItem1=myResultDocument()->getResults()->findResultItem(baseItem);
	if(resultItem1.isNull())
		return;

	IResultItem* resultItem=resultItem1.data();
	if(_resultViewManager){
		QList<double> d1Points,d1Params;
		if(getSectionParas(d1Points,d1Params)){
			_resultViewManager->addSectionSurface(resultItem,d1Points,d1Params);
		}
	}
}


void PreHQWidget::onAddAllSectionSurface()
{
	if(_resultViewManager){
		QList<double> d1Points,d1Params;
		if(getSectionParas(d1Points,d1Params)){
			IResults::ResultMap& results=myResultDocument()->getResults()->getResults();
			for(IResults::ResultMap::Iterator b=results.begin();
				b!=results.end();++b){
					QSharedPointer<IResultItem> resultItem=b.value();
					if(resultItem->getClassType()==TDY_POST_ITEMCLASS_FLEX){
						_resultViewManager->addSectionSurface(resultItem.data(),d1Points,d1Params);
					}
			}
			//_resultViewManager->addSectionSurface(resultItem,d1Points,d1Params);
		}
	}
}

bool PreHQWidget::getSectionParas( QList<double>& d1Poitns,QList<double>& d1Params )
{
	static SectionInputDialog* sectionInputDialog=NULL;
	if(!sectionInputDialog)
		sectionInputDialog=new SectionInputDialog(this);

	if(sectionInputDialog->exec()==QDialog::Accepted)
	{
		d1Poitns=sectionInputDialog->getSection1DPoints();
		d1Params=sectionInputDialog->getSection1DParameters();
		return true;
	}
	return false;
}

void PreHQWidget::onDisplayPickMenu()
{
	QPoint globalPos =QCursor::pos();

	QMenu menu;

	QAction* ac;
	
	ac=menu.addAction("select",this,SLOT(onSelect()));
	ac=menu.addAction("select region",this,SLOT(onSelectRegion()));

	ac=menu.addAction("Entity",this,SLOT(setPickEntity()));

	ac = menu.addAction("Face",this,SLOT(setPickFace()));

	ac=menu.addAction("Node",this,SLOT(setPickNode()));
	ac->setIcon(QIcon(":/resources/menu/a021x16x16.png"));

	ac=menu.addAction("Element",this,SLOT(setPickElement()));
	ac->setIcon(QIcon(":/resources/menu/a022x16x16.png"));


	menu.exec(globalPos);
}

void PreHQWidget::setPickEntity()
{
	LocalSetOperator(new OmniControlOperator(m_pHView));
	m_pHView->GetSelection()->SetSelectionLevel(HSelectSegment);
	myProjectSelector()->setSelectionType(ProjectSelector::ST_Entity);
}

void PreHQWidget::setPickFace()
{
	LocalSetOperator(new OmniControlOperator(m_pHView));
	m_pHView->GetSelection()->SetSelectionLevel(HSelectRegion);
	m_pHView->GetSelection()->SetSubentityVertexSelection(false);
	m_pHView->GetSelection()->SetSubentityFaceSelection(true);
	m_pHView->GetSelection()->SetSubentityEdgeSelection(false);
	myProjectSelector()->setSelectionType(ProjectSelector::ST_Entity);
}

void PreHQWidget::setPickElement()
{
	LocalSetOperator(new OmniControlOperator(m_pHView));
	m_pHView->GetSelection()->SetSelectionLevel(HSelectSubentity);
	m_pHView->GetSelection()->SetSubentityVertexSelection(false);
	m_pHView->GetSelection()->SetSubentityFaceSelection(true);
	m_pHView->GetSelection()->SetSubentityEdgeSelection(true);
	myProjectSelector()->setSelectionType(ProjectSelector::ST_Element);
}

void PreHQWidget::setPickNode()
{
	LocalSetOperator(new OmniControlOperator(m_pHView));
	m_pHView->GetSelection()->SetSelectionLevel(HSelectSubentity);
	m_pHView->GetSelection()->SetSubentityFaceSelection(false);
	m_pHView->GetSelection()->SetSubentityEdgeSelection(false);
	m_pHView->GetSelection()->SetSubentityVertexSelection(true);
	myProjectSelector()->setSelectionType(ProjectSelector::ST_Node);
}

QVariant PreHQWidget::getTreeItemData( BaseItem* baseItem,int index )
{
	//props->addProperty(TreeItemProperty(renderViewName+"::Color",QVariant::Color,false,10))
	//	.addProperty(TreeItemProperty(renderViewName+"::HKey",QVariant::LongLong,false,90))
	//	.addProperty(TreeItemProperty(renderViewName+"::ShowPath",QVariant::Bool,true,20))
	//	.addProperty(TreeItemProperty(renderViewName+"::ShowCenter",QVariant::Bool,true,20))
	//	.addProperty(TreeItemProperty(renderViewName+"::Visibility",QVariant::LongLong,true,20))
	QWeakPointer<ViewManager> vManager=getViewManager();
	ViewManager* realManager=vManager.data();
	if(vManager.isNull()|| !realManager)
		return QVariant();

	switch(index){
	case 0:	//material
	case 4:	//visibility
		{
			AppearanceItem* tmpApp=realManager->getAppearance(baseItem);
			return (qlonglong)(void*)tmpApp;
		}
	case 1:
		{
			AppearanceItem* tmpApp=realManager->getAppearance(baseItem);
			if(tmpApp)
				return tmpApp->getHCKey();
			break;
		}
	case 2: // show path
		{
			if(_displayStatus==ActiveViewObject::MODEL_STASTUS_DYNAMIC)
			{
				(ResultViewManager*)getViewManager().data();
			}
			return QVariant();
		}
	case 3:
		return false;
	}
	return QVariant();
}

bool PreHQWidget::setTreeItemData( BaseItem* baseItem,int index,const QVariant& data )
{
	QWeakPointer<ViewManager> vManager=getViewManager();
	ViewManager* realManager=vManager.data();
	if(vManager.isNull()|| !realManager)
		return false;

	switch(index){
	case 0:
	case 4:
		realManager->onVisibilityChanged( (AppearanceItem*)(void*)data.toULongLong());
		realManager->onApplyMaterial((AppearanceItem*)(void*)data.toULongLong());
		this->GetHoopsView()->Update();
		return true;
	}
	return false;
}

void PreHQWidget::res_ResultsDeleted()
{

}

void PreHQWidget::doc_ModelReseted( BaseItem* rootItem )
{
	_displayStatus=ActiveViewObject::MODEL_STATUS_MODEL;
	reload();
}

void PreHQWidget::addFrameView()
{
	ResultViewManager* resultView=new ResultViewManager(this);
	resultView->setEnableAnimation(false);
	resultView->reset();
	resultView->drawResult();
	_resultFrameViewList.push_back(QSharedPointer<ResultViewManager>(resultView));
}

void PreHQWidget::clearAllFrameViews()
{
	_resultFrameViewList.clear();
	m_pHView->Update();
}

bool PreHQWidget::parameterChanged( ParametersGroup* parameterManager, 
	const ParameterItem* newParameter,const ParameterItem* oldParameter )
{
	QString paraKeyName=newParameter->getKeyword();
	if( (paraKeyName.compare("show constraint",Qt::CaseInsensitive)==0)
		|| (paraKeyName.compare("show FEM marker",Qt::CaseInsensitive)==0)
		|| (paraKeyName.compare("showIMarker",Qt::CaseInsensitive)==0)
		|| (paraKeyName.compare("showJMarker",Qt::CaseInsensitive)==0)
		)
	{
		reload();
		m_pHView->Update();
	}
	if(
		(paraKeyName.compare("show initial",Qt::CaseInsensitive)==0)
		|| (paraKeyName.compare("show mass center",Qt::CaseInsensitive)==0)
		)
	{
		redraw();
		m_pHView->Update();
	}
	else if(paraKeyName.compare("Marker size",Qt::CaseInsensitive)==0)
	{
		flushSize();
		//HoopsShapeManager::instance()->setShapeAbsoluteDimension("Marker",newParameter->getVariant().toDouble());
		m_pHView->Update();
	}
	else if(paraKeyName.compare("Constraint size",Qt::CaseInsensitive)==0)
	{
		flushSize();
		m_pHView->Update();
	}
	if( (paraKeyName.compare("Force scale size",Qt::CaseInsensitive)==0)
		|| (paraKeyName.compare("Mass center size",Qt::CaseInsensitive)==0)
		|| (paraKeyName.compare("Shell edge size",Qt::CaseInsensitive)==0)
		|| (paraKeyName.compare("Shell vertex size",Qt::CaseInsensitive)==0)
		|| (paraKeyName.compare("Eigen display scale",Qt::CaseInsensitive)==0)
		)
	{
		redraw();
		m_pHView->Update();
	}

	return false;
}

void PreHQWidget::flushSize()
{
	double markerSize=1;
	double constraintSize=1;
	const ParameterItem* item=AppConfiguration::instance()->getParametersManager()->get("Constraint size","Display");
	if(item)
		constraintSize=item->getVariant().toDouble();

	item=AppConfiguration::instance()->getParametersManager()->get("Marker size","Display");
	if(item)
		markerSize=item->getVariant().toDouble();

	ShapeManager::instance()->setGlobalScale(constraintSize);
	HoopsShapeManager::instance()->setShapeAbsoluteDimension("Marker",
		markerSize);
}



void PreHQWidget::doc_RootItemChanged( BaseItem* currentRoot,BaseItem* oldRoot )
{
	if(_modelViewManager)
		_modelViewManager->reset();
}

void PreHQWidget::showSegmentBrowser()
{
	HQSegmentBrowserFrame* frame=new HQSegmentBrowserFrame(this);
	frame->setAttribute(Qt::WA_DeleteOnClose,true);
	frame->setHoopsView(m_pHView);
	frame->show();
}

void PreHQWidget::onEditPaths()
{
	PathPropertyDialog dlg(_resultViewManager.data(),this);
	dlg.exec();
}

void PreHQWidget::onMeasureDistance()
{
	LocalSetOperator(new HOpMarkupMeasure(m_pHView));
}

void PreHQWidget::onOrbitVertical()
{
    LocalSetOperator(new HOpCameraOrbitTurntable(m_pHView));	
}

void PreHQWidget::onShowVelocity()
{
	setShowVelocity(true);
}

void PreHQWidget::onHideVelocity()
{
	setShowVelocity(false);
}

void PreHQWidget::setShowVelocity( bool showOrHide )
{
	ViewManager* viewManager=getViewManager().data();
	if(!viewManager)
		return;

	BaseItemSelection selections=ProjectSelector::instance()->getSelection();
	for(int i=0;i<selections.size();++i){
		BaseItem* item=selections[i];
		if(item->getCategory()==TDY_PRE_CATE_RIGIDPART){
			AppearanceItem* appItem=viewManager->getAppearance(item);
			if(appItem)
				appItem->_showVelocity=showOrHide;
		}
	}

	redraw();
	GetHoopsView()->Update();
}

bool PreHQWidget::saveState( QDataStream& out )
{
	MimeData mimeData;
	QDataStream* cameraData=mimeData.startWriteCustomData("insides/viewer/prev3d/camera/1.0");
	saveCameraState(cameraData);
	
	QDataStream* pathData = mimeData.startWriteCustomData("insides/viewer/prev3d/trackpath/1.0");
	saveTrackPathsState(pathData);

	QDataStream* hoops3DConfigData = mimeData.startWriteCustomData("insides/viewer/prev3d/hoops3dconfiguration/1.0");
	Hoops3DConfiguration* tmp=Hoops3DConfiguration::instance();
	*hoops3DConfigData<<*tmp;


	mimeData.stopWriteAllCustomData();
	out<<mimeData;
	
	return true;
}

bool PreHQWidget::loadState( QDataStream& in )
{
	MimeData mimeData;
	in>>mimeData;

	QSharedPointer<QDataStream> cameraData=mimeData.startReadCustomData("insides/viewer/prev3d/camera/1.0");
	if(cameraData)
		loadCameraState(cameraData.data());

	QSharedPointer<QDataStream> pathData = mimeData.startReadCustomData("insides/viewer/prev3d/trackpath/1.0");
	if(pathData)
		loadTrackPathsState(pathData.data());

	QSharedPointer<QDataStream> hoops3DConfigData = mimeData.startReadCustomData("insides/viewer/prev3d/hoops3dconfiguration/1.0");
	if(hoops3DConfigData)
		loadHoops3DConfigData(hoops3DConfigData.data());

	
	return true;
}

void PreHQWidget::saveTrackPathsState( QDataStream* pathData )
{
	if(_resultViewManager)
	{
		TrackPaths* paths = _resultViewManager->getTrackPaths();
		*pathData<<*paths;
	}
}

void PreHQWidget::loadTrackPathsState( QDataStream* pathData )
{
	TrackPaths paths;
	*pathData>>paths;

	for(int i=0;i<paths.getTrackPathCount();i++)
	{
		TrackPath* path = paths.getTrackPath(i);
		_resultViewManager->addTrackPath(path);
	}
	//_resultViewManager->reset();
}

void PreHQWidget::loadHoops3DConfigData( QDataStream* hoopsData )
{
	Hoops3DConfiguration* config = Hoops3DConfiguration::instance();
	*hoopsData>>*config;
}

void PreHQWidget::showHideTimeLabel()
{
	QAction* ac = static_cast<QAction*>(sender());
	
	_resultViewManager->setIsShowTime();
	HC_Delete_By_Key(_resultViewManager->getTimeKey());
	_resultViewManager->redraw();
	m_pHView->Update();
	if(_resultViewManager->IsShowTime())
		ac->setText("hide time label");
	else
		ac->setText("show time label");
}

void PreHQWidget::translateTime()
{
	static bool flag = false;
	flag = !flag;
	if(flag)
		LocalSetOperator(new TimeTranslateOperator(m_pHView,this));
	else
		delete m_pHView->GetCurrentOperator();
}

long PreHQWidget::getTimeKey()
{
	if(_resultViewManager)
		return _resultViewManager->getTimeKey();
	else
		return -1;
}

void PreHQWidget::setTimePostion( float x,float y )
{
	if(_resultViewManager)
		_resultViewManager->setTimePos(x,y);
}

void PreHQWidget::onSetWindowColor()
{
	if(!_setWindowColorDialog){
		_setWindowColorDialog=new SetWindowColorDialog(0,this->GetHoopsView());
	}

	_setWindowColorDialog->hide();
	_setWindowColorDialog->show();
}

void PreHQWidget::onOptions()
{
	AppSettings* settings = AppSettings::instance();
	
	settings->setAppPath(qApp->applicationDirPath());
	settings->init();
	static ViewerOptionsDialog dlg(m_pHView);
	dlg.exec();
}

void PreHQWidget::onCreateCuboit()
{
	if(m_pHView->GetCurrentOperator())
		delete m_pHView->GetCurrentOperator();

	m_pHView->SetOperator(new HOpCreateCuboid(m_pHView));
}

void PreHQWidget::onCreateSphere()
{
	if(m_pHView->GetCurrentOperator())
	delete m_pHView->GetCurrentOperator();

	m_pHView->SetOperator(new HOpCreateSphere(m_pHView));
}

void PreHQWidget::testHoopsMaterial()
{
	static bool flag = false;
	static HMaterialLibrary hmat;

	if(!flag)
	{
		hmat.RegisterMaterials (H_FORMAT_TEXT ("%s%s", qApp->applicationDirPath().toStdString().c_str(), "/material_library"));
		flag = true;
	}

	const char* list = hmat.GetMaterialList();
	const char* env_list = hmat.GetEnvironmentList();

	QString str1(list),str2(env_list);
	 TestMaterialDialog dlg(this);
	dlg.initList(str1,str2);
	dlg.exec();
	if(!dlg.isAddClicked())
		return;

	HSelectionSet* selectionSet = m_pHView->GetSelection();
	int size = selectionSet->GetSize();
	if(size > 0)
	{
		for (int i=0;i<size;i++)
		{
			const HSelectionItem* item = selectionSet->GetSelectionItemAt(i);
			HC_KEY key = item->GetKey();
			testCreateCylinder(hmat,dlg.getCurrentMaterial(),dlg.getCurrentEnvironment(),dlg.getAmbientColor(),dlg.getSpecularColor(),dlg.getEmissionColor(),dlg.getGloss(),dlg.getDiffuseColor(),key);
		}
	}
	else
		testCreateCylinder(hmat,dlg.getCurrentMaterial(),dlg.getCurrentEnvironment(),dlg.getAmbientColor(),dlg.getSpecularColor(),dlg.getEmissionColor(),dlg.getGloss(),dlg.getDiffuseColor());
}



void PreHQWidget::testCreateCylinder(HMaterialLibrary& hmat, const QString& material,const QString& environment ,const QString& ambient,const QString& specular,const QString& emission ,int gloss,const QString& diffuse,HC_KEY key)
{
	QColor c("lemon");
	int r = c.red();
	int g = c.green();
	int b = c.blue();
	QByteArray arr1 = material.toLatin1();
	QByteArray arr2 = environment.toLatin1();
	const char *material_name = arr1.data();
	const char *environment_name = arr2.data();

	hmat.SetEnvironment (environment_name);
	m_pHView->SetLightFollowsCamera(true);

	HC_Open_Segment_By_Key(m_pHView->GetModelKey()); 
	{
		HC_Set_Visibility ("faces,no edges,no vertices");
		hmat.ApplyStyles();
		//HC_Set_Color("ambient down=(r=0.247059 g=0.243137 b=0.235294),ambient up=(r=0.247059 g=0.243137 b=0.235294),cut edge=white,face=green,marker=edge=line=text=(R=0 G=0 B=1)");
		//HC_Set_Rendering_Options("lighting interpolation=(faces=gouraud),texture interpolation,color interpolation=(faces,no edges,markers),color index interpolation=(off),no lod,ambient up vector=(0,1,0),general curve=(no view dependent,budget=512,continued budget=0,max deviation=0,max angle=20,max length=0.1),cut geometry options=level=segment,simple shadow=(off,plane=(0,0,-1,-0.047902),light=(0,0,1),color='( r = 1.000000 g = 0.984314 b = 0.941176)',opacity=1,resolution=64,blurring=4,no ignore transparency),simple reflection=(on,plane=(0,0,1,0.047902),opacity=0.5,fading,no blur,attenuation=(hither=0,yon=0)),gooch options=(diffuse weight=0.5,color range=(0,2)),no force grayscale,color index interpolation options=visibility,diffuse color tint=off");

		if(key == NULL)
		{
			HC_KEY imageKey;
			HC_KEY ttKey = HC_Open_Segment("/image");
				HInputHandler* handler = HDB::GetHIOManager()->GetInputHandler("jpg");
				handler->FileInputToImageKey("g:/muban.jpg",&imageKey,ttKey,new HInputHandlerOptions());
				HC_Edit_Image_Options(imageKey,"name=image.jpg"); 
				HC_Define_Texture("texture1","tiling, parameterization source = world, source = image.jpg");
			HC_Close_Segment();

			HC_Open_Segment("?Picture");
			HC_KEY cuKey = HC_Open_Segment (""); 
			{
				
		//		hmat.ApplyStyles();
				static int x=1,y=1,z=1;
				HC_POINT center(x,y,z);
				HC_POINT center2(x+1,y+1,z+1);
		//		HC_Insert_Sphere(&center, 1, NULL, NULL );

		//		HC_Insert_Cylinder(&center,&center2,1,"both");
		//		HUtilityGeometryCreation::CreateCuboid(&center,&center2);
		//		HUtilityGeometryCreation::CreateCylinder(center,1,2,50,HPoint(0,0,1),HPoint(1,1,0));
				HUtilityGeometryCreation::CreateSphere(center,1,50,HPoint(0,0,1),HPoint(1,1,0));
		//	    HUtility::InsertBox(&center,&center2);
		//		hmat.ApplyMaterial (material_name);
				x += 12;
				y += 12;
				z += 12;

				HC_Set_Color("faces=texture1");

		//		char ch[MVO_BUFFER_SIZE];
		//		sprintf(ch,"specular=green,emission=green,gloss=green"
		//			",back=white,faces=(transmission=black)"
		//			,specular.toStdString().c_str()
		//			,emission.toStdString().c_str(),gloss);
		////		HC_Set_Color (ch);
		//		HC_Set_Color("polygon=line=R=0.27 G=0.54 B=0.14");

		//		//test
		//		char ch2[MVO_BUFFER_SIZE];
		//		sprintf(ch2,"polygon=line=R=%f G=%f B=%f",243.f/255.f,168.f/255.f,187.f/255.f);
		//		HC_Set_Color(ch2);

			} 
			HC_Close_Segment ();

			
			

			HC_Open_Segment (""); 
			{
				
				static int x=3,y=3,z=3;
				HC_POINT center(x,y,z);
				HC_POINT center2(x+1,y+1,z+1);
			
				HUtilityGeometryCreation::CreateCylinder(center,1,2,50,HPoint(0,0,1),HPoint(1,1,0));

				HC_Set_Color("faces=texture1");
			}
			HC_Close_Segment ();
			
			HC_Open_Segment (""); 
			{
				/*hmat.SetEnvironment ("sea");
				hmat.ApplyStyles();
				hmat.ApplyMaterial ("metal/chrome");*/
				static int x=5,y=5,z=5;
				HC_POINT center(x,y,z);
				HC_POINT center2(x+1,y+1,z+1);
			
				HUtilityGeometryCreation::CreateSphere(center,1,50,HPoint(0,0,1),HPoint(1,1,0));
				
			//	HC_Set_Color("polygon=line=R=0.27 G=0.54 B=0.14");
				//test
				char ch2[MVO_BUFFER_SIZE];
				sprintf(ch2,"polygon=line=R=%f G=%f B=%f",247.f/255.f,185.f/255.f,120.f/255.f);
			//	HC_Set_Color(ch2);
				HC_Set_Color("faces=texture1");
			}
			HC_Close_Segment ();
			HC_Close_Segment();
		}
		else
		{
			HC_Open_Segment_By_Key(key);
			/*hmat.ApplyStyles();
			hmat.ApplyMaterial(material_name);
			char ch[MVO_BUFFER_SIZE];
			sprintf(ch,"ambient up=%s,specular=%s,emission=%s,gloss=%d,back=white,faces=(transmission=black,diffuse=%s)",ambient.toStdString().c_str(),specular.toStdString().c_str(),emission.toStdString().c_str(),gloss,diffuse.toStdString().c_str());
			HC_Set_Color(ch);*/
			char ch[MVO_BUFFER_SIZE];
			HC_Show_Color(ch);
			
			hmat.ApplyStyles();
			hmat.ApplyMaterial (material_name);
			HC_Set_Color("ambient down=(r=0.247059 g=0.243137 b=0.235294),ambient up=(r=0.247059 g=0.243137 b=0.235294),cut edge=white,marker=edge=line=text=(R=0 G=0 B=1),back=white,faces=(transmission=black)");
			HC_Set_Rendering_Options("lighting interpolation=(faces=gouraud),texture interpolation,color interpolation=(faces,no edges,markers)"
				",color index interpolation=(off),no lod,ambient up vector=(0,1,0)"
				",general curve=(no view dependent,budget=512,continued budget=0,max deviation=0,max angle=20,max length=0.1),cut geometry options=level=segment"
				",simple shadow=(off,plane=(0,0,-1,-0.047902),light=(0,0,1),color='( r = 1.000000 g = 0.984314 b = 0.941176)',opacity=1,resolution=64,blurring=4,no ignore transparency)"
				//	",simple reflection=(on,plane=(0,0,1,0.047902),opacity=0.5,fading,no blur,attenuation=(hither=0,yon=0))"
				",gooch options=(diffuse weight=0.5,color range=(0,2)),no force grayscale,color index interpolation options=visibility,diffuse color tint=off");

			HC_Set_Color("ambient=green,specular=green white,emission=green,faces=green");
			HC_Close_Segment();
		}
	} 
	HC_Close_Segment ();

	HC_Update_Display();
	m_pHView->Update();
}

