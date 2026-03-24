#include "modelparser.h"

#include <QtCore>

#include "instemplate.h"
#include "tdytypeinfomanager.h"

namespace INSEditor
{
namespace Parse
{

class ModelParser::StringReader
{
public:
	StringReader(QString* text)
		:_rowIndex(0)
		,_columnIndex(0)
		,_pos(text->constBegin())
		,_end(text->constEnd())
		,_last('a')
	{
	}

	QChar next(){
		if(atEnd())
			return '\n';	
		if(_last=='\n'){
			_rowIndex++;
			_columnIndex=0;
		}
		else
			_columnIndex++;
		_last=*_pos;
		_pos++;
		return _last;
	}

	QString getUntilLineEnd()
	{
		QString str;
		while(!atEnd())
		{
			QChar c=next();
			if(c!='\n')
				str.push_back(c);
			else
				break;
		}
		return str;
	}

	bool atEnd(){return _pos==_end;}
	int currentLineIndex()const{return _rowIndex;}
	int currentColumnIndex()const{return _columnIndex;}

private:
	int			_rowIndex;
	int			_columnIndex;
	QString::const_iterator _pos;
	QString::const_iterator _end;
	QChar		_last;
};


ModelParser::ModelParser()
	:_expandInclude(false)
	,_templateManager(ItemTemplateManager())
	,_assembleItem(NULL)
{
}

ModelParser::~ModelParser()
{
	disattachAll();
}

static void _parseLineComment(ModelParser::StringReader& reader,QString& comment,QChar& ch,
	LineItem* currentItem,AssemblyItem* currentParent)
{
	while(!reader.atEnd()){
		ch=reader.next();
		if(ch=='\n')
			break;
		comment.push_back(ch);
	}

	///增加到注释行号的记录
	CommentItem tmp(comment);
	tmp.rowIndex = reader.currentLineIndex();
	if(currentItem)
		currentItem->addItem(tmp);
	else
		currentParent->addItem(tmp);
}
static void _parseBlockComment(ModelParser::StringReader& reader,QString& comment,QChar& ch,
	LineItem* currentItem,AssemblyItem* currentParent)
{
	ch='a';
	QChar ch2;
	while(!reader.atEnd()){
		ch2=ch;
		ch=reader.next();
		comment.push_back(ch);
		if( (ch2=='*')&&(ch=='/') )
			break;
	}
	if(currentItem)
		currentItem->addItem(CommentItem(comment));
	else
		currentParent->addComment(CommentItem(comment));
}

bool ModelParser::parse( const QString& text,const QString& fileName,AssemblyItem* root)
{
	QString _buffer;
	QString _contents;

	_contents=text;
	_buffer.resize(1000);

	StringReader reader(&_contents);

	bool isInQuote=false; //是否处于引号内
	
	AssemblyItem*	currentParent=root;
	LineItem*	currentItem=NULL;
	KeyValueItem* currentSubItem=NULL; //当前的键值条目

	int	bufferIndex=0;

	QChar ch=reader.next();
	bool runlastCycle=false;
	while(true)
	{
		if(reader.atEnd()){
			if(runlastCycle)
				break;
			runlastCycle=true;
		}
		QString str(ch);
		if(((ch==',')||(ch=='\n')) && !isInQuote)//原来没有 && !isInQuote
		{
			if(isInQuote)
				_buffer[bufferIndex++]=',';
			else if(currentSubItem&& bufferIndex!=0){ //键－值对
				currentSubItem->valueList.push_back(_buffer.left(bufferIndex));
				bufferIndex=0;
			}
			else if(currentItem && bufferIndex!=0){	//属性
				currentItem->addItem(PropertyItem(_buffer.left(bufferIndex)));
				bufferIndex=0;
			}
			else{
				// error
			}
		}
		else if(ch.isSpace())
		{
			;//pause
		}
		else if(ch=='/')
		{
			if(isInQuote)
				_buffer[bufferIndex++]=ch;
			else{
				QChar ch2=reader.next();
				if(ch2=='/'){ //行注释
					QString comment("//");
					_parseLineComment(reader,comment,ch,currentItem,currentParent);
					continue;
				}
				else if(ch2=='*'){ //块注释
					QString comment("/*");
					_parseBlockComment(reader,comment,ch,currentItem,currentParent);
					ch=reader.next();
					continue;
				}
				if(bufferIndex!=0){
					QString tmpKey=_buffer.left(bufferIndex);
					if(_expandInclude && !tmpKey.compare("INCLUDE",Qt::CaseInsensitive)){
						// 展开 Include
						QString includeFileName=reader.getUntilLineEnd();
						includeFileName=includeFileName.trimmed();
						// 得到文件名
						if(includeFileName[0]=='\"'){
							int second=includeFileName.indexOf('\"',1);
							if(second>0)
								includeFileName=includeFileName.mid(1,second-1);
							else{
								emitError(reader,fileName,"Invalid filename");
								includeFileName=QString();
							}
						}
						else{
							includeFileName.replace('!',' ');
							QStringList tmp=includeFileName.split(' ');
							includeFileName=tmp[0];
						}
						QString fullFilename=getFullFileName(includeFileName);
						if(fullFilename.isEmpty()){
							// error
							emitError(reader,fileName,"Filename is empty.");
						}
						else
							parse(readFromFile(fullFilename),fullFilename,currentParent);
						bufferIndex=0;
					}
					else{ //不展开
						LineItem* newItem=new LineItem(tmpKey);
						newItem->rowIndex=reader.currentLineIndex();
						newItem->columnIndex=reader.currentColumnIndex()-bufferIndex;
						currentParent->addChild(newItem);
						currentItem=newItem;
						currentSubItem=NULL;
						bufferIndex=0;
					}
				}
				else{
					// error
					emitError(reader,fileName,"Unexpected character \"/\"");
					
					return false;
				}
				ch=ch2;
				continue;
			}

		}
		else if(ch=='"')
		{
			if(currentSubItem)
			{
				if(!isInQuote){
					isInQuote=true;
					_buffer[bufferIndex++]=ch;
				}
				else{//键－值对
					_buffer[bufferIndex++]=ch;
					currentSubItem->valueList.push_back(_buffer.left(bufferIndex));
					bufferIndex=0;
					isInQuote=false;
				}
			}
			else{
				// error
				emitError(reader,fileName,"Unexpected character \"\\\"");
			}
		}
		else if(ch=='='){
			if(isInQuote)
				_buffer[bufferIndex++]=ch;
			else if(currentItem && bufferIndex!=0){
				KeyValueItem subItem(_buffer.left(bufferIndex));
				subItem.rowIndex=reader.currentLineIndex();
				subItem.columnIndex=reader.currentColumnIndex()-bufferIndex;
				bufferIndex=0;
				
				currentSubItem=(KeyValueItem*)currentItem->addItem(subItem);
			}
			else{
				// error
				emitError(reader,fileName,"Unmatched '=', did you mistype it?");
			}
		}
		else if(ch=='{')
		{
			if(currentSubItem && bufferIndex!=0){ //键－值对
				currentSubItem->valueList.push_back(_buffer.left(bufferIndex));
				bufferIndex=0;
			}
			else if(currentItem && bufferIndex!=0){	//属性
				currentItem->addItem(PropertyItem(_buffer.left(bufferIndex)));
				bufferIndex=0;
			}

			if(currentItem){
				AssemblyItem* newParent=new AssemblyItem(*currentItem);
				currentParent->removeChild(currentItem);
				currentParent->addChild(newParent);
				currentParent=newParent;
				currentItem=NULL;
			}
			else{
				// error
				emitError(reader,fileName,"Unmatched '{'");
			}
		}
		else if(ch=='}')
		{
			if(currentParent && currentParent->getParent()){
				currentParent=currentParent->getParent();
				currentItem=NULL;
			}
			else{
				// error
				emitError(reader,fileName,"Unmatched '}'");
			}
		}
		else if(ch=='!')
		{
			QString comment("!");
			_parseLineComment(reader,comment,ch,currentItem,currentParent);
			continue; // 让　\n直接进入处理
		}
		else
			_buffer[bufferIndex++]=ch;
		
		ch=reader.next();
	}

	if(currentSubItem && currentSubItem->valueList.size())
	{
		if(currentSubItem->valueList.last().compare("END",Qt::CaseInsensitive)==0)
			currentSubItem->valueList.removeLast();
	}
	return true;
}

QString ModelParser::readFromFile( const QString& fileName )
{
	QFile file(fileName);
	if (!file.open(QFile::ReadOnly))
		return QString();

	QTextStream in(&file);
	return in.readAll();
}

AssemblyItem* ModelParser::parseFile(const QString& fileName,bool expandInclude)
{
	_expandInclude=expandInclude;
	AssemblyItem* mainItem=new AssemblyItem();
	parse(readFromFile(fileName),fileName,mainItem);
	return mainItem;
}

AssemblyItem* ModelParser::parseFile( const QString& text,const QString& fileName)
{
	_expandInclude=false;
	AssemblyItem* mainItem=new AssemblyItem();
	bool flag = parse(text,fileName,mainItem);
	if(!flag)
	{
		delete mainItem;
		mainItem = NULL;
	}
	return mainItem;
}

AssemblyItem* ModelParser::parseFile( const QString& text,const QString& fileName,bool expandInclude)
{
	_expandInclude=expandInclude;
	AssemblyItem* mainItem=new AssemblyItem();
	bool flag = parse(text,fileName,mainItem);
	if(!flag)
	{
		delete mainItem;
		mainItem = NULL;
	}
	return mainItem;
}

AssemblyItem* ModelParser::parse( const QString& mainFileName)
{
	QFileInfo info(mainFileName);
	if(!info.exists())
		return NULL;

	_expandInclude=true;
	QString root=info.absoluteDir().absolutePath();
	_includeFolders.clear();
	_includeFolders<<root;

	AssemblyItem* mainItem=new AssemblyItem();
	parse(readFromFile(mainFileName),mainFileName,mainItem);
	return mainItem;
}

AssemblyItem* ModelParser::parse( const QString& mainFileName, const QStringList& includeFolders )
{
	_includeFolders=includeFolders;
	_expandInclude=true;

	AssemblyItem* mainItem=new AssemblyItem();
	parse(readFromFile(mainFileName),mainFileName,mainItem);
	return mainItem;
}

AssemblyItem* ModelParser::parseSolution( const QString& solutionFileName )
{
	return NULL;
}

bool ModelParser::compile( const QString& mainFileName, const QStringList& includeFolders )
{
	AssemblyItem assemblyItem;
	parse(mainFileName,includeFolders);
	return _errorItemList.size()==0;
}

void ModelParser::attachErrorObserver( CompileInfoObserver* observer )
{
	if(!observer)
		return;
	if(_observers.contains(observer))
		return;
	
	_observers.push_back(observer);
}

void ModelParser::disattachErrorObserver( CompileInfoObserver* observer )
{
	if(observer){
		_observers.removeOne(observer);
		delete observer;
	}
}

void ModelParser::disattachAll()
{
	qDeleteAll(_observers);
	_observers.clear();
}

void ModelParser::emitError( const StringReader& reader,const QString& fileName, const QString& errorInfo )
{
	CompileInfoItem item(fileName,errorInfo);
	item.rowIndex=reader.currentLineIndex();
	item.columnIndex=reader.currentColumnIndex();

	emitError(item);
}
void ModelParser::emitError( const LineItem* lineitem,const QString& fileName,const QString& errorInfo )
{
	CompileInfoItem item(fileName,errorInfo);
	item.rowIndex=lineitem->rowIndex;
	item.columnIndex=lineitem->columnIndex;

	emitError(item);
}
void ModelParser::emitError( const CompileInfoItem& item )
{
	_errorItemList.push_back(item);

	int n=_observers.size();
	for(int i=0;i<n;++i)
		_observers[i]->error(item);
}

QString ModelParser::getFullFileName( const QString& fileName ) const
{
	QString name=fileName.trimmed();
	if(name.isEmpty())
		return QString();

	foreach(QString strDir,_includeFolders)
	{
		QFile file(strDir +"/" + name);
		if(file.exists())
			return strDir + "/" + name;
	}
	return QString();
}

void ModelParser::addDefaultObserver()
{
	ConsoleInfoObserver* observer=new ConsoleInfoObserver();
	attachErrorObserver(observer);
}

TDYTypeInfoPtr ModelParser::getTypeInfo( const QString& keyName )
{
	QMap<QString,TDYTypeInfoPtr>::iterator f=_infos.find(keyName);
	if(f==_infos.end())
		return TDYTypeInfoPtr();
	return f.value();
}

void ModelParser::compileAssemblyItem( LineItem* item ,QMap<QString,TDYTypeInfoPtr>& infos)
{
	_infos = infos;
	compileAssemblyItem(item);
}

void ModelParser::compileAssemblyItem( LineItem* item,QString fullFileName ,QMap<QString,TDYTypeInfoPtr>& infos)
{
	_fullFileName = fullFileName;
	_infos = infos;
	compileAssemblyItem(item);
}

void ModelParser::compileAssemblyItem( LineItem* item )
{
	if(_assembleItem == NULL)
		_assembleItem = static_cast<AssemblyItem*>(item);

	TDYTypeInfoPtr typeInfo=getTypeInfo(item->keyname.toUpper());
	if(!typeInfo.isNull())
		compileAssemblyItem(item,typeInfo);
	else
	{
		// warning: can't find type info
		if(item->properties.size()>0){
			QString p1=item->properties[0]->name;
			bool flag;
			int id=p1.toInt(&flag);
			if(flag)
			{
				item->mainID=p1;
				item->mainLabel=item->keyname+"_"+p1;
				item->removeProperty(item->properties[0]);
				//如果没有明确给出LABEL就用默认如parameter_1
				if(item->properties.size()>0){
					item->mainLabel=item->properties[0]->name;
					item->removeProperty(item->properties[0]);
				}
			}
			else
			{
				item->mainLabel=p1;
				item->removeProperty(item->properties[0]);
			}
		}
	}

	if(item->type==ASSEMBLYITEM)
	{
		AssemblyItem* assemItem=(AssemblyItem*)item;
		foreach(LineItem* c,assemItem->getItemList())
			compileAssemblyItem(c);
	}
}

void ModelParser::compileAssemblyItem( LineItem* item,TDYTypeInfoPtr typeInfo )
{
	if(item->properties.size()==0)
		item->mainLabel=item->mainID=item->keyname;
	else
	{
		//检测不可省略的 和不可多选的（相斥）
		QList<TDYTypeKeyValuePtr> noOptimalInfoList,noMultipleInfoList,mustMultipleInfoList;
		foreach(TDYTypeKeyValuePtr ptr,typeInfo->keyvalueList)
		{
			if(!ptr->isOptimal)
				noOptimalInfoList.push_back(ptr);
			if(!ptr->isMultipleKeyvalue)
				noMultipleInfoList.push_back(ptr);
			if(ptr->isMultipleKeyvalue && ptr->selectCount != 1)
				mustMultipleInfoList.push_back(ptr);
		}

		//检测键-值对是否含有空值
		checkKeyValues(item);

		//检测关键字是否定义
//		checkKeydefine(item,typeInfo);

		//检测值的个数
		checkValueCount(item,typeInfo);

		//不可省略的
		notOmitted(item,noOptimalInfoList);

		//不可多选的
		notAllowMultiple(item,noMultipleInfoList);

		//必须选多少个
		mustSelectNumber(item,mustMultipleInfoList);

		//检测重复定义
		redefinition(item);

		//检测非法引用
		unlawfulReference(item,typeInfo);

		//检测有些键是否在特定属性下
		isUnderProperty(item,typeInfo);
		
		//检测属性值
		checkPreperty(item,typeInfo);
	}
}

void ModelParser::redefinition(LineItem* item)
{
	if(item->keyValues.count()<=1)
		return;
	for (int i=0;i<item->keyValues.count();i++)
	{
		for (int j=i+1;j<item->keyValues.count();j++)
		{
			if(item->keyValues[i]->keyname.compare(item->keyValues[j]->keyname,Qt::CaseInsensitive))
				continue;

			QString errStr;
			errStr = QString("Repeat define key \"%1\".").arg(item->keyValues[i]->keyname);
			emitError(item,_fullFileName,errStr);
		}
	}
}

void ModelParser::unlawfulReference( LineItem* item , TDYTypeInfoPtr typeInfo)
{
	foreach(Parse::KeyValueItem* c,item->keyValues)
	{
		QList<QString> newValueList;
		foreach(TDYTypeKeyValuePtr ptr,typeInfo->keyvalueList)
		{
			if(ptr->keyName.compare(c->keyname,Qt::CaseInsensitive))
				continue;

			QStringList vaildResTypes = ptr->validReferenceTypes;
			if(vaildResTypes.isEmpty())
				continue;

			bool vaild = false;
			if(!c->valueList.isEmpty())
			{
				if(!item->keyname.compare("INSTANCE",Qt::CaseInsensitive))
				{
					foreach(LineItem* tmp,item->getParent()->getItemList())//查的是普通的PART
					{
						if(tmp->type != ASSEMBLYITEM)
							continue;

						AssemblyItem* assTmp = static_cast<AssemblyItem*>(tmp);

						if(!assTmp->mainLabel.compare(c->valueList[0]) && vaildResTypes.contains(assTmp->keyname,Qt::CaseInsensitive))
						{
							vaild = true;
							break;
						}
					}
				}
				else if(!item->keyname.compare("MARKER",Qt::CaseInsensitive))
				{
					foreach(LineItem* tmp,item->getParent()->getItemList())//查的是MARKER的PART
					{
						if(tmp->keyname.compare("INSTANCE",Qt::CaseInsensitive))
							continue;

						if(!tmp->mainLabel.compare(c->valueList[0]) && vaildResTypes.contains(tmp->keyname,Qt::CaseInsensitive))
						{
							vaild = true;
							break;
						}
					}
				}
			}

			if(!vaild)
			{
				QString errStr;
				errStr = QString("The reference of \"%1\" is lawless.").arg(c->keyname);
			//	emitError(item,_fullFileName,errStr);
			}
		}

		foreach(const QString& v,c->valueList)
		{
			if(!typeInfo->hasProperty(v))
				newValueList<<v;
			else
				item->addItem(PropertyItem(v));
		}

		c->valueList=newValueList;
	}
}

void ModelParser::notAllowMultiple(LineItem* item,QList<TDYTypeKeyValuePtr> noMultipleInfoList)
{
	foreach(TDYTypeKeyValuePtr ptr,noMultipleInfoList)
	{
		int num =0;
		QStringList noMultipleKeyNames;
		foreach(TDYTypeKeyValuePtr tmp,ptr->subKeyValueGroup)
			noMultipleKeyNames.push_back(tmp->keyName);

		foreach(QString name,noMultipleKeyNames)
		{
			foreach(KeyValueItem* tmp,item->keyValues)
			{
				if(!tmp->keyname.compare(name))
					num ++;
			}
		}
		if(num > 1)
		{
			QString errStr;
			errStr = QString("The group \"%1\" can not multiple.").arg(ptr->keyName);
			emitError(item,_fullFileName,errStr);
		}
		num =0;
	}
}

void ModelParser::mustSelectNumber(LineItem* item,QList<TDYTypeKeyValuePtr> mustMultipleInfoList)
{
	foreach(TDYTypeKeyValuePtr ptr,mustMultipleInfoList)
	{
		if(ptr->subKeyValueGroup.count()==0)
			continue;

		int num =0;
		QStringList mustMultipleKeyNames;
		foreach(TDYTypeKeyValuePtr tmp,ptr->subKeyValueGroup)
			mustMultipleKeyNames.push_back(tmp->keyName);

		foreach(QString name,mustMultipleKeyNames)
		{
			foreach(KeyValueItem* tmp,item->keyValues)
			{
				if(!tmp->keyname.compare(name,Qt::CaseInsensitive))
					num ++;
			}
		}
		if(num != ptr->selectCount)
		{
			QString errStr;
			errStr = QString("The group \"%1\" must select %2 item.").arg(ptr->keyName).arg(ptr->selectCount);
			emitError(item,_fullFileName,errStr);
		}
		num =0;
	}
}

void ModelParser::notOmitted( LineItem* item,QList<TDYTypeKeyValuePtr> noOptimalInfoList )
{
	foreach(TDYTypeKeyValuePtr ptr,noOptimalInfoList)
	{
		QStringList noOptimalKeyNames;
		foreach(TDYTypeKeyValuePtr tmp,ptr->subKeyValueGroup)
			noOptimalKeyNames.push_back(tmp->keyName);

		bool isContains = false;
		foreach(KeyValueItem* tmp,item->keyValues)
		{
			if(noOptimalKeyNames.contains(tmp->keyname,Qt::CaseInsensitive))	
				isContains = true;
		}
		if(!isContains)
		{
			QString errStr;
			errStr = QString("The group \"%1\" is not optimal.").arg(ptr->keyName);
			emitError(item,_fullFileName,errStr);
		}
	}
}

void ModelParser::checkValueCount( LineItem* item , TDYTypeInfoPtr typeInfo )
{
	foreach(KeyValueItem* tmp,item->keyValues)
	{
		bool isEqual = false;
		foreach(TDYTypeKeyValuePtr ptr,typeInfo->keyvalueList)
		{
			if(!ptr->keyName.compare(tmp->keyname,Qt::CaseInsensitive))
			{
				if(ptr->valueCount != 0 && tmp->valueList.count() != ptr->valueCount)
				{
					QString errStr;
					errStr = QString("The value count of \"%1\" must is %2.").arg(ptr->keyName).arg(ptr->valueCount);
					emitError(item,_fullFileName,errStr);
				}
			}
		}
	}
}

void ModelParser::checkKeydefine( LineItem* item , TDYTypeInfoPtr typeInfo )
{
	if(item->keyname.compare("parameter",Qt::CaseInsensitive) && item->keyname.compare("request",Qt::CaseInsensitive))
	{
		QStringList keyValueList;
		foreach(TDYTypeKeyValuePtr ptr,typeInfo->keyvalueList)
			keyValueList<<ptr->keyName;

		foreach(KeyValueItem* tmp,item->keyValues)
		{
			if(keyValueList.contains(tmp->keyname,Qt::CaseInsensitive))
				continue;
			
			QString errStr;
			errStr = QString("The \"%1\" does not contain the keywords \"%2\".").arg(item->keyname).arg(tmp->keyname);
			emitError(item,_fullFileName,errStr);
		}
	}
}

void ModelParser::isUnderProperty( LineItem* item,TDYTypeInfoPtr typeInfo )
{
	foreach(KeyValueItem* tmp ,item->keyValues)
	{
		foreach(TDYTypeKeyValuePtr ptr,typeInfo->keyvalueList)
		{
			if(ptr->keyName.compare(tmp->keyname,Qt::CaseInsensitive))
				continue;
			
			if(ptr->validUnderProperties.isEmpty())
				continue;
			
			bool isContains = false;
			foreach(PropertyItem* pTmp,item->properties)
				if(ptr->validUnderProperties.contains(pTmp->name,Qt::CaseInsensitive))
					isContains = true;
			
			if(isContains)
				continue;
			
			QString errStr;
			errStr = QString("The key name \"%1\" need to under \"%2\" attribute.").arg(tmp->keyname).arg(ptr->validUnderProperties.join(","));
			emitError(item,_fullFileName,errStr);
		}
	}
}

void ModelParser::checkKeyValues( LineItem* item )
{
	foreach(KeyValueItem* tmp,item->keyValues)
	{
		if(!tmp->valueList.isEmpty())
			continue;
		
		QString errStr;
		errStr = QString("The value of %1 is empty !").arg(tmp->keyname);
		emitError(item,_fullFileName,errStr);
	}
}

void ModelParser::checkPreperty( LineItem* item,TDYTypeInfoPtr typeInfo )
{
	QList<PropertyItem*> needRemoveProperties;
	foreach(PropertyItem* p,item->properties)
	{
		bool hasProperty=typeInfo->hasProperty(p->name.toUpper());
		if(!hasProperty)
			needRemoveProperties<<p;
	}

	if(needRemoveProperties.size()>0)
	{
		QString p1=needRemoveProperties[0]->name;
		bool flag;
		int id=p1.toInt(&flag);
		if(flag)
		{
			item->mainID=p1;
			item->mainLabel=item->keyname+"_"+p1;
			item->removeProperty(needRemoveProperties[0]);
			needRemoveProperties.removeFirst();

			if(needRemoveProperties.size()>0)
			{
				item->mainLabel=needRemoveProperties[0]->name;
				item->removeProperty(needRemoveProperties[0]);
				needRemoveProperties.removeFirst();
			}
		}
		else
		{
			item->mainLabel=p1;
			item->removeProperty(needRemoveProperties[0]);
		}
	}

	if(!typeInfo->supportUnknownProperty)
	{
		while(needRemoveProperties.size()>0)
		{
			item->removeProperty(needRemoveProperties.last());
			needRemoveProperties.removeLast();
		}
	}
}


} //end namespace Parse

} //end namespace INSEditor