#pragma once

#include "pp_xml/pp_xml_global.h"
#include <list>
#include <QUuid>
#include <QStringList>
//#include <BXMObserver.h>



#define PP_BULK_MAGIC_STRING	_T("_JERRY_HE_PRODUCT_")

PP_XML_EXPORT bool  bxWriteBulkHeader(FILE* fp, unsigned long ulVer);
PP_XML_EXPORT bool  bxWriteBulkHeader(int fp, unsigned long ulVer);


namespace pp
{

class BulkBlock;


class  PP_XML_EXPORT BulkHandler  //: public CBXSubject 
{
public:
	BulkHandler(void);
	virtual ~BulkHandler(void);
public:
	bool AddFile(QString strFilePath);
	void Clear();
	
	typedef std::list<BulkBlock*> container_type;

	BulkBlock* FindBlock(QUuid guid);
	BulkBlock* FindFirstBlock(QString strID);
	void Remove(QUuid guid);
	void Remove(BulkBlock* pBlock);

protected:
	QStringList m_listFilePath;
	container_type m_listBlock;

};


}