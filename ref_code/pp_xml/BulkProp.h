#pragma once

#include "pp_xml/pp_xml_global.h"
#include <map>
#include <QString>


namespace pp
{
/*!
*	This class represents a list of properties.
*	@author Jerry He
*	@date 2013.9.10
*/
class  PP_XML_EXPORT BulkProp
{
public:
	BulkProp(void);
	BulkProp(QString strBuf);
	virtual ~BulkProp(void);

	typedef std::map<QString,QString> container_type;

	bool Parse(QString strBuf);
	QString Composite();

	int GetCount();
	double GetDouble(QString strKey);
	long GetLong(QString strKey);
	QString GetString(QString strKey);

	void SetDouble(QString strKey, double dValue);
	void SetLong(QString strKey, long lValue);
	void SetString(QString strKey, QString strValue);

	void Clear();

protected:
	void Set(QString& strKey, QString strValue);
	QString Get(QString& strKey);

	// Variables
protected:
	container_type m_map;

};


}