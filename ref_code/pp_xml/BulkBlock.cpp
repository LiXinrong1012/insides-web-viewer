#include "BulkBlock.h"

#include <fcntl.h>
#include <io.h>
#include <tchar.h>
#include <wchar.h>
#include <QStdWString>
#include <string>
#include <xstring>

using namespace std;

namespace pp
{

bool _writeBulkGeneral(FILE* fp, QUuid uuid,const QString& strID, BulkProp* pProp)
{
	if( fp == NULL ) return false;

	// write QUuid
	fwrite(&uuid, sizeof(QUuid), 1, fp);

	// write Identifier
	TCHAR buf[256];
	memset(buf,0,sizeof(TCHAR)*256);
	strID.toWCharArray(buf);
	//_tcscpy_s(buf,strID.toWCharArray());
	fwrite(buf,sizeof(TCHAR), 256,fp);

	// write properties
	QString strProp = pProp->Composite();
	unsigned long lengthText  = strProp.length();
	unsigned long sizeProp = lengthText * sizeof(TCHAR);
	fwrite(&sizeProp, sizeof(unsigned long), 1, fp);
	fwrite(strProp.constData(),sizeof(char),lengthText*2, fp);
	return true;
}

void _writeBulkData(FILE* fp,void* lpData,unsigned long ulSizeData)
{
	// write data
	fwrite(&ulSizeData,sizeof(unsigned long), 1, fp);
	fwrite(lpData,1, ulSizeData,fp);	
}

void _writeBulkData(FILE* fp,void** lpData,long lCntSubItem, unsigned long ulSizeData)
{
	// write data
	unsigned long sz = ulSizeData * lCntSubItem;
	fwrite(&sz,sizeof(unsigned long), 1, fp);
	for(long i=0;i<lCntSubItem; i++)
	{
		fwrite(lpData[i],ulSizeData,1,fp);
	}
}

bool bxWriteBulkBlock(FILE* fp, QUuid uuid, QString strID, BulkProp* pProp, void* lpData, unsigned long ulSizeData)
{
	if(!_writeBulkGeneral(fp,uuid,strID,pProp))
		return false;

	_writeBulkData(fp,lpData,ulSizeData);
	return true;
}


bool bxWriteBulkBlock(FILE* fp, QUuid uuid, QString strID, BulkProp* pProp, void** lppData, 
	long lCntSubItem, unsigned long ulSizeData)
{
	if(!_writeBulkGeneral(fp,uuid,strID,pProp))
		return false;

	_writeBulkData(fp,lppData,lCntSubItem,ulSizeData);
	return true;
}


/*
bool bxWriteBulkBlock(int fp, QUuid tmpQUuid, QString strID, BulkProp* pProp, void* lpData, unsigned long ulSizeData)
{
	if( fp == -1 ) return FALSE;

	// write QUuid
	_write(fp, &tmpQUuid, sizeof(QUuid));

	// write Identifier
	TCHAR buf[256];
	memset(buf,0,sizeof(TCHAR)*256);
	strID.toWCharArray(buf);
	_write(fp, buf,sizeof(TCHAR)*256);

	// write properties
	QString strProp = pProp->Composite();
	unsigned long lengthText  = strProp.length();
	unsigned long sizeProp = lengthText * sizeof(TCHAR);
	_write(fp, &sizeProp, sizeof(unsigned long));
	_write(fp, strProp.constData(),sizeof(char)*lengthText*2);

	// write data
	_write(fp, &ulSizeData,sizeof(unsigned long));
	_write(fp, lpData,ulSizeData);

	return TRUE;
}


bool bxWriteBulkBlock(int fp, QUuid tmpQUuid, QString strID, BulkProp* pProp, void** lppData, 
	long lCntSubItem, unsigned long ulSizeData)
{
	if( fp == -1 ) return FALSE;

	// write QUuid
	_write(fp, &tmpQUuid, sizeof(QUuid));

	// write Identifier
	TCHAR buf[256];
	memset(buf,0,256*sizeof(TCHAR));
	_
	_tcscpy_s(buf,strID);
	_write(fp, buf,sizeof(TCHAR)*256);

	// write properties
	QString strProp = pProp->Composite();
	unsigned long lengthText  = strProp.GetLength();
	unsigned long sizeProp = lengthText * sizeof(TCHAR);
	_write(fp, &sizeProp, sizeof(unsigned long) );
	_write(fp, (LPCTSTR)strProp,sizeof(TCHAR) * lengthText);

	// write data
	unsigned long sz = ulSizeData * lCntSubItem;
	_write(fp, &sz,sizeof(unsigned long));
	for(long i=0;i<lCntSubItem; i++)
	{
		_write(fp, lppData[i],ulSizeData);
	}
	return TRUE;
}
*/



BulkBlock::BulkBlock(void)
{
}

BulkBlock::~BulkBlock(void)
{
}


unsigned long BulkBlock::LoadData(void* lpData, long lStartPos, long lSize)
{
	if( !lpData ) return 0;
	errno_t err;
	FILE* fp=NULL;
	wstring str=m_strFilePath.toStdWString();
	if((err=_tfopen_s(&fp, str.c_str(),_T("rb"))) != 0){// File Open Error
		return 0;
	}
	fpos_t posData = m_posData + (fpos_t)lStartPos;

	unsigned long sizeData = m_ulSizeData - (unsigned long)lStartPos;
	if( lSize > 0  ){
		sizeData = lSize;
	}

	fsetpos(fp,&posData);
	if( fread(lpData, sizeData, 1, fp) != 1 ){	// File Reading Error
		fclose(fp);
		return 0;
	}
	// succeed
	fclose(fp);
	return sizeData;
}


unsigned long BulkBlock::LoadData(void** lppData, long lSubItem, long lSize)
{
	if( !lppData ) return 0;
	if( lSubItem * lSize <= 0 ) return 0;
	if( lSubItem * lSize > (long)m_ulSizeData ) return 0;

	errno_t err;
	FILE* fp=NULL;
	wstring str=m_strFilePath.toStdWString();
	if((err = _tfopen_s(&fp, str.c_str(),_T("rb"))) != 0){	// File Open Error
		return 0;
	}

	fsetpos(fp,&m_posData);
	unsigned long lRead = 0;
	for(long i=0;i<lSubItem;i++)
	{
		if( fread(lppData[i], lSize, 1, fp) != 1 ){	// File Reading Error
			fclose(fp);
			return lRead;
		}	
		lRead += lSize;
	}
	// succeed
	fclose(fp);
	return lRead;
}


bool BulkBlock::Scan(QString strFilePath, FILE* fp)
{
	if( strFilePath == ("") || fp == NULL ) return false;
	Clear();

	// Set path
	m_strFilePath = strFilePath;

	// save current file pos
	fgetpos(fp,&m_posBlock);

	TCHAR strbuf[256];

	//////////////////////////////////////////////////////////////////////////
	// read QUuid
	QUuid uuid;
	if( fread(&uuid,sizeof(QUuid),1,fp) != 1 ){
		Clear(); return FALSE;
	}
	m_QUuid = uuid;

	//////////////////////////////////////////////////////////////////////////
	// read ID
	fgetpos(fp, &m_posID);
	if( fread(strbuf,sizeof(TCHAR),256,fp) != 256 ){
		Clear(); 
		return false;
	}
	m_strID=QString::fromWCharArray(strbuf);

	//////////////////////////////////////////////////////////////////////////
	// read Property
	TCHAR* buf = NULL;
	unsigned long sizeProp;
	if( fread(&sizeProp,sizeof(unsigned long),1,fp) != 1){
		Clear(); return FALSE;
	}
	unsigned long lengthText = sizeProp / sizeof(TCHAR);
	fgetpos(fp,&m_posProp);

	if( sizeProp > 0 ){
		buf = new TCHAR[lengthText+1];
		memset(buf,0,sizeof(TCHAR)*(lengthText+1));
		if( fread(buf, sizeof(TCHAR), lengthText, fp) != lengthText ){
			delete [] buf;
			Clear(); return FALSE;
		}
		// Parse properties
		m_prop.Parse(QString::fromWCharArray(buf));
		delete [] buf;
	}	

	//////////////////////////////////////////////////////////////////////////
	// read data size and skip data block
	if( fread(&m_ulSizeData, sizeof(long),1,fp) != 1 ){ 
		Clear(); 
		return FALSE;
	}
	fgetpos(fp,&m_posData);
	fpos_t posNext = m_posData + (fpos_t)m_ulSizeData;
	fsetpos(fp,&posNext);

	return TRUE;
}

void BulkBlock::Clear()
{
	m_prop.Clear();
	m_bEmpty = TRUE;
	m_posID = 0;
	m_posProp = 0;
	m_posData = 0;
	m_strFilePath =QString("");
	m_ulSizeData = 0;
	m_strID =QString("");
}


}