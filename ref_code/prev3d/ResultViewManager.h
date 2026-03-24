#pragma once

#include "prev3d/BaseResultViewManager.h"
#include <Qtcore>

#include "precore/ResultDocument.h"

class CameraTrack;
class TrackPaths;
class TrackPath;
class LegendManager;
class LegendItem;
class DisplayLegendItem;
class SectionSurfaceManager;

class ResultViewManager :
	public BaseResultViewManager,public IResultListener
{
public:
	ResultViewManager(PreHQWidget* w);
	~ResultViewManager(void);

	virtual void reset();	//重置并刷新显示。
	virtual void redraw();	//重新刷新显示

	void setEnableAnimation(bool b){_enableAnimation=b;}
	PreHQWidget* getPreHQWidget()const{return _preHQWidget;}
	void drawResult();

	CameraTrack* getCameraTrack(){return _cameraTrack.data();}
	void setCameraTrack(CameraTrack* cameraTrack);

	void clearTrackPath();
	void addTrackPath(TrackPath* path);
	TrackPaths* getTrackPaths(){return _trackPaths.data();}

	void addOneContour(const DisplayLegendItem& displayLegendItem,bool onlyUseCurrrent=false);
	void removeAllContour();

	void addSectionSurface(IResultItem* resultItem,QList<double>& points,QList<double>& paras);

	///更改TIME位置
	void setTimePos(float x,float y);
	
	///得到TIMEKEY
	HC_KEY getTimeKey(){return _timeKey;}
	///是否显示TIME
	bool IsShowTime(){return _isShowTime;}
	void setIsShowTime(){_isShowTime = !_isShowTime;}
protected:
	/// invoked after result data has changed.
	virtual void onResultCurrentFrameChanged();

private:

	bool		_enableAnimation;

	QSharedPointer<CameraTrack>	_cameraTrack;
	QSharedPointer<TrackPaths>	_trackPaths;
	QSharedPointer<LegendManager> _legendManager;
	QSharedPointer<SectionSurfaceManager> _sectionSurfaceManager;
	PreHQWidget*	_preHQWidget;

	float _positionTimeX;
	float _positionTimeY;
	HC_KEY _timeKey;
	bool   _isShowTime;

	void updateCameraTrack();
	void updateTrackPaths();
	void updateTrackPath(TrackPath* path);
	void updateLegends();
	void updateLegendItem(LegendItem* item);
	void updateDisplayLegendItem(DisplayLegendItem* displayLegendItem);
	void updateUnsetDisplayLegendItem(DisplayLegendItem* displayLegendItem);

	/// 更新约束,Joint的位置，Jerry, 2014.6.16
	void updateConstraints(BaseItem* item);
	void createPPDisplay_TimeEntity(IResults* results);
};

