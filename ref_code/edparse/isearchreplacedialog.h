#ifndef ISEARCHREPLACEDIALOG_H
#define ISEARCHREPLACEDIALOG_H

#include <QDialog>

/*!
*	这是搜索和替换对话框是基类。
*	@author	Jerry He
*	@date	2014.9.17
*/
namespace Ui{
	class SearchKeyWidget;
}
class ISearchReplaceDialog : public QDialog
{
	Q_OBJECT

public:
	enum SearchPlace{SearchInCurrentDocument,SearchInAllOpenDocuments,SearchAll};

	ISearchReplaceDialog(QWidget *parent);
	~ISearchReplaceDialog();


	//search页对应函数

	///搜索时是否区分大小写
	bool isCaseSensitiveSearch() const {return _isCaseSensitive;}

	///搜索时是否要求全词匹配
	bool isCaseWholeWordsSearch() const {return _isMatchWholeWords;}

	///是否启用正则表达式
	bool isUseSearch() const {return _isUse;}

	///group是否为展开状态
	bool isGroupExpandingSearch() const {return _isGroupExpanding;}

	///是否在搜索页面1打开搜索结果
	bool isOpenResultOnPage1Search()const {return _isOpenResultOnPage1;}

	///是否显示文件名字
	bool isShowOnlyFileName()const {return _isShowOnlyFileName;}

	///是否保持被替换内容的文件为修改状态并打开
	bool isKeepReplacedFileOpen()const {return _isKeepReplacedFileOpen;}

	///获得搜索位置，当前文档，当前打开的所有文档以及所有文档
	SearchPlace getSearchPlace()const{return _searchPlace;}

	///获得搜索内容
	virtual QString getSearchContent()const=0;

	//replace页面对应函数

	///获得替换内容
	virtual QString getReplaceContent()const=0;

	///调协类型查找或替换，默认为查找
	virtual void setTypeFindOrReplace(bool showFind=true)=0;

signals:
	///查找下一个信号
	void sigFindNext();

	///查找上一个信号
	void sigFindPrevious();

	///查找全部信号
	void sigFindAll();

	///替换下一个信号
	void sigReplaceNext();

	///替换上一个信号
	void sigReplace();

	///替换全部信号
	void sigReplaceAll();

protected:
	//search页保存的属性

	///是否区分大小写
	bool _isCaseSensitive;

	///是否使用全词匹配
	bool _isMatchWholeWords;

	///是否使用正则表达式
	bool _isUse;

	///是否展开group组
	bool _isGroupExpanding;

	///是否在搜索1页显示结果
	bool _isOpenResultOnPage1;

	///是否只显示文件名
	bool _isShowOnlyFileName;

	///是否保持替换过的文件修改和打开
	bool _isKeepReplacedFileOpen;

	///搜索位置：当前文档，当前打开的所有文档，所有文档
	SearchPlace	_searchPlace;

	//replace页保存的属性.

};

#endif // ISEARCHREPLACEDIALOG_H
