#include "BulkHandler.h"
#include "BulkBlock.h"
#include <io.h>
#include <TCHAR.h>

#define MAX_PATH 1024

bool  bxWriteBulkHeader(FILE* fp, unsigned long ulVer)
{
	if( fp == NULL ) return FALSE;
	// magic string
	TCHAR szMagic[20];
	_tcscpy_s(szMagic,PP_BULK_MAGIC_STRING);
	fwrite(szMagic,sizeof(TCHAR),18,fp);
	// version
	fwrite(&ulVer,4,1,fp);
	return TRUE;
}

bool  bxWriteBulkHeader(int fp, unsigned long ulVer)
{
	if( fp== -1 ) return FALSE;
	// magic string
	TCHAR szMagic[20];
	_tcscpy_s(szMagic,PP_BULK_MAGIC_STRING);
	_write(fp, szMagic,sizeof(TCHAR)*18);
	// version
	_write(fp, &ulVer,4*1);
	return TRUE;

}

namespace pp
{

BulkHandler::BulkHandler(void)
{
}

BulkHandler::~BulkHandler(void)
{
	Clear();
}


BulkBlock* BulkHandler::FindBlock(QUuid guid)
{
	if(guid.isNull())
		return NULL;

	container_type::iterator itr;
	for(itr=m_listBlock.begin();itr!=m_listBlock.end();++itr){
		if( (*itr)->GetGUID() == guid ) return (*itr);
	}
	return NULL;
}

BulkBlock* BulkHandler::FindFirstBlock( QString strID )
{
	if(strID.isEmpty() )
		return NULL;

	container_type::iterator itr;
	for(itr=m_listBlock.begin();itr!=m_listBlock.end();++itr){
		if( (*itr)->GetID() == strID ) return (*itr);
	}
	return NULL;
}

void BulkHandler::Remove(BulkBlock *pBlock)
{
	if( pBlock == NULL ) return;
	delete pBlock;
	m_listBlock.remove(pBlock);
}

void BulkHandler::Remove(QUuid guid)
{
	Remove(FindBlock(guid));
}

void BulkHandler::Clear()
{
	m_listFilePath.clear();
	container_type::iterator itr;
	for(itr=m_listBlock.begin();itr!=m_listBlock.end();++itr){
		delete (*itr);
	}
	m_listBlock.clear();
}


bool BulkHandler::AddFile(QString strFilePath)
{
	FILE* fp = NULL;
	errno_t err;

	if((err=_tfopen_s(&fp, (const TCHAR*)strFilePath.utf16(),_T("rb")))!=0)
		return FALSE;

	long lSize = _filelength(_fileno(fp));
	long lCurPos = 0L;
	int  nPos = 0;

	long lSizeMagic = _tcslen(PP_BULK_MAGIC_STRING);
	TCHAR szmagic[MAX_PATH];
	fread(szmagic,sizeof(TCHAR),lSizeMagic,fp);
	szmagic[lSizeMagic] = 0;

	if( _tcscmp(szmagic,PP_BULK_MAGIC_STRING) ){
		fclose(fp);
		return FALSE;
	}

	// Check Version
	unsigned long ulVer;
	fread(&ulVer,4,1,fp);

	while(!feof(fp))
	{
		BulkBlock* pBlock = new BulkBlock;
		if( pBlock->Scan(strFilePath,fp) ){
			m_listBlock.push_back(pBlock);
		}
		else{
			delete pBlock;
			break;
		}
		lCurPos = ftell(fp);
		nPos = (int)(((float)lCurPos/(float)lSize)*100);
		//Notify(BX_SUB_UM_PROGRESS_MSG, BX_SUB_UM_SEND_PROGPOS_MSG, nPos);
	}
	m_listFilePath.push_back(strFilePath);
	fclose(fp); //THJ (Some modification is needed) 
	return TRUE;
}

}