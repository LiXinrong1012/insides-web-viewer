#include "ResultViewManager.h"
#include "HoopsUpdator.h"
#include "CameraTrack.h"
#include "PreHQWidget.h"

#include "precore/modeldocument.h"
#include "precore/precore_data.h"
#include "precore/IResultItem.h"
#include "precore/ResultDocument.h"
#include "precore/FlexResultItem.h"
#include "precore/BaseItemHelper.h"
#include "precore/femappearanceitem.h"

#include "prefem/JFEMPart.h"
#include "prefem/JMesh.h"
#include "prefem/JMeshGroup.h"

#include "base/ParametersManager.h"
#include "base/Console.h"

#include "coresps/ShapeManager.h"
#include "coresps/HoopsUltility.h"

#include <osg/Matrixf>

#include "TrackPaths.h"
#include "LegendManager.h"
#include "SectionSurfaceManager.h"

using namespace Base;

ResultViewManager::ResultViewManager(PreHQWidget* w)
	:BaseResultViewManager(w)
	,_preHQWidget(w)
	,_trackPaths(new TrackPaths())
	,_legendManager(new LegendManager())
	,_sectionSurfaceManager(new SectionSurfaceManager())
	,_enableAnimation(true)
	,_positionTimeX(-0.45f)
	,_positionTimeY(0.45f)
	,_timeKey(-1)
	,_isShowTime(true)
{
	setViewType(ResultViewType);

	this->setPriority(20);
	myResultDocument()->attachListener(this);
}


ResultViewManager::~ResultViewManager(void)
{
	myResultDocument()->disattachListener(this);
}


void ResultViewManager::reset()
{
	clearView();

	if(openRootSegment()){
		createModelItem(myDocument()->getAssembly());
		closeSegment();

		removePartMatrix();
		onResultCurrentFrameChanged();
	}
}


void ResultViewManager::createPPDisplay_TimeEntity(IResults* results)
{
	HC_KEY key=HC_Open_Segment("TIME");
	HC_Flush_Contents(".","everything");

	HPoint pos(0.0, 0.0, 1.0), target(0.0, 0.0, -1.0), up(0.0, 1.0, 0.0);
	float acpect=(float)(5/3.0);
	float height=1.0;
	float width=1.0;
	HC_Set_Camera( &pos, &target, &up, width, height, "orthographic" );
	HC_Set_Selectability("text=on");
	HC_Set_Visibility("cutting planes = off");
	HC_Set_Rendering_Options("depth range = (0,1e-4), simple shadow=off, anti-alias = text");
	HC_Set_Heuristics("no backplane culls");
	HC_Set_Color("edge=line=text=R=0 G=0 B=0");
	HC_Set_Camera_Projection("stretched");

	HC_Set_Text_Font("size=.07 oru, size tolerance=0 points, no transforms, line spacing=1");
	HC_Set_Text_Alignment("<^");

	QString str=QString("Time = %1").arg(results->getTime());
	_timeKey = HC_Insert_Text( _positionTimeX, _positionTimeY, 0.0f, str.toStdString().c_str());
	HC_Close_Segment();
}

void ResultViewManager::onResultCurrentFrameChanged()
{
	if(!_enableAnimation)
		return;

	drawResult();

	//updateView();
	if(_preHQWidget && _preHQWidget->GetHoopsView())
		_preHQWidget->GetHoopsView()->Update();
}

void ResultViewManager::setCameraTrack( CameraTrack* cameraTrack )
{
	_cameraTrack=QSharedPointer<CameraTrack>(cameraTrack);
}

static void _setHQPoint(HPoint& p,double* data,int startIndex)
{
	p.x=data[startIndex];
	p.y=data[startIndex+1];
	p.z=data[startIndex+2];
}

