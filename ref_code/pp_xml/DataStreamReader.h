#pragma once

#include "pp_xml/pp_xml_global.h"

#include <QStringList>
#include <QString>
#include <QHash>
#include <QFile>
#include <QDataStream>

namespace pp
{

class DataBlock
{
public:
	quint32		id;
	quint32		dataSize;
	qint64		startPos;
	QDataStream*	fileHandler;

	void resetPos(){fileHandler->device()->seek(startPos);}
};

/*!
*	This class is used to read data from binary file and store them 
*	as DataBlocks.
*	@author Jerry He
*	@date	2014.3.24
*/
class PP_XML_EXPORT DataStreamReader
{
public:
	DataStreamReader(void);
	~DataStreamReader(void);

	bool addFile(const QString& strFilePath);
	void clear();

	typedef quint32 KEY_TYPE;
	typedef QHash<KEY_TYPE,DataBlock*> container_type;

	DataBlock* findBlock(const KEY_TYPE& type);
	int getBlockCount(){return _listBlocks.size();}


protected:
	QStringList			_listFilePath;
	QList<QFile*>		_listFiles;
	QList<QDataStream*>	_listDataStreams;
	container_type		_listBlocks;
	

};


}