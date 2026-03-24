#pragma once


#include <QVector>
#include <QSharedPointer>

namespace INSIDES{
	class BulkResultItem;
}

using namespace INSIDES;

/*!
*	相机轨迹数据。
*	@author	Jerry He
*	@date	2014.5.20
*/
class CameraTrack
{
public:
	CameraTrack(int frameCount);
	~CameraTrack(void);

	void setName(const QString& name){_name=name;}
	QString getName()const{return _name;}

	double* getData(int frameIndex);

protected:
	QSharedPointer<BulkResultItem> _datas;
	QString		_name;
};

