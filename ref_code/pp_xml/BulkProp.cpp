#include "BulkProp.h"
#include <tchar.h>


namespace pp
{

BulkProp::BulkProp(void)
{
}

BulkProp::BulkProp(QString strBuf)
{
	Parse(strBuf);
}


BulkProp::~BulkProp(void)
{
	Clear();
}


long BulkProp::GetLong(QString strKey)
{
	QString strValue;
	if((strValue = Get(strKey))!= ("") ){
		return strValue.toLong();
	}
	return 0;
}

QString BulkProp::GetString(QString strKey)
{
	return Get(strKey);
}

double BulkProp::GetDouble(QString strKey)
{
	QString strValue;
	if((strValue = Get(strKey)) != ("") ){
		return strValue.toDouble();
	}
	return 0.0;
}

void BulkProp::SetLong(QString strKey, long lValue)
{
	QString strValue=QString::number(lValue);
	Set(strKey,strValue);
}

void BulkProp::SetString(QString strKey, QString strValue)
{
	Set(strKey,strValue);
}

void BulkProp::SetDouble(QString strKey, double dValue)
{
	QString strValue=QString::number(dValue);;
	Set(strKey,strValue);
}

bool BulkProp::Parse(QString strBuf)
{
	if(!m_map.empty())
		m_map.clear();

	strBuf.replace(("\n"),(""));
	strBuf.replace(("\r"),(""));

	QChar buf_name[1024], buf_val[2048];

	QString buf = strBuf;

	int len = strBuf.length();
	if( len < 1 ) return false;

	int idx, idx_sub;
	bool bBraceOpen, bValueArea;

	idx = 0;
	idx_sub = 0;
	buf_name[0] = 0;
	buf_val[0] = 0;
	bBraceOpen = false;
	bValueArea = false;
	while( buf[idx] != 0 ){
		if( buf[idx] == QChar('=') && !bBraceOpen ){
			idx_sub = 0;
			bValueArea = true;
		}
		else if( buf[idx] == QChar('"') && bValueArea){
			bBraceOpen = !bBraceOpen;
		}
		else if( buf[idx] !=QChar( ';') || bBraceOpen ){  
			// char add
			if( !bValueArea && buf[idx]!=QChar(' ') ){
				buf_name[idx_sub] = buf[idx];
				buf_name[idx_sub+1] = 0;
				idx_sub++;
			}
			else if( bBraceOpen ){
				buf_val[idx_sub] = buf[idx];
				buf_val[idx_sub+1] = 0;
				idx_sub++;
			}

		}


		if( ( buf[idx] == QChar(';') && !bBraceOpen) || idx == len-1  ){

			// Add Parameter

			if( bValueArea ){
				m_map.insert(container_type::value_type(buf_name, buf_val));			
			}

			// Reset
			bBraceOpen = false;
			bValueArea = false;
			idx_sub = 0;
			buf_name[0] = buf_val[0] = 0;

		}

		idx++;
	}

	return TRUE;

}

void BulkProp::Clear()
{
	m_map.clear();
}

void BulkProp::Set(QString& strKey, QString strValue)
{
	container_type::iterator itr = m_map.find(strKey);

	if(m_map.end() != itr)
	{
		(*itr).second = strValue;
	}
	else{
		m_map.insert(container_type::value_type(strKey, strValue));
	}
}

QString BulkProp::Get(QString& strKey)
{
	container_type::iterator itr = m_map.find(strKey);
	if(m_map.end() != itr)
	{
		return (*itr).second;		
	}
	return "";
}

int BulkProp::GetCount()
{
	return m_map.size();
}

QString BulkProp::Composite()
{
	// Format 
	// KEY="VALUE";KEY="VALUE";KEY="VALUE";
	if( m_map.empty() ) return "";

	QString strBuf = "";

	container_type::iterator itr;
	for(itr=m_map.begin();itr!=m_map.end();++itr)
	{
		strBuf += (*itr).first + QString("=\"") + (*itr).second + QString("\";"); 
	}

	return strBuf;
}

}