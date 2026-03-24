#ifndef MODELPARSER_H
#define MODELPARSER_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QDebug>

#include "mainitem.h"
#include "tdytypeinfomanager.h"

namespace INSEditor{

namespace Parse
{
	
class ItemTemplateManagerSinleton;
/*!
	@brief 编译错误信息观察类基类。
	@author	Jerry He
	@date	2014.10.29
*/
class CompileInfoObserver
{
public:
	virtual void error(const CompileInfoItem& ErrorItem)=0;
	virtual ~CompileInfoObserver(){}
};

class ConsoleInfoObserver : public CompileInfoObserver
{
	virtual void error(const CompileInfoItem& ErrorItem){
		qDebug()<<ErrorItem.fileName<<"\t"<<ErrorItem.errorInfo<<endl;
	}
};


/*!
*	The ModelParser is used to parse a .ins format text.
*	The result is stored in a tree structure.
*	@author	Jerry He
*	@date	2014.8.24
*/
class ModelParser
{
public:
	ModelParser();
	~ModelParser();

	/// 解析一个文件内容，生成此文件内容的结构
	AssemblyItem* parseFile(const QString& text,const QString& fileName);

	///解析一个文件内容，生成此文件内容的结构，并可控制是否展开
	AssemblyItem* parseFile( const QString& text,const QString& fileName,bool expandInclude);

	/// 解析一个文件
	AssemblyItem* parseFile(const QString& fileName,bool expandInclude);

	/// 解析一个模型，返回顶层指针
	AssemblyItem* parse(const QString& mainFileName, const QStringList& includeFolders);

	/// 解析一个模型
	AssemblyItem* parse(const QString& fileName);

	/// 解析一个模型
	AssemblyItem* parseSolution(const QString& solutionFileName);

	/// 编译一个模型文件，返回是否编译成功。
	bool compile(const QString& mainFileName, const QStringList& includeFolders);

	///接收传过来的文件名并作存储
	void compileAssemblyItem(LineItem* item,QString fullFileName,QMap<QString,TDYTypeInfoPtr>& infos);

	/// 编译Parse完的结果，重新整理
	void compileAssemblyItem(LineItem* item,QMap<QString,TDYTypeInfoPtr>& infos);
	void compileAssemblyItem(LineItem* item);

	///观察者模式,错误提示连接
	void attachErrorObserver(CompileInfoObserver* observer);

	///观察者模式,断开连接
	void disattachErrorObserver(CompileInfoObserver* observer);

	///断开所有连接
	void disattachAll();

	///添加默认观察者
	void addDefaultObserver();

	///从文件中读取
	static QString readFromFile(const QString& fileName);

	///错误信息
	static void error(const LineItem* item,const QString& fileName,const QString& errorInfo);

public:
	class StringReader;
private:
	///获得文件全名
	QString getFullFileName(const 
		QString& fileName)const;

	/// 获得某个关键字的条目信息
	TDYTypeInfoPtr getTypeInfo(const QString& keyName);

	///能过item,编译assembly
	void compileAssemblyItem(LineItem* item,TDYTypeInfoPtr typeInfo);

	/// 实际进行Parse工作
	bool parse(const QString& contents,const QString& fileName,AssemblyItem* root);

	///发送错误信息
	void emitError(const LineItem* item,const QString& fileName,const QString& errorInfo);
	void emitError(const StringReader& reader,const QString& fileName, const QString& errorInfo);
	void emitError(const CompileInfoItem& errorItem);

	///检测是否重定义
	void redefinition(LineItem* item);

	///检测PART,ASSEMBLY的非法引用
	void unlawfulReference(LineItem* item , TDYTypeInfoPtr typeInfo);

	///不可多选
	void notAllowMultiple(LineItem* item,QList<TDYTypeKeyValuePtr> noMultipleInfoList);

	///必须选多少个
	void mustSelectNumber(LineItem* item,QList<TDYTypeKeyValuePtr> mustMultipleInfoList);

	///不可省略的
	void notOmitted(LineItem* item,QList<TDYTypeKeyValuePtr> noOptimalInfoList);

	///检测值的个数
	void checkValueCount(LineItem* item , TDYTypeInfoPtr typeInfo);

	///检测关键字是否定义
	void checkKeydefine(LineItem* item , TDYTypeInfoPtr typeInfo);

	///是否在特定属性下
	void isUnderProperty(LineItem* item,TDYTypeInfoPtr typeInfo);

	///检测属性值
	void checkPreperty(LineItem* item,TDYTypeInfoPtr typeInfo);

	///检测键值对是否含有空值
	void checkKeyValues(LineItem* item);

private:
	
	///用来存放所有错误
	QList<CompileInfoItem>	_errorItemList;

	QList<CompileInfoObserver*> _observers;
	AssemblyItem*	_assembleItem;

	///是否需要展开引用的文件
	bool	_expandInclude;

	///包含的文件夹
	QStringList _includeFolders;
	
	ItemTemplateManagerSinleton*	_templateManager;
	
	///正在解析的文件全名
	QString			_fullFileName;

	QMap<QString,TDYTypeInfoPtr> _infos;
};

} // end namespace Parse

} // end namespace INSEditor

#endif // MODELPARSER_H
