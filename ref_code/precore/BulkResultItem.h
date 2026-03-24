#pragma once

#include "precore/iresultitem.h"
#include <QVector>

namespace INSIDES
{

/*!
*	代表简单的一片数据。
*	@author Jerry He
*	@date	2014.5.20
*/
class PRECORE_EXPORT BulkResultItem :
	public IResultItem
{
public:
	BulkResultItem(IResults* results,int frameCount,int dataSize);
	virtual ~BulkResultItem(void);

	virtual int sectionCount()const{return _size;}
	virtual QString sectionName(int section)const{return QString("%1").arg(section+1);}
	virtual int getDataLength()const{return _size;}

	virtual Precision* getData(int section,int subSection=-1,int sbusubSection=-1);
	virtual void setPos(int pos);

	friend PRECORE_EXPORT QDataStream& operator << (QDataStream& fout,const BulkResultItem& item);
	friend PRECORE_EXPORT QDataStream& operator >> (QDataStream& fin, BulkResultItem& item);

private:
	QVector<Precision>	_datas;
	int			_size;
	int			_frameCount;
	int			_currentIndex;
};


PRECORE_EXPORT QDataStream& operator << (QDataStream& fout,const BulkResultItem& item);
PRECORE_EXPORT QDataStream& operator >> (QDataStream& fin, BulkResultItem& item);

}