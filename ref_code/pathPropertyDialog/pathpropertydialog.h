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


class  PathPropertyDialog : public QDialog
{
	Q_OBJECT

public:
	PathPropertyDialog(QWidget *parent = 0);
	~PathPropertyDialog();
	public slots:
		bool insertOnePathItem(bool isVisuable,QString maker,QString text,bool arrow,int width,QString color,int delay,int length);
		void onClearBtnClicked();
		void onRemoveBtnClicked();
		void onImportBtnClicked();
		void onExportBtnClicked();
		void onItemClicked(QTableWidgetItem* item);

private:
	Ui::PathPropertyDialogClass *ui;
};

#endif // PATHPROPERTYDIALOG_H
