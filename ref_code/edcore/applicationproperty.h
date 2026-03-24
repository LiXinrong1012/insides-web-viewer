#ifndef APPLICATIONPROPERTY_H
#define APPLICATIONPROPERTY_H

#include "edcore/edcore_global.h"
#include <QString>

namespace INSEditor{

/*!
	@brief 储存程序的全局设置。
	@author	Jerry He
	@date	2014.11.19
*/
class EDCORE_EXPORT ApplicationProperty
{
public:
	ApplicationProperty();

	///dir config
	///后处理所在目录
	QString		viewerExecutablePath;
	///求解器目录
	QString		solverExecutablePath;
	///文件对比程序目录
	QString		fileDiffExecutablePath;
	///材质库位置
	QString		materialLibraryPath;

	///format config
	///格式化控制，缩进空格数
	int			formatIndentationValue;
	///格式化控制，每行最大空格数
	int			formatLineMaxNumValue;

	///solve config
	///求解器界面LOGS更新频率
	int			logsUpdateFrequency;
	///求解时树上进度条更新频率
	int			treeProcessUpdateFrequency;
	///最大同时求解工程数
	int			maxSolveNumber;
	///求解时是否显示界面
	bool		isShowSolverUI;

	///custom config
	///是否显示上次打开的文件
	bool		isShowLastOpenedFiles;
	///是否更新模型树
	bool		isCreateModelTree;
	///是否自动显示帮助
	bool		isAutoShowHelp;

	///system config
	///是否在每次打开软件时自动检测更新
	bool		isAutoCheckUpdate;

	/// 从设置中恢复
	void load();

	/// 保存到设置
	void save();
};

} // end namespace INSIDES

#endif // APPLICATIONPROPERTY_H
