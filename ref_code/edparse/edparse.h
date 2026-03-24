#ifndef EDPARSE_H
#define EDPARSE_H


#include "edparse/edparse_global.h"
#include "edparse/EDParsePlugin.h"
#include "edparse/errortablemodel.h"



class QTreeView;
class SolutionWidget;
class QTableView;
class QSortFilterProxyModel;
class OutputListWidget;

/*!
	@brief   负责支持主要界面框架的插件
	@date    2015.6.17
	@author  Jianjun
*/
class EDPARSE_EXPORT EDParse: public QObject, public EDParsePlugin
{
	Q_OBJECT

	///此类为插件
	Q_INTERFACES(EDParsePlugin)

public:
	EDParse();
	~EDParse();

	///获得插件名字
	virtual QString getKeyname();

	///初始化该插件部分的界面
	virtual void initUI(QMainWindow* mainWindow);

	///获得搜索替换对话框
	virtual ISearchReplaceDialog* getSearchReplaceDialog();

public slots:
	///展开模型树
	void onExpandModelTree();
	
private slots:
	///当工程加载时调用，暂时未启用
	void onProjectLoaded();

	///当工程项增加时调用，暂时未启用
	void onProjectItemAdded();

	///保存设置，暂时未启用
	void saveSetting( const QModelIndex & index);

	///加载设置，暂时未启用
	void loadSetting();
		
private:
	///主窗口指针
	QMainWindow* _mainWindow;

	///模型树指针
	QTreeView*	_modelTreeView;

	///输出窗口指针
	OutputListWidget*  _outputListWidget;

	///解决方案窗口指针
	SolutionWidget*	_solutionWidget;

	///错误表格窗口
	QTableView* _errorTableView;

	///错误代理模型类
	QSortFilterProxyModel* _errorProxyModel;

	///搜索和替换窗口指针 
	ISearchReplaceDialog*	_searchReplaceDialog;
};

#endif // EDPARSE_H