void ResultViewManager::updateCameraTrack()
{
	if(_cameraTrack.isNull()){
		HC_Open_Segment("CameraTrack");
		HC_Flush_Contents(".","everything");
		HC_Close_Segment();
		return;
	}

	int currFrame=myResultDocument()->getResults()->getCurrentFrame();
	double* d=_cameraTrack->getData(currFrame);
	HCamera camera;
	_preHQWidget->GetHoopsView()->GetCamera(&camera);
	_setHQPoint(camera.position,d,0);
	_setHQPoint(camera.target,d,3);
	_setHQPoint(camera.up_vector,d,6);

	_preHQWidget->GetHoopsView()->SetCamera(camera);

	HC_Open_Segment("CameraTrack");
	HPoint pos(0.0, 0.0, 1.0), target(0.0, 0.0, -1.0), up(0.0, 1.0, 0.0);
	float acpect=(float)(5/3.0);
	float height=1.0;
	float width=1.0;
	HC_Set_Camera( &pos, &target, &up, width, height, "orthographic" );
	//HC_Set_Handedness("left");
	HC_Set_Selectability("geometry=off");
	HC_Set_Visibility("cutting planes = off");
	HC_Set_Rendering_Options("depth range = (0,1e-4), simple shadow=off, anti-alias = text");
	HC_Set_Heuristics("no backplane culls");
	HC_Set_Color("edge=line=text=R=0 G=0 B=0");
	HC_Set_Camera_Projection("stretched");

	HC_Set_Text_Font("size=.03 oru, size tolerance=0 points, no transforms, line spacing=1");
	HC_Set_Text_Alignment("<^");
	//float mm[] = { 0.1f, 0.0f, 0.0f, 0.0f,
	//	0.0f, 0.1f, 0.0f, 0.0f,
	//	0.0f, 0.0f, 0.1f, 0.0f,
	//	-1.00f, -.75f, 0.0f, 1.0f};
	//HC_Set_Modelling_Matrix( mm );
	QString str=QString("Tracking marker: %1").arg(_cameraTrack->getName());

	HC_Insert_Text( -width*0.45, -height*0.45, 0.0f, str.toStdString().c_str());
	HC_Close_Segment();
}

void ResultViewManager::addTrackPath( TrackPath* path )
{
	_trackPaths->addTrackPath(path);
}

void ResultViewManager::updateTrackPaths()
{
	int n=_trackPaths->getTrackPathCount();
	if(n==0)
		return;

	HC_Open_Segment("TrackPaths");
	HC_Flush_Contents(".","everything");
	for(int i=0;i<n;++i)
	{
		HC_Open_Segment("");
		updateTrackPath(_trackPaths->getTrackPath(i));
		HC_Close_Segment();
	}
	HC_Close_Segment();
}

void ResultViewManager::updateTrackPath( TrackPath* path )
{
	int currentFrameIndex=myResultDocument()->getResults()->getCurrentFrame();
	int startIndex=0;
	if(path->getDisplayFrameCount()!=0)
		startIndex=currentFrameIndex-path->getDisplayFrameCount()-path->getDelayFrameCount();

	startIndex=startIndex>0?startIndex:0;

	int stopIndex=currentFrameIndex-path->getDelayFrameCount();
	stopIndex=stopIndex>0?stopIndex:0;
	stopIndex=stopIndex<myResultDocument()->getResults()->getFrameCount()?stopIndex:myResultDocument()->getResults()->getFrameCount()-1;

	int nodeCount=stopIndex-startIndex+1;
	if(nodeCount<2)
		return;


	HPoint *nodexyz= new HPoint[nodeCount];
	for(int i=0;i<nodeCount;++i){
		double* d=path->getData(startIndex+i);
		nodexyz[i].Set(d[0],d[1],d[2]);
	}
	HC_Insert_Polyline(nodeCount,nodexyz);
	delete []nodexyz;

	/*
	static bool _isInitialized=false;
	if(!_isInitialized){
		const char Arrow[] =
		{
			10, 0, 0, -1, 4,

			-5, -10,
			0, 0, 
			5, -10, 
			-5, -10,

			-3, 0
		};

		HC_Define_Glyph
			(
			"triangle",
			sizeof(Arrow),
			Arrow
			);

		HC_Define_Line_Style
			(
			"myLineStyle",
			"arrows = 0.15 oru triangle, 3 pixel weight,"
			"dash"
			);
	}


	HC_Set_Line_Pattern("myLineStyle");
	*/
	HC_Set_Line_Weight(path->getLineWidth());

	QColor color=path->getLineColor();
	QString str=QString("%4=(R=%1 G=%2 B=%3)")
		.arg(color.redF()).arg(color.greenF()).arg(color.blueF()).arg("line");
	HC_Set_Color(str.toStdString().c_str());

	HC_Set_Visibility("marker=off");
}

