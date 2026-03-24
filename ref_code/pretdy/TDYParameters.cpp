#include "TDYParameters.h"
#include <map>
#include <string>
#include <QList>
#include <QObject>

#include "parameter/Parameter_Pre.h"

using namespace std;

typedef map<std::string,Parameter*> ParameterList;

class TDYParametersPrivate
{
public:
	QList<TDYParameterItem> _itemlist;
	ParameterList _tdyMaps;
	Parameter* _tmpPara;
	
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
TDYParameters::TDYParameters(void)
	:_ptr(new TDYParametersPrivate())
{
	_ptr->_tmpPara=parameter_create();
}


TDYParameters::~TDYParameters(void)
{
	clear();
	parameter_destory(_ptr->_tmpPara);
}

int TDYParameters::count() const
{
	return _ptr->_itemlist.size();
}

const TDYParameterItem* TDYParameters::getAt( int index )const
{
	return &_ptr->_itemlist[index];
}

bool TDYParameters::add( const TDYParameterItem& item )
{
	QString str;
	return add(item,str);
}

bool TDYParameters::add( const TDYParameterItem& item,QString& errMessage )
{
	string keyname=item.keyname.toStdString();
	QString qPara=item.strPara;
	if(qPara[0]=='"')
		qPara=qPara.mid(1,qPara.size()-2);
	string para=qPara.toStdString();
	if(_ptr->_tdyMaps.find(keyname)!=_ptr->_tdyMaps.end()){
		errMessage=QString(QObject::tr("Parameter: %1 already exists")).arg(item.keyname);
		return false;
	}

	Parameter* newItem=parameter_create();
	int result=parameter_str2para(newItem,para,& (_ptr->_tdyMaps));

	if(result!=0)
	{
		parameter_destory(newItem);
		return false;
	}

	_ptr->_tdyMaps[keyname]=newItem;
	_ptr->_itemlist.push_back(item);
	return true;
}

bool TDYParameters::addOrReplace( const TDYParameterItem& item)
{
	string keyname=item.keyname.toStdString();
	string para=item.strPara.toStdString();
	ParameterList::iterator f=_ptr->_tdyMaps.find(keyname);
	if(f!=_ptr->_tdyMaps.end()){
		parameter_destory(f->second);
		_ptr->_tdyMaps.erase(f);
		for(int j=0;j<_ptr->_itemlist.size();++j)
			if(_ptr->_itemlist[j].keyname==item.keyname){
				_ptr->_itemlist.removeAt(j);
				break;
			}
	}

	Parameter* newItem=parameter_create();
	int result=parameter_str2para(newItem,para,& (_ptr->_tdyMaps));

	if(result!=0)
	{
		parameter_destory(newItem);
		return false;
	}

	_ptr->_tdyMaps[keyname]=newItem;
	_ptr->_itemlist.push_back(item);
	return true;
}

bool TDYParameters::add( const QString& key,const QString& para )
{
	TDYParameterItem item;
	item.keyname=key;
	item.strPara=para;
	return add(item);
}

bool TDYParameters::add( const QString& key,const QString& para,const QString& des )
{
	TDYParameterItem item;
	item.keyname=key;
	item.strPara=para;
	item.description=des;
	return add(item);
}

bool TDYParameters::add( const QString& key,const QString& para,const QString& des,QString& errmess )
{
	TDYParameterItem item;
	item.keyname=key;
	item.strPara=para;
	item.description=des;
	return add(item,errmess);
}

void TDYParameters::clear()
{
	_ptr->_itemlist.clear();
	for(ParameterList::iterator b=_ptr->_tdyMaps.begin();
		b!=_ptr->_tdyMaps.end();++b)
		parameter_destory(b->second);
	_ptr->_tdyMaps.clear();
}

double TDYParameters::getValue( const QString& str ,bool* result) const
{
	int re=parameter_str2para(_ptr->_tmpPara,str.toStdString(),&_ptr->_tdyMaps);
	if(result)
		*result=(re==0);
	if(!re)
		return parameter_eval(_ptr->_tmpPara);
	else
		return 0;
}

TDYParameters* TDYParameters::clone() const
{
	TDYParameters* para=new TDYParameters();
	int n=this->count();
	for(int i=0;i<n;++i)
	{
		const TDYParameterItem* item=getAt(i);
		para->add(*item);
	}
	return para;
}

QList<TDYParameterItem> TDYParameters::getAll() const
{
	return _ptr->_itemlist;
}

bool TDYParameters::hasKey( const QString& key ) const
{
	foreach(const TDYParameterItem& item,_ptr->_itemlist)
	{
		if(key==item.keyname)
			return true;
	}
	return false;

}

bool TDYParameters::addOrReplace( const QString& key,const QString& para )
{
	TDYParameterItem item;
	item.keyname=key;
	item.strPara=para;
	return addOrReplace(item);
}

QDataStream &	operator<< ( QDataStream & out, const TDYParameterItem& paras )
{
	return out<<paras.keyname<<paras.strPara<<paras.description;
}
QDataStream &	operator>> ( QDataStream & in, TDYParameterItem& paras )
{
	return in>>paras.keyname>>paras.strPara>>paras.description;
}

QDataStream &	operator<< ( QDataStream & out, const TDYParameters& paras )
{
	out<<paras._ptr->_itemlist;
	return out;
}

QDataStream &	operator>> ( QDataStream & in, TDYParameters& paras )
{
	QList<TDYParameterItem> paralist;
	in>>paralist;
	for(int i=0;i<paralist.size();++i)
		paras.add(paralist[i]);

	return in;
}