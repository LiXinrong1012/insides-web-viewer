#ifndef DIRCONFIGWIDGET_H
#define DIRCONFIGWIDGET_H

#include <QWidget>
namespace Ui {class DirConfigWidget;};

/*!
	@biref 路径相关设置界面
	@date  2015.6.3
	@author Jianjun
*/
class DirConfigWidget : public QWidget
{
	Q_OBJECT

public:
	DirConfigWidget(QWidget *parent = 0);
	~DirConfigWidget();

	///设置或获取后处理所在路径
	void setViewPathEditText(const QString& text);
	QString getViewPathEditText();

	///设置或获取求解器所在路径
	void setSolverPathEditText(const QString& text);
	QString getSolverPathEditText();

	///设置或获取比对程序所在路径
	void setFileDiffEditText(const QString& text);
	QString getFileDiffEditText();

	///设置或获取材质库所在路径
	void setMaterialLibraryEditText(const QString& text);
	QString getMaterialLibraryEditText();

private slots:
	void onViewerSelectPathToolButtonClicked();
	void onSolverSelectPathToolButtonClicked();
	void onSelectPathToolButton_3Clicked();
private:
	Ui::DirConfigWidget *ui;
};

#endif // DIRCONFIGWIDGET_H
