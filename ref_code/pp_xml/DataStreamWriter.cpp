#include "DataStreamWriter.h"
#include <QtCore>
#include <iostream>

using namespace pp;


DataStreamWriter::DataStreamWriter(void)
	:_stream(NULL)
	,_isOpened(false)
	,_isInBlock(false)
	,_blockDataStartPos(0)
{
}


DataStreamWriter::~DataStreamWriter(void)
{
	close();
	delete _stream;
	delete _file;
}

bool DataStreamWriter::open( const QString& fileName )
{
	QFile* file=new QFile(fileName);  
	if (!file->open(QIODevice::WriteOnly)) {  
		std::cerr << "Cannot open file for writing: " 
			<< qPrintable(file->errorString()) << std::endl;  
		delete file;
		return false;  
	}  

	_file=file;
	_stream=new QDataStream(file);
	_stream->setVersion(QDataStream::Qt_4_8);  

	_isOpened=true;
	return true;
}

void DataStreamWriter::close()
{
	_file->close();
}

QDataStream* DataStreamWriter::getDataStream() const
{
	return _stream;
}

QIODevice* DataStreamWriter::getIODevice() const
{
	return _stream->device();
}

void DataStreamWriter::startBlock( long id )
{
	quint32 qid=(quint32)id;
	(*_stream)<<qid;
	(*_stream)<<(quint32)0;
	_blockDataStartPos=_stream->device()->pos();
}

void DataStreamWriter::stopBlock()
{
	quint64 current=_stream->device()->pos();
	quint32 dataSize=(current-_blockDataStartPos);
	_stream->device()->seek(_blockDataStartPos-sizeof(qint32));
	(*_stream)<<dataSize;
	_stream->device()->seek(current);
	_isInBlock=false;
}

quint32 DataStreamWriter::nextUniqueID()
{
	static quint32 _curr=1;
	return _curr++;
}
