#include "insmodelformator.h"
#include "mainitem.h"
#include "modelparser.h"
#include "tdytypeinfomanager.h"

#include <QFile>
#include <QTextStream>

namespace INSEditor
{
namespace Parse
{

INSModelFormator::INSModelFormator()
	:_braceAtRight(true)
	,_indentation(4)
	,_maxLineWord(0)
	,_currentCeng(0)
	,_lineItemChangeFeed(false)
{
	for(int i=0;i<_indentation;i++)
		_spaceStr+=" ";
}

INSModelFormator::~INSModelFormator()
{
}

QString INSModelFormator::toString( AssemblyItem* item )
{
	QString str;
	QTextStream stream(&str);
	printToStream(stream,item,"");
	return str;
}

void INSModelFormator::saveAsFile( INSEditor::Parse::AssemblyItem* item ,const QString& fileName )
{
	QFile file(fileName);
	if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
		return;

	QTextStream stream(&file);
	printToStream(stream,item,"");

	file.close();
}

void INSModelFormator::printToStream( QTextStream& stream,AssemblyItem* item,QString pre )
{
	handleAssemblyChildren(stream,item,pre);
}

void INSModelFormator::handleLineItem( LineItem* lineItem, QTextStream& stream,QString pre )
{
	QString str;
	QString tmpStr;
	int subLastType=0;

	stream<<pre;
	str+=pre;

	stream<<lineItem->keyname;
	str+= lineItem->keyname;

	stream<<" / ";
	str+= " / ";

	QList<BaseItem*> allItems = lineItem->allItems;

	if(!lineItem->mainID.isEmpty())
	{
		stream<<lineItem->mainID;
		str+= lineItem->mainID;
	}

	if(!lineItem->mainLabel.isEmpty())
	{
		if(lineItem->type != ASSEMBLYITEM && lineItem->keyname.compare("include",Qt::CaseInsensitive))
		{
			stream<<", ";
			str+=", ";
		}
		
		stream<<lineItem->mainLabel;
		str+=lineItem->mainLabel;

		if(!lineItem->keyname.compare("include",Qt::CaseInsensitive))
		{
			stream<<"\n";
			stream<<_spaceStr;
			stream<<pre;
		}
	}

	for(int i=0;i<allItems.count();i++,allItems)
	{
		BaseItem* item=allItems[i];

		if(item->type == COMMENT)
		{
			if(subLastType == 0)
				subLastType = item->type;
	
			CommentItem* commentItem = (CommentItem*)item;
			tmpStr = str + commentItem->comment;
			if(tmpStr.size()>_maxLineWord && _maxLineWord>0)
				handleLineFeed(stream,pre,str,tmpStr);
			else if(_maxLineWord >0 )
				str += commentItem->comment;

			if(i != 0)
				if(commentItem->rowIndex > allItems[i-1]->rowIndex)
				{
					stream<<"\n";
					stream<<pre;
					stream<<_spaceStr;
					stream<<_spaceStr;
					str.clear();
					str += pre + _spaceStr + _spaceStr;
				}
				else if(lineItem->type != ASSEMBLYITEM)
					stream<<" ";

			if(lineItem->type == ASSEMBLYITEM)
			{
				commentItem->comment.remove(commentItem->comment.count()-1,1);
				_commentList<<commentItem;
			}
			else
				handleComment(commentItem,stream);
			subLastType = COMMENT;
		}
		else if(item->type == PROPERTYITEM)
		{
			if(i!=allItems.count()-1)
				stream<<", ";

			PropertyItem* propertyItem = (PropertyItem*)item;

			tmpStr = propertyItem->name + str;
			if(tmpStr.size()>_maxLineWord && _maxLineWord>0)
				handleLineFeed(stream,pre,str,tmpStr);
			else if(_maxLineWord >0 )
				str += propertyItem->name+", ";

			handlePropertyItem(propertyItem,stream);
			subLastType = PROPERTYITEM;
		}
		else if(item->type == KEYVALUEITEM)
		{
			KeyValueItem* keyValueItem = (KeyValueItem*)item;

			if(i == 0 )
			{
				if(keyValueItem->rowIndex > lineItem->rowIndex)
				{
					str.clear();
					stream<<"\n";
					stream<<pre;
					stream<<_spaceStr;
					stream<<", ";
					str+= pre + _spaceStr + ", ";
				}
				else
				{
					stream<<", ";
					str+= ", ";
				}
			}
			else
			{
				if(keyValueItem->rowIndex>allItems[i-1]->rowIndex)
				{
					str.clear();
					stream<<"\n";
					stream<<pre;
					stream<<_spaceStr;
					stream<<", ";
					str+= pre + _spaceStr + ", ";
				}
				else
				{
					stream<<", ";
					str+=", ";
				}
			}

			tmpStr = keyValueItem->keyname;
			tmpStr+=" = ";
			tmpStr += keyValueItem->valueList.join(", ");
			tmpStr+=", ";
			if((tmpStr.size()+str.size())>_maxLineWord && _maxLineWord>0)
				handleLineFeed(stream,pre,str,tmpStr);
			else
				str+=tmpStr;

			handleKeyValueItem(keyValueItem,stream);
			subLastType = KEYVALUEITEM;
		}
	}
	QList<BaseItem*> items = lineItem->parent->getAllItemList();
	for (int i=0;i<items.count();i++)
	{
		//这里最后多一个回车
		if(items[i] == lineItem && i != items.count()-1)
		{
			if(!allItems.isEmpty() && lineItem->type != ASSEMBLYITEM)
				stream<<"\n";
			break;
		}
	}
}

void INSModelFormator::handleLineFeed( QTextStream& stream,const QString& pre,QString& str,const QString& tmpStr )
{
	stream<< "\n";
	stream<< pre;
	stream<< _spaceStr;
	str.clear();
	str=tmpStr;
	str+= pre;
	str+= _spaceStr;
}

void INSModelFormator::handleComment( CommentItem* comItem,QTextStream& stream )
{
	stream<<comItem->comment;
}

void INSModelFormator::handlePropertyItem( PropertyItem* propertyItem,QTextStream& stream )
{
	stream<<propertyItem->name;
}

void INSModelFormator::handleKeyValueItem( KeyValueItem* keyValueItem,QTextStream& stream )
{
	stream<<keyValueItem->keyname;
	stream<<" = ";
	stream<<keyValueItem->valueList.join(", ");
}

void INSModelFormator::handleAssemblyChildren( QTextStream& stream,AssemblyItem* item,QString pre )
{
	QString lastKeyName;
	static bool flag=true;//第一次调用
	int lastType =0;
	int num = item->getAllItemList().count();
	QList<BaseItem*> itemList = item->getAllItemList();
	for (int i=0;i<num;i++)
	{
		if (itemList[i]->type == ASSEMBLYITEM)
		{
			if(!lastType)
				lastType = ASSEMBLYITEM;
			else if(lastType != ASSEMBLYITEM)
			{
				lastType = ASSEMBLYITEM;
				stream<<"\n";
			}

			AssemblyItem* assItem = (AssemblyItem*)itemList[i];
			if(flag)
			{
				handleAssembly(stream,assItem,pre);
				flag = false;
			}
			else
				handleAssembly(stream,assItem,pre+_spaceStr);
		}
		else if(itemList[i]->type == COMMENT)
		{
			CommentItem* comment = (CommentItem*)itemList[i];
			stream<<pre;
			if(i != 0 )
				if(itemList[i]->rowIndex > itemList[i-1]->rowIndex)
					stream<<"\n";

			handleComment(comment,stream);

			stream<<"\n";
			lastType = COMMENT;
		}
		else if (itemList[i]->type == LINEITEM)
		{
			lastType = LINEITEM;
			LineItem* lineItem = (LineItem*)itemList[i];

			if(lastKeyName.isEmpty())
				lastKeyName = lineItem->keyname;
			else if(lastKeyName != lineItem->keyname)
			{
				lastKeyName = lineItem->keyname;
				stream<<"\n";
			}
			handleLineItem(lineItem,stream,pre);
		}
	}
}

void INSModelFormator::handleAssembly( QTextStream& stream,AssemblyItem* item,QString pre )
{
	pre.clear();
	for(int i=0;i<_currentCeng;i++)
		pre+=_spaceStr;

	_commentList.clear();
	handleLineItem((LineItem*)item,stream,pre);
	if(!_braceAtRight)
	{
		stream<<"\n";
		stream<<pre;
	}
	stream<<"{\n";
	_currentCeng++;
	
	foreach(CommentItem* tmp,_commentList)
	{
		stream<<pre;
		stream<<_spaceStr;
		stream<<tmp->comment;
	}

	stream<<"\n";
	handleAssemblyChildren(stream,item,pre+_spaceStr);
	stream<<"\n";
	stream<<pre;
	stream<<"}\n";
	_currentCeng--;
	stream<<"\n";
}

void INSModelFormator::setMaxLineWord( int m )
{
	_maxLineWord = m;
}

void INSModelFormator::setIndentation( int i )
{
	_indentation=i;
	_spaceStr.clear();
	for(int i=0;i<_indentation;i++)
		_spaceStr+=" ";
}



} //end namespace parse
} //end namespace inseditor