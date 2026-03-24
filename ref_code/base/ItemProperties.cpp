#include "ItemProperties.h"
#include <tchar.h>


namespace Base
{

	ItemProperties::ItemProperties(void)
	{
	}

	ItemProperties::ItemProperties(const QString& strBuf)
	{
		Parse(strBuf);
	}


	ItemProperties::~ItemProperties(void)
	{
		Clear();
	}


	long ItemProperties::GetLong(const QString& strKey)
	{
		QString strValue;
		if((strValue = Get(strKey))!= ("") ){
			return strValue.toLong();
		}
		return 0;
	}

	QString ItemProperties::GetString(const QString& strKey)
	{
		return Get(strKey);
	}

	double ItemProperties::GetDouble(const QString& strKey)
	{
		QString strValue;
		if((strValue = Get(strKey)) != ("") ){
			return strValue.toDouble();
		}
		return 0.0;
	}

	void ItemProperties::SetLong(const QString& strKey, long lValue)
	{
		QString strValue=QString::number(lValue);
		Set(strKey,strValue);
	}

	void ItemProperties::SetString(const QString& strKey, const QString& strValue)
	{
		Set(strKey,strValue);
	}

	void ItemProperties::SetDouble(const QString& strKey, double dValue)
	{
		QString strValue=QString::number(dValue);;
		Set(strKey,strValue);
	}

	bool ItemProperties::Parse(const QString& strBuff)
	{
		QString strBuf=strBuff;
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
					m_map[QString(buf_name)]=QString(buf_val);
					//m_map.insert(container_type::value_type(buf_name, buf_val));			
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

	void ItemProperties::Clear()
	{
		m_map.clear();
	}

	void ItemProperties::Set(const QString& strKey, const QString& strValue)
	{
		container_type::iterator itr = m_map.find(strKey);

		if(m_map.end() != itr)
		{
			(*itr) = strValue;
		}
		else{
			m_map[strKey]=strValue;
		}
	}

	QString ItemProperties::Get(const QString& strKey)
	{
		container_type::iterator itr = m_map.find(strKey);
		if(m_map.end() != itr)
		{
			return itr.value();	
		}
		return QString();
	}

	int ItemProperties::GetCount()
	{
		return m_map.size();
	}

	QString ItemProperties::Composite()const
	{
		// Format 
		// KEY="VALUE";KEY="VALUE";KEY="VALUE";
		if( m_map.empty() ) return "";

		QString strBuf = "";

		container_type::const_iterator itr;
		for(itr=m_map.constBegin();itr!=m_map.constEnd();++itr)
		{
			strBuf += itr.key() + QString("=\"") + itr.value() + QString("\";"); 
		}

		return strBuf;
	}

	bool ItemProperties::HasKey(const QString& key)
	{
		return m_map.find(key)!=m_map.end();
	}

	void ItemProperties::RemoveKey( const QString& key )
	{
		m_map.remove(key);
	}


}