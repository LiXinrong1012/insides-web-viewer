#ifndef PATHPROPERTYDIALOG_H
#define PATHPROPERTYDIALOG_H

#include <QtGui/QDialog>
#include <QPushButton>
#include <QTableWidget>
#include <QColorDialog>
#include "ui_pathpropertydialog.h"
namespace Ui{
	class PathPropertyDialogClass;
}

class ResultViewManager;
class TrackPaths;

class  PathPropertyDialog : public QDialog
{
	Q_OBJECT

public:
	PathPropertyDialog(ResultViewManager* viewManager,QWidget *parent = 0);
	~PathPropertyDialog();
protected:
//	void closeEvent(QCloseEvent * event);
	bool eventFilter( QObject * o, QEvent * e );
	public slots:
		bool insertOnePathItem(bool isVisuable,QString maker,QString text,bool arrow,int width,QString color,int delay,int length);
		void onClearBtnClicked();
		void onRemoveBtnClicked();
		void onImportBtnClicked();
		void onExportBtnClicked();
		void onCloseBtnClicked();
//		void onItemClicked(QTableWidgetItem* item);

private:
	Ui::PathPropertyDialogClass *ui;
	ResultViewManager*			_resultViewManager;
	TrackPaths* _trackPaths;
};

#endif // PATHPROPERTYDIALOG_H
