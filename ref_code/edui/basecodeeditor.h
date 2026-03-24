#ifndef INSIDES_BASECODEEDITOR_H
#define INSIDES_BASECODEEDITOR_H

#include <Qsci/qsciscintilla.h>
#include <QMap>

#include "edcompile/tdytypeinfomanager.h"
#include "edcompile/modelparser.h"

class QShortcut;
class QFileSystemWatcher;
class QsciAPIs;

namespace INSEditor{
	namespace Parse
	{
		class AssemblyItem;
	}
}

/*!
	@brief   主窗口模型文件编辑器
	@date    2015.6.18
	@author  Jerry
*/
class BaseCodeEditor : public QsciScintilla
{
	Q_OBJECT

public:
	BaseCodeEditor(QWidget *parent);
	~BaseCodeEditor();

	///设置当前的文件名字
	void setFileName(const QString& fileName){_fileName=fileName;}

	///获取当前文件名
	const QString& getFileName()const{return _fileName;}

	///创建新的文件 
	void openOrCreateFile(const QString& fileName);

	///测试marker
	void testMarker();

	///测试anntation
	void testAnnotation();

	///获取是否需要编译
	bool needCompiling()const{return _needCompiling;}

	///设置是否需要编译
	void setNeedCompiling(bool b){_needCompiling=b;}

	///获得文字字体
	static QFont getTextFont(){return _textFont;}

	///设置文字字体
	static void setTextFont(const QFont& font){_textFont=font;}

	///添加监视文件，当文件在本软件外部发生改变时提示是否重新载入
	void addWatchFile(const QString& fileName);

	///删除监视文件
	void removeWatchFile(const QString& fileName);

public slots:
	///只在当前文件
	void save();

signals:
	///编辑器正在关闭时调用 
	void widgetClosing(BaseCodeEditor* w);

	///打开名为fileName的文件，在激活时调用 
	void gotoFile(const QString& fileName);

protected slots:
	///当当前文件改变时窗口标题以文件名+*显示
	void onModificationChanged();

	///当有字符增加时调用（未启用）
	void onCharAdded(int charAdded);

	///当文字改变时标记为需要编译状态
	void onTextChanged();

	///获得当前行号
	int getCurrentLineNumber();

	///减小字体
	void decreaseFont();

	///增大字体
	void increaseFont();

	///打开该文件
	void onOpenFile();

	///当被监视的文件改变时
	void onFileChanged(const QString& filaName);

	///定时编译模型文件生成最新树用作提示计算 
	void onTimeouted();

	///当光标位置改变时调用，根据光标位置不同来计算不同的提示内容 
	void onCursorPositionChanged(int line,int index);

	///定位到part等引用的定义位置
	void onGotoDefinition();

protected:
	///重写关闭事件，如果有更改内容未保存则提示
	virtual void closeEvent(QCloseEvent *event);

	///重写上下文菜单事件
	virtual void contextMenuEvent (QContextMenuEvent *e);

	///重写事件过滤器事件
	virtual bool eventFilter ( QObject * object, QEvent * event );

	///初始化材质相关需要用到的提示内容
	void initMaterial();

	///获得本行内容 
	int getLineText(int lineId,QString& str);

	///获得引用文件的文件名开始位置
	int getFileStartPos(int pos);

	///获得引用文件的文件名的结束位置
	int getFileEndPos(int pos);

	///提示API内容更新
	void updateAPI(QsciAPIs* apis);

	///得到本句关键字
	QString getKeyWords();

	///得到当前光标处词语并返回当前对应的行号,isFullName = true ,得到结果为 bbbb,如果isFullName = false ,得到结果为 aaaa.bbbb.cccc
	QString getCurrentWords(bool isFullName=false);
	
	///更新提示总函数
	void updatePrompt();

	///更新所有可用的提示
	void updatePromptWords();

	///更新引号中可以出现的关键字为提示
	void updateInYinWords();

	///更新与某个词相关的提示
	void updatePromptWords(QString keyWord);

