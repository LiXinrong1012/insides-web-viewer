#pragma once

#include "base/base_global.h"
#include <map>
#include <QMap>
#include <QString>
#include <QDataStream>


namespace Base
{
/*!
*	This class represents a list of properties.
*	@author Jerry He
*	@date 2013.9.10
*	modified to use as the class properties.
*	Jerry, 2014.2.25
*/
class BASE_EXPORT ItemProperties
{
public:
	ItemProperties(void);
	ItemProperties(const QString& strBuf);
	virtual ~ItemProperties(void);

	typedef QMap<QString,QString> container_type;

	bool Parse(const QString& strBuf);
	QString Composite()const;

	int GetCount();
	double GetDouble(const QString& strKey);
	long GetLong(const QString& strKey);
	QString GetString(const QString& strKey);

	void SetDouble(const QString& strKey, double dValue);
	void SetLong(const QString& strKey, long lValue);
	void SetString(const QString& strKey, const QString& strValue);

	void Clear();
	bool HasKey(const QString& key);
	void RemoveKey(const QString& key);
	QString& operator[] (const QString& nIndex){return m_map[nIndex];}

	container_type& getMap(){return m_map;}

	friend QDataStream& operator<< (QDataStream& out,const ItemProperties& item);
	friend QDataStream& operator>> (QDataStream& in,ItemProperties& item);

protected:
	void Set(const QString& strKey, const QString &strValue);
	QString Get(const QString& strKey);

	// Variables
protected:
	container_type m_map;

};

inline QDataStream&  operator<< (QDataStream& out,const ItemProperties& item){
	return out<<item.m_map;
}
inline QDataStream&  operator>> (QDataStream& in,ItemProperties& item){
	return in>>item.m_map;
}


}	//end namespace Base