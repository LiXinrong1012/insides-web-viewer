#ifndef INSMODELFORMATOR_H
#define INSMODELFORMATOR_H

#include <QObject>

class QTextStream;

namespace INSEditor{
	namespace Parse{
		class AssemblyItem;
		class LineItem;
		class KeyValueItem;
		class PropertyItem;
		class CommentItem;

/*!
	@brief  负责ins模型文件的格式化类
	@date   2015.6.15
	@author Jianjun
*/
class INSModelFormator
{
public:
	INSModelFormator();
	~INSModelFormator();

	/// braceAtRight 大括号‘{’是否在右侧，默认为false在下侧
	void setBraceAtRight(bool b){_braceAtRight=b;}

	/// indentation  大括号内的lineItem缩进空格数，默认4
	void setIndentation(int i);

	/// maxLineWord 一行最大字符数
	/// <=0时表示无限制
	void setMaxLineWord(int m);

	///当LineItem 的keyName与上一个的不同时是否空一行
	void setLineItemChangeFeed(bool b ){_lineItemChangeFeed = b;};

	///格式化后以字符串形式返回
	QString toString(AssemblyItem* item);

	///格式化后直接保存到文件
	void saveAsFile(AssemblyItem* item ,const QString& fileName);

private:
	/*
	1. 进入 printToStream 主要处理函数
		调用handleAssemblyChildren

	2. handleAssemblyChildren 逻辑
	如果是 ASSEMBLYITEM 调用handleAssembly处理方法
		调用handleLineItem
		输出 {
		调用handleAssemblyChildren
		输出 }

	如果是 COMMENT 输出
		
	如果是 LINEITEM 调用handleLineItem处理方法

	3. handleLineItem 逻辑
		获取 LINEITEM中的 所有item
		如果是COMMENT
		如果是PROPERTYITEM
		如果是KEYVALUEITEM
	*/

	///打印到字符串
	void printToStream(QTextStream& out,AssemblyItem* item,QString pre);

	///用来处理assembly的子项
	void handleAssemblyChildren(QTextStream& out,AssemblyItem* item,QString pre);

	///处理assembly
	void handleAssembly(QTextStream& stream,AssemblyItem* item,QString pre);

	///处理LineItem
	void handleLineItem(LineItem* lineItem, QTextStream& stream,QString pre);

	///处理注释
	void handleComment(CommentItem* comItem,QTextStream& stream);

	///处理换行和行首缩进
	void handleLineFeed(QTextStream& stream,const QString& pre,QString& str,const QString& tmpStr);

	///处理属性项
	void handlePropertyItem(PropertyItem* propertyItem,QTextStream& stream);

	///处理键值对项
	void handleKeyValueItem(KeyValueItem* keyValueItem,QTextStream& stream);

private:
	///记录大括号是否在右边
	bool _braceAtRight;

	///当LineItem 的KeyName与上一个不同时是否空一行
	bool _lineItemChangeFeed;
	
	///每行缩进字符数
	int	_indentation;

	///每行最大字符数
	int _maxLineWord;

	//代表一个缩进单位
	QString _spaceStr;

	///记录当前为第几层
	int _currentCeng;

	//属于ASSEMBLYITEM类型的注释
	QList<CommentItem*> _commentList;
};

} // end namespace Parse
} // end namespace INSEditor

#endif // INSMODELFORMATOR_H