	///返回‘＝’前的词
	QString isPartEqualBefore(bool& exist);
	
	///更新PART相关提示
	void updatePromptWordsWithPart();
	
	///更新PART可引用的API
	void updatePartApi(INSEditor::Parse::LineItem* assItem,QString prefix);

	///显示光标处的关键字帮助
	void showHelp();
	
	///真正执行显示光标处关键字帮助的函数
	void showHelp(QString keyWord,QString word,int line);

	///整理某个INSTANCE中XXXX对应的提示
	void setKeyValues(INSEditor::Parse::LineItem* key);

	///整理一些提示
	void tidyAssItem(INSEditor::Parse::AssemblyItem* assItem);

	///找到Part所引用AssItem
	void getPartAssItem(const QString& mainLabel,INSEditor::Parse::AssemblyItem* assItem,const QStringList& types);

	///更新_keyvalues
	void updatePartStrList(INSEditor::Parse::AssemblyItem* assItem,QString key ,QStringList& list);

	///更新一些位置信息
	void updateSomePos();

	///在parentItem中通过给定的keyword和line找到自己
	INSEditor::Parse::LineItem* getAssItemByKeyword(const QString& keyword,int line);
	void getAssItemByKeyword(INSEditor::Parse::AssemblyItem* item,const QString& keyword,QList<INSEditor::Parse::LineItem*>& list);

private:
	///更新part相关提示，区分assembly
	void updatePartPrompt(const QString& type);

	///当按下ENTER键
	void onPressEnter();
	
	///当按下CTRL+P
	void onPressCtrlP();
	
	///当按下等号键
	void onPressEqual();
	
	///item为自已，查找list中的一系列子成员，已经查找到了第POS个，配合FOR使用
	INSEditor::Parse::LineItem* getGotoItem(QStringList list,int pos,INSEditor::Parse::LineItem* item);
	
	///建立模型
	void building();
private:
	///当前编辑器显示的文件的名字
	QString _fileName;

	///保存文档快捷键
	QShortcut*	_saveDocument;

	/// 是否需要进行编译
	bool		_needCompiling;
	
	///监视打开的文件是否在外部更改
	QFileSystemWatcher*			_watcher;

	///文本是否被修改
	bool	_isTextModified;

	///文本字体
	static QFont	_textFont;
	
	///记录编译时间的计时器吗
	QTimer*		_buildTimer;

	///存放某关键字对应提示的列表 
	QMap<QString,QStringList> _proMap;
//	QMap<QString,QStringList> _keyValueMap;

	///提示管理指针
	QsciAPIs* _apis;

	///用来存放所有的键
	QStringList _allKeyNames;

	///当前键
	int _currentKey;

	///关键字所在行
	int _keyWordLine;

	///用来定时编译的计时器
	QTimer* _timer;

	///用来存放所有从ins.xml在读取的TDYTypeInfoPtr
	QMap<QString,INSEditor::Parse::TDYTypeInfoPtr> _tdyInfoList;
	
	///用于解析整理树形结构所须变量
	INSEditor::Parse::AssemblyItem* _assemblyItem;
	INSEditor::Parse::ModelParser _parser;
	INSEditor::Parse::TDYTypeInfoManager _typeManager;
	
	///文本最后一次变化过时间
	int _textChangedTime;
	bool _isRunning;
	
	///存放某个关键词对应的提示
	QMap<QString,QStringList> _keyValues;

	///存放part引用ITEM
	INSEditor::Parse::AssemblyItem* _partRefItem;

	//逗号行和当前行
	int _comLine,_cuLine,_numletLine;

	//逗号位置，括号位置，数字或字母位置，引号位置，等号位置
	int _comPos,_kuoPos,_numletPos,_yinPos,_dengPos;
	
	//是否在引号之中
	bool _inYin;

	//支持引用的keyName 已知I，J
	QStringList _kList;

	///有存放材质文件列表
	QString _materialStr;
};

#endif // INSIDES_BASECODEEDITOR_H
