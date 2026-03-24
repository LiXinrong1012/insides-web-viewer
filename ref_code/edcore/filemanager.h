#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "edcore_global.h"
#include <QObject>

namespace INSEditor{
	namespace Parse{
		class CompileInfoItem;
		class AssemblyItem;
	}
}

enum BuildType{Build_File=300,Build_Row,Build_Column,Build_Info};

/*!
	负责通知editor的中间件
	@date 2014.12.30
	@author jianjun
*/
class EDCORE_EXPORT FileManager : public QObject
{
	Q_OBJECT

public:
	static FileManager* instance();

public:
	///通知编辑器打开文件
	void notifyOpenFile(const QString& fullFileName);

	///通知output框更新编译内容
	void notifyUpdateOutputInfo(const INSEditor::Parse::CompileInfoItem& item);

	///通知output框更新开始 要求初始化output
	void notifyBeginBuild();

	///通知output框更新完成 进入收尾工作
	void notifyEndBuild();

	///通知mdiarea定位
	void notifyGotoPosition(const QString& fullFileName,int rowIndex,int columnIndex);

	///通知编译工程
	void notifyBuildProject();

	///更新icon的可用状态
	void notifyUpdateIcon();

	///通知开始求解选中工程
	void notifySolveProject();

	///重新导入解决方案时，清空求解
	void notifyClearSolve();

	///build时通知更新MODEL
	void notifyUpdateModel(INSEditor::Parse::AssemblyItem* item,const QString& fileName);

	///通知展开MODEL树
	void notifyExpandModelTree();

	///output显示信息，暂留测试用
	void notifyTestOutput(QString s);

public slots:
	///保存文件供主程序action调用
	void onSaveFile();

signals:
	void requestOpenFile(const QString& fullFileName);

	void requestUpdateOutputInfo(const INSEditor::Parse::CompileInfoItem& item);

	void requestBeginBuild();

	void requestEndBuild();

	void requestGotoPosition(const QString& fullFileName,int rowIndex,int columnIndex);

	void requestSaveFile();

	void requestBuildProject();

	void requestUpdateIcon();

	void requestSolveProject();

	void requestClearSolve();

	void requestUpdateModel(INSEditor::Parse::AssemblyItem* item,const QString& fileName);

	void requestExpandModelTree();

	void requestTestOutput(QString s);

	void requestAddSolveProject();

private:
	FileManager(QObject *parent);
	~FileManager();
	Q_DISABLE_COPY(FileManager);
};

#endif // FILEMANAGER_H
