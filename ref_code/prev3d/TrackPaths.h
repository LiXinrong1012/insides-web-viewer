#pragma once

#include <QString>
#include <QSharedPointer>
#include <QColor>
#include <QList>

namespace INSIDES{
	class BulkResultItem;
}

using namespace INSIDES;

class TrackPath
{
public:
	TrackPath();
	TrackPath(int frameCount);

	QString getRelatedMarkerName()const{return _markerName;}
	void setRelatedMarkerName(const QString& name){_markerName=name;}

	QString getName()const{return _name;}
	void setName(const QString& name){_name=name;}

	QString getFullItemName()const{return _fullItemName;}
	void setFullItemName(const QString& fullName){_fullItemName = fullName;}

	int getNodeNumber()const{return _nodeNumber;}
	void setNodeNumber(int number){_nodeNumber = number;}

	int		getLineWidth()const{return _lineWidth;}
	void	setLineWidth(int lineWidth){_lineWidth=lineWidth;}

	QColor	getLineColor()const{return _lineColor;}
	void	setLineColor(const QColor& color){_lineColor=color;}

	int		getDelayFrameCount()const{return _delay;}
	void	setDelayFrameCount(int delay){_delay=delay;}

	int		getDisplayFrameCount()const{return _showLength;}
	void	setDisplayFrameCount(int count){_showLength=count;}

	bool	getEnabled()const{return _isEnabled;}
	void	setEnabled(bool b){_isEnabled=b;}

	bool	getShowArrow()const{return _isShowArrow;}
	void	setShowArrow(bool b){_isShowArrow=b;}

	double* getData(int frameIndex);

	friend QDataStream& operator << (QDataStream& fout,const TrackPath& path);
	friend QDataStream& operator >> (QDataStream& fin, TrackPath& path);

private:
	QSharedPointer<BulkResultItem> _datas;
	///绑定条目的全名
	QString		_fullItemName;
	int			_nodeNumber;
	QString		_markerName;
	QString		_name;
	int			_lineWidth;
	QColor		_lineColor;
	int			_delay;
	int			_showLength;
	bool		_isEnabled;
	bool		_isShowArrow;
};

QDataStream& operator << (QDataStream& fout,const TrackPath& path);
QDataStream& operator >> (QDataStream& fin, TrackPath& path);

/*!
*	管理多条轨迹线，每条轨迹线为一个TrackLine实例。
*	@author	Jerry He
*	@date	2014.5.21
*/
class TrackPaths
{
public:
	TrackPaths(void);
	~TrackPaths(void);

	int getTrackPathCount()const{return _trackPaths.size();}
	TrackPath* getTrackPath(int index){return _trackPaths[index];}
	void removeTrackPath(int index);
	void addTrackPath(TrackPath* path);
	void clearAll();

	friend QDataStream& operator << (QDataStream& fout,const TrackPaths& path);
	friend QDataStream& operator >> (QDataStream& fin,TrackPaths& path);

private:
	QList<TrackPath*>	_trackPaths;

};

QDataStream& operator << (QDataStream& fout,const TrackPaths& path);
QDataStream& operator >> (QDataStream& fin,TrackPaths& path);