void ResultViewManager::updateLegends()
{
	int legendCount=_legendManager->getLegendCount();
	if(legendCount==0)
		return;
	HC_Open_Segment("Legends");
	HC_Flush_Contents(".","everything");
	HC_Set_Visibility("faces=on,edges=off,vertex=off,lights=off");

	for(int i=0;i<legendCount;++i){
		LegendItem* legendItem=_legendManager->getLegend(i);
		updateLegendItem(legendItem);

		// update contours on the FEM part
		for(int j=0;j<legendItem->getItemCount();++j){
			updateDisplayLegendItem(legendItem->getItem(j));
		}
		if(legendItem->isDirty())
		{
			legendItem->setDirty(false);
			updateLegendItem(legendItem);
		}
	}

	HC_Close_Segment();
}



void _insertLegend(Base::Legend* legend,float* width,float *height)
{
	int levelSize=legend->getLevelSize();

	char valueStr[100];

	const Legend::value_type* levelVec=legend->getLevelPtr();
	for(int i=0;i<levelSize;++i){
		sprintf(valueStr, legend->getValueStrFormat(), levelVec[i]);
		HC_Insert_Text(1.2,i+0.5,0,valueStr);
	}

	// Insert chart.
	int colorSize=legend->getColorSize();
	HPoint* nodes=new HPoint[(colorSize+1)*2];
	float xdelta=1.0f,ydelta=1.0f;
	nodes[0].Set(0,0);
	nodes[colorSize+1].Set(xdelta,0);
	for(int i=1;i<colorSize;++i){
		nodes[i].Set(0,(i-0.5)*ydelta);
		nodes[i+colorSize+1].Set(xdelta,(i-0.5)*ydelta);
	}
	nodes[colorSize].Set(0,(colorSize-1)*ydelta);
	nodes[2*colorSize+1].Set(xdelta,(colorSize-1)*ydelta);
	int* faceList=new int[colorSize*5];
	int curr=0;
	for(int i=0;i<colorSize;++i){
		faceList[curr++]=4;
		faceList[curr++]=i;
		faceList[curr++]=i+1;
		faceList[curr++]=i+colorSize+2;
		faceList[curr++]=i+colorSize+1;
	}
	HC_KEY faceKey=HC_Insert_Shell(colorSize*2+2,nodes,colorSize*5,faceList);
	// set a default face color
	float* indices = new float[ colorSize ];
	for (int i = 0 ; i < colorSize ; i++ ) {
		indices[i] = (float)i;
	}
	HC_MSet_Face_Colors_By_FIndex( faceKey, "faces", 0, colorSize, indices);

	delete [] nodes;
	delete [] indices;

	*width=3.2f;
	*height=levelSize;
}

void ResultViewManager::updateLegendItem( LegendItem* item )
{
	HC_Open_Segment("");
	if(item->getItemCount()==0){
		HC_Flush_Contents(".","everything");
		HC_Close_Segment();
		return;
	}

	Legend* legend=item->getLegend();
	HC_Set_Color_Map_By_Value( "RGB", legend->getColorSize(), legend->getColorPtr());


	HC_Set_Handedness("right");
	HC_Set_Selectability("geometry=off");
	HC_Set_Visibility("cutting planes = off");
	HC_Set_Rendering_Options("depth range = (0,1e-4), simple shadow=off, anti-alias = text");
	HC_Set_Heuristics("no backplane culls");
	HC_Set_Color("edge=line=text=R=0 G=0 B=0");
	HC_Set_Camera_Projection("stretched");

	HC_Set_Text_Font("size=12 pixels, size tolerance=0 points, no transforms, line spacing=1");
	HC_Set_Text_Alignment("<*");

	float width,height;
	_insertLegend(legend,&width,&height);


	float realH=height+2;
	float realW=realH*1.5;

	HPoint pos(0, 0.0, 10), target(0, 0.0, -10), up(0.0, 1.0, 0.0);
	HC_Set_Camera( &pos, &target, &up, realW, realH, "orthographic" );


	HoopsUltility::setModelMatrix_Pos((realW/2)-width,-height/2,0);


	HC_Close_Segment();
}


