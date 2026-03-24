#include "errormanager.h"

namespace Parse{


	////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////
	QString ErrorItem::toString() const
	{
		return QString("%1_%2_%3").arg(fileName).arg(lineIndex).arg(columnIndex);
	}

	////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////
	ErrorItemManager::ErrorItemManager(QObject* parent):QObject(parent)
	{
		connect(this,SIGNAL(pAdd(const ErrorItem&)),this,SLOT(onPAdd(const ErrorItem&)));
		connect(this,SIGNAL(pClear()),this,SLOT(onPClear()));
		connect(this,SIGNAL(pClear(const QString&)),this,SLOT(onPClear(const QString&)));
	}

	ErrorItemManager::~ErrorItemManager()
	{
		clear();
	}

	void ErrorItemManager::clear()
	{
		emit pClear();
	}

	void ErrorItemManager::clear( const QString& fileName )
	{
		emit pClear(fileName);
	}

	void ErrorItemManager::add( const ErrorItem& errorItem )
	{
		emit pAdd(errorItem);
	}


	void ErrorItemManager::onPAdd( const ErrorItem& errorItem )
	{
		QString str=errorItem.toString();
		if(_errorMap.find(str)==_errorMap.end()){
			ErrorItem* newError=new ErrorItem(errorItem);
			_errorMap[str]=newError;
			_errorList.push_back(newError);
			emit changed();
			return;
		}
	}

	void ErrorItemManager::onPClear()
	{
		qDeleteAll(_errorList);
		_errorList.clear();
		_errorMap.clear();
		emit changed();
	}

	void ErrorItemManager::onPClear( const QString& fileName )
	{
		QList<ErrorItem*> tmpList=_errorList;
		foreach(ErrorItem* tmp,tmpList)
		{
			if(tmp->fileName.compare(fileName,Qt::CaseInsensitive)==0){
				_errorList.removeOne(tmp);
				_errorMap.remove(tmp->toString());
			}
		}
		emit changed();
	}


}

