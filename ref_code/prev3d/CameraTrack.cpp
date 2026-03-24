#include "CameraTrack.h"

#include "precore/BulkResultItem.h"

using namespace INSIDES;

CameraTrack::CameraTrack( int frameCount )
{
	if(frameCount>=0)
		_datas=QSharedPointer<BulkResultItem>(new BulkResultItem(NULL,frameCount,9));
}


CameraTrack::~CameraTrack(void)
{
}

double* CameraTrack::getData( int frameIndex )
{
	if(_datas.isNull())
		return NULL;
	_datas->setPos(frameIndex);
	return _datas->getData(0);
}