void ResultViewManager::addOneContour( const DisplayLegendItem& aaa,bool onlyUseCurrent )
{
	if(_legendManager->getLegendCount()==0)
		_legendManager->addLegend(new LegendItem());
	LegendItem* legendItem=_legendManager->getLegend(0);
	DisplayLegendItem displayLegendItem=aaa;

	int secIndex=displayLegendItem.sectionIndex;
	int subSecIndex=displayLegendItem.subSectionIndex;
	int subsubSecIndex=displayLegendItem.subsubSectionIndex;

	legendItem->addItem(displayLegendItem);
	if(onlyUseCurrent)
		legendItem->updateOnlyCurrentBounding();
	else
		legendItem->updateBounding();

	this->onResultCurrentFrameChanged();
}
void ResultViewManager::removeAllContour()
{
	if(_legendManager->getLegendCount()==0)
		return;
	LegendItem* legendItem=_legendManager->getLegend(0);
	legendItem->clearAll();

	this->onResultCurrentFrameChanged();
}


void ResultViewManager::updateDisplayLegendItem( DisplayLegendItem* displayLegendItem )
{
	if(displayLegendItem->isRemoved){
		updateUnsetDisplayLegendItem(displayLegendItem);
		return;
	}

	IResultItem* resultItem=displayLegendItem->relatedResultItem;
	BaseItem*	modelItem=resultItem->connectedItem();
	FEMAppearanceItem* appItem=(FEMAppearanceItem*)getAppearance(modelItem);

	if(!appItem || displayLegendItem->sectionIndex<1)
		return;

	if(modelItem->getCategory()!=TDY_PRE_CATE_FEMPART)
		return;

	HC_Open_Segment_By_Key(appItem->getHCKey());
	//HC_UnSet_One_Color("edges");

	Base::Legend* legend=displayLegendItem->parentLegendItem->getLegend();
	HC_Set_Color_Map_By_Value( "RGB", legend->getColorSize(), legend->getColorPtr());
	FlexResultItem* flexResultItem=(FlexResultItem*)resultItem;
	JFEMPart* femPart=flexResultItem->getFEMBaseItem()->getFEMPart();


	if(displayLegendItem->sectionIndex==1) // node contours
	{
		int groupN=femPart->m_Group.getGroupList().size();
		for(int i=0;i<groupN;++i)
		{
			JMeshGroup* group=femPart->m_Group.getGroupList()[i];
			QList<HC_KEY> validKeys;
			bool is1D=false;
			for(int jjj=0;jjj<3;++jjj)
				if(appItem->getGroupHKey(i,jjj)!=-1){
					validKeys<<appItem->getGroupHKey(i,jjj);
					if(jjj==0)
						is1D=true;
				}

			if(validKeys.size()!=0)
			{
				int nodeCount=flexResultItem->getNodeCount();
				float* vertexdata=new float[nodeCount];
				for(int nodeIndex=0;nodeIndex<nodeCount;++nodeIndex){
					double va=flexResultItem->getNodeElemData(displayLegendItem->sectionIndex,
						displayLegendItem->subSectionIndex,nodeIndex)[displayLegendItem->subsubSectionIndex];
					vertexdata[nodeIndex]=legend->mapDataToColorIndex(va);
				}

				foreach(HC_KEY key,validKeys)
					HC_MSet_Vertex_Colors_By_FIndex(key,"faces,edges",0,nodeCount,vertexdata);
				delete []vertexdata;
			}
			if(is1D)
				HC_Set_Rendering_Options("color interpolation=edges");
		}
	}
	else  // element contours
	{
		
		int elementGroupsIndex=displayLegendItem->sectionIndex-2;
		JMeshGroup* meshGroup=femPart->m_Group.getGroupList()[elementGroupsIndex];

		// 1D contour
		{
			HC_KEY shellKey=appItem->getGroupHKey(elementGroupsIndex,0);
			int surfCount=meshGroup->GetSurface1DCnt();
			PP_SURFACE* surf=meshGroup->GetSurface1D();
			JMesh* mesh=&flexResultItem->getFEMBaseItem()->getFEMPart()->m_Mesh;
			if(surfCount!=0 && shellKey!=-1)
			{
				float tmpColor[3];
				HC_Open_Geometry(shellKey);
				for(int faceIndex=0;faceIndex<surfCount;++faceIndex){
					PP_SURFACE* curSurf=&surf[faceIndex];
					DWORD eID=curSurf->getEID();
					PP_ELEMENT* elem=mesh->GetElement(eID);
					int node1=mesh->GetElementNode(elem->NSI+curSurf->ElNode[0]);
					int node2=mesh->GetElementNode(elem->NSI+curSurf->ElNode[1]);

					double va=flexResultItem->getNodeElemData(displayLegendItem->sectionIndex,
						displayLegendItem->subSectionIndex,eID)[displayLegendItem->subsubSectionIndex];
					float aa=legend->mapDataToColorIndex(va);
					legend->getColor(aa/(legend->getColorSize()-1),tmpColor);

					HC_Open_Edge(node1,node2);
					QString str=QString("edges=(r=%1 g=%2 b=%3)").arg(tmpColor[0]).arg(tmpColor[1]).arg(tmpColor[2]);
					HC_Set_Color(str.toStdString().c_str());
					HC_Close_Edge();
				}

				HC_Close_Geometry();
			}
		}

		// 2D contour
		{
			HC_KEY shellKey=appItem->getGroupHKey(elementGroupsIndex,1);

			int surfCount=meshGroup->GetSurface2DCnt();
			PP_SURFACE* surf=meshGroup->GetSurface2D();
			if(surfCount!=0 && shellKey!=-1)
			{
				float* facedata=new float[surfCount];
				for(int faceIndex=0;faceIndex<surfCount;++faceIndex){
					PP_SURFACE* curSurf=&surf[faceIndex];
					// to-do: might cause error
					//DWORD eID=curSurf->getEID();
					DWORD eID=faceIndex;
					double va=flexResultItem->getNodeElemData(displayLegendItem->sectionIndex,
						displayLegendItem->subSectionIndex,eID)[displayLegendItem->subsubSectionIndex];
					facedata[faceIndex]=legend->mapDataToColorIndex(va);
				}
				//HC_MSet_Face_Colors_By_FIndex(shellKey,"faces,edges",0,surfCount,vertexdata);
				HC_MSet_Face_Colors_By_FIndex(shellKey,"faces",0,surfCount,facedata);
				delete []facedata;
			}
		}

	}
	
	//HC_Set_Rendering_Options("color interpolation=faces");
	//HC_Set_Visibility("lights=off");
	//HC_Set_Color("edges=black");
	HC_Close_Segment();
}

