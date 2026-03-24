#include "TrackPaths.h"

#include "precore/BulkResultItem.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
TrackPath::TrackPath( int frameCount )
	:_markerName("No marker")
	,_name("untitled")
	,_lineWidth(2)
	,_lineColor(QColor("black"))
	,_delay(0)
	,_showLength(99999)
	,_isEnabled(true)
	,_isShowArrow(false)
{
	if(frameCount!=0)
		_datas=QSharedPointer<BulkResultItem>(new BulkResultItem(NULL,frameCount,3));
}

TrackPath::TrackPath()
{

}

double* TrackPath::getData( int frameIndex )
{
	_datas->setPos(frameIndex);
	return _datas->getData(0);
}


QDataStream& operator << (QDataStream& fout,const TrackPath& path)
{
	if(path._datas.isNull())
		fout<<false;
	else{
		fout<<true;
		fout<<*path._datas.data();
	}
	fout<<path._markerName
		<<path._name
		<<path._lineWidth
		<<path._lineColor
		<<path._delay
		<<path._showLength
		<<path._isShowArrow
		<<path._isEnabled;
	return fout;
}
QDataStream& operator >> (QDataStream& fin, TrackPath& path)
{
	bool hasData;
	fin>>hasData;
	if(hasData){
		BulkResultItem* bulkResult=new BulkResultItem(NULL,0,0);
		fin>>*bulkResult;
		path._datas=QSharedPointer<BulkResultItem>(bulkResult);
	}
	fin>>path._markerName
		>>path._name
		>>path._lineWidth
		>>path._lineColor
		>>path._delay
		>>path._showLength
		>>path._isShowArrow
		>>path._isEnabled;
	return fin;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
TrackPaths::TrackPaths(void)
{
}


TrackPaths::~TrackPaths(void)
{
}

void TrackPaths::clearAll()
{
	qDeleteAll(_trackPaths);
	_trackPaths.clear();
}

void TrackPaths::addTrackPath( TrackPath* path )
{
	_trackPaths.push_back(path);
}

void TrackPaths::removeTrackPath( int index )
{
	_trackPaths.removeAt(index);
}

QDataStream& operator << (QDataStream& fout,const TrackPaths& path)
{
	qint32 lineSize=path._trackPaths.size();
	fout<<lineSize;
	for(int i=0;i<lineSize;++i){
		fout<<*path._trackPaths[i];
	}
	return fout;
}
QDataStream& operator >> (QDataStream& fin,TrackPaths& path)
{
	int testInt = path.getTrackPathCount();
	qint32 lineSize;
	path.clearAll();
	fin>>lineSize;
	for(int i=0;i<lineSize;++i){
		TrackPath* newPath=new TrackPath();
		fin>>*newPath;
		path._trackPaths.push_back(newPath);
	}
	return fin;
}