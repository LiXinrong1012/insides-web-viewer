#include "ExportTDY.h"
#include "precore/PreDocument.h"
#include "precore/itemlist.h"
#include "precore/precore_data.h"
#include "precore/TypeDataManager.h"
#include "precore/DataExchangeAPI.h"
#include "base/Console.h"

#include "pretdy/TDYParameters.h"

#include <QtCore>

using namespace Base;

class ExportTDYPrivate
{
public:
	void writeAssembly(BaseItem* item,bool isRoot=false);
	void writeParameter(BaseItem* item);
	void writeRigidPart(BaseItem* item);
	void writeRigid6(BaseItem* item);
	void writeInstance(BaseItem* item);
	void writeItem(BaseItem* item);
	void writeProperties(BaseItem* item);
	void writeGeneralItem(BaseItem* item);
	
	QTextStream* out;
	TypeDataManager* typeDataManager;
};

void ExportTDYPrivate::writeAssembly( BaseItem* item,bool isRoot/*=false*/ )
{
	Assembly* assembly=(Assembly*)item;
	if(isRoot){
		int n=assembly->count();
		for(int i=0;i<n;++i)
			writeItem(assembly->child(i));
	}
}

void ExportTDYPrivate::writeItem( BaseItem* item )
{
	if(item->getIncluded())
		return;
	switch(item->getCategory()){
	case TDY_PRE_CATE_FOLDER:
		{
			int n=item->count();
			for(int i=0;i<n;++i)
				writeItem(item->child(i));
			break;
		}
	case TDY_PRE_CATE_RIGIDPART:
		{
			writeRigidPart(item);
			break;
		}
	case TDY_PRE_CATE_PARAMETERS:
		{
			writeParameter(item);
			break;
		}
	//case TDY_PRE_CATE_INSTNACE:
	//	{
	//		writeInstance(item);
	//		break;
	//	}
	case TDY_PRE_CATE_MARKER:
	case TDY_PRE_CATE_JOINT:
	case TDY_PRE_CATE_MOTION:
	case TDY_PRE_CATE_INTPAR:
		{
			writeGeneralItem(item);
			break;
		}
	default:
		Console().Warning("Item (%s) was not exported.",item->getKeyName().toAscii().constData());
		break;
	}
}

void ExportTDYPrivate::writeRigidPart( BaseItem* item )
{
	TypeData* data=typeDataManager->getTypeData(item->getCategory());
	
	(*out)<<"RigidPart / "<<item->getKeyName()<<" {"<<endl;

	writeRigid6(item);

	int n=item->count();
	for(int i=0;i<n;++i)
		writeItem(item->child(i));

	(*out)<<"}"<<endl<<endl;

}

void ExportTDYPrivate::writeRigid6( BaseItem* item )
{
	TypeData* data=typeDataManager->getTypeData(item->getCategory());
	(*out)<<data->TDYName<<" / "<<item->getKeyName();
	writeProperties(item);
	(*out)<<endl;
}

void ExportTDYPrivate::writeProperties( BaseItem* item )
{
	TypeData* data=typeDataManager->getTypeData(item->getCategory());
	
	for(int i=0;i<data->groups.size();++i)
	{
		TypeDataGroup& group=data->groups[i];
		for(int j=0;j<group.items.size();++j){
			TypeDataSingleItem& single=group.items[j];
			if(item->hasKey(single.keyname)){
				(*out)<<","<<single.keyname<<"="<<item->get(single.keyname);
			}
		}
	}
}

void ExportTDYPrivate::writeGeneralItem( BaseItem* item )
{
	TypeData* data=typeDataManager->getTypeData(item->getCategory());
	(*out)<<data->TDYName<<" / "<<item->getKeyName();
	writeProperties(item);
	(*out)<<endl;
}

void ExportTDYPrivate::writeParameter( BaseItem* item )
{
	ParametersBaseItem* paraItem=(ParametersBaseItem*)item;
	const TDYParameters* para=paraItem->getParameters();
	if(!para)
		return;
	int n=para->count();
	if(n==0)
		return;

	(*out)<<"Parameter / "<<paraItem->getKeyName();

	for(int i=0;i<n;++i){
		const TDYParameterItem* onePara=para->getAt(i);
		(*out)<<","<<endl;
		(*out)<<onePara->keyname<<"="<<onePara->strPara;
	}
	(*out)<<endl;
}

void ExportTDYPrivate::writeInstance( BaseItem* item )
{
	(*out)<<"Instance / "<<item->getKeyName()<<",";
	QString name=item->get(BaseItem::instanceKeyName);
	QString tdyName=DataExchangeAPI::fullName2TDYName(name);
	(*out)<<"part="<<tdyName<<endl;

	int n=item->count();
	for(int i=0;i<n;++i)
		writeItem(item->child(i));
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
ExportTDY::ExportTDY(void)
	:_ptr(new ExportTDYPrivate())
{
	_ptr->typeDataManager=TypeDataManager::instance();
}


ExportTDY::~ExportTDY(void)
{
}

bool ExportTDY::doJob( const QString& fileName )
{
	QFile file(fileName);
	if(!file.open(QFile::WriteOnly)){
		Console().Error("Open file failed.");
		return false;
	}

	QTextStream out(&file);
	_ptr->out=&out;
	PreDocument* doc=myDocument();
	_ptr->writeAssembly(doc->getAssembly(),true);
	return true;
}
