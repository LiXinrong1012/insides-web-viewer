#include "BaseItem.h"
#include <QDebug>
#include <QtCore>
#include "precore_data.h"
#include "base/ItemProperties.h"
#include "BaseItemFactory.h"
#include "base/Console.h"
#include <QtAlgorithms>
#include <vector>
#include "modeldocument.h"

#include <osg/Matrixf>

using namespace std;

namespace INSIDES
{


QString BaseItem::instanceKeyName=QString("_INSTANCE_NAME");

BaseItem::BaseItem( const QString& keyname )
	:_category(0)
	,_id(0)
	,_parent(NULL)
	,_keyname(keyname)
	,_classType(TDY_PRE_ITEMCLASS_BASEITEM)
	,_properties(NULL)
	,_appearance(new AppearanceItem())
	,_matrix(NULL)
{
	_flags[0]=true;
	_flags[1]=false;
	_flags[2]=false;
	_flags[3]=false;
	_flags[4]=false;
}


BaseItem::~BaseItem(void)
{
	if(_properties)
		delete _properties;
	if(_appearance)
		delete _appearance;
	if(_matrix)
		delete _matrix;

	clearChildren();
}

void BaseItem::copyTo( BaseItem* item ) const
{
	// 首先判断清空item的创建内存，否则会内存泄漏
	if(item->_properties){
		delete item->_properties;
		item->_properties=NULL;
	}
	item->_category=this->_category;
	item->_id=this->_id;
	item->_keyname=this->_keyname;
	//item->_parent=this->_parent;
	item->_flags=this->_flags;
	item->_classType=this->_classType;

	if(this->_appearance)
		item->setAppearance(_appearance->clone());
	else
		item->setAppearance(NULL);

	item->setMatrix(this->_matrix);

	//　处理属性的深拷备
	if(_properties){
		Properties* p=new Properties(*_properties);
		item->_properties=p;
	}
}

BaseItem* BaseItem::clone()const
{
	BaseItem* item;
	item=(BaseItem*)BaseItemFactory()->Produce(this->getCategory());

	if(!item)
		return NULL;
	copyTo(item);
	return item;
}

void BaseItem::printProperties()
{
	//qDebug()<<_properties<<endl;
}

QString BaseItem::toString()
{
	QString str=
		QString("[%1,%2,%3]").arg(_keyname).arg(_category).arg(_id);
	return str;
}


BaseItem* BaseItem::child( const QString& keyname )
{
	int n=this->count();
	for(int i=0;i<n;++i)
	{
		BaseItem* c=child(i);
		if(keyname.compare(c->getKeyName(),Qt::CaseInsensitive)==0)
			return c;
	}
	return NULL;
}
const BaseItem* BaseItem::child( int index ) const
{
	return _itemList[index];
}


int BaseItem::row() const
{
	if(_parent)
		return _parent->indexOf(const_cast<BaseItem*>(this));
	else
		return 0;
}



QString BaseItem::get( const QString& index ) const
{
	if(!_properties)
		return QString();
	return _properties->GetString(index);
}

bool BaseItem::hasKey( const QString& index ) const
{
	if(!_properties)
		return false;
	return _properties->HasKey(index);
}

QString BaseItem::getFullName() const
{
	if(!_parent)
		return QString();	//根节点不进入路径。
		//return getKeyName();
	else
	{
		return _parent->getFullName()+"."+getKeyName();
	}
}

void BaseItem::removeKey( const QString& index )
{
	if(!_properties)
		return;
	_properties->RemoveKey(index);
}

QString& BaseItem::operator [] (const QString& nIndex)
{
	Properties* p=getOrCreateProperties();
	return (*p)[nIndex];
}

QString BaseItem::operator[]( const QString& index ) const
{
	if(!_properties)
		return QString();
	return _properties->GetString(index);
}

BaseItem::Properties* BaseItem::getOrCreateProperties()
{
	if(!_properties)
		_properties=new Base::ItemProperties();
	return _properties;
}

QMap<QString,QString>& BaseItem::getMap()
{
	Properties* p=getOrCreateProperties();
	return p->getMap();
}

bool BaseItem::hasProperties() const
{
	if(!_properties)
		return false;
	return _properties->GetCount()!=0;
}

QString BaseItem::getPropertiesString() const
{
	if(!_properties)
		return QString();
	return _properties->Composite();
}

void BaseItem::setPropertiesString( const QString& str )
{
	Properties* p=getOrCreateProperties();
	p->Parse(str);
}


BaseItem* BaseItem::createInstance()
{
	BaseItem* item=this->clone();
	(*item)[instanceKeyName]=this->getFullName();
	item->setIsInstance(true);
	createInstanceChildren(this,item);
	return item;
}

void BaseItem::updateInstance( const BaseItem* src,BaseItem* dst )
{
	QString dstName=dst->get(instanceKeyName);
	QString name=dst->getKeyName();
	long flags=dst->getFlags();
	if(dstName.isEmpty()){
		Base::Console().Warning("Update instance failed.");
		return;
	}

	static QString globalAttitudes[] = { "THETA", "PHI"
		, "EULER321", "EULER323", "EULER313", "EULER312" 
		, "EULER212", "EULER213", "EULER231", "EULER232"
		, "EULER123", "EULER121", "EULER131", "EULER132" 
		, "CENTER", "XAXIS","YAXIS","ZAXIS","PARA_NAME","PARA_VALUE"} ;
	static int attitudesSize=20;
	QList<QPair<QString,QString> > oldProperties;
	for(int i=0;i<attitudesSize;++i){
		if(!dst->get(globalAttitudes[i]).isEmpty())
			oldProperties.push_back(qMakePair(globalAttitudes[i],dst->get(globalAttitudes[i])));
	}
	//other properties that should be restored on the dst item

	src->copyTo(dst);
	dst->setKeyname(name);
	dst->setIsInstance(true);
	dst->setFlags(flags);
	(*dst)[instanceKeyName]=dstName;

	for(QList<QPair<QString,QString> >::Iterator b=oldProperties.begin();
		b!=oldProperties.end();++b)
		dst->set(b->first,b->second);

	updateInstanceChildren(src,dst);
}

void BaseItem::updateInstance()
{
	if(!isInstance())
		return;

	QString tt=this->get(instanceKeyName);
	BaseItem* src=myDocument()->findItem(tt);
	if(src)
		updateInstance(src,this);
}

static void _getAllChildrenIDs(BaseItem* item,
	vector<BaseItem*>& srcVec,bool checkInclude)
{
	int n=item->count();
	if(checkInclude)
	{
		for(int i=0;i<n;++i){
			BaseItem* c=item->child(i);
			if(c->getIncluded())
				srcVec.push_back(c);
		}
	}
	else
	{
		for(int i=0;i<n;++i){
			BaseItem* c=item->child(i);
			srcVec.push_back(c);
		}
	}
	qSort(srcVec.begin(),srcVec.end(),BaseItem::compareID);

}
void BaseItem::updateInstanceChildren( const BaseItem* src,BaseItem* dst )
{
	if(src->count()+ dst->count()==0)
		return;
	if(dst->isPartOrAssembly())
		return;

	vector<BaseItem*> srcVec,dstVec;
	_getAllChildrenIDs(const_cast<BaseItem*>(src),srcVec,false);
	_getAllChildrenIDs(dst,dstVec,true);

	int srcIndex=0,nSrc=srcVec.size(),dstIndex=0,nDst=dstVec.size();
	while(srcIndex<nSrc || srcIndex<nDst)
	{
		if(dstIndex>=nDst){ //添加，更新
			BaseItem* newItem=srcVec[srcIndex]->clone();
			if(newItem->getCategory()==TDY_PRE_CATE_PARAMETERS)
				dst->insertChild(0,newItem);
			else
				dst->appendChild(newItem);
			newItem->setIncluded(true);
			updateInstanceChildren(srcVec[srcIndex],newItem);
			srcIndex++;
			continue;;
		}
		if(srcIndex>=nSrc){ //删除
			BaseItem* p=dstVec[dstIndex]->getParent();
			p->remove(dstVec[dstIndex]);
			dstIndex++;
			continue;
		}
		BaseItem* i1=srcVec[srcIndex];
		BaseItem* i2=dstVec[dstIndex];
		if(i1->getID()>i2->getID()){ //删除
			BaseItem* p=i2->getParent();
			p->remove(i2);
			dstIndex++;
			continue;
		}
		if(i1->getID()==i2->getID()){ //更新
			i1->copyTo(i2);
			i2->setIncluded(true);
			updateInstanceChildren(i1,i2);
			srcIndex++;dstIndex++;
			continue;;
		}
		else{ //增加，更新
			BaseItem* newItem=srcVec[srcIndex]->clone();
			dst->appendChild(newItem);
			newItem->setIncluded(true);
			updateInstanceChildren(srcVec[srcIndex],newItem);
			srcIndex++;
			continue;;
		}
	}
}

void BaseItem::createInstanceChildren( const BaseItem* src,BaseItem* dst )
{
	if(src->count()==0)
		return;

	int n=src->count();
	for(int i=0;i<n;++i)
	{
		const BaseItem* c=src->child(i);
		BaseItem* newItem=c->clone();
		newItem->setIncluded(true);
		dst->appendChild(newItem);

		createInstanceChildren(c,newItem);
	}
}

bool BaseItem::compareID( const BaseItem* i1,const BaseItem* i2 )
{
	return i1->getID()<i2->getID();
}

bool BaseItem::compareKeyname( const BaseItem* i1,const BaseItem* i2 )
{
	return QString::compare(i1->getKeyName(),i2->getKeyName(),Qt::CaseInsensitive);
}
bool BaseItem::compareKeyname(const QString& name)
{
	return QString::compare(getKeyName(),name,Qt::CaseInsensitive);
}
void BaseItem::getChildren( BaseItem* item,QList<BaseItem*>& children,bool recusive/*=false*/ )
{
	int count=item->count();
	if(recusive)
	{
		for(int i=0;i<count;++i){
			children.push_back(item->child(i));
			getChildren(item->child(i),children);
		}
	}
	else{
		for(int i=0;i<count;++i)
			children.push_back(item->child(i));
	}
}

bool BaseItem::isPartOrAssembly()
{
	if(isInstance())
		return false;

	switch(_category)
	{
	case TDY_PRE_CATE_RIGIDPART:
	case TDY_PRE_CATE_ASSEMBLY:
	case TDY_PRE_CATE_FEMPART:
		return true;
	default:
		return false;
	}
}

long BaseItem::_currentMaxID=1;
long BaseItem::currentMaxID()
{
	return _currentMaxID;
}

long BaseItem::nextCurrentMaxID()
{
	return _currentMaxID++;
}

void BaseItem::setFlags( unsigned long f )
{
	std::bitset<16> tmp((unsigned long long)f);
	_flags=tmp;
}

const AppearanceItem* BaseItem::getAppearance()const
{
	return _appearance;
}

AppearanceItem* BaseItem::getAppearance()
{
	return _appearance;
}

void BaseItem::setProperties( Properties* p )
{
	if(_properties==p)
		return;
	if(_properties)
		delete _properties;
	_properties=p;
}

void BaseItem::set( const QString& key,const QString& value )
{
	Properties* p=getOrCreateProperties();
	p->SetString(key,value);
}


void BaseItem::clearChildren()
{
	qDeleteAll(_itemList);
	_itemList.clear();
}


bool BaseItem::appendChild( BaseItem* item )
{
	_itemList.push_back(item);
	item->setParent(this);
	return true;
}

bool BaseItem::insertChild(int pos ,BaseItem* item)
{
	_itemList.insert(pos,item);
	item->setParent(this);
	return true;
}

int BaseItem::indexOf(BaseItem*const child ) const
{
	return _itemList.indexOf(child);
}


bool BaseItem::remove( BaseItem* item,bool deleteIt )
{
	BaseItemList::Iterator f=std::find(_itemList.begin(),_itemList.end(),item);
	if(f==_itemList.end())
		return false;
	_itemList.erase(f);
	if(deleteIt)
		delete item;
	return true;
}

BaseItem* BaseItem::cloneAll() const
{
	BaseItem* item;
	item=(BaseItem*)BaseItemFactory()->Produce(this->getCategory());

	if(!item)
		return NULL;
	copyTo(item);

	int n=count();
	for(int i=0;i<n;++i){
		BaseItem* newChild=child(i)->cloneAll();
		if(newChild)
			item->appendChild(newChild);
	}
	return item;
}

void BaseItem::setAppearance( AppearanceItem* item )
{
	if(_appearance)
		delete _appearance;
	_appearance=item;
}

void BaseItem::setMatrix( const Matrix* matrix )
{
	if(_matrix==matrix)
		return;

	if(_matrix)
	{
		if(matrix)
			*_matrix=*matrix;
		else{
			delete _matrix;
			_matrix=NULL;
		}
	}
	else{
		if(matrix)
			_matrix=new Matrix(*matrix);
	}
}


Assembly* BaseItem::getParentAssembly()
{
	if(!getParent())
		return NULL;

	if(getParent()->getCategory()==TDY_PRE_CATE_ASSEMBLY)
		return (Assembly*)getParent();

	return getParent()->getParentAssembly();
}

void BaseItem::getRelativeMatrix( Matrix& matrix,Assembly* parentAssembly/*=NULL*/ )
{
	QVector<BaseItem*> itemlist;
	BaseItem* tmp=this;
	while(parentAssembly!=tmp && tmp){
		itemlist.push_back(tmp);
		tmp=tmp->getParent();
	}

	for(int i=itemlist.size()-1;i>=0;--i){
		BaseItem* tmpItem=itemlist[i];
		const Matrix* m=tmpItem->getMatrix();
		if(m)
			matrix.preMult(*m);
	}
}


BaseItem* BaseItem::findItem( const QString& absoluteName,BaseItem* baseAssembly )
{
	QStringList vec=absoluteName.split('.',QString::SkipEmptyParts);
	BaseItem* item=baseAssembly?baseAssembly:this;
	for(int i=0;i<vec.size();++i)
	{
		item=item->child(vec[i]);
		if(!item)
			return NULL;
	}
	return item;
}

static BaseItem* _findItemWithoutFolder(const QStringList& vec,BaseItem* item,int index)
{
	if(index==vec.size())
		return item;

	int s=item->count();
	for(int i=0;i<s;++i)
	{
		BaseItem* c=item->child(i);
		if((c->getCategory()==TDY_PRE_CATE_FOLDER)
			|| (c->getCategory()==TDY_PRE_CATE_GROUND)){
				BaseItem* a= _findItemWithoutFolder(vec,c,index);
				if(a)
					return a;
				continue;
		}
		if(!c->compareKeyname(vec[index]))
			return _findItemWithoutFolder(vec,c,index+1);
	}
	return NULL;
}


BaseItem* BaseItem::findItemWithoutFolder( const QString& name,BaseItem* baseAssembly )
{
	QStringList vec=name.split('.',QString::SkipEmptyParts);
	BaseItem* item=baseAssembly?baseAssembly:this;
	return _findItemWithoutFolder(vec,item,0);
}

} // end namespace INSIDES