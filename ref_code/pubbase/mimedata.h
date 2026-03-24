#ifndef SAVEORREADCLASS_H
#define SAVEORREADCLASS_H

#include <QMimeData>
#include <QVector>
#include <QMessageBox>
#include <QSharedPointer>

namespace INSIDES
{
	class BufferDataStreamWriter;

	/*!
		@brief 整块数据输入输出类。
		支持输入输出多类数据，每类数据既可以是简单数据，也可以使用QDataStream来输入输出。
		@author	Jerry He
		@date	2014.11.23
	*/
	class MimeData : public QMimeData
	{
	public:
		friend QDataStream& operator << (QDataStream& out,const MimeData& item);
		friend QDataStream& operator >> (QDataStream& in,MimeData& item);

		///关闭所有写入数据程序
		void close();

		MimeData();
		~MimeData();

		/// 保存全部数据到文件
		bool save(const QString& fileName)const;

		/// 从文件中读入全部数据
		bool load(const QString& fileName);

		///设置自定义数据
		template<class T> void setCustomData(const QString& mimeType,const T& va);

		///获取自定义数据
		template<class T> T getCustomData(const QString& mimeType,const T& a=T())const;

		///设置QString类型自定义数据
		void setCustomDataString(const QString& mimeType,const QString& text);

		///获取QString类型自定义数据
		QString getCustomDataString(const QString& mimeType,const QString& defaultValue=QString())const;

		///设置double类型的自定义数据
		void setCustomDataDouble(const QString& mimeType,double va);

		///获取double类型的自定义数据
		double getCustomDataDouble(const QString& mimeType,double defaultValue=0.0)const;

		///设置long类型的自定义数据
		void setCustomDataLong(const QString& mimeType,int va);

		///获取long类型的自定义数据
		int getCustomDataLong(const QString& mimeType,int defaultValue=0)const;

		///开始写mimeType类型的自定义数据
		QDataStream* startWriteCustomData(const QString& mimeType);

		///停止写mimeType类型的自定义数据
		void stopWriteCustomData(const QString& mimeType);

		///停止写所有类型的自定义数据
		void stopWriteAllCustomData();

		///开始读取mimeType类型的自定义数据
		QSharedPointer<QDataStream> startReadCustomData(const QString& mimeType)const;

	private:
		typedef QMap<QString,BufferDataStreamWriter*> DataStreamWriterMap;
		typedef QMap<QString,QDataStream*> DataStreamReaderMap;

		///存放着所有的写入数据流对象
		DataStreamWriterMap _dataStreamWriterList;

	};

	template<class T>
	///通过模版实现获取自定义数据
	T INSIDES::MimeData::getCustomData( const QString& mimeType,const T& a/*=T()*/ )const
	{
		QByteArray array = data(mimeType);
		if(array.isEmpty())
			return a;

		QDataStream stream(&array,QIODevice::ReadOnly);
		T va;
		stream>>va;
		return va;
	}

	template<class T>
	///通过模版实现设置自定义数据  
	void INSIDES::MimeData::setCustomData( const QString& mimeType,const T& va )
	{
		QByteArray encodeData;
		QDataStream stream(&encodeData,QIODevice::WriteOnly);
		stream<<va;	
		this->setData(mimeType,encodeData);
	}

	QDataStream& operator << (QDataStream& out,const MimeData& item);
	QDataStream& operator >> (QDataStream& in,MimeData& item);
}


#endif // SAVEORREADCLASS_H
