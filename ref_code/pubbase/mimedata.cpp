#include "mimedata.h"
#include <QStringList>
#include <QFile>
#include <QBuffer>

namespace INSIDES{

/*!
	@brief 进行临时数据的写操作。
	@author	Jerry He
	@date	2014.11.23
*/
class BufferDataStreamWriter
{
public:
	QBuffer buffer;
	QDataStream dataStream;

	BufferDataStreamWriter()
	{
		buffer.open(QBuffer::WriteOnly);
		dataStream.setDevice(&buffer);
		dataStream.setVersion(QDataStream::Qt_4_8);
	}
};


QDataStream& operator<<( QDataStream& out,const MimeData& item )
{
	QStringList types = item.formats();
	out<<types.count();
	for(int i=0;i<types.count();i++)
	{
		out<<types[i];
		QByteArray bytes=item.data((types[i]));
		out<<bytes;
	}
	return out;
}

QDataStream& operator>>( QDataStream& in,MimeData& item )
{
	item.close();
	item.clear();

	int count ;
	in>>count;

	QString typeStr ;
	QByteArray byte;
	for (int i=0;i<count;i++)
	{
		in>>typeStr;
		in>>byte;
		item.setData(typeStr,byte);
	}
	return in;
}

MimeData::MimeData()
{
}

MimeData::~MimeData()
{
	close();	
}

void MimeData::close()
{
	stopWriteAllCustomData();
}

bool MimeData::save(const QString& fileName)const
{
	QFile saveData(fileName);
	if(!saveData.open(QFile::WriteOnly))
		return false;

	QDataStream stream(&saveData);
	stream.setVersion(QDataStream::Qt_4_8);
	stream<<*this;
	saveData.close();
	return true;
}

bool MimeData::load(const QString& fileName)
{
	QFile openData(fileName);
	if(!openData.open(QFile::ReadOnly))
		return false;

	QDataStream stream(&openData);
	stream.setVersion(QDataStream::Qt_4_8);

	stream>>*this;

	openData.close();
	return true;
}

void MimeData::setCustomDataString(const QString& mimeType,const QString& text)
{
	setCustomData(mimeType,text);
}

QString MimeData::getCustomDataString(const QString& mimeType,const QString& defaultValue)const
{
	return getCustomData(mimeType,defaultValue);
}

void MimeData::setCustomDataLong( const QString& mimeType,int va )
{
	setCustomData(mimeType,va);
}

int MimeData::getCustomDataLong( const QString& mimeType,int defaultValue/*=0*/ )const
{
	return getCustomData(mimeType,defaultValue);
}

QDataStream* MimeData::startWriteCustomData( const QString& mimeType )
{
	BufferDataStreamWriter* writer=_dataStreamWriterList.value(mimeType,NULL);
	if(writer)
		return &writer->dataStream;

	writer=new BufferDataStreamWriter();
	_dataStreamWriterList[mimeType]=writer;
	return &writer->dataStream;
}


void MimeData::stopWriteCustomData( const QString& mimeType )
{
	BufferDataStreamWriter* s=_dataStreamWriterList.value(mimeType);
	if(s){
		setData(mimeType,s->buffer.buffer());
		delete s;
		_dataStreamWriterList.remove(mimeType);
	}
}

void MimeData::stopWriteAllCustomData()
{
	for(DataStreamWriterMap::Iterator b=_dataStreamWriterList.begin();
		b!=_dataStreamWriterList.end();++b)
	{
		BufferDataStreamWriter* s=b.value();
		QString mimeType=b.key();
		if(s){
			setData(mimeType,s->buffer.buffer());
			delete s;
		}
	}
	_dataStreamWriterList.clear();
}

QSharedPointer<QDataStream> MimeData::startReadCustomData( const QString& mimeType )const
{
	QByteArray bytes=data(mimeType);
	if(bytes.isEmpty())
		return QSharedPointer<QDataStream>();

	QDataStream* s=new QDataStream(bytes);
	s->setVersion(QDataStream::Qt_4_8);
	return QSharedPointer<QDataStream>(s);
}

} // end namespace INSIDES