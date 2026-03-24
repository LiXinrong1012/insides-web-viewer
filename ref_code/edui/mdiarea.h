#ifndef MDIAREA_H
#define MDIAREA_H

#include <QMdiArea>
#include <QMap>
#include <QDateTime>


class QTreeView;
class QTimer;
class QFontComboBox;
class QComboBox;


class BaseCodeEditor;
class ModelViewModel;
class QModelIndex;
class ViewerWrapper;
class INSEntity;
class EDParsePlugin;
class FindResultItem;

namespace Qtitan{
	class RibbonBar;
	class RibbonPage;
	class RibbonGroup;
}
namespace INSEditor{
	namespace Parse{
		class AssemblyItem;
	}
}

/*!
	@brief   带有时间的assemblyItem,未启用。
	@date    2015.6.23
	@author  Jerry
*/
class AssemblyItemWithTime
{
public:
	QDateTime dataTime;
	INSEditor::Parse::AssemblyItem* item;
};

/*!
	@brief   负责软件主窗口布局整体管理 
	@date    2015.6.23
	@author  Jerry
*/
class MdiArea : public QMdiArea
{
	Q_OBJECT
public:
	MdiArea(QWidget* parent,ViewerWrapper* viewerWrapper);
	virtual ~MdiArea();

	///创建字体的ribbonBar
	void createRibbonBar(Qtitan::RibbonPage* page);

	///添加一个窗口w到界面
	void addMyWindow(BaseCodeEditor* w);

	///通过文件名获得对应窗口
	QMdiSubWindow* getMyWidget(const QString& fileName);

	///初始化搜索替换对话框的相关槽
	void setEDParsePlugin(EDParsePlugin* p);

	///获得子窗口window对应的文件 
	QString getCurrentFile(QMdiSubWindow* window)const;

	///获得当前所有打开的文件
	QStringList getOpenFiles()const;

	///设置当前所有打开的文件 
	void setOpenFiles(QStringList list)const;

public slots:
	///当窗口关闭时调用
	void onWidgetClosing(BaseCodeEditor* w);

	///激活或打开文件fullFileName
	void activateOrOpenFile(const QString& fullFileName);

	///缩小字体
	void decreaseFont();

	///增大字体
	void increaseFont();

protected slots:
	/// 某个子窗口被激活时
	void onSubWindowActivated( QMdiSubWindow* window );

	/// 光标定位到某个文件的某个位置
	void onGotoPosition(const QString& fullFileName,int rowIndex,int columnIndex);

	/// 执行编译改变的文件内容
	void onCompileTimer();

	/// 查找条目被激活时
	void onFindResultItemActivated(const FindResultItem& resultItem);

	/// 打开查找对话框
	void openFindDialog();

	///打开替换对话框
	void openReplaceDialog();

	///查找下一个对应槽
	void onFindNext();

	///查找上一个对应槽(未实现)
	void onFindPrevious();

	///查找全部对应槽
	void onFindAll();

	///替换下一个对应槽
	void onReplaceNext();

	///替换全部对应槽
	void onReplaceAll();

	///关闭当前
	void closeCurr();

	///关闭所有除了当前
	void closeAllButThis();

	///copy当前打开文件的完整路径
	void copyFullPath();

	///在资源管理中打开
	void openContainingFolder();

	///获得相应字体后设置
	void optionFont();

	///字体加粗
	void textBold();

	///字体倾斜
	void textItalic();
	
	///更改字体（如宋体，黑体）
	void textFamily(const QString &f);

	///更改字大小，如（18，24.5）
	void textSize(const QString &p);

protected:
	///重写paintEvent方法
	virtual void paintEvent(QPaintEvent* paintEvent);
	
	///创建字体组
	void createGroupFont(Qtitan::RibbonGroup* group);

	///创建编辑组
	void createGroupEditing(Qtitan::RibbonGroup* group);

	///更新字体
	void updateFont(const QFont& font);

	///查看子窗口subWindow是否存在
	bool findInWindow(QMdiSubWindow* subWindow);

	///打开所有文档，未实现
	void openAllDocuments();

	///初始化subWindow的菜单
	void initSubWindowMenu(QMdiSubWindow* tmp,BaseCodeEditor* editor);

private:
	///文件名与子窗口相对应的MAP
	QMap<QString,QMdiSubWindow*>	_windows;

	///当前激活的子窗口
	QMdiSubWindow*					_currentActivatedWindow;

	///用于和后处理通信的类
	ViewerWrapper*					_viewerWrapper;

	///编译计时定时器
	QTimer*							_compileTimer;

	///edparse插件
	EDParsePlugin*					_edparsePlugin;

	///增大字体的action
	QAction*						_increaseFont;

	///减小字体的action
	QAction*						_decreaseFont;

	///字体选择下拉框
	QFontComboBox*					_comboFont;

	///字体大小选择下拉框
	QComboBox*						_comboSize;

	///是否使用黑体的action
	QAction*						_actionTextBold;

	///是否使用倾斜的action
	QAction*						_actionTextItalic;
};

#endif // MDIAREA_H
