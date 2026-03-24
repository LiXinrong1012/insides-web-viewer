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
*	视图配置保存对话框，用于保存视图配置
*	@author	Jianjun
*	@date	2014.12.24
*/
class CurveConfigDialog : public QDialog
{
	Q_OBJECT

public:
	CurveConfigDialog(QCustomPlot* plot);
	~CurveConfigDialog();

	///获得配置路径
	QString getConfigDir()const{return _configDir;}

private slots:
	///导入当前配置
	void openConfig();

	///导出当前配置
	void saveConfig();

	///当条目被点击时调用
	void onItemClicked ( QTreeWidgetItem * item, int column );

	///删除配置
	void deleteConfig();

	///重命名配置
	void renameConfig();

	///向上按钮或向下按钮被点击时调用
	void upOrDownBtnClicked();

	///导出按钮被点击时调用
	void onExportBtnClicked();

	///导入按钮被点击时调用
	void onImportBtnClicked();

	///当树条目被双击时调用
	void onTreeItemDoubleClicked( QTreeWidgetItem * item, int column );

private:
	Ui::CurveConfigDialog *ui;

	///曲线视图指针
	QCustomPlot* _customPlot;

	///配置路径
	QString _configDir;

private:
	///对树进行初始化
	void initTree();

	///导入指定ID的数据
	void importData(INSIDES::MimeData& mimeData,INSIDES::MimeData& yMimeData,const QString& id );

	///名字是否合法
	bool isLegal(const QString& str);
	
};

#endif // CURVECONFIGDIALOG_H
