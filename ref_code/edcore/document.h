#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "edcore/edcore_global.h"
#include <QObject>
#include <QSharedPointer>

#include "edcore/applicationproperty.h"

class ViewerProcess;
namespace INSEditor
{
class Solution;
class SolveProcess;

/*!
	@brief 解决方案以及属性设置管理单例
	@date  2015.6.5
	@author Jerry
*/
class EDCORE_EXPORT Document : public QObject
{
	Q_OBJECT

public:
	///获得唯一document指针
	static Document* instance();

	///销毁程序
	static void destruct();

	///打开解决方案
	Solution* open(const QString& solutionName);

	///创建新的解决方案
	Solution* createNew(const QString& dir,const QString& solutionName);

	/// 关闭解决方案，提示用户保存
	void close();
	
	///获得当前解决方案指针
	Solution* getSolution(){return _solution.data();}

	///获得当前程序设置属性
	ApplicationProperty* getProperties(){return _properties;}

	///设置程序设置属性
	void setProperties(ApplicationProperty* ap);

	///请求SolveProcess更新
	void requestSolveProcessUpdate(SolveProcess* process);

signals:
	///解决方案关闭后发出
	void solutionClosed(Solution* solution);

	///解决方案被创建后发出
	void solutionCreated(Solution* solution);

	///SolveProcess改变时发出
	void solveProcessChanged(SolveProcess* process);

public slots:
	///显示属性设置对话框
	void showApplicationSetting();

	///启动帮助程序
	void startHelpApplication();

private:
	Document(QObject *parent);
	~Document();

	typedef QSharedPointer<Solution> SolutionPtr;

	SolutionPtr					_solution;
	ApplicationProperty*		_properties;

	static Document*			_instance;
};


}

#endif // DOCUMENT_H