void ResultViewManager::updateUnsetDisplayLegendItem( DisplayLegendItem* displayLegendItem )
{
	IResultItem* resultItem=displayLegendItem->relatedResultItem;
	BaseItem*	modelItem=resultItem->connectedItem();
	AppearanceItem* appItem=getAppearance(modelItem);

	if(!appItem)
		return;

	if(modelItem->getCategory()!=TDY_PRE_CATE_FEMPART)
		return;

	HC_Open_Segment_By_Key(appItem->getHCKey());

	Base::Legend* legend=displayLegendItem->parentLegendItem->getLegend();
	HC_UnSet_Color_Map();
	FlexResultItem* flexResultItem=(FlexResultItem*)resultItem;

	for(int i=0;i<3;++i){
		HC_KEY shellKey=appItem->getHCSubKey(i);
		if(shellKey==-1)
			continue;

		if(displayLegendItem->sectionIndex==1)		// show node contour
		{
			int nodeCount=flexResultItem->getNodeCount();

			HC_MUnSet_Vertex_Colors(shellKey,0,nodeCount);
		}
		else if(displayLegendItem->sectionIndex==2)	// show element contour
		{
			if(i==0)	// 1d contour
			{
				int surfCount=flexResultItem->getFEMBaseItem()->getFEMPart()->m_Group.getGroupList()[0]->GetSurfaceCnt(i);
				PP_SURFACE* surf=flexResultItem->getFEMBaseItem()->getFEMPart()->m_Group.getGroupList()[0]->GetSurface(i);
				JMesh* mesh=&flexResultItem->getFEMBaseItem()->getFEMPart()->m_Mesh;
				if(surfCount==0)
					continue;

				float tmpColor[3];
				HC_Open_Geometry(shellKey);
				for(int faceIndex=0;faceIndex<surfCount;++faceIndex){
					PP_SURFACE* curSurf=&surf[faceIndex];
					DWORD eID=curSurf->getEID();
					PP_ELEMENT* elem=mesh->GetElement(eID);
					int node1=mesh->GetElementNode(elem->NSI+curSurf->ElNode[0]);
					int node2=mesh->GetElementNode(elem->NSI+curSurf->ElNode[1]);

					double va=flexResultItem->getNodeElemData(displayLegendItem->sectionIndex,
						displayLegendItem->subSectionIndex,eID)[displayLegendItem->subsubSectionIndex];
					float aa=legend->mapDataToColorIndex(va);
					legend->getColor(aa/(legend->getColorSize()-1),tmpColor);

					HC_Open_Edge(node1,node2);
					HC_UnSet_Color();
					HC_Close_Edge();
				}

				HC_Close_Geometry();
			}
			else
			{
				int surfCount=flexResultItem->getFEMBaseItem()->getFEMPart()->m_Group.getGroupList()[0]->GetSurfaceCnt(i);
				PP_SURFACE* surf=flexResultItem->getFEMBaseItem()->getFEMPart()->m_Group.getGroupList()[0]->GetSurface(i);
				if(surfCount==0)
					continue;

				HC_MUnSet_Face_Colors(shellKey,0,surfCount);
			}
		}

	}

	HC_Close_Segment();
}


