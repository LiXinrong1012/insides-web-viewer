#include "ResultExchangeVersion1_0.h"

#include <QDataStream>

#include "precore/IResults.h"
#include "precore/IResultItem.h"
#include "precore/FlexResultItem.h"
#include "precore/RigidResultItem.h"
#include "precore/precore_data.h"

#include "precore/modeldocument.h"

#include "JResults.h"
#include "JRigidResultItem.h"

#include "pp_xml/DataStreamReader.h"
#include "pp_xml/DataStreamWriter.h"

#include "base/Console.h"
#include "base/MultiProgressOperator.h"

using namespace Base;
using namespace pp;

namespace INSIDES
{

struct ResultsHeader_1_0
{
	int	version;
	int frameCount;
	int hasData;
	int resultItemCount;
	int tmp1;
	int tmp2;
	int tmp3;
	int tmp4;
};

struct RigidSection_1_0
{
	enum {MAX_RIGID_SUBITEMS=10};
	char	name[256];
	int		count;
	double	minBounding[MAX_RIGID_SUBITEMS];
	double	maxBounding[MAX_RIGID_SUBITEMS];
	int		realIndex[MAX_RIGID_SUBITEMS];
};

static void _rigidItem2RigidSection_1_0(RigidSection* rigidSec,RigidSection_1_0* myRigidSec)
{
	memcpy(myRigidSec->minBounding,rigidSec->minBounding,RigidSection_1_0::MAX_RIGID_SUBITEMS*sizeof(double));
	memcpy(myRigidSec->maxBounding,rigidSec->maxBounding,RigidSection_1_0::MAX_RIGID_SUBITEMS*sizeof(double));
	memcpy(myRigidSec->realIndex,rigidSec->realIndex,RigidSection_1_0::MAX_RIGID_SUBITEMS*sizeof(int));
	myRigidSec->count=rigidSec->count;
	strcpy(myRigidSec->name,rigidSec->name.toStdString().c_str());
}

static void _rigidSection_1_02RigidSec(RigidSection_1_0* src,RigidSection* dst)
{
	memcpy(dst->minBounding,src->minBounding,RigidSection_1_0::MAX_RIGID_SUBITEMS*sizeof(double));
	memcpy(dst->maxBounding,src->maxBounding,RigidSection_1_0::MAX_RIGID_SUBITEMS*sizeof(double));
	memcpy(dst->realIndex,src->realIndex,RigidSection_1_0::MAX_RIGID_SUBITEMS*sizeof(int));
	dst->count=src->count;
	dst->name=src->name;
}

ResultExchangeVersion1_0::ResultExchangeVersion1_0(void)
{
}


ResultExchangeVersion1_0::~ResultExchangeVersion1_0(void)
{
}

void ResultExchangeVersion1_0::saveGeneralInfo( IResults* results,QSharedPointer<pp::DataStreamWriter> writer )
{
	_writer=writer;
	_results=results;
	_frameCount=results->getFrameCount();

	// 4 字节版本号
	ResultsHeader_1_0 resultsHeader;
	memset(&resultsHeader,0,sizeof(ResultsHeader_1_0));
	resultsHeader.version=1;
	if(results)
	{
		resultsHeader.hasData=1;
		resultsHeader.resultItemCount=results->getResultCount();
		resultsHeader.frameCount=_frameCount;
	}
	writer->writeArray(&resultsHeader,1);

	QList<double> timelist=_results->getTimeList();
	(*writer->getDataStream())<<timelist;
}


void ResultExchangeVersion1_0::save( IResults* results,QSharedPointer<pp::DataStreamWriter> writer )
{
	_writer=writer;
	_frameCount=results->getFrameCount();


	// 依次写出所有条目
	int resultCount=results->getResultCount();
	(*writer->getDataStream())<<(qint32)resultCount;
	IResults::ResultItemListType& allResults=results->getResultItemList();
	for(int i=0;i<resultCount;++i){
		IResultItem* resultItem=allResults[i].data();
		saveOne(resultItem);

		Base::MultiProgressOperator::setProgress(100.0*(i+1)/resultCount);
	}

}

void ResultExchangeVersion1_0::saveOne( IResultItem* item)
{
	QDataStream& stream=*_writer->getDataStream();
	// 4位类类型
	(*_writer->getDataStream())<<(qint32)item->getClassType();

	// 4字节数据长度
	qint64 dataLengthPos=stream.device()->pos();
	stream<<(qint32)0;

	switch(item->getClassType())
	{
	case TDY_POST_ITEMCLASS_RIGID:
		saveRigidItem(item);
		break;;
	case TDY_POST_ITEMCLASS_FLEX:
		break;;
	}
	qint64 endPos=stream.device()->pos();
	stream.device()->seek(dataLengthPos);
	stream<<(qint32)(endPos-dataLengthPos);
	stream.device()->seek(endPos);
}

void ResultExchangeVersion1_0::saveData( IResultItem* item)
{
	// 结果数据
	bool hasBounding=item->hasBounding();
	if(hasBounding){
		int dataLength=item->getDataLength();
		for(int i=0;i<_frameCount;++i){
			item->setPos(i);
			double* data=item->getData(0,0,0);
			_writer->writeArray(data,dataLength);
		}
	}
	else
	{
		int dataLength=item->getDataLength();
		for(int i=0;i<_frameCount;++i){
			item->setPos(i);
			item->updateCurrentBounding();
			double* data=item->getData(0,0,0);
			_writer->writeArray(data,dataLength);
		}
	}

}

void ResultExchangeVersion1_0::saveRigidSec( IResultItem* item ,bool bRealData)
{
	QList<RigidSection> rigidSecs=((RigidResultItem*)item)->getSections();
	(*_writer->getDataStream())<<rigidSecs.size();
	RigidSection_1_0 rigidHeader;
	for(int i=0;i<rigidSecs.size();++i){
		if(bRealData)
			_rigidItem2RigidSection_1_0(&rigidSecs[i],&rigidHeader);
		_writer->writeArray<RigidSection_1_0>(&rigidHeader,1);
	}
}

void ResultExchangeVersion1_0::saveRigidItem( IResultItem* item )
{
	// 抬头信息
	bool hasBounding=item->hasBounding();
	qint64 headerPos=_writer->getDataStream()->device()->pos();

	saveRigidSec(item,hasBounding);


	// 拓朴信息
	if(item->connectedItem())
		(*_writer->getDataStream())<<item->connectedItem()->getFullName();
	else
		(*_writer->getDataStream())<<QString("_NULL_");

	saveData(item);
	if(!hasBounding){
		qint64 endPos=_writer->getDataStream()->device()->pos();
		_writer->getDataStream()->device()->seek(headerPos);
		saveRigidSec(item,true);
		_writer->getDataStream()->device()->seek(endPos);
	}
}

void ResultExchangeVersion1_0::loadRigid( pp::DataBlock* dataBlock )
{
	// 抬头信息
	qint32 secSize;
	QDataStream& reader=*dataBlock->fileHandler;
	reader>>secSize;
	QList<RigidSection> rigidSecs;

	for(int i=0;i<secSize;++i){
		RigidSection_1_0 rigidHeader;
		reader.readRawData((char*)&rigidHeader,sizeof(RigidSection_1_0));
		RigidSection rigidSec;
		_rigidSection_1_02RigidSec(&rigidHeader,&rigidSec);
		rigidSecs.push_back(rigidSec);
	}


	QString connectName;
	reader>>connectName;
	BaseItem* connectedItem=NULL;
	if(connectName!="_NULL_")
		connectedItem=myDocument()->findItem(connectName);

	qint64 dataPos=reader.device()->pos();


	JRigidResultItem* rigidItem=new JRigidResultItem(_results,dataPos);
	rigidItem->setSections(rigidSecs);
	rigidItem->setDataBlock(dataBlock);
	rigidItem->setHasData(true);
	rigidItem->setHasBounding(true);
	_results->addResult(connectedItem,rigidItem);
}


IResults* ResultExchangeVersion1_0::loadGeneralInfo( DataBlock* reader )
{
	reader->resetPos();
	ResultsHeader_1_0 resultsHeader;
	reader->fileHandler->readRawData((char*)&resultsHeader,sizeof(ResultsHeader_1_0));

	if(resultsHeader.hasData==0)
		return NULL;

	JResults* results=new JResults();
	results->setFrameCount(resultsHeader.frameCount);
	QList<double> timeList;
	(*reader->fileHandler)>>timeList;
	results->setTimeList(timeList);
	_results=results;
	return results;
}


void ResultExchangeVersion1_0::load(IResults* results, DataBlock* dataBlock )
{
	dataBlock->resetPos();
	_results=results;
	qint32 itemCount;
	(*dataBlock->fileHandler)>>itemCount;
	for(int i=0;i<itemCount;++i){
		loadOne(dataBlock);
	}
}

void ResultExchangeVersion1_0::loadOne(pp::DataBlock* dataBlock)
{
	qint32 classType=0,datalen=0;
	(*dataBlock->fileHandler)>>classType;
	qint64 currPos=dataBlock->fileHandler->device()->pos();
	(*dataBlock->fileHandler)>>datalen;

	switch(classType){
	case TDY_POST_ITEMCLASS_RIGID:
		loadRigid(dataBlock);
		break;
	default:
		break;
	}
	dataBlock->fileHandler->device()->seek(currPos+datalen);
}

void ResultExchangeVersion1_0::saveFlexItem( IResultItem* item )
{
	FlexResultItem* flexResultItem=(FlexResultItem*)item;
	// 抬头信息
	bool hasBounding=item->hasBounding();
	qint64 headerPos=_writer->getDataStream()->device()->pos();

	saveFlexSec(item,hasBounding);


	// 拓朴信息
	if(item->connectedItem())
		(*_writer->getDataStream())<<item->connectedItem()->getFullName();
	else
		(*_writer->getDataStream())<<QString("_NULL_");
	//flexResultItem->getFEMBaseItem()->getFEMPart()

	saveData(item);
	if(!hasBounding){
		qint64 endPos=_writer->getDataStream()->device()->pos();
		_writer->getDataStream()->device()->seek(headerPos);
		saveRigidSec(item,true);
		_writer->getDataStream()->device()->seek(endPos);
	}
}

void ResultExchangeVersion1_0::saveFlexSec( IResultItem* item,bool realData/*=true*/ )
{

}


}