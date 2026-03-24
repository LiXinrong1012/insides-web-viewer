#ifndef VIEWEROPTIONS_H
#define VIEWEROPTIONS_H

#include <QDialog>
#include "HBaseView.h"

class LightingWidget;
namespace Ui {class ViewerOptionsDialog;};

class ViewerOptionsDialog : public QDialog
{
	Q_OBJECT

public:
	ViewerOptionsDialog(HBaseView* view);
	~ViewerOptionsDialog();

private:
	Ui::ViewerOptionsDialog *ui;
	HBaseView* _hBaseView;
	LightingWidget* _lightingWidget;


	QList<QWidget*>	_widgetList;
};

#endif // VIEWEROPTIONS_H
