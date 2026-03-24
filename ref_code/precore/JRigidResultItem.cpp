#include "JRigidResultItem.h"

#include "JResults.h"
#include "pp_xml/DataStreamReader.h"

namespace INSIDES
{

JRigidResultItem::JRigidResultItem(IResults* parent,qint64 startPos)
	:RigidResultItem(parent)
	,_startPos(startPos)
	,_dataBlock(NULL)
{
}


JRigidResultItem::~JRigidResultItem(void)
{
}

void JRigidResultItem::setPos( int index )
{
	QDataStream* dataStream=_dataBlock->fileHandler;
	dataStream->device()->seek(_startPos+getDataLength()*index*sizeof(double));
	dataStream->readRawData((char*)getData(0,0,0),getDataLength()*sizeof(double));
}

}