#include "DataStreamReader.h"
#include <iostream>

using namespace pp;


DataStreamReader::DataStreamReader(void)
{
}


DataStreamReader::~DataStreamReader(void)
{
	_listFilePath.clear();
	qDeleteAll(_listFiles);
	qDeleteAll(_listDataStreams);
	qDeleteAll(_listBlocks.values());
	_listBlocks.clear();
}

bool DataStreamReader::addFile( const QString& strFilePath )
{
	QFile *file=new QFile(strFilePath);  
	if (!file->open(QIODevice::ReadOnly)) {  
		std::cerr << "Cannot open file for writing: " 
			<< qPrintable(file->errorString()) << std::endl;  
		delete file;
		return false;  
	}  

	QDataStream *fin=new QDataStream(file);  
	fin->setVersion(QDataStream::Qt_4_8);	

	// read all blocks
	while(!fin->atEnd())
	{
		DataBlock* newBlock=new DataBlock();
		(*fin)>>newBlock->id>>newBlock->dataSize;
		newBlock->startPos=fin->device()->pos();
		newBlock->fileHandler=fin;
		fin->device()->seek(fin->device()->pos()+newBlock->dataSize);

		_listBlocks[newBlock->id]=newBlock;
	}


	_listFiles.push_back(file);
	_listDataStreams.push_back(fin);
	return true;
}

void DataStreamReader::clear()
{
	for(container_type::Iterator b=_listBlocks.begin();
		b!=_listBlocks.end();++b)
		delete b.value();
	_listBlocks.clear();
	_listFilePath.clear();
}

DataBlock* DataStreamReader::findBlock( const KEY_TYPE& type )
{
	container_type::Iterator f=_listBlocks.find(type);
	if(f!=_listBlocks.end())
		return f.value();
	return NULL;
}