void ResultViewManager::addSectionSurface( IResultItem* resultItem,QList<double>& points,QList<double>& paras )
{
	_sectionSurfaceManager->addSectionSurface((FlexResultItem*)resultItem,
		points,paras);
}


static BaseItem* getJointMarker(BaseItem* item,const QString& keyName)
{
	QString markerName=item->get(keyName);
	if(markerName.isEmpty())
		return NULL;

	Assembly* parentAssebmly=item->getParentAssembly();
	return myDocument()->findItemWithoutFolder(markerName,parentAssebmly);
}
void ResultViewManager::updateConstraints(BaseItem* item)
{
	if(item->getCategory()==TDY_PRE_CATE_JOINT){
		BaseItem* IMarker=getJointMarker(item,"I");
		BaseItem* JMarker=getJointMarker(item,"J");
		AppearanceItem* itemAppItem=getAppearance(item);

		if(itemAppItem && itemAppItem->getHCKey()!=-1){
			AppearanceItem* appItemI=getAppearance(IMarker);
			AppearanceItem* appItemJ=getAppearance(JMarker);
			static float matrix[16];
			if(appItemI && appItemI->getHCKey()!=-1){
				HC_Open_Segment_By_Key(appItemI->getHCKey());
				HC_Show_Net_Modelling_Matrix(matrix);
				HC_Close_Segment();

				HC_Open_Segment_By_Key(itemAppItem->getHCKey());
				HC_Open_Segment("I");
				HC_Set_Modelling_Matrix(matrix);
				HC_Close_Segment();
				HC_Close_Segment();
			}
			if(appItemJ && appItemJ->getHCKey()!=-1){
				HC_Open_Segment_By_Key(appItemJ->getHCKey());
				HC_Show_Net_Modelling_Matrix(matrix);
				HC_Close_Segment();

				HC_Open_Segment_By_Key(itemAppItem->getHCKey());
				HC_Open_Segment("J");
				HC_Set_Modelling_Matrix(matrix);
				HC_Close_Segment();
				HC_Close_Segment();
			}
		}
	}
	int n=item->count();
	for(int i=0;i<n;++i){
		updateConstraints(item->child(i));
	}
}

void ResultViewManager::drawResult()
{
	ResultDocument* resultDoc=myResultDocument();
	IResults* results=resultDoc->getResults();
	if(!results)
		return;


	HoopsUpdatorSingleton* updator=HoopsUpdator();

	ResultUpdatePara para;
	para.viewManager=this;

	IResultItem* ritem;
	IResults::ResultMap& datasMap=results->getResults();
	for(IResults::ResultMap::Iterator b=datasMap.begin();
		b!=datasMap.end();++b){
		ritem=b.value().data();
		if(ritem->connectedItem() && ritem->hasData()){
			AppearanceItem* appItem=getAppearance(ritem->connectedItem());
			if(appItem && appItem->getHCKey()!=-1){
				HC_Open_Segment_By_Key(appItem->getHCKey());
				updator->onResultItemUpdating(&para,ritem,appItem);
				HC_Close_Segment();
			}
		}
	}
	updateConstraints(myDocument()->getAssembly());

	this->openRootSegment();
	if(IsShowTime())
		createPPDisplay_TimeEntity(results);
	updateTrackPaths();
	updateLegends();


	updateCameraTrack();
	this->closeSegment();
}

void ResultViewManager::redraw()
{
	drawResult();
}

void ResultViewManager::clearTrackPath()
{
	if(_trackPaths)
		_trackPaths->clearAll();
}

void ResultViewManager::setTimePos( float x,float y )
{
	_positionTimeX = x;
	_positionTimeY = y;
}

