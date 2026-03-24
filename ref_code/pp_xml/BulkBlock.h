#pragma once

#include "pp_xml/pp_xml_global.h"
#include "BulkProp.h"
#include <stdio.h>
#include <QUuid>
#include <QString>

namespace pp
{
class BulkBlock;

PP_XML_EXPORT bool bxWriteBulkBlock(FILE* fp, QUuid QUuid, QString strID, BulkProp* pProp, 
	void* lpData, unsigned long ulSizeData);
PP_XML_EXPORT bool bxWriteBulkBlock(FILE* fp, QUuid QUuid, QString strID, BulkProp* pProp, 
	void** lppData, long lCntSubItem, unsigned long ulSizeData);

template<class T>
QUuid bxSaveSimpleArrayToBulk(FILE* fp,QString strId,T* data,long size)
{
	QUuid uuid;
	if(data!=NULL && size>0)
	{
		uuid=QUuid::createUuid();
		BulkProp prop;
		prop.SetLong("COUNT",size);
		bxWriteBulkBlock(fp,uuid,strId,&prop,data,size*sizeof(T));
	}
	return uuid;
}

template<class T>
long bxLoadSimpleArrayFromBulk(pp::BulkBlock* block,T** dataDist)
{
	BulkProp* prop=block->GetProperties();
	long count=prop->GetLong("COUNT");
	if(count<=0)
		return 0;
	*dataDist=new T[count];
	block->LoadData(*dataDist);
	return count;
}

/*
bool bxWriteBulkBlock(int fp, QUuid QUuid, QString strID, BulkProp* pProp, 
	void* lpData, unsigned long ulSizeData);
bool bxWriteBulkBlock(int fp, QUuid QUuid, QString strID, BulkProp* pProp, 
	void** lppData, long lCntSubItem, unsigned long ulSizeData);
*/




class PP_XML_EXPORT BulkBlock
{
public:
	BulkBlock(void);
	virtual ~BulkBlock(void);
	BulkBlock(QString strFilePath, FILE* fp);

	void Clear();

	QString GetID() { return m_strID; }
	BulkProp* GetProperties() { return &m_prop; }	
	fpos_t GetDataPos() { return m_posData; }
	QString GetFilePath() { return m_strFilePath; }
	QUuid GetGUID() { return m_QUuid; }
	unsigned long GetDataSize() { return m_ulSizeData; }

	// return value = size of binary data in bytes
	unsigned long LoadData(void* lpData, long lStartPos = 0, long lSize = -1);
	unsigned long LoadData(void** lppData, long lSubItem, long lSize);

	bool Scan(QString strFilePath, FILE* fp);

	QString m_strFilePath;
	QUuid m_QUuid;
	bool m_bEmpty;

	// Start Block
	fpos_t m_posBlock;

	// Identifier
	fpos_t m_posID;
	QString m_strID;

	// Properties
	fpos_t m_posProp;
	BulkProp m_prop;

	// Data Block
	fpos_t	m_posData;
	unsigned long m_ulSizeData;
};

}	//end namespace pp