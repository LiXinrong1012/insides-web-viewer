#pragma once

#include "pp_xml/pp_xml_global.h"
#include <QString>
#include <QIODevice>
#include <QDataStream>
#include <QFile>

namespace pp
{

/*!
*	This class is used to write binary data into file.
*	@author Jerry He
*	@date	2014.3.24
*/
class PP_XML_EXPORT DataStreamWriter
{
public:
	DataStreamWriter(void);
	~DataStreamWriter(void);

	bool open(const QString& fileName);
	void close();

	QDataStream* getDataStream()const;
	QIODevice*	getIODevice()const;

	void startBlock(long id);
	void stopBlock();

	template<class T>
	void writeArray(T* a,int arraySize);

	static quint32 nextUniqueID();

private:
	QDataStream*	_stream;
	QFile*			_file;
	bool _isOpened;
	bool _isInBlock;
	qint64 _blockDataStartPos;

};

template<class T>
void pp::DataStreamWriter::writeArray( T* a,int arraySize )
{
	_stream->writeRawData((char*)a,sizeof(T)*arraySize);
}


}