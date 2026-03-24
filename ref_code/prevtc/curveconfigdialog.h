#ifndef CURVECONFIGDIALOG_H
#define CURVECONFIGDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "qcustomplot/qcustomplot.h"
namespace Ui {class CurveConfigDialog;};

class CustomCurvePlot;
class CurvePointsTracer;
namespace INSIDES{
	class MimeData;
}

struct AxisSetting;

/*!
*	@brief   视图配置保存对话框，用于保存视图配置
*	@author	 Jianjun
*	@date	 2014.12.24
*/
class CurveConfigDialog : public QDialog
{
	Q_OBJECT

public:
	CurveConfigDialog(QCustomPlot* plot);
	~CurveConfigDialog();

	///获得配置文件路径
	const QString& getConfigDir()const{return _configDir;}

private slots:
	///导入当前配置
	void openConfig();

	///导出当前配置
	void saveConfig();

	///当项目被点击时调用
	void onItemClicked ( QTreeWidgetItem * item, int column );

	///删除选中配置
	void deleteConfig();

	///对当前选中的配置进行重命名
	void renameConfig();

	///上移或下移按钮被点击时调用
	void upOrDownBtnClicked();

	///导出按钮点击时调用
	void onExportBtnClicked();

	///导入按钮点击时调用
	void onImportBtnClicked();

	///当树节点被双击时调用，更改为当前配置
	void onTreeItemDoubleClicked( QTreeWidgetItem * item, int column );

private:
	///将树列表更新到树上
	void initTree();

	///导入指定ID的数据
	void importData(INSIDES::MimeData& mimeData,INSIDES::MimeData& yMimeData,const QString& id );

	///名字是否合法
	bool isLegal(const QString& str);

private:
	Ui::CurveConfigDialog *ui;

	QCustomPlot* _customPlot;
	
	QString _configDir;

};

#endif // CURVECONFIGDIALOG_H
